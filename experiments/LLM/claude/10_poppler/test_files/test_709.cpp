#include <gtest/gtest.h>
#include <memory>
#include <cstring>
#include <cmath>

#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "PDFRectangle.h"

class PageGetCropHeightTest_709 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Helper: create a PDFDoc from an in-memory PDF string
static std::unique_ptr<PDFDoc> createPDFDocFromString(const std::string &pdfContent) {
    // GooString takes ownership in some contexts; we need a copy
    auto *stream = new MemStream(const_cast<char *>(pdfContent.c_str()), 0, pdfContent.size(), Object(objNull));
    // Wrap into a BaseStream-based PDFDoc
    return std::make_unique<PDFDoc>(stream);
}

// Minimal valid PDF with a specific MediaBox (no CropBox, so CropBox defaults to MediaBox)
static std::string makeMinimalPDF(double x1, double y1, double x2, double y2) {
    // Create a minimal PDF with specified MediaBox
    char buf[2048];
    snprintf(buf, sizeof(buf),
        "%%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [%.1f %.1f %.1f %.1f] >>\n"
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
        "0\n"  // We'll rely on poppler's repair mode
        "%%%%EOF\n",
        x1, y1, x2, y2);
    return std::string(buf);
}

static std::string makeMinimalPDFWithCropBox(double mx1, double my1, double mx2, double my2,
                                              double cx1, double cy1, double cx2, double cy2) {
    char buf[2048];
    snprintf(buf, sizeof(buf),
        "%%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [%.1f %.1f %.1f %.1f] /CropBox [%.1f %.1f %.1f %.1f] >>\n"
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
        "0\n"
        "%%%%EOF\n",
        mx1, my1, mx2, my2, cx1, cy1, cx2, cy2);
    return std::string(buf);
}

// Test: getCropHeight with standard letter-size page (no explicit CropBox)
TEST_F(PageGetCropHeightTest_709, DefaultCropBoxMatchesMediaBox_709) {
    // Standard US Letter: 612 x 792 points
    std::string pdf = makeMinimalPDF(0, 0, 612, 792);
    auto doc = createPDFDocFromString(pdf);
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());
    ASSERT_GE(doc->getNumPages(), 1);

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // Without explicit CropBox, it defaults to MediaBox, so height = 792 - 0 = 792
    EXPECT_DOUBLE_EQ(page->getCropHeight(), 792.0);
}

// Test: getCropHeight with explicit CropBox
TEST_F(PageGetCropHeightTest_709, ExplicitCropBox_709) {
    std::string pdf = makeMinimalPDFWithCropBox(0, 0, 612, 792, 50, 100, 562, 692);
    auto doc = createPDFDocFromString(pdf);
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());
    ASSERT_GE(doc->getNumPages(), 1);

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // CropBox y2 - y1 = 692 - 100 = 592
    EXPECT_DOUBLE_EQ(page->getCropHeight(), 592.0);
}

// Test: getCropHeight with zero-height CropBox
TEST_F(PageGetCropHeightTest_709, ZeroHeightCropBox_709) {
    std::string pdf = makeMinimalPDFWithCropBox(0, 0, 612, 792, 0, 100, 612, 100);
    auto doc = createPDFDocFromString(pdf);
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());
    ASSERT_GE(doc->getNumPages(), 1);

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // CropBox y2 - y1 = 100 - 100 = 0
    EXPECT_DOUBLE_EQ(page->getCropHeight(), 0.0);
}

// Test: getCropHeight with MediaBox starting at non-zero origin
TEST_F(PageGetCropHeightTest_709, NonZeroOriginMediaBox_709) {
    std::string pdf = makeMinimalPDF(100, 200, 500, 800);
    auto doc = createPDFDocFromString(pdf);
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());
    ASSERT_GE(doc->getNumPages(), 1);

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // MediaBox as CropBox: y2 - y1 = 800 - 200 = 600
    EXPECT_DOUBLE_EQ(page->getCropHeight(), 600.0);
}

