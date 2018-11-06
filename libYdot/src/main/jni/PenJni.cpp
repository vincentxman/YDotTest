//
// Created by Administrator on 2018-11-06.
//

#include <jni.h>
#include <string>
#include <android/log.h>

#ifdef __cplusplus
extern "C" {
#endif

#define   LOG_TAG    "LibYdot"
#define   LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define   LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
//------------------------------------------------
static JNIEnv *g_env=NULL;
static jobject g_obj=NULL;
#define SetEnv() {g_env=env;g_obj=obj;}


JNIEXPORT jstring JNICALL Java_com_cdgo_libydot_PenJni_stringFromJNI(JNIEnv *env, jobject obj)
{
    std::string hello = "Hello from C++, Vincent is vector";
    return env->NewStringUTF(hello.c_str());
}

JNIEXPORT void JNICALL Java_com_cdgo_libydot_PenJni_decodeBuf(JNIEnv *env, jobject obj, jbyteArray dataIn)
{
    SetEnv();

    jbyte   *pDataIn = env->GetByteArrayElements(dataIn, 0);
    jsize   lenData = env->GetArrayLength(dataIn);
    LOGD("pDataIn:%d",*pDataIn);
    LOGD("lenData:%d",lenData);

    //Oid_Decode((U8 *)pDataIn,lenData);
}


#ifdef __cplusplus
}
#endif