#include <gtest/gtest.h>

#include "table/format.h"

#include "leveldb/slice.h"



using namespace leveldb;



class BlockHandleTest_397 : public ::testing::Test {

protected:

    BlockHandle block_handle_;

};



TEST_F(BlockHandleTest_397, DecodeFromValidInput_397) {

    const char* data = "\x01\x02"; // Varint encoding for 1 and 2

    Slice input(data, 2);

    Status status = block_handle_.DecodeFrom(&input);

    EXPECT_TRUE(status.ok());

    EXPECT_EQ(block_handle_.offset(), 1U);

    EXPECT_EQ(block_handle_.size(), 2U);

}



TEST_F(BlockHandleTest_397, DecodeFromShortInput_397) {

    const char* data = "\x01"; // Varint encoding for 1 only

    Slice input(data, 1);

    Status status = block_handle_.DecodeFrom(&input);

    EXPECT_EQ(status.code(), kCorruption);

    EXPECT_EQ(status.ToString(), "Corruption: bad block handle");

}



TEST_F(BlockHandleTest_397, DecodeFromEmptyInput_397) {

    Slice input("", 0);

    Status status = block_handle_.DecodeFrom(&input);

    EXPECT_EQ(status.code(), kCorruption);

    EXPECT_EQ(status.ToString(), "Corruption: bad block handle");

}



TEST_F(BlockHandleTest_397, DecodeFromLargeOffset_397) {

    const char* data = "\x80\x80\x80\x80\x80\x80\x80\x80\x01\x02"; // Varint encoding for large offset and size 2

    Slice input(data, 10);

    Status status = block_handle_.DecodeFrom(&input);

    EXPECT_TRUE(status.ok());

    EXPECT_EQ(block_handle_.size(), 2U);

}



TEST_F(BlockHandleTest_397, DecodeFromLargeSize_397) {

    const char* data = "\x01\x80\x80\x80\x80\x80\x80\x80\x80\x01"; // Varint encoding for offset 1 and large size

    Slice input(data, 10);

    Status status = block_handle_.DecodeFrom(&input);

    EXPECT_TRUE(status.ok());

    EXPECT_EQ(block_handle_.offset(), 1U);

}
