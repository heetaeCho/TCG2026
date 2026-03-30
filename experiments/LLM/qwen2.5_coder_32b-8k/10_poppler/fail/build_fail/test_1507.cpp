#include <gtest/gtest.h>

#include "CIDFontsWidthsBuilder.h"

#include <vector>



class CIDFontsWidthsBuilderTest_1507 : public ::testing::Test {

protected:

    CIDFontsWidthsBuilder builder;

};



TEST_F(CIDFontsWidthsBuilderTest_1507, AddWidth_NormalOperation_1507) {

    builder.addWidth(0, 10);

    builder.addWidth(1, 20);

    builder.addWidth(2, 30);



    // Assuming takeSegments() can be used to verify the internal state

    std::vector<Segment> segments = builder.takeSegments();

    EXPECT_EQ(segments.size(), 1); // All indices are in the same segment

}



TEST_F(CIDFontsWidthsBuilderTest_1507, AddWidth_BoundaryCondition_StartIndex_1507) {

    builder.addWidth(0, 10);



    std::vector<Segment> segments = builder.takeSegments();

    EXPECT_EQ(segments.size(), 1);

}



TEST_F(CIDFontsWidthsBuilderTest_1507, AddWidth_BoundaryCondition_MaxIntIndex_1507) {

    builder.addWidth(INT_MAX - 2, 10);

    builder.addWidth(INT_MAX - 1, 20);

    builder.addWidth(INT_MAX, 30);



    std::vector<Segment> segments = builder.takeSegments();

    EXPECT_EQ(segments.size(), 1);

}



TEST_F(CIDFontsWidthsBuilderTest_1507, AddWidth_ErrorCase_DuplicateIndex_1507) {

    builder.addWidth(0, 10);

    ASSERT_DEATH(builder.addWidth(0, 20), ".*"); // Expect assertion failure

}



TEST_F(CIDFontsWidthsBuilderTest_1507, AddWidth_ErrorCase_DecreasingIndex_1507) {

    builder.addWidth(2, 30);

    ASSERT_DEATH(builder.addWidth(1, 20), ".*"); // Expect assertion failure

}
