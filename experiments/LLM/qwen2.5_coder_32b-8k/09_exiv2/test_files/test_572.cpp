#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming the necessary headers are included for Exiv2::BlockMap and related types



namespace {



class BlockMapTest_572 : public ::testing::Test {

protected:

    Exiv2::BlockMap blockMap;

};



TEST_F(BlockMapTest_572, DefaultStateIsNone_572) {

    EXPECT_TRUE(blockMap.isNone());

    EXPECT_FALSE(blockMap.isKnown());

}



TEST_F(BlockMapTest_572, MarkKnownSetsTypeToKnown_572) {

    blockMap.markKnown(10);

    EXPECT_FALSE(blockMap.isNone());

    EXPECT_TRUE(blockMap.isKnown());

}



TEST_F(BlockMapTest_572, PopulateDoesNotChangeKnownStateInitially_572) {

    byte data[10] = {0};

    blockMap.populate(data, 10);

    EXPECT_TRUE(blockMap.isNone());

    EXPECT_FALSE(blockMap.isKnown());

}



TEST_F(BlockMapTest_572, MarkKnownThenPopulateKeepsKnownState_572) {

    blockMap.markKnown(10);

    byte data[10] = {0};

    blockMap.populate(data, 10);

    EXPECT_FALSE(blockMap.isNone());

    EXPECT_TRUE(blockMap.isKnown());

}



TEST_F(BlockMapTest_572, GetSizeReturnsCorrectValueAfterPopulate_572) {

    byte data[10] = {0};

    blockMap.populate(data, 10);

    EXPECT_EQ(blockMap.getSize(), 10);

}



TEST_F(BlockMapTest_572, GetDataReturnsNonNullPointerAfterPopulate_572) {

    byte data[10] = {0};

    blockMap.populate(data, 10);

    EXPECT_NE(blockMap.getData(), nullptr);

}



}  // namespace
