#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/db.h"

#include "db/c.cc"



using namespace leveldb;

using ::testing::Return;

using ::testing::NotNull;



class LeveldbPropertyTest_229 : public ::testing::Test {

protected:

    void SetUp() override {

        DB* mock_db = new DB();

        db_wrapper.rep = mock_db;

        ON_CALL(*mock_db, GetProperty(_, NotNull()))

            .WillByDefault(Return(false));

    }



    void TearDown() override {

        delete db_wrapper.rep;

    }



    leveldb_t db_wrapper;

};



TEST_F(LeveldbPropertyTest_229, PropertyNotFound_ReturnsNullptr_229) {

    char* result = leveldb_property_value(&db_wrapper, "nonexistent_property");

    EXPECT_EQ(result, nullptr);

}



TEST_F(LeveldbPropertyTest_229, ValidProperty_ReturnsNonNullString_229) {

    std::string expected_value = "some_value";

    ON_CALL(*db_wrapper.rep, GetProperty(_, NotNull()))

        .WillByDefault(DoAll(SetArgReferee<1>(expected_value), Return(true)));



    char* result = leveldb_property_value(&db_wrapper, "valid_property");

    EXPECT_NE(result, nullptr);

    EXPECT_STREQ(result, expected_value.c_str());

    free(result);

}



TEST_F(LeveldbPropertyTest_229, ValidProperty_ReturnsCorrectValue_229) {

    std::string expected_value = "expected_result";

    ON_CALL(*db_wrapper.rep, GetProperty(_, NotNull()))

        .WillByDefault(DoAll(SetArgReferee<1>(expected_value), Return(true)));



    char* result = leveldb_property_value(&db_wrapper, "test_property");

    EXPECT_STREQ(result, expected_value.c_str());

    free(result);

}



TEST_F(LeveldbPropertyTest_229, NullDb_ReturnsNullptr_229) {

    char* result = leveldb_property_value(nullptr, "any_property");

    EXPECT_EQ(result, nullptr);

}



TEST_F(LeveldbPropertyTest_229, NullPropertyName_ReturnsNullptr_229) {

    char* result = leveldb_property_value(&db_wrapper, nullptr);

    EXPECT_EQ(result, nullptr);

}
