package com.example.skia2dsample;

import android.graphics.Bitmap;
import android.util.Log;

public class SkiaNative {
    public static final String TAG = "SkiaNative";

    static {
        try {
            System.loadLibrary("2dSample");
        } catch (UnsatisfiedLinkError e) {
            Log.e(TAG, e.toString());
        }

    }

    public void drawView(Bitmap bitmap, long elapsedTime, double frame) {
        drawQuad(bitmap, elapsedTime, frame);
    }

    private native void drawQuad(Bitmap image, long elapsedTime, double frame);
}
