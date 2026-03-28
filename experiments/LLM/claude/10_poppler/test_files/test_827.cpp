#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Annot.h"
#include "PDFDoc.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"
#include "Object.h"
#include "GooString.h"

class AnnotLineTest_827 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // We need a PDFDoc to create annotations. We'll try to create a minimal one.
        // For testing, we create AnnotLine with a rect.
    }

    std::unique_ptr<PDFDoc> loadTestDoc(const char *filename) {
        auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(GooString(filename)));
        return doc;
    }
};

// Test that we can create an AnnotLine with a PDFRectangle and it has default values
TEST_F(AnnotLineTest_827, DefaultLeaderLineLength_827) {
    // We need a valid PDFDoc. Since we may not have a file, we test via known interface.
    // This test verifies the getter returns some value after construction.
    // Without a real PDFDoc, we focus on what we can test from the interface.
    
    // If we cannot create AnnotLine without a valid PDFDoc, we skip.
    // But we can test getLeaderLineLength exists and is callable on a constructed object.
    // For this we need at minimum a PDFDoc.
    
    // Create a minimal PDF in memory
    static const char *minimalPdf = 
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

    // Try to create a PDFDoc from a memory stream
    auto *stream = new MemStream(const_cast<char*>(minimalPdf), 0, strlen(minimalPdf), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
    }

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
    
    // Default leader line length should be 0
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 0.0);
}

TEST_F(AnnotLineTest_827, SetAndGetLeaderLineLength_827) {
    static const char *minimalPdf = 
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

    auto *stream = new MemStream(const_cast<char*>(minimalPdf), 0, strlen(minimalPdf), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
    }

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
    
    annot->setLeaderLineLength(15.5);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 15.5);
}

TEST_F(AnnotLineTest_827, SetAndGetLeaderLineExtension_827) {
    static const char *minimalPdf = 
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

    auto *stream = new MemStream(const_cast<char*>(minimalPdf), 0, strlen(minimalPdf), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
    }

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
    
    annot->setLeaderLineExtension(5.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineExtension(), 5.0);
}

TEST_F(AnnotLineTest_827, SetVerticesAndGetCoordinates_827) {
    static const char *minimalPdf = 
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

    auto *stream = new MemStream(const_cast<char*>(minimalPdf), 0, strlen(minimalPdf), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
    }

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
    
    annot->setVertices(10.0, 20.0, 30.0, 40.0);
    EXPECT_DOUBLE_EQ(annot->getX1(), 10.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), 20.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), 30.0);
    EXPECT_DOUBLE_EQ(annot->getY2(), 40.0);
}

TEST_F(AnnotLineTest_827, SetAndGetCaption_827) {
    static const char *minimalPdf = 
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

    auto *stream = new MemStream(const_cast<char*>(minimalPdf), 0, strlen(minimalPdf), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
    }

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
    
    // Default caption should be false
    EXPECT_FALSE(annot->getCaption());
    
    annot->setCaption(true);
    EXPECT_TRUE(annot->getCaption());
    
    annot->setCaption(false);
    EXPECT_FALSE(annot->getCaption());
}

TEST_F(AnnotLineTest_827, SetAndGetIntent_827) {
    static const char *minimalPdf = 
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

    auto *stream = new MemStream(const_cast<char*>(minimalPdf), 0, strlen(minimalPdf), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
    }

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
    
    annot->setIntent(AnnotLine::intentLineArrow);
    EXPECT_EQ(annot->getIntent(), AnnotLine::intentLineArrow);
    
    annot->setIntent(AnnotLine::intentLineDimension);
    EXPECT_EQ(annot->getIntent(), AnnotLine::intentLineDimension);
}

TEST_F(AnnotLineTest_827, DefaultInteriorColor_827) {
    static const char *minimalPdf = 
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

    auto *stream = new MemStream(const_cast<char*>(minimalPdf), 0, strlen(minimalPdf), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
    }

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
    
    // Default interior color should be nullptr
    EXPECT_EQ(annot->getInteriorColor(), nullptr);
}

TEST_F(AnnotLineTest_827, SetInteriorColor_827) {
    static const char *minimalPdf = 
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

    auto *stream = new MemStream(const_cast<char*>(minimalPdf), 0, strlen(minimalPdf), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
    }

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
    
    auto color = std::make_unique<AnnotColor>(1.0, 0.0, 0.0);
    annot->setInteriorColor(std::move(color));
    EXPECT_NE(annot->getInteriorColor(), nullptr);
}

