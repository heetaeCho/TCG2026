#include <gtest/gtest.h>

#include "basicio.cpp"



using namespace Exiv2;



class BlockMapTest : public ::testing::Test {

protected:

    BlockMap blockMap;

};



TEST_F(BlockMapTest_569, PopulateSetsSizeAndType_569) {

    const byte data[] = {1, 2, 3, 4};

    size_t num = sizeof(data) / sizeof(data[0]);

    blockMap.populate(data, num);

    EXPECT_EQ(blockMap.getSize(), num);

    EXPECT_FALSE(blockMap.isNone());

    EXPECT_TRUE(blockMap.isKnown());

}



TEST_F(BlockMapTest_569, PopulateWithZeroSizeDoesNotChangeType_569) {

    const byte data[] = {1, 2, 3, 4};

    size_t num = 0;

    blockMap.populate(data, num);

    EXPECT_EQ(blockMap.getSize(), num);

    EXPECT_TRUE(blockMap.isNone());

    EXPECT_FALSE(blockMap.isKnown());

}



TEST_F(BlockMapTest_569, GetDataReturnsCorrectData_569) {

    const byte data[] = {1, 2, 3, 4};

    size_t num = sizeof(data) / sizeof(data[0]);

    blockMap.populate(data, num);

    auto resultData = blockMap.getData();

    EXPECT_EQ(std::memcmp(resultData.data(), data, num), 0);

}



TEST_F(BlockMapTest_569, IsNoneReturnsTrueInitially_569) {

    EXPECT_TRUE(blockMap.isNone());

    EXPECT_FALSE(blockMap.isKnown());

}



TEST_F(BlockMapTest_569, MarkKnownSetsTypeToKnown_569) {

    blockMap.markKnown(10);

    EXPECT_FALSE(blockMap.isNone());

    EXPECT_TRUE(blockMap.isKnown());

}
