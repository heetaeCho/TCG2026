#include "gtest/gtest.h"
#include "leveldb/status.h"

namespace leveldb {

// Test OK status
TEST(StatusTest_23, OKStatusIsOk_23) {
  Status s = Status::OK();
  EXPECT_TRUE(s.ok());
}

TEST(StatusTest_23, OKStatusIsNotCorruption_23) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsCorruption());
}

TEST(StatusTest_23, OKStatusIsNotNotFound_23) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsNotFound());
}

TEST(StatusTest_23, OKStatusIsNotIOError_23) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsIOError());
}

TEST(StatusTest_23, OKStatusIsNotNotSupported_23) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsNotSupportedError());
}

TEST(StatusTest_23, OKStatusIsNotInvalidArgument_23) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_23, OKStatusToString_23) {
  Status s = Status::OK();
  EXPECT_EQ("OK", s.ToString());
}

// Test NotFound status
TEST(StatusTest_23, NotFoundIsNotOk_23) {
  Status s = Status::NotFound("key not found");
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_23, NotFoundIsNotFound_23) {
  Status s = Status::NotFound("key not found");
  EXPECT_TRUE(s.IsNotFound());
}

TEST(StatusTest_23, NotFoundIsNotCorruption_23) {
  Status s = Status::NotFound("key not found");
  EXPECT_FALSE(s.IsCorruption());
}

TEST(StatusTest_23, NotFoundIsNotIOError_23) {
  Status s = Status::NotFound("key not found");
  EXPECT_FALSE(s.IsIOError());
}

TEST(StatusTest_23, NotFoundIsNotNotSupported_23) {
  Status s = Status::NotFound("key not found");
  EXPECT_FALSE(s.IsNotSupportedError());
}

TEST(StatusTest_23, NotFoundIsNotInvalidArgument_23) {
  Status s = Status::NotFound("key not found");
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_23, NotFoundToStringContainsMessage_23) {
  Status s = Status::NotFound("key not found");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("key not found"));
  EXPECT_NE(std::string::npos, str.find("Not found"));
}

TEST(StatusTest_23, NotFoundWithTwoMessages_23) {
  Status s = Status::NotFound("primary msg", "secondary msg");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("primary msg"));
  EXPECT_NE(std::string::npos, str.find("secondary msg"));
}

// Test Corruption status
TEST(StatusTest_23, CorruptionIsNotOk_23) {
  Status s = Status::Corruption("data corrupted");
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_23, CorruptionIsCorruption_23) {
  Status s = Status::Corruption("data corrupted");
  EXPECT_TRUE(s.IsCorruption());
}

TEST(StatusTest_23, CorruptionIsNotNotFound_23) {
  Status s = Status::Corruption("data corrupted");
  EXPECT_FALSE(s.IsNotFound());
}

TEST(StatusTest_23, CorruptionIsNotIOError_23) {
  Status s = Status::Corruption("data corrupted");
  EXPECT_FALSE(s.IsIOError());
}

TEST(StatusTest_23, CorruptionToStringContainsMessage_23) {
  Status s = Status::Corruption("data corrupted");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("data corrupted"));
  EXPECT_NE(std::string::npos, str.find("Corruption"));
}

TEST(StatusTest_23, CorruptionWithTwoMessages_23) {
  Status s = Status::Corruption("primary", "secondary");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("primary"));
  EXPECT_NE(std::string::npos, str.find("secondary"));
}

// Test NotSupported status
TEST(StatusTest_23, NotSupportedIsNotOk_23) {
  Status s = Status::NotSupported("operation not supported");
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_23, NotSupportedIsNotSupportedError_23) {
  Status s = Status::NotSupported("operation not supported");
  EXPECT_TRUE(s.IsNotSupportedError());
}

TEST(StatusTest_23, NotSupportedIsNotCorruption_23) {
  Status s = Status::NotSupported("operation not supported");
  EXPECT_FALSE(s.IsCorruption());
}

TEST(StatusTest_23, NotSupportedIsNotNotFound_23) {
  Status s = Status::NotSupported("operation not supported");
  EXPECT_FALSE(s.IsNotFound());
}

