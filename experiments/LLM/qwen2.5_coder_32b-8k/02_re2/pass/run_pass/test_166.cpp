#include <gtest/gtest.h>

#include "re2/regexp.h"



using namespace re2;



class CharClassBuilderTest_166 : public ::testing::Test {

protected:

    CharClassBuilder builder;

};



TEST_F(CharClassBuilderTest_166, EmptyInitially_166) {

    EXPECT_TRUE(builder.empty());

}



TEST_F(CharClassBuilderTest_166, NotEmptyAfterAddingRange_166) {

    Rune lo = 97; // 'a'

    Rune hi = 122; // 'z'

    builder.AddRange(lo, hi);

    EXPECT_FALSE(builder.empty());

}



TEST_F(CharClassBuilderTest_166, SizeIncreasesWithAddRange_166) {

    int initialSize = builder.size();

    Rune lo = 97; // 'a'

    Rune hi = 122; // 'z'

    builder.AddRange(lo, hi);

    EXPECT_GT(builder.size(), initialSize);

}



TEST_F(CharClassBuilderTest_166, AddRangeWithSameValuesDoesNotIncreaseSize_166) {

    int initialSize = builder.size();

    Rune value = 97; // 'a'

    builder.AddRange(value, value);

    EXPECT_EQ(builder.size(), initialSize);

}



TEST_F(CharClassBuilderTest_166, RemoveAboveReducesSize_166) {

    Rune lo = 97; // 'a'

    Rune hi = 122; // 'z'

    builder.AddRange(lo, hi);

    int sizeBeforeRemoval = builder.size();

    Rune threshold = 100; // 'd'

    builder.RemoveAbove(threshold);

    EXPECT_LT(builder.size(), sizeBeforeRemoval);

}



TEST_F(CharClassBuilderTest_166, NegateChangesContents_166) {

    Rune lo = 97; // 'a'

    Rune hi = 122; // 'z'

    builder.AddRange(lo, hi);

    bool wasEmpty = builder.empty();

    builder.Negate();

    EXPECT_NE(builder.empty(), wasEmpty);

}



TEST_F(CharClassBuilderTest_166, FullAfterNegateIfInitiallyEmpty_166) {

    EXPECT_TRUE(builder.empty());

    builder.Negate();

    EXPECT_TRUE(builder.full());

}
