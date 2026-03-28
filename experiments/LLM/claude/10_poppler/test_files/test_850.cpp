#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler/Annot.h"
#include "poppler/PDFDoc.h"
#include "poppler/Object.h"
#include "poppler/PDFDocFactory.h"
#include "poppler/GlobalParams.h"

#include <memory>
#include <string>

class AnnotPolygonTest_850 : public ::testing::Test {
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

// Test that creating a Polygon annotation with AnnotSubtype::Polygon works
TEST_F(AnnotPolygonTest_850, CreatePolygonAnnotation_850)
{
    // Create a minimal PDF document in memory
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    ASSERT_NE(annot, nullptr);
    // Vertices should be accessible (may be empty initially)
    // Intent should have some default value
}

// Test that creating a Polyline annotation with AnnotSubtype::PolyLine works
TEST_F(AnnotPolygonTest_850, CreatePolyLineAnnotation_850)
{
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10, 10, 200, 200);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolyLine);

    ASSERT_NE(annot, nullptr);
}

// Test getIntent returns the intent value
TEST_F(AnnotPolygonTest_850, GetIntentReturnsValue_850)
{
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    // getIntent should return some valid AnnotPolygonIntent value
    AnnotPolygon::AnnotPolygonIntent intent = annot->getIntent();
    // Just verify it's a valid enum value (no crash)
    SUCCEED();
}

// Test setIntent and then getIntent
TEST_F(AnnotPolygonTest_850, SetIntentThenGetIntent_850)
{
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    annot->setIntent(AnnotPolygon::polygonCloud);
    EXPECT_EQ(annot->getIntent(), AnnotPolygon::polygonCloud);
}

// Test setIntent with polygonDimension
TEST_F(AnnotPolygonTest_850, SetIntentPolygonDimension_850)
{
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    annot->setIntent(AnnotPolygon::polygonDimension);
    EXPECT_EQ(annot->getIntent(), AnnotPolygon::polygonDimension);
}

// Test setIntent with polylineDimension
TEST_F(AnnotPolygonTest_850, SetIntentPolylineDimension_850)
{
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolyLine);

    annot->setIntent(AnnotPolygon::polylineDimension);
    EXPECT_EQ(annot->getIntent(), AnnotPolygon::polylineDimension);
}

// Test getVertices on a newly created annotation
TEST_F(AnnotPolygonTest_850, GetVerticesOnNewAnnotation_850)
{
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    // Vertices pointer - may or may not be null on a newly created annotation
    AnnotPath *vertices = annot->getVertices();
    // Just ensure no crash
    SUCCEED();
}

// Test setVertices and getVertices
TEST_F(AnnotPolygonTest_850, SetAndGetVertices_850)
{
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    // Create an AnnotPath with some vertices
    std::vector<AnnotCoord> coords;
    coords.emplace_back(10.0, 20.0);
    coords.emplace_back(30.0, 40.0);
    coords.emplace_back(50.0, 60.0);
    AnnotPath path(coords.data(), coords.size());

    annot->setVertices(path);

    AnnotPath *resultVertices = annot->getVertices();
    ASSERT_NE(resultVertices, nullptr);
    EXPECT_EQ(resultVertices->getCoordsLength(), 3);
}

// Test getStartStyle and getEndStyle on a newly created annotation
TEST_F(AnnotPolygonTest_850, GetStartEndStyleDefaults_850)
{
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolyLine);

    AnnotLineEndingStyle startStyle = annot->getStartStyle();
    AnnotLineEndingStyle endStyle = annot->getEndStyle();

    // Default styles should be annotLineEndingNone
    EXPECT_EQ(startStyle, annotLineEndingNone);
    EXPECT_EQ(endStyle, annotLineEndingNone);
}

// Test setStartEndStyle
TEST_F(AnnotPolygonTest_850, SetStartEndStyle_850)
{
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolyLine);

    annot->setStartEndStyle(annotLineEndingOpenArrow, annotLineEndingClosedArrow);

    EXPECT_EQ(annot->getStartStyle(), annotLineEndingOpenArrow);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingClosedArrow);
}

// Test getInteriorColor on a new annotation (should be null by default)
TEST_F(AnnotPolygonTest_850, GetInteriorColorDefault_850)
{
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    AnnotColor *color = annot->getInteriorColor();
    // Default interior color may be null
    // Just checking no crash
    SUCCEED();
}

// Test setInteriorColor
TEST_F(AnnotPolygonTest_850, SetInteriorColor_850)
{
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    auto newColor = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    annot->setInteriorColor(std::move(newColor));

    AnnotColor *color = annot->getInteriorColor();
    ASSERT_NE(color, nullptr);
}

// Test setInteriorColor with nullptr to clear it
TEST_F(AnnotPolygonTest_850, SetInteriorColorNull_850)
{
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    // First set a color
    auto newColor = std::make_unique<AnnotColor>(0.0, 1.0, 0.0);
    annot->setInteriorColor(std::move(newColor));
    ASSERT_NE(annot->getInteriorColor(), nullptr);

    // Now set to null
    annot->setInteriorColor(nullptr);
    EXPECT_EQ(annot->getInteriorColor(), nullptr);
}

// Test getBorderEffect on a new annotation
TEST_F(AnnotPolygonTest_850, GetBorderEffectDefault_850)
{
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    // Border effect may or may not be set by default
    AnnotBorderEffect *be = annot->getBorderEffect();
    // No crash expected
    SUCCEED();
}

// Test setType to change from Polygon to PolyLine
TEST_F(AnnotPolygonTest_850, SetTypeChangeSubtype_850)
{
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    annot->setType(Annot::typePolyLine);
    EXPECT_EQ(annot->getType(), Annot::typePolyLine);
}

// Test setType from PolyLine to Polygon
TEST_F(AnnotPolygonTest_850, SetTypePolyLineToPolygon_850)
{
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolyLine);

    annot->setType(Annot::typePolygon);
    EXPECT_EQ(annot->getType(), Annot::typePolygon);
}

// Test setting multiple intents consecutively
TEST_F(AnnotPolygonTest_850, SetIntentMultipleTimes_850)
{
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    annot->setIntent(AnnotPolygon::polygonCloud);
    EXPECT_EQ(annot->getIntent(), AnnotPolygon::polygonCloud);

    annot->setIntent(AnnotPolygon::polygonDimension);
    EXPECT_EQ(annot->getIntent(), AnnotPolygon::polygonDimension);

    annot->setIntent(AnnotPolygon::polylineDimension);
    EXPECT_EQ(annot->getIntent(), AnnotPolygon::polylineDimension);
}

// Test setting vertices with a single point
TEST_F(AnnotPolygonTest_850, SetVerticesSinglePoint_850)
{
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    std::vector<AnnotCoord> coords;
    coords.emplace_back(50.0, 50.0);
    AnnotPath path(coords.data(), coords.size());

    annot->setVertices(path);

    AnnotPath *resultVertices = annot->getVertices();
    ASSERT_NE(resultVertices, nullptr);
    EXPECT_EQ(resultVertices->getCoordsLength(), 1);
}

// Test setting various start/end styles
TEST_F(AnnotPolygonTest_850, SetVariousLineEndingStyles_850)
{
    GooString *uri = new GooString("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*uri));
    delete uri;

    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolyLine);

    annot->setStartEndStyle(annotLineEndingSquare, annotLineEndingCircle);
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingSquare);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingCircle);

    annot->setStartEndStyle(annotLineEndingDiamond, annotLineEndingButt);
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingDiamond);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingButt);
}
