// FlateEncoder_test_1652.cpp
#include <gtest/gtest.h>

#include <optional>
#include <string>

#include "FlateEncoder.h"

namespace {

class FlateEncoderTest_1652 : public ::testing::Test {
protected:
  FlateEncoder encoder;
};

TEST_F(FlateEncoderTest_1652, GetPSFilterReturnsNulloptForTypicalInputs_1652) {
  std::optional<std::string> out = encoder.getPSFilter(0, "  ");
  EXPECT_FALSE(out.has_value());
}

TEST_F(FlateEncoderTest_1652, GetPSFilterReturnsNulloptForNonZeroPsLevel_1652) {
  std::optional<std::string> out = encoder.getPSFilter(3, "\t");
  EXPECT_FALSE(out.has_value());
}

TEST_F(FlateEncoderTest_1652, GetPSFilterReturnsNulloptForEmptyIndentString_1652) {
  std::optional<std::string> out = encoder.getPSFilter(1, "");
  EXPECT_FALSE(out.has_value());
}

TEST_F(FlateEncoderTest_1652, GetPSFilterReturnsNulloptForNullIndentPointer_1652) {
  std::optional<std::string> out = encoder.getPSFilter(2, nullptr);
  EXPECT_FALSE(out.has_value());
}

TEST_F(FlateEncoderTest_1652, GetPSFilterIsDeterministicAcrossRepeatedCalls_1652) {
  const std::optional<std::string> out1 = encoder.getPSFilter(5, "    ");
  const std::optional<std::string> out2 = encoder.getPSFilter(5, "    ");
  EXPECT_EQ(out1.has_value(), out2.has_value());
  if (out1.has_value() && out2.has_value()) {
    EXPECT_EQ(*out1, *out2);
  }
}

TEST_F(FlateEncoderTest_1652, GetPSFilterHandlesExtremePsLevelValues_1652) {
  std::optional<std::string> outMin = encoder.getPSFilter(std::numeric_limits<int>::min(), " ");
  std::optional<std::string> outMax = encoder.getPSFilter(std::numeric_limits<int>::max(), " ");
  EXPECT_FALSE(outMin.has_value());
  EXPECT_FALSE(outMax.has_value());
}

TEST_F(FlateEncoderTest_1652, GetPSFilterReturnsNulloptForLongIndent_1652) {
  std::string longIndent(4096, ' ');
  std::optional<std::string> out = encoder.getPSFilter(0, longIndent.c_str());
  EXPECT_FALSE(out.has_value());
}

}  // namespace