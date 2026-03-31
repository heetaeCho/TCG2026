#include "re2/re2.h"
#include <gtest/gtest.h>
#include <string>

namespace re2 {

// ============================================================
// Tests for RE2::Options default constructor
// ============================================================

TEST(RE2OptionsTest_14, DefaultConstructor_EncodingIsUTF8_14) {
  RE2::Options opts;
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_14, DefaultConstructor_PosixSyntaxIsFalse_14) {
  RE2::Options opts;
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_14, DefaultConstructor_LongestMatchIsFalse_14) {
  RE2::Options opts;
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_14, DefaultConstructor_LogErrorsIsTrue_14) {
  RE2::Options opts;
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_14, DefaultConstructor_LiteralIsFalse_14) {
  RE2::Options opts;
  EXPECT_FALSE(opts.literal());
}

TEST(RE2OptionsTest_14, DefaultConstructor_NeverNlIsFalse_14) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_nl());
}

TEST(RE2OptionsTest_14, DefaultConstructor_DotNlIsFalse_14) {
  RE2::Options opts;
  EXPECT_FALSE(opts.dot_nl());
}

TEST(RE2OptionsTest_14, DefaultConstructor_NeverCaptureIsFalse_14) {
  RE2::Options opts;
  EXPECT_FALSE(opts.never_capture());
}

TEST(RE2OptionsTest_14, DefaultConstructor_CaseSensitiveIsTrue_14) {
  RE2::Options opts;
  EXPECT_TRUE(opts.case_sensitive());
}

TEST(RE2OptionsTest_14, DefaultConstructor_PerlClassesIsFalse_14) {
  RE2::Options opts;
  EXPECT_FALSE(opts.perl_classes());
}

TEST(RE2OptionsTest_14, DefaultConstructor_WordBoundaryIsFalse_14) {
  RE2::Options opts;
  EXPECT_FALSE(opts.word_boundary());
}

TEST(RE2OptionsTest_14, DefaultConstructor_OneLineIsFalse_14) {
  RE2::Options opts;
  EXPECT_FALSE(opts.one_line());
}

// ============================================================
// Tests for RE2::Options CannedOptions constructor
// ============================================================

TEST(RE2OptionsTest_14, Latin1Constructor_EncodingIsLatin1_14) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

TEST(RE2OptionsTest_14, Latin1Constructor_PosixSyntaxIsFalse_14) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_14, Latin1Constructor_LongestMatchIsFalse_14) {
  RE2::Options opts(RE2::Latin1);
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_14, POSIXConstructor_EncodingIsUTF8_14) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_14, POSIXConstructor_PosixSyntaxIsTrue_14) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.posix_syntax());
}

TEST(RE2OptionsTest_14, POSIXConstructor_LongestMatchIsTrue_14) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.longest_match());
}

TEST(RE2OptionsTest_14, POSIXConstructor_LogErrorsIsTrue_14) {
  RE2::Options opts(RE2::POSIX);
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_14, QuietConstructor_LogErrorsIsFalse_14) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.log_errors());
}

TEST(RE2OptionsTest_14, QuietConstructor_EncodingIsUTF8_14) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_14, QuietConstructor_PosixSyntaxIsFalse_14) {
  RE2::Options opts(RE2::Quiet);
  EXPECT_FALSE(opts.posix_syntax());
}

// ============================================================
// Tests for setters and getters
// ============================================================

TEST(RE2OptionsTest_14, SetEncoding_Latin1_14) {
  RE2::Options opts;
  opts.set_encoding(RE2::Options::EncodingLatin1);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingLatin1);
}

TEST(RE2OptionsTest_14, SetEncoding_UTF8_14) {
  RE2::Options opts(RE2::Latin1);
  opts.set_encoding(RE2::Options::EncodingUTF8);
  EXPECT_EQ(opts.encoding(), RE2::Options::EncodingUTF8);
}

TEST(RE2OptionsTest_14, SetPosixSyntax_True_14) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  EXPECT_TRUE(opts.posix_syntax());
}

TEST(RE2OptionsTest_14, SetPosixSyntax_False_14) {
  RE2::Options opts;
  opts.set_posix_syntax(true);
  opts.set_posix_syntax(false);
  EXPECT_FALSE(opts.posix_syntax());
}

