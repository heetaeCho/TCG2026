#include "gtest/gtest.h"
#include "./TestProjects/re2/util/pcre.h"

namespace re2 {

class PCREOptionsTest_182 : public ::testing::Test {
 protected:
  PCRE_Options options_;
};

// Test that default report_errors is true (based on inferred constructor)
TEST_F(PCREOptionsTest_182, DefaultReportErrorsIsTrue_182) {
  EXPECT_TRUE(options_.report_errors());
}

// Test setting report_errors to false
TEST_F(PCREOptionsTest_182, SetReportErrorsFalse_182) {
  options_.set_report_errors(false);
  EXPECT_FALSE(options_.report_errors());
}

// Test setting report_errors to true explicitly
TEST_F(PCREOptionsTest_182, SetReportErrorsTrue_182) {
  options_.set_report_errors(true);
  EXPECT_TRUE(options_.report_errors());
}

// Test toggling report_errors from true to false and back
TEST_F(PCREOptionsTest_182, ToggleReportErrors_182) {
  EXPECT_TRUE(options_.report_errors());
  options_.set_report_errors(false);
  EXPECT_FALSE(options_.report_errors());
  options_.set_report_errors(true);
  EXPECT_TRUE(options_.report_errors());
}

// Test setting report_errors multiple times to the same value
TEST_F(PCREOptionsTest_182, SetReportErrorsMultipleTimesSameValue_182) {
  options_.set_report_errors(false);
  options_.set_report_errors(false);
  EXPECT_FALSE(options_.report_errors());
  options_.set_report_errors(true);
  options_.set_report_errors(true);
  EXPECT_TRUE(options_.report_errors());
}

// Test default option
TEST_F(PCREOptionsTest_182, DefaultOption_182) {
  EXPECT_EQ(options_.option(), PCRE::None);
}

// Test set_option
TEST_F(PCREOptionsTest_182, SetOption_182) {
  options_.set_option(PCRE::UTF8);
  EXPECT_EQ(options_.option(), PCRE::UTF8);
}

// Test default match_limit is 0
TEST_F(PCREOptionsTest_182, DefaultMatchLimitIsZero_182) {
  EXPECT_EQ(options_.match_limit(), 0);
}

// Test set_match_limit
TEST_F(PCREOptionsTest_182, SetMatchLimit_182) {
  options_.set_match_limit(1000);
  EXPECT_EQ(options_.match_limit(), 1000);
}

// Test set_match_limit to zero
TEST_F(PCREOptionsTest_182, SetMatchLimitZero_182) {
  options_.set_match_limit(500);
  options_.set_match_limit(0);
  EXPECT_EQ(options_.match_limit(), 0);
}

// Test set_match_limit to negative value (boundary)
TEST_F(PCREOptionsTest_182, SetMatchLimitNegative_182) {
  options_.set_match_limit(-1);
  EXPECT_EQ(options_.match_limit(), -1);
}

// Test default stack_limit is 0
TEST_F(PCREOptionsTest_182, DefaultStackLimitIsZero_182) {
  EXPECT_EQ(options_.stack_limit(), 0);
}

// Test set_stack_limit
TEST_F(PCREOptionsTest_182, SetStackLimit_182) {
  options_.set_stack_limit(2048);
  EXPECT_EQ(options_.stack_limit(), 2048);
}

// Test set_stack_limit to zero
TEST_F(PCREOptionsTest_182, SetStackLimitZero_182) {
  options_.set_stack_limit(100);
  options_.set_stack_limit(0);
  EXPECT_EQ(options_.stack_limit(), 0);
}

// Test set_stack_limit to negative value (boundary)
TEST_F(PCREOptionsTest_182, SetStackLimitNegative_182) {
  options_.set_stack_limit(-1);
  EXPECT_EQ(options_.stack_limit(), -1);
}

// Test setting all options together
TEST_F(PCREOptionsTest_182, SetAllOptionsTogether_182) {
  options_.set_option(PCRE::UTF8);
  options_.set_match_limit(500);
  options_.set_stack_limit(1024);
  options_.set_report_errors(false);

  EXPECT_EQ(options_.option(), PCRE::UTF8);
  EXPECT_EQ(options_.match_limit(), 500);
  EXPECT_EQ(options_.stack_limit(), 1024);
  EXPECT_FALSE(options_.report_errors());
}

// Test that large match_limit values are preserved
TEST_F(PCREOptionsTest_182, LargeMatchLimit_182) {
  options_.set_match_limit(INT_MAX);
  EXPECT_EQ(options_.match_limit(), INT_MAX);
}

// Test that large stack_limit values are preserved
TEST_F(PCREOptionsTest_182, LargeStackLimit_182) {
  options_.set_stack_limit(INT_MAX);
  EXPECT_EQ(options_.stack_limit(), INT_MAX);
}

}  // namespace re2
