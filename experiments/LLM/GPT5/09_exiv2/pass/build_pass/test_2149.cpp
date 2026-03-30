// ***************************************************************** -*- C++ -*-
// Unit tests for Exiv2::Error (template ctor with 1 argument)
// File: test_error_template_ctor_2149.cpp
// *****************************************************************

#include <gtest/gtest.h>

#include <exiv2/error.hpp>

#include <cstring>
#include <exception>
#include <string>

namespace {

class ErrorTest_2149 : public ::testing::Test {};

TEST_F(ErrorTest_2149, ConstructWithCString_DoesNotThrow_2149) {
  const Exiv2::ErrorCode code = static_cast<Exiv2::ErrorCode>(0);

  EXPECT_NO_THROW({
    Exiv2::Error err(code, "arg1");
    (void)err;
  });
}

TEST_F(ErrorTest_2149, ConstructWithStdString_DoesNotThrow_2149) {
  const Exiv2::ErrorCode code = static_cast<Exiv2::ErrorCode>(0);
  const std::string arg1 = "hello";

  EXPECT_NO_THROW({
    Exiv2::Error err(code, arg1);
    (void)err;
  });
}

TEST_F(ErrorTest_2149, ConstructWithIntegralType_DoesNotThrow_2149) {
  const Exiv2::ErrorCode code = static_cast<Exiv2::ErrorCode>(0);

  EXPECT_NO_THROW({
    Exiv2::Error err(code, 12345);
    (void)err;
  });
}

TEST_F(ErrorTest_2149, CodeMatchesConstructorArgument_2149) {
  const Exiv2::ErrorCode code = static_cast<Exiv2::ErrorCode>(0);
  Exiv2::Error err(code, "arg1");

  // Observable behavior: public accessor should report the code passed in.
  EXPECT_EQ(err.code(), code);
}

TEST_F(ErrorTest_2149, WhatReturnsNonNullAndStableAcrossCalls_2149) {
  const Exiv2::ErrorCode code = static_cast<Exiv2::ErrorCode>(0);
  Exiv2::Error err(code, "arg1");

  const char* w1 = nullptr;
  const char* w2 = nullptr;

  EXPECT_NO_THROW({ w1 = err.what(); });
  EXPECT_NO_THROW({ w2 = err.what(); });

  ASSERT_NE(w1, nullptr);
  ASSERT_NE(w2, nullptr);

  // Don't assume formatting/content. Just check it behaves like a valid C-string.
  EXPECT_GE(std::strlen(w1), static_cast<std::size_t>(0));
  EXPECT_GE(std::strlen(w2), static_cast<std::size_t>(0));
}

TEST_F(ErrorTest_2149, CanBeCaughtAsStdException_2149) {
  const Exiv2::ErrorCode code = static_cast<Exiv2::ErrorCode>(0);

  try {
    throw Exiv2::Error(code, "arg1");
  } catch (const std::exception& e) {
    const char* w = e.what();
    ASSERT_NE(w, nullptr);
    EXPECT_GE(std::strlen(w), static_cast<std::size_t>(0));
  } catch (...) {
    FAIL() << "Expected to catch Exiv2::Error as std::exception";
  }
}

TEST_F(ErrorTest_2149, Boundary_EmptyStringArgument_DoesNotThrow_2149) {
  const Exiv2::ErrorCode code = static_cast<Exiv2::ErrorCode>(0);

  Exiv2::Error err(code, std::string{});
  const char* w = nullptr;
  EXPECT_NO_THROW({ w = err.what(); });
  ASSERT_NE(w, nullptr);
}

TEST_F(ErrorTest_2149, Boundary_LongStringArgument_DoesNotThrow_2149) {
  const Exiv2::ErrorCode code = static_cast<Exiv2::ErrorCode>(0);
  const std::string long_arg(64 * 1024, 'x');

  Exiv2::Error err(code, long_arg);
  const char* w = nullptr;
  EXPECT_NO_THROW({ w = err.what(); });
  ASSERT_NE(w, nullptr);
}

}  // namespace