// File: re2_ok_test_1.cc
#include <string>
#include "gtest/gtest.h"
#include "re2/re2.h"

using re2::RE2;

namespace {

// Verifies that for a *valid* pattern, ok() is equivalent to (error_code() == NoError).
TEST(RE2OkTest_1, OkReflectsErrorCodeForValidPattern_1) {
  RE2 re("abc");  // Pick a simple, well-formed pattern.
  const bool no_error = (re.error_code() == RE2::NoError);
  EXPECT_EQ(no_error, re.ok());
}

// Verifies that for an *invalid* pattern, ok() is equivalent to (error_code() == NoError).
TEST(RE2OkTest_1, OkReflectsErrorCodeForInvalidPattern_1) {
  RE2 re("(");  // Intentionally malformed (unmatched parenthesis).
  const bool no_error = (re.error_code() == RE2::NoError);
  EXPECT_EQ(no_error, re.ok());
}

// Boundary condition: empty pattern.
// We don't assume whether empty is valid or invalid—only that ok() mirrors error_code()==NoError.
TEST(RE2OkTest_1, OkReflectsErrorCodeForEmptyPattern_1) {
  RE2 re("");
  const bool no_error = (re.error_code() == RE2::NoError);
  EXPECT_EQ(no_error, re.ok());
}

// Constructor coverage: const char* vs std::string should behave consistently
// with respect to ok() == (error_code() == NoError).
TEST(RE2OkTest_1, OkConsistencyAcrossConstructors_1) {
  const char* pat_cstr = "a+b*";
  std::string pat_str = pat_cstr;

  RE2 re_cstr(pat_cstr);
  RE2 re_str(pat_str);

  EXPECT_EQ(re_cstr.ok(), (re_cstr.error_code() == RE2::NoError));
  EXPECT_EQ(re_str.ok(), (re_str.error_code() == RE2::NoError));
}

}  // namespace
