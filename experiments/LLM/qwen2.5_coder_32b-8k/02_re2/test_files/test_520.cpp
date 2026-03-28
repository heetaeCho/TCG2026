#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/regexp.h"

#include "re2/parse.cc"



using namespace re2;



class CharClassBuilderTest_520 : public ::testing::Test {

protected:

    CharClassBuilder builder;

};



TEST_F(CharClassBuilderTest_520, NormalRangeAddition_520) {

    EXPECT_TRUE(builder.AddRange(97, 122)); // 'a' to 'z'

}



TEST_F(CharClassBuilderTest_520, RangeWithNewlineExcluded_520) {

    builder.AddRangeFlags('\n', '\n', Regexp::NeverNL);

    EXPECT_FALSE(builder.Contains('\n'));

}



TEST_F(CharClassBuilderTest_520, RangeWithNewlineIncluded_520) {

    builder.AddRangeFlags('a', 'z', Regexp::ClassNL);

    EXPECT_TRUE(builder.Contains('\n'));

}



TEST_F(CharClassBuilderTest_520, FoldCaseLatin1_520) {

    builder.AddRangeFlags('A', 'Z', Regexp::FoldCase | Regexp::Latin1);

    EXPECT_TRUE(builder.Contains('a'));

}



TEST_F(CharClassBuilderTest_520, FoldCaseUnicode_520) {

    builder.AddRangeFlags('A', 'Z', Regexp::FoldCase);

    EXPECT_TRUE(builder.Contains('a'));

}



TEST_F(CharClassBuilderTest_520, EmptyRangeAddition_520) {

    EXPECT_FALSE(builder.AddRange(97, 96)); // Invalid range

}



TEST_F(CharClassBuilderTest_520, LargeRangeAddition_520) {

    EXPECT_TRUE(builder.AddRange(1, 0x10FFFF)); // Full Unicode range

}



TEST_F(CharClassBuilderTest_520, BoundaryConditionWithNewline_520) {

    builder.AddRangeFlags('\n', '\n', Regexp::NeverNL | Regexp::ClassNL);

    EXPECT_FALSE(builder.Contains('\n'));

}



TEST_F(CharClassBuilderTest_520, RangeSplittingAroundNewline_520) {

    builder.AddRangeFlags(97, 101, Regexp::NeverNL); // 'a' to 'e'

    EXPECT_TRUE(builder.Contains('a'));

    EXPECT_FALSE(builder.Contains('\n'));

    EXPECT_TRUE(builder.Contains('e'));

}
