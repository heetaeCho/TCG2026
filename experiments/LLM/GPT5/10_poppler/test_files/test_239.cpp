// SPDX-License-Identifier: GPL-2.0-or-later
//
// File: RGBGrayEncoder_test.cpp
// TEST_ID: 239
//
// Unit tests for RGBGrayEncoder (Stream.h)
//
// Constraints respected:
// - Treat implementation as black box
// - Use only public interface
// - No private state access
// - Include normal + boundary + (observable) error cases

#include <gtest/gtest.h>

#include <optional>
#include <string>

// Include the header under test.
#include "Stream.h"

// If Stream.h places RGBGrayEncoder in a namespace, you may need to adjust this.
// For example: using poppler::RGBGrayEncoder;

namespace {

class RGBGrayEncoderTest_239 : public ::testing::Test {
protected:
  RGBGrayEncoder encoder_;
};

TEST_F(RGBGrayEncoderTest_239, GetPSFilterReturnsEmptyOptional_239) {
  const auto result = encoder_.getPSFilter(1, "  ");
  EXPECT_FALSE(result.has_value());
}

TEST_F(RGBGrayEncoderTest_239, GetPSFilterNullIndentReturnsEmptyOptional_239) {
  const auto result = encoder_.getPSFilter(2, nullptr);
  EXPECT_FALSE(result.has_value());
}

TEST_F(RGBGrayEncoderTest_239, GetPSFilterVariousPSLevelsReturnEmptyOptional_239) {
  // Boundary-ish coverage over a few representative psLevel values.
  for (int level : {0, 1, 2, 3, 10, -1, -100, 100}) {
    const auto result = encoder_.getPSFilter(level, "");
    EXPECT_FALSE(result.has_value()) << "psLevel=" << level;
  }
}

TEST_F(RGBGrayEncoderTest_239, GetPSFilterVariousIndentsReturnEmptyOptional_239) {
  // Indent is accepted as const char*, so test empty, whitespace, and longer strings.
  const char* indents[] = {"", " ", "\t", "    ", ">>", "indent", "0123456789abcdef"};
  for (const char* indent : indents) {
    const auto result = encoder_.getPSFilter(1, indent);
    EXPECT_FALSE(result.has_value()) << "indent=" << (indent ? indent : "(null)");
  }
}

TEST_F(RGBGrayEncoderTest_239, GetPSFilterRepeatedCallsRemainEmptyOptional_239) {
  // Observable behavior should be stable across calls.
  const auto r1 = encoder_.getPSFilter(1, "  ");
  const auto r2 = encoder_.getPSFilter(1, "  ");
  const auto r3 = encoder_.getPSFilter(2, "\t");

  EXPECT_FALSE(r1.has_value());
  EXPECT_FALSE(r2.has_value());
  EXPECT_FALSE(r3.has_value());
}

TEST_F(RGBGrayEncoderTest_239, GetPSFilterDoesNotThrow_239) {
  // Exceptional/error cases are not observable via return values here, but we can ensure no exceptions.
  EXPECT_NO_THROW({
    (void)encoder_.getPSFilter(0, "");
    (void)encoder_.getPSFilter(-1, nullptr);
    (void)encoder_.getPSFilter(999999, "    ");
  });
}

}  // namespace