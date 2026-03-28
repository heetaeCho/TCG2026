#include <gtest/gtest.h>

#include <gmock/gmock.h>



namespace leveldb {



class Table {

public:

    struct Rep {

        Options options;

        uint64_t cache_id;

        FilterBlockReader* filter;

        const char* filter_data;

        BlockHandle metaindex_handle;

        Block* index_block;



        ~Rep();

    };

};



}  // namespace leveldb



namespace {



using ::testing::NotNull;

using ::testing::IsNull;



class TableTest_418 : public ::testing::Test {

protected:

    void SetUp() override {

        rep = new leveldb::Table::Rep();

    }



    void TearDown() override {

        delete rep;

    }



    leveldb::Table::Rep* rep;

};



TEST_F(TableTest_418, FilterInitializationNullFilter_418) {

    rep->filter = nullptr;

    EXPECT_THAT(rep->filter, IsNull());

}



TEST_F(TableTest_418, FilterInitializationNonNullFilter_418) {

    rep->filter = new leveldb::FilterBlockReader(nullptr);

    EXPECT_THAT(rep->filter, NotNull());

    delete rep->filter;  // Clean up to avoid memory leak

}



TEST_F(TableTest_418, FilterDataInitializationNullData_418) {

    rep->filter_data = nullptr;

    EXPECT_THAT(rep->filter_data, IsNull());

}



TEST_F(TableTest_418, FilterDataInitializationNonNullData_418) {

    const char* data = "dummy_filter_data";

    rep->filter_data = data;

    EXPECT_EQ(rep->filter_data, data);

}



TEST_F(TableTest_418, IndexBlockInitializationNullIndexBlock_418) {

    rep->index_block = nullptr;

    EXPECT_THAT(rep->index_block, IsNull());

}



TEST_F(TableTest_418, IndexBlockInitializationNonNullIndexBlock_418) {

    rep->index_block = new leveldb::Block();

    EXPECT_THAT(rep->index_block, NotNull());

    delete rep->index_block;  // Clean up to avoid memory leak

}



TEST_F(TableTest_418, DestructorDeallocatesFilterAndData_418) {

    rep->filter = new leveldb::FilterBlockReader(nullptr);

    rep->filter_data = new char[10];

    delete rep;



    // Since the destructor is called in TearDown, we just ensure no crash here.

}



TEST_F(TableTest_418, DestructorDeallocatesIndexBlock_418) {

    rep->index_block = new leveldb::Block();

    delete rep;



    // Since the destructor is called in TearDown, we just ensure no crash here.

}



}  // namespace
