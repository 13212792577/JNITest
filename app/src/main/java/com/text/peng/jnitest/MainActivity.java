package com.text.peng.jnitest;

import android.app.Application;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

//    public static native Object getPackage();
    //静态注册的方法  Alt+Enter就可以注册
    public static native int addTest(int a,int b);
    //动态注册的方法
    public static native Application getApplicationObject();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        StringBuilder sb = new StringBuilder(stringFromJNI());
        sb.append(addTest(150,300)).append(getApplicationObject());
        tv.setText(sb.toString());
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}
