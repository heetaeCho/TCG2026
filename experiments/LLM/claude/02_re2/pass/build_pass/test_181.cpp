#include "gtest/gtest.h"
#include "./TestProjects/re2/util/pcre.h"

namespace re2 {

class PCREOptionsTest_181 : public ::testing::Test {
protected:
    PCRE_Options options_;
};

// Test that default construction sets report_errors to true
TEST_F(PCREOptionsTest_181, DefaultReportErrorsIsTrue_181) {
    PCRE_Options opts;
    EXPECT_TRUE(opts.report_errors());
}

// Test that set_report_errors(false) changes report_errors to false
TEST_F(PCREOptionsTest_181, SetReportErrorsFalse_181) {
    options_.set_report_errors(false);
    EXPECT_FALSE(options_.report_errors());
}

// Test that set_report_errors(true) keeps report_errors as true
TEST_F(PCREOptionsTest_181, SetReportErrorsTrue_181) {
    options_.set_report_errors(true);
    EXPECT_TRUE(options_.report_errors());
}

// Test toggling report_errors from true to false and back to true
TEST_F(PCREOptionsTest_181, ToggleReportErrors_181) {
    EXPECT_TRUE(options_.report_errors());
    options_.set_report_errors(false);
    EXPECT_FALSE(options_.report_errors());
    options_.set_report_errors(true);
    EXPECT_TRUE(options_.report_errors());
}

// Test that default option is PCRE::None
TEST_F(PCREOptionsTest_181, DefaultOptionIsNone_181) {
    EXPECT_EQ(options_.option(), PCRE::None);
}

// Test set_option and option getter
TEST_F(PCREOptionsTest_181, SetAndGetOption_181) {
    options_.set_option(PCRE::UTF8);
    EXPECT_EQ(options_.option(), PCRE::UTF8);
}

// Test that default match_limit is 0
TEST_F(PCREOptionsTest_181, DefaultMatchLimitIsZero_181) {
    EXPECT_EQ(options_.match_limit(), 0);
}

// Test set_match_limit and match_limit getter
TEST_F(PCREOptionsTest_181, SetAndGetMatchLimit_181) {
    options_.set_match_limit(1000);
    EXPECT_EQ(options_.match_limit(), 1000);
}

// Test set_match_limit with boundary value
TEST_F(PCREOptionsTest_181, SetMatchLimitBoundary_181) {
    options_.set_match_limit(0);
    EXPECT_EQ(options_.match_limit(), 0);
    options_.set_match_limit(INT_MAX);
    EXPECT_EQ(options_.match_limit(), INT_MAX);
}

// Test that default stack_limit is 0
TEST_F(PCREOptionsTest_181, DefaultStackLimitIsZero_181) {
    EXPECT_EQ(options_.stack_limit(), 0);
}

// Test set_stack_limit and stack_limit getter
TEST_F(PCREOptionsTest_181, SetAndGetStackLimit_181) {
    options_.set_stack_limit(500);
    EXPECT_EQ(options_.stack_limit(), 500);
}

// Test set_stack_limit with boundary value
TEST_F(PCREOptionsTest_181, SetStackLimitBoundary_181) {
    options_.set_stack_limit(0);
    EXPECT_EQ(options_.stack_limit(), 0);
    options_.set_stack_limit(INT_MAX);
    EXPECT_EQ(options_.stack_limit(), INT_MAX);
}

// Test multiple set operations don't interfere with each other
TEST_F(PCREOptionsTest_181, MultipleSettersIndependent_181) {
    options_.set_match_limit(42);
    options_.set_stack_limit(84);
    options_.set_report_errors(false);
    
    EXPECT_EQ(options_.match_limit(), 42);
    EXPECT_EQ(options_.stack_limit(), 84);
    EXPECT_FALSE(options_.report_errors());
}

// Test that setting match_limit with negative value works (int allows it)
TEST_F(PCREOptionsTest_181, SetMatchLimitNegative_181) {
    options_.set_match_limit(-1);
    EXPECT_EQ(options_.match_limit(), -1);
}

// Test that setting stack_limit with negative value works
TEST_F(PCREOptionsTest_181, SetStackLimitNegative_181) {
    options_.set_stack_limit(-1);
    EXPECT_EQ(options_.stack_limit(), -1);
}

// Test copy behavior - ensure a fresh PCRE_Options has all defaults
TEST_F(PCREOptionsTest_181, FreshObjectHasAllDefaults_181) {
    PCRE_Options fresh;
    EXPECT_EQ(fresh.option(), PCRE::None);
    EXPECT_EQ(fresh.match_limit(), 0);
    EXPECT_EQ(fresh.stack_limit(), 0);
    EXPECT_TRUE(fresh.report_errors());
}

}  // namespace re2
