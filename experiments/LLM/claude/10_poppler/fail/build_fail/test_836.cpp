#include <gtest/gtest.h>
#include <memory>

#include "Annot.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "PDFDocFactory.h"

class AnnotLineTest_836 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    std::unique_ptr<PDFDoc> createEmptyDoc() {
        // Create a minimal valid PDF in memory
        static const char minimalPDF[] =
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

        auto *stream = new MemStream(const_cast<char *>(minimalPDF), 0, sizeof(minimalPDF) - 1, Object(objNull));
        return std::make_unique<PDFDoc>(stream);
    }
};

TEST_F(AnnotLineTest_836, ConstructWithRect_DefaultCoordinates_836) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    // After construction with a rectangle, coordinates should be set
    // based on the rectangle corners
    double x1 = annot->getX1();
    double y1 = annot->getY1();
    double x2 = annot->getX2();
    double y2 = annot->getY2();

    // The coordinates should correspond to the rectangle
    EXPECT_DOUBLE_EQ(x1, 10.0);
    EXPECT_DOUBLE_EQ(y1, 20.0);
    EXPECT_DOUBLE_EQ(x2, 100.0);
    EXPECT_DOUBLE_EQ(y2, 200.0);
}

TEST_F(AnnotLineTest_836, SetVertices_836) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setVertices(5.0, 10.0, 50.0, 80.0);

    EXPECT_DOUBLE_EQ(annot->getX1(), 5.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), 10.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), 50.0);
    EXPECT_DOUBLE_EQ(annot->getY2(), 80.0);
}

TEST_F(AnnotLineTest_836, SetVertices_NegativeCoordinates_836) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(-100.0, -100.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setVertices(-50.0, -25.0, 50.0, 25.0);

    EXPECT_DOUBLE_EQ(annot->getX1(), -50.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), -25.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), 50.0);
    EXPECT_DOUBLE_EQ(annot->getY2(), 25.0);
}

TEST_F(AnnotLineTest_836, SetVertices_ZeroCoordinates_836) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setVertices(0.0, 0.0, 0.0, 0.0);

    EXPECT_DOUBLE_EQ(annot->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), 0.0);
    EXPECT_DOUBLE_EQ(annot->getY2(), 0.0);
}

TEST_F(AnnotLineTest_836, SetVertices_LargeCoordinates_836) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 1e6, 1e6);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setVertices(1e6, 1e6, -1e6, -1e6);

    EXPECT_DOUBLE_EQ(annot->getX1(), 1e6);
    EXPECT_DOUBLE_EQ(annot->getY1(), 1e6);
    EXPECT_DOUBLE_EQ(annot->getX2(), -1e6);
    EXPECT_DOUBLE_EQ(annot->getY2(), -1e6);
}

TEST_F(AnnotLineTest_836, DefaultCaption_836) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    // Default caption should be false
    EXPECT_FALSE(annot->getCaption());
}

TEST_F(AnnotLineTest_836, SetCaptionTrue_836) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setCaption(true);
    EXPECT_TRUE(annot->getCaption());
}

TEST_F(AnnotLineTest_836, SetCaptionFalse_836) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setCaption(true);
    EXPECT_TRUE(annot->getCaption());

    annot->setCaption(false);
    EXPECT_FALSE(annot->getCaption());
}

TEST_F(AnnotLineTest_836, SetLeaderLineLength_836) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setLeaderLineLength(15.5);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 15.5);
}

TEST_F(AnnotLineTest_836, SetLeaderLineLength_Zero_836) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setLeaderLineLength(0.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 0.0);
}

TEST_F(AnnotLineTest_836, SetLeaderLineLength_Negative_836) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setLeaderLineLength(-10.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), -10.0);
}

TEST_F(AnnotLineTest_836, SetLeaderLineExtension_836) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setLeaderLineExtension(7.25);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineExtension(), 7.25);
}

TEST_F(AnnotLineTest_836, SetLeaderLineExtension_Zero_836) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setLeaderLineExtension(0.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineExtension(), 0.0);
}

TEST_F(AnnotLineTest_836, SetInteriorColor_836) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    annot->setInteriorColor(std::move(color));

    AnnotColor *retrievedColor = annot->getInteriorColor();
    ASSERT_NE(retrievedColor, nullptr);
}

TEST_F(AnnotLineTest_836, SetInteriorColor_Null_836) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setInteriorColor(nullptr);
    EXPECT_EQ(annot->getInteriorColor(), nullptr);
}

