// File: pcre_options_report_errors_test_182.cc
#include <gtest/gtest.h>
#include "util/pcre.h"

using re2::PCRE_Options;

namespace {

// A simple fixture in case future tests need shared setup/teardown.
class PCREOptionsTest_182 : public ::testing::Test {};

TEST_F(PCREOptionsTest_182, DefaultReportErrorsIsTrue_182) {
  PCRE_Options opts;
  // Observe the default via the public getter only.
  EXPECT_TRUE(opts.report_errors());
}

TEST_F(PCREOptionsTest_182, SetReportErrorsTrue_182) {
  PCRE_Options opts;
  opts.set_report_errors(true);
  EXPECT_TRUE(opts.report_errors());
}

TEST_F(PCREOptionsTest_182, SetReportErrorsFalse_182) {
  PCRE_Options opts;
  opts.set_report_errors(false);
  EXPECT_FALSE(opts.report_errors());
}

TEST_F(PCREOptionsTest_182, ToggleReportErrorsMultipleTimes_182) {
  PCRE_Options opts;

  opts.set_report_errors(true);
  EXPECT_TRUE(opts.report_errors());

  opts.set_report_errors(false);
  EXPECT_FALSE(opts.report_errors());

  opts.set_report_errors(true);
  EXPECT_TRUE(opts.report_errors());

  opts.set_report_errors(false);
  EXPECT_FALSE(opts.report_errors());
}

TEST_F(PCREOptionsTest_182, ChangingReportErrorsDoesNotAffectOtherFields_182) {
  PCRE_Options opts;

  // Capture current observable values of other options without assuming specifics.
  const auto initial_option      = opts.option();
  const int  initial_match_limit = opts.match_limit();
  const int  initial_stack_limit = opts.stack_limit();

  // Flip report_errors a few times.
  opts.set_report_errors(false);
  opts.set_report_errors(true);

  // Verify the other observable properties remain unchanged.
  EXPECT_EQ(initial_option, opts.option());
  EXPECT_EQ(initial_match_limit, opts.match_limit());
  EXPECT_EQ(initial_stack_limit, opts.stack_limit());
}

}  // namespace
