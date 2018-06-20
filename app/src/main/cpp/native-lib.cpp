#include <jni.h>
#include <string>
#include "pthread.h"
#include "AndroidLog.h"

pthread_t thread;

void* normalThread(void*)
{
    LOGD("create thread from c++");
    pthread_exit(&thread);
}

extern "C"
JNIEXPORT void JNICALL
Java_test_lqk_openssltest_ThreadDemo_normalThread(JNIEnv *env, jobject instance) {

    // TODO
    pthread_create(&thread, 0, normalThread, 0);

}

#include "queue"
#include "unistd.h"// sleep,usleep

std::queue<int> queue;

pthread_t producor;//生产者
pthread_t customer;//消费者

pthread_mutex_t mutex;  // 互斥锁
pthread_cond_t cond;    // 信号

void* productThread(void*)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        queue.push(1);  // 生产产品
        LOGD("生产者生产一个产品 总数 %d", queue.size());
        pthread_cond_signal(&cond);// 发出信号
        pthread_mutex_unlock(&mutex);
        sleep(5);
    }

    pthread_exit(&producor);
}

void* customThread(void*)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);
        if (queue.size() > 0)
        {
            queue.pop();    // 消费产品
            LOGD("消费者消费一个产品");
        } else{
            LOGD("消费者等待中...");
            pthread_cond_wait(&cond, &mutex);// 等待信号，没有信号解锁mutex
        }
        pthread_mutex_unlock(&mutex);
        usleep(1000 * 500);
    }
    pthread_exit(&customer);
}




extern "C"
JNIEXPORT void JNICALL
Java_test_lqk_openssltest_ThreadDemo_matuxThread(JNIEnv *env, jobject instance) {

    for (int i = 0; i < 10; ++i) {
        queue.push(i);
    }


    pthread_mutex_init(&mutex, 0);
    pthread_cond_init(&cond, 0);

    pthread_create(&producor, 0, productThread, NULL);
    pthread_create(&customer, 0, customThread, NULL);



}

#include "JavaListener.h"
JavaVM*jvm;
JavaListener* javaListener;

pthread_t childthread;

void* childCallback(void*data)
{
    LOGD("childCallback in");

    JavaListener*listener = (JavaListener *) (data);
    listener->onError(0, 101, "native call java method from child thread");

    pthread_exit(&childthread);
    LOGD("childCallback in");

}

extern "C"
JNIEXPORT void JNICALL
Java_test_lqk_openssltest_ThreadDemo_callbackFromC(JNIEnv *env, jobject instance)
{
    LOGD("callbackFromC in");
    env->GetJavaVM(&jvm);

    if (!jvm)
    {
        LOGD("callbackFromC jvm NULL");

        return;
    }
    javaListener = new JavaListener(jvm, env, env->NewGlobalRef(instance));

    // 主线程调用
    //javaListener->onError(1, 100, "native call java method from main thread");

    // 子线程调用
    pthread_create(&childthread, 0, childCallback, javaListener);
}

