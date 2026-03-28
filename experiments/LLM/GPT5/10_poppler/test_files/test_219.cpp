// SPDX-License-Identifier: GPL-2.0-or-later
// TestProjects/poppler/poppler/ASCII85Encoder_tests_219.cpp

#include <gtest/gtest.h>

#if __has_include("poppler/Stream.h")
#include "poppler/Stream.h"
#elif __has_include("Stream.h")
#include "Stream.h"
#else
#error "Cannot find Stream.h (tried <poppler/Stream.h> and <Stream.h>)"
#endif

namespace {

class ASCII85EncoderTest_219 : public ::testing::Test {};

TEST_F(ASCII85EncoderTest_219, IsEncoderReturnsTrue_219) {
  // Only observable contract from the provided interface: isEncoder() returns true.
  ASCII85Encoder enc(nullptr);
  EXPECT_TRUE(enc.isEncoder());

  const ASCII85Encoder& cenc = enc;
  EXPECT_TRUE(cenc.isEncoder());
}

TEST_F(ASCII85EncoderTest_219, IsEncoderStableAcrossMultipleCalls_219) {
  ASCII85Encoder enc(nullptr);

  // Boundary-ish: repeated calls should be consistent.
  EXPECT_TRUE(enc.isEncoder());
  EXPECT_TRUE(enc.isEncoder());
  EXPECT_TRUE(enc.isEncoder());
}

}  // namespace