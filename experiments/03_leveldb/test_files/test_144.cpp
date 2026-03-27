#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/version_set.cc"

#include "leveldb/slice.h"

#include "leveldb/status.h"

#include "leveldb/options.h"

#include "db/table_cache.h"



using namespace leveldb;



class MockTableCache : public TableCache {

public:

    MockTableCache(const std::string & dbname, const Options & options, int entries)

        : TableCache(dbname, options, entries) {}



    MOCK_METHOD3(NewIterator, Iterator*(const ReadOptions& options, uint64_t file_number, uint64_t file_size));

};



TEST(GetFileIteratorTest_144, ValidInput_ReturnsIterator_144) {

    MockTableCache mock_table_cache("test_db", Options(), 10);

    ReadOptions read_options;

    Slice file_value("\x00\x00\x00\x00\x00\x00\x00\x08\x00\x00\x00\x00\x00\x00\x00\x10", 16);



    EXPECT_CALL(mock_table_cache, NewIterator(read_options, 8, 16))

        .WillOnce(testing::Return(new Iterator()));



    Iterator* result = GetFileIterator(&mock_table_cache, read_options, file_value);

    ASSERT_NE(result, nullptr);

    delete result;

}



TEST(GetFileIteratorTest_144, InvalidInput_ReturnsErrorIterator_144) {

    MockTableCache mock_table_cache("test_db", Options(), 10);

    ReadOptions read_options;

    Slice file_value("\x00\x00\x00\x00\x00\x00\x00\x08\x00\x00\x00\x00\x00\x00\x00", 15);



    Iterator* result = GetFileIterator(&mock_table_cache, read_options, file_value);

    ASSERT_NE(result, nullptr);



    EXPECT_TRUE(dynamic_cast<ErrorIterator*>(result) != nullptr);

    delete result;

}



TEST(GetFileIteratorTest_144, ZeroSize_ReturnsErrorIterator_144) {

    MockTableCache mock_table_cache("test_db", Options(), 10);

    ReadOptions read_options;

    Slice file_value("", 0);



    Iterator* result = GetFileIterator(&mock_table_cache, read_options, file_value);

    ASSERT_NE(result, nullptr);



    EXPECT_TRUE(dynamic_cast<ErrorIterator*>(result) != nullptr);

    delete result;

}



TEST(GetFileIteratorTest_144, MaxSize_ReturnsIterator_144) {

    MockTableCache mock_table_cache("test_db", Options(), 10);

    ReadOptions read_options;

    std::string max_value(16, '\xFF');

    Slice file_value(max_value.data(), 16);



    EXPECT_CALL(mock_table_cache, NewIterator(read_options, UINT64_MAX, UINT64_MAX))

        .WillOnce(testing::Return(new Iterator()));



    Iterator* result = GetFileIterator(&mock_table_cache, read_options, file_value);

    ASSERT_NE(result, nullptr);

    delete result;

}
