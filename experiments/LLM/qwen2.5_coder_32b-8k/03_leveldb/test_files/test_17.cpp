#include "gtest/gtest.h"

#include "leveldb/status.h"



using namespace leveldb;



class StatusTest_17 : public ::testing::Test {

protected:

    // You can add any necessary setup here

};



TEST_F(StatusTest_17, OkStatusReturnsTrue_17) {

    Status status = Status::OK();

    EXPECT_TRUE(status.ok());

}



TEST_F(StatusTest_17, NotFoundStatusIsNotFoundReturnsTrue_17) {

    Status status = Status::NotFound("File not found");

    EXPECT_TRUE(status.IsNotFound());

}



TEST_F(StatusTest_17, CorruptionStatusIsCorruptionReturnsTrue_17) {

    Status status = Status::Corruption("Data corrupted");

    EXPECT_TRUE(status.IsCorruption());

}



TEST_F(StatusTest_17, NotSupportedStatusIsNotSupportedErrorReturnsTrue_17) {

    Status status = Status::NotSupported("Operation not supported");

    EXPECT_TRUE(status.IsNotSupportedError());

}



TEST_F(StatusTest_17, InvalidArgumentStatusIsInvalidArgumentReturnsTrue_17) {

    Status status = Status::InvalidArgument("Invalid argument provided");

    EXPECT_TRUE(status.IsInvalidArgument());

}



TEST_F(StatusTest_17, IOErrorStatusIsIOErrorReturnsTrue_17) {

    Status status = Status::IOError("IO Error occurred");

    EXPECT_TRUE(status.IsIOError());

}



TEST_F(StatusTest_17, DefaultConstructorCreatesOkStatus_17) {

    Status status;

    EXPECT_TRUE(status.ok());

}



TEST_F(StatusTest_17, ToStringForOKStatusReturnsEmptyString_17) {

    Status status = Status::OK();

    EXPECT_EQ(status.ToString(), "OK");

}



TEST_F(StatusTest_17, ToStringForCorruptionStatusIncludesMessage_17) {

    std::string message = "Data corrupted";

    Status status = Status::Corruption(message);

    EXPECT_TRUE(status.ToString().find("Corruption: Data corrupted") != std::string::npos);

}



TEST_F(StatusTest_17, CopyConstructorPreservesState_17) {

    Status original = Status::NotFound("File not found");

    Status copy = original;

    EXPECT_EQ(original.ToString(), copy.ToString());

}



TEST_F(StatusTest_17, MoveConstructorPreservesState_17) {

    Status original = Status::Corruption("Data corrupted");

    Status moved = std::move(original);

    EXPECT_TRUE(moved.IsCorruption());

}



TEST_F(StatusTest_17, AssignmentOperatorPreservesState_17) {

    Status original = Status::NotSupported("Operation not supported");

    Status assigned;

    assigned = original;

    EXPECT_EQ(original.ToString(), assigned.ToString());

}



TEST_F(StatusTest_17, MoveAssignmentOperatorPreservesState_17) {

    Status original = Status::InvalidArgument("Invalid argument provided");

    Status moved;

    moved = std::move(original);

    EXPECT_TRUE(moved.IsInvalidArgument());

}
