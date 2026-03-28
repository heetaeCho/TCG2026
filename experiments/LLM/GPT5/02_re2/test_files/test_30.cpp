// File: re2_options_test_30.cc
#include <gtest/gtest.h>
#include "re2/re2.h"

using re2::RE2;

class RE2OptionsTest_30 : public ::testing::Test {};

// --- Default construction behavior ---

TEST_F(RE2OptionsTest_30, Defaults_AreAsDocumented_30) {
  RE2::Options opt;

  // Scalar defaults
  EXPECT_EQ(kDefaultMaxMem, opt.max_mem());
  EXPECT_EQ(EncodingUTF8, opt.encoding());

  // Boolean defaults (as exposed by getters)
  EXPECT_FALSE(opt.posix_syntax());
  EXPECT_FALSE(opt.longest_match());
  EXPECT_TRUE(opt.log_errors());
  EXPECT_FALSE(opt.literal());
  EXPECT_FALSE(opt.never_nl());
  EXPECT_FALSE(opt.dot_nl());
  EXPECT_FALSE(opt.never_capture());
  EXPECT_TRUE(opt.case_sensitive());
  EXPECT_FALSE(opt.perl_classes());
  EXPECT_FALSE(opt.word_boundary());
  EXPECT_FALSE(opt.one_line());
}

// --- Setter/getter round trips ---

TEST_F(RE2OptionsTest_30, MaxMem_SetGet_RoundTrip_30) {
  RE2::Options opt;
  // Boundary-ish values that should round-trip via the public API
  opt.set_max_mem(0);
  EXPECT_EQ(0, opt.max_mem());

  const int64_t big = (1LL << 62);
  opt.set_max_mem(big);
  EXPECT_EQ(big, opt.max_mem());
}

TEST_F(RE2OptionsTest_30, Encoding_SetGet_RoundTrip_30) {
  RE2::Options opt;
  opt.set_encoding(EncodingLatin1);
  EXPECT_EQ(EncodingLatin1, opt.encoding());

  opt.set_encoding(EncodingUTF8);
  EXPECT_EQ(EncodingUTF8, opt.encoding());
}

TEST_F(RE2OptionsTest_30, BoolFlags_SetGet_RoundTrip_30) {
  RE2::Options opt;

  opt.set_posix_syntax(true);
  EXPECT_TRUE(opt.posix_syntax());
  opt.set_posix_syntax(false);
  EXPECT_FALSE(opt.posix_syntax());

  opt.set_longest_match(true);
  EXPECT_TRUE(opt.longest_match());
  opt.set_longest_match(false);
  EXPECT_FALSE(opt.longest_match());

  opt.set_log_errors(false);
  EXPECT_FALSE(opt.log_errors());
  opt.set_log_errors(true);
  EXPECT_TRUE(opt.log_errors());

  opt.set_literal(true);
  EXPECT_TRUE(opt.literal());
  opt.set_literal(false);
  EXPECT_FALSE(opt.literal());

  opt.set_never_nl(true);
  EXPECT_TRUE(opt.never_nl());
  opt.set_never_nl(false);
  EXPECT_FALSE(opt.never_nl());

  opt.set_dot_nl(true);
  EXPECT_TRUE(opt.dot_nl());
  opt.set_dot_nl(false);
  EXPECT_FALSE(opt.dot_nl());

  opt.set_never_capture(true);
  EXPECT_TRUE(opt.never_capture());
  opt.set_never_capture(false);
  EXPECT_FALSE(opt.never_capture());

  opt.set_case_sensitive(false);
  EXPECT_FALSE(opt.case_sensitive());
  opt.set_case_sensitive(true);
  EXPECT_TRUE(opt.case_sensitive());

  opt.set_perl_classes(true);
  EXPECT_TRUE(opt.perl_classes());
  opt.set_perl_classes(false);
  EXPECT_FALSE(opt.perl_classes());

  opt.set_word_boundary(true);
  EXPECT_TRUE(opt.word_boundary());
  opt.set_word_boundary(false);
  EXPECT_FALSE(opt.word_boundary());

  opt.set_one_line(true);
  EXPECT_TRUE(opt.one_line());
  opt.set_one_line(false);
  EXPECT_FALSE(opt.one_line());
}

// --- Focused test on case sensitivity (explicit per prompt header) ---

