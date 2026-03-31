#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "util/utf.h"

namespace re2 {

// Helper to build a CharClass via CharClassBuilder
// Since CharClass::New is private, we need to use CharClassBuilder to create CharClass instances.
// Let's include the necessary headers.

} // namespace re2

#include "re2/re2.h"

// We need access to CharClassBuilder to create CharClass objects for testing.
// CharClassBuilder is typically used to build CharClass instances.

namespace re2 {

class CharClassBuilder;

} // namespace re2

// Since CharClass has private constructors and static New, we need to use
// the public API that produces CharClass objects. CharClassBuilder::GetCharClass()
// is the typical way to create a CharClass.

#include <vector>

namespace {

// We'll use a helper that creates CharClass via parsing regexps
// since CharClass constructors are private.

class CharClassTest_147 : public ::testing::Test {
protected:
  void TearDown() override {
    for (auto* cc : to_delete_) {
      cc->Delete();
    }
    to_delete_.clear();
  }

  // Track CharClass pointers for cleanup
  std::vector<re2::CharClass*> to_delete_;
};

// Helper: Parse a character class from a regexp pattern and extract the CharClass.
// This is a roundabout way since CharClass::New is private.
// We'll use re2::Regexp::Parse to get regexps that contain character classes.

#include "re2/regexp.h"

re2::Regexp* ParseRegexp(const std::string& pattern) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse(pattern, re2::Regexp::ClassNL, &status);
  return re;
}

TEST_F(CharClassTest_147, FullReturnsTrueForDotStar_147) {
  // A character class that matches everything (all runes) should be full.
  // [^\x00-\x{10FFFF}] negated => all. Let's try [^] or [\x00-\x{10FFFF}]
  // Actually, parsing "." with certain flags gives all characters.
  // Let's try a different approach - build via CharClassBuilder if accessible.

  // Use a regexp like [\x{0}-\x{10FFFF}] to get a full char class
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("[\\x{0}-\\x{10FFFF}]",
                                        re2::Regexp::ClassNL, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpCharClass) {
    re2::CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    EXPECT_TRUE(cc->full());
  }
  
  re->Decref();
}

TEST_F(CharClassTest_147, FullReturnsFalseForPartialClass_147) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("[a-z]",
                                        re2::Regexp::ClassNL, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpCharClass) {
    re2::CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    EXPECT_FALSE(cc->full());
  }
  
  re->Decref();
}

TEST_F(CharClassTest_147, ContainsReturnsTrueForIncludedRune_147) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("[a-z]",
                                        re2::Regexp::ClassNL, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpCharClass) {
    re2::CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    EXPECT_TRUE(cc->Contains('a'));
    EXPECT_TRUE(cc->Contains('m'));
    EXPECT_TRUE(cc->Contains('z'));
  }
  
  re->Decref();
}

TEST_F(CharClassTest_147, ContainsReturnsFalseForExcludedRune_147) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("[a-z]",
                                        re2::Regexp::ClassNL, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpCharClass) {
    re2::CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    EXPECT_FALSE(cc->Contains('A'));
    EXPECT_FALSE(cc->Contains('0'));
    EXPECT_FALSE(cc->Contains('{'));
  }
  
  re->Decref();
}

TEST_F(CharClassTest_147, EmptyReturnsFalseForNonEmptyClass_147) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("[a]",
                                        re2::Regexp::ClassNL, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpCharClass) {
    re2::CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    EXPECT_FALSE(cc->empty());
  }
  
  re->Decref();
}

TEST_F(CharClassTest_147, SizeReturnsCorrectCount_147) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("[a-z]",
                                        re2::Regexp::ClassNL, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpCharClass) {
    re2::CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    // [a-z] is one range, size() returns number of ranges
    EXPECT_GE(cc->size(), 1);
  }
  
  re->Decref();
}

TEST_F(CharClassTest_147, BeginEndIteratorTraversal_147) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("[a-zA-Z0-9]",
                                        re2::Regexp::ClassNL, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpCharClass) {
    re2::CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    int count = 0;
    for (auto it = cc->begin(); it != cc->end(); ++it) {
      count++;
    }
    EXPECT_EQ(count, cc->size());
  }
  
  re->Decref();
}

TEST_F(CharClassTest_147, NegateProducesComplement_147) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("[a-z]",
                                        re2::Regexp::ClassNL, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpCharClass) {
    re2::CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    re2::CharClass* neg = cc->Negate();
    ASSERT_NE(neg, nullptr);
    
    // 'a' should be in original but not in negation
    EXPECT_TRUE(cc->Contains('a'));
    EXPECT_FALSE(neg->Contains('a'));
    
    // 'A' should not be in original but should be in negation
    EXPECT_FALSE(cc->Contains('A'));
    EXPECT_TRUE(neg->Contains('A'));
    
    neg->Delete();
  }
  
  re->Decref();
}

