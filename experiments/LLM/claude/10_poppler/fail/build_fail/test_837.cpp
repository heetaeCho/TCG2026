#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// We need to include the necessary headers for AnnotLine and its dependencies
#include "Annot.h"
#include "PDFDoc.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"
#include "Object.h"
#include "GooString.h"

class AnnotLineTest_837 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override
    {
        // We'll create AnnotLine objects using the constructor that takes a PDFDoc and PDFRectangle
        // For that we need a valid PDFDoc. We'll try to create a minimal one or use a test PDF.
    }

    void TearDown() override
    {
    }
};

// Helper to create a minimal PDF document for testing
static std::unique_ptr<PDFDoc> createMinimalPDFDoc()
{
    // Create a minimal valid PDF in memory
    static const char *minimalPDF =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPDF), 0, strlen(minimalPDF), Object(objNull));
    return std::make_unique<PDFDoc>(stream);
}

TEST_F(AnnotLineTest_837, ConstructorWithRect_DefaultCoordinates_837)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(100.0, 200.0, 300.0, 400.0);
    auto line = std::make_unique<AnnotLine>(doc.get(), &rect);

    // After construction with a rect, the line should exist
    ASSERT_NE(line, nullptr);
}

TEST_F(AnnotLineTest_837, SetVertices_GetCoordinates_837)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    auto line = std::make_unique<AnnotLine>(doc.get(), &rect);

    line->setVertices(10.0, 20.0, 30.0, 40.0);

    EXPECT_DOUBLE_EQ(line->getX1(), 10.0);
    EXPECT_DOUBLE_EQ(line->getY1(), 20.0);
    EXPECT_DOUBLE_EQ(line->getX2(), 30.0);
    EXPECT_DOUBLE_EQ(line->getY2(), 40.0);
}

TEST_F(AnnotLineTest_837, SetVertices_ZeroCoordinates_837)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    auto line = std::make_unique<AnnotLine>(doc.get(), &rect);

    line->setVertices(0.0, 0.0, 0.0, 0.0);

    EXPECT_DOUBLE_EQ(line->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(line->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(line->getX2(), 0.0);
    EXPECT_DOUBLE_EQ(line->getY2(), 0.0);
}

TEST_F(AnnotLineTest_837, SetVertices_NegativeCoordinates_837)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(-100.0, -200.0, 100.0, 200.0);
    auto line = std::make_unique<AnnotLine>(doc.get(), &rect);

    line->setVertices(-50.0, -100.0, 50.0, 100.0);

    EXPECT_DOUBLE_EQ(line->getX1(), -50.0);
    EXPECT_DOUBLE_EQ(line->getY1(), -100.0);
    EXPECT_DOUBLE_EQ(line->getX2(), 50.0);
    EXPECT_DOUBLE_EQ(line->getY2(), 100.0);
}

TEST_F(AnnotLineTest_837, SetVertices_LargeCoordinates_837)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100000.0, 100000.0);
    auto line = std::make_unique<AnnotLine>(doc.get(), &rect);

    line->setVertices(99999.0, 99999.0, 0.001, 0.001);

    EXPECT_DOUBLE_EQ(line->getX1(), 99999.0);
    EXPECT_DOUBLE_EQ(line->getY1(), 99999.0);
    EXPECT_DOUBLE_EQ(line->getX2(), 0.001);
    EXPECT_DOUBLE_EQ(line->getY2(), 0.001);
}

TEST_F(AnnotLineTest_837, SetCaption_True_837)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    auto line = std::make_unique<AnnotLine>(doc.get(), &rect);

    line->setCaption(true);
    EXPECT_TRUE(line->getCaption());
}

TEST_F(AnnotLineTest_837, SetCaption_False_837)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    auto line = std::make_unique<AnnotLine>(doc.get(), &rect);

    line->setCaption(false);
    EXPECT_FALSE(line->getCaption());
}

TEST_F(AnnotLineTest_837, SetLeaderLineLength_837)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    auto line = std::make_unique<AnnotLine>(doc.get(), &rect);

    line->setLeaderLineLength(15.5);
    EXPECT_DOUBLE_EQ(line->getLeaderLineLength(), 15.5);
}

