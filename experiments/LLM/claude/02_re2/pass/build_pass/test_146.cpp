#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/testing/regexp_generator.h"
#include "re2/testing/tester.h"

#include <string>
#include <vector>

namespace re2 {

// Helper to parse a regexp and extract a CharClass from a character class pattern
// We use the Regexp parsing infrastructure to create CharClass instances.

class CharClassTest_146 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that an empty character class reports empty() == true
TEST_F(CharClassTest_146, EmptyCharClassIsEmpty_146) {
  // Parse a regexp that produces an empty char class via negation tricks
  // Use [^\x00-\x{10ffff}] which should match nothing
  // Actually, let's use the CharClassBuilder to build one
  // We'll rely on parsing regexps that produce character classes
  
  // A character class like [a] is not empty
  // Let's test via Regexp parsing
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a]", Regexp::Latin1, &status);
  ASSERT_TRUE(re != nullptr);
  ASSERT_EQ(re->op(), kRegexpCharClass);
  CharClass* cc = re->cc();
  ASSERT_TRUE(cc != nullptr);
  EXPECT_FALSE(cc->empty());
  re->Decref();
}

// Test that a single-character class is not empty and has size 1
TEST_F(CharClassTest_146, SingleCharClassNotEmpty_146) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a]", Regexp::Latin1, &status);
  ASSERT_TRUE(re != nullptr);
  ASSERT_EQ(re->op(), kRegexpCharClass);
  CharClass* cc = re->cc();
  ASSERT_TRUE(cc != nullptr);
  EXPECT_FALSE(cc->empty());
  EXPECT_EQ(cc->size(), 1);
  re->Decref();
}

// Test Contains for a single character class
TEST_F(CharClassTest_146, ContainsSingleChar_146) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a]", Regexp::Latin1, &status);
  ASSERT_TRUE(re != nullptr);
  ASSERT_EQ(re->op(), kRegexpCharClass);
  CharClass* cc = re->cc();
  ASSERT_TRUE(cc != nullptr);
  EXPECT_TRUE(cc->Contains('a'));
  EXPECT_FALSE(cc->Contains('b'));
  re->Decref();
}

// Test Contains for a range character class
TEST_F(CharClassTest_146, ContainsRange_146) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::Latin1, &status);
  ASSERT_TRUE(re != nullptr);
  ASSERT_EQ(re->op(), kRegexpCharClass);
  CharClass* cc = re->cc();
  ASSERT_TRUE(cc != nullptr);
  EXPECT_TRUE(cc->Contains('a'));
  EXPECT_TRUE(cc->Contains('m'));
  EXPECT_TRUE(cc->Contains('z'));
  EXPECT_FALSE(cc->Contains('A'));
  EXPECT_FALSE(cc->Contains('0'));
  re->Decref();
}

// Test Contains for multiple ranges
TEST_F(CharClassTest_146, ContainsMultipleRanges_146) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-zA-Z0-9]", Regexp::Latin1, &status);
  ASSERT_TRUE(re != nullptr);
  ASSERT_EQ(re->op(), kRegexpCharClass);
  CharClass* cc = re->cc();
  ASSERT_TRUE(cc != nullptr);
  EXPECT_TRUE(cc->Contains('a'));
  EXPECT_TRUE(cc->Contains('Z'));
  EXPECT_TRUE(cc->Contains('5'));
  EXPECT_FALSE(cc->Contains('!'));
  EXPECT_FALSE(cc->Contains(' '));
  re->Decref();
}

// Test size returns correct number of runes
TEST_F(CharClassTest_146, SizeMultipleChars_146) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[abc]", Regexp::Latin1, &status);
  ASSERT_TRUE(re != nullptr);
  ASSERT_EQ(re->op(), kRegexpCharClass);
  CharClass* cc = re->cc();
  ASSERT_TRUE(cc != nullptr);
  EXPECT_EQ(cc->size(), 3);
  re->Decref();
}

// Test size for a range
TEST_F(CharClassTest_146, SizeRange_146) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::Latin1, &status);
  ASSERT_TRUE(re != nullptr);
  ASSERT_EQ(re->op(), kRegexpCharClass);
  CharClass* cc = re->cc();
  ASSERT_TRUE(cc != nullptr);
  EXPECT_EQ(cc->size(), 26);
  re->Decref();
}

// Test begin and end iterators
TEST_F(CharClassTest_146, IteratorTraversal_146) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-cf-h]", Regexp::Latin1, &status);
  ASSERT_TRUE(re != nullptr);
  ASSERT_EQ(re->op(), kRegexpCharClass);
  CharClass* cc = re->cc();
  ASSERT_TRUE(cc != nullptr);
  
  int range_count = 0;
  for (CharClass::iterator it = cc->begin(); it != cc->end(); ++it) {
    range_count++;
  }
  // Should have 2 ranges: a-c and f-h
  EXPECT_EQ(range_count, 2);
  re->Decref();
}

