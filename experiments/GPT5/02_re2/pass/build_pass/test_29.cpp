// File: re2_options_never_capture_test_29.cc
#include <gtest/gtest.h>
#include "re2/re2.h"

using re2::RE2;

class RE2OptionsNeverCaptureTest_29 : public ::testing::Test {};

// Verifies the default value exposed by the public getter.
TEST_F(RE2OptionsNeverCaptureTest_29, DefaultIsFalse_29) {
  RE2::Options opt;
  // Observable behavior: default never_capture() is false (per public API).
  EXPECT_FALSE(opt.never_capture());
}

// Verifies that setting true is reflected by the getter.
TEST_F(RE2OptionsNeverCaptureTest_29, SetTrueReflectsInGetter_29) {
  RE2::Options opt;
  opt.set_never_capture(true);
  EXPECT_TRUE(opt.never_capture());
}

// Verifies toggling true -> false is reflected by the getter.
TEST_F(RE2OptionsNeverCaptureTest_29, ToggleTrueThenFalse_29) {
  RE2::Options opt;
  opt.set_never_capture(true);
  ASSERT_TRUE(opt.never_capture());  // confirm precondition via public API

  opt.set_never_capture(false);
  EXPECT_FALSE(opt.never_capture());
}

// Verifies idempotency when setting the same value repeatedly.
TEST_F(RE2OptionsNeverCaptureTest_29, IdempotentWhenSettingSameValue_29) {
  RE2::Options opt;
  // Start from default false; set false again should remain false.
  opt.set_never_capture(false);
  EXPECT_FALSE(opt.never_capture());

  // Set true repeatedly; should remain true.
  opt.set_never_capture(true);
  EXPECT_TRUE(opt.never_capture());
  opt.set_never_capture(true);
  EXPECT_TRUE(opt.never_capture());
}

// Verifies that Copy(...) copies the never_capture flag (observable via public APIs).
TEST_F(RE2OptionsNeverCaptureTest_29, CopyPropagatesNeverCapture_29) {
  RE2::Options src;
  src.set_never_capture(true);
  ASSERT_TRUE(src.never_capture());  // confirm source state via public API

  RE2::Options dst;
  EXPECT_FALSE(dst.never_capture()); // default before copy

  dst.Copy(src);
  EXPECT_TRUE(dst.never_capture());  // copied state visible via public API
}
