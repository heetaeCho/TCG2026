#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"
#include "Dict.h"
#include "XRef.h"

class PageTest_721 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override
    {
        // We'll load a real PDF for testing purposes
    }

    void TearDown() override
    {
    }

    std::unique_ptr<PDFDoc> loadTestDoc(const char *filename)
    {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Helper to create a minimal in-memory PDF for testing
class InMemoryPDFPageTest_721 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> createMinimalPDF()
    {
        // Create a minimal PDF in memory
        static const char pdfData[] =
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
            "/CropBox [10 10 600 780] "
            "/BleedBox [5 5 607 787] "
            "/TrimBox [15 15 597 777] "
            "/ArtBox [20 20 592 772] "
            "/Rotate 90 "
            "/Contents 4 0 R "
            "/StructParents 5 "
            ">>\n"
            "endobj\n"
            "4 0 obj\n"
            "<< /Length 0 >>\n"
            "stream\n"
            "endstream\n"
            "endobj\n"
            "xref\n"
            "0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000384 00000 n \n"
            "trailer\n"
            "<< /Size 5 /Root 1 0 R >>\n"
            "startxref\n"
            "434\n"
            "%%EOF\n";

        auto stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
        auto doc = std::make_unique<PDFDoc>(stream);
        return doc;
    }

    std::unique_ptr<PDFDoc> createSimplePDF()
    {
        static const char pdfData[] =
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 300] >>\n"
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
            "198\n"
            "%%EOF\n";

        auto stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
        auto doc = std::make_unique<PDFDoc>(stream);
        return doc;
    }
};

// Test getRef returns a valid Ref
TEST_F(InMemoryPDFPageTest_721, GetRef_ReturnsValidRef_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Ref ref = page->getRef();
    // The page object should have a valid ref (num >= 0)
    EXPECT_GE(ref.num, 0);
    EXPECT_GE(ref.gen, 0);
}

// Test getNum returns 1 for first page
TEST_F(InMemoryPDFPageTest_721, GetNum_ReturnsPageNumber_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_EQ(page->getNum(), 1);
}

// Test isOk returns true for valid page
TEST_F(InMemoryPDFPageTest_721, IsOk_ReturnsTrueForValidPage_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_TRUE(page->isOk());
}

// Test getMediaBox returns non-null
TEST_F(InMemoryPDFPageTest_721, GetMediaBox_ReturnsNonNull_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *mediaBox = page->getMediaBox();
    ASSERT_NE(mediaBox, nullptr);

    // The simple PDF has MediaBox [0 0 200 300]
    EXPECT_DOUBLE_EQ(mediaBox->x1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->y1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->x2, 200.0);
    EXPECT_DOUBLE_EQ(mediaBox->y2, 300.0);
}

// Test getMediaWidth and getMediaHeight
TEST_F(InMemoryPDFPageTest_721, GetMediaWidthHeight_ReturnsCorrectDimensions_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_DOUBLE_EQ(page->getMediaWidth(), 200.0);
    EXPECT_DOUBLE_EQ(page->getMediaHeight(), 300.0);
}

// Test getCropBox when no explicit CropBox is set (should default to MediaBox)
TEST_F(InMemoryPDFPageTest_721, GetCropBox_DefaultsToMediaBox_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *cropBox = page->getCropBox();
    ASSERT_NE(cropBox, nullptr);

    // When no CropBox is specified, it should default to MediaBox
    EXPECT_DOUBLE_EQ(cropBox->x1, 0.0);
    EXPECT_DOUBLE_EQ(cropBox->y1, 0.0);
    EXPECT_DOUBLE_EQ(cropBox->x2, 200.0);
    EXPECT_DOUBLE_EQ(cropBox->y2, 300.0);
}

// Test getCropWidth and getCropHeight when no explicit CropBox
TEST_F(InMemoryPDFPageTest_721, GetCropWidthHeight_DefaultsToMediaDimensions_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_DOUBLE_EQ(page->getCropWidth(), 200.0);
    EXPECT_DOUBLE_EQ(page->getCropHeight(), 300.0);
}

// Test isCropped returns false when no CropBox set
TEST_F(InMemoryPDFPageTest_721, IsCropped_ReturnsFalseWhenNoCropBox_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_FALSE(page->isCropped());
}

