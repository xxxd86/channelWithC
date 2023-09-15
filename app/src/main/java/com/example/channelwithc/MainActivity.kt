package com.example.channelwithc

import android.annotation.SuppressLint
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.example.channelwithc.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    /**
     * 需要进行使用的class
     */

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = stringFromJNI()
        binding.hello.setOnClickListener {
            HELLO()

        }

    }

    /**
     * A native method that is implemented by the 'channelwithc' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String
    private external fun HELLO()
    companion object {
        // Used to load the 'channelwithc' library on application startup.
        init {
            var ClassList = ArrayList<Any>();
            System.loadLibrary("channelwithc")
        }
    }

    @SuppressLint("SetTextI18n")
    private fun start() {
        binding.sampleText.text = "hello world"
         print("hello world");
    }

}