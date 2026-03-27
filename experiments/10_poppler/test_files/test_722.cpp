#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/Page.h"

#include "poppler/Object.h"



using namespace testing;



class PageTest : public Test {

protected:

    PDFDoc* mockPDFDoc;

    Ref mockPageRef;

    Object mockPageDict;

    std::unique_ptr<PageAttrs> mockPageAttrs;



    void SetUp() override {

        mockPDFDoc = nullptr; // Assuming no need to mock PDFDoc for these tests

        mockPageRef.num = 1;

        mockPageRef.gen = 0;

        mockPageAttrs = std::make_unique<PageAttrs>();

    }



    Page* createPage() {

        return new Page(mockPDFDoc, 1, std::move(mockPageDict), mockPageRef, std::move(mockPageAttrs));

    }

};



TEST_F(PageTest_722, IsOkReturnsTrue_722) {

    Page* page = createPage();

    EXPECT_TRUE(page->isOk());

    delete page;

}



TEST_F(PageTest_722, GetNumReturnsCorrectNumber_722) {

    Page* page = createPage();

    EXPECT_EQ(page->getNum(), 1);

    delete page;

}



TEST_F(PageTest_722, GetPageObjReturnsValidObject_722) {

    Page* page = createPage();

    const Object& obj = page->getPageObj();

    EXPECT_TRUE(obj.isNone()); // Assuming default constructed Object is None

    delete page;

}



TEST_F(PageTest_722, GetMediaBoxReturnsNonNullPointer_722) {

    Page* page = createPage();

    const PDFRectangle* mediaBox = page->getMediaBox();

    EXPECT_NE(mediaBox, nullptr);

    delete page;

}



TEST_F(PageTest_722, GetCropBoxReturnsNonNullPointer_722) {

    Page* page = createPage();

    const PDFRectangle* cropBox = page->getCropBox();

    EXPECT_NE(cropBox, nullptr);

    delete page;

}



TEST_F(PageTest_722, IsCroppedReturnsFalseByDefault_722) {

    Page* page = createPage();

    EXPECT_FALSE(page->isCropped());

    delete page;

}



TEST_F(PageTest_722, GetMediaWidthReturnsPositiveValue_722) {

    Page* page = createPage();

    double mediaWidth = page->getMediaWidth();

    EXPECT_GT(mediaWidth, 0.0);

    delete page;

}



TEST_F(PageTest_722, GetMediaHeightReturnsPositiveValue_722) {

    Page* page = createPage();

    double mediaHeight = page->getMediaHeight();

    EXPECT_GT(mediaHeight, 0.0);

    delete page;

}



TEST_F(PageTest_722, GetCropWidthReturnsPositiveValue_722) {

    Page* page = createPage();

    double cropWidth = page->getCropWidth();

    EXPECT_GT(cropWidth, 0.0);

    delete page;

}



TEST_F(PageTest_722, GetCropHeightReturnsPositiveValue_722) {

    Page* page = createPage();

    double cropHeight = page->getCropHeight();

    EXPECT_GT(cropHeight, 0.0);

    delete page;

}



TEST_F(PageTest_722, GetBleedBoxReturnsNonNullPointer_722) {

    Page* page = createPage();

    const PDFRectangle* bleedBox = page->getBleedBox();

    EXPECT_NE(bleedBox, nullptr);

    delete page;

}



TEST_F(PageTest_722, GetTrimBoxReturnsNonNullPointer_722) {

    Page* page = createPage();

    const PDFRectangle* trimBox = page->getTrimBox();

    EXPECT_NE(trimBox, nullptr);

    delete page;

}



TEST_F(PageTest_722, GetArtBoxReturnsNonNullPointer_722) {

    Page* page = createPage();

    const PDFRectangle* artBox = page->getArtBox();

    EXPECT_NE(artBox, nullptr);

    delete page;

}



TEST_F(PageTest_722, GetRotateReturnsValidRotationValue_722) {

    Page* page = createPage();

    int rotation = page->getRotate();

    EXPECT_TRUE(rotation == 0 || rotation == 90 || rotation == 180 || rotation == 270);

    delete page;

}



TEST_F(PageTest_722, GetLastModifiedReturnsNonNullPointer_722) {

    Page* page = createPage();

    const GooString* lastModified = page->getLastModified();

    EXPECT_NE(lastModified, nullptr);

    delete page;

}



TEST_F(PageTest_722, GetBoxColorInfoReturnsNonNullPointer_722) {

    Page* page = createPage();

    Dict* boxColorInfo = page->getBoxColorInfo();

    EXPECT_NE(boxColorInfo, nullptr);

    delete page;

}



TEST_F(PageTest_722, GetGroupReturnsNonNullPointer_722) {

    Page* page = createPage();

    Dict* group = page->getGroup();

    EXPECT_NE(group, nullptr);

    delete page;

}



TEST_F(PageTest_722, GetMetadataReturnsNullPointerByDefault_722) {

    Page* page = createPage();

    Stream* metadata = page->getMetadata();

    EXPECT_EQ(metadata, nullptr);

    delete page;

}



TEST_F(PageTest_722, GetPieceInfoReturnsNonNullPointer_722) {

    Page* page = createPage();

    Dict* pieceInfo = page->getPieceInfo();

    EXPECT_NE(pieceInfo, nullptr);

    delete page;

}



TEST_F(PageTest_722, GetSeparationInfoReturnsNonNullPointer_722) {

    Page* page = createPage();

    Dict* separationInfo = page->getSeparationInfo();

    EXPECT_NE(separationInfo, nullptr);

    delete page;

}



TEST_F(PageTest_722, GetDocReturnsNullPointerByDefault_722) {

    Page* page = createPage();

    PDFDoc* doc = page->getDoc();

    EXPECT_EQ(doc, nullptr);

    delete page;

}



TEST_F(PageTest_722, GetRefReturnsValidReference_722) {

    Page* page = createPage();

    Ref ref = page->getRef();

    EXPECT_EQ(ref.num, mockPageRef.num);

    EXPECT_EQ(ref.gen, mockPageRef.gen);

    delete page;

}



TEST_F(PageTest_722, GetAnnotsObjectReturnsValidObject_722) {

    Page* page = createPage();

    Object annotsObj = page->getAnnotsObject();

    EXPECT_TRUE(annotsObj.isNone()); // Assuming default constructed Object is None

    delete page;

}



TEST_F(PageTest_722, GetContentsReturnsValidObject_722) {

    Page* page = createPage();

    Object contents = page->getContents();

    EXPECT_TRUE(contents.isNone()); // Assuming default constructed Object is None

    delete page;

}



TEST_F(PageTest_722, GetThumbReturnsValidObject_722) {

    Page* page = createPage();

    Object thumb = page->getThumb();

    EXPECT_TRUE(thumb.isNone()); // Assuming default constructed Object is None

    delete page;

}



TEST_F(PageTest_722, GetTransReturnsValidObject_722) {

    Page* page = createPage();

    Object trans = page->getTrans();

    EXPECT_TRUE(trans.isNone()); // Assuming default constructed Object is None

    delete page;

}



TEST_F(PageTest_722, GetDurationReturnsNonNegativeValue_722) {

    Page* page = createPage();

    double duration = page->getDuration();

    EXPECT_GE(duration, 0.0);

    delete page;

}



TEST_F(PageTest_722, GetActionsReturnsValidObject_722) {

    Page* page = createPage();

    Object actions = page->getActions();

    EXPECT_TRUE(actions.isNone()); // Assuming default constructed Object is None

    delete page;

}



TEST_F(PageTest_722, HasStandaloneFieldsReturnsFalseByDefault_722) {

    Page* page = createPage();

    EXPECT_FALSE(page->hasStandaloneFields());

    delete page;

}



TEST_F(PageTest_722, GetStructParentsReturnsNonNegativeValue_722) {

    Page* page = createPage();

    int structParents = page->getStructParents();

    EXPECT_GE(structParents, 0);

    delete page;

}
