// File: re2_options_never_capture_test_28.cc

#include <gtest/gtest.h>
#include "re2/re2.h"

using re2::RE2;

class OptionsNeverCaptureTest_28 : public ::testing::Test {
protected:
  RE2::Options opts_;  // Fresh default-constructed options for each test
};

// [Normal] Default constructor should have never_capture() == false.
TEST_F(OptionsNeverCaptureTest_28, DefaultIsFalse_28) {
  EXPECT_FALSE(opts_.never_capture());
}

// [Normal] Setter toggles the observable getter result.
TEST_F(OptionsNeverCaptureTest_28, SetTrueThenFalse_28) {
  opts_.set_never_capture(true);
  EXPECT_TRUE(opts_.never_capture());

  opts_.set_never_capture(false);
  EXPECT_FALSE(opts_.never_capture());
}

// [Boundary/Independence] Changing unrelated flags should not change never_capture()
// (observable independence through the public API).
TEST_F(OptionsNeverCaptureTest_28, UnrelatedFlagsDoNotAffectNeverCapture_28) {
  // Take baseline.
  bool baseline = opts_.never_capture();

  // Flip a variety of other public flags.
  opts_.set_longest_match(true);
  opts_.set_log_errors(false);
  opts_.set_literal(true);
  opts_.set_never_nl(true);
  opts_.set_dot_nl(true);
  opts_.set_case_sensitive(false);
  opts_.set_perl_classes(true);
  opts_.set_word_boundary(true);
  opts_.set_one_line(true);

  // Observable expectation: never_capture() remains as it was unless we set it.
  EXPECT_EQ(baseline, opts_.never_capture());

  // Now explicitly set never_capture and verify it changes as commanded.
  opts_.set_never_capture(!baseline);
  EXPECT_EQ(!baseline, opts_.never_capture());
}

// [Normal] Copy(...) should copy the observable never_capture() state.
TEST_F(OptionsNeverCaptureTest_28, CopyPreservesNeverCapture_28) {
  RE2::Options src;
  src.set_never_capture(true);

  RE2::Options dst;
  EXPECT_NE(src.never_capture(), dst.never_capture()); // Sanity: different before copy (true vs default false)

  dst.Copy(src);
  EXPECT_EQ(src.never_capture(), dst.never_capture());
}

// [Boundary/Constructor variants] CannedOptions constructors should not
// enable never_capture() unless the public API says so; from the provided
// interface, never_capture defaults to false for canned presets.
TEST_F(OptionsNeverCaptureTest_28, CannedOptionsDefaultIsFalse_28) {
  // NOTE: The following enum values are used purely via the public interface.
  // If any are not available in your build, remove that case.
  {
    RE2::Options o(RE2::Latin1);
    EXPECT_FALSE(o.never_capture());
  }
  {
    RE2::Options o(RE2::POSIX);
    EXPECT_FALSE(o.never_capture());
  }
  {
    RE2::Options o(RE2::Quiet);
    EXPECT_FALSE(o.never_capture());
  }
}

// [Robustness] never_capture() remains consistent across multiple sets.
TEST_F(OptionsNeverCaptureTest_28, MultipleSetsAreConsistent_28) {
  for (int i = 0; i < 3; ++i) {
    opts_.set_never_capture(true);
    EXPECT_TRUE(opts_.never_capture());
    opts_.set_never_capture(false);
    EXPECT_FALSE(opts_.never_capture());
  }
}
