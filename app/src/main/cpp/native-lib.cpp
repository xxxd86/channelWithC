#include <jni.h>
#include <string>
#include <sys/stat.h>
#include "core/buid.h"
#include "android/log.h"
#include "cJSON.h"
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#define FILE_NAME "text.json"
#define LOG_TAG "System.out"
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <iostream>
#include <string>
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
jstring convertToJString(JNIEnv* env, const std::string& str) {
    return env->NewStringUTF(str.c_str());
}
AAssetManager* mgr = NULL;

//获取setAAssetManager


//读取assets文件
char* readFileFromAssets(const std::string& path)
{
    AAsset* asset = AAssetManager_open(mgr, path.c_str(), AASSET_MODE_BUFFER);
    if(asset)
    {
        size_t dataFileSize = AAsset_getLength(asset);
        char *buffer = (char *)malloc(dataFileSize);
        memset(buffer, 0x00, dataFileSize);
        int numBytesRead = AAsset_read(asset, buffer, dataFileSize);
        buffer[dataFileSize]=0;
        AAsset_close(asset);
//        __android_log_print(ANDROID_LOG_INFO, "axxxxzzzzzzxx", ": %s\\n", buffer);
        return buffer;
    }
}
jstring  nativeSetAAssetManager(JNIEnv* env, jclass obj,jobject assetManager)
{

    mgr = AAssetManager_fromJava(env, assetManager);
    std::string path = "text.json";
    char * pData = readFileFromAssets(path);
    __android_log_print(ANDROID_LOG_INFO, "axxxxzzzzzzxx", ": %s\\n", pData);

////do something
//    std::cin.getline(pData, 256); // 从标准输入读取一行数据到缓冲区
//
//    std::string str(pData);
////释放内存
//    if(pData != nullptr)
//    {
//        free(pData);
//        pData = nullptr;
//    }
    return convertToJString(env,pData);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_channelwithc_MainActivity_readFromAssets(JNIEnv *env, jobject thiz, jobject assetManager,
                                                          jstring filename)
{
    AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
    if(mgr==NULL)
    {
        __android_log_print(ANDROID_LOG_INFO, "zj", ":%s", "AAssetManager==NULL");
        //LOGI(" %s","AAssetManager==NULL");
        return ;
    }
    /*获取文件名并打开*/
    jboolean iscopy;
    const char *mfile = env->GetStringUTFChars(filename, &iscopy);
    AAsset* asset = AAssetManager_open(mgr, mfile,AASSET_MODE_UNKNOWN);
    env->ReleaseStringUTFChars(filename, mfile);
    if(asset==NULL)
    {
        // LOGI(" %s","asset==NULL");
        __android_log_print(ANDROID_LOG_INFO, "zj", ":%s", "asset==NULL");
        return ;
    }
    /*获取文件大小*/
    off_t bufferSize = AAsset_getLength(asset);
    //LOGI("file size         : %d\n",bufferSize);
    __android_log_print(ANDROID_LOG_INFO, "zj", "file size  : %d\\n", bufferSize);
    char *buffer=(char *)malloc(bufferSize+1);
    buffer[bufferSize]=0;
    int numBytesRead = AAsset_read(asset, buffer, bufferSize);
    //  LOGI(": %s",buffer);
    __android_log_print(ANDROID_LOG_INFO, "zj", ": %s\\n", buffer);
    free(buffer);
    /*关闭文件*/
    AAsset_close(asset);
}

/**
 * native注册接口,动态注册
 */
//static int registerNativeMethods(JNIEnv* env, const char* className,JNINativeMethod* getMethods,int methodsNum){
//    jclass clazz;
//    //找到声明native方法的类
//    clazz = env->FindClass(className);
//    if(clazz == NULL){
//        return JNI_FALSE;
//    }
//    //注册函数 参数：java类 所要注册的函数数组 注册函数的个数
//    if(env->RegisterNatives(clazz,getMethods,methodsNum) < 0){
//        return JNI_FALSE;
//    }
//    return JNI_TRUE;
//}
//
//static int registerNatives(JNIEnv* env){
//    //指定类的路径，通过FindClass 方法来找到对应的类
//    const char* className  = "com/example/channelwithc/TestLayer";
//    return registerNativeMethods(env,className,getMethods, sizeof(getMethods)/ sizeof(getMethods[0]));
//}
void  registerNative(JavaVM *vm) {

    JNIEnv* env = nullptr;
    vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6);

    jclass customLayerClass = env->FindClass("com/example/channelwithc/TestLayer");

    JNINativeMethod methods[] = {
            {"SetAssetManager", "(Landroid/content/res/AssetManager;)Ljava/lang/String;", reinterpret_cast<void *>(&nativeSetAAssetManager)},
    };

    if (env->RegisterNatives(customLayerClass, methods, sizeof(methods) / sizeof(JNINativeMethod)) < 0) {
        env->ExceptionDescribe();
    }
    LOGI("READYSX");
}
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_channelwithc_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    return env->NewStringUTF(hello.c_str());

}
/**
 * 使用classLoader与JNI框架进行联合
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_example_channelwithc_MainActivity_HELLO(JNIEnv *env, jobject thiz) {
    jclass clazz = env -> FindClass("com/example/channelwithc/JUtils");
    jmethodID methodId = env->GetMethodID(clazz, "jni_start", "()V");
    jmethodID method_construct = env->GetMethodID(clazz,"<init>","()V");
    jobject jnutils = env->NewObject(clazz,method_construct);
    if (methodId == nullptr) {
        return;
    }
    env->CallVoidMethod(jnutils, methodId);
}
/**
 * 获取json文件信息
 * */
