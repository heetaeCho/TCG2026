#include "gtest/gtest.h"
#include "leveldb/status.h"
#include "leveldb/slice.h"

namespace leveldb {

// Test OK status creation and properties
TEST(StatusTest_17, OKStatusIsOk_17) {
  Status s = Status::OK();
  EXPECT_TRUE(s.ok());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_17, OKStatusToString_17) {
  Status s = Status::OK();
  EXPECT_EQ("OK", s.ToString());
}

// Test NotFound status
TEST(StatusTest_17, NotFoundStatus_17) {
  Status s = Status::NotFound("key missing");
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_17, NotFoundStatusWithTwoMessages_17) {
  Status s = Status::NotFound("key missing", "details");
  EXPECT_TRUE(s.IsNotFound());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("key missing"));
  EXPECT_NE(std::string::npos, str.find("details"));
}

TEST(StatusTest_17, NotFoundToStringContainsMessage_17) {
  Status s = Status::NotFound("custom message");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Not found"));
  EXPECT_NE(std::string::npos, str.find("custom message"));
}

// Test Corruption status
TEST(StatusTest_17, CorruptionStatus_17) {
  Status s = Status::Corruption("bad data");
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_17, CorruptionStatusWithTwoMessages_17) {
  Status s = Status::Corruption("bad data", "file.sst");
  EXPECT_TRUE(s.IsCorruption());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("bad data"));
  EXPECT_NE(std::string::npos, str.find("file.sst"));
}

TEST(StatusTest_17, CorruptionToStringContainsMessage_17) {
  Status s = Status::Corruption("checksum mismatch");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Corruption"));
  EXPECT_NE(std::string::npos, str.find("checksum mismatch"));
}

// Test NotSupported status
TEST(StatusTest_17, NotSupportedStatus_17) {
  Status s = Status::NotSupported("feature X");
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_17, NotSupportedToStringContainsMessage_17) {
  Status s = Status::NotSupported("feature X");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Not implemented"));
  EXPECT_NE(std::string::npos, str.find("feature X"));
}

// Test InvalidArgument status
TEST(StatusTest_17, InvalidArgumentStatus_17) {
  Status s = Status::InvalidArgument("bad param");
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsInvalidArgument());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
}

TEST(StatusTest_17, InvalidArgumentToStringContainsMessage_17) {
  Status s = Status::InvalidArgument("bad param");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Invalid argument"));
  EXPECT_NE(std::string::npos, str.find("bad param"));
}

// Test IOError status
TEST(StatusTest_17, IOErrorStatus_17) {
  Status s = Status::IOError("read failure");
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsIOError());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_17, IOErrorWithTwoMessages_17) {
  Status s = Status::IOError("read failure", "/tmp/file");
  EXPECT_TRUE(s.IsIOError());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("read failure"));
  EXPECT_NE(std::string::npos, str.find("/tmp/file"));
}

TEST(StatusTest_17, IOErrorToStringContainsMessage_17) {
  Status s = Status::IOError("disk full");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("IO error"));
  EXPECT_NE(std::string::npos, str.find("disk full"));
}

// Test copy constructor
TEST(StatusTest_17, CopyConstructorOK_17) {
  Status original = Status::OK();
  Status copy(original);
  EXPECT_TRUE(copy.ok());
  EXPECT_TRUE(original.ok());
}

TEST(StatusTest_17, CopyConstructorError_17) {
  Status original = Status::NotFound("missing key");
  Status copy(original);
  EXPECT_TRUE(copy.IsNotFound());
  EXPECT_TRUE(original.IsNotFound());
  EXPECT_EQ(original.ToString(), copy.ToString());
}

// Test copy assignment
TEST(StatusTest_17, CopyAssignmentOK_17) {
  Status s = Status::NotFound("test");
  s = Status::OK();
  EXPECT_TRUE(s.ok());
}

TEST(StatusTest_17, CopyAssignmentError_17) {
  Status s = Status::OK();
  Status error = Status::Corruption("bad");
  s = error;
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_TRUE(error.IsCorruption());
}

TEST(StatusTest_17, SelfAssignment_17) {
  Status s = Status::IOError("io problem");
  s = s;
  EXPECT_TRUE(s.IsIOError());
  EXPECT_NE(std::string::npos, s.ToString().find("io problem"));
}

