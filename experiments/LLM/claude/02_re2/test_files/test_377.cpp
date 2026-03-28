#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

#include <vector>

namespace re2 {

class CharClassTest_377 : public ::testing::Test {
 protected:
  void TearDown() override {
    // CharClass instances are cleaned up via Delete() in individual tests
  }
};

TEST_F(CharClassTest_377, EmptyCharClassIsEmpty_377) {
  CharClassBuilder builder;
  CharClass* cc = builder.GetCharClass();
  ASSERT_NE(cc, nullptr);
  EXPECT_TRUE(cc->empty());
  EXPECT_EQ(cc->size(), 0);
  EXPECT_FALSE(cc->full());
  cc->Delete();
}

TEST_F(CharClassTest_377, SingleRuneContains_377) {
  CharClassBuilder builder;
  builder.AddRange('a', 'a');
  CharClass* cc = builder.GetCharClass();
  ASSERT_NE(cc, nullptr);
  EXPECT_TRUE(cc->Contains('a'));
  EXPECT_FALSE(cc->Contains('b'));
  EXPECT_FALSE(cc->Contains('A'));
  EXPECT_EQ(cc->size(), 1);
  EXPECT_FALSE(cc->empty());
  cc->Delete();
}

TEST_F(CharClassTest_377, RangeContains_377) {
  CharClassBuilder builder;
  builder.AddRange('a', 'z');
  CharClass* cc = builder.GetCharClass();
  ASSERT_NE(cc, nullptr);
  EXPECT_TRUE(cc->Contains('a'));
  EXPECT_TRUE(cc->Contains('m'));
  EXPECT_TRUE(cc->Contains('z'));
  EXPECT_FALSE(cc->Contains('A'));
  EXPECT_FALSE(cc->Contains('0'));
  EXPECT_EQ(cc->size(), 26);
  cc->Delete();
}

TEST_F(CharClassTest_377, MultipleRangesContains_377) {
  CharClassBuilder builder;
  builder.AddRange('a', 'c');
  builder.AddRange('x', 'z');
  CharClass* cc = builder.GetCharClass();
  ASSERT_NE(cc, nullptr);
  EXPECT_TRUE(cc->Contains('a'));
  EXPECT_TRUE(cc->Contains('b'));
  EXPECT_TRUE(cc->Contains('c'));
  EXPECT_TRUE(cc->Contains('x'));
  EXPECT_TRUE(cc->Contains('y'));
  EXPECT_TRUE(cc->Contains('z'));
  EXPECT_FALSE(cc->Contains('d'));
  EXPECT_FALSE(cc->Contains('w'));
  EXPECT_EQ(cc->size(), 6);
  cc->Delete();
}

TEST_F(CharClassTest_377, NegateInvertsContainment_377) {
  CharClassBuilder builder;
  builder.AddRange('a', 'z');
  CharClass* cc = builder.GetCharClass();
  ASSERT_NE(cc, nullptr);
  EXPECT_TRUE(cc->Contains('a'));
  EXPECT_FALSE(cc->Contains('A'));

  CharClass* negated = cc->Negate();
  ASSERT_NE(negated, nullptr);
  EXPECT_FALSE(negated->Contains('a'));
  EXPECT_FALSE(negated->Contains('z'));
  EXPECT_TRUE(negated->Contains('A'));
  EXPECT_TRUE(negated->Contains('0'));

  cc->Delete();
  negated->Delete();
}

TEST_F(CharClassTest_377, IteratorWorks_377) {
  CharClassBuilder builder;
  builder.AddRange('a', 'c');
  builder.AddRange('x', 'z');
  CharClass* cc = builder.GetCharClass();
  ASSERT_NE(cc, nullptr);

  int range_count = 0;
  for (CharClass::iterator it = cc->begin(); it != cc->end(); ++it) {
    range_count++;
  }
  EXPECT_EQ(range_count, 2);
  cc->Delete();
}

TEST_F(CharClassTest_377, EmptyClassNotFull_377) {
  CharClassBuilder builder;
  CharClass* cc = builder.GetCharClass();
  ASSERT_NE(cc, nullptr);
  EXPECT_FALSE(cc->full());
  EXPECT_TRUE(cc->empty());
  cc->Delete();
}

TEST_F(CharClassTest_377, FullClass_377) {
  CharClassBuilder builder;
  builder.AddRange(0, Runemax);
  CharClass* cc = builder.GetCharClass();
  ASSERT_NE(cc, nullptr);
  EXPECT_TRUE(cc->full());
  EXPECT_FALSE(cc->empty());
  cc->Delete();
}

TEST_F(CharClassTest_377, FoldsASCII_377) {
  CharClassBuilder builder;
  builder.AddRange('a', 'z');
  builder.AddRange('A', 'Z');
  CharClass* cc = builder.GetCharClass();
  ASSERT_NE(cc, nullptr);
  // FoldsASCII is set by the builder based on whether ASCII case folding applies
  // Just verify it returns a bool without crashing
  bool folds = cc->FoldsASCII();
  (void)folds;
  cc->Delete();
}

TEST_F(CharClassTest_377, NegateEmptyClassBecomesFull_377) {
  CharClassBuilder builder;
  CharClass* cc = builder.GetCharClass();
  ASSERT_NE(cc, nullptr);
  CharClass* negated = cc->Negate();
  ASSERT_NE(negated, nullptr);
  EXPECT_TRUE(negated->full());
  cc->Delete();
  negated->Delete();
}

TEST_F(CharClassTest_377, ContainsBoundaryValues_377) {
  CharClassBuilder builder;
  builder.AddRange(0, 0);
  CharClass* cc = builder.GetCharClass();
  ASSERT_NE(cc, nullptr);
  EXPECT_TRUE(cc->Contains(0));
  EXPECT_FALSE(cc->Contains(1));
  EXPECT_EQ(cc->size(), 1);
  cc->Delete();
}

TEST_F(CharClassTest_377, ContainsHighUnicodeRune_377) {
  CharClassBuilder builder;
  builder.AddRange(0x10000, 0x10FFFF);
  CharClass* cc = builder.GetCharClass();
  ASSERT_NE(cc, nullptr);
  EXPECT_TRUE(cc->Contains(0x10000));
  EXPECT_TRUE(cc->Contains(0x10FFFF));
  EXPECT_FALSE(cc->Contains(0xFFFF));
  cc->Delete();
}

TEST_F(CharClassTest_377, DeleteDoesNotCrash_377) {
  CharClassBuilder builder;
  builder.AddRange('a', 'z');
  CharClass* cc = builder.GetCharClass();
  ASSERT_NE(cc, nullptr);
  // Simply verifying Delete doesn't crash
  cc->Delete();
}

TEST_F(CharClassTest_377, SizeMatchesAddedRunes_377) {
  CharClassBuilder builder;
  builder.AddRange('0', '9');
  builder.AddRange('a', 'f');
  CharClass* cc = builder.GetCharClass();
  ASSERT_NE(cc, nullptr);
  EXPECT_EQ(cc->size(), 16);  // 10 digits + 6 hex letters
  cc->Delete();
}

}  // namespace re2
