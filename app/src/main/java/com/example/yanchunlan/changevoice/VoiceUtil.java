package com.example.yanchunlan.changevoice;

/**
 * Created by yanchunlan on 2017/7/2.
 */

public class VoiceUtil {

    public static final int TYPE_NORMAL = 0;    // 普通
    public static final int TYPE_LOLITA=1;      // 萝莉
    public static final int TYPE_UNCLE=2;       // 大叔
    public static final int TYPE_THRILLER=3;    // 惊悚
    public static final int TYPE_FUNNY=4;       // 搞怪
    public static final int TYPE_ETHEREAL=5;    // 空灵

    public static native void fix(String path, int type);

    static {
        System.loadLibrary("fmod");
        System.loadLibrary("fmodL");
        System.loadLibrary("changevoice");
    }

}
