#include <gtest/gtest.h>

#include "leveldb/status.h"



namespace leveldb {



class StatusTest_27 : public ::testing::Test {

protected:

    Status okStatus;

    Status notFoundStatus;

    Status corruptionStatus;

    Status ioErrorStatus;



    StatusTest_27()

        : okStatus(Status::OK()),

          notFoundStatus(Status::NotFound("Not Found")),

          corruptionStatus(Status::Corruption("Corruption")),

          ioErrorStatus(Status::IOError("IO Error")) {}

};



TEST_F(StatusTest_27, OKReturnsTrueForOkStatus_27) {

    EXPECT_TRUE(okStatus.ok());

}



TEST_F(StatusTest_27, OKReturnsFalseForNotFoundStatus_27) {

    EXPECT_FALSE(notFoundStatus.ok());

}



TEST_F(StatusTest_27, OKReturnsFalseForCorruptionStatus_27) {

    EXPECT_FALSE(corruptionStatus.ok());

}



TEST_F(StatusTest_27, OKReturnsFalseForIOErrorStatus_27) {

    EXPECT_FALSE(ioErrorStatus.ok());

}



TEST_F(StatusTest_27, IsNotFoundReturnsTrueForNotFoundStatus_27) {

    EXPECT_TRUE(notFoundStatus.IsNotFound());

}



TEST_F(StatusTest_27, IsNotFoundReturnsFalseForOkStatus_27) {

    EXPECT_FALSE(okStatus.IsNotFound());

}



TEST_F(StatusTest_27, IsCorruptionReturnsTrueForCorruptionStatus_27) {

    EXPECT_TRUE(corruptionStatus.IsCorruption());

}



TEST_F(StatusTest_27, IsCorruptionReturnsFalseForOkStatus_27) {

    EXPECT_FALSE(okStatus.IsCorruption());

}



TEST_F(StatusTest_27, IsIOErrorReturnsTrueForIOErrorStatus_27) {

    EXPECT_TRUE(ioErrorStatus.IsIOError());

}



TEST_F(StatusTest_27, IsIOErrorReturnsFalseForOkStatus_27) {

    EXPECT_FALSE(okStatus.IsIOError());

}



TEST_F(StatusTest_27, ToStringDoesNotThrowException_27) {

    EXPECT_NO_THROW(okStatus.ToString());

    EXPECT_NO_THROW(notFoundStatus.ToString());

    EXPECT_NO_THROW(corruptionStatus.ToString());

    EXPECT_NO_THROW(ioErrorStatus.ToString());

}



TEST_F(StatusTest_27, CopyConstructorPreservesState_27) {

    Status copyNotFoundStatus(notFoundStatus);

    EXPECT_TRUE(copyNotFoundStatus.IsNotFound());

}



TEST_F(StatusTest_27, MoveConstructorTransfersState_27) {

    Status movedNotFoundStatus(std::move(notFoundStatus));

    EXPECT_TRUE(movedNotFoundStatus.IsNotFound());

}



TEST_F(StatusTest_27, AssignmentOperatorPreservesState_27) {

    Status assignedStatus;

    assignedStatus = notFoundStatus;

    EXPECT_TRUE(assignedStatus.IsNotFound());

}



TEST_F(StatusTest_27, MoveAssignmentOperatorTransfersState_27) {

    Status moveAssignedStatus;

    moveAssignedStatus = std::move(notFoundStatus);

    EXPECT_TRUE(moveAssignedStatus.IsNotFound());

}



} // namespace leveldb
