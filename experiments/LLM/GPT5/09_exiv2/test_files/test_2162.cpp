// SPDX-License-Identifier: GPL-2.0-or-later
// File: ./TestProjects/exiv2/tests/error_ctor_test_2162.cpp

#include <gtest/gtest.h>

#include <cstring>
#include <exception>
#include <string>

#include "exiv2/error.hpp"

namespace {

// The TEST_ID is 2162
class ErrorCtorTest_2162 : public ::testing::Test {};

TEST_F(ErrorCtorTest_2162, ConstructsWithCodeAndReturnsSameCode_2162) {
  const auto code = static_cast<Exiv2::ErrorCode>(0);
  Exiv2::Error err(code);

  // Observable behavior: code() reflects the code passed in.
  EXPECT_EQ(err.code(), code);
}

TEST_F(ErrorCtorTest_2162, WhatReturnsNonNullCString_2162) {
  Exiv2::Error err(static_cast<Exiv2::ErrorCode>(0));

  const char* w = err.what();
  EXPECT_NE(w, nullptr);

  // Don't assume any specific message content; just require it is a valid C-string.
  // (If it can be empty, strlen==0 is still valid, so we only check it doesn't crash.)
  (void)std::strlen(w);
}

TEST_F(ErrorCtorTest_2162, WhatIsStableAcrossCallsInContent_2162) {
  Exiv2::Error err(static_cast<Exiv2::ErrorCode>(0));

  const char* w1 = err.what();
  const char* w2 = err.what();

  ASSERT_NE(w1, nullptr);
  ASSERT_NE(w2, nullptr);

  // Do not require pointer stability (implementation-defined); require observable content stability.
  EXPECT_STREQ(w1, w2);
}

TEST_F(ErrorCtorTest_2162, DifferentCodesAreReflectedByCodeAccessor_2162) {
  const auto code0 = static_cast<Exiv2::ErrorCode>(0);
  const auto code1 = static_cast<Exiv2::ErrorCode>(1);

  Exiv2::Error e0(code0);
  Exiv2::Error e1(code1);

  EXPECT_EQ(e0.code(), code0);
  EXPECT_EQ(e1.code(), code1);
}

TEST_F(ErrorCtorTest_2162, CanBeThrownAndCaughtAsStdException_2162) {
  const auto code = static_cast<Exiv2::ErrorCode>(0);

  try {
    throw Exiv2::Error(code);
  } catch (const std::exception& se) {
    // Observable behavior: it is a std::exception and provides a what() message.
    const char* w = se.what();
    EXPECT_NE(w, nullptr);
    (void)std::strlen(w);
  } catch (...) {
    FAIL() << "Expected Exiv2::Error to be caught as std::exception";
  }
}

TEST_F(ErrorCtorTest_2162, CanBeCaughtAsExiv2ErrorAndPreservesCode_2162) {
  const auto code = static_cast<Exiv2::ErrorCode>(1);

  try {
    throw Exiv2::Error(code);
  } catch (const Exiv2::Error& e) {
    EXPECT_EQ(e.code(), code);
    EXPECT_NE(e.what(), nullptr);
  }
}

}  // namespace