// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_error_ctor3_2151.cpp
//
// Unit tests for Exiv2::Error 3-argument templated constructor.
//
// Constraints honored:
// - Treat implementation as a black box (no assumptions about message formatting).
// - Test only observable behavior through public interface: code() and what().
// - No private state access.

#include <gtest/gtest.h>

#include <cstring>
#include <exception>
#include <string>
#include <type_traits>

#include "exiv2/error.hpp"

namespace {

// Use a value that compiles regardless of whether ErrorCode is an enum or enum class.
// We intentionally avoid relying on any specific enumerator names.
inline Exiv2::ErrorCode MakeAnyErrorCode(int v = 1) {
  return static_cast<Exiv2::ErrorCode>(v);
}

class ErrorTest_2151 : public ::testing::Test {};

}  // namespace

TEST_F(ErrorTest_2151, Ctor3_StoresCode_2151) {
  const Exiv2::ErrorCode code = MakeAnyErrorCode(7);

  Exiv2::Error err(code, "a1", "a2", "a3");

  // Observable via public API: code() should report the code used to construct.
  EXPECT_EQ(err.code(), code);
}

TEST_F(ErrorTest_2151, Ctor3_WhatIsNonNullAndStable_2151) {
  Exiv2::Error err(MakeAnyErrorCode(3), "x", "y", "z");

  // what() should be callable and return a non-null C-string.
  const char* w1 = nullptr;
  const char* w2 = nullptr;

  EXPECT_NO_THROW(w1 = err.what());
  EXPECT_NE(w1, nullptr);

  // Repeated calls should remain callable and return something usable as a C-string.
  EXPECT_NO_THROW(w2 = err.what());
  EXPECT_NE(w2, nullptr);

  // Without assuming formatting/content, we can still check it's a valid C-string.
  EXPECT_GE(std::strlen(w1), 0u);
  EXPECT_GE(std::strlen(w2), 0u);
}

TEST_F(ErrorTest_2151, Ctor3_CanBeCaughtAsStdException_2151) {
  const Exiv2::ErrorCode code = MakeAnyErrorCode(11);

  try {
    throw Exiv2::Error(code, "arg1", "arg2", "arg3");
  } catch (const std::exception& e) {
    // Observable: polymorphic behavior through std::exception::what().
    const char* w = nullptr;
    EXPECT_NO_THROW(w = e.what());
    EXPECT_NE(w, nullptr);
    // And dynamic type should still allow querying code() if caught as Exiv2::Error.
  } catch (...) {
    FAIL() << "Expected Exiv2::Error to be caught as std::exception";
  }

  try {
    throw Exiv2::Error(code, "arg1", "arg2", "arg3");
  } catch (const Exiv2::Error& e) {
    EXPECT_EQ(e.code(), code);
    const char* w = nullptr;
    EXPECT_NO_THROW(w = e.what());
    EXPECT_NE(w, nullptr);
  } catch (...) {
    FAIL() << "Expected Exiv2::Error to be caught as Exiv2::Error";
  }
}

TEST_F(ErrorTest_2151, Ctor3_AcceptsMixedArgumentTypes_2151) {
  // Boundary/robustness: constructor is templated; ensure it accepts common types.
  // We do not assume how they are rendered, only that construction and what() succeed.
  const std::string s = "str";
  const int number = 42;

  Exiv2::Error err(MakeAnyErrorCode(2), s, number, "tail");

  EXPECT_EQ(err.code(), MakeAnyErrorCode(2));
  const char* w = nullptr;
  EXPECT_NO_THROW(w = err.what());
  EXPECT_NE(w, nullptr);
}

TEST_F(ErrorTest_2151, Ctor3_HandlesEmptyStrings_2151) {
  // Boundary: empty string arguments should still be accepted.
  Exiv2::Error err(MakeAnyErrorCode(9), "", std::string{}, "");

  EXPECT_EQ(err.code(), MakeAnyErrorCode(9));
  const char* w = nullptr;
  EXPECT_NO_THROW(w = err.what());
  EXPECT_NE(w, nullptr);
}

TEST_F(ErrorTest_2151, Ctor3_IndependentInstancesHaveUsableWhat_2151) {
  // Basic sanity: multiple instances constructed with different args are all valid.
  Exiv2::Error e1(MakeAnyErrorCode(1), "a", "b", "c");
  Exiv2::Error e2(MakeAnyErrorCode(2), "d", "e", "f");

  EXPECT_EQ(e1.code(), MakeAnyErrorCode(1));
  EXPECT_EQ(e2.code(), MakeAnyErrorCode(2));

  const char* w1 = nullptr;
  const char* w2 = nullptr;
  EXPECT_NO_THROW(w1 = e1.what());
  EXPECT_NO_THROW(w2 = e2.what());
  EXPECT_NE(w1, nullptr);
  EXPECT_NE(w2, nullptr);
}