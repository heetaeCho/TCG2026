#include <gtest/gtest.h>
#include <memory>
#include "Annot.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class AnnotLineTest_839 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Helper to create an AnnotLine via PDFDoc with a simple PDF
static std::unique_ptr<PDFDoc> createMinimalPDFDoc() {
    // Create a minimal PDF in memory
    static const char *minimalPDF =
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

    auto *stream = new MemStream(const_cast<char *>(minimalPDF), 0, strlen(minimalPDF), Object(objNull));
    return std::make_unique<PDFDoc>(stream);
}

TEST_F(AnnotLineTest_839, GetY2ReturnsCorrectValue_839) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    // Set vertices and check Y2
    annot->setVertices(10.0, 20.0, 30.0, 40.0);
    EXPECT_DOUBLE_EQ(40.0, annot->getY2());
}

TEST_F(AnnotLineTest_839, GetY2AfterSettingZeroCoordinates_839) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setVertices(0.0, 0.0, 0.0, 0.0);
    EXPECT_DOUBLE_EQ(0.0, annot->getY2());
}

TEST_F(AnnotLineTest_839, GetY2WithNegativeCoordinates_839) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(-100, -100, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setVertices(-50.0, -25.0, -75.0, -99.5);
    EXPECT_DOUBLE_EQ(-99.5, annot->getY2());
}

TEST_F(AnnotLineTest_839, GetY2WithLargeValues_839) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 1e6, 1e6);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setVertices(0.0, 0.0, 500000.0, 999999.99);
    EXPECT_DOUBLE_EQ(999999.99, annot->getY2());
}

TEST_F(AnnotLineTest_839, GetAllCoordinatesAfterSetVertices_839) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 200, 200);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setVertices(1.5, 2.5, 3.5, 4.5);
    EXPECT_DOUBLE_EQ(1.5, annot->getX1());
    EXPECT_DOUBLE_EQ(2.5, annot->getY1());
    EXPECT_DOUBLE_EQ(3.5, annot->getX2());
    EXPECT_DOUBLE_EQ(4.5, annot->getY2());
}

TEST_F(AnnotLineTest_839, GetY2UpdatesAfterMultipleSetVerticesCalls_839) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 500, 500);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setVertices(10.0, 20.0, 30.0, 40.0);
    EXPECT_DOUBLE_EQ(40.0, annot->getY2());

    annot->setVertices(100.0, 200.0, 300.0, 400.0);
    EXPECT_DOUBLE_EQ(400.0, annot->getY2());

    annot->setVertices(0.0, 0.0, 0.0, 0.001);
    EXPECT_DOUBLE_EQ(0.001, annot->getY2());
}

TEST_F(AnnotLineTest_839, GetY2WithFractionalValues_839) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());

    annot->setVertices(0.1, 0.2, 0.3, 0.123456789);
    EXPECT_DOUBLE_EQ(0.123456789, annot->getY2());
}
