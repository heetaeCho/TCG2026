#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/HtmlOutputDev.h"

#include <gmock/gmock.h>



class HtmlOutputDevTest : public ::testing::Test {

protected:

    HtmlOutputDev* htmlOutputDev;



    virtual void SetUp() {

        Catalog catalog;

        const char* fileName = "test.html";

        const char* title = "Test Document";

        const char* author = "Author";

        const char* keywords = "Keywords";

        const char* subject = "Subject";

        const char* date = "2023-10-01";

        bool rawOrder = false;

        int firstPage = 1;

        bool outline = true;



        htmlOutputDev = new HtmlOutputDev(&catalog, fileName, title, author, keywords, subject, date, rawOrder, firstPage, outline);

    }



    virtual void TearDown() {

        delete htmlOutputDev;

    }

};



TEST_F(HtmlOutputDevTest_2706, UpsideDownReturnsTrue_2706) {

    EXPECT_TRUE(htmlOutputDev->upsideDown());

}



TEST_F(HtmlOutputDevTest_2706, UseDrawCharReturnsFalseByDefault_2706) {

    EXPECT_FALSE(htmlOutputDev->useDrawChar());

}



TEST_F(HtmlOutputDevTest_2706, InterpretType3CharsReturnsTrueByDefault_2706) {

    EXPECT_TRUE(htmlOutputDev->interpretType3Chars());

}



TEST_F(HtmlOutputDevTest_2706, NeedNonTextReturnsFalseByDefault_2706) {

    EXPECT_FALSE(htmlOutputDev->needNonText());

}



TEST_F(HtmlOutputDevTest_2706, CheckPageSliceWithoutAbortCheckCbkAndAnnotDisplayDecideCbk_2706) {

    Page page;

    EXPECT_TRUE(htmlOutputDev->checkPageSlice(&page, 300.0, 300.0, 0, false, false, 0, 0, 100, 100, false));

}



TEST_F(HtmlOutputDevTest_2706, CheckPageSliceWithAbortCheckCbkReturningFalse_2706) {

    Page page;

    bool abortCheckResult = false;

    auto abortCheckCbk = [&abortCheckResult](void*) { return abortCheckResult; };

    EXPECT_TRUE(htmlOutputDev->checkPageSlice(&page, 300.0, 300.0, 0, false, false, 0, 0, 100, 100, false, abortCheckCbk));

}



TEST_F(HtmlOutputDevTest_2706, CheckPageSliceWithAbortCheckCbkReturningTrue_2706) {

    Page page;

    bool abortCheckResult = true;

    auto abortCheckCbk = [&abortCheckResult](void*) { return abortCheckResult; };

    EXPECT_FALSE(htmlOutputDev->checkPageSlice(&page, 300.0, 300.0, 0, false, false, 0, 0, 100, 100, false, abortCheckCbk));

}



TEST_F(HtmlOutputDevTest_2706, CheckPageSliceWithAnnotDisplayDecideCbkReturningFalse_2706) {

    Page page;

    bool annotDisplayResult = false;

    auto annotDisplayDecideCbk = [&annotDisplayResult](Annot*, void*) { return annotDisplayResult; };

    EXPECT_TRUE(htmlOutputDev->checkPageSlice(&page, 300.0, 300.0, 0, false, false, 0, 0, 100, 100, false, nullptr, nullptr, annotDisplayDecideCbk));

}



TEST_F(HtmlOutputDevTest_2706, CheckPageSliceWithAnnotDisplayDecideCbkReturningTrue_2706) {

    Page page;

    bool annotDisplayResult = true;

    auto annotDisplayDecideCbk = [&annotDisplayResult](Annot*, void*) { return annotDisplayResult; };

    EXPECT_TRUE(htmlOutputDev->checkPageSlice(&page, 300.0, 300.0, 0, false, false, 0, 0, 100, 100, false, nullptr, nullptr, annotDisplayDecideCbk));

}



TEST_F(HtmlOutputDevTest_2706, DevTypeReturnsUniqueValue_2706) {

    EXPECT_EQ(htmlOutputDev->DevType(), htmlOutputDev->DevType());

}
