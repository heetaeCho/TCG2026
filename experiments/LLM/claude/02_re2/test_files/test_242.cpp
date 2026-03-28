#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"

namespace re2 {

class RE2OptionsParseFlags_242 : public ::testing::Test {
 protected:
  RE2::Options options_;
};

// Test default options produce expected flags
TEST_F(RE2OptionsParseFlags_242, DefaultOptionsProduceExpectedFlags_242) {
  // Default: encoding=UTF8, posix_syntax=false, literal=false, never_nl=false,
  // dot_nl=false, never_capture=false, case_sensitive=true, perl_classes=false,
  // word_boundary=false, one_line=false
  int flags = options_.ParseFlags();
  
  // ClassNL should always be set
  EXPECT_TRUE(flags & Regexp::ClassNL);
  
  // LikePerl should be set because posix_syntax is false by default
  EXPECT_TRUE(flags & Regexp::LikePerl);
  
  // Literal should NOT be set
  EXPECT_FALSE(flags & Regexp::Literal);
  
  // NeverNL should NOT be set
  EXPECT_FALSE(flags & Regexp::NeverNL);
  
  // DotNL should NOT be set
  EXPECT_FALSE(flags & Regexp::DotNL);
  
  // NeverCapture should NOT be set
  EXPECT_FALSE(flags & Regexp::NeverCapture);
  
  // FoldCase should NOT be set (case_sensitive is true by default)
  EXPECT_FALSE(flags & Regexp::FoldCase);
  
  // PerlClasses should NOT be set
  EXPECT_FALSE(flags & Regexp::PerlClasses);
  
  // PerlB should NOT be set
  EXPECT_FALSE(flags & Regexp::PerlB);
  
  // OneLine should NOT be set
  EXPECT_FALSE(flags & Regexp::OneLine);
  
  // Latin1 should NOT be set (encoding is UTF8)
  EXPECT_FALSE(flags & Regexp::Latin1);
}

// Test Latin1 encoding sets Latin1 flag
TEST_F(RE2OptionsParseFlags_242, Latin1EncodingSetsLatin1Flag_242) {
  options_.set_encoding(RE2::Options::EncodingLatin1);
  int flags = options_.ParseFlags();
  EXPECT_TRUE(flags & Regexp::Latin1);
}

// Test UTF8 encoding does not set Latin1 flag
TEST_F(RE2OptionsParseFlags_242, UTF8EncodingDoesNotSetLatin1Flag_242) {
  options_.set_encoding(RE2::Options::EncodingUTF8);
  int flags = options_.ParseFlags();
  EXPECT_FALSE(flags & Regexp::Latin1);
}

// Test posix_syntax true removes LikePerl flag
TEST_F(RE2OptionsParseFlags_242, PosixSyntaxRemovesLikePerlFlag_242) {
  options_.set_posix_syntax(true);
  int flags = options_.ParseFlags();
  EXPECT_FALSE(flags & Regexp::LikePerl);
}

// Test posix_syntax false sets LikePerl flag
TEST_F(RE2OptionsParseFlags_242, NonPosixSyntaxSetsLikePerlFlag_242) {
  options_.set_posix_syntax(false);
  int flags = options_.ParseFlags();
  EXPECT_TRUE(flags & Regexp::LikePerl);
}

// Test literal flag
TEST_F(RE2OptionsParseFlags_242, LiteralSetsLiteralFlag_242) {
  options_.set_literal(true);
  int flags = options_.ParseFlags();
  EXPECT_TRUE(flags & Regexp::Literal);
}

// Test literal false does not set literal flag
TEST_F(RE2OptionsParseFlags_242, NonLiteralDoesNotSetLiteralFlag_242) {
  options_.set_literal(false);
  int flags = options_.ParseFlags();
  EXPECT_FALSE(flags & Regexp::Literal);
}

// Test never_nl flag
TEST_F(RE2OptionsParseFlags_242, NeverNLSetsNeverNLFlag_242) {
  options_.set_never_nl(true);
  int flags = options_.ParseFlags();
  EXPECT_TRUE(flags & Regexp::NeverNL);
}

// Test never_nl false
TEST_F(RE2OptionsParseFlags_242, NonNeverNLDoesNotSetNeverNLFlag_242) {
  options_.set_never_nl(false);
  int flags = options_.ParseFlags();
  EXPECT_FALSE(flags & Regexp::NeverNL);
}

// Test dot_nl flag
TEST_F(RE2OptionsParseFlags_242, DotNLSetsDotNLFlag_242) {
  options_.set_dot_nl(true);
  int flags = options_.ParseFlags();
  EXPECT_TRUE(flags & Regexp::DotNL);
}

// Test dot_nl false
TEST_F(RE2OptionsParseFlags_242, NonDotNLDoesNotSetDotNLFlag_242) {
  options_.set_dot_nl(false);
  int flags = options_.ParseFlags();
  EXPECT_FALSE(flags & Regexp::DotNL);
}

// Test never_capture flag
TEST_F(RE2OptionsParseFlags_242, NeverCaptureSetsNeverCaptureFlag_242) {
  options_.set_never_capture(true);
  int flags = options_.ParseFlags();
  EXPECT_TRUE(flags & Regexp::NeverCapture);
}

// Test never_capture false
TEST_F(RE2OptionsParseFlags_242, NonNeverCaptureDoesNotSetNeverCaptureFlag_242) {
  options_.set_never_capture(false);
  int flags = options_.ParseFlags();
  EXPECT_FALSE(flags & Regexp::NeverCapture);
}

// Test case_sensitive false sets FoldCase
TEST_F(RE2OptionsParseFlags_242, CaseInsensitiveSetsFoldCaseFlag_242) {
  options_.set_case_sensitive(false);
  int flags = options_.ParseFlags();
  EXPECT_TRUE(flags & Regexp::FoldCase);
}

// Test case_sensitive true does not set FoldCase
TEST_F(RE2OptionsParseFlags_242, CaseSensitiveDoesNotSetFoldCaseFlag_242) {
  options_.set_case_sensitive(true);
  int flags = options_.ParseFlags();
  EXPECT_FALSE(flags & Regexp::FoldCase);
}

// Test perl_classes flag
TEST_F(RE2OptionsParseFlags_242, PerlClassesSetsPerlClassesFlag_242) {
  options_.set_perl_classes(true);
  int flags = options_.ParseFlags();
  EXPECT_TRUE(flags & Regexp::PerlClasses);
}

// Test perl_classes false
TEST_F(RE2OptionsParseFlags_242, NonPerlClassesDoesNotSetPerlClassesFlag_242) {
  options_.set_perl_classes(false);
  int flags = options_.ParseFlags();
  EXPECT_FALSE(flags & Regexp::PerlClasses);
}

// Test word_boundary flag
TEST_F(RE2OptionsParseFlags_242, WordBoundarySetsPerlBFlag_242) {
  options_.set_word_boundary(true);
  int flags = options_.ParseFlags();
  EXPECT_TRUE(flags & Regexp::PerlB);
}

// Test word_boundary false
TEST_F(RE2OptionsParseFlags_242, NonWordBoundaryDoesNotSetPerlBFlag_242) {
  options_.set_word_boundary(false);
  int flags = options_.ParseFlags();
  EXPECT_FALSE(flags & Regexp::PerlB);
}

// Test one_line flag
TEST_F(RE2OptionsParseFlags_242, OneLineSetsOneLineFlag_242) {
  options_.set_one_line(true);
  int flags = options_.ParseFlags();
  EXPECT_TRUE(flags & Regexp::OneLine);
}

// Test one_line false
TEST_F(RE2OptionsParseFlags_242, NonOneLineDoesNotSetOneLineFlag_242) {
  options_.set_one_line(false);
  int flags = options_.ParseFlags();
  EXPECT_FALSE(flags & Regexp::OneLine);
}

// Test ClassNL is always set
TEST_F(RE2OptionsParseFlags_242, ClassNLAlwaysSet_242) {
  int flags = options_.ParseFlags();
  EXPECT_TRUE(flags & Regexp::ClassNL);
}

// Test all flags enabled together
TEST_F(RE2OptionsParseFlags_242, AllFlagsEnabled_242) {
  options_.set_encoding(RE2::Options::EncodingLatin1);
  options_.set_posix_syntax(false);  // LikePerl
  options_.set_literal(true);
  options_.set_never_nl(true);
  options_.set_dot_nl(true);
  options_.set_never_capture(true);
  options_.set_case_sensitive(false);  // FoldCase
  options_.set_perl_classes(true);
  options_.set_word_boundary(true);
  options_.set_one_line(true);
  
  int flags = options_.ParseFlags();
  
  EXPECT_TRUE(flags & Regexp::ClassNL);
  EXPECT_TRUE(flags & Regexp::Latin1);
  EXPECT_TRUE(flags & Regexp::LikePerl);
  EXPECT_TRUE(flags & Regexp::Literal);
  EXPECT_TRUE(flags & Regexp::NeverNL);
  EXPECT_TRUE(flags & Regexp::DotNL);
  EXPECT_TRUE(flags & Regexp::NeverCapture);
  EXPECT_TRUE(flags & Regexp::FoldCase);
  EXPECT_TRUE(flags & Regexp::PerlClasses);
  EXPECT_TRUE(flags & Regexp::PerlB);
  EXPECT_TRUE(flags & Regexp::OneLine);
}

// Test with POSIX canned option
TEST_F(RE2OptionsParseFlags_242, POSIXCannedOption_242) {
  RE2::Options posix_opts(RE2::POSIX);
  int flags = posix_opts.ParseFlags();
  
  // POSIX sets posix_syntax=true, so LikePerl should NOT be set
  EXPECT_FALSE(flags & Regexp::LikePerl);
  EXPECT_TRUE(flags & Regexp::ClassNL);
}

// Test with Latin1 canned option
TEST_F(RE2OptionsParseFlags_242, Latin1CannedOption_242) {
  RE2::Options latin1_opts(RE2::Latin1);
  int flags = latin1_opts.ParseFlags();
  
  EXPECT_TRUE(flags & Regexp::Latin1);
  EXPECT_TRUE(flags & Regexp::ClassNL);
  // Latin1 canned option does not set posix_syntax, so LikePerl should be set
  EXPECT_TRUE(flags & Regexp::LikePerl);
}

// Test with Quiet canned option
TEST_F(RE2OptionsParseFlags_242, QuietCannedOption_242) {
  RE2::Options quiet_opts(RE2::Quiet);
  int flags = quiet_opts.ParseFlags();
  
  // Quiet does not change encoding from UTF8
  EXPECT_FALSE(flags & Regexp::Latin1);
  EXPECT_TRUE(flags & Regexp::ClassNL);
  // Quiet does not set posix_syntax, so LikePerl should be set
  EXPECT_TRUE(flags & Regexp::LikePerl);
}

// Test combination: posix_syntax + Latin1
TEST_F(RE2OptionsParseFlags_242, PosixWithLatin1Encoding_242) {
  options_.set_posix_syntax(true);
  options_.set_encoding(RE2::Options::EncodingLatin1);
  int flags = options_.ParseFlags();
  
  EXPECT_TRUE(flags & Regexp::ClassNL);
  EXPECT_TRUE(flags & Regexp::Latin1);
  EXPECT_FALSE(flags & Regexp::LikePerl);
}

// Test combination: literal + never_capture
TEST_F(RE2OptionsParseFlags_242, LiteralWithNeverCapture_242) {
  options_.set_literal(true);
  options_.set_never_capture(true);
  int flags = options_.ParseFlags();
  
  EXPECT_TRUE(flags & Regexp::Literal);
  EXPECT_TRUE(flags & Regexp::NeverCapture);
}

// Test that toggling options works correctly
TEST_F(RE2OptionsParseFlags_242, TogglingOptionWorks_242) {
  options_.set_dot_nl(true);
  EXPECT_TRUE(options_.ParseFlags() & Regexp::DotNL);
  
  options_.set_dot_nl(false);
  EXPECT_FALSE(options_.ParseFlags() & Regexp::DotNL);
}

// Test minimal flags: posix_syntax true, everything else default
TEST_F(RE2OptionsParseFlags_242, MinimalFlagsWithPosixSyntax_242) {
  options_.set_posix_syntax(true);
  int flags = options_.ParseFlags();
  
  // Only ClassNL should be set from the base, LikePerl should NOT be set
  EXPECT_TRUE(flags & Regexp::ClassNL);
  EXPECT_FALSE(flags & Regexp::LikePerl);
  EXPECT_FALSE(flags & Regexp::Literal);
  EXPECT_FALSE(flags & Regexp::NeverNL);
  EXPECT_FALSE(flags & Regexp::DotNL);
  EXPECT_FALSE(flags & Regexp::NeverCapture);
  EXPECT_FALSE(flags & Regexp::FoldCase);
  EXPECT_FALSE(flags & Regexp::PerlClasses);
  EXPECT_FALSE(flags & Regexp::PerlB);
  EXPECT_FALSE(flags & Regexp::OneLine);
  EXPECT_FALSE(flags & Regexp::Latin1);
}

// Test Copy method preserves flags
TEST_F(RE2OptionsParseFlags_242, CopyPreservesParseFlags_242) {
  options_.set_literal(true);
  options_.set_dot_nl(true);
  options_.set_never_capture(true);
  
  RE2::Options copied;
  copied.Copy(options_);
  
  EXPECT_EQ(options_.ParseFlags(), copied.ParseFlags());
}

}  // namespace re2
