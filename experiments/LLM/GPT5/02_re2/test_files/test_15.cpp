// File: re2_options_test_15.cc
#include <gtest/gtest.h>
#include "re2/re2.h"

using re2::RE2;

class RE2OptionsTest_15 : public ::testing::Test {
protected:
  RE2::Options opts_;
};

// ---- Defaults ---------------------------------------------------------------

TEST_F(RE2OptionsTest_15, DefaultConstructor_HasExpectedDefaults_15) {
  // Only verify via public accessors.
  // Expect defaults based on the interface description.
  EXPECT_GT(opts_.max_mem(), 0);  // Should be kDefaultMaxMem (> 0), but we don't assert the exact constant.

  // Encoding default: UTF-8 per interface docs.
  EXPECT_EQ(opts_.encoding(), RE2::Options::EncodingUTF8);

  // Booleans (from the known interface defaults)
  EXPECT_FALSE(opts_.posix_syntax());
  EXPECT_FALSE(opts_.longest_match());
  EXPECT_TRUE(opts_.log_errors());
  EXPECT_FALSE(opts_.literal());
  EXPECT_FALSE(opts_.never_nl());
  EXPECT_FALSE(opts_.dot_nl());
  EXPECT_FALSE(opts_.never_capture());
  EXPECT_TRUE(opts_.case_sensitive());
  EXPECT_FALSE(opts_.perl_classes());
  EXPECT_FALSE(opts_.word_boundary());
  EXPECT_FALSE(opts_.one_line());

  // ParseFlags should be stable for unchanged config.
  int f1 = opts_.ParseFlags();
  int f2 = opts_.ParseFlags();
  EXPECT_EQ(f1, f2);
}

// ---- Canned options ctor behavior ------------------------------------------

TEST_F(RE2OptionsTest_15, CannedOptions_POSIX_AffectsRelatedFlags_15) {
  RE2::Options posix(RE2::POSIX);
  EXPECT_TRUE(posix.posix_syntax());
  EXPECT_TRUE(posix.longest_match());
  // Quiet is separate; POSIX shouldn't disable error logging.
  EXPECT_TRUE(posix.log_errors());

  // Encoding not forced to Latin1 by POSIX.
  EXPECT_NE(posix.encoding(), RE2::Options::EncodingLatin1);
}

TEST_F(RE2OptionsTest_15, CannedOptions_Latin1_SetsLatin1Encoding_15) {
  RE2::Options latin1(RE2::Latin1);
  EXPECT_EQ(latin1.encoding(), RE2::Options::EncodingLatin1);

  // Other representative defaults remain typical values.
  EXPECT_TRUE(latin1.case_sensitive());
}

TEST_F(RE2OptionsTest_15, CannedOptions_Quiet_DisablesLogErrors_15) {
  RE2::Options quiet(RE2::Quiet);
  EXPECT_FALSE(quiet.log_errors());
  // Quiet should not imply POSIX or longest match.
  EXPECT_FALSE(quiet.posix_syntax());
  EXPECT_FALSE(quiet.longest_match());
}

// ---- Setters <-> Getters round-trip -----------------------------------------

TEST_F(RE2OptionsTest_15, SettersUpdateGetters_15) {
  // Flip each flag and verify the getter reflects the change.
  opts_.set_posix_syntax(true);
  EXPECT_TRUE(opts_.posix_syntax());

  opts_.set_longest_match(true);
  EXPECT_TRUE(opts_.longest_match());

  opts_.set_log_errors(false);
  EXPECT_FALSE(opts_.log_errors());

  opts_.set_literal(true);
  EXPECT_TRUE(opts_.literal());

  opts_.set_never_nl(true);
  EXPECT_TRUE(opts_.never_nl());

  opts_.set_dot_nl(true);
  EXPECT_TRUE(opts_.dot_nl());

  opts_.set_never_capture(true);
  EXPECT_TRUE(opts_.never_capture());

  opts_.set_case_sensitive(false);
  EXPECT_FALSE(opts_.case_sensitive());

  opts_.set_perl_classes(true);
  EXPECT_TRUE(opts_.perl_classes());

  opts_.set_word_boundary(true);
  EXPECT_TRUE(opts_.word_boundary());

  opts_.set_one_line(true);
  EXPECT_TRUE(opts_.one_line());

  // Encoding setter round-trip
  opts_.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(opts_.encoding(), RE2::Options::EncodingLatin1);

  // max_mem round-trip with a representative value
  const int64_t m = 1LL << 20; // 1 MiB
  opts_.set_max_mem(m);
  EXPECT_EQ(opts_.max_mem(), m);
}

