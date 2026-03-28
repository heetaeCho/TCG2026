#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary headers from the poppler project
#include "Annot.h"
#include "PDFDoc.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"
#include "Object.h"
#include "GooString.h"

class AnnotPolygonTest_845 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override
    {
        // We'll create AnnotPolygon objects in individual tests as needed
    }

    void TearDown() override
    {
    }
};

// Test that creating an AnnotPolygon with a rectangle and Polygon subtype works
TEST_F(AnnotPolygonTest_845, ConstructWithRectAndPolygonSubtype_845)
{
    // Create a minimal PDF in memory to get a valid PDFDoc
    GooString *filename = new GooString(TESTDATADIR "/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*filename));
    delete filename;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    ASSERT_NE(annot, nullptr);
}

// Test that creating an AnnotPolygon with PolyLine subtype works
TEST_F(AnnotPolygonTest_845, ConstructWithRectAndPolyLineSubtype_845)
{
    GooString *filename = new GooString(TESTDATADIR "/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*filename));
    delete filename;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    PDFRectangle rect(10, 20, 200, 300);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolyLine);

    ASSERT_NE(annot, nullptr);
}

// Test getVertices returns non-null after construction
TEST_F(AnnotPolygonTest_845, GetVerticesAfterConstruction_845)
{
    GooString *filename = new GooString(TESTDATADIR "/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*filename));
    delete filename;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    // After default construction, vertices may or may not be set
    // This tests the getter doesn't crash
    AnnotPath *vertices = annot->getVertices();
    // vertices could be nullptr for a freshly constructed annotation without path data
}

// Test setVertices and then getVertices
TEST_F(AnnotPolygonTest_845, SetAndGetVertices_845)
{
    GooString *filename = new GooString(TESTDATADIR "/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*filename));
    delete filename;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    // Create an AnnotPath with some coordinates
    std::vector<double> coords = {10, 20, 30, 40, 50, 60};
    AnnotPath path(coords.data(), 0, coords.size());

    annot->setVertices(path);

    AnnotPath *retrievedVertices = annot->getVertices();
    ASSERT_NE(retrievedVertices, nullptr);
    EXPECT_EQ(retrievedVertices->getCoordsLength(), 3);
}

// Test getInteriorColor returns nullptr by default
TEST_F(AnnotPolygonTest_845, GetInteriorColorDefaultIsNull_845)
{
    GooString *filename = new GooString(TESTDATADIR "/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*filename));
    delete filename;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    // Interior color may be nullptr by default
    AnnotColor *color = annot->getInteriorColor();
    // Just verify it doesn't crash; color could be nullptr
}

// Test setInteriorColor and getInteriorColor
TEST_F(AnnotPolygonTest_845, SetAndGetInteriorColor_845)
{
    GooString *filename = new GooString(TESTDATADIR "/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*filename));
    delete filename;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    auto newColor = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    annot->setInteriorColor(std::move(newColor));

    AnnotColor *color = annot->getInteriorColor();
    ASSERT_NE(color, nullptr);
}

// Test getStartStyle and getEndStyle defaults
TEST_F(AnnotPolygonTest_845, GetStartEndStyleDefaults_845)
{
    GooString *filename = new GooString(TESTDATADIR "/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*filename));
    delete filename;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolyLine);

    // Default line ending styles should be annotLineEndingNone
    AnnotLineEndingStyle startStyle = annot->getStartStyle();
    AnnotLineEndingStyle endStyle = annot->getEndStyle();

    EXPECT_EQ(startStyle, annotLineEndingNone);
    EXPECT_EQ(endStyle, annotLineEndingNone);
}

// Test setStartEndStyle
TEST_F(AnnotPolygonTest_845, SetStartEndStyle_845)
{
    GooString *filename = new GooString(TESTDATADIR "/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*filename));
    delete filename;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolyLine);

    annot->setStartEndStyle(annotLineEndingOpenArrow, annotLineEndingClosedArrow);

    EXPECT_EQ(annot->getStartStyle(), annotLineEndingOpenArrow);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingClosedArrow);
}

// Test setIntent and getIntent
TEST_F(AnnotPolygonTest_845, SetAndGetIntent_845)
{
    GooString *filename = new GooString(TESTDATADIR "/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*filename));
    delete filename;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    annot->setIntent(AnnotPolygon::polygonCloud);
    EXPECT_EQ(annot->getIntent(), AnnotPolygon::polygonCloud);

    annot->setIntent(AnnotPolygon::polylineDimension);
    EXPECT_EQ(annot->getIntent(), AnnotPolygon::polylineDimension);
}

// Test getBorderEffect returns a value (possibly null)
TEST_F(AnnotPolygonTest_845, GetBorderEffect_845)
{
    GooString *filename = new GooString(TESTDATADIR "/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*filename));
    delete filename;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    // Just verify this doesn't crash
    AnnotBorderEffect *effect = annot->getBorderEffect();
    // effect may be nullptr for default constructed annotation
}

// Test setType changes the annotation subtype
TEST_F(AnnotPolygonTest_845, SetType_845)
{
    GooString *filename = new GooString(TESTDATADIR "/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*filename));
    delete filename;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    EXPECT_EQ(annot->getType(), Annot::typePolygon);

    annot->setType(Annot::typePolyLine);
    EXPECT_EQ(annot->getType(), Annot::typePolyLine);
}

// Test setting vertices with an empty path
TEST_F(AnnotPolygonTest_845, SetVerticesEmptyPath_845)
{
    GooString *filename = new GooString(TESTDATADIR "/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*filename));
    delete filename;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    // Create an empty path
    AnnotPath emptyPath(nullptr, 0, 0);
    annot->setVertices(emptyPath);

    AnnotPath *vertices = annot->getVertices();
    // Should handle empty path gracefully
    if (vertices != nullptr) {
        EXPECT_EQ(vertices->getCoordsLength(), 0);
    }
}

// Test setting vertices with a single point
TEST_F(AnnotPolygonTest_845, SetVerticesSinglePoint_845)
{
    GooString *filename = new GooString(TESTDATADIR "/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*filename));
    delete filename;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    std::vector<double> coords = {50, 50};
    AnnotPath path(coords.data(), 0, coords.size());

    annot->setVertices(path);

    AnnotPath *vertices = annot->getVertices();
    ASSERT_NE(vertices, nullptr);
    EXPECT_EQ(vertices->getCoordsLength(), 1);
}

// Test setting vertices with many points
TEST_F(AnnotPolygonTest_845, SetVerticesManyPoints_845)
{
    GooString *filename = new GooString(TESTDATADIR "/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*filename));
    delete filename;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    PDFRectangle rect(0, 0, 500, 500);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    // Create a path with many points
    std::vector<double> coords;
    for (int i = 0; i < 200; i++) {
        coords.push_back(i * 1.0);
        coords.push_back(i * 2.0);
    }
    AnnotPath path(coords.data(), 0, coords.size());

    annot->setVertices(path);

    AnnotPath *vertices = annot->getVertices();
    ASSERT_NE(vertices, nullptr);
    EXPECT_EQ(vertices->getCoordsLength(), 100);
}

// Test setInteriorColor with nullptr to clear it
TEST_F(AnnotPolygonTest_845, SetInteriorColorToNull_845)
{
    GooString *filename = new GooString(TESTDATADIR "/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*filename));
    delete filename;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    // First set a color
    auto newColor = std::make_unique<AnnotColor>(0.0, 1.0, 0.0);
    annot->setInteriorColor(std::move(newColor));
    ASSERT_NE(annot->getInteriorColor(), nullptr);

    // Now set to nullptr
    annot->setInteriorColor(nullptr);
    EXPECT_EQ(annot->getInteriorColor(), nullptr);
}

// Test all line ending styles
TEST_F(AnnotPolygonTest_845, SetVariousLineEndingStyles_845)
{
    GooString *filename = new GooString(TESTDATADIR "/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*filename));
    delete filename;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolyLine);

    annot->setStartEndStyle(annotLineEndingSquare, annotLineEndingCircle);
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingSquare);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingCircle);

    annot->setStartEndStyle(annotLineEndingDiamond, annotLineEndingButt);
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingDiamond);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingButt);

    annot->setStartEndStyle(annotLineEndingROpenArrow, annotLineEndingRClosedArrow);
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingROpenArrow);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingRClosedArrow);

    annot->setStartEndStyle(annotLineEndingSlash, annotLineEndingNone);
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingSlash);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingNone);
}

// Test switching between polygon and polyline types
TEST_F(AnnotPolygonTest_845, SwitchBetweenTypes_845)
{
    GooString *filename = new GooString(TESTDATADIR "/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*filename));
    delete filename;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolyLine);

    EXPECT_EQ(annot->getType(), Annot::typePolyLine);

    annot->setType(Annot::typePolygon);
    EXPECT_EQ(annot->getType(), Annot::typePolygon);

    annot->setType(Annot::typePolyLine);
    EXPECT_EQ(annot->getType(), Annot::typePolyLine);
}

// Test that vertices coordinate values are preserved
TEST_F(AnnotPolygonTest_845, VerticesCoordinatesPreserved_845)
{
    GooString *filename = new GooString(TESTDATADIR "/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*filename));
    delete filename;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF";
    }

    PDFRectangle rect(0, 0, 200, 200);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    std::vector<double> coords = {10.5, 20.3, 30.7, 40.1, 50.9, 60.2};
    AnnotPath path(coords.data(), 0, coords.size());
    annot->setVertices(path);

    AnnotPath *vertices = annot->getVertices();
    ASSERT_NE(vertices, nullptr);
    ASSERT_EQ(vertices->getCoordsLength(), 3);

    EXPECT_DOUBLE_EQ(vertices->getX(0), 10.5);
    EXPECT_DOUBLE_EQ(vertices->getY(0), 20.3);
    EXPECT_DOUBLE_EQ(vertices->getX(1), 30.7);
    EXPECT_DOUBLE_EQ(vertices->getY(1), 40.1);
    EXPECT_DOUBLE_EQ(vertices->getX(2), 50.9);
    EXPECT_DOUBLE_EQ(vertices->getY(2), 60.2);
}
