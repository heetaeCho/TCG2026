// File: eofstream_test_201.cpp
#include <gtest/gtest.h>

#include <climits>
#include <optional>
#include <string>

#include "Stream.h"

// The TEST_ID is 201

class EOFStreamTest_201 : public ::testing::Test {
 protected:
  EOFStream stream_;
};

TEST_F(EOFStreamTest_201, GetPSFilterReturnsEmptyOptionalForTypicalInputs_201) {
  std::optional<std::string> result = stream_.getPSFilter(0, "  ");
  EXPECT_FALSE(result.has_value());
}

TEST_F(EOFStreamTest_201, GetPSFilterReturnsEmptyOptionalWhenIndentIsNull_201) {
  std::optional<std::string> result = stream_.getPSFilter(1, nullptr);
  EXPECT_FALSE(result.has_value());
}

TEST_F(EOFStreamTest_201, GetPSFilterReturnsEmptyOptionalForExtremePsLevelValues_201) {
  std::optional<std::string> r1 = stream_.getPSFilter(INT_MIN, "");
  std::optional<std::string> r2 = stream_.getPSFilter(INT_MAX, "indent");

  EXPECT_FALSE(r1.has_value());
  EXPECT_FALSE(r2.has_value());
}

TEST_F(EOFStreamTest_201, GetPSFilterReturnsEmptyOptionalAcrossMultipleCalls_201) {
  std::optional<std::string> r1 = stream_.getPSFilter(2, "a");
  std::optional<std::string> r2 = stream_.getPSFilter(3, "b");
  std::optional<std::string> r3 = stream_.getPSFilter(-7, nullptr);

  EXPECT_FALSE(r1.has_value());
  EXPECT_FALSE(r2.has_value());
  EXPECT_FALSE(r3.has_value());
}