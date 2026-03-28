#include <gtest/gtest.h>

#include "TextOutputDev.h"



class TextFlowTest_1210 : public ::testing::Test {

protected:

    TextBlock* block1;

    TextBlock* block2;

    TextPage* page;



    void SetUp() override {

        page = new TextPage();

        block1 = new TextBlock();

        block2 = new TextBlock();

    }



    void TearDown() override {

        delete page;

        delete block1;

        delete block2;

    }

};



TEST_F(TextFlowTest_1210, ConstructorInitializesBlocksPointer_1210) {

    TextFlow textFlow(page, block1);

    EXPECT_EQ(textFlow.getBlocks(), block1);

}



TEST_F(TextFlowTest_1210, AddBlockUpdatesBlocksChain_1210) {

    TextFlow textFlow(page, block1);

    textFlow.addBlock(block2);

    EXPECT_NE(textFlow.getBlocks()->getNext(), nullptr);

    EXPECT_EQ(textFlow.getBlocks()->getNext()->getBlock(), block2);

}



TEST_F(TextFlowTest_1210, BlockFitsReturnsTrueForCompatibleBlock_1210) {

    TextFlow textFlow(page, block1);

    EXPECT_TRUE(textFlow.blockFits(block2));

}



TEST_F(TextFlowTest_1210, GetNextReturnsNullptrInitially_1210) {

    TextFlow textFlow(page, block1);

    EXPECT_EQ(textFlow.getNext(), nullptr);

}



TEST_F(TextFlowTest_1210, AddBlockDoesNotChangeLastBlockIfItFits_1210) {

    TextFlow textFlow(page, block1);

    textFlow.addBlock(block2);

    EXPECT_NE(textFlow.getBlocks()->getNext(), nullptr);

}



// Assuming there are some boundary conditions or error cases based on known behavior

TEST_F(TextFlowTest_1210, AddNullBlockDoesNotChangeState_1210) {

    TextFlow textFlow(page, block1);

    textFlow.addBlock(nullptr);

    EXPECT_EQ(textFlow.getBlocks(), block1);

    EXPECT_EQ(textFlow.getNext(), nullptr);

}
