#include <gtest/gtest.h>

#include "leveldb/status.h"



using namespace leveldb;



class StatusTest_23 : public ::testing::Test {

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



TEST_F(StatusTest_23, Ok_ReturnsTrueForOkStatus_23) {

    EXPECT_TRUE(okStatus.ok());

}



TEST_F(StatusTest_23, Ok_ReturnsFalseForNonOkStatus_23) {

    EXPECT_FALSE(notFoundStatus.ok());

    EXPECT_FALSE(corruptionStatus.ok());

    EXPECT_FALSE(notSupportedStatus.ok());

    EXPECT_FALSE(invalidArgumentStatus.ok());

    EXPECT_FALSE(ioErrorStatus.ok());

}



TEST_F(StatusTest_23, IsNotFound_ReturnsTrueForNotFoundStatus_23) {

    EXPECT_TRUE(notFoundStatus.IsNotFound());

}



TEST_F(StatusTest_23, IsNotFound_ReturnsFalseForOtherStatuses_23) {

    EXPECT_FALSE(okStatus.IsNotFound());

    EXPECT_FALSE(corruptionStatus.IsNotFound());

    EXPECT_FALSE(notSupportedStatus.IsNotFound());

    EXPECT_FALSE(invalidArgumentStatus.IsNotFound());

    EXPECT_FALSE(ioErrorStatus.IsNotFound());

}



TEST_F(StatusTest_23, IsCorruption_ReturnsTrueForCorruptionStatus_23) {

    EXPECT_TRUE(corruptionStatus.IsCorruption());

}



TEST_F(StatusTest_23, IsCorruption_ReturnsFalseForOtherStatuses_23) {

    EXPECT_FALSE(okStatus.IsCorruption());

    EXPECT_FALSE(notFoundStatus.IsCorruption());

    EXPECT_FALSE(notSupportedStatus.IsCorruption());

    EXPECT_FALSE(invalidArgumentStatus.IsCorruption());

    EXPECT_FALSE(ioErrorStatus.IsCorruption());

}



TEST_F(StatusTest_23, IsNotSupported_ReturnsTrueForNotSupportedStatus_23) {

    EXPECT_TRUE(notSupportedStatus.IsNotSupportedError());

}



TEST_F(StatusTest_23, IsNotSupported_ReturnsFalseForOtherStatuses_23) {

    EXPECT_FALSE(okStatus.IsNotSupportedError());

    EXPECT_FALSE(notFoundStatus.IsNotSupportedError());

    EXPECT_FALSE(corruptionStatus.IsNotSupportedError());

    EXPECT_FALSE(invalidArgumentStatus.IsNotSupportedError());

    EXPECT_FALSE(ioErrorStatus.IsNotSupportedError());

}



TEST_F(StatusTest_23, IsInvalidArgument_ReturnsTrueForInvalidArgumentStatus_23) {

    EXPECT_TRUE(invalidArgumentStatus.IsInvalidArgument());

}



TEST_F(StatusTest_23, IsInvalidArgument_ReturnsFalseForOtherStatuses_23) {

    EXPECT_FALSE(okStatus.IsInvalidArgument());

    EXPECT_FALSE(notFoundStatus.IsInvalidArgument());

    EXPECT_FALSE(corruptionStatus.IsInvalidArgument());

    EXPECT_FALSE(notSupportedStatus.IsInvalidArgument());

    EXPECT_FALSE(ioErrorStatus.IsInvalidArgument());

}



TEST_F(StatusTest_23, IsIOError_ReturnsTrueForIOErrorStatus_23) {

    EXPECT_TRUE(ioErrorStatus.IsIOError());

}



TEST_F(StatusTest_23, IsIOError_ReturnsFalseForOtherStatuses_23) {

    EXPECT_FALSE(okStatus.IsIOError());

    EXPECT_FALSE(notFoundStatus.IsIOError());

    EXPECT_FALSE(corruptionStatus.IsIOError());

    EXPECT_FALSE(notSupportedStatus.IsIOError());

    EXPECT_FALSE(invalidArgumentStatus.IsIOError());

}



TEST_F(StatusTest_23, ToString_ReturnsNonEmptyStringForAllStatuses_23) {

    EXPECT_FALSE(okStatus.ToString().empty());

    EXPECT_FALSE(notFoundStatus.ToString().empty());

    EXPECT_FALSE(corruptionStatus.ToString().empty());

    EXPECT_FALSE(notSupportedStatus.ToString().empty());

    EXPECT_FALSE(invalidArgumentStatus.ToString().empty());

    EXPECT_FALSE(ioErrorStatus.ToString().empty());

}



TEST_F(StatusTest_23, CopyConstructor_CreatesEquivalentStatus_23) {

    Status copiedOkStatus(okStatus);

    Status copiedNotFoundStatus(notFoundStatus);

    Status copiedCorruptionStatus(corruptionStatus);



    EXPECT_EQ(okStatus.ToString(), copiedOkStatus.ToString());

    EXPECT_EQ(notFoundStatus.ToString(), copiedNotFoundStatus.ToString());

    EXPECT_EQ(corruptionStatus.ToString(), copiedCorruptionStatus.ToString());

}



TEST_F(StatusTest_23, MoveConstructor_CreatesEquivalentStatus_23) {

    Status movedOkStatus(std::move(Status::OK()));

    Status movedNotFoundStatus(std::move(Status::NotFound("Not found message")));

    Status movedCorruptionStatus(std::move(Status::Corruption("Corruption message")));



    EXPECT_EQ(okStatus.ToString(), movedOkStatus.ToString());

    EXPECT_EQ(notFoundStatus.ToString(), movedNotFoundStatus.ToString());

    EXPECT_EQ(corruptionStatus.ToString(), movedCorruptionStatus.ToString());

}



TEST_F(StatusTest_23, CopyAssignmentOperator_CreatesEquivalentStatus_23) {

    Status assignedOkStatus;

    Status assignedNotFoundStatus;

    Status assignedCorruptionStatus;



    assignedOkStatus = okStatus;

    assignedNotFoundStatus = notFoundStatus;

    assignedCorruptionStatus = corruptionStatus;



    EXPECT_EQ(okStatus.ToString(), assignedOkStatus.ToString());

    EXPECT_EQ(notFoundStatus.ToString(), assignedNotFoundStatus.ToString());

    EXPECT_EQ(corruptionStatus.ToString(), assignedCorruptionStatus.ToString());

}



TEST_F(StatusTest_23, MoveAssignmentOperator_CreatesEquivalentStatus_23) {

    Status assignedOkStatus;

    Status assignedNotFoundStatus;

    Status assignedCorruptionStatus;



    assignedOkStatus = std::move(Status::OK());

    assignedNotFoundStatus = std::move(Status::NotFound("Not found message"));

    assignedCorruptionStatus = std::move(Status::Corruption("Corruption message"));



    EXPECT_EQ(okStatus.ToString(), assignedOkStatus.ToString());

    EXPECT_EQ(notFoundStatus.ToString(), assignedNotFoundStatus.ToString());

    EXPECT_EQ(corruptionStatus.ToString(), assignedCorruptionStatus.ToString());

}
