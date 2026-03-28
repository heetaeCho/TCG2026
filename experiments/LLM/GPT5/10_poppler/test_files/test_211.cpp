// SPDX-License-Identifier: MIT
// Unit tests for ASCIIHexEncoder::getPSFilter
// The TEST_ID is 211

#include <gtest/gtest.h>

#include <optional>
#include <string>

// Include the real header from the codebase.
#include "Stream.h"

namespace {

class ASCIIHexEncoderTest_211 : public ::testing::Test {};

TEST_F(ASCIIHexEncoderTest_211, GetPSFilter_ReturnsEmptyOptional_211) {
  ASCIIHexEncoder encoder;

  const auto result = encoder.getPSFilter(0, "");
  EXPECT_FALSE(result.has_value());
}

TEST_F(ASCIIHexEncoderTest_211, GetPSFilter_ReturnsEmptyOptional_WithNonNullIndent_211) {
  ASCIIHexEncoder encoder;

  const char indent[] = "  ";
  const auto result = encoder.getPSFilter(1, indent);
  EXPECT_FALSE(result.has_value());
}

TEST_F(ASCIIHexEncoderTest_211, GetPSFilter_ReturnsEmptyOptional_WithLargePsLevel_211) {
  ASCIIHexEncoder encoder;

  const auto result = encoder.getPSFilter(9999, ">>");
  EXPECT_FALSE(result.has_value());
}

TEST_F(ASCIIHexEncoderTest_211, GetPSFilter_ReturnsEmptyOptional_WhenIndentIsWhitespace_211) {
  ASCIIHexEncoder encoder;

  const auto result = encoder.getPSFilter(2, " \t");
  EXPECT_FALSE(result.has_value());
}

// Boundary-ish call patterns: ensure it behaves consistently across repeated calls.
TEST_F(ASCIIHexEncoderTest_211, GetPSFilter_RepeatedCallsAlwaysEmpty_211) {
  ASCIIHexEncoder encoder;

  for (int level : {0, 1, 2, 10}) {
    const auto result = encoder.getPSFilter(level, "  ");
    EXPECT_FALSE(result.has_value());
  }
}

}  // namespace