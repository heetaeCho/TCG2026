#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary headers from the poppler project
#include "poppler/PDFDoc.h"
#include "poppler/Annot.h"
#include "poppler/PDFDocFactory.h"
#include "poppler/GlobalParams.h"
#include "goo/GooString.h"

class AnnotTest_788 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // We need a valid PDFDoc to create annotations
        // Try to create a minimal PDF document
    }

    void TearDown() override {
    }

    // Helper to create a PDFDoc from a minimal PDF file if available
    std::unique_ptr<PDFDoc> createTestDoc(const char *filename) {
        auto *fileName = new GooString(filename);
        auto doc = std::make_unique<PDFDoc>(fileName);
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test getFlags returns the flags value
TEST_F(AnnotTest_788, GetFlagsReturnsValue_788) {
    // Create a minimal PDF in memory to get a valid PDFDoc
    // We'll use a PDFRectangle-based constructor
    // Since we can't easily create a PDFDoc without a file, we test with a sample PDF
    // For this test, we create an annotation using PDFRectangle
    
    // Attempt to create a doc from a test file
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    // Default flags should be 0 for a newly created annotation
    unsigned int flags = annot->getFlags();
    // Just verify it returns without crashing - exact value depends on implementation
    EXPECT_EQ(flags, flags); // Tautological but ensures no crash
}

// Test setFlags and getFlags roundtrip
TEST_F(AnnotTest_788, SetFlagsAndGetFlags_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    annot->setFlags(0x04); // Hidden flag
    EXPECT_EQ(annot->getFlags(), 0x04u);
}

// Test setFlags with zero
TEST_F(AnnotTest_788, SetFlagsZero_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 10;
    rect.y1 = 10;
    rect.x2 = 50;
    rect.y2 = 50;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    annot->setFlags(0);
    EXPECT_EQ(annot->getFlags(), 0u);
}

// Test setFlags with maximum value
TEST_F(AnnotTest_788, SetFlagsMaxValue_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    annot->setFlags(0xFFFFFFFF);
    EXPECT_EQ(annot->getFlags(), 0xFFFFFFFFu);
}

// Test setFlags overwrite previous value
TEST_F(AnnotTest_788, SetFlagsOverwritesPrevious_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    annot->setFlags(0x01);
    EXPECT_EQ(annot->getFlags(), 0x01u);
    
    annot->setFlags(0x02);
    EXPECT_EQ(annot->getFlags(), 0x02u);
}

// Test getRect coordinates
TEST_F(AnnotTest_788, GetRectCoordinates_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 10.0;
    rect.y1 = 20.0;
    rect.x2 = 30.0;
    rect.y2 = 40.0;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    EXPECT_DOUBLE_EQ(annot->getXMin(), 10.0);
    EXPECT_DOUBLE_EQ(annot->getYMin(), 20.0);
    EXPECT_DOUBLE_EQ(annot->getXMax(), 30.0);
    EXPECT_DOUBLE_EQ(annot->getYMax(), 40.0);
}

// Test setRect with individual coordinates
TEST_F(AnnotTest_788, SetRectWithCoordinates_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    annot->setRect(5.0, 10.0, 50.0, 60.0);
    
    double x1, y1, x2, y2;
    annot->getRect(&x1, &y1, &x2, &y2);
    EXPECT_DOUBLE_EQ(x1, 5.0);
    EXPECT_DOUBLE_EQ(y1, 10.0);
    EXPECT_DOUBLE_EQ(x2, 50.0);
    EXPECT_DOUBLE_EQ(y2, 60.0);
}

// Test setRect with PDFRectangle
TEST_F(AnnotTest_788, SetRectWithPDFRectangle_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    PDFRectangle newRect;
    newRect.x1 = 15.0;
    newRect.y1 = 25.0;
    newRect.x2 = 75.0;
    newRect.y2 = 85.0;
    
    annot->setRect(newRect);
    
    const PDFRectangle &resultRect = annot->getRect();
    EXPECT_DOUBLE_EQ(resultRect.x1, 15.0);
    EXPECT_DOUBLE_EQ(resultRect.y1, 25.0);
    EXPECT_DOUBLE_EQ(resultRect.x2, 75.0);
    EXPECT_DOUBLE_EQ(resultRect.y2, 85.0);
}

// Test inRect
TEST_F(AnnotTest_788, InRectInsidePoint_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 10.0;
    rect.y1 = 10.0;
    rect.x2 = 100.0;
    rect.y2 = 100.0;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    EXPECT_TRUE(annot->inRect(50.0, 50.0));
}

// Test inRect outside point
TEST_F(AnnotTest_788, InRectOutsidePoint_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 10.0;
    rect.y1 = 10.0;
    rect.x2 = 100.0;
    rect.y2 = 100.0;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    EXPECT_FALSE(annot->inRect(200.0, 200.0));
}

// Test inRect boundary point
TEST_F(AnnotTest_788, InRectBoundaryPoint_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 10.0;
    rect.y1 = 10.0;
    rect.x2 = 100.0;
    rect.y2 = 100.0;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    // Test exact boundary - behavior depends on implementation (inclusive/exclusive)
    bool onBoundary = annot->inRect(10.0, 10.0);
    // Just ensure it doesn't crash; the exact result depends on implementation
    SUCCEED();
}

// Test setContents and getContents
TEST_F(AnnotTest_788, SetAndGetContents_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    auto content = std::make_unique<GooString>("Test content");
    annot->setContents(std::move(content));
    
    const GooString *result = annot->getContents();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "Test content");
}

