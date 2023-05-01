package com.example.skia2dsample;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Picture;
import android.os.SystemClock;
import android.util.Log;
import android.view.View;

public class SkiaContentView extends View {
    private static final String TAG = "SkiaContentView";
    private Bitmap bitmap;
    private SkiaNative skiaNative;
    private static double frameCounter;

    public SkiaContentView(Context context) {
        super(context);
        skiaNative = new SkiaNative();
    }

    @Override
    protected void onDraw(Canvas canvas) {
        if (++frameCounter > 240) {
            frameCounter = 1;
        }
        skiaNative.drawView(bitmap, SystemClock.elapsedRealtime(), frameCounter / 240);
        canvas.drawBitmap(bitmap, 0, 0, null);
        Log.i(TAG, "isHardwareAccelerated --> " + canvas.isHardwareAccelerated() + "frame --> " + Double.toString(frameCounter / 240));
    }

    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh) {
        bitmap = Bitmap.createBitmap(w, h, Bitmap.Config.ARGB_8888);
    }
}