TEST_F(AnnotLineTest_827, LeaderLineLengthZero_827) {
    static const char *minimalPdf = 
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

    auto *stream = new MemStream(const_cast<char*>(minimalPdf), 0, strlen(minimalPdf), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
    }

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
    
    annot->setLeaderLineLength(0.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 0.0);
}

TEST_F(AnnotLineTest_827, NegativeLeaderLineLength_827) {
    static const char *minimalPdf = 
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

    auto *stream = new MemStream(const_cast<char*>(minimalPdf), 0, strlen(minimalPdf), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
    }

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
    
    annot->setLeaderLineLength(-10.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), -10.0);
}

TEST_F(AnnotLineTest_827, LargeLeaderLineLength_827) {
    static const char *minimalPdf = 
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

    auto *stream = new MemStream(const_cast<char*>(minimalPdf), 0, strlen(minimalPdf), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
    }

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
    
    annot->setLeaderLineLength(1e10);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 1e10);
}

TEST_F(AnnotLineTest_827, DefaultLeaderLineOffset_827) {
    static const char *minimalPdf = 
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

    auto *stream = new MemStream(const_cast<char*>(minimalPdf), 0, strlen(minimalPdf), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
    }

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
    
    EXPECT_DOUBLE_EQ(annot->getLeaderLineOffset(), 0.0);
}

TEST_F(AnnotLineTest_827, DefaultCaptionTextValues_827) {
    static const char *minimalPdf = 
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

    auto *stream = new MemStream(const_cast<char*>(minimalPdf), 0, strlen(minimalPdf), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
    }

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
    
    EXPECT_DOUBLE_EQ(annot->getCaptionTextHorizontal(), 0.0);
    EXPECT_DOUBLE_EQ(annot->getCaptionTextVertical(), 0.0);
}

TEST_F(AnnotLineTest_827, DefaultMeasure_827) {
    static const char *minimalPdf = 
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

    auto *stream = new MemStream(const_cast<char*>(minimalPdf), 0, strlen(minimalPdf), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
    }

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
    
    EXPECT_EQ(annot->getMeasure(), nullptr);
}

TEST_F(AnnotLineTest_827, SetVerticesUpdatesCoordinates_827) {
    static const char *minimalPdf = 
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

    auto *stream = new MemStream(const_cast<char*>(minimalPdf), 0, strlen(minimalPdf), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
    }

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
    
    // Set vertices once
    annot->setVertices(1.0, 2.0, 3.0, 4.0);
    EXPECT_DOUBLE_EQ(annot->getX1(), 1.0);
    EXPECT_DOUBLE_EQ(annot->getY1(), 2.0);
    EXPECT_DOUBLE_EQ(annot->getX2(), 3.0);
    EXPECT_DOUBLE_EQ(annot->getY2(), 4.0);
    
    // Update vertices
    annot->setVertices(100.5, 200.5, 300.5, 400.5);
    EXPECT_DOUBLE_EQ(annot->getX1(), 100.5);
    EXPECT_DOUBLE_EQ(annot->getY1(), 200.5);
    EXPECT_DOUBLE_EQ(annot->getX2(), 300.5);
    EXPECT_DOUBLE_EQ(annot->getY2(), 400.5);
}

TEST_F(AnnotLineTest_827, SetNullInteriorColor_827) {
    static const char *minimalPdf = 
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

    auto *stream = new MemStream(const_cast<char*>(minimalPdf), 0, strlen(minimalPdf), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
    }

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
    
    // Set a color, then reset to null
    auto color = std::make_unique<AnnotColor>(0.0, 1.0, 0.0);
    annot->setInteriorColor(std::move(color));
    EXPECT_NE(annot->getInteriorColor(), nullptr);
    
    annot->setInteriorColor(nullptr);
    EXPECT_EQ(annot->getInteriorColor(), nullptr);
}

TEST_F(AnnotLineTest_827, MultipleLeaderLineLengthUpdates_827) {
    static const char *minimalPdf = 
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

    auto *stream = new MemStream(const_cast<char*>(minimalPdf), 0, strlen(minimalPdf), Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
    }

    auto rect = std::make_unique<PDFRectangle>(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotLine>(doc.get(), rect.get());
    
    annot->setLeaderLineLength(5.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 5.0);
    
    annot->setLeaderLineLength(10.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 10.0);
    
    annot->setLeaderLineLength(0.0);
    EXPECT_DOUBLE_EQ(annot->getLeaderLineLength(), 0.0);
}
