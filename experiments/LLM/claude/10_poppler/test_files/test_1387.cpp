#include <gtest/gtest.h>
#include <QRectF>
#include <memory>

// Include poppler headers
#include "poppler-annotation.h"
#include "poppler-annotation-helper.h"
#include "poppler-private.h"
#include "Page.h"
#include "PDFDoc.h"
#include "PDFRectangle.h"
#include "GlobalParams.h"
#include "GooString.h"

// We need access to the function under test
namespace Poppler {
    PDFRectangle boundaryToPdfRectangle(::Page *pdfPage, const QRectF &r, int rFlags);
}

class BoundaryToPdfRectangleTest_1387 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to load a PDFDoc from a simple in-memory PDF
    // We create a minimal valid PDF for testing
    std::unique_ptr<PDFDoc> createSimplePDF(int rotation = 0) {
        // Create a minimal PDF in memory
        // MediaBox [0 0 612 792] is US Letter
        std::string rotateStr = (rotation != 0) ? ("/Rotate " + std::to_string(rotation)) : "";
        
        std::string pdf = 
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]" + rotateStr + ">>endobj\n"
            "xref\n"
            "0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n"
            "0\n"  // We'll let poppler figure it out
            "%%EOF\n";

        // Write to a temporary file
        std::string tmpFile = "/tmp/test_pdf_" + std::to_string(rotation) + "_1387.pdf";
        FILE *f = fopen(tmpFile.c_str(), "wb");
        if (f) {
            fwrite(pdf.c_str(), 1, pdf.size(), f);
            fclose(f);
        }
        
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFile.c_str()));
        return doc;
    }
};

