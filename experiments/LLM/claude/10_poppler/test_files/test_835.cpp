#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Annot.h"
#include "PDFDoc.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"
#include "Object.h"
#include "Dict.h"
#include "GooString.h"

class AnnotLineTest_835 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    std::unique_ptr<AnnotLine> createAnnotLineFromRect(PDFDoc *doc, double x1, double y1, double x2, double y2) {
        PDFRectangle rect(x1, y1, x2, y2);
        return std::make_unique<AnnotLine>(doc, &rect);
    }
};

// Test that getCaptionTextVertical returns a value (default behavior)
TEST_F(AnnotLineTest_835, GetCaptionTextVerticalDefault_835) {
    // We need a valid PDFDoc to create an AnnotLine
    // Create a minimal PDF in memory or use a file-based approach
    // For this test, we'll try to create an AnnotLine with a rectangle
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        // getCaptionTextVertical should return a double value
        double val = annot->getCaptionTextVertical();
        // Default value is typically 0.0
        EXPECT_DOUBLE_EQ(val, 0.0);
    }
}

// Test getCaptionTextHorizontal default
TEST_F(AnnotLineTest_835, GetCaptionTextHorizontalDefault_835) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        double val = annot->getCaptionTextHorizontal();
        EXPECT_DOUBLE_EQ(val, 0.0);
    }
}

// Test getLeaderLineLength default
TEST_F(AnnotLineTest_835, GetLeaderLineLengthDefault_835) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        double val = annot->getLeaderLineLength();
        EXPECT_DOUBLE_EQ(val, 0.0);
    }
}

// Test getLeaderLineExtension default
TEST_F(AnnotLineTest_835, GetLeaderLineExtensionDefault_835) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        double val = annot->getLeaderLineExtension();
        EXPECT_DOUBLE_EQ(val, 0.0);
    }
}

// Test getCaption default
TEST_F(AnnotLineTest_835, GetCaptionDefault_835) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        bool val = annot->getCaption();
        EXPECT_FALSE(val);
    }
}

// Test getLeaderLineOffset default
TEST_F(AnnotLineTest_835, GetLeaderLineOffsetDefault_835) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        double val = annot->getLeaderLineOffset();
        EXPECT_DOUBLE_EQ(val, 0.0);
    }
}

// Test getInteriorColor default (should be nullptr)
TEST_F(AnnotLineTest_835, GetInteriorColorDefault_835) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        AnnotColor *color = annot->getInteriorColor();
        EXPECT_EQ(color, nullptr);
    }
}

// Test getMeasure default (should be nullptr)
TEST_F(AnnotLineTest_835, GetMeasureDefault_835) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        Dict *measure = annot->getMeasure();
        EXPECT_EQ(measure, nullptr);
    }
}

// Test setVertices and verify with getX1, getY1, getX2, getY2
TEST_F(AnnotLineTest_835, SetVerticesAndGetCoordinates_835) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 200, 200);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        annot->setVertices(10.0, 20.0, 30.0, 40.0);
        
        EXPECT_DOUBLE_EQ(annot->getX1(), 10.0);
        EXPECT_DOUBLE_EQ(annot->getY1(), 20.0);
        EXPECT_DOUBLE_EQ(annot->getX2(), 30.0);
        EXPECT_DOUBLE_EQ(annot->getY2(), 40.0);
    }
}

// Test setLeaderLineLength and getLeaderLineLength
TEST_F(AnnotLineTest_835, SetAndGetLeaderLineLength_835) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        annot->setLeaderLineLength(15.5);
        EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 15.5);
    }
}

// Test setLeaderLineExtension and getLeaderLineExtension
TEST_F(AnnotLineTest_835, SetAndGetLeaderLineExtension_835) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        annot->setLeaderLineExtension(5.0);
        EXPECT_DOUBLE_EQ(annot->getLeaderLineExtension(), 5.0);
    }
}

// Test setCaption and getCaption
TEST_F(AnnotLineTest_835, SetAndGetCaption_835) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        annot->setCaption(true);
        EXPECT_TRUE(annot->getCaption());
        
        annot->setCaption(false);
        EXPECT_FALSE(annot->getCaption());
    }
}

