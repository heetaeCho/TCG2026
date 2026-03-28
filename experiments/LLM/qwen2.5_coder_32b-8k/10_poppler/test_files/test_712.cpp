#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Page.h"

#include "TestProjects/poppler/poppler/PageAttrs.h"



class PageTest_712 : public ::testing::Test {

protected:

    PDFDoc* mockDoc;

    int num = 1;

    Object pageDict;

    Ref pageRef;

    std::unique_ptr<PageAttrs> attrs;



    void SetUp() override {

        mockDoc = new PDFDoc();

        pageRef.num = 0;

        pageRef.gen = 0;

        attrs = std::make_unique<PageAttrs>(nullptr, nullptr);

    }



    void TearDown() override {

        delete mockDoc;

    }

};



TEST_F(PageTest_712, GetArtBox_ReturnsValidPointer_712) {

    Page page(mockDoc, num, std::move(pageDict), pageRef, std::move(attrs));

    const PDFRectangle* artBox = page.getArtBox();

    EXPECT_NE(artBox, nullptr);

}



TEST_F(PageTest_712, GetMediaBox_ReturnsValidPointer_712) {

    Page page(mockDoc, num, std::move(pageDict), pageRef, std::move(attrs));

    const PDFRectangle* mediaBox = page.getMediaBox();

    EXPECT_NE(mediaBox, nullptr);

}



TEST_F(PageTest_712, GetCropBox_ReturnsValidPointer_712) {

    Page page(mockDoc, num, std::move(pageDict), pageRef, std::move(attrs));

    const PDFRectangle* cropBox = page.getCropBox();

    EXPECT_NE(cropBox, nullptr);

}



TEST_F(PageTest_712, IsCropped_ReturnsFalseWhenNoCropBox_712) {

    Page page(mockDoc, num, std::move(pageDict), pageRef, std::move(attrs));

    bool cropped = page.isCropped();

    EXPECT_FALSE(cropped);

}



TEST_F(PageTest_712, GetBleedBox_ReturnsValidPointer_712) {

    Page page(mockDoc, num, std::move(pageDict), pageRef, std::move(attrs));

    const PDFRectangle* bleedBox = page.getBleedBox();

    EXPECT_NE(bleedBox, nullptr);

}



TEST_F(PageTest_712, GetTrimBox_ReturnsValidPointer_712) {

    Page page(mockDoc, num, std::move(pageDict), pageRef, std::move(attrs));

    const PDFRectangle* trimBox = page.getTrimBox();

    EXPECT_NE(trimBox, nullptr);

}



TEST_F(PageTest_712, GetRotate_ReturnsZeroByDefault_712) {

    Page page(mockDoc, num, std::move(pageDict), pageRef, std::move(attrs));

    int rotate = page.getRotate();

    EXPECT_EQ(rotate, 0);

}



TEST_F(PageTest_712, IsOk_ReturnsTrueWhenInitialized_712) {

    Page page(mockDoc, num, std::move(pageDict), pageRef, std::move(attrs));

    bool isOk = page.isOk();

    EXPECT_TRUE(isOk);

}



TEST_F(PageTest_712, GetNum_ReturnsCorrectPageNumber_712) {

    Page page(mockDoc, num, std::move(pageDict), pageRef, std::move(attrs));

    int pageNumber = page.getNum();

    EXPECT_EQ(pageNumber, 1);

}
