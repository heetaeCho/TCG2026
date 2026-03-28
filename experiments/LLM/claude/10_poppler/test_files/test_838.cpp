#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Annot.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"
#include "PDFDocFactory.h"

class AnnotLineTest_838 : public ::testing::Test {
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
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n190\n%%EOF\n";

        auto stream = new MemStream(const_cast<char*>(minimalPDF), 0, sizeof(minimalPDF) - 1, Object(objNull));
        return std::make_unique<PDFDoc>(stream);
    }
};

// Test that AnnotLine created with a rectangle has proper coordinate accessors
TEST_F(AnnotLineTest_838, ConstructorWithRect_DefaultCoordinates_838) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(10.0, 20.0, 100.0, 200.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    // After construction with a rect, we can at least call getX2 and getY2 without crashing
    // The exact values depend on the implementation but they should be accessible
    double x2 = annot->getX2();
    double y2 = annot->getY2();
    double x1 = annot->getX1();
    double y1 = annot->getY1();
    // Coordinates should be finite numbers
    EXPECT_FALSE(std::isnan(x1));
    EXPECT_FALSE(std::isnan(y1));
    EXPECT_FALSE(std::isnan(x2));
    EXPECT_FALSE(std::isnan(y2));
}

// Test setVertices and then retrieve coordinates
TEST_F(AnnotLineTest_838, SetVertices_GetCoordinates_838) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 500.0, 500.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setVertices(10.0, 20.0, 30.0, 40.0);

    EXPECT_DOUBLE_EQ(annot->getX1(), 10.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), 20.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), 30.0);
    EXPECT_DOUBLE_EQ(annot->getY2(), 40.0);
}

// Test setVertices with zero coordinates
TEST_F(AnnotLineTest_838, SetVertices_ZeroCoordinates_838) {
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

// Test setVertices with negative coordinates
TEST_F(AnnotLineTest_838, SetVertices_NegativeCoordinates_838) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(-100.0, -100.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setVertices(-50.0, -25.0, -10.0, -5.0);

    EXPECT_DOUBLE_EQ(annot->getX1(), -50.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), -25.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), -10.0);
    EXPECT_DOUBLE_EQ(annot->getY2(), -5.0);
}

// Test setVertices with large coordinates
TEST_F(AnnotLineTest_838, SetVertices_LargeCoordinates_838) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 1e6, 1e6);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setVertices(1e5, 2e5, 3e5, 4e5);

    EXPECT_DOUBLE_EQ(annot->getX1(), 1e5);
    EXPECT_DOUBLE_EQ(annot->getY1(), 2e5);
    EXPECT_DOUBLE_EQ(annot->getX2(), 3e5);
    EXPECT_DOUBLE_EQ(annot->getY2(), 4e5);
}

// Test setVertices with fractional coordinates
TEST_F(AnnotLineTest_838, SetVertices_FractionalCoordinates_838) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setVertices(1.5, 2.7, 3.14159, 99.999);

    EXPECT_DOUBLE_EQ(annot->getX1(), 1.5);
    EXPECT_DOUBLE_EQ(annot->getY1(), 2.7);
    EXPECT_DOUBLE_EQ(annot->getX2(), 3.14159);
    EXPECT_DOUBLE_EQ(annot->getY2(), 99.999);
}

// Test caption default value
TEST_F(AnnotLineTest_838, Caption_DefaultValue_838) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    // Default caption should be false
    EXPECT_FALSE(annot->getCaption());
}

// Test setCaption
TEST_F(AnnotLineTest_838, SetCaption_True_838) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setCaption(true);
    EXPECT_TRUE(annot->getCaption());
}

// Test setCaption to false
TEST_F(AnnotLineTest_838, SetCaption_False_838) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setCaption(true);
    annot->setCaption(false);
    EXPECT_FALSE(annot->getCaption());
}

// Test setLeaderLineLength
TEST_F(AnnotLineTest_838, SetLeaderLineLength_838) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setLeaderLineLength(15.5);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 15.5);
}

// Test setLeaderLineExtension
TEST_F(AnnotLineTest_838, SetLeaderLineExtension_838) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setLeaderLineExtension(7.25);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineExtension(), 7.25);
}

// Test setIntent
TEST_F(AnnotLineTest_838, SetIntent_838) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setIntent(annotLineArrow);
    EXPECT_EQ(annot->getIntent(), annotLineArrow);
}

