#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

// Test basic parsing of simple patterns
TEST(RegexpParseTest_497, ParseSimpleLiteral_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseTest_497, ParseEmptyString_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseTest_497, ParseInvalidRegexp_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

TEST(RegexpParseTest_497, ParseUnmatchedParen_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc", Regexp::LikePerl, &status);
  EXPECT_EQ(re, nullptr);
  EXPECT_FALSE(status.ok());
}

// Test repetition patterns
TEST(RegexpParseTest_497, ParseSimpleRepetition_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{2,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseTest_497, ParseStarRepetition_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseTest_497, ParsePlusRepetition_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseTest_497, ParseQuestRepetition_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test nested repetitions - these are typically rejected
TEST(RegexpParseTest_497, ParseNestedRepetition_497) {
  RegexpStatus status;
  // Nested repetitions like (a*)* should still parse in LikePerl mode
  Regexp* re = Regexp::Parse("(a*)*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test capturing groups
TEST(RegexpParseTest_497, ParseCapturingGroup_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->NumCaptures(), 2);
  re->Decref();
}

TEST(RegexpParseTest_497, ParseNamedCapture_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<name>abc)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->NumCaptures(), 1);
  auto* named = re->NamedCaptures();
  ASSERT_NE(named, nullptr);
  EXPECT_EQ(named->count("name"), 1);
  delete named;
  re->Decref();
}

// Test alternation
TEST(RegexpParseTest_497, ParseAlternation_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a|b|c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test character classes
TEST(RegexpParseTest_497, ParseCharClass_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[abc]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

TEST(RegexpParseTest_497, ParseNegatedCharClass_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[^abc]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test ToString roundtrip
TEST(RegexpParseTest_497, ToStringSimple_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string s = re->ToString();
  EXPECT_FALSE(s.empty());
  re->Decref();
}

// Test Simplify
TEST(RegexpParseTest_497, SimplifyBasic_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* simplified = re->Simplify();
  ASSERT_NE(simplified, nullptr);
  simplified->Decref();
  re->Decref();
}

// Test SimplifyRegexp static method
TEST(RegexpParseTest_497, SimplifyRegexpStatic_497) {
  std::string dst;
  RegexpStatus status;
  bool ok = Regexp::SimplifyRegexp("a{2,5}", Regexp::LikePerl, &dst, &status);
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dst.empty());
}

// Test NumCaptures
TEST(RegexpParseTest_497, NumCapturesZero_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

TEST(RegexpParseTest_497, NumCapturesMultiple_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)(c)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_EQ(re->NumCaptures(), 3);
  re->Decref();
}

// Test CaptureNames
TEST(RegexpParseTest_497, CaptureNamesWithNamedGroups_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?P<first>a)(?P<second>b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  auto* names = re->CaptureNames();
  ASSERT_NE(names, nullptr);
  EXPECT_EQ(names->size(), 2u);
  EXPECT_EQ((*names)[1], "first");
  EXPECT_EQ((*names)[2], "second");
  delete names;
  re->Decref();
}

// Test reference counting
TEST(RegexpParseTest_497, IncrefDecref_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Regexp* re2 = re->Incref();
  EXPECT_EQ(re, re2);
  re->Decref();
  re2->Decref();
}

// Test Dump
TEST(RegexpParseTest_497, DumpBasic_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string dump = re->Dump();
  EXPECT_FALSE(dump.empty());
  re->Decref();
}

// Test RequiredPrefix
TEST(RegexpParseTest_497, RequiredPrefixWithLiteral_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc.*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (has_prefix) {
    EXPECT_FALSE(prefix.empty());
    if (suffix != nullptr) {
      suffix->Decref();
    }
  }
  re->Decref();
}

TEST(RegexpParseTest_497, RequiredPrefixNoPrefix_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;
  bool has_prefix = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(has_prefix);
  re->Decref();
}

// Test complex patterns with large repetitions
TEST(RegexpParseTest_497, ParseLargeRepetition_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{1,1000}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test anchored patterns
TEST(RegexpParseTest_497, ParseAnchoredPattern_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test dot
TEST(RegexpParseTest_497, ParseDotAll_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test escape sequences
TEST(RegexpParseTest_497, ParseEscapeSequences_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\d+\\s+\\w+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test non-capturing group
TEST(RegexpParseTest_497, ParseNonCapturingGroup_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?:abc)+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->NumCaptures(), 0);
  re->Decref();
}

// Test POSIX flags
TEST(RegexpParseTest_497, ParseWithPOSIXFlags_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test CompileToProg
TEST(RegexpParseTest_497, CompileToProgBasic_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test CompileToReverseProg
TEST(RegexpParseTest_497, CompileToReverseProgBasic_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToReverseProg(0);
  ASSERT_NE(prog, nullptr);
  delete prog;
  re->Decref();
}

// Test static factory methods through Parse
TEST(RegexpParseTest_497, ParseCharClassRange_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z0-9]", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test deeply nested groups
TEST(RegexpParseTest_497, ParseDeeplyNested_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((((a))))", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  EXPECT_EQ(re->NumCaptures(), 4);
  re->Decref();
}

// Test bad repetition syntax
TEST(RegexpParseTest_497, ParseBadRepetition_497) {
  RegexpStatus status;
  // In POSIX mode, bad repetitions might cause errors
  Regexp* re = Regexp::Parse("*abc", Regexp::LikePerl, &status);
  // In Perl mode, leading * might be treated as literal or error
  if (re != nullptr) {
    re->Decref();
  }
}

// Test MimicsPCRE
TEST(RegexpParseTest_497, MimicsPCRESimple_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  // Simple patterns should mimic PCRE
  bool mimics = re->MimicsPCRE();
  EXPECT_TRUE(mimics);
  re->Decref();
}

// Test NullWalk doesn't crash
TEST(RegexpParseTest_497, NullWalkNoCrash_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a(b|c)*d", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  re->NullWalk();  // Should not crash
  re->Decref();
}

// Test patterns with Unicode
TEST(RegexpParseTest_497, ParseUnicodePattern_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\p{L}+", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test exact repetition
TEST(RegexpParseTest_497, ParseExactRepetition_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test zero or more repetition with min=0
TEST(RegexpParseTest_497, ParseZeroMinRepetition_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{0,5}", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  EXPECT_TRUE(status.ok());
  re->Decref();
}

// Test RequiredPrefixForAccel
TEST(RegexpParseTest_497, RequiredPrefixForAccelBasic_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^hello.*world", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  std::string prefix;
  bool foldcase = false;
  bool has = re->RequiredPrefixForAccel(&prefix, &foldcase);
  // We just verify it doesn't crash and returns a valid result
  if (has) {
    EXPECT_FALSE(prefix.empty());
  }
  re->Decref();
}

// Test NamedCaptures with no named groups
TEST(RegexpParseTest_497, NamedCapturesNone_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(a)(b)", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  auto* named = re->NamedCaptures();
  // Should be null when there are no named captures
  EXPECT_EQ(named, nullptr);
  delete named;
  re->Decref();
}

// Test CaptureNames with no captures
TEST(RegexpParseTest_497, CaptureNamesNone_497) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);
  auto* names = re->CaptureNames();
  // May return null or empty map
  if (names != nullptr) {
    EXPECT_TRUE(names->empty());
    delete names;
  }
  re->Decref();
}

}  // namespace re2
