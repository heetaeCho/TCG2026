// File: re2_error_arg_test.cc
#include <gtest/gtest.h>
#include <string>

// Include the header under test
#include "re2/re2.h"

using re2::RE2;

// A simple fixture to group tests for error_arg()
class RE2ErrorArgTest_5 : public ::testing::Test {};

// Verifies that error_arg() returns a const std::string& (compiles and binds to a reference).
TEST_F(RE2ErrorArgTest_5, ErrorArg_ReturnsConstStringRef_5) {
  RE2 re("a");  // treat implementation as a black box; any simple pattern
  const std::string& ref = re.error_arg();
  // We don't assume content; just ensure we can read size() from the referenced string.
  (void)ref.size();
  SUCCEED();
}

// Verifies that repeated calls return a reference to the same string object (stable aliasing).
TEST_F(RE2ErrorArgTest_5, ErrorArg_ReferenceStableAcrossCalls_5) {
  RE2 re("a");
  const std::string* ref1 = &re.error_arg();
  const std::string* ref2 = &re.error_arg();
  // Same object address indicates stable reference semantics.
  EXPECT_EQ(ref1, ref2);
}

// Calls error_arg() on an empty pattern instance to ensure it is callable without assumptions.
// (No assumptions about content or error state.)
TEST_F(RE2ErrorArgTest_5, ErrorArg_CallOnEmptyPattern_NoCrash_5) {
  RE2 re("");
  // Just calling and touching the reference should not crash.
  const std::string& ref = re.error_arg();
  (void)ref.size();
  SUCCEED();
}

// Calls error_arg() on a pattern that may be invalid in some engines.
// We don't assert error specifics—only that the accessor is callable consistently.
TEST_F(RE2ErrorArgTest_5, ErrorArg_CallAfterPotentialErrorPattern_NoCrash_5) {
  RE2 re("(");  // might be invalid; treat as black box
  const std::string* ref1 = &re.error_arg();
  const std::string* ref2 = &re.error_arg();
  // Even in error scenarios, repeated calls should be safe and consistent.
  EXPECT_EQ(ref1, ref2);
}
