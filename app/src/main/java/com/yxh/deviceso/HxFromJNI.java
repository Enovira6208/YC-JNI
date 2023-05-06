package com.yxh.deviceso;


/**
 * @Description  {具体做什么}
 * @Author wushan
 * @Date 2021/12/2 11:18
 */

public class HxFromJNI {

    static {
        System.loadLibrary("hx");
    }

    public static native String stringFromJNI();
    public static native String analysisDataUHF(String name);
    public static native String analysisDataAE(String name);
    public static native String analysisDataTEV(String name);

}
