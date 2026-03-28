#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

// Helper to build a CharClass via CharClassBuilder
class CharClassContainsTest_379 : public ::testing::Test {
protected:
    // We'll use CharClassBuilder to create CharClass instances
};

TEST_F(CharClassContainsTest_379, EmptyCharClassContainsNothing_379) {
    CharClassBuilder builder;
    CharClass* cc = builder.GetCharClass();
    ASSERT_NE(cc, nullptr);
    EXPECT_FALSE(cc->Contains(0));
    EXPECT_FALSE(cc->Contains('a'));
    EXPECT_FALSE(cc->Contains('z'));
    EXPECT_FALSE(cc->Contains(0x10FFFF));
    cc->Delete();
}

TEST_F(CharClassContainsTest_379, SingleRuneContains_379) {
    CharClassBuilder builder;
    builder.AddRange('a', 'a');
    CharClass* cc = builder.GetCharClass();
    ASSERT_NE(cc, nullptr);
    EXPECT_TRUE(cc->Contains('a'));
    EXPECT_FALSE(cc->Contains('b'));
    EXPECT_FALSE(cc->Contains('`'));  // 'a' - 1
    EXPECT_FALSE(cc->Contains(0));
    cc->Delete();
}

TEST_F(CharClassContainsTest_379, SingleRangeContainsBoundaries_379) {
    CharClassBuilder builder;
    builder.AddRange('a', 'z');
    CharClass* cc = builder.GetCharClass();
    ASSERT_NE(cc, nullptr);
    EXPECT_TRUE(cc->Contains('a'));
    EXPECT_TRUE(cc->Contains('z'));
    EXPECT_TRUE(cc->Contains('m'));
    EXPECT_FALSE(cc->Contains('`'));  // 'a' - 1
    EXPECT_FALSE(cc->Contains('{'));  // 'z' + 1
    EXPECT_FALSE(cc->Contains('A'));
    cc->Delete();
}

TEST_F(CharClassContainsTest_379, MultipleDisjointRanges_379) {
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
    EXPECT_FALSE(cc->Contains('`'));
    EXPECT_FALSE(cc->Contains('{'));
    cc->Delete();
}

TEST_F(CharClassContainsTest_379, ManyRangesBinarySearchPath_379) {
    CharClassBuilder builder;
    // Add many disjoint ranges to exercise binary search
    builder.AddRange(10, 20);
    builder.AddRange(30, 40);
    builder.AddRange(50, 60);
    builder.AddRange(70, 80);
    builder.AddRange(90, 100);
    builder.AddRange(110, 120);
    builder.AddRange(130, 140);
    builder.AddRange(150, 160);
    CharClass* cc = builder.GetCharClass();
    ASSERT_NE(cc, nullptr);
    
    // Check contained values
    EXPECT_TRUE(cc->Contains(10));
    EXPECT_TRUE(cc->Contains(15));
    EXPECT_TRUE(cc->Contains(20));
    EXPECT_TRUE(cc->Contains(90));
    EXPECT_TRUE(cc->Contains(95));
    EXPECT_TRUE(cc->Contains(100));
    EXPECT_TRUE(cc->Contains(150));
    EXPECT_TRUE(cc->Contains(160));
    
    // Check gaps
    EXPECT_FALSE(cc->Contains(0));
    EXPECT_FALSE(cc->Contains(9));
    EXPECT_FALSE(cc->Contains(21));
    EXPECT_FALSE(cc->Contains(25));
    EXPECT_FALSE(cc->Contains(29));
    EXPECT_FALSE(cc->Contains(41));
    EXPECT_FALSE(cc->Contains(89));
    EXPECT_FALSE(cc->Contains(101));
    EXPECT_FALSE(cc->Contains(161));
    EXPECT_FALSE(cc->Contains(200));
    cc->Delete();
}

TEST_F(CharClassContainsTest_379, ContainsZeroRune_379) {
    CharClassBuilder builder;
    builder.AddRange(0, 0);
    CharClass* cc = builder.GetCharClass();
    ASSERT_NE(cc, nullptr);
    EXPECT_TRUE(cc->Contains(0));
    EXPECT_FALSE(cc->Contains(1));
    cc->Delete();
}

