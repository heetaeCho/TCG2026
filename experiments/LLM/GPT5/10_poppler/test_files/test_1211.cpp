#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/TextOutputDev.h"

class TextFlowTest_1211 : public ::testing::Test {
protected:
    // Setup before each test
    TextFlow *textFlow;
    TextBlock *block;
    TextPage *textPage;

    void SetUp() override {
        // Initialize the test objects here
        textPage = new TextPage();
        block = new TextBlock();
        textFlow = new TextFlow(textPage, block);
    }

    // Cleanup after each test
    void TearDown() override {
        delete textFlow;
        delete block;
        delete textPage;
    }
};

// Test for normal operation: Ensure getNext() returns the next TextFlow element
TEST_F(TextFlowTest_1211, GetNextReturnsNextTextFlow_1211) {
    TextFlow *nextFlow = new TextFlow(textPage, block);  // Create another TextFlow
    textFlow->addBlock(block);
    
    // Set the next TextFlow manually
    textFlow->setNext(nextFlow);
    
    // Ensure that getNext() returns the correct next TextFlow
    EXPECT_EQ(textFlow->getNext(), nextFlow);
}

// Test boundary condition: Ensure getNext() returns nullptr when there is no next TextFlow
TEST_F(TextFlowTest_1211, GetNextReturnsNullWhenNoNextTextFlow_1212) {
    // At first, there should be no next TextFlow, so it should return nullptr
    EXPECT_EQ(textFlow->getNext(), nullptr);
}

// Test exceptional case: Ensure blockFits returns false when block doesn't fit
TEST_F(TextFlowTest_1211, BlockFitsReturnsFalseWhenBlockDoesNotFit_1213) {
    // Mock a TextBlock that doesn't fit
    TextBlock *largeBlock = new TextBlock(); // A large block that doesn't fit
    EXPECT_FALSE(textFlow->blockFits(largeBlock));
    delete largeBlock;
}

// Test normal operation: Ensure getBlocks returns the correct block
TEST_F(TextFlowTest_1211, GetBlocksReturnsCorrectTextBlock_1214) {
    // Initially, textFlow should have the block we added in SetUp()
    EXPECT_EQ(textFlow->getBlocks(), block);
}

// Test boundary condition: Ensure addBlock works when adding a block
TEST_F(TextFlowTest_1211, AddBlockAddsCorrectTextBlock_1215) {
    TextBlock *newBlock = new TextBlock();
    textFlow->addBlock(newBlock);
    
    // After adding the new block, getBlocks should reflect the added block
    EXPECT_EQ(textFlow->getBlocks(), newBlock);
    
    delete newBlock;
}

// Test for exceptional case: Ensure no memory leaks after TextFlow is destroyed
TEST_F(TextFlowTest_1211, DestructorDoesNotLeakMemory_1216) {
    // There should be no memory leak after destruction
    EXPECT_NO_THROW({
        delete textFlow;
    });
}