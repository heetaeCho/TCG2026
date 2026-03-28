#include "gtest/gtest.h"
#include "./TestProjects/re2/util/pcre.h"

namespace re2 {

// Test default stack_limit value
TEST(PCREOptionsTest_179, DefaultStackLimit_179) {
  PCRE_Options options;
  EXPECT_EQ(options.stack_limit(), 0);
}

// Test set_stack_limit and stack_limit
TEST(PCREOptionsTest_179, SetAndGetStackLimit_179) {
  PCRE_Options options;
  options.set_stack_limit(1024);
  EXPECT_EQ(options.stack_limit(), 1024);
}

// Test setting stack_limit to zero
TEST(PCREOptionsTest_179, SetStackLimitToZero_179) {
  PCRE_Options options;
  options.set_stack_limit(500);
  EXPECT_EQ(options.stack_limit(), 500);
  options.set_stack_limit(0);
  EXPECT_EQ(options.stack_limit(), 0);
}

// Test setting stack_limit to a large value
TEST(PCREOptionsTest_179, SetStackLimitLargeValue_179) {
  PCRE_Options options;
  options.set_stack_limit(INT_MAX);
  EXPECT_EQ(options.stack_limit(), INT_MAX);
}

// Test setting stack_limit to negative value (boundary)
TEST(PCREOptionsTest_179, SetStackLimitNegativeValue_179) {
  PCRE_Options options;
  options.set_stack_limit(-1);
  EXPECT_EQ(options.stack_limit(), -1);
}

// Test setting stack_limit multiple times
TEST(PCREOptionsTest_179, SetStackLimitMultipleTimes_179) {
  PCRE_Options options;
  options.set_stack_limit(100);
  EXPECT_EQ(options.stack_limit(), 100);
  options.set_stack_limit(200);
  EXPECT_EQ(options.stack_limit(), 200);
  options.set_stack_limit(300);
  EXPECT_EQ(options.stack_limit(), 300);
}

// Test default option value
TEST(PCREOptionsTest_179, DefaultOption_179) {
  PCRE_Options options;
  EXPECT_EQ(options.option(), PCRE::None);
}

// Test set_option and option
TEST(PCREOptionsTest_179, SetAndGetOption_179) {
  PCRE_Options options;
  options.set_option(PCRE::UTF8);
  EXPECT_EQ(options.option(), PCRE::UTF8);
}

// Test default match_limit value
TEST(PCREOptionsTest_179, DefaultMatchLimit_179) {
  PCRE_Options options;
  EXPECT_EQ(options.match_limit(), 0);
}

// Test set_match_limit and match_limit
TEST(PCREOptionsTest_179, SetAndGetMatchLimit_179) {
  PCRE_Options options;
  options.set_match_limit(5000);
  EXPECT_EQ(options.match_limit(), 5000);
}

// Test setting match_limit to zero
TEST(PCREOptionsTest_179, SetMatchLimitToZero_179) {
  PCRE_Options options;
  options.set_match_limit(100);
  options.set_match_limit(0);
  EXPECT_EQ(options.match_limit(), 0);
}

// Test default report_errors value
TEST(PCREOptionsTest_179, DefaultReportErrors_179) {
  PCRE_Options options;
  EXPECT_TRUE(options.report_errors());
}

// Test set_report_errors to false
TEST(PCREOptionsTest_179, SetReportErrorsFalse_179) {
  PCRE_Options options;
  options.set_report_errors(false);
  EXPECT_FALSE(options.report_errors());
}

// Test set_report_errors to true
TEST(PCREOptionsTest_179, SetReportErrorsTrue_179) {
  PCRE_Options options;
  options.set_report_errors(false);
  EXPECT_FALSE(options.report_errors());
  options.set_report_errors(true);
  EXPECT_TRUE(options.report_errors());
}

// Test all fields are independent
TEST(PCREOptionsTest_179, FieldsAreIndependent_179) {
  PCRE_Options options;
  options.set_stack_limit(1024);
  options.set_match_limit(2048);
  options.set_report_errors(false);
  
  EXPECT_EQ(options.stack_limit(), 1024);
  EXPECT_EQ(options.match_limit(), 2048);
  EXPECT_FALSE(options.report_errors());
  
  // Changing one should not affect others
  options.set_stack_limit(4096);
  EXPECT_EQ(options.stack_limit(), 4096);
  EXPECT_EQ(options.match_limit(), 2048);
  EXPECT_FALSE(options.report_errors());
}

// Test match_limit with large value
TEST(PCREOptionsTest_179, SetMatchLimitLargeValue_179) {
  PCRE_Options options;
  options.set_match_limit(INT_MAX);
  EXPECT_EQ(options.match_limit(), INT_MAX);
}

}  // namespace re2
