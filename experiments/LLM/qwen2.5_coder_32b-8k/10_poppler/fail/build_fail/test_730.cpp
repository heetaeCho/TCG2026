#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Page.h"



class PageTest : public ::testing::Test {

protected:

    // Assuming a mock PDFDoc and XRef are available for construction

    // For simplicity, we will use nullptr here as the actual implementation is not known.

    Page* page;



    virtual void SetUp() {

        page = new Page(nullptr, 1, std::move(Object()), Ref(), std::make_unique<PageAttrs>());

    }



    virtual void TearDown() {

        delete page;

    }

};



TEST_F(PageTest_730, GetStructParents_ReturnsDefault_730) {

    // Assuming structParents is initialized to a default value, e.g., 0

    EXPECT_EQ(page->getStructParents(), 0);

}



TEST_F(PageTest_730, IsOk_ReturnsTrueForValidPage_730) {

    EXPECT_TRUE(page->isOk());

}



TEST_F(PageTest_730, GetNum_ReturnsCorrectPageNumber_730) {

    EXPECT_EQ(page->getNum(), 1);

}



TEST_F(PageTest_730, GetMediaBox_ReturnsNonNullPointer_730) {

    EXPECT_NE(page->getMediaBox(), nullptr);

}



TEST_F(PageTest_730, GetCropBox_ReturnsNonNullPointer_730) {

    EXPECT_NE(page->getCropBox(), nullptr);

}



TEST_F(PageTest_730, IsCropped_ReturnsFalseByDefault_730) {

    EXPECT_FALSE(page->isCropped());

}



TEST_F(PageTest_730, GetMediaWidth_ReturnsPositiveValue_730) {

    EXPECT_GT(page->getMediaWidth(), 0.0);

}



TEST_F(PageTest_730, GetMediaHeight_ReturnsPositiveValue_730) {

    EXPECT_GT(page->getMediaHeight(), 0.0);

}



TEST_F(PageTest_730, GetCropWidth_ReturnsPositiveOrZero_730) {

    EXPECT_GE(page->getCropWidth(), 0.0);

}



TEST_F(PageTest_730, GetCropHeight_ReturnsPositiveOrZero_730) {

    EXPECT_GE(page->getCropHeight(), 0.0);

}



TEST_F(PageTest_730, GetBleedBox_ReturnsNonNullPointer_730) {

    EXPECT_NE(page->getBleedBox(), nullptr);

}



TEST_F(PageTest_730, GetTrimBox_ReturnsNonNullPointer_730) {

    EXPECT_NE(page->getTrimBox(), nullptr);

}



TEST_F(PageTest_730, GetArtBox_ReturnsNonNullPointer_730) {

    EXPECT_NE(page->getArtBox(), nullptr);

}



TEST_F(PageTest_730, GetRotate_ReturnsValidRotationValue_730) {

    int rotation = page->getRotate();

    EXPECT_TRUE(rotation == 0 || rotation == 90 || rotation == 180 || rotation == 270);

}



TEST_F(PageTest_730, GetLastModified_ReturnsNonNullPointer_730) {

    EXPECT_NE(page->getLastModified(), nullptr);

}



TEST_F(PageTest_730, GetBoxColorInfo_ReturnsNonNullPointer_730) {

    EXPECT_NE(page->getBoxColorInfo(), nullptr);

}



TEST_F(PageTest_730, GetGroup_ReturnsNonNullPointer_730) {

    EXPECT_NE(page->getGroup(), nullptr);

}



TEST_F(PageTest_730, GetMetadata_ReturnsNonNullPointer_730) {

    EXPECT_NE(page->getMetadata(), nullptr);

}



TEST_F(PageTest_730, GetPieceInfo_ReturnsNonNullPointer_730) {

    EXPECT_NE(page->getPieceInfo(), nullptr);

}



TEST_F(PageTest_730, GetSeparationInfo_ReturnsNonNullPointer_730) {

    EXPECT_NE(page->getSeparationInfo(), nullptr);

}



TEST_F(PageTest_730, GetDoc_ReturnsNullPointerForNoDocument_730) {

    // Since no document is provided in the setup

    EXPECT_EQ(page->getDoc(), nullptr);

}



TEST_F(PageTest_730, GetRef_ReturnsValidReference_730) {

    Ref ref = page->getRef();

    EXPECT_TRUE(ref.num >= 0 && ref.gen >= 0); // Assuming valid references have non-negative numbers and generation

}



TEST_F(PageTest_730, GetPageObj_ReturnsNonNullObject_730) {

    const Object& obj = page->getPageObj();

    EXPECT_FALSE(obj.isNull());

}



TEST_F(PageTest_730, GetAnnotsObject_ReturnsNonNullObject_730) {

    Object obj = page->getAnnotsObject();

    EXPECT_FALSE(obj.isNull());

}



TEST_F(PageTest_730, GetContents_ReturnsNonNullObject_730) {

    Object obj = page->getContents();

    EXPECT_FALSE(obj.isNull());

}



TEST_F(PageTest_730, GetThumb_ReturnsNonNullObject_730) {

    Object obj = page->getThumb();

    EXPECT_FALSE(obj.isNull());

}



TEST_F(PageTest_730, GetTrans_ReturnsNonNullObject_730) {

    Object obj = page->getTrans();

    EXPECT_FALSE(obj.isNull());

}



TEST_F(PageTest_730, GetDuration_ReturnsPositiveOrZeroValue_730) {

    double duration = page->getDuration();

    EXPECT_GE(duration, 0.0);

}



TEST_F(PageTest_730, GetActions_ReturnsNonNullObject_730) {

    Object obj = page->getActions();

    EXPECT_FALSE(obj.isNull());

}



TEST_F(PageTest_730, HasStandaloneFields_ReturnsFalseByDefault_730) {

    EXPECT_FALSE(page->hasStandaloneFields());

}
