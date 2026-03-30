#include <gtest/gtest.h>

#include "table/format.h"

#include <string>



using namespace leveldb;



// Fixture for Footer class tests.

class FooterTest_395 : public ::testing::Test {

protected:

    Footer footer;

};



// Test normal operation of setting and getting index handle.

TEST_F(FooterTest_395, SetAndGetIndexHandle_NormalOperation_395) {

    BlockHandle bh;

    bh.set_offset(10);

    bh.set_size(20);



    footer.set_index_handle(bh);

    const BlockHandle& retrieved_bh = footer.index_handle();



    EXPECT_EQ(retrieved_bh.offset(), 10);

    EXPECT_EQ(retrieved_bh.size(), 20);

}



// Test boundary conditions for setting and getting index handle with zero values.

TEST_F(FooterTest_395, SetAndGetIndexHandle_ZeroValues_BoundaryConditions_395) {

    BlockHandle bh;

    bh.set_offset(0);

    bh.set_size(0);



    footer.set_index_handle(bh);

    const BlockHandle& retrieved_bh = footer.index_handle();



    EXPECT_EQ(retrieved_bh.offset(), 0);

    EXPECT_EQ(retrieved_bh.size(), 0);

}



// Test boundary conditions for setting and getting index handle with max values.

TEST_F(FooterTest_395, SetAndGetIndexHandle_MaxValues_BoundaryConditions_395) {

    BlockHandle bh;

    bh.set_offset(~static_cast<uint64_t>(0));

    bh.set_size(~static_cast<uint64_t>(0));



    footer.set_index_handle(bh);

    const BlockHandle& retrieved_bh = footer.index_handle();



    EXPECT_EQ(retrieved_bh.offset(), ~static_cast<uint64_t>(0));

    EXPECT_EQ(retrieved_bh.size(), ~static_cast<uint64_t>(0));

}



// Test setting and getting metaindex handle.

TEST_F(FooterTest_395, SetAndGetMetaindexHandle_NormalOperation_395) {

    BlockHandle bh;

    bh.set_offset(100);

    bh.set_size(200);



    footer.set_metaindex_handle(bh);

    const BlockHandle& retrieved_bh = footer.metaindex_handle();



    EXPECT_EQ(retrieved_bh.offset(), 100);

    EXPECT_EQ(retrieved_bh.size(), 200);

}



// Test boundary conditions for setting and getting metaindex handle with zero values.

TEST_F(FooterTest_395, SetAndGetMetaindexHandle_ZeroValues_BoundaryConditions_395) {

    BlockHandle bh;

    bh.set_offset(0);

    bh.set_size(0);



    footer.set_metaindex_handle(bh);

    const BlockHandle& retrieved_bh = footer.metaindex_handle();



    EXPECT_EQ(retrieved_bh.offset(), 0);

    EXPECT_EQ(retrieved_bh.size(), 0);

}



// Test boundary conditions for setting and getting metaindex handle with max values.

TEST_F(FooterTest_395, SetAndGetMetaindexHandle_MaxValues_BoundaryConditions_395) {

    BlockHandle bh;

    bh.set_offset(~static_cast<uint64_t>(0));

    bh.set_size(~static_cast<uint64_t>(0));



    footer.set_metaindex_handle(bh);

    const BlockHandle& retrieved_bh = footer.metaindex_handle();



    EXPECT_EQ(retrieved_bh.offset(), ~static_cast<uint64_t>(0));

    EXPECT_EQ(retrieved_bh.size(), ~static_cast<uint64_t>(0));

}