TEST_F(AnnotLineTest_837, SetLeaderLineLength_Zero_837)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    auto line = std::make_unique<AnnotLine>(doc.get(), &rect);

    line->setLeaderLineLength(0.0);
    EXPECT_DOUBLE_EQ(line->getLeaderLineLength(), 0.0);
}

TEST_F(AnnotLineTest_837, SetLeaderLineExtension_837)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    auto line = std::make_unique<AnnotLine>(doc.get(), &rect);

    line->setLeaderLineExtension(5.0);
    EXPECT_DOUBLE_EQ(line->getLeaderLineExtension(), 5.0);
}

TEST_F(AnnotLineTest_837, SetLeaderLineExtension_Zero_837)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    auto line = std::make_unique<AnnotLine>(doc.get(), &rect);

    line->setLeaderLineExtension(0.0);
    EXPECT_DOUBLE_EQ(line->getLeaderLineExtension(), 0.0);
}

TEST_F(AnnotLineTest_837, SetIntent_837)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    auto line = std::make_unique<AnnotLine>(doc.get(), &rect);

    line->setIntent(annotLineArrow);
    EXPECT_EQ(line->getIntent(), annotLineArrow);

    line->setIntent(annotLineDimension);
    EXPECT_EQ(line->getIntent(), annotLineDimension);
}

TEST_F(AnnotLineTest_837, SetInteriorColor_Null_837)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    auto line = std::make_unique<AnnotLine>(doc.get(), &rect);

    line->setInteriorColor(nullptr);
    EXPECT_EQ(line->getInteriorColor(), nullptr);
}

TEST_F(AnnotLineTest_837, SetInteriorColor_WithColor_837)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    auto line = std::make_unique<AnnotLine>(doc.get(), &rect);

    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    AnnotColor *colorPtr = color.get();
    line->setInteriorColor(std::move(color));

    AnnotColor *retrievedColor = line->getInteriorColor();
    // The color should be set (not null)
    EXPECT_NE(retrievedColor, nullptr);
}

TEST_F(AnnotLineTest_837, DefaultLeaderLineOffset_837)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    auto line = std::make_unique<AnnotLine>(doc.get(), &rect);

    // Default leader line offset should be 0
    EXPECT_DOUBLE_EQ(line->getLeaderLineOffset(), 0.0);
}

TEST_F(AnnotLineTest_837, DefaultCaptionTextHorizontal_837)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    auto line = std::make_unique<AnnotLine>(doc.get(), &rect);

    EXPECT_DOUBLE_EQ(line->getCaptionTextHorizontal(), 0.0);
}

TEST_F(AnnotLineTest_837, DefaultCaptionTextVertical_837)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    auto line = std::make_unique<AnnotLine>(doc.get(), &rect);

    EXPECT_DOUBLE_EQ(line->getCaptionTextVertical(), 0.0);
}

TEST_F(AnnotLineTest_837, DefaultMeasure_837)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    auto line = std::make_unique<AnnotLine>(doc.get(), &rect);

    EXPECT_EQ(line->getMeasure(), nullptr);
}

TEST_F(AnnotLineTest_837, DefaultCaption_837)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    auto line = std::make_unique<AnnotLine>(doc.get(), &rect);

    // Default caption should be false
    EXPECT_FALSE(line->getCaption());
}

TEST_F(AnnotLineTest_837, SetStartEndStyle_837)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    auto line = std::make_unique<AnnotLine>(doc.get(), &rect);

    line->setStartEndStyle(annotLineEndingOpenArrow, annotLineEndingClosedArrow);
    EXPECT_EQ(line->getStartStyle(), annotLineEndingOpenArrow);
    EXPECT_EQ(line->getEndStyle(), annotLineEndingClosedArrow);
}

TEST_F(AnnotLineTest_837, SetStartEndStyle_None_837)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    auto line = std::make_unique<AnnotLine>(doc.get(), &rect);

    line->setStartEndStyle(annotLineEndingNone, annotLineEndingNone);
    EXPECT_EQ(line->getStartStyle(), annotLineEndingNone);
    EXPECT_EQ(line->getEndStyle(), annotLineEndingNone);
}

