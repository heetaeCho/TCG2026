#include <gtest/gtest.h>

#include "table/format.h"

#include <string>



namespace leveldb {



class BlockHandleTest_396 : public ::testing::Test {

protected:

    BlockHandle block_handle_;

};



TEST_F(BlockHandleTest_396, EncodeTo_ValidOffsetAndSize_396) {

    std::string dst;

    block_handle_.set_offset(1234);

    block_handle_.set_size(5678);

    block_handle_.EncodeTo(&dst);

    EXPECT_EQ(dst.size(), 10); // Varint encoding of two 32-bit numbers

}



TEST_F(BlockHandleTest_396, EncodeTo_MaxOffsetAndSize_396) {

    std::string dst;

    block_handle_.set_offset(~static_cast<uint64_t>(0));

    block_handle_.set_size(~static_cast<uint64_t>(0));

    EXPECT_THROW(block_handle_.EncodeTo(&dst), std::exception);

}



TEST_F(BlockHandleTest_396, EncodeTo_ZeroOffsetAndSize_396) {

    std::string dst;

    block_handle_.set_offset(0);

    block_handle_.set_size(0);

    block_handle_.EncodeTo(&dst);

    EXPECT_EQ(dst.size(), 2); // Varint encoding of two zeros

}



TEST_F(BlockHandleTest_396, EncodeTo_LargeOffsetAndSize_396) {

    std::string dst;

    block_handle_.set_offset(123456789012345);

    block_handle_.set_size(987654321098765);

    block_handle_.EncodeTo(&dst);

    EXPECT_EQ(dst.size(), 22); // Varint encoding of two large numbers

}



TEST_F(BlockHandleTest_396, EncodeTo_DefaultValuesThrow_396) {

    std::string dst;

    EXPECT_THROW(block_handle_.EncodeTo(&dst), std::exception);

}



}  // namespace leveldb
