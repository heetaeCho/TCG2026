// File: pcre_options_test_178.cc
#include <climits>
#include "gtest/gtest.h"
#include "./TestProjects/re2/util/pcre.h"

using namespace re2;

class PCREOptionsTest_178 : public ::testing::Test {
protected:
    PCRE_Options opts_;
};

// --- Defaults ---

TEST_F(PCREOptionsTest_178, Defaults_AreWellDefined_178) {
    // Expect observable defaults via the public getters.
    // (Interface exposes these; we don't rely on internal state.)
    EXPECT_EQ(0, opts_.match_limit());
    EXPECT_EQ(0, opts_.stack_limit());
    EXPECT_TRUE(opts_.report_errors());
}

TEST_F(PCREOptionsTest_178, DefaultOption_IsNone_178) {
    // Only uses the public API; verifies default enum value if exposed.
    EXPECT_EQ(PCRE::None, opts_.option());
}

// --- match_limit ---

TEST_F(PCREOptionsTest_178, SetMatchLimit_Positive_ReflectsViaGetter_178) {
    opts_.set_match_limit(1000);
    EXPECT_EQ(1000, opts_.match_limit());
}

TEST_F(PCREOptionsTest_178, SetMatchLimit_Zero_ReflectsViaGetter_178) {
    opts_.set_match_limit(0);
    EXPECT_EQ(0, opts_.match_limit());
}

TEST_F(PCREOptionsTest_178, SetMatchLimit_Negative_ReflectsAsSet_178) {
    // We don't assume validation; we only confirm observable return.
    opts_.set_match_limit(-1);
    EXPECT_EQ(-1, opts_.match_limit());
}

TEST_F(PCREOptionsTest_178, SetMatchLimit_IntMax_ReflectsViaGetter_178) {
    opts_.set_match_limit(INT_MAX);
    EXPECT_EQ(INT_MAX, opts_.match_limit());
}

TEST_F(PCREOptionsTest_178, SetMatchLimit_MultipleSequentialUpdates_178) {
    opts_.set_match_limit(10);
    EXPECT_EQ(10, opts_.match_limit());
    opts_.set_match_limit(20);
    EXPECT_EQ(20, opts_.match_limit());
    opts_.set_match_limit(-5);
    EXPECT_EQ(-5, opts_.match_limit());
}

// --- stack_limit ---

TEST_F(PCREOptionsTest_178, SetStackLimit_Positive_ReflectsViaGetter_178) {
    opts_.set_stack_limit(2048);
    EXPECT_EQ(2048, opts_.stack_limit());
}

TEST_F(PCREOptionsTest_178, SetStackLimit_Zero_ReflectsViaGetter_178) {
    opts_.set_stack_limit(0);
    EXPECT_EQ(0, opts_.stack_limit());
}

TEST_F(PCREOptionsTest_178, SetStackLimit_Negative_ReflectsAsSet_178) {
    opts_.set_stack_limit(-256);
    EXPECT_EQ(-256, opts_.stack_limit());
}

TEST_F(PCREOptionsTest_178, SetStackLimit_IntMax_ReflectsViaGetter_178) {
    opts_.set_stack_limit(INT_MAX);
    EXPECT_EQ(INT_MAX, opts_.stack_limit());
}

TEST_F(PCREOptionsTest_178, SetStackLimit_MultipleSequentialUpdates_178) {
    opts_.set_stack_limit(1);
    EXPECT_EQ(1, opts_.stack_limit());
    opts_.set_stack_limit(2);
    EXPECT_EQ(2, opts_.stack_limit());
    opts_.set_stack_limit(-3);
    EXPECT_EQ(-3, opts_.stack_limit());
}

// --- report_errors ---

TEST_F(PCREOptionsTest_178, SetReportErrors_FalseThenTrue_TogglesViaGetter_178) {
    opts_.set_report_errors(false);
    EXPECT_FALSE(opts_.report_errors());
    opts_.set_report_errors(true);
    EXPECT_TRUE(opts_.report_errors());
}

// --- option enum ---

TEST_F(PCREOptionsTest_178, SetOption_ToNone_ReflectsViaGetter_178) {
    // We only use enum values exposed by the interface; no assumptions about others.
    opts_.set_option(PCRE::None);
    EXPECT_EQ(PCRE::None, opts_.option());
}
