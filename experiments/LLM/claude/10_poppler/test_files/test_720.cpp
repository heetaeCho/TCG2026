#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "PDFDoc.h"
#include "Page.h"
#include "GlobalParams.h"

class PageTest_720 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
    }

    void TearDown() override {
    }

    std::unique_ptr<PDFDoc> loadTestDoc(const char *filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Helper to find a valid test PDF. We'll use a simple approach.
// Many poppler test suites assume a test PDF is available.
// We'll create a minimal in-memory PDF for testing.

static std::unique_ptr<PDFDoc> createMinimalPDF() {
    // Minimal valid PDF content
    const char *pdfContent =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    size_t len = strlen(pdfContent);
    char *buf = (char *)gmalloc(len);
    memcpy(buf, pdfContent, len);

    auto stream = new MemStream(buf, 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    // Note: buf ownership is taken by MemStream/PDFDoc
    return doc;
}

TEST_F(PageTest_720, GetDocReturnsNonNull_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    ASSERT_GE(doc->getNumPages(), 1);

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_EQ(page->getDoc(), doc.get());
}

TEST_F(PageTest_720, IsOkReturnsTrueForValidPage_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    ASSERT_GE(doc->getNumPages(), 1);

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_TRUE(page->isOk());
}

TEST_F(PageTest_720, GetNumReturnsCorrectPageNumber_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    ASSERT_GE(doc->getNumPages(), 1);

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_EQ(page->getNum(), 1);
}

TEST_F(PageTest_720, GetMediaBoxReturnsNonNull_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *mediaBox = page->getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
    EXPECT_DOUBLE_EQ(mediaBox->x1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->y1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->x2, 612.0);
    EXPECT_DOUBLE_EQ(mediaBox->y2, 792.0);
}

TEST_F(PageTest_720, GetMediaWidthAndHeight_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_DOUBLE_EQ(page->getMediaWidth(), 612.0);
    EXPECT_DOUBLE_EQ(page->getMediaHeight(), 792.0);
}

TEST_F(PageTest_720, GetCropBoxReturnsNonNull_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *cropBox = page->getCropBox();
    ASSERT_NE(cropBox, nullptr);
}

TEST_F(PageTest_720, GetCropWidthAndHeight_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // If no explicit CropBox, it defaults to MediaBox
    EXPECT_DOUBLE_EQ(page->getCropWidth(), 612.0);
    EXPECT_DOUBLE_EQ(page->getCropHeight(), 792.0);
}

TEST_F(PageTest_720, IsCroppedDefaultFalse_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // No explicit CropBox, so isCropped should be false
    EXPECT_FALSE(page->isCropped());
}

TEST_F(PageTest_720, GetRotateDefault_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // No explicit Rotate, default should be 0
    EXPECT_EQ(page->getRotate(), 0);
}

TEST_F(PageTest_720, GetBleedBoxReturnsNonNull_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *bleedBox = page->getBleedBox();
    ASSERT_NE(bleedBox, nullptr);
}

TEST_F(PageTest_720, GetTrimBoxReturnsNonNull_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *trimBox = page->getTrimBox();
    ASSERT_NE(trimBox, nullptr);
}

TEST_F(PageTest_720, GetArtBoxReturnsNonNull_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *artBox = page->getArtBox();
    ASSERT_NE(artBox, nullptr);
}

TEST_F(PageTest_720, GetLastModifiedDefaultNull_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // Minimal PDF has no LastModified
    EXPECT_EQ(page->getLastModified(), nullptr);
}

TEST_F(PageTest_720, GetDurationDefault_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // Default duration should be -1 (not set)
    EXPECT_EQ(page->getDuration(), -1.0);
}

TEST_F(PageTest_720, GetRef_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Ref ref = page->getRef();
    // The ref should have valid num (>= 0) and gen (>= 0)
    EXPECT_GE(ref.num, 0);
    EXPECT_GE(ref.gen, 0);
}

TEST_F(PageTest_720, GetPageObjIsNotNull_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const Object &pageObj = page->getPageObj();
    EXPECT_TRUE(pageObj.isDict());
}

TEST_F(PageTest_720, GetContents_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object contents = page->getContents();
    // Minimal PDF has no contents stream
    EXPECT_TRUE(contents.isNull());
}

TEST_F(PageTest_720, GetThumb_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object thumb = page->getThumb();
    // Minimal PDF has no thumbnail
    EXPECT_TRUE(thumb.isNull());
}

TEST_F(PageTest_720, GetTrans_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object trans = page->getTrans();
    // Minimal PDF has no transition
    EXPECT_TRUE(trans.isNull());
}

TEST_F(PageTest_720, GetActions_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object actions = page->getActions();
    // Minimal PDF has no actions
    EXPECT_TRUE(actions.isNull());
}

TEST_F(PageTest_720, HasStandaloneFieldsDefault_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_FALSE(page->hasStandaloneFields());
}

TEST_F(PageTest_720, GetStructParentsDefault_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // Default structParents should be -1 (not set)
    EXPECT_EQ(page->getStructParents(), -1);
}

TEST_F(PageTest_720, GetResourceDict_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // Minimal PDF may or may not have resources
    // Just test it doesn't crash
    Dict *resDict = page->getResourceDict();
    // Could be nullptr for minimal PDF
    (void)resDict;
}

TEST_F(PageTest_720, GetResourceDictObject_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object *resDictObj = page->getResourceDictObject();
    ASSERT_NE(resDictObj, nullptr);
}

TEST_F(PageTest_720, GetAnnotsObject_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object annotsObj = page->getAnnotsObject();
    // Minimal PDF has no annotations
    EXPECT_TRUE(annotsObj.isNull());
}

TEST_F(PageTest_720, GetLinksReturnsNonNull_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    auto links = page->getLinks();
    // Should return a valid Links object even if empty
    EXPECT_NE(links, nullptr);
}

TEST_F(PageTest_720, GetFormWidgets_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    auto formWidgets = page->getFormWidgets();
    // Minimal PDF has no form widgets, but should not crash
    // formWidgets could be nullptr or empty
}

TEST_F(PageTest_720, LoadThumbReturnsFalseForMinimalPDF_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    unsigned char *data = nullptr;
    int width = 0, height = 0, rowstride = 0;
    bool result = page->loadThumb(&data, &width, &height, &rowstride);
    EXPECT_FALSE(result);
}

TEST_F(PageTest_720, GetDefaultCTM_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    double ctm[6];
    page->getDefaultCTM(ctm, 72.0, 72.0, 0, true, false);
    // At 72 DPI with no rotation, for media box usage:
    // CTM should represent identity-like transformation scaled to 72 DPI
    // The exact values depend on implementation but should not all be zero
    bool allZero = true;
    for (int i = 0; i < 6; i++) {
        if (ctm[i] != 0.0) {
            allZero = false;
            break;
        }
    }
    EXPECT_FALSE(allZero);
}

TEST_F(PageTest_720, MakeBox_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    PDFRectangle box;
    bool crop = false;
    page->makeBox(72.0, 72.0, 0, true, false, 0, 0, 612, 792, &box, &crop);
    // Box should be set to something reasonable
    EXPECT_GE(box.x2, box.x1);
    EXPECT_GE(box.y2, box.y1);
}

TEST_F(PageTest_720, GetGroupDefaultNull_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Dict *group = page->getGroup();
    EXPECT_EQ(group, nullptr);
}

TEST_F(PageTest_720, GetBoxColorInfoDefaultNull_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Dict *boxColorInfo = page->getBoxColorInfo();
    EXPECT_EQ(boxColorInfo, nullptr);
}

TEST_F(PageTest_720, GetMetadataDefaultNull_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Stream *metadata = page->getMetadata();
    EXPECT_EQ(metadata, nullptr);
}

TEST_F(PageTest_720, GetPieceInfoDefaultNull_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Dict *pieceInfo = page->getPieceInfo();
    EXPECT_EQ(pieceInfo, nullptr);
}

TEST_F(PageTest_720, GetSeparationInfoDefaultNull_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Dict *sepInfo = page->getSeparationInfo();
    EXPECT_EQ(sepInfo, nullptr);
}

// Test with a rotated page
static std::unique_ptr<PDFDoc> createPDFWithRotation() {
    const char *pdfContent =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/Rotate 90>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "200\n"
        "%%EOF\n";

    size_t len = strlen(pdfContent);
    char *buf = (char *)gmalloc(len);
    memcpy(buf, pdfContent, len);

    auto stream = new MemStream(buf, 0, len, Object(objNull));
    return std::make_unique<PDFDoc>(stream);
}

TEST_F(PageTest_720, GetRotateWithExplicitRotation_720) {
    auto doc = createPDFWithRotation();
    if (!doc || !doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Could not create rotated PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_EQ(page->getRotate(), 90);
}

// Test with a cropped page
static std::unique_ptr<PDFDoc> createPDFWithCropBox() {
    const char *pdfContent =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/CropBox[10 10 600 780]>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "220\n"
        "%%EOF\n";

    size_t len = strlen(pdfContent);
    char *buf = (char *)gmalloc(len);
    memcpy(buf, pdfContent, len);

    auto stream = new MemStream(buf, 0, len, Object(objNull));
    return std::make_unique<PDFDoc>(stream);
}

TEST_F(PageTest_720, IsCroppedWithExplicitCropBox_720) {
    auto doc = createPDFWithCropBox();
    if (!doc || !doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Could not create cropped PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_TRUE(page->isCropped());
}

TEST_F(PageTest_720, CropBoxDimensionsWithExplicitCropBox_720) {
    auto doc = createPDFWithCropBox();
    if (!doc || !doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Could not create cropped PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *cropBox = page->getCropBox();
    ASSERT_NE(cropBox, nullptr);
    EXPECT_DOUBLE_EQ(cropBox->x1, 10.0);
    EXPECT_DOUBLE_EQ(cropBox->y1, 10.0);
    EXPECT_DOUBLE_EQ(cropBox->x2, 600.0);
    EXPECT_DOUBLE_EQ(cropBox->y2, 780.0);

    EXPECT_DOUBLE_EQ(page->getCropWidth(), 590.0);
    EXPECT_DOUBLE_EQ(page->getCropHeight(), 770.0);
}

TEST_F(PageTest_720, GetAnnotsWithXRef_720) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    XRef *xref = doc->getXRef();
    Annots *annots = page->getAnnots(xref);
    // Should return something (possibly empty annots), not crash
    EXPECT_NE(annots, nullptr);
}
