#include <gtest/gtest.h>

#include "TextOutputDev.h"



class TextPoolTest : public ::testing::Test {

protected:

    void SetUp() override {

        textPool = new TextPool();

        textWord1 = new TextWord(nullptr, 0, 12.0);

        textWord2 = new TextWord(nullptr, 45, 14.0);

    }



    void TearDown() override {

        delete textPool;

        delete textWord1;

        delete textWord2;

    }



    TextPool* textPool;

    TextWord* textWord1;

    TextWord* textWord2;

};



TEST_F(TextPoolTest_1200, SetPoolWithValidBaseIdxAndTextWord_1200) {

    int baseIdx = 10;

    textPool->setPool(baseIdx, textWord1);

    EXPECT_EQ(textPool->getPool(baseIdx)->head, textWord1);

}



TEST_F(TextPoolTest_1200, SetPoolWithMultipleBaseIdxAndTextWords_1200) {

    int baseIdx1 = 10;

    int baseIdx2 = 20;

    textPool->setPool(baseIdx1, textWord1);

    textPool->setPool(baseIdx2, textWord2);



    EXPECT_EQ(textPool->getPool(baseIdx1)->head, textWord1);

    EXPECT_EQ(textPool->getPool(baseIdx2)->head, textWord2);

}



TEST_F(TextPoolTest_1200, GetPoolWithNonExistentBaseIdxReturnsNull_1200) {

    int nonExistentBaseIdx = 999;

    EXPECT_EQ(textPool->getPool(nonExistentBaseIdx), nullptr);

}



TEST_F(TextPoolTest_1200, SetPoolOverwritesExistingTextWord_1200) {

    int baseIdx = 10;

    textPool->setPool(baseIdx, textWord1);

    textPool->setPool(baseIdx, textWord2);



    EXPECT_EQ(textPool->getPool(baseIdx)->head, textWord2);

}



TEST_F(TextPoolTest_1200, SetPoolWithNegativeBaseIdxHandlesCorrectly_1200) {

    int negativeBaseIdx = -5;

    textPool->setPool(negativeBaseIdx, textWord1);



    EXPECT_EQ(textPool->getPool(negativeBaseIdx)->head, textWord1);

}
