// SPDX-License-Identifier: GPL-2.0-or-later
// Unit tests for SplashBitmapCMYKEncoder (Poppler)
// File: SplashBitmapCMYKEncoder_test.cpp
//
// The TEST_ID is 250

#include <gtest/gtest.h>

#include <memory>

#include "poppler/Stream.h"
#include "splash/SplashBitmap.h"
#include "splash/SplashTypes.h"

namespace {

class SplashBitmapCMYKEncoderTest_250 : public ::testing::Test {
protected:
  void SetUp() override {
    // Create a tiny, valid CMYK bitmap to avoid relying on null handling in the encoder.
    // SplashBitmap ctor signature (Poppler): SplashBitmap(int w, int h, int rowPad, SplashColorMode mode,
    //                                                   bool alpha, bool topDown = true, ...)
    bitmap_ = std::make_unique<SplashBitmap>(1, 1, /*rowPad=*/1, splashModeCMYK8, /*alphaA=*/false);
    encoder_ = std::make_unique<SplashBitmapCMYKEncoder>(bitmap_.get());
  }

  std::unique_ptr<SplashBitmap> bitmap_;
  std::unique_ptr<SplashBitmapCMYKEncoder> encoder_;
};

TEST_F(SplashBitmapCMYKEncoderTest_250, GetDictReturnsNull_250) {
  ASSERT_NE(encoder_, nullptr);
  EXPECT_EQ(encoder_->getDict(), nullptr);
}

TEST_F(SplashBitmapCMYKEncoderTest_250, GetDictReturnsNullOnRepeatedCalls_250) {
  ASSERT_NE(encoder_, nullptr);
  EXPECT_EQ(encoder_->getDict(), nullptr);
  EXPECT_EQ(encoder_->getDict(), nullptr);
  EXPECT_EQ(encoder_->getDict(), nullptr);
}

TEST_F(SplashBitmapCMYKEncoderTest_250, GetDictRemainsNullAfterRewind_250) {
  ASSERT_NE(encoder_, nullptr);

  // Exercise rewind() as a normal-operation call. We don't assert its return value
  // beyond "call succeeds" because internal behavior is treated as a black box.
  (void)encoder_->rewind();

  EXPECT_EQ(encoder_->getDict(), nullptr);
}

TEST_F(SplashBitmapCMYKEncoderTest_250, GetDictRemainsNullAfterReadingChars_250) {
  ASSERT_NE(encoder_, nullptr);

  // Exercise basic read/look calls; do not assume anything about the stream contents.
  (void)encoder_->lookChar();
  (void)encoder_->getChar();
  (void)encoder_->lookChar();
  (void)encoder_->getChar();

  EXPECT_EQ(encoder_->getDict(), nullptr);
}

TEST_F(SplashBitmapCMYKEncoderTest_250, GetDictRemainsNullAfterPositionOperations_250) {
  ASSERT_NE(encoder_, nullptr);

  // Exercise position APIs without assuming semantics of dir values.
  const Goffset pos0 = encoder_->getPos();
  encoder_->setPos(pos0, /*dir=*/0);
  (void)encoder_->getPos();

  EXPECT_EQ(encoder_->getDict(), nullptr);
}

} // namespace