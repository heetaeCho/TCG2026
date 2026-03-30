#include "gtest/gtest.h"

#include "leveldb/status.h"



using namespace leveldb;



class StatusTest_456 : public ::testing::Test {

protected:

    Status okStatus;

    Status notFoundStatus;

    Status corruptionStatus;

    Status notSupportedStatus;

    Status invalidArgumentStatus;

    Status ioErrorStatus;



    StatusTest_456()

        : okStatus(Status::OK()),

          notFoundStatus(Status::NotFound("Not found message")),

          corruptionStatus(Status::Corruption("Corruption message")),

          notSupportedStatus(Status::NotSupported("Not supported message")),

          invalidArgumentStatus(Status::InvalidArgument("Invalid argument message")),

          ioErrorStatus(Status::IOError("IO error message")) {}

};



TEST_F(StatusTest_456, OKStatus_ReturnsOKString_456) {

    EXPECT_EQ(okStatus.ToString(), "OK");

}



TEST_F(StatusTest_456, NotFoundStatus_ReturnsCorrectString_456) {

    EXPECT_EQ(notFoundStatus.ToString(), "NotFound: Not found message");

}



TEST_F(StatusTest_456, CorruptionStatus_ReturnsCorrectString_456) {

    EXPECT_EQ(corruptionStatus.ToString(), "Corruption: Corruption message");

}



TEST_F(StatusTest_456, NotSupportedStatus_ReturnsCorrectString_456) {

    EXPECT_EQ(notSupportedStatus.ToString(), "Not implemented: Not supported message");

}



TEST_F(StatusTest_456, InvalidArgumentStatus_ReturnsCorrectString_456) {

    EXPECT_EQ(invalidArgumentStatus.ToString(), "Invalid argument: Invalid argument message");

}



TEST_F(StatusTest_456, IOErrorStatus_ReturnsCorrectString_456) {

    EXPECT_EQ(ioErrorStatus.ToString(), "IO error: IO error message");

}



TEST_F(StatusTest_456, OKStatus_IsOK_ReturnsTrue_456) {

    EXPECT_TRUE(okStatus.ok());

}



TEST_F(StatusTest_456, NotFoundStatus_IsNotFound_ReturnsTrue_456) {

    EXPECT_TRUE(notFoundStatus.IsNotFound());

}



TEST_F(StatusTest_456, CorruptionStatus_IsCorruption_ReturnsTrue_456) {

    EXPECT_TRUE(corruptionStatus.IsCorruption());

}



TEST_F(StatusTest_456, NotSupportedStatus_IsNotSupportedError_ReturnsTrue_456) {

    EXPECT_TRUE(notSupportedStatus.IsNotSupportedError());

}



TEST_F(StatusTest_456, InvalidArgumentStatus_IsInvalidArgument_ReturnsTrue_456) {

    EXPECT_TRUE(invalidArgumentStatus.IsInvalidArgument());

}



TEST_F(StatusTest_456, IOErrorStatus_IsIOError_ReturnsTrue_456) {

    EXPECT_TRUE(ioErrorStatus.IsIOError());

}



TEST_F(StatusTest_456, NonOKStatus_IsOK_ReturnsFalse_456) {

    EXPECT_FALSE(notFoundStatus.ok());

    EXPECT_FALSE(corruptionStatus.ok());

    EXPECT_FALSE(notSupportedStatus.ok());

    EXPECT_FALSE(invalidArgumentStatus.ok());

    EXPECT_FALSE(ioErrorStatus.ok());

}



TEST_F(StatusTest_456, DefaultConstructedStatus_IsOK_ReturnsTrue_456) {

    Status defaultStatus;

    EXPECT_TRUE(defaultStatus.ok());

}
