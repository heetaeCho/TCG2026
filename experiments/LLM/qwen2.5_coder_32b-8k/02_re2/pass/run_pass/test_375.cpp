#include <gtest/gtest.h>

#include "re2/regexp.h"



using namespace re2;



class CharClassBuilderTest_375 : public ::testing::Test {

protected:

    CharClassBuilder builder;

};



TEST_F(CharClassBuilderTest_375, RemoveAbove_BelowRuneself_375) {

    builder.AddRange(0, 128);

    builder.RemoveAbove('z');

    EXPECT_TRUE(builder.Contains('a'));

    EXPECT_TRUE(builder.Contains('z'));

    EXPECT_FALSE(builder.Contains('{'));

}



TEST_F(CharClassBuilderTest_375, RemoveAbove_AboveRuneself_375) {

    builder.AddRange(0, 200);

    builder.RemoveAbove(Runeself);

    EXPECT_TRUE(builder.Contains('a'));

    EXPECT_FALSE(builder.Contains('z' + 1));

}



TEST_F(CharClassBuilderTest_375, RemoveAbove_AtRunemax_375) {

    builder.AddRange(0, Runemax);

    builder.RemoveAbove(Runemax);

    EXPECT_TRUE(builder.Contains(Runemax - 1));

    EXPECT_FALSE(builder.Contains(Runemax));

}



TEST_F(CharClassBuilderTest_375, RemoveAbove_AboveRunemax_375) {

    builder.AddRange(0, Runemax);

    builder.RemoveAbove(Runemax + 1);

    EXPECT_TRUE(builder.Contains(Runemax - 1));

    EXPECT_TRUE(builder.Contains(Runemax));

}



TEST_F(CharClassBuilderTest_375, RemoveAbove_LowerRange_375) {

    builder.AddRange('a', 'z');

    builder.RemoveAbove('m');

    EXPECT_TRUE(builder.Contains('a'));

    EXPECT_TRUE(builder.Contains('m'));

    EXPECT_FALSE(builder.Contains('n'));

    EXPECT_FALSE(builder.Contains('z'));

}



TEST_F(CharClassBuilderTest_375, RemoveAbove_UpperRange_375) {

    builder.AddRange('A', 'Z');

    builder.RemoveAbove('M');

    EXPECT_TRUE(builder.Contains('A'));

    EXPECT_TRUE(builder.Contains('M'));

    EXPECT_FALSE(builder.Contains('N'));

    EXPECT_FALSE(builder.Contains('Z'));

}



TEST_F(CharClassBuilderTest_375, RemoveAbove_NoRange_375) {

    builder.AddRange(100, 200);

    builder.RemoveAbove(99);

    EXPECT_FALSE(builder.Contains(100));

    EXPECT_FALSE(builder.Contains(200));

}



TEST_F(CharClassBuilderTest_375, RemoveAbove_EmptyRange_375) {

    builder.RemoveAbove('z');

    EXPECT_TRUE(builder.empty());

}
