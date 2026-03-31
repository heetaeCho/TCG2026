#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

// Poppler includes
#include "poppler/PDFDoc.h"
#include "poppler/Page.h"
#include "poppler/GlobalParams.h"
#include "goo/GooString.h"

class PageTest_704 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // We'll load a simple PDF for testing
    }

    void TearDown() override {
        doc.reset();
    }

    std::unique_ptr<PDFDoc> loadTestDoc(const char *pdfContent = nullptr) {
        // Create a minimal PDF in memory
        static const char *minimalPDF =
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /CropBox [10 10 600 780] >>\n"
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
            "221\n"
            "%%EOF\n";

        const char *content = pdfContent ? pdfContent : minimalPDF;
        auto *str = new GooString(content);
        return std::make_unique<PDFDoc>(str);
    }

    std::unique_ptr<PDFDoc> doc;
};

// Test that getCropBox returns a non-null pointer for a valid page
TEST_F(PageTest_704, GetCropBoxReturnsNonNull_704) {
    doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    ASSERT_GE(doc->getNumPages(), 1);

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *cropBox = page->getCropBox();
    ASSERT_NE(cropBox, nullptr);
}

// Test that getCropBox returns expected values when CropBox is defined
TEST_F(PageTest_704, GetCropBoxReturnsExpectedValues_704) {
    doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    ASSERT_GE(doc->getNumPages(), 1);

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *cropBox = page->getCropBox();
    ASSERT_NE(cropBox, nullptr);

    // The CropBox in our test PDF is [10 10 600 780]
    EXPECT_DOUBLE_EQ(cropBox->x1, 10.0);
    EXPECT_DOUBLE_EQ(cropBox->y1, 10.0);
    EXPECT_DOUBLE_EQ(cropBox->x2, 600.0);
    EXPECT_DOUBLE_EQ(cropBox->y2, 780.0);
}

// Test that getMediaBox returns a non-null pointer
TEST_F(PageTest_704, GetMediaBoxReturnsNonNull_704) {
    doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());
    ASSERT_GE(doc->getNumPages(), 1);

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *mediaBox = page->getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
}

// Test that getMediaBox returns expected values
TEST_F(PageTest_704, GetMediaBoxReturnsExpectedValues_704) {
    doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *mediaBox = page->getMediaBox();
    ASSERT_NE(mediaBox, nullptr);

    // MediaBox in our test PDF is [0 0 612 792]
    EXPECT_DOUBLE_EQ(mediaBox->x1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->y1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->x2, 612.0);
    EXPECT_DOUBLE_EQ(mediaBox->y2, 792.0);
}

// Test isCropped returns true when CropBox is specified
TEST_F(PageTest_704, IsCroppedReturnsTrueWhenCropBoxDefined_704) {
    doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_TRUE(page->isCropped());
}

// Test page without explicit CropBox
TEST_F(PageTest_704, GetCropBoxWithoutExplicitCropBox_704) {
    static const char *pdfNoCrop =
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
        "195\n"
        "%%EOF\n";

    doc = loadTestDoc(pdfNoCrop);
    ASSERT_TRUE(doc->isOk());
    ASSERT_GE(doc->getNumPages(), 1);

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // When no CropBox is defined, getCropBox should still return a valid pointer
    // (typically defaults to MediaBox)
    const PDFRectangle *cropBox = page->getCropBox();
    ASSERT_NE(cropBox, nullptr);

    // Without explicit crop box, it should default to media box values
    const PDFRectangle *mediaBox = page->getMediaBox();
    ASSERT_NE(mediaBox, nullptr);

    EXPECT_DOUBLE_EQ(cropBox->x1, mediaBox->x1);
    EXPECT_DOUBLE_EQ(cropBox->y1, mediaBox->y1);
    EXPECT_DOUBLE_EQ(cropBox->x2, mediaBox->x2);
    EXPECT_DOUBLE_EQ(cropBox->y2, mediaBox->y2);
}

// Test isCropped returns false when no CropBox is defined
TEST_F(PageTest_704, IsCroppedReturnsFalseWhenNoCropBox_704) {
    static const char *pdfNoCrop =
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
        "195\n"
        "%%EOF\n";

    doc = loadTestDoc(pdfNoCrop);
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_FALSE(page->isCropped());
}

// Test getMediaWidth and getMediaHeight
TEST_F(PageTest_704, GetMediaWidthAndHeight_704) {
    doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_DOUBLE_EQ(page->getMediaWidth(), 612.0);
    EXPECT_DOUBLE_EQ(page->getMediaHeight(), 792.0);
}

// Test getCropWidth and getCropHeight
TEST_F(PageTest_704, GetCropWidthAndHeight_704) {
    doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // CropBox is [10 10 600 780], so width = 590, height = 770
    EXPECT_DOUBLE_EQ(page->getCropWidth(), 590.0);
    EXPECT_DOUBLE_EQ(page->getCropHeight(), 770.0);
}

// Test getNum returns the correct page number
TEST_F(PageTest_704, GetNumReturnsCorrectPageNumber_704) {
    doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_EQ(page->getNum(), 1);
}