// Test getRotate when no Rotate is set (should default to 0)
TEST_F(InMemoryPDFPageTest_721, GetRotate_DefaultsToZero_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_EQ(page->getRotate(), 0);
}

// Test getDoc returns the parent document
TEST_F(InMemoryPDFPageTest_721, GetDoc_ReturnsParentDocument_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    PDFDoc *returnedDoc = page->getDoc();
    EXPECT_EQ(returnedDoc, doc.get());
}

// Test getPageObj returns a valid object
TEST_F(InMemoryPDFPageTest_721, GetPageObj_ReturnsValidObject_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const Object &pageObj = page->getPageObj();
    EXPECT_TRUE(pageObj.isDict());
}

// Test getDuration returns default value
TEST_F(InMemoryPDFPageTest_721, GetDuration_ReturnsDefaultValue_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // When no duration is set, it should be -1 or some default
    double duration = page->getDuration();
    EXPECT_LE(duration, 0.0);
}

// Test getBleedBox returns non-null
TEST_F(InMemoryPDFPageTest_721, GetBleedBox_ReturnsNonNull_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *bleedBox = page->getBleedBox();
    ASSERT_NE(bleedBox, nullptr);
}

// Test getTrimBox returns non-null
TEST_F(InMemoryPDFPageTest_721, GetTrimBox_ReturnsNonNull_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *trimBox = page->getTrimBox();
    ASSERT_NE(trimBox, nullptr);
}

// Test getArtBox returns non-null
TEST_F(InMemoryPDFPageTest_721, GetArtBox_ReturnsNonNull_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *artBox = page->getArtBox();
    ASSERT_NE(artBox, nullptr);
}

// Test hasStandaloneFields on a simple page
TEST_F(InMemoryPDFPageTest_721, HasStandaloneFields_ReturnsFalseForSimplePage_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_FALSE(page->hasStandaloneFields());
}

// Test getContents returns an object
TEST_F(InMemoryPDFPageTest_721, GetContents_ReturnsObject_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object contents = page->getContents();
    // For a simple page without contents, it should be null
    EXPECT_TRUE(contents.isNull() || contents.isStream() || contents.isArray());
}

// Test getAnnotsObject
TEST_F(InMemoryPDFPageTest_721, GetAnnotsObject_ReturnsObject_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object annotsObj = page->getAnnotsObject();
    // For a simple page without annotations, it should be null or an empty array
    EXPECT_TRUE(annotsObj.isNull() || annotsObj.isArray());
}

// Test getThumb on a page without thumbnails
TEST_F(InMemoryPDFPageTest_721, GetThumb_ReturnsNullForNoThumbnail_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object thumb = page->getThumb();
    EXPECT_TRUE(thumb.isNull());
}

// Test getTrans on a page without transitions
TEST_F(InMemoryPDFPageTest_721, GetTrans_ReturnsNullForNoTransition_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object trans = page->getTrans();
    EXPECT_TRUE(trans.isNull());
}

// Test getActions on a page without actions
TEST_F(InMemoryPDFPageTest_721, GetActions_ReturnsNullForNoActions_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object actions = page->getActions();
    EXPECT_TRUE(actions.isNull());
}

// Test getLastModified on a page without last modified
TEST_F(InMemoryPDFPageTest_721, GetLastModified_ReturnsNullForNoLastModified_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const GooString *lastModified = page->getLastModified();
    EXPECT_EQ(lastModified, nullptr);
}

// Test getStructParents default
TEST_F(InMemoryPDFPageTest_721, GetStructParents_ReturnsDefaultValue_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // When no StructParents is set, typically returns -1
    int structParents = page->getStructParents();
    EXPECT_EQ(structParents, -1);
}

// Test getResourceDict
TEST_F(InMemoryPDFPageTest_721, GetResourceDict_CanReturnNull_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // For a minimal PDF, resource dict might be null or valid
    Dict *resourceDict = page->getResourceDict();
    // Just verify it doesn't crash; result may be null for minimal PDF
    (void)resourceDict;
}

// Test getResourceDictObject
TEST_F(InMemoryPDFPageTest_721, GetResourceDictObject_ReturnsObjectPointer_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object *resourceDictObj = page->getResourceDictObject();
    // Should return a valid pointer (even if the object is null type)
    ASSERT_NE(resourceDictObj, nullptr);
}

