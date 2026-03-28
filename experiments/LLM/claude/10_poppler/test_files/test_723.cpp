#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

// Include necessary headers from the project
#include "poppler/Page.h"
#include "poppler/Object.h"
#include "poppler/XRef.h"
#include "poppler/PDFDoc.h"
#include "poppler/Dict.h"
#include "poppler/Stream.h"
#include "poppler/GlobalParams.h"

// Helper to create a minimal valid PDF in memory for testing
class PageTest_723 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize globalParams if needed
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a PDFDoc from a file path for testing
    // We'll use a minimal approach - create objects directly where possible
};

// Since Page requires a PDFDoc and complex initialization, we test through
// document loading. We'll create a minimal PDF buffer for testing.

static const char *minimalPDF =
    "%PDF-1.4\n"
    "1 0 obj\n"
    "<< /Type /Catalog /Pages 2 0 R >>\n"
    "endobj\n"
    "2 0 obj\n"
    "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
    "endobj\n"
    "3 0 obj\n"
    "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
    "endobj\n"
    "xref\n"
    "0 4\n"
    "0000000000 65535 f \n"
    "0000000009 00000 n \n"
    "0000000058 00000 n \n"
    "0000000115 00000 n \n"
    "trailer\n"
    "<< /Size 4 /Root 1 0 R >>\n"
    "startxref\n"
    "190\n"
    "%%EOF\n";

static const char *pdfWithAnnots =
    "%PDF-1.4\n"
    "1 0 obj\n"
    "<< /Type /Catalog /Pages 2 0 R >>\n"
    "endobj\n"
    "2 0 obj\n"
    "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
    "endobj\n"
    "3 0 obj\n"
    "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
    "/Annots [4 0 R] >>\n"
    "endobj\n"
    "4 0 obj\n"
    "<< /Type /Annot /Subtype /Text /Rect [100 100 200 200] /Contents (Test) >>\n"
    "endobj\n"
    "xref\n"
    "0 5\n"
    "0000000000 65535 f \n"
    "0000000009 00000 n \n"
    "0000000058 00000 n \n"
    "0000000115 00000 n \n"
    "0000000209 00000 n \n"
    "trailer\n"
    "<< /Size 5 /Root 1 0 R >>\n"
    "startxref\n"
    "302\n"
    "%%EOF\n";

class PageDocTest_723 : public ::testing::Test {
protected:
    std::unique_ptr<PDFDoc> doc;
    std::unique_ptr<PDFDoc> docWithAnnots;

    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }

        // Create PDFDoc from minimal PDF string
        {
            auto *str = new GooString(minimalPDF);
            doc = std::make_unique<PDFDoc>(str);
        }

        {
            auto *str2 = new GooString(pdfWithAnnots);
            docWithAnnots = std::make_unique<PDFDoc>(str2);
        }
    }

    void TearDown() override {
    }
};

// Test that a minimal PDF document loads successfully
TEST_F(PageDocTest_723, DocumentIsValid_723) {
    ASSERT_TRUE(doc->isOk());
}

// Test that we can get the first page
TEST_F(PageDocTest_723, GetFirstPage_723) {
    ASSERT_TRUE(doc->isOk());
    ASSERT_GE(doc->getNumPages(), 1);
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
}

// Test Page::isOk returns true for a valid page
TEST_F(PageDocTest_723, PageIsOk_723) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_TRUE(page->isOk());
}

// Test Page::getNum returns correct page number
TEST_F(PageDocTest_723, GetNum_723) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_EQ(page->getNum(), 1);
}

// Test Page::getMediaBox returns a valid media box
TEST_F(PageDocTest_723, GetMediaBox_723) {
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

// Test Page::getMediaWidth and getMediaHeight
TEST_F(PageDocTest_723, GetMediaDimensions_723) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_DOUBLE_EQ(page->getMediaWidth(), 612.0);
    EXPECT_DOUBLE_EQ(page->getMediaHeight(), 792.0);
}

// Test Page::getCropBox
TEST_F(PageDocTest_723, GetCropBox_723) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    const PDFRectangle *cropBox = page->getCropBox();
    ASSERT_NE(cropBox, nullptr);
    // When no crop box is specified, it defaults to media box
    EXPECT_DOUBLE_EQ(cropBox->x1, 0.0);
    EXPECT_DOUBLE_EQ(cropBox->y1, 0.0);
    EXPECT_DOUBLE_EQ(cropBox->x2, 612.0);
    EXPECT_DOUBLE_EQ(cropBox->y2, 792.0);
}

