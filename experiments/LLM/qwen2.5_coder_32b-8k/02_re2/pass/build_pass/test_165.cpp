#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "regexp.h"



using namespace re2;



class CharClassBuilderTest_165 : public ::testing::Test {

protected:

    void SetUp() override {

        charClassBuilder = new CharClassBuilder();

    }



    void TearDown() override {

        delete charClassBuilder;

    }



    CharClassBuilder* charClassBuilder;

};



TEST_F(CharClassBuilderTest_165, SizeInitiallyZero_165) {

    EXPECT_EQ(charClassBuilder->size(), 0);

}



TEST_F(CharClassBuilderTest_165, AddRangeIncreasesSize_165) {

    Rune lo = 'a';

    Rune hi = 'z';

    charClassBuilder->AddRange(lo, hi);

    EXPECT_EQ(charClassBuilder->size(), 1);

}



TEST_F(CharClassBuilderTest_165, AddMultipleRangesIncreasesSize_165) {

    charClassBuilder->AddRange('a', 'z');

    charClassBuilder->AddRange('A', 'Z');

    EXPECT_EQ(charClassBuilder->size(), 2);

}



TEST_F(CharClassBuilderTest_165, AddOverlappingRangesDoesNotIncreaseSize_165) {

    charClassBuilder->AddRange('a', 'm');

    charClassBuilder->AddRange('l', 'z');

    EXPECT_EQ(charClassBuilder->size(), 1);

}



TEST_F(CharClassBuilderTest_165, RemoveAboveReducesSize_165) {

    charClassBuilder->AddRange('a', 'z');

    charClassBuilder->RemoveAbove('m');

    EXPECT_EQ(charClassBuilder->size(), 1);

}



TEST_F(CharClassBuilderTest_165, NegateChangesContent_165) {

    charClassBuilder->AddRange('a', 'z');

    int initialSize = charClassBuilder->size();

    charClassBuilder->Negate();

    EXPECT_NE(charClassBuilder->size(), initialSize);

}



TEST_F(CharClassBuilderTest_165, EmptyInitiallyTrue_165) {

    EXPECT_TRUE(charClassBuilder->empty());

}



TEST_F(CharClassBuilderTest_165, EmptyFalseAfterAddRange_165) {

    charClassBuilder->AddRange('a', 'z');

    EXPECT_FALSE(charClassBuilder->empty());

}



TEST_F(CharClassBuilderTest_165, FullInitiallyFalse_165) {

    EXPECT_FALSE(charClassBuilder->full());

}



// Assuming full means the entire range of Rune is covered

TEST_F(CharClassBuilderTest_165, FullTrueAfterFullRangeAdd_165) {

    charClassBuilder->AddRange(std::numeric_limits<Rune>::min(), std::numeric_limits<Rune>::max());

    EXPECT_TRUE(charClassBuilder->full());

}



TEST_F(CharClassBuilderTest_165, ContainsReturnsFalseInitially_165) {

    Rune testRune = 'a';

    EXPECT_FALSE(charClassBuilder->Contains(testRune));

}



TEST_F(CharClassBuilderTest_165, ContainsReturnsTrueAfterAddRange_165) {

    Rune testRune = 'a';

    charClassBuilder->AddRange('a', 'z');

    EXPECT_TRUE(charClassBuilder->Contains(testRune));

}



TEST_F(CharClassBuilderTest_165, FoldsASCIIFalseInitially_165) {

    EXPECT_FALSE(charClassBuilder->FoldsASCII());

}
