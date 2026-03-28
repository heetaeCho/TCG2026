// File: pcre_options_stack_limit_test_180.cc

#include "gtest/gtest.h"
#include "re2/util/pcre.h"
#include <climits>

using re2::PCRE_Options;

class PCRE_OptionsTest_180 : public ::testing::Test {
protected:
    PCRE_Options opts_;
};

// Normal operation: default-initialized observable state via public getter.
TEST_F(PCRE_OptionsTest_180, DefaultStackLimitIsZero_180) {
    // Expect the documented/observable default to be 0 (checked via getter).
    EXPECT_EQ(0, opts_.stack_limit());
}

// Normal operation: setting a typical positive value is reflected by the getter.
TEST_F(PCRE_OptionsTest_180, SetStackLimit_UpdatesValue_180) {
    opts_.set_stack_limit(1024);
    EXPECT_EQ(1024, opts_.stack_limit());
}

// Boundary condition: setting to zero is allowed and observable as zero.
TEST_F(PCRE_OptionsTest_180, SetStackLimit_AllowsZero_180) {
    opts_.set_stack_limit(0);
    EXPECT_EQ(0, opts_.stack_limit());
}

// Normal operation: last-writer-wins behavior via public API (no internal peeking).
TEST_F(PCRE_OptionsTest_180, SetStackLimit_OverwritesPrevious_180) {
    opts_.set_stack_limit(10);
    opts_.set_stack_limit(20);
    EXPECT_EQ(20, opts_.stack_limit());
}

// Boundary condition: large positive value remains as set (no assumptions about clamping).
TEST_F(PCRE_OptionsTest_180, SetStackLimit_LargeValue_Preserved_180) {
    opts_.set_stack_limit(INT_MAX);
    EXPECT_EQ(INT_MAX, opts_.stack_limit());
}

// Exceptional/edge input (as observable): negative value remains as set, if accepted by API.
TEST_F(PCRE_OptionsTest_180, SetStackLimit_NegativeValue_Preserved_180) {
    opts_.set_stack_limit(-1);
    EXPECT_EQ(-1, opts_.stack_limit());
}