TEST(StatusTest_23, NotSupportedToStringContainsMessage_23) {
  Status s = Status::NotSupported("not supported op");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("not supported op"));
  EXPECT_NE(std::string::npos, str.find("Not implemented"));
}

// Test InvalidArgument status
TEST(StatusTest_23, InvalidArgumentIsNotOk_23) {
  Status s = Status::InvalidArgument("bad argument");
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_23, InvalidArgumentIsInvalidArgument_23) {
  Status s = Status::InvalidArgument("bad argument");
  EXPECT_TRUE(s.IsInvalidArgument());
}

TEST(StatusTest_23, InvalidArgumentIsNotCorruption_23) {
  Status s = Status::InvalidArgument("bad argument");
  EXPECT_FALSE(s.IsCorruption());
}

TEST(StatusTest_23, InvalidArgumentIsNotNotFound_23) {
  Status s = Status::InvalidArgument("bad argument");
  EXPECT_FALSE(s.IsNotFound());
}

TEST(StatusTest_23, InvalidArgumentIsNotIOError_23) {
  Status s = Status::InvalidArgument("bad argument");
  EXPECT_FALSE(s.IsIOError());
}

TEST(StatusTest_23, InvalidArgumentToStringContainsMessage_23) {
  Status s = Status::InvalidArgument("bad argument");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("bad argument"));
  EXPECT_NE(std::string::npos, str.find("Invalid argument"));
}

// Test IOError status
TEST(StatusTest_23, IOErrorIsNotOk_23) {
  Status s = Status::IOError("disk failure");
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_23, IOErrorIsIOError_23) {
  Status s = Status::IOError("disk failure");
  EXPECT_TRUE(s.IsIOError());
}

TEST(StatusTest_23, IOErrorIsNotCorruption_23) {
  Status s = Status::IOError("disk failure");
  EXPECT_FALSE(s.IsCorruption());
}

TEST(StatusTest_23, IOErrorIsNotNotFound_23) {
  Status s = Status::IOError("disk failure");
  EXPECT_FALSE(s.IsNotFound());
}

TEST(StatusTest_23, IOErrorIsNotNotSupported_23) {
  Status s = Status::IOError("disk failure");
  EXPECT_FALSE(s.IsNotSupportedError());
}

TEST(StatusTest_23, IOErrorIsNotInvalidArgument_23) {
  Status s = Status::IOError("disk failure");
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_23, IOErrorToStringContainsMessage_23) {
  Status s = Status::IOError("disk failure");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("disk failure"));
  EXPECT_NE(std::string::npos, str.find("IO error"));
}

TEST(StatusTest_23, IOErrorWithTwoMessages_23) {
  Status s = Status::IOError("file open", "permission denied");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("file open"));
  EXPECT_NE(std::string::npos, str.find("permission denied"));
}

// Test copy constructor
TEST(StatusTest_23, CopyConstructorOK_23) {
  Status original = Status::OK();
  Status copy(original);
  EXPECT_TRUE(copy.ok());
  EXPECT_TRUE(original.ok());
}

TEST(StatusTest_23, CopyConstructorError_23) {
  Status original = Status::NotFound("missing key");
  Status copy(original);
  EXPECT_TRUE(copy.IsNotFound());
  EXPECT_TRUE(original.IsNotFound());
  EXPECT_EQ(original.ToString(), copy.ToString());
}

// Test copy assignment
TEST(StatusTest_23, CopyAssignmentOK_23) {
  Status s = Status::NotFound("test");
  s = Status::OK();
  EXPECT_TRUE(s.ok());
}

TEST(StatusTest_23, CopyAssignmentError_23) {
  Status s = Status::OK();
  Status error = Status::Corruption("bad data");
  s = error;
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_TRUE(error.IsCorruption());
  EXPECT_EQ(error.ToString(), s.ToString());
}

// Test move constructor
TEST(StatusTest_23, MoveConstructorOK_23) {
  Status original = Status::OK();
  Status moved(std::move(original));
  EXPECT_TRUE(moved.ok());
}

