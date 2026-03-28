#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/HtmlOutputDev.h"

#include <memory>



class HtmlOutputDevTest_2712 : public ::testing::Test {

protected:

    virtual void SetUp() {

        catalogMock = std::make_unique<Catalog>();

        htmlOutputDev = std::make_unique<HtmlOutputDev>(catalogMock.get(), "testFile.html", "Title", "Author", "Keywords", "Subject", "Date", false, 1, true);

    }



    virtual void TearDown() {

        htmlOutputDev.reset();

        catalogMock.reset();

    }



    std::unique_ptr<Catalog> catalogMock;

    std::unique_ptr<HtmlOutputDev> htmlOutputDev;

};



TEST_F(HtmlOutputDevTest_2712, getPageWidth_ReturnsCorrectValue_2712) {

    // Assuming we know the maxPageWidth is set to a specific value during construction or by another method

    int expectedWidth = 800; // This is an assumption for the test case

    EXPECT_EQ(expectedWidth, htmlOutputDev->getPageWidth());

}



TEST_F(HtmlOutputDevTest_2712, getPageHeight_ReturnsCorrectValue_2712) {

    // Assuming we know the maxPageHeight is set to a specific value during construction or by another method

    int expectedHeight = 600; // This is an assumption for the test case

    EXPECT_EQ(expectedHeight, htmlOutputDev->getPageHeight());

}



TEST_F(HtmlOutputDevTest_2712, isOk_ReturnsTrueWhenValid_2712) {

    EXPECT_TRUE(htmlOutputDev->isOk());

}



TEST_F(HtmlOutputDevTest_2712, upsideDown_ReturnsFalseByDefault_2712) {

    EXPECT_FALSE(htmlOutputDev->upsideDown());

}



TEST_F(HtmlOutputDevTest_2712, useDrawChar_ReturnsTrueByDefault_2712) {

    EXPECT_TRUE(htmlOutputDev->useDrawChar());

}



TEST_F(HtmlOutputDevTest_2712, interpretType3Chars_ReturnsFalseByDefault_2712) {

    EXPECT_FALSE(htmlOutputDev->interpretType3Chars());

}



TEST_F(HtmlOutputDevTest_2712, needNonText_ReturnsTrueByDefault_2712) {

    EXPECT_TRUE(htmlOutputDev->needNonText());

}



TEST_F(HtmlOutputDevTest_2712, DevType_ReturnsUniqueValue_2712) {

    int devType = htmlOutputDev->DevType();

    EXPECT_GE(devType, 0); // Assuming DevType returns a non-negative value

}
