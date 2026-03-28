#include <gtest/gtest.h>

#include "poppler/Page.h"

#include "poppler/Object.h"

#include "poppler/Ref.h"

#include "poppler/PDFDoc.h"



class PageTest_721 : public ::testing::Test {

protected:

    PDFDoc* mockDoc;

    Ref pageRef;

    Object pageDict;



    void SetUp() override {

        mockDoc = new PDFDoc();

        pageRef.num = 42;

        pageRef.gen = 0;

    }



    void TearDown() override {

        delete mockDoc;

    }

};



TEST_F(PageTest_721, GetRef_ReturnsCorrectRef_721) {

    Page page(mockDoc, 1, std::move(pageDict), pageRef, nullptr);

    EXPECT_EQ(page.getRef(), pageRef);

}



TEST_F(PageTest_721, IsOk_ReturnsTrueForValidPage_721) {

    Page page(mockDoc, 1, std::move(pageDict), pageRef, nullptr);

    EXPECT_TRUE(page.isOk());

}



TEST_F(PageTest_721, GetNum_ReturnsCorrectNumber_721) {

    int pageNumber = 5;

    Page page(mockDoc, pageNumber, std::move(pageDict), pageRef, nullptr);

    EXPECT_EQ(page.getNum(), pageNumber);

}



TEST_F(PageTest_721, GetMediaBox_ReturnsNonNullPointer_721) {

    Page page(mockDoc, 1, std::move(pageDict), pageRef, nullptr);

    EXPECT_NE(page.getMediaBox(), nullptr);

}



TEST_F(PageTest_721, GetCropBox_ReturnsNonNullPointer_721) {

    Page page(mockDoc, 1, std::move(pageDict), pageRef, nullptr);

    EXPECT_NE(page.getCropBox(), nullptr);

}



TEST_F(PageTest_721, IsCropped_ReturnsFalseForDefaultPage_721) {

    Page page(mockDoc, 1, std::move(pageDict), pageRef, nullptr);

    EXPECT_FALSE(page.isCropped());

}



TEST_F(PageTest_721, GetMediaWidth_ReturnsPositiveValue_721) {

    Page page(mockDoc, 1, std::move(pageDict), pageRef, nullptr);

    EXPECT_GT(page.getMediaWidth(), 0.0);

}



TEST_F(PageTest_721, GetMediaHeight_ReturnsPositiveValue_721) {

    Page page(mockDoc, 1, std::move(pageDict), pageRef, nullptr);

    EXPECT_GT(page.getMediaHeight(), 0.0);

}



TEST_F(PageTest_721, GetCropWidth_ReturnsPositiveOrZeroValue_721) {

    Page page(mockDoc, 1, std::move(pageDict), pageRef, nullptr);

    EXPECT_GE(page.getCropWidth(), 0.0);

}



TEST_F(PageTest_721, GetCropHeight_ReturnsPositiveOrZeroValue_721) {

    Page page(mockDoc, 1, std::move(pageDict), pageRef, nullptr);

    EXPECT_GE(page.getCropHeight(), 0.0);

}



TEST_F(PageTest_721, GetBleedBox_ReturnsNonNullPointer_721) {

    Page page(mockDoc, 1, std::move(pageDict), pageRef, nullptr);

    EXPECT_NE(page.getBleedBox(), nullptr);

}



TEST_F(PageTest_721, GetTrimBox_ReturnsNonNullPointer_721) {

    Page page(mockDoc, 1, std::move(pageDict), pageRef, nullptr);

    EXPECT_NE(page.getTrimBox(), nullptr);

}



TEST_F(PageTest_721, GetArtBox_ReturnsNonNullPointer_721) {

    Page page(mockDoc, 1, std::move(pageDict), pageRef, nullptr);

    EXPECT_NE(page.getArtBox(), nullptr);

}



