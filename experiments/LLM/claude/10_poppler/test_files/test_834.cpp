#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Annot.h"
#include "PDFDoc.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"
#include "Object.h"
#include "Dict.h"
#include "GooString.h"

class AnnotLineTest_834 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a minimal PDFDoc from a file if available,
    // or we rely on constructing AnnotLine with a rect-based constructor
    std::unique_ptr<PDFDoc> createTestDoc(const char *filename) {
        auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(GooString(filename)));
        return doc;
    }
};

// Test that getCaptionTextHorizontal returns the captionTextHorizontal value
// We test this through constructing an AnnotLine with a PDFRectangle and checking defaults
TEST_F(AnnotLineTest_834, GetCaptionTextHorizontalDefault_834) {
    // We need a valid PDFDoc to construct AnnotLine
    // Create a minimal PDF in memory or use a test file
    // For this test, we attempt to create an AnnotLine with a rect constructor
    // Since we can't easily create a PDFDoc without a file, we test what we can

    // If we have access to a test PDF:
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

        // Default captionTextHorizontal should be 0
        double horizontal = annot->getCaptionTextHorizontal();
        EXPECT_DOUBLE_EQ(horizontal, 0.0);
    }
}

TEST_F(AnnotLineTest_834, GetCaptionTextVerticalDefault_834) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

        double vertical = annot->getCaptionTextVertical();
        EXPECT_DOUBLE_EQ(vertical, 0.0);
    }
}

TEST_F(AnnotLineTest_834, GetLeaderLineLengthDefault_834) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

        double length = annot->getLeaderLineLength();
        EXPECT_DOUBLE_EQ(length, 0.0);
    }
}

TEST_F(AnnotLineTest_834, GetLeaderLineExtensionDefault_834) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

        double ext = annot->getLeaderLineExtension();
        EXPECT_DOUBLE_EQ(ext, 0.0);
    }
}

TEST_F(AnnotLineTest_834, GetCaptionDefault_834) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

        bool cap = annot->getCaption();
        EXPECT_FALSE(cap);
    }
}

TEST_F(AnnotLineTest_834, GetInteriorColorDefault_834) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

        AnnotColor *color = annot->getInteriorColor();
        EXPECT_EQ(color, nullptr);
    }
}

TEST_F(AnnotLineTest_834, GetMeasureDefault_834) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

        Dict *measure = annot->getMeasure();
        EXPECT_EQ(measure, nullptr);
    }
}

TEST_F(AnnotLineTest_834, SetVerticesAndGetCoordinates_834) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 200, 200);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

        annot->setVertices(10.0, 20.0, 150.0, 180.0);

        EXPECT_DOUBLE_EQ(annot->getX1(), 10.0);
        EXPECT_DOUBLE_EQ(annot->getY1(), 20.0);
        EXPECT_DOUBLE_EQ(annot->getX2(), 150.0);
        EXPECT_DOUBLE_EQ(annot->getY2(), 180.0);
    }
}

TEST_F(AnnotLineTest_834, SetLeaderLineLength_834) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

        annot->setLeaderLineLength(25.5);
        EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 25.5);
    }
}

TEST_F(AnnotLineTest_834, SetLeaderLineExtension_834) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

        annot->setLeaderLineExtension(12.3);
        EXPECT_DOUBLE_EQ(annot->getLeaderLineExtension(), 12.3);
    }
}

TEST_F(AnnotLineTest_834, SetCaptionTrue_834) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

        annot->setCaption(true);
        EXPECT_TRUE(annot->getCaption());
    }
}

TEST_F(AnnotLineTest_834, SetCaptionFalse_834) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

        annot->setCaption(true);
        annot->setCaption(false);
        EXPECT_FALSE(annot->getCaption());
    }
}

TEST_F(AnnotLineTest_834, SetInteriorColor_834) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

        auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
        annot->setInteriorColor(std::move(color));

        AnnotColor *result = annot->getInteriorColor();
        EXPECT_NE(result, nullptr);
    }
}

