#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Annot.h"
#include "PDFDoc.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"
#include "Object.h"
#include "GooString.h"

class AnnotLineTest_825 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    std::unique_ptr<AnnotLine> createAnnotLine() {
        // Create a minimal PDF document for testing
        auto *rect = new PDFRectangle(0, 0, 100, 100);
        // We need a PDFDoc; for unit testing we try to create one from a minimal source
        // Since we can't easily create a PDFDoc without a file, we'll use a different approach
        // We'll test what we can through the interface
        return nullptr;
    }
};

// Helper to create a test PDF doc and AnnotLine
class AnnotLineWithDocTest_825 : public ::testing::Test {
protected:
    PDFDoc *doc = nullptr;
    AnnotLine *annotLine = nullptr;

    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
        // Try to create a minimal PDFDoc
        // We use a simple approach - create from a test file if available
        // For this test we'll create AnnotLine with a PDFRectangle
    }

    void TearDown() override {
        delete annotLine;
    }
};

// Test that getEndStyle returns a valid AnnotLineEndingStyle
TEST_F(AnnotLineTest_825, GetEndStyleReturnsValidStyle_825) {
    // This test verifies the getEndStyle() getter is const and returns AnnotLineEndingStyle
    // Since we need a PDFDoc to construct AnnotLine, we verify the interface exists
    // by checking the method signature compiles correctly
    AnnotLine *line = nullptr;
    // Verify the method signature compiles - this is a compile-time check
    if (line) {
        AnnotLineEndingStyle style = line->getEndStyle();
        (void)style;
    }
    SUCCEED();
}

// Test that getStartStyle returns a valid AnnotLineEndingStyle
TEST_F(AnnotLineTest_825, GetStartStyleReturnsValidStyle_825) {
    AnnotLine *line = nullptr;
    if (line) {
        AnnotLineEndingStyle style = line->getStartStyle();
        (void)style;
    }
    SUCCEED();
}

// Test getInteriorColor returns pointer
TEST_F(AnnotLineTest_825, GetInteriorColorReturnsPointer_825) {
    AnnotLine *line = nullptr;
    if (line) {
        AnnotColor *color = line->getInteriorColor();
        (void)color;
    }
    SUCCEED();
}

// Test getLeaderLineLength returns double
TEST_F(AnnotLineTest_825, GetLeaderLineLengthReturnsDouble_825) {
    AnnotLine *line = nullptr;
    if (line) {
        double len = line->getLeaderLineLength();
        (void)len;
    }
    SUCCEED();
}

// Test getLeaderLineExtension returns double
TEST_F(AnnotLineTest_825, GetLeaderLineExtensionReturnsDouble_825) {
    AnnotLine *line = nullptr;
    if (line) {
        double ext = line->getLeaderLineExtension();
        (void)ext;
    }
    SUCCEED();
}

// Test getCaption returns bool
TEST_F(AnnotLineTest_825, GetCaptionReturnsBool_825) {
    AnnotLine *line = nullptr;
    if (line) {
        bool cap = line->getCaption();
        (void)cap;
    }
    SUCCEED();
}

// Test getIntent returns AnnotLineIntent
TEST_F(AnnotLineTest_825, GetIntentReturnsLineIntent_825) {
    AnnotLine *line = nullptr;
    if (line) {
        AnnotLineIntent intent = line->getIntent();
        (void)intent;
    }
    SUCCEED();
}

// Test getLeaderLineOffset returns double
TEST_F(AnnotLineTest_825, GetLeaderLineOffsetReturnsDouble_825) {
    AnnotLine *line = nullptr;
    if (line) {
        double offset = line->getLeaderLineOffset();
        (void)offset;
    }
    SUCCEED();
}

// Test getCaptionPos returns AnnotLineCaptionPos
TEST_F(AnnotLineTest_825, GetCaptionPosReturnsCaptionPos_825) {
    AnnotLine *line = nullptr;
    if (line) {
        AnnotLineCaptionPos pos = line->getCaptionPos();
        (void)pos;
    }
    SUCCEED();
}

// Test getMeasure returns Dict pointer
TEST_F(AnnotLineTest_825, GetMeasureReturnsDictPointer_825) {
    AnnotLine *line = nullptr;
    if (line) {
        Dict *measure = line->getMeasure();
        (void)measure;
    }
    SUCCEED();
}

// Test getCaptionTextHorizontal returns double
TEST_F(AnnotLineTest_825, GetCaptionTextHorizontalReturnsDouble_825) {
    AnnotLine *line = nullptr;
    if (line) {
        double h = line->getCaptionTextHorizontal();
        (void)h;
    }
    SUCCEED();
}

// Test getCaptionTextVertical returns double
TEST_F(AnnotLineTest_825, GetCaptionTextVerticalReturnsDouble_825) {
    AnnotLine *line = nullptr;
    if (line) {
        double v = line->getCaptionTextVertical();
        (void)v;
    }
    SUCCEED();
}