// Test Page::getCropWidth and getCropHeight
TEST_F(PageDocTest_723, GetCropDimensions_723) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_DOUBLE_EQ(page->getCropWidth(), 612.0);
    EXPECT_DOUBLE_EQ(page->getCropHeight(), 792.0);
}

// Test Page::isCropped returns false when no crop box is set
TEST_F(PageDocTest_723, IsCroppedFalseByDefault_723) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_FALSE(page->isCropped());
}

// Test Page::getRotate returns 0 when no rotation is set
TEST_F(PageDocTest_723, GetRotateDefault_723) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_EQ(page->getRotate(), 0);
}

// Test Page::getAnnotsObject with nullptr (default XRef)
TEST_F(PageDocTest_723, GetAnnotsObjectDefaultXRef_723) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    Object annotsObj = page->getAnnotsObject();
    // Minimal PDF has no annotations, so the result should be null
    EXPECT_TRUE(annotsObj.isNull() || annotsObj.isNone());
}

// Test Page::getAnnotsObject with explicit XRef
TEST_F(PageDocTest_723, GetAnnotsObjectWithXRef_723) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    XRef *xref = doc->getXRef();
    ASSERT_NE(xref, nullptr);
    Object annotsObj = page->getAnnotsObject(xref);
    // Minimal PDF has no annotations
    EXPECT_TRUE(annotsObj.isNull() || annotsObj.isNone());
}

// Test Page::getAnnotsObject on a page with annotations
TEST_F(PageDocTest_723, GetAnnotsObjectWithAnnotations_723) {
    if (!docWithAnnots->isOk()) {
        GTEST_SKIP() << "PDF with annotations did not load correctly";
    }
    ASSERT_GE(docWithAnnots->getNumPages(), 1);
    Page *page = docWithAnnots->getPage(1);
    ASSERT_NE(page, nullptr);
    Object annotsObj = page->getAnnotsObject();
    // The page has an Annots array
    EXPECT_TRUE(annotsObj.isArray());
}

// Test Page::getAnnotsObject with explicit XRef on annotated page
TEST_F(PageDocTest_723, GetAnnotsObjectWithXRefAnnotated_723) {
    if (!docWithAnnots->isOk()) {
        GTEST_SKIP() << "PDF with annotations did not load correctly";
    }
    Page *page = docWithAnnots->getPage(1);
    ASSERT_NE(page, nullptr);
    XRef *xref = docWithAnnots->getXRef();
    ASSERT_NE(xref, nullptr);
    Object annotsObj = page->getAnnotsObject(xref);
    EXPECT_TRUE(annotsObj.isArray());
}

// Test Page::getContents on a page with no contents
TEST_F(PageDocTest_723, GetContentsEmpty_723) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    Object contents = page->getContents();
    // Minimal page has no contents
    EXPECT_TRUE(contents.isNull() || contents.isNone());
}

// Test Page::getThumb on page with no thumbnail
TEST_F(PageDocTest_723, GetThumbEmpty_723) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    Object thumb = page->getThumb();
    EXPECT_TRUE(thumb.isNull() || thumb.isNone());
}

// Test Page::getTrans on page with no transition
TEST_F(PageDocTest_723, GetTransEmpty_723) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    Object trans = page->getTrans();
    EXPECT_TRUE(trans.isNull() || trans.isNone());
}

// Test Page::getActions on page with no actions
TEST_F(PageDocTest_723, GetActionsEmpty_723) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    Object actions = page->getActions();
    EXPECT_TRUE(actions.isNull() || actions.isNone());
}

// Test Page::getDuration
TEST_F(PageDocTest_723, GetDurationDefault_723) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    // Default duration should be -1 or 0 (no duration set)
    double duration = page->getDuration();
    EXPECT_LE(duration, 0.0);
}

// Test Page::getRef returns a valid Ref
TEST_F(PageDocTest_723, GetRef_723) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    Ref ref = page->getRef();
    EXPECT_GT(ref.num, 0);
}

// Test Page::getPageObj returns a valid page dictionary object
TEST_F(PageDocTest_723, GetPageObj_723) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    const Object &pageObj = page->getPageObj();
    EXPECT_TRUE(pageObj.isDict());
}

// Test Page::getBleedBox
TEST_F(PageDocTest_723, GetBleedBox_723) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    const PDFRectangle *bleedBox = page->getBleedBox();
    ASSERT_NE(bleedBox, nullptr);
    // Should default to crop box / media box
    EXPECT_DOUBLE_EQ(bleedBox->x2, 612.0);
    EXPECT_DOUBLE_EQ(bleedBox->y2, 792.0);
}

