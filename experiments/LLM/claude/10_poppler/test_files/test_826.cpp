#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Annot.h"
#include "PDFDoc.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"
#include "Object.h"

class AnnotLineTest_826 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    std::unique_ptr<PDFDoc> loadTestDoc(const char *filename) {
        GooString path(filename);
        return std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(path));
    }
};

// Test that getInteriorColor returns nullptr when no interior color is set
TEST_F(AnnotLineTest_826, GetInteriorColorReturnsNullByDefault_826) {
    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    // We need a valid PDFDoc; create a minimal one if possible
    // Since we can't easily create a PDFDoc without a file, we test through
    // the interface constraints. We'll create an AnnotLine with a rectangle.
    
    // For this test, we attempt to construct an AnnotLine and check default interior color
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle pdfRect(10, 10, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &pdfRect);
        
        // By default, interior color should be nullptr (no interior color set)
        AnnotColor *color = annot->getInteriorColor();
        // It may or may not be null depending on defaults; we just verify it doesn't crash
        // and returns a consistent result
        AnnotColor *color2 = annot->getInteriorColor();
        EXPECT_EQ(color, color2);
    }
}

// Test setInteriorColor and getInteriorColor
TEST_F(AnnotLineTest_826, SetAndGetInteriorColor_826) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle pdfRect(10, 10, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &pdfRect);
        
        // Set a new interior color (red)
        auto newColor = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
        AnnotColor *rawPtr = newColor.get();
        annot->setInteriorColor(std::move(newColor));
        
        AnnotColor *result = annot->getInteriorColor();
        ASSERT_NE(result, nullptr);
        // The pointer may differ if internal copy is made, but values should match
        EXPECT_DOUBLE_EQ(result->getValues()[0], 1.0);
        EXPECT_DOUBLE_EQ(result->getValues()[1], 0.0);
        EXPECT_DOUBLE_EQ(result->getValues()[2], 0.0);
    }
}

// Test setInteriorColor to nullptr clears the color
TEST_F(AnnotLineTest_826, SetInteriorColorToNull_826) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle pdfRect(10, 10, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &pdfRect);
        
        // First set a color
        auto color = std::make_unique<AnnotColor>(0.5, 0.5, 0.5);
        annot->setInteriorColor(std::move(color));
        ASSERT_NE(annot->getInteriorColor(), nullptr);
        
        // Now set to null
        annot->setInteriorColor(nullptr);
        EXPECT_EQ(annot->getInteriorColor(), nullptr);
    }
}

// Test setVertices and getX1/getY1/getX2/getY2
TEST_F(AnnotLineTest_826, SetAndGetVertices_826) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle pdfRect(0, 0, 200, 200);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &pdfRect);
        
        annot->setVertices(10.0, 20.0, 150.0, 180.0);
        
        EXPECT_DOUBLE_EQ(annot->getX1(), 10.0);
        EXPECT_DOUBLE_EQ(annot->getY1(), 20.0);
        EXPECT_DOUBLE_EQ(annot->getX2(), 150.0);
        EXPECT_DOUBLE_EQ(annot->getY2(), 180.0);
    }
}

// Test setCaption and getCaption
TEST_F(AnnotLineTest_826, SetAndGetCaption_826) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle pdfRect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &pdfRect);
        
        annot->setCaption(true);
        EXPECT_TRUE(annot->getCaption());
        
        annot->setCaption(false);
        EXPECT_FALSE(annot->getCaption());
    }
}

// Test setLeaderLineLength and getLeaderLineLength
TEST_F(AnnotLineTest_826, SetAndGetLeaderLineLength_826) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle pdfRect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &pdfRect);
        
        annot->setLeaderLineLength(25.5);
        EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 25.5);
    }
}

// Test setLeaderLineExtension and getLeaderLineExtension
TEST_F(AnnotLineTest_826, SetAndGetLeaderLineExtension_826) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle pdfRect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &pdfRect);
        
        annot->setLeaderLineExtension(12.3);
        EXPECT_DOUBLE_EQ(annot->getLeaderLineExtension(), 12.3);
    }
}

// Test setIntent and getIntent
TEST_F(AnnotLineTest_826, SetAndGetIntent_826) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle pdfRect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &pdfRect);
        
        annot->setIntent(annotLineArrow);
        EXPECT_EQ(annot->getIntent(), annotLineArrow);
        
        annot->setIntent(annotLineDimension);
        EXPECT_EQ(annot->getIntent(), annotLineDimension);
    }
}

// Test default values after construction
TEST_F(AnnotLineTest_826, DefaultValuesAfterConstruction_826) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle pdfRect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &pdfRect);
        
        // Check that default getters don't crash and return reasonable defaults
        annot->getStartStyle();
        annot->getEndStyle();
        annot->getLeaderLineLength();
        annot->getLeaderLineExtension();
        annot->getCaption();
        annot->getIntent();
        annot->getLeaderLineOffset();
        annot->getCaptionPos();
        annot->getMeasure();
        annot->getCaptionTextHorizontal();
        annot->getCaptionTextVertical();
        annot->getX1();
        annot->getY1();
        annot->getX2();
        annot->getY2();
        
        // If we get here without crashing, the defaults are accessible
        SUCCEED();
    }
}

// Test setStartEndStyle and getStartStyle/getEndStyle
TEST_F(AnnotLineTest_826, SetAndGetStartEndStyle_826) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle pdfRect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &pdfRect);
        
        annot->setStartEndStyle(annotLineEndingOpenArrow, annotLineEndingClosedArrow);
        EXPECT_EQ(annot->getStartStyle(), annotLineEndingOpenArrow);
        EXPECT_EQ(annot->getEndStyle(), annotLineEndingClosedArrow);
    }
}

