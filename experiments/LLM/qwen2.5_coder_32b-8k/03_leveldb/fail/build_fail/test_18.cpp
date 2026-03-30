#include <gtest/gtest.h>

#include "leveldb/status.h"

#include "leveldb/slice.h"



namespace {



class StatusTest_18 : public ::testing::Test {

protected:

    using leveldb::Status;

    using leveldb::Slice;



    void SetUp() override {

        // No setup required for this test suite

    }



    void TearDown() override {

        // No teardown required for this test suite

    }

};



TEST_F(StatusTest_18, OK_ReturnsTrueWhenOk_18) {

    Status status = Status::OK();

    EXPECT_TRUE(status.ok());

}



TEST_F(StatusTest_18, NotFound_ReturnsNotFoundStatus_18) {

    Status status = Status::NotFound("File not found");

    EXPECT_FALSE(status.ok());

    EXPECT_TRUE(status.IsNotFound());

}



TEST_F(StatusTest_18, Corruption_ReturnsCorruptionStatus_18) {

    Status status = Status::Corruption("Data corrupted");

    EXPECT_FALSE(status.ok());

    EXPECT_TRUE(status.IsCorruption());

}



TEST_F(StatusTest_18, NotSupported_ReturnsNotSupportedStatus_18) {

    Status status = Status::NotSupported("Operation not supported");

    EXPECT_FALSE(status.ok());

    EXPECT_TRUE(status.IsNotSupportedError());

}



TEST_F(StatusTest_18, InvalidArgument_ReturnsInvalidArgumentStatus_18) {

    Status status = Status::InvalidArgument("Invalid argument provided");

    EXPECT_FALSE(status.ok());

    EXPECT_TRUE(status.IsInvalidArgument());

}



TEST_F(StatusTest_18, IOError_ReturnsIOErrorStatus_18) {

    Status status = Status::IOError("I/O error occurred");

    EXPECT_FALSE(status.ok());

    EXPECT_TRUE(status.IsIOError());

}



TEST_F(StatusTest_18, ToString_ReturnsExpectedStringForOK_18) {

    Status status = Status::OK();

    EXPECT_EQ(status.ToString(), "OK");

}



TEST_F(StatusTest_18, ToString_ReturnsExpectedStringForNotFound_18) {

    Slice msg("File not found");

    Status status = Status::NotFound(msg);

    EXPECT_EQ(status.ToString(), "NotFound: File not found");

}



TEST_F(StatusTest_18, ToString_ReturnsExpectedStringForCorruption_18) {

    Slice msg("Data corrupted");

    Status status = Status::Corruption(msg);

    EXPECT_EQ(status.ToString(), "Corruption: Data corrupted");

}



TEST_F(StatusTest_18, ToString_ReturnsExpectedStringForNotSupported_18) {

    Slice msg("Operation not supported");

    Status status = Status::NotSupported(msg);

    EXPECT_EQ(status.ToString(), "NotSupported: Operation not supported");

}



TEST_F(StatusTest_18, ToString_ReturnsExpectedStringForInvalidArgument_18) {

    Slice msg("Invalid argument provided");

    Status status = Status::InvalidArgument(msg);

    EXPECT_EQ(status.ToString(), "InvalidArgument: Invalid argument provided");

}



TEST_F(StatusTest_18, ToString_ReturnsExpectedStringForIOError_18) {

    Slice msg("I/O error occurred");

    Status status = Status::IOError(msg);

    EXPECT_EQ(status.ToString(), "IOError: I/O error occurred");

}



}  // namespace
