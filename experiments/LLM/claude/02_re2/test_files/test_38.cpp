#include "re2/re2.h"
#include <gtest/gtest.h>

namespace re2 {

// Test default constructor defaults
TEST(RE2OptionsTest_38, DefaultConstructorDefaults_38) {
  RE2::Options opts;
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
  EXPECT_FALSE(opts.posix_syntax());
  EXPECT_FALSE(opts.longest_match());
  EXPECT_TRUE(opts.log_errors());
  EXPECT_FALSE(opts.literal());
  EXPECT_FALSE(opts.never_nl());
  EXPECT_FALSE(opts.dot_nl());
  EXPECT_FALSE(opts.never_capture());
  EXPECT_TRUE(opts.case_sensitive());
  EXPECT_FALSE(opts.perl_classes());
  EXPECT_FALSE(opts.word_boundary());
  EXPECT_FALSE(opts.one_line());
}

// Test CannedOptions Latin1
TEST(RE2OptionsTest_38, CannedOptionsLatin1_38) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
  EXPECT_FALSE(opts.posix_syntax());
  EXPECT_FALSE(opts.longest_match());
  EXPECT_TRUE(opts.log_errors());
}

// Test CannedOptions POSIX
TEST(RE2OptionsTest_38, CannedOptionsPOSIX_38) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
  EXPECT_TRUE(opts.posix_syntax());
  EXPECT_TRUE(opts.longest_match());
  EXPECT_TRUE(opts.log_errors());
}

// Test CannedOptions Quiet
TEST(RE2OptionsTest_38, CannedOptionsQuiet_38) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
  EXPECT_FALSE(opts.posix_syntax());
  EXPECT_FALSE(opts.longest_match());
}

// Test set_max_mem and max_mem
TEST(RE2OptionsTest_38, SetMaxMem_38) {
  RE2::Options opts;
  int64_t original = opts.max_mem();
  EXPECT_GT(original, 0);

  opts.set_max_mem(1024);
  EXPECT_EQ(opts.max_mem(), 1024);

  opts.set_max_mem(0);
  EXPECT_EQ(opts.max_mem(), 0);

  opts.set_max_mem(INT64_MAX);
  EXPECT_EQ(opts.max_mem(), INT64_MAX);
}

// Test set_encoding and encoding
TEST(RE2OptionsTest_38, SetEncoding_38) {
  RE2::Options opts;
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);

  opts.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);

  opts.set_encoding(RE2::Options::EncodingUTF8);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

// Test set_posix_syntax
TEST(RE2OptionsTest_38, SetPosixSyntax_38) {
  RE2::Options opts;
  EXPECT_FALSE(opts.posix_syntax());

  opts.set_posix_syntax(true);
  EXPECT_TRUE(opts.posix_syntax());

  opts.set_posix_syntax(false);
  EXPECT_FALSE(opts.posix_syntax());
}

// Test set_longest_match
TEST(RE2OptionsTest_38, SetLongestMatch_38) {
  RE2::Options opts;
  EXPECT_FALSE(opts.longest_match());

  opts.set_longest_match(true);
  EXPECT_TRUE(opts.longest_match());

  opts.set_longest_match(false);
  EXPECT_FALSE(opts.longest_match());
}

// Test set_log_errors
TEST(RE2OptionsTest_38, SetLogErrors_38) {
  RE2::Options opts;
  EXPECT_TRUE(opts.log_errors());

  opts.set_log_errors(false);
  EXPECT_FALSE(opts.log_errors());

  opts.set_log_errors(true);
  EXPECT_TRUE(opts.log_errors());
}

// Test set_literal
TEST(RE2OptionsTest_38, SetLiteral_38) {
  RE2::Options opts;
  EXPECT_FALSE(opts.literal());

  opts.set_literal(true);
  EXPECT_TRUE(opts.literal());

  opts.set_literal(false);
  EXPECT_FALSE(opts.literal());
}

// Test set_never_nl
TEST(RE2OptionsTest_38, SetNeverNl_38) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_nl());

  opts.set_never_nl(true);
  EXPECT_TRUE(opts.never_nl());

  opts.set_never_nl(false);
  EXPECT_FALSE(opts.never_nl());
}

// Test set_dot_nl
TEST(RE2OptionsTest_38, SetDotNl_38) {
  RE2::Options opts;
  EXPECT_FALSE(opts.dot_nl());

  opts.set_dot_nl(true);
  EXPECT_TRUE(opts.dot_nl());

  opts.set_dot_nl(false);
  EXPECT_FALSE(opts.dot_nl());
}

// Test set_never_capture
TEST(RE2OptionsTest_38, SetNeverCapture_38) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_capture());

  opts.set_never_capture(true);
  EXPECT_TRUE(opts.never_capture());

  opts.set_never_capture(false);
  EXPECT_FALSE(opts.never_capture());
}

// Test set_case_sensitive
TEST(RE2OptionsTest_38, SetCaseSensitive_38) {
  RE2::Options opts;
  EXPECT_TRUE(opts.case_sensitive());

  opts.set_case_sensitive(false);
  EXPECT_FALSE(opts.case_sensitive());

  opts.set_case_sensitive(true);
  EXPECT_TRUE(opts.case_sensitive());
}

// Test set_perl_classes
TEST(RE2OptionsTest_38, SetPerlClasses_38) {
  RE2::Options opts;
  EXPECT_FALSE(opts.perl_classes());

  opts.set_perl_classes(true);
  EXPECT_TRUE(opts.perl_classes());

  opts.set_perl_classes(false);
  EXPECT_FALSE(opts.perl_classes());
}

