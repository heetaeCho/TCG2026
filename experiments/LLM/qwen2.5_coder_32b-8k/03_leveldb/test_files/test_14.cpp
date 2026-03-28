#include <gtest/gtest.h>

#include "leveldb/status.h"



namespace leveldb {



class StatusTest_14 : public ::testing::Test {

};



TEST_F(StatusTest_14, DefaultConstructorCreatesOkStatus_14) {

    Status status;

    EXPECT_TRUE(status.ok());

}



TEST_F(StatusTest_14, OkStaticMethodReturnsOkStatus_14) {

    Status status = Status::OK();

    EXPECT_TRUE(status.ok());

}



TEST_F(StatusTest_14, NotFoundStaticMethodCreatesNotFoundStatus_14) {

    Status status = Status::NotFound("Not found message");

    EXPECT_FALSE(status.ok());

    EXPECT_TRUE(status.IsNotFound());

}



TEST_F(StatusTest_14, CorruptionStaticMethodCreatesCorruptionStatus_14) {

    Status status = Status::Corruption("Corruption message");

    EXPECT_FALSE(status.ok());

    EXPECT_TRUE(status.IsCorruption());

}



TEST_F(StatusTest_14, IOErrorStaticMethodCreatesIOErrorStatus_14) {

    Status status = Status::IOError("IO error message");

    EXPECT_FALSE(status.ok());

    EXPECT_TRUE(status.IsIOError());

}



TEST_F(StatusTest_14, InvalidArgumentStaticMethodCreatesInvalidArgumentStatus_14) {

    Status status = Status::InvalidArgument("Invalid argument message");

    EXPECT_FALSE(status.ok());

    EXPECT_TRUE(status.IsInvalidArgument());

}



TEST_F(StatusTest_14, NotSupportedStaticMethodCreatesNotSupportedErrorStatus_14) {

    Status status = Status::NotSupported("Not supported message");

    EXPECT_FALSE(status.ok());

    EXPECT_TRUE(status.IsNotSupportedError());

}



TEST_F(StatusTest_14, ToStringReturnsEmptyStringForOkStatus_14) {

    Status status;

    EXPECT_EQ("", status.ToString());

}



TEST_F(StatusTest_14, ToStringIncludesErrorMessageForNotFound_14) {

    std::string msg = "Not found message";

    Status status = Status::NotFound(msg);

    EXPECT_TRUE(status.ToString().find(msg) != std::string::npos);

}



TEST_F(StatusTest_14, ToStringIncludesErrorMessageForCorruption_14) {

    std::string msg = "Corruption message";

    Status status = Status::Corruption(msg);

    EXPECT_TRUE(status.ToString().find(msg) != std::string::npos);

}



TEST_F(StatusTest_14, ToStringIncludesErrorMessageForIOError_14) {

    std::string msg = "IO error message";

    Status status = Status::IOError(msg);

    EXPECT_TRUE(status.ToString().find(msg) != std::string::npos);

}



TEST_F(StatusTest_14, ToStringIncludesErrorMessageForInvalidArgument_14) {

    std::string msg = "Invalid argument message";

    Status status = Status::InvalidArgument(msg);

    EXPECT_TRUE(status.ToString().find(msg) != std::string::npos);

}



TEST_F(StatusTest_14, ToStringIncludesErrorMessageForNotSupportedError_14) {

    std::string msg = "Not supported message";

    Status status = Status::NotSupported(msg);

    EXPECT_TRUE(status.ToString().find(msg) != std::string::npos);

}



TEST_F(StatusTest_14, CopyConstructorPreservesOkStatus_14) {

    Status original;

    Status copy = original;

    EXPECT_TRUE(copy.ok());

}



TEST_F(StatusTest_14, MoveConstructorPreservesOkStatus_14) {

    Status original;

    Status moved = std::move(original);

    EXPECT_TRUE(moved.ok());

}



TEST_F(StatusTest_14, CopyConstructorPreservesNotFoundStatus_14) {

    Status original = Status::NotFound("Not found message");

    Status copy = original;

    EXPECT_TRUE(copy.IsNotFound());

}



TEST_F(StatusTest_14, MoveConstructorPreservesNotFoundStatus_14) {

    Status original = Status::NotFound("Not found message");

    Status moved = std::move(original);

    EXPECT_TRUE(moved.IsNotFound());

}



}  // namespace leveldb
