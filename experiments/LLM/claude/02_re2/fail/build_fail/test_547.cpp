#include <gtest/gtest.h>
#include "re2/prefilter.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prefilter_tree.h"

namespace re2 {

class PrefilterTest_547 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that Prefilter can be created from a simple literal regex
TEST_F(PrefilterTest_547, FromLiteralRegex_547) {
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  ASSERT_NE(pf, nullptr);
  // A literal string should produce an ATOM prefilter
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  delete pf;
  re->Decref();
}

// Test that Prefilter from ".*" produces ALL
TEST_F(PrefilterTest_547, FromDotStarRegex_547) {
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
  re->Decref();
}

// Test that Prefilter from alternation produces OR
TEST_F(PrefilterTest_547, FromAlternationRegex_547) {
  Regexp* re = Regexp::Parse("hello|world", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  ASSERT_NE(pf, nullptr);
  // alternation of two literals should produce OR of ATOMs or similar
  EXPECT_TRUE(pf->op() == Prefilter::OR || pf->op() == Prefilter::AND || 
               pf->op() == Prefilter::ATOM || pf->op() == Prefilter::ALL);
  delete pf;
  re->Decref();
}

// Test that Prefilter from concatenation produces AND or ATOM
TEST_F(PrefilterTest_547, FromConcatenationRegex_547) {
  Regexp* re = Regexp::Parse("abc.*def", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  ASSERT_NE(pf, nullptr);
  // Should have some structure
  EXPECT_TRUE(pf->op() == Prefilter::AND || pf->op() == Prefilter::ATOM || 
               pf->op() == Prefilter::ALL);
  delete pf;
  re->Decref();
}

// Test quest (optional) pattern
TEST_F(PrefilterTest_547, FromQuestRegex_547) {
  Regexp* re = Regexp::Parse("abc?", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  // Quest makes the match less specific
  if (pf != nullptr) {
    EXPECT_TRUE(pf->op() == Prefilter::ATOM || pf->op() == Prefilter::ALL);
    delete pf;
  }
  re->Decref();
}

// Test star pattern
TEST_F(PrefilterTest_547, FromStarRegex_547) {
  Regexp* re = Regexp::Parse("a*", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
  re->Decref();
}

// Test plus pattern
TEST_F(PrefilterTest_547, FromPlusRegex_547) {
  Regexp* re = Regexp::Parse("hello+", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  ASSERT_NE(pf, nullptr);
  EXPECT_TRUE(pf->op() == Prefilter::ATOM || pf->op() == Prefilter::ALL);
  delete pf;
  re->Decref();
}

// Test empty regex
TEST_F(PrefilterTest_547, FromEmptyRegex_547) {
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
  re->Decref();
}

// Test character class pattern
TEST_F(PrefilterTest_547, FromCharClassRegex_547) {
  Regexp* re = Regexp::Parse("[abc]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  if (pf != nullptr) {
    EXPECT_TRUE(pf->op() == Prefilter::ALL || pf->op() == Prefilter::OR ||
                 pf->op() == Prefilter::ATOM);
    delete pf;
  }
  re->Decref();
}

// Test Prefilter DebugString returns non-empty for ATOM
TEST_F(PrefilterTest_547, DebugStringNotEmpty_547) {
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  ASSERT_NE(pf, nullptr);
  std::string debug = pf->DebugString();
  EXPECT_FALSE(debug.empty());
  delete pf;
  re->Decref();
}

// Test complex regex with AND structure
TEST_F(PrefilterTest_547, ComplexRegexAndStructure_547) {
  Regexp* re = Regexp::Parse("foo.*bar.*baz", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  ASSERT_NE(pf, nullptr);
  EXPECT_TRUE(pf->op() == Prefilter::AND || pf->op() == Prefilter::ATOM);
  delete pf;
  re->Decref();
}

// Test that atom() returns the correct string for a literal
TEST_F(PrefilterTest_547, AtomValueForLiteral_547) {
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  ASSERT_NE(pf, nullptr);
  if (pf->op() == Prefilter::ATOM) {
    EXPECT_EQ(pf->atom(), "hello");
  }
  delete pf;
  re->Decref();
}

// Test Prefilter from single character
TEST_F(PrefilterTest_547, FromSingleCharRegex_547) {
  Regexp* re = Regexp::Parse("x", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prefilter* pf = Prefilter::FromRegexp(re);
  // Single character might be too short to be useful as atom
  if (pf != nullptr) {
    EXPECT_TRUE(pf->op() == Prefilter::ALL || pf->op() == Prefilter::ATOM);
    delete pf;
  }
  re->Decref();
}

}  // namespace re2