extern "C"
JNIEXPORT jstring  JNICALL
Java_com_example_channelwithc_MainActivity_GETJSON(JNIEnv *env, jobject thiz) {
    // TODO: implement GETJSON()
    /**
     * 解析文件
     * */
    FILE *file = NULL;
    file = fopen("/text.json", "r");
    if (file == NULL) {
        printf("Open file fail！\n");
        LOGI("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
        return convertToJString(env,"noone");
    }


// 获得文件大小
    struct stat statbuf;
    stat(FILE_NAME, &statbuf);
    int fileSize = statbuf.st_size;
    printf("文件大小：%d\n", fileSize);
    LOGI("文件大小：%d\n", fileSize);

// 分配符合文件大小的内存
    char *jsonStr = (char *)malloc(sizeof(char) * fileSize + 1);
    memset(jsonStr, 0, fileSize + 1);


// 读取文件中的json字符串
    int size = fread(jsonStr, sizeof(char), fileSize, file);
    if (size == 0) {
        LOGI("读取文件失败！\n");
        fclose(file);
        return convertToJString(env,"noone");
    }
    printf("%s\n", jsonStr);
    LOGI("hLLLO:%s\n", jsonStr);
    LOGI("pass");
    fclose(file);
// 将读取到的json字符串转换成json变量指针
    cJSON *root = cJSON_Parse(jsonStr);
    if (!root) {
        printf("Error before: [%s]\n", cJSON_GetErrorPtr());
        free(jsonStr);
        return convertToJString(env,"noone");
    }
    free(jsonStr);
    cJSON *item = NULL;
    char *v_str = NULL;
    double v_double = 0.0;
    int v_int = 0;
    bool v_bool = false;
// 解析："name":	"小明",
    item = cJSON_GetObjectItem(root, "name");
    if (item != NULL) {
        /* 写法一：*/
        // 判断是不是字符串类型
        //if (item->type == cJSON_String) {
        //	v_str = cJSON_Print(item);		// 通过函数获取值
        //	printf("name = %s\n", v_str);
        //	free(v_str);					// 通过函数返回的指针需要自行free，否则会导致内存泄漏
        //	v_str = NULL;
        //}


        /* 写法二： */
        // 判断是不是字符串类型
        if (item->type == cJSON_String) {
            v_str = item->valuestring;		// 此赋值是浅拷贝，不需要现在释放内存
            printf("name = %s\n", v_str);
            return convertToJString(env,v_str);
        }

    }

//
//
//// 解析："age":	"23",
//    item = cJSON_GetObjectItem(root, "age");
//    if (item != NULL) {	// 合法性检查
//        if (item->type == cJSON_Number) {		// 判断是不是数字
//            v_int = item->valueint;			// 获取值
//            printf("age = %d\n", v_int);
//        }
//    }
//
//
//
//// 解析："vip":	true,
//    item = cJSON_GetObjectItem(root, "vip");
//    if (item != NULL) {
//        if (item->type == cJSON_True || item->type == cJSON_False) {
//            v_str = cJSON_Print(item);		// 由于bool类型结构体中没有给出，所以使用字符串代替
//            printf("vip = %s\n", v_str);
//            free(v_str);
//            v_str = NULL;
//        }
//    }
//
//
//
//// 解析："address":	null
//    item = cJSON_GetObjectItem(root, "address");
//    if (item != NULL && item->type == cJSON_NULL) {
//        v_str = cJSON_Print(item);		// 由于NULL类型结构体中没有给出，所以使用字符串代替
//        printf("address = %s\n", v_str);
//        free(v_str);
//        v_str = NULL;
//    }

}
//extern "C"
//JNIEXPORT jstring JNICALL
//Java_com_example_channelwithc_MainActivity_nativeReadFromAssets(JNIEnv* env, jobject tis,jobject assetManager,jstring filename) {
//
//
//}
JNIEXPORT jstring JNICALL  stringFromJNI(JNIEnv *env, jobject thiz) {//冗长方法直接删短
    return nullptr;
}
static const JNINativeMethod jniNativeMethod[] = {
        {"stringFromJNI", "()Ljava/lang/String;", (void *) (stringFromJNI)},
};
/**
 * 1.设置jvm全局变量，多线程需要用到
 * 2.nullptr: C++11后，要取代NULL，作用是可以给初始化的指针赋值
 */
JavaVM *jvm = nullptr;
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *javaVm, void *pVoid) {
    registerNative(javaVm);
    jvm = javaVm;
    // 1.通过JavaVM 创建全新的JNIEnv
    JNIEnv *jniEnv = nullptr;
    // 2.判断创建是否成功
    jint result = javaVm->GetEnv(reinterpret_cast<void **>(&jniEnv),JNI_VERSION_1_6); // 参数2：是JNI的版本 NDK 1.6   JavaJni 1.8
    if (result != JNI_OK) {
        return -1; // 主动报错
    }
    // 3.找到需要动态动态注册的Jni类
    jclass jniClass = jniEnv->FindClass("com/example/channelwithc/JUtils");

    //动态注册（这里就需要用到签名后的方法了）   待注册class 方法集合 方法数量
    jniEnv->RegisterNatives(jniClass, jniNativeMethod,sizeof(jniNativeMethod) / sizeof(JNINativeMethod));
    return JNI_VERSION_1_6;
}
