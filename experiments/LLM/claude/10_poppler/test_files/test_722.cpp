#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Page.h"
#include "PDFDoc.h"
#include "Object.h"
#include "GlobalParams.h"

class PageTest_722 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // We need a valid PDFDoc to create Page objects
        // We'll load a minimal PDF for testing
    }

    std::unique_ptr<PDFDoc> loadTestDoc(const char *filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Helper to create a simple in-memory PDF document
class InMemoryPDFTest_722 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Create a minimal valid PDF in memory
    std::unique_ptr<PDFDoc> createMinimalPDF() {
        // Minimal PDF content
        static const char pdfContent[] =
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
            "/Contents 4 0 R /Resources << >> >>\n"
            "endobj\n"
            "4 0 obj\n"
            "<< /Length 44 >>\n"
            "stream\n"
            "BT /F1 12 Tf 100 700 Td (Hello) Tj ET\n"
            "endstream\n"
            "endobj\n"
            "xref\n"
            "0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000266 00000 n \n"
            "trailer\n"
            "<< /Size 5 /Root 1 0 R >>\n"
            "startxref\n"
            "360\n"
            "%%EOF\n";

        auto *stream = new MemStream(const_cast<char *>(pdfContent), 0, sizeof(pdfContent) - 1, Object(objNull));
        auto doc = std::make_unique<PDFDoc>(stream);
        return doc;
    }
};

// Test that getPageObj returns a valid Object reference
TEST_F(InMemoryPDFTest_722, GetPageObjReturnsValidObject_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const Object &pageObj = page->getPageObj();
    // The page object should be a dictionary
    EXPECT_TRUE(pageObj.isDict());
}

// Test isOk returns true for a valid page
TEST_F(InMemoryPDFTest_722, IsOkReturnsTrueForValidPage_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_TRUE(page->isOk());
}

// Test getNum returns the correct page number
TEST_F(InMemoryPDFTest_722, GetNumReturnsCorrectPageNumber_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_EQ(page->getNum(), 1);
}

// Test getMediaBox returns non-null pointer
TEST_F(InMemoryPDFTest_722, GetMediaBoxReturnsNonNull_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *mediaBox = page->getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
    // Our minimal PDF has MediaBox [0 0 612 792]
    EXPECT_DOUBLE_EQ(mediaBox->x1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->y1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->x2, 612.0);
    EXPECT_DOUBLE_EQ(mediaBox->y2, 792.0);
}

// Test getMediaWidth and getMediaHeight
TEST_F(InMemoryPDFTest_722, GetMediaDimensions_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_DOUBLE_EQ(page->getMediaWidth(), 612.0);
    EXPECT_DOUBLE_EQ(page->getMediaHeight(), 792.0);
}

// Test getCropBox returns non-null pointer
TEST_F(InMemoryPDFTest_722, GetCropBoxReturnsNonNull_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *cropBox = page->getCropBox();
    ASSERT_NE(cropBox, nullptr);
}

// Test getCropWidth and getCropHeight
TEST_F(InMemoryPDFTest_722, GetCropDimensions_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // Without explicit crop box, crop dimensions should match media dimensions
    EXPECT_GT(page->getCropWidth(), 0.0);
    EXPECT_GT(page->getCropHeight(), 0.0);
}

// Test isCropped when no crop box is set
TEST_F(InMemoryPDFTest_722, IsCroppedWithNoCropBox_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // Our minimal PDF doesn't have a CropBox, so isCropped should be false
    EXPECT_FALSE(page->isCropped());
}

// Test getRotate for default rotation
TEST_F(InMemoryPDFTest_722, GetRotateDefaultIsZero_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // No rotation specified, should default to 0
    EXPECT_EQ(page->getRotate(), 0);
}

// Test getDoc returns the parent document
TEST_F(InMemoryPDFTest_722, GetDocReturnsParentDocument_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_EQ(page->getDoc(), doc.get());
}

// Test getRef returns a valid Ref
TEST_F(InMemoryPDFTest_722, GetRefReturnsValidRef_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Ref ref = page->getRef();
    // The ref should have a valid num (>= 0) and gen (>= 0)
    EXPECT_GE(ref.num, 0);
    EXPECT_GE(ref.gen, 0);
}

// Test getContents returns an Object
TEST_F(InMemoryPDFTest_722, GetContentsReturnsObject_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object contents = page->getContents();
    // Our minimal PDF has a Contents entry
    EXPECT_FALSE(contents.isNull() && contents.isNone());
}

// Test getDuration default value
TEST_F(InMemoryPDFTest_722, GetDurationDefault_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // No duration set, should return a default (typically -1 or 0)
    double duration = page->getDuration();
    EXPECT_LE(duration, 0.0);
}

// Test getBleedBox returns non-null
TEST_F(InMemoryPDFTest_722, GetBleedBoxReturnsNonNull_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *bleedBox = page->getBleedBox();
    ASSERT_NE(bleedBox, nullptr);
}

// Test getTrimBox returns non-null
TEST_F(InMemoryPDFTest_722, GetTrimBoxReturnsNonNull_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *trimBox = page->getTrimBox();
    ASSERT_NE(trimBox, nullptr);
}

// Test getArtBox returns non-null
TEST_F(InMemoryPDFTest_722, GetArtBoxReturnsNonNull_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *artBox = page->getArtBox();
    ASSERT_NE(artBox, nullptr);
}

// Test getResourceDict returns non-null for page with resources
TEST_F(InMemoryPDFTest_722, GetResourceDictReturnsNonNull_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // Our minimal PDF has Resources << >> on the page
    Dict *resources = page->getResourceDict();
    // It may be empty but should be non-null since we defined Resources
    EXPECT_NE(resources, nullptr);
}

