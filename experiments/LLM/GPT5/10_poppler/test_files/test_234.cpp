// SPDX-License-Identifier: MIT
//
// Unit tests for CMYKGrayEncoder (Stream.h)
//
// Constraints honored:
// - Treat implementation as a black box (no internal logic assumptions beyond observable interface).
// - Use only the provided public interface.
// - Cover normal + boundary-style cases that are observable.
//
// NOTE:
// The provided partial code shows only:
//   class CMYKGrayEncoder { public: bool isBinary(bool /*last = true*/) const override { return false; } };
// So the only observable behavior we can test is that isBinary(...) returns false for any bool input.

#include <gtest/gtest.h>

// Include the real header from the codebase.
#include "poppler/Stream.h"

namespace {

class CMYKGrayEncoderTest_234 : public ::testing::Test {};

TEST_F(CMYKGrayEncoderTest_234, IsBinaryReturnsFalseWithDefaultLikeTrue_234) {
  CMYKGrayEncoder enc;
  EXPECT_FALSE(enc.isBinary(true));
}

TEST_F(CMYKGrayEncoderTest_234, IsBinaryReturnsFalseWithFalse_234) {
  CMYKGrayEncoder enc;
  EXPECT_FALSE(enc.isBinary(false));
}

TEST_F(CMYKGrayEncoderTest_234, IsBinaryIsConstCallableAndReturnsFalse_234) {
  const CMYKGrayEncoder enc;
  EXPECT_FALSE(enc.isBinary(true));
  EXPECT_FALSE(enc.isBinary(false));
}

TEST_F(CMYKGrayEncoderTest_234, IsBinaryRepeatedCallsAlwaysFalse_234) {
  CMYKGrayEncoder enc;
  for (int i = 0; i < 10; ++i) {
    EXPECT_FALSE(enc.isBinary((i % 2) == 0));
  }
}

}  // namespace