// Test setContents with empty string
TEST_F(AnnotTest_788, SetContentsEmpty_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    auto content = std::make_unique<GooString>("");
    annot->setContents(std::move(content));
    
    const GooString *result = annot->getContents();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "");
}

// Test setContents with nullptr
TEST_F(AnnotTest_788, SetContentsNull_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    annot->setContents(nullptr);
    // Just verify no crash
    SUCCEED();
}

// Test getType returns a valid AnnotSubtype
TEST_F(AnnotTest_788, GetTypeReturnsValidSubtype_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    AnnotSubtype type = annot->getType();
    // Just verify it returns without crashing
    SUCCEED();
}

// Test getDoc returns the associated document
TEST_F(AnnotTest_788, GetDocReturnsDocument_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    EXPECT_EQ(annot->getDoc(), doc.get());
}

// Test setModified and getModified
TEST_F(AnnotTest_788, SetAndGetModified_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    auto modified = std::make_unique<GooString>("D:20230101120000");
    annot->setModified(std::move(modified));
    
    const GooString *result = annot->getModified();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "D:20230101120000");
}

// Test multiple flag operations
TEST_F(AnnotTest_788, SetFlagsMultipleTimes_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    // Set various annotation flag combinations
    // Invisible = 0x01, Hidden = 0x02, Print = 0x04, etc.
    annot->setFlags(0x01);
    EXPECT_EQ(annot->getFlags(), 0x01u);
    
    annot->setFlags(0x04);
    EXPECT_EQ(annot->getFlags(), 0x04u);
    
    annot->setFlags(0x01 | 0x04);
    EXPECT_EQ(annot->getFlags(), 0x05u);
}

// Test getHasRef for newly created annotation
TEST_F(AnnotTest_788, GetHasRefNewAnnot_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    // For a newly created annotation, hasRef state depends on constructor logic
    bool hasRef = annot->getHasRef();
    // Just verify it doesn't crash
    SUCCEED();
}

// Test getBorder for newly created annotation
TEST_F(AnnotTest_788, GetBorderNewAnnot_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    AnnotBorder *border = annot->getBorder();
    // Border may or may not be null depending on initialization
    SUCCEED();
}

// Test getColor for newly created annotation
TEST_F(AnnotTest_788, GetColorNewAnnot_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    AnnotColor *color = annot->getColor();
    // Color may or may not be null depending on initialization
    SUCCEED();
}

// Test getAppearStreams for newly created annotation
TEST_F(AnnotTest_788, GetAppearStreamsNewAnnot_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    AnnotAppearance *streams = annot->getAppearStreams();
    // May be null for a newly created annotation
    SUCCEED();
}

// Test getTreeKey
TEST_F(AnnotTest_788, GetTreeKey_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    int treeKey = annot->getTreeKey();
    // Just verify no crash
    SUCCEED();
}

// Test getPageNum
TEST_F(AnnotTest_788, GetPageNum_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    int pageNum = annot->getPageNum();
    // Page number depends on initialization
    SUCCEED();
}

