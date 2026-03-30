// File: re2_options_log_errors_test_20.cc

#include "gtest/gtest.h"
#include "re2/re2.h"

using re2::RE2;

class RE2OptionsLogErrorsTest_20 : public ::testing::Test {};

// [Normal] Default-constructed Options should have logging enabled.
TEST_F(RE2OptionsLogErrorsTest_20, DefaultLogErrorsEnabled_20) {
  RE2::Options opt;
  EXPECT_TRUE(opt.log_errors());
}

// [Normal] set_log_errors should toggle the observable getter result.
TEST_F(RE2OptionsLogErrorsTest_20, SetLogErrors_TogglesValue_20) {
  RE2::Options opt;

  opt.set_log_errors(false);
  EXPECT_FALSE(opt.log_errors());

  opt.set_log_errors(true);
  EXPECT_TRUE(opt.log_errors());
}

// [Boundary/Config Variant] Quiet canned option should disable logging.
TEST_F(RE2OptionsLogErrorsTest_20, CannedOptionQuiet_DisablesLogErrors_20) {
  RE2::Options quiet_opt(RE2::Quiet);
  EXPECT_FALSE(quiet_opt.log_errors());
}

// [Boundary/Config Variant] POSIX canned option should not disable logging.
TEST_F(RE2OptionsLogErrorsTest_20, CannedOptionPOSIX_EnablesLogErrors_20) {
  RE2::Options posix_opt(RE2::POSIX);
  EXPECT_TRUE(posix_opt.log_errors());
}

// [Boundary/Config Variant] Latin1 canned option should not disable logging.
TEST_F(RE2OptionsLogErrorsTest_20, CannedOptionLatin1_EnablesLogErrors_20) {
  RE2::Options latin1_opt(RE2::Latin1);
  EXPECT_TRUE(latin1_opt.log_errors());
}

// [External Interaction via Public API] Copy should preserve log_errors state.
TEST_F(RE2OptionsLogErrorsTest_20, Copy_PreservesLogErrors_20) {
  RE2::Options src;
  src.set_log_errors(false);

  RE2::Options dst;
  dst.set_log_errors(true);  // ensure it changes
  dst.Copy(src);

  EXPECT_FALSE(dst.log_errors());
  // Also confirm source remains unchanged (black-box observable).
  EXPECT_FALSE(src.log_errors());
}
