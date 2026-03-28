#include "re2/re2.h"
#include <gtest/gtest.h>

namespace re2 {

// Test default construction of Options
TEST(RE2OptionsTest_16, DefaultConstructorDefaults_16) {
  RE2::Options opts;
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

// Test CannedOptions: RE2::DefaultOptions (should behave like default)
TEST(RE2OptionsTest_16, CannedDefaultOptions_16) {
  RE2::Options opts(RE2::DefaultOptions);
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

// Test CannedOptions: RE2::Latin1
TEST(RE2OptionsTest_16, CannedLatin1Options_16) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.posix_syntax());
  EXPECT_FALSE(opts.longest_match());
  EXPECT_TRUE(opts.log_errors());
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

// Test CannedOptions: RE2::POSIX
TEST(RE2OptionsTest_16, CannedPOSIXOptions_16) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
  EXPECT_TRUE(opts.longest_match());
  EXPECT_TRUE(opts.log_errors());
}

// Test CannedOptions: RE2::Quiet
TEST(RE2OptionsTest_16, CannedQuietOptions_16) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
}

// Test set_posix_syntax / posix_syntax
TEST(RE2OptionsTest_16, SetPosixSyntax_16) {
  RE2::Options opts;
  EXPECT_FALSE(opts.posix_syntax());
  opts.set_posix_syntax(true);
  EXPECT_TRUE(opts.posix_syntax());
  opts.set_posix_syntax(false);
  EXPECT_FALSE(opts.posix_syntax());
}

// Test set_longest_match / longest_match
TEST(RE2OptionsTest_16, SetLongestMatch_16) {
  RE2::Options opts;
  EXPECT_FALSE(opts.longest_match());
  opts.set_longest_match(true);
  EXPECT_TRUE(opts.longest_match());
  opts.set_longest_match(false);
  EXPECT_FALSE(opts.longest_match());
}

// Test set_log_errors / log_errors
TEST(RE2OptionsTest_16, SetLogErrors_16) {
  RE2::Options opts;
  EXPECT_TRUE(opts.log_errors());
  opts.set_log_errors(false);
  EXPECT_FALSE(opts.log_errors());
  opts.set_log_errors(true);
  EXPECT_TRUE(opts.log_errors());
}

// Test set_literal / literal
TEST(RE2OptionsTest_16, SetLiteral_16) {
  RE2::Options opts;
  EXPECT_FALSE(opts.literal());
  opts.set_literal(true);
  EXPECT_TRUE(opts.literal());
  opts.set_literal(false);
  EXPECT_FALSE(opts.literal());
}

// Test set_never_nl / never_nl
TEST(RE2OptionsTest_16, SetNeverNl_16) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_nl());
  opts.set_never_nl(true);
  EXPECT_TRUE(opts.never_nl());
  opts.set_never_nl(false);
  EXPECT_FALSE(opts.never_nl());
}

// Test set_dot_nl / dot_nl
TEST(RE2OptionsTest_16, SetDotNl_16) {
  RE2::Options opts;
  EXPECT_FALSE(opts.dot_nl());
  opts.set_dot_nl(true);
  EXPECT_TRUE(opts.dot_nl());
  opts.set_dot_nl(false);
  EXPECT_FALSE(opts.dot_nl());
}

// Test set_never_capture / never_capture
TEST(RE2OptionsTest_16, SetNeverCapture_16) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_capture());
  opts.set_never_capture(true);
  EXPECT_TRUE(opts.never_capture());
  opts.set_never_capture(false);
  EXPECT_FALSE(opts.never_capture());
}

// Test set_case_sensitive / case_sensitive
TEST(RE2OptionsTest_16, SetCaseSensitive_16) {
  RE2::Options opts;
  EXPECT_TRUE(opts.case_sensitive());
  opts.set_case_sensitive(false);
  EXPECT_FALSE(opts.case_sensitive());
  opts.set_case_sensitive(true);
  EXPECT_TRUE(opts.case_sensitive());
}

// Test set_perl_classes / perl_classes
TEST(RE2OptionsTest_16, SetPerlClasses_16) {
  RE2::Options opts;
  EXPECT_FALSE(opts.perl_classes());
  opts.set_perl_classes(true);
  EXPECT_TRUE(opts.perl_classes());
  opts.set_perl_classes(false);
  EXPECT_FALSE(opts.perl_classes());
}

// Test set_word_boundary / word_boundary
TEST(RE2OptionsTest_16, SetWordBoundary_16) {
  RE2::Options opts;
  EXPECT_FALSE(opts.word_boundary());
  opts.set_word_boundary(true);
  EXPECT_TRUE(opts.word_boundary());
  opts.set_word_boundary(false);
  EXPECT_FALSE(opts.word_boundary());
}