TEST_F(AnnotLineTest_834, SetInteriorColorToNull_834) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

        // Set to a color first
        auto color = std::make_unique<AnnotColor>(0.0, 1.0, 0.0);
        annot->setInteriorColor(std::move(color));
        EXPECT_NE(annot->getInteriorColor(), nullptr);

        // Then set to nullptr
        annot->setInteriorColor(nullptr);
        EXPECT_EQ(annot->getInteriorColor(), nullptr);
    }
}

TEST_F(AnnotLineTest_834, SetVerticesZero_834) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

        annot->setVertices(0.0, 0.0, 0.0, 0.0);

        EXPECT_DOUBLE_EQ(annot->getX1(), 0.0);
        EXPECT_DOUBLE_EQ(annot->getY1(), 0.0);
        EXPECT_DOUBLE_EQ(annot->getX2(), 0.0);
        EXPECT_DOUBLE_EQ(annot->getY2(), 0.0);
    }
}

TEST_F(AnnotLineTest_834, SetVerticesNegative_834) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        PDFRectangle rect(-100, -100, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

        annot->setVertices(-50.0, -30.0, 50.0, 30.0);

        EXPECT_DOUBLE_EQ(annot->getX1(), -50.0);
        EXPECT_DOUBLE_EQ(annot->getY1(), -30.0);
        EXPECT_DOUBLE_EQ(annot->getX2(), 50.0);
        EXPECT_DOUBLE_EQ(annot->getY2(), 30.0);
    }
}

TEST_F(AnnotLineTest_834, SetLeaderLineLengthNegative_834) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

        annot->setLeaderLineLength(-10.0);
        EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), -10.0);
    }
}

TEST_F(AnnotLineTest_834, SetLeaderLineExtensionNegative_834) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

        // Extension should typically be non-negative, but we test observable behavior
        annot->setLeaderLineExtension(-5.0);
        EXPECT_DOUBLE_EQ(annot->getLeaderLineExtension(), -5.0);
    }
}

TEST_F(AnnotLineTest_834, GetLeaderLineOffsetDefault_834) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

        double offset = annot->getLeaderLineOffset();
        EXPECT_DOUBLE_EQ(offset, 0.0);
    }
}

TEST_F(AnnotLineTest_834, SetVerticesLargeValues_834) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 10000, 10000);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

        annot->setVertices(9999.99, 9999.99, 0.01, 0.01);

        EXPECT_DOUBLE_EQ(annot->getX1(), 9999.99);
        EXPECT_DOUBLE_EQ(annot->getY1(), 9999.99);
        EXPECT_DOUBLE_EQ(annot->getX2(), 0.01);
        EXPECT_DOUBLE_EQ(annot->getY2(), 0.01);
    }
}

TEST_F(AnnotLineTest_834, SetContentsWithString_834) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

        auto contents = std::make_unique<GooString>("Test annotation line");
        annot->setContents(std::move(contents));
        // No crash means the setter works; we verify through the parent class getContents if available
    }
}

TEST_F(AnnotLineTest_834, SetIntent_834) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

        annot->setIntent(annotLineArrow);
        EXPECT_EQ(annot->getIntent(), annotLineArrow);

        annot->setIntent(annotLineDimension);
        EXPECT_EQ(annot->getIntent(), annotLineDimension);
    }
}

TEST_F(AnnotLineTest_834, MultipleSetVerticesCalls_834) {
    auto doc = createTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 500, 500);
        auto annot = std::make_unique<AnnotLine>(doc.get(), &rect);

        annot->setVertices(10.0, 20.0, 30.0, 40.0);
        EXPECT_DOUBLE_EQ(annot->getX1(), 10.0);
        EXPECT_DOUBLE_EQ(annot->getY1(), 20.0);

        annot->setVertices(100.0, 200.0, 300.0, 400.0);
        EXPECT_DOUBLE_EQ(annot->getX1(), 100.0);
        EXPECT_DOUBLE_EQ(annot->getY1(), 200.0);
        EXPECT_DOUBLE_EQ(annot->getX2(), 300.0);
        EXPECT_DOUBLE_EQ(annot->getY2(), 400.0);
    }
}
