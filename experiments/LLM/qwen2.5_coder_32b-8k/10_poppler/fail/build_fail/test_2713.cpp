#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/HtmlOutputDev.h"

#include <memory>



class HtmlOutputDevTest : public ::testing::Test {

protected:

    std::unique_ptr<HtmlOutputDev> htmlOutputDev;



    virtual void SetUp() {

        // Assuming Catalog, fileName, title, author, keywords, subject, date are dummy values

        Catalog* catalog = nullptr;

        const char* fileName = "dummy.html";

        const char* title = "Dummy Title";

        const char* author = "Dummy Author";

        const char* keywords = "Dummy Keywords";

        const char* subject = "Dummy Subject";

        const char* date = "2023-10-01";

        bool rawOrder = false;

        int firstPage = 1;

        bool outline = true;



        htmlOutputDev.reset(new HtmlOutputDev(catalog, fileName, title, author, keywords, subject, date, rawOrder, firstPage, outline));

    }

};



TEST_F(HtmlOutputDevTest_2713, GetPageHeight_ReturnsMaxPageHeight_2713) {

    // Assuming maxPageHeight is set to a known value

    int expectedHeight = 800; // This value should be consistent with the actual setup in HtmlOutputDev constructor or some other means

    EXPECT_EQ(expectedHeight, htmlOutputDev->getPageHeight());

}



TEST_F(HtmlOutputDevTest_2713, GetPageWidth_ReturnsMaxPageWidth_2713) {

    // Assuming maxPageWidth is set to a known value

    int expectedWidth = 600; // This value should be consistent with the actual setup in HtmlOutputDev constructor or some other means

    EXPECT_EQ(expectedWidth, htmlOutputDev->getPageWidth());

}



TEST_F(HtmlOutputDevTest_2713, IsOk_ReturnsTrue_2713) {

    EXPECT_TRUE(htmlOutputDev->isOk());

}



TEST_F(HtmlOutputDevTest_2713, UpsideDown_ReturnsFalse_2713) {

    EXPECT_FALSE(htmlOutputDev->upsideDown());

}



TEST_F(HtmlOutputDevTest_2713, UseDrawChar_ReturnsTrue_2713) {

    EXPECT_TRUE(htmlOutputDev->useDrawChar());

}



TEST_F(HtmlOutputDevTest_2713, InterpretType3Chars_ReturnsTrue_2713) {

    EXPECT_TRUE(htmlOutputDev->interpretType3Chars());

}



TEST_F(HtmlOutputDevTest_2713, NeedNonText_ReturnsTrue_2713) {

    EXPECT_TRUE(htmlOutputDev->needNonText());

}



TEST_F(HtmlOutputDevTest_2713, CheckPageSlice_NoAbortOrAnnotationCallback_ReturnsFalse_2713) {

    Page* page = nullptr; // Assuming page is a dummy value

    bool result = htmlOutputDev->checkPageSlice(page, 96.0, 96.0, 0, false, false, 0, 0, 0, 0, false);

    EXPECT_FALSE(result);

}



TEST_F(HtmlOutputDevTest_2713, DevType_ReturnsExpectedValue_2713) {

    int expectedDevType = 0; // Assuming the default dev type is 0

    EXPECT_EQ(expectedDevType, htmlOutputDev->DevType());

}
