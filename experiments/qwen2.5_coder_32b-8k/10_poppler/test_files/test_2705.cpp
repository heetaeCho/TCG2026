#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/utils/HtmlOutputDev.h"



class HtmlOutputDevTest : public ::testing::Test {

protected:

    HtmlOutputDev* htmlOutputDev;



    virtual void SetUp() {

        // Assuming a constructor that doesn't require parameters for testing purposes

        htmlOutputDev = new HtmlOutputDev(nullptr, "", "", "", "", "", "", false, 0, false);

    }



    virtual void TearDown() {

        delete htmlOutputDev;

    }

};



TEST_F(HtmlOutputDevTest_2705, IsOk_ReturnsTrue_2705) {

    EXPECT_TRUE(htmlOutputDev->isOk());

}



TEST_F(HtmlOutputDevTest_2705, AddBackgroundImage_DoesNotCrash_2705) {

    htmlOutputDev->addBackgroundImage("test_image.png");

}



TEST_F(HtmlOutputDevTest_2705, DumpDocOutline_ReturnsFalse_WhenNoCatalog_2705) {

    EXPECT_FALSE(htmlOutputDev->dumpDocOutline(nullptr));

}



TEST_F(HtmlOutputDevTest_2705, UpsideDown_ReturnsFalse_2705) {

    EXPECT_FALSE(htmlOutputDev->upsideDown());

}



TEST_F(HtmlOutputDevTest_2705, UseDrawChar_ReturnsTrue_2705) {

    EXPECT_TRUE(htmlOutputDev->useDrawChar());

}



TEST_F(HtmlOutputDevTest_2705, InterpretType3Chars_ReturnsFalse_2705) {

    EXPECT_FALSE(htmlOutputDev->interpretType3Chars());

}



TEST_F(HtmlOutputDevTest_2705, NeedNonText_ReturnsTrue_2705) {

    EXPECT_TRUE(htmlOutputDev->needNonText());

}



TEST_F(HtmlOutputDevTest_2705, CheckPageSlice_ReturnsFalse_WhenNoCallback_2705) {

    Page* page = nullptr;

    EXPECT_FALSE(htmlOutputDev->checkPageSlice(page, 300, 300, 0, false, false, 0, 0, 100, 100, false));

}



TEST_F(HtmlOutputDevTest_2705, DevType_ReturnsExpectedValue_2705) {

    EXPECT_EQ(htmlOutputDev->DevType(), 6); // Assuming the DevType for HtmlOutputDev is 6

}



TEST_F(HtmlOutputDevTest_2705, GetPageWidth_ReturnsZero_ByDefault_2705) {

    EXPECT_EQ(htmlOutputDev->getPageWidth(), 0);

}



TEST_F(HtmlOutputDevTest_2705, GetPageHeight_ReturnsZero_ByDefault_2705) {

    EXPECT_EQ(htmlOutputDev->getPageHeight(), 0);

}
