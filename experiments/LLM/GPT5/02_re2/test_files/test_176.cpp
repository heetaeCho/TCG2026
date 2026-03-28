// File: pcre_options_test_176.cc
#include <gtest/gtest.h>
#include <climits>
#include "re2/util/pcre.h"

using re2::PCRE_Options;

class PCREOptionsTest_176 : public ::testing::Test {
protected:
  PCRE_Options opts_;
};

// --- Defaults & basic getters ---

TEST_F(PCREOptionsTest_176, DefaultValues_176) {
  // Verify constructor-initialized observable state
  // (Only through public getters; treat as black box.)
  EXPECT_EQ(opts_.option(), PCRE::None);
  EXPECT_EQ(opts_.match_limit(), 0);
  EXPECT_EQ(opts_.stack_limit(), 0);
  EXPECT_TRUE(opts_.report_errors());
}

// --- Option setter/getter ---

TEST_F(PCREOptionsTest_176, SetOptionToNone_176) {
  // Setting to a known enumerator (no inference beyond interface)
  opts_.set_option(PCRE::None);
  EXPECT_EQ(opts_.option(), PCRE::None);
}

TEST_F(PCREOptionsTest_176, SetOptionToArbitraryEnumValue_176) {
  // Treating as black box: set to an arbitrary value of the same enum type.
  // We avoid assuming specific enumerators beyond None.
  const PCRE::Option some_value = static_cast<PCRE::Option>(1);
  opts_.set_option(some_value);
  EXPECT_EQ(opts_.option(), some_value);
}

// --- Match limit setter/getter ---

TEST_F(PCREOptionsTest_176, MatchLimitSetGet_Normal_176) {
  const int kVal = 12345;
  opts_.set_match_limit(kVal);
  EXPECT_EQ(opts_.match_limit(), kVal);
}

TEST_F(PCREOptionsTest_176, MatchLimit_Boundary_IntMax_176) {
  opts_.set_match_limit(INT_MAX);
  EXPECT_EQ(opts_.match_limit(), INT_MAX);
}

TEST_F(PCREOptionsTest_176, MatchLimit_Boundary_IntMin_176) {
  // If implementation clamps or validates, this will fail, revealing behavior.
  const int kMin = INT_MIN;
  opts_.set_match_limit(kMin);
  EXPECT_EQ(opts_.match_limit(), kMin);
}

// --- Stack limit setter/getter ---

TEST_F(PCREOptionsTest_176, StackLimitSetGet_Normal_176) {
  const int kVal = 6789;
  opts_.set_stack_limit(kVal);
  EXPECT_EQ(opts_.stack_limit(), kVal);
}

TEST_F(PCREOptionsTest_176, StackLimit_Boundary_IntMax_176) {
  opts_.set_stack_limit(INT_MAX);
  EXPECT_EQ(opts_.stack_limit(), INT_MAX);
}

TEST_F(PCREOptionsTest_176, StackLimit_Boundary_IntMin_176) {
  const int kMin = INT_MIN;
  opts_.set_stack_limit(kMin);
  EXPECT_EQ(opts_.stack_limit(), kMin);
}

// --- Report errors toggle ---

TEST_F(PCREOptionsTest_176, ReportErrorsToggleFalseTrue_176) {
  opts_.set_report_errors(false);
  EXPECT_FALSE(opts_.report_errors());

  opts_.set_report_errors(true);
  EXPECT_TRUE(opts_.report_errors());
}
