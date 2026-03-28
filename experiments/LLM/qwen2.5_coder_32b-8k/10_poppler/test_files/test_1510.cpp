#include <gtest/gtest.h>

#include "CIDFontsWidthsBuilder.h"

#include <optional>

#include <vector>



using namespace std;



class CIDFontsWidthsBuilderTest : public ::testing::Test {

protected:

    CIDFontsWidthsBuilder::SegmentBuilder segmentBuilder;

};



TEST_F(CIDFontsWidthsBuilderTest_1510, AcceptSingleValue_1510) {

    EXPECT_TRUE(segmentBuilder.accept(0, 10));

}



TEST_F(CIDFontsWidthsBuilderTest_1510, AcceptMultipleSameValues_1510) {

    segmentBuilder.accept(0, 10);

    segmentBuilder.accept(1, 10);

    segmentBuilder.accept(2, 10);

    EXPECT_TRUE(segmentBuilder.accept(3, 10));

}



TEST_F(CIDFontsWidthsBuilderTest_1510, AcceptMultipleDifferentValues_1510) {

    segmentBuilder.accept(0, 10);

    segmentBuilder.accept(1, 20);

    EXPECT_FALSE(segmentBuilder.accept(2, 30));

}



TEST_F(CIDFontsWidthsBuilderTest_1510, BuildSingleValueSegment_1510) {

    segmentBuilder.accept(0, 10);

    auto segment = segmentBuilder.build();

    ASSERT_EQ(std::holds_alternative<CIDFontsWidthsBuilder::RangeSegment>(segment), true);

    EXPECT_EQ(std::get<CIDFontsWidthsBuilder::RangeSegment>(segment).first, 0);

    EXPECT_EQ(std::get<CIDFontsWidthsBuilder::RangeSegment>(segment).last, 0);

    EXPECT_EQ(std::get<CIDFontsWidthsBuilder::RangeSegment>(segment).width, 10);

}



TEST_F(CIDFontsWidthsBuilderTest_1510, BuildMultipleSameValuesSegment_1510) {

    segmentBuilder.accept(0, 10);

    segmentBuilder.accept(1, 10);

    segmentBuilder.accept(2, 10);

    segmentBuilder.accept(3, 10);

    auto segment = segmentBuilder.build();

    ASSERT_EQ(std::holds_alternative<CIDFontsWidthsBuilder::RangeSegment>(segment), true);

    EXPECT_EQ(std::get<CIDFontsWidthsBuilder::RangeSegment>(segment).first, 0);

    EXPECT_EQ(std::get<CIDFontsWidthsBuilder::RangeSegment>(segment).last, 3);

    EXPECT_EQ(std::get<CIDFontsWidthsBuilder::RangeSegment>(segment).width, 10);

}



TEST_F(CIDFontsWidthsBuilderTest_1510, BuildMultipleDifferentValuesSegment_1510) {

    segmentBuilder.accept(0, 10);

    segmentBuilder.accept(1, 20);

    segmentBuilder.accept(2, 30);

    auto segment = segmentBuilder.build();

    ASSERT_EQ(std::holds_alternative<CIDFontsWidthsBuilder::ListSegment>(segment), true);

    EXPECT_EQ(std::get<CIDFontsWidthsBuilder::ListSegment>(segment).widths, std::vector<int>({10, 20, 30}));

}



TEST_F(CIDFontsWidthsBuilderTest_1510, BuildMixedValuesSegment_1510) {

    segmentBuilder.accept(0, 10);

    segmentBuilder.accept(1, 10);

    segmentBuilder.accept(2, 10);

    segmentBuilder.accept(3, 20);

    segmentBuilder.accept(4, 20);

    auto segment = segmentBuilder.build();

    ASSERT_EQ(std::holds_alternative<CIDFontsWidthsBuilder::RangeSegment>(segment), true);

    EXPECT_EQ(std::get<CIDFontsWidthsBuilder::RangeSegment>(segment).first, 3);

    EXPECT_EQ(std::get<CIDFontsWidthsBuilder::RangeSegment>(segment).last, 4);

    EXPECT_EQ(std::get<CIDFontsWidthsBuilder::RangeSegment>(segment).width, 20);

}



TEST_F(CIDFontsWidthsBuilderTest_1510, BuildBoundaryCondition_1510) {

    segmentBuilder.accept(0, 10);

    segmentBuilder.accept(1, 10);

    segmentBuilder.accept(2, 10);

    segmentBuilder.accept(3, 10);

    segmentBuilder.accept(4, 10);

    auto segment = segmentBuilder.build();

    ASSERT_EQ(std::holds_alternative<CIDFontsWidthsBuilder::RangeSegment>(segment), true);

    EXPECT_EQ(std::get<CIDFontsWidthsBuilder::RangeSegment>(segment).first, 0);

    EXPECT_EQ(std::get<CIDFontsWidthsBuilder::RangeSegment>(segment).last, 4);

    EXPECT_EQ(std::get<CIDFontsWidthsBuilder::RangeSegment>(segment).width, 10);

}



TEST_F(CIDFontsWidthsBuilderTest_1510, BuildEmptySegment_1510) {

    auto segment = segmentBuilder.build();

    ASSERT_EQ(std::holds_alternative<CIDFontsWidthsBuilder::ListSegment>(segment), true);

    EXPECT_TRUE(std::get<CIDFontsWidthsBuilder::ListSegment>(segment).widths.empty());

}