TEST(RE2OptionsTest_14, SetLongestMatch_True_14) {
  RE2::Options opts;
  opts.set_longest_match(true);
  EXPECT_TRUE(opts.longest_match());
}

TEST(RE2OptionsTest_14, SetLongestMatch_False_14) {
  RE2::Options opts;
  opts.set_longest_match(true);
  opts.set_longest_match(false);
  EXPECT_FALSE(opts.longest_match());
}

TEST(RE2OptionsTest_14, SetLogErrors_False_14) {
  RE2::Options opts;
  opts.set_log_errors(false);
  EXPECT_FALSE(opts.log_errors());
}

TEST(RE2OptionsTest_14, SetLogErrors_True_14) {
  RE2::Options opts;
  opts.set_log_errors(false);
  opts.set_log_errors(true);
  EXPECT_TRUE(opts.log_errors());
}

TEST(RE2OptionsTest_14, SetLiteral_True_14) {
  RE2::Options opts;
  opts.set_literal(true);
  EXPECT_TRUE(opts.literal());
}

TEST(RE2OptionsTest_14, SetLiteral_False_14) {
  RE2::Options opts;
  opts.set_literal(true);
  opts.set_literal(false);
  EXPECT_FALSE(opts.literal());
}

TEST(RE2OptionsTest_14, SetNeverNl_True_14) {
  RE2::Options opts;
  opts.set_never_nl(true);
  EXPECT_TRUE(opts.never_nl());
}

TEST(RE2OptionsTest_14, SetNeverNl_False_14) {
  RE2::Options opts;
  opts.set_never_nl(true);
  opts.set_never_nl(false);
  EXPECT_FALSE(opts.never_nl());
}

TEST(RE2OptionsTest_14, SetDotNl_True_14) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  EXPECT_TRUE(opts.dot_nl());
}

TEST(RE2OptionsTest_14, SetDotNl_False_14) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  opts.set_dot_nl(false);
  EXPECT_FALSE(opts.dot_nl());
}

TEST(RE2OptionsTest_14, SetNeverCapture_True_14) {
  RE2::Options opts;
  opts.set_never_capture(true);
  EXPECT_TRUE(opts.never_capture());
}

TEST(RE2OptionsTest_14, SetNeverCapture_False_14) {
  RE2::Options opts;
  opts.set_never_capture(true);
  opts.set_never_capture(false);
  EXPECT_FALSE(opts.never_capture());
}

TEST(RE2OptionsTest_14, SetCaseSensitive_False_14) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  EXPECT_FALSE(opts.case_sensitive());
}

TEST(RE2OptionsTest_14, SetCaseSensitive_True_14) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  opts.set_case_sensitive(true);
  EXPECT_TRUE(opts.case_sensitive());
}

TEST(RE2OptionsTest_14, SetPerlClasses_True_14) {
  RE2::Options opts;
  opts.set_perl_classes(true);
  EXPECT_TRUE(opts.perl_classes());
}

TEST(RE2OptionsTest_14, SetPerlClasses_False_14) {
  RE2::Options opts;
  opts.set_perl_classes(true);
  opts.set_perl_classes(false);
  EXPECT_FALSE(opts.perl_classes());
}

TEST(RE2OptionsTest_14, SetWordBoundary_True_14) {
  RE2::Options opts;
  opts.set_word_boundary(true);
  EXPECT_TRUE(opts.word_boundary());
}

TEST(RE2OptionsTest_14, SetWordBoundary_False_14) {
  RE2::Options opts;
  opts.set_word_boundary(true);
  opts.set_word_boundary(false);
  EXPECT_FALSE(opts.word_boundary());
}

TEST(RE2OptionsTest_14, SetOneLine_True_14) {
  RE2::Options opts;
  opts.set_one_line(true);
  EXPECT_TRUE(opts.one_line());
}

TEST(RE2OptionsTest_14, SetOneLine_False_14) {
  RE2::Options opts;
  opts.set_one_line(true);
  opts.set_one_line(false);
  EXPECT_FALSE(opts.one_line());
}

