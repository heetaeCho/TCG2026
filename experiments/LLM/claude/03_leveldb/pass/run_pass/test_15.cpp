#include "gtest/gtest.h"
#include "leveldb/status.h"

namespace leveldb {

// Test OK status creation and ok() check
TEST(StatusTest_15, OKStatusIsOk_15) {
  Status s = Status::OK();
  EXPECT_TRUE(s.ok());
}

// Test OK status is not any error type
TEST(StatusTest_15, OKStatusIsNotError_15) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

// Test NotFound status
TEST(StatusTest_15, NotFoundStatus_15) {
  Status s = Status::NotFound("key not found");
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

// Test NotFound with two message arguments
TEST(StatusTest_15, NotFoundStatusWithTwoMessages_15) {
  Status s = Status::NotFound("key not found", "details");
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsNotFound());
}

// Test Corruption status
TEST(StatusTest_15, CorruptionStatus_15) {
  Status s = Status::Corruption("data corrupted");
  EXPECT_FALSE(s.ok());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

// Test Corruption with two message arguments
TEST(StatusTest_15, CorruptionStatusWithTwoMessages_15) {
  Status s = Status::Corruption("data corrupted", "block checksum mismatch");
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_FALSE(s.ok());
}

// Test NotSupported status
TEST(StatusTest_15, NotSupportedStatus_15) {
  Status s = Status::NotSupported("operation not supported");
  EXPECT_FALSE(s.ok());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_TRUE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

// Test InvalidArgument status
TEST(StatusTest_15, InvalidArgumentStatus_15) {
  Status s = Status::InvalidArgument("bad argument");
  EXPECT_FALSE(s.ok());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_TRUE(s.IsInvalidArgument());
}

// Test IOError status
TEST(StatusTest_15, IOErrorStatus_15) {
  Status s = Status::IOError("file not accessible");
  EXPECT_FALSE(s.ok());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_TRUE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

// Test IOError with two messages
TEST(StatusTest_15, IOErrorStatusWithTwoMessages_15) {
  Status s = Status::IOError("file error", "permission denied");
  EXPECT_TRUE(s.IsIOError());
  EXPECT_FALSE(s.ok());
}

// Test ToString for OK status
TEST(StatusTest_15, ToStringOK_15) {
  Status s = Status::OK();
  std::string str = s.ToString();
  EXPECT_EQ(str, "OK");
}

// Test ToString for NotFound status contains message
TEST(StatusTest_15, ToStringNotFound_15) {
  Status s = Status::NotFound("my_key");
  std::string str = s.ToString();
  EXPECT_NE(str.find("my_key"), std::string::npos);
  EXPECT_NE(str.find("Not found"), std::string::npos);
}

// Test ToString for Corruption status contains message
TEST(StatusTest_15, ToStringCorruption_15) {
  Status s = Status::Corruption("bad data");
  std::string str = s.ToString();
  EXPECT_NE(str.find("bad data"), std::string::npos);
  EXPECT_NE(str.find("Corruption"), std::string::npos);
}

// Test ToString for IOError status contains message
TEST(StatusTest_15, ToStringIOError_15) {
  Status s = Status::IOError("disk failure");
  std::string str = s.ToString();
  EXPECT_NE(str.find("disk failure"), std::string::npos);
  EXPECT_NE(str.find("IO error"), std::string::npos);
}

// Test ToString for NotSupported status contains message
TEST(StatusTest_15, ToStringNotSupported_15) {
  Status s = Status::NotSupported("feature X");
  std::string str = s.ToString();
  EXPECT_NE(str.find("feature X"), std::string::npos);
  EXPECT_NE(str.find("Not implemented"), std::string::npos);
}

// Test ToString for InvalidArgument status contains message
TEST(StatusTest_15, ToStringInvalidArgument_15) {
  Status s = Status::InvalidArgument("param Y");
  std::string str = s.ToString();
  EXPECT_NE(str.find("param Y"), std::string::npos);
  EXPECT_NE(str.find("Invalid argument"), std::string::npos);
}

// Test ToString with two messages includes both
TEST(StatusTest_15, ToStringWithTwoMessages_15) {
  Status s = Status::NotFound("first", "second");
  std::string str = s.ToString();
  EXPECT_NE(str.find("first"), std::string::npos);
  EXPECT_NE(str.find("second"), std::string::npos);
}

// Test copy constructor preserves status
TEST(StatusTest_15, CopyConstructor_15) {
  Status s1 = Status::NotFound("test");
  Status s2(s1);
  EXPECT_TRUE(s2.IsNotFound());
  EXPECT_FALSE(s2.ok());
  // Original should still be valid
  EXPECT_TRUE(s1.IsNotFound());
}

// Test copy constructor with OK status
TEST(StatusTest_15, CopyConstructorOK_15) {
  Status s1 = Status::OK();
  Status s2(s1);
  EXPECT_TRUE(s2.ok());
  EXPECT_TRUE(s1.ok());
}

// Test copy assignment operator
TEST(StatusTest_15, CopyAssignment_15) {
  Status s1 = Status::IOError("io problem");
  Status s2 = Status::OK();
  EXPECT_TRUE(s2.ok());
  s2 = s1;
  EXPECT_TRUE(s2.IsIOError());
  EXPECT_TRUE(s1.IsIOError());
}

// Test copy assignment from OK to error
TEST(StatusTest_15, CopyAssignmentFromOKToError_15) {
  Status s1 = Status::OK();
  Status s2 = Status::Corruption("corrupt");
  s2 = s1;
  EXPECT_TRUE(s2.ok());
}

// Test move constructor
TEST(StatusTest_15, MoveConstructor_15) {
  Status s1 = Status::InvalidArgument("bad arg");
  Status s2(std::move(s1));
  EXPECT_TRUE(s2.IsInvalidArgument());
}

// Test move assignment operator
TEST(StatusTest_15, MoveAssignment_15) {
  Status s1 = Status::NotSupported("unsupported");
  Status s2 = Status::OK();
  s2 = std::move(s1);
  EXPECT_TRUE(s2.IsNotSupportedError());
}

// Test self-assignment
TEST(StatusTest_15, SelfCopyAssignment_15) {
  Status s = Status::Corruption("self test");
  s = s;
  EXPECT_TRUE(s.IsCorruption());
}

// Test empty message
TEST(StatusTest_15, EmptyMessageNotFound_15) {
  Status s = Status::NotFound("");
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_FALSE(s.ok());
}

// Test empty message for all error types
TEST(StatusTest_15, EmptyMessageAllTypes_15) {
  EXPECT_TRUE(Status::Corruption("").IsCorruption());
  EXPECT_TRUE(Status::NotSupported("").IsNotSupportedError());
  EXPECT_TRUE(Status::InvalidArgument("").IsInvalidArgument());
  EXPECT_TRUE(Status::IOError("").IsIOError());
}

// Test that different error types are distinct
TEST(StatusTest_15, ErrorTypesAreDistinct_15) {
  Status notFound = Status::NotFound("msg");
  Status corruption = Status::Corruption("msg");
  Status ioError = Status::IOError("msg");
  Status notSupported = Status::NotSupported("msg");
  Status invalidArg = Status::InvalidArgument("msg");

  EXPECT_TRUE(notFound.IsNotFound());
  EXPECT_FALSE(notFound.IsCorruption());
  EXPECT_FALSE(notFound.IsIOError());
  EXPECT_FALSE(notFound.IsNotSupportedError());
  EXPECT_FALSE(notFound.IsInvalidArgument());

  EXPECT_TRUE(corruption.IsCorruption());
  EXPECT_FALSE(corruption.IsNotFound());

  EXPECT_TRUE(ioError.IsIOError());
  EXPECT_FALSE(ioError.IsNotFound());

  EXPECT_TRUE(notSupported.IsNotSupportedError());
  EXPECT_FALSE(notSupported.IsCorruption());

  EXPECT_TRUE(invalidArg.IsInvalidArgument());
  EXPECT_FALSE(invalidArg.IsIOError());
}

// Test default constructor creates OK status
TEST(StatusTest_15, DefaultConstructorIsOK_15) {
  Status s;
  EXPECT_TRUE(s.ok());
}

// Test copy of error status preserves message in ToString
TEST(StatusTest_15, CopyPreservesMessage_15) {
  Status s1 = Status::NotFound("unique_message_xyz");
  Status s2 = s1;
  std::string str = s2.ToString();
  EXPECT_NE(str.find("unique_message_xyz"), std::string::npos);
}

// Test move assignment from OK
TEST(StatusTest_15, MoveAssignmentFromOK_15) {
  Status s1 = Status::OK();
  Status s2 = Status::Corruption("test");
  s2 = std::move(s1);
  EXPECT_TRUE(s2.ok());
}

// Test chaining: assign error then OK
TEST(StatusTest_15, AssignErrorThenOK_15) {
  Status s = Status::IOError("err");
  EXPECT_TRUE(s.IsIOError());
  s = Status::OK();
  EXPECT_TRUE(s.ok());
  EXPECT_FALSE(s.IsIOError());
}

// Test chaining: assign OK then error
TEST(StatusTest_15, AssignOKThenError_15) {
  Status s = Status::OK();
  EXPECT_TRUE(s.ok());
  s = Status::InvalidArgument("bad");
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsInvalidArgument());
}

// Test multiple reassignments
TEST(StatusTest_15, MultipleReassignments_15) {
  Status s = Status::OK();
  s = Status::NotFound("a");
  EXPECT_TRUE(s.IsNotFound());
  s = Status::Corruption("b");
  EXPECT_TRUE(s.IsCorruption());
  s = Status::IOError("c");
  EXPECT_TRUE(s.IsIOError());
  s = Status::NotSupported("d");
  EXPECT_TRUE(s.IsNotSupportedError());
  s = Status::InvalidArgument("e");
  EXPECT_TRUE(s.IsInvalidArgument());
  s = Status::OK();
  EXPECT_TRUE(s.ok());
}

}  // namespace leveldb
