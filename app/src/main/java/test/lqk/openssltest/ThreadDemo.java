package test.lqk.openssltest;

import android.util.Log;

/**
 * Created by liuqikang on 2018/6/20.
 */

public class ThreadDemo {
    static {
        System.loadLibrary("native-lib");
    }

    public void setOnErrorListener(ThreadDemo.onErrorListener onErrorListener) {
        this.onErrorListener = onErrorListener;
    }

    public onErrorListener onErrorListener;


    public native void normalThread();  // 线程测试

    public native void matuxThread();   // 生产者消费者模型

    // 用来给native层回调
    public void OnError(int codec, String msg){
        Log.d("lqkssltest", "OnError call success");

        if (onErrorListener != null){
            onErrorListener.OnError(codec, msg);
        }else {
            Log.d("lqkssltest", "onErrorListener is NULL");

        }
    }

    // 创建一个回调接口
    public interface onErrorListener{
        public void OnError(int codec, String msg);
    }

    public native void callbackFromC();// 从native层回调JAVA方法
}
