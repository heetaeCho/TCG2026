#include <gtest/gtest.h>

#include "table/format.h"



using namespace leveldb;



class BlockHandleTest_390 : public ::testing::Test {

protected:

    BlockHandle block_handle;

};



TEST_F(BlockHandleTest_390, DefaultConstructorInitializesOffsetAndSizeToMaxValue_390) {

    EXPECT_EQ(block_handle.offset(), ~static_cast<uint64_t>(0));

    EXPECT_EQ(block_handle.size(), ~static_cast<uint64_t>(0));

}



TEST_F(BlockHandleTest_390, SetOffsetUpdatesOffsetValue_390) {

    uint64_t test_offset = 12345;

    block_handle.set_offset(test_offset);

    EXPECT_EQ(block_handle.offset(), test_offset);

}



TEST_F(BlockHandleTest_390, SetSizeUpdatesSizeValue_390) {

    uint64_t test_size = 54321;

    block_handle.set_size(test_size);

    EXPECT_EQ(block_handle.size(), test_size);

}



TEST_F(BlockHandleTest_390, EncodeToSetsCorrectValuesInString_390) {

    std::string encoded_string;

    block_handle.set_offset(100);

    block_handle.set_size(200);

    block_handle.EncodeTo(&encoded_string);

    EXPECT_EQ(encoded_string.size(), sizeof(uint64_t) * 2); // offset and size are both uint64_t

}



TEST_F(BlockHandleTest_390, DecodeFromCorrectlySetsOffsetAndSizeFromEncodedString_390) {

    std::string encoded_string;

    block_handle.set_offset(100);

    block_handle.set_size(200);

    block_handle.EncodeTo(&encoded_string);



    BlockHandle decoded_block_handle;

    Slice input(encoded_string);

    Status status = decoded_block_handle.DecodeFrom(&input);

    

    EXPECT_TRUE(status.ok());

    EXPECT_EQ(decoded_block_handle.offset(), 100);

    EXPECT_EQ(decoded_block_handle.size(), 200);

}



TEST_F(BlockHandleTest_390, DecodeFromHandlesInvalidInputGracefully_390) {

    std::string invalid_input = "invalid";

    Slice input(invalid_input);



    Status status = block_handle.DecodeFrom(&input);

    

    EXPECT_FALSE(status.ok());

}
