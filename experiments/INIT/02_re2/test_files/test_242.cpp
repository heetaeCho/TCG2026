// File: re2_options_parseflags_test_242.cc
#include "gtest/gtest.h"

#include "re2/re2.h"
#include "re2/regexp.h"

using re2::RE2;
using re2::Regexp;

class RE2OptionsParseFlagsTest_242 : public ::testing::Test {
protected:
  static bool Has(int flags, int bit) { return (flags & bit) == bit; }
};

// Default behavior: UTF-8, !posix_syntax, all other toggles false.
// Expect ClassNL plus LikePerl composite flags.
TEST(RE2OptionsParseFlagsTest_242, DefaultsIncludeLikePerlAndClassNL_242) {
  RE2::Options opt;
  const int flags = opt.ParseFlags();
  EXPECT_TRUE(Has(flags, Regexp::ClassNL));
  EXPECT_TRUE(Has(flags, Regexp::LikePerl));     // composite bitmask
  EXPECT_FALSE(Has(flags, Regexp::Latin1));
  EXPECT_FALSE(Has(flags, Regexp::Literal));
  EXPECT_FALSE(Has(flags, Regexp::NeverNL));
  EXPECT_FALSE(Has(flags, Regexp::DotNL));
  EXPECT_FALSE(Has(flags, Regexp::NeverCapture));
  EXPECT_FALSE(Has(flags, Regexp::FoldCase));    // case_sensitive defaults true
}

// Encoding: Latin1 should add the Latin1 flag.
TEST(RE2OptionsParseFlagsTest_242, Latin1EncodingSetsLatin1Flag_242) {
  RE2::Options opt;
  opt.set_encoding(RE2::Options::EncodingLatin1);
  const int flags = opt.ParseFlags();
  EXPECT_TRUE(Has(flags, Regexp::Latin1));
}

// Encoding: UTF8 (default) should NOT add Latin1.
TEST(RE2OptionsParseFlagsTest_242, UTF8EncodingDoesNotSetLatin1Flag_242) {
  RE2::Options opt;
  opt.set_encoding(RE2::Options::EncodingUTF8);
  const int flags = opt.ParseFlags();
  EXPECT_FALSE(Has(flags, Regexp::Latin1));
}

// Unknown encoding goes through the default branch (logs error).
// Observable effect: same as UTF-8 (no Latin1 bit set).
TEST(RE2OptionsParseFlagsTest_242, UnknownEncodingDoesNotSetLatin1_242) {
  RE2::Options opt;
  opt.set_encoding(static_cast<RE2::Options::Encoding>(999));
  const int flags = opt.ParseFlags();
  EXPECT_FALSE(Has(flags, Regexp::Latin1));
}

// posix_syntax = true suppresses LikePerl composite flags.
TEST(RE2OptionsParseFlagsTest_242, PosixSyntaxDisablesLikePerl_242) {
  RE2::Options opt;
  opt.set_posix_syntax(true);
  const int flags = opt.ParseFlags();
  EXPECT_TRUE(Has(flags, Regexp::ClassNL));   // always set initially
  EXPECT_FALSE(Has(flags, Regexp::LikePerl)); // not added when posix_syntax is true
}

// Each toggle independently adds its corresponding flag when posix_syntax = true
// (to avoid incidental bits from LikePerl).
TEST(RE2OptionsParseFlagsTest_242, LiteralTrueSetsLiteral_242) {
  RE2::Options opt;
  opt.set_posix_syntax(true);
  opt.set_literal(true);
  const int flags = opt.ParseFlags();
  EXPECT_TRUE(Has(flags, Regexp::ClassNL));
  EXPECT_TRUE(Has(flags, Regexp::Literal));
}

TEST(RE2OptionsParseFlagsTest_242, NeverNLTrueSetsNeverNL_242) {
  RE2::Options opt;
  opt.set_posix_syntax(true);
  opt.set_never_nl(true);
  const int flags = opt.ParseFlags();
  EXPECT_TRUE(Has(flags, Regexp::ClassNL));
  EXPECT_TRUE(Has(flags, Regexp::NeverNL));
}