TEST_F(PageTest_721, GetRotate_ReturnsValidRotation_721) {

    Page page(mockDoc, 1, std::move(pageDict), pageRef, nullptr);

    int rotation = page.getRotate();

    EXPECT_TRUE(rotation == 0 || rotation == 90 || rotation == 180 || rotation == 270);

}



TEST_F(PageTest_721, GetLastModified_ReturnsNonNullPointer_721) {

    Page page(mockDoc, 1, std::move(pageDict), pageRef, nullptr);

    EXPECT_NE(page.getLastModified(), nullptr);

}



TEST_F(PageTest_721, GetBoxColorInfo_ReturnsNonNullPointer_721) {

    Page page(mockDoc, 1, std::move(pageDict), pageRef, nullptr);

    EXPECT_NE(page.getBoxColorInfo(), nullptr);

}



TEST_F(PageTest_721, GetGroup_ReturnsNonNullPointer_721) {

    Page page(mockDoc, 1, std::move(pageDict), pageRef, nullptr);

    EXPECT_NE(page.getGroup(), nullptr);

}



TEST_F(PageTest_721, GetMetadata_ReturnsNonNullPointer_721) {

    Page page(mockDoc, 1, std::move(pageDict), pageRef, nullptr);

    EXPECT_NE(page.getMetadata(), nullptr);

}



TEST_F(PageTest_721, GetPieceInfo_ReturnsNonNullPointer_721) {

    Page page(mockDoc, 1, std::move(pageDict), pageRef, nullptr);

    EXPECT_NE(page.getPieceInfo(), nullptr);

}



TEST_F(PageTest_721, GetSeparationInfo_ReturnsNonNullPointer_721) {

    Page page(mockDoc, 1, std::move(pageDict), pageRef, nullptr);

    EXPECT_NE(page.getSeparationInfo(), nullptr);

}



TEST_F(PageTest_721, GetDoc_ReturnsCorrectPDFDoc_721) {

    Page page(mockDoc, 1, std::move(pageDict), pageRef, nullptr);

    EXPECT_EQ(page.getDoc(), mockDoc);

}



TEST_F(PageTest_721, GetPageObj_ReturnsValidObject_721) {

    Page page(mockDoc, 1, std::move(pageDict), pageRef, nullptr);

    const Object& obj = page.getPageObj();

    EXPECT_TRUE(obj.isDict());

}



TEST_F(PageTest_721, GetAnnotsObject_ReturnsValidObject_721) {

    Page page(mockDoc, 1, std::move(pageDict), pageRef, nullptr);

    Object obj = page.getAnnotsObject();

    EXPECT_TRUE(obj.isNull() || obj.isArray());

}



TEST_F(PageTest_721, GetContents_ReturnsValidObject_721) {

    Page page(mockDoc, 1, std::move(pageDict), pageRef, nullptr);

    Object obj = page.getContents();

    EXPECT_TRUE(obj.isNull() || obj.isStream() || obj.isArray());

}



TEST_F(PageTest_721, GetThumb_ReturnsValidObject_721) {

    Page page(mockDoc, 1, std::move(pageDict), pageRef, nullptr);

    Object obj = page.getThumb();

    EXPECT_TRUE(obj.isNull() || obj.isStream());

}



TEST_F(PageTest_721, GetTrans_ReturnsValidObject_721) {

    Page page(mockDoc, 1, std::move(pageDict), pageRef, nullptr);

    Object obj = page.getTrans();

    EXPECT_TRUE(obj.isNull() || obj.isDict());

}



TEST_F(PageTest_721, GetDuration_ReturnsNonNegativeValue_721) {

    Page page(mockDoc, 1, std::move(pageDict), pageRef, nullptr);

    EXPECT_GE(page.getDuration(), 0.0);

}



TEST_F(PageTest_721, GetActions_ReturnsValidObject_721) {

    Page page(mockDoc, 1, std::move(pageDict), pageRef, nullptr);

    Object obj = page.getActions();

    EXPECT_TRUE(obj.isNull() || obj.isDict());

}
