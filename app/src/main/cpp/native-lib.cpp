#include <jni.h>
#include <string>

static const char *const CLASSNAME = "com/text/peng/jnitest/MainActivity";

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_text_peng_jnitest_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++王立鹏";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_text_peng_jnitest_MainActivity_addTest(JNIEnv *env, jclass type, jint a, jint b) {

    // TODO
    return  a + b;
}

jobject getApplicationObject(JNIEnv *env, jobject thiz){
    jobject mApplicationObj = NULL;
    //找到ActivityThread类
    jclass jclass1 = env -> FindClass("android/app/ActivityThread");
    //找到currentActivityThread方法
    jmethodID jmethodID1 = env -> GetStaticMethodID(jclass1,"currentActivityThread","()Landroid/app/ActivityThread;");

    jobject mCurrentActivity = env -> CallStaticObjectMethod(jclass1,jmethodID1);
    //找到currentApplication方法
    jmethodID jmethodID2 = env->GetMethodID(jclass1, "getApplication",
                                            "()Landroid/app/Application;");

    mApplicationObj = env->CallObjectMethod(mCurrentActivity,jmethodID2);

    if(mApplicationObj == NULL){
        return NULL;
    }
    return mApplicationObj;
}

//TODO 动态注册的方法集合
static JNINativeMethod gMethods[] = {
        {"getApplicationObject", "()Landroid/app/Application;", (void *) getApplicationObject}
};

/*
* System.loadLibrary("lib")时调用
* 如果成功返回JNI版本, 失败返回-1
* 这个方法一般都是固定的
*/
extern "C"
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        return -1;
    }
    if (env == NULL) {
        return -1;
    }
    // 需要注册的类
    jclass clazz = env->FindClass(CLASSNAME);
    if (clazz == NULL) {
        return -1;
    }
    //TODO 这里是重点，动态注册方法
    if (env->RegisterNatives(clazz, gMethods, sizeof(gMethods) / sizeof(gMethods[0])) < 0) {
        return -1;
    }
//    LOGD("dynamic success is %d", JNI_VERSION_1_4);
    return JNI_VERSION_1_4;
}

//日志文件代码如下:
//#ifndef FINENGINE_LOG_H
//#define FINENGINE_LOG_H
//#include <android/log.h>
//static const char* kTAG = "JNIDEMO";
//#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
//#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
//#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,kTAG,__VA_ARGS__)
//#endif