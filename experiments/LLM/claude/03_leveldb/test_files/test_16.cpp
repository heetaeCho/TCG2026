#include "gtest/gtest.h"
#include "leveldb/status.h"
#include "leveldb/slice.h"

namespace leveldb {

// Test OK status
TEST(StatusTest_16, OKStatusIsOk_16) {
  Status s = Status::OK();
  EXPECT_TRUE(s.ok());
}

TEST(StatusTest_16, OKStatusIsNotError_16) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_16, OKStatusToString_16) {
  Status s = Status::OK();
  EXPECT_EQ("OK", s.ToString());
}

// Test NotFound status
TEST(StatusTest_16, NotFoundStatus_16) {
  Status s = Status::NotFound("key missing");
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_FALSE(s.ok());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_16, NotFoundStatusToStringContainsMessage_16) {
  Status s = Status::NotFound("key missing");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("key missing"));
  EXPECT_NE(std::string::npos, str.find("Not found"));
}

TEST(StatusTest_16, NotFoundWithTwoMessages_16) {
  Status s = Status::NotFound("primary msg", "secondary msg");
  EXPECT_TRUE(s.IsNotFound());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("primary msg"));
  EXPECT_NE(std::string::npos, str.find("secondary msg"));
}

// Test Corruption status
TEST(StatusTest_16, CorruptionStatus_16) {
  Status s = Status::Corruption("data corrupted");
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_FALSE(s.ok());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_16, CorruptionStatusToString_16) {
  Status s = Status::Corruption("data corrupted");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Corruption"));
  EXPECT_NE(std::string::npos, str.find("data corrupted"));
}

TEST(StatusTest_16, CorruptionWithTwoMessages_16) {
  Status s = Status::Corruption("msg1", "msg2");
  EXPECT_TRUE(s.IsCorruption());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("msg1"));
  EXPECT_NE(std::string::npos, str.find("msg2"));
}

// Test NotSupported status
TEST(StatusTest_16, NotSupportedStatus_16) {
  Status s = Status::NotSupported("feature X");
  EXPECT_TRUE(s.IsNotSupportedError());
  EXPECT_FALSE(s.ok());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_16, NotSupportedStatusToString_16) {
  Status s = Status::NotSupported("feature X");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Not implemented"));
  EXPECT_NE(std::string::npos, str.find("feature X"));
}

TEST(StatusTest_16, NotSupportedWithTwoMessages_16) {
  Status s = Status::NotSupported("msg1", "msg2");
  EXPECT_TRUE(s.IsNotSupportedError());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("msg1"));
  EXPECT_NE(std::string::npos, str.find("msg2"));
}

// Test InvalidArgument status
TEST(StatusTest_16, InvalidArgumentStatus_16) {
  Status s = Status::InvalidArgument("bad arg");
  EXPECT_TRUE(s.IsInvalidArgument());
  EXPECT_FALSE(s.ok());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
}

TEST(StatusTest_16, InvalidArgumentStatusToString_16) {
  Status s = Status::InvalidArgument("bad arg");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Invalid argument"));
  EXPECT_NE(std::string::npos, str.find("bad arg"));
}

TEST(StatusTest_16, InvalidArgumentWithTwoMessages_16) {
  Status s = Status::InvalidArgument("msg1", "msg2");
  EXPECT_TRUE(s.IsInvalidArgument());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("msg1"));
  EXPECT_NE(std::string::npos, str.find("msg2"));
}

// Test IOError status
TEST(StatusTest_16, IOErrorStatus_16) {
  Status s = Status::IOError("disk failure");
  EXPECT_TRUE(s.IsIOError());
  EXPECT_FALSE(s.ok());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_16, IOErrorStatusToString_16) {
  Status s = Status::IOError("disk failure");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("IO error"));
  EXPECT_NE(std::string::npos, str.find("disk failure"));
}

TEST(StatusTest_16, IOErrorWithTwoMessages_16) {
  Status s = Status::IOError("msg1", "msg2");
  EXPECT_TRUE(s.IsIOError());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("msg1"));
  EXPECT_NE(std::string::npos, str.find("msg2"));
}

