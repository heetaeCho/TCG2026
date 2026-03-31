#include "gtest/gtest.h"
#include "leveldb/status.h"
#include "leveldb/slice.h"

namespace leveldb {

// Test OK status creation and properties
TEST(StatusTest_20, OKStatusIsOk_20) {
  Status s = Status::OK();
  EXPECT_TRUE(s.ok());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_20, OKStatusToString_20) {
  Status s = Status::OK();
  EXPECT_EQ("OK", s.ToString());
}

// Test NotFound status
TEST(StatusTest_20, NotFoundStatus_20) {
  Status s = Status::NotFound("key missing");
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_20, NotFoundStatusWithTwoMessages_20) {
  Status s = Status::NotFound("key missing", "details here");
  EXPECT_TRUE(s.IsNotFound());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("key missing"));
  EXPECT_NE(std::string::npos, str.find("details here"));
}

TEST(StatusTest_20, NotFoundToStringContainsMessage_20) {
  Status s = Status::NotFound("some key");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Not found"));
  EXPECT_NE(std::string::npos, str.find("some key"));
}

// Test Corruption status
TEST(StatusTest_20, CorruptionStatus_20) {
  Status s = Status::Corruption("bad data");
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_20, CorruptionToStringContainsMessage_20) {
  Status s = Status::Corruption("block checksum mismatch");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Corruption"));
  EXPECT_NE(std::string::npos, str.find("block checksum mismatch"));
}

TEST(StatusTest_20, CorruptionWithTwoMessages_20) {
  Status s = Status::Corruption("file error", "extra info");
  EXPECT_TRUE(s.IsCorruption());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("file error"));
  EXPECT_NE(std::string::npos, str.find("extra info"));
}

// Test NotSupported status
TEST(StatusTest_20, NotSupportedStatus_20) {
  Status s = Status::NotSupported("feature X");
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_20, NotSupportedToStringContainsMessage_20) {
  Status s = Status::NotSupported("not implemented");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Not implemented"));
  EXPECT_NE(std::string::npos, str.find("not implemented"));
}

// Test InvalidArgument status
TEST(StatusTest_20, InvalidArgumentStatus_20) {
  Status s = Status::InvalidArgument("bad arg");
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsInvalidArgument());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
}

TEST(StatusTest_20, InvalidArgumentToStringContainsMessage_20) {
  Status s = Status::InvalidArgument("null pointer");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Invalid argument"));
  EXPECT_NE(std::string::npos, str.find("null pointer"));
}

// Test IOError status
TEST(StatusTest_20, IOErrorStatus_20) {
  Status s = Status::IOError("disk failure");
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsIOError());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_20, IOErrorToStringContainsMessage_20) {
  Status s = Status::IOError("read error");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("IO error"));
  EXPECT_NE(std::string::npos, str.find("read error"));
}

TEST(StatusTest_20, IOErrorWithTwoMessages_20) {
  Status s = Status::IOError("write failed", "/tmp/file.db");
  EXPECT_TRUE(s.IsIOError());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("write failed"));
  EXPECT_NE(std::string::npos, str.find("/tmp/file.db"));
}

// Test copy constructor
TEST(StatusTest_20, CopyConstructorOK_20) {
  Status original = Status::OK();
  Status copy(original);
  EXPECT_TRUE(copy.ok());
  EXPECT_TRUE(original.ok());
}

TEST(StatusTest_20, CopyConstructorError_20) {
  Status original = Status::NotFound("missing key");
  Status copy(original);
  EXPECT_TRUE(copy.IsNotFound());
  EXPECT_TRUE(original.IsNotFound());
  EXPECT_EQ(original.ToString(), copy.ToString());
}

// Test move constructor
TEST(StatusTest_20, MoveConstructor_20) {
  Status original = Status::IOError("disk error");
  Status moved(std::move(original));
  EXPECT_TRUE(moved.IsIOError());
  std::string str = moved.ToString();
  EXPECT_NE(std::string::npos, str.find("disk error"));
}

// Test copy assignment operator
TEST(StatusTest_20, CopyAssignmentOperator_20) {
  Status s1 = Status::OK();
  Status s2 = Status::NotFound("key");
  s1 = s2;
  EXPECT_TRUE(s1.IsNotFound());
  EXPECT_TRUE(s2.IsNotFound());
}

TEST(StatusTest_20, CopyAssignmentFromOKToError_20) {
  Status s1 = Status::Corruption("bad");
  Status s2 = Status::OK();
  s1 = s2;
  EXPECT_TRUE(s1.ok());
}

