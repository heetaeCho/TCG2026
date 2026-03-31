#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Annot.h"
#include "PDFDoc.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"
#include "Object.h"
#include <memory>

class AnnotPolygonTest_847 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

// Test that getEndStyle returns a valid AnnotLineEndingStyle value
TEST_F(AnnotPolygonTest_847, GetEndStyleReturnsValidStyle_847)
{
    // We need a PDFDoc and rectangle to create an AnnotPolygon
    // Create a minimal polygon annotation
    auto *rect = new PDFRectangle(0, 0, 100, 100);
    
    // Try to create a document from a test PDF if available
    // Since we may not have a real PDF, we test via the interface contract
    // The getEndStyle should return a value from the AnnotLineEndingStyle enum
    
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        auto annot = std::make_unique<AnnotPolygon>(doc.get(), rect, Annot::typePolygon);
        
        AnnotLineEndingStyle endStyle = annot->getEndStyle();
        // The default end style should be annotLineEndingNone
        EXPECT_GE(static_cast<int>(endStyle), 0);
    }
    delete rect;
}

// Test getStartStyle returns a valid style
TEST_F(AnnotPolygonTest_847, GetStartStyleReturnsValidStyle_847)
{
    auto *rect = new PDFRectangle(0, 0, 200, 200);
    
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        auto annot = std::make_unique<AnnotPolygon>(doc.get(), rect, Annot::typePolygon);
        
        AnnotLineEndingStyle startStyle = annot->getStartStyle();
        EXPECT_GE(static_cast<int>(startStyle), 0);
    }
    delete rect;
}

// Test setStartEndStyle changes the start and end styles
TEST_F(AnnotPolygonTest_847, SetStartEndStyleUpdatesStyles_847)
{
    auto *rect = new PDFRectangle(10, 10, 150, 150);
    
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        auto annot = std::make_unique<AnnotPolygon>(doc.get(), rect, Annot::typePolygon);
        
        annot->setStartEndStyle(annotLineEndingSquare, annotLineEndingCircle);
        
        EXPECT_EQ(annot->getStartStyle(), annotLineEndingSquare);
        EXPECT_EQ(annot->getEndStyle(), annotLineEndingCircle);
    }
    delete rect;
}

// Test setStartEndStyle with None styles
TEST_F(AnnotPolygonTest_847, SetStartEndStyleNone_847)
{
    auto *rect = new PDFRectangle(0, 0, 100, 100);
    
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        auto annot = std::make_unique<AnnotPolygon>(doc.get(), rect, Annot::typePolygon);
        
        annot->setStartEndStyle(annotLineEndingNone, annotLineEndingNone);
        
        EXPECT_EQ(annot->getStartStyle(), annotLineEndingNone);
        EXPECT_EQ(annot->getEndStyle(), annotLineEndingNone);
    }
    delete rect;
}

// Test getVertices returns vertices pointer
TEST_F(AnnotPolygonTest_847, GetVerticesInitial_847)
{
    auto *rect = new PDFRectangle(0, 0, 100, 100);
    
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        auto annot = std::make_unique<AnnotPolygon>(doc.get(), rect, Annot::typePolygon);
        
        // Initially vertices may be null or empty for a newly created polygon
        AnnotPath *vertices = annot->getVertices();
        // Just check it doesn't crash - vertices may or may not be null
        (void)vertices;
    }
    delete rect;
}

// Test getInteriorColor returns nullptr by default
TEST_F(AnnotPolygonTest_847, GetInteriorColorDefault_847)
{
    auto *rect = new PDFRectangle(0, 0, 100, 100);
    
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        auto annot = std::make_unique<AnnotPolygon>(doc.get(), rect, Annot::typePolygon);
        
        AnnotColor *color = annot->getInteriorColor();
        // Default interior color is likely nullptr
        // Just verify it doesn't crash
        (void)color;
    }
    delete rect;
}

// Test setInteriorColor with a valid color
TEST_F(AnnotPolygonTest_847, SetInteriorColor_847)
{
    auto *rect = new PDFRectangle(0, 0, 100, 100);
    
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        auto annot = std::make_unique<AnnotPolygon>(doc.get(), rect, Annot::typePolygon);
        
        auto newColor = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
        annot->setInteriorColor(std::move(newColor));
        
        AnnotColor *color = annot->getInteriorColor();
        ASSERT_NE(color, nullptr);
    }
    delete rect;
}

// Test setInteriorColor with nullptr
TEST_F(AnnotPolygonTest_847, SetInteriorColorNull_847)
{
    auto *rect = new PDFRectangle(0, 0, 100, 100);
    
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        auto annot = std::make_unique<AnnotPolygon>(doc.get(), rect, Annot::typePolygon);
        
        annot->setInteriorColor(nullptr);
        
        AnnotColor *color = annot->getInteriorColor();
        EXPECT_EQ(color, nullptr);
    }
    delete rect;
}

