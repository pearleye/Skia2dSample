package com.example.skia2dsample;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Bitmap;
import android.os.Bundle;

import com.codemonkeylabs.fpslibrary.TinyDancer;

import java.util.Timer;
import java.util.TimerTask;

public class MainActivity extends AppCompatActivity {
    private SkiaContentView skiaContentView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        skiaContentView = new SkiaContentView(this);
        setContentView(skiaContentView);

        TinyDancer.create()
                .show(this);
        Timer skiaAnimateTimer = new Timer();
        skiaAnimateTimer.schedule(new TimerTask() {
            @Override
            public void run() {
                skiaContentView.postInvalidate();
            }
        }, 0, 5);
    }

    private native void drawIntoBitmap(Bitmap image, long elapsedTime);
}