// SPDX-License-Identifier: GPL-2.0-or-later
// File: error_test_725.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "exiv2/error.hpp"

namespace {

using Exiv2::Error;
using Exiv2::ErrorCode;

class ErrorTest_725 : public ::testing::Test {};

constexpr ErrorCode EC(int v) {
  return static_cast<ErrorCode>(v);
}

TEST_F(ErrorTest_725, CodeIsNoexcept_725) {
  static_assert(noexcept(std::declval<const Error&>().code()),
                "Error::code() must be noexcept");
}

TEST_F(ErrorTest_725, CodeReturnsValueFromExplicitConstructor_725) {
  const ErrorCode code = EC(0);
  const Error err(code);

  EXPECT_EQ(err.code(), code);
}

TEST_F(ErrorTest_725, CodeReturnsValueFromTemplateConstructorOneArg_725) {
  const ErrorCode code = EC(1);
  const Error err(code, "arg1");

  EXPECT_EQ(err.code(), code);
}

TEST_F(ErrorTest_725, CodeReturnsValueFromTemplateConstructorTwoArgs_725) {
  const ErrorCode code = EC(42);
  const Error err(code, "arg1", "arg2");

  EXPECT_EQ(err.code(), code);
}

TEST_F(ErrorTest_725, CodeReturnsValueFromTemplateConstructorThreeArgs_725) {
  const ErrorCode code = EC(9999);
  const Error err(code, "arg1", "arg2", "arg3");

  EXPECT_EQ(err.code(), code);
}

TEST_F(ErrorTest_725, CodeStableAcrossMultipleCalls_725) {
  const ErrorCode code = EC(7);
  const Error err(code);

  EXPECT_EQ(err.code(), code);
  EXPECT_EQ(err.code(), code);
  EXPECT_EQ(err.code(), code);
}

TEST_F(ErrorTest_725, CodeWorksThroughBaseExceptionReference_725) {
  const ErrorCode code = EC(123);
  const Error err(code);

  const std::exception& base = err;  // Error derives from std::exception
  (void)base;                        // we only care that this is well-formed

  EXPECT_EQ(err.code(), code);
}

}  // namespace