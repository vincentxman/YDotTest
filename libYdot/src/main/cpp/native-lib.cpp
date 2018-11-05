#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_cdgo_libydot_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++, Vincent";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_cdgo_libydot_LibX_stringFromJNI(
        JNIEnv *env,
jobject /* this */) {
std::string hello = "Hello from C++, Vincent";
return env->NewStringUTF(hello.c_str());
}
