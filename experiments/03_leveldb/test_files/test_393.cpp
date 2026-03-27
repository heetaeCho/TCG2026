#include <gtest/gtest.h>

#include "table/format.h"

#include <string>



using namespace leveldb;



class FooterTest_393 : public ::testing::Test {

protected:

    Footer footer;

};



TEST_F(FooterTest_393, SetAndGetMetaindexHandle_NormalOperation_393) {

    BlockHandle block_handle;

    block_handle.set_offset(12345);

    block_handle.set_size(6789);



    footer.set_metaindex_handle(block_handle);

    const BlockHandle& retrieved_handle = footer.metaindex_handle();



    EXPECT_EQ(retrieved_handle.offset(), 12345);

    EXPECT_EQ(retrieved_handle.size(), 6789);

}



TEST_F(FooterTest_393, SetAndGetMetaindexHandle_BoundaryConditions_393) {

    BlockHandle block_handle;

    block_handle.set_offset(0);

    block_handle.set_size(0);



    footer.set_metaindex_handle(block_handle);

    const BlockHandle& retrieved_handle = footer.metaindex_handle();



    EXPECT_EQ(retrieved_handle.offset(), 0);

    EXPECT_EQ(retrieved_handle.size(), 0);

}



TEST_F(FooterTest_393, SetAndGetMetaindexHandle_MaxValues_393) {

    BlockHandle block_handle;

    block_handle.set_offset(~static_cast<uint64_t>(0));

    block_handle.set_size(~static_cast<uint64_t>(0));



    footer.set_metaindex_handle(block_handle);

    const BlockHandle& retrieved_handle = footer.metaindex_handle();



    EXPECT_EQ(retrieved_handle.offset(), ~static_cast<uint64_t>(0));

    EXPECT_EQ(retrieved_handle.size(), ~static_cast<uint64_t>(0));

}



TEST_F(FooterTest_393, SetAndGetIndexHandle_NormalOperation_393) {

    BlockHandle block_handle;

    block_handle.set_offset(12345);

    block_handle.set_size(6789);



    footer.set_index_handle(block_handle);

    const BlockHandle& retrieved_handle = footer.index_handle();



    EXPECT_EQ(retrieved_handle.offset(), 12345);

    EXPECT_EQ(retrieved_handle.size(), 6789);

}



TEST_F(FooterTest_393, SetAndGetIndexHandle_BoundaryConditions_393) {

    BlockHandle block_handle;

    block_handle.set_offset(0);

    block_handle.set_size(0);



    footer.set_index_handle(block_handle);

    const BlockHandle& retrieved_handle = footer.index_handle();



    EXPECT_EQ(retrieved_handle.offset(), 0);

    EXPECT_EQ(retrieved_handle.size(), 0);

}



TEST_F(FooterTest_393, SetAndGetIndexHandle_MaxValues_393) {

    BlockHandle block_handle;

    block_handle.set_offset(~static_cast<uint64_t>(0));

    block_handle.set_size(~static_cast<uint64_t>(0));



    footer.set_index_handle(block_handle);

    const BlockHandle& retrieved_handle = footer.index_handle();



    EXPECT_EQ(retrieved_handle.offset(), ~static_cast<uint64_t>(0));

    EXPECT_EQ(retrieved_handle.size(), ~static_cast<uint64_t>(0));

}



// Assuming EncodeTo and DecodeFrom are part of the interface, we need to mock Slice and std::string for testing.

class MockSlice : public Slice {

public:

    MOCK_CONST_METHOD0(data, const char*());

    MOCK_CONST_METHOD0(size, size_t());

};



TEST_F(FooterTest_393, EncodeTo_DecodeFrom_RoundTrip_393) {

    BlockHandle block_handle;

    block_handle.set_offset(12345);

    block_handle.set_size(6789);



    footer.set_metaindex_handle(block_handle);

    footer.set_index_handle(block_handle);



    std::string encoded_string;

    footer.EncodeTo(&encoded_string);



    Footer decoded_footer;

    Slice input(encoded_string.data(), encoded_string.size());

    Status status = decoded_footer.DecodeFrom(&input);



    EXPECT_TRUE(status.ok());



    const BlockHandle& retrieved_metaindex_handle = decoded_footer.metaindex_handle();

    const BlockHandle& retrieved_index_handle = decoded_footer.index_handle();



    EXPECT_EQ(retrieved_metaindex_handle.offset(), 12345);

    EXPECT_EQ(retrieved_metaindex_handle.size(), 6789);

    EXPECT_EQ(retrieved_index_handle.offset(), 12345);

    EXPECT_EQ(retrieved_index_handle.size(), 6789);

}