// Test setIntent and getIntent
TEST_F(AnnotLineTest_835, SetAndGetIntent_835) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        annot->setIntent(annotLineArrow);
        EXPECT_EQ(annot->getIntent(), annotLineArrow);
        
        annot->setIntent(annotLineDimension);
        EXPECT_EQ(annot->getIntent(), annotLineDimension);
    }
}

// Test setVertices with zero coordinates
TEST_F(AnnotLineTest_835, SetVerticesZeroCoordinates_835) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        annot->setVertices(0.0, 0.0, 0.0, 0.0);
        
        EXPECT_DOUBLE_EQ(annot->getX1(), 0.0);
        EXPECT_DOUBLE_EQ(annot->getY1(), 0.0);
        EXPECT_DOUBLE_EQ(annot->getX2(), 0.0);
        EXPECT_DOUBLE_EQ(annot->getY2(), 0.0);
    }
}

// Test setVertices with negative coordinates
TEST_F(AnnotLineTest_835, SetVerticesNegativeCoordinates_835) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(-100, -100, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        annot->setVertices(-50.0, -25.0, 50.0, 25.0);
        
        EXPECT_DOUBLE_EQ(annot->getX1(), -50.0);
        EXPECT_DOUBLE_EQ(annot->getY1(), -25.0);
        EXPECT_DOUBLE_EQ(annot->getX2(), 50.0);
        EXPECT_DOUBLE_EQ(annot->getY2(), 25.0);
    }
}

// Test setLeaderLineLength with zero
TEST_F(AnnotLineTest_835, SetLeaderLineLengthZero_835) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        annot->setLeaderLineLength(0.0);
        EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 0.0);
    }
}

// Test setLeaderLineLength with negative value
TEST_F(AnnotLineTest_835, SetLeaderLineLengthNegative_835) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        annot->setLeaderLineLength(-10.0);
        EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), -10.0);
    }
}

// Test setVertices with large coordinates
TEST_F(AnnotLineTest_835, SetVerticesLargeCoordinates_835) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100000, 100000);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        annot->setVertices(99999.99, 99999.99, 0.01, 0.01);
        
        EXPECT_DOUBLE_EQ(annot->getX1(), 99999.99);
        EXPECT_DOUBLE_EQ(annot->getY1(), 99999.99);
        EXPECT_DOUBLE_EQ(annot->getX2(), 0.01);
        EXPECT_DOUBLE_EQ(annot->getY2(), 0.01);
    }
}

// Test setInteriorColor with a valid color and verify
TEST_F(AnnotLineTest_835, SetInteriorColor_835) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
        annot->setInteriorColor(std::move(color));
        
        AnnotColor *retrievedColor = annot->getInteriorColor();
        EXPECT_NE(retrievedColor, nullptr);
    }
}

// Test setInteriorColor with nullptr
TEST_F(AnnotLineTest_835, SetInteriorColorNull_835) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        annot->setInteriorColor(nullptr);
        
        AnnotColor *retrievedColor = annot->getInteriorColor();
        EXPECT_EQ(retrievedColor, nullptr);
    }
}

// Test setVertices called multiple times - last values should persist
TEST_F(AnnotLineTest_835, SetVerticesMultipleTimes_835) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 200, 200);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        annot->setVertices(10.0, 20.0, 30.0, 40.0);
        annot->setVertices(50.0, 60.0, 70.0, 80.0);
        
        EXPECT_DOUBLE_EQ(annot->getX1(), 50.0);
        EXPECT_DOUBLE_EQ(annot->getY1(), 60.0);
        EXPECT_DOUBLE_EQ(annot->getX2(), 70.0);
        EXPECT_DOUBLE_EQ(annot->getY2(), 80.0);
    }
}

// Test setLeaderLineExtension with zero
TEST_F(AnnotLineTest_835, SetLeaderLineExtensionZero_835) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        annot->setLeaderLineExtension(0.0);
        EXPECT_DOUBLE_EQ(annot->getLeaderLineExtension(), 0.0);
    }
}
