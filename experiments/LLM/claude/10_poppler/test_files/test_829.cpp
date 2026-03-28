#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Annot.h"
#include "PDFDoc.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"
#include "Object.h"
#include "GooString.h"

class AnnotLineTest_829 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // We'll create AnnotLine objects as needed in individual tests
    }

    void TearDown() override {
    }

    // Helper to create a minimal PDFDoc for testing
    // We need a valid PDFDoc to construct AnnotLine
    std::unique_ptr<PDFDoc> createMinimalPDFDoc() {
        // Create a minimal PDF in memory
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

TEST_F(AnnotLineTest_829, ConstructWithRect_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(100, 200, 300, 400);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    // After construction with a rect, the annotation should exist
    ASSERT_NE(annot, nullptr);
}

TEST_F(AnnotLineTest_829, GetCaptionDefaultFalse_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    // Default caption should be false
    EXPECT_FALSE(annot->getCaption());
}

TEST_F(AnnotLineTest_829, SetCaptionTrue_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setCaption(true);
    EXPECT_TRUE(annot->getCaption());
}

TEST_F(AnnotLineTest_829, SetCaptionFalse_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setCaption(true);
    EXPECT_TRUE(annot->getCaption());

    annot->setCaption(false);
    EXPECT_FALSE(annot->getCaption());
}

TEST_F(AnnotLineTest_829, SetVertices_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 500, 500);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setVertices(10.0, 20.0, 30.0, 40.0);
    EXPECT_DOUBLE_EQ(annot->getX1(), 10.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), 20.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), 30.0);
    EXPECT_DOUBLE_EQ(annot->getY2(), 40.0);
}

TEST_F(AnnotLineTest_829, SetVerticesZero_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setVertices(0.0, 0.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(annot->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), 0.0);
    EXPECT_DOUBLE_EQ(annot->getY2(), 0.0);
}

TEST_F(AnnotLineTest_829, SetVerticesNegative_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(-100, -100, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setVertices(-50.5, -25.3, 75.7, 99.9);
    EXPECT_DOUBLE_EQ(annot->getX1(), -50.5);
    EXPECT_DOUBLE_EQ(annot->getY1(), -25.3);
    EXPECT_DOUBLE_EQ(annot->getX2(), 75.7);
    EXPECT_DOUBLE_EQ(annot->getY2(), 99.9);
}

TEST_F(AnnotLineTest_829, SetLeaderLineLength_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setLeaderLineLength(15.5);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 15.5);
}

TEST_F(AnnotLineTest_829, SetLeaderLineLengthZero_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setLeaderLineLength(0.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 0.0);
}

TEST_F(AnnotLineTest_829, SetLeaderLineExtension_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setLeaderLineExtension(7.3);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineExtension(), 7.3);
}

TEST_F(AnnotLineTest_829, SetInteriorColor_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    annot->setInteriorColor(std::move(color));

    AnnotColor *retrievedColor = annot->getInteriorColor();
    ASSERT_NE(retrievedColor, nullptr);
}

TEST_F(AnnotLineTest_829, SetInteriorColorNull_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setInteriorColor(nullptr);
    EXPECT_EQ(annot->getInteriorColor(), nullptr);
}

TEST_F(AnnotLineTest_829, SetStartEndStyle_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setStartEndStyle(annotLineEndingOpenArrow, annotLineEndingClosedArrow);
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingOpenArrow);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingClosedArrow);
}

TEST_F(AnnotLineTest_829, SetStartEndStyleNone_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setStartEndStyle(annotLineEndingNone, annotLineEndingNone);
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingNone);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingNone);
}

TEST_F(AnnotLineTest_829, SetIntent_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setIntent(annotLineArrow);
    EXPECT_EQ(annot->getIntent(), annotLineArrow);
}

TEST_F(AnnotLineTest_829, SetIntentDimension_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setIntent(annotLineDimension);
    EXPECT_EQ(annot->getIntent(), annotLineDimension);
}

TEST_F(AnnotLineTest_829, DefaultLeaderLineOffset_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    // Default leader line offset should be 0
    EXPECT_DOUBLE_EQ(annot->getLeaderLineOffset(), 0.0);
}

TEST_F(AnnotLineTest_829, DefaultCaptionTextHorizontal_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    EXPECT_DOUBLE_EQ(annot->getCaptionTextHorizontal(), 0.0);
}

TEST_F(AnnotLineTest_829, DefaultCaptionTextVertical_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    EXPECT_DOUBLE_EQ(annot->getCaptionTextVertical(), 0.0);
}

TEST_F(AnnotLineTest_829, DefaultMeasureIsNull_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    EXPECT_EQ(annot->getMeasure(), nullptr);
}

TEST_F(AnnotLineTest_829, SetContentsString_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    auto contents = std::make_unique<GooString>("Test Line Annotation");
    annot->setContents(std::move(contents));

    // Verify the contents were set (accessible through parent class)
    const GooString *retrieved = annot->getContents();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "Test Line Annotation");
}

TEST_F(AnnotLineTest_829, SetVerticesMultipleTimes_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 500, 500);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setVertices(10.0, 20.0, 30.0, 40.0);
    EXPECT_DOUBLE_EQ(annot->getX1(), 10.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), 20.0);

    annot->setVertices(100.0, 200.0, 300.0, 400.0);
    EXPECT_DOUBLE_EQ(annot->getX1(), 100.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), 200.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), 300.0);
    EXPECT_DOUBLE_EQ(annot->getY2(), 400.0);
}

TEST_F(AnnotLineTest_829, SetCaptionToggle_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    // Toggle caption multiple times
    EXPECT_FALSE(annot->getCaption());
    annot->setCaption(true);
    EXPECT_TRUE(annot->getCaption());
    annot->setCaption(true);
    EXPECT_TRUE(annot->getCaption());
    annot->setCaption(false);
    EXPECT_FALSE(annot->getCaption());
    annot->setCaption(false);
    EXPECT_FALSE(annot->getCaption());
}

TEST_F(AnnotLineTest_829, SetLeaderLineLengthNegative_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setLeaderLineLength(-10.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), -10.0);
}

TEST_F(AnnotLineTest_829, SetLeaderLineExtensionZero_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setLeaderLineExtension(0.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineExtension(), 0.0);
}

TEST_F(AnnotLineTest_829, LargeCoordinateValues_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100000, 100000);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setVertices(99999.99, 99999.99, 0.01, 0.01);
    EXPECT_DOUBLE_EQ(annot->getX1(), 99999.99);
    EXPECT_DOUBLE_EQ(annot->getY1(), 99999.99);
    EXPECT_DOUBLE_EQ(annot->getX2(), 0.01);
    EXPECT_DOUBLE_EQ(annot->getY2(), 0.01);
}

TEST_F(AnnotLineTest_829, DefaultStartEndStyle_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    // Default line ending styles should be None
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingNone);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingNone);
}

TEST_F(AnnotLineTest_829, ReplaceInteriorColor_829) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    auto color1 = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    annot->setInteriorColor(std::move(color1));
    ASSERT_NE(annot->getInteriorColor(), nullptr);

    auto color2 = std::make_unique<AnnotColor>(0.0, 1.0, 0.0);
    annot->setInteriorColor(std::move(color2));
    ASSERT_NE(annot->getInteriorColor(), nullptr);

    annot->setInteriorColor(nullptr);
    EXPECT_EQ(annot->getInteriorColor(), nullptr);
}