// Test set_word_boundary
TEST(RE2OptionsTest_38, SetWordBoundary_38) {
  RE2::Options opts;
  EXPECT_FALSE(opts.word_boundary());

  opts.set_word_boundary(true);
  EXPECT_TRUE(opts.word_boundary());

  opts.set_word_boundary(false);
  EXPECT_FALSE(opts.word_boundary());
}

// Test set_one_line
TEST(RE2OptionsTest_38, SetOneLine_38) {
  RE2::Options opts;
  EXPECT_FALSE(opts.one_line());

  opts.set_one_line(true);
  EXPECT_TRUE(opts.one_line());

  opts.set_one_line(false);
  EXPECT_FALSE(opts.one_line());
}

// Test Copy method
TEST(RE2OptionsTest_38, CopyMethod_38) {
  RE2::Options src;
  src.set_max_mem(2048);
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

  RE2::Options dest;
  dest.Copy(src);

  EXPECT_EQ(dest.max_mem(), 2048);
  EXPECT_EQ(dest.encoding(), RE2::Options::EncodingLatin1);
  EXPECT_TRUE(dest.posix_syntax());
  EXPECT_TRUE(dest.longest_match());
  EXPECT_FALSE(dest.log_errors());
  EXPECT_TRUE(dest.literal());
  EXPECT_TRUE(dest.never_nl());
  EXPECT_TRUE(dest.dot_nl());
  EXPECT_TRUE(dest.never_capture());
  EXPECT_FALSE(dest.case_sensitive());
  EXPECT_TRUE(dest.perl_classes());
  EXPECT_TRUE(dest.word_boundary());
  EXPECT_TRUE(dest.one_line());
}

// Test Copy from default options
TEST(RE2OptionsTest_38, CopyFromDefault_38) {
  RE2::Options src;  // default
  RE2::Options dest;
  dest.set_literal(true);
  dest.set_dot_nl(true);
  dest.set_case_sensitive(false);

  dest.Copy(src);

  EXPECT_FALSE(dest.literal());
  EXPECT_FALSE(dest.dot_nl());
  EXPECT_TRUE(dest.case_sensitive());
}

// Test Copy self-assignment
TEST(RE2OptionsTest_38, CopySelf_38) {
  RE2::Options opts;
  opts.set_max_mem(4096);
  opts.set_literal(true);

  opts.Copy(opts);

  EXPECT_EQ(opts.max_mem(), 4096);
  EXPECT_TRUE(opts.literal());
}

// Test ParseFlags returns a value (we just ensure it doesn't crash and returns int)
TEST(RE2OptionsTest_38, ParseFlagsDefault_38) {
  RE2::Options opts;
  int flags = opts.ParseFlags();
  // Just verify it returns something without crashing
  (void)flags;
}

// Test ParseFlags changes with different settings
TEST(RE2OptionsTest_38, ParseFlagsChangesWithSettings_38) {
  RE2::Options opts1;
  int flags1 = opts1.ParseFlags();

  RE2::Options opts2;
  opts2.set_case_sensitive(false);
  int flags2 = opts2.ParseFlags();

  // Different settings should (likely) produce different parse flags
  EXPECT_NE(flags1, flags2);
}

// Test ParseFlags with POSIX canned options
TEST(RE2OptionsTest_38, ParseFlagsPOSIX_38) {
  RE2::Options opts1;
  RE2::Options opts2(RE2::POSIX);

  int flags1 = opts1.ParseFlags();
  int flags2 = opts2.ParseFlags();

  // POSIX options differ from default, so flags should differ
  EXPECT_NE(flags1, flags2);
}

// Test that multiple set calls work correctly (last one wins)
TEST(RE2OptionsTest_38, MultipleSetCalls_38) {
  RE2::Options opts;
  opts.set_literal(true);
  opts.set_literal(false);
  opts.set_literal(true);
  EXPECT_TRUE(opts.literal());

  opts.set_max_mem(100);
  opts.set_max_mem(200);
  opts.set_max_mem(300);
  EXPECT_EQ(opts.max_mem(), 300);
}

// Test boundary: max_mem with negative value
TEST(RE2OptionsTest_38, MaxMemNegative_38) {
  RE2::Options opts;
  opts.set_max_mem(-1);
  EXPECT_EQ(opts.max_mem(), -1);
}

// Test that CannedOptions default constructor (no args) gives expected defaults
TEST(RE2OptionsTest_38, DefaultOptionsMatchExpectedValues_38) {
  RE2::Options opts;
  // Verify all defaults explicitly
  EXPECT_FALSE(opts.posix_syntax());
  EXPECT_FALSE(opts.longest_match());
  EXPECT_TRUE(opts.log_errors());
  EXPECT_FALSE(opts.literal());
  EXPECT_FALSE(opts.never_nl());
  EXPECT_FALSE(opts.dot_nl());
  EXPECT_FALSE(opts.never_capture());
  EXPECT_TRUE(opts.case_sensitive());
  EXPECT_FALSE(opts.perl_classes());
  EXPECT_FALSE(opts.word_boundary());
  EXPECT_FALSE(opts.one_line());
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

// Test independence of two Options objects
TEST(RE2OptionsTest_38, IndependenceOfObjects_38) {
  RE2::Options opts1;
  RE2::Options opts2;

  opts1.set_literal(true);
  opts1.set_dot_nl(true);

  EXPECT_TRUE(opts1.literal());
  EXPECT_TRUE(opts1.dot_nl());
  EXPECT_FALSE(opts2.literal());
  EXPECT_FALSE(opts2.dot_nl());
}

}  // namespace re2
