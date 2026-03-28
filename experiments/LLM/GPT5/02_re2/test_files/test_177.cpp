// File: pcre_options_match_limit_test_177.cc
#include <climits>
#include "gtest/gtest.h"
#include "TestProjects/re2/util/pcre.h"

using namespace re2;

class PCRE_OptionsTest_177 : public ::testing::Test {};

// Normal operation: default-constructed object exposes a match limit.
// (Based on the public API; verifies observable default behavior.)
TEST_F(PCRE_OptionsTest_177, DefaultMatchLimitIsZero_177) {
  PCRE_Options opts;
  EXPECT_EQ(0, opts.match_limit());
}

// Normal operation: setting a typical positive limit is observable via getter.
TEST_F(PCRE_OptionsTest_177, SetMatchLimit_UpdatesValue_177) {
  PCRE_Options opts;
  opts.set_match_limit(123);
  EXPECT_EQ(123, opts.match_limit());
}

// Boundary: setting to zero should be observable via getter.
TEST_F(PCRE_OptionsTest_177, SetMatchLimit_AllowsZero_177) {
  PCRE_Options opts;
  opts.set_match_limit(0);
  EXPECT_EQ(0, opts.match_limit());
}

// Boundary: very large value is preserved (no assumptions about internal caps;
// we only assert what the getter reports after the setter).
TEST_F(PCRE_OptionsTest_177, SetMatchLimit_AllowsIntMax_177) {
  PCRE_Options opts;
  opts.set_match_limit(INT_MAX);
  EXPECT_EQ(INT_MAX, opts.match_limit());
}

// Edge/exceptional input (if permitted by the interface): negative value.
// We don't infer clamping—just verify observable result equals what we set.
TEST_F(PCRE_OptionsTest_177, SetMatchLimit_NegativeValue_177) {
  PCRE_Options opts;
  opts.set_match_limit(-1);
  EXPECT_EQ(-1, opts.match_limit());
}
