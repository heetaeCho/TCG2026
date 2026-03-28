#include <gtest/gtest.h>

#include "leveldb/status.h"



using namespace leveldb;



class StatusTest_26 : public ::testing::Test {

protected:

    Status okStatus;

    Status notFoundStatus;

    Status corruptionStatus;

    Status notSupportedStatus;

    Status invalidArgumentStatus;

    Status ioErrorStatus;



    void SetUp() override {

        okStatus = Status::OK();

        notFoundStatus = Status::NotFound("Not found message");

        corruptionStatus = Status::Corruption("Corruption message");

        notSupportedStatus = Status::NotSupported("Not supported message");

        invalidArgumentStatus = Status::InvalidArgument("Invalid argument message");

        ioErrorStatus = Status::IOError("IO error message");

    }

};



TEST_F(StatusTest_26, OkStatus_ReturnsTrueForOk_26) {

    EXPECT_TRUE(okStatus.ok());

}



TEST_F(StatusTest_26, NotFoundStatus_ReturnsFalseForOk_26) {

    EXPECT_FALSE(notFoundStatus.ok());

}



TEST_F(StatusTest_26, CorruptionStatus_ReturnsFalseForOk_26) {

    EXPECT_FALSE(corruptionStatus.ok());

}



TEST_F(StatusTest_26, NotSupportedStatus_ReturnsFalseForOk_26) {

    EXPECT_FALSE(notSupportedStatus.ok());

}



TEST_F(StatusTest_26, InvalidArgumentStatus_ReturnsFalseForOk_26) {

    EXPECT_FALSE(invalidArgumentStatus.ok());

}



TEST_F(StatusTest_26, IOErrorStatus_ReturnsFalseForOk_26) {

    EXPECT_FALSE(ioErrorStatus.ok());

}



TEST_F(StatusTest_26, NotFoundStatus_IsNotFound_ReturnsTrue_26) {

    EXPECT_TRUE(notFoundStatus.IsNotFound());

}



TEST_F(StatusTest_26, CorruptionStatus_IsCorruption_ReturnsTrue_26) {

    EXPECT_TRUE(corruptionStatus.IsCorruption());

}



TEST_F(StatusTest_26, NotSupportedStatus_IsNotSupportedError_ReturnsTrue_26) {

    EXPECT_TRUE(notSupportedStatus.IsNotSupportedError());

}



TEST_F(StatusTest_26, InvalidArgumentStatus_IsInvalidArgument_ReturnsTrue_26) {

    EXPECT_TRUE(invalidArgumentStatus.IsInvalidArgument());

}



TEST_F(StatusTest_26, IOErrorStatus_IsIOError_ReturnsTrue_26) {

    EXPECT_TRUE(ioErrorStatus.IsIOError());

}



TEST_F(StatusTest_26, OkStatus_OtherIsMethods_ReturnFalse_26) {

    EXPECT_FALSE(okStatus.IsNotFound());

    EXPECT_FALSE(okStatus.IsCorruption());

    EXPECT_FALSE(okStatus.IsNotSupportedError());

    EXPECT_FALSE(okStatus.IsInvalidArgument());

    EXPECT_FALSE(okStatus.IsIOError());

}



TEST_F(StatusTest_26, NotFoundStatus_OtherIsMethods_ReturnFalse_26) {

    EXPECT_FALSE(notFoundStatus.IsCorruption());

    EXPECT_FALSE(notFoundStatus.IsNotSupportedError());

    EXPECT_FALSE(notFoundStatus.IsInvalidArgument());

    EXPECT_FALSE(notFoundStatus.IsIOError());

}



TEST_F(StatusTest_26, CorruptionStatus_OtherIsMethods_ReturnFalse_26) {

    EXPECT_FALSE(corruptionStatus.IsNotFound());

    EXPECT_FALSE(corruptionStatus.IsNotSupportedError());

    EXPECT_FALSE(corruptionStatus.IsInvalidArgument());

    EXPECT_FALSE(corruptionStatus.IsIOError());

}



TEST_F(StatusTest_26, NotSupportedStatus_OtherIsMethods_ReturnFalse_26) {

    EXPECT_FALSE(notSupportedStatus.IsNotFound());

    EXPECT_FALSE(notSupportedStatus.IsCorruption());

    EXPECT_FALSE(notSupportedStatus.IsInvalidArgument());

    EXPECT_FALSE(notSupportedStatus.IsIOError());

}



TEST_F(StatusTest_26, InvalidArgumentStatus_OtherIsMethods_ReturnFalse_26) {

    EXPECT_FALSE(invalidArgumentStatus.IsNotFound());

    EXPECT_FALSE(invalidArgumentStatus.IsCorruption());

    EXPECT_FALSE(invalidArgumentStatus.IsNotSupportedError());

    EXPECT_FALSE(invalidArgumentStatus.IsIOError());

}



TEST_F(StatusTest_26, IOErrorStatus_OtherIsMethods_ReturnFalse_26) {

    EXPECT_FALSE(ioErrorStatus.IsNotFound());

    EXPECT_FALSE(ioErrorStatus.IsCorruption());

    EXPECT_FALSE(ioErrorStatus.IsNotSupportedError());

    EXPECT_FALSE(ioErrorStatus.IsInvalidArgument());

}
