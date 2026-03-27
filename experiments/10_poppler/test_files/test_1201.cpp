#include <gtest/gtest.h>

#include "TextOutputDev.h"



class TextLineTest : public ::testing::Test {

protected:

    PDFRectangle pdfRect;

    TextBlock* textBlock;

    TextLine* textLine;



    void SetUp() override {

        pdfRect = {0, 0, 10, 10};

        textBlock = new TextBlock(); // Assuming TextBlock has a default constructor

        textLine = new TextLine(textBlock, 0, 0.0);

    }



    void TearDown() override {

        delete textLine;

        delete textBlock;

    }

};



TEST_F(TextLineTest_1201, GetBBox_ReturnsCorrectRectangle_1201) {

    // Assuming the bounding box is initialized correctly in the constructor

    PDFRectangle bbox = textLine->getBBox();

    EXPECT_EQ(bbox.xMin, 0);

    EXPECT_EQ(bbox.yMin, 0);

    EXPECT_EQ(bbox.xMax, 10);

    EXPECT_EQ(bbox.yMax, 10);

}



TEST_F(TextLineTest_1201, GetWords_ReturnsNullPointerInitially_1201) {

    // Assuming no words are added initially

    const TextWord* words = textLine->getWords();

    EXPECT_EQ(words, nullptr);

}



TEST_F(TextLineTest_1201, GetNext_ReturnsNullPointerInitially_1201) {

    // Assuming no next line is linked initially

    const TextLine* nextLine = textLine->getNext();

    EXPECT_EQ(nextLine, nullptr);

}



TEST_F(TextLineTest_1201, IsHyphenated_ReturnsFalseInitially_1201) {

    // Assuming hyphenation status is false initially

    bool isHyph = textLine->isHyphenated();

    EXPECT_FALSE(isHyph);

}
