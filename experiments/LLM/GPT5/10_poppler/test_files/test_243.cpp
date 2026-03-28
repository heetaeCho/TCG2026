// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for SplashBitmapCMYKEncoder::getPSFilter
// File under test: ./TestProjects/poppler/poppler/Stream.h
//
// TEST_ID: 243

#include <gtest/gtest.h>

#include <optional>
#include <string>

#include "Stream.h"

namespace {

// If Stream.h requires additional Poppler headers/types in your build,
// include them here as needed. The provided partial interface is treated
// as a black box.

class SplashBitmapCMYKEncoderTest_243 : public ::testing::Test {
 protected:
  // Concrete instance as provided by the partial code.
  SplashBitmapCMYKEncoder encoder_;
};

}  // namespace

TEST_F(SplashBitmapCMYKEncoderTest_243, GetPSFilterReturnsEmptyOptionalForTypicalInputs_243) {
  const int psLevel = 2;
  const char indent[] = "  ";

  const std::optional<std::string> result = encoder_.getPSFilter(psLevel, indent);

  EXPECT_FALSE(result.has_value());
}

TEST_F(SplashBitmapCMYKEncoderTest_243, GetPSFilterReturnsEmptyOptionalForNullIndent_243) {
  const int psLevel = 3;

  const std::optional<std::string> result = encoder_.getPSFilter(psLevel, nullptr);

  EXPECT_FALSE(result.has_value());
}

TEST_F(SplashBitmapCMYKEncoderTest_243, GetPSFilterReturnsEmptyOptionalForExtremePsLevels_243) {
  const char indent[] = "\t";

  {
    const std::optional<std::string> result = encoder_.getPSFilter(0, indent);
    EXPECT_FALSE(result.has_value());
  }
  {
    const std::optional<std::string> result = encoder_.getPSFilter(-1, indent);
    EXPECT_FALSE(result.has_value());
  }
  {
    const std::optional<std::string> result = encoder_.getPSFilter(1000000, indent);
    EXPECT_FALSE(result.has_value());
  }
}

TEST_F(SplashBitmapCMYKEncoderTest_243, GetPSFilterReturnsEmptyOptionalForVariousIndentStrings_243) {
  const int psLevel = 1;

  const char emptyIndent[] = "";
  const char spacesIndent[] = "        ";
  const char mixedIndent[] = " \t  \t";

  EXPECT_FALSE(encoder_.getPSFilter(psLevel, emptyIndent).has_value());
  EXPECT_FALSE(encoder_.getPSFilter(psLevel, spacesIndent).has_value());
  EXPECT_FALSE(encoder_.getPSFilter(psLevel, mixedIndent).has_value());
}

TEST_F(SplashBitmapCMYKEncoderTest_243, GetPSFilterIsRepeatableAndHasNoObservableState_243) {
  const int psLevel = 2;
  const char indent[] = "  ";

  const std::optional<std::string> r1 = encoder_.getPSFilter(psLevel, indent);
  const std::optional<std::string> r2 = encoder_.getPSFilter(psLevel, indent);
  const std::optional<std::string> r3 = encoder_.getPSFilter(psLevel, indent);

  EXPECT_FALSE(r1.has_value());
  EXPECT_FALSE(r2.has_value());
  EXPECT_FALSE(r3.has_value());
}

TEST_F(SplashBitmapCMYKEncoderTest_243, GetPSFilterDoesNotThrowForEdgeCases_243) {
  // Even though exceptions may not be used in the codebase, this test ensures
  // the call is safe for boundary inputs observable via the interface.
  EXPECT_NO_THROW({
    (void)encoder_.getPSFilter(0, nullptr);
    (void)encoder_.getPSFilter(-999999, nullptr);
    const char indent[] = "x";
    (void)encoder_.getPSFilter(999999, indent);
  });
}