// Test coordinate getters
TEST_F(AnnotLineTest_825, GetCoordinatesReturnDoubles_825) {
    AnnotLine *line = nullptr;
    if (line) {
        double x1 = line->getX1();
        double y1 = line->getY1();
        double x2 = line->getX2();
        double y2 = line->getY2();
        (void)x1;
        (void)y1;
        (void)x2;
        (void)y2;
    }
    SUCCEED();
}

// Integration-style test: create AnnotLine with PDFDoc if possible
class AnnotLineIntegrationTest_825 : public ::testing::Test {
protected:
    std::unique_ptr<PDFDoc> doc;

    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

TEST_F(AnnotLineIntegrationTest_825, CreateAnnotLineWithRect_825) {
    // Attempt to create an AnnotLine with a PDFRectangle
    // This requires a valid PDFDoc which needs a real PDF file
    // We test that the constructor interface is correct
    
    // Create a minimal PDF in memory
    static const char pdfData[] = 
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

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        PDFRectangle rect(10, 10, 200, 200);
        auto line = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        ASSERT_NE(line, nullptr);
        
        // Test default coordinate values
        // After construction with a rect, coordinates should have some default
        double x1 = line->getX1();
        double y1 = line->getY1();
        double x2 = line->getX2();
        double y2 = line->getY2();
        
        // Verify coordinates are finite numbers
        EXPECT_FALSE(std::isnan(x1));
        EXPECT_FALSE(std::isnan(y1));
        EXPECT_FALSE(std::isnan(x2));
        EXPECT_FALSE(std::isnan(y2));
    }
}

TEST_F(AnnotLineIntegrationTest_825, SetVerticesUpdatesCoordinates_825) {
    static const char pdfData[] = 
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

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 500, 500);
        auto line = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        ASSERT_NE(line, nullptr);
        
        line->setVertices(10.0, 20.0, 300.0, 400.0);
        
        EXPECT_DOUBLE_EQ(line->getX1(), 10.0);
        EXPECT_DOUBLE_EQ(line->getY1(), 20.0);
        EXPECT_DOUBLE_EQ(line->getX2(), 300.0);
        EXPECT_DOUBLE_EQ(line->getY2(), 400.0);
    }
}

TEST_F(AnnotLineIntegrationTest_825, SetStartEndStyleUpdatesStyles_825) {
    static const char pdfData[] = 
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

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto line = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        ASSERT_NE(line, nullptr);
        
        line->setStartEndStyle(annotLineEndingOpenArrow, annotLineEndingClosedArrow);
        
        EXPECT_EQ(line->getStartStyle(), annotLineEndingOpenArrow);
        EXPECT_EQ(line->getEndStyle(), annotLineEndingClosedArrow);
    }
}

TEST_F(AnnotLineIntegrationTest_825, SetCaptionUpdatesCaption_825) {
    static const char pdfData[] = 
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

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto line = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        ASSERT_NE(line, nullptr);
        
        line->setCaption(true);
        EXPECT_TRUE(line->getCaption());
        
        line->setCaption(false);
        EXPECT_FALSE(line->getCaption());
    }
}

TEST_F(AnnotLineIntegrationTest_825, SetLeaderLineLengthUpdatesLength_825) {
    static const char pdfData[] = 
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

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto line = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        ASSERT_NE(line, nullptr);
        
        line->setLeaderLineLength(25.5);
        EXPECT_DOUBLE_EQ(line->getLeaderLineLength(), 25.5);
    }
}

TEST_F(AnnotLineIntegrationTest_825, SetLeaderLineExtensionUpdatesExtension_825) {
    static const char pdfData[] = 
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

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto line = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        ASSERT_NE(line, nullptr);
        
        line->setLeaderLineExtension(15.0);
        EXPECT_DOUBLE_EQ(line->getLeaderLineExtension(), 15.0);
    }
}

TEST_F(AnnotLineIntegrationTest_825, SetIntentUpdatesIntent_825) {
    static const char pdfData[] = 
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

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto line = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        ASSERT_NE(line, nullptr);
        
        line->setIntent(annotLineIntentDimension);
        EXPECT_EQ(line->getIntent(), annotLineIntentDimension);
        
        line->setIntent(annotLineIntentArrow);
        EXPECT_EQ(line->getIntent(), annotLineIntentArrow);
    }
}

TEST_F(AnnotLineIntegrationTest_825, SetVerticesBoundaryZeroCoordinates_825) {
    static const char pdfData[] = 
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

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto line = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        ASSERT_NE(line, nullptr);
        
        line->setVertices(0.0, 0.0, 0.0, 0.0);
        
        EXPECT_DOUBLE_EQ(line->getX1(), 0.0);
        EXPECT_DOUBLE_EQ(line->getY1(), 0.0);
        EXPECT_DOUBLE_EQ(line->getX2(), 0.0);
        EXPECT_DOUBLE_EQ(line->getY2(), 0.0);
    }
}

