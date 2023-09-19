package com.example.channelwithc

import android.annotation.SuppressLint
import android.content.Context
import android.content.res.AssetManager
import android.os.Bundle
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import com.example.channelwithc.databinding.ActivityMainBinding


class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding
     lateinit var Mcontext: Context
    /**
     * 需要进行使用的class
     */
    var JUtils = JUtils();
    var text = "non";
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
        Mcontext = applicationContext
        // Example of a call to a native method
        binding.sampleText.text = text
        binding.hello.setOnClickListener {
//            HELLO()
//
//            text = GETJSON()
//            binding.sampleText.text = text//读取JSON文件
            /**
             * kotlin处理方式
             * */
//            var input = resources.assets.open("text.json");
//            JUtils.stringFromJNI();
            val it = TestLayer()
//mContext为当前项目上下文
//mContext为当前项目上下文
            val result = it.setAssetManager(Mcontext.assets)
            Log.v("HEXXXXXXXXXXX",result)
//            readFromAssets(Mcontext.assets,"text.json");

//            input.use {
//                val reader = BufferedReader(InputStreamReader(it))
//                try {
//                    val results = StringBuilder()
//                    while (true) {
//                        val line = reader.readLine()
//                        if (line == null) break
//                        results.append(line)
//                    }
//                    val inputAsString = results.toString()
//                    Log.v("xsax", inputAsString)
//                } finally {
//                    reader.close()
//                }
//
//
//            }

        }

    }

    /**
     * A native method that is implemented by the 'channelwithc' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String
    private external fun HELLO()
    external fun readFromAssets(ass: AssetManager?, filename: String?)
    private external fun GETJSON():String



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