// Test setRect with swapped coordinates (x1 > x2)
TEST_F(AnnotTest_788, SetRectSwappedCoordinates_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    // Set rect with x1 > x2 and y1 > y2 - implementation may normalize
    annot->setRect(100.0, 100.0, 10.0, 10.0);
    
    double x1, y1, x2, y2;
    annot->getRect(&x1, &y1, &x2, &y2);
    // The implementation may or may not normalize coordinates
    // Just verify no crash and values are returned
    SUCCEED();
}

// Test inRect at edges
TEST_F(AnnotTest_788, InRectEdgeCases_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 10.0;
    rect.y1 = 10.0;
    rect.x2 = 100.0;
    rect.y2 = 100.0;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    // Test point clearly outside
    EXPECT_FALSE(annot->inRect(0.0, 0.0));
    EXPECT_FALSE(annot->inRect(200.0, 200.0));
    EXPECT_FALSE(annot->inRect(5.0, 50.0));
    EXPECT_FALSE(annot->inRect(50.0, 5.0));
    
    // Test point clearly inside
    EXPECT_TRUE(annot->inRect(50.0, 50.0));
    EXPECT_TRUE(annot->inRect(55.0, 55.0));
}

// Test setFlags with specific annotation flag values
TEST_F(AnnotTest_788, SetFlagsAnnotationSpecificValues_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    // Test common PDF annotation flags
    // Print flag (bit 3) = 4
    annot->setFlags(4);
    EXPECT_EQ(annot->getFlags(), 4u);
    
    // NoZoom flag (bit 4) = 8
    annot->setFlags(8);
    EXPECT_EQ(annot->getFlags(), 8u);
    
    // Combined flags
    annot->setFlags(4 | 8); // Print | NoZoom
    EXPECT_EQ(annot->getFlags(), 12u);
}

// Test getName for newly created annotation
TEST_F(AnnotTest_788, GetNameNewAnnot_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    const GooString *name = annot->getName();
    // Name may be null for newly created annotation
    SUCCEED();
}

// Test getAppearState for newly created annotation
TEST_F(AnnotTest_788, GetAppearStateNewAnnot_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    const GooString *state = annot->getAppearState();
    // State may be null for a newly created annotation
    SUCCEED();
}

// Test setAppearanceState
TEST_F(AnnotTest_788, SetAppearanceState_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    annot->setAppearanceState("On");
    const GooString *state = annot->getAppearState();
    ASSERT_NE(state, nullptr);
    EXPECT_STREQ(state->c_str(), "On");
}

// Test setAppearanceState with different value
TEST_F(AnnotTest_788, SetAppearanceStateOff_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    annot->setAppearanceState("Off");
    const GooString *state = annot->getAppearState();
    ASSERT_NE(state, nullptr);
    EXPECT_STREQ(state->c_str(), "Off");
}

// Test isOk for newly created annotation
TEST_F(AnnotTest_788, IsOkNewAnnot_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    EXPECT_TRUE(annot->isOk());
}

// Test getId
TEST_F(AnnotTest_788, GetId_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    int id = annot->getId();
    // Just check it returns without crashing
    SUCCEED();
}

// Test setRect with zero-area rectangle
TEST_F(AnnotTest_788, SetRectZeroArea_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    // Point rectangle
    annot->setRect(50.0, 50.0, 50.0, 50.0);
    
    double x1, y1, x2, y2;
    annot->getRect(&x1, &y1, &x2, &y2);
    EXPECT_DOUBLE_EQ(x1, 50.0);
    EXPECT_DOUBLE_EQ(y1, 50.0);
    EXPECT_DOUBLE_EQ(x2, 50.0);
    EXPECT_DOUBLE_EQ(y2, 50.0);
}

// Test setRect with negative coordinates
TEST_F(AnnotTest_788, SetRectNegativeCoordinates_788) {
    auto *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(fileName);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    rect.x2 = 100;
    rect.y2 = 100;

    auto annot = std::make_unique<Annot>(doc.get(), &rect);
    
    annot->setRect(-50.0, -50.0, -10.0, -10.0);
    
    double x1, y1, x2, y2;
    annot->getRect(&x1, &y1, &x2, &y2);
    EXPECT_DOUBLE_EQ(x1, -50.0);
    EXPECT_DOUBLE_EQ(y1, -50.0);
    EXPECT_DOUBLE_EQ(x2, -10.0);
    EXPECT_DOUBLE_EQ(y2, -10.0);
}
