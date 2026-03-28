// File: ./TestProjects/re2/tests/re2_ctor_with_options_598_test.cc

#include <gtest/gtest.h>
#include <string>
#include "re2/re2.h"  // Uses the provided headers

namespace {

using re2::RE2;

// A simple fixture to keep things tidy.
class RE2CtorWithOptionsTest_598 : public ::testing::Test {
protected:
  // Helper to make an Options with some non-default toggles,
  // without asserting anything about their effects.
  static RE2::Options MakeNonDefaultOptions() {
    RE2::Options opt;
    // Flip a few flags to non-defaults; we won't assert their effects,
    // just validate that construction with such options is supported.
    opt.set_case_sensitive(false);
    opt.set_posix_syntax(true);
    opt.set_longest_match(true);
    opt.set_log_errors(false);
    opt.set_never_nl(true);
    opt.set_dot_nl(true);
    opt.set_never_capture(true);
    opt.set_perl_classes(true);
    opt.set_word_boundary(true);
    opt.set_one_line(true);
    return opt;
  }
};

// --- Normal operation ----------------------------------------------------

// Ensures the constructor is callable with a typical pattern and default options.
TEST_F(RE2CtorWithOptionsTest_598, ConstructsWithDefaultOptions_598) {
  RE2::Options opt;  // default-constructed options
  EXPECT_NO_THROW({
    RE2 re("abc", opt);
    (void)re;  // silence unused warning
  });
}

// Ensures the constructor accepts an absl::string_view and customized options
// without making any assumptions about internal behavior.
TEST_F(RE2CtorWithOptionsTest_598, ConstructsWithCustomOptions_598) {
  RE2::Options opt = RE2CtorWithOptionsTest_598::MakeNonDefaultOptions();
  absl::string_view pattern_sv = absl::string_view("a.*b");
  EXPECT_NO_THROW({
    RE2 re(pattern_sv, opt);
    (void)re;
  });
}

// --- Boundary conditions --------------------------------------------------

// Empty pattern should be acceptable as an input to the constructor.
TEST_F(RE2CtorWithOptionsTest_598, ConstructsWithEmptyPattern_598) {
  RE2::Options opt;
  absl::string_view empty("");
  EXPECT_NO_THROW({
    RE2 re(empty, opt);
    (void)re;
  });
}

// Very long pattern (stress the constructor input path) — we only assert it doesn't throw.
TEST_F(RE2CtorWithOptionsTest_598, ConstructsWithLongPattern_598) {
  std::string long_pattern(10000, 'x');  // 10k chars
  RE2::Options opt = RE2CtorWithOptionsTest_598::MakeNonDefaultOptions();
  EXPECT_NO_THROW({
    RE2 re(absl::string_view(long_pattern), opt);
    (void)re;
  });
}

// --- Type traits & interface properties (from public declarations) --------

// Validate copy/move construction and assignment are deleted per interface.
TEST_F(RE2CtorWithOptionsTest_598, CopyAndMoveAreDeleted_598) {
  // Use static_asserts inside a test body to keep everything in one TU.
  static_assert(!std::is_copy_constructible<RE2>::value,
                "RE2 must not be copy-constructible per interface");
  static_assert(!std::is_copy_assignable<RE2>::value,
                "RE2 must not be copy-assignable per interface");
  static_assert(!std::is_move_constructible<RE2>::value,
                "RE2 must not be move-constructible per interface");
  static_assert(!std::is_move_assignable<RE2>::value,
                "RE2 must not be move-assignable per interface");
  SUCCEED();
}

// Ensure the specific overload under test is viable with (absl::string_view, Options).
TEST_F(RE2CtorWithOptionsTest_598, OverloadIsCallableWithStringViewAndOptions_598) {
  RE2::Options opt;
  absl::string_view sv = "hello(world)?";
  EXPECT_NO_THROW({
    RE2 re(sv, opt);
    (void)re;
  });
}

}  // namespace
