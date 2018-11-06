//
// Created by Administrator on 2018-11-06.
//

#include <jni.h>
#include <string>
#include <android/log.h>
#include "ydotLib.h"

#ifdef __cplusplus
extern "C" {
#endif

#define   LOG_TAG    "LibYdot"
#define   LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define   LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
//------------------------------------------------
static JNIEnv *g_env=NULL;
static jobject g_obj=NULL;
#define SetEnv() {g_env=env;g_obj=obj;}

//When the pen point close to the coded paper. Not necessarily successful decoding.
void cbTouch(In BoolX bTouch)
{
    LOGI("cpp: cbTouch:%d",bTouch);
    jclass LibYdotJni = g_env->GetObjectClass(g_obj);
    jmethodID mTouch = g_env->GetMethodID(LibYdotJni, "cbTouch", "(Z)V");

    LOGI("cpp: cbTouch:%d ->  mTouch=%p",bTouch,(void *)mTouch);
    g_env->CallVoidMethod(g_obj,mTouch,(jboolean)bTouch);
}

//When decoding success, the same continuous id will only be invoked once.
void cbRecognized(In U32 id)
{
    LOGI("cpp: cbRecognized:%ld",id);
    jclass LibYdotJni = g_env->GetObjectClass(g_obj);
    jmethodID mRecognized = g_env->GetMethodID(LibYdotJni, "cbRecognized", "(J)V");

    LOGI("cpp: cbRecognized:%ld -> mRecognized=%p",id,(void *)mRecognized);
    g_env->CallVoidMethod(g_obj,mRecognized,(jlong)id);

    //g_env->GetByteArrayRegion();
    //env->SetByteArrayRegion(newByteArray, 0, 5, buffer);
}

void Oid_InitYDotDriver(void)
{
    IniData iniData;

    //step 1: Allocates a block of memory to decode Library
    U32 memSize=yGetFixedMemSize();		//Ask how much memory need.
    iniData.pFixedMem=malloc(memSize);//memory allocate

    LOGI("memSize:%ld",memSize);
    LOGI("pFixedMem:%p",iniData.pFixedMem);

    //step 2: Set decode result processing function. When the "Event" occur will triger the callback.
    iniData.fTouch=cbTouch; 			//Event: When the pen point close to the coded paper. Not necessarily successful decoding.
    iniData.fRecognized=cbRecognized;	//Event: When decoding success, the same continuous id will only be invoked once.

    //step 3: Assign to YdOT driver.
    yInitYdot(&iniData);
}

//Android系统加载JNI Lib后第一调用 JNI_OnLoad()
JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    Oid_InitYDotDriver();
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNI_OnUnload(JavaVM* vm, void* reserved)
{

}

void Oid_Decode(U8 *pDataIn,long lenData)
{
    BoolX b=yResetBuf();//Before calling "yDecodeImage()" must call "yResetBuf()" first.
    LOGI("b:%d",b);

    U8 *pImg=yGetImageBuf();//Should put camera image into this buffer.
    LOGI("pImg:%p",pImg);

    memcpy(pImg,pDataIn,lenData);

    yDecodeImage();//Result -> see callback function "cbTouch" & "cbRecognized"
}


//*********************************************************************
JNIEXPORT jstring JNICALL Java_com_cdgo_libydot_PenJni_getVersion(JNIEnv *env, jobject obj)
{
    std::string version = "1.0.0";
    return env->NewStringUTF(version.c_str());
}

JNIEXPORT void JNICALL Java_com_cdgo_libydot_PenJni_decodeBuf(JNIEnv *env, jobject obj, jbyteArray dataIn)
{
    SetEnv();

    jbyte   *pDataIn = env->GetByteArrayElements(dataIn, 0);
    jsize   lenData = env->GetArrayLength(dataIn);
    LOGI("pDataIn:%d",*pDataIn);
    LOGI("lenData:%d",lenData);

    Oid_Decode((U8 *)pDataIn,lenData);
}


#ifdef __cplusplus
}
#endif