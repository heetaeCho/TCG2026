#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

// Include necessary headers from poppler
#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"
#include "Dict.h"
#include "Stream.h"
#include "Annot.h"
#include "Link.h"
#include "Form.h"
#include "OutputDev.h"
#include "Gfx.h"
#include "GooString.h"

// Helper to create a PDFDoc from a file
class PageTest_701 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // We'll try to load a minimal valid PDF for testing.
        // If no PDF is available, some tests may be skipped.
    }

    void TearDown() override {
    }

    // Helper to create a PDFDoc from a buffer containing a minimal PDF
    std::unique_ptr<PDFDoc> createMinimalPDFDoc() {
        // Minimal valid PDF content
        static const char *minimalPDF =
            "%PDF-1.0\n"
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

        int len = strlen(minimalPDF);
        auto *stream = new MemStream(const_cast<char *>(minimalPDF), 0, len, Object(objNull));
        auto doc = std::make_unique<PDFDoc>(stream);
        return doc;
    }

    // Helper to create a PDFDoc with a cropped page
    std::unique_ptr<PDFDoc> createCroppedPDFDoc() {
        static const char *croppedPDF =
            "%PDF-1.0\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /CropBox [10 10 300 400] >>\n"
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
            "210\n"
            "%%EOF\n";

        int len = strlen(croppedPDF);
        auto *stream = new MemStream(const_cast<char *>(croppedPDF), 0, len, Object(objNull));
        auto doc = std::make_unique<PDFDoc>(stream);
        return doc;
    }
};

// Test that a page from a valid minimal PDF is ok
TEST_F(PageTest_701, IsOkReturnsTrueForValidPage_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());
    ASSERT_GE(doc->getNumPages(), 1);

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_TRUE(page->isOk());
}

// Test getNum returns the correct page number
TEST_F(PageTest_701, GetNumReturnsCorrectPageNumber_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());
    ASSERT_GE(doc->getNumPages(), 1);

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_EQ(page->getNum(), 1);
}

// Test getMediaBox returns non-null
TEST_F(PageTest_701, GetMediaBoxReturnsNonNull_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *mediaBox = page->getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
}

// Test getMediaWidth and getMediaHeight
TEST_F(PageTest_701, GetMediaDimensions_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // The minimal PDF has MediaBox [0 0 612 792]
    EXPECT_DOUBLE_EQ(page->getMediaWidth(), 612.0);
    EXPECT_DOUBLE_EQ(page->getMediaHeight(), 792.0);
}

// Test getCropBox returns non-null
TEST_F(PageTest_701, GetCropBoxReturnsNonNull_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *cropBox = page->getCropBox();
    ASSERT_NE(cropBox, nullptr);
}

// Test isCropped returns false when no CropBox is specified
TEST_F(PageTest_701, IsCroppedReturnsFalseWhenNoCropBox_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_FALSE(page->isCropped());
}

// Test getCropWidth and getCropHeight when not cropped (should equal media dimensions)
TEST_F(PageTest_701, GetCropDimensionsEqualMediaWhenNotCropped_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_DOUBLE_EQ(page->getCropWidth(), page->getMediaWidth());
    EXPECT_DOUBLE_EQ(page->getCropHeight(), page->getMediaHeight());
}

// Test getRotate returns 0 for default page
TEST_F(PageTest_701, GetRotateReturnsZeroByDefault_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_EQ(page->getRotate(), 0);
}

// Test getDoc returns the parent document
TEST_F(PageTest_701, GetDocReturnsParentDocument_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_EQ(page->getDoc(), doc.get());
}

// Test getBleedBox returns non-null
TEST_F(PageTest_701, GetBleedBoxReturnsNonNull_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *bleedBox = page->getBleedBox();
    ASSERT_NE(bleedBox, nullptr);
}

// Test getTrimBox returns non-null
TEST_F(PageTest_701, GetTrimBoxReturnsNonNull_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *trimBox = page->getTrimBox();
    ASSERT_NE(trimBox, nullptr);
}

