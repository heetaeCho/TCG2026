// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <string>

#include <exiv2/types.hpp>

namespace {

class ParseInt64Test_1157 : public ::testing::Test {};

TEST_F(ParseInt64Test_1157, ParsesDecimalInteger_SetsOkTrueAndReturnsValue_1157) {
  bool ok = false;
  const int64_t v = Exiv2::parseInt64("123", ok);

  EXPECT_TRUE(ok);
  EXPECT_EQ(v, 123);
}

TEST_F(ParseInt64Test_1157, ParsesNegativeDecimalInteger_SetsOkTrueAndReturnsValue_1157) {
  bool ok = false;
  const int64_t v = Exiv2::parseInt64("-42", ok);

  EXPECT_TRUE(ok);
  EXPECT_EQ(v, -42);
}

TEST_F(ParseInt64Test_1157, ParsesInt64MaxBoundary_SetsOkTrueAndReturnsMax_1157) {
  const auto maxv = std::numeric_limits<int64_t>::max();
  bool ok = false;
  const int64_t v = Exiv2::parseInt64(std::to_string(maxv), ok);

  EXPECT_TRUE(ok);
  EXPECT_EQ(v, maxv);
}

TEST_F(ParseInt64Test_1157, ParsesInt64MinBoundary_SetsOkTrueAndReturnsMin_1157) {
  const auto minv = std::numeric_limits<int64_t>::min();
  bool ok = false;
  const int64_t v = Exiv2::parseInt64(std::to_string(minv), ok);

  EXPECT_TRUE(ok);
  EXPECT_EQ(v, minv);
}

TEST_F(ParseInt64Test_1157, ParsesFloatString_TruncatesTowardZeroAndSetsOkTrue_1157) {
  bool ok = false;
  const int64_t v = Exiv2::parseInt64("3.9", ok);

  EXPECT_TRUE(ok);
  // Observable behavior: conversion from floating-point to int64_t truncates toward zero.
  EXPECT_EQ(v, 3);
}

TEST_F(ParseInt64Test_1157, ParsesNegativeFloatString_TruncatesTowardZeroAndSetsOkTrue_1157) {
  bool ok = false;
  const int64_t v = Exiv2::parseInt64("-2.3", ok);

  EXPECT_TRUE(ok);
  EXPECT_EQ(v, -2);
}

TEST_F(ParseInt64Test_1157, ParsesBoolTrueString_ReturnsOneAndSetsOkTrue_1157) {
  bool ok = false;
  const int64_t v = Exiv2::parseInt64("true", ok);

  EXPECT_TRUE(ok);
  EXPECT_EQ(v, 1);
}

TEST_F(ParseInt64Test_1157, ParsesBoolFalseString_ReturnsZeroAndSetsOkTrue_1157) {
  bool ok = false;
  const int64_t v = Exiv2::parseInt64("false", ok);

  EXPECT_TRUE(ok);
  EXPECT_EQ(v, 0);
}

TEST_F(ParseInt64Test_1157, InvalidString_SetsOkFalse_1157) {
  bool ok = true;  // start true to ensure it can be reset by the function
  (void)Exiv2::parseInt64("not_a_number", ok);

  EXPECT_FALSE(ok);
}

TEST_F(ParseInt64Test_1157, EmptyString_SetsOkFalse_1157) {
  bool ok = true;
  (void)Exiv2::parseInt64("", ok);

  EXPECT_FALSE(ok);
}

TEST_F(ParseInt64Test_1157, IntegerOverflowString_SetsOkFalse_1157) {
  // One greater than int64 max. We only assert ok becomes false (return value is unspecified here).
  bool ok = true;
  (void)Exiv2::parseInt64("9223372036854775808", ok);

  EXPECT_FALSE(ok);
}

}  // namespace