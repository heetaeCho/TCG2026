#include "gtest/gtest.h"
#include "leveldb/status.h"

namespace leveldb {

// Test fixture for Status tests
class StatusTest_24 : public ::testing::Test {
 protected:
  // Helper to create various status objects
};

// ==================== OK Status Tests ====================

TEST_F(StatusTest_24, OKStatusIsOk_24) {
  Status s = Status::OK();
  EXPECT_TRUE(s.ok());
}

TEST_F(StatusTest_24, OKStatusIsNotNotFound_24) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsNotFound());
}

TEST_F(StatusTest_24, OKStatusIsNotCorruption_24) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsCorruption());
}

TEST_F(StatusTest_24, OKStatusIsNotIOError_24) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsIOError());
}

TEST_F(StatusTest_24, OKStatusIsNotNotSupported_24) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsNotSupportedError());
}

TEST_F(StatusTest_24, OKStatusIsNotInvalidArgument_24) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST_F(StatusTest_24, OKStatusToString_24) {
  Status s = Status::OK();
  EXPECT_EQ("OK", s.ToString());
}

// ==================== NotFound Status Tests ====================

TEST_F(StatusTest_24, NotFoundStatusIsNotOk_24) {
  Status s = Status::NotFound("key not found");
  EXPECT_FALSE(s.ok());
}

TEST_F(StatusTest_24, NotFoundStatusIsNotFound_24) {
  Status s = Status::NotFound("key not found");
  EXPECT_TRUE(s.IsNotFound());
}

TEST_F(StatusTest_24, NotFoundStatusIsNotCorruption_24) {
  Status s = Status::NotFound("key not found");
  EXPECT_FALSE(s.IsCorruption());
}

TEST_F(StatusTest_24, NotFoundStatusIsNotIOError_24) {
  Status s = Status::NotFound("key not found");
  EXPECT_FALSE(s.IsIOError());
}

TEST_F(StatusTest_24, NotFoundStatusIsNotNotSupported_24) {
  Status s = Status::NotFound("key not found");
  EXPECT_FALSE(s.IsNotSupportedError());
}

TEST_F(StatusTest_24, NotFoundStatusIsNotInvalidArgument_24) {
  Status s = Status::NotFound("key not found");
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST_F(StatusTest_24, NotFoundToStringContainsMessage_24) {
  Status s = Status::NotFound("key not found");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Not found"));
  EXPECT_NE(std::string::npos, str.find("key not found"));
}

TEST_F(StatusTest_24, NotFoundWithTwoMessages_24) {
  Status s = Status::NotFound("key not found", "details");
  EXPECT_TRUE(s.IsNotFound());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("key not found"));
  EXPECT_NE(std::string::npos, str.find("details"));
}

// ==================== Corruption Status Tests ====================

TEST_F(StatusTest_24, CorruptionStatusIsNotOk_24) {
  Status s = Status::Corruption("data corrupted");
  EXPECT_FALSE(s.ok());
}

TEST_F(StatusTest_24, CorruptionStatusIsCorruption_24) {
  Status s = Status::Corruption("data corrupted");
  EXPECT_TRUE(s.IsCorruption());
}

TEST_F(StatusTest_24, CorruptionStatusIsNotNotFound_24) {
  Status s = Status::Corruption("data corrupted");
  EXPECT_FALSE(s.IsNotFound());
}

TEST_F(StatusTest_24, CorruptionStatusIsNotIOError_24) {
  Status s = Status::Corruption("data corrupted");
  EXPECT_FALSE(s.IsIOError());
}

TEST_F(StatusTest_24, CorruptionToStringContainsMessage_24) {
  Status s = Status::Corruption("data corrupted");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Corruption"));
  EXPECT_NE(std::string::npos, str.find("data corrupted"));
}

TEST_F(StatusTest_24, CorruptionWithTwoMessages_24) {
  Status s = Status::Corruption("bad block", "checksum mismatch");
  EXPECT_TRUE(s.IsCorruption());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("bad block"));
  EXPECT_NE(std::string::npos, str.find("checksum mismatch"));
}

// ==================== NotSupported Status Tests ====================

TEST_F(StatusTest_24, NotSupportedStatusIsNotOk_24) {
  Status s = Status::NotSupported("not supported");
  EXPECT_FALSE(s.ok());
}

TEST_F(StatusTest_24, NotSupportedStatusIsNotSupported_24) {
  Status s = Status::NotSupported("not supported");
  EXPECT_TRUE(s.IsNotSupportedError());
}

TEST_F(StatusTest_24, NotSupportedStatusIsNotOtherErrors_24) {
  Status s = Status::NotSupported("not supported");
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST_F(StatusTest_24, NotSupportedToStringContainsMessage_24) {
  Status s = Status::NotSupported("feature X");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Not implemented"));
  EXPECT_NE(std::string::npos, str.find("feature X"));
}

// ==================== InvalidArgument Status Tests ====================

TEST_F(StatusTest_24, InvalidArgumentStatusIsNotOk_24) {
  Status s = Status::InvalidArgument("bad argument");
  EXPECT_FALSE(s.ok());
}

TEST_F(StatusTest_24, InvalidArgumentStatusIsInvalidArgument_24) {
  Status s = Status::InvalidArgument("bad argument");
  EXPECT_TRUE(s.IsInvalidArgument());
}

TEST_F(StatusTest_24, InvalidArgumentStatusIsNotOtherErrors_24) {
  Status s = Status::InvalidArgument("bad argument");
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
}

TEST_F(StatusTest_24, InvalidArgumentToStringContainsMessage_24) {
  Status s = Status::InvalidArgument("bad argument");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Invalid argument"));
  EXPECT_NE(std::string::npos, str.find("bad argument"));
}

TEST_F(StatusTest_24, InvalidArgumentWithTwoMessages_24) {
  Status s = Status::InvalidArgument("param error", "value too large");
  EXPECT_TRUE(s.IsInvalidArgument());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("param error"));
  EXPECT_NE(std::string::npos, str.find("value too large"));
}

