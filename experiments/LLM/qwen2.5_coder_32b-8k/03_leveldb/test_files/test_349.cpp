#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/table_cache.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockCache : public Cache {

public:

    MOCK_METHOD(void, Insert, (const Slice& key, void* value, size_t charge,

                                void (*deleter)(const Slice& key, void* value)), (override));

    MOCK_METHOD(Handle*, Lookup, (const Slice& key), (override));

    MOCK_METHOD(void, Release, (Handle* handle), (override));

    MOCK_METHOD(void, Erase, (const Slice& key), (override));

};



class MockEnv : public Env {

public:

    MOCK_METHOD(Status, NewSequentialFile, (const std::string& fname, SequentialFile** result), (override));

    MOCK_METHOD(Status, NewRandomAccessFile, (const std::string& fname, RandomAccessFile** result), (override));

    MOCK_METHOD(Status, NewWritableFile, (const std::string& fname, WritableFile** result), (override));

};



class MockTable : public Table {

public:

    MOCK_METHOD(void, SeekToFirst, (), (override));

    MOCK_METHOD(void, SeekToLast, (), (override));

    MOCK_METHOD(void, Seek, (const Slice& target), (override));

    MOCK_METHOD(void, Next, (), (override));

    MOCK_METHOD(void, Prev, (), (override));

    MOCK_METHOD(bool, Valid, (), (const override));

    MOCK_METHOD(Slice, key, (), (const override));

    MOCK_METHOD(Slice, value, (), (const override));

    MOCK_METHOD(Status, Get, (const ReadOptions& options, const Slice& k, void* arg,

                              void (*handle_result)(void*, const Slice&, const Slice&)), (override));

};



class MockIterator : public Iterator {

public:

    MOCK_METHOD(bool, Valid, (), (const override));

    MOCK_METHOD(void, SeekToFirst, (), (override));

    MOCK_METHOD(void, SeekToLast, (), (override));

    MOCK_METHOD(void, Seek, (const Slice& target), (override));

    MOCK_METHOD(void, Next, (), (override));

    MOCK_METHOD(void, Prev, (), (override));

    MOCK_METHOD(Slice, key, (), (const override));

    MOCK_METHOD(Slice, value, (), (const override));

    MOCK_METHOD(Status, status, (), (const override));

};



class TableCacheTest_349 : public ::testing::Test {

protected:

    Options options_;

    MockEnv mock_env_;

    std::string dbname_ = "test_db";

    int cache_entries_ = 10;

    TableCache table_cache_;



    TableCacheTest_349() : table_cache_(dbname_, options_, cache_entries_) {

        options_.env = &mock_env_;

    }

};



TEST_F(TableCacheTest_349, NewIterator_ReturnsValidIterator_349) {

    ReadOptions read_options;

    uint64_t file_number = 1;

    uint64_t file_size = 1024;

    Table* tableptr;



    EXPECT_CALL(mock_env_, NewRandomAccessFile(_, _))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<1>(static_cast<RandomAccessFile*>(new RandomAccessFile())),

            Return(Status::OK())));



    Iterator* iterator = table_cache_.NewIterator(read_options, file_number, file_size, &tableptr);

    EXPECT_TRUE(iterator != nullptr);

    delete iterator;

}



TEST_F(TableCacheTest_349, Get_CallsHandleResultWithCorrectParameters_349) {

    ReadOptions read_options;

    uint64_t file_number = 1;

    uint64_t file_size = 1024;

    Slice key("test_key");

    void* arg = nullptr;



    EXPECT_CALL(mock_env_, NewRandomAccessFile(_, _))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<1>(static_cast<RandomAccessFile*>(new RandomAccessFile())),

            Return(Status::OK())));



    Slice value("test_value");

    auto handle_result = [](void* arg, const Slice& k, const Slice& v) {

        EXPECT_EQ(k.ToString(), "test_key");

        EXPECT_EQ(v.ToString(), "test_value");

    };



    table_cache_.Get(read_options, file_number, file_size, key, arg, handle_result);

}



TEST_F(TableCacheTest_349, Evict_RemovesEntryFromCache_349) {

    uint64_t file_number = 1;



    EXPECT_CALL(mock_env_, NewRandomAccessFile(_, _))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<1>(static_cast<RandomAccessFile*>(new RandomAccessFile())),

            Return(Status::OK())));



    table_cache_.Evict(file_number);

}



TEST_F(TableCacheTest_349, NewIterator_ReturnsNullOnEnvError_349) {

    ReadOptions read_options;

    uint64_t file_number = 1;

    uint64_t file_size = 1024;

    Table* tableptr;



    EXPECT_CALL(mock_env_, NewRandomAccessFile(_, _))

        .WillOnce(Return(Status::IOError()));



    Iterator* iterator = table_cache_.NewIterator(read_options, file_number, file_size, &tableptr);

    EXPECT_TRUE(iterator == nullptr);

}



TEST_F(TableCacheTest_349, Get_ReturnsNonOkStatusOnEnvError_349) {

    ReadOptions read_options;

    uint64_t file_number = 1;

    uint64_t file_size = 1024;

    Slice key("test_key");

    void* arg = nullptr;



    EXPECT_CALL(mock_env_, NewRandomAccessFile(_, _))

        .WillOnce(Return(Status::IOError()));



    auto handle_result = [](void* arg, const Slice& k, const Slice& v) {

        GTEST_FAIL() << "handle_result should not be called";

    };



    Status status = table_cache_.Get(read_options, file_number, file_size, key, arg, handle_result);

    EXPECT_TRUE(!status.ok());

}
