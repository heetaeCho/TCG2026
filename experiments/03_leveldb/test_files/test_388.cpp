#include <gtest/gtest.h>

#include "table/format.h"



using namespace leveldb;



class BlockHandleTest_388 : public ::testing::Test {

protected:

    BlockHandle block_handle_;

};



TEST_F(BlockHandleTest_388, DefaultConstructorInitializesOffsetAndSizeToMax_388) {

    EXPECT_EQ(block_handle_.offset(), ~static_cast<uint64_t>(0));

    EXPECT_EQ(block_handle_.size(), ~static_cast<uint64_t>(0));

}



TEST_F(BlockHandleTest_388, SetOffsetUpdatesOffsetValue_388) {

    block_handle_.set_offset(12345);

    EXPECT_EQ(block_handle_.offset(), 12345);

}



TEST_F(BlockHandleTest_388, SetSizeUpdatesSizeValue_388) {

    block_handle_.set_size(67890);

    EXPECT_EQ(block_handle_.size(), 67890);

}



TEST_F(BlockHandleTest_388, EncodeToAndDecodeFromRoundTrip_388) {

    std::string encoded;

    Slice input;



    block_handle_.set_offset(12345);

    block_handle_.set_size(67890);



    block_handle_.EncodeTo(&encoded);

    input = Slice(encoded);



    BlockHandle decoded_block_handle;

    Status status = decoded_block_handle.DecodeFrom(&input);



    EXPECT_TRUE(status.ok());

    EXPECT_EQ(decoded_block_handle.offset(), 12345);

    EXPECT_EQ(decoded_block_handle.size(), 67890);

}



TEST_F(BlockHandleTest_388, DecodeFromWithInvalidInputReturnsErrorStatus_388) {

    Slice input = Slice("invalid_data");

    Status status = block_handle_.DecodeFrom(&input);



    EXPECT_TRUE(!status.ok());

}