TEST(RE2OptionsTest_14, SetMaxMem_14) {
  RE2::Options opts;
  opts.set_max_mem(1024 * 1024);
  EXPECT_EQ(opts.max_mem(), 1024 * 1024);
}

TEST(RE2OptionsTest_14, SetMaxMem_Zero_14) {
  RE2::Options opts;
  opts.set_max_mem(0);
  EXPECT_EQ(opts.max_mem(), 0);
}

TEST(RE2OptionsTest_14, SetMaxMem_Large_14) {
  RE2::Options opts;
  int64_t large_val = static_cast<int64_t>(1) << 40;
  opts.set_max_mem(large_val);
  EXPECT_EQ(opts.max_mem(), large_val);
}

// ============================================================
// Tests for Copy
// ============================================================

TEST(RE2OptionsTest_14, Copy_AllFieldsCopied_14) {
  RE2::Options src;
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
  src.set_max_mem(12345);

  RE2::Options dst;
  dst.Copy(src);

  EXPECT_EQ(dst.encoding(), RE2::Options::EncodingLatin1);
  EXPECT_TRUE(dst.posix_syntax());
  EXPECT_TRUE(dst.longest_match());
  EXPECT_FALSE(dst.log_errors());
  EXPECT_TRUE(dst.literal());
  EXPECT_TRUE(dst.never_nl());
  EXPECT_TRUE(dst.dot_nl());
  EXPECT_TRUE(dst.never_capture());
  EXPECT_FALSE(dst.case_sensitive());
  EXPECT_TRUE(dst.perl_classes());
  EXPECT_TRUE(dst.word_boundary());
  EXPECT_TRUE(dst.one_line());
  EXPECT_EQ(dst.max_mem(), 12345);
}

TEST(RE2OptionsTest_14, Copy_DefaultToDefault_14) {
  RE2::Options src;
  RE2::Options dst;
  dst.set_literal(true);  // change something
  dst.Copy(src);
  EXPECT_FALSE(dst.literal());
  EXPECT_EQ(dst.encoding(), RE2::Options::EncodingUTF8);
  EXPECT_TRUE(dst.log_errors());
  EXPECT_TRUE(dst.case_sensitive());
}

// ============================================================
// Tests for RE2 basic functionality
// ============================================================

TEST(RE2Test_14, SimpleMatch_14) {
  RE2 re("hello");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("world", re));
}

TEST(RE2Test_14, PartialMatch_14) {
  RE2 re("ell");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::PartialMatch("hello", re));
  EXPECT_FALSE(RE2::PartialMatch("world", re));
}

TEST(RE2Test_14, InvalidPattern_14) {
  RE2 re("[invalid");
  EXPECT_FALSE(re.ok());
  EXPECT_NE(re.error().size(), 0u);
}

TEST(RE2Test_14, EmptyPattern_14) {
  RE2 re("");
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("", re));
  EXPECT_FALSE(RE2::FullMatch("notempty", re));
}

TEST(RE2Test_14, PatternString_14) {
  RE2 re("abc.*def");
  EXPECT_EQ(re.pattern(), "abc.*def");
}

TEST(RE2Test_14, FullMatchWithCapture_14) {
  RE2 re("(\\d+)-(\\d+)");
  std::string s1, s2;
  EXPECT_TRUE(RE2::FullMatch("123-456", re, &s1, &s2));
  EXPECT_EQ(s1, "123");
  EXPECT_EQ(s2, "456");
}

TEST(RE2Test_14, PartialMatchWithCapture_14) {
  RE2 re("(\\w+)@(\\w+)");
  std::string user, domain;
  EXPECT_TRUE(RE2::PartialMatch("test user@host more", re, &user, &domain));
  EXPECT_EQ(user, "user");
  EXPECT_EQ(domain, "host");
}

TEST(RE2Test_14, FullMatchNoMatch_14) {
  EXPECT_FALSE(RE2::FullMatch("abc", "def"));
}

