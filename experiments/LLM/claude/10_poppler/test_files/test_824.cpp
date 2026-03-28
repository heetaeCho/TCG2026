#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Annot.h"
#include "PDFDoc.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"
#include "Object.h"
#include "GooString.h"

class AnnotLineTest_824 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // We need a valid PDFDoc to create annotations.
        // We'll try to create a minimal one or use a test PDF if available.
    }

    void TearDown() override {
    }

    // Helper to create an AnnotLine with a PDFDoc and rectangle
    std::unique_ptr<AnnotLine> createAnnotLine(PDFDoc *doc) {
        auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
        return std::make_unique<AnnotLine>(doc, rect.get());
    }
};

// Since AnnotLine requires a valid PDFDoc, we need a minimal PDF.
// We'll create a helper that provides a simple in-memory PDF document.

class AnnotLineWithDocTest_824 : public ::testing::Test {
protected:
    std::unique_ptr<PDFDoc> doc;
    std::unique_ptr<AnnotLine> annot;

    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // Create a minimal PDF in memory
        static const char minimalPDF[] =
            "%PDF-1.4\n"
            "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
            "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
            "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer\n<< /Size 4 /Root 1 0 R >>\n"
            "startxref\n200\n%%EOF\n";

        auto *stream = new MemStream(const_cast<char *>(minimalPDF), 0, sizeof(minimalPDF) - 1, Object(objNull));
        doc = std::make_unique<PDFDoc>(stream);

        if (doc->isOk()) {
            auto rect = std::make_unique<PDFRectangle>(10, 10, 200, 200);
            annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
        }
    }

    void TearDown() override {
        annot.reset();
        doc.reset();
    }

    bool isValid() const {
        return doc && doc->isOk() && annot;
    }
};

TEST_F(AnnotLineWithDocTest_824, Creation_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    EXPECT_NE(annot.get(), nullptr);
}

TEST_F(AnnotLineWithDocTest_824, GetStartStyleDefault_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    // Default start style should be annotLineEndingNone
    AnnotLineEndingStyle style = annot->getStartStyle();
    EXPECT_EQ(style, annotLineEndingNone);
}

TEST_F(AnnotLineWithDocTest_824, GetEndStyleDefault_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    AnnotLineEndingStyle style = annot->getEndStyle();
    EXPECT_EQ(style, annotLineEndingNone);
}

TEST_F(AnnotLineWithDocTest_824, SetStartEndStyle_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    annot->setStartEndStyle(annotLineEndingOpenArrow, annotLineEndingClosedArrow);
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingOpenArrow);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingClosedArrow);
}

TEST_F(AnnotLineWithDocTest_824, SetStartEndStyleMultipleStyles_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    annot->setStartEndStyle(annotLineEndingSquare, annotLineEndingCircle);
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingSquare);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingCircle);
}

TEST_F(AnnotLineWithDocTest_824, SetStartEndStyleDiamond_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    annot->setStartEndStyle(annotLineEndingDiamond, annotLineEndingButt);
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingDiamond);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingButt);
}

TEST_F(AnnotLineWithDocTest_824, SetStartEndStyleROpenArrow_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    annot->setStartEndStyle(annotLineEndingROpenArrow, annotLineEndingRClosedArrow);
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingROpenArrow);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingRClosedArrow);
}

TEST_F(AnnotLineWithDocTest_824, SetStartEndStyleSlash_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    annot->setStartEndStyle(annotLineEndingSlash, annotLineEndingNone);
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingSlash);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingNone);
}

TEST_F(AnnotLineWithDocTest_824, SetVertices_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    annot->setVertices(10.0, 20.0, 30.0, 40.0);
    EXPECT_DOUBLE_EQ(annot->getX1(), 10.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), 20.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), 30.0);
    EXPECT_DOUBLE_EQ(annot->getY2(), 40.0);
}

