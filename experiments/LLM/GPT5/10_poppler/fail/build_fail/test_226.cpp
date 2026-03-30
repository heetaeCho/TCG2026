// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for LZWEncoder (partial interface)
// File: Stream.h
//
// The TEST_ID is 226

#include <gtest/gtest.h>

#include "poppler/Stream.h"

// NOTE:
// - We only test observable behavior from the provided interface.
// - For this snippet, the only provided/implemented observable behavior is getKind().

namespace {

class LZWEncoderTest_226 : public ::testing::Test {};

TEST_F(LZWEncoderTest_226, GetKindReturnsStrWeird_226) {
  // The provided partial implementation hard-codes getKind() to return strWeird.
  // This is directly observable via the public interface.
  LZWEncoder encoder;
  EXPECT_EQ(encoder.getKind(), strWeird);
}

TEST_F(LZWEncoderTest_226, GetKindIsStableAcrossMultipleCalls_226) {
  LZWEncoder encoder;
  const StreamKind first = encoder.getKind();
  const StreamKind second = encoder.getKind();
  const StreamKind third = encoder.getKind();

  EXPECT_EQ(first, strWeird);
  EXPECT_EQ(second, strWeird);
  EXPECT_EQ(third, strWeird);
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(LZWEncoderTest_226, GetKindMatchesEnumValueForWeird_226) {
  LZWEncoder encoder;

  // Boundary/robustness style check: ensure it maps exactly to the enum constant.
  // (No assumptions about numeric values beyond the enum definition in the header.)
  EXPECT_EQ(encoder.getKind(), StreamKind::strWeird);
}

}  // namespace