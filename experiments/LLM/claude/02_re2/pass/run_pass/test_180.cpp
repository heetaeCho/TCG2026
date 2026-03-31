#include "gtest/gtest.h"
#include "./TestProjects/re2/util/pcre.h"

namespace re2 {

class PCREOptionsTest_180 : public ::testing::Test {
 protected:
  PCRE_Options options_;
};

// Test default construction values
TEST_F(PCREOptionsTest_180, DefaultStackLimitIsZero_180) {
  EXPECT_EQ(options_.stack_limit(), 0);
}

TEST_F(PCREOptionsTest_180, DefaultMatchLimitIsZero_180) {
  EXPECT_EQ(options_.match_limit(), 0);
}

TEST_F(PCREOptionsTest_180, DefaultReportErrorsIsTrue_180) {
  EXPECT_TRUE(options_.report_errors());
}

TEST_F(PCREOptionsTest_180, DefaultOptionIsNone_180) {
  EXPECT_EQ(options_.option(), PCRE::None);
}

// Test set_stack_limit and stack_limit
TEST_F(PCREOptionsTest_180, SetStackLimitPositiveValue_180) {
  options_.set_stack_limit(1024);
  EXPECT_EQ(options_.stack_limit(), 1024);
}

TEST_F(PCREOptionsTest_180, SetStackLimitZero_180) {
  options_.set_stack_limit(0);
  EXPECT_EQ(options_.stack_limit(), 0);
}

TEST_F(PCREOptionsTest_180, SetStackLimitNegativeValue_180) {
  options_.set_stack_limit(-1);
  EXPECT_EQ(options_.stack_limit(), -1);
}

TEST_F(PCREOptionsTest_180, SetStackLimitLargeValue_180) {
  options_.set_stack_limit(INT_MAX);
  EXPECT_EQ(options_.stack_limit(), INT_MAX);
}

TEST_F(PCREOptionsTest_180, SetStackLimitMultipleTimes_180) {
  options_.set_stack_limit(100);
  EXPECT_EQ(options_.stack_limit(), 100);
  options_.set_stack_limit(200);
  EXPECT_EQ(options_.stack_limit(), 200);
  options_.set_stack_limit(0);
  EXPECT_EQ(options_.stack_limit(), 0);
}

// Test set_match_limit and match_limit
TEST_F(PCREOptionsTest_180, SetMatchLimitPositiveValue_180) {
  options_.set_match_limit(500);
  EXPECT_EQ(options_.match_limit(), 500);
}

TEST_F(PCREOptionsTest_180, SetMatchLimitZero_180) {
  options_.set_match_limit(0);
  EXPECT_EQ(options_.match_limit(), 0);
}

TEST_F(PCREOptionsTest_180, SetMatchLimitLargeValue_180) {
  options_.set_match_limit(INT_MAX);
  EXPECT_EQ(options_.match_limit(), INT_MAX);
}

TEST_F(PCREOptionsTest_180, SetMatchLimitMultipleTimes_180) {
  options_.set_match_limit(10);
  EXPECT_EQ(options_.match_limit(), 10);
  options_.set_match_limit(20);
  EXPECT_EQ(options_.match_limit(), 20);
}

// Test set_report_errors and report_errors
TEST_F(PCREOptionsTest_180, SetReportErrorsFalse_180) {
  options_.set_report_errors(false);
  EXPECT_FALSE(options_.report_errors());
}

TEST_F(PCREOptionsTest_180, SetReportErrorsTrue_180) {
  options_.set_report_errors(false);
  EXPECT_FALSE(options_.report_errors());
  options_.set_report_errors(true);
  EXPECT_TRUE(options_.report_errors());
}

// Test set_option and option
TEST_F(PCREOptionsTest_180, SetOptionValue_180) {
  options_.set_option(PCRE::None);
  EXPECT_EQ(options_.option(), PCRE::None);
}

// Test independence of fields
TEST_F(PCREOptionsTest_180, FieldsAreIndependent_180) {
  options_.set_stack_limit(42);
  options_.set_match_limit(84);
  options_.set_report_errors(false);

  EXPECT_EQ(options_.stack_limit(), 42);
  EXPECT_EQ(options_.match_limit(), 84);
  EXPECT_FALSE(options_.report_errors());

  // Changing one should not affect others
  options_.set_stack_limit(99);
  EXPECT_EQ(options_.stack_limit(), 99);
  EXPECT_EQ(options_.match_limit(), 84);
  EXPECT_FALSE(options_.report_errors());
}

}  // namespace re2
