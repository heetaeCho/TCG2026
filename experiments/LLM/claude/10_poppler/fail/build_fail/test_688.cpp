#include <gtest/gtest.h>
#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include <memory>
#include <cstring>

class PageAttrsTest_688 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that getBleedBox returns a non-null pointer
TEST_F(PageAttrsTest_688, GetBleedBoxReturnsNonNull_688) {
    // Create a PageAttrs with null parent and null dict
    // We need a minimal setup. Since PageAttrs constructor requires Dict*,
    // we'll use a real PDF document to get a valid Page with PageAttrs.
    // However, we can also test with a constructed PageAttrs if possible.
    
    // For a minimal test, let's create a PDFDoc from a minimal PDF in memory
    // and access its page attributes.
    
    // Create a minimal valid PDF in memory
    const char *pdfData = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n198\n%%EOF\n";
    
    // We'll test using a GooString-based approach if available
    // For now, just verify the interface contract through a loaded document
    
    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, strlen(pdfData), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        
        const PDFRectangle *bleedBox = page->getBleedBox();
        ASSERT_NE(bleedBox, nullptr);
    }
}

// Test that getBleedBox returns a valid PDFRectangle with expected values
TEST_F(PageAttrsTest_688, GetBleedBoxHasValidCoordinates_688) {
    const char *pdfData = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n198\n%%EOF\n";
    
    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, strlen(pdfData), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        
        const PDFRectangle *bleedBox = page->getBleedBox();
        ASSERT_NE(bleedBox, nullptr);
        
        // When no BleedBox is specified, it should default to CropBox,
        // which defaults to MediaBox
        EXPECT_DOUBLE_EQ(bleedBox->x1, 0.0);
        EXPECT_DOUBLE_EQ(bleedBox->y1, 0.0);
        EXPECT_DOUBLE_EQ(bleedBox->x2, 612.0);
        EXPECT_DOUBLE_EQ(bleedBox->y2, 792.0);
    }
}

// Test that getBleedBox with explicit BleedBox returns correct values
TEST_F(PageAttrsTest_688, GetBleedBoxWithExplicitBleedBox_688) {
    const char *pdfData = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /BleedBox [10 10 602 782] >>\nendobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n224\n%%EOF\n";
    
    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, strlen(pdfData), Object(objNull));
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

// Test that getBleedBox and getCropBox relationship when no BleedBox specified
TEST_F(PageAttrsTest_688, BleedBoxDefaultsToCropBoxWhenNotSpecified_688) {
    const char *pdfData = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /CropBox [50 50 562 742] >>\nendobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n222\n%%EOF\n";
    
    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, strlen(pdfData), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        
        const PDFRectangle *bleedBox = page->getBleedBox();
        const PDFRectangle *cropBox = page->getCropBox();
        ASSERT_NE(bleedBox, nullptr);
        ASSERT_NE(cropBox, nullptr);
        
        // When BleedBox is not specified, it should default to CropBox
        EXPECT_DOUBLE_EQ(bleedBox->x1, cropBox->x1);
        EXPECT_DOUBLE_EQ(bleedBox->y1, cropBox->y1);
        EXPECT_DOUBLE_EQ(bleedBox->x2, cropBox->x2);
        EXPECT_DOUBLE_EQ(bleedBox->y2, cropBox->y2);
    }
}

// Test that getBleedBox is clipped to CropBox when BleedBox extends beyond CropBox
TEST_F(PageAttrsTest_688, BleedBoxClippedToCropBox_688) {
    const char *pdfData = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /CropBox [50 50 562 742] /BleedBox [0 0 612 792] >>\nendobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n250\n%%EOF\n";
    
    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, strlen(pdfData), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        
        const PDFRectangle *bleedBox = page->getBleedBox();
        const PDFRectangle *cropBox = page->getCropBox();
        ASSERT_NE(bleedBox, nullptr);
        ASSERT_NE(cropBox, nullptr);
        
        // BleedBox should be clipped to CropBox
        EXPECT_GE(bleedBox->x1, cropBox->x1);
        EXPECT_GE(bleedBox->y1, cropBox->y1);
        EXPECT_LE(bleedBox->x2, cropBox->x2);
        EXPECT_LE(bleedBox->y2, cropBox->y2);
    }
}

// Test that calling getBleedBox multiple times returns the same pointer (const reference)
TEST_F(PageAttrsTest_688, GetBleedBoxReturnsSamePointerOnMultipleCalls_688) {
    const char *pdfData = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n198\n%%EOF\n";
    
    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, strlen(pdfData), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        
        const PDFRectangle *bleedBox1 = page->getBleedBox();
        const PDFRectangle *bleedBox2 = page->getBleedBox();
        
        // Since it returns address of internal member, pointer should be same
        EXPECT_EQ(bleedBox1, bleedBox2);
    }
}

// Test other PageAttrs box getters alongside getBleedBox
TEST_F(PageAttrsTest_688, AllBoxGettersReturnNonNull_688) {
    const char *pdfData = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n198\n%%EOF\n";
    
    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, strlen(pdfData), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        
        EXPECT_NE(page->getMediaBox(), nullptr);
        EXPECT_NE(page->getCropBox(), nullptr);
        EXPECT_NE(page->getBleedBox(), nullptr);
        EXPECT_NE(page->getTrimBox(), nullptr);
        EXPECT_NE(page->getArtBox(), nullptr);
    }
}

// Test with zero-area MediaBox
TEST_F(PageAttrsTest_688, GetBleedBoxWithZeroAreaMediaBox_688) {
    const char *pdfData = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 0 0] >>\nendobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n194\n%%EOF\n";
    
    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, strlen(pdfData), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        
        const PDFRectangle *bleedBox = page->getBleedBox();
        ASSERT_NE(bleedBox, nullptr);
        
        EXPECT_DOUBLE_EQ(bleedBox->x1, 0.0);
        EXPECT_DOUBLE_EQ(bleedBox->y1, 0.0);
        EXPECT_DOUBLE_EQ(bleedBox->x2, 0.0);
        EXPECT_DOUBLE_EQ(bleedBox->y2, 0.0);
    }
}
