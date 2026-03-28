#include "gtest/gtest.h"
#include "leveldb/status.h"
#include "leveldb/slice.h"

namespace leveldb {

// Test default constructor creates OK status
TEST(StatusTest_18, DefaultConstructorIsOK_18) {
  Status s;
  EXPECT_TRUE(s.ok());
}

// Test OK factory method
TEST(StatusTest_18, OKFactoryMethod_18) {
  Status s = Status::OK();
  EXPECT_TRUE(s.ok());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

// Test NotFound factory method
TEST(StatusTest_18, NotFoundStatus_18) {
  Status s = Status::NotFound("key not found");
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

// Test NotFound with two messages
TEST(StatusTest_18, NotFoundWithTwoMessages_18) {
  Status s = Status::NotFound("key not found", "details");
  EXPECT_TRUE(s.IsNotFound());
  std::string str = s.ToString();
  EXPECT_NE(str.find("key not found"), std::string::npos);
  EXPECT_NE(str.find("details"), std::string::npos);
}

// Test Corruption factory method
TEST(StatusTest_18, CorruptionStatus_18) {
  Status s = Status::Corruption("file corrupted");
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

// Test Corruption with two messages
TEST(StatusTest_18, CorruptionWithTwoMessages_18) {
  Status s = Status::Corruption("bad block", "checksum mismatch");
  EXPECT_TRUE(s.IsCorruption());
  std::string str = s.ToString();
  EXPECT_NE(str.find("bad block"), std::string::npos);
  EXPECT_NE(str.find("checksum mismatch"), std::string::npos);
}

// Test NotSupported factory method
TEST(StatusTest_18, NotSupportedStatus_18) {
  Status s = Status::NotSupported("operation not supported");
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

// Test NotSupported with two messages
TEST(StatusTest_18, NotSupportedWithTwoMessages_18) {
  Status s = Status::NotSupported("op", "reason");
  EXPECT_TRUE(s.IsNotSupportedError());
  std::string str = s.ToString();
  EXPECT_NE(str.find("op"), std::string::npos);
  EXPECT_NE(str.find("reason"), std::string::npos);
}

// Test InvalidArgument factory method
TEST(StatusTest_18, InvalidArgumentStatus_18) {
  Status s = Status::InvalidArgument("bad argument");
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsInvalidArgument());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
}

// Test InvalidArgument with two messages
TEST(StatusTest_18, InvalidArgumentWithTwoMessages_18) {
  Status s = Status::InvalidArgument("arg", "out of range");
  EXPECT_TRUE(s.IsInvalidArgument());
  std::string str = s.ToString();
  EXPECT_NE(str.find("arg"), std::string::npos);
  EXPECT_NE(str.find("out of range"), std::string::npos);
}

// Test IOError factory method
TEST(StatusTest_18, IOErrorStatus_18) {
  Status s = Status::IOError("disk failure");
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsIOError());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

// Test IOError with two messages
TEST(StatusTest_18, IOErrorWithTwoMessages_18) {
  Status s = Status::IOError("read error", "/tmp/file");
  EXPECT_TRUE(s.IsIOError());
  std::string str = s.ToString();
  EXPECT_NE(str.find("read error"), std::string::npos);
  EXPECT_NE(str.find("/tmp/file"), std::string::npos);
}

// Test ToString for OK status
TEST(StatusTest_18, ToStringOK_18) {
  Status s = Status::OK();
  EXPECT_EQ(s.ToString(), "OK");
}

// Test ToString for non-OK status contains message
TEST(StatusTest_18, ToStringNotFound_18) {
  Status s = Status::NotFound("missing key");
  std::string str = s.ToString();
  EXPECT_NE(str.find("missing key"), std::string::npos);
  EXPECT_NE(str.find("Not found"), std::string::npos);
}

// Test ToString for Corruption
TEST(StatusTest_18, ToStringCorruption_18) {
  Status s = Status::Corruption("bad data");
  std::string str = s.ToString();
  EXPECT_NE(str.find("Corruption"), std::string::npos);
  EXPECT_NE(str.find("bad data"), std::string::npos);
}

// Test ToString for NotSupported
TEST(StatusTest_18, ToStringNotSupported_18) {
  Status s = Status::NotSupported("unsupported op");
  std::string str = s.ToString();
  EXPECT_NE(str.find("Not implemented"), std::string::npos);
  EXPECT_NE(str.find("unsupported op"), std::string::npos);
}

// Test ToString for InvalidArgument
TEST(StatusTest_18, ToStringInvalidArgument_18) {
  Status s = Status::InvalidArgument("bad arg");
  std::string str = s.ToString();
  EXPECT_NE(str.find("Invalid argument"), std::string::npos);
  EXPECT_NE(str.find("bad arg"), std::string::npos);
}

// Test ToString for IOError
TEST(StatusTest_18, ToStringIOError_18) {
  Status s = Status::IOError("io fail");
  std::string str = s.ToString();
  EXPECT_NE(str.find("IO error"), std::string::npos);
  EXPECT_NE(str.find("io fail"), std::string::npos);
}

// Test copy constructor
TEST(StatusTest_18, CopyConstructor_18) {
  Status original = Status::NotFound("test message");
  Status copy(original);
  EXPECT_TRUE(copy.IsNotFound());
  EXPECT_FALSE(copy.ok());
  EXPECT_EQ(copy.ToString(), original.ToString());
}

// Test copy constructor for OK status
TEST(StatusTest_18, CopyConstructorOK_18) {
  Status original = Status::OK();
  Status copy(original);
  EXPECT_TRUE(copy.ok());
}

// Test copy assignment operator
TEST(StatusTest_18, CopyAssignment_18) {
  Status s1 = Status::IOError("error");
  Status s2;
  s2 = s1;
  EXPECT_TRUE(s2.IsIOError());
  EXPECT_EQ(s1.ToString(), s2.ToString());
}

// Test copy assignment from OK
TEST(StatusTest_18, CopyAssignmentFromOK_18) {
  Status s1 = Status::OK();
  Status s2 = Status::NotFound("something");
  s2 = s1;
  EXPECT_TRUE(s2.ok());
}

// Test move constructor
TEST(StatusTest_18, MoveConstructor_18) {
  Status original = Status::Corruption("corrupted");
  Status moved(std::move(original));
  EXPECT_TRUE(moved.IsCorruption());
}

// Test move assignment operator
TEST(StatusTest_18, MoveAssignment_18) {
  Status s1 = Status::InvalidArgument("bad");
  Status s2;
  s2 = std::move(s1);
  EXPECT_TRUE(s2.IsInvalidArgument());
}

// Test self-assignment (copy)
TEST(StatusTest_18, SelfCopyAssignment_18) {
  Status s = Status::NotFound("key");
  s = s;
  EXPECT_TRUE(s.IsNotFound());
}

// Test empty message
TEST(StatusTest_18, EmptyMessage_18) {
  Status s = Status::NotFound("");
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_FALSE(s.ok());
}

// Test with Slice objects
TEST(StatusTest_18, WithSliceMessages_18) {
  Slice msg1("primary error");
  Slice msg2("secondary detail");
  Status s = Status::IOError(msg1, msg2);
  EXPECT_TRUE(s.IsIOError());
  std::string str = s.ToString();
  EXPECT_NE(str.find("primary error"), std::string::npos);
  EXPECT_NE(str.find("secondary detail"), std::string::npos);
}

// Test with std::string messages
TEST(StatusTest_18, WithStdStringMessages_18) {
  std::string msg1 = "string error";
  std::string msg2 = "string detail";
  Status s = Status::Corruption(msg1, msg2);
  EXPECT_TRUE(s.IsCorruption());
  std::string str = s.ToString();
  EXPECT_NE(str.find("string error"), std::string::npos);
  EXPECT_NE(str.find("string detail"), std::string::npos);
}

// Test that different error types don't interfere
TEST(StatusTest_18, DifferentErrorTypesAreDistinct_18) {
  Status notFound = Status::NotFound("msg");
  Status corruption = Status::Corruption("msg");
  Status notSupported = Status::NotSupported("msg");
  Status invalidArg = Status::InvalidArgument("msg");
  Status ioError = Status::IOError("msg");

  EXPECT_TRUE(notFound.IsNotFound());
  EXPECT_FALSE(notFound.IsCorruption());
  EXPECT_FALSE(notFound.IsNotSupportedError());
  EXPECT_FALSE(notFound.IsInvalidArgument());
  EXPECT_FALSE(notFound.IsIOError());

  EXPECT_TRUE(corruption.IsCorruption());
  EXPECT_FALSE(corruption.IsNotFound());

  EXPECT_TRUE(notSupported.IsNotSupportedError());
  EXPECT_FALSE(notSupported.IsNotFound());

  EXPECT_TRUE(invalidArg.IsInvalidArgument());
  EXPECT_FALSE(invalidArg.IsNotFound());

  EXPECT_TRUE(ioError.IsIOError());
  EXPECT_FALSE(ioError.IsNotFound());
}

// Test overwriting status with assignment
TEST(StatusTest_18, OverwriteStatusWithAssignment_18) {
  Status s = Status::NotFound("first");
  EXPECT_TRUE(s.IsNotFound());
  s = Status::IOError("second");
  EXPECT_TRUE(s.IsIOError());
  EXPECT_FALSE(s.IsNotFound());
  s = Status::OK();
  EXPECT_TRUE(s.ok());
}

// Test long messages
TEST(StatusTest_18, LongMessage_18) {
  std::string longMsg(10000, 'x');
  Status s = Status::NotFound(longMsg);
  EXPECT_TRUE(s.IsNotFound());
  std::string str = s.ToString();
  EXPECT_NE(str.find(longMsg), std::string::npos);
}

// Test default second argument (empty Slice)
TEST(StatusTest_18, DefaultSecondArgument_18) {
  Status s1 = Status::NotFound("msg");
  Status s2 = Status::NotFound("msg", Slice());
  // Both should be NotFound with same primary message
  EXPECT_TRUE(s1.IsNotFound());
  EXPECT_TRUE(s2.IsNotFound());
}

}  // namespace leveldb
