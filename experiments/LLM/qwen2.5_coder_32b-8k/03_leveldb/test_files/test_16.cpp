#include <gtest/gtest.h>

#include "leveldb/status.h"

#include "leveldb/slice.h"



using namespace leveldb;



TEST(StatusTest_16, OKStatus_ReturnsTrue_16) {

    Status status = Status::OK();

    EXPECT_TRUE(status.ok());

}



TEST(StatusTest_16, NotFoundStatus_ReturnsFalseForOk_16) {

    Status status = Status::NotFound(Slice("Not found error"));

    EXPECT_FALSE(status.ok());

}



TEST(StatusTest_16, NotFoundStatus_ReturnsTrueForIsNotFound_16) {

    Status status = Status::NotFound(Slice("Not found error"));

    EXPECT_TRUE(status.IsNotFound());

}



TEST(StatusTest_16, CorruptionStatus_ReturnsFalseForOk_16) {

    Status status = Status::Corruption(Slice("Corruption error"));

    EXPECT_FALSE(status.ok());

}



TEST(StatusTest_16, CorruptionStatus_ReturnsTrueForIsCorruption_16) {

    Status status = Status::Corruption(Slice("Corruption error"));

    EXPECT_TRUE(status.IsCorruption());

}



TEST(StatusTest_16, NotSupportedStatus_ReturnsFalseForOk_16) {

    Status status = Status::NotSupported(Slice("Not supported error"));

    EXPECT_FALSE(status.ok());

}



TEST(StatusTest_16, NotSupportedStatus_ReturnsTrueForIsNotSupportedError_16) {

    Status status = Status::NotSupported(Slice("Not supported error"));

    EXPECT_TRUE(status.IsNotSupportedError());

}



TEST(StatusTest_16, InvalidArgumentStatus_ReturnsFalseForOk_16) {

    Status status = Status::InvalidArgument(Slice("Invalid argument error"));

    EXPECT_FALSE(status.ok());

}



TEST(StatusTest_16, InvalidArgumentStatus_ReturnsTrueForIsInvalidArgument_16) {

    Status status = Status::InvalidArgument(Slice("Invalid argument error"));

    EXPECT_TRUE(status.IsInvalidArgument());

}



TEST(StatusTest_16, IOErrorStatus_ReturnsFalseForOk_16) {

    Status status = Status::IOError(Slice("IO error"));

    EXPECT_FALSE(status.ok());

}



TEST(StatusTest_16, IOErrorStatus_ReturnsTrueForIsIOError_16) {

    Status status = Status::IOError(Slice("IO error"));

    EXPECT_TRUE(status.IsIOError());

}



TEST(StatusTest_16, ToString_ReturnsCorrectStringForOK_16) {

    Status status = Status::OK();

    EXPECT_EQ(status.ToString(), "OK");

}



TEST(StatusTest_16, ToString_ReturnsCorrectStringForNotFound_16) {

    Status status = Status::NotFound(Slice("Not found error"));

    EXPECT_EQ(status.ToString(), "NotFound: Not found error");

}



TEST(StatusTest_16, ToString_ReturnsCorrectStringForCorruption_16) {

    Status status = Status::Corruption(Slice("Corruption error"));

    EXPECT_EQ(status.ToString(), "Corruption: Corruption error");

}



TEST(StatusTest_16, ToString_ReturnsCorrectStringForNotSupported_16) {

    Status status = Status::NotSupported(Slice("Not supported error"));

    EXPECT_EQ(status.ToString(), "NotSupported: Not supported error");

}



TEST(StatusTest_16, ToString_ReturnsCorrectStringForInvalidArgument_16) {

    Status status = Status::InvalidArgument(Slice("Invalid argument error"));

    EXPECT_EQ(status.ToString(), "Invalid argument: Invalid argument error");

}



TEST(StatusTest_16, ToString_ReturnsCorrectStringForIOError_16) {

    Status status = Status::IOError(Slice("IO error"));

    EXPECT_EQ(status.ToString(), "IO error: IO error");

}



TEST(StatusTest_16, CopyConstructor_DoesNotAffectOriginalStatus_16) {

    Status original = Status::NotFound(Slice("Not found error"));

    Status copy(original);

    EXPECT_EQ(copy.ToString(), "NotFound: Not found error");

    EXPECT_EQ(original.ToString(), "NotFound: Not found error");

}



TEST(StatusTest_16, AssignmentOperator_DoesNotAffectOriginalStatus_16) {

    Status original = Status::NotFound(Slice("Not found error"));

    Status assigned;

    assigned = original;

    EXPECT_EQ(assigned.ToString(), "NotFound: Not found error");

    EXPECT_EQ(original.ToString(), "NotFound: Not found error");

}



TEST(StatusTest_16, MoveConstructor_DoesTransferStateCorrectly_16) {

    Status original = Status::NotFound(Slice("Not found error"));

    Status moved(std::move(original));

    EXPECT_EQ(moved.ToString(), "NotFound: Not found error");

    // The state of the original status after move is undefined, so we don't check it

}



TEST(StatusTest_16, MoveAssignmentOperator_DoesTransferStateCorrectly_16) {

    Status original = Status::NotFound(Slice("Not found error"));

    Status moved;

    moved = std::move(original);

    EXPECT_EQ(moved.ToString(), "NotFound: Not found error");

    // The state of the original status after move is undefined, so we don't check it

}
