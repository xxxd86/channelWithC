#include <jni.h>
#include <string>
#include "core/buid.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_channelwithc_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    return env->NewStringUTF(hello.c_str());

}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_channelwithc_MainActivity_HELLO(JNIEnv *env, jobject thiz) {
    jclass clazz = env -> FindClass("com/example/channelwithc/JUtils");
    jmethodID methodId = env->GetMethodID(clazz, "start", "()V");
    jmethodID method_construct = env->GetMethodID(clazz,"<init>","()V");
    jobject jnutils = env->NewObject(clazz,method_construct);
    if (methodId == nullptr) {
        return;
    }
    env->CallVoidMethod(jnutils, methodId);
}