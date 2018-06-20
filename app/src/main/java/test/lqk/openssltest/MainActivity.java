package test.lqk.openssltest;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    ThreadDemo threadDemo;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        threadDemo = new ThreadDemo();
//        threadDemo.normalThread();
//        threadDemo.matuxThread();

        threadDemo.setOnErrorListener(new ThreadDemo.onErrorListener() {
            @Override
            public void OnError(int codec, String msg) {
                Log.d("lqkssltest", "code is " + codec + "msg is " + msg);
            }
        });

        threadDemo.callbackFromC();


    }

}