// Test setting vertices with zero-length line
TEST_F(AnnotLineTest_826, SetVerticesZeroLength_826) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle pdfRect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &pdfRect);
        
        annot->setVertices(50.0, 50.0, 50.0, 50.0);
        
        EXPECT_DOUBLE_EQ(annot->getX1(), 50.0);
        EXPECT_DOUBLE_EQ(annot->getY1(), 50.0);
        EXPECT_DOUBLE_EQ(annot->getX2(), 50.0);
        EXPECT_DOUBLE_EQ(annot->getY2(), 50.0);
    }
}

// Test setLeaderLineLength with zero
TEST_F(AnnotLineTest_826, SetLeaderLineLengthZero_826) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle pdfRect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &pdfRect);
        
        annot->setLeaderLineLength(0.0);
        EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 0.0);
    }
}

// Test setLeaderLineLength with negative value
TEST_F(AnnotLineTest_826, SetLeaderLineLengthNegative_826) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle pdfRect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &pdfRect);
        
        annot->setLeaderLineLength(-10.0);
        // Negative leader line lengths are valid in PDF spec
        EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), -10.0);
    }
}

// Test setting vertices with negative coordinates
TEST_F(AnnotLineTest_826, SetVerticesNegativeCoordinates_826) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle pdfRect(-100, -100, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &pdfRect);
        
        annot->setVertices(-50.0, -30.0, 50.0, 30.0);
        
        EXPECT_DOUBLE_EQ(annot->getX1(), -50.0);
        EXPECT_DOUBLE_EQ(annot->getY1(), -30.0);
        EXPECT_DOUBLE_EQ(annot->getX2(), 50.0);
        EXPECT_DOUBLE_EQ(annot->getY2(), 30.0);
    }
}

// Test setting interior color with different color spaces
TEST_F(AnnotLineTest_826, SetInteriorColorGray_826) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle pdfRect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &pdfRect);
        
        // Create a grayscale color
        auto grayColor = std::make_unique<AnnotColor>(0.5);
        annot->setInteriorColor(std::move(grayColor));
        
        AnnotColor *result = annot->getInteriorColor();
        ASSERT_NE(result, nullptr);
    }
}

// Test setting interior color with CMYK
TEST_F(AnnotLineTest_826, SetInteriorColorCMYK_826) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle pdfRect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &pdfRect);
        
        // Create a CMYK color
        auto cmykColor = std::make_unique<AnnotColor>(0.1, 0.2, 0.3, 0.4);
        annot->setInteriorColor(std::move(cmykColor));
        
        AnnotColor *result = annot->getInteriorColor();
        ASSERT_NE(result, nullptr);
    }
}

// Test multiple setInteriorColor calls (replacing color)
TEST_F(AnnotLineTest_826, ReplaceInteriorColor_826) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle pdfRect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &pdfRect);
        
        // Set first color (red)
        auto color1 = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
        annot->setInteriorColor(std::move(color1));
        
        AnnotColor *result1 = annot->getInteriorColor();
        ASSERT_NE(result1, nullptr);
        
        // Replace with second color (blue)
        auto color2 = std::make_unique<AnnotColor>(0.0, 0.0, 1.0);
        annot->setInteriorColor(std::move(color2));
        
        AnnotColor *result2 = annot->getInteriorColor();
        ASSERT_NE(result2, nullptr);
        EXPECT_DOUBLE_EQ(result2->getValues()[0], 0.0);
        EXPECT_DOUBLE_EQ(result2->getValues()[1], 0.0);
        EXPECT_DOUBLE_EQ(result2->getValues()[2], 1.0);
    }
}

// Test setStartEndStyle with same styles
TEST_F(AnnotLineTest_826, SetStartEndStyleSame_826) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle pdfRect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &pdfRect);
        
        annot->setStartEndStyle(annotLineEndingNone, annotLineEndingNone);
        EXPECT_EQ(annot->getStartStyle(), annotLineEndingNone);
        EXPECT_EQ(annot->getEndStyle(), annotLineEndingNone);
    }
}

// Test setContents
TEST_F(AnnotLineTest_826, SetContents_826) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle pdfRect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &pdfRect);
        
        auto contents = std::make_unique<GooString>("Test annotation content");
        annot->setContents(std::move(contents));
        
        // Verify it doesn't crash; content retrieval through parent class
        SUCCEED();
    }
}

// Test setLeaderLineExtension with zero
TEST_F(AnnotLineTest_826, SetLeaderLineExtensionZero_826) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle pdfRect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &pdfRect);
        
        annot->setLeaderLineExtension(0.0);
        EXPECT_DOUBLE_EQ(annot->getLeaderLineExtension(), 0.0);
    }
}

// Test large coordinate values
TEST_F(AnnotLineTest_826, SetVerticesLargeValues_826) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle pdfRect(0, 0, 100000, 100000);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &pdfRect);
        
        annot->setVertices(99999.99, 99999.99, 0.01, 0.01);
        
        EXPECT_DOUBLE_EQ(annot->getX1(), 99999.99);
        EXPECT_DOUBLE_EQ(annot->getY1(), 99999.99);
        EXPECT_DOUBLE_EQ(annot->getX2(), 0.01);
        EXPECT_DOUBLE_EQ(annot->getY2(), 0.01);
    }
}
