#include <gtest/gtest.h>

#include "poppler/Page.h"

#include "poppler/PDFDoc.h"



class PageTest_720 : public ::testing::Test {

protected:

    PDFDoc* mockDoc;

    Page* page;



    void SetUp() override {

        mockDoc = new PDFDoc();

        page = new Page(mockDoc, 1, Object(), Ref(), std::unique_ptr<PageAttrs>(new PageAttrs()));

    }



    void TearDown() override {

        delete page;

        delete mockDoc;

    }

};



TEST_F(PageTest_720, GetDoc_ReturnsCorrectPointer_720) {

    EXPECT_EQ(page->getDoc(), mockDoc);

}



TEST_F(PageTest_720, IsOk_ReturnsTrueForValidPage_720) {

    EXPECT_TRUE(page->isOk());

}



TEST_F(PageTest_720, GetNum_ReturnsProvidedNumber_720) {

    EXPECT_EQ(page->getNum(), 1);

}



TEST_F(PageTest_720, GetMediaBox_ReturnsNonNullPointer_720) {

    EXPECT_NE(page->getMediaBox(), nullptr);

}



TEST_F(PageTest_720, GetCropBox_ReturnsNonNullPointer_720) {

    EXPECT_NE(page->getCropBox(), nullptr);

}



TEST_F(PageTest_720, IsCropped_ReturnsFalseForDefaultPage_720) {

    EXPECT_FALSE(page->isCropped());

}



TEST_F(PageTest_720, GetMediaWidth_ReturnsPositiveValue_720) {

    EXPECT_GT(page->getMediaWidth(), 0);

}



TEST_F(PageTest_720, GetMediaHeight_ReturnsPositiveValue_720) {

    EXPECT_GT(page->getMediaHeight(), 0);

}



TEST_F(PageTest_720, GetCropWidth_ReturnsPositiveOrZeroValue_720) {

    EXPECT_GE(page->getCropWidth(), 0);

}



TEST_F(PageTest_720, GetCropHeight_ReturnsPositiveOrZeroValue_720) {

    EXPECT_GE(page->getCropHeight(), 0);

}



TEST_F(PageTest_720, GetBleedBox_ReturnsNonNullPointer_720) {

    EXPECT_NE(page->getBleedBox(), nullptr);

}



TEST_F(PageTest_720, GetTrimBox_ReturnsNonNullPointer_720) {

    EXPECT_NE(page->getTrimBox(), nullptr);

}



TEST_F(PageTest_720, GetArtBox_ReturnsNonNullPointer_720) {

    EXPECT_NE(page->getArtBox(), nullptr);

}



TEST_F(PageTest_720, GetRotate_ReturnsValidRotationValue_720) {

    int rotation = page->getRotate();

    EXPECT_TRUE(rotation == 0 || rotation == 90 || rotation == 180 || rotation == 270);

}



TEST_F(PageTest_720, GetLastModified_ReturnsNonNullPointer_720) {

    EXPECT_NE(page->getLastModified(), nullptr);

}



TEST_F(PageTest_720, GetBoxColorInfo_ReturnsNonNullPointer_720) {

    EXPECT_NE(page->getBoxColorInfo(), nullptr);

}



TEST_F(PageTest_720, GetGroup_ReturnsNonNullPointer_720) {

    EXPECT_NE(page->getGroup(), nullptr);

}



TEST_F(PageTest_720, GetMetadata_ReturnsNonNullPointer_720) {

    EXPECT_NE(page->getMetadata(), nullptr);

}



TEST_F(PageTest_720, GetPieceInfo_ReturnsNonNullPointer_720) {

    EXPECT_NE(page->getPieceInfo(), nullptr);

}



TEST_F(PageTest_720, GetSeparationInfo_ReturnsNonNullPointer_720) {

    EXPECT_NE(page->getSeparationInfo(), nullptr);

}



TEST_F(PageTest_720, GetRef_ReturnsValidReference_720) {

    Ref ref = page->getRef();

    EXPECT_TRUE(ref.num >= 0 && ref.gen >= 0); // Assuming valid reference numbers are non-negative

}



TEST_F(PageTest_720, GetPageObj_ReturnsValidObject_720) {

    const Object& obj = page->getPageObj();

    EXPECT_FALSE(obj.isNull());

}



TEST_F(PageTest_720, GetAnnotsObject_ReturnsNonNullObject_720) {

    Object obj = page->getAnnotsObject();

    EXPECT_FALSE(obj.isNull());

}



TEST_F(PageTest_720, GetContents_ReturnsValidObject_720) {

    Object obj = page->getContents();

    EXPECT_FALSE(obj.isNull());

}



TEST_F(PageTest_720, GetThumb_ReturnsNonNullObject_720) {

    Object obj = page->getThumb();

    EXPECT_FALSE(obj.isNull());

}



TEST_F(PageTest_720, GetTrans_ReturnsValidObject_720) {

    Object obj = page->getTrans();

    EXPECT_FALSE(obj.isNull());

}



TEST_F(PageTest_720, GetDuration_ReturnsNonNegativeValue_720) {

    double duration = page->getDuration();

    EXPECT_GE(duration, 0);

}



TEST_F(PageTest_720, GetActions_ReturnsNonNullObject_720) {

    Object obj = page->getActions();

    EXPECT_FALSE(obj.isNull());

}



TEST_F(PageTest_720, HasStandaloneFields_ReturnsFalseForDefaultPage_720) {

    EXPECT_FALSE(page->hasStandaloneFields());

}



TEST_F(PageTest_720, GetStructParents_ReturnsNonNegativeValue_720) {

    int structParents = page->getStructParents();

    EXPECT_GE(structParents, 0);

}
