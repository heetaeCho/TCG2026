#include "gtest/gtest.h"
#include "./TestProjects/re2/util/pcre.h"

namespace re2 {

// Test fixture for PCRE_Options
class PCREOptionsTest_177 : public ::testing::Test {
protected:
    PCRE_Options options_;
};

// Test default construction values
TEST_F(PCREOptionsTest_177, DefaultMatchLimitIsZero_177) {
    EXPECT_EQ(0, options_.match_limit());
}

TEST_F(PCREOptionsTest_177, DefaultStackLimitIsZero_177) {
    EXPECT_EQ(0, options_.stack_limit());
}

TEST_F(PCREOptionsTest_177, DefaultReportErrorsIsTrue_177) {
    EXPECT_TRUE(options_.report_errors());
}

TEST_F(PCREOptionsTest_177, DefaultOptionIsNone_177) {
    EXPECT_EQ(PCRE::None, options_.option());
}

// Test set_match_limit and match_limit
TEST_F(PCREOptionsTest_177, SetMatchLimitPositiveValue_177) {
    options_.set_match_limit(1000);
    EXPECT_EQ(1000, options_.match_limit());
}

TEST_F(PCREOptionsTest_177, SetMatchLimitZero_177) {
    options_.set_match_limit(0);
    EXPECT_EQ(0, options_.match_limit());
}

TEST_F(PCREOptionsTest_177, SetMatchLimitNegativeValue_177) {
    options_.set_match_limit(-1);
    EXPECT_EQ(-1, options_.match_limit());
}

TEST_F(PCREOptionsTest_177, SetMatchLimitLargeValue_177) {
    options_.set_match_limit(INT_MAX);
    EXPECT_EQ(INT_MAX, options_.match_limit());
}

TEST_F(PCREOptionsTest_177, SetMatchLimitMultipleTimes_177) {
    options_.set_match_limit(100);
    EXPECT_EQ(100, options_.match_limit());
    options_.set_match_limit(200);
    EXPECT_EQ(200, options_.match_limit());
    options_.set_match_limit(0);
    EXPECT_EQ(0, options_.match_limit());
}

// Test set_stack_limit and stack_limit
TEST_F(PCREOptionsTest_177, SetStackLimitPositiveValue_177) {
    options_.set_stack_limit(500);
    EXPECT_EQ(500, options_.stack_limit());
}

TEST_F(PCREOptionsTest_177, SetStackLimitZero_177) {
    options_.set_stack_limit(0);
    EXPECT_EQ(0, options_.stack_limit());
}

TEST_F(PCREOptionsTest_177, SetStackLimitNegativeValue_177) {
    options_.set_stack_limit(-100);
    EXPECT_EQ(-100, options_.stack_limit());
}

TEST_F(PCREOptionsTest_177, SetStackLimitLargeValue_177) {
    options_.set_stack_limit(INT_MAX);
    EXPECT_EQ(INT_MAX, options_.stack_limit());
}

TEST_F(PCREOptionsTest_177, SetStackLimitMultipleTimes_177) {
    options_.set_stack_limit(10);
    EXPECT_EQ(10, options_.stack_limit());
    options_.set_stack_limit(20);
    EXPECT_EQ(20, options_.stack_limit());
}

// Test set_report_errors and report_errors
TEST_F(PCREOptionsTest_177, SetReportErrorsTrue_177) {
    options_.set_report_errors(true);
    EXPECT_TRUE(options_.report_errors());
}

TEST_F(PCREOptionsTest_177, SetReportErrorsFalse_177) {
    options_.set_report_errors(false);
    EXPECT_FALSE(options_.report_errors());
}

TEST_F(PCREOptionsTest_177, SetReportErrorsToggle_177) {
    options_.set_report_errors(false);
    EXPECT_FALSE(options_.report_errors());
    options_.set_report_errors(true);
    EXPECT_TRUE(options_.report_errors());
}

// Test set_option and option
TEST_F(PCREOptionsTest_177, SetOptionNone_177) {
    options_.set_option(PCRE::None);
    EXPECT_EQ(PCRE::None, options_.option());
}

// Test that setting one field doesn't affect others
TEST_F(PCREOptionsTest_177, SettingMatchLimitDoesNotAffectStackLimit_177) {
    options_.set_match_limit(42);
    EXPECT_EQ(0, options_.stack_limit());
    EXPECT_TRUE(options_.report_errors());
}

TEST_F(PCREOptionsTest_177, SettingStackLimitDoesNotAffectMatchLimit_177) {
    options_.set_stack_limit(99);
    EXPECT_EQ(0, options_.match_limit());
    EXPECT_TRUE(options_.report_errors());
}

TEST_F(PCREOptionsTest_177, SettingReportErrorsDoesNotAffectLimits_177) {
    options_.set_report_errors(false);
    EXPECT_EQ(0, options_.match_limit());
    EXPECT_EQ(0, options_.stack_limit());
}

// Test combination of all setters
TEST_F(PCREOptionsTest_177, SetAllFieldsCombination_177) {
    options_.set_match_limit(100);
    options_.set_stack_limit(200);
    options_.set_report_errors(false);
    
    EXPECT_EQ(100, options_.match_limit());
    EXPECT_EQ(200, options_.stack_limit());
    EXPECT_FALSE(options_.report_errors());
}

}  // namespace re2