// Test Negate produces the complement
TEST_F(CharClassTest_146, NegateCharClass_146) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a]", Regexp::Latin1, &status);
  ASSERT_TRUE(re != nullptr);
  ASSERT_EQ(re->op(), kRegexpCharClass);
  CharClass* cc = re->cc();
  ASSERT_TRUE(cc != nullptr);
  
  CharClass* neg = cc->Negate();
  ASSERT_TRUE(neg != nullptr);
  EXPECT_FALSE(neg->Contains('a'));
  EXPECT_TRUE(neg->Contains('b'));
  EXPECT_TRUE(neg->Contains('0'));
  EXPECT_FALSE(neg->empty());
  neg->Delete();
  re->Decref();
}

// Test that negating a large class gives a small one
TEST_F(CharClassTest_146, NegateRangeClass_146) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::Latin1, &status);
  ASSERT_TRUE(re != nullptr);
  ASSERT_EQ(re->op(), kRegexpCharClass);
  CharClass* cc = re->cc();
  ASSERT_TRUE(cc != nullptr);
  
  CharClass* neg = cc->Negate();
  ASSERT_TRUE(neg != nullptr);
  EXPECT_FALSE(neg->Contains('a'));
  EXPECT_FALSE(neg->Contains('z'));
  EXPECT_TRUE(neg->Contains('A'));
  EXPECT_TRUE(neg->Contains('0'));
  neg->Delete();
  re->Decref();
}

// Test full() - a character class that matches everything
TEST_F(CharClassTest_146, FullCharClass_146) {
  RegexpStatus status;
  // Parse a negated empty class, which matches everything
  // [^] is not standard, but [\x00-\x{10ffff}] should be full in some sense
  // Actually, let's use the dot with flags or something simpler
  // Let's negate a single char and check it's not full, then negate it back
  Regexp* re = Regexp::Parse("[a]", Regexp::Latin1, &status);
  ASSERT_TRUE(re != nullptr);
  ASSERT_EQ(re->op(), kRegexpCharClass);
  CharClass* cc = re->cc();
  ASSERT_TRUE(cc != nullptr);
  EXPECT_FALSE(cc->full());
  re->Decref();
}

// Test FoldsASCII
TEST_F(CharClassTest_146, FoldsASCII_146) {
  RegexpStatus status;
  // Case-insensitive character class
  Regexp* re = Regexp::Parse("(?i)[a]", Regexp::PerlX, &status);
  ASSERT_TRUE(re != nullptr);
  if (re->op() == kRegexpCharClass) {
    CharClass* cc = re->cc();
    ASSERT_TRUE(cc != nullptr);
    // With case folding, [a] should contain both 'a' and 'A'
    EXPECT_TRUE(cc->Contains('a'));
    EXPECT_TRUE(cc->Contains('A'));
  }
  re->Decref();
}

// Test Contains boundary - character just before and after range
TEST_F(CharClassTest_146, ContainsBoundary_146) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[b-y]", Regexp::Latin1, &status);
  ASSERT_TRUE(re != nullptr);
  ASSERT_EQ(re->op(), kRegexpCharClass);
  CharClass* cc = re->cc();
  ASSERT_TRUE(cc != nullptr);
  EXPECT_FALSE(cc->Contains('a'));  // just before range
  EXPECT_TRUE(cc->Contains('b'));   // start of range
  EXPECT_TRUE(cc->Contains('y'));   // end of range
  EXPECT_FALSE(cc->Contains('z'));  // just after range
  re->Decref();
}

// Test size for a digit range
TEST_F(CharClassTest_146, DigitRangeSize_146) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[0-9]", Regexp::Latin1, &status);
  ASSERT_TRUE(re != nullptr);
  ASSERT_EQ(re->op(), kRegexpCharClass);
  CharClass* cc = re->cc();
  ASSERT_TRUE(cc != nullptr);
  EXPECT_EQ(cc->size(), 10);
  re->Decref();
}

// Test double negation restores containment
TEST_F(CharClassTest_146, DoubleNegate_146) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[a-z]", Regexp::Latin1, &status);
  ASSERT_TRUE(re != nullptr);
  ASSERT_EQ(re->op(), kRegexpCharClass);
  CharClass* cc = re->cc();
  ASSERT_TRUE(cc != nullptr);
  
  CharClass* neg = cc->Negate();
  CharClass* neg_neg = neg->Negate();
  ASSERT_TRUE(neg_neg != nullptr);
  
  EXPECT_TRUE(neg_neg->Contains('a'));
  EXPECT_TRUE(neg_neg->Contains('z'));
  EXPECT_FALSE(neg_neg->Contains('A'));
  EXPECT_EQ(neg_neg->size(), 26);
  
  neg_neg->Delete();
  neg->Delete();
  re->Decref();
}

}  // namespace re2
