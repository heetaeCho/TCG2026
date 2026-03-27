#include <gtest/gtest.h>

#include "leveldb/status.h"



class StatusTest_28 : public ::testing::Test {

protected:

    leveldb::Status statusOK;

    leveldb::Status statusNotFound;

    leveldb::Status statusCorruption;

    leveldb::Status statusNotSupported;

    leveldb::Status statusInvalidArgument;

    leveldb::Status statusIOError;



    StatusTest_28()

        : statusOK(leveldb::Status::OK()),

          statusNotFound(leveldb::Status::NotFound("not found")),

          statusCorruption(leveldb::Status::Corruption("corruption")),

          statusNotSupported(leveldb::Status::NotSupported("not supported")),

          statusInvalidArgument(leveldb::Status::InvalidArgument("invalid argument")),

          statusIOError(leveldb::Status::IOError("io error")) {}

};



TEST_F(StatusTest_28, OK_ReturnsTrue_28) {

    EXPECT_TRUE(statusOK.ok());

}



TEST_F(StatusTest_28, NotFound_ReturnsFalseForOK_28) {

    EXPECT_FALSE(statusNotFound.ok());

}



TEST_F(StatusTest_28, Corruption_ReturnsFalseForOK_28) {

    EXPECT_FALSE(statusCorruption.ok());

}



TEST_F(StatusTest_28, NotSupported_ReturnsFalseForOK_28) {

    EXPECT_FALSE(statusNotSupported.ok());

}



TEST_F(StatusTest_28, InvalidArgument_ReturnsFalseForOK_28) {

    EXPECT_FALSE(statusInvalidArgument.ok());

}



TEST_F(StatusTest_28, IOError_ReturnsFalseForOK_28) {

    EXPECT_FALSE(statusIOError.ok());

}



TEST_F(StatusTest_28, IsNotFound_ReturnsTrue_28) {

    EXPECT_TRUE(statusNotFound.IsNotFound());

}



TEST_F(StatusTest_28, IsCorruption_ReturnsTrue_28) {

    EXPECT_TRUE(statusCorruption.IsCorruption());

}



TEST_F(StatusTest_28, IsNotSupportedError_ReturnsTrue_28) {

    EXPECT_TRUE(statusNotSupported.IsNotSupportedError());

}



TEST_F(StatusTest_28, IsInvalidArgument_ReturnsTrue_28) {

    EXPECT_TRUE(statusInvalidArgument.IsInvalidArgument());

}



TEST_F(StatusTest_28, IsIOError_ReturnsTrue_28) {

    EXPECT_TRUE(statusIOError.IsIOError());

}



TEST_F(StatusTest_28, ToString_IsNotEmptyForErrors_28) {

    EXPECT_FALSE(statusNotFound.ToString().empty());

    EXPECT_FALSE(statusCorruption.ToString().empty());

    EXPECT_FALSE(statusNotSupported.ToString().empty());

    EXPECT_FALSE(statusInvalidArgument.ToString().empty());

    EXPECT_FALSE(statusIOError.ToString().empty());

}



TEST_F(StatusTest_28, ToString_IsEmptyForOK_28) {

    EXPECT_TRUE(statusOK.ToString().empty());

}