TEST_F(AnnotLineTest_836, DefaultInteriorColor_836) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    // Default interior color should be null
    EXPECT_EQ(annot->getInteriorColor(), nullptr);
}

TEST_F(AnnotLineTest_836, DefaultLeaderLineOffset_836) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    EXPECT_DOUBLE_EQ(annot->getLeaderLineOffset(), 0.0);
}

TEST_F(AnnotLineTest_836, DefaultCaptionTextHorizontal_836) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    EXPECT_DOUBLE_EQ(annot->getCaptionTextHorizontal(), 0.0);
}

TEST_F(AnnotLineTest_836, DefaultCaptionTextVertical_836) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    EXPECT_DOUBLE_EQ(annot->getCaptionTextVertical(), 0.0);
}

TEST_F(AnnotLineTest_836, DefaultMeasure_836) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    EXPECT_EQ(annot->getMeasure(), nullptr);
}

TEST_F(AnnotLineTest_836, SetIntent_836) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setIntent(AnnotLine::annotLineArrow);
    EXPECT_EQ(annot->getIntent(), AnnotLine::annotLineArrow);
}

TEST_F(AnnotLineTest_836, SetIntent_Dimension_836) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setIntent(AnnotLine::annotLineDimension);
    EXPECT_EQ(annot->getIntent(), AnnotLine::annotLineDimension);
}

TEST_F(AnnotLineTest_836, SetVertices_MultipleUpdates_836) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setVertices(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(annot->getX1(), 1.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), 2.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), 3.0);
    EXPECT_DOUBLE_EQ(annot->getY2(), 4.0);

    annot->setVertices(10.0, 20.0, 30.0, 40.0);
    EXPECT_DOUBLE_EQ(annot->getX1(), 10.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), 20.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), 30.0);
    EXPECT_DOUBLE_EQ(annot->getY2(), 40.0);
}

TEST_F(AnnotLineTest_836, GetX1_DelegatesToCoord1_836) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(42.0, 84.0, 200.0, 300.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    // getX1 should return coord1's x value
    EXPECT_DOUBLE_EQ(annot->getX1(), 42.0);
}

TEST_F(AnnotLineTest_836, GetY1_DelegatesToCoord1_836) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(42.0, 84.0, 200.0, 300.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    EXPECT_DOUBLE_EQ(annot->getY1(), 84.0);
}

TEST_F(AnnotLineTest_836, GetX2_DelegatesToCoord2_836) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(42.0, 84.0, 200.0, 300.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    EXPECT_DOUBLE_EQ(annot->getX2(), 200.0);
}

TEST_F(AnnotLineTest_836, GetY2_DelegatesToCoord2_836) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(42.0, 84.0, 200.0, 300.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    EXPECT_DOUBLE_EQ(annot->getY2(), 300.0);
}

// Test AnnotCoord directly
TEST_F(AnnotLineTest_836, AnnotCoord_DefaultConstructor_836) {
    AnnotCoord coord;
    EXPECT_DOUBLE_EQ(coord.getX(), 0.0);
    EXPECT_DOUBLE_EQ(coord.getY(), 0.0);
}

TEST_F(AnnotLineTest_836, AnnotCoord_ParameterizedConstructor_836) {
    AnnotCoord coord(3.14, 2.71);
    EXPECT_DOUBLE_EQ(coord.getX(), 3.14);
    EXPECT_DOUBLE_EQ(coord.getY(), 2.71);
}

TEST_F(AnnotLineTest_836, AnnotCoord_NegativeValues_836) {
    AnnotCoord coord(-100.5, -200.75);
    EXPECT_DOUBLE_EQ(coord.getX(), -100.5);
    EXPECT_DOUBLE_EQ(coord.getY(), -200.75);
}

TEST_F(AnnotLineTest_836, AnnotCoord_ZeroValues_836) {
    AnnotCoord coord(0.0, 0.0);
    EXPECT_DOUBLE_EQ(coord.getX(), 0.0);
    EXPECT_DOUBLE_EQ(coord.getY(), 0.0);
}

TEST_F(AnnotLineTest_836, AnnotCoord_LargeValues_836) {
    AnnotCoord coord(1e15, -1e15);
    EXPECT_DOUBLE_EQ(coord.getX(), 1e15);
    EXPECT_DOUBLE_EQ(coord.getY(), -1e15);
}

TEST_F(AnnotLineTest_836, AnnotCoord_VerySmallValues_836) {
    AnnotCoord coord(1e-15, 1e-15);
    EXPECT_DOUBLE_EQ(coord.getX(), 1e-15);
    EXPECT_DOUBLE_EQ(coord.getY(), 1e-15);
}
