// File: re2_options_case_sensitive_test_31.cc
#include <gtest/gtest.h>
#include "./TestProjects/re2/re2/re2.h"

using re2::RE2;

class RE2OptionsTest_31 : public ::testing::Test {};

// [Normal] Default should be case-sensitive.
TEST_F(RE2OptionsTest_31, DefaultIsCaseSensitive_31) {
  RE2::Options opts;
  EXPECT_TRUE(opts.case_sensitive());
}

// [Normal] Setting false then true should reflect through the getter.
TEST_F(RE2OptionsTest_31, SetCaseSensitive_ToggleFalseThenTrue_31) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  EXPECT_FALSE(opts.case_sensitive());

  opts.set_case_sensitive(true);
  EXPECT_TRUE(opts.case_sensitive());
}

// [Boundary/Idempotence] Re-setting to the same value should keep it unchanged.
TEST_F(RE2OptionsTest_31, SetCaseSensitive_Idempotent_31) {
  RE2::Options opts;

  // Ensure initial state is true (observable via getter).
  EXPECT_TRUE(opts.case_sensitive());

  // Set to true repeatedly — should remain true.
  opts.set_case_sensitive(true);
  EXPECT_TRUE(opts.case_sensitive());
  opts.set_case_sensitive(true);
  EXPECT_TRUE(opts.case_sensitive());

  // Flip to false and set false repeatedly — should remain false.
  opts.set_case_sensitive(false);
  EXPECT_FALSE(opts.case_sensitive());
  opts.set_case_sensitive(false);
  EXPECT_FALSE(opts.case_sensitive());
}

// [Isolation] Changing case sensitivity should not change other option getters.
// We do NOT assert specific default values of other flags; instead, we capture
// their observed values and verify they are unchanged after toggling.
TEST_F(RE2OptionsTest_31, SetCaseSensitive_DoesNotAffectOtherFlags_31) {
  RE2::Options opts;

  // Capture initial observable values.
  const bool posix_syntax_initial   = opts.posix_syntax();
  const bool longest_match_initial  = opts.longest_match();
  const bool log_errors_initial     = opts.log_errors();
  const bool literal_initial        = opts.literal();
  const bool never_nl_initial       = opts.never_nl();
  const bool dot_nl_initial         = opts.dot_nl();
  const bool never_capture_initial  = opts.never_capture();
  const bool perl_classes_initial   = opts.perl_classes();
  const bool word_boundary_initial  = opts.word_boundary();
  const bool one_line_initial       = opts.one_line();

  // Toggle case sensitivity a couple of times.
  opts.set_case_sensitive(false);
  opts.set_case_sensitive(true);

  // Other flags should remain exactly as observed initially.
  EXPECT_EQ(posix_syntax_initial,  opts.posix_syntax());
  EXPECT_EQ(longest_match_initial, opts.longest_match());
  EXPECT_EQ(log_errors_initial,    opts.log_errors());
  EXPECT_EQ(literal_initial,       opts.literal());
  EXPECT_EQ(never_nl_initial,      opts.never_nl());
  EXPECT_EQ(dot_nl_initial,        opts.dot_nl());
  EXPECT_EQ(never_capture_initial, opts.never_capture());
  EXPECT_EQ(perl_classes_initial,  opts.perl_classes());
  EXPECT_EQ(word_boundary_initial, opts.word_boundary());
  EXPECT_EQ(one_line_initial,      opts.one_line());
}

// [External interaction via public API] Copy should preserve the setting.
TEST_F(RE2OptionsTest_31, Copy_PreservesCaseSensitive_31) {
  RE2::Options src;
  src.set_case_sensitive(false);
  ASSERT_FALSE(src.case_sensitive());

  RE2::Options dst;
  // Start different to ensure change is observable.
  dst.set_case_sensitive(true);
  ASSERT_TRUE(dst.case_sensitive());

  // Copy from src and verify observable equality.
  dst.Copy(src);
  EXPECT_EQ(src.case_sensitive(), dst.case_sensitive());
}

// [Constructor variant] CannedOptions constructor should result in a usable object,
// and set_case_sensitive should still control the observable getter.
TEST_F(RE2OptionsTest_31, CtorWithCannedOptions_CaseSensitiveBehavior_31) {
  // We don't assert which canned option affects case-sensitivity by default.
  // We only check that set_case_sensitive controls the observable behavior.
  RE2::Options opts_latin(re2::RE2::Latin1);
  opts_latin.set_case_sensitive(false);
  EXPECT_FALSE(opts_latin.case_sensitive());
  opts_latin.set_case_sensitive(true);
  EXPECT_TRUE(opts_latin.case_sensitive());

  RE2::Options opts_posix(re2::RE2::POSIX);
  opts_posix.set_case_sensitive(false);
  EXPECT_FALSE(opts_posix.case_sensitive());
  opts_posix.set_case_sensitive(true);
  EXPECT_TRUE(opts_posix.case_sensitive());
}
