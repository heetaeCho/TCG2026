#include <gtest/gtest.h>

#include "TextOutputDev.h"

#include <vector>



class TextPoolTest_1199 : public ::testing::Test {

protected:

    TextPool textPool;

    TextWord* word1 = new TextWord();

    TextWord* word2 = new TextWord();



    void SetUp() override {

        // Setup can be used to initialize common resources

        textPool.addWord(word1);

        textPool.sort();

    }



    void TearDown() override {

        // Clean up any resources after each test

        delete word1;

        delete word2;

    }

};



TEST_F(TextPoolTest_1199, GetPoolReturnsCorrectHead_1199) {

    int baseIdx = textPool.getBaseIdx(0.0);

    EXPECT_EQ(word1, textPool.getPool(baseIdx));

}



TEST_F(TextPoolTest_1199, AddWordIncreasesPoolSize_1199) {

    int initialBaseIdx = textPool.getBaseIdx(0.0);

    textPool.addWord(word2);

    textPool.sort();

    EXPECT_NE(word1, textPool.getPool(initialBaseIdx));

}



TEST_F(TextPoolTest_1199, GetPoolReturnsNullForInvalidIndex_1199) {

    int invalidBaseIdx = -1;

    EXPECT_EQ(nullptr, textPool.getPool(invalidBaseIdx));

}



TEST_F(TextPoolTest_1199, SortMaintainsOrder_1199) {

    int baseIdx1 = textPool.getBaseIdx(0.0);

    textPool.addWord(word2);

    textPool.sort();

    EXPECT_EQ(word1, textPool.getPool(baseIdx1));

}



TEST_F(TextPoolTest_1199, SetPoolUpdatesHeadCorrectly_1199) {

    int baseIdx = textPool.getBaseIdx(0.0);

    textPool.setPool(baseIdx, word2);

    EXPECT_EQ(word2, textPool.getPool(baseIdx));

}
