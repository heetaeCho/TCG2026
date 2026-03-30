#include <gtest/gtest.h>

#include "TextOutputDev.h"



class TextBlockTest_1205 : public ::testing::Test {

protected:

    TextBlock* textBlock;



    void SetUp() override {

        // Assuming TextPage and other dependencies are properly constructed elsewhere.

        textBlock = new TextBlock(nullptr, 0);

    }



    void TearDown() override {

        delete textBlock;

    }

};



TEST_F(TextBlockTest_1205, GetLinesReturnsNullptrWhenNoLinesAdded_1205) {

    EXPECT_EQ(textBlock->getLines(), nullptr);

}



TEST_F(TextBlockTest_1205, GetNextReturnsNullptrByDefault_1205) {

    EXPECT_EQ(textBlock->getNext(), nullptr);

}



TEST_F(TextBlockTest_1205, GetBBoxSetsCoordinatesCorrectly_1205) {

    double xMin = 0.0, yMin = 0.0, xMax = 0.0, yMax = 0.0;

    textBlock->getBBox(&xMin, &yMin, &xMax, &yMax);

    // Assuming default bounding box coordinates are (0.0, 0.0, 0.0, 0.0) for a new TextBlock.

    EXPECT_DOUBLE_EQ(xMin, 0.0);

    EXPECT_DOUBLE_EQ(yMin, 0.0);

    EXPECT_DOUBLE_EQ(xMax, 0.0);

    EXPECT_DOUBLE_EQ(yMax, 0.0);

}



TEST_F(TextBlockTest_1205, GetLineCountReturnsZeroInitially_1205) {

    EXPECT_EQ(textBlock->getLineCount(), 0);

}