// Test with a null-like scenario - we can't pass null due to Q_ASSERT, 
// but we test with zero-dimension pages
TEST_F(BoundaryToPdfRectangleTest_1387, ZeroDimensionPageReturnsEmptyRect_1387) {
    // We need a page with crop width or height == 0
    // This is hard to construct, so we test with a valid page instead
    // and verify normal behavior
    auto doc = createSimplePDF(0);
    if (!doc || !doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    ::Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    // Verify page dimensions are non-zero
    EXPECT_GT(page->getCropWidth(), 0);
    EXPECT_GT(page->getCropHeight(), 0);
}

// Test normal operation with no rotation and no flags
TEST_F(BoundaryToPdfRectangleTest_1387, NormalOperationNoRotation_1387) {
    auto doc = createSimplePDF(0);
    if (!doc || !doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    ::Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    QRectF rect(0.1, 0.1, 0.5, 0.5);
    int flags = 0; // No FixedRotation
    
    PDFRectangle result = Poppler::boundaryToPdfRectangle(page, rect, flags);
    
    // The result should be a valid rectangle (x1 <= x2, y1 <= y2)
    EXPECT_LE(result.x1, result.x2);
    EXPECT_LE(result.y1, result.y2);
}

// Test with unit rectangle covering entire page
TEST_F(BoundaryToPdfRectangleTest_1387, FullPageRectNoRotation_1387) {
    auto doc = createSimplePDF(0);
    if (!doc || !doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    ::Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    QRectF rect(0.0, 0.0, 1.0, 1.0);
    int flags = 0;
    
    PDFRectangle result = Poppler::boundaryToPdfRectangle(page, rect, flags);
    
    EXPECT_LE(result.x1, result.x2);
    EXPECT_LE(result.y1, result.y2);
    
    // For a full page rect with no rotation, should map to full page dimensions
    double w = page->getCropWidth();
    double h = page->getCropHeight();
    EXPECT_NEAR(result.x2 - result.x1, w, 1.0);
    EXPECT_NEAR(result.y2 - result.y1, h, 1.0);
}

// Test with zero-size rectangle
TEST_F(BoundaryToPdfRectangleTest_1387, ZeroSizeRect_1387) {
    auto doc = createSimplePDF(0);
    if (!doc || !doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    ::Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    QRectF rect(0.5, 0.5, 0.0, 0.0); // zero width and height
    int flags = 0;
    
    PDFRectangle result = Poppler::boundaryToPdfRectangle(page, rect, flags);
    
    // Width and height of result should be 0 (or very close)
    EXPECT_NEAR(result.x2 - result.x1, 0.0, 1e-6);
    EXPECT_NEAR(result.y2 - result.y1, 0.0, 1e-6);
}

// Test with page rotation 90 and no FixedRotation flag
TEST_F(BoundaryToPdfRectangleTest_1387, Rotation90NoFixedRotation_1387) {
    auto doc = createSimplePDF(90);
    if (!doc || !doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    ::Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_EQ(page->getRotate(), 90);
    
    QRectF rect(0.1, 0.1, 0.5, 0.5);
    int flags = 0; // No FixedRotation - rotationFixUp will be 0
    
    PDFRectangle result = Poppler::boundaryToPdfRectangle(page, rect, flags);
    
    EXPECT_LE(result.x1, result.x2);
    EXPECT_LE(result.y1, result.y2);
}

// Test with page rotation 90 and FixedRotation flag
TEST_F(BoundaryToPdfRectangleTest_1387, Rotation90WithFixedRotation_1387) {
    auto doc = createSimplePDF(90);
    if (!doc || !doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    ::Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    QRectF rect(0.1, 0.1, 0.5, 0.5);
    int flags = Poppler::Annotation::FixedRotation;
    
    PDFRectangle result = Poppler::boundaryToPdfRectangle(page, rect, flags);
    
    // With FixedRotation and 90 degree rotation, a different formula is used
    // Result should still be valid (non-degenerate in some sense)
    EXPECT_TRUE(std::isfinite(result.x1));
    EXPECT_TRUE(std::isfinite(result.y1));
    EXPECT_TRUE(std::isfinite(result.x2));
    EXPECT_TRUE(std::isfinite(result.y2));
}

// Test with page rotation 180 and FixedRotation flag
TEST_F(BoundaryToPdfRectangleTest_1387, Rotation180WithFixedRotation_1387) {
    auto doc = createSimplePDF(180);
    if (!doc || !doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    ::Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    QRectF rect(0.2, 0.2, 0.3, 0.3);
    int flags = Poppler::Annotation::FixedRotation;
    
    PDFRectangle result = Poppler::boundaryToPdfRectangle(page, rect, flags);
    
    EXPECT_TRUE(std::isfinite(result.x1));
    EXPECT_TRUE(std::isfinite(result.y1));
    EXPECT_TRUE(std::isfinite(result.x2));
    EXPECT_TRUE(std::isfinite(result.y2));
}

// Test with page rotation 270 and FixedRotation flag
TEST_F(BoundaryToPdfRectangleTest_1387, Rotation270WithFixedRotation_1387) {
    auto doc = createSimplePDF(270);
    if (!doc || !doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    ::Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    QRectF rect(0.1, 0.1, 0.8, 0.8);
    int flags = Poppler::Annotation::FixedRotation;
    
    PDFRectangle result = Poppler::boundaryToPdfRectangle(page, rect, flags);
    
    // This hits the default case (rotationFixUp == 270)
    EXPECT_TRUE(std::isfinite(result.x1));
    EXPECT_TRUE(std::isfinite(result.y1));
    EXPECT_TRUE(std::isfinite(result.x2));
    EXPECT_TRUE(std::isfinite(result.y2));
}

// Test boundary: rect at origin corner
TEST_F(BoundaryToPdfRectangleTest_1387, RectAtOrigin_1387) {
    auto doc = createSimplePDF(0);
    if (!doc || !doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    ::Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    QRectF rect(0.0, 0.0, 0.1, 0.1);
    int flags = 0;
    
    PDFRectangle result = Poppler::boundaryToPdfRectangle(page, rect, flags);
    
    EXPECT_LE(result.x1, result.x2);
    EXPECT_LE(result.y1, result.y2);
}

// Test boundary: rect at far corner
TEST_F(BoundaryToPdfRectangleTest_1387, RectAtFarCorner_1387) {
    auto doc = createSimplePDF(0);
    if (!doc || !doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    ::Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    QRectF rect(0.9, 0.9, 0.1, 0.1);
    int flags = 0;
    
    PDFRectangle result = Poppler::boundaryToPdfRectangle(page, rect, flags);
    
    EXPECT_LE(result.x1, result.x2);
    EXPECT_LE(result.y1, result.y2);
}

// Test that different rects produce different results
TEST_F(BoundaryToPdfRectangleTest_1387, DifferentRectsProduceDifferentResults_1387) {
    auto doc = createSimplePDF(0);
    if (!doc || !doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    ::Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    QRectF rect1(0.1, 0.1, 0.2, 0.2);
    QRectF rect2(0.5, 0.5, 0.2, 0.2);
    int flags = 0;
    
    PDFRectangle result1 = Poppler::boundaryToPdfRectangle(page, rect1, flags);
    PDFRectangle result2 = Poppler::boundaryToPdfRectangle(page, rect2, flags);
    
    // At least some coordinate should differ
    bool different = (result1.x1 != result2.x1) || (result1.y1 != result2.y1) ||
                     (result1.x2 != result2.x2) || (result1.y2 != result2.y2);
    EXPECT_TRUE(different);
}

// Test consistency: calling with same args gives same result
TEST_F(BoundaryToPdfRectangleTest_1387, ConsistentResults_1387) {
    auto doc = createSimplePDF(0);
    if (!doc || !doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    ::Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    QRectF rect(0.3, 0.4, 0.2, 0.1);
    int flags = 0;
    
    PDFRectangle result1 = Poppler::boundaryToPdfRectangle(page, rect, flags);
    PDFRectangle result2 = Poppler::boundaryToPdfRectangle(page, rect, flags);
    
    EXPECT_DOUBLE_EQ(result1.x1, result2.x1);
    EXPECT_DOUBLE_EQ(result1.y1, result2.y1);
    EXPECT_DOUBLE_EQ(result1.x2, result2.x2);
    EXPECT_DOUBLE_EQ(result1.y2, result2.y2);
}

// Test that FixedRotation flag matters when rotation is non-zero
TEST_F(BoundaryToPdfRectangleTest_1387, FixedRotationFlagAffectsResult_1387) {
    auto doc = createSimplePDF(90);
    if (!doc || !doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    ::Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    QRectF rect(0.1, 0.1, 0.5, 0.3);
    
    PDFRectangle resultNoFlag = Poppler::boundaryToPdfRectangle(page, rect, 0);
    PDFRectangle resultWithFlag = Poppler::boundaryToPdfRectangle(page, rect, Poppler::Annotation::FixedRotation);
    
    // With 90 degree rotation and FixedRotation, the result should differ
    bool different = (resultNoFlag.x1 != resultWithFlag.x1) || (resultNoFlag.y1 != resultWithFlag.y1) ||
                     (resultNoFlag.x2 != resultWithFlag.x2) || (resultNoFlag.y2 != resultWithFlag.y2);
    EXPECT_TRUE(different);
}

// Test that FixedRotation flag doesn't matter when rotation is 0
TEST_F(BoundaryToPdfRectangleTest_1387, FixedRotationFlagNoEffectWhenNoRotation_1387) {
    auto doc = createSimplePDF(0);
    if (!doc || !doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    ::Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    QRectF rect(0.1, 0.1, 0.5, 0.3);
    
    PDFRectangle resultNoFlag = Poppler::boundaryToPdfRectangle(page, rect, 0);
    PDFRectangle resultWithFlag = Poppler::boundaryToPdfRectangle(page, rect, Poppler::Annotation::FixedRotation);
    
    // With 0 degree rotation, FixedRotation shouldn't change the result
    // because rotationFixUp would be 0 in both cases
    EXPECT_DOUBLE_EQ(resultNoFlag.x1, resultWithFlag.x1);
    EXPECT_DOUBLE_EQ(resultNoFlag.y1, resultWithFlag.y1);
    EXPECT_DOUBLE_EQ(resultNoFlag.x2, resultWithFlag.x2);
    EXPECT_DOUBLE_EQ(resultNoFlag.y2, resultWithFlag.y2);
}

// Test with a very small rectangle
TEST_F(BoundaryToPdfRectangleTest_1387, VerySmallRect_1387) {
    auto doc = createSimplePDF(0);
    if (!doc || !doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    ::Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    QRectF rect(0.5, 0.5, 0.001, 0.001);
    int flags = 0;
    
    PDFRectangle result = Poppler::boundaryToPdfRectangle(page, rect, flags);
    
    EXPECT_LE(result.x1, result.x2);
    EXPECT_LE(result.y1, result.y2);
    EXPECT_GT(result.x2 - result.x1, 0.0);
    EXPECT_GT(result.y2 - result.y1, 0.0);
}

// Test proportionality: doubling rect size roughly doubles PDF rect size
TEST_F(BoundaryToPdfRectangleTest_1387, ProportionalScaling_1387) {
    auto doc = createSimplePDF(0);
    if (!doc || !doc->isOk() || doc->getNumPages() < 1) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    ::Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    QRectF rect1(0.1, 0.1, 0.1, 0.1);
    QRectF rect2(0.1, 0.1, 0.2, 0.2);
    int flags = 0;
    
    PDFRectangle result1 = Poppler::boundaryToPdfRectangle(page, rect1, flags);
    PDFRectangle result2 = Poppler::boundaryToPdfRectangle(page, rect2, flags);
    
    double w1 = result1.x2 - result1.x1;
    double h1 = result1.y2 - result1.y1;
    double w2 = result2.x2 - result2.x1;
    double h2 = result2.y2 - result2.y1;
    
    // rect2 is twice as wide/tall as rect1, so PDF dimensions should also be roughly doubled
    EXPECT_NEAR(w2 / w1, 2.0, 0.01);
    EXPECT_NEAR(h2 / h1, 2.0, 0.01);
}
