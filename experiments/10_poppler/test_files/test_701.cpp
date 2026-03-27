#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Page.h"



class PageTest : public ::testing::Test {

protected:

    class MockPDFDoc : public PDFDoc {

        // Mock implementation if needed for external collaborators

    };



    std::unique_ptr<MockPDFDoc> mock_doc_;

    Ref pageRef;

    Object pageDict;



    void SetUp() override {

        mock_doc_ = std::make_unique<MockPDFDoc>();

        pageRef.num = 1;

        pageRef.gen = 0;

        // Initialize pageDict if necessary for testing

    }

};



TEST_F(PageTest_701, IsOk_ReturnsTrueWhenPageIsValid_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    EXPECT_TRUE(page.isOk());

}



TEST_F(PageTest_701, GetNum_ReturnsCorrectPageNumber_701) {

    int pageNum = 5;

    Page page(mock_doc_.get(), pageNum, std::move(pageDict), pageRef, nullptr);

    EXPECT_EQ(page.getNum(), pageNum);

}



TEST_F(PageTest_701, GetMediaBox_ReturnsNonNullPointerWhenAvailable_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    const PDFRectangle* mediaBox = page.getMediaBox();

    EXPECT_NE(mediaBox, nullptr);

}



TEST_F(PageTest_701, GetCropBox_ReturnsNonNullPointerWhenAvailable_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    const PDFRectangle* cropBox = page.getCropBox();

    EXPECT_NE(cropBox, nullptr);

}



TEST_F(PageTest_701, IsCropped_ReturnsFalseWhenNoCrop_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    EXPECT_FALSE(page.isCropped());

}



TEST_F(PageTest_701, GetMediaWidth_ReturnsPositiveValue_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    EXPECT_GT(page.getMediaWidth(), 0.0);

}



TEST_F(PageTest_701, GetMediaHeight_ReturnsPositiveValue_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    EXPECT_GT(page.getMediaHeight(), 0.0);

}



TEST_F(PageTest_701, GetCropWidth_ReturnsPositiveOrZero_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    EXPECT_GE(page.getCropWidth(), 0.0);

}



TEST_F(PageTest_701, GetCropHeight_ReturnsPositiveOrZero_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    EXPECT_GE(page.getCropHeight(), 0.0);

}



TEST_F(PageTest_701, GetBleedBox_ReturnsNonNullPointerWhenAvailable_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    const PDFRectangle* bleedBox = page.getBleedBox();

    EXPECT_NE(bleedBox, nullptr);

}



TEST_F(PageTest_701, GetTrimBox_ReturnsNonNullPointerWhenAvailable_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    const PDFRectangle* trimBox = page.getTrimBox();

    EXPECT_NE(trimBox, nullptr);

}



TEST_F(PageTest_701, GetArtBox_ReturnsNonNullPointerWhenAvailable_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    const PDFRectangle* artBox = page.getArtBox();

    EXPECT_NE(artBox, nullptr);

}



TEST_F(PageTest_701, GetRotate_ReturnsValidRotationValue_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    int rotate = page.getRotate();

    EXPECT_TRUE(rotate == 0 || rotate == 90 || rotate == 180 || rotate == 270);

}



TEST_F(PageTest_701, GetLastModified_ReturnsNonNullPointerWhenAvailable_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    const GooString* lastModified = page.getLastModified();

    EXPECT_NE(lastModified, nullptr);

}



TEST_F(PageTest_701, GetBoxColorInfo_ReturnsNonNullPointerWhenAvailable_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    Dict* boxColorInfo = page.getBoxColorInfo();

    EXPECT_NE(boxColorInfo, nullptr);

}



TEST_F(PageTest_701, GetGroup_ReturnsNonNullPointerWhenAvailable_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    Dict* group = page.getGroup();

    EXPECT_NE(group, nullptr);

}



TEST_F(PageTest_701, GetMetadata_ReturnsNonNullPointerWhenAvailable_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    Stream* metadata = page.getMetadata();

    EXPECT_NE(metadata, nullptr);

}



TEST_F(PageTest_701, GetPieceInfo_ReturnsNonNullPointerWhenAvailable_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    Dict* pieceInfo = page.getPieceInfo();

    EXPECT_NE(pieceInfo, nullptr);

}



TEST_F(PageTest_701, GetSeparationInfo_ReturnsNonNullPointerWhenAvailable_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    Dict* separationInfo = page.getSeparationInfo();

    EXPECT_NE(separationInfo, nullptr);

}



TEST_F(PageTest_701, GetDoc_ReturnsNonNullPointer_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    PDFDoc* doc = page.getDoc();

    EXPECT_NE(doc, nullptr);

}



TEST_F(PageTest_701, GetRef_ReturnsCorrectPageReference_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    Ref ref = page.getRef();

    EXPECT_EQ(ref.num, pageRef.num);

    EXPECT_EQ(ref.gen, pageRef.gen);

}



TEST_F(PageTest_701, GetPageObj_ReturnsNonNullPointer_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    const Object& pageObj = page.getPageObj();

    EXPECT_FALSE(pageObj.isNull());

}



TEST_F(PageTest_701, GetAnnotsObject_ReturnsNonNullPointerWhenAvailable_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    Object annotsObj = page.getAnnotsObject();

    EXPECT_FALSE(annotsObj.isNull());

}



TEST_F(PageTest_701, GetContents_ReturnsNonNullPointerWhenAvailable_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    Object contents = page.getContents();

    EXPECT_FALSE(contents.isNull());

}



TEST_F(PageTest_701, GetThumb_ReturnsNonNullPointerWhenAvailable_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    Object thumb = page.getThumb();

    EXPECT_FALSE(thumb.isNull());

}



TEST_F(PageTest_701, GetTrans_ReturnsNonNullPointerWhenAvailable_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    Object trans = page.getTrans();

    EXPECT_FALSE(trans.isNull());

}



TEST_F(PageTest_701, GetDuration_ReturnsNonNegativeValue_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    double duration = page.getDuration();

    EXPECT_GE(duration, 0.0);

}



TEST_F(PageTest_701, GetActions_ReturnsNonNullPointerWhenAvailable_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    Object actions = page.getActions();

    EXPECT_FALSE(actions.isNull());

}



TEST_F(PageTest_701, HasStandaloneFields_ReturnsFalseWhenNoFields_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    EXPECT_FALSE(page.hasStandaloneFields());

}



TEST_F(PageTest_701, GetStructParents_ReturnsNonNegativeValue_701) {

    Page page(mock_doc_.get(), 1, std::move(pageDict), pageRef, nullptr);

    int structParents = page.getStructParents();

    EXPECT_GE(structParents, 0);

}
