#include <jni.h>

#include <math.h>

#include <android/bitmap.h>

#include "SkCanvas.h"
#include "SkGraphics.h"
#include "SkSurface.h"
#include "SkString.h"
#include "SkTime.h"
#include "SkTextBlob.h"
#include "SkFontMgr.h"
#include "SkPath.h"
#include "SkGradientShader.h"

SkPoint cubic(SkPoint p0, SkPoint p1, SkPoint p2, SkPoint p3, float t)
{
    // a simple mathematical definition of cubic curve.
    // There are faster ways to calculate this.
    float s = 1 - t;
    return {(s * s * s * p0.x()) +
                (3 * s * s * t * p1.x()) +
                (3 * s * t * t * p2.x()) +
                (t * t * t * p3.x()),
            (s * s * s * p0.y()) +
                (3 * s * s * t * p1.y()) +
                (3 * s * t * t * p2.y()) +
                (t * t * t * p3.y())};
}

static SkPoint interpolate(SkPoint a, SkPoint b, float t)
{
    return {SkScalarInterp(a.x(), b.x(), t),
            SkScalarInterp(a.y(), b.y(), t)};
}

extern "C" JNIEXPORT void JNICALL Java_com_example_skia2dsample_SkiaNative_drawQuad(JNIEnv *env,
                                                                                    jobject thiz,
                                                                                    jobject dstBitmap,
                                                                                    jlong elapsedTime,
                                                                                    jdouble frame)
{
    AndroidBitmapInfo dstInfo;
    void *dstPixels;
    AndroidBitmap_getInfo(env, dstBitmap, &dstInfo);
    AndroidBitmap_lockPixels(env, dstBitmap, &dstPixels);
    SkImageInfo info = SkImageInfo::MakeN32Premul(dstInfo.width, dstInfo.height);

    SkBitmap skBitmap;
    skBitmap.installPixels(info, dstPixels, dstInfo.stride);
    SkCanvas canvas(skBitmap);

    canvas.clear(SkColorSetARGB(255, 255, 255, 255));

    SkPoint a{136, 64};
    SkPoint b{448, 448};
    SkPoint c{64, 448};
    SkPoint d{376, 64};

    SkPoint ab = interpolate(a, b, frame);
    SkPoint bc = interpolate(b, c, frame);
    SkPoint cd = interpolate(c, d, frame);
    SkPoint abc = interpolate(ab, bc, frame);
    SkPoint bcd = interpolate(bc, cd, frame);

    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setStyle(SkPaint::kStroke_Style);
    paint.setStrokeWidth(1);

    canvas.drawLine(ab, bc, paint);
    canvas.drawLine(bc, cd, paint);
    canvas.drawLine(abc, bcd, paint);

    paint.setStrokeWidth(3);
    canvas.drawLine(a, b, paint);
    canvas.drawLine(b, c, paint);
    canvas.drawLine(c, d, paint);

    paint.setStrokeWidth(5);
    paint.setColor(SkColorSetARGB(255, 0, 0, 255));
    SkPath cubicCurve;
    cubicCurve.moveTo(a);
    cubicCurve.cubicTo(b, c, d);
    canvas.drawPath(cubicCurve, paint);

    SkFont font(nullptr, 32);
    SkPaint textPaint;
    textPaint.setColor(SkColorSetARGB(255, 0, 255, 0));
    textPaint.setAntiAlias(true);
    sk_sp<SkFontMgr> mgr(SkFontMgr::RefDefault());
    sk_sp<SkTypeface> face(mgr->matchFamilyStyle("DejaVu Sans Mono", SkFontStyle()));
    canvas.drawString("a", a.x(), a.y(), font, textPaint);
    canvas.drawString("b", b.x(), b.y(), font, textPaint);
    canvas.drawString("c", c.x() - 20, c.y(), font, textPaint);
    canvas.drawString("d", d.x(), d.y(), font, textPaint);
    SkString msg = SkStringPrintf("%.4f", frame);
    textPaint.setColor(SkColorSetARGB(255, 204, 204, 204));
    canvas.drawString(msg.c_str(), 4, 36, font, textPaint);

    SkPaint pointPaint;
    pointPaint.setAntiAlias(true);
    pointPaint.setStrokeWidth(8);
    pointPaint.setStrokeCap(SkPaint::kRound_Cap);

    pointPaint.setColor(SkColorSetARGB(255, 255, 0, 0));
    canvas.drawPoint(interpolate(abc, bcd, frame), pointPaint);

    pointPaint.setColor(SkColorSetARGB(255, 0, 255, 0));
    pointPaint.setStrokeWidth(7);
    canvas.drawPoint(cubic(a, b, c, d, frame), pointPaint);

    AndroidBitmap_unlockPixels(env, dstBitmap);
}
