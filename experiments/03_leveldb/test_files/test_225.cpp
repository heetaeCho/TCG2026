#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/c.h"

#include "leveldb/db.h"



using namespace leveldb;

using ::testing::Return;



class MockDB : public DB {

public:

    MOCK_METHOD(Status, Get, (const ReadOptions&, const Slice&, std::string*), (override));

};



TEST_F(MockDBTest_225, Get_NormalOperation_ReturnsValue_225) {

    MockDB mock_db;

    leveldb_t db;

    db.rep = &mock_db;



    leveldb_readoptions_t options;

    const char key[] = "test_key";

    size_t vallen;

    char* result;

    char** errptr = nullptr;



    std::string expected_value = "test_value";

    EXPECT_CALL(mock_db, Get(options.rep, Slice(key, sizeof(key) - 1), testing::_))

        .WillOnce(DoAll(SetArgReferee<2>(expected_value), Return(Status::OK())));



    result = leveldb_get(&db, &options, key, sizeof(key) - 1, &vallen, errptr);

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(std::string(result, vallen), expected_value);

    free(result);

}



TEST_F(MockDBTest_225, Get_NotFound_ReturnsNull_225) {

    MockDB mock_db;

    leveldb_t db;

    db.rep = &mock_db;



    leveldb_readoptions_t options;

    const char key[] = "non_existent_key";

    size_t vallen;

    char* result;

    char** errptr = nullptr;



    EXPECT_CALL(mock_db, Get(options.rep, Slice(key, sizeof(key) - 1), testing::_))

        .WillOnce(Return(Status::NotFound(Slice(), Slice())));



    result = leveldb_get(&db, &options, key, sizeof(key) - 1, &vallen, errptr);

    EXPECT_EQ(result, nullptr);

    EXPECT_EQ(vallen, 0);

}



TEST_F(MockDBTest_225, Get_Error_ReturnsNullAndError_225) {

    MockDB mock_db;

    leveldb_t db;

    db.rep = &mock_db;



    leveldb_readoptions_t options;

    const char key[] = "error_key";

    size_t vallen;

    char* result;

    char* errptr = nullptr;



    std::string error_message = "Error occurred";

    EXPECT_CALL(mock_db, Get(options.rep, Slice(key, sizeof(key) - 1), testing::_))

        .WillOnce(DoAll(SaveArg<2>(&error_message), Return(Status::IOError(Slice(), Slice()))));



    result = leveldb_get(&db, &options, key, sizeof(key) - 1, &vallen, &errptr);

    EXPECT_EQ(result, nullptr);

    EXPECT_EQ(vallen, 0);

    ASSERT_NE(errptr, nullptr);

    std::string error_string(errptr);

    free(errptr);

    EXPECT_EQ(error_string, "IOError: ");

}



TEST_F(MockDBTest_225, Get_EmptyKey_ReturnsNull_225) {

    MockDB mock_db;

    leveldb_t db;

    db.rep = &mock_db;



    leveldb_readoptions_t options;

    const char key[] = "";

    size_t vallen;

    char* result;

    char** errptr = nullptr;



    EXPECT_CALL(mock_db, Get(options.rep, Slice(key, 0), testing::_))

        .WillOnce(Return(Status::InvalidArgument(Slice(), Slice())));



    result = leveldb_get(&db, &options, key, 0, &vallen, errptr);

    EXPECT_EQ(result, nullptr);

    EXPECT_EQ(vallen, 0);

}



TEST_F(MockDBTest_225, Get_NullKey_ReturnsNull_225) {

    MockDB mock_db;

    leveldb_t db;

    db.rep = &mock_db;



    leveldb_readoptions_t options;

    const char* key = nullptr;

    size_t vallen;

    char* result;

    char** errptr = nullptr;



    EXPECT_CALL(mock_db, Get(options.rep, Slice(key, 0), testing::_))

        .WillOnce(Return(Status::InvalidArgument(Slice(), Slice())));



    result = leveldb_get(&db, &options, key, 0, &vallen, errptr);

    EXPECT_EQ(result, nullptr);

    EXPECT_EQ(vallen, 0);

}



TEST_F(MockDBTest_225, Get_LargeKey_ReturnsValue_225) {

    MockDB mock_db;

    leveldb_t db;

    db.rep = &mock_db;



    leveldb_readoptions_t options;

    std::string large_key(1000, 'a');

    size_t vallen;

    char* result;

    char** errptr = nullptr;



    std::string expected_value = "large_test_value";

    EXPECT_CALL(mock_db, Get(options.rep, Slice(large_key), testing::_))

        .WillOnce(DoAll(SetArgReferee<2>(expected_value), Return(Status::OK())));



    result = leveldb_get(&db, &options, large_key.c_str(), large_key.size(), &vallen, errptr);

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(std::string(result, vallen), expected_value);

    free(result);

}
