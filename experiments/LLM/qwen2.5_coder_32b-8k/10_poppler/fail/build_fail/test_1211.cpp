#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TextOutputDev.h"



class TextFlowTest_1211 : public ::testing::Test {

protected:

    TextBlock* block1;

    TextBlock* block2;

    TextPage* page;



    void SetUp() override {

        block1 = new TextBlock();

        block2 = new TextBlock();

        page = new TextPage();

    }



    void TearDown() override {

        delete block1;

        delete block2;

        delete page;

    }

};



TEST_F(TextFlowTest_1211, ConstructionAndGetters_1211) {

    TextFlow textFlow(page, block1);

    EXPECT_EQ(textFlow.getBlocks(), block1);

    EXPECT_EQ(textFlow.getNext(), nullptr);

}



TEST_F(TextFlowTest_1211, AddBlockAndGetBlocks_1211) {

    TextFlow textFlow(page, block1);

    textFlow.addBlock(block2);

    EXPECT_EQ(textFlow.getBlocks(), block1); // getBlocks should return the first block

}



TEST_F(TextFlowTest_1211, BlockFits_NormalCase_1211) {

    TextFlow textFlow(page, block1);

    EXPECT_TRUE(textFlow.blockFits(block2)); // Assuming blockFits returns true for normal cases

}



TEST_F(TextFlowTest_1211, BlockFits_SameBlock_1211) {

    TextFlow textFlow(page, block1);

    EXPECT_FALSE(textFlow.blockFits(block1)); // Block should not fit if it's the same as the current one

}



TEST_F(TextFlowTest_1211, GetNext_AfterAddingFlow_1211) {

    TextFlow textFlow1(page, block1);

    TextFlow textFlow2(page, block2);



    textFlow1.addBlock(block2); // This should not change the next pointer

    EXPECT_EQ(textFlow1.getNext(), nullptr);



    textFlow1 = TextFlow(page, block1);

    textFlow1.next = &textFlow2;

    EXPECT_EQ(textFlow1.getNext(), &textFlow2);

}



TEST_F(TextFlowTest_1211, BlockFits_BoundaryCase_EmptyBlock_1211) {

    TextFlow textFlow(page, nullptr);

    EXPECT_FALSE(textFlow.blockFits(block1)); // Assuming blockFits returns false if the current block is null

}



TEST_F(TextFlowTest_1211, AddBlock_NullBlock_1211) {

    TextFlow textFlow(page, block1);

    textFlow.addBlock(nullptr); // Adding a null block should not change the internal state

    EXPECT_EQ(textFlow.getBlocks(), block1);

}
