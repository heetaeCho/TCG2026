#include <gtest/gtest.h>

#include "table/format.h"



namespace leveldb {



class FooterTest_394 : public ::testing::Test {

protected:

    Footer footer_;

};



TEST_F(FooterTest_394, DefaultConstructorInitializesHandles_394) {

    BlockHandle empty_handle;

    EXPECT_EQ(footer_.index_handle(), empty_handle);

}



TEST_F(FooterTest_394, SetAndGetIndexHandle_394) {

    BlockHandle handle;

    handle.set_offset(123);

    handle.set_size(456);



    footer_.set_index_handle(handle);

    EXPECT_EQ(footer_.index_handle().offset(), 123);

    EXPECT_EQ(footer_.index_handle().size(), 456);

}



TEST_F(FooterTest_394, SetAndGetMetaindexHandle_394) {

    BlockHandle handle;

    handle.set_offset(789);

    handle.set_size(101);



    footer_.set_metaindex_handle(handle);

    EXPECT_EQ(footer_.metaindex_handle().offset(), 789);

    EXPECT_EQ(footer_.metaindex_handle().size(), 101);

}



TEST_F(FooterTest_394, EncodeToAndDecodeFromRoundTrip_394) {

    BlockHandle index_handle;

    index_handle.set_offset(12345);

    index_handle.set_size(67890);



    BlockHandle metaindex_handle;

    metaindex_handle.set_offset(54321);

    metaindex_handle.set_size(9876);



    footer_.set_index_handle(index_handle);

    footer_.set_metaindex_handle(metaindex_handle);



    std::string encoded_string;

    footer_.EncodeTo(&encoded_string);



    Footer decoded_footer;

    Status status = decoded_footer.DecodeFrom(Slice(encoded_string));



    EXPECT_TRUE(status.ok());

    EXPECT_EQ(decoded_footer.index_handle().offset(), 12345);

    EXPECT_EQ(decoded_footer.index_handle().size(), 67890);

    EXPECT_EQ(decoded_footer.metaindex_handle().offset(), 54321);

    EXPECT_EQ(decoded_footer.metaindex_handle().size(), 9876);

}



TEST_F(FooterTest_394, DecodeFromInvalidInputFails_394) {

    Slice invalid_input("invalid_data");

    Status status = footer_.DecodeFrom(invalid_input);



    EXPECT_FALSE(status.ok());

}



} // namespace leveldb
