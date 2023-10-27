#include <jni.h>
#include <string>


extern "C" {

#include "public/interface.h"

unsigned char *jstringToUnsignedChar(JNIEnv *env, jstring jstr) {
    char *rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("utf-8");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0) {
        rtn = (char *) malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return reinterpret_cast<unsigned char *>(rtn);
}
jstring unsignedChar2Jstring( JNIEnv* env, unsigned char* pat )
{
    unsigned char *newresult = pat;
    //定义java String类 clsstring
    jclass clsstring = env->FindClass("java/lang/String");
    //获取String(byte[],String)的构造器,用于将本地byte[]数组转换为一个新String
    jmethodID mid = env->GetMethodID(clsstring , "<init>" , "([BLjava/lang/String;)V");
    // 设置String, 保存语言类型,用于byte数组转换至String时的参数
    jstring encoding = env->NewStringUTF("utf-8");
    //建立byte数组
    jbyteArray bytes = env->NewByteArray(strlen((char*)newresult));
    //将char* 转换为byte数组
    env->SetByteArrayRegion(bytes, 0, strlen((char*)newresult), (jbyte*) newresult);
    //将byte数组转换为java String,并输出
    return (jstring) env->NewObject(clsstring, mid, bytes, encoding);
}

JNIEXPORT jstring JNICALL
Java_com_esinhai_collectiondevice_DeviceCommunicationJNI_InterfaceJsonMagLoading(JNIEnv *env, jclass param,jstring path, jint count, jint baud) {
    LOGE("InterfaceJsonMagLoading count==  %d",count);
    unsigned char *buf_1 = jstringToUnsignedChar(env, path);
    unsigned char *des = InterfaceJsonMagLoading(buf_1, count, baud);
    if (des == NULL) {
        return unsignedChar2Jstring(env,(unsigned char *)"fail");
    }
    return unsignedChar2Jstring(env,des);
}

JNIEXPORT jstring JNICALL
Java_com_esinhai_collectiondevice_DeviceCommunicationJNI_InterfaceDeviceDataAnalysis(JNIEnv *env, jclass thizm,jstring path, jint size) {
    unsigned char *buf_2 = jstringToUnsignedChar(env, path);
    unsigned char *desBuf = InterfaceDeviceDataAnalysis(buf_2, size);
    LOGE("SoDealResult==%s",desBuf);
    if (desBuf == NULL) {
        return unsignedChar2Jstring(env,(unsigned char *)"fail");
    }
    return unsignedChar2Jstring(env,desBuf);
}

}