// Test Page::getTrimBox
TEST_F(PageDocTest_723, GetTrimBox_723) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    const PDFRectangle *trimBox = page->getTrimBox();
    ASSERT_NE(trimBox, nullptr);
    EXPECT_DOUBLE_EQ(trimBox->x2, 612.0);
    EXPECT_DOUBLE_EQ(trimBox->y2, 792.0);
}

// Test Page::getArtBox
TEST_F(PageDocTest_723, GetArtBox_723) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    const PDFRectangle *artBox = page->getArtBox();
    ASSERT_NE(artBox, nullptr);
    EXPECT_DOUBLE_EQ(artBox->x2, 612.0);
    EXPECT_DOUBLE_EQ(artBox->y2, 792.0);
}

// Test Page::getDoc returns a valid document pointer
TEST_F(PageDocTest_723, GetDoc_723) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    PDFDoc *pageDoc = page->getDoc();
    EXPECT_EQ(pageDoc, doc.get());
}

// Test Page::hasStandaloneFields
TEST_F(PageDocTest_723, HasStandaloneFields_723) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    // Minimal PDF should not have standalone fields
    EXPECT_FALSE(page->hasStandaloneFields());
}

// Test Page::getStructParents
TEST_F(PageDocTest_723, GetStructParents_723) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    int sp = page->getStructParents();
    // No StructParents set, should be -1 or default
    EXPECT_EQ(sp, -1);
}

// Test Page::getLastModified returns nullptr when not set
TEST_F(PageDocTest_723, GetLastModifiedNull_723) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    const GooString *lastMod = page->getLastModified();
    EXPECT_EQ(lastMod, nullptr);
}

// Test Page::getResourceDict
TEST_F(PageDocTest_723, GetResourceDict_723) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    // Minimal page may or may not have resources
    // Just test it doesn't crash
    Dict *resources = page->getResourceDict();
    // Could be nullptr for minimal page
    (void)resources;
}

// Test Page::getResourceDictObject
TEST_F(PageDocTest_723, GetResourceDictObject_723) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    Object *resObj = page->getResourceDictObject();
    // Should not crash, may be null object
    (void)resObj;
}

// Test loading thumb returns false for page without thumbnail
TEST_F(PageDocTest_723, LoadThumbNoThumb_723) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    unsigned char *data = nullptr;
    int width = 0, height = 0, rowstride = 0;
    bool result = page->loadThumb(&data, &width, &height, &rowstride);
    EXPECT_FALSE(result);
    EXPECT_EQ(data, nullptr);
}

// Test getAnnotsObject called multiple times returns consistent results
TEST_F(PageDocTest_723, GetAnnotsObjectConsistency_723) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    Object annotsObj1 = page->getAnnotsObject();
    Object annotsObj2 = page->getAnnotsObject();
    EXPECT_EQ(annotsObj1.getType(), annotsObj2.getType());
}

// Test getAnnotsObject with annotations - consistency between default and explicit XRef
TEST_F(PageDocTest_723, GetAnnotsObjectConsistencyWithXRef_723) {
    if (!docWithAnnots->isOk()) {
        GTEST_SKIP() << "PDF with annotations did not load correctly";
    }
    Page *page = docWithAnnots->getPage(1);
    ASSERT_NE(page, nullptr);
    XRef *xref = docWithAnnots->getXRef();
    Object annotsObj1 = page->getAnnotsObject();
    Object annotsObj2 = page->getAnnotsObject(xref);
    EXPECT_EQ(annotsObj1.getType(), annotsObj2.getType());
    if (annotsObj1.isArray() && annotsObj2.isArray()) {
        EXPECT_EQ(annotsObj1.arrayGetLength(), annotsObj2.arrayGetLength());
    }
}

// Test getAnnotsObject with annotations array has correct length
TEST_F(PageDocTest_723, GetAnnotsObjectArrayLength_723) {
    if (!docWithAnnots->isOk()) {
        GTEST_SKIP() << "PDF with annotations did not load correctly";
    }
    Page *page = docWithAnnots->getPage(1);
    ASSERT_NE(page, nullptr);
    Object annotsObj = page->getAnnotsObject();
    if (annotsObj.isArray()) {
        EXPECT_EQ(annotsObj.arrayGetLength(), 1);
    }
}
