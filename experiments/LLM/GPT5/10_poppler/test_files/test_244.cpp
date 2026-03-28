// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for SplashBitmapCMYKEncoder (partial interface)
// File under test: ./TestProjects/poppler/poppler/Stream.h
//
// Constraints note:
// - Treat implementation as a black box.
// - Only test observable behavior via public interface.

#include <gtest/gtest.h>

#include "Stream.h"

namespace {

class SplashBitmapCMYKEncoderTest_244 : public ::testing::Test {};

TEST_F(SplashBitmapCMYKEncoderTest_244, IsBinary_DefaultArg_ReturnsTrue_244) {
  SplashBitmapCMYKEncoder encoder;
  EXPECT_TRUE(encoder.isBinary());
}

TEST_F(SplashBitmapCMYKEncoderTest_244, IsBinary_LastTrue_ReturnsTrue_244) {
  SplashBitmapCMYKEncoder encoder;
  EXPECT_TRUE(encoder.isBinary(true));
}

TEST_F(SplashBitmapCMYKEncoderTest_244, IsBinary_LastFalse_ReturnsTrue_244) {
  SplashBitmapCMYKEncoder encoder;
  EXPECT_TRUE(encoder.isBinary(false));
}

// Boundary-style checks: call repeatedly to ensure stable/consistent observable behavior.
TEST_F(SplashBitmapCMYKEncoderTest_244, IsBinary_RepeatedCalls_AreAlwaysTrue_244) {
  SplashBitmapCMYKEncoder encoder;

  for (int i = 0; i < 100; ++i) {
    EXPECT_TRUE(encoder.isBinary());
    EXPECT_TRUE(encoder.isBinary(true));
    EXPECT_TRUE(encoder.isBinary(false));
  }
}

// Const-correctness / usage through const reference (observable interface behavior should match).
TEST_F(SplashBitmapCMYKEncoderTest_244, IsBinary_CalledOnConstObject_ReturnsTrue_244) {
  const SplashBitmapCMYKEncoder encoder;
  EXPECT_TRUE(encoder.isBinary());
  EXPECT_TRUE(encoder.isBinary(false));
}

}  // namespace