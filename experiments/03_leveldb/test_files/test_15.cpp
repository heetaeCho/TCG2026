#include <gtest/gtest.h>

#include "leveldb/status.h"



using namespace leveldb;



class StatusTest_15 : public ::testing::Test {

protected:

    Status okStatus;

    Status notFoundStatus;

    Status corruptionStatus;

    Status ioErrorStatus;

    Status notSupportedStatus;

    Status invalidArgumentStatus;



    void SetUp() override {

        okStatus = Status::OK();

        notFoundStatus = Status::NotFound("Not found");

        corruptionStatus = Status::Corruption("Corruption occurred");

        ioErrorStatus = Status::IOError("IO Error");

        notSupportedStatus = Status::NotSupported("Not supported");

        invalidArgumentStatus = Status::InvalidArgument("Invalid argument");

    }

};



TEST_F(StatusTest_15, OkReturnsTrueForOkStatus_15) {

    EXPECT_TRUE(okStatus.ok());

}



TEST_F(StatusTest_15, OkReturnsFalseForNotFoundStatus_15) {

    EXPECT_FALSE(notFoundStatus.ok());

}



TEST_F(StatusTest_15, OkReturnsFalseForCorruptionStatus_15) {

    EXPECT_FALSE(corruptionStatus.ok());

}



TEST_F(StatusTest_15, OkReturnsFalseForIoErrorStatus_15) {

    EXPECT_FALSE(ioErrorStatus.ok());

}



TEST_F(StatusTest_15, OkReturnsFalseForNotSupportedStatus_15) {

    EXPECT_FALSE(notSupportedStatus.ok());

}



TEST_F(StatusTest_15, OkReturnsFalseForInvalidArgumentStatus_15) {

    EXPECT_FALSE(invalidArgumentStatus.ok());

}



TEST_F(StatusTest_15, IsNotFoundReturnsTrueForNotFoundStatus_15) {

    EXPECT_TRUE(notFoundStatus.IsNotFound());

}



TEST_F(StatusTest_15, IsNotFoundReturnsFalseForOkStatus_15) {

    EXPECT_FALSE(okStatus.IsNotFound());

}



TEST_F(StatusTest_15, IsCorruptionReturnsTrueForCorruptionStatus_15) {

    EXPECT_TRUE(corruptionStatus.IsCorruption());

}



TEST_F(StatusTest_15, IsCorruptionReturnsFalseForOkStatus_15) {

    EXPECT_FALSE(okStatus.IsCorruption());

}



TEST_F(StatusTest_15, IsIOErrorReturnsTrueForIoErrorStatus_15) {

    EXPECT_TRUE(ioErrorStatus.IsIOError());

}



TEST_F(StatusTest_15, IsIOErrorReturnsFalseForOkStatus_15) {

    EXPECT_FALSE(okStatus.IsIOError());

}



TEST_F(StatusTest_15, IsNotSupportedErrorReturnsTrueForNotSupportedStatus_15) {

    EXPECT_TRUE(notSupportedStatus.IsNotSupportedError());

}



TEST_F(StatusTest_15, IsNotSupportedErrorReturnsFalseForOkStatus_15) {

    EXPECT_FALSE(okStatus.IsNotSupportedError());

}



TEST_F(StatusTest_15, IsInvalidArgumentReturnsTrueForInvalidArgumentStatus_15) {

    EXPECT_TRUE(invalidArgumentStatus.IsInvalidArgument());

}



TEST_F(StatusTest_15, IsInvalidArgumentReturnsFalseForOkStatus_15) {

    EXPECT_FALSE(okStatus.IsInvalidArgument());

}
