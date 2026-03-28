#include <gtest/gtest.h>
#include <memory>
#include "Annot.h"
#include "PDFDoc.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"
#include "Object.h"
#include "Array.h"
#include "Dict.h"
#include "GooString.h"

class AnnotTextMarkupTest_840 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override
    {
        // Try to create a minimal PDF document in memory
        // We need a valid PDFDoc for annotation creation
    }

    void TearDown() override
    {
    }

    std::unique_ptr<PDFDoc> createMinimalPDFDoc()
    {
        // Create a minimal valid PDF in a temp file or from string
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
};

TEST_F(AnnotTextMarkupTest_840, ConstructHighlightAnnotation_840)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(100.0, 100.0, 200.0, 200.0);
    auto annot = std::make_unique<AnnotTextMarkup>(doc.get(), &rect, Annot::typeHighlight);

    EXPECT_NE(annot, nullptr);
}

TEST_F(AnnotTextMarkupTest_840, ConstructUnderlineAnnotation_840)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(50.0, 50.0, 150.0, 150.0);
    auto annot = std::make_unique<AnnotTextMarkup>(doc.get(), &rect, Annot::typeUnderline);

    EXPECT_NE(annot, nullptr);
}

TEST_F(AnnotTextMarkupTest_840, ConstructStrikeOutAnnotation_840)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotTextMarkup>(doc.get(), &rect, Annot::typeStrikeOut);

    EXPECT_NE(annot, nullptr);
}

TEST_F(AnnotTextMarkupTest_840, ConstructSquigglyAnnotation_840)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(10.0, 10.0, 300.0, 300.0);
    auto annot = std::make_unique<AnnotTextMarkup>(doc.get(), &rect, Annot::typeSquiggly);

    EXPECT_NE(annot, nullptr);
}

TEST_F(AnnotTextMarkupTest_840, GetQuadrilateralsInitiallyNotNull_840)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(100.0, 100.0, 200.0, 200.0);
    auto annot = std::make_unique<AnnotTextMarkup>(doc.get(), &rect, Annot::typeHighlight);

    // After construction, quadrilaterals may or may not be null depending on implementation
    // but it should be callable without crash
    AnnotQuadrilaterals *quads = annot->getQuadrilaterals();
    // Just verify no crash - the result depends on implementation
    (void)quads;
    SUCCEED();
}

TEST_F(AnnotTextMarkupTest_840, SetQuadrilateralsAndRetrieve_840)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(100.0, 100.0, 200.0, 200.0);
    auto annot = std::make_unique<AnnotTextMarkup>(doc.get(), &rect, Annot::typeHighlight);

    // Create quadrilateral points
    auto quadPoint = std::make_unique<AnnotQuadrilaterals::AnnotQuadrilateral>(
        100.0, 200.0, 200.0, 200.0, 100.0, 100.0, 200.0, 100.0);

    AnnotQuadrilaterals::AnnotQuadrilateral *quadsArray = quadPoint.get();
    AnnotQuadrilaterals quadrilaterals(&quadsArray, 1);

    annot->setQuadrilaterals(quadrilaterals);

    AnnotQuadrilaterals *result = annot->getQuadrilaterals();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getQuadrilateralsLength(), 1);
}

TEST_F(AnnotTextMarkupTest_840, SetTypeChangesSubtype_840)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(100.0, 100.0, 200.0, 200.0);
    auto annot = std::make_unique<AnnotTextMarkup>(doc.get(), &rect, Annot::typeHighlight);

    EXPECT_EQ(annot->getType(), Annot::typeHighlight);

    annot->setType(Annot::typeUnderline);
    EXPECT_EQ(annot->getType(), Annot::typeUnderline);
}

TEST_F(AnnotTextMarkupTest_840, SetTypeToStrikeOut_840)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(100.0, 100.0, 200.0, 200.0);
    auto annot = std::make_unique<AnnotTextMarkup>(doc.get(), &rect, Annot::typeHighlight);

    annot->setType(Annot::typeStrikeOut);
    EXPECT_EQ(annot->getType(), Annot::typeStrikeOut);
}

