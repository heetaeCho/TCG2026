#include <gtest/gtest.h>

#include "poppler/Page.h"

#include <memory>



class PageTest : public ::testing::Test {

protected:

    std::unique_ptr<Page> page;

    PDFDoc* docMock = nullptr; // Assuming PDFDoc is a class that needs to be mocked or passed in

    Object pageDictMock;        // Mock object for the page dictionary

    Ref pageRefMock;            // Mock reference for the page



    void SetUp() override {

        page = std::make_unique<Page>(docMock, 702, std::move(pageDictMock), pageRefMock, std::make_unique<PageAttrs>());

    }

};



TEST_F(PageTest_702, GetNum_ReturnsCorrectNumber_702) {

    EXPECT_EQ(page->getNum(), 702);

}



TEST_F(PageTest_702, IsOk_ReturnsTrue_702) {

    EXPECT_TRUE(page->isOk());

}



TEST_F(PageTest_702, GetResourceDict_ReturnsNonNullPointer_702) {

    EXPECT_NE(page->getResourceDict(), nullptr);

}



TEST_F(PageTest_702, GetResourceDictObject_ReturnsNonNullPointer_702) {

    EXPECT_NE(page->getResourceDictObject(), nullptr);

}



TEST_F(PageTest_702, AddAnnot_ReturnsTrueForValidAnnotation_702) {

    auto annot = std::make_shared<Annot>();

    EXPECT_TRUE(page->addAnnot(annot));

}



TEST_F(PageTest_702, RemoveAnnot_DoesNotThrowForValidAnnotation_702) {

    auto annot = std::make_shared<Annot>();

    page->addAnnot(annot);

    EXPECT_NO_THROW(page->removeAnnot(annot));

}



TEST_F(PageTest_702, GetLinks_ReturnsNonNullPointer_702) {

    EXPECT_NE(page->getLinks(), nullptr);

}



TEST_F(PageTest_702, GetAnnots_ReturnsNonNullPointerWithValidXRef_702) {

    XRef xrefMock; // Assuming XRef is a class that needs to be mocked or passed in

    EXPECT_NE(page->getAnnots(&xrefMock), nullptr);

}



TEST_F(PageTest_702, LoadThumb_ReturnsTrueForValidDataPointers_702) {

    unsigned char* data = nullptr;

    int width = 0, height = 0, rowstride = 0;

    EXPECT_TRUE(page->loadThumb(&data, &width, &height, &rowstride));

}



TEST_F(PageTest_702, GetFormWidgets_ReturnsNonNullPointer_702) {

    EXPECT_NE(page->getFormWidgets(), nullptr);

}



TEST_F(PageTest_702, GetAdditionalAction_ReturnsNonNullPointerForValidType_702) {

    EXPECT_NE(page->getAdditionalAction(PA_OPEN), nullptr);

}



TEST_F(PageTest_702, CreateGfx_ReturnsNonNullPointerWithValidOutputDev_702) {

    OutputDev* outMock = nullptr; // Assuming OutputDev is a class that needs to be mocked or passed in

    EXPECT_NE(page->createGfx(outMock, 150.0, 150.0, 0, true, false, 0, 0, 0, 0, nullptr, nullptr, nullptr), nullptr);

}



TEST_F(PageTest_702, Display_DoesNotThrowWithValidOutputDev_702) {

    OutputDev* outMock = nullptr; // Assuming OutputDev is a class that needs to be mocked or passed in

    EXPECT_NO_THROW(page->display(outMock, 150.0, 150.0, 0, true, false, true, nullptr, nullptr, nullptr, nullptr, false));

}



TEST_F(PageTest_702, DisplaySlice_DoesNotThrowWithValidOutputDevAndSliceParameters_702) {

    OutputDev* outMock = nullptr; // Assuming OutputDev is a class that needs to be mocked or passed in

    EXPECT_NO_THROW(page->displaySlice(outMock, 150.0, 150.0, 0, true, false, 0, 0, 100, 100, true, nullptr, nullptr, nullptr, nullptr, false));

}



TEST_F(PageTest_702, Display_DoesNotThrowWithValidGfx_702) {

    Gfx* gfxMock = nullptr; // Assuming Gfx is a class that needs to be mocked or passed in

    EXPECT_NO_THROW(page->display(gfxMock));

}



TEST_F(PageTest_702, MakeBox_DoesNotThrowWithValidParameters_702) {

    PDFRectangle box;

    _Bool crop;

    EXPECT_NO_THROW(page->makeBox(150.0, 150.0, 0, true, false, 0, 0, 100, 100, &box, &crop));

}



TEST_F(PageTest_702, ProcessLinks_DoesNotThrowWithValidOutputDev_702) {

    OutputDev* outMock = nullptr; // Assuming OutputDev is a class that needs to be mocked or passed in

    EXPECT_NO_THROW(page->processLinks(outMock));

}



