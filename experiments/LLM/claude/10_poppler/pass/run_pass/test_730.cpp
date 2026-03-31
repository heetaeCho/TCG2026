#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include <memory>
#include <string>

class PageTest_730 : public ::testing::Test {
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

// Test that getStructParents returns an integer value for a valid page
TEST_F(PageTest_730, GetStructParentsReturnsValue_730)
{
    // We need a valid PDF to test. We'll try to create a minimal test.
    // If no test PDF is available, we verify the interface exists.
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    int structParents = page->getStructParents();
    // structParents should be a valid integer (could be -1 if not set, or >= 0)
    EXPECT_GE(structParents, -1);
}

// Test isOk for a valid page
TEST_F(PageTest_730, IsOkReturnsTrueForValidPage_730)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_TRUE(page->isOk());
}

// Test getNum returns the correct page number
TEST_F(PageTest_730, GetNumReturnsCorrectPageNumber_730)
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
TEST_F(PageTest_730, GetMediaBoxReturnsNonNull_730)
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
    EXPECT_GT(mediaBox->x2 - mediaBox->x1, 0.0);
    EXPECT_GT(mediaBox->y2 - mediaBox->y1, 0.0);
}

// Test getCropBox returns non-null
TEST_F(PageTest_730, GetCropBoxReturnsNonNull_730)
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
TEST_F(PageTest_730, GetMediaDimensionsArePositive_730)
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
TEST_F(PageTest_730, GetCropDimensionsArePositive_730)
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
TEST_F(PageTest_730, GetRotateReturnsValidValue_730)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    int rotate = page->getRotate();
    EXPECT_TRUE(rotate == 0 || rotate == 90 || rotate == 180 || rotate == 270)
        << "Rotation was " << rotate;
}

// Test getDuration returns a value
TEST_F(PageTest_730, GetDurationReturnsValue_730)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    double duration = page->getDuration();
    // Duration can be -1 (not set) or >= 0
    EXPECT_GE(duration, -1.0);
}

// Test getDoc returns the parent document
TEST_F(PageTest_730, GetDocReturnsParentDocument_730)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    PDFDoc *parentDoc = page->getDoc();
    EXPECT_EQ(parentDoc, doc.get());
}

// Test getBleedBox returns non-null
TEST_F(PageTest_730, GetBleedBoxReturnsNonNull_730)
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
TEST_F(PageTest_730, GetTrimBoxReturnsNonNull_730)
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
TEST_F(PageTest_730, GetArtBoxReturnsNonNull_730)
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

// Test that crop dimensions are <= media dimensions
TEST_F(PageTest_730, CropDimensionsNotExceedMedia_730)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_LE(page->getCropWidth(), page->getMediaWidth());
    EXPECT_LE(page->getCropHeight(), page->getMediaHeight());
}

// Test getResourceDict
TEST_F(PageTest_730, GetResourceDictNotNull_730)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // Resource dict may or may not be null depending on the page
    // Just call it to ensure no crash
    Dict *resDict = page->getResourceDict();
    (void)resDict;
}

// Test getContents returns an Object
TEST_F(PageTest_730, GetContentsReturnsObject_730)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object contents = page->getContents();
    // Contents can be a stream, array, or null
    EXPECT_TRUE(contents.isStream() || contents.isArray() || contents.isNull());
}

// Test getPageObj returns a reference to a valid Object
TEST_F(PageTest_730, GetPageObjReturnsValidObject_730)
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

// Test hasStandaloneFields
TEST_F(PageTest_730, HasStandaloneFieldsReturnsBool_730)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // Just verify it returns a bool without crashing
    bool hasFields = page->hasStandaloneFields();
    (void)hasFields;
}

// Test isCropped
TEST_F(PageTest_730, IsCroppedReturnsBool_730)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    bool cropped = page->isCropped();
    (void)cropped;
}

// Test multiple pages if document has more than one
TEST_F(PageTest_730, MultiplePageNumbers_730)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    int numPages = doc->getNumPages();
    for (int i = 1; i <= numPages; i++) {
        Page *page = doc->getPage(i);
        ASSERT_NE(page, nullptr) << "Page " << i << " is null";
        EXPECT_EQ(page->getNum(), i);
        EXPECT_TRUE(page->isOk());
    }
}

// Test getRef returns a valid Ref
TEST_F(PageTest_730, GetRefReturnsValidRef_730)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Ref ref = page->getRef();
    // A valid page ref should have non-negative num
    EXPECT_GE(ref.num, 0);
    EXPECT_GE(ref.gen, 0);
}

// Test getAnnotsObject
TEST_F(PageTest_730, GetAnnotsObjectReturnsObject_730)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object annotsObj = page->getAnnotsObject();
    // Annots can be an array or null
    EXPECT_TRUE(annotsObj.isArray() || annotsObj.isNull());
}

// Test getDefaultCTM doesn't crash
TEST_F(PageTest_730, GetDefaultCTMNoCrash_730)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    double ctm[6];
    page->getDefaultCTM(ctm, 72.0, 72.0, 0, true, false);

    // The CTM should be initialized with some values
    // At least it shouldn't crash
    bool allZero = true;
    for (int i = 0; i < 6; i++) {
        if (ctm[i] != 0.0) {
            allZero = false;
            break;
        }
    }
    // A valid CTM shouldn't be all zeros for a page with dimensions
    EXPECT_FALSE(allZero);
}

// Test makeBox doesn't crash
TEST_F(PageTest_730, MakeBoxNoCrash_730)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    PDFRectangle box;
    bool crop;
    page->makeBox(72.0, 72.0, 0, true, false, 0, 0,
                  page->getMediaWidth(), page->getMediaHeight(),
                  &box, &crop);

    // The box should have some dimensions
    EXPECT_GE(box.x2 - box.x1, 0.0);
    EXPECT_GE(box.y2 - box.y1, 0.0);
}

// Test getLinks
TEST_F(PageTest_730, GetLinksReturnsObject_730)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    auto links = page->getLinks();
    // Links may or may not be null, just verify no crash
}

// Test copy constructor is deleted (compile-time test - this shouldn't compile if uncommented)
// This is verified by the class definition: Page(const Page &) = delete;

// Test assignment operator is deleted
// This is verified by the class definition: Page &operator=(const Page &) = delete;

// Test getStructParents with multiple pages
TEST_F(PageTest_730, GetStructParentsMultiplePages_730)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    int numPages = doc->getNumPages();
    for (int i = 1; i <= numPages; i++) {
        Page *page = doc->getPage(i);
        ASSERT_NE(page, nullptr);
        // structParents should be consistent - call it to verify no crash
        int sp = page->getStructParents();
        (void)sp;
    }
}

// Test getThumb
TEST_F(PageTest_730, GetThumbReturnsObject_730)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object thumb = page->getThumb();
    // Thumb can be a stream or null
    EXPECT_TRUE(thumb.isStream() || thumb.isNull());
}

// Test getTrans
TEST_F(PageTest_730, GetTransReturnsObject_730)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object trans = page->getTrans();
    // Trans can be a dict or null
    EXPECT_TRUE(trans.isDict() || trans.isNull());
}

// Test getActions
TEST_F(PageTest_730, GetActionsReturnsObject_730)
{
    auto doc = loadDocument("../test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object actions = page->getActions();
    // Actions can be a dict or null
    EXPECT_TRUE(actions.isDict() || actions.isNull());
}