// Test isOk for a valid page
TEST_F(PageTest_704, IsOkReturnsTrueForValidPage_704) {
    doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_TRUE(page->isOk());
}

// Test getBleedBox returns non-null
TEST_F(PageTest_704, GetBleedBoxReturnsNonNull_704) {
    doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *bleedBox = page->getBleedBox();
    ASSERT_NE(bleedBox, nullptr);
}

// Test getTrimBox returns non-null
TEST_F(PageTest_704, GetTrimBoxReturnsNonNull_704) {
    doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *trimBox = page->getTrimBox();
    ASSERT_NE(trimBox, nullptr);
}

// Test getArtBox returns non-null
TEST_F(PageTest_704, GetArtBoxReturnsNonNull_704) {
    doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *artBox = page->getArtBox();
    ASSERT_NE(artBox, nullptr);
}

// Test getRotate for a page without explicit rotation
TEST_F(PageTest_704, GetRotateDefaultsToZero_704) {
    doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_EQ(page->getRotate(), 0);
}

// Test getDuration
TEST_F(PageTest_704, GetDurationDefaultValue_704) {
    doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // Default duration when not specified should be -1 or 0
    double duration = page->getDuration();
    EXPECT_LE(duration, 0.0);
}

// Test getRef returns a valid Ref
TEST_F(PageTest_704, GetRefReturnsValidRef_704) {
    doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Ref ref = page->getRef();
    EXPECT_GT(ref.num, 0);
}

// Test getDoc returns the parent document
TEST_F(PageTest_704, GetDocReturnsParentDoc_704) {
    doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_EQ(page->getDoc(), doc.get());
}

// Test CropBox is clipped to MediaBox boundaries
TEST_F(PageTest_704, CropBoxClippedToMediaBox_704) {
    doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *cropBox = page->getCropBox();
    const PDFRectangle *mediaBox = page->getMediaBox();
    ASSERT_NE(cropBox, nullptr);
    ASSERT_NE(mediaBox, nullptr);

    // CropBox should be within or equal to MediaBox
    EXPECT_GE(cropBox->x1, mediaBox->x1);
    EXPECT_GE(cropBox->y1, mediaBox->y1);
    EXPECT_LE(cropBox->x2, mediaBox->x2);
    EXPECT_LE(cropBox->y2, mediaBox->y2);
}

// Test getPageObj returns a valid object
TEST_F(PageTest_704, GetPageObjReturnsValidObject_704) {
    doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const Object &pageObj = page->getPageObj();
    EXPECT_TRUE(pageObj.isDict());
}

// Test getContents
TEST_F(PageTest_704, GetContentsForEmptyPage_704) {
    doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    Object contents = page->getContents();
    // For a page with no contents, it should be null
    EXPECT_TRUE(contents.isNull() || contents.isStream() || contents.isArray());
}

// Test that bleed/trim/art boxes default to crop box when not specified
TEST_F(PageTest_704, DefaultBoxesFallbackToCropBox_704) {
    doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *cropBox = page->getCropBox();
    const PDFRectangle *bleedBox = page->getBleedBox();
    const PDFRectangle *trimBox = page->getTrimBox();
    const PDFRectangle *artBox = page->getArtBox();

    ASSERT_NE(cropBox, nullptr);
    ASSERT_NE(bleedBox, nullptr);
    ASSERT_NE(trimBox, nullptr);
    ASSERT_NE(artBox, nullptr);

    // When not explicitly set, these boxes should default to the crop box
    EXPECT_DOUBLE_EQ(bleedBox->x1, cropBox->x1);
    EXPECT_DOUBLE_EQ(bleedBox->y1, cropBox->y1);
    EXPECT_DOUBLE_EQ(bleedBox->x2, cropBox->x2);
    EXPECT_DOUBLE_EQ(bleedBox->y2, cropBox->y2);

    EXPECT_DOUBLE_EQ(trimBox->x1, cropBox->x1);
    EXPECT_DOUBLE_EQ(trimBox->y1, cropBox->y1);
    EXPECT_DOUBLE_EQ(trimBox->x2, cropBox->x2);
    EXPECT_DOUBLE_EQ(trimBox->y2, cropBox->y2);

    EXPECT_DOUBLE_EQ(artBox->x1, cropBox->x1);
    EXPECT_DOUBLE_EQ(artBox->y1, cropBox->y1);
    EXPECT_DOUBLE_EQ(artBox->x2, cropBox->x2);
    EXPECT_DOUBLE_EQ(artBox->y2, cropBox->y2);
}

// Test getStructParents default value
TEST_F(PageTest_704, GetStructParentsDefault_704) {
    doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // When not specified, structParents should be -1
    int structParents = page->getStructParents();
    EXPECT_EQ(structParents, -1);
}

// Test hasStandaloneFields
TEST_F(PageTest_704, HasStandaloneFieldsDefault_704) {
    doc = loadTestDoc();
    ASSERT_TRUE(doc->isOk());

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_FALSE(page->hasStandaloneFields());
}
