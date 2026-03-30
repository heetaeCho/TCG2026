// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for SplashBitmapCMYKEncoder::getUnfilteredChar()
// TEST_ID: 246
//
// File under test: ./TestProjects/poppler/poppler/Stream.h

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "poppler/Stream.h"

// These headers are typically available in Poppler builds.
// They provide SplashBitmap and SplashColorMode needed to construct a bitmap.
#include "splash/SplashBitmap.h"
#include "splash/SplashTypes.h"

using ::testing::Return;
using ::testing::Sequence;

namespace {

class SplashBitmapCMYKEncoderMockGetChar : public SplashBitmapCMYKEncoder {
public:
  explicit SplashBitmapCMYKEncoderMockGetChar(SplashBitmap *bitmap) : SplashBitmapCMYKEncoder(bitmap) {}
  ~SplashBitmapCMYKEncoderMockGetChar() override = default;

  MOCK_METHOD(int, getChar, (), (override));
};

class SplashBitmapCMYKEncoderTest_246 : public ::testing::Test {
protected:
  // Create a tiny bitmap that should be safe for construction.
  // CMYK8 is the expected Splash mode for a CMYK bitmap encoder.
  std::unique_ptr<SplashBitmap> makeTinyCmykBitmap() {
    // Common Poppler SplashBitmap ctor:
    // SplashBitmap(int widthA, int heightA, int rowPadA, SplashColorMode modeA,
    //             bool alphaA, bool topDownA, SplashBitmap *parentA = nullptr)
    //
    // Use a 1x1 bitmap; rowPad 4 (CMYK bytes-per-pixel) is a reasonable minimum.
    return std::make_unique<SplashBitmap>(1, 1, 4, splashModeCMYK8, /*alphaA=*/false, /*topDownA=*/true);
  }
};

TEST_F(SplashBitmapCMYKEncoderTest_246, GetUnfilteredCharDelegatesToGetChar_246) {
  auto bmp = makeTinyCmykBitmap();
  SplashBitmapCMYKEncoderMockGetChar enc(bmp.get());

  EXPECT_CALL(enc, getChar()).Times(1).WillOnce(Return(42));

  EXPECT_EQ(enc.getUnfilteredChar(), 42);
}

TEST_F(SplashBitmapCMYKEncoderTest_246, GetUnfilteredCharPropagatesEOF_246) {
  auto bmp = makeTinyCmykBitmap();
  SplashBitmapCMYKEncoderMockGetChar enc(bmp.get());

  EXPECT_CALL(enc, getChar()).Times(1).WillOnce(Return(-1));

  EXPECT_EQ(enc.getUnfilteredChar(), -1);
}

TEST_F(SplashBitmapCMYKEncoderTest_246, GetUnfilteredCharMultipleCallsMatchUnderlyingGetChar_246) {
  auto bmp = makeTinyCmykBitmap();
  SplashBitmapCMYKEncoderMockGetChar enc(bmp.get());

  Sequence s;
  EXPECT_CALL(enc, getChar()).InSequence(s).WillOnce(Return(0));
  EXPECT_CALL(enc, getChar()).InSequence(s).WillOnce(Return(255));
  EXPECT_CALL(enc, getChar()).InSequence(s).WillOnce(Return(-1));

  EXPECT_EQ(enc.getUnfilteredChar(), 0);
  EXPECT_EQ(enc.getUnfilteredChar(), 255);
  EXPECT_EQ(enc.getUnfilteredChar(), -1);
}

} // namespace