TEST(StatusTest_23, MoveConstructorError_23) {
  Status original = Status::IOError("read error");
  std::string origStr = original.ToString();
  Status moved(std::move(original));
  EXPECT_TRUE(moved.IsIOError());
  EXPECT_EQ(origStr, moved.ToString());
}

// Test move assignment
TEST(StatusTest_23, MoveAssignmentOK_23) {
  Status s = Status::Corruption("test");
  s = Status::OK();
  EXPECT_TRUE(s.ok());
}

TEST(StatusTest_23, MoveAssignmentError_23) {
  Status s = Status::OK();
  s = Status::InvalidArgument("bad arg");
  EXPECT_TRUE(s.IsInvalidArgument());
}

// Test self-assignment
TEST(StatusTest_23, SelfCopyAssignment_23) {
  Status s = Status::NotFound("test");
  s = s;
  EXPECT_TRUE(s.IsNotFound());
}

// Test default constructor
TEST(StatusTest_23, DefaultConstructorIsOK_23) {
  Status s;
  EXPECT_TRUE(s.ok());
}

// Test with empty message
TEST(StatusTest_23, EmptyMessageNotFound_23) {
  Status s = Status::NotFound("");
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_23, EmptyMessageCorruption_23) {
  Status s = Status::Corruption("");
  EXPECT_TRUE(s.IsCorruption());
}

TEST(StatusTest_23, EmptyMessageIOError_23) {
  Status s = Status::IOError("");
  EXPECT_TRUE(s.IsIOError());
}

TEST(StatusTest_23, EmptyMessageNotSupported_23) {
  Status s = Status::NotSupported("");
  EXPECT_TRUE(s.IsNotSupportedError());
}

TEST(StatusTest_23, EmptyMessageInvalidArgument_23) {
  Status s = Status::InvalidArgument("");
  EXPECT_TRUE(s.IsInvalidArgument());
}

// Test with default second message (Slice())
TEST(StatusTest_23, NotFoundDefaultSecondMsg_23) {
  Status s = Status::NotFound("msg");
  EXPECT_TRUE(s.IsNotFound());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("msg"));
}

// Test that each error type is distinct
TEST(StatusTest_23, AllErrorTypesAreDistinct_23) {
  Status notFound = Status::NotFound("a");
  Status corruption = Status::Corruption("b");
  Status notSupported = Status::NotSupported("c");
  Status invalidArg = Status::InvalidArgument("d");
  Status ioError = Status::IOError("e");

  EXPECT_TRUE(notFound.IsNotFound());
  EXPECT_FALSE(notFound.IsCorruption());
  EXPECT_FALSE(notFound.IsNotSupportedError());
  EXPECT_FALSE(notFound.IsInvalidArgument());
  EXPECT_FALSE(notFound.IsIOError());

  EXPECT_FALSE(corruption.IsNotFound());
  EXPECT_TRUE(corruption.IsCorruption());
  EXPECT_FALSE(corruption.IsNotSupportedError());
  EXPECT_FALSE(corruption.IsInvalidArgument());
  EXPECT_FALSE(corruption.IsIOError());

  EXPECT_FALSE(notSupported.IsNotFound());
  EXPECT_FALSE(notSupported.IsCorruption());
  EXPECT_TRUE(notSupported.IsNotSupportedError());
  EXPECT_FALSE(notSupported.IsInvalidArgument());
  EXPECT_FALSE(notSupported.IsIOError());

  EXPECT_FALSE(invalidArg.IsNotFound());
  EXPECT_FALSE(invalidArg.IsCorruption());
  EXPECT_FALSE(invalidArg.IsNotSupportedError());
  EXPECT_TRUE(invalidArg.IsInvalidArgument());
  EXPECT_FALSE(invalidArg.IsIOError());

  EXPECT_FALSE(ioError.IsNotFound());
  EXPECT_FALSE(ioError.IsCorruption());
  EXPECT_FALSE(ioError.IsNotSupportedError());
  EXPECT_FALSE(ioError.IsInvalidArgument());
  EXPECT_TRUE(ioError.IsIOError());
}

}  // namespace leveldb