TEST_F(AnnotLineTest_837, SetVertices_UpdateMultipleTimes_837)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    auto line = std::make_unique<AnnotLine>(doc.get(), &rect);

    line->setVertices(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(line->getX1(), 1.0);
    EXPECT_DOUBLE_EQ(line->getY1(), 2.0);
    EXPECT_DOUBLE_EQ(line->getX2(), 3.0);
    EXPECT_DOUBLE_EQ(line->getY2(), 4.0);

    // Update vertices again
    line->setVertices(100.0, 200.0, 300.0, 400.0);
    EXPECT_DOUBLE_EQ(line->getX1(), 100.0);
    EXPECT_DOUBLE_EQ(line->getY1(), 200.0);
    EXPECT_DOUBLE_EQ(line->getX2(), 300.0);
    EXPECT_DOUBLE_EQ(line->getY2(), 400.0);
}

TEST_F(AnnotLineTest_837, SetCaption_Toggle_837)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    auto line = std::make_unique<AnnotLine>(doc.get(), &rect);

    line->setCaption(true);
    EXPECT_TRUE(line->getCaption());

    line->setCaption(false);
    EXPECT_FALSE(line->getCaption());

    line->setCaption(true);
    EXPECT_TRUE(line->getCaption());
}

TEST_F(AnnotLineTest_837, SetLeaderLineLength_Negative_837)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    auto line = std::make_unique<AnnotLine>(doc.get(), &rect);

    line->setLeaderLineLength(-10.0);
    EXPECT_DOUBLE_EQ(line->getLeaderLineLength(), -10.0);
}

TEST_F(AnnotLineTest_837, SetContents_837)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    auto line = std::make_unique<AnnotLine>(doc.get(), &rect);

    auto contents = std::make_unique<GooString>("Test annotation content");
    line->setContents(std::move(contents));

    // Verify the contents were set (through getContents inherited from Annot)
    const GooString *retrievedContents = line->getContents();
    ASSERT_NE(retrievedContents, nullptr);
    EXPECT_STREQ(retrievedContents->c_str(), "Test annotation content");
}

TEST_F(AnnotLineTest_837, SetContents_Empty_837)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 612.0, 792.0);
    auto line = std::make_unique<AnnotLine>(doc.get(), &rect);

    auto contents = std::make_unique<GooString>("");
    line->setContents(std::move(contents));

    const GooString *retrievedContents = line->getContents();
    ASSERT_NE(retrievedContents, nullptr);
    EXPECT_STREQ(retrievedContents->c_str(), "");
}

// Test AnnotCoord separately
TEST_F(AnnotLineTest_837, AnnotCoord_DefaultConstructor_837)
{
    AnnotCoord coord;
    EXPECT_DOUBLE_EQ(coord.getX(), 0.0);
    EXPECT_DOUBLE_EQ(coord.getY(), 0.0);
}

TEST_F(AnnotLineTest_837, AnnotCoord_ParameterizedConstructor_837)
{
    AnnotCoord coord(3.14, 2.71);
    EXPECT_DOUBLE_EQ(coord.getX(), 3.14);
    EXPECT_DOUBLE_EQ(coord.getY(), 2.71);
}

TEST_F(AnnotLineTest_837, AnnotCoord_NegativeValues_837)
{
    AnnotCoord coord(-100.5, -200.3);
    EXPECT_DOUBLE_EQ(coord.getX(), -100.5);
    EXPECT_DOUBLE_EQ(coord.getY(), -200.3);
}

TEST_F(AnnotLineTest_837, AnnotCoord_ZeroValues_837)
{
    AnnotCoord coord(0.0, 0.0);
    EXPECT_DOUBLE_EQ(coord.getX(), 0.0);
    EXPECT_DOUBLE_EQ(coord.getY(), 0.0);
}

TEST_F(AnnotLineTest_837, AnnotCoord_LargeValues_837)
{
    AnnotCoord coord(1e10, 1e10);
    EXPECT_DOUBLE_EQ(coord.getX(), 1e10);
    EXPECT_DOUBLE_EQ(coord.getY(), 1e10);
}

TEST_F(AnnotLineTest_837, AnnotCoord_SmallValues_837)
{
    AnnotCoord coord(1e-10, 1e-10);
    EXPECT_DOUBLE_EQ(coord.getX(), 1e-10);
    EXPECT_DOUBLE_EQ(coord.getY(), 1e-10);
}
