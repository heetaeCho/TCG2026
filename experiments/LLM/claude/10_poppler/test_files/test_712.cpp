#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

class PageGetArtBoxTest_712 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
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

// Test that getArtBox returns a non-null pointer for a valid page
TEST_F(PageGetArtBoxTest_712, GetArtBoxReturnsNonNull_712)
{
    // We need a valid PDF to test. Use a minimal approach with PDFDoc from memory.
    // Create a minimal PDF in memory
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n197\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, strlen(pdfData), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        const PDFRectangle *artBox = page->getArtBox();
        ASSERT_NE(artBox, nullptr);
    }
}

// Test that getArtBox returns a rectangle with valid dimensions
TEST_F(PageGetArtBoxTest_712, GetArtBoxHasValidDimensions_712)
{
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n197\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, strlen(pdfData), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        const PDFRectangle *artBox = page->getArtBox();
        ASSERT_NE(artBox, nullptr);
        // When no ArtBox is explicitly set, it defaults to the media box after clipping
        EXPECT_GE(artBox->x2 - artBox->x1, 0);
        EXPECT_GE(artBox->y2 - artBox->y1, 0);
    }
}

// Test that getArtBox defaults to media box when not explicitly set
TEST_F(PageGetArtBoxTest_712, GetArtBoxDefaultsToMediaBoxWhenNotSet_712)
{
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n197\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, strlen(pdfData), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        const PDFRectangle *artBox = page->getArtBox();
        const PDFRectangle *mediaBox = page->getMediaBox();
        ASSERT_NE(artBox, nullptr);
        ASSERT_NE(mediaBox, nullptr);
        // When no explicit ArtBox, it should default to CropBox which defaults to MediaBox
        EXPECT_DOUBLE_EQ(artBox->x1, mediaBox->x1);
        EXPECT_DOUBLE_EQ(artBox->y1, mediaBox->y1);
        EXPECT_DOUBLE_EQ(artBox->x2, mediaBox->x2);
        EXPECT_DOUBLE_EQ(artBox->y2, mediaBox->y2);
    }
}

// Test with an explicit ArtBox set
TEST_F(PageGetArtBoxTest_712, GetArtBoxWithExplicitArtBox_712)
{
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /ArtBox [10 20 300 400] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n222\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, strlen(pdfData), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        const PDFRectangle *artBox = page->getArtBox();
        ASSERT_NE(artBox, nullptr);
        EXPECT_DOUBLE_EQ(artBox->x1, 10.0);
        EXPECT_DOUBLE_EQ(artBox->y1, 20.0);
        EXPECT_DOUBLE_EQ(artBox->x2, 300.0);
        EXPECT_DOUBLE_EQ(artBox->y2, 400.0);
    }
}

// Test that getArtBox is const-correct (returns const pointer)
TEST_F(PageGetArtBoxTest_712, GetArtBoxReturnsConstPointer_712)
{
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n197\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, strlen(pdfData), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        const Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        const PDFRectangle *artBox = page->getArtBox();
        ASSERT_NE(artBox, nullptr);
        // Verify it's a valid const pointer by reading values
        EXPECT_TRUE(std::isfinite(artBox->x1));
        EXPECT_TRUE(std::isfinite(artBox->y1));
        EXPECT_TRUE(std::isfinite(artBox->x2));
        EXPECT_TRUE(std::isfinite(artBox->y2));
    }
}

// Test that multiple calls to getArtBox return the same pointer (stable reference)
TEST_F(PageGetArtBoxTest_712, GetArtBoxReturnsSamePointerOnMultipleCalls_712)
{
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n197\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, strlen(pdfData), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        const PDFRectangle *artBox1 = page->getArtBox();
        const PDFRectangle *artBox2 = page->getArtBox();
        EXPECT_EQ(artBox1, artBox2);
    }
}

// Test ArtBox clipped to CropBox boundaries
TEST_F(PageGetArtBoxTest_712, GetArtBoxClippedToCropBox_712)
{
    // ArtBox extends beyond CropBox - should be clipped
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /CropBox [50 50 500 700] /ArtBox [0 0 600 800] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n262\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, strlen(pdfData), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        const PDFRectangle *artBox = page->getArtBox();
        const PDFRectangle *cropBox = page->getCropBox();
        ASSERT_NE(artBox, nullptr);
        ASSERT_NE(cropBox, nullptr);
        // ArtBox should be clipped to not exceed CropBox
        EXPECT_GE(artBox->x1, cropBox->x1);
        EXPECT_GE(artBox->y1, cropBox->y1);
        EXPECT_LE(artBox->x2, cropBox->x2);
        EXPECT_LE(artBox->y2, cropBox->y2);
    }
}

// Test ArtBox with zero-size MediaBox
TEST_F(PageGetArtBoxTest_712, GetArtBoxWithZeroSizeMediaBox_712)
{
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 0 0] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n193\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, strlen(pdfData), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        const PDFRectangle *artBox = page->getArtBox();
        ASSERT_NE(artBox, nullptr);
    }
}
