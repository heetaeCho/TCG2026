#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Annot.h"
#include "PDFDoc.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"
#include "Object.h"
#include "GooString.h"

class AnnotLineTest_830 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // We need a valid PDFDoc to create annotations
        // Try to create a minimal PDF document for testing
    }

    void TearDown() override {
    }

    // Helper to create a PDFDoc from a minimal PDF in memory
    std::unique_ptr<PDFDoc> createMinimalPDFDoc() {
        // Create a minimal valid PDF file for testing
        static const char *minimalPDF =
            "%PDF-1.4\n"
            "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
            "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
            "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n206\n%%EOF\n";

        auto *stream = new MemStream(const_cast<char *>(minimalPDF), 0, strlen(minimalPDF), Object(objNull));
        auto doc = std::make_unique<PDFDoc>(stream);
        return doc;
    }
};

TEST_F(AnnotLineTest_830, ConstructWithRect_830) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(100.0, 200.0, 300.0, 400.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);
    ASSERT_NE(annot, nullptr);
}

TEST_F(AnnotLineTest_830, SetAndGetVertices_830) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 500.0, 500.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setVertices(10.0, 20.0, 30.0, 40.0);
    EXPECT_DOUBLE_EQ(annot->getX1(), 10.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), 20.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), 30.0);
    EXPECT_DOUBLE_EQ(annot->getY2(), 40.0);
}

TEST_F(AnnotLineTest_830, SetAndGetVerticesZero_830) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 500.0, 500.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setVertices(0.0, 0.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(annot->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), 0.0);
    EXPECT_DOUBLE_EQ(annot->getY2(), 0.0);
}

TEST_F(AnnotLineTest_830, SetAndGetVerticesNegative_830) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(-100.0, -100.0, 500.0, 500.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setVertices(-50.0, -25.0, 100.0, 200.0);
    EXPECT_DOUBLE_EQ(annot->getX1(), -50.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), -25.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), 100.0);
    EXPECT_DOUBLE_EQ(annot->getY2(), 200.0);
}

TEST_F(AnnotLineTest_830, SetAndGetIntent_830) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 500.0, 500.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setIntent(annotLineArrow);
    EXPECT_EQ(annot->getIntent(), annotLineArrow);
}

TEST_F(AnnotLineTest_830, SetAndGetIntentDimension_830) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 500.0, 500.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setIntent(annotLineDimension);
    EXPECT_EQ(annot->getIntent(), annotLineDimension);
}

TEST_F(AnnotLineTest_830, SetAndGetCaption_830) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 500.0, 500.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setCaption(true);
    EXPECT_TRUE(annot->getCaption());

    annot->setCaption(false);
    EXPECT_FALSE(annot->getCaption());
}

TEST_F(AnnotLineTest_830, SetAndGetLeaderLineLength_830) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 500.0, 500.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setLeaderLineLength(15.5);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 15.5);
}

TEST_F(AnnotLineTest_830, SetAndGetLeaderLineLengthZero_830) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 500.0, 500.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setLeaderLineLength(0.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 0.0);
}

TEST_F(AnnotLineTest_830, SetAndGetLeaderLineExtension_830) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 500.0, 500.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setLeaderLineExtension(10.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineExtension(), 10.0);
}

TEST_F(AnnotLineTest_830, SetAndGetLeaderLineExtensionZero_830) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 500.0, 500.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setLeaderLineExtension(0.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineExtension(), 0.0);
}

TEST_F(AnnotLineTest_830, SetAndGetInteriorColor_830) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 500.0, 500.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    annot->setInteriorColor(std::move(color));
    ASSERT_NE(annot->getInteriorColor(), nullptr);
}

TEST_F(AnnotLineTest_830, SetInteriorColorNull_830) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 500.0, 500.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setInteriorColor(nullptr);
    EXPECT_EQ(annot->getInteriorColor(), nullptr);
}

