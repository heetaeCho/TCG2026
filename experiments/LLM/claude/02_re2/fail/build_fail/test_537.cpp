#include "gtest/gtest.h"
#include "re2/prefilter.h"
#include "re2/re2.h"
#include "util/utf.h"

// We need access to ToLowerRune which is a static function in prefilter.cc
// Since it's static, we can't directly test it from outside the translation unit.
// However, we can test it indirectly through the Prefilter interface, or we
// can include the source file to access the static function for testing purposes.

// Since ToLowerRune is static in prefilter.cc, we need to test it indirectly.
// We'll test through Prefilter's behavior which uses ToLowerRune internally.
// Prefilter is used when compiling regexps with case-insensitive flags.

namespace re2 {

// We can test ToLowerRune indirectly by examining Prefilter atoms generated
// from case-insensitive patterns, or we can use a workaround to access the
// static function. Let's test via the Prefilter public interface.

class PrefilterTest_537 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a simple literal pattern produces a Prefilter
TEST_F(PrefilterTest_537, SimpleLiteralPattern_537) {
  Regexp::ParseFlags flags = Regexp::LikePerl;
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", flags, &status);
  ASSERT_NE(re, nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  // A simple literal should produce a non-null prefilter
  EXPECT_NE(pf, nullptr);
  
  delete pf;
  re->Decref();
}

// Test that case-insensitive pattern produces a Prefilter (exercises ToLowerRune for ASCII)
TEST_F(PrefilterTest_537, CaseInsensitiveASCII_537) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::LikePerl | Regexp::FoldCase);
  RegexpStatus status;
  Regexp* re = Regexp::Parse("HELLO", flags, &status);
  ASSERT_NE(re, nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  // Case insensitive literal should still produce a prefilter
  // The atoms should be lowercased due to ToLowerRune
  EXPECT_NE(pf, nullptr);
  
  delete pf;
  re->Decref();
}

// Test with lowercase ASCII letters (ToLowerRune should leave them unchanged)
TEST_F(PrefilterTest_537, LowercaseASCII_537) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::LikePerl | Regexp::FoldCase);
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", flags, &status);
  ASSERT_NE(re, nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  EXPECT_NE(pf, nullptr);
  
  delete pf;
  re->Decref();
}

// Test empty pattern
TEST_F(PrefilterTest_537, EmptyPattern_537) {
  Regexp::ParseFlags flags = Regexp::LikePerl;
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", flags, &status);
  ASSERT_NE(re, nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  // Empty pattern may or may not produce a prefilter
  // Just verify no crash
  delete pf;
  re->Decref();
}

// Test alternation pattern
TEST_F(PrefilterTest_537, AlternationPattern_537) {
  Regexp::ParseFlags flags = Regexp::LikePerl;
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello|world", flags, &status);
  ASSERT_NE(re, nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  EXPECT_NE(pf, nullptr);
  
  if (pf != nullptr) {
    // Alternation should produce an OR node
    EXPECT_EQ(pf->op(), Prefilter::OR);
  }
  
  delete pf;
  re->Decref();
}

// Test pattern with Unicode characters (exercises ToLowerRune for non-ASCII)
TEST_F(PrefilterTest_537, UnicodePattern_537) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::LikePerl | Regexp::FoldCase);
  RegexpStatus status;
  // Use a pattern with Unicode uppercase letters
  Regexp* re = Regexp::Parse("ÄHELLO", flags, &status);
  ASSERT_NE(re, nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  // Just verify no crash with Unicode
  delete pf;
  re->Decref();
}

// Test concatenation of literals
TEST_F(PrefilterTest_537, ConcatenationPattern_537) {
  Regexp::ParseFlags flags = Regexp::LikePerl;
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc.*def", flags, &status);
  ASSERT_NE(re, nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  EXPECT_NE(pf, nullptr);
  
  if (pf != nullptr) {
    // Should be AND of the two literal parts
    EXPECT_EQ(pf->op(), Prefilter::AND);
  }
  
  delete pf;
  re->Decref();
}

// Test dot-star pattern (should match everything)
TEST_F(PrefilterTest_537, DotStarPattern_537) {
  Regexp::ParseFlags flags = Regexp::LikePerl;
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*", flags, &status);
  ASSERT_NE(re, nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  // .* matches everything, prefilter should be ALL or null
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
  }
  
  delete pf;
  re->Decref();
}

// Test single character pattern
TEST_F(PrefilterTest_537, SingleCharPattern_537) {
  Regexp::ParseFlags flags = Regexp::LikePerl;
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", flags, &status);
  ASSERT_NE(re, nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  // Single char may not produce meaningful prefilter (too short)
  // Just verify no crash
  delete pf;
  re->Decref();
}

// Test Prefilter debug string
TEST_F(PrefilterTest_537, DebugString_537) {
  Regexp::ParseFlags flags = Regexp::LikePerl;
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", flags, &status);
  ASSERT_NE(re, nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  ASSERT_NE(pf, nullptr);
  
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  
  delete pf;
  re->Decref();
}

// Test mixed case ASCII with FoldCase (ToLowerRune boundary: 'A' and 'Z')
TEST_F(PrefilterTest_537, BoundaryASCIIUppercase_537) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::LikePerl | Regexp::FoldCase);
  RegexpStatus status;
  // 'A' and 'Z' are boundary uppercase ASCII chars
  Regexp* re = Regexp::Parse("AZZAA", flags, &status);
  ASSERT_NE(re, nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  EXPECT_NE(pf, nullptr);
  
  delete pf;
  re->Decref();
}

// Test non-alphabetic ASCII (below Runeself, not in A-Z range)
TEST_F(PrefilterTest_537, NonAlphaASCII_537) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::LikePerl | Regexp::FoldCase);
  RegexpStatus status;
  // Digits and punctuation should pass through ToLowerRune unchanged
  Regexp* re = Regexp::Parse("12345", flags, &status);
  ASSERT_NE(re, nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  // Just verify no crash
  delete pf;
  re->Decref();
}

// Test character class pattern
TEST_F(PrefilterTest_537, CharClassPattern_537) {
  Regexp::ParseFlags flags = Regexp::LikePerl;
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[abc]def", flags, &status);
  ASSERT_NE(re, nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  // Should produce some prefilter
  // Just verify no crash
  delete pf;
  re->Decref();
}

// Test Prefilter with characters at Runeself boundary (127 and 128)
TEST_F(PrefilterTest_537, RuneselfBoundary_537) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(
      Regexp::LikePerl | Regexp::FoldCase);
  RegexpStatus status;
  // Character 127 (DEL) is < Runeself, not in A-Z so unchanged
  // Character 128 is >= Runeself, goes to Unicode fold path
  Regexp* re = Regexp::Parse("test\\x7f", flags, &status);
  ASSERT_NE(re, nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  delete pf;
  re->Decref();
}

}  // namespace re2
