// File: pcre_options_report_errors_test_181.cc
#include <gtest/gtest.h>
#include "re2/util/pcre.h"

using re2::PCRE_Options;

// Fixture kept minimal for clarity; no internal state assumptions.
class PCREOptionsTest_181 : public ::testing::Test {};

// Normal operation: default-constructed value is observable via the getter.
TEST(PCREOptionsTest_181, DefaultReportErrorsIsTrue_181) {
    PCRE_Options opts;
    EXPECT_TRUE(opts.report_errors()) << "Default report_errors() should be true";
}

// Normal operation: setting false is reflected by the getter.
TEST(PCREOptionsTest_181, SetReportErrorsFalse_181) {
    PCRE_Options opts;
    // Exercise the public setter only; do not infer internal state.
    opts.set_report_errors(false);
    EXPECT_FALSE(opts.report_errors()) << "report_errors() should reflect set_report_errors(false)";
}

// Normal operation + const-correctness: read through const reference.
TEST(PCREOptionsTest_181, GetterWorksThroughConstReference_181) {
    PCRE_Options opts;
    opts.set_report_errors(false);

    const PCRE_Options& cref = opts;  // verify const-qualified accessor
    EXPECT_FALSE(cref.report_errors()) << "const report_errors() should match the non-const observable state";
}

// Boundary (bool domain): toggling back to true works as expected.
TEST(PCREOptionsTest_181, ToggleReportErrorsTrueThenFalse_181) {
    PCRE_Options opts;

    opts.set_report_errors(false);
    EXPECT_FALSE(opts.report_errors());

    opts.set_report_errors(true);
    EXPECT_TRUE(opts.report_errors());
}

// Idempotence: setting to the same value repeatedly yields the same observable result.
TEST(PCREOptionsTest_181, IdempotentSetReportErrors_181) {
    PCRE_Options opts;

    opts.set_report_errors(false);
    EXPECT_FALSE(opts.report_errors());
    opts.set_report_errors(false);
    EXPECT_FALSE(opts.report_errors()) << "Setting the same value twice should not change the observable result";

    opts.set_report_errors(true);
    EXPECT_TRUE(opts.report_errors());
    opts.set_report_errors(true);
    EXPECT_TRUE(opts.report_errors()) << "Setting the same value twice should not change the observable result";
}