// Test: getCropHeight with A4-size page
TEST_F(PageGetCropHeightTest_709, A4SizePage_709) {
    // A4: 595.28 x 841.89 points
    std::string pdf = makeMinimalPDF(0, 0, 595.28, 841.89);
    auto doc = createPDFDocFromString(pdf);
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());
    ASSERT_GE(doc->getNumPages(), 1);

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_NEAR(page->getCropHeight(), 841.89, 0.01);
}

// Test: getCropHeight with CropBox larger than MediaBox (should be clipped to MediaBox)
TEST_F(PageGetCropHeightTest_709, CropBoxClippedToMediaBox_709) {
    // CropBox extends beyond MediaBox; PageAttrs::clipBoxes should clip it
    std::string pdf = makeMinimalPDFWithCropBox(0, 0, 612, 792, -50, -50, 700, 900);
    auto doc = createPDFDocFromString(pdf);
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());
    ASSERT_GE(doc->getNumPages(), 1);

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // After clipping, CropBox should be clipped to MediaBox: height = 792 - 0 = 792
    EXPECT_DOUBLE_EQ(page->getCropHeight(), 792.0);
}

// Test: getCropHeight with small CropBox
TEST_F(PageGetCropHeightTest_709, SmallCropBox_709) {
    std::string pdf = makeMinimalPDFWithCropBox(0, 0, 612, 792, 10, 20, 30, 25);
    auto doc = createPDFDocFromString(pdf);
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());
    ASSERT_GE(doc->getNumPages(), 1);

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // CropBox y2 - y1 = 25 - 20 = 5
    EXPECT_DOUBLE_EQ(page->getCropHeight(), 5.0);
}

// Test: getCropHeight is consistent with getCropBox
TEST_F(PageGetCropHeightTest_709, ConsistentWithGetCropBox_709) {
    std::string pdf = makeMinimalPDFWithCropBox(0, 0, 612, 792, 72, 144, 540, 648);
    auto doc = createPDFDocFromString(pdf);
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());
    ASSERT_GE(doc->getNumPages(), 1);

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    const PDFRectangle *cropBox = page->getCropBox();
    ASSERT_NE(cropBox, nullptr);

    double expectedHeight = cropBox->y2 - cropBox->y1;
    EXPECT_DOUBLE_EQ(page->getCropHeight(), expectedHeight);
}

// Test: getCropWidth and getCropHeight are independent
TEST_F(PageGetCropHeightTest_709, WidthAndHeightIndependent_709) {
    std::string pdf = makeMinimalPDFWithCropBox(0, 0, 612, 792, 10, 20, 310, 520);
    auto doc = createPDFDocFromString(pdf);
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());
    ASSERT_GE(doc->getNumPages(), 1);

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    // Width = 310 - 10 = 300, Height = 520 - 20 = 500
    EXPECT_DOUBLE_EQ(page->getCropWidth(), 300.0);
    EXPECT_DOUBLE_EQ(page->getCropHeight(), 500.0);
    EXPECT_NE(page->getCropWidth(), page->getCropHeight());
}

// Test: Square page getCropHeight equals getCropWidth
TEST_F(PageGetCropHeightTest_709, SquarePage_709) {
    std::string pdf = makeMinimalPDF(0, 0, 500, 500);
    auto doc = createPDFDocFromString(pdf);
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());
    ASSERT_GE(doc->getNumPages(), 1);

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_DOUBLE_EQ(page->getCropHeight(), 500.0);
    EXPECT_DOUBLE_EQ(page->getCropHeight(), page->getCropWidth());
}

// Test: Large coordinate values
TEST_F(PageGetCropHeightTest_709, LargeCoordinates_709) {
    std::string pdf = makeMinimalPDF(0, 0, 100000, 100000);
    auto doc = createPDFDocFromString(pdf);
    ASSERT_TRUE(doc != nullptr);
    ASSERT_TRUE(doc->isOk());
    ASSERT_GE(doc->getNumPages(), 1);

    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);

    EXPECT_DOUBLE_EQ(page->getCropHeight(), 100000.0);
}