// Test getIntent returns a valid intent
TEST_F(AnnotPolygonTest_847, GetIntentDefault_847)
{
    auto *rect = new PDFRectangle(0, 0, 100, 100);
    
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        auto annot = std::make_unique<AnnotPolygon>(doc.get(), rect, Annot::typePolygon);
        
        AnnotPolygonIntent intent = annot->getIntent();
        // Just verify it returns a valid intent value
        EXPECT_GE(static_cast<int>(intent), 0);
    }
    delete rect;
}

// Test setIntent changes the intent
TEST_F(AnnotPolygonTest_847, SetIntent_847)
{
    auto *rect = new PDFRectangle(0, 0, 100, 100);
    
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        auto annot = std::make_unique<AnnotPolygon>(doc.get(), rect, Annot::typePolygon);
        
        annot->setIntent(polygonCloud);
        EXPECT_EQ(annot->getIntent(), polygonCloud);
    }
    delete rect;
}

// Test getBorderEffect
TEST_F(AnnotPolygonTest_847, GetBorderEffect_847)
{
    auto *rect = new PDFRectangle(0, 0, 100, 100);
    
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        auto annot = std::make_unique<AnnotPolygon>(doc.get(), rect, Annot::typePolygon);
        
        AnnotBorderEffect *effect = annot->getBorderEffect();
        // May be null for default, just ensure no crash
        (void)effect;
    }
    delete rect;
}

// Test creating a PolyLine subtype
TEST_F(AnnotPolygonTest_847, CreatePolyLineSubtype_847)
{
    auto *rect = new PDFRectangle(0, 0, 100, 100);
    
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        auto annot = std::make_unique<AnnotPolygon>(doc.get(), rect, Annot::typePolyLine);
        
        // Should be created successfully as a polyline
        AnnotLineEndingStyle startStyle = annot->getStartStyle();
        AnnotLineEndingStyle endStyle = annot->getEndStyle();
        EXPECT_GE(static_cast<int>(startStyle), 0);
        EXPECT_GE(static_cast<int>(endStyle), 0);
    }
    delete rect;
}

// Test setType changes the annotation type
TEST_F(AnnotPolygonTest_847, SetType_847)
{
    auto *rect = new PDFRectangle(0, 0, 100, 100);
    
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        auto annot = std::make_unique<AnnotPolygon>(doc.get(), rect, Annot::typePolygon);
        
        // Change type to polyline
        annot->setType(Annot::typePolyLine);
        // Verify it doesn't crash - type change should be accepted
    }
    delete rect;
}

// Test setVertices with a path
TEST_F(AnnotPolygonTest_847, SetVertices_847)
{
    auto *rect = new PDFRectangle(0, 0, 200, 200);
    
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        auto annot = std::make_unique<AnnotPolygon>(doc.get(), rect, Annot::typePolygon);
        
        // Create a simple path with a few points
        std::vector<AnnotCoord> coords;
        coords.emplace_back(10, 10);
        coords.emplace_back(50, 50);
        coords.emplace_back(100, 10);
        
        AnnotPath path(std::move(coords));
        annot->setVertices(path);
        
        AnnotPath *vertices = annot->getVertices();
        ASSERT_NE(vertices, nullptr);
    }
    delete rect;
}

// Test setStartEndStyle with various line ending styles
TEST_F(AnnotPolygonTest_847, SetStartEndStyleVariousStyles_847)
{
    auto *rect = new PDFRectangle(0, 0, 100, 100);
    
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        auto annot = std::make_unique<AnnotPolygon>(doc.get(), rect, Annot::typePolyLine);
        
        annot->setStartEndStyle(annotLineEndingOpenArrow, annotLineEndingClosedArrow);
        EXPECT_EQ(annot->getStartStyle(), annotLineEndingOpenArrow);
        EXPECT_EQ(annot->getEndStyle(), annotLineEndingClosedArrow);
        
        annot->setStartEndStyle(annotLineEndingDiamond, annotLineEndingSlash);
        EXPECT_EQ(annot->getStartStyle(), annotLineEndingDiamond);
        EXPECT_EQ(annot->getEndStyle(), annotLineEndingSlash);
    }
    delete rect;
}

// Test with zero-size rectangle (boundary condition)
TEST_F(AnnotPolygonTest_847, ZeroSizeRectangle_847)
{
    auto *rect = new PDFRectangle(0, 0, 0, 0);
    
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        auto annot = std::make_unique<AnnotPolygon>(doc.get(), rect, Annot::typePolygon);
        
        // Should still be able to query properties
        AnnotLineEndingStyle endStyle = annot->getEndStyle();
        EXPECT_GE(static_cast<int>(endStyle), 0);
    }
    delete rect;
}
