#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/basicio.cpp"



using namespace Exiv2;



class BlockMapTest_574 : public ::testing::Test {

protected:

    BlockMap blockMap;

};



TEST_F(BlockMapTest_574, InitialSizeIsZero_574) {

    EXPECT_EQ(blockMap.getSize(), 0);

}



TEST_F(BlockMapTest_574, PopulateSetsCorrectSize_574) {

    const byte source[] = {1, 2, 3};

    blockMap.populate(source, sizeof(source));

    EXPECT_EQ(blockMap.getSize(), sizeof(source));

}



TEST_F(BlockMapTest_574, MarkKnownDoesNotChangeSize_574) {

    const byte source[] = {1, 2, 3};

    blockMap.populate(source, sizeof(source));

    blockMap.markKnown(2);

    EXPECT_EQ(blockMap.getSize(), sizeof(source));

}



TEST_F(BlockMapTest_574, IsNoneInitiallyTrue_574) {

    EXPECT_TRUE(blockMap.isNone());

}



TEST_F(BlockMapTest_574, IsKnownInitiallyFalse_574) {

    EXPECT_FALSE(blockMap.isKnown());

}



TEST_F(BlockMapTest_574, IsNoneFalseAfterPopulate_574) {

    const byte source[] = {1, 2, 3};

    blockMap.populate(source, sizeof(source));

    EXPECT_FALSE(blockMap.isNone());

}



TEST_F(BlockMapTest_574, IsKnownTrueAfterMarkKnown_574) {

    const byte source[] = {1, 2, 3};

    blockMap.populate(source, sizeof(source));

    blockMap.markKnown(sizeof(source));

    EXPECT_TRUE(blockMap.isKnown());

}



TEST_F(BlockMapTest_574, GetDataReturnsValidPointer_574) {

    const byte source[] = {1, 2, 3};

    blockMap.populate(source, sizeof(source));

    auto data = blockMap.getData();

    EXPECT_NE(data.get(), nullptr);

}



TEST_F(BlockMapTest_574, PopulateWithZeroSizeDoesNotChangeState_574) {

    const byte source[] = {1, 2, 3};

    blockMap.populate(source, 0);

    EXPECT_EQ(blockMap.getSize(), 0);

    EXPECT_TRUE(blockMap.isNone());

    EXPECT_FALSE(blockMap.isKnown());

}



TEST_F(BlockMapTest_574, MarkKnownWithZeroDoesNotChangeState_574) {

    const byte source[] = {1, 2, 3};

    blockMap.populate(source, sizeof(source));

    blockMap.markKnown(0);

    EXPECT_FALSE(blockMap.isKnown());

}
