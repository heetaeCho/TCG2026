// File: re2_options_one_line_test.cc

#include <gtest/gtest.h>
#include "re2/re2.h"

// Keep tests within the re2 namespace usage context only via public API.
using re2::RE2;

class RE2OptionsOneLineTest_36 : public ::testing::Test {
protected:
  RE2::Options opts_;  // fresh instance per test via fixture
};

// [Normal] Default-constructed Options should have one_line() == false.
TEST_F(RE2OptionsOneLineTest_36, DefaultIsFalse_36) {
  EXPECT_FALSE(opts_.one_line());
}

// [Normal] set_one_line(true) should flip the observable getter to true.
TEST_F(RE2OptionsOneLineTest_36, SetTrueMakesGetterTrue_36) {
  opts_.set_one_line(true);
  EXPECT_TRUE(opts_.one_line());
}

// [Boundary] Toggling the flag multiple times should reflect the last set value.
TEST_F(RE2OptionsOneLineTest_36, ToggleTrueThenFalse_36) {
  opts_.set_one_line(true);
  EXPECT_TRUE(opts_.one_line());

  opts_.set_one_line(false);
  EXPECT_FALSE(opts_.one_line());

  // One more toggle to ensure stability
  opts_.set_one_line(true);
  EXPECT_TRUE(opts_.one_line());
}

// [Interaction] Changing unrelated flags should not implicitly change one_line().
TEST_F(RE2OptionsOneLineTest_36, IndependentFromOtherFlags_36) {
  // Start from default
  ASSERT_FALSE(opts_.one_line());

  // Flip a few other flags through their public setters
  opts_.set_dot_nl(true);
  opts_.set_never_nl(true);
  opts_.set_case_sensitive(false);
  opts_.set_word_boundary(true);
  opts_.set_log_errors(false);
  opts_.set_never_capture(true);
  opts_.set_posix_syntax(true);
  opts_.set_longest_match(true);
  opts_.set_literal(true);
  opts_.set_perl_classes(true);

  // one_line() should remain whatever it was unless explicitly set
  EXPECT_FALSE(opts_.one_line()) << "one_line() must be unaffected by other toggles";

  // Now explicitly set and ensure it stays true even if we toggle others again
  opts_.set_one_line(true);
  EXPECT_TRUE(opts_.one_line());

  opts_.set_dot_nl(false);
  opts_.set_never_nl(false);
  opts_.set_case_sensitive(true);
  opts_.set_word_boundary(false);
  opts_.set_log_errors(true);
  opts_.set_never_capture(false);
  opts_.set_posix_syntax(false);
  opts_.set_longest_match(false);
  opts_.set_literal(false);
  opts_.set_perl_classes(false);

  EXPECT_TRUE(opts_.one_line()) << "one_line() must only change via set_one_line()";
}

// [Copy] Copy() should copy the one_line setting from src to dst.
TEST_F(RE2OptionsOneLineTest_36, CopyPropagatesOneLine_36) {
  RE2::Options src;
  RE2::Options dst;

  // Establish distinct initial states
  src.set_one_line(true);
  dst.set_one_line(false);
  ASSERT_TRUE(src.one_line());
  ASSERT_FALSE(dst.one_line());

  // Copy into dst and verify the observable effect
  dst.Copy(src);
  EXPECT_TRUE(dst.one_line());

  // Also verify copying back the other way flips to false if src is false
  src.set_one_line(false);
  dst.set_one_line(true);
  ASSERT_FALSE(src.one_line());
  ASSERT_TRUE(dst.one_line());

  dst.Copy(src);
  EXPECT_FALSE(dst.one_line());
}

// [Constructor Variants] Canned options should not implicitly force one_line=true.
// This verifies observable behavior only; we don't assert anything about other flags.
TEST_F(RE2OptionsOneLineTest_36, CannedOptionsDoNotForceOneLine_36) {
  // If the CannedOptions enum is available, construct via those and check one_line().
  // We avoid making assumptions beyond the getter value.
  RE2::Options def; // default
  EXPECT_FALSE(def.one_line());

  // Construct via each known canned option if they compile in this codebase.
  // These are separate scopes to avoid shadowing if any are conditionally compiled.
  {
    RE2::Options latin1(RE2::Latin1);
    EXPECT_FALSE(latin1.one_line());
  }
  {
    RE2::Options posix(RE2::POSIX);
    EXPECT_FALSE(posix.one_line());
  }
  {
    RE2::Options quiet(RE2::Quiet);
    EXPECT_FALSE(quiet.one_line());
  }
}

// Note: We intentionally do NOT test ParseFlags() because its return contract
// for one_line() is not specified here. We keep strictly to observable behavior
// via the provided one_line() getter/setter and Copy(), per constraints.

