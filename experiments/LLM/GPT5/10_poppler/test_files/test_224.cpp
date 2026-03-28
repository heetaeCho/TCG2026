// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for RunLengthEncoder (Stream.h)
// TEST_ID: 224

#include <gtest/gtest.h>

#include "Stream.h"

class RunLengthEncoderTest_224 : public ::testing::Test {};

TEST_F(RunLengthEncoderTest_224, IsBinaryReturnsTrueWhenLastTrue_224) {
  RunLengthEncoder enc;
  EXPECT_TRUE(enc.isBinary(true));
}

TEST_F(RunLengthEncoderTest_224, IsBinaryReturnsTrueWhenLastFalse_224) {
  RunLengthEncoder enc;
  EXPECT_TRUE(enc.isBinary(false));
}

TEST_F(RunLengthEncoderTest_224, IsBinaryReturnsTrueForBothBooleanInputs_224) {
  RunLengthEncoder enc;

  const bool inputs[] = {false, true};
  for (bool last : inputs) {
    EXPECT_TRUE(enc.isBinary(last)) << "last=" << last;
  }
}