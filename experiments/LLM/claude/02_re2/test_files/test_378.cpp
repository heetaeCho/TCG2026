#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "util/utf.h"

namespace re2 {

// Helper function to create a CharClass using the CharClassBuilder
// Since CharClass::New is private, we need to use CharClassBuilder to create CharClass instances
class CharClassBuilder;

class CharClassNegateTest_378 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Clean up any allocated CharClass objects
  }
};

// We need to use the public RE2 API or CharClassBuilder to create CharClass objects
// since CharClass::New is private. Let's use Regexp parsing to obtain CharClass objects.

} // namespace re2

#include "re2/re2.h"
#include "re2/prog.h"

namespace re2 {

// Since CharClass has private constructors and New, we need to obtain instances
// through the regexp parsing infrastructure.

// Helper: parse a character class pattern and extract the CharClass
static Regexp* ParseRegexp(const char* pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::ClassNL | Regexp::OneLine, &status);
  return re;
}

TEST(CharClassNegateTest_378, NegateEmptyCharClass_378) {
  // Parse a pattern that gives us a character class, then negate it
  // [^\x00-\x{10FFFF}] would be empty but that's hard to express
  // Instead, let's use a simple class and test negate behavior
  
  Regexp* re = ParseRegexp("[a]");
  ASSERT_NE(re, nullptr);
  
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    // 'a' should be contained
    EXPECT_TRUE(cc->Contains('a'));
    EXPECT_FALSE(cc->Contains('b'));
    
    CharClass* neg = cc->Negate();
    ASSERT_NE(neg, nullptr);
    
    // After negation, 'a' should NOT be contained
    EXPECT_FALSE(neg->Contains('a'));
    // 'b' should be contained in the negation
    EXPECT_TRUE(neg->Contains('b'));
    // 0 should be contained in the negation
    EXPECT_TRUE(neg->Contains(0));
    // Runemax should be contained in the negation
    EXPECT_TRUE(neg->Contains(Runemax));
    
    neg->Delete();
  }
  
  re->Decref();
}

TEST(CharClassNegateTest_378, NegateSingleCharClass_378) {
  Regexp* re = ParseRegexp("[z]");
  ASSERT_NE(re, nullptr);
  
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    EXPECT_TRUE(cc->Contains('z'));
    EXPECT_EQ(cc->size(), 1);
    
    CharClass* neg = cc->Negate();
    ASSERT_NE(neg, nullptr);
    
    EXPECT_FALSE(neg->Contains('z'));
    EXPECT_TRUE(neg->Contains('a'));
    EXPECT_TRUE(neg->Contains(0));
    EXPECT_TRUE(neg->Contains(Runemax));
    
    neg->Delete();
  }
  
  re->Decref();
}

TEST(CharClassNegateTest_378, NegateRangeCharClass_378) {
  Regexp* re = ParseRegexp("[a-z]");
  ASSERT_NE(re, nullptr);
  
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    EXPECT_TRUE(cc->Contains('a'));
    EXPECT_TRUE(cc->Contains('m'));
    EXPECT_TRUE(cc->Contains('z'));
    EXPECT_FALSE(cc->Contains('A'));
    EXPECT_FALSE(cc->Contains('0'));
    
    CharClass* neg = cc->Negate();
    ASSERT_NE(neg, nullptr);
    
    EXPECT_FALSE(neg->Contains('a'));
    EXPECT_FALSE(neg->Contains('m'));
    EXPECT_FALSE(neg->Contains('z'));
    EXPECT_TRUE(neg->Contains('A'));
    EXPECT_TRUE(neg->Contains('0'));
    EXPECT_TRUE(neg->Contains(0));
    EXPECT_TRUE(neg->Contains(Runemax));
    
    neg->Delete();
  }
  
  re->Decref();
}

TEST(CharClassNegateTest_378, NegateMultipleRanges_378) {
  Regexp* re = ParseRegexp("[a-zA-Z]");
  ASSERT_NE(re, nullptr);
  
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    EXPECT_TRUE(cc->Contains('a'));
    EXPECT_TRUE(cc->Contains('Z'));
    EXPECT_FALSE(cc->Contains('0'));
    EXPECT_FALSE(cc->Contains('['));
    
    CharClass* neg = cc->Negate();
    ASSERT_NE(neg, nullptr);
    
    EXPECT_FALSE(neg->Contains('a'));
    EXPECT_FALSE(neg->Contains('Z'));
    EXPECT_TRUE(neg->Contains('0'));
    EXPECT_TRUE(neg->Contains('['));
    EXPECT_TRUE(neg->Contains(0));
    EXPECT_TRUE(neg->Contains(Runemax));
    
    neg->Delete();
  }
  
  re->Decref();
}

