#include "re2/re2.h"
#include <gtest/gtest.h>
#include <string>

namespace re2 {

// Test default construction of Options
TEST(RE2OptionsTest_26, DefaultConstructorDefaults_26) {
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

// Test CannedOptions: RE2::Latin1
TEST(RE2OptionsTest_26, CannedOptionsLatin1_26) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
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

// Test CannedOptions: RE2::POSIX
TEST(RE2OptionsTest_26, CannedOptionsPOSIX_26) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
  EXPECT_TRUE(opts.posix_syntax());
  EXPECT_TRUE(opts.longest_match());
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

// Test CannedOptions: RE2::Quiet
TEST(RE2OptionsTest_26, CannedOptionsQuiet_26) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
  EXPECT_FALSE(opts.posix_syntax());
  EXPECT_FALSE(opts.longest_match());
}

// Test CannedOptions: RE2::DefaultOptions
TEST(RE2OptionsTest_26, CannedOptionsDefault_26) {
  RE2::Options opts(RE2::DefaultOptions);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
  EXPECT_FALSE(opts.posix_syntax());
  EXPECT_FALSE(opts.longest_match());
  EXPECT_TRUE(opts.log_errors());
  EXPECT_FALSE(opts.dot_nl());
}

// Test dot_nl getter and setter
TEST(RE2OptionsTest_26, DotNlGetterSetter_26) {
  RE2::Options opts;
  EXPECT_FALSE(opts.dot_nl());
  opts.set_dot_nl(true);
  EXPECT_TRUE(opts.dot_nl());
  opts.set_dot_nl(false);
  EXPECT_FALSE(opts.dot_nl());
}

// Test posix_syntax getter and setter
TEST(RE2OptionsTest_26, PosixSyntaxGetterSetter_26) {
  RE2::Options opts;
  EXPECT_FALSE(opts.posix_syntax());
  opts.set_posix_syntax(true);
  EXPECT_TRUE(opts.posix_syntax());
  opts.set_posix_syntax(false);
  EXPECT_FALSE(opts.posix_syntax());
}

// Test longest_match getter and setter
TEST(RE2OptionsTest_26, LongestMatchGetterSetter_26) {
  RE2::Options opts;
  EXPECT_FALSE(opts.longest_match());
  opts.set_longest_match(true);
  EXPECT_TRUE(opts.longest_match());
  opts.set_longest_match(false);
  EXPECT_FALSE(opts.longest_match());
}

// Test log_errors getter and setter
TEST(RE2OptionsTest_26, LogErrorsGetterSetter_26) {
  RE2::Options opts;
  EXPECT_TRUE(opts.log_errors());
  opts.set_log_errors(false);
  EXPECT_FALSE(opts.log_errors());
  opts.set_log_errors(true);
  EXPECT_TRUE(opts.log_errors());
}

// Test literal getter and setter
TEST(RE2OptionsTest_26, LiteralGetterSetter_26) {
  RE2::Options opts;
  EXPECT_FALSE(opts.literal());
  opts.set_literal(true);
  EXPECT_TRUE(opts.literal());
  opts.set_literal(false);
  EXPECT_FALSE(opts.literal());
}

// Test never_nl getter and setter
TEST(RE2OptionsTest_26, NeverNlGetterSetter_26) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_nl());
  opts.set_never_nl(true);
  EXPECT_TRUE(opts.never_nl());
  opts.set_never_nl(false);
  EXPECT_FALSE(opts.never_nl());
}

// Test never_capture getter and setter
TEST(RE2OptionsTest_26, NeverCaptureGetterSetter_26) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_capture());
  opts.set_never_capture(true);
  EXPECT_TRUE(opts.never_capture());
  opts.set_never_capture(false);
  EXPECT_FALSE(opts.never_capture());
}

// Test case_sensitive getter and setter
TEST(RE2OptionsTest_26, CaseSensitiveGetterSetter_26) {
  RE2::Options opts;
  EXPECT_TRUE(opts.case_sensitive());
  opts.set_case_sensitive(false);
  EXPECT_FALSE(opts.case_sensitive());
  opts.set_case_sensitive(true);
  EXPECT_TRUE(opts.case_sensitive());
}

// Test perl_classes getter and setter
TEST(RE2OptionsTest_26, PerlClassesGetterSetter_26) {
  RE2::Options opts;
  EXPECT_FALSE(opts.perl_classes());
  opts.set_perl_classes(true);
  EXPECT_TRUE(opts.perl_classes());
  opts.set_perl_classes(false);
  EXPECT_FALSE(opts.perl_classes());
}