// Test move assignment operator
TEST(StatusTest_20, MoveAssignmentOperator_20) {
  Status s1 = Status::OK();
  Status s2 = Status::Corruption("data corrupt");
  s1 = std::move(s2);
  EXPECT_TRUE(s1.IsCorruption());
  std::string str = s1.ToString();
  EXPECT_NE(std::string::npos, str.find("data corrupt"));
}

// Test self-assignment
TEST(StatusTest_20, SelfCopyAssignment_20) {
  Status s = Status::NotFound("self");
  s = s;
  EXPECT_TRUE(s.IsNotFound());
}

// Test with empty message
TEST(StatusTest_20, EmptyMessageNotFound_20) {
  Status s = Status::NotFound("");
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_20, EmptyMessageIOError_20) {
  Status s = Status::IOError("");
  EXPECT_TRUE(s.IsIOError());
  EXPECT_FALSE(s.ok());
}

// Test with std::string messages
TEST(StatusTest_20, StringMessageNotFound_20) {
  std::string msg = "key not found in database";
  Status s = Status::NotFound(msg);
  EXPECT_TRUE(s.IsNotFound());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find(msg));
}

// Test that different error types are mutually exclusive
TEST(StatusTest_20, ErrorTypesMutuallyExclusive_20) {
  Status notFound = Status::NotFound("a");
  Status corruption = Status::Corruption("b");
  Status ioError = Status::IOError("c");
  Status notSupported = Status::NotSupported("d");
  Status invalidArg = Status::InvalidArgument("e");

  // NotFound
  EXPECT_TRUE(notFound.IsNotFound());
  EXPECT_FALSE(notFound.IsCorruption());
  EXPECT_FALSE(notFound.IsIOError());
  EXPECT_FALSE(notFound.IsNotSupportedError());
  EXPECT_FALSE(notFound.IsInvalidArgument());

  // Corruption
  EXPECT_FALSE(corruption.IsNotFound());
  EXPECT_TRUE(corruption.IsCorruption());
  EXPECT_FALSE(corruption.IsIOError());
  EXPECT_FALSE(corruption.IsNotSupportedError());
  EXPECT_FALSE(corruption.IsInvalidArgument());

  // IOError
  EXPECT_FALSE(ioError.IsNotFound());
  EXPECT_FALSE(ioError.IsCorruption());
  EXPECT_TRUE(ioError.IsIOError());
  EXPECT_FALSE(ioError.IsNotSupportedError());
  EXPECT_FALSE(ioError.IsInvalidArgument());

  // NotSupported
  EXPECT_FALSE(notSupported.IsNotFound());
  EXPECT_FALSE(notSupported.IsCorruption());
  EXPECT_FALSE(notSupported.IsIOError());
  EXPECT_TRUE(notSupported.IsNotSupportedError());
  EXPECT_FALSE(notSupported.IsInvalidArgument());

  // InvalidArgument
  EXPECT_FALSE(invalidArg.IsNotFound());
  EXPECT_FALSE(invalidArg.IsCorruption());
  EXPECT_FALSE(invalidArg.IsIOError());
  EXPECT_FALSE(invalidArg.IsNotSupportedError());
  EXPECT_TRUE(invalidArg.IsInvalidArgument());
}

// Test default constructor
TEST(StatusTest_20, DefaultConstructorIsOK_20) {
  Status s;
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("OK", s.ToString());
}

// Test that copies are independent
TEST(StatusTest_20, CopiesAreIndependent_20) {
  Status s1 = Status::IOError("original error");
  Status s2 = s1;
  s1 = Status::OK();
  EXPECT_TRUE(s1.ok());
  EXPECT_TRUE(s2.IsIOError());
  EXPECT_NE(std::string::npos, s2.ToString().find("original error"));
}

// Test long messages
TEST(StatusTest_20, LongMessage_20) {
  std::string longMsg(1000, 'x');
  Status s = Status::NotFound(longMsg);
  EXPECT_TRUE(s.IsNotFound());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find(longMsg));
}

// Test reassignment from error to different error
TEST(StatusTest_20, ReassignDifferentError_20) {
  Status s = Status::NotFound("first");
  s = Status::Corruption("second");
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_NE(std::string::npos, s.ToString().find("second"));
}

// Test with Slice arguments
TEST(StatusTest_20, SliceArguments_20) {
  Slice msg1("slice message");
  Slice msg2("extra detail");
  Status s = Status::IOError(msg1, msg2);
  EXPECT_TRUE(s.IsIOError());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("slice message"));
  EXPECT_NE(std::string::npos, str.find("extra detail"));
}

}  // namespace leveldb