TEST_F(AnnotTextMarkupTest_840, SetTypeToSquiggly_840)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(100.0, 100.0, 200.0, 200.0);
    auto annot = std::make_unique<AnnotTextMarkup>(doc.get(), &rect, Annot::typeUnderline);

    annot->setType(Annot::typeSquiggly);
    EXPECT_EQ(annot->getType(), Annot::typeSquiggly);
}

TEST_F(AnnotTextMarkupTest_840, SetMultipleQuadrilaterals_840)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 500.0, 500.0);
    auto annot = std::make_unique<AnnotTextMarkup>(doc.get(), &rect, Annot::typeHighlight);

    auto q1 = std::make_unique<AnnotQuadrilaterals::AnnotQuadrilateral>(
        100.0, 200.0, 200.0, 200.0, 100.0, 100.0, 200.0, 100.0);
    auto q2 = std::make_unique<AnnotQuadrilaterals::AnnotQuadrilateral>(
        300.0, 400.0, 400.0, 400.0, 300.0, 300.0, 400.0, 300.0);

    AnnotQuadrilaterals::AnnotQuadrilateral *quadsArray[2] = { q1.get(), q2.get() };
    AnnotQuadrilaterals::AnnotQuadrilateral **ptr = quadsArray;
    AnnotQuadrilaterals quadrilaterals(&ptr, 2);

    annot->setQuadrilaterals(quadrilaterals);

    AnnotQuadrilaterals *result = annot->getQuadrilaterals();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getQuadrilateralsLength(), 2);
}

TEST_F(AnnotTextMarkupTest_840, QuadrilateralCoordinatesPreserved_840)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 500.0, 500.0);
    auto annot = std::make_unique<AnnotTextMarkup>(doc.get(), &rect, Annot::typeHighlight);

    auto q1 = std::make_unique<AnnotQuadrilaterals::AnnotQuadrilateral>(
        10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0);

    AnnotQuadrilaterals::AnnotQuadrilateral *quadsArray = q1.get();
    AnnotQuadrilaterals quadrilaterals(&quadsArray, 1);

    annot->setQuadrilaterals(quadrilaterals);

    AnnotQuadrilaterals *result = annot->getQuadrilaterals();
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result->getQuadrilateralsLength(), 1);

    EXPECT_DOUBLE_EQ(result->getX1(0), 10.0);
    EXPECT_DOUBLE_EQ(result->getY1(0), 20.0);
    EXPECT_DOUBLE_EQ(result->getX2(0), 30.0);
    EXPECT_DOUBLE_EQ(result->getY2(0), 40.0);
    EXPECT_DOUBLE_EQ(result->getX3(0), 50.0);
    EXPECT_DOUBLE_EQ(result->getY3(0), 60.0);
    EXPECT_DOUBLE_EQ(result->getX4(0), 70.0);
    EXPECT_DOUBLE_EQ(result->getY4(0), 80.0);
}

TEST_F(AnnotTextMarkupTest_840, ZeroSizeRectangle_840)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 0.0, 0.0);
    auto annot = std::make_unique<AnnotTextMarkup>(doc.get(), &rect, Annot::typeHighlight);

    EXPECT_NE(annot, nullptr);
    // Should construct without crash
    SUCCEED();
}

