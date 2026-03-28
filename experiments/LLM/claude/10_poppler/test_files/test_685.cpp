#include <gtest/gtest.h>
#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include <memory>
#include <string>

class PageAttrsTest_685 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that getMediaBox returns a non-null pointer
TEST_F(PageAttrsTest_685, GetMediaBoxReturnsNonNull_685) {
    // Create a PageAttrs with null parent and null dict
    // We need a valid Dict to construct PageAttrs
    // Use a real PDF document to get valid Page objects
    
    // Since we can't easily construct PageAttrs without a Dict,
    // we'll test through PDFDoc which creates Page objects with PageAttrs
    
    // For a minimal test, create PageAttrs with nullptr attrs and a dict
    // We need an XRef for Dict, so let's use a document approach
    
    // Create a minimal PDF in memory
    const std::string pdfContent = 
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
        "196\n"
        "%%EOF\n";
    
    // We'll use a file-based approach or GooString-based approach
    // For simplicity, test what we can
    
    // Since constructing PageAttrs directly is complex, 
    // we verify the interface contract through a loaded document
    auto *stream = new MemStream(const_cast<char*>(pdfContent.c_str()), 0, pdfContent.size(), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        
        const PDFRectangle *mediaBox = page->getMediaBox();
        ASSERT_NE(mediaBox, nullptr);
    }
}

// Test MediaBox values for a standard letter-size page
TEST_F(PageAttrsTest_685, MediaBoxHasExpectedValues_685) {
    const std::string pdfContent = 
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
        "196\n"
        "%%EOF\n";
    
    auto *stream = new MemStream(const_cast<char*>(pdfContent.c_str()), 0, pdfContent.size(), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        
        const PDFRectangle *mediaBox = page->getMediaBox();
        ASSERT_NE(mediaBox, nullptr);
        EXPECT_DOUBLE_EQ(mediaBox->x1, 0.0);
        EXPECT_DOUBLE_EQ(mediaBox->y1, 0.0);
        EXPECT_DOUBLE_EQ(mediaBox->x2, 612.0);
        EXPECT_DOUBLE_EQ(mediaBox->y2, 792.0);
    }
}

// Test CropBox - when not specified, should default to MediaBox
TEST_F(PageAttrsTest_685, CropBoxDefaultsToMediaBox_685) {
    const std::string pdfContent = 
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
        "196\n"
        "%%EOF\n";
    
    auto *stream = new MemStream(const_cast<char*>(pdfContent.c_str()), 0, pdfContent.size(), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        
        const PDFRectangle *cropBox = page->getCropBox();
        const PDFRectangle *mediaBox = page->getMediaBox();
        ASSERT_NE(cropBox, nullptr);
        ASSERT_NE(mediaBox, nullptr);
        
        // When no CropBox is specified, it defaults to MediaBox
        EXPECT_DOUBLE_EQ(cropBox->x1, mediaBox->x1);
        EXPECT_DOUBLE_EQ(cropBox->y1, mediaBox->y1);
        EXPECT_DOUBLE_EQ(cropBox->x2, mediaBox->x2);
        EXPECT_DOUBLE_EQ(cropBox->y2, mediaBox->y2);
    }
}

// Test isCropped returns false when no CropBox is specified
TEST_F(PageAttrsTest_685, IsCroppedFalseWhenNoCropBox_685) {
    const std::string pdfContent = 
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
        "196\n"
        "%%EOF\n";
    
    auto *stream = new MemStream(const_cast<char*>(pdfContent.c_str()), 0, pdfContent.size(), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_FALSE(page->isCropped());
    }
}

// Test with explicit CropBox
TEST_F(PageAttrsTest_685, ExplicitCropBoxSetsCropped_685) {
    const std::string pdfContent = 
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
        "219\n"
        "%%EOF\n";
    
    auto *stream = new MemStream(const_cast<char*>(pdfContent.c_str()), 0, pdfContent.size(), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_TRUE(page->isCropped());
        
        const PDFRectangle *cropBox = page->getCropBox();
        ASSERT_NE(cropBox, nullptr);
        EXPECT_DOUBLE_EQ(cropBox->x1, 10.0);
        EXPECT_DOUBLE_EQ(cropBox->y1, 10.0);
        EXPECT_DOUBLE_EQ(cropBox->x2, 600.0);
        EXPECT_DOUBLE_EQ(cropBox->y2, 780.0);
    }
}

// Test BleedBox defaults when not specified
TEST_F(PageAttrsTest_685, BleedBoxReturnsNonNull_685) {
    const std::string pdfContent = 
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
        "196\n"
        "%%EOF\n";
    
    auto *stream = new MemStream(const_cast<char*>(pdfContent.c_str()), 0, pdfContent.size(), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        
        const PDFRectangle *bleedBox = page->getBleedBox();
        ASSERT_NE(bleedBox, nullptr);
    }
}

