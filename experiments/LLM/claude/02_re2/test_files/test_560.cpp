#include "re2/prefilter.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prefilter_tree.h"
#include "gtest/gtest.h"
#include <string>
#include <vector>
#include <memory>

namespace re2 {

class PrefilterTest_560 : public ::testing::Test {
 protected:
  void TearDown() override {}
};

// Test that FromRegexp returns a non-null Prefilter for a simple literal pattern
TEST_F(PrefilterTest_560, SimpleLiteralPrefilter_560) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  EXPECT_NE(pf, nullptr);
  
  delete pf;
  re->Decref();
}

// Test that FromRegexp returns a Prefilter for alternation patterns
TEST_F(PrefilterTest_560, AlternationPrefilter_560) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello|world", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  EXPECT_NE(pf, nullptr);
  
  delete pf;
  re->Decref();
}

// Test that FromRegexp handles dot-star (any match) patterns
TEST_F(PrefilterTest_560, DotStarPrefilter_560) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  // .* matches everything, so prefilter might be an ALL match or null
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
  re->Decref();
}

// Test that FromRegexp handles concatenation patterns
TEST_F(PrefilterTest_560, ConcatenationPrefilter_560) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc.*def", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  EXPECT_NE(pf, nullptr);
  
  delete pf;
  re->Decref();
}

// Test that FromRegexp handles character class patterns
TEST_F(PrefilterTest_560, CharClassPrefilter_560) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[abc]def", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  EXPECT_NE(pf, nullptr);
  
  delete pf;
  re->Decref();
}

// Test that FromRegexp handles question mark (optional) patterns
TEST_F(PrefilterTest_560, QuestPrefilter_560) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc?def", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  EXPECT_NE(pf, nullptr);
  
  delete pf;
  re->Decref();
}

// Test that FromRegexp handles plus (one or more) patterns
TEST_F(PrefilterTest_560, PlusPrefilter_560) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("ab+c", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  EXPECT_NE(pf, nullptr);
  
  delete pf;
  re->Decref();
}

// Test that FromRegexp handles star (zero or more) patterns
TEST_F(PrefilterTest_560, StarPrefilter_560) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("ab*c", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  EXPECT_NE(pf, nullptr);
  
  delete pf;
  re->Decref();
}

// Test that FromRegexp handles empty string pattern
TEST_F(PrefilterTest_560, EmptyStringPrefilter_560) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  // Empty string - prefilter might be ALL or null
  if (pf != nullptr) {
    delete pf;
  }
  re->Decref();
}

// Test that FromRegexp handles single character pattern
TEST_F(PrefilterTest_560, SingleCharPrefilter_560) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  // Single char may or may not produce a useful prefilter
  if (pf != nullptr) {
    delete pf;
  }
  re->Decref();
}

// Test Prefilter DebugString returns non-empty for valid prefilter
TEST_F(PrefilterTest_560, DebugStringNonEmpty_560) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  ASSERT_NE(pf, nullptr);
  
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  
  delete pf;
  re->Decref();
}

// Test Prefilter with complex nested pattern
TEST_F(PrefilterTest_560, ComplexNestedPattern_560) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(foo|bar)(baz|qux)", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  EXPECT_NE(pf, nullptr);
  
  if (pf != nullptr) {
    // For AND of two ORs, we expect a compound prefilter
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
  re->Decref();
}

// Test Prefilter op() for literal returns ATOM
TEST_F(PrefilterTest_560, LiteralOpIsAtom_560) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  
  delete pf;
  re->Decref();
}

// Test Prefilter for alternation returns OR
TEST_F(PrefilterTest_560, AlternationOpIsOr_560) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello|world", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  ASSERT_NE(pf, nullptr);
  // Alternation should produce OR prefilter
  EXPECT_EQ(pf->op(), Prefilter::OR);
  
  delete pf;
  re->Decref();
}

// Test Prefilter atom() returns expected string for literal
TEST_F(PrefilterTest_560, AtomValueForLiteral_560) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  ASSERT_NE(pf, nullptr);
  ASSERT_EQ(pf->op(), Prefilter::ATOM);
  EXPECT_EQ(pf->atom(), "hello");
  
  delete pf;
  re->Decref();
}

// Test Prefilter with case-insensitive Latin1 pattern
TEST_F(PrefilterTest_560, CaseInsensitivePrefilter_560) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?i)hello", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  // Case insensitive may still produce a prefilter
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
  re->Decref();
}

// Test Prefilter with Latin1 encoding
TEST_F(PrefilterTest_560, Latin1Prefilter_560) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("hello", Regexp::Latin1 | Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  EXPECT_NE(pf, nullptr);
  
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ATOM);
    delete pf;
  }
  re->Decref();
}

// Test Prefilter with repeated pattern
TEST_F(PrefilterTest_560, RepeatedPattern_560) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a{3,5}b", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  // Should produce some prefilter containing 'aaa' and 'b' or similar
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
  re->Decref();
}

// Test Prefilter with capture group
TEST_F(PrefilterTest_560, CaptureGroupPrefilter_560) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc)def", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  EXPECT_EQ(pf->atom(), "abcdef");
  
  delete pf;
  re->Decref();
}

// Test Prefilter with dot (any character)
TEST_F(PrefilterTest_560, DotPrefilter_560) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a.b", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  // a.b - the dot breaks the atom, so AND of atoms or similar
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
  re->Decref();
}

// Test FromRE2 convenience function
TEST_F(PrefilterTest_560, FromRE2_560) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  
  Prefilter* pf = Prefilter::FromRE2(&re);
  EXPECT_NE(pf, nullptr);
  
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ATOM);
    EXPECT_EQ(pf->atom(), "hello");
    delete pf;
  }
}

// Test Prefilter subs() for compound prefilter
TEST_F(PrefilterTest_560, SubsForOrPrefilter_560) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("foo|bar|baz", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  ASSERT_NE(pf, nullptr);
  ASSERT_EQ(pf->op(), Prefilter::OR);
  
  const std::vector<Prefilter*>* subs = pf->subs();
  ASSERT_NE(subs, nullptr);
  EXPECT_EQ(static_cast<int>(subs->size()), 3);
  
  delete pf;
  re->Decref();
}

// Test Prefilter with anchored pattern
TEST_F(PrefilterTest_560, AnchoredPrefilter_560) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^hello$", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  EXPECT_NE(pf, nullptr);
  
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ATOM);
    EXPECT_EQ(pf->atom(), "hello");
    delete pf;
  }
  re->Decref();
}

// Test Prefilter with Unicode pattern
TEST_F(PrefilterTest_560, UnicodePrefilter_560) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("café", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  EXPECT_NE(pf, nullptr);
  
  if (pf != nullptr) {
    std::string debug = pf->DebugString();
    EXPECT_FALSE(debug.empty());
    delete pf;
  }
  re->Decref();
}

// Test Prefilter with word boundary
TEST_F(PrefilterTest_560, WordBoundaryPrefilter_560) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("\\bhello\\b", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);
  
  Prefilter* pf = Prefilter::FromRegexp(re);
  EXPECT_NE(pf, nullptr);
  
  if (pf != nullptr) {
    delete pf;
  }
  re->Decref();
}

// Test ALL prefilter construction
TEST_F(PrefilterTest_560, AllMatchPrefilter_560) {
  Prefilter* pf = new Prefilter(Prefilter::ALL);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ALL);
  delete pf;
}

// Test NONE prefilter construction
TEST_F(PrefilterTest_560, NoneMatchPrefilter_560) {
  Prefilter* pf = new Prefilter(Prefilter::NONE);
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::NONE);
  delete pf;
}

}  // namespace re2