// Test set_one_line / one_line
TEST(RE2OptionsTest_16, SetOneLine_16) {
  RE2::Options opts;
  EXPECT_FALSE(opts.one_line());
  opts.set_one_line(true);
  EXPECT_TRUE(opts.one_line());
  opts.set_one_line(false);
  EXPECT_FALSE(opts.one_line());
}

// Test set_max_mem / max_mem
TEST(RE2OptionsTest_16, SetMaxMem_16) {
  RE2::Options opts;
  int64_t default_mem = opts.max_mem();
  EXPECT_GT(default_mem, 0);
  
  opts.set_max_mem(1024);
  EXPECT_EQ(opts.max_mem(), 1024);
  
  opts.set_max_mem(0);
  EXPECT_EQ(opts.max_mem(), 0);
  
  opts.set_max_mem(1000000000LL);
  EXPECT_EQ(opts.max_mem(), 1000000000LL);
}

// Test set_encoding / encoding
TEST(RE2OptionsTest_16, SetEncoding_16) {
  RE2::Options opts;
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
  
  opts.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
  
  opts.set_encoding(RE2::Options::EncodingUTF8);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

// Test Copy method
TEST(RE2OptionsTest_16, CopyOptions_16) {
  RE2::Options src;
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
  src.set_max_mem(12345);
  src.set_encoding(RE2::Options::EncodingLatin1);

  RE2::Options dst;
  dst.Copy(src);

  EXPECT_EQ(dst.posix_syntax(), true);
  EXPECT_EQ(dst.longest_match(), true);
  EXPECT_EQ(dst.log_errors(), false);
  EXPECT_EQ(dst.literal(), true);
  EXPECT_EQ(dst.never_nl(), true);
  EXPECT_EQ(dst.dot_nl(), true);
  EXPECT_EQ(dst.never_capture(), true);
  EXPECT_EQ(dst.case_sensitive(), false);
  EXPECT_EQ(dst.perl_classes(), true);
  EXPECT_EQ(dst.word_boundary(), true);
  EXPECT_EQ(dst.one_line(), true);
  EXPECT_EQ(dst.max_mem(), 12345);
  EXPECT_EQ(dst.encoding(), RE2::Options::EncodingLatin1);
}

// Test that POSIX canned option sets encoding to UTF8
TEST(RE2OptionsTest_16, POSIXEncodingIsUTF8_16) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

// Test that Latin1 canned option disables posix_syntax and longest_match
TEST(RE2OptionsTest_16, Latin1DisablesPosixAndLongest_16) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.posix_syntax());
  EXPECT_FALSE(opts.longest_match());
}

// Test multiple set/get cycles for the same option
TEST(RE2OptionsTest_16, MultipleSetGetCycles_16) {
  RE2::Options opts;
  for (int i = 0; i < 10; ++i) {
    bool val = (i % 2 == 0);
    opts.set_posix_syntax(val);
    EXPECT_EQ(opts.posix_syntax(), val);
  }
}

// Test setting max_mem to a very large value
TEST(RE2OptionsTest_16, MaxMemLargeValue_16) {
  RE2::Options opts;
  int64_t large_val = static_cast<int64_t>(1) << 40;  // 1TB
  opts.set_max_mem(large_val);
  EXPECT_EQ(opts.max_mem(), large_val);
}

// Test that ParseFlags returns a consistent value
TEST(RE2OptionsTest_16, ParseFlagsConsistency_16) {
  RE2::Options opts1;
  RE2::Options opts2;
  // Two default-constructed options should have the same parse flags
  EXPECT_EQ(opts1.ParseFlags(), opts2.ParseFlags());
}

// Test that changing options affects ParseFlags
TEST(RE2OptionsTest_16, ParseFlagsChangesWithOptions_16) {
  RE2::Options opts1;
  RE2::Options opts2;
  
  int flags_default = opts1.ParseFlags();
  
  opts2.set_case_sensitive(false);
  int flags_case_insensitive = opts2.ParseFlags();
  
  // Changing case sensitivity should change parse flags
  EXPECT_NE(flags_default, flags_case_insensitive);
}

// Test ParseFlags difference between POSIX and default
TEST(RE2OptionsTest_16, ParseFlagsPOSIXvDefault_16) {
  RE2::Options opts_default;
  RE2::Options opts_posix(RE2::POSIX);
  
  EXPECT_NE(opts_default.ParseFlags(), opts_posix.ParseFlags());
}

// Test Copy from POSIX to default and verify
TEST(RE2OptionsTest_16, CopyFromPOSIX_16) {
  RE2::Options src(RE2::POSIX);
  RE2::Options dst;
  
  EXPECT_FALSE(dst.posix_syntax());
  dst.Copy(src);
  EXPECT_TRUE(dst.posix_syntax());
  EXPECT_TRUE(dst.longest_match());
}

}  // namespace re2
