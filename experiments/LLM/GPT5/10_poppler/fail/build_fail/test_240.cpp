// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID: 240
//
// Unit tests for RGBGrayEncoder (poppler/Stream.h)

#include <gtest/gtest.h>

#include "Stream.h"

class RGBGrayEncoderTest_240 : public ::testing::Test {};

TEST_F(RGBGrayEncoderTest_240, IsBinaryDefaultArgReturnsFalse_240) {
  const RGBGrayEncoder encoder;
  EXPECT_FALSE(encoder.isBinary());
}

TEST_F(RGBGrayEncoderTest_240, IsBinaryExplicitLastTrueReturnsFalse_240) {
  const RGBGrayEncoder encoder;
  EXPECT_FALSE(encoder.isBinary(true));
}

TEST_F(RGBGrayEncoderTest_240, IsBinaryExplicitLastFalseReturnsFalse_240) {
  const RGBGrayEncoder encoder;
  EXPECT_FALSE(encoder.isBinary(false));
}