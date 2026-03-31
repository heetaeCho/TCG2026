#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/testing/regexp_generator.h"
#include "re2/testing/tester.h"

#include <vector>

namespace re2 {

// Helper to create a CharClass through parsing a regexp
// Since CharClass::New is private, we need to obtain CharClass instances
// through the public API (e.g., parsing regexps that produce character classes)

class CharClassTest_143 : public ::testing::Test {
 protected:
  // Parse a pattern and extract the CharClass from the resulting Regexp
  Regexp* ParseRegexp(const char* pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::ClassNL | Regexp::PerlX, &status);
    return re;
  }
};

TEST_F(CharClassTest_143, SimpleCharClassContains_143) {
  // Parse [a-z] which should create a character class containing a-z
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::ClassNL, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    // 'a' through 'z' should be contained
    EXPECT_TRUE(cc->Contains('a'));
    EXPECT_TRUE(cc->Contains('m'));
    EXPECT_TRUE(cc->Contains('z'));
    
    // Characters outside the range should not be contained
    EXPECT_FALSE(cc->Contains('A'));
    EXPECT_FALSE(cc->Contains('0'));
    EXPECT_FALSE(cc->Contains('`'));  // character just before 'a'
    EXPECT_FALSE(cc->Contains('{'));  // character just after 'z'
  }
  
  re->Decref();
}

TEST_F(CharClassTest_143, CharClassSize_143) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::ClassNL, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    // [a-z] has 26 runes
    EXPECT_EQ(cc->size(), 26);
  }
  
  re->Decref();
}

TEST_F(CharClassTest_143, CharClassNotEmpty_143) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::ClassNL, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    EXPECT_FALSE(cc->empty());
  }
  
  re->Decref();
}

TEST_F(CharClassTest_143, CharClassNotFull_143) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::ClassNL, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    EXPECT_FALSE(cc->full());
  }
  
  re->Decref();
}

TEST_F(CharClassTest_143, CharClassIteratorRange_143) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::ClassNL, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    // Iterate over ranges
    int count = 0;
    for (CharClass::iterator it = cc->begin(); it != cc->end(); ++it) {
      count++;
      // For [a-z], there should be exactly one range: 'a' to 'z'
      EXPECT_EQ(it->lo, 'a');
      EXPECT_EQ(it->hi, 'z');
    }
    EXPECT_EQ(count, 1);
  }
  
  re->Decref();
}

TEST_F(CharClassTest_143, MultipleRangesIterator_143) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-zA-Z]", Regexp::ClassNL, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    // Should have 2 ranges: A-Z and a-z
    int count = 0;
    for (CharClass::iterator it = cc->begin(); it != cc->end(); ++it) {
      count++;
    }
    EXPECT_EQ(count, 2);
    EXPECT_EQ(cc->size(), 52);
  }
  
  re->Decref();
}

TEST_F(CharClassTest_143, SingleCharClass_143) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[x]", Regexp::ClassNL, &status);
  ASSERT_NE(re, nullptr);
  
  // A single character class might be optimized to kRegexpLiteral,
  // but if it stays as a char class:
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    EXPECT_TRUE(cc->Contains('x'));
    EXPECT_FALSE(cc->Contains('y'));
    EXPECT_EQ(cc->size(), 1);
    EXPECT_FALSE(cc->empty());
    EXPECT_FALSE(cc->full());
  }
  
  re->Decref();
}

TEST_F(CharClassTest_143, NegateCharClass_143) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::ClassNL, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    CharClass* negated = cc->Negate();
    ASSERT_NE(negated, nullptr);
    
    // Negated class should NOT contain 'a'-'z'
    EXPECT_FALSE(negated->Contains('a'));
    EXPECT_FALSE(negated->Contains('z'));
    
    // Negated class should contain characters outside 'a'-'z'
    EXPECT_TRUE(negated->Contains('A'));
    EXPECT_TRUE(negated->Contains('0'));
    
    negated->Delete();
  }
  
  re->Decref();
}

TEST_F(CharClassTest_143, NegatedCharClassContains_143) {
  RegexpStatus status;
  // [^a-z] should contain everything except a-z
  Regexp* re = Regexp::Parse("[^a-z]", Regexp::ClassNL, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    EXPECT_FALSE(cc->Contains('a'));
    EXPECT_FALSE(cc->Contains('z'));
    EXPECT_TRUE(cc->Contains('A'));
    EXPECT_TRUE(cc->Contains('0'));
  }
  
  re->Decref();
}

TEST_F(CharClassTest_143, DigitClass_143) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[0-9]", Regexp::ClassNL, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    EXPECT_EQ(cc->size(), 10);
    EXPECT_TRUE(cc->Contains('0'));
    EXPECT_TRUE(cc->Contains('5'));
    EXPECT_TRUE(cc->Contains('9'));
    EXPECT_FALSE(cc->Contains('a'));
    EXPECT_FALSE(cc->Contains('/'));  // just before '0'
    EXPECT_FALSE(cc->Contains(':'));  // just after '9'
  }
  
  re->Decref();
}

TEST_F(CharClassTest_143, FoldsASCII_143) {
  RegexpStatus status;
  // Case-insensitive [a-z] should fold ASCII
  Regexp* re = Regexp::Parse("(?i)[a-z]", Regexp::ClassNL | Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    // Should contain both cases
    EXPECT_TRUE(cc->Contains('a'));
    EXPECT_TRUE(cc->Contains('A'));
    EXPECT_TRUE(cc->Contains('z'));
    EXPECT_TRUE(cc->Contains('Z'));
  }
  
  re->Decref();
}

TEST_F(CharClassTest_143, DisjointRanges_143) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-c0-2]", Regexp::ClassNL, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    EXPECT_EQ(cc->size(), 6);  // a,b,c,0,1,2
    EXPECT_TRUE(cc->Contains('a'));
    EXPECT_TRUE(cc->Contains('b'));
    EXPECT_TRUE(cc->Contains('c'));
    EXPECT_TRUE(cc->Contains('0'));
    EXPECT_TRUE(cc->Contains('1'));
    EXPECT_TRUE(cc->Contains('2'));
    EXPECT_FALSE(cc->Contains('d'));
    EXPECT_FALSE(cc->Contains('3'));
  }
  
  re->Decref();
}

TEST_F(CharClassTest_143, DotClassContainsMost_143) {
  RegexpStatus status;
  // Parse "." with ClassNL off - should match everything except \n
  Regexp* re = Regexp::Parse("[\\x00-\\x09\\x0b-\\x{10ffff}]", Regexp::ClassNL, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    EXPECT_FALSE(cc->empty());
    EXPECT_TRUE(cc->Contains('a'));
    EXPECT_TRUE(cc->Contains('Z'));
    EXPECT_TRUE(cc->Contains('0'));
  }
  
  re->Decref();
}

TEST_F(CharClassTest_143, BoundaryContainsCheck_143) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::ClassNL, &status);
  ASSERT_NE(re, nullptr);
  
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    
    // Boundary: just before 'a' and just after 'z'
    EXPECT_FALSE(cc->Contains('a' - 1));
    EXPECT_TRUE(cc->Contains('a'));
    EXPECT_TRUE(cc->Contains('z'));
    EXPECT_FALSE(cc->Contains('z' + 1));
  }
  
  re->Decref();
}

}  // namespace re2