TEST(CharClassNegateTest_378, DoubleNegateRestoresOriginal_378) {
  Regexp* re = ParseRegexp("[a-f]");
  ASSERT_NE(re, nullptr);
  
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    CharClass* neg = cc->Negate();
    ASSERT_NE(neg, nullptr);
    
    CharClass* neg_neg = neg->Negate();
    ASSERT_NE(neg_neg, nullptr);
    
    // Double negation should restore original containment
    EXPECT_TRUE(neg_neg->Contains('a'));
    EXPECT_TRUE(neg_neg->Contains('c'));
    EXPECT_TRUE(neg_neg->Contains('f'));
    EXPECT_FALSE(neg_neg->Contains('g'));
    EXPECT_FALSE(neg_neg->Contains('0'));
    EXPECT_FALSE(neg_neg->Contains(0));
    
    neg_neg->Delete();
    neg->Delete();
  }
  
  re->Decref();
}

TEST(CharClassNegateTest_378, NegateDigitClass_378) {
  Regexp* re = ParseRegexp("[0-9]");
  ASSERT_NE(re, nullptr);
  
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    for (int i = '0'; i <= '9'; i++) {
      EXPECT_TRUE(cc->Contains(i));
    }
    
    CharClass* neg = cc->Negate();
    ASSERT_NE(neg, nullptr);
    
    for (int i = '0'; i <= '9'; i++) {
      EXPECT_FALSE(neg->Contains(i));
    }
    EXPECT_TRUE(neg->Contains('a'));
    EXPECT_TRUE(neg->Contains(' '));
    
    neg->Delete();
  }
  
  re->Decref();
}

TEST(CharClassNegateTest_378, NegateClassStartingAtZero_378) {
  // \x00-\x09 - class that starts at rune 0
  Regexp* re = ParseRegexp("[\\x00-\\x09]");
  ASSERT_NE(re, nullptr);
  
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    EXPECT_TRUE(cc->Contains(0));
    EXPECT_TRUE(cc->Contains(9));
    EXPECT_FALSE(cc->Contains(10));
    
    CharClass* neg = cc->Negate();
    ASSERT_NE(neg, nullptr);
    
    EXPECT_FALSE(neg->Contains(0));
    EXPECT_FALSE(neg->Contains(9));
    EXPECT_TRUE(neg->Contains(10));
    EXPECT_TRUE(neg->Contains(Runemax));
    
    neg->Delete();
  }
  
  re->Decref();
}

TEST(CharClassNegateTest_378, NegateClassWithBoundaryRunes_378) {
  // Test with class containing boundary values
  Regexp* re = ParseRegexp("[a-cx-z]");
  ASSERT_NE(re, nullptr);
  
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    CharClass* neg = cc->Negate();
    ASSERT_NE(neg, nullptr);
    
    // Boundary checks
    EXPECT_TRUE(neg->Contains('a' - 1));  // just before 'a'
    EXPECT_FALSE(neg->Contains('a'));
    EXPECT_FALSE(neg->Contains('c'));
    EXPECT_TRUE(neg->Contains('c' + 1));  // just after 'c' ('d')
    EXPECT_TRUE(neg->Contains('w'));       // between ranges
    EXPECT_TRUE(neg->Contains('x' - 1));  // just before 'x' ('w')
    EXPECT_FALSE(neg->Contains('x'));
    EXPECT_FALSE(neg->Contains('z'));
    EXPECT_TRUE(neg->Contains('z' + 1));  // just after 'z'
    
    neg->Delete();
  }
  
  re->Decref();
}

TEST(CharClassNegateTest_378, NegatePreservesNonEmptiness_378) {
  // Negating a non-full class should produce a non-empty class
  Regexp* re = ParseRegexp("[a]");
  ASSERT_NE(re, nullptr);
  
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    EXPECT_FALSE(cc->empty());
    
    CharClass* neg = cc->Negate();
    ASSERT_NE(neg, nullptr);
    
    EXPECT_FALSE(neg->empty());
    
    neg->Delete();
  }
  
  re->Decref();
}

TEST(CharClassNegateTest_378, NegateAlphanumericClass_378) {
  Regexp* re = ParseRegexp("[a-zA-Z0-9]");
  ASSERT_NE(re, nullptr);
  
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    CharClass* neg = cc->Negate();
    ASSERT_NE(neg, nullptr);
    
    // Alphanumeric chars should not be in negation
    EXPECT_FALSE(neg->Contains('a'));
    EXPECT_FALSE(neg->Contains('Z'));
    EXPECT_FALSE(neg->Contains('5'));
    
    // Non-alphanumeric should be in negation
    EXPECT_TRUE(neg->Contains(' '));
    EXPECT_TRUE(neg->Contains('!'));
    EXPECT_TRUE(neg->Contains('@'));
    EXPECT_TRUE(neg->Contains('['));
    EXPECT_TRUE(neg->Contains('{'));
    
    neg->Delete();
  }
  
  re->Decref();
}

} // namespace re2
