#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/db.h"

#include "db/c.cc"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockDB : public DB {

public:

    MOCK_METHOD3(Delete, Status(const WriteOptions&, const Slice&, Status*));

};



class LevelDBCTest : public ::testing::Test {

protected:

    void SetUp() override {

        db = new MockDB();

        leveldb_t->rep = db;

        options = new leveldb_writeoptions_t();

    }



    void TearDown() override {

        delete leveldb_t;

        delete options;

    }



    leveldb_t* leveldb_t = new leveldb_t();

    leveldb_writeoptions_t* options;

    MockDB* db;

};



TEST_F(LevelDBCTest, DeleteSuccess_223) {

    const char* key = "test_key";

    size_t keylen = strlen(key);

    char* errptr = nullptr;



    EXPECT_CALL(*db, Delete(_, Slice(key, keylen), _))

        .WillOnce(Return(Status::OK()));



    leveldb_delete(leveldb_t, options, key, keylen, &errptr);



    ASSERT_EQ(errptr, nullptr);

}



TEST_F(LevelDBCTest, DeleteFailure_223) {

    const char* key = "test_key";

    size_t keylen = strlen(key);

    char* errptr = nullptr;

    Status expected_error = Status::NotFound("Key not found");



    EXPECT_CALL(*db, Delete(_, Slice(key, keylen), _))

        .WillOnce(Return(expected_error));



    leveldb_delete(leveldb_t, options, key, keylen, &errptr);



    ASSERT_NE(errptr, nullptr);

    std::string error_message = errptr;

    free(errptr);

    ASSERT_EQ(error_message, expected_error.ToString());

}



TEST_F(LevelDBCTest, DeleteEmptyKey_223) {

    const char* key = "";

    size_t keylen = strlen(key);

    char* errptr = nullptr;



    EXPECT_CALL(*db, Delete(_, Slice(key, keylen), _))

        .WillOnce(Return(Status::InvalidArgument("Empty key")));



    leveldb_delete(leveldb_t, options, key, keylen, &errptr);



    ASSERT_NE(errptr, nullptr);

    std::string error_message = errptr;

    free(errptr);

    ASSERT_EQ(error_message, Status::InvalidArgument("Empty key").ToString());

}



TEST_F(LevelDBCTest, DeleteNullKey_223) {

    const char* key = nullptr;

    size_t keylen = 0;

    char* errptr = nullptr;



    EXPECT_CALL(*db, Delete(_, Slice(key, keylen), _))

        .WillOnce(Return(Status::InvalidArgument("Null key")));



    leveldb_delete(leveldb_t, options, key, keylen, &errptr);



    ASSERT_NE(errptr, nullptr);

    std::string error_message = errptr;

    free(errptr);

    ASSERT_EQ(error_message, Status::InvalidArgument("Null key").ToString());

}