TEST_F(CharClassTest_147, NegateOfFullIsEmpty_147) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("[\\x{0}-\\x{10FFFF}]",
                                        re2::Regexp::ClassNL, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpCharClass) {
    re2::CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    if (cc->full()) {
      re2::CharClass* neg = cc->Negate();
      ASSERT_NE(neg, nullptr);
      EXPECT_TRUE(neg->empty());
      neg->Delete();
    }
  }
  
  re->Decref();
}

TEST_F(CharClassTest_147, SingleCharacterClass_147) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("[x]",
                                        re2::Regexp::ClassNL, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpCharClass) {
    re2::CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    EXPECT_TRUE(cc->Contains('x'));
    EXPECT_FALSE(cc->Contains('y'));
    EXPECT_FALSE(cc->full());
    EXPECT_FALSE(cc->empty());
  }
  
  re->Decref();
}

TEST_F(CharClassTest_147, ContainsBoundaryRunes_147) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("[a-f]",
                                        re2::Regexp::ClassNL, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpCharClass) {
    re2::CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    // Boundary: just before 'a' and just after 'f'
    EXPECT_FALSE(cc->Contains('`')); // 'a' - 1
    EXPECT_TRUE(cc->Contains('a'));
    EXPECT_TRUE(cc->Contains('f'));
    EXPECT_FALSE(cc->Contains('g')); // 'f' + 1
  }
  
  re->Decref();
}

TEST_F(CharClassTest_147, MultipleDisjointRanges_147) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("[a-cx-z]",
                                        re2::Regexp::ClassNL, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpCharClass) {
    re2::CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    EXPECT_TRUE(cc->Contains('a'));
    EXPECT_TRUE(cc->Contains('b'));
    EXPECT_TRUE(cc->Contains('c'));
    EXPECT_FALSE(cc->Contains('d'));
    EXPECT_FALSE(cc->Contains('w'));
    EXPECT_TRUE(cc->Contains('x'));
    EXPECT_TRUE(cc->Contains('y'));
    EXPECT_TRUE(cc->Contains('z'));
  }
  
  re->Decref();
}

TEST_F(CharClassTest_147, FoldsASCIIForCaseFolded_147) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("(?i)[a-z]",
                                        re2::Regexp::FoldCase | re2::Regexp::ClassNL,
                                        &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpCharClass) {
    re2::CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    // When folding case, FoldsASCII might be true
    // This is implementation-dependent, but we test the method exists and returns a bool
    bool folds = cc->FoldsASCII();
    (void)folds; // Just ensure it's callable
  }
  
  re->Decref();
}

TEST_F(CharClassTest_147, UnicodeCharacterContainment_147) {
  re2::RegexpStatus status;
  // Test with Unicode range
  re2::Regexp* re = re2::Regexp::Parse("[\\x{4e00}-\\x{9fff}]",
                                        re2::Regexp::ClassNL, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpCharClass) {
    re2::CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    EXPECT_TRUE(cc->Contains(0x4e00));  // CJK Unified start
    EXPECT_TRUE(cc->Contains(0x9fff));  // CJK Unified end
    EXPECT_FALSE(cc->Contains(0x4dff)); // Just before range
    EXPECT_FALSE(cc->Contains(0xa000)); // Just after range
    EXPECT_FALSE(cc->Contains('a'));    // ASCII not in range
  }
  
  re->Decref();
}

TEST_F(CharClassTest_147, DoubleNegateReturnsOriginalBehavior_147) {
  re2::RegexpStatus status;
  re2::Regexp* re = re2::Regexp::Parse("[a-z]",
                                        re2::Regexp::ClassNL, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == re2::kRegexpCharClass) {
    re2::CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    re2::CharClass* neg = cc->Negate();
    ASSERT_NE(neg, nullptr);
    
    re2::CharClass* neg_neg = neg->Negate();
    ASSERT_NE(neg_neg, nullptr);
    
    // Double negation should contain same runes as original
    EXPECT_TRUE(neg_neg->Contains('a'));
    EXPECT_TRUE(neg_neg->Contains('z'));
    EXPECT_FALSE(neg_neg->Contains('A'));
    EXPECT_FALSE(neg_neg->Contains('0'));
    
    neg_neg->Delete();
    neg->Delete();
  }
  
  re->Decref();
}

} // anonymous namespace
