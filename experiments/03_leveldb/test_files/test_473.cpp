#include <gtest/gtest.h>

#include "leveldb/status.h"



using namespace leveldb;



class StatusTest_473 : public ::testing::Test {

protected:

    // No setup or teardown needed for this class

};



TEST_F(StatusTest_473, DefaultConstructorCreatesOkStatus_473) {

    Status status;

    EXPECT_TRUE(status.ok());

}



TEST_F(StatusTest_473, CopyConstructorPreservesState_473) {

    Status original = Status::NotFound("test message");

    Status copy(original);

    EXPECT_EQ(copy.ToString(), original.ToString());

}



TEST_F(StatusTest_473, MoveConstructorTransfersState_473) {

    Status original = Status::Corruption("test message");

    Status moved(std::move(original));

    EXPECT_TRUE(original.ok()); // After move, original should be OK

    EXPECT_EQ(moved.IsCorruption(), true);

}



TEST_F(StatusTest_473, AssignmentOperatorPreservesState_473) {

    Status original = Status::IOError("test message");

    Status assigned;

    assigned = original;

    EXPECT_EQ(assigned.ToString(), original.ToString());

}



TEST_F(StatusTest_473, MoveAssignmentOperatorTransfersState_473) {

    Status original = Status::InvalidArgument("test message");

    Status moved;

    moved = std::move(original);

    EXPECT_TRUE(original.ok()); // After move, original should be OK

    EXPECT_EQ(moved.IsInvalidArgument(), true);

}



TEST_F(StatusTest_473, ToStringReflectsStatus_473) {

    Status status = Status::NotFound("test message");

    EXPECT_NE(status.ToString().find("Not found"), std::string::npos);

    EXPECT_NE(status.ToString().find("test message"), std::string::npos);

}



TEST_F(StatusTest_473, OkReturnsTrueForOkStatus_473) {

    Status status = Status::OK();

    EXPECT_TRUE(status.ok());

}



TEST_F(StatusTest_473, OkReturnsFalseForNonOkStatus_473) {

    Status status = Status::Corruption("test message");

    EXPECT_FALSE(status.ok());

}



TEST_F(StatusTest_473, IsNotFoundDetectsNotFoundStatus_473) {

    Status status = Status::NotFound("test message");

    EXPECT_TRUE(status.IsNotFound());

}



TEST_F(StatusTest_473, IsNotSupportedErrorDetectsNotSupportedStatus_473) {

    Status status = Status::NotSupported("test message");

    EXPECT_TRUE(status.IsNotSupportedError());

}



TEST_F(StatusTest_473, IsInvalidArgumentDetectsInvalidArgumentStatus_473) {

    Status status = Status::InvalidArgument("test message");

    EXPECT_TRUE(status.IsInvalidArgument());

}



TEST_F(StatusTest_473, IsCorruptionDetectsCorruptionStatus_473) {

    Status status = Status::Corruption("test message");

    EXPECT_TRUE(status.IsCorruption());

}



TEST_F(StatusTest_473, IsIOErrorDetectsIOErrorStatus_473) {

    Status status = Status::IOError("test message");

    EXPECT_TRUE(status.IsIOError());

}
