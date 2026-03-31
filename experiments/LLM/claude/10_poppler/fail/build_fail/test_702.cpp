#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary headers from poppler
#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"
#include "Dict.h"
#include "Stream.h"
#include "GooString.h"

class PageTest_702 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // Load a simple PDF for testing
        doc = nullptr;
    }

    void TearDown() override {
        delete doc;
        doc = nullptr;
    }

    PDFDoc *loadTestDoc(const char *filename) {
        auto *gooFilename = new GooString(filename);
        doc = new PDFDoc(gooFilename);
        return doc;
    }

    PDFDoc *doc;
};

// Helper to find a valid test PDF. We'll attempt to use a minimal PDF.
// In a real test environment, you'd have test fixtures available.

class PageWithDocTest_702 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // Create a minimal PDF in memory
        const char *minimalPDF =
            "%PDF-1.0\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
            "xref\n"
            "0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n"
            "206\n"
            "%%EOF\n";

        int len = strlen(minimalPDF);
        char *buf = (char *)gmalloc(len);
        memcpy(buf, minimalPDF, len);
        auto *stream = new MemStream(buf, 0, len, Object(objNull));
        doc = new PDFDoc(stream);
    }

    void TearDown() override {
        delete doc;
        doc = nullptr;
    }

    PDFDoc *doc;
};

// Test: getNum returns correct page number for first page
TEST_F(PageWithDocTest_702, GetNum_FirstPage_702) {
    ASSERT_TRUE(doc->isOk());
    ASSERT_GE(doc->getNumPages(), 1);
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_EQ(page->getNum(), 1);
}

// Test: isOk returns true for a valid page
TEST_F(PageWithDocTest_702, IsOk_ValidPage_702) {
    ASSERT_TRUE(doc->isOk());
    ASSERT_GE(doc->getNumPages(), 1);
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_TRUE(page->isOk());
}

// Test: getMediaBox returns non-null for valid page
TEST_F(PageWithDocTest_702, GetMediaBox_NotNull_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    const PDFRectangle *mediaBox = page->getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
}

// Test: getMediaBox returns expected dimensions for our test PDF
TEST_F(PageWithDocTest_702, GetMediaBox_Dimensions_702) {
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

// Test: getMediaWidth returns correct width
TEST_F(PageWithDocTest_702, GetMediaWidth_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_DOUBLE_EQ(page->getMediaWidth(), 612.0);
}

// Test: getMediaHeight returns correct height
TEST_F(PageWithDocTest_702, GetMediaHeight_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_DOUBLE_EQ(page->getMediaHeight(), 792.0);
}

// Test: getCropBox returns non-null
TEST_F(PageWithDocTest_702, GetCropBox_NotNull_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    const PDFRectangle *cropBox = page->getCropBox();
    ASSERT_NE(cropBox, nullptr);
}

// Test: getCropWidth returns correct width (should match media if no explicit crop)
TEST_F(PageWithDocTest_702, GetCropWidth_MatchesMedia_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    // When no explicit crop box, crop should match media
    EXPECT_DOUBLE_EQ(page->getCropWidth(), page->getMediaWidth());
}

// Test: getCropHeight returns correct height
TEST_F(PageWithDocTest_702, GetCropHeight_MatchesMedia_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_DOUBLE_EQ(page->getCropHeight(), page->getMediaHeight());
}

// Test: isCropped returns false when no explicit crop box
TEST_F(PageWithDocTest_702, IsCropped_NoCropBox_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_FALSE(page->isCropped());
}

// Test: getRotate returns 0 when no rotation specified
TEST_F(PageWithDocTest_702, GetRotate_Default_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_EQ(page->getRotate(), 0);
}

// Test: getBleedBox returns non-null
TEST_F(PageWithDocTest_702, GetBleedBox_NotNull_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    const PDFRectangle *bleedBox = page->getBleedBox();
    ASSERT_NE(bleedBox, nullptr);
}

// Test: getTrimBox returns non-null
TEST_F(PageWithDocTest_702, GetTrimBox_NotNull_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    const PDFRectangle *trimBox = page->getTrimBox();
    ASSERT_NE(trimBox, nullptr);
}

// Test: getArtBox returns non-null
TEST_F(PageWithDocTest_702, GetArtBox_NotNull_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    const PDFRectangle *artBox = page->getArtBox();
    ASSERT_NE(artBox, nullptr);
}

// Test: getDoc returns the parent document
TEST_F(PageWithDocTest_702, GetDoc_ReturnsParent_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_EQ(page->getDoc(), doc);
}

// Test: getRef returns a valid Ref
TEST_F(PageWithDocTest_702, GetRef_Valid_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    Ref ref = page->getRef();
    EXPECT_GT(ref.num, 0);
}

// Test: getPageObj returns a valid object
TEST_F(PageWithDocTest_702, GetPageObj_IsDict_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    const Object &pageObj = page->getPageObj();
    EXPECT_TRUE(pageObj.isDict());
}

// Test: getContents for a page with no content stream
TEST_F(PageWithDocTest_702, GetContents_EmptyPage_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    Object contents = page->getContents();
    // A page with no content may return null object
    EXPECT_TRUE(contents.isNull() || contents.isStream() || contents.isArray());
}

// Test: getDuration returns default for page without duration
TEST_F(PageWithDocTest_702, GetDuration_Default_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    double duration = page->getDuration();
    // Default duration when not set is typically -1
    EXPECT_LE(duration, 0.0);
}

// Test: getLastModified returns null when not set
TEST_F(PageWithDocTest_702, GetLastModified_Null_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    const GooString *lastMod = page->getLastModified();
    // May be nullptr if not specified in the page dictionary
    // Just verify it doesn't crash
    (void)lastMod;
}

// Test: getResourceDict returns a valid dictionary or null
TEST_F(PageWithDocTest_702, GetResourceDict_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    Dict *resDict = page->getResourceDict();
    // Our minimal PDF has Resources<<>>, so this should be non-null
    // but the dict may be empty
    ASSERT_NE(resDict, nullptr);
}

// Test: getResourceDictObject returns valid object
TEST_F(PageWithDocTest_702, GetResourceDictObject_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    Object *resDictObj = page->getResourceDictObject();
    ASSERT_NE(resDictObj, nullptr);
}

// Test: getAnnotsObject
TEST_F(PageWithDocTest_702, GetAnnotsObject_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    Object annotsObj = page->getAnnotsObject();
    // Page without annotations should return null object
    EXPECT_TRUE(annotsObj.isNull() || annotsObj.isArray());
}

// Test: getThumb returns null for page without thumbnail
TEST_F(PageWithDocTest_702, GetThumb_NoThumbnail_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    Object thumb = page->getThumb();
    EXPECT_TRUE(thumb.isNull() || thumb.isStream());
}

// Test: getTrans returns null for page without transition
TEST_F(PageWithDocTest_702, GetTrans_NoTransition_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    Object trans = page->getTrans();
    EXPECT_TRUE(trans.isNull() || trans.isDict());
}

// Test: getActions returns null for page without actions
TEST_F(PageWithDocTest_702, GetActions_NoActions_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    Object actions = page->getActions();
    EXPECT_TRUE(actions.isNull() || actions.isDict());
}

// Test: hasStandaloneFields for basic page
TEST_F(PageWithDocTest_702, HasStandaloneFields_False_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_FALSE(page->hasStandaloneFields());
}

// Test: getStructParents
TEST_F(PageWithDocTest_702, GetStructParents_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    int sp = page->getStructParents();
    // When not set, structParents is typically -1
    (void)sp;
}

// Test: loadThumb returns false for page without thumbnail
TEST_F(PageWithDocTest_702, LoadThumb_NoThumbnail_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    unsigned char *data = nullptr;
    int width = 0, height = 0, rowstride = 0;
    bool result = page->loadThumb(&data, &width, &height, &rowstride);
    EXPECT_FALSE(result);
    EXPECT_EQ(data, nullptr);
}

// Test: getFormWidgets returns non-null (possibly empty)
TEST_F(PageWithDocTest_702, GetFormWidgets_Empty_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    auto widgets = page->getFormWidgets();
    // Should return a valid object even if there are no form widgets
    // It may or may not be null depending on implementation
}

// Test: getLinks returns non-null (possibly empty)
TEST_F(PageWithDocTest_702, GetLinks_Empty_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    auto links = page->getLinks();
    // Should return a valid Links object even if no links exist
}

// Test: getDefaultCTM doesn't crash with valid parameters
TEST_F(PageWithDocTest_702, GetDefaultCTM_NoRotation_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    double ctm[6] = {0};
    page->getDefaultCTM(ctm, 72.0, 72.0, 0, true, false);
    // CTM should be filled with some values; at least not all zeros for a valid page
    bool allZero = true;
    for (int i = 0; i < 6; i++) {
        if (ctm[i] != 0.0) {
            allZero = false;
            break;
        }
    }
    EXPECT_FALSE(allZero);
}

// Test: getDefaultCTM with rotation
TEST_F(PageWithDocTest_702, GetDefaultCTM_With90Rotation_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    double ctm[6] = {0};
    page->getDefaultCTM(ctm, 72.0, 72.0, 90, true, false);
    bool allZero = true;
    for (int i = 0; i < 6; i++) {
        if (ctm[i] != 0.0) {
            allZero = false;
            break;
        }
    }
    EXPECT_FALSE(allZero);
}

// Test: makeBox produces valid box
TEST_F(PageWithDocTest_702, MakeBox_ValidOutput_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    PDFRectangle box;
    bool crop = false;
    page->makeBox(72.0, 72.0, 0, true, false, 0, 0, 612, 792, &box, (Bool *)&crop);
    // Box should have valid dimensions
    EXPECT_GE(box.x2, box.x1);
    EXPECT_GE(box.y2, box.y1);
}

// Test: getAdditionalAction returns nullptr for page without additional actions
TEST_F(PageWithDocTest_702, GetAdditionalAction_None_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    auto action = page->getAdditionalAction(Page::actionOpenPage);
    EXPECT_EQ(action, nullptr);
}

// Test: getBoxColorInfo returns null for page without BoxColorInfo
TEST_F(PageWithDocTest_702, GetBoxColorInfo_Null_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    Dict *boxColorInfo = page->getBoxColorInfo();
    // May be nullptr if not defined
    (void)boxColorInfo;
}

// Test: getGroup returns null for page without group
TEST_F(PageWithDocTest_702, GetGroup_Null_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    Dict *group = page->getGroup();
    EXPECT_EQ(group, nullptr);
}

// Test: getMetadata returns null for page without metadata
TEST_F(PageWithDocTest_702, GetMetadata_Null_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    Stream *metadata = page->getMetadata();
    EXPECT_EQ(metadata, nullptr);
}

// Test: getPieceInfo returns null for page without piece info
TEST_F(PageWithDocTest_702, GetPieceInfo_Null_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    Dict *pieceInfo = page->getPieceInfo();
    EXPECT_EQ(pieceInfo, nullptr);
}

// Test: getSeparationInfo returns null for page without separation info
TEST_F(PageWithDocTest_702, GetSeparationInfo_Null_702) {
    ASSERT_TRUE(doc->isOk());
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    Dict *sepInfo = page->getSeparationInfo();
    EXPECT_EQ(sepInfo, nullptr);
}

// Test: Copy constructor is deleted
TEST_F(PageWithDocTest_702, CopyConstructorDeleted_702) {
    // This test verifies at compile time that Page is not copyable
    EXPECT_FALSE(std::is_copy_constructible<Page>::value);
}

// Test: Copy assignment is deleted
TEST_F(PageWithDocTest_702, CopyAssignmentDeleted_702) {
    EXPECT_FALSE(std::is_copy_assignable<Page>::value);
}
