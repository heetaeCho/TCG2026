#include <gtest/gtest.h>

#include "re2/regexp.h"

#include "util/utf.h"



using namespace re2;



class CharClassBuilderTest_376 : public ::testing::Test {

protected:

    CharClassBuilder builder;

};



TEST_F(CharClassBuilderTest_376, NegateEmptyRange_376) {

    builder.Negate();

    EXPECT_TRUE(builder.full());

}



TEST_F(CharClassBuilderTest_376, NegateSingleRangeFull_376) {

    builder.AddRange(0, Runemax);

    builder.Negate();

    EXPECT_TRUE(builder.empty());

}



TEST_F(CharClassBuilderTest_376, NegateSingleRangeStart_376) {

    builder.AddRange(0, 10);

    builder.Negate();

    EXPECT_EQ(builder.size(), 2);

    auto it = builder.begin();

    EXPECT_EQ(it->lo, 11);

    EXPECT_EQ(it->hi, Runemax);

    ++it;

    EXPECT_EQ(it->lo, 0);

    EXPECT_EQ(it->hi, 0); // This range will be invalid but the primary check is the above

}



TEST_F(CharClassBuilderTest_376, NegateSingleRangeMiddle_376) {

    builder.AddRange(10, 20);

    builder.Negate();

    EXPECT_EQ(builder.size(), 2);

    auto it = builder.begin();

    EXPECT_EQ(it->lo, 0);

    EXPECT_EQ(it->hi, 9);

    ++it;

    EXPECT_EQ(it->lo, 21);

    EXPECT_EQ(it->hi, Runemax);

}



TEST_F(CharClassBuilderTest_376, NegateMultipleRanges_376) {

    builder.AddRange(0, 5);

    builder.AddRange(10, 15);

    builder.Negate();

    EXPECT_EQ(builder.size(), 3);

    auto it = builder.begin();

    EXPECT_EQ(it->lo, 6);

    EXPECT_EQ(it->hi, 9);

    ++it;

    EXPECT_EQ(it->lo, 16);

    EXPECT_EQ(it->hi, Runemax);

    ++it;

    EXPECT_EQ(it->lo, 0);

    EXPECT_EQ(it->hi, 0); // This range will be invalid but the primary check is the above

}