TEST_F(AnnotLineWithDocTest_824, SetVerticesZero_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    annot->setVertices(0.0, 0.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(annot->getX1(), 0.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), 0.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), 0.0);
    EXPECT_DOUBLE_EQ(annot->getY2(), 0.0);
}

TEST_F(AnnotLineWithDocTest_824, SetVerticesNegative_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    annot->setVertices(-10.5, -20.3, -30.7, -40.9);
    EXPECT_DOUBLE_EQ(annot->getX1(), -10.5);
    EXPECT_DOUBLE_EQ(annot->getY1(), -20.3);
    EXPECT_DOUBLE_EQ(annot->getX2(), -30.7);
    EXPECT_DOUBLE_EQ(annot->getY2(), -40.9);
}

TEST_F(AnnotLineWithDocTest_824, SetVerticesLargeValues_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    annot->setVertices(1e10, 1e10, 1e10, 1e10);
    EXPECT_DOUBLE_EQ(annot->getX1(), 1e10);
    EXPECT_DOUBLE_EQ(annot->getY1(), 1e10);
    EXPECT_DOUBLE_EQ(annot->getX2(), 1e10);
    EXPECT_DOUBLE_EQ(annot->getY2(), 1e10);
}

TEST_F(AnnotLineWithDocTest_824, GetInteriorColorDefault_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    // Default interior color should be nullptr
    EXPECT_EQ(annot->getInteriorColor(), nullptr);
}

TEST_F(AnnotLineWithDocTest_824, SetInteriorColor_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    annot->setInteriorColor(std::move(color));
    AnnotColor *c = annot->getInteriorColor();
    EXPECT_NE(c, nullptr);
}

TEST_F(AnnotLineWithDocTest_824, SetInteriorColorNull_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    annot->setInteriorColor(nullptr);
    EXPECT_EQ(annot->getInteriorColor(), nullptr);
}

TEST_F(AnnotLineWithDocTest_824, GetLeaderLineLengthDefault_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 0.0);
}

TEST_F(AnnotLineWithDocTest_824, SetLeaderLineLength_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    annot->setLeaderLineLength(15.5);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 15.5);
}

TEST_F(AnnotLineWithDocTest_824, SetLeaderLineLengthNegative_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    annot->setLeaderLineLength(-5.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), -5.0);
}

TEST_F(AnnotLineWithDocTest_824, GetLeaderLineExtensionDefault_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    EXPECT_DOUBLE_EQ(annot->getLeaderLineExtension(), 0.0);
}

TEST_F(AnnotLineWithDocTest_824, SetLeaderLineExtension_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    annot->setLeaderLineExtension(10.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineExtension(), 10.0);
}

TEST_F(AnnotLineWithDocTest_824, GetCaptionDefault_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    EXPECT_FALSE(annot->getCaption());
}

TEST_F(AnnotLineWithDocTest_824, SetCaptionTrue_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    annot->setCaption(true);
    EXPECT_TRUE(annot->getCaption());
}

TEST_F(AnnotLineWithDocTest_824, SetCaptionFalse_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    annot->setCaption(true);
    EXPECT_TRUE(annot->getCaption());
    annot->setCaption(false);
    EXPECT_FALSE(annot->getCaption());
}

TEST_F(AnnotLineWithDocTest_824, GetIntentDefault_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    // Default intent
    AnnotLineIntent intent = annot->getIntent();
    EXPECT_EQ(intent, annotLineArrow);
}

TEST_F(AnnotLineWithDocTest_824, SetIntent_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    annot->setIntent(annotLineDimension);
    EXPECT_EQ(annot->getIntent(), annotLineDimension);
}

TEST_F(AnnotLineWithDocTest_824, SetIntentArrow_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    annot->setIntent(annotLineDimension);
    annot->setIntent(annotLineArrow);
    EXPECT_EQ(annot->getIntent(), annotLineArrow);
}

TEST_F(AnnotLineWithDocTest_824, GetLeaderLineOffsetDefault_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    EXPECT_DOUBLE_EQ(annot->getLeaderLineOffset(), 0.0);
}

