package com.text.peng.jnitest;

/**
 * Created by Administrator on 2018/2/23.
 */

public class JniDemo {

    static{
        System.loadLibrary("native-lib");
    }

    public native String addTest(int a,int b);
}
