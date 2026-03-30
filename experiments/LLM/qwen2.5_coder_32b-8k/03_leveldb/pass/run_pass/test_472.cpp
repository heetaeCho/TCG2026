#include <gtest/gtest.h>

#include "leveldb/status.h"



using namespace leveldb;



class StatusTest_472 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(StatusTest_472, DefaultConstructor_Ok_472) {

    Status status;

    EXPECT_TRUE(status.ok());

}



TEST_F(StatusTest_472, OK_ReturnsOkStatus_472) {

    Status status = Status::OK();

    EXPECT_TRUE(status.ok());

}



TEST_F(StatusTest_472, NotFound_ReturnsNotFoundStatus_472) {

    Status status = Status::NotFound("not found");

    EXPECT_FALSE(status.ok());

    EXPECT_TRUE(status.IsNotFound());

}



TEST_F(StatusTest_472, Corruption_ReturnsCorruptionStatus_472) {

    Status status = Status::Corruption("corrupted data");

    EXPECT_FALSE(status.ok());

    EXPECT_TRUE(status.IsCorruption());

}



TEST_F(StatusTest_472, IOError_ReturnsIOErrorStatus_472) {

    Status status = Status::IOError("io error");

    EXPECT_FALSE(status.ok());

    EXPECT_TRUE(status.IsIOError());

}



TEST_F(StatusTest_472, NotSupported_ReturnsNotSupportedStatus_472) {

    Status status = Status::NotSupported("not supported");

    EXPECT_FALSE(status.ok());

    EXPECT_TRUE(status.IsNotSupportedError());

}



TEST_F(StatusTest_472, InvalidArgument_ReturnsInvalidArgumentStatus_472) {

    Status status = Status::InvalidArgument("invalid argument");

    EXPECT_FALSE(status.ok());

    EXPECT_TRUE(status.IsInvalidArgument());

}



TEST_F(StatusTest_472, CopyConstructor_SameState_472) {

    Status original = Status::NotFound("not found");

    Status copy = original;

    EXPECT_EQ(original.ToString(), copy.ToString());

}



TEST_F(StatusTest_472, MoveConstructor_TakesOwnershipOfState_472) {

    Status original = Status::Corruption("corrupted data");

    Status moved = std::move(original);

    EXPECT_TRUE(original.ok());  // original should be in a valid but unspecified state

    EXPECT_FALSE(moved.ok());

}



TEST_F(StatusTest_472, AssignmentOperator_SameState_472) {

    Status original = Status::IOError("io error");

    Status assigned;

    assigned = original;

    EXPECT_EQ(original.ToString(), assigned.ToString());

}



TEST_F(StatusTest_472, MoveAssignmentOperator_TakesOwnershipOfState_472) {

    Status original = Status::NotSupported("not supported");

    Status moved;

    moved = std::move(original);

    EXPECT_TRUE(original.ok());  // original should be in a valid but unspecified state

    EXPECT_FALSE(moved.ok());

}



TEST_F(StatusTest_472, ToString_ReturnsMeaningfulString_472) {

    Status status = Status::InvalidArgument("invalid argument");

    std::string message = status.ToString();

    EXPECT_EQ(message.find("Invalid argument: invalid argument"), 0U);

}