TEST_F(AnnotLineWithDocTest_824, GetCaptionPosDefault_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    AnnotLineCaptionPos pos = annot->getCaptionPos();
    EXPECT_EQ(pos, annotLineCaptionPosInline);
}

TEST_F(AnnotLineWithDocTest_824, GetMeasureDefault_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    EXPECT_EQ(annot->getMeasure(), nullptr);
}

TEST_F(AnnotLineWithDocTest_824, GetCaptionTextHorizontalDefault_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    EXPECT_DOUBLE_EQ(annot->getCaptionTextHorizontal(), 0.0);
}

TEST_F(AnnotLineWithDocTest_824, GetCaptionTextVerticalDefault_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    EXPECT_DOUBLE_EQ(annot->getCaptionTextVertical(), 0.0);
}

TEST_F(AnnotLineWithDocTest_824, SetContents_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    auto content = std::make_unique<GooString>("Test content");
    annot->setContents(std::move(content));
    // We verify it doesn't crash; contents getter is inherited from Annot
    const GooString *c = annot->getContents();
    ASSERT_NE(c, nullptr);
    EXPECT_STREQ(c->c_str(), "Test content");
}

TEST_F(AnnotLineWithDocTest_824, SetContentsEmpty_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    auto content = std::make_unique<GooString>("");
    annot->setContents(std::move(content));
    const GooString *c = annot->getContents();
    ASSERT_NE(c, nullptr);
    EXPECT_STREQ(c->c_str(), "");
}

TEST_F(AnnotLineWithDocTest_824, SetVerticesThenChangeAgain_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    annot->setVertices(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(annot->getX1(), 1.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), 2.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), 3.0);
    EXPECT_DOUBLE_EQ(annot->getY2(), 4.0);

    annot->setVertices(5.0, 6.0, 7.0, 8.0);
    EXPECT_DOUBLE_EQ(annot->getX1(), 5.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), 6.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), 7.0);
    EXPECT_DOUBLE_EQ(annot->getY2(), 8.0);
}

TEST_F(AnnotLineWithDocTest_824, SetStartEndStyleThenChange_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    annot->setStartEndStyle(annotLineEndingOpenArrow, annotLineEndingClosedArrow);
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingOpenArrow);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingClosedArrow);

    annot->setStartEndStyle(annotLineEndingNone, annotLineEndingNone);
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingNone);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingNone);
}

TEST_F(AnnotLineWithDocTest_824, SetLeaderLineLengthMultipleTimes_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    annot->setLeaderLineLength(5.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 5.0);

    annot->setLeaderLineLength(0.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 0.0);

    annot->setLeaderLineLength(100.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 100.0);
}

TEST_F(AnnotLineWithDocTest_824, SetLeaderLineExtensionMultipleTimes_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    annot->setLeaderLineExtension(3.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineExtension(), 3.0);

    annot->setLeaderLineExtension(0.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineExtension(), 0.0);
}

TEST_F(AnnotLineWithDocTest_824, SetInteriorColorThenClear_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    auto color = std::make_unique<AnnotColor>(0.0, 1.0, 0.0);
    annot->setInteriorColor(std::move(color));
    EXPECT_NE(annot->getInteriorColor(), nullptr);

    annot->setInteriorColor(nullptr);
    EXPECT_EQ(annot->getInteriorColor(), nullptr);
}

TEST_F(AnnotLineWithDocTest_824, CaptionToggle_824) {
    if (!isValid()) {
        GTEST_SKIP() << "Could not create valid PDFDoc";
    }
    EXPECT_FALSE(annot->getCaption());
    annot->setCaption(true);
    EXPECT_TRUE(annot->getCaption());
    annot->setCaption(false);
    EXPECT_FALSE(annot->getCaption());
    annot->setCaption(true);
    EXPECT_TRUE(annot->getCaption());
}