// ==================== IOError Status Tests ====================

TEST_F(StatusTest_24, IOErrorStatusIsNotOk_24) {
  Status s = Status::IOError("io error");
  EXPECT_FALSE(s.ok());
}

TEST_F(StatusTest_24, IOErrorStatusIsIOError_24) {
  Status s = Status::IOError("io error");
  EXPECT_TRUE(s.IsIOError());
}

TEST_F(StatusTest_24, IOErrorStatusIsNotOtherErrors_24) {
  Status s = Status::IOError("io error");
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST_F(StatusTest_24, IOErrorToStringContainsMessage_24) {
  Status s = Status::IOError("disk failure");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("IO error"));
  EXPECT_NE(std::string::npos, str.find("disk failure"));
}

TEST_F(StatusTest_24, IOErrorWithTwoMessages_24) {
  Status s = Status::IOError("read error", "/tmp/file");
  EXPECT_TRUE(s.IsIOError());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("read error"));
  EXPECT_NE(std::string::npos, str.find("/tmp/file"));
}

// ==================== Copy and Assignment Tests ====================

TEST_F(StatusTest_24, CopyConstructorOK_24) {
  Status original = Status::OK();
  Status copy(original);
  EXPECT_TRUE(copy.ok());
  EXPECT_TRUE(original.ok());
}

TEST_F(StatusTest_24, CopyConstructorError_24) {
  Status original = Status::NotFound("missing key");
  Status copy(original);
  EXPECT_TRUE(copy.IsNotFound());
  EXPECT_TRUE(original.IsNotFound());
  EXPECT_EQ(original.ToString(), copy.ToString());
}

TEST_F(StatusTest_24, CopyAssignmentOK_24) {
  Status s = Status::NotFound("something");
  s = Status::OK();
  EXPECT_TRUE(s.ok());
}

TEST_F(StatusTest_24, CopyAssignmentError_24) {
  Status s = Status::OK();
  Status error = Status::Corruption("bad data");
  s = error;
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_TRUE(error.IsCorruption());
  EXPECT_EQ(s.ToString(), error.ToString());
}

TEST_F(StatusTest_24, MoveConstructor_24) {
  Status original = Status::IOError("disk fail");
  Status moved(std::move(original));
  EXPECT_TRUE(moved.IsIOError());
}

TEST_F(StatusTest_24, MoveAssignment_24) {
  Status s = Status::OK();
  s = Status::InvalidArgument("bad");
  EXPECT_TRUE(s.IsInvalidArgument());
}

TEST_F(StatusTest_24, MoveAssignmentFromError_24) {
  Status s = Status::Corruption("corrupt");
  s = Status::IOError("io fail");
  EXPECT_TRUE(s.IsIOError());
  EXPECT_FALSE(s.IsCorruption());
}

// ==================== Default Constructor Test ====================

TEST_F(StatusTest_24, DefaultConstructorIsOk_24) {
  Status s;
  EXPECT_TRUE(s.ok());
}

// ==================== Empty Message Tests ====================

TEST_F(StatusTest_24, NotFoundWithEmptyMessage_24) {
  Status s = Status::NotFound("");
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_FALSE(s.ok());
}

TEST_F(StatusTest_24, IOErrorWithEmptyMessage_24) {
  Status s = Status::IOError("");
  EXPECT_TRUE(s.IsIOError());
  EXPECT_FALSE(s.ok());
}

TEST_F(StatusTest_24, CorruptionWithEmptyMessage_24) {
  Status s = Status::Corruption("");
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_FALSE(s.ok());
}

// ==================== Self-Assignment Test ====================

TEST_F(StatusTest_24, SelfAssignment_24) {
  Status s = Status::NotFound("test");
  s = s;
  EXPECT_TRUE(s.IsNotFound());
}

// ==================== Chain Assignment Tests ====================

TEST_F(StatusTest_24, ChainAssignment_24) {
  Status a = Status::OK();
  Status b = Status::NotFound("x");
  Status c = Status::IOError("y");
  a = b = c;
  EXPECT_TRUE(a.IsIOError());
  EXPECT_TRUE(b.IsIOError());
  EXPECT_TRUE(c.IsIOError());
}

// ==================== Multiple Status Instances ====================

TEST_F(StatusTest_24, MultipleStatusInstancesIndependent_24) {
  Status s1 = Status::OK();
  Status s2 = Status::NotFound("a");
  Status s3 = Status::Corruption("b");
  Status s4 = Status::IOError("c");
  Status s5 = Status::NotSupported("d");
  Status s6 = Status::InvalidArgument("e");

  EXPECT_TRUE(s1.ok());
  EXPECT_TRUE(s2.IsNotFound());
  EXPECT_TRUE(s3.IsCorruption());
  EXPECT_TRUE(s4.IsIOError());
  EXPECT_TRUE(s5.IsNotSupportedError());
  EXPECT_TRUE(s6.IsInvalidArgument());
}

}  // namespace leveldb
