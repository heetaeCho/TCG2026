#include "gtest/gtest.h"
#include "./TestProjects/re2/util/pcre.h"

namespace re2 {

class PCREOptionsTest_178 : public ::testing::Test {
 protected:
  PCRE_Options options_;
};

// Test default construction - match_limit should have a default value
TEST_F(PCREOptionsTest_178, DefaultConstruction_178) {
  PCRE_Options opts;
  EXPECT_EQ(opts.match_limit(), 0);
}

// Test set_match_limit with a positive value
TEST_F(PCREOptionsTest_178, SetMatchLimitPositive_178) {
  options_.set_match_limit(1000);
  EXPECT_EQ(options_.match_limit(), 1000);
}

// Test set_match_limit with zero
TEST_F(PCREOptionsTest_178, SetMatchLimitZero_178) {
  options_.set_match_limit(0);
  EXPECT_EQ(options_.match_limit(), 0);
}

// Test set_match_limit with a large value
TEST_F(PCREOptionsTest_178, SetMatchLimitLargeValue_178) {
  options_.set_match_limit(INT_MAX);
  EXPECT_EQ(options_.match_limit(), INT_MAX);
}

// Test set_match_limit with a negative value
TEST_F(PCREOptionsTest_178, SetMatchLimitNegative_178) {
  options_.set_match_limit(-1);
  EXPECT_EQ(options_.match_limit(), -1);
}

// Test set_match_limit overwrite previous value
TEST_F(PCREOptionsTest_178, SetMatchLimitOverwrite_178) {
  options_.set_match_limit(500);
  EXPECT_EQ(options_.match_limit(), 500);
  options_.set_match_limit(1000);
  EXPECT_EQ(options_.match_limit(), 1000);
}

// Test set_stack_limit with a positive value
TEST_F(PCREOptionsTest_178, SetStackLimitPositive_178) {
  options_.set_stack_limit(2048);
  EXPECT_EQ(options_.stack_limit(), 2048);
}

// Test set_stack_limit with zero
TEST_F(PCREOptionsTest_178, SetStackLimitZero_178) {
  options_.set_stack_limit(0);
  EXPECT_EQ(options_.stack_limit(), 0);
}

// Test default stack_limit
TEST_F(PCREOptionsTest_178, DefaultStackLimit_178) {
  PCRE_Options opts;
  EXPECT_EQ(opts.stack_limit(), 0);
}

// Test set_report_errors to true
TEST_F(PCREOptionsTest_178, SetReportErrorsTrue_178) {
  options_.set_report_errors(true);
  EXPECT_TRUE(options_.report_errors());
}

// Test set_report_errors to false
TEST_F(PCREOptionsTest_178, SetReportErrorsFalse_178) {
  options_.set_report_errors(false);
  EXPECT_FALSE(options_.report_errors());
}

// Test default report_errors
TEST_F(PCREOptionsTest_178, DefaultReportErrors_178) {
  PCRE_Options opts;
  EXPECT_TRUE(opts.report_errors());
}

// Test set_option
TEST_F(PCREOptionsTest_178, SetOption_178) {
  options_.set_option(PCRE::None);
  EXPECT_EQ(options_.option(), PCRE::None);
}

// Test default option
TEST_F(PCREOptionsTest_178, DefaultOption_178) {
  PCRE_Options opts;
  EXPECT_EQ(opts.option(), PCRE::None);
}

// Test multiple set/get operations are independent
TEST_F(PCREOptionsTest_178, IndependentFields_178) {
  options_.set_match_limit(42);
  options_.set_stack_limit(84);
  options_.set_report_errors(false);

  EXPECT_EQ(options_.match_limit(), 42);
  EXPECT_EQ(options_.stack_limit(), 84);
  EXPECT_FALSE(options_.report_errors());
}

// Test overwriting stack_limit
TEST_F(PCREOptionsTest_178, SetStackLimitOverwrite_178) {
  options_.set_stack_limit(100);
  EXPECT_EQ(options_.stack_limit(), 100);
  options_.set_stack_limit(200);
  EXPECT_EQ(options_.stack_limit(), 200);
}

// Test overwriting report_errors
TEST_F(PCREOptionsTest_178, SetReportErrorsOverwrite_178) {
  options_.set_report_errors(false);
  EXPECT_FALSE(options_.report_errors());
  options_.set_report_errors(true);
  EXPECT_TRUE(options_.report_errors());
}

// Test set_match_limit with INT_MIN
TEST_F(PCREOptionsTest_178, SetMatchLimitIntMin_178) {
  options_.set_match_limit(INT_MIN);
  EXPECT_EQ(options_.match_limit(), INT_MIN);
}

// Test set_stack_limit with large value
TEST_F(PCREOptionsTest_178, SetStackLimitLargeValue_178) {
  options_.set_stack_limit(INT_MAX);
  EXPECT_EQ(options_.stack_limit(), INT_MAX);
}

}  // namespace re2
