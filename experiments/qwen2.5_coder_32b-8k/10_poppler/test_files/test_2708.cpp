#include <gtest/gtest.h>

#include "HtmlOutputDev.h"

#include <gmock/gmock.h>



using namespace testing;



class HtmlOutputDevTest : public ::testing::Test {

protected:

    HtmlOutputDev* html_output_dev;



    void SetUp() override {

        Catalog catalog;

        const char* fileName = "test.html";

        const char* title = "Test Document";

        const char* author = "Author";

        const char* keywords = "Keywords";

        const char* subject = "Subject";

        const char* date = "2023-10-01";

        bool rawOrder = true;

        int firstPage = 1;

        bool outline = false;



        html_output_dev = new HtmlOutputDev(&catalog, fileName, title, author, keywords, subject, date, rawOrder, firstPage, outline);

    }



    void TearDown() override {

        delete html_output_dev;

    }

};



TEST_F(HtmlOutputDevTest_2708, InterpretType3CharsReturnsFalse_2708) {

    EXPECT_FALSE(html_output_dev->interpretType3Chars());

}



TEST_F(HtmlOutputDevTest_2708, IsOkDefaultBehavior_2708) {

    EXPECT_TRUE(html_output_dev->isOk());

}



TEST_F(HtmlOutputDevTest_2708, UpsideDownDefaultBehavior_2708) {

    EXPECT_FALSE(html_output_dev->upsideDown());

}



TEST_F(HtmlOutputDevTest_2708, UseDrawCharDefaultBehavior_2708) {

    EXPECT_TRUE(html_output_dev->useDrawChar());

}



TEST_F(HtmlOutputDevTest_2708, NeedNonTextDefaultBehavior_2708) {

    EXPECT_FALSE(html_output_dev->needNonText());

}



TEST_F(HtmlOutputDevTest_2708, CheckPageSliceNoAbortOrAnnotDisplayDecideCallbacks_2708) {

    Page page;

    bool result = html_output_dev->checkPageSlice(&page, 1.0, 1.0, 0, false, false, 0, 0, 1, 1, false);

    EXPECT_TRUE(result);

}



TEST_F(HtmlOutputDevTest_2708, DevTypeDefaultBehavior_2708) {

    EXPECT_EQ(html_output_dev->DevType(), 0); // Assuming default returns 0 as no specific value is provided

}



TEST_F(HtmlOutputDevTest_2708, GetPageWidthBoundaryCondition_2708) {

    EXPECT_GE(html_output_dev->getPageWidth(), 0);

}



TEST_F(HtmlOutputDevTest_2708, GetPageHeightBoundaryCondition_2708) {

    EXPECT_GE(html_output_dev->getPageHeight(), 0);

}
