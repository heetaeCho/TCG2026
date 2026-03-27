#include <gtest/gtest.h>

#include "basicio.cpp" // Assuming the header file includes this implementation



using namespace Exiv2;



class BlockMapTest_570 : public ::testing::Test {

protected:

    BlockMap blockMap;

};



TEST_F(BlockMapTest_570, MarkKnownSetsTypeAndSize_570) {

    size_t num = 10;

    blockMap.markKnown(num);

    EXPECT_TRUE(blockMap.isKnown());

    EXPECT_EQ(blockMap.getSize(), num);

}



TEST_F(BlockMapTest_570, InitialStateIsNone_570) {

    EXPECT_TRUE(blockMap.isNone());

    EXPECT_FALSE(blockMap.isKnown());

    EXPECT_EQ(blockMap.getSize(), 0);

}



TEST_F(BlockMapTest_570, MarkKnownTwiceUpdatesSize_570) {

    size_t num1 = 5;

    size_t num2 = 15;

    blockMap.markKnown(num1);

    blockMap.markKnown(num2);

    EXPECT_TRUE(blockMap.isKnown());

    EXPECT_EQ(blockMap.getSize(), num2);

}



TEST_F(BlockMapTest_570, GetDataReturnsEmptyInitially_570) {

    auto data = blockMap.getData();

    EXPECT_EQ(data.size(), 0);

}
