#include <gtest/gtest.h>

#include "regexp.h"

#include "utf.h"



using namespace re2;



class CharClassTest_378 : public ::testing::Test {

protected:

    void SetUp() override {

        charClass = CharClass::New(10);

    }



    void TearDown() override {

        charClass->Delete();

    }



    CharClass* charClass;

};



TEST_F(CharClassTest_378, NegateEmptyCharClass_378) {

    // Test negating an empty char class

    CharClass* negated = charClass->Negate();

    EXPECT_EQ(negated->size(), 1);

    EXPECT_TRUE(negated->Contains(0));

    EXPECT_TRUE(negated->Contains(Runemax));

    negated->Delete();

}



TEST_F(CharClassTest_378, NegateFullCharClass_378) {

    // Test negating a full char class

    for (int i = 0; i <= Runemax; ++i) {

        charClass->ranges_[charClass->nranges_++] = RuneRange(i, i);

    }

    CharClass* negated = charClass->Negate();

    EXPECT_EQ(negated->size(), 0);

    EXPECT_FALSE(negated->Contains(0));

    EXPECT_FALSE(negated->Contains(Runemax));

    negated->Delete();

}



TEST_F(CharClassTest_378, NegateSingleRangeCharClass_378) {

    // Test negating a char class with a single range

    charClass->ranges_[charClass->nranges_++] = RuneRange(10, 20);

    CharClass* negated = charClass->Negate();

    EXPECT_EQ(negated->size(), 2);

    EXPECT_TRUE(negated->Contains(9));

    EXPECT_FALSE(negated->Contains(15));

    EXPECT_TRUE(negated->Contains(Runemax));

    negated->Delete();

}



TEST_F(CharClassTest_378, NegateMultipleRangesCharClass_378) {

    // Test negating a char class with multiple ranges

    charClass->ranges_[charClass->nranges_++] = RuneRange(10, 20);

    charClass->ranges_[charClass->nranges_++] = RuneRange(30, 40);

    CharClass* negated = charClass->Negate();

    EXPECT_EQ(negated->size(), 3);

    EXPECT_TRUE(negated->Contains(9));

    EXPECT_FALSE(negated->Contains(15));

    EXPECT_TRUE(negated->Contains(25));

    EXPECT_FALSE(negated->Contains(35));

    EXPECT_TRUE(negated->Contains(Runemax));

    negated->Delete();

}



TEST_F(CharClassTest_378, NegateBoundaryConditions_378) {

    // Test negating a char class with boundary conditions

    charClass->ranges_[charClass->nranges_++] = RuneRange(0, 0);

    charClass->ranges_[charClass->nranges_++] = RuneRange(Runemax, Runemax);

    CharClass* negated = charClass->Negate();

    EXPECT_EQ(negated->size(), 1);

    EXPECT_TRUE(negated->Contains(1));

    EXPECT_TRUE(negated->Contains(Runemax - 1));

    negated->Delete();

}