TEST_F(RE2OptionsTest_30, CaseSensitive_Toggle_30) {
  RE2::Options opt;
  // Default is case sensitive
  EXPECT_TRUE(opt.case_sensitive());

  opt.set_case_sensitive(false);
  EXPECT_FALSE(opt.case_sensitive());

  opt.set_case_sensitive(true);
  EXPECT_TRUE(opt.case_sensitive());
}

// --- Copy() should copy all observable fields ---

TEST_F(RE2OptionsTest_30, Copy_ClonesAllObservableState_30) {
  RE2::Options src;

  // Configure a non-default mix
  src.set_max_mem(1234567);
  src.set_encoding(EncodingLatin1);
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

  RE2::Options dst;
  dst.Copy(src);

  // Verify all values via getters
  EXPECT_EQ(src.max_mem(), dst.max_mem());
  EXPECT_EQ(src.encoding(), dst.encoding());
  EXPECT_EQ(src.posix_syntax(), dst.posix_syntax());
  EXPECT_EQ(src.longest_match(), dst.longest_match());
  EXPECT_EQ(src.log_errors(), dst.log_errors());
  EXPECT_EQ(src.literal(), dst.literal());
  EXPECT_EQ(src.never_nl(), dst.never_nl());
  EXPECT_EQ(src.dot_nl(), dst.dot_nl());
  EXPECT_EQ(src.never_capture(), dst.never_capture());
  EXPECT_EQ(src.case_sensitive(), dst.case_sensitive());
  EXPECT_EQ(src.perl_classes(), dst.perl_classes());
  EXPECT_EQ(src.word_boundary(), dst.word_boundary());
  EXPECT_EQ(src.one_line(), dst.one_line());
}

// --- Canned options constructor behavior (observable via getters) ---

TEST_F(RE2OptionsTest_30, Canned_POSIX_SetsExpectedFlags_30) {
  RE2::Options opt(RE2::POSIX);

  // Encoding: POSIX should keep UTF-8 per constructor rule (Latin1 only for Latin1 option)
  EXPECT_EQ(EncodingUTF8, opt.encoding());

  // POSIX should enable POSIX syntax and longest match
  EXPECT_TRUE(opt.posix_syntax());
  EXPECT_TRUE(opt.longest_match());

  // Quiet only affects log_errors; POSIX should keep it true
  EXPECT_TRUE(opt.log_errors());

  // Other flags remain at their documented defaults
  EXPECT_FALSE(opt.literal());
  EXPECT_FALSE(opt.never_nl());
  EXPECT_FALSE(opt.dot_nl());
  EXPECT_FALSE(opt.never_capture());
  EXPECT_TRUE(opt.case_sensitive());
  EXPECT_FALSE(opt.perl_classes());
  EXPECT_FALSE(opt.word_boundary());
  EXPECT_FALSE(opt.one_line());
}

TEST_F(RE2OptionsTest_30, Canned_Latin1_SetsEncoding_Only_30) {
  RE2::Options opt(RE2::Latin1);

  EXPECT_EQ(EncodingLatin1, opt.encoding());

  // All other flags should remain at defaults
  EXPECT_FALSE(opt.posix_syntax());
  EXPECT_FALSE(opt.longest_match());
  EXPECT_TRUE(opt.log_errors());
  EXPECT_FALSE(opt.literal());
  EXPECT_FALSE(opt.never_nl());
  EXPECT_FALSE(opt.dot_nl());
  EXPECT_FALSE(opt.never_capture());
  EXPECT_TRUE(opt.case_sensitive());
  EXPECT_FALSE(opt.perl_classes());
  EXPECT_FALSE(opt.word_boundary());
  EXPECT_FALSE(opt.one_line());
}

TEST_F(RE2OptionsTest_30, Canned_Quiet_DisablesLogging_30) {
  RE2::Options opt(RE2::Quiet);

  EXPECT_FALSE(opt.log_errors());

  // Encoding defaults to UTF-8 unless Latin1 was requested
  EXPECT_EQ(EncodingUTF8, opt.encoding());

  // POSIX-related flags remain default unless POSIX was requested
  EXPECT_FALSE(opt.posix_syntax());
  EXPECT_FALSE(opt.longest_match());

  // Other defaults unchanged
  EXPECT_FALSE(opt.literal());
  EXPECT_FALSE(opt.never_nl());
  EXPECT_FALSE(opt.dot_nl());
  EXPECT_FALSE(opt.never_capture());
  EXPECT_TRUE(opt.case_sensitive());
  EXPECT_FALSE(opt.perl_classes());
  EXPECT_FALSE(opt.word_boundary());
  EXPECT_FALSE(opt.one_line());
}
