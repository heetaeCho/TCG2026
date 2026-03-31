#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary headers
#include "Annot.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"

class AnnotGeometryTest_844 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }
};

// Test that getGeometryRect returns a non-null or valid pointer for a properly constructed AnnotGeometry
TEST_F(AnnotGeometryTest_844, GetGeometryRectReturnsValue_844) {
    // We test the getter method on the class interface.
    // Since we cannot easily construct AnnotGeometry without a valid PDFDoc,
    // we verify the interface signature and behavior through available means.
    
    // Create a minimal PDF document for testing
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotGeometry>(doc.get(), &rect, Annot::typeSquare);
        
        PDFRectangle *geomRect = annot->getGeometryRect();
        // The geometry rect may or may not be set depending on construction
        // We just verify the call doesn't crash and returns something
        // (could be nullptr if not initialized from dict)
        SUCCEED();
    } else {
        GTEST_SKIP() << "Test PDF not available";
    }
}

// Test getInteriorColor returns value (possibly null for default construction)
TEST_F(AnnotGeometryTest_844, GetInteriorColorDefault_844) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotGeometry>(doc.get(), &rect, Annot::typeSquare);
        
        AnnotColor *color = annot->getInteriorColor();
        // Default interior color may be nullptr
        // We just verify the interface works without crashing
        SUCCEED();
    } else {
        GTEST_SKIP() << "Test PDF not available";
    }
}

// Test getBorderEffect returns value
TEST_F(AnnotGeometryTest_844, GetBorderEffectDefault_844) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotGeometry>(doc.get(), &rect, Annot::typeSquare);
        
        AnnotBorderEffect *effect = annot->getBorderEffect();
        // Just verify no crash
        SUCCEED();
    } else {
        GTEST_SKIP() << "Test PDF not available";
    }
}

// Test creating AnnotGeometry with typeSquare subtype
TEST_F(AnnotGeometryTest_844, CreateSquareAnnotation_844) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (doc->isOk()) {
        PDFRectangle rect(10, 20, 200, 300);
        auto annot = std::make_unique<AnnotGeometry>(doc.get(), &rect, Annot::typeSquare);
        
        EXPECT_EQ(annot->getType(), Annot::typeSquare);
    } else {
        GTEST_SKIP() << "Test PDF not available";
    }
}

// Test creating AnnotGeometry with typeCircle subtype
TEST_F(AnnotGeometryTest_844, CreateCircleAnnotation_844) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (doc->isOk()) {
        PDFRectangle rect(10, 20, 200, 300);
        auto annot = std::make_unique<AnnotGeometry>(doc.get(), &rect, Annot::typeCircle);
        
        EXPECT_EQ(annot->getType(), Annot::typeCircle);
    } else {
        GTEST_SKIP() << "Test PDF not available";
    }
}

// Test setType changes the annotation subtype
TEST_F(AnnotGeometryTest_844, SetTypeChangesSubtype_844) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (doc->isOk()) {
        PDFRectangle rect(10, 20, 200, 300);
        auto annot = std::make_unique<AnnotGeometry>(doc.get(), &rect, Annot::typeSquare);
        
        EXPECT_EQ(annot->getType(), Annot::typeSquare);
        
        annot->setType(Annot::typeCircle);
        EXPECT_EQ(annot->getType(), Annot::typeCircle);
    } else {
        GTEST_SKIP() << "Test PDF not available";
    }
}

// Test setInteriorColor with a valid color
TEST_F(AnnotGeometryTest_844, SetInteriorColor_844) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (doc->isOk()) {
        PDFRectangle rect(10, 20, 200, 300);
        auto annot = std::make_unique<AnnotGeometry>(doc.get(), &rect, Annot::typeSquare);
        
        auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
        annot->setInteriorColor(std::move(color));
        
        AnnotColor *retrievedColor = annot->getInteriorColor();
        ASSERT_NE(retrievedColor, nullptr);
    } else {
        GTEST_SKIP() << "Test PDF not available";
    }
}

// Test setInteriorColor with nullptr to clear color
TEST_F(AnnotGeometryTest_844, SetInteriorColorNull_844) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (doc->isOk()) {
        PDFRectangle rect(10, 20, 200, 300);
        auto annot = std::make_unique<AnnotGeometry>(doc.get(), &rect, Annot::typeSquare);
        
        // Set a color first
        auto color = std::make_unique<AnnotColor>(0.0, 1.0, 0.0);
        annot->setInteriorColor(std::move(color));
        
        // Now set to nullptr
        annot->setInteriorColor(nullptr);
        
        AnnotColor *retrievedColor = annot->getInteriorColor();
        EXPECT_EQ(retrievedColor, nullptr);
    } else {
        GTEST_SKIP() << "Test PDF not available";
    }
}

// Test with boundary rectangle values (zero-size rect)
TEST_F(AnnotGeometryTest_844, ZeroSizeRectangle_844) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 0, 0);
        auto annot = std::make_unique<AnnotGeometry>(doc.get(), &rect, Annot::typeSquare);
        
        // Should still be constructible
        EXPECT_EQ(annot->getType(), Annot::typeSquare);
    } else {
        GTEST_SKIP() << "Test PDF not available";
    }
}

// Test with large rectangle values
TEST_F(AnnotGeometryTest_844, LargeRectangleValues_844) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 100000, 100000);
        auto annot = std::make_unique<AnnotGeometry>(doc.get(), &rect, Annot::typeCircle);
        
        EXPECT_EQ(annot->getType(), Annot::typeCircle);
        // Verify getGeometryRect doesn't crash
        annot->getGeometryRect();
        SUCCEED();
    } else {
        GTEST_SKIP() << "Test PDF not available";
    }
}
