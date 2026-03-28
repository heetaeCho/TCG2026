#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Page.h"



class PageTest_703 : public ::testing::Test {

protected:

    PDFDoc* mock_doc = nullptr;

    int num = 1;

    Object pageDict;

    Ref pageRef = {1, 0};

    std::unique_ptr<PageAttrs> attrs = std::make_unique<PageAttrs>(nullptr, nullptr);

    Page page{mock_doc, num, std::move(pageDict), pageRef, std::move(attrs)};

};



TEST_F(PageTest_703, GetMediaBox_ReturnsValidPointer_703) {

    const PDFRectangle* mediaBox = page.getMediaBox();

    EXPECT_NE(mediaBox, nullptr);

}



TEST_F(PageTest_703, GetCropBox_ReturnsValidPointer_703) {

    const PDFRectangle* cropBox = page.getCropBox();

    EXPECT_NE(cropBox, nullptr);

}



TEST_F(PageTest_703, IsCropped_ReturnsFalseWhenNotCropped_703) {

    bool isCropped = page.isCropped();

    EXPECT_FALSE(isCropped);

}



TEST_F(PageTest_703, GetMediaWidth_ReturnsPositiveValue_703) {

    double mediaWidth = page.getMediaWidth();

    EXPECT_GT(mediaWidth, 0.0);

}



TEST_F(PageTest_703, GetMediaHeight_ReturnsPositiveValue_703) {

    double mediaHeight = page.getMediaHeight();

    EXPECT_GT(mediaHeight, 0.0);

}



TEST_F(PageTest_703, GetCropWidth_ReturnsNonNegativeValue_703) {

    double cropWidth = page.getCropWidth();

    EXPECT_GE(cropWidth, 0.0);

}



TEST_F(PageTest_703, GetCropHeight_ReturnsNonNegativeValue_703) {

    double cropHeight = page.getCropHeight();

    EXPECT_GE(cropHeight, 0.0);

}



TEST_F(PageTest_703, GetBleedBox_ReturnsValidPointer_703) {

    const PDFRectangle* bleedBox = page.getBleedBox();

    EXPECT_NE(bleedBox, nullptr);

}



TEST_F(PageTest_703, GetTrimBox_ReturnsValidPointer_703) {

    const PDFRectangle* trimBox = page.getTrimBox();

    EXPECT_NE(trimBox, nullptr);

}



TEST_F(PageTest_703, GetArtBox_ReturnsValidPointer_703) {

    const PDFRectangle* artBox = page.getArtBox();

    EXPECT_NE(artBox, nullptr);

}



TEST_F(PageTest_703, GetRotate_ReturnsNonNegativeValue_703) {

    int rotate = page.getRotate();

    EXPECT_GE(rotate, 0);

}



TEST_F(PageTest_703, GetLastModified_ReturnsValidPointer_703) {

    const GooString* lastModified = page.getLastModified();

    EXPECT_NE(lastModified, nullptr);

}



TEST_F(PageTest_703, GetBoxColorInfo_ReturnsValidPointer_703) {

    Dict* boxColorInfo = page.getBoxColorInfo();

    EXPECT_NE(boxColorInfo, nullptr);

}



TEST_F(PageTest_703, GetGroup_ReturnsValidPointer_703) {

    Dict* group = page.getGroup();

    EXPECT_NE(group, nullptr);

}



TEST_F(PageTest_703, GetMetadata_ReturnsValidPointer_703) {

    Stream* metadata = page.getMetadata();

    EXPECT_NE(metadata, nullptr);

}



TEST_F(PageTest_703, GetPieceInfo_ReturnsValidPointer_703) {

    Dict* pieceInfo = page.getPieceInfo();

    EXPECT_NE(pieceInfo, nullptr);

}



TEST_F(PageTest_703, GetSeparationInfo_ReturnsValidPointer_703) {

    Dict* separationInfo = page.getSeparationInfo();

    EXPECT_NE(separationInfo, nullptr);

}



TEST_F(PageTest_703, GetDoc_ReturnsNonNullPointer_703) {

    PDFDoc* doc = page.getDoc();

    EXPECT_NE(doc, nullptr);

}



TEST_F(PageTest_703, GetRef_ReturnsValidReference_703) {

    Ref ref = page.getRef();

    EXPECT_EQ(ref.num, 1);

    EXPECT_EQ(ref.gen, 0);

}



TEST_F(PageTest_703, GetPageObj_ReturnsConstObject_703) {

    const Object& pageObj = page.getPageObj();

    EXPECT_TRUE(pageObj.isDict());

}



TEST_F(PageTest_703, GetAnnotsObject_ReturnsValidObject_703) {

    Object annotsObj = page.getAnnotsObject(nullptr);

    EXPECT_TRUE(annotsObj.isNull()); // Assuming no annotations are present

}



TEST_F(PageTest_703, GetContents_ReturnsValidObject_703) {

    Object contents = page.getContents();

    EXPECT_TRUE(contents.isNull()); // Assuming no contents are present

}



TEST_F(PageTest_703, GetThumb_ReturnsValidObject_703) {

    Object thumb = page.getThumb();

    EXPECT_TRUE(thumb.isNull()); // Assuming no thumbnail is present

}



TEST_F(PageTest_703, GetTrans_ReturnsValidObject_703) {

    Object trans = page.getTrans();

    EXPECT_TRUE(trans.isNull()); // Assuming no transition is present

}



TEST_F(PageTest_703, GetDuration_ReturnsNonNegativeValue_703) {

    double duration = page.getDuration();

    EXPECT_GE(duration, 0.0);

}



TEST_F(PageTest_703, GetActions_ReturnsValidObject_703) {

    Object actions = page.getActions();

    EXPECT_TRUE(actions.isNull()); // Assuming no actions are present

}



TEST_F(PageTest_703, HasStandaloneFields_ReturnsFalseWhenNoFields_703) {

    bool hasFields = page.hasStandaloneFields();

    EXPECT_FALSE(hasFields);

}



TEST_F(PageTest_703, GetStructParents_ReturnsNonNegativeValue_703) {

    int structParents = page.getStructParents();

    EXPECT_GE(structParents, 0);

}
