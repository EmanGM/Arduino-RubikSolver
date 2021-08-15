package com.example.rubiksensor

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle

import android.app.ProgressDialog
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothSocket
import android.content.Context
import android.content.Intent
import android.os.AsyncTask
import android.util.Log
import com.google.android.material.floatingactionbutton.FloatingActionButton
import com.google.android.material.snackbar.Snackbar
import com.google.android.material.tabs.TabLayout
import androidx.viewpager.widget.ViewPager
import org.opencv.android.OpenCVLoader
import java.io.IOException
import java.util.*

class MainActivity : AppCompatActivity() {


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        ConnectDeviceTo(this).execute()
    }

    companion object {
        var myUUID: UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB")
        private var myBTSocket: BluetoothSocket? = null
        //lateinit var m_progress: ProgressDialog
        lateinit var m_bluetoothAdapter: BluetoothAdapter
        private var isConnected: Boolean = false
        private var m_adress: String = "98:D3:21:F4:96:AC"

        public fun sendCommand(input: String) {
            if(myBTSocket != null) {
                try {
                    myBTSocket!!.outputStream.write(input.toByteArray())
                    //Toast.makeText(this, input, Toast.LENGTH_LONG).show()
                } catch (e: IOException) {
                    e.printStackTrace()
                }
            } else {
                //Toast.makeText(this, "bluetooth sockect = null", Toast.LENGTH_LONG).show()
            }
        }
    }


    fun disconnect() {
        if (myBTSocket != null) {
            try {
                myBTSocket!!.close()
                myBTSocket = null
                isConnected = false
            } catch (e: IOException) {
                e.printStackTrace()
            }
        }
        finish()
    }

    private class ConnectDeviceTo(ctx: Context) : AsyncTask<Void, Void, String>() {
        private var connectedSuccess : Boolean = true
        private val context: Context = ctx

        override fun onPreExecute() {
            super.onPreExecute()
            //m_progress = ProgressDialog.show(context, "Connecting...", "Aguarde!")
        }

        override fun doInBackground(vararg params: Void?): String? {
            try {
                if (myBTSocket == null || !isConnected) {
                    m_bluetoothAdapter = BluetoothAdapter.getDefaultAdapter()
                    val device: BluetoothDevice = m_bluetoothAdapter.getRemoteDevice(m_adress)
                    myBTSocket = device.createInsecureRfcommSocketToServiceRecord(myUUID)
                    BluetoothAdapter.getDefaultAdapter().cancelDiscovery()
                    myBTSocket!!.connect()
                }
            } catch (e: IOException) {
                connectedSuccess = false
                e.printStackTrace()
            }
            return null
        }

        override fun onPostExecute(result: String?) {
            super.onPostExecute(result)
            if (!connectedSuccess) {
                Log.i("connectDeviceTo", "impossivel ligar")
            } else {
                isConnected = true
            }
            //m_progress.dismiss()
        }
    }
}