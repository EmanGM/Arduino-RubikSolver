package com.example.rubiksensor


import android.app.Activity
import android.content.pm.PackageManager
import android.os.Bundle
import android.util.Log
import android.view.SurfaceView
import android.view.WindowManager
import android.widget.Button
import android.widget.Toast
import androidx.core.content.ContextCompat
import org.opencv.android.*
import org.opencv.core.*
import org.opencv.imgproc.Imgproc
import java.lang.StringBuilder
import java.util.*
import kotlin.collections.ArrayList


class CameraActivity : Activity(), CameraBridgeViewBase.CvCameraViewListener2 {

    private lateinit var cameraView: JavaCameraView
    private lateinit  var frame: Mat
    private val CAMERA_PERMISSION_REQUEST = 50

    private val colorsMask = arrayOf(arrayOf(Scalar(96.0, 110.0, 110.0), Scalar(130.0, 256.0, 256.0)), //azul
            arrayOf(Scalar(5.0, 120.0, 165.0), Scalar(17.0, 256.0, 256.0)), //laranja
            arrayOf(Scalar(21.0, 55.0, 117.0), Scalar(40.0, 256.0, 256.0)), //amarelo
            arrayOf(Scalar(45.0, 80.0, 120.0), Scalar(76.0, 256.0, 256.0)), //verde
            arrayOf(Scalar(165.0, 114.0, 0.0), Scalar(179.0, 256.0, 256.0)), //vermelho
            arrayOf(Scalar(0.0, 2.0, 150.0), Scalar(255.0, 60.0, 256.0)), //branco
            arrayOf(Scalar(0.0, 114.0, 136.0), Scalar(4.0, 256.0, 256.0))) //2º vermelho


    private val rectColors = arrayListOf(Scalar(10.0, 207.0, 20.0), Scalar(7.0, 7.0, 237.0), Scalar(255.0, 255.0, 255.0),
            Scalar(252.0, 5.0, 6.0), Scalar(10.0, 111.0, 242.0), Scalar(96.0, 255.0, 242.0))
    private var corners = arrayListOf(arrayOf<Int>())
    private var modeIsStickers = false
    private var faceText = ""
    private var toCapture = false

    private val mLoaderCallback = object : BaseLoaderCallback(this) {
        override fun onManagerConnected(status: Int) {
            when (status) {
                LoaderCallbackInterface.SUCCESS -> {
                    Log.i("CameraActivity", "OpenCV loaded successfully")

                    cameraView.enableView()
                }
                else -> {
                    super.onManagerConnected(status)
                }
            }
        }
    }


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        window.addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        setContentView(R.layout.camera)

        modeIsStickers = intent.extras!!.getBoolean("modeIsStikers")

        if(OpenCVLoader.initDebug()) {
            Log.i("CameraActivity", "funcionou!!")
        } else {
            Log.i("CameraActivity", "Não é desta!")
        }

        cameraView = findViewById(R.id.my_camera_view)
        cameraView.visibility = SurfaceView.VISIBLE
        cameraView.setCvCameraViewListener(this)
        cameraView.enableFpsMeter()

        findViewById<Button>(R.id.capture).setOnClickListener {
            toCapture = true
            //Toast.makeText(this, faceText, Toast.LENGTH_SHORT).show()
        }

        findViewById<Button>(R.id.quitCameraAct).setOnClickListener {
            MainActivity.disconnect()
            finish()
        }

