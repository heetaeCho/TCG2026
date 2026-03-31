#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/testing/regexp_generator.h"

#include <string>
#include <vector>

namespace re2 {

// Helper to get a CharClass from a parsed regexp pattern
// We use Regexp::Parse to obtain CharClass instances since
// CharClass constructor is private and New is private.
class CharClassTest_145 : public ::testing::Test {
 protected:
  // Parse a character class pattern and return the Regexp.
  // Caller must Decref the returned Regexp.
  Regexp* ParseRegexp(const std::string& pattern) {
    RegexpStatus status;
    Regexp* re = Regexp::Parse(pattern, Regexp::PerlX, &status);
    return re;
  }
};

TEST_F(CharClassTest_145, SingleCharClassSize_145) {
  // [a] should contain exactly 1 rune
  Regexp* re = ParseRegexp("[a]");
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    EXPECT_EQ(cc->size(), 1);
  }
  re->Decref();
}

TEST_F(CharClassTest_145, MultiCharClassSize_145) {
  // [abc] should contain 3 runes
  Regexp* re = ParseRegexp("[abc]");
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    EXPECT_EQ(cc->size(), 3);
  }
  re->Decref();
}

TEST_F(CharClassTest_145, RangeCharClassSize_145) {
  // [a-z] should contain 26 runes
  Regexp* re = ParseRegexp("[a-z]");
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    EXPECT_EQ(cc->size(), 26);
  }
  re->Decref();
}

TEST_F(CharClassTest_145, ContainsSingleChar_145) {
  // [a] should contain 'a' but not 'b'
  Regexp* re = ParseRegexp("[a]");
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    EXPECT_TRUE(cc->Contains('a'));
    EXPECT_FALSE(cc->Contains('b'));
  }
  re->Decref();
}

TEST_F(CharClassTest_145, ContainsRange_145) {
  // [a-f] should contain 'a' through 'f', but not 'g'
  Regexp* re = ParseRegexp("[a-f]");
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    EXPECT_TRUE(cc->Contains('a'));
    EXPECT_TRUE(cc->Contains('c'));
    EXPECT_TRUE(cc->Contains('f'));
    EXPECT_FALSE(cc->Contains('g'));
    EXPECT_FALSE(cc->Contains('z'));
  }
  re->Decref();
}

TEST_F(CharClassTest_145, EmptyCheck_145) {
  // [a-z] should not be empty
  Regexp* re = ParseRegexp("[a-z]");
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    EXPECT_FALSE(cc->empty());
  }
  re->Decref();
}

TEST_F(CharClassTest_145, FullCheck_145) {
  // [a] is definitely not full
  Regexp* re = ParseRegexp("[a]");
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    EXPECT_FALSE(cc->full());
  }
  re->Decref();
}

TEST_F(CharClassTest_145, IteratorRange_145) {
  // [a-c] should have begin != end, and we should be able to iterate
  Regexp* re = ParseRegexp("[a-c]");
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    int count = 0;
    for (CharClass::iterator it = cc->begin(); it != cc->end(); ++it) {
      count++;
    }
    EXPECT_GT(count, 0);
  }
  re->Decref();
}

TEST_F(CharClassTest_145, NegateCharClass_145) {
  // Negating [a] should produce a class that does NOT contain 'a'
  // but contains other characters like 'b'
  Regexp* re = ParseRegexp("[a]");
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    EXPECT_TRUE(cc->Contains('a'));
    EXPECT_FALSE(cc->Contains('b'));

    CharClass* neg = cc->Negate();
    ASSERT_NE(neg, nullptr);
    EXPECT_FALSE(neg->Contains('a'));
    EXPECT_TRUE(neg->Contains('b'));
    EXPECT_TRUE(neg->Contains('z'));
    neg->Delete();
  }
  re->Decref();
}

TEST_F(CharClassTest_145, NegateSize_145) {
  // Negating [a-z] (26 runes) should give a much larger class
  Regexp* re = ParseRegexp("[a-z]");
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    int orig_size = cc->size();
    EXPECT_EQ(orig_size, 26);

    CharClass* neg = cc->Negate();
    ASSERT_NE(neg, nullptr);
    EXPECT_GT(neg->size(), orig_size);
    neg->Delete();
  }
  re->Decref();
}

TEST_F(CharClassTest_145, MultipleRangesSize_145) {
  // [a-zA-Z] should have 52 runes
  Regexp* re = ParseRegexp("[a-zA-Z]");
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    EXPECT_EQ(cc->size(), 52);
  }
  re->Decref();
}

TEST_F(CharClassTest_145, MultipleRangesContains_145) {
  // [a-zA-Z] should contain both lowercase and uppercase
  Regexp* re = ParseRegexp("[a-zA-Z]");
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    EXPECT_TRUE(cc->Contains('a'));
    EXPECT_TRUE(cc->Contains('z'));
    EXPECT_TRUE(cc->Contains('A'));
    EXPECT_TRUE(cc->Contains('Z'));
    EXPECT_FALSE(cc->Contains('0'));
    EXPECT_FALSE(cc->Contains(' '));
  }
  re->Decref();
}

TEST_F(CharClassTest_145, DigitClassSize_145) {
  // [0-9] should have 10 runes
  Regexp* re = ParseRegexp("[0-9]");
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    EXPECT_EQ(cc->size(), 10);
    EXPECT_TRUE(cc->Contains('0'));
    EXPECT_TRUE(cc->Contains('9'));
    EXPECT_FALSE(cc->Contains('a'));
  }
  re->Decref();
}

TEST_F(CharClassTest_145, FoldsASCII_145) {
  // Test FoldsASCII - case-insensitive patterns might set this
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::FoldCase | Regexp::PerlX, &status);
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    // With FoldCase, [a-z] should fold ASCII
    // Both 'a' and 'A' should be contained
    EXPECT_TRUE(cc->Contains('a'));
    EXPECT_TRUE(cc->Contains('A'));
  }
  re->Decref();
}

TEST_F(CharClassTest_145, DoubleNegate_145) {
  // Negating twice should give a class equivalent to the original
  Regexp* re = ParseRegexp("[a-f]");
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);

    CharClass* neg = cc->Negate();
    ASSERT_NE(neg, nullptr);
    CharClass* neg2 = neg->Negate();
    ASSERT_NE(neg2, nullptr);

    EXPECT_EQ(neg2->size(), cc->size());
    EXPECT_TRUE(neg2->Contains('a'));
    EXPECT_TRUE(neg2->Contains('f'));
    EXPECT_FALSE(neg2->Contains('g'));

    neg2->Delete();
    neg->Delete();
  }
  re->Decref();
}

TEST_F(CharClassTest_145, BoundaryContainsFirstAndLastInRange_145) {
  // Check boundary: first and last element of a range
  Regexp* re = ParseRegexp("[d-m]");
  ASSERT_NE(re, nullptr);
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_NE(cc, nullptr);
    EXPECT_TRUE(cc->Contains('d'));
    EXPECT_TRUE(cc->Contains('m'));
    EXPECT_FALSE(cc->Contains('c'));
    EXPECT_FALSE(cc->Contains('n'));
    EXPECT_EQ(cc->size(), 10); // d,e,f,g,h,i,j,k,l,m
  }
  re->Decref();
}

}  // namespace re2
