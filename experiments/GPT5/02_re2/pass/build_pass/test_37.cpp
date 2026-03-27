// File: re2_options_set_one_line_test_37.cc
#include <gtest/gtest.h>
#include "re2/re2.h"

namespace {

using re2::RE2;

// Fixture kept minimal for clarity/consistency across similar test files.
class OptionsOneLineTest_37 : public ::testing::Test {};

//
// Normal operation
//

// Verifies the default value exposed by the public getter.
TEST_F(OptionsOneLineTest_37, DefaultIsFalse_37) {
  RE2::Options opts;
  EXPECT_FALSE(opts.one_line()) << "Default one_line() should be false";
}

// Verifies that setting true is reflected by the public getter.
TEST_F(OptionsOneLineTest_37, SetTrueReflectsInGetter_37) {
  RE2::Options opts;
  opts.set_one_line(true);
  EXPECT_TRUE(opts.one_line());
}

// Verifies toggling back to false is reflected by the public getter.
TEST_F(OptionsOneLineTest_37, ToggleTrueThenFalse_37) {
  RE2::Options opts;
  opts.set_one_line(true);
  ASSERT_TRUE(opts.one_line());

  opts.set_one_line(false);
  EXPECT_FALSE(opts.one_line());
}

//
// Boundary / Idempotence
//

// Setting the same value repeatedly should keep the observable state unchanged.
TEST_F(OptionsOneLineTest_37, IdempotentWhenSettingSameValue_37) {
  RE2::Options opts;
  // Repeatedly set to false
  opts.set_one_line(false);
  opts.set_one_line(false);
  EXPECT_FALSE(opts.one_line());

  // Repeatedly set to true
  opts.set_one_line(true);
  opts.set_one_line(true);
  EXPECT_TRUE(opts.one_line());
}

//
// Copy semantics (external interaction via another public API)
//

// Copy() should preserve the externally visible one_line() value.
TEST_F(OptionsOneLineTest_37, CopyPreservesOneLine_37) {
  RE2::Options src;
  src.set_one_line(true);
  ASSERT_TRUE(src.one_line());

  RE2::Options dst;           // default false
  ASSERT_FALSE(dst.one_line());

  dst.Copy(src);              // exercise public Copy()
  EXPECT_TRUE(dst.one_line());  // observable state preserved
}

//
// Construction from canned options (should not implicitly flip one_line)
//

// Constructing with different canned presets should leave one_line() at its
// default unless explicitly set via setter. We only assert the observable
// one_line() value.
TEST_F(OptionsOneLineTest_37, CannedOptionsDoNotAffectOneLine_37) {
  RE2::Options latin1(RE2::Latin1);
  EXPECT_FALSE(latin1.one_line());

  RE2::Options posix(RE2::POSIX);
  EXPECT_FALSE(posix.one_line());

  RE2::Options quiet(RE2::Quiet);
  EXPECT_FALSE(quiet.one_line());
}

}  // namespace