TEST(RE2Test_14, ConstructWithOptions_14) {
  RE2::Options opts;
  opts.set_case_sensitive(false);
  RE2 re("HELLO", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_TRUE(RE2::FullMatch("HELLO", re));
  EXPECT_TRUE(RE2::FullMatch("Hello", re));
}

TEST(RE2Test_14, ConstructWithLatin1_14) {
  RE2 re("hello", RE2::Latin1);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

TEST(RE2Test_14, ConstructWithPOSIX_14) {
  RE2 re("hello", RE2::POSIX);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
}

TEST(RE2Test_14, ConstructWithQuiet_14) {
  RE2 re("[invalid", RE2::Quiet);
  EXPECT_FALSE(re.ok());
}

TEST(RE2Test_14, LiteralOption_14) {
  RE2::Options opts;
  opts.set_literal(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a.b", re));
  EXPECT_FALSE(RE2::FullMatch("axb", re));
}

TEST(RE2Test_14, NeverCapture_14) {
  RE2::Options opts;
  opts.set_never_capture(true);
  RE2 re("(\\d+)", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST(RE2Test_14, NumberOfCapturingGroups_14) {
  RE2 re("(a)(b)(c)");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 3);
}

TEST(RE2Test_14, NumberOfCapturingGroups_None_14) {
  RE2 re("abc");
  EXPECT_TRUE(re.ok());
  EXPECT_EQ(re.NumberOfCapturingGroups(), 0);
}

TEST(RE2Test_14, Replace_14) {
  std::string s = "hello world";
  EXPECT_TRUE(RE2::Replace(&s, "world", "there"));
  EXPECT_EQ(s, "hello there");
}

TEST(RE2Test_14, GlobalReplace_14) {
  std::string s = "aaa";
  int count = RE2::GlobalReplace(&s, "a", "bb");
  EXPECT_EQ(count, 3);
  EXPECT_EQ(s, "bbbbbb");
}

TEST(RE2Test_14, ReplaceNoMatch_14) {
  std::string s = "hello";
  EXPECT_FALSE(RE2::Replace(&s, "xyz", "abc"));
  EXPECT_EQ(s, "hello");
}

TEST(RE2Test_14, QuoteMeta_14) {
  std::string quoted = RE2::QuoteMeta("a.b+c*d");
  RE2 re(quoted);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("a.b+c*d", re));
  EXPECT_FALSE(RE2::FullMatch("axbxcxd", re));
}

TEST(RE2Test_14, ErrorCode_ValidPattern_14) {
  RE2 re("abc");
  EXPECT_EQ(re.error_code(), RE2::NoError);
}

TEST(RE2Test_14, ErrorCode_InvalidPattern_14) {
  RE2 re("[invalid", RE2::Quiet);
  EXPECT_NE(re.error_code(), RE2::NoError);
}

TEST(RE2Test_14, DotNl_14) {
  RE2::Options opts;
  opts.set_dot_nl(true);
  RE2 re("a.b", opts);
  EXPECT_TRUE(RE2::FullMatch("a\nb", re));
}

TEST(RE2Test_14, DotNlDefault_14) {
  RE2 re("a.b");
  EXPECT_FALSE(RE2::FullMatch("a\nb", re));
}

TEST(RE2Test_14, NeverNl_14) {
  RE2::Options opts;
  opts.set_never_nl(true);
  RE2 re("[^a]", opts);
  EXPECT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("b", re));
  // With never_nl, [^a] should not match \n
  EXPECT_FALSE(RE2::FullMatch("\n", re));
}

// ============================================================
// Tests for Options::ParseFlags
// ============================================================

TEST(RE2OptionsTest_14, ParseFlags_Default_14) {
  RE2::Options opts;
  int flags = opts.ParseFlags();
  // We just verify it returns something without crashing
  // and that different options produce different flags
  RE2::Options opts2;
  opts2.set_posix_syntax(true);
  int flags2 = opts2.ParseFlags();
  EXPECT_NE(flags, flags2);
}

TEST(RE2OptionsTest_14, ParseFlags_LongestMatchChangesFlags_14) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_longest_match(true);
  EXPECT_NE(opts1.ParseFlags(), opts2.ParseFlags());
}

TEST(RE2OptionsTest_14, ParseFlags_CaseSensitiveChangesFlags_14) {
  RE2::Options opts1;
  RE2::Options opts2;
  opts2.set_case_sensitive(false);
  EXPECT_NE(opts1.ParseFlags(), opts2.ParseFlags());
}

}  // namespace re2