TEST_F(CharClassContainsTest_379, ContainsMaxUnicodeRune_379) {
    CharClassBuilder builder;
    builder.AddRange(0x10FFFF, 0x10FFFF);
    CharClass* cc = builder.GetCharClass();
    ASSERT_NE(cc, nullptr);
    EXPECT_TRUE(cc->Contains(0x10FFFF));
    EXPECT_FALSE(cc->Contains(0x10FFFE));
    cc->Delete();
}

TEST_F(CharClassContainsTest_379, FullRange_379) {
    CharClassBuilder builder;
    builder.AddRange(0, 0x10FFFF);
    CharClass* cc = builder.GetCharClass();
    ASSERT_NE(cc, nullptr);
    EXPECT_TRUE(cc->Contains(0));
    EXPECT_TRUE(cc->Contains(0x10FFFF));
    EXPECT_TRUE(cc->Contains('a'));
    EXPECT_TRUE(cc->Contains(0x5000));
    cc->Delete();
}

TEST_F(CharClassContainsTest_379, NegateAndContains_379) {
    CharClassBuilder builder;
    builder.AddRange('a', 'z');
    CharClass* cc = builder.GetCharClass();
    ASSERT_NE(cc, nullptr);
    
    CharClass* negated = cc->Negate();
    ASSERT_NE(negated, nullptr);
    
    EXPECT_FALSE(negated->Contains('a'));
    EXPECT_FALSE(negated->Contains('m'));
    EXPECT_FALSE(negated->Contains('z'));
    EXPECT_TRUE(negated->Contains('A'));
    EXPECT_TRUE(negated->Contains('0'));
    EXPECT_TRUE(negated->Contains('{'));
    EXPECT_TRUE(negated->Contains(0));
    
    cc->Delete();
    negated->Delete();
}

TEST_F(CharClassContainsTest_379, SizeAndEmpty_379) {
    CharClassBuilder builder;
    CharClass* cc = builder.GetCharClass();
    ASSERT_NE(cc, nullptr);
    EXPECT_TRUE(cc->empty());
    EXPECT_EQ(cc->size(), 0);
    cc->Delete();
}

TEST_F(CharClassContainsTest_379, SizeNonEmpty_379) {
    CharClassBuilder builder;
    builder.AddRange('a', 'z');
    CharClass* cc = builder.GetCharClass();
    ASSERT_NE(cc, nullptr);
    EXPECT_FALSE(cc->empty());
    EXPECT_EQ(cc->size(), 1);
    cc->Delete();
}

TEST_F(CharClassContainsTest_379, AdjacentRangesLeftBoundary_379) {
    CharClassBuilder builder;
    builder.AddRange(10, 19);
    builder.AddRange(20, 29);
    CharClass* cc = builder.GetCharClass();
    ASSERT_NE(cc, nullptr);
    // Adjacent ranges may be merged by the builder
    EXPECT_TRUE(cc->Contains(10));
    EXPECT_TRUE(cc->Contains(19));
    EXPECT_TRUE(cc->Contains(20));
    EXPECT_TRUE(cc->Contains(29));
    EXPECT_FALSE(cc->Contains(9));
    EXPECT_FALSE(cc->Contains(30));
    cc->Delete();
}

TEST_F(CharClassContainsTest_379, ThreeRangesMiddleElement_379) {
    CharClassBuilder builder;
    builder.AddRange(10, 20);
    builder.AddRange(50, 60);
    builder.AddRange(90, 100);
    CharClass* cc = builder.GetCharClass();
    ASSERT_NE(cc, nullptr);
    
    // Middle range
    EXPECT_TRUE(cc->Contains(50));
    EXPECT_TRUE(cc->Contains(55));
    EXPECT_TRUE(cc->Contains(60));
    
    // Gaps
    EXPECT_FALSE(cc->Contains(21));
    EXPECT_FALSE(cc->Contains(49));
    EXPECT_FALSE(cc->Contains(61));
    EXPECT_FALSE(cc->Contains(89));
    cc->Delete();
}

}  // namespace re2