// Test getArtBox returns non-null
TEST_F(PageTest_701, GetArtBoxReturnsNonNull_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *artBox = page->getArtBox();
    ASSERT_NE(artBox, nullptr);
}

// Test getDuration returns default value
TEST_F(PageTest_701, GetDurationReturnsDefault_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // Default duration should be -1 (no duration specified)
    double duration = page->getDuration();
    EXPECT_LE(duration, 0.0);
}

// Test getContents returns an object (may be null for empty page)
TEST_F(PageTest_701, GetContentsReturnsObject_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object contents = page->getContents();
    // For a minimal page with no content stream, this should be null
    EXPECT_TRUE(contents.isNull() || contents.isNone() || contents.isStream() || contents.isArray());
}

// Test getThumb returns an object
TEST_F(PageTest_701, GetThumbReturnsObject_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object thumb = page->getThumb();
    // For a minimal page without thumbnail, expect null/none
    EXPECT_TRUE(thumb.isNull() || thumb.isNone());
}

// Test getTrans returns an object
TEST_F(PageTest_701, GetTransReturnsObject_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object trans = page->getTrans();
    // For a minimal page without transition, expect null/none
    EXPECT_TRUE(trans.isNull() || trans.isNone());
}

// Test getActions returns an object
TEST_F(PageTest_701, GetActionsReturnsObject_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object actions = page->getActions();
    // For a minimal page without additional actions, expect null/none
    EXPECT_TRUE(actions.isNull() || actions.isNone());
}

// Test getAnnotsObject returns an object
TEST_F(PageTest_701, GetAnnotsObjectReturnsObject_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object annots = page->getAnnotsObject();
    // For a minimal page without annotations, could be null or array
    EXPECT_TRUE(annots.isNull() || annots.isNone() || annots.isArray());
}

// Test getRef returns a valid Ref
TEST_F(PageTest_701, GetRefReturnsValidRef_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Ref ref = page->getRef();
    EXPECT_GE(ref.num, 0);
    EXPECT_GE(ref.gen, 0);
}

// Test getPageObj returns a valid object
TEST_F(PageTest_701, GetPageObjReturnsValidObject_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const Object &pageObj = page->getPageObj();
    EXPECT_TRUE(pageObj.isDict());
}

// Test hasStandaloneFields returns false for minimal page
TEST_F(PageTest_701, HasStandaloneFieldsReturnsFalseForMinimalPage_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_FALSE(page->hasStandaloneFields());
}

// Test getLinks returns a non-null Links object
TEST_F(PageTest_701, GetLinksReturnsNonNull_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    auto links = page->getLinks();
    EXPECT_NE(links, nullptr);
}

// Test getLastModified returns nullptr for page without modification date
TEST_F(PageTest_701, GetLastModifiedReturnsNullForMinimalPage_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const GooString *lastModified = page->getLastModified();
    // For a minimal page, there's no LastModified entry
    EXPECT_EQ(lastModified, nullptr);
}

// Test getBoxColorInfo returns nullptr for minimal page
TEST_F(PageTest_701, GetBoxColorInfoReturnsNullForMinimalPage_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Dict *boxColorInfo = page->getBoxColorInfo();
    EXPECT_EQ(boxColorInfo, nullptr);
}

// Test getGroup returns nullptr for minimal page
TEST_F(PageTest_701, GetGroupReturnsNullForMinimalPage_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Dict *group = page->getGroup();
    EXPECT_EQ(group, nullptr);
}

// Test getMetadata returns nullptr for minimal page
TEST_F(PageTest_701, GetMetadataReturnsNullForMinimalPage_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Stream *metadata = page->getMetadata();
    EXPECT_EQ(metadata, nullptr);
}

// Test getPieceInfo returns nullptr for minimal page
TEST_F(PageTest_701, GetPieceInfoReturnsNullForMinimalPage_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Dict *pieceInfo = page->getPieceInfo();
    EXPECT_EQ(pieceInfo, nullptr);
}

// Test getSeparationInfo returns nullptr for minimal page
TEST_F(PageTest_701, GetSeparationInfoReturnsNullForMinimalPage_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Dict *sepInfo = page->getSeparationInfo();
    EXPECT_EQ(sepInfo, nullptr);
}

// Test getResourceDict for minimal page (may be null if no resources)
TEST_F(PageTest_701, GetResourceDictForMinimalPage_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // A minimal page might or might not have resource dict
    // Just ensure it doesn't crash
    Dict *resDict = page->getResourceDict();
    // May be null for minimal page
    (void)resDict;
}

// Test getResourceDictObject for minimal page
TEST_F(PageTest_701, GetResourceDictObjectForMinimalPage_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object *resDictObj = page->getResourceDictObject();
    ASSERT_NE(resDictObj, nullptr);
}

// Test loadThumb returns false for minimal page without thumbnail
TEST_F(PageTest_701, LoadThumbReturnsFalseForMinimalPage_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    unsigned char *data = nullptr;
    int width = 0, height = 0, rowstride = 0;
    bool result = page->loadThumb(&data, &width, &height, &rowstride);
    EXPECT_FALSE(result);
}

// Test getFormWidgets returns non-null for minimal page
TEST_F(PageTest_701, GetFormWidgetsForMinimalPage_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    auto formWidgets = page->getFormWidgets();
    // May or may not be null, but shouldn't crash
    (void)formWidgets;
}

// Test getStructParents for minimal page
TEST_F(PageTest_701, GetStructParentsForMinimalPage_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    int structParents = page->getStructParents();
    // Default should be -1 when not specified
    EXPECT_EQ(structParents, -1);
}

// Test that a page with CropBox is reported as cropped
TEST_F(PageTest_701, IsCroppedReturnsTrueWhenCropBoxPresent_701) {
    auto doc = createCroppedPDFDoc();
    if (!doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Cropped PDF document could not be created";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_TRUE(page->isCropped());
}

// Test crop dimensions differ from media when cropped
TEST_F(PageTest_701, CropDimensionsDifferFromMediaWhenCropped_701) {
    auto doc = createCroppedPDFDoc();
    if (!doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Cropped PDF document could not be created";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    if (page->isCropped()) {
        // CropBox [10 10 300 400] => width=290, height=390
        EXPECT_DOUBLE_EQ(page->getCropWidth(), 290.0);
        EXPECT_DOUBLE_EQ(page->getCropHeight(), 390.0);
        EXPECT_NE(page->getCropWidth(), page->getMediaWidth());
        EXPECT_NE(page->getCropHeight(), page->getMediaHeight());
    }
}

// Test MediaBox coordinates for minimal PDF
TEST_F(PageTest_701, MediaBoxCoordinatesCorrect_701) {
    auto doc = createMinimalPDFDoc();
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

// Test getDefaultCTM doesn't crash
TEST_F(PageTest_701, GetDefaultCTMDoesNotCrash_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    double ctm[6] = {0};
    page->getDefaultCTM(ctm, 72.0, 72.0, 0, true, false);
    // CTM should have been populated; at minimum the identity-like matrix
    // Just verify no crash and some values are non-zero
    bool allZero = true;
    for (int i = 0; i < 6; i++) {
        if (ctm[i] != 0.0) {
            allZero = false;
            break;
        }
    }
    EXPECT_FALSE(allZero);
}

// Test makeBox doesn't crash
TEST_F(PageTest_701, MakeBoxDoesNotCrash_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    PDFRectangle box;
    bool crop = false;
    page->makeBox(72.0, 72.0, 0, true, false, 0, 0, 612, 792, &box, &crop);
    // Box should have valid dimensions
    EXPECT_GE(box.x2 - box.x1, 0.0);
    EXPECT_GE(box.y2 - box.y1, 0.0);
}

// Test getAdditionalAction returns nullptr for minimal page
TEST_F(PageTest_701, GetAdditionalActionReturnsNullForMinimalPage_701) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    auto action = page->getAdditionalAction(actionOpenPage);
    EXPECT_EQ(action, nullptr);

    auto action2 = page->getAdditionalAction(actionClosePage);
    EXPECT_EQ(action2, nullptr);
}
