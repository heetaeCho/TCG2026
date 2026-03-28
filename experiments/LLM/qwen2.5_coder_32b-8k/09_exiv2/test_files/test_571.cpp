#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/basicio.cpp"



using namespace Exiv2;



class BlockMapTest_571 : public ::testing::Test {

protected:

    BlockMap blockMap;

};



TEST_F(BlockMapTest_571, IsNone_ReturnsTrueInitially_571) {

    EXPECT_TRUE(blockMap.isNone());

}



TEST_F(BlockMapTest_571, Populate_SetsBlockToKnown_571) {

    const byte source[] = {0x01, 0x02};

    size_t num = sizeof(source);

    blockMap.populate(source, num);

    EXPECT_FALSE(blockMap.isNone());

}



TEST_F(BlockMapTest_571, MarkKnown_SetsBlockToKnown_571) {

    blockMap.markKnown(1);

    EXPECT_FALSE(blockMap.isNone());

}



TEST_F(BlockMapTest_571, GetData_ReturnsEmptyInitially_571) {

    auto data = blockMap.getData();

    EXPECT_EQ(data.size(), 0U);

}



TEST_F(BlockMapTest_571, GetData_ReturnsPopulatedData_571) {

    const byte source[] = {0x01, 0x02};

    size_t num = sizeof(source);

    blockMap.populate(source, num);

    auto data = blockMap.getData();

    EXPECT_EQ(data.size(), num);

    EXPECT_TRUE(std::equal(data.begin(), data.end(), std::begin(source)));

}



TEST_F(BlockMapTest_571, GetSize_ReturnsZeroInitially_571) {

    EXPECT_EQ(blockMap.getSize(), 0U);

}



TEST_F(BlockMapTest_571, GetSize_ReturnsPopulatedSize_571) {

    const byte source[] = {0x01, 0x02};

    size_t num = sizeof(source);

    blockMap.populate(source, num);

    EXPECT_EQ(blockMap.getSize(), num);

}



TEST_F(BlockMapTest_571, IsKnown_ReturnsFalseInitially_571) {

    EXPECT_FALSE(blockMap.isKnown());

}



TEST_F(BlockMapTest_571, MarkKnown_SetsBlockToKnownAndIsKnownReturnsTrue_571) {

    blockMap.markKnown(1);

    EXPECT_TRUE(blockMap.isKnown());

}
