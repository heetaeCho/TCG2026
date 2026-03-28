#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "TextOutputDev.h"
#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

// Since TextBlock requires a TextPage and rotation, and we need to test
// the public interface without re-implementing internals, we'll focus
// on what's observable through the public API.

class TextBlockTest_1205 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }
};

// Test that a newly constructed TextBlock has null lines (no lines added yet)
TEST_F(TextBlockTest_1205, NewBlockHasNullLines_1205) {
    // TextBlock requires a TextPage*, but we can try with nullptr
    // if the constructor doesn't immediately dereference it.
    // This tests the getLines() accessor on a fresh block.
    // Note: This may or may not work depending on constructor behavior.
    // We're testing the observable interface.
    TextPage *page = new TextPage(false, 0);
    TextBlock block(page, 0);
    
    const TextLine *lines = block.getLines();
    // A newly created block with no words added should have no lines
    EXPECT_EQ(lines, nullptr);
    
    delete page;
}

// Test that getNext returns nullptr for a standalone block
TEST_F(TextBlockTest_1205, NewBlockHasNullNext_1205) {
    TextPage *page = new TextPage(false, 0);
    TextBlock block(page, 0);
    
    const TextBlock *next = block.getNext();
    EXPECT_EQ(next, nullptr);
    
    delete page;
}

// Test that getLineCount returns 0 for a new block
TEST_F(TextBlockTest_1205, NewBlockHasZeroLineCount_1205) {
    TextPage *page = new TextPage(false, 0);
    TextBlock block(page, 0);
    
    int lineCount = block.getLineCount();
    EXPECT_EQ(lineCount, 0);
    
    delete page;
}

// Test getBBox with pointer parameters on a new block
TEST_F(TextBlockTest_1205, GetBBoxPointersOnNewBlock_1205) {
    TextPage *page = new TextPage(false, 0);
    TextBlock block(page, 0);
    
    double xMin, yMin, xMax, yMax;
    block.getBBox(&xMin, &yMin, &xMax, &yMax);
    
    // For a new block with no content, bounding box values should be
    // some initial/default values. We just verify the function doesn't crash.
    // The exact values depend on implementation.
    SUCCEED();
    
    delete page;
}

// Test getBBox returning PDFRectangle on a new block
TEST_F(TextBlockTest_1205, GetBBoxRectangleOnNewBlock_1205) {
    TextPage *page = new TextPage(false, 0);
    TextBlock block(page, 0);
    
    PDFRectangle rect = block.getBBox();
    
    // Just verify it doesn't crash and returns something
    // We can check that the rect has some defined values
    SUCCEED();
    
    delete page;
}

// Test that copy constructor is deleted (compile-time check - we verify it's non-copyable)
// This is verified by the = delete declaration, so we just note it.

// Test that assignment operator is deleted (compile-time check)
// This is verified by the = delete declaration.

// Test with different rotation values
TEST_F(TextBlockTest_1205, ConstructWithRotation0_1205) {
    TextPage *page = new TextPage(false, 0);
    TextBlock block(page, 0);
    
    EXPECT_EQ(block.getLines(), nullptr);
    EXPECT_EQ(block.getNext(), nullptr);
    EXPECT_EQ(block.getLineCount(), 0);
    
    delete page;
}

TEST_F(TextBlockTest_1205, ConstructWithRotation1_1205) {
    TextPage *page = new TextPage(false, 0);
    TextBlock block(page, 1);
    
    EXPECT_EQ(block.getLines(), nullptr);
    EXPECT_EQ(block.getNext(), nullptr);
    EXPECT_EQ(block.getLineCount(), 0);
    
    delete page;
}

TEST_F(TextBlockTest_1205, ConstructWithRotation2_1205) {
    TextPage *page = new TextPage(false, 0);
    TextBlock block(page, 2);
    
    EXPECT_EQ(block.getLines(), nullptr);
    EXPECT_EQ(block.getNext(), nullptr);
    EXPECT_EQ(block.getLineCount(), 0);
    
    delete page;
}

TEST_F(TextBlockTest_1205, ConstructWithRotation3_1205) {
    TextPage *page = new TextPage(false, 0);
    TextBlock block(page, 3);
    
    EXPECT_EQ(block.getLines(), nullptr);
    EXPECT_EQ(block.getNext(), nullptr);
    EXPECT_EQ(block.getLineCount(), 0);
    
    delete page;
}

// Test getBBox consistency between the two overloads
TEST_F(TextBlockTest_1205, GetBBoxConsistency_1205) {
    TextPage *page = new TextPage(false, 0);
    TextBlock block(page, 0);
    
    double xMin, yMin, xMax, yMax;
    block.getBBox(&xMin, &yMin, &xMax, &yMax);
    
    PDFRectangle rect = block.getBBox();
    
    EXPECT_DOUBLE_EQ(xMin, rect.x1);
    EXPECT_DOUBLE_EQ(yMin, rect.y1);
    EXPECT_DOUBLE_EQ(xMax, rect.x2);
    EXPECT_DOUBLE_EQ(yMax, rect.y2);
    
    delete page;
}

// Test const correctness of getLines
TEST_F(TextBlockTest_1205, GetLinesIsConst_1205) {
    TextPage *page = new TextPage(false, 0);
    const TextBlock block(page, 0);
    
    // Should compile since getLines() is const
    const TextLine *lines = block.getLines();
    EXPECT_EQ(lines, nullptr);
    
    delete page;
}

// Test const correctness of getNext
TEST_F(TextBlockTest_1205, GetNextIsConst_1205) {
    TextPage *page = new TextPage(false, 0);
    const TextBlock block(page, 0);
    
    // Should compile since getNext() is const
    const TextBlock *next = block.getNext();
    EXPECT_EQ(next, nullptr);
    
    delete page;
}

// Test const correctness of getLineCount
TEST_F(TextBlockTest_1205, GetLineCountIsConst_1205) {
    TextPage *page = new TextPage(false, 0);
    const TextBlock block(page, 0);
    
    int count = block.getLineCount();
    EXPECT_EQ(count, 0);
    
    delete page;
}
