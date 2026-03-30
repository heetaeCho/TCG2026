// File: ./TestProjects/re2/util/pcre_options_test_175.cc

#include <climits>
#include "gtest/gtest.h"
#include "TestProjects/re2/util/pcre.h"

using namespace re2;

class PCREOptionsTest_175 : public ::testing::Test {
protected:
    PCRE_Options opts;
};

// --- Default state ----------------------------------------------------------

TEST_F(PCREOptionsTest_175, DefaultsAreAsDocumented_175) {
    // From the provided constructor snippet:
    // option_ = PCRE::None, match_limit_ = 0, stack_limit_ = 0, report_errors_ = true
    EXPECT_EQ(PCRE::None, opts.option());
    EXPECT_EQ(0, opts.match_limit());
    EXPECT_EQ(0, opts.stack_limit());
    EXPECT_TRUE(opts.report_errors());
}

// --- Option flag ------------------------------------------------------------

TEST_F(PCREOptionsTest_175, SetOption_IdempotentWithNone_175) {
    // We only rely on the presence of PCRE::None in the interface.
    opts.set_option(PCRE::None);
    EXPECT_EQ(PCRE::None, opts.option());
}

// --- Match limit ------------------------------------------------------------

TEST_F(PCREOptionsTest_175, SetMatchLimit_RoundTripTypical_175) {
    const int kVal = 123;
    opts.set_match_limit(kVal);
    EXPECT_EQ(kVal, opts.match_limit());
}

TEST_F(PCREOptionsTest_175, SetMatchLimit_ZeroAndMax_175) {
    opts.set_match_limit(0);
    EXPECT_EQ(0, opts.match_limit());

    opts.set_match_limit(INT_MAX);
    EXPECT_EQ(INT_MAX, opts.match_limit());
}

// --- Stack limit ------------------------------------------------------------

TEST_F(PCREOptionsTest_175, SetStackLimit_RoundTripTypical_175) {
    const int kVal = 456;
    opts.set_stack_limit(kVal);
    EXPECT_EQ(kVal, opts.stack_limit());
}

TEST_F(PCREOptionsTest_175, SetStackLimit_ZeroAndMax_175) {
    opts.set_stack_limit(0);
    EXPECT_EQ(0, opts.stack_limit());

    opts.set_stack_limit(INT_MAX);
    EXPECT_EQ(INT_MAX, opts.stack_limit());
}

// --- Error reporting toggle -------------------------------------------------

TEST_F(PCREOptionsTest_175, ToggleReportErrors_175) {
    // default documented as true
    EXPECT_TRUE(opts.report_errors());

    opts.set_report_errors(false);
    EXPECT_FALSE(opts.report_errors());

    opts.set_report_errors(true);
    EXPECT_TRUE(opts.report_errors());
}
