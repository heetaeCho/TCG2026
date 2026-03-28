// FixedLengthEncoder_getPSFilter_test_206.cpp

#include <gtest/gtest.h>

#include <optional>
#include <string>

// The class under test is declared in this header.
#include "Stream.h"

namespace {

class FixedLengthEncoderTest_206 : public ::testing::Test {
 protected:
  FixedLengthEncoder encoder_;
};

TEST_F(FixedLengthEncoderTest_206, GetPSFilterReturnsEmptyOptionalForTypicalInputs_206) {
  const std::optional<std::string> result = encoder_.getPSFilter(/*psLevel=*/2, /*indent=*/"  ");
  EXPECT_FALSE(result.has_value());
}

TEST_F(FixedLengthEncoderTest_206, GetPSFilterReturnsEmptyOptionalForVariousPsLevels_206) {
  const char* const indent = "    ";

  for (int psLevel : { -1, 0, 1, 2, 3, 999999 }) {
    const std::optional<std::string> result = encoder_.getPSFilter(psLevel, indent);
    EXPECT_FALSE(result.has_value()) << "psLevel=" << psLevel;
  }
}

TEST_F(FixedLengthEncoderTest_206, GetPSFilterReturnsEmptyOptionalForVariousIndents_206) {
  for (const char* indent : { "", " ", "\t", "  ", "        ", ">>>indent<<<" }) {
    const std::optional<std::string> result = encoder_.getPSFilter(/*psLevel=*/1, indent);
    EXPECT_FALSE(result.has_value()) << "indent=\"" << (indent ? indent : "(null)") << "\"";
  }
}

}  // namespace