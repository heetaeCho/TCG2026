// SPDX-License-Identifier: GPL-2.0-or-later
// Unit tests for CMYKGrayEncoder::getPSFilter
// File: CMYKGrayEncoder_test.cpp
//
// The TEST_ID is 233

#include <gtest/gtest.h>

#include <optional>
#include <string>

// Include the header under test
#include "poppler/Stream.h"

namespace {

class CMYKGrayEncoderTest_233 : public ::testing::Test {};

TEST_F(CMYKGrayEncoderTest_233, GetPSFilterReturnsEmptyOptional_DefaultArgs_233) {
  CMYKGrayEncoder enc;

  std::optional<std::string> out = enc.getPSFilter(0, "");

  EXPECT_FALSE(out.has_value());
}

TEST_F(CMYKGrayEncoderTest_233, GetPSFilterReturnsEmptyOptional_NonNullIndent_233) {
  CMYKGrayEncoder enc;

  std::optional<std::string> out = enc.getPSFilter(2, "  ");

  EXPECT_FALSE(out.has_value());
}

TEST_F(CMYKGrayEncoderTest_233, GetPSFilterReturnsEmptyOptional_NullIndentPointer_233) {
  CMYKGrayEncoder enc;

  // Interface accepts const char*. Passing nullptr is a boundary case.
  std::optional<std::string> out = enc.getPSFilter(3, nullptr);

  EXPECT_FALSE(out.has_value());
}

TEST_F(CMYKGrayEncoderTest_233, GetPSFilterReturnsEmptyOptional_ExtremePsLevelValues_233) {
  CMYKGrayEncoder enc;

  // Boundary conditions for int parameter.
  EXPECT_FALSE(enc.getPSFilter(std::numeric_limits<int>::min(), " ").has_value());
  EXPECT_FALSE(enc.getPSFilter(std::numeric_limits<int>::max(), " ").has_value());
}

TEST_F(CMYKGrayEncoderTest_233, GetPSFilterReturnsEmptyOptional_RepeatedCallsStable_233) {
  CMYKGrayEncoder enc;

  auto a = enc.getPSFilter(1, "\t");
  auto b = enc.getPSFilter(1, "\t");
  auto c = enc.getPSFilter(4, "    ");

  EXPECT_FALSE(a.has_value());
  EXPECT_FALSE(b.has_value());
  EXPECT_FALSE(c.has_value());
}

}  // namespace