// ---- Boundary values for max_mem --------------------------------------------

TEST_F(RE2OptionsTest_15, MaxMem_AllowsZeroAndLargeValues_15) {
  // Zero boundary
  opts_.set_max_mem(0);
  EXPECT_EQ(opts_.max_mem(), 0);

  // Large boundary
  const int64_t big = std::numeric_limits<int64_t>::max();
  opts_.set_max_mem(big);
  EXPECT_EQ(opts_.max_mem(), big);
}

// ---- ParseFlags observable changes ------------------------------------------

TEST_F(RE2OptionsTest_15, ParseFlags_ChangesWhenTogglingRelevantOptions_15) {
  int base = opts_.ParseFlags();

  // Toggle a few options that should influence parse flags.
  opts_.set_posix_syntax(true);
  int f_posix = opts_.ParseFlags();
  EXPECT_NE(base, f_posix);

  // Toggle case sensitivity should affect flags.
  opts_.set_case_sensitive(false);
  int f_ci = opts_.ParseFlags();
  // It's possible posix + case-insensitive collide differently; only assert that a change occurred
  // from the immediate prior state.
  EXPECT_NE(f_posix, f_ci);

  // Idempotency: re-reading without changes should be equal.
  int f_ci2 = opts_.ParseFlags();
  EXPECT_EQ(f_ci, f_ci2);
}

// ---- Copy semantics ----------------------------------------------------------

TEST_F(RE2OptionsTest_15, Copy_CopiesAllVisibleState_15) {
  // Prepare a non-default source.
  RE2::Options src;
  src.set_max_mem(123456);
  src.set_encoding(RE2::Options::EncodingLatin1);
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
  int src_flags = src.ParseFlags();

  // Copy into destination and verify equality via getters.
  RE2::Options dst;
  dst.Copy(src);

  EXPECT_EQ(dst.max_mem(), src.max_mem());
  EXPECT_EQ(dst.encoding(), src.encoding());
  EXPECT_EQ(dst.posix_syntax(), src.posix_syntax());
  EXPECT_EQ(dst.longest_match(), src.longest_match());
  EXPECT_EQ(dst.log_errors(), src.log_errors());
  EXPECT_EQ(dst.literal(), src.literal());
  EXPECT_EQ(dst.never_nl(), src.never_nl());
  EXPECT_EQ(dst.dot_nl(), src.dot_nl());
  EXPECT_EQ(dst.never_capture(), src.never_capture());
  EXPECT_EQ(dst.case_sensitive(), src.case_sensitive());
  EXPECT_EQ(dst.perl_classes(), src.perl_classes());
  EXPECT_EQ(dst.word_boundary(), src.word_boundary());
  EXPECT_EQ(dst.one_line(), src.one_line());
  EXPECT_EQ(dst.ParseFlags(), src_flags);

  // Independence after copy: mutating src doesn't change dst.
  src.set_case_sensitive(true);
  src.set_encoding(RE2::Options::EncodingUTF8);
  src.set_max_mem(42);

  EXPECT_NE(dst.case_sensitive(), src.case_sensitive());
  EXPECT_NE(dst.encoding(), src.encoding());
  EXPECT_NE(dst.max_mem(), src.max_mem());
}

// ---- Cross-check: Copy preserves ParseFlags equivalence ---------------------

TEST_F(RE2OptionsTest_15, ParseFlags_EqualAfterCopy_15) {
  RE2::Options a;
  a.set_posix_syntax(true);
  a.set_case_sensitive(false);
  a.set_never_capture(true);

  int a_flags = a.ParseFlags();

  RE2::Options b;
  b.Copy(a);

  EXPECT_EQ(b.ParseFlags(), a_flags);
}