// Test word_boundary getter and setter
TEST(RE2OptionsTest_26, WordBoundaryGetterSetter_26) {
  RE2::Options opts;
  EXPECT_FALSE(opts.word_boundary());
  opts.set_word_boundary(true);
  EXPECT_TRUE(opts.word_boundary());
  opts.set_word_boundary(false);
  EXPECT_FALSE(opts.word_boundary());
}

// Test one_line getter and setter
TEST(RE2OptionsTest_26, OneLineGetterSetter_26) {
  RE2::Options opts;
  EXPECT_FALSE(opts.one_line());
  opts.set_one_line(true);
  EXPECT_TRUE(opts.one_line());
  opts.set_one_line(false);
  EXPECT_FALSE(opts.one_line());
}

// Test max_mem getter and setter
TEST(RE2OptionsTest_26, MaxMemGetterSetter_26) {
  RE2::Options opts;
  int64_t default_max_mem = opts.max_mem();
  EXPECT_GT(default_max_mem, 0);

  opts.set_max_mem(1024);
  EXPECT_EQ(opts.max_mem(), 1024);

  opts.set_max_mem(0);
  EXPECT_EQ(opts.max_mem(), 0);

  opts.set_max_mem(1000000000LL);
  EXPECT_EQ(opts.max_mem(), 1000000000LL);
}

// Test encoding getter and setter
TEST(RE2OptionsTest_26, EncodingGetterSetter_26) {
  RE2::Options opts;
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
  opts.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
  opts.set_encoding(RE2::Options::EncodingUTF8);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

// Test Copy method
TEST(RE2OptionsTest_26, CopyMethod_26) {
  RE2::Options src;
  src.set_dot_nl(true);
  src.set_case_sensitive(false);
  src.set_longest_match(true);
  src.set_max_mem(2048);
  src.set_encoding(RE2::Options::EncodingLatin1);
  src.set_posix_syntax(true);
  src.set_log_errors(false);
  src.set_literal(true);
  src.set_never_nl(true);
  src.set_never_capture(true);
  src.set_perl_classes(true);
  src.set_word_boundary(true);
  src.set_one_line(true);

  RE2::Options dst;
  dst.Copy(src);

  EXPECT_TRUE(dst.dot_nl());
  EXPECT_FALSE(dst.case_sensitive());
  EXPECT_TRUE(dst.longest_match());
  EXPECT_EQ(dst.max_mem(), 2048);
  EXPECT_EQ(dst.encoding(), RE2::Options::EncodingLatin1);
  EXPECT_TRUE(dst.posix_syntax());
  EXPECT_FALSE(dst.log_errors());
  EXPECT_TRUE(dst.literal());
  EXPECT_TRUE(dst.never_nl());
  EXPECT_TRUE(dst.never_capture());
  EXPECT_TRUE(dst.perl_classes());
  EXPECT_TRUE(dst.word_boundary());
  EXPECT_TRUE(dst.one_line());
}

// Test that Copy doesn't affect source
TEST(RE2OptionsTest_26, CopyDoesNotAffectSource_26) {
  RE2::Options src;
  src.set_dot_nl(true);

  RE2::Options dst;
  dst.Copy(src);
  dst.set_dot_nl(false);

  EXPECT_TRUE(src.dot_nl());
  EXPECT_FALSE(dst.dot_nl());
}

// Test multiple setter calls in sequence
TEST(RE2OptionsTest_26, MultipleSetterCalls_26) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  opts.set_dot_nl(true);
  EXPECT_TRUE(opts.dot_nl());

  opts.set_dot_nl(false);
  opts.set_dot_nl(false);
  EXPECT_FALSE(opts.dot_nl());
}

// Test setting all boolean options to true
TEST(RE2OptionsTest_26, AllBooleanOptionsTrue_26) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  opts.set_longest_match(true);
  opts.set_log_errors(true);
  opts.set_literal(true);
  opts.set_never_nl(true);
  opts.set_dot_nl(true);
  opts.set_never_capture(true);
  opts.set_case_sensitive(true);
  opts.set_perl_classes(true);
  opts.set_word_boundary(true);
  opts.set_one_line(true);

  EXPECT_TRUE(opts.posix_syntax());
  EXPECT_TRUE(opts.longest_match());
  EXPECT_TRUE(opts.log_errors());
  EXPECT_TRUE(opts.literal());
  EXPECT_TRUE(opts.never_nl());
  EXPECT_TRUE(opts.dot_nl());
  EXPECT_TRUE(opts.never_capture());
  EXPECT_TRUE(opts.case_sensitive());
  EXPECT_TRUE(opts.perl_classes());
  EXPECT_TRUE(opts.word_boundary());
  EXPECT_TRUE(opts.one_line());
}

