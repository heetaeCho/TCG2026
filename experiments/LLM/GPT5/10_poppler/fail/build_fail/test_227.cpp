// SPDX-License-Identifier: GPL-2.0-or-later
// Unit tests for LZWEncoder (Stream.h)
// TEST_ID: 227

#include <gtest/gtest.h>

#include <limits>
#include <optional>
#include <string>

#include "poppler/Stream.h"

namespace {

class LZWEncoderTest_227 : public ::testing::Test {};

TEST_F(LZWEncoderTest_227, GetPSFilterReturnsEmptyOptionalWithTypicalArgs_227) {
  LZWEncoder enc;

  std::optional<std::string> out = enc.getPSFilter(0, "  ");
  EXPECT_FALSE(out.has_value());
}

TEST_F(LZWEncoderTest_227, GetPSFilterReturnsEmptyOptionalWithNegativePsLevel_227) {
  LZWEncoder enc;

  std::optional<std::string> out = enc.getPSFilter(-1, "");
  EXPECT_FALSE(out.has_value());
}

TEST_F(LZWEncoderTest_227, GetPSFilterReturnsEmptyOptionalWithLargePsLevel_227) {
  LZWEncoder enc;

  std::optional<std::string> out = enc.getPSFilter(std::numeric_limits<int>::max(), "indent");
  EXPECT_FALSE(out.has_value());
}

TEST_F(LZWEncoderTest_227, GetPSFilterReturnsEmptyOptionalWithLongIndent_227) {
  LZWEncoder enc;

  const std::string longIndent(4096, ' ');
  std::optional<std::string> out = enc.getPSFilter(3, longIndent.c_str());
  EXPECT_FALSE(out.has_value());
}

TEST_F(LZWEncoderTest_227, GetPSFilterDoesNotThrowAndReturnsEmptyOptionalWithNullIndent_227) {
  LZWEncoder enc;

  EXPECT_NO_THROW({
    std::optional<std::string> out = enc.getPSFilter(1, nullptr);
    EXPECT_FALSE(out.has_value());
  });
}

TEST_F(LZWEncoderTest_227, GetPSFilterIsConsistentlyEmptyAcrossMultipleCalls_227) {
  LZWEncoder enc;

  const std::optional<std::string> out1 = enc.getPSFilter(0, "x");
  const std::optional<std::string> out2 = enc.getPSFilter(123, "y");
  const std::optional<std::string> out3 = enc.getPSFilter(std::numeric_limits<int>::min(), nullptr);

  EXPECT_FALSE(out1.has_value());
  EXPECT_FALSE(out2.has_value());
  EXPECT_FALSE(out3.has_value());
}

}  // namespace