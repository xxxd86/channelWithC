package com.example.channelwithc

import android.os.Build
import android.util.Log
import androidx.annotation.RequiresApi
import com.example.channelwithc.JNIUtils.A
import java.util.Date
import java.util.Objects
import kotlin.jvm.internal.Reflection

class JUtils {
    /**
     * 获得source root
     */
    private fun GET_SOURCE_ROOT(root:Any): String {
        return root.javaClass.name.replace(Regex("[.]")){
            when(it.value) {
                "." -> "/"
                else -> it.value
            }
        }

    }
    /**
     * 有参获取class,
     */
    private fun object_Loader_Class(root:Any): Class<*> {
        val clazz2: Class<*> = root.javaClass
        return clazz2;
    }
    /**
     * 有参获取class method,
     */
    private fun object_Loader_Class_method(root:Any,methodName:String){
        val class_temp = object_Loader_Class(root)
        val newInstance: Any = class_temp.newInstance()
        val start = class_temp.getMethod(methodName);
        start.invoke(newInstance);
    }
    /**
     * root ClassLoader获取class
     */
    private fun root_Loader_Class(root:String): Class<*>? {
        val classLoader: ClassLoader = javaClass.classLoader as ClassLoader
        val aClass3 = classLoader.loadClass(root)
        return aClass3;
    }
    /**
     *  root ClassLoader 获取class method,
     */
    private fun root_Loader_Class_method(root:String,methodName:String){
        val class_temp = root_Loader_Class(root)
        val newInstance: Any? = class_temp?.newInstance()
        val start = class_temp?.getMethod(methodName);
        if (start != null) {
            start.invoke(newInstance)
        };
    }

    /**
     * 实例Loader
     */
    @RequiresApi(Build.VERSION_CODES.S)
    private fun jni_start() {
        val A = A();
        //获得无参构造函数,通过有参
        object_Loader_Class_method(A,"start")
        //classLoader获得有参
       root_Loader_Class_method(GET_SOURCE_ROOT(A),"start")
    }
}