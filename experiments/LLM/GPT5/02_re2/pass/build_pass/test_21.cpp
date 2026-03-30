// File: re2_options_set_log_errors_test_21.cc
#include <gtest/gtest.h>
#include "re2/re2.h"

namespace {

using re2::RE2;

// A simple fixture for RE2::Options tests (no special setup needed)
class RE2OptionsTest_21 : public ::testing::Test {};

TEST_F(RE2OptionsTest_21, DefaultLogErrorsIsTrue_21) {
  RE2::Options opts;
  // Observable behavior: default-constructed options should report current log_errors state
  EXPECT_TRUE(opts.log_errors());
}

TEST_F(RE2OptionsTest_21, SetLogErrorsFalseThenTrue_21) {
  RE2::Options opts;

  // Toggle off
  opts.set_log_errors(false);
  EXPECT_FALSE(opts.log_errors());

  // Toggle back on
  opts.set_log_errors(true);
  EXPECT_TRUE(opts.log_errors());
}

TEST_F(RE2OptionsTest_21, SetLogErrorsIsIdempotentWhenNoChange_21) {
  RE2::Options opts;

  // Starting from default (true), setting true again should keep it true
  opts.set_log_errors(true);
  EXPECT_TRUE(opts.log_errors());

  // Now set to false, then set false again — should remain false
  opts.set_log_errors(false);
  EXPECT_FALSE(opts.log_errors());
  opts.set_log_errors(false);
  EXPECT_FALSE(opts.log_errors());
}

TEST_F(RE2OptionsTest_21, CopyPreservesLogErrorsValue_21) {
  RE2::Options src;
  src.set_log_errors(false);

  RE2::Options dst;  // default constructed
  dst.Copy(src);

  // After Copy, dst should reflect src's observable state
  EXPECT_FALSE(dst.log_errors());
  EXPECT_EQ(dst.log_errors(), src.log_errors());
}

TEST_F(RE2OptionsTest_21, CannedQuietDisablesLogErrors_21) {
  // Construct with a canned option that is expected (by interface contract) to quiet logging
  RE2::Options quiet_opts(RE2::Quiet);
  EXPECT_FALSE(quiet_opts.log_errors());
}

TEST_F(RE2OptionsTest_21, OtherCannedOptionsDoNotDisableLogErrors_21) {
  // Sanity check with non-Quiet presets: they should not disable logging by default
  RE2::Options latin1_opts(RE2::Latin1);
  RE2::Options posix_opts(RE2::POSIX);

  EXPECT_TRUE(latin1_opts.log_errors());
  EXPECT_TRUE(posix_opts.log_errors());
}

}  // namespace
