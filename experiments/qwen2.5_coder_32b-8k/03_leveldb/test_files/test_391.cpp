#include <gtest/gtest.h>

#include "table/format.h"

#include <string>



using namespace leveldb;



class BlockHandleTest_391 : public ::testing::Test {

protected:

    BlockHandle block_handle_;

};



TEST_F(BlockHandleTest_391, DefaultConstructorInitializesOffsetsAndSizesToMax_391) {

    EXPECT_EQ(block_handle_.offset(), ~static_cast<uint64_t>(0));

    EXPECT_EQ(block_handle_.size(), ~static_cast<uint64_t>(0));

}



TEST_F(BlockHandleTest_391, SetOffsetUpdatesOffsetCorrectly_391) {

    uint64_t new_offset = 12345;

    block_handle_.set_offset(new_offset);

    EXPECT_EQ(block_handle_.offset(), new_offset);

}



TEST_F(BlockHandleTest_391, SetSizeUpdatesSizeCorrectly_391) {

    uint64_t new_size = 54321;

    block_handle_.set_size(new_size);

    EXPECT_EQ(block_handle_.size(), new_size);

}



// Assuming EncodeTo and DecodeFrom interact with a string or Slice in a meaningful way, we would need more context.

// For now, we assume they do not throw exceptions under normal circumstances.



TEST_F(BlockHandleTest_391, EncodeToDoesNotThrowException_391) {

    std::string encoded;

    EXPECT_NO_THROW(block_handle_.EncodeTo(&encoded));

}



TEST_F(BlockHandleTest_391, DecodeFromDoesNotThrowExceptionWithValidInput_391) {

    std::string encoded;

    block_handle_.EncodeTo(&encoded);

    Slice slice(encoded);

    EXPECT_NO_THROW(block_handle_.DecodeFrom(&slice));

}



// Boundary conditions for offset and size

TEST_F(BlockHandleTest_391, SetOffsetToZeroWorksCorrectly_391) {

    block_handle_.set_offset(0);

    EXPECT_EQ(block_handle_.offset(), 0);

}



TEST_F(BlockHandleTest_391, SetSizeToZeroWorksCorrectly_391) {

    block_handle_.set_size(0);

    EXPECT_EQ(block_handle_.size(), 0);

}



TEST_F(BlockHandleTest_391, SetOffsetToMaxUint64WorksCorrectly_391) {

    block_handle_.set_offset(~static_cast<uint64_t>(0));

    EXPECT_EQ(block_handle_.offset(), ~static_cast<uint64_t>(0));

}



TEST_F(BlockHandleTest_391, SetSizeToMaxUint64WorksCorrectly_391) {

    block_handle_.set_size(~static_cast<uint64_t>(0));

    EXPECT_EQ(block_handle_.size(), ~static_cast<uint64_t>(0));

}
