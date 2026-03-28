#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Annot.h"
#include "PDFDoc.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"
#include "Object.h"
#include "GooString.h"

class AnnotLineTest_831 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // We need a valid PDFDoc to create annotations
        // Create a minimal PDF in memory or load a test file
    }

    void TearDown() override {
    }

    std::unique_ptr<PDFDoc> createMinimalPDF() {
        // Create a minimal valid PDF document
        auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf");
        auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(*fileName));
        if (!doc || !doc->isOk()) {
            // Try another common test file
            fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/truetype.pdf");
            doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(*fileName));
        }
        return doc;
    }
};

TEST_F(AnnotLineTest_831, ConstructWithRect_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(100.0, 200.0, 300.0, 400.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
    ASSERT_NE(annot, nullptr);
}

TEST_F(AnnotLineTest_831, GetLeaderLineOffset_DefaultValue_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
    // Default leader line offset should be 0
    EXPECT_DOUBLE_EQ(annot->getLeaderLineOffset(), 0.0);
}

TEST_F(AnnotLineTest_831, GetLeaderLineLength_DefaultValue_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 0.0);
}

TEST_F(AnnotLineTest_831, GetLeaderLineExtension_DefaultValue_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
    EXPECT_DOUBLE_EQ(annot->getLeaderLineExtension(), 0.0);
}

TEST_F(AnnotLineTest_831, GetCaption_DefaultValue_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
    EXPECT_FALSE(annot->getCaption());
}

TEST_F(AnnotLineTest_831, GetInteriorColor_DefaultNull_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
    EXPECT_EQ(annot->getInteriorColor(), nullptr);
}

TEST_F(AnnotLineTest_831, GetMeasure_DefaultNull_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
    EXPECT_EQ(annot->getMeasure(), nullptr);
}

TEST_F(AnnotLineTest_831, SetVertices_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 500.0, 500.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setVertices(10.0, 20.0, 300.0, 400.0);
    EXPECT_DOUBLE_EQ(annot->getX1(), 10.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), 20.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), 300.0);
    EXPECT_DOUBLE_EQ(annot->getY2(), 400.0);
}

TEST_F(AnnotLineTest_831, SetVertices_SamePoint_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setVertices(50.0, 50.0, 50.0, 50.0);
    EXPECT_DOUBLE_EQ(annot->getX1(), 50.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), 50.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), 50.0);
    EXPECT_DOUBLE_EQ(annot->getY2(), 50.0);
}

TEST_F(AnnotLineTest_831, SetVertices_NegativeCoordinates_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(-100.0, -100.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setVertices(-50.0, -50.0, 50.0, 50.0);
    EXPECT_DOUBLE_EQ(annot->getX1(), -50.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), -50.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), 50.0);
    EXPECT_DOUBLE_EQ(annot->getY2(), 50.0);
}

TEST_F(AnnotLineTest_831, SetLeaderLineLength_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setLeaderLineLength(25.5);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 25.5);
}

TEST_F(AnnotLineTest_831, SetLeaderLineLength_Zero_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setLeaderLineLength(0.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 0.0);
}

TEST_F(AnnotLineTest_831, SetLeaderLineExtension_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setLeaderLineExtension(15.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineExtension(), 15.0);
}

TEST_F(AnnotLineTest_831, SetCaption_True_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setCaption(true);
    EXPECT_TRUE(annot->getCaption());
}

TEST_F(AnnotLineTest_831, SetCaption_False_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setCaption(true);
    EXPECT_TRUE(annot->getCaption());

    annot->setCaption(false);
    EXPECT_FALSE(annot->getCaption());
}

TEST_F(AnnotLineTest_831, SetIntent_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setIntent(annotLineArrow);
    EXPECT_EQ(annot->getIntent(), annotLineArrow);
}

TEST_F(AnnotLineTest_831, SetIntent_Dimension_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setIntent(annotLineDimension);
    EXPECT_EQ(annot->getIntent(), annotLineDimension);
}

TEST_F(AnnotLineTest_831, SetInteriorColor_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    AnnotColor *colorPtr = color.get();
    annot->setInteriorColor(std::move(color));
    EXPECT_NE(annot->getInteriorColor(), nullptr);
}

TEST_F(AnnotLineTest_831, SetInteriorColor_Null_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setInteriorColor(nullptr);
    EXPECT_EQ(annot->getInteriorColor(), nullptr);
}

TEST_F(AnnotLineTest_831, GetCaptionTextHorizontal_Default_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
    // Default caption text offsets should be 0
    EXPECT_DOUBLE_EQ(annot->getCaptionTextHorizontal(), 0.0);
}

TEST_F(AnnotLineTest_831, GetCaptionTextVertical_Default_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
    EXPECT_DOUBLE_EQ(annot->getCaptionTextVertical(), 0.0);
}

TEST_F(AnnotLineTest_831, SetVertices_LargeCoordinates_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100000.0, 100000.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setVertices(99999.0, 99999.0, 0.001, 0.001);
    EXPECT_DOUBLE_EQ(annot->getX1(), 99999.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), 99999.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), 0.001);
    EXPECT_DOUBLE_EQ(annot->getY2(), 0.001);
}

TEST_F(AnnotLineTest_831, SetLeaderLineLength_Negative_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setLeaderLineLength(-10.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), -10.0);
}

TEST_F(AnnotLineTest_831, SetStartEndStyle_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setStartEndStyle(annotLineEndingOpenArrow, annotLineEndingClosedArrow);
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingOpenArrow);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingClosedArrow);
}

TEST_F(AnnotLineTest_831, SetStartEndStyle_None_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setStartEndStyle(annotLineEndingNone, annotLineEndingNone);
    EXPECT_EQ(annot->getStartStyle(), annotLineEndingNone);
    EXPECT_EQ(annot->getEndStyle(), annotLineEndingNone);
}

TEST_F(AnnotLineTest_831, GetCaptionPos_Default_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
    // Default caption position should be inline
    auto pos = annot->getCaptionPos();
    EXPECT_TRUE(pos == captionPosInline || pos == captionPosTop);
}

TEST_F(AnnotLineTest_831, MultipleSetVerticesCalls_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 500.0, 500.0);
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

TEST_F(AnnotLineTest_831, SetContents_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    auto contents = std::make_unique<GooString>("Test content");
    annot->setContents(std::move(contents));
    // Just verifying it doesn't crash; contents are managed by parent class
}

TEST_F(AnnotLineTest_831, SetLeaderLineExtension_Zero_831) {
    auto doc = createMinimalPDF();
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto rect = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 100.0);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setLeaderLineExtension(0.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineExtension(), 0.0);
}
