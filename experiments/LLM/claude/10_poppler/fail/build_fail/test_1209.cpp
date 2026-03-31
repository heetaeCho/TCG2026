#include <gtest/gtest.h>
#include <gmock/gmock.h>

// We need to include the necessary headers from poppler
#include "TextOutputDev.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GfxState.h"

#include <memory>
#include <cstring>

// Since TextBlock requires a TextPage which requires complex setup,
// and we must treat the implementation as a black box, we test
// what we can through the public interface.

class TextBlockTest_1209 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // TextPage requires a rotation value (0, 1, 2, or 3)
        // We create a TextPage to use for TextBlock construction
    }

    void TearDown() override {
    }
};

// Test that a newly created TextBlock has zero line count
TEST_F(TextBlockTest_1209, NewBlockHasZeroLineCount_1209) {
    // TextBlock requires a TextPage* and rotation int
    // TextPage constructor: TextPage(bool rawOrderA, int rotateA)
    TextPage *page = new TextPage(false);
    TextBlock *block = new TextBlock(page, 0);

    EXPECT_EQ(block->getLineCount(), 0);

    delete block;
    page->decRefCnt();
}

// Test that getLines returns nullptr for a newly created TextBlock (no lines added)
TEST_F(TextBlockTest_1209, NewBlockHasNullLines_1209) {
    TextPage *page = new TextPage(false);
    TextBlock *block = new TextBlock(page, 0);

    const TextLine *lines = block->getLines();
    EXPECT_EQ(lines, nullptr);

    delete block;
    page->decRefCnt();
}

// Test that getNext returns nullptr for a newly created TextBlock
TEST_F(TextBlockTest_1209, NewBlockHasNullNext_1209) {
    TextPage *page = new TextPage(false);
    TextBlock *block = new TextBlock(page, 0);

    const TextBlock *next = block->getNext();
    EXPECT_EQ(next, nullptr);

    delete block;
    page->decRefCnt();
}

// Test getBBox with pointer parameters for a newly created TextBlock
TEST_F(TextBlockTest_1209, GetBBoxReturnsValues_1209) {
    TextPage *page = new TextPage(false);
    TextBlock *block = new TextBlock(page, 0);

    double xMin = -1, yMin = -1, xMax = -1, yMax = -1;
    block->getBBox(&xMin, &yMin, &xMax, &yMax);

    // For a new block with no words, the bbox values should be initialized
    // We just verify the function doesn't crash and returns some values
    // The exact values depend on implementation, but they should be finite
    EXPECT_FALSE(std::isnan(xMin));
    EXPECT_FALSE(std::isnan(yMin));
    EXPECT_FALSE(std::isnan(xMax));
    EXPECT_FALSE(std::isnan(yMax));

    delete block;
    page->decRefCnt();
}

// Test getBBox returning PDFRectangle for a newly created TextBlock
TEST_F(TextBlockTest_1209, GetBBoxReturnsPDFRectangle_1209) {
    TextPage *page = new TextPage(false);
    TextBlock *block = new TextBlock(page, 0);

    PDFRectangle rect = block->getBBox();

    // Just verify no crash and values are finite
    EXPECT_FALSE(std::isnan(rect.x1));
    EXPECT_FALSE(std::isnan(rect.y1));
    EXPECT_FALSE(std::isnan(rect.x2));
    EXPECT_FALSE(std::isnan(rect.y2));

    delete block;
    page->decRefCnt();
}

// Test construction with different rotation values
TEST_F(TextBlockTest_1209, ConstructWithRotation0_1209) {
    TextPage *page = new TextPage(false);
    TextBlock *block = new TextBlock(page, 0);

    EXPECT_EQ(block->getLineCount(), 0);
    EXPECT_EQ(block->getLines(), nullptr);
    EXPECT_EQ(block->getNext(), nullptr);

    delete block;
    page->decRefCnt();
}

TEST_F(TextBlockTest_1209, ConstructWithRotation1_1209) {
    TextPage *page = new TextPage(false);
    TextBlock *block = new TextBlock(page, 1);

    EXPECT_EQ(block->getLineCount(), 0);
    EXPECT_EQ(block->getLines(), nullptr);

    delete block;
    page->decRefCnt();
}

TEST_F(TextBlockTest_1209, ConstructWithRotation2_1209) {
    TextPage *page = new TextPage(false);
    TextBlock *block = new TextBlock(page, 2);

    EXPECT_EQ(block->getLineCount(), 0);
    EXPECT_EQ(block->getLines(), nullptr);

    delete block;
    page->decRefCnt();
}

TEST_F(TextBlockTest_1209, ConstructWithRotation3_1209) {
    TextPage *page = new TextPage(false);
    TextBlock *block = new TextBlock(page, 3);

    EXPECT_EQ(block->getLineCount(), 0);
    EXPECT_EQ(block->getLines(), nullptr);

    delete block;
    page->decRefCnt();
}

// Test that getBBox pointer and PDFRectangle versions return consistent results
TEST_F(TextBlockTest_1209, GetBBoxConsistency_1209) {
    TextPage *page = new TextPage(false);
    TextBlock *block = new TextBlock(page, 0);

    double xMin, yMin, xMax, yMax;
    block->getBBox(&xMin, &yMin, &xMax, &yMax);

    PDFRectangle rect = block->getBBox();

    EXPECT_DOUBLE_EQ(xMin, rect.x1);
    EXPECT_DOUBLE_EQ(yMin, rect.y1);
    EXPECT_DOUBLE_EQ(xMax, rect.x2);
    EXPECT_DOUBLE_EQ(yMax, rect.y2);

    delete block;
    page->decRefCnt();
}

// Test that copy constructor is deleted (compile-time check - this test just documents the constraint)
// TextBlock(const TextBlock &) = delete;
// TextBlock &operator=(const TextBlock &) = delete;
// These are compile-time constraints verified by the deleted declarations.

// Test getLineCount returns int type
TEST_F(TextBlockTest_1209, GetLineCountReturnsInt_1209) {
    TextPage *page = new TextPage(false);
    TextBlock *block = new TextBlock(page, 0);

    int count = block->getLineCount();
    EXPECT_GE(count, 0);

    delete block;
    page->decRefCnt();
}

// Test that multiple calls to getLineCount return consistent results
TEST_F(TextBlockTest_1209, GetLineCountConsistentMultipleCalls_1209) {
    TextPage *page = new TextPage(false);
    TextBlock *block = new TextBlock(page, 0);

    int count1 = block->getLineCount();
    int count2 = block->getLineCount();
    int count3 = block->getLineCount();

    EXPECT_EQ(count1, count2);
    EXPECT_EQ(count2, count3);

    delete block;
    page->decRefCnt();
}

// Test that multiple calls to getNext return consistent results
TEST_F(TextBlockTest_1209, GetNextConsistentMultipleCalls_1209) {
    TextPage *page = new TextPage(false);
    TextBlock *block = new TextBlock(page, 0);

    const TextBlock *next1 = block->getNext();
    const TextBlock *next2 = block->getNext();

    EXPECT_EQ(next1, next2);

    delete block;
    page->decRefCnt();
}

// Test that multiple calls to getLines return consistent results
TEST_F(TextBlockTest_1209, GetLinesConsistentMultipleCalls_1209) {
    TextPage *page = new TextPage(false);
    TextBlock *block = new TextBlock(page, 0);

    const TextLine *lines1 = block->getLines();
    const TextLine *lines2 = block->getLines();

    EXPECT_EQ(lines1, lines2);

    delete block;
    page->decRefCnt();
}
