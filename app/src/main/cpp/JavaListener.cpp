//
// Created by liuqikang on 2018/6/20.
//

#include "JavaListener.h"
#include "AndroidLog.h"

JavaListener::JavaListener(JavaVM *vm, JNIEnv *env, jobject obj) {
    jvm = vm;
    jenv = env;
    jobj = obj;
    // 获取类对象
    jclass clz = env->GetObjectClass(obj);
    if(!clz)
    {
        return;
    }
    // 获取函数
    jmethod = env->GetMethodID(clz, "OnError", "(ILjava/lang/String;)V");

    if (!jmethod)
    {
        LOGD("GetMethodID failed");
    }
    LOGD("GetMethodID success");

}

JavaListener::~JavaListener() {

}

void JavaListener::onError(int threadType, int code, const char *msg) {
    LOGD("JavaListener OnError in threadtype = %d", threadType);

    if (threadType == 0)
    {
        JNIEnv*env;
        jvm->AttachCurrentThread(&env, 0);  // 获取子线程的ENV
        // 注意下面的操作要使用上面获取的线程env
        jstring jmsg = env->NewStringUTF(msg);
        env->CallVoidMethod(jobj,jmethod, code, jmsg); // 调用java方法传参
        env->DeleteLocalRef(jmsg);//析构字符串

        jvm->DetachCurrentThread();

    }
    else if (threadType == 1)
    {
        jstring jmsg = jenv->NewStringUTF(msg);
        jenv->CallVoidMethod(jobj,jmethod, code, jmsg); // 调用java方法传参
        jenv->DeleteLocalRef(jmsg);//析构字符串
    }
    LOGD("JavaListener OnError out");

}
