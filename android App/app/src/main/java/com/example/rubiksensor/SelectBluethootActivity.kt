package com.example.rubiksensor


import android.app.Activity.RESULT_CANCELED
import android.app.Activity.RESULT_OK
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.content.Intent
import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.*
import androidx.appcompat.app.AppCompatActivity


class SelectBluetooth : AppCompatActivity() {

    private var m_bluetoothAdapter: BluetoothAdapter? = null
    private lateinit var m_pairedDevices: Set<BluetoothDevice>
    private val REQUEST_ENABLE_BLUETOOTH = 1



    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.bluethoot_init)

        m_bluetoothAdapter = BluetoothAdapter.getDefaultAdapter()
        if(m_bluetoothAdapter == null) {
            Toast.makeText(this, "This device does not support bluetooth", Toast.LENGTH_SHORT).show()
            return
        }

        if(!m_bluetoothAdapter!!.isEnabled) {
            val enableBluetoothIntent = Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE)
            startActivityForResult(enableBluetoothIntent, REQUEST_ENABLE_BLUETOOTH)
        }

        findViewById<Button>(R.id.refresh)?.setOnClickListener {
            pairedDeviceList()
        }

        findViewById<Button>(R.id.jump)?.setOnClickListener {

            val intent = Intent(this, MainActivity::class.java)
            intent.putExtra(EXTRA_ADRESS, "98:D3:21:F4:96:AC")
            startActivity(intent)
        }
        pairedDeviceList()
    }


    private fun pairedDeviceList() {
        m_pairedDevices = m_bluetoothAdapter!!.bondedDevices
        val list : ArrayList<BluetoothDevice> = ArrayList()


        val listItems = arrayOfNulls<String>(m_pairedDevices.size)
        var index = 0
        if (m_pairedDevices.isNotEmpty()) {
            for (device: BluetoothDevice in m_pairedDevices) {
                list.add(device)
                Log.i("device", "device $device")
                listItems[index++] = device.name
            }
        } else {
            Toast.makeText(this, "no paired bluetooth devices found", Toast.LENGTH_LONG).show()
        }

        val adapter = ArrayAdapter(this, android.R.layout.simple_list_item_1, listItems)
        val myListView = findViewById<ListView>(R.id.bluetooth_list)
        myListView.adapter = adapter
    }


    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        if (requestCode == REQUEST_ENABLE_BLUETOOTH) {
            if(resultCode == RESULT_OK) {
                if(m_bluetoothAdapter!!.isEnabled) {
                    Toast.makeText(this, "Bluetooth Ligado", Toast.LENGTH_SHORT).show()
                } else {
                    Toast.makeText(this, "Bluetooth Desligado", Toast.LENGTH_SHORT).show()
                }
            } else if (resultCode == RESULT_CANCELED) {
                Toast.makeText(this, "Pedido foi Cancelado", Toast.LENGTH_SHORT).show()
            }
        }
    }

    companion object {
        /**
         * The fragment argument representing the section number for this
         * fragment.
         */
        val EXTRA_ADRESS: String = "Device_adress"
        private const val ARG_SECTION_NUMBER = "section_number"
    }
}