// Test copy constructor
TEST(StatusTest_16, CopyConstructorOK_16) {
  Status s1 = Status::OK();
  Status s2(s1);
  EXPECT_TRUE(s2.ok());
}

TEST(StatusTest_16, CopyConstructorError_16) {
  Status s1 = Status::NotFound("missing key");
  Status s2(s1);
  EXPECT_TRUE(s2.IsNotFound());
  EXPECT_EQ(s1.ToString(), s2.ToString());
}

// Test move constructor
TEST(StatusTest_16, MoveConstructor_16) {
  Status s1 = Status::IOError("disk error");
  Status s2(std::move(s1));
  EXPECT_TRUE(s2.IsIOError());
}

// Test copy assignment
TEST(StatusTest_16, CopyAssignmentOK_16) {
  Status s1 = Status::OK();
  Status s2 = Status::NotFound("something");
  s2 = s1;
  EXPECT_TRUE(s2.ok());
}

TEST(StatusTest_16, CopyAssignmentError_16) {
  Status s1 = Status::Corruption("bad data");
  Status s2 = Status::OK();
  s2 = s1;
  EXPECT_TRUE(s2.IsCorruption());
  EXPECT_EQ(s1.ToString(), s2.ToString());
}

// Test move assignment
TEST(StatusTest_16, MoveAssignment_16) {
  Status s1 = Status::InvalidArgument("wrong");
  Status s2 = Status::OK();
  s2 = std::move(s1);
  EXPECT_TRUE(s2.IsInvalidArgument());
}

// Test self-assignment
TEST(StatusTest_16, SelfCopyAssignment_16) {
  Status s = Status::NotFound("test");
  s = s;
  EXPECT_TRUE(s.IsNotFound());
}

// Test with empty message
TEST(StatusTest_16, NotFoundEmptyMessage_16) {
  Status s = Status::NotFound("");
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_FALSE(s.ok());
}

// Test with std::string based Slice
TEST(StatusTest_16, NotFoundWithStdString_16) {
  std::string msg = "key not found";
  Status s = Status::NotFound(msg);
  EXPECT_TRUE(s.IsNotFound());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("key not found"));
}

// Test default constructor
TEST(StatusTest_16, DefaultConstructorIsOK_16) {
  Status s;
  EXPECT_TRUE(s.ok());
}

// Test that different error types are distinct
TEST(StatusTest_16, DifferentErrorTypesAreDistinct_16) {
  Status notFound = Status::NotFound("a");
  Status corruption = Status::Corruption("b");
  Status notSupported = Status::NotSupported("c");
  Status invalidArg = Status::InvalidArgument("d");
  Status ioError = Status::IOError("e");

  EXPECT_TRUE(notFound.IsNotFound());
  EXPECT_FALSE(notFound.IsCorruption());

  EXPECT_TRUE(corruption.IsCorruption());
  EXPECT_FALSE(corruption.IsNotFound());

  EXPECT_TRUE(notSupported.IsNotSupportedError());
  EXPECT_FALSE(notSupported.IsIOError());

  EXPECT_TRUE(invalidArg.IsInvalidArgument());
  EXPECT_FALSE(invalidArg.IsNotSupportedError());

  EXPECT_TRUE(ioError.IsIOError());
  EXPECT_FALSE(ioError.IsInvalidArgument());
}

// Test multiple copies maintain independence
TEST(StatusTest_16, CopiedStatusIsIndependent_16) {
  Status s1 = Status::NotFound("original");
  Status s2 = s1;
  s1 = Status::OK();
  EXPECT_TRUE(s1.ok());
  EXPECT_TRUE(s2.IsNotFound());
}

// Test with long message
TEST(StatusTest_16, LongMessage_16) {
  std::string longMsg(1000, 'x');
  Status s = Status::Corruption(longMsg);
  EXPECT_TRUE(s.IsCorruption());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find(longMsg));
}

// Test NotFound with default second argument (empty Slice)
TEST(StatusTest_16, NotFoundDefaultSecondArg_16) {
  Status s = Status::NotFound("only one msg");
  EXPECT_TRUE(s.IsNotFound());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("only one msg"));
}

}  // namespace leveldb
