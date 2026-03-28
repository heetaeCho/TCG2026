#include <gtest/gtest.h>
#include <memory>
#include <cstring>

#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"
#include "PDFDocFactory.h"

class PageGetBleedBoxTest_710 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that getBleedBox returns a non-null pointer when a valid Page exists
TEST_F(PageGetBleedBoxTest_710, GetBleedBoxReturnsNonNull_710)
{
    // Create a minimal PDF in memory to test with
    // We'll use a simple approach: create a PDF file string
    static const char pdfData[] =
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

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);

        const PDFRectangle *bleedBox = page->getBleedBox();
        ASSERT_NE(bleedBox, nullptr);
    }
}

// Test that getBleedBox returns valid coordinates (defaults to cropBox/mediaBox when not explicitly set)
TEST_F(PageGetBleedBoxTest_710, GetBleedBoxDefaultsToCropBox_710)
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

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);

        const PDFRectangle *bleedBox = page->getBleedBox();
        ASSERT_NE(bleedBox, nullptr);

        // When no BleedBox is specified, it defaults to the CropBox (which defaults to MediaBox)
        const PDFRectangle *cropBox = page->getCropBox();
        ASSERT_NE(cropBox, nullptr);

        EXPECT_DOUBLE_EQ(bleedBox->x1, cropBox->x1);
        EXPECT_DOUBLE_EQ(bleedBox->y1, cropBox->y1);
        EXPECT_DOUBLE_EQ(bleedBox->x2, cropBox->x2);
        EXPECT_DOUBLE_EQ(bleedBox->y2, cropBox->y2);
    }
}

// Test that getBleedBox returns the explicitly set BleedBox
TEST_F(PageGetBleedBoxTest_710, GetBleedBoxReturnsExplicitBleedBox_710)
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
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /BleedBox [10 10 602 782] >>\n"
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

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);

        const PDFRectangle *bleedBox = page->getBleedBox();
        ASSERT_NE(bleedBox, nullptr);

        EXPECT_DOUBLE_EQ(bleedBox->x1, 10.0);
        EXPECT_DOUBLE_EQ(bleedBox->y1, 10.0);
        EXPECT_DOUBLE_EQ(bleedBox->x2, 602.0);
        EXPECT_DOUBLE_EQ(bleedBox->y2, 782.0);
    }
}

// Test that getBleedBox with CropBox set - BleedBox should be clipped to CropBox
TEST_F(PageGetBleedBoxTest_710, GetBleedBoxClippedToCropBox_710)
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
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /CropBox [50 50 562 742] /BleedBox [0 0 612 792] >>\n"
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
        "240\n"
        "%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);

        const PDFRectangle *bleedBox = page->getBleedBox();
        ASSERT_NE(bleedBox, nullptr);

        const PDFRectangle *cropBox = page->getCropBox();
        ASSERT_NE(cropBox, nullptr);

        // BleedBox should be clipped to CropBox
        EXPECT_GE(bleedBox->x1, cropBox->x1);
        EXPECT_GE(bleedBox->y1, cropBox->y1);
        EXPECT_LE(bleedBox->x2, cropBox->x2);
        EXPECT_LE(bleedBox->y2, cropBox->y2);
    }
}

// Test getBleedBox consistency - calling multiple times returns same result
TEST_F(PageGetBleedBoxTest_710, GetBleedBoxConsistentMultipleCalls_710)
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

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);

        const PDFRectangle *bleedBox1 = page->getBleedBox();
        const PDFRectangle *bleedBox2 = page->getBleedBox();

        ASSERT_NE(bleedBox1, nullptr);
        ASSERT_NE(bleedBox2, nullptr);

        // Should return the same pointer (same internal object)
        EXPECT_EQ(bleedBox1, bleedBox2);

        EXPECT_DOUBLE_EQ(bleedBox1->x1, bleedBox2->x1);
        EXPECT_DOUBLE_EQ(bleedBox1->y1, bleedBox2->y1);
        EXPECT_DOUBLE_EQ(bleedBox1->x2, bleedBox2->x2);
        EXPECT_DOUBLE_EQ(bleedBox1->y2, bleedBox2->y2);
    }
}

// Test getBleedBox returns const pointer
TEST_F(PageGetBleedBoxTest_710, GetBleedBoxReturnsConstPointer_710)
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
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 100 200] /BleedBox [5 5 95 195] >>\n"
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

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);

        const PDFRectangle *bleedBox = page->getBleedBox();
        ASSERT_NE(bleedBox, nullptr);

        // Verify the values are reasonable (within the media box)
        EXPECT_GE(bleedBox->x1, 0.0);
        EXPECT_GE(bleedBox->y1, 0.0);
        EXPECT_LE(bleedBox->x2, 100.0);
        EXPECT_LE(bleedBox->y2, 200.0);
    }
}

// Test with zero-size MediaBox
TEST_F(PageGetBleedBoxTest_710, GetBleedBoxZeroSizeMediaBox_710)
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
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 0 0] >>\n"
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
        "186\n"
        "%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        if (page != nullptr) {
            const PDFRectangle *bleedBox = page->getBleedBox();
            // Even with zero-size media box, getBleedBox should return non-null
            ASSERT_NE(bleedBox, nullptr);
        }
    }
}