// Test move constructor
TEST(StatusTest_17, MoveConstructorOK_17) {
  Status original = Status::OK();
  Status moved(std::move(original));
  EXPECT_TRUE(moved.ok());
}

TEST(StatusTest_17, MoveConstructorError_17) {
  Status original = Status::Corruption("data error");
  Status moved(std::move(original));
  EXPECT_TRUE(moved.IsCorruption());
}

// Test move assignment
TEST(StatusTest_17, MoveAssignment_17) {
  Status s = Status::OK();
  s = Status::NotFound("gone");
  EXPECT_TRUE(s.IsNotFound());
}

TEST(StatusTest_17, MoveAssignmentFromError_17) {
  Status s = Status::Corruption("bad");
  s = Status::OK();
  EXPECT_TRUE(s.ok());
}

// Boundary: empty message
TEST(StatusTest_17, EmptyMessage_17) {
  Status s = Status::NotFound("");
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_FALSE(s.ok());
}

// Boundary: empty second message
TEST(StatusTest_17, EmptySecondMessage_17) {
  Status s = Status::Corruption("msg1", "");
  EXPECT_TRUE(s.IsCorruption());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("msg1"));
}

// Boundary: both messages empty
TEST(StatusTest_17, BothMessagesEmpty_17) {
  Status s = Status::IOError("", "");
  EXPECT_TRUE(s.IsIOError());
  EXPECT_FALSE(s.ok());
}

// Test with std::string based Slice
TEST(StatusTest_17, StringSliceMessage_17) {
  std::string msg = "string message";
  Status s = Status::InvalidArgument(Slice(msg));
  EXPECT_TRUE(s.IsInvalidArgument());
  EXPECT_NE(std::string::npos, s.ToString().find("string message"));
}

// Test long message
TEST(StatusTest_17, LongMessage_17) {
  std::string long_msg(1000, 'x');
  Status s = Status::NotFound(long_msg);
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_NE(std::string::npos, s.ToString().find(long_msg));
}

// Test that each status type is distinct
TEST(StatusTest_17, AllTypesDistinct_17) {
  Status ok = Status::OK();
  Status nf = Status::NotFound("a");
  Status cr = Status::Corruption("b");
  Status ns = Status::NotSupported("c");
  Status ia = Status::InvalidArgument("d");
  Status io = Status::IOError("e");

  EXPECT_TRUE(ok.ok());
  EXPECT_FALSE(ok.IsNotFound());
  EXPECT_FALSE(ok.IsCorruption());
  EXPECT_FALSE(ok.IsNotSupportedError());
  EXPECT_FALSE(ok.IsInvalidArgument());
  EXPECT_FALSE(ok.IsIOError());

  EXPECT_TRUE(nf.IsNotFound());
  EXPECT_FALSE(nf.ok());
  EXPECT_FALSE(nf.IsCorruption());

  EXPECT_TRUE(cr.IsCorruption());
  EXPECT_FALSE(cr.IsNotFound());

  EXPECT_TRUE(ns.IsNotSupportedError());
  EXPECT_FALSE(ns.IsCorruption());

  EXPECT_TRUE(ia.IsInvalidArgument());
  EXPECT_FALSE(ia.IsNotSupportedError());

  EXPECT_TRUE(io.IsIOError());
  EXPECT_FALSE(io.IsInvalidArgument());
}

// Test default constructor
TEST(StatusTest_17, DefaultConstructorIsOK_17) {
  Status s;
  EXPECT_TRUE(s.ok());
  EXPECT_EQ("OK", s.ToString());
}

// Test chained assignments
TEST(StatusTest_17, ChainedAssignment_17) {
  Status a, b, c;
  a = b = c = Status::Corruption("chain");
  EXPECT_TRUE(a.IsCorruption());
  EXPECT_TRUE(b.IsCorruption());
  EXPECT_TRUE(c.IsCorruption());
}

// Test copy preserves independence
TEST(StatusTest_17, CopyIndependence_17) {
  Status original = Status::IOError("original");
  Status copy = original;
  original = Status::OK();
  EXPECT_TRUE(original.ok());
  EXPECT_TRUE(copy.IsIOError());
  EXPECT_NE(std::string::npos, copy.ToString().find("original"));
}

}  // namespace leveldb
