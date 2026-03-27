// TEST_ID is 249
// Unit tests for SplashBitmapCMYKEncoder::getUndecodedStream()
// File: ./TestProjects/poppler/poppler/Stream.h

#include <gtest/gtest.h>

#include <memory>

#include "Stream.h"
#include "splash/SplashBitmap.h"
#include "splash/SplashTypes.h"

namespace {

std::unique_ptr<SplashBitmap> makeCmykBitmap(int w, int h)
{
    // rowPad: 1 is a safe minimal padding choice for a tiny bitmap.
    // alpha: false (encoder is CMYK-focused).
    return std::make_unique<SplashBitmap>(w, h, /*rowPad=*/1, splashModeCMYK8, /*alphaA=*/false);
}

class SplashBitmapCMYKEncoderTest_249 : public ::testing::Test
{
};

} // namespace

TEST_F(SplashBitmapCMYKEncoderTest_249, GetUndecodedStreamReturnsThis_249)
{
    auto bmp = makeCmykBitmap(1, 1);
    SplashBitmapCMYKEncoder enc(bmp.get());

    Stream *s = enc.getUndecodedStream();

    ASSERT_NE(s, nullptr);
    EXPECT_EQ(s, &enc);
}

TEST_F(SplashBitmapCMYKEncoderTest_249, GetUndecodedStreamViaBasePointerReturnsSameObject_249)
{
    auto bmp = makeCmykBitmap(2, 1);
    SplashBitmapCMYKEncoder enc(bmp.get());

    Stream *base = &enc;
    Stream *u = base->getUndecodedStream();

    ASSERT_NE(u, nullptr);
    EXPECT_EQ(u, base);
    EXPECT_EQ(u, &enc);
}

TEST_F(SplashBitmapCMYKEncoderTest_249, GetUndecodedStreamIsStableAcrossCallsAndIndependentAcrossInstances_249)
{
    auto bmp1 = makeCmykBitmap(1, 2);
    auto bmp2 = makeCmykBitmap(1, 2);

    SplashBitmapCMYKEncoder enc1(bmp1.get());
    SplashBitmapCMYKEncoder enc2(bmp2.get());

    Stream *u1a = enc1.getUndecodedStream();
    Stream *u1b = enc1.getUndecodedStream();
    Stream *u2 = enc2.getUndecodedStream();

    ASSERT_NE(u1a, nullptr);
    ASSERT_NE(u1b, nullptr);
    ASSERT_NE(u2, nullptr);

    EXPECT_EQ(u1a, &enc1);
    EXPECT_EQ(u1b, &enc1);
    EXPECT_EQ(u1a, u1b);

    EXPECT_EQ(u2, &enc2);
    EXPECT_NE(u1a, u2);

    // Optional interaction: rewind should not change what getUndecodedStream() returns.
    (void)enc1.rewind();
    EXPECT_EQ(enc1.getUndecodedStream(), &enc1);
}