#include "gtest/gtest.h"
#include "leveldb/status.h"

namespace leveldb {

// Test OK status
TEST(StatusTest_456, OKStatusToString_456) {
  Status s = Status::OK();
  EXPECT_EQ(s.ToString(), "OK");
}

TEST(StatusTest_456, OKStatusIsOk_456) {
  Status s = Status::OK();
  EXPECT_TRUE(s.ok());
}

TEST(StatusTest_456, OKStatusIsNotError_456) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

// Test NotFound status
TEST(StatusTest_456, NotFoundToString_456) {
  Status s = Status::NotFound("key missing");
  std::string result = s.ToString();
  EXPECT_TRUE(result.find("NotFound") != std::string::npos);
  EXPECT_TRUE(result.find("key missing") != std::string::npos);
}

TEST(StatusTest_456, NotFoundIsNotFound_456) {
  Status s = Status::NotFound("some key");
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_FALSE(s.ok());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_456, NotFoundWithTwoMessages_456) {
  Status s = Status::NotFound("primary msg", "secondary msg");
  std::string result = s.ToString();
  EXPECT_TRUE(result.find("NotFound") != std::string::npos);
  EXPECT_TRUE(result.find("primary msg") != std::string::npos);
}

// Test Corruption status
TEST(StatusTest_456, CorruptionToString_456) {
  Status s = Status::Corruption("file corrupted");
  std::string result = s.ToString();
  EXPECT_TRUE(result.find("Corruption") != std::string::npos);
  EXPECT_TRUE(result.find("file corrupted") != std::string::npos);
}

TEST(StatusTest_456, CorruptionIsCorruption_456) {
  Status s = Status::Corruption("bad data");
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_FALSE(s.ok());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_456, CorruptionWithTwoMessages_456) {
  Status s = Status::Corruption("block", "checksum mismatch");
  std::string result = s.ToString();
  EXPECT_TRUE(result.find("Corruption") != std::string::npos);
  EXPECT_TRUE(result.find("block") != std::string::npos);
}

// Test NotSupported status
TEST(StatusTest_456, NotSupportedToString_456) {
  Status s = Status::NotSupported("feature X");
  std::string result = s.ToString();
  EXPECT_TRUE(result.find("Not implemented") != std::string::npos);
  EXPECT_TRUE(result.find("feature X") != std::string::npos);
}

TEST(StatusTest_456, NotSupportedIsNotSupported_456) {
  Status s = Status::NotSupported("op");
  EXPECT_TRUE(s.IsNotSupportedError());
  EXPECT_FALSE(s.ok());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

// Test InvalidArgument status
TEST(StatusTest_456, InvalidArgumentToString_456) {
  Status s = Status::InvalidArgument("bad param");
  std::string result = s.ToString();
  EXPECT_TRUE(result.find("Invalid argument") != std::string::npos);
  EXPECT_TRUE(result.find("bad param") != std::string::npos);
}

TEST(StatusTest_456, InvalidArgumentIsInvalidArgument_456) {
  Status s = Status::InvalidArgument("null");
  EXPECT_TRUE(s.IsInvalidArgument());
  EXPECT_FALSE(s.ok());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
}

// Test IOError status
TEST(StatusTest_456, IOErrorToString_456) {
  Status s = Status::IOError("disk failure");
  std::string result = s.ToString();
  EXPECT_TRUE(result.find("IO error") != std::string::npos);
  EXPECT_TRUE(result.find("disk failure") != std::string::npos);
}

TEST(StatusTest_456, IOErrorIsIOError_456) {
  Status s = Status::IOError("read error");
  EXPECT_TRUE(s.IsIOError());
  EXPECT_FALSE(s.ok());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_456, IOErrorWithTwoMessages_456) {
  Status s = Status::IOError("open failed", "/tmp/test.db");
  std::string result = s.ToString();
  EXPECT_TRUE(result.find("IO error") != std::string::npos);
  EXPECT_TRUE(result.find("open failed") != std::string::npos);
}

// Test copy constructor
TEST(StatusTest_456, CopyConstructorOK_456) {
  Status original = Status::OK();
  Status copy(original);
  EXPECT_TRUE(copy.ok());
  EXPECT_EQ(copy.ToString(), "OK");
}

TEST(StatusTest_456, CopyConstructorError_456) {
  Status original = Status::NotFound("missing key");
  Status copy(original);
  EXPECT_TRUE(copy.IsNotFound());
  EXPECT_TRUE(copy.ToString().find("missing key") != std::string::npos);
  // Original should still be valid
  EXPECT_TRUE(original.IsNotFound());
}

// Test copy assignment
TEST(StatusTest_456, CopyAssignmentOK_456) {
  Status s = Status::NotFound("x");
  s = Status::OK();
  EXPECT_TRUE(s.ok());
}

TEST(StatusTest_456, CopyAssignmentError_456) {
  Status s = Status::OK();
  Status err = Status::Corruption("bad block");
  s = err;
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_TRUE(s.ToString().find("bad block") != std::string::npos);
}

// Test move constructor
TEST(StatusTest_456, MoveConstructor_456) {
  Status original = Status::IOError("disk full");
  Status moved(std::move(original));
  EXPECT_TRUE(moved.IsIOError());
  EXPECT_TRUE(moved.ToString().find("disk full") != std::string::npos);
}

// Test move assignment
TEST(StatusTest_456, MoveAssignment_456) {
  Status s = Status::OK();
  s = Status::InvalidArgument("bad value");
  EXPECT_TRUE(s.IsInvalidArgument());
  EXPECT_TRUE(s.ToString().find("bad value") != std::string::npos);
}

// Test self-assignment
TEST(StatusTest_456, SelfCopyAssignment_456) {
  Status s = Status::NotFound("test");
  const Status& ref = s;
  s = ref;
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_TRUE(s.ToString().find("test") != std::string::npos);
}

// Boundary: empty message
TEST(StatusTest_456, EmptyMessage_456) {
  Status s = Status::NotFound("");
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_FALSE(s.ok());
  std::string result = s.ToString();
  EXPECT_TRUE(result.find("NotFound") != std::string::npos);
}

// Boundary: very long message
TEST(StatusTest_456, LongMessage_456) {
  std::string long_msg(10000, 'a');
  Status s = Status::Corruption(long_msg);
  EXPECT_TRUE(s.IsCorruption());
  std::string result = s.ToString();
  EXPECT_TRUE(result.find("Corruption") != std::string::npos);
  EXPECT_TRUE(result.find(long_msg) != std::string::npos);
}

// Test default constructor
TEST(StatusTest_456, DefaultConstructorIsOK_456) {
  Status s;
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(s.ToString(), "OK");
}

// Test that different error types produce distinct ToString prefixes
TEST(StatusTest_456, DifferentErrorTypesDistinctPrefixes_456) {
  Status nf = Status::NotFound("msg");
  Status cr = Status::Corruption("msg");
  Status ns = Status::NotSupported("msg");
  Status ia = Status::InvalidArgument("msg");
  Status io = Status::IOError("msg");

  EXPECT_NE(nf.ToString(), cr.ToString());
  EXPECT_NE(cr.ToString(), ns.ToString());
  EXPECT_NE(ns.ToString(), ia.ToString());
  EXPECT_NE(ia.ToString(), io.ToString());
}

// Test with msg2 (secondary message)
TEST(StatusTest_456, NotFoundWithSecondaryMessage_456) {
  Status s = Status::NotFound("primary", "secondary");
  std::string result = s.ToString();
  EXPECT_TRUE(result.find("NotFound") != std::string::npos);
  EXPECT_TRUE(result.find("primary") != std::string::npos);
}

// Test multiple copies are independent
TEST(StatusTest_456, MultipleCopiesIndependent_456) {
  Status s1 = Status::NotFound("first");
  Status s2 = s1;
  Status s3 = Status::Corruption("third");
  s1 = s3;
  // s2 should still be NotFound
  EXPECT_TRUE(s2.IsNotFound());
  EXPECT_TRUE(s1.IsCorruption());
}

// Test chaining assignments
TEST(StatusTest_456, ChainAssignment_456) {
  Status s1, s2, s3;
  s1 = s2 = s3 = Status::IOError("chain");
  EXPECT_TRUE(s1.IsIOError());
  EXPECT_TRUE(s2.IsIOError());
  EXPECT_TRUE(s3.IsIOError());
}

}  // namespace leveldb