TEST_F(AnnotLineTest_830, SetAndGetStartEndStyle_830) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 500.0, 500.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setStartEndStyle(annotLineEndingOpenArrow, annotLineEndingClosedArrow);
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingOpenArrow);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingClosedArrow);
}

TEST_F(AnnotLineTest_830, SetStartEndStyleNone_830) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 500.0, 500.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setStartEndStyle(annotLineEndingNone, annotLineEndingNone);
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingNone);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingNone);
}

TEST_F(AnnotLineTest_830, DefaultGetters_830) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 500.0, 500.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    // Test default values are accessible without crashing
    annot->getLeaderLineOffset();
    annot->getCaptionPos();
    annot->getMeasure();
    annot->getCaptionTextHorizontal();
    annot->getCaptionTextVertical();
}

TEST_F(AnnotLineTest_830, SetContents_830) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 500.0, 500.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    auto contents = std::make_unique<GooString>("Test annotation contents");
    annot->setContents(std::move(contents));
    // Verify it doesn't crash; contents verification would require getContents
}

TEST_F(AnnotLineTest_830, SetVerticesUpdateCoordinates_830) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 1000.0, 1000.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    // Set initial vertices
    annot->setVertices(10.0, 20.0, 30.0, 40.0);
    EXPECT_DOUBLE_EQ(annot->getX1(), 10.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), 20.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), 30.0);
    EXPECT_DOUBLE_EQ(annot->getY2(), 40.0);

    // Update vertices
    annot->setVertices(100.0, 200.0, 300.0, 400.0);
    EXPECT_DOUBLE_EQ(annot->getX1(), 100.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), 200.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), 300.0);
    EXPECT_DOUBLE_EQ(annot->getY2(), 400.0);
}

TEST_F(AnnotLineTest_830, SetLeaderLineLengthNegative_830) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 500.0, 500.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setLeaderLineLength(-10.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), -10.0);
}

TEST_F(AnnotLineTest_830, SetCaptionToggle_830) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 500.0, 500.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    // Toggle caption multiple times
    annot->setCaption(true);
    EXPECT_TRUE(annot->getCaption());
    annot->setCaption(false);
    EXPECT_FALSE(annot->getCaption());
    annot->setCaption(true);
    EXPECT_TRUE(annot->getCaption());
}

TEST_F(AnnotLineTest_830, SetMultipleStartEndStyles_830) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 500.0, 500.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setStartEndStyle(annotLineEndingSquare, annotLineEndingCircle);
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingSquare);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingCircle);

    annot->setStartEndStyle(annotLineEndingDiamond, annotLineEndingButt);
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingDiamond);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingButt);
}

TEST_F(AnnotLineTest_830, LargeCoordinateValues_830) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 100000.0, 100000.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setVertices(99999.99, 99999.99, 0.01, 0.01);
    EXPECT_DOUBLE_EQ(annot->getX1(), 99999.99);
    EXPECT_DOUBLE_EQ(annot->getY1(), 99999.99);
    EXPECT_DOUBLE_EQ(annot->getX2(), 0.01);
    EXPECT_DOUBLE_EQ(annot->getY2(), 0.01);
}

TEST_F(AnnotLineTest_830, SetLeaderLineExtensionLargeValue_830) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 500.0, 500.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setLeaderLineExtension(1000000.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineExtension(), 1000000.0);
}

TEST_F(AnnotLineTest_830, IntentChangeMultipleTimes_830) {
    auto doc = createMinimalPDFDoc();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 500.0, 500.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

    annot->setIntent(annotLineArrow);
    EXPECT_EQ(annot->getIntent(), annotLineArrow);

    annot->setIntent(annotLineDimension);
    EXPECT_EQ(annot->getIntent(), annotLineDimension);

    annot->setIntent(annotLineArrow);
    EXPECT_EQ(annot->getIntent(), annotLineArrow);
}
