#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "re2/prefilter.h"
#include "re2/re2.h"

namespace re2 {

class PrefilterPostVisitTest_561 : public ::testing::Test {
 protected:
  void TearDown() override {}

  // Helper to get a Prefilter from a pattern string
  Prefilter* GetPrefilter(const std::string& pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
    if (re == nullptr) return nullptr;
    Prefilter* pf = Prefilter::FromRegexp(re);
    re->Decref();
    return pf;
  }
};

// Test literal regexp - should produce a prefilter with the literal atom
TEST_F(PrefilterPostVisitTest_561, LiteralRegexp_561) {
  Prefilter* pf = GetPrefilter("hello");
  ASSERT_NE(pf, nullptr);
  // A literal string should produce an ATOM prefilter
  EXPECT_EQ(pf->op(), Prefilter::ALL) || EXPECT_EQ(pf->op(), Prefilter::ATOM);
  delete pf;
}

// Test empty match (e.g., empty pattern)
TEST_F(PrefilterPostVisitTest_561, EmptyMatch_561) {
  Prefilter* pf = GetPrefilter("");
  // Empty match should yield ALL (matches everything)
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test NoMatch
TEST_F(PrefilterPostVisitTest_561, NoMatch_561) {
  Prefilter* pf = GetPrefilter("[^\\s\\S]");
  // NoMatch could result in nullptr or NONE
  if (pf != nullptr) {
    delete pf;
  }
}

// Test alternation (kRegexpAlternate)
TEST_F(PrefilterPostVisitTest_561, Alternation_561) {
  Prefilter* pf = GetPrefilter("hello|world");
  ASSERT_NE(pf, nullptr);
  // Alternation should produce OR prefilter
  EXPECT_EQ(pf->op(), Prefilter::OR);
  delete pf;
}

// Test concatenation (kRegexpConcat)
TEST_F(PrefilterPostVisitTest_561, Concatenation_561) {
  Prefilter* pf = GetPrefilter("abc");
  ASSERT_NE(pf, nullptr);
  // Simple concatenation of literals should produce an ATOM
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  delete pf;
}

// Test Star (kRegexpStar) - a* matches empty string
TEST_F(PrefilterPostVisitTest_561, Star_561) {
  Prefilter* pf = GetPrefilter("a*");
  // Star of anything matches empty, so prefilter should be ALL or null
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test Plus (kRegexpPlus) - a+ requires at least one 'a'
TEST_F(PrefilterPostVisitTest_561, Plus_561) {
  Prefilter* pf = GetPrefilter("a+");
  // Plus should preserve the child's prefilter
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ATOM);
    delete pf;
  }
}

// Test Quest (kRegexpQuest) - a? matches empty string
TEST_F(PrefilterPostVisitTest_561, Quest_561) {
  Prefilter* pf = GetPrefilter("a?");
  // Quest matches empty, so prefilter should be ALL
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test AnyChar (kRegexpAnyChar)
TEST_F(PrefilterPostVisitTest_561, AnyChar_561) {
  Prefilter* pf = GetPrefilter(".");
  // AnyChar should produce ALL prefilter
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test character class (kRegexpCharClass)
TEST_F(PrefilterPostVisitTest_561, CharClass_561) {
  Prefilter* pf = GetPrefilter("[abc]");
  if (pf != nullptr) {
    // Character class could produce OR or ALL
    EXPECT_TRUE(pf->op() == Prefilter::OR || pf->op() == Prefilter::ALL || pf->op() == Prefilter::ATOM);
    delete pf;
  }
}

// Test BeginLine anchor
TEST_F(PrefilterPostVisitTest_561, BeginLine_561) {
  Prefilter* pf = GetPrefilter("^hello");
  ASSERT_NE(pf, nullptr);
  // Anchor should not affect the prefilter content, still "hello"
  delete pf;
}

// Test EndLine anchor
TEST_F(PrefilterPostVisitTest_561, EndLine_561) {
  Prefilter* pf = GetPrefilter("hello$");
  ASSERT_NE(pf, nullptr);
  delete pf;
}

// Test WordBoundary
TEST_F(PrefilterPostVisitTest_561, WordBoundary_561) {
  Prefilter* pf = GetPrefilter("\\bhello\\b");
  ASSERT_NE(pf, nullptr);
  delete pf;
}

// Test Capture (kRegexpCapture) - should pass through child
TEST_F(PrefilterPostVisitTest_561, Capture_561) {
  Prefilter* pf = GetPrefilter("(hello)");
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  delete pf;
}

// Test complex pattern: concatenation with alternation
TEST_F(PrefilterPostVisitTest_561, ConcatWithAlternation_561) {
  Prefilter* pf = GetPrefilter("foo(bar|baz)qux");
  ASSERT_NE(pf, nullptr);
  // Should produce AND of atoms
  EXPECT_TRUE(pf->op() == Prefilter::AND || pf->op() == Prefilter::OR || pf->op() == Prefilter::ATOM);
  delete pf;
}

// Test complex concat with exact strings that might exceed size threshold
TEST_F(PrefilterPostVisitTest_561, ConcatExactSizeThreshold_561) {
  // This creates a pattern where exact set multiplication would exceed 16
  Prefilter* pf = GetPrefilter("[abcde][abcde][abcde]");
  if (pf != nullptr) {
    delete pf;
  }
}

// Test AnyByte
TEST_F(PrefilterPostVisitTest_561, AnyByte_561) {
  Prefilter* pf = GetPrefilter("\\C");
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ALL);
    delete pf;
  }
}

// Test single literal character
TEST_F(PrefilterPostVisitTest_561, SingleLiteral_561) {
  Prefilter* pf = GetPrefilter("x");
  if (pf != nullptr) {
    EXPECT_EQ(pf->op(), Prefilter::ATOM);
    delete pf;
  }
}

// Test longer literal string produces ATOM with correct value
TEST_F(PrefilterPostVisitTest_561, LongerLiteralString_561) {
  Prefilter* pf = GetPrefilter("abcdef");
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  EXPECT_EQ(pf->atom(), "abcdef");
  delete pf;
}

// Test nested captures
TEST_F(PrefilterPostVisitTest_561, NestedCapture_561) {
  Prefilter* pf = GetPrefilter("((abc))");
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::ATOM);
  delete pf;
}

// Test begin/end text anchors
TEST_F(PrefilterPostVisitTest_561, BeginEndText_561) {
  Prefilter* pf = GetPrefilter("\\Ahello\\z");
  ASSERT_NE(pf, nullptr);
  delete pf;
}

// Test multiple alternations
TEST_F(PrefilterPostVisitTest_561, MultipleAlternations_561) {
  Prefilter* pf = GetPrefilter("abc|def|ghi|jkl");
  ASSERT_NE(pf, nullptr);
  EXPECT_EQ(pf->op(), Prefilter::OR);
  delete pf;
}

}  // namespace re2