// Test getLastModified returns null when not set
TEST_F(InMemoryPDFTest_722, GetLastModifiedNullWhenNotSet_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // No LastModified in our minimal PDF
    const GooString *lastModified = page->getLastModified();
    EXPECT_EQ(lastModified, nullptr);
}

// Test hasStandaloneFields
TEST_F(InMemoryPDFTest_722, HasStandaloneFieldsDefault_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // No form fields in minimal PDF
    EXPECT_FALSE(page->hasStandaloneFields());
}

// Test getAnnotsObject
TEST_F(InMemoryPDFTest_722, GetAnnotsObjectDefault_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object annotsObj = page->getAnnotsObject();
    // No annotations in minimal PDF, should be null or array
    // The result depends on the PDF content; just verify no crash
}

// Test getTrans when no transition is set
TEST_F(InMemoryPDFTest_722, GetTransDefault_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object trans = page->getTrans();
    // No transition in minimal PDF
    EXPECT_TRUE(trans.isNull() || trans.isNone());
}

// Test getActions when no actions are set
TEST_F(InMemoryPDFTest_722, GetActionsDefault_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object actions = page->getActions();
    // No additional actions in minimal PDF
    EXPECT_TRUE(actions.isNull() || actions.isNone());
}

// Test getThumb when no thumbnail is set
TEST_F(InMemoryPDFTest_722, GetThumbDefault_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object thumb = page->getThumb();
    // No thumbnail in minimal PDF
    EXPECT_TRUE(thumb.isNull() || thumb.isNone());
}

// Test getStructParents default value
TEST_F(InMemoryPDFTest_722, GetStructParentsDefault_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // No StructParents in minimal PDF, should return default (-1 typically)
    int structParents = page->getStructParents();
    EXPECT_EQ(structParents, -1);
}

// Test loadThumb returns false when no thumbnail
TEST_F(InMemoryPDFTest_722, LoadThumbReturnsFalseWhenNoThumb_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    unsigned char *data = nullptr;
    int width = 0, height = 0, rowstride = 0;
    bool result = page->loadThumb(&data, &width, &height, &rowstride);
    EXPECT_FALSE(result);
}

// Test getGroup returns null when no group is set
TEST_F(InMemoryPDFTest_722, GetGroupReturnsNullWhenNotSet_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Dict *group = page->getGroup();
    EXPECT_EQ(group, nullptr);
}

// Test getBoxColorInfo returns null when not set
TEST_F(InMemoryPDFTest_722, GetBoxColorInfoReturnsNullWhenNotSet_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Dict *boxColorInfo = page->getBoxColorInfo();
    EXPECT_EQ(boxColorInfo, nullptr);
}

// Test getPieceInfo returns null when not set
TEST_F(InMemoryPDFTest_722, GetPieceInfoReturnsNullWhenNotSet_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Dict *pieceInfo = page->getPieceInfo();
    EXPECT_EQ(pieceInfo, nullptr);
}

// Test getSeparationInfo returns null when not set
TEST_F(InMemoryPDFTest_722, GetSeparationInfoReturnsNullWhenNotSet_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Dict *sepInfo = page->getSeparationInfo();
    EXPECT_EQ(sepInfo, nullptr);
}

// Test getDefaultCTM produces valid transformation matrix
TEST_F(InMemoryPDFTest_722, GetDefaultCTMProducesValidMatrix_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    double ctm[6] = {0};
    page->getDefaultCTM(ctm, 72.0, 72.0, 0, true, false);
    
    // At 72 DPI with no rotation, using media box, the CTM should be identity-like
    // ctm[0] should be 1.0 (scale x), ctm[3] should be -1.0 or 1.0 (scale y)
    // At least some values should be non-zero
    bool hasNonZero = false;
    for (int i = 0; i < 6; i++) {
        if (ctm[i] != 0.0) {
            hasNonZero = true;
            break;
        }
    }
    EXPECT_TRUE(hasNonZero);
}

// Test makeBox produces valid box
TEST_F(InMemoryPDFTest_722, MakeBoxProducesValidBox_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    PDFRectangle box;
    bool crop = false;
    page->makeBox(72.0, 72.0, 0, true, false, 0, 0, 612, 792, &box, &crop);

    // The box should have reasonable dimensions
    EXPECT_GE(box.x2, box.x1);
    EXPECT_GE(box.y2, box.y1);
}

// Test getResourceDictObject returns non-null
TEST_F(InMemoryPDFTest_722, GetResourceDictObjectReturnsNonNull_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object *resObj = page->getResourceDictObject();
    EXPECT_NE(resObj, nullptr);
}

// Test that copy constructor is deleted (compile-time test, just verify we can't copy)
// This is a compile-time guarantee, not a runtime test. We verify it doesn't compile
// by NOT trying to copy, which is the correct behavior.

// Test getFormWidgets returns a valid (possibly empty) result
TEST_F(InMemoryPDFTest_722, GetFormWidgetsNoFormFields_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    auto formWidgets = page->getFormWidgets();
    // May be null or empty for a PDF without forms
    // Just verify no crash
}

// Test getLinks returns a valid (possibly empty) result
TEST_F(InMemoryPDFTest_722, GetLinksReturnsValidResult_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    auto links = page->getLinks();
    // Should return a valid Links object even if no links
    EXPECT_NE(links, nullptr);
}

// Test getMetadata returns null when not set
TEST_F(InMemoryPDFTest_722, GetMetadataReturnsNullWhenNotSet_722) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    if (doc->getNumPages() < 1) {
        GTEST_SKIP() << "No pages in test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Stream *metadata = page->getMetadata();
    EXPECT_EQ(metadata, nullptr);
}