        if (ContextCompat.checkSelfPermission(this, android.Manifest.permission.CAMERA) != PackageManager.PERMISSION_GRANTED) {
            Log.d("CameraActivity", "Permissions not granted")
        } else {
            Log.d("CameraActivity", "Permissions granted")
            cameraView.setCameraPermissionGranted()
        }

    }


    override fun onRequestPermissionsResult(
            requestCode: Int,
            permissions: Array<String>,
            grantResults: IntArray
    ) {
        Log.d("CameraActivity", "permition")
        when (requestCode) {
            CAMERA_PERMISSION_REQUEST -> {
                if (grantResults.isNotEmpty() && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    cameraView.setCameraPermissionGranted()
                } else {
                    val message = "Camera permission was not granted"
                    Log.e("CameraActivity", message)
                    Toast.makeText(this, message, Toast.LENGTH_LONG).show()
                }
            }
            else -> {
                Log.e("CameraActivity", "Unexpected permission request")
            }
        }
    }


    override fun onCameraViewStarted(width: Int, height: Int) {
        Log.d("CameraActivity", "Camera started $width  $height")
        frame = Mat(height, width, CvType.CV_8UC4)
    }

    override fun onCameraViewStopped() {
        Log.d("CameraActivity", "Camera parou")
        frame.release()
    }


    override fun onCameraFrame(inputFrame: CameraBridgeViewBase.CvCameraViewFrame?): Mat {

        frame = inputFrame!!.rgba()

        val originalSize = frame.size()

        var img = Mat()
        if(modeIsStickers) {
            img = processImg(frame)
            configureFace()
        } else {
            img = processSquares(frame)
            sendColors()
        }

        Imgproc.cvtColor(img, frame, Imgproc.COLOR_BGR2RGBA)
        Imgproc.resize(frame, frame, originalSize)
        img.release()

        System.gc()
        System.runFinalization()

        return frame
    }

    private fun processImg(tempFrame: Mat): Mat {
        val imgHSV = Mat()
        Imgproc.cvtColor(tempFrame, tempFrame, Imgproc.COLOR_RGBA2BGR)
        Imgproc.cvtColor(tempFrame, imgHSV, Imgproc.COLOR_BGR2HSV)


        val fullMask = Mat.zeros(tempFrame.size(), CvType.CV_8U)
        for(i in 0..5) {

            val mask = Mat()
            Core.inRange(imgHSV, colorsMask[i][0], colorsMask[i][1], mask)
            if(i == 4) {
                val provisory = Mat()
                Core.inRange(imgHSV, colorsMask[6][0], colorsMask[6][1], provisory)
                Core.bitwise_or(provisory, mask, mask)
                provisory.release()
            }
            if (i != 0) {
                Core.bitwise_or(fullMask, mask, fullMask)
            } else {
                Core.bitwise_or(mask, mask, fullMask)
            }

            val result = Mat()
            //Imgproc.cvtColor(tempFrame, tempFrame, Imgproc.COLOR_BGR2RGBA)
            Core.bitwise_and(tempFrame, tempFrame, result, mask)

            val imgGray = Mat()
            Imgproc.cvtColor(result, imgGray, Imgproc.COLOR_RGBA2GRAY)
            val contours: List<MatOfPoint> = ArrayList()
            Imgproc.findContours(imgGray, contours, Mat(), Imgproc.RETR_TREE, Imgproc.CHAIN_APPROX_SIMPLE)

            for (contourIdx in contours.indices) {
                val rect = Imgproc.boundingRect(contours[contourIdx])
                if (rect.height in 140..200 && rect.width in 140..200 && rect.height - rect.width <= 10) {
                    Imgproc.rectangle(tempFrame, rect.tl(), rect.br(), rectColors[i], 10)
                    val miniArr = arrayOf<Int>(i, rect.x, rect.y)
                    corners.add(miniArr)
                }
            }

            //Release Mats to prevent memory leaks!
            mask.release()
            result.release()
            imgGray.release()
        }
        imgHSV.release()

        Log.i("CameraActivity", "size...: " + corners.size.toString())
        for ( ele in corners) {
            for(el in ele)
                Log.i("CameraActivity", el.toString())
        }

        val img = Mat()
        Core.bitwise_and(tempFrame, tempFrame, img, fullMask)
        tempFrame.release()
        return img
    }

    private fun configureFace() {

        val face = arrayOf(arrayOf(" ", " ", " "), arrayOf(" ", " ", " "), arrayOf(" ", " ", " "))
        val index2color = arrayListOf<String>("B", "O", "Y", "G", "R", "W")
        if(corners.size == 10) {

            mySort(1, corners.size, 1)
            for (i in 0 until 3) {
                mySort(i * 3 + 1, i * 3 + 4, 2)
            }

            var column = 0
            var row = 0
            for (c in 1 until corners.size) {
                face[row][column++] = index2color[corners[c][0]]
                if (column > 2) {
                    column = 0
                    row++
                }
            }

            if (toCapture) {
                faceText = ""
                for (ele in face) {
                    for (el in ele) {
                        Log.i("Cube", el.toString())
                        faceText += el
                    }
                    //faceText += "\n"
                }
                Log.i("Cube", "#\n\n")
                toCapture = false
                MainActivity.sendCommand(faceText)
            }
        }
        corners = arrayListOf(arrayOf<Int>())
    }

    private fun sendColors() {

        if(toCapture && faceText.length == 9) {
            val builder = StringBuilder()
            builder.append(faceText[8])
            builder.append(faceText[5])
            builder.append(faceText[2])
            builder.append(faceText[7])
            builder.append(faceText[4])
            builder.append(faceText[1])
            builder.append(faceText[6])
            builder.append(faceText[3])
            builder.append(faceText[0])
            MainActivity.sendCommand(builder.toString())
        }
        toCapture = false
    }

    private fun processSquares(tempFrame: Mat) : Mat {
        val imgHSV = Mat()
        Imgproc.cvtColor(tempFrame, tempFrame, Imgproc.COLOR_RGBA2BGR)
        Imgproc.cvtColor(tempFrame, imgHSV, Imgproc.COLOR_BGR2HSV)

        val offsetX = 280
        val offsetY = 100
        val width = 110
        val height = 110
        faceText = ""

        for (row in 0..2) {
            for (column in 0..2) {
                val rectCrop = Rect(offsetX + column * 190, offsetY + row * 190, width, height)
                val imageROI = Mat(imgHSV, rectCrop)
                val mean = Core.mean(imageROI)
                val color = getCorrectColor(mean)
                if(color != "No color found!") {
                    var index = -1;
                    when(color) {
                        "R" -> index = 1
                        "G" -> index = 0
                        "B" -> index = 3
                        "Y" -> index = 5
                        "W" -> index = 2
                        "O" -> index = 4
                    }
                    Imgproc.rectangle(tempFrame, rectCrop.tl(), rectCrop.br(), rectColors[index], -1)
                    faceText += color
                } else {
                    Imgproc.rectangle(tempFrame, rectCrop.tl(), rectCrop.br(), Scalar(0.0, 0.0, 0.0), 2)
                }
                Log.i("corMean", mean.toString())
            }
        }
        Log.i("corMean", "#\n\n")
        imgHSV.release()

        val img = Mat()
        Core.bitwise_and(tempFrame, tempFrame, img)
        tempFrame.release()
        return img
    }

    //Bubble sort
    private fun mySort(start: Int, end: Int, dimension: Int) {
        for (i in start until end) {
            for (j in i until end) {
                if(corners[j][dimension] > corners[i][dimension]) {
                    val temp = corners[i]
                    corners[i] = corners[j]
                    corners[j] = temp
                }
            }
        }
    }

    private fun getCorrectColor(color : Scalar) : String {

        var correctColor = "No color found!"
        for (i in colorsMask.indices) {
            if(colorsMask[i][0].`val`[0] <= color.`val`[0] && color.`val`[0] <= colorsMask[i][1].`val`[0] &&
                    colorsMask[i][0].`val`[1] <= color.`val`[1] && color.`val`[1] <= colorsMask[i][1].`val`[1] &&
                    colorsMask[i][0].`val`[2] <= color.`val`[2] && color.`val`[2] <= colorsMask[i][1].`val`[2]) {
                when(i) {
                    0 -> correctColor = "B";
                    1 -> correctColor = "O";
                    2 -> correctColor = "Y";
                    3 -> correctColor = "G";
                    4, 6 -> correctColor = "R";
                    5 -> correctColor = "W";
                }
            }
        }
        return correctColor
    }

    override fun onResume() {
        super.onResume()
        if (!OpenCVLoader.initDebug()) {
            Log.d("CameraActivity", "Internal OpenCV library not found. Using OpenCV Manager for initialization")
            OpenCVLoader.initAsync(OpenCVLoader.OPENCV_VERSION_2_4_10, this, mLoaderCallback)
        } else {
            Log.d("CameraActivity", "OpenCV library found inside package. Using it!")
            mLoaderCallback.onManagerConnected(LoaderCallbackInterface.SUCCESS)
        }
    }

    override fun onPause() {
        super.onPause()

        cameraView.disableView()
    }

    override fun onDestroy() {
        super.onDestroy()

        cameraView.disableView()
    }

}
