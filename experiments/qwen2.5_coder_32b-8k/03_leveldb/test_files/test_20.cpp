#include <gtest/gtest.h>

#include "leveldb/status.h"



using namespace leveldb;



class StatusTest_20 : public ::testing::Test {

protected:

    // You can set up any common state here if needed.

};



TEST_F(StatusTest_20, DefaultConstructor_IsOk_20) {

    Status status;

    EXPECT_TRUE(status.ok());

}



TEST_F(StatusTest_20, OK_ReturnsOkStatus_20) {

    Status status = Status::OK();

    EXPECT_TRUE(status.ok());

}



TEST_F(StatusTest_20, NotFound_CreatesNotFoundStatus_20) {

    Status status = Status::NotFound("not found");

    EXPECT_FALSE(status.ok());

    EXPECT_TRUE(status.IsNotFound());

}



TEST_F(StatusTest_20, Corruption_CreatesCorruptionStatus_20) {

    Status status = Status::Corruption("corrupted data");

    EXPECT_FALSE(status.ok());

    EXPECT_TRUE(status.IsCorruption());

}



TEST_F(StatusTest_20, IOError_CreatesIOErrorStatus_20) {

    Status status = Status::IOError("io error occurred");

    EXPECT_FALSE(status.ok());

    EXPECT_TRUE(status.IsIOError());

}



TEST_F(StatusTest_20, NotSupported_CreatesNotSupportedStatus_20) {

    Status status = Status::NotSupported("not supported operation");

    EXPECT_FALSE(status.ok());

    EXPECT_TRUE(status.IsNotSupportedError());

}



TEST_F(StatusTest_20, InvalidArgument_CreatesInvalidArgumentStatus_20) {

    Status status = Status::InvalidArgument("invalid argument provided");

    EXPECT_FALSE(status.ok());

    EXPECT_TRUE(status.IsInvalidArgument());

}



TEST_F(StatusTest_20, ToString_ReturnsEmptyStringForOk_20) {

    Status status = Status::OK();

    EXPECT_EQ("", status.ToString());

}



TEST_F(StatusTest_20, ToString_ReturnsErrorMessageForNotFound_20) {

    Status status = Status::NotFound("not found");

    EXPECT_EQ("Not found: not found", status.ToString());

}



TEST_F(StatusTest_20, ToString_ReturnsErrorMessageForCorruption_20) {

    Status status = Status::Corruption("corrupted data");

    EXPECT_EQ("Corruption: corrupted data", status.ToString());

}



TEST_F(StatusTest_20, ToString_ReturnsErrorMessageForIOError_20) {

    Status status = Status::IOError("io error occurred");

    EXPECT_EQ("IO error: io error occurred", status.ToString());

}



TEST_F(StatusTest_20, ToString_ReturnsErrorMessageForNotSupported_20) {

    Status status = Status::NotSupported("not supported operation");

    EXPECT_EQ("Not implemented: not supported operation", status.ToString());

}



TEST_F(StatusTest_20, ToString_ReturnsErrorMessageForInvalidArgument_20) {

    Status status = Status::InvalidArgument("invalid argument provided");

    EXPECT_EQ("Invalid argument: invalid argument provided", status.ToString());

}
