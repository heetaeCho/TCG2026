#include <gtest/gtest.h>

#include "leveldb/status.h"



class StatusTest_25 : public ::testing::Test {

};



TEST_F(StatusTest_25, OK_IsOk_25) {

    leveldb::Status status = leveldb::Status::OK();

    EXPECT_TRUE(status.ok());

}



TEST_F(StatusTest_25, NotFound_IsNotFound_25) {

    leveldb::Status status = leveldb::Status::NotFound("Not found error");

    EXPECT_TRUE(status.IsNotFound());

}



TEST_F(StatusTest_25, Corruption_IsCorruption_25) {

    leveldb::Status status = leveldb::Status::Corruption("Corruption error");

    EXPECT_TRUE(status.IsCorruption());

}



TEST_F(StatusTest_25, NotSupported_IsNotSupportedError_25) {

    leveldb::Status status = leveldb::Status::NotSupported("Not supported error");

    EXPECT_TRUE(status.IsNotSupportedError());

}



TEST_F(StatusTest_25, InvalidArgument_IsInvalidArgument_25) {

    leveldb::Status status = leveldb::Status::InvalidArgument("Invalid argument error");

    EXPECT_TRUE(status.IsInvalidArgument());

}



TEST_F(StatusTest_25, IOError_IsIOError_25) {

    leveldb::Status status = leveldb::Status::IOError("IO error");

    EXPECT_TRUE(status.IsIOError());

}



TEST_F(StatusTest_25, CopyConstructor_PreservesState_25) {

    leveldb::Status original = leveldb::Status::NotSupported("Not supported error");

    leveldb::Status copy = original;

    EXPECT_EQ(original.ToString(), copy.ToString());

    EXPECT_TRUE(copy.IsNotSupportedError());

}



TEST_F(StatusTest_25, MoveConstructor_PreservesState_25) {

    leveldb::Status original = leveldb::Status::Corruption("Corruption error");

    leveldb::Status moved = std::move(original);

    EXPECT_TRUE(moved.IsCorruption());

}



TEST_F(StatusTest_25, AssignmentOperator_PreservesState_25) {

    leveldb::Status original = leveldb::Status::IOError("IO error");

    leveldb::Status assigned;

    assigned = original;

    EXPECT_EQ(original.ToString(), assigned.ToString());

    EXPECT_TRUE(assigned.IsIOError());

}



TEST_F(StatusTest_25, MoveAssignmentOperator_PreservesState_25) {

    leveldb::Status original = leveldb::Status::InvalidArgument("Invalid argument error");

    leveldb::Status moved;

    moved = std::move(original);

    EXPECT_TRUE(moved.IsInvalidArgument());

}



TEST_F(StatusTest_25, ToString_ReturnsExpectedString_25) {

    leveldb::Status status = leveldb::Status::NotFound("Key not found", "Detailed info");

    std::string expected = "NotFound: Key not found : Detailed info";

    EXPECT_EQ(expected, status.ToString());

}



TEST_F(StatusTest_25, ToString_EmptyMessages_ReturnsExpectedString_25) {

    leveldb::Status status = leveldb::Status::Corruption();

    std::string expected = "Corruption: ";

    EXPECT_EQ(expected, status.ToString());

}
