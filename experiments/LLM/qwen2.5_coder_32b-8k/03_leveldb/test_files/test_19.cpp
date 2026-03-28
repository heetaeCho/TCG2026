#include "gtest/gtest.h"

#include "leveldb/status.h"



namespace leveldb {



class StatusTest_19 : public ::testing::Test {

protected:

    Status okStatus;

    Status invalidArgumentStatus;



    StatusTest_19() : okStatus(Status::OK()),

                      invalidArgumentStatus(Status::InvalidArgument("test message")) {}

};



TEST_F(StatusTest_19, OK_IsOk_ReturnsTrue_19) {

    EXPECT_TRUE(okStatus.ok());

}



TEST_F(StatusTest_19, OK_IsNotFound_ReturnsFalse_19) {

    EXPECT_FALSE(okStatus.IsNotFound());

}



TEST_F(StatusTest_19, OK_IsCorruption_ReturnsFalse_19) {

    EXPECT_FALSE(okStatus.IsCorruption());

}



TEST_F(StatusTest_19, OK_IsIOError_ReturnsFalse_19) {

    EXPECT_FALSE(okStatus.IsIOError());

}



TEST_F(StatusTest_19, OK_IsNotSupportedError_ReturnsFalse_19) {

    EXPECT_FALSE(okStatus.IsNotSupportedError());

}



TEST_F(StatusTest_19, OK_IsInvalidArgument_ReturnsFalse_19) {

    EXPECT_FALSE(okStatus.IsInvalidArgument());

}



TEST_F(StatusTest_19, InvalidArgument_IsOk_ReturnsFalse_19) {

    EXPECT_FALSE(invalidArgumentStatus.ok());

}



TEST_F(StatusTest_19, InvalidArgument_IsNotFound_ReturnsFalse_19) {

    EXPECT_FALSE(invalidArgumentStatus.IsNotFound());

}



TEST_F(StatusTest_19, InvalidArgument_IsCorruption_ReturnsFalse_19) {

    EXPECT_FALSE(invalidArgumentStatus.IsCorruption());

}



TEST_F(StatusTest_19, InvalidArgument_IsIOError_ReturnsFalse_19) {

    EXPECT_FALSE(invalidArgumentStatus.IsIOError());

}



TEST_F(StatusTest_19, InvalidArgument_IsNotSupportedError_ReturnsFalse_19) {

    EXPECT_FALSE(invalidArgumentStatus.IsNotSupportedError());

}



TEST_F(StatusTest_19, InvalidArgument_IsInvalidArgument_ReturnsTrue_19) {

    EXPECT_TRUE(invalidArgumentStatus.IsInvalidArgument());

}



TEST_F(StatusTest_19, ToString_EmptyMessage_ReturnsOkString_19) {

    EXPECT_EQ(okStatus.ToString(), "OK");

}



TEST_F(StatusTest_19, ToString_NonEmptyMessage_ReturnsCorrectString_19) {

    EXPECT_EQ(invalidArgumentStatus.ToString(), "Invalid argument: test message");

}



}  // namespace leveldb