TEST(RE2OptionsParseFlagsTest_242, DotNLTrueSetsDotNL_242) {
  RE2::Options opt;
  opt.set_posix_syntax(true);
  opt.set_dot_nl(true);
  const int flags = opt.ParseFlags();
  EXPECT_TRUE(Has(flags, Regexp::ClassNL));
  EXPECT_TRUE(Has(flags, Regexp::DotNL));
}

TEST(RE2OptionsParseFlagsTest_242, NeverCaptureTrueSetsNeverCapture_242) {
  RE2::Options opt;
  opt.set_posix_syntax(true);
  opt.set_never_capture(true);
  const int flags = opt.ParseFlags();
  EXPECT_TRUE(Has(flags, Regexp::ClassNL));
  EXPECT_TRUE(Has(flags, Regexp::NeverCapture));
}

TEST(RE2OptionsParseFlagsTest_242, CaseInsensitiveSetsFoldCase_242) {
  RE2::Options opt;
  opt.set_posix_syntax(true);
  opt.set_case_sensitive(false);  // request case-insensitive
  const int flags = opt.ParseFlags();
  EXPECT_TRUE(Has(flags, Regexp::ClassNL));
  EXPECT_TRUE(Has(flags, Regexp::FoldCase));
}

TEST(RE2OptionsParseFlagsTest_242, PerlClassesTrueSetsPerlClasses_242) {
  RE2::Options opt;
  opt.set_posix_syntax(true);
  opt.set_perl_classes(true);
  const int flags = opt.ParseFlags();
  EXPECT_TRUE(Has(flags, Regexp::ClassNL));
  EXPECT_TRUE(Has(flags, Regexp::PerlClasses));
}

TEST(RE2OptionsParseFlagsTest_242, WordBoundaryTrueSetsPerlB_242) {
  RE2::Options opt;
  opt.set_posix_syntax(true);
  opt.set_word_boundary(true);
  const int flags = opt.ParseFlags();
  EXPECT_TRUE(Has(flags, Regexp::ClassNL));
  EXPECT_TRUE(Has(flags, Regexp::PerlB));
}

TEST(RE2OptionsParseFlagsTest_242, OneLineTrueSetsOneLine_242) {
  RE2::Options opt;
  opt.set_posix_syntax(true);
  opt.set_one_line(true);
  const int flags = opt.ParseFlags();
  EXPECT_TRUE(Has(flags, Regexp::ClassNL));
  EXPECT_TRUE(Has(flags, Regexp::OneLine));
}

// OneLine is already part of LikePerl; enabling it explicitly shouldn’t change
// the outcome compared to defaults (observable: same flags as default).
TEST(RE2OptionsParseFlagsTest_242, OneLineFlagAlreadyInLikePerl_242) {
  RE2::Options opt_default;
  const int default_flags = opt_default.ParseFlags(); // LikePerl included

  RE2::Options opt_explicit;
  opt_explicit.set_one_line(true); // still !posix_syntax by default
  const int explicit_flags = opt_explicit.ParseFlags();

  EXPECT_EQ(default_flags, explicit_flags);
}

// Multiple independent toggles combine additively (bitwise OR).
TEST(RE2OptionsParseFlagsTest_242, MultipleFlagsCombine_242) {
  RE2::Options opt;
  opt.set_posix_syntax(true);      // keep baseline minimal (no LikePerl)
  opt.set_literal(true);
  opt.set_never_nl(true);
  opt.set_dot_nl(true);
  opt.set_case_sensitive(false);
  const int flags = opt.ParseFlags();

  EXPECT_TRUE(Has(flags, Regexp::ClassNL));
  EXPECT_TRUE(Has(flags, Regexp::Literal));
  EXPECT_TRUE(Has(flags, Regexp::NeverNL));
  EXPECT_TRUE(Has(flags, Regexp::DotNL));
  EXPECT_TRUE(Has(flags, Regexp::FoldCase));
  // And still no unrelated bits:
  EXPECT_FALSE(Has(flags, Regexp::NeverCapture));
  EXPECT_FALSE(Has(flags, Regexp::Latin1));
}
