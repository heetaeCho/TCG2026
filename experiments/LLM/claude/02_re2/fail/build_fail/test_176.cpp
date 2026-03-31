#include "gtest/gtest.h"
#include "./TestProjects/re2/util/pcre.h"

namespace re2 {

class PCREOptionsTest_176 : public ::testing::Test {
 protected:
  PCRE_Options options_;
};

// Test default construction values
TEST_F(PCREOptionsTest_176, DefaultConstructionOption_176) {
  EXPECT_EQ(options_.option(), PCRE::None);
}

TEST_F(PCREOptionsTest_176, DefaultConstructionMatchLimit_176) {
  EXPECT_EQ(options_.match_limit(), 0);
}

TEST_F(PCREOptionsTest_176, DefaultConstructionStackLimit_176) {
  EXPECT_EQ(options_.stack_limit(), 0);
}

TEST_F(PCREOptionsTest_176, DefaultConstructionReportErrors_176) {
  EXPECT_TRUE(options_.report_errors());
}

// Test set_option and option()
TEST_F(PCREOptionsTest_176, SetOptionNone_176) {
  options_.set_option(PCRE::None);
  EXPECT_EQ(options_.option(), PCRE::None);
}

TEST_F(PCREOptionsTest_176, SetOptionUTF8_176) {
  options_.set_option(PCRE::UTF8);
  EXPECT_EQ(options_.option(), PCRE::UTF8);
}

TEST_F(PCREOptionsTest_176, SetOptionMultiline_176) {
  options_.set_option(PCRE::MULTILINE);
  EXPECT_EQ(options_.option(), PCRE::MULTILINE);
}

TEST_F(PCREOptionsTest_176, SetOptionOverwritesPrevious_176) {
  options_.set_option(PCRE::UTF8);
  EXPECT_EQ(options_.option(), PCRE::UTF8);
  options_.set_option(PCRE::MULTILINE);
  EXPECT_EQ(options_.option(), PCRE::MULTILINE);
}

// Test set_match_limit and match_limit()
TEST_F(PCREOptionsTest_176, SetMatchLimitPositive_176) {
  options_.set_match_limit(1000);
  EXPECT_EQ(options_.match_limit(), 1000);
}

TEST_F(PCREOptionsTest_176, SetMatchLimitZero_176) {
  options_.set_match_limit(0);
  EXPECT_EQ(options_.match_limit(), 0);
}

TEST_F(PCREOptionsTest_176, SetMatchLimitLargeValue_176) {
  options_.set_match_limit(INT_MAX);
  EXPECT_EQ(options_.match_limit(), INT_MAX);
}

TEST_F(PCREOptionsTest_176, SetMatchLimitOverwritesPrevious_176) {
  options_.set_match_limit(500);
  EXPECT_EQ(options_.match_limit(), 500);
  options_.set_match_limit(1500);
  EXPECT_EQ(options_.match_limit(), 1500);
}

// Test set_stack_limit and stack_limit()
TEST_F(PCREOptionsTest_176, SetStackLimitPositive_176) {
  options_.set_stack_limit(2048);
  EXPECT_EQ(options_.stack_limit(), 2048);
}

TEST_F(PCREOptionsTest_176, SetStackLimitZero_176) {
  options_.set_stack_limit(0);
  EXPECT_EQ(options_.stack_limit(), 0);
}

TEST_F(PCREOptionsTest_176, SetStackLimitLargeValue_176) {
  options_.set_stack_limit(INT_MAX);
  EXPECT_EQ(options_.stack_limit(), INT_MAX);
}

TEST_F(PCREOptionsTest_176, SetStackLimitOverwritesPrevious_176) {
  options_.set_stack_limit(100);
  EXPECT_EQ(options_.stack_limit(), 100);
  options_.set_stack_limit(999);
  EXPECT_EQ(options_.stack_limit(), 999);
}

// Test set_report_errors and report_errors()
TEST_F(PCREOptionsTest_176, SetReportErrorsFalse_176) {
  options_.set_report_errors(false);
  EXPECT_FALSE(options_.report_errors());
}

TEST_F(PCREOptionsTest_176, SetReportErrorsTrue_176) {
  options_.set_report_errors(true);
  EXPECT_TRUE(options_.report_errors());
}

TEST_F(PCREOptionsTest_176, SetReportErrorsToggle_176) {
  options_.set_report_errors(false);
  EXPECT_FALSE(options_.report_errors());
  options_.set_report_errors(true);
  EXPECT_TRUE(options_.report_errors());
}

// Test independence of fields
TEST_F(PCREOptionsTest_176, FieldsAreIndependent_176) {
  options_.set_option(PCRE::UTF8);
  options_.set_match_limit(42);
  options_.set_stack_limit(84);
  options_.set_report_errors(false);

  EXPECT_EQ(options_.option(), PCRE::UTF8);
  EXPECT_EQ(options_.match_limit(), 42);
  EXPECT_EQ(options_.stack_limit(), 84);
  EXPECT_FALSE(options_.report_errors());
}

// Test that setting one field doesn't affect others
TEST_F(PCREOptionsTest_176, SetOptionDoesNotAffectOtherFields_176) {
  options_.set_match_limit(100);
  options_.set_stack_limit(200);
  options_.set_report_errors(false);

  options_.set_option(PCRE::MULTILINE);

  EXPECT_EQ(options_.match_limit(), 100);
  EXPECT_EQ(options_.stack_limit(), 200);
  EXPECT_FALSE(options_.report_errors());
}

TEST_F(PCREOptionsTest_176, SetMatchLimitDoesNotAffectOtherFields_176) {
  options_.set_option(PCRE::UTF8);
  options_.set_stack_limit(200);
  options_.set_report_errors(false);

  options_.set_match_limit(999);

  EXPECT_EQ(options_.option(), PCRE::UTF8);
  EXPECT_EQ(options_.stack_limit(), 200);
  EXPECT_FALSE(options_.report_errors());
}

}  // namespace re2
