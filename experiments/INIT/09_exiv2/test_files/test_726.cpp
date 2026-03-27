// File: error_test_726.cpp
// Unit tests for Exiv2::Error (./TestProjects/exiv2/src/error.cpp)

#include <gtest/gtest.h>

#include <cstring>
#include <exception>
#include <type_traits>

#include "exiv2/error.hpp"

namespace {

// Helper: create a deterministic ErrorCode value without relying on specific enumerators.
constexpr Exiv2::ErrorCode kCode0 = static_cast<Exiv2::ErrorCode>(0);
constexpr Exiv2::ErrorCode kCode1 = static_cast<Exiv2::ErrorCode>(1);

class ErrorTest_726 : public ::testing::Test {};

}  // namespace

TEST_F(ErrorTest_726, WhatIsNoexceptAndReturnsCString_726) {
  static_assert(noexcept(std::declval<const Exiv2::Error&>().what()),
                "Exiv2::Error::what() must be noexcept");
  static_assert(std::is_same_v<decltype(std::declval<const Exiv2::Error&>().what()), const char*>,
                "Exiv2::Error::what() must return const char*");

  const Exiv2::Error err(kCode0);

  const char* w = err.what();
  ASSERT_NE(w, nullptr);

  // Must be a valid C-string pointer (at least NUL-terminated).
  // strlen requires NUL-termination; if not, this would be UB in production too.
  (void)std::strlen(w);
}

TEST_F(ErrorTest_726, WhatIsStableAcrossMultipleCalls_726) {
  const Exiv2::Error err(kCode0);

  const char* w1 = err.what();
  const char* w2 = err.what();

  ASSERT_NE(w1, nullptr);
  ASSERT_NE(w2, nullptr);

  // We do not assume pointer identity, only that the observable text is stable.
  EXPECT_STREQ(w1, w2);
}

TEST_F(ErrorTest_726, WhatIsConsistentThroughStdExceptionInterface_726) {
  const Exiv2::Error err(kCode0);

  const std::exception& asStdEx = err;
  const char* wDerived = err.what();
  const char* wBase = asStdEx.what();

  ASSERT_NE(wDerived, nullptr);
  ASSERT_NE(wBase, nullptr);
  EXPECT_STREQ(wDerived, wBase);
}

TEST_F(ErrorTest_726, CodeRoundTripsConstructorInput_BoundaryValues_726) {
  // Boundary-ish cases without relying on specific enum constants.
  const Exiv2::Error err0(kCode0);
  const Exiv2::Error err1(kCode1);

  EXPECT_EQ(err0.code(), kCode0);
  EXPECT_EQ(err1.code(), kCode1);

  // Calling what() should remain safe for different codes.
  ASSERT_NE(err0.what(), nullptr);
  ASSERT_NE(err1.what(), nullptr);
  EXPECT_STREQ(err0.what(), err0.what());
  EXPECT_STREQ(err1.what(), err1.what());
}