TEST_F(PageTest_702, GetDefaultCTM_DoesNotThrowWithValidParameters_702) {

    double ctm[6];

    EXPECT_NO_THROW(page->getDefaultCTM(ctm, 150.0, 150.0, 0, true, false));

}



TEST_F(PageTest_702, GetMediaBox_ReturnsNonNullPointer_702) {

    EXPECT_NE(page->getMediaBox(), nullptr);

}



TEST_F(PageTest_702, GetCropBox_ReturnsNonNullPointer_702) {

    EXPECT_NE(page->getCropBox(), nullptr);

}



TEST_F(PageTest_702, IsCropped_ReturnsFalseForDefaultPage_702) {

    EXPECT_FALSE(page->isCropped());

}



TEST_F(PageTest_702, GetMediaWidth_ReturnsPositiveValue_702) {

    EXPECT_GT(page->getMediaWidth(), 0.0);

}



TEST_F(PageTest_702, GetMediaHeight_ReturnsPositiveValue_702) {

    EXPECT_GT(page->getMediaHeight(), 0.0);

}



TEST_F(PageTest_702, GetCropWidth_ReturnsPositiveOrZeroValue_702) {

    EXPECT_GE(page->getCropWidth(), 0.0);

}



TEST_F(PageTest_702, GetCropHeight_ReturnsPositiveOrZeroValue_702) {

    EXPECT_GE(page->getCropHeight(), 0.0);

}



TEST_F(PageTest_702, GetBleedBox_ReturnsNonNullPointer_702) {

    EXPECT_NE(page->getBleedBox(), nullptr);

}



TEST_F(PageTest_702, GetTrimBox_ReturnsNonNullPointer_702) {

    EXPECT_NE(page->getTrimBox(), nullptr);

}



TEST_F(PageTest_702, GetArtBox_ReturnsNonNullPointer_702) {

    EXPECT_NE(page->getArtBox(), nullptr);

}



TEST_F(PageTest_702, GetRotate_ReturnsNonNegativeValue_702) {

    EXPECT_GE(page->getRotate(), 0);

}



TEST_F(PageTest_702, GetLastModified_ReturnsNonNullPointerIfSet_702) {

    // Assuming the last modified date is set

    EXPECT_NE(page->getLastModified(), nullptr);

}



TEST_F(PageTest_702, GetBoxColorInfo_ReturnsNonNullPointer_702) {

    EXPECT_NE(page->getBoxColorInfo(), nullptr);

}



TEST_F(PageTest_702, GetGroup_ReturnsNonNullPointer_702) {

    EXPECT_NE(page->getGroup(), nullptr);

}



TEST_F(PageTest_702, GetMetadata_ReturnsNonNullPointerIfSet_702) {

    // Assuming metadata is set

    EXPECT_NE(page->getMetadata(), nullptr);

}



TEST_F(PageTest_702, GetPieceInfo_ReturnsNonNullPointer_702) {

    EXPECT_NE(page->getPieceInfo(), nullptr);

}



TEST_F(PageTest_702, GetSeparationInfo_ReturnsNonNullPointer_702) {

    EXPECT_NE(page->getSeparationInfo(), nullptr);

}



TEST_F(PageTest_702, GetDoc_ReturnsNonNullPointer_702) {

    EXPECT_NE(page->getDoc(), nullptr);

}



TEST_F(PageTest_702, GetRef_ReturnsValidReference_702) {

    Ref ref = page->getRef();

    EXPECT_TRUE(ref.num > 0 && ref.gen >= 0);

}



TEST_F(PageTest_702, GetPageObj_ReturnsNonNullObject_702) {

    EXPECT_NE(&page->getPageObj(), nullptr);

}



TEST_F(PageTest_702, GetAnnotsObject_ReturnsValidObject_702) {

    Object obj = page->getAnnotsObject();

    EXPECT_TRUE(obj.isDict() || obj.isNull());

}



TEST_F(PageTest_702, GetContents_ReturnsNonNullObject_702) {

    EXPECT_NE(&page->getContents(), nullptr);

}



TEST_F(PageTest_702, GetThumb_ReturnsNonNullObject_702) {

    EXPECT_NE(&page->getThumb(), nullptr);

}



TEST_F(PageTest_702, GetTrans_ReturnsNonNullObject_702) {

    EXPECT_NE(&page->getTrans(), nullptr);

}



TEST_F(PageTest_702, GetDuration_ReturnsNonNegativeValue_702) {

    EXPECT_GE(page->getDuration(), 0.0);

}



TEST_F(PageTest_702, GetActions_ReturnsNonNullObject_702) {

    EXPECT_NE(&page->getActions(), nullptr);

}



TEST_F(PageTest_702, HasStandaloneFields_ReturnsFalseForDefaultPage_702) {

    EXPECT_FALSE(page->hasStandaloneFields());

}



TEST_F(PageTest_702, GetStructParents_ReturnsNonNegativeValue_702) {

    EXPECT_GE(page->getStructParents(), 0);

}
