#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler/Annot.h"
#include "poppler/PDFDoc.h"
#include "poppler/Object.h"
#include "poppler/PDFDocFactory.h"
#include "poppler/GlobalParams.h"

#include <memory>
#include <string>

class AnnotPolygonTest_846 : public ::testing::Test {
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

    std::unique_ptr<AnnotPolygon> createPolygonAnnot(AnnotSubtype subType = Annot::typePolygon)
    {
        // Create a minimal PDFDoc from a simple PDF in memory
        // We need a valid PDFDoc for annotation creation
        // Using a rectangle for the annotation bounds
        PDFRectangle rect(0, 0, 100, 100);

        // We'll try to create via the constructor that takes a rect
        // This requires a valid PDFDoc; we attempt to create a minimal one
        // If PDFDoc cannot be easily created, we rely on the dict-based constructor
        return nullptr; // placeholder
    }
};

// Test that getStartStyle returns a valid AnnotLineEndingStyle
TEST_F(AnnotPolygonTest_846, GetStartStyleReturnsValidStyle_846)
{
    // Create a minimal PDF in memory to get a PDFDoc
    static const char pdfData[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(10, 10, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    AnnotLineEndingStyle startStyle = annot->getStartStyle();
    // Default start style should be annotLineEndingNone for a newly created polygon
    EXPECT_EQ(startStyle, annotLineEndingNone);
}

// Test that getEndStyle returns a valid AnnotLineEndingStyle
TEST_F(AnnotPolygonTest_846, GetEndStyleReturnsValidStyle_846)
{
    static const char pdfData[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(10, 10, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    AnnotLineEndingStyle endStyle = annot->getEndStyle();
    EXPECT_EQ(endStyle, annotLineEndingNone);
}

// Test setStartEndStyle and verify via getters
TEST_F(AnnotPolygonTest_846, SetStartEndStyleUpdatesStyles_846)
{
    static const char pdfData[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(10, 10, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    annot->setStartEndStyle(annotLineEndingOpenArrow, annotLineEndingClosedArrow);

    EXPECT_EQ(annot->getStartStyle(), annotLineEndingOpenArrow);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingClosedArrow);
}

// Test getInteriorColor returns nullptr by default
TEST_F(AnnotPolygonTest_846, GetInteriorColorDefaultIsNull_846)
{
    static const char pdfData[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(10, 10, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    AnnotColor *interiorColor = annot->getInteriorColor();
    // For a newly created polygon, interior color may be nullptr
    // This tests the default state
    EXPECT_EQ(interiorColor, nullptr);
}

// Test setInteriorColor and then getInteriorColor
TEST_F(AnnotPolygonTest_846, SetInteriorColorUpdatesColor_846)
{
    static const char pdfData[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(10, 10, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    annot->setInteriorColor(std::move(color));

    AnnotColor *interiorColor = annot->getInteriorColor();
    ASSERT_NE(interiorColor, nullptr);
}

// Test getVertices returns something (possibly empty path) for a new annotation
TEST_F(AnnotPolygonTest_846, GetVerticesAfterCreation_846)
{
    static const char pdfData[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(10, 10, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    AnnotPath *vertices = annot->getVertices();
    // Vertices may or may not be null depending on initialization
    // We just verify it doesn't crash
    (void)vertices;
}

// Test getIntent returns default intent
TEST_F(AnnotPolygonTest_846, GetIntentDefaultValue_846)
{
    static const char pdfData[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(10, 10, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    AnnotPolygonIntent intent = annot->getIntent();
    // Just verify it returns a valid intent without crashing
    (void)intent;
}

// Test setIntent and getIntent roundtrip
TEST_F(AnnotPolygonTest_846, SetIntentUpdatesIntent_846)
{
    static const char pdfData[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(10, 10, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    annot->setIntent(polygonCloud);
    EXPECT_EQ(annot->getIntent(), polygonCloud);
}

// Test creating a PolyLine subtype
TEST_F(AnnotPolygonTest_846, CreatePolyLineAnnotation_846)
{
    static const char pdfData[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0, 0, 200, 200);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolyLine);

    // Verify default styles for polyline
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingNone);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingNone);
}

// Test getBorderEffect for default annotation
TEST_F(AnnotPolygonTest_846, GetBorderEffectDefault_846)
{
    static const char pdfData[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(10, 10, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    AnnotBorderEffect *borderEffect = annot->getBorderEffect();
    // May be null for a newly created annotation
    (void)borderEffect;
}

// Test multiple line ending style combinations
TEST_F(AnnotPolygonTest_846, SetVariousLineEndingStyles_846)
{
    static const char pdfData[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(10, 10, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    // Test Diamond and Square
    annot->setStartEndStyle(annotLineEndingDiamond, annotLineEndingSquare);
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingDiamond);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingSquare);

    // Test Circle and Butt
    annot->setStartEndStyle(annotLineEndingCircle, annotLineEndingButt);
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingCircle);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingButt);

    // Test same style for both
    annot->setStartEndStyle(annotLineEndingSlash, annotLineEndingSlash);
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingSlash);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingSlash);
}

// Test setVertices
TEST_F(AnnotPolygonTest_846, SetVerticesUpdatesVertices_846)
{
    static const char pdfData[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(10, 10, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    // Create a path with some vertices
    double coords[] = {10.0, 20.0, 30.0, 40.0, 50.0, 60.0};
    AnnotPath path(coords, 3);
    annot->setVertices(path);

    AnnotPath *retrievedVertices = annot->getVertices();
    ASSERT_NE(retrievedVertices, nullptr);
    EXPECT_EQ(retrievedVertices->getCoordsLength(), 3);
}

// Test setType changes the annotation subtype
TEST_F(AnnotPolygonTest_846, SetTypeChangesSubtype_846)
{
    static const char pdfData[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n183\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(10, 10, 100, 100);
    auto annot = std::make_unique<AnnotPolygon>(doc.get(), &rect, Annot::typePolygon);

    EXPECT_EQ(annot->getType(), Annot::typePolygon);

    annot->setType(Annot::typePolyLine);
    EXPECT_EQ(annot->getType(), Annot::typePolyLine);
}