// Test TrimBox returns non-null
TEST_F(PageAttrsTest_685, TrimBoxReturnsNonNull_685) {
    const std::string pdfContent = 
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
        "196\n"
        "%%EOF\n";
    
    auto *stream = new MemStream(const_cast<char*>(pdfContent.c_str()), 0, pdfContent.size(), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        
        const PDFRectangle *trimBox = page->getTrimBox();
        ASSERT_NE(trimBox, nullptr);
    }
}

// Test ArtBox returns non-null
TEST_F(PageAttrsTest_685, ArtBoxReturnsNonNull_685) {
    const std::string pdfContent = 
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
        "196\n"
        "%%EOF\n";
    
    auto *stream = new MemStream(const_cast<char*>(pdfContent.c_str()), 0, pdfContent.size(), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        
        const PDFRectangle *artBox = page->getArtBox();
        ASSERT_NE(artBox, nullptr);
    }
}

// Test default rotation is 0
TEST_F(PageAttrsTest_685, DefaultRotationIsZero_685) {
    const std::string pdfContent = 
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
        "196\n"
        "%%EOF\n";
    
    auto *stream = new MemStream(const_cast<char*>(pdfContent.c_str()), 0, pdfContent.size(), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_EQ(page->getRotate(), 0);
    }
}

// Test rotation with explicit Rotate value
TEST_F(PageAttrsTest_685, ExplicitRotation90_685) {
    const std::string pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /Rotate 90 >>\n"
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
        "208\n"
        "%%EOF\n";
    
    auto *stream = new MemStream(const_cast<char*>(pdfContent.c_str()), 0, pdfContent.size(), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_EQ(page->getRotate(), 90);
    }
}

// Test that getMediaBox returns consistent results on multiple calls
TEST_F(PageAttrsTest_685, GetMediaBoxConsistentMultipleCalls_685) {
    const std::string pdfContent = 
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
        "196\n"
        "%%EOF\n";
    
    auto *stream = new MemStream(const_cast<char*>(pdfContent.c_str()), 0, pdfContent.size(), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        
        const PDFRectangle *mediaBox1 = page->getMediaBox();
        const PDFRectangle *mediaBox2 = page->getMediaBox();
        
        // Should return the same pointer (same internal object)
        EXPECT_EQ(mediaBox1, mediaBox2);
        
        // Values should be identical
        EXPECT_DOUBLE_EQ(mediaBox1->x1, mediaBox2->x1);
        EXPECT_DOUBLE_EQ(mediaBox1->y1, mediaBox2->y1);
        EXPECT_DOUBLE_EQ(mediaBox1->x2, mediaBox2->x2);
        EXPECT_DOUBLE_EQ(mediaBox1->y2, mediaBox2->y2);
    }
}

// Test non-standard MediaBox dimensions (A4 page)
TEST_F(PageAttrsTest_685, A4MediaBoxDimensions_685) {
    const std::string pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 595.276 841.89] >>\n"
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
        "204\n"
        "%%EOF\n";
    
    auto *stream = new MemStream(const_cast<char*>(pdfContent.c_str()), 0, pdfContent.size(), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        
        const PDFRectangle *mediaBox = page->getMediaBox();
        ASSERT_NE(mediaBox, nullptr);
        EXPECT_NEAR(mediaBox->x1, 0.0, 0.01);
        EXPECT_NEAR(mediaBox->y1, 0.0, 0.01);
        EXPECT_NEAR(mediaBox->x2, 595.276, 0.01);
        EXPECT_NEAR(mediaBox->y2, 841.89, 0.01);
    }
}

// Test MediaBox inherited from parent Pages node
TEST_F(PageAttrsTest_685, MediaBoxInheritedFromParent_685) {
    const std::string pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 /MediaBox [0 0 400 500] >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R >>\n"
        "endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000131 00000 n \n"
        "trailer\n"
        "<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n"
        "180\n"
        "%%EOF\n";
    
    auto *stream = new MemStream(const_cast<char*>(pdfContent.c_str()), 0, pdfContent.size(), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        
        const PDFRectangle *mediaBox = page->getMediaBox();
        ASSERT_NE(mediaBox, nullptr);
        EXPECT_DOUBLE_EQ(mediaBox->x1, 0.0);
        EXPECT_DOUBLE_EQ(mediaBox->y1, 0.0);
        EXPECT_DOUBLE_EQ(mediaBox->x2, 400.0);
        EXPECT_DOUBLE_EQ(mediaBox->y2, 500.0);
    }
}

// Test all box getters return non-null with minimal page
TEST_F(PageAttrsTest_685, AllBoxGettersReturnNonNull_685) {
    const std::string pdfContent = 
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
        "196\n"
        "%%EOF\n";
    
    auto *stream = new MemStream(const_cast<char*>(pdfContent.c_str()), 0, pdfContent.size(), Object(objNull));
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