// Test setting all boolean options to false
TEST(RE2OptionsTest_26, AllBooleanOptionsFalse_26) {
  RE2::Options opts;
  opts.set_posix_syntax(false);
  opts.set_longest_match(false);
  opts.set_log_errors(false);
  opts.set_literal(false);
  opts.set_never_nl(false);
  opts.set_dot_nl(false);
  opts.set_never_capture(false);
  opts.set_case_sensitive(false);
  opts.set_perl_classes(false);
  opts.set_word_boundary(false);
  opts.set_one_line(false);

  EXPECT_FALSE(opts.posix_syntax());
  EXPECT_FALSE(opts.longest_match());
  EXPECT_FALSE(opts.log_errors());
  EXPECT_FALSE(opts.literal());
  EXPECT_FALSE(opts.never_nl());
  EXPECT_FALSE(opts.dot_nl());
  EXPECT_FALSE(opts.never_capture());
  EXPECT_FALSE(opts.case_sensitive());
  EXPECT_FALSE(opts.perl_classes());
  EXPECT_FALSE(opts.word_boundary());
  EXPECT_FALSE(opts.one_line());
}

// Test max_mem boundary with large values
TEST(RE2OptionsTest_26, MaxMemLargeValue_26) {
  RE2::Options opts;
  int64_t large_value = static_cast<int64_t>(1) << 40;  // 1TB
  opts.set_max_mem(large_value);
  EXPECT_EQ(opts.max_mem(), large_value);
}

// Test that Options with dot_nl affects RE2 matching behavior
TEST(RE2OptionsTest_26, DotNlAffectsMatching_26) {
  RE2::Options opts_no_dot_nl;
  opts_no_dot_nl.set_dot_nl(false);
  RE2 re_no_dot_nl(".", opts_no_dot_nl);
  EXPECT_FALSE(RE2::FullMatch("\n", re_no_dot_nl));

  RE2::Options opts_dot_nl;
  opts_dot_nl.set_dot_nl(true);
  RE2 re_dot_nl(".", opts_dot_nl);
  EXPECT_TRUE(RE2::FullMatch("\n", re_dot_nl));
}

// Test that case_sensitive option affects matching
TEST(RE2OptionsTest_26, CaseSensitiveAffectsMatching_26) {
  RE2::Options opts_sensitive;
  opts_sensitive.set_case_sensitive(true);
  RE2 re_sensitive("hello", opts_sensitive);
  EXPECT_TRUE(RE2::FullMatch("hello", re_sensitive));
  EXPECT_FALSE(RE2::FullMatch("HELLO", re_sensitive));

  RE2::Options opts_insensitive;
  opts_insensitive.set_case_sensitive(false);
  RE2 re_insensitive("hello", opts_insensitive);
  EXPECT_TRUE(RE2::FullMatch("hello", re_insensitive));
  EXPECT_TRUE(RE2::FullMatch("HELLO", re_insensitive));
}

// Test literal option affects matching
TEST(RE2OptionsTest_26, LiteralAffectsMatching_26) {
  RE2::Options opts_literal;
  opts_literal.set_literal(true);
  RE2 re_literal("a.b", opts_literal);
  EXPECT_TRUE(RE2::FullMatch("a.b", re_literal));
  EXPECT_FALSE(RE2::FullMatch("axb", re_literal));

  RE2::Options opts_regex;
  opts_regex.set_literal(false);
  RE2 re_regex("a.b", opts_regex);
  EXPECT_TRUE(RE2::FullMatch("a.b", re_regex));
  EXPECT_TRUE(RE2::FullMatch("axb", re_regex));
}

// Test ParseFlags returns a value (black box - just ensure it's callable)
TEST(RE2OptionsTest_26, ParseFlagsCallable_26) {
  RE2::Options opts;
  int flags = opts.ParseFlags();
  // We don't know the exact value but it should be deterministic
  EXPECT_EQ(flags, opts.ParseFlags());
}

// Test ParseFlags changes with different option settings
TEST(RE2OptionsTest_26, ParseFlagsChangesWithOptions_26) {
  RE2::Options opts1;
  int flags1 = opts1.ParseFlags();

  RE2::Options opts2;
  opts2.set_dot_nl(true);
  int flags2 = opts2.ParseFlags();

  // Different options should generally produce different parse flags
  // (though we treat this as a soft expectation since it's black box)
  // At minimum, changing options should be reflected
  EXPECT_NE(flags1, flags2);
}

// Test Copy from POSIX canned options
TEST(RE2OptionsTest_26, CopyFromPOSIXOptions_26) {
  RE2::Options src(RE2::POSIX);
  RE2::Options dst;
  dst.Copy(src);

  EXPECT_TRUE(dst.posix_syntax());
  EXPECT_TRUE(dst.longest_match());
  EXPECT_EQ(dst.encoding(), RE2::Options::EncodingUTF8);
}

}  // namespace re2
