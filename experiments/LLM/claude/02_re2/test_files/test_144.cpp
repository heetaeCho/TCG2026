#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/parse.h"

namespace re2 {

class CharClassTest_144 : public ::testing::Test {
 protected:
  // Helper to build a CharClass via CharClassBuilder
  CharClass* MakeCharClass(const std::vector<std::pair<Rune, Rune>>& ranges) {
    CharClassBuilder builder;
    for (const auto& range : ranges) {
      builder.AddRange(range.first, range.second);
    }
    return builder.GetCharClass();
  }
};

TEST_F(CharClassTest_144, EmptyCharClass_144) {
  CharClass* cc = MakeCharClass({});
  ASSERT_NE(cc, nullptr);
  EXPECT_TRUE(cc->empty());
  EXPECT_FALSE(cc->full());
  EXPECT_EQ(cc->size(), 0);
  EXPECT_EQ(cc->begin(), cc->end());
  EXPECT_FALSE(cc->Contains('a'));
  EXPECT_FALSE(cc->Contains('Z'));
  cc->Delete();
}

TEST_F(CharClassTest_144, SingleCharContains_144) {
  CharClass* cc = MakeCharClass({{'a', 'a'}});
  ASSERT_NE(cc, nullptr);
  EXPECT_FALSE(cc->empty());
  EXPECT_EQ(cc->size(), 1);
  EXPECT_TRUE(cc->Contains('a'));
  EXPECT_FALSE(cc->Contains('b'));
  EXPECT_FALSE(cc->Contains('A'));
  cc->Delete();
}

TEST_F(CharClassTest_144, RangeContains_144) {
  CharClass* cc = MakeCharClass({{'a', 'z'}});
  ASSERT_NE(cc, nullptr);
  EXPECT_FALSE(cc->empty());
  EXPECT_TRUE(cc->Contains('a'));
  EXPECT_TRUE(cc->Contains('m'));
  EXPECT_TRUE(cc->Contains('z'));
  EXPECT_FALSE(cc->Contains('A'));
  EXPECT_FALSE(cc->Contains('0'));
  cc->Delete();
}

TEST_F(CharClassTest_144, MultipleRanges_144) {
  CharClass* cc = MakeCharClass({{'a', 'z'}, {'A', 'Z'}, {'0', '9'}});
  ASSERT_NE(cc, nullptr);
  EXPECT_FALSE(cc->empty());
  EXPECT_TRUE(cc->Contains('a'));
  EXPECT_TRUE(cc->Contains('Z'));
  EXPECT_TRUE(cc->Contains('5'));
  EXPECT_FALSE(cc->Contains('!'));
  EXPECT_FALSE(cc->Contains(' '));
  cc->Delete();
}

TEST_F(CharClassTest_144, IteratorTraversal_144) {
  CharClass* cc = MakeCharClass({{'a', 'c'}, {'x', 'z'}});
  ASSERT_NE(cc, nullptr);
  int count = 0;
  for (auto it = cc->begin(); it != cc->end(); ++it) {
    count++;
  }
  EXPECT_EQ(count, cc->size());
  cc->Delete();
}

TEST_F(CharClassTest_144, NegateCharClass_144) {
  CharClass* cc = MakeCharClass({{'a', 'z'}});
  ASSERT_NE(cc, nullptr);
  EXPECT_TRUE(cc->Contains('a'));
  EXPECT_FALSE(cc->Contains('A'));

  CharClass* neg = cc->Negate();
  ASSERT_NE(neg, nullptr);
  EXPECT_FALSE(neg->Contains('a'));
  EXPECT_FALSE(neg->Contains('m'));
  EXPECT_TRUE(neg->Contains('A'));
  EXPECT_TRUE(neg->Contains('0'));
  EXPECT_TRUE(neg->Contains('!'));

  neg->Delete();
  cc->Delete();
}

TEST_F(CharClassTest_144, NegateEmptyIsFull_144) {
  CharClass* cc = MakeCharClass({});
  ASSERT_NE(cc, nullptr);
  EXPECT_TRUE(cc->empty());

  CharClass* neg = cc->Negate();
  ASSERT_NE(neg, nullptr);
  EXPECT_TRUE(neg->full());
  EXPECT_TRUE(neg->Contains('a'));
  EXPECT_TRUE(neg->Contains(0));

  neg->Delete();
  cc->Delete();
}

TEST_F(CharClassTest_144, SizeMatchesRangeCount_144) {
  CharClass* cc = MakeCharClass({{'a', 'a'}, {'c', 'c'}, {'e', 'e'}});
  ASSERT_NE(cc, nullptr);
  EXPECT_EQ(cc->size(), 3);
  cc->Delete();
}

TEST_F(CharClassTest_144, ContainsBoundaryValues_144) {
  CharClass* cc = MakeCharClass({{'b', 'y'}});
  ASSERT_NE(cc, nullptr);
  EXPECT_FALSE(cc->Contains('a'));
  EXPECT_TRUE(cc->Contains('b'));
  EXPECT_TRUE(cc->Contains('y'));
  EXPECT_FALSE(cc->Contains('z'));
  cc->Delete();
}

TEST_F(CharClassTest_144, SingleRuneRange_144) {
  CharClass* cc = MakeCharClass({{0, 0}});
  ASSERT_NE(cc, nullptr);
  EXPECT_TRUE(cc->Contains(0));
  EXPECT_FALSE(cc->Contains(1));
  EXPECT_EQ(cc->size(), 1);
  cc->Delete();
}

TEST_F(CharClassTest_144, FullCharClassAfterWideRange_144) {
  // Create a char class covering all of Unicode
  CharClass* cc = MakeCharClass({{0, Runemax}});
  ASSERT_NE(cc, nullptr);
  EXPECT_TRUE(cc->full());
  EXPECT_FALSE(cc->empty());
  EXPECT_TRUE(cc->Contains(0));
  EXPECT_TRUE(cc->Contains('a'));
  EXPECT_TRUE(cc->Contains(Runemax));
  cc->Delete();
}

TEST_F(CharClassTest_144, DoubleNegateRestoresOriginal_144) {
  CharClass* cc = MakeCharClass({{'A', 'Z'}});
  ASSERT_NE(cc, nullptr);

  CharClass* neg1 = cc->Negate();
  CharClass* neg2 = neg1->Negate();

  EXPECT_TRUE(neg2->Contains('A'));
  EXPECT_TRUE(neg2->Contains('Z'));
  EXPECT_FALSE(neg2->Contains('a'));

  neg2->Delete();
  neg1->Delete();
  cc->Delete();
}

TEST_F(CharClassTest_144, BeginEndForSingleRange_144) {
  CharClass* cc = MakeCharClass({{'0', '9'}});
  ASSERT_NE(cc, nullptr);
  auto it = cc->begin();
  ASSERT_NE(it, cc->end());
  EXPECT_EQ(it->lo, '0');
  EXPECT_EQ(it->hi, '9');
  ++it;
  EXPECT_EQ(it, cc->end());
  cc->Delete();
}

}  // namespace re2