// Test setIntent to dimension
TEST_F(AnnotLineTest_838, SetIntentDimension_838) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setIntent(annotLineDimension);
    EXPECT_EQ(annot->getIntent(), annotLineDimension);
}

// Test getInteriorColor default (should be nullptr)
TEST_F(AnnotLineTest_838, InteriorColor_Default_838) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    // Default interior color is typically nullptr
    AnnotColor *color = annot->getInteriorColor();
    // May or may not be null depending on implementation, just check it doesn't crash
    (void)color;
}

// Test setVertices updates coordinates correctly when called multiple times
TEST_F(AnnotLineTest_838, SetVertices_MultipleCalls_838) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 500.0, 500.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setVertices(10.0, 20.0, 30.0, 40.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), 30.0);

    annot->setVertices(100.0, 200.0, 300.0, 400.0);
    EXPECT_DOUBLE_EQ(annot->getX1(), 100.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), 200.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), 300.0);
    EXPECT_DOUBLE_EQ(annot->getY2(), 400.0);
}

// Test AnnotCoord directly
TEST_F(AnnotLineTest_838, AnnotCoord_DefaultConstructor_838) {
    AnnotCoord coord;
    EXPECT_DOUBLE_EQ(coord.getX(), 0.0);
    EXPECT_DOUBLE_EQ(coord.getY(), 0.0);
}

TEST_F(AnnotLineTest_838, AnnotCoord_ParameterizedConstructor_838) {
    AnnotCoord coord(42.5, -17.3);
    EXPECT_DOUBLE_EQ(coord.getX(), 42.5);
    EXPECT_DOUBLE_EQ(coord.getY(), -17.3);
}

TEST_F(AnnotLineTest_838, AnnotCoord_ZeroValues_838) {
    AnnotCoord coord(0.0, 0.0);
    EXPECT_DOUBLE_EQ(coord.getX(), 0.0);
    EXPECT_DOUBLE_EQ(coord.getY(), 0.0);
}

TEST_F(AnnotLineTest_838, AnnotCoord_LargeValues_838) {
    AnnotCoord coord(1e15, -1e15);
    EXPECT_DOUBLE_EQ(coord.getX(), 1e15);
    EXPECT_DOUBLE_EQ(coord.getY(), -1e15);
}

TEST_F(AnnotLineTest_838, AnnotCoord_SmallFractionalValues_838) {
    AnnotCoord coord(0.000001, 0.000002);
    EXPECT_DOUBLE_EQ(coord.getX(), 0.000001);
    EXPECT_DOUBLE_EQ(coord.getY(), 0.000002);
}

// Test getLeaderLineOffset default
TEST_F(AnnotLineTest_838, LeaderLineOffset_Default_838) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    double offset = annot->getLeaderLineOffset();
    EXPECT_FALSE(std::isnan(offset));
}

// Test getCaptionTextHorizontal and getCaptionTextVertical defaults
TEST_F(AnnotLineTest_838, CaptionTextDefaults_838) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    double horiz = annot->getCaptionTextHorizontal();
    double vert = annot->getCaptionTextVertical();
    EXPECT_FALSE(std::isnan(horiz));
    EXPECT_FALSE(std::isnan(vert));
}

// Test getMeasure default
TEST_F(AnnotLineTest_838, Measure_Default_838) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    Dict* measure = annot->getMeasure();
    // For a newly created annotation, measure should typically be nullptr
    EXPECT_EQ(measure, nullptr);
}

// Test setLeaderLineLength with zero
TEST_F(AnnotLineTest_838, SetLeaderLineLength_Zero_838) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setLeaderLineLength(0.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 0.0);
}

// Test setLeaderLineExtension with zero
TEST_F(AnnotLineTest_838, SetLeaderLineExtension_Zero_838) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setLeaderLineExtension(0.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineExtension(), 0.0);
}

// Test that setVertices with identical start and end points works
TEST_F(AnnotLineTest_838, SetVertices_IdenticalPoints_838) {
    auto doc = createEmptyDoc();
    ASSERT_TRUE(doc->isOk());

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setVertices(50.0, 50.0, 50.0, 50.0);

    EXPECT_DOUBLE_EQ(annot->getX1(), 50.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), 50.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), 50.0);
    EXPECT_DOUBLE_EQ(annot->getY2(), 50.0);
}