// Test loadThumb returns false for page without thumbnail
TEST_F(InMemoryPDFPageTest_721, LoadThumb_ReturnsFalseForNoThumbnail_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    unsigned char *data = nullptr;
    int width = 0, height = 0, rowstride = 0;
    bool result = page->loadThumb(&data, &width, &height, &rowstride);
    EXPECT_FALSE(result);
}

// Test getGroup returns null for page without group
TEST_F(InMemoryPDFPageTest_721, GetGroup_ReturnsNullForSimplePage_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Dict *group = page->getGroup();
    EXPECT_EQ(group, nullptr);
}

// Test getMetadata returns null for page without metadata
TEST_F(InMemoryPDFPageTest_721, GetMetadata_ReturnsNullForSimplePage_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Stream *metadata = page->getMetadata();
    EXPECT_EQ(metadata, nullptr);
}

// Test getPieceInfo returns null for page without piece info
TEST_F(InMemoryPDFPageTest_721, GetPieceInfo_ReturnsNullForSimplePage_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Dict *pieceInfo = page->getPieceInfo();
    EXPECT_EQ(pieceInfo, nullptr);
}

// Test getSeparationInfo returns null for page without separation info
TEST_F(InMemoryPDFPageTest_721, GetSeparationInfo_ReturnsNullForSimplePage_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Dict *sepInfo = page->getSeparationInfo();
    EXPECT_EQ(sepInfo, nullptr);
}

// Test getBoxColorInfo returns null for page without box color info
TEST_F(InMemoryPDFPageTest_721, GetBoxColorInfo_ReturnsNullForSimplePage_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Dict *boxColorInfo = page->getBoxColorInfo();
    EXPECT_EQ(boxColorInfo, nullptr);
}

// Test getFormWidgets returns a valid pointer for a simple page
TEST_F(InMemoryPDFPageTest_721, GetFormWidgets_ReturnsValidPointer_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    auto formWidgets = page->getFormWidgets();
    // Should return a valid (possibly empty) FormPageWidgets
    EXPECT_NE(formWidgets, nullptr);
}

// Test getLinks returns a valid pointer for a simple page
TEST_F(InMemoryPDFPageTest_721, GetLinks_ReturnsValidPointer_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    auto links = page->getLinks();
    EXPECT_NE(links, nullptr);
}

// Test getDefaultCTM does not crash
TEST_F(InMemoryPDFPageTest_721, GetDefaultCTM_DoesNotCrash_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    double ctm[6] = {0};
    page->getDefaultCTM(ctm, 72.0, 72.0, 0, true, false);

    // The CTM should be populated with non-trivial values for a valid page
    // At least some elements should be non-zero
    bool hasNonZero = false;
    for (int i = 0; i < 6; i++) {
        if (ctm[i] != 0.0) {
            hasNonZero = true;
            break;
        }
    }
    EXPECT_TRUE(hasNonZero);
}

// Test makeBox does not crash
TEST_F(InMemoryPDFPageTest_721, MakeBox_DoesNotCrash_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    PDFRectangle box;
    bool crop = false;
    page->makeBox(72.0, 72.0, 0, true, false, 0, 0, 200, 300, &box, &crop);

    // Box should have valid dimensions
    EXPECT_GE(box.x2 - box.x1, 0.0);
    EXPECT_GE(box.y2 - box.y1, 0.0);
}

// Test getAdditionalAction returns null for page without additional actions
TEST_F(InMemoryPDFPageTest_721, GetAdditionalAction_ReturnsNullForSimplePage_721)
{
    auto doc = createSimplePDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    auto action = page->getAdditionalAction(Page::actionOpenPage);
    EXPECT_EQ(action, nullptr);

    action = page->getAdditionalAction(Page::actionClosePage);
    EXPECT_EQ(action, nullptr);
}

// Test copy constructor is deleted (compile-time check - just verify the class is non-copyable conceptually)
// This is a static assertion test
TEST_F(InMemoryPDFPageTest_721, PageIsNonCopyable_721)
{
    EXPECT_FALSE(std::is_copy_constructible<Page>::value);
    EXPECT_FALSE(std::is_copy_assignable<Page>::value);
}
