//
// Created by liuqikang on 2018/6/20.
//

#ifndef OPENSSLTEST_JAVALISTENER_H
#define OPENSSLTEST_JAVALISTENER_H


#include <jni.h>

class JavaListener {
public:
    JavaVM* jvm;    // 虚拟机
    JNIEnv* jenv;   // 环境env
    jobject jobj;  // 对象
    jmethodID jmethod;  // 方法

    JavaListener(JavaVM* vm, JNIEnv*env, jobject obj);
    ~JavaListener();

    /**
     * 主线程与子线程中调用java函数的方法有区别
     * threadType:线程类型 1:mainthread 0:childthread
     */
    void onError(int threadType, int code, const char* msg);
};


#endif //OPENSSLTEST_JAVALISTENER_H
