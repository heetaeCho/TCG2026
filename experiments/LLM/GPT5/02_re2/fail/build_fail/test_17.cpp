// File: options_test_17.cc
#include <gtest/gtest.h>
#include <cstdint>
#include "re2/re2.h"

using re2::RE2;

class OptionsTest_17 : public ::testing::Test {
protected:
  RE2::Options opts_;  // fresh instance per test
};

// --- Normal operation: simple flag round-trips ---
TEST_F(OptionsTest_17, PosixSyntaxSetterGetterRoundTrip_17) {
  // Default-to-true
  opts_.set_posix_syntax(true);
  EXPECT_TRUE(opts_.posix_syntax());

  // Then back to false
  opts_.set_posix_syntax(false);
  EXPECT_FALSE(opts_.posix_syntax());
}

TEST_F(OptionsTest_17, CaseSensitiveSetterGetterRoundTrip_17) {
  opts_.set_case_sensitive(false);
  EXPECT_FALSE(opts_.case_sensitive());
  opts_.set_case_sensitive(true);
  EXPECT_TRUE(opts_.case_sensitive());
}

TEST_F(OptionsTest_17, MaxMemSetterGetterRoundTrip_17) {
  const int64_t kMem = 4LL * 1024 * 1024; // 4 MiB
  opts_.set_max_mem(kMem);
  EXPECT_EQ(kMem, opts_.max_mem());
}

TEST_F(OptionsTest_17, EncodingSetterGetterRoundTrip_17) {
  // Start by setting Latin1 then UTF8 and validate round-trip.
  opts_.set_encoding(RE2::EncodingLatin1);
  EXPECT_EQ(RE2::EncodingLatin1, opts_.encoding());
  opts_.set_encoding(RE2::EncodingUTF8);
  EXPECT_EQ(RE2::EncodingUTF8, opts_.encoding());
}

// --- Boundary-ish toggles over multiple independent flags ---
TEST_F(OptionsTest_17, MultipleFlagsAffectParseFlags_17) {
  const int base = opts_.ParseFlags();

  // Flip a collection of flags that are expected to contribute to parse flags.
  // We do not assert exact values, only that the combined effect changes.
  opts_.set_posix_syntax(true);
  opts_.set_longest_match(true);
  opts_.set_literal(true);
  opts_.set_never_nl(true);
  opts_.set_dot_nl(true);
  opts_.set_never_capture(true);
  opts_.set_case_sensitive(false);
  opts_.set_perl_classes(true);
  opts_.set_word_boundary(true);
  opts_.set_one_line(true);

  const int changed = opts_.ParseFlags();
  EXPECT_NE(base, changed);
}

// --- Copy semantics: all observable fields should match after Copy() ---
TEST_F(OptionsTest_17, CopyClonesAllObservableOptions_17) {
  // Configure non-default settings on src
  RE2::Options src;
  src.set_max_mem(8LL * 1024 * 1024);
  src.set_encoding(RE2::EncodingLatin1);
  src.set_posix_syntax(true);
  src.set_longest_match(true);
  src.set_log_errors(false);
  src.set_literal(true);
  src.set_never_nl(true);
  src.set_dot_nl(true);
  src.set_never_capture(true);
  src.set_case_sensitive(false);
  src.set_perl_classes(true);
  src.set_word_boundary(true);
  src.set_one_line(true);

  // Copy into dst and compare via public getters
  RE2::Options dst;
  dst.Copy(src);

  EXPECT_EQ(src.max_mem(),        dst.max_mem());
  EXPECT_EQ(src.encoding(),       dst.encoding());
  EXPECT_EQ(src.posix_syntax(),   dst.posix_syntax());
  EXPECT_EQ(src.longest_match(),  dst.longest_match());
  EXPECT_EQ(src.log_errors(),     dst.log_errors());
  EXPECT_EQ(src.literal(),        dst.literal());
  EXPECT_EQ(src.never_nl(),       dst.never_nl());
  EXPECT_EQ(src.dot_nl(),         dst.dot_nl());
  EXPECT_EQ(src.never_capture(),  dst.never_capture());
  EXPECT_EQ(src.case_sensitive(), dst.case_sensitive());
  EXPECT_EQ(src.perl_classes(),   dst.perl_classes());
  EXPECT_EQ(src.word_boundary(),  dst.word_boundary());
  EXPECT_EQ(src.one_line(),       dst.one_line());

  // ParseFlags is an observable aggregate — should match after Copy.
  EXPECT_EQ(src.ParseFlags(), dst.ParseFlags());
}

// --- Exceptional / constructor variants (observable via getters) ---
TEST_F(OptionsTest_17, CannedOptionsLatin1SetsEncoding_17) {
  // Construct with a canned "Latin1" option and confirm observable encoding.
  RE2::Options latin1(RE2::Latin1);
  EXPECT_EQ(RE2::EncodingLatin1, latin1.encoding());
}

TEST_F(OptionsTest_17, CannedOptionsPOSIXEnablesPOSIXAndLongestMatch_17) {
  // POSIX canned option is expected (per public ctor behavior) to enable these flags.
  RE2::Options posix(RE2::POSIX);
  EXPECT_TRUE(posix.posix_syntax());
  EXPECT_TRUE(posix.longest_match());
}

TEST_F(OptionsTest_17, CannedOptionsQuietDisablesLogErrors_17) {
  RE2::Options quiet(RE2::Quiet);
  EXPECT_FALSE(quiet.log_errors());
}

// --- Stability: ParseFlags Stable Under No-Op Reassignments ---
TEST_F(OptionsTest_17, ParseFlagsStableWhenFlagsUnchanged_17) {
  const int a = opts_.ParseFlags();

  // Re-setting each flag to its current value should not change ParseFlags.
  opts_.set_posix_syntax(opts_.posix_syntax());
  opts_.set_longest_match(opts_.longest_match());
  opts_.set_log_errors(opts_.log_errors());
  opts_.set_literal(opts_.literal());
  opts_.set_never_nl(opts_.never_nl());
  opts_.set_dot_nl(opts_.dot_nl());
  opts_.set_never_capture(opts_.never_capture());
  opts_.set_case_sensitive(opts_.case_sensitive());
  opts_.set_perl_classes(opts_.perl_classes());
  opts_.set_word_boundary(opts_.word_boundary());
  opts_.set_one_line(opts_.one_line());

  const int b = opts_.ParseFlags();
  EXPECT_EQ(a, b);
}
