#include "gtest/gtest.h"
#include "leveldb/status.h"

namespace leveldb {

// Test OK status
TEST(StatusTest_22, OKStatusIsOk_22) {
  Status status = Status::OK();
  EXPECT_TRUE(status.ok());
}

TEST(StatusTest_22, OKStatusIsNotNotFound_22) {
  Status status = Status::OK();
  EXPECT_FALSE(status.IsNotFound());
}

TEST(StatusTest_22, OKStatusIsNotCorruption_22) {
  Status status = Status::OK();
  EXPECT_FALSE(status.IsCorruption());
}

TEST(StatusTest_22, OKStatusIsNotIOError_22) {
  Status status = Status::OK();
  EXPECT_FALSE(status.IsIOError());
}

TEST(StatusTest_22, OKStatusIsNotNotSupported_22) {
  Status status = Status::OK();
  EXPECT_FALSE(status.IsNotSupportedError());
}

TEST(StatusTest_22, OKStatusIsNotInvalidArgument_22) {
  Status status = Status::OK();
  EXPECT_FALSE(status.IsInvalidArgument());
}

TEST(StatusTest_22, OKStatusToString_22) {
  Status status = Status::OK();
  EXPECT_EQ("OK", status.ToString());
}

// Test NotFound status
TEST(StatusTest_22, NotFoundStatusIsNotOk_22) {
  Status status = Status::NotFound("key not found");
  EXPECT_FALSE(status.ok());
}

TEST(StatusTest_22, NotFoundStatusIsNotFound_22) {
  Status status = Status::NotFound("key not found");
  EXPECT_TRUE(status.IsNotFound());
}

TEST(StatusTest_22, NotFoundStatusIsNotCorruption_22) {
  Status status = Status::NotFound("key not found");
  EXPECT_FALSE(status.IsCorruption());
}

TEST(StatusTest_22, NotFoundStatusIsNotIOError_22) {
  Status status = Status::NotFound("key not found");
  EXPECT_FALSE(status.IsIOError());
}

TEST(StatusTest_22, NotFoundStatusIsNotNotSupported_22) {
  Status status = Status::NotFound("key not found");
  EXPECT_FALSE(status.IsNotSupportedError());
}

TEST(StatusTest_22, NotFoundStatusIsNotInvalidArgument_22) {
  Status status = Status::NotFound("key not found");
  EXPECT_FALSE(status.IsInvalidArgument());
}

TEST(StatusTest_22, NotFoundStatusToStringContainsMessage_22) {
  Status status = Status::NotFound("key not found");
  std::string str = status.ToString();
  EXPECT_NE(std::string::npos, str.find("Not found"));
  EXPECT_NE(std::string::npos, str.find("key not found"));
}

TEST(StatusTest_22, NotFoundWithTwoMessages_22) {
  Status status = Status::NotFound("primary msg", "secondary msg");
  EXPECT_TRUE(status.IsNotFound());
  std::string str = status.ToString();
  EXPECT_NE(std::string::npos, str.find("primary msg"));
  EXPECT_NE(std::string::npos, str.find("secondary msg"));
}

// Test Corruption status
TEST(StatusTest_22, CorruptionStatusIsNotOk_22) {
  Status status = Status::Corruption("data corrupted");
  EXPECT_FALSE(status.ok());
}

TEST(StatusTest_22, CorruptionStatusIsCorruption_22) {
  Status status = Status::Corruption("data corrupted");
  EXPECT_TRUE(status.IsCorruption());
}

TEST(StatusTest_22, CorruptionStatusIsNotNotFound_22) {
  Status status = Status::Corruption("data corrupted");
  EXPECT_FALSE(status.IsNotFound());
}

TEST(StatusTest_22, CorruptionStatusToStringContainsMessage_22) {
  Status status = Status::Corruption("data corrupted");
  std::string str = status.ToString();
  EXPECT_NE(std::string::npos, str.find("Corruption"));
  EXPECT_NE(std::string::npos, str.find("data corrupted"));
}

TEST(StatusTest_22, CorruptionWithTwoMessages_22) {
  Status status = Status::Corruption("primary", "secondary");
  EXPECT_TRUE(status.IsCorruption());
  std::string str = status.ToString();
  EXPECT_NE(std::string::npos, str.find("primary"));
  EXPECT_NE(std::string::npos, str.find("secondary"));
}

// Test NotSupported status
TEST(StatusTest_22, NotSupportedStatusIsNotOk_22) {
  Status status = Status::NotSupported("feature not supported");
  EXPECT_FALSE(status.ok());
}

TEST(StatusTest_22, NotSupportedStatusIsNotSupported_22) {
  Status status = Status::NotSupported("feature not supported");
  EXPECT_TRUE(status.IsNotSupportedError());
}

TEST(StatusTest_22, NotSupportedStatusIsNotOtherErrors_22) {
  Status status = Status::NotSupported("feature not supported");
  EXPECT_FALSE(status.IsNotFound());
  EXPECT_FALSE(status.IsCorruption());
  EXPECT_FALSE(status.IsIOError());
  EXPECT_FALSE(status.IsInvalidArgument());
}

TEST(StatusTest_22, NotSupportedStatusToStringContainsMessage_22) {
  Status status = Status::NotSupported("feature not supported");
  std::string str = status.ToString();
  EXPECT_NE(std::string::npos, str.find("Not implemented"));
  EXPECT_NE(std::string::npos, str.find("feature not supported"));
}

// Test InvalidArgument status
TEST(StatusTest_22, InvalidArgumentStatusIsNotOk_22) {
  Status status = Status::InvalidArgument("bad argument");
  EXPECT_FALSE(status.ok());
}

TEST(StatusTest_22, InvalidArgumentStatusIsInvalidArgument_22) {
  Status status = Status::InvalidArgument("bad argument");
  EXPECT_TRUE(status.IsInvalidArgument());
}

TEST(StatusTest_22, InvalidArgumentStatusIsNotOtherErrors_22) {
  Status status = Status::InvalidArgument("bad argument");
  EXPECT_FALSE(status.IsNotFound());
  EXPECT_FALSE(status.IsCorruption());
  EXPECT_FALSE(status.IsIOError());
  EXPECT_FALSE(status.IsNotSupportedError());
}

TEST(StatusTest_22, InvalidArgumentStatusToStringContainsMessage_22) {
  Status status = Status::InvalidArgument("bad argument");
  std::string str = status.ToString();
  EXPECT_NE(std::string::npos, str.find("Invalid argument"));
  EXPECT_NE(std::string::npos, str.find("bad argument"));
}

// Test IOError status
TEST(StatusTest_22, IOErrorStatusIsNotOk_22) {
  Status status = Status::IOError("disk error");
  EXPECT_FALSE(status.ok());
}

TEST(StatusTest_22, IOErrorStatusIsIOError_22) {
  Status status = Status::IOError("disk error");
  EXPECT_TRUE(status.IsIOError());
}

TEST(StatusTest_22, IOErrorStatusIsNotOtherErrors_22) {
  Status status = Status::IOError("disk error");
  EXPECT_FALSE(status.IsNotFound());
  EXPECT_FALSE(status.IsCorruption());
  EXPECT_FALSE(status.IsNotSupportedError());
  EXPECT_FALSE(status.IsInvalidArgument());
}

TEST(StatusTest_22, IOErrorStatusToStringContainsMessage_22) {
  Status status = Status::IOError("disk error");
  std::string str = status.ToString();
  EXPECT_NE(std::string::npos, str.find("IO error"));
  EXPECT_NE(std::string::npos, str.find("disk error"));
}

TEST(StatusTest_22, IOErrorWithTwoMessages_22) {
  Status status = Status::IOError("read failed", "errno=5");
  EXPECT_TRUE(status.IsIOError());
  std::string str = status.ToString();
  EXPECT_NE(std::string::npos, str.find("read failed"));
  EXPECT_NE(std::string::npos, str.find("errno=5"));
}

// Test copy constructor
TEST(StatusTest_22, CopyConstructorOK_22) {
  Status original = Status::OK();
  Status copy(original);
  EXPECT_TRUE(copy.ok());
  EXPECT_TRUE(original.ok());
}

TEST(StatusTest_22, CopyConstructorError_22) {
  Status original = Status::NotFound("missing");
  Status copy(original);
  EXPECT_TRUE(copy.IsNotFound());
  EXPECT_TRUE(original.IsNotFound());
  EXPECT_EQ(original.ToString(), copy.ToString());
}

// Test copy assignment
TEST(StatusTest_22, CopyAssignmentOK_22) {
  Status status = Status::NotFound("missing");
  status = Status::OK();
  EXPECT_TRUE(status.ok());
}

TEST(StatusTest_22, CopyAssignmentError_22) {
  Status status = Status::OK();
  Status error = Status::Corruption("bad data");
  status = error;
  EXPECT_TRUE(status.IsCorruption());
  EXPECT_TRUE(error.IsCorruption());
}

// Test move constructor
TEST(StatusTest_22, MoveConstructorOK_22) {
  Status original = Status::OK();
  Status moved(std::move(original));
  EXPECT_TRUE(moved.ok());
}

TEST(StatusTest_22, MoveConstructorError_22) {
  Status original = Status::IOError("disk failure");
  std::string originalStr = original.ToString();
  Status moved(std::move(original));
  EXPECT_TRUE(moved.IsIOError());
  EXPECT_EQ(originalStr, moved.ToString());
}

// Test move assignment
TEST(StatusTest_22, MoveAssignmentOK_22) {
  Status status = Status::NotFound("key");
  status = Status::OK();
  EXPECT_TRUE(status.ok());
}

TEST(StatusTest_22, MoveAssignmentError_22) {
  Status status = Status::OK();
  status = Status::InvalidArgument("bad arg");
  EXPECT_TRUE(status.IsInvalidArgument());
}

// Test self assignment
TEST(StatusTest_22, SelfCopyAssignment_22) {
  Status status = Status::NotFound("test");
  const Status& ref = status;
  status = ref;
  EXPECT_TRUE(status.IsNotFound());
}

// Test with empty messages
TEST(StatusTest_22, NotFoundWithEmptyMessage_22) {
  Status status = Status::NotFound("");
  EXPECT_TRUE(status.IsNotFound());
  EXPECT_FALSE(status.ok());
}

TEST(StatusTest_22, CorruptionWithEmptyMessage_22) {
  Status status = Status::Corruption("");
  EXPECT_TRUE(status.IsCorruption());
}

TEST(StatusTest_22, IOErrorWithEmptyMessage_22) {
  Status status = Status::IOError("");
  EXPECT_TRUE(status.IsIOError());
}

TEST(StatusTest_22, NotSupportedWithEmptyMessage_22) {
  Status status = Status::NotSupported("");
  EXPECT_TRUE(status.IsNotSupportedError());
}

TEST(StatusTest_22, InvalidArgumentWithEmptyMessage_22) {
  Status status = Status::InvalidArgument("");
  EXPECT_TRUE(status.IsInvalidArgument());
}

// Test default constructor
TEST(StatusTest_22, DefaultConstructorIsOk_22) {
  Status status;
  EXPECT_TRUE(status.ok());
}

// Test chained assignments
TEST(StatusTest_22, ChainedStatusTransitions_22) {
  Status status = Status::OK();
  EXPECT_TRUE(status.ok());

  status = Status::NotFound("a");
  EXPECT_TRUE(status.IsNotFound());

  status = Status::Corruption("b");
  EXPECT_TRUE(status.IsCorruption());

  status = Status::IOError("c");
  EXPECT_TRUE(status.IsIOError());

  status = Status::NotSupported("d");
  EXPECT_TRUE(status.IsNotSupportedError());

  status = Status::InvalidArgument("e");
  EXPECT_TRUE(status.IsInvalidArgument());

  status = Status::OK();
  EXPECT_TRUE(status.ok());
}

// Test with long messages
TEST(StatusTest_22, LongErrorMessage_22) {
  std::string longMsg(10000, 'x');
  Status status = Status::NotFound(longMsg);
  EXPECT_TRUE(status.IsNotFound());
  std::string str = status.ToString();
  EXPECT_NE(std::string::npos, str.find(longMsg));
}

// Test that different error types produce different ToString output
TEST(StatusTest_22, DifferentErrorTypesHaveDifferentToString_22) {
  Status notFound = Status::NotFound("msg");
  Status corruption = Status::Corruption("msg");
  Status ioError = Status::IOError("msg");
  Status notSupported = Status::NotSupported("msg");
  Status invalidArg = Status::InvalidArgument("msg");

  // All should be different from each other (different prefixes)
  EXPECT_NE(notFound.ToString(), corruption.ToString());
  EXPECT_NE(notFound.ToString(), ioError.ToString());
  EXPECT_NE(notFound.ToString(), notSupported.ToString());
  EXPECT_NE(notFound.ToString(), invalidArg.ToString());
  EXPECT_NE(corruption.ToString(), ioError.ToString());
}

}  // namespace leveldb
