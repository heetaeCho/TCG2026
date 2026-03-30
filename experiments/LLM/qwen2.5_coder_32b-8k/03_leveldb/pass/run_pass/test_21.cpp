#include <gtest/gtest.h>

#include "leveldb/status.h"



using namespace leveldb;



class StatusTest_21 : public ::testing::Test {

protected:

    // Setup and teardown methods can be added here if needed.

};



TEST_F(StatusTest_21, OKReturnsTrueWhenStateIsNull_21) {

    Status status = Status::OK();

    EXPECT_TRUE(status.ok());

}



TEST_F(StatusTest_21, NotFoundSetsAppropriateCode_21) {

    Status status = Status::NotFound("test message");

    EXPECT_FALSE(status.ok());

    EXPECT_TRUE(status.IsNotFound());

}



TEST_F(StatusTest_21, CorruptionSetsAppropriateCode_21) {

    Status status = Status::Corruption("test message");

    EXPECT_FALSE(status.ok());

    EXPECT_TRUE(status.IsCorruption());

}



TEST_F(StatusTest_21, IOErrorSetsAppropriateCode_21) {

    Status status = Status::IOError("test message");

    EXPECT_FALSE(status.ok());

    EXPECT_TRUE(status.IsIOError());

}



TEST_F(StatusTest_21, NotSupportedSetsAppropriateCode_21) {

    Status status = Status::NotSupported("test message");

    EXPECT_FALSE(status.ok());

    EXPECT_TRUE(status.IsNotSupportedError());

}



TEST_F(StatusTest_21, InvalidArgumentSetsAppropriateCode_21) {

    Status status = Status::InvalidArgument("test message");

    EXPECT_FALSE(status.ok());

    EXPECT_TRUE(status.IsInvalidArgument());

}



TEST_F(StatusTest_21, CopyConstructorPreservesState_21) {

    Status original = Status::NotFound("original message");

    Status copy = original;

    EXPECT_EQ(original.ToString(), copy.ToString());

}



TEST_F(StatusTest_21, MoveConstructorTransfersState_21) {

    Status original = Status::NotFound("original message");

    std::string originalToString = original.ToString();

    Status moved = std::move(original);

    EXPECT_EQ(originalToString, moved.ToString());

}



TEST_F(StatusTest_21, AssignmentOperatorPreservesState_21) {

    Status original = Status::NotFound("original message");

    Status assigned;

    assigned = original;

    EXPECT_EQ(original.ToString(), assigned.ToString());

}



TEST_F(StatusTest_21, MoveAssignmentOperatorTransfersState_21) {

    Status original = Status::NotFound("original message");

    std::string originalToString = original.ToString();

    Status moved;

    moved = std::move(original);

    EXPECT_EQ(originalToString, moved.ToString());

}
