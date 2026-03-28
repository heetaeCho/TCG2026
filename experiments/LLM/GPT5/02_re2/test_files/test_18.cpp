// File: re2_options_longest_match_test_18.cc
#include <gtest/gtest.h>
#include "re2/re2.h"

// We strictly test via the public interface only (constructors, getters, setters, Copy).
// No assumptions about internal state beyond what is observable through these APIs.

namespace {

using re2::RE2;

// Test fixture kept simple; no shared state required.
class RE2OptionsLongestMatchTest_18 : public ::testing::Test {};

//
// Normal operation: default constructor behavior
//
TEST_F(RE2OptionsLongestMatchTest_18, DefaultIsFalse_18) {
  RE2::Options opts;
  // Observable behavior via the getter
  EXPECT_FALSE(opts.longest_match());
}

//
// Normal operation: setter -> getter reflection
//
TEST_F(RE2OptionsLongestMatchTest_18, SetTrueReflectsInGetter_18) {
  RE2::Options opts;
  opts.set_longest_match(true);
  EXPECT_TRUE(opts.longest_match());
}

//
// Boundary/Toggle behavior: flip true -> false and ensure it tracks
//
TEST_F(RE2OptionsLongestMatchTest_18, ToggleTrueThenFalse_18) {
  RE2::Options opts;

  opts.set_longest_match(true);
  ASSERT_TRUE(opts.longest_match());  // ensure first transition observed

  opts.set_longest_match(false);
  EXPECT_FALSE(opts.longest_match()); // ensure it flips back as observed via getter
}

//
// Constructor variant: CannedOptions POSIX should enable longest_match
// (observable through the getter). We don't rely on internals; just the API.
TEST_F(RE2OptionsLongestMatchTest_18, CannedPOSIXEnablesLongestMatch_18) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.longest_match());
}

//
// Constructor variant: Non-POSIX canned option (e.g., Latin1) should not force longest_match.
// We validate observable behavior only.
TEST_F(RE2OptionsLongestMatchTest_18, CannedLatin1DoesNotEnableLongestMatch_18) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.longest_match());
}

//
// External interaction via public API: Copy should transfer the observable setting
//
TEST_F(RE2OptionsLongestMatchTest_18, CopyCopiesLongestMatch_18) {
  RE2::Options src;
  src.set_longest_match(true);
  RE2::Options dst;
  dst.set_longest_match(false); // ensure it changes after copy if copied correctly

  dst.Copy(src);
  EXPECT_TRUE(dst.longest_match());
}

}  // namespace
