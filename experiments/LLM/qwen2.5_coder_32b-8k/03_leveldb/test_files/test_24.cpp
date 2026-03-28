#include <gtest/gtest.h>

#include "leveldb/status.h"



class StatusTest_24 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(StatusTest_24, OKStatus_IsOK_24) {

    leveldb::Status status = leveldb::Status::OK();

    EXPECT_TRUE(status.ok());

}



TEST_F(StatusTest_24, NotFoundStatus_IsNotFound_24) {

    leveldb::Status status = leveldb::Status::NotFound("Not found message");

    EXPECT_TRUE(status.IsNotFound());

    EXPECT_FALSE(status.ok());

}



TEST_F(StatusTest_24, CorruptionStatus_IsCorruption_24) {

    leveldb::Status status = leveldb::Status::Corruption("Corruption message");

    EXPECT_TRUE(status.IsCorruption());

    EXPECT_FALSE(status.ok());

}



TEST_F(StatusTest_24, IOErrorStatus_IsIOError_24) {

    leveldb::Status status = leveldb::Status::IOError("IO error message");

    EXPECT_TRUE(status.IsIOError());

    EXPECT_FALSE(status.ok());

}



TEST_F(StatusTest_24, NotSupportedStatus_IsNotSupportedError_24) {

    leveldb::Status status = leveldb::Status::NotSupported("Not supported message");

    EXPECT_TRUE(status.IsNotSupportedError());

    EXPECT_FALSE(status.ok());

}



TEST_F(StatusTest_24, InvalidArgumentStatus_IsInvalidArgument_24) {

    leveldb::Status status = leveldb::Status::InvalidArgument("Invalid argument message");

    EXPECT_TRUE(status.IsInvalidArgument());

    EXPECT_FALSE(status.ok());

}



TEST_F(StatusTest_24, CopyConstructor_StatusOK_24) {

    leveldb::Status original = leveldb::Status::OK();

    leveldb::Status copy = original;

    EXPECT_EQ(original.ToString(), copy.ToString());

    EXPECT_TRUE(copy.ok());

}



TEST_F(StatusTest_24, MoveConstructor_StatusIOError_24) {

    leveldb::Status original = leveldb::Status::IOError("Move constructor error");

    leveldb::Status moved = std::move(original);

    EXPECT_EQ(moved.IsIOError(), true);

    EXPECT_FALSE(original.ok());  // Original should be in a valid but unspecified state

}



TEST_F(StatusTest_24, AssignmentOperator_StatusCorruption_24) {

    leveldb::Status original = leveldb::Status::Corruption("Assignment operator error");

    leveldb::Status assigned;

    assigned = original;

    EXPECT_EQ(assigned.IsCorruption(), true);

    EXPECT_FALSE(assigned.ok());

}



TEST_F(StatusTest_24, MoveAssignmentOperator_StatusNotFound_24) {

    leveldb::Status original = leveldb::Status::NotFound("Move assignment error");

    leveldb::Status moved;

    moved = std::move(original);

    EXPECT_EQ(moved.IsNotFound(), true);

    EXPECT_FALSE(original.ok());  // Original should be in a valid but unspecified state

}



TEST_F(StatusTest_24, ToString_ReturnsValidString_24) {

    leveldb::Status status = leveldb::Status::IOError("Custom error message");

    std::string str = status.ToString();

    EXPECT_FALSE(str.empty());

    EXPECT_EQ(str.find("IOError"), 0);  // StartsWith check

}
