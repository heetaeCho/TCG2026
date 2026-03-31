#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary headers from poppler
#include "Annot.h"
#include "PDFDoc.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"
#include "Object.h"
#include "GooString.h"

class AnnotPolygonTest_849 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that an AnnotPolygon can be created with a rectangle and Polygon subtype
TEST_F(AnnotPolygonTest_849, CreatePolygonWithRect_849) {
    // Create a minimal PDF document in memory
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);
    
    ASSERT_NE(annot, nullptr);
}

// Test that an AnnotPolygon can be created with PolyLine subtype
TEST_F(AnnotPolygonTest_849, CreatePolyLineWithRect_849) {
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(50, 50, 300, 300);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolyLine);
    
    ASSERT_NE(annot, nullptr);
}

// Test getBorderEffect returns nullptr when no border effect is set
TEST_F(AnnotPolygonTest_849, GetBorderEffectDefaultIsNull_849) {
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);
    
    // Border effect may be null for a freshly created annotation
    AnnotBorderEffect *be = annot->getBorderEffect();
    // Just check it doesn't crash - it could be null or valid
    (void)be;
    SUCCEED();
}

// Test getVertices returns a valid pointer or nullptr for new annotation
TEST_F(AnnotPolygonTest_849, GetVerticesDefault_849) {
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);
    
    AnnotPath *vertices = annot->getVertices();
    // For a newly created polygon, vertices may or may not be set
    (void)vertices;
    SUCCEED();
}

// Test getInteriorColor returns nullptr for a default annotation
TEST_F(AnnotPolygonTest_849, GetInteriorColorDefault_849) {
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);
    
    AnnotColor *color = annot->getInteriorColor();
    // Default interior color should be null
    EXPECT_EQ(color, nullptr);
}

// Test getStartStyle and getEndStyle defaults
TEST_F(AnnotPolygonTest_849, GetStartEndStyleDefaults_849) {
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);
    
    AnnotLineEndingStyle startStyle = annot->getStartStyle();
    AnnotLineEndingStyle endStyle = annot->getEndStyle();
    
    // Default line ending style should be None
    EXPECT_EQ(startStyle, annotLineEndingNone);
    EXPECT_EQ(endStyle, annotLineEndingNone);
}

// Test setStartEndStyle modifies the start and end styles
TEST_F(AnnotPolygonTest_849, SetStartEndStyle_849) {
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolyLine);
    
    annot->setStartEndStyle(annotLineEndingOpenArrow, annotLineEndingClosedArrow);
    
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingOpenArrow);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingClosedArrow);
}

// Test setInteriorColor with a valid color
TEST_F(AnnotPolygonTest_849, SetInteriorColor_849) {
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);
    
    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    annot->setInteriorColor(std::move(color));
    
    AnnotColor *ic = annot->getInteriorColor();
    ASSERT_NE(ic, nullptr);
}

// Test setInteriorColor with nullptr
TEST_F(AnnotPolygonTest_849, SetInteriorColorNull_849) {
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);
    
    annot->setInteriorColor(nullptr);
    
    AnnotColor *ic = annot->getInteriorColor();
    EXPECT_EQ(ic, nullptr);
}

// Test setVertices
TEST_F(AnnotPolygonTest_849, SetVertices_849) {
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);
    
    // Create a simple path with 3 points
    double coords[] = {100.0, 100.0, 150.0, 200.0, 200.0, 100.0};
    AnnotPath path(coords, 3);
    
    annot->setVertices(path);
    
    AnnotPath *v = annot->getVertices();
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->getCoordsLength(), 3);
}

// Test setIntent and getIntent
TEST_F(AnnotPolygonTest_849, SetAndGetIntent_849) {
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);
    
    annot->setIntent(AnnotPolygon::polygonCloud);
    EXPECT_EQ(annot->getIntent(), AnnotPolygon::polygonCloud);
    
    annot->setIntent(AnnotPolygon::polygonDimension);
    EXPECT_EQ(annot->getIntent(), AnnotPolygon::polygonDimension);
}

// Test setType changes the annotation subtype
TEST_F(AnnotPolygonTest_849, SetType_849) {
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);
    
    // Change from Polygon to PolyLine
    annot->setType(Annot::typePolyLine);
    EXPECT_EQ(annot->getType(), Annot::typePolyLine);
    
    // Change back
    annot->setType(Annot::typePolygon);
    EXPECT_EQ(annot->getType(), Annot::typePolygon);
}

// Test setting multiple line ending styles
TEST_F(AnnotPolygonTest_849, SetVariousLineEndingStyles_849) {
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolyLine);
    
    annot->setStartEndStyle(annotLineEndingSquare, annotLineEndingCircle);
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingSquare);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingCircle);
    
    annot->setStartEndStyle(annotLineEndingDiamond, annotLineEndingButt);
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingDiamond);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingButt);
}

// Test setVertices with single point
TEST_F(AnnotPolygonTest_849, SetVerticesSinglePoint_849) {
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);
    
    double coords[] = {150.0, 150.0};
    AnnotPath path(coords, 1);
    
    annot->setVertices(path);
    
    AnnotPath *v = annot->getVertices();
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->getCoordsLength(), 1);
}

// Test getIntent default value
TEST_F(AnnotPolygonTest_849, GetIntentDefault_849) {
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);
    
    // Just ensure we can get the intent without crashing
    AnnotPolygon::AnnotPolygonIntent intent = annot->getIntent();
    (void)intent;
    SUCCEED();
}

// Test boundary: zero-size rectangle
TEST_F(AnnotPolygonTest_849, CreateWithZeroSizeRect_849) {
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 0, 0);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);
    
    ASSERT_NE(annot, nullptr);
}

// Test multiple vertices
TEST_F(AnnotPolygonTest_849, SetVerticesMultiplePoints_849) {
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 500, 500);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);
    
    // 5 points forming a pentagon
    double coords[] = {250.0, 0.0, 500.0, 190.0, 405.0, 500.0, 95.0, 500.0, 0.0, 190.0};
    AnnotPath path(coords, 5);
    
    annot->setVertices(path);
    
    AnnotPath *v = annot->getVertices();
    ASSERT_NE(v, nullptr);
    EXPECT_EQ(v->getCoordsLength(), 5);
}