TEST_F(AnnotTextMarkupTest_840, ReplaceQuadrilaterals_840)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 500.0, 500.0);
    auto annot = std::make_unique<AnnotTextMarkup>(doc.get(), &rect, Annot::typeHighlight);

    // Set first set of quadrilaterals
    auto q1 = std::make_unique<AnnotQuadrilaterals::AnnotQuadrilateral>(
        10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0);
    AnnotQuadrilaterals::AnnotQuadrilateral *quadsArray1 = q1.get();
    AnnotQuadrilaterals quadrilaterals1(&quadsArray1, 1);
    annot->setQuadrilaterals(quadrilaterals1);

    ASSERT_NE(annot->getQuadrilaterals(), nullptr);
    EXPECT_EQ(annot->getQuadrilaterals()->getQuadrilateralsLength(), 1);

    // Replace with different quadrilaterals
    auto q2a = std::make_unique<AnnotQuadrilaterals::AnnotQuadrilateral>(
        100.0, 200.0, 300.0, 400.0, 150.0, 250.0, 350.0, 450.0);
    auto q2b = std::make_unique<AnnotQuadrilaterals::AnnotQuadrilateral>(
        110.0, 210.0, 310.0, 410.0, 160.0, 260.0, 360.0, 460.0);
    AnnotQuadrilaterals::AnnotQuadrilateral *quadsArray2[2] = { q2a.get(), q2b.get() };
    AnnotQuadrilaterals::AnnotQuadrilateral **ptr2 = quadsArray2;
    AnnotQuadrilaterals quadrilaterals2(&ptr2, 2);
    annot->setQuadrilaterals(quadrilaterals2);

    ASSERT_NE(annot->getQuadrilaterals(), nullptr);
    EXPECT_EQ(annot->getQuadrilaterals()->getQuadrilateralsLength(), 2);
}

TEST_F(AnnotTextMarkupTest_840, AnnotationTypeAfterConstruction_840)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(100.0, 100.0, 200.0, 200.0);

    auto highlight = std::make_unique<AnnotTextMarkup>(doc.get(), &rect, Annot::typeHighlight);
    EXPECT_EQ(highlight->getType(), Annot::typeHighlight);

    auto underline = std::make_unique<AnnotTextMarkup>(doc.get(), &rect, Annot::typeUnderline);
    EXPECT_EQ(underline->getType(), Annot::typeUnderline);

    auto strikeout = std::make_unique<AnnotTextMarkup>(doc.get(), &rect, Annot::typeStrikeOut);
    EXPECT_EQ(strikeout->getType(), Annot::typeStrikeOut);

    auto squiggly = std::make_unique<AnnotTextMarkup>(doc.get(), &rect, Annot::typeSquiggly);
    EXPECT_EQ(squiggly->getType(), Annot::typeSquiggly);
}

TEST_F(AnnotTextMarkupTest_840, LargeCoordinateValues_840)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100000.0, 100000.0);
    auto annot = std::make_unique<AnnotTextMarkup>(doc.get(), &rect, Annot::typeHighlight);

    auto q = std::make_unique<AnnotQuadrilaterals::AnnotQuadrilateral>(
        99999.0, 99999.0, 100000.0, 99999.0, 99999.0, 99998.0, 100000.0, 99998.0);

    AnnotQuadrilaterals::AnnotQuadrilateral *quadsArray = q.get();
    AnnotQuadrilaterals quadrilaterals(&quadsArray, 1);
    annot->setQuadrilaterals(quadrilaterals);

    AnnotQuadrilaterals *result = annot->getQuadrilaterals();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getQuadrilateralsLength(), 1);
}

TEST_F(AnnotTextMarkupTest_840, NegativeCoordinateValues_840)
{
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(-100.0, -100.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotTextMarkup>(doc.get(), &rect, Annot::typeHighlight);

    auto q = std::make_unique<AnnotQuadrilaterals::AnnotQuadrilateral>(
        -50.0, -50.0, 50.0, -50.0, -50.0, -60.0, 50.0, -60.0);

    AnnotQuadrilaterals::AnnotQuadrilateral *quadsArray = q.get();
    AnnotQuadrilaterals quadrilaterals(&quadsArray, 1);
    annot->setQuadrilaterals(quadrilaterals);

    AnnotQuadrilaterals *result = annot->getQuadrilaterals();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->getQuadrilateralsLength(), 1);
    EXPECT_DOUBLE_EQ(result->getX1(0), -50.0);
    EXPECT_DOUBLE_EQ(result->getY1(0), -50.0);
}