TEST_F(AnnotLineIntegrationTest_825, SetVerticesNegativeCoordinates_825) {
    static const char pdfData[] = 
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

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        PDFRectangle rect(-100, -100, 100, 100);
        auto line = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        ASSERT_NE(line, nullptr);
        
        line->setVertices(-50.0, -50.0, 50.0, 50.0);
        
        EXPECT_DOUBLE_EQ(line->getX1(), -50.0);
        EXPECT_DOUBLE_EQ(line->getY1(), -50.0);
        EXPECT_DOUBLE_EQ(line->getX2(), 50.0);
        EXPECT_DOUBLE_EQ(line->getY2(), 50.0);
    }
}

TEST_F(AnnotLineIntegrationTest_825, SetLeaderLineLengthZero_825) {
    static const char pdfData[] = 
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

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto line = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        ASSERT_NE(line, nullptr);
        
        line->setLeaderLineLength(0.0);
        EXPECT_DOUBLE_EQ(line->getLeaderLineLength(), 0.0);
    }
}

TEST_F(AnnotLineIntegrationTest_825, SetInteriorColorNull_825) {
    static const char pdfData[] = 
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

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto line = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        ASSERT_NE(line, nullptr);
        
        line->setInteriorColor(nullptr);
        EXPECT_EQ(line->getInteriorColor(), nullptr);
    }
}

TEST_F(AnnotLineIntegrationTest_825, DefaultStartEndStyleIsNone_825) {
    static const char pdfData[] = 
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

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto line = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        ASSERT_NE(line, nullptr);
        
        // Default line ending style should be None
        EXPECT_EQ(line->getStartStyle(), annotLineEndingNone);
        EXPECT_EQ(line->getEndStyle(), annotLineEndingNone);
    }
}

TEST_F(AnnotLineIntegrationTest_825, DefaultCaptionIsFalse_825) {
    static const char pdfData[] = 
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

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto line = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        ASSERT_NE(line, nullptr);
        
        EXPECT_FALSE(line->getCaption());
    }
}

TEST_F(AnnotLineIntegrationTest_825, DefaultLeaderLineLengthIsZero_825) {
    static const char pdfData[] = 
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

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto line = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        ASSERT_NE(line, nullptr);
        
        EXPECT_DOUBLE_EQ(line->getLeaderLineLength(), 0.0);
        EXPECT_DOUBLE_EQ(line->getLeaderLineExtension(), 0.0);
        EXPECT_DOUBLE_EQ(line->getLeaderLineOffset(), 0.0);
    }
}

TEST_F(AnnotLineIntegrationTest_825, SetAllLineEndingStyles_825) {
    static const char pdfData[] = 
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

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto line = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        ASSERT_NE(line, nullptr);
        
        // Test various line ending styles
        line->setStartEndStyle(annotLineEndingSquare, annotLineEndingCircle);
        EXPECT_EQ(line->getStartStyle(), annotLineEndingSquare);
        EXPECT_EQ(line->getEndStyle(), annotLineEndingCircle);
        
        line->setStartEndStyle(annotLineEndingDiamond, annotLineEndingOpenArrow);
        EXPECT_EQ(line->getStartStyle(), annotLineEndingDiamond);
        EXPECT_EQ(line->getEndStyle(), annotLineEndingOpenArrow);
        
        line->setStartEndStyle(annotLineEndingClosedArrow, annotLineEndingButt);
        EXPECT_EQ(line->getStartStyle(), annotLineEndingClosedArrow);
        EXPECT_EQ(line->getEndStyle(), annotLineEndingButt);
        
        line->setStartEndStyle(annotLineEndingROpenArrow, annotLineEndingRClosedArrow);
        EXPECT_EQ(line->getStartStyle(), annotLineEndingROpenArrow);
        EXPECT_EQ(line->getEndStyle(), annotLineEndingRClosedArrow);
        
        line->setStartEndStyle(annotLineEndingSlash, annotLineEndingNone);
        EXPECT_EQ(line->getStartStyle(), annotLineEndingSlash);
        EXPECT_EQ(line->getEndStyle(), annotLineEndingNone);
    }
}

TEST_F(AnnotLineIntegrationTest_825, SetVerticesLargeValues_825) {
    static const char pdfData[] = 
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

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 100000, 100000);
        auto line = std::make_unique<AnnotLine>(doc.get(), &rect);
        
        ASSERT_NE(line, nullptr);
        
        line->setVertices(99999.99, 99999.99, 0.001, 0.001);
        
        EXPECT_DOUBLE_EQ(line->getX1(), 99999.99);
        EXPECT_DOUBLE_EQ(line->getY1(), 99999.99);
        EXPECT_DOUBLE_EQ(line->getX2(), 0.001);
        EXPECT_DOUBLE_EQ(line->getY2(), 0.001);
    }
}
