// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_error_two_arg_ctor_2150.cpp

#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "exiv2/error.hpp"

namespace {

class ErrorTwoArgCtorTest_2150 : public ::testing::Test {
 protected:
  static Exiv2::ErrorCode AnyCode() {
    // Avoid relying on any specific enumerator being present.
    return static_cast<Exiv2::ErrorCode>(0);
  }
};

TEST_F(ErrorTwoArgCtorTest_2150, ConstructsWithTwoCStringArgs_2150) {
  const Exiv2::ErrorCode code = AnyCode();

  EXPECT_NO_THROW({
    Exiv2::Error err(code, "arg1", "arg2");

    // Observable behavior: code() and what()
    EXPECT_EQ(err.code(), code);

    const char* w = err.what();
    EXPECT_NE(w, nullptr);
    // We don't assume any specific formatting, only that a message exists.
    EXPECT_NE(std::string(w).size(), 0u);
  });
}

TEST_F(ErrorTwoArgCtorTest_2150, ConstructsWithStdStringAndCString_2150) {
  const Exiv2::ErrorCode code = AnyCode();
  const std::string a1 = "first";
  const char* a2 = "second";

  Exiv2::Error err(code, a1, a2);

  EXPECT_EQ(err.code(), code);
  EXPECT_NE(err.what(), nullptr);
  EXPECT_NE(std::string(err.what()).size(), 0u);
}

TEST_F(ErrorTwoArgCtorTest_2150, ConstructsWithNumericArgs_2150) {
  const Exiv2::ErrorCode code = AnyCode();

  // Verifies the templated ctor accepts non-string-like types (conversion happens internally).
  Exiv2::Error err(code, 123, -456);

  EXPECT_EQ(err.code(), code);
  EXPECT_NE(err.what(), nullptr);
  EXPECT_NE(std::string(err.what()).size(), 0u);
}

TEST_F(ErrorTwoArgCtorTest_2150, AcceptsEmptyStringArguments_2150) {
  const Exiv2::ErrorCode code = AnyCode();

  Exiv2::Error err(code, "", std::string(""));

  EXPECT_EQ(err.code(), code);
  EXPECT_NE(err.what(), nullptr);
  EXPECT_NE(std::string(err.what()).size(), 0u);
}

TEST_F(ErrorTwoArgCtorTest_2150, WhatIsStableAcrossCalls_2150) {
  const Exiv2::ErrorCode code = AnyCode();
  Exiv2::Error err(code, "alpha", "beta");

  const std::string first = (err.what() ? std::string(err.what()) : std::string());
  const std::string second = (err.what() ? std::string(err.what()) : std::string());
  const std::string third = (err.what() ? std::string(err.what()) : std::string());

  // We avoid assuming pointer identity; only require observable consistency.
  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
  EXPECT_NE(first.size(), 0u);
}

TEST_F(ErrorTwoArgCtorTest_2150, HandlesLongArguments_2150) {
  const Exiv2::ErrorCode code = AnyCode();

  const std::string long1(4096, 'A');
  const std::string long2(4096, 'B');

  Exiv2::Error err(code, long1, long2);

  EXPECT_EQ(err.code(), code);
  ASSERT_NE(err.what(), nullptr);
  EXPECT_NE(std::string(err.what()).size(), 0u);
}

}  // namespace