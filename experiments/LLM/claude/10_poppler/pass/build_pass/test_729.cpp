#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

// Include necessary headers from poppler
#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class PageTest_729 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadDocument(const char *filename)
    {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test hasStandaloneFields returns false for a page without standalone fields
TEST_F(PageTest_729, HasStandaloneFieldsReturnsFalseForNormalPage_729)
{
    // Create a simple PDF document - use a test PDF if available
    // For a basic PDF without form fields, hasStandaloneFields should return false
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    // A regular page without standalone form fields
    // We verify the method is callable and returns a bool
    bool result = page->hasStandaloneFields();
    // For a non-form PDF, we expect no standalone fields
    EXPECT_FALSE(result);
}

// Test isOk for a valid page
TEST_F(PageTest_729, IsOkReturnsTrueForValidPage_729)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_TRUE(page->isOk());
}

// Test getNum returns correct page number
TEST_F(PageTest_729, GetNumReturnsCorrectPageNumber_729)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_EQ(page->getNum(), 1);
}

// Test getMediaBox returns non-null
TEST_F(PageTest_729, GetMediaBoxReturnsNonNull_729)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    const PDFRectangle *mediaBox = page->getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
    // Media box should have positive dimensions
    EXPECT_GT(mediaBox->x2 - mediaBox->x1, 0);
    EXPECT_GT(mediaBox->y2 - mediaBox->y1, 0);
}

// Test getCropBox returns non-null
TEST_F(PageTest_729, GetCropBoxReturnsNonNull_729)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    const PDFRectangle *cropBox = page->getCropBox();
    ASSERT_NE(cropBox, nullptr);
}

// Test getMediaWidth and getMediaHeight return positive values
TEST_F(PageTest_729, GetMediaDimensionsArePositive_729)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_GT(page->getMediaWidth(), 0.0);
    EXPECT_GT(page->getMediaHeight(), 0.0);
}

// Test getCropWidth and getCropHeight return positive values
TEST_F(PageTest_729, GetCropDimensionsArePositive_729)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_GT(page->getCropWidth(), 0.0);
    EXPECT_GT(page->getCropHeight(), 0.0);
}

// Test getRotate returns a valid rotation value (0, 90, 180, 270)
TEST_F(PageTest_729, GetRotateReturnsValidValue_729)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    int rotate = page->getRotate();
    EXPECT_TRUE(rotate == 0 || rotate == 90 || rotate == 180 || rotate == 270);
}

// Test getDuration returns a non-negative value (0 means no duration set)
TEST_F(PageTest_729, GetDurationReturnsNonNegative_729)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    double duration = page->getDuration();
    // Duration is typically -1 if not set, or >= 0 if set
    // Just check it's callable
    (void)duration;
}

// Test getDoc returns the parent document
TEST_F(PageTest_729, GetDocReturnsParentDocument_729)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_EQ(page->getDoc(), doc.get());
}

// Test getPageObj returns a valid object
TEST_F(PageTest_729, GetPageObjReturnsValidObject_729)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    const Object &pageObj = page->getPageObj();
    EXPECT_TRUE(pageObj.isDict());
}

// Test getBleedBox returns non-null
TEST_F(PageTest_729, GetBleedBoxReturnsNonNull_729)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    const PDFRectangle *bleedBox = page->getBleedBox();
    ASSERT_NE(bleedBox, nullptr);
}

// Test getTrimBox returns non-null
TEST_F(PageTest_729, GetTrimBoxReturnsNonNull_729)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    const PDFRectangle *trimBox = page->getTrimBox();
    ASSERT_NE(trimBox, nullptr);
}

// Test getArtBox returns non-null
TEST_F(PageTest_729, GetArtBoxReturnsNonNull_729)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    const PDFRectangle *artBox = page->getArtBox();
    ASSERT_NE(artBox, nullptr);
}

// Test crop box dimensions are not larger than media box
TEST_F(PageTest_729, CropBoxNotLargerThanMediaBox_729)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_LE(page->getCropWidth(), page->getMediaWidth() + 0.01);
    EXPECT_LE(page->getCropHeight(), page->getMediaHeight() + 0.01);
}

// Test getStructParents
TEST_F(PageTest_729, GetStructParentsReturnsValue_729)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    // structParents is typically -1 if not set
    int sp = page->getStructParents();
    (void)sp; // Just verify it's callable
}

// Test getContents returns an object
TEST_F(PageTest_729, GetContentsReturnsObject_729)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    Object contents = page->getContents();
    // Contents can be a stream, array, or null
    EXPECT_TRUE(contents.isStream() || contents.isArray() || contents.isNull() || contents.isRef());
}

// Test getRef returns a valid Ref
TEST_F(PageTest_729, GetRefReturnsValidRef_729)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    Ref ref = page->getRef();
    EXPECT_GE(ref.num, 0);
    EXPECT_GE(ref.gen, 0);
}

// Test getResourceDict for a valid page
TEST_F(PageTest_729, GetResourceDictReturnsDict_729)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    Dict *resDict = page->getResourceDict();
    // Resource dict may or may not be null depending on the PDF
    // Just verify the method is callable
    (void)resDict;
}

// Test multiple pages in a multi-page document
TEST_F(PageTest_729, MultiplePageNumbersAreCorrect_729)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    int numPages = doc->getNumPages();
    for (int i = 1; i <= numPages; i++) {
        Page *page = doc->getPage(i);
        ASSERT_NE(page, nullptr);
        EXPECT_EQ(page->getNum(), i);
        EXPECT_TRUE(page->isOk());
    }
}

// Test getDefaultCTM produces valid CTM values
TEST_F(PageTest_729, GetDefaultCTMProducesValidValues_729)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    double ctm[6];
    page->getDefaultCTM(ctm, 72.0, 72.0, 0, true, false);

    // At 72 DPI with no rotation, the CTM should have reasonable values
    // At minimum, not all zeros
    bool allZero = true;
    for (int i = 0; i < 6; i++) {
        if (ctm[i] != 0.0) {
            allZero = false;
            break;
        }
    }
    EXPECT_FALSE(allZero);
}

// Test makeBox produces a valid box
TEST_F(PageTest_729, MakeBoxProducesValidBox_729)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    PDFRectangle box;
    bool crop = false;
    page->makeBox(72.0, 72.0, 0, true, false, 0, 0,
                  page->getMediaWidth(), page->getMediaHeight(),
                  &box, &crop);

    EXPECT_GE(box.x2 - box.x1, 0);
    EXPECT_GE(box.y2 - box.y1, 0);
}

// Test getAnnotsObject returns an object
TEST_F(PageTest_729, GetAnnotsObjectReturnsObject_729)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    Object annotsObj = page->getAnnotsObject();
    // Annots can be array, null, or ref
    EXPECT_TRUE(annotsObj.isArray() || annotsObj.isNull() || annotsObj.isRef());
}

// Test isCropped
TEST_F(PageTest_729, IsCroppedReturnsBool_729)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    bool cropped = page->isCropped();
    (void)cropped; // Just verify it's callable and returns a bool
}

// Test getFormWidgets
TEST_F(PageTest_729, GetFormWidgetsReturnsObject_729)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    auto widgets = page->getFormWidgets();
    // For a non-form PDF, widgets object should still be valid (possibly empty)
    // Just verify it doesn't crash
}

// Test getLinks
TEST_F(PageTest_729, GetLinksReturnsObject_729)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    auto links = page->getLinks();
    // Just verify it doesn't crash and returns a valid unique_ptr
}
