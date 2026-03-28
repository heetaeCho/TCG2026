#include "gtest/gtest.h"
#include "./TestProjects/re2/util/pcre.h"

namespace re2 {

// Test default construction
TEST(PCREOptionsTest_175, DefaultConstructionOption_175) {
  PCRE_Options options;
  EXPECT_EQ(options.option(), PCRE::None);
}

TEST(PCREOptionsTest_175, DefaultConstructionMatchLimit_175) {
  PCRE_Options options;
  EXPECT_EQ(options.match_limit(), 0);
}

TEST(PCREOptionsTest_175, DefaultConstructionStackLimit_175) {
  PCRE_Options options;
  EXPECT_EQ(options.stack_limit(), 0);
}

TEST(PCREOptionsTest_175, DefaultConstructionReportErrors_175) {
  PCRE_Options options;
  EXPECT_TRUE(options.report_errors());
}

// Test set_option and option
TEST(PCREOptionsTest_175, SetOptionAndGetOption_175) {
  PCRE_Options options;
  options.set_option(PCRE::UTF8);
  EXPECT_EQ(options.option(), PCRE::UTF8);
}

TEST(PCREOptionsTest_175, SetOptionNone_175) {
  PCRE_Options options;
  options.set_option(PCRE::UTF8);
  options.set_option(PCRE::None);
  EXPECT_EQ(options.option(), PCRE::None);
}

// Test set_match_limit and match_limit
TEST(PCREOptionsTest_175, SetMatchLimitPositive_175) {
  PCRE_Options options;
  options.set_match_limit(1000);
  EXPECT_EQ(options.match_limit(), 1000);
}

TEST(PCREOptionsTest_175, SetMatchLimitZero_175) {
  PCRE_Options options;
  options.set_match_limit(500);
  options.set_match_limit(0);
  EXPECT_EQ(options.match_limit(), 0);
}

TEST(PCREOptionsTest_175, SetMatchLimitLargeValue_175) {
  PCRE_Options options;
  options.set_match_limit(2147483647);
  EXPECT_EQ(options.match_limit(), 2147483647);
}

TEST(PCREOptionsTest_175, SetMatchLimitNegative_175) {
  PCRE_Options options;
  options.set_match_limit(-1);
  EXPECT_EQ(options.match_limit(), -1);
}

// Test set_stack_limit and stack_limit
TEST(PCREOptionsTest_175, SetStackLimitPositive_175) {
  PCRE_Options options;
  options.set_stack_limit(2048);
  EXPECT_EQ(options.stack_limit(), 2048);
}

TEST(PCREOptionsTest_175, SetStackLimitZero_175) {
  PCRE_Options options;
  options.set_stack_limit(100);
  options.set_stack_limit(0);
  EXPECT_EQ(options.stack_limit(), 0);
}

TEST(PCREOptionsTest_175, SetStackLimitLargeValue_175) {
  PCRE_Options options;
  options.set_stack_limit(2147483647);
  EXPECT_EQ(options.stack_limit(), 2147483647);
}

// Test set_report_errors and report_errors
TEST(PCREOptionsTest_175, SetReportErrorsFalse_175) {
  PCRE_Options options;
  options.set_report_errors(false);
  EXPECT_FALSE(options.report_errors());
}

TEST(PCREOptionsTest_175, SetReportErrorsTrue_175) {
  PCRE_Options options;
  options.set_report_errors(false);
  options.set_report_errors(true);
  EXPECT_TRUE(options.report_errors());
}

// Test multiple fields set independently
TEST(PCREOptionsTest_175, MultipleFieldsIndependent_175) {
  PCRE_Options options;
  options.set_option(PCRE::UTF8);
  options.set_match_limit(500);
  options.set_stack_limit(1024);
  options.set_report_errors(false);

  EXPECT_EQ(options.option(), PCRE::UTF8);
  EXPECT_EQ(options.match_limit(), 500);
  EXPECT_EQ(options.stack_limit(), 1024);
  EXPECT_FALSE(options.report_errors());
}

// Test overwriting values multiple times
TEST(PCREOptionsTest_175, OverwriteOptionMultipleTimes_175) {
  PCRE_Options options;
  options.set_option(PCRE::UTF8);
  EXPECT_EQ(options.option(), PCRE::UTF8);
  options.set_option(PCRE::None);
  EXPECT_EQ(options.option(), PCRE::None);
}

TEST(PCREOptionsTest_175, OverwriteMatchLimitMultipleTimes_175) {
  PCRE_Options options;
  options.set_match_limit(10);
  EXPECT_EQ(options.match_limit(), 10);
  options.set_match_limit(20);
  EXPECT_EQ(options.match_limit(), 20);
  options.set_match_limit(30);
  EXPECT_EQ(options.match_limit(), 30);
}

}  // namespace re2
