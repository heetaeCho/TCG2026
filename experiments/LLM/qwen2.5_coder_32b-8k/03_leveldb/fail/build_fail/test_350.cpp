#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/table_cache.h"

#include "leveldb/status.h"

#include "leveldb/iterator.h"

#include "leveldb/options.h"

#include "leveldb/cache.h"

#include "leveldb/table.h"



using namespace leveldb;

using ::testing::_;

using ::testing::NiceMock;



class MockCache : public Cache {

public:

    MOCK_METHOD1(Lookup, Handle*(const Slice&));

    MOCK_METHOD1(Release, void(Handle*));

    MOCK_METHOD2(Insert, Handle*(const Slice&, void*, size_t, void (*)(const Slice &, void *)));

    MOCK_METHOD1(Erase, void(const Slice&));

    MOCK_METHOD1(Value, void*(Handle*));

};



class MockIterator : public Iterator {

public:

    MOCK_METHOD0(Valid, bool());

    MOCK_METHOD0(SeekToFirst, void());

    MOCK_METHOD0(SeekToLast, void());

    MOCK_METHOD1(Seek, void(const Slice & target));

    MOCK_METHOD0(Next, void());

    MOCK_METHOD0(Prev, void());

    MOCK_METHOD0(key, Slice());

    MOCK_METHOD0(value, Slice());

    MOCK_METHOD0(status, Status());

};



class MockTable : public Table {

public:

    MOCK_METHOD1(NewIterator, Iterator*(const ReadOptions&));

};



class MockRandomAccessFile : public RandomAccessFile {

public:

    MOCK_METHOD3(Read, Status(uint64_t, size_t, Slice*));

    MOCK_METHOD0(GetFileSize, uint64_t());

};



class TableCacheTest_350 : public ::testing::Test {

protected:

    NiceMock<MockCache> cache_;

    Options options_;

    std::string dbname_ = "test_db";

    TableCache table_cache_{dbname_, options_, 10};

};



TEST_F(TableCacheTest_350, NewIterator_ReturnsValidIterator_350) {

    ReadOptions read_options;

    uint64_t file_number = 123;

    uint64_t file_size = 456;

    Cache::Handle* handle = nullptr;



    MockTable* mock_table = new MockTable();

    TableAndFile* table_and_file = new TableAndFile{nullptr, mock_table};



    EXPECT_CALL(cache_, Lookup(_)).WillOnce(testing::Return(handle));

    EXPECT_CALL(*mock_table, NewIterator(_)).WillOnce(testing::Return(new NiceMock<MockIterator>()));



    Iterator* result = table_cache_.NewIterator(read_options, file_number, file_size, nullptr);



    ASSERT_NE(result, nullptr);

    delete result;

}



TEST_F(TableCacheTest_350, NewIterator_SetsTablePointer_350) {

    ReadOptions read_options;

    uint64_t file_number = 123;

    uint64_t file_size = 456;

    Cache::Handle* handle = nullptr;



    MockTable* mock_table = new MockTable();

    TableAndFile* table_and_file = new TableAndFile{nullptr, mock_table};



    EXPECT_CALL(cache_, Lookup(_)).WillOnce(testing::Return(handle));

    EXPECT_CALL(*mock_table, NewIterator(_)).WillOnce(testing::Return(new NiceMock<MockIterator>()));



    Table* returned_table = nullptr;

    Iterator* result = table_cache_.NewIterator(read_options, file_number, file_size, &returned_table);



    ASSERT_NE(returned_table, nullptr);

    delete result;

}



TEST_F(TableCacheTest_350, NewIterator_ReturnsErrorIteratorOnFailure_350) {

    ReadOptions read_options;

    uint64_t file_number = 123;

    uint64_t file_size = 456;

    Cache::Handle* handle = nullptr;



    EXPECT_CALL(cache_, Lookup(_)).WillOnce(testing::Return(nullptr));



    Iterator* result = table_cache_.NewIterator(read_options, file_number, file_size, nullptr);



    ASSERT_NE(result, nullptr);

    ASSERT_TRUE(!result->status().ok());

    delete result;

}



TEST_F(TableCacheTest_350, NewIterator_CleansUpHandleOnFailure_350) {

    ReadOptions read_options;

    uint64_t file_number = 123;

    uint64_t file_size = 456;

    Cache::Handle* handle = new Cache::Handle;



    EXPECT_CALL(cache_, Lookup(_)).WillOnce(testing::Return(handle));

    EXPECT_CALL(cache_, Release(handle));



    Iterator* result = table_cache_.NewIterator(read_options, file_number, file_size, nullptr);



    ASSERT_NE(result, nullptr);

    ASSERT_TRUE(!result->status().ok());

    delete result;

}



TEST_F(TableCacheTest_350, NewIterator_RegistersCleanupFunction_350) {

    ReadOptions read_options;

    uint64_t file_number = 123;

    uint64_t file_size = 456;

    Cache::Handle* handle = nullptr;



    MockTable* mock_table = new MockTable();

    TableAndFile* table_and_file = new TableAndFile{nullptr, mock_table};



    EXPECT_CALL(cache_, Lookup(_)).WillOnce(testing::Return(handle));

    EXPECT_CALL(*mock_table, NewIterator(_)).WillOnce(testing::Return(new NiceMock<MockIterator>()));



    Iterator* result = table_cache_.NewIterator(read_options, file_number, file_size, nullptr);



    ASSERT_NE(result, nullptr);

    delete result;

}



TEST_F(TableCacheTest_350, NewIterator_BoundaryConditions_FileNumberZero_350) {

    ReadOptions read_options;

    uint64_t file_number = 0;

    uint64_t file_size = 456;

    Cache::Handle* handle = nullptr;



    EXPECT_CALL(cache_, Lookup(_)).WillOnce(testing::Return(nullptr));



    Iterator* result = table_cache_.NewIterator(read_options, file_number, file_size, nullptr);



    ASSERT_NE(result, nullptr);

    ASSERT_TRUE(!result->status().ok());

    delete result;

}



TEST_F(TableCacheTest_350, NewIterator_BoundaryConditions_FileSizeZero_350) {

    ReadOptions read_options;

    uint64_t file_number = 123;

    uint64_t file_size = 0;

    Cache::Handle* handle = nullptr;



    EXPECT_CALL(cache_, Lookup(_)).WillOnce(testing::Return(nullptr));



    Iterator* result = table_cache_.NewIterator(read_options, file_number, file_size, nullptr);



    ASSERT_NE(result, nullptr);

    ASSERT_TRUE(!result->status().ok());

    delete result;

}
