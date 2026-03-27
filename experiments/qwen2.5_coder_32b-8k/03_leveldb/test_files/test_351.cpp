#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/table_cache.h"

#include "leveldb/status.h"

#include "leveldb/slice.h"

#include "leveldb/options.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;

using ::testing::InvokeWithoutArgs;



class MockCache : public Cache {

public:

    MOCK_METHOD(Handle*, Insert, (const Slice & key, void * value, size_t charge, void (*)(const Slice &, void *) deleter), (override));

    MOCK_METHOD(Handle*, Lookup, (const Slice & key), (override));

    MOCK_METHOD(void, Release, (Handle * handle), (override));

    MOCK_METHOD(void*, Value, (Handle * handle), (override));

    MOCK_METHOD(void, Erase, (const Slice & key), (override));

    MOCK_METHOD(uint64_t, NewId, (), (override));

    MOCK_METHOD(size_t, TotalCharge, (), (override));

    MOCK_METHOD(void, Prune, (), (override));

};



class MockTable : public Table {

public:

    MOCK_METHOD(Status, InternalGet, (const ReadOptions & options, const Slice & key, void * arg, void (*handle_result)(void *, const Slice &, const Slice &)), (override));

};



class MockRandomAccessFile : public RandomAccessFile {

public:

    MOCK_METHOD(Status, Read, (uint64_t offset, size_t n, Slice* result, char* scratch), (override));

    MOCK_METHOD(uint64_t, GetFileSize, (), (override));

    MOCK_METHOD(void, Close, (), (override));

};



class TableCacheTest_351 : public ::testing::Test {

protected:

    void SetUp() override {

        options = Options();

        cache = new MockCache();

        table_cache = new TableCache("dbname", options, 10);

        table_cache->cache_ = cache;

        mock_table = new MockTable();

    }



    void TearDown() override {

        delete table_cache;

        delete mock_table;

        delete cache;

    }



    Options options;

    MockCache* cache;

    TableCache* table_cache;

    MockTable* mock_table;

};



TEST_F(TableCacheTest_351, GetSuccess_351) {

    ReadOptions read_options;

    uint64_t file_number = 1;

    uint64_t file_size = 1024;

    Slice key("test_key");

    void* arg = nullptr;

    auto handle_result = [](void*, const Slice&, const Slice&) {};



    Cache::Handle* mock_handle = new Cache::Handle();

    TableAndFile* table_and_file = new TableAndFile{nullptr, mock_table};



    EXPECT_CALL(*cache, Lookup(_))

        .WillOnce(Return(mock_handle));

    EXPECT_CALL(*mock_table, InternalGet(_, key, arg, handle_result))

        .WillOnce(Return(Status::OK()));



    Status status = table_cache->Get(read_options, file_number, file_size, key, arg, handle_result);

    EXPECT_TRUE(status.ok());



    delete mock_handle;

    delete table_and_file;

}



TEST_F(TableCacheTest_351, GetNotFoundInCache_351) {

    ReadOptions read_options;

    uint64_t file_number = 1;

    uint64_t file_size = 1024;

    Slice key("test_key");

    void* arg = nullptr;

    auto handle_result = [](void*, const Slice&, const Slice&) {};



    EXPECT_CALL(*cache, Lookup(_))

        .WillOnce(Return(nullptr));



    Status status = table_cache->Get(read_options, file_number, file_size, key, arg, handle_result);

    EXPECT_TRUE(status.IsNotFound());

}



TEST_F(TableCacheTest_351, GetInternalGetFailure_351) {

    ReadOptions read_options;

    uint64_t file_number = 1;

    uint64_t file_size = 1024;

    Slice key("test_key");

    void* arg = nullptr;

    auto handle_result = [](void*, const Slice&, const Slice&) {};



    Cache::Handle* mock_handle = new Cache::Handle();

    TableAndFile* table_and_file = new TableAndFile{nullptr, mock_table};



    EXPECT_CALL(*cache, Lookup(_))

        .WillOnce(Return(mock_handle));

    EXPECT_CALL(*mock_table, InternalGet(_, key, arg, handle_result))

        .WillOnce(Return(Status::NotFound("Not found")));



    Status status = table_cache->Get(read_options, file_number, file_size, key, arg, handle_result);

    EXPECT_TRUE(status.IsNotFound());



    delete mock_handle;

    delete table_and_file;

}



TEST_F(TableCacheTest_351, GetBoundaryFileNumberZero_351) {

    ReadOptions read_options;

    uint64_t file_number = 0; // Boundary case

    uint64_t file_size = 1024;

    Slice key("test_key");

    void* arg = nullptr;

    auto handle_result = [](void*, const Slice&, const Slice&) {};



    EXPECT_CALL(*cache, Lookup(_))

        .WillOnce(Return(nullptr));



    Status status = table_cache->Get(read_options, file_number, file_size, key, arg, handle_result);

    EXPECT_TRUE(status.IsNotFound());

}



TEST_F(TableCacheTest_351, GetBoundaryFileSizeZero_351) {

    ReadOptions read_options;

    uint64_t file_number = 1;

    uint64_t file_size = 0; // Boundary case

    Slice key("test_key");

    void* arg = nullptr;

    auto handle_result = [](void*, const Slice&, const Slice&) {};



    EXPECT_CALL(*cache, Lookup(_))

        .WillOnce(Return(nullptr));



    Status status = table_cache->Get(read_options, file_number, file_size, key, arg, handle_result);

    EXPECT_TRUE(status.IsNotFound());

}



TEST_F(TableCacheTest_351, GetBoundaryEmptyKey_351) {

    ReadOptions read_options;

    uint64_t file_number = 1;

    uint64_t file_size = 1024;

    Slice key(""); // Boundary case

    void* arg = nullptr;

    auto handle_result = [](void*, const Slice&, const Slice&) {};



    EXPECT_CALL(*cache, Lookup(_))

        .WillOnce(Return(nullptr));



    Status status = table_cache->Get(read_options, file_number, file_size, key, arg, handle_result);

    EXPECT_TRUE(status.IsNotFound());

}



TEST_F(TableCacheTest_351, GetHandlerResultCalled_351) {

    ReadOptions read_options;

    uint64_t file_number = 1;

    uint64_t file_size = 1024;

    Slice key("test_key");

    void* arg = nullptr;



    Cache::Handle* mock_handle = new Cache::Handle();

    TableAndFile* table_and_file = new TableAndFile{nullptr, mock_table};



    EXPECT_CALL(*cache, Lookup(_))

        .WillOnce(Return(mock_handle));

    EXPECT_CALL(*mock_table, InternalGet(_, key, arg, _))

        .WillOnce(InvokeWithoutArgs([this]() {

            Slice value("test_value");

            table_cache->handle_result(table_cache->arg_, key, value);

            return Status::OK();

        }));



    bool handler_called = false;

    auto handle_result = [&handler_called](void*, const Slice&, const Slice&) {

        handler_called = true;

    };



    table_cache->arg_ = arg;

    table_cache->handle_result = handle_result;



    Status status = table_cache->Get(read_options, file_number, file_size, key, arg, handle_result);

    EXPECT_TRUE(status.ok());

    EXPECT_TRUE(handler_called);



    delete mock_handle;

    delete table_and_file;

}
