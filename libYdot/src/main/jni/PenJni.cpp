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
#define   LOGI(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define   LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
//------------------------------------------------
static JNIEnv *g_env=NULL;
static jobject g_obj=NULL;
#define SetEnv() {g_env=env;g_obj=obj;}

//When the pen point close to the coded paper. Not necessarily successful decoding.
void cbTouch(In BoolX bTouch)
{
    jclass LibYdotJni = g_env->GetObjectClass(g_obj);
    jmethodID mTouch = g_env->GetMethodID(LibYdotJni, "cbTouch", "(Z)V");

    LOGI("cpp: cbTouch(%d) ->  java: cbTouch=%p",bTouch,(void *)mTouch);
    g_env->CallVoidMethod(g_obj,mTouch,(jboolean)bTouch);
}

//When decoding success, the same continuous id will only be invoked once.
void cbRecognized(In U32 id)
{
    jclass LibYdotJni = g_env->GetObjectClass(g_obj);
    jmethodID mRecognized = g_env->GetMethodID(LibYdotJni, "cbRecognized", "(J)V");

    LOGI("cpp: cbRecognized(%ld) -> java: cbRecognized=%p",id,(void *)mRecognized);
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

    LOGI("cpp: Oid_InitYDotDriver() {memSize:%ld, pFixedMem:%p}",memSize,iniData.pFixedMem);

    //step 2: Set decode result processing function. When the "Event" occur will triger the callback.
    iniData.fTouch=cbTouch; 			//Event: When the pen point close to the coded paper. Not necessarily successful decoding.
    iniData.fRecognized=cbRecognized;	//Event: When decoding success, the same continuous id will only be invoked once.

    //step 3: Assign to YdOT driver.
    yInitYdot(&iniData);
}

//Android系统加载JNI Lib后第一调用 JNI_OnLoad()
JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    LOGI("JNI_OnLoad()");
    try {
        Oid_InitYDotDriver();
    }catch (...){
        LOGE("cpp: Error when run Oid_InitYDotDriver()");
    }
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNI_OnUnload(JavaVM* vm, void* reserved)
{
    LOGI("JNI_OnUnload()");
    yFreeYdot();
}

void Oid_Decode(U8 *pDataIn,long lenData,BoolX bLoop)
{
    BoolX b=yResetBuf();//Before calling "yDecodeImage()" must call "yResetBuf()" first.
    //LOGI("cpp: yResetBuf(): %d",b);

    U8 *pImg=yGetImageBuf();//Should put camera image into this buffer.
    if(pImg==NULL)
    {
        LOGE("cpp: Error when run yGetImageBuf()");
        return ;
    }

    memcpy(pImg,pDataIn,lenData);

    yDecodeImage(bLoop);//Result -> see callback function "cbTouch" & "cbRecognized"
}


//*********************************************************************
JNIEXPORT jstring JNICALL Java_com_cdgo_libydot_PenJni_getVersion(JNIEnv *env, jobject obj)
{
    SetEnv();

    std::string version = "1.0.0";
    return env->NewStringUTF(version.c_str());
}

JNIEXPORT void JNICALL Java_com_cdgo_libydot_PenJni_decodeBuf(JNIEnv *env, jobject obj, jbyteArray dataIn, jboolean bLoop)
{
    try{
        SetEnv();

        jbyte   *pDataIn = env->GetByteArrayElements(dataIn, 0);
        jsize   lenData = env->GetArrayLength(dataIn);
        LOGI("cpp: Java_com_cdgo_libydot_PenJni_decodeBuf() {image pDataIn:%d, lenData:%d}",*pDataIn,lenData);

        Oid_Decode((U8 *)pDataIn,lenData,bLoop);
    }catch (...){
        LOGE("cpp: Error when run Oid_Decode()");
    }


}


#ifdef __cplusplus
}
#endif