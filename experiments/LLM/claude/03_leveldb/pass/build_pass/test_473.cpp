#include "gtest/gtest.h"
#include "leveldb/status.h"

namespace leveldb {

// ==================== OK Status Tests ====================

TEST(StatusTest_473, DefaultConstructorIsOk_473) {
  Status s;
  EXPECT_TRUE(s.ok());
}

TEST(StatusTest_473, OKFactoryIsOk_473) {
  Status s = Status::OK();
  EXPECT_TRUE(s.ok());
}

TEST(StatusTest_473, OKStatusToString_473) {
  Status s = Status::OK();
  EXPECT_EQ("OK", s.ToString());
}

TEST(StatusTest_473, OKStatusIsNotError_473) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

// ==================== NotFound Tests ====================

TEST(StatusTest_473, NotFoundStatus_473) {
  Status s = Status::NotFound("key missing");
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_FALSE(s.ok());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_473, NotFoundWithTwoMessages_473) {
  Status s = Status::NotFound("key missing", "details");
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_FALSE(s.ok());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("key missing"));
  EXPECT_NE(std::string::npos, str.find("details"));
}

TEST(StatusTest_473, NotFoundToStringContainsMessage_473) {
  Status s = Status::NotFound("test message");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Not found"));
  EXPECT_NE(std::string::npos, str.find("test message"));
}

// ==================== Corruption Tests ====================

TEST(StatusTest_473, CorruptionStatus_473) {
  Status s = Status::Corruption("bad data");
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_FALSE(s.ok());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_473, CorruptionWithTwoMessages_473) {
  Status s = Status::Corruption("bad data", "at offset 10");
  EXPECT_TRUE(s.IsCorruption());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("bad data"));
  EXPECT_NE(std::string::npos, str.find("at offset 10"));
}

TEST(StatusTest_473, CorruptionToStringContainsMessage_473) {
  Status s = Status::Corruption("corrupted file");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Corruption"));
  EXPECT_NE(std::string::npos, str.find("corrupted file"));
}

// ==================== NotSupported Tests ====================

TEST(StatusTest_473, NotSupportedStatus_473) {
  Status s = Status::NotSupported("feature X");
  EXPECT_TRUE(s.IsNotSupportedError());
  EXPECT_FALSE(s.ok());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_473, NotSupportedToStringContainsMessage_473) {
  Status s = Status::NotSupported("unsupported op");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Not implemented"));
  EXPECT_NE(std::string::npos, str.find("unsupported op"));
}

// ==================== InvalidArgument Tests ====================

TEST(StatusTest_473, InvalidArgumentStatus_473) {
  Status s = Status::InvalidArgument("bad arg");
  EXPECT_TRUE(s.IsInvalidArgument());
  EXPECT_FALSE(s.ok());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
}

TEST(StatusTest_473, InvalidArgumentToStringContainsMessage_473) {
  Status s = Status::InvalidArgument("invalid param");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Invalid argument"));
  EXPECT_NE(std::string::npos, str.find("invalid param"));
}

// ==================== IOError Tests ====================

TEST(StatusTest_473, IOErrorStatus_473) {
  Status s = Status::IOError("disk failure");
  EXPECT_TRUE(s.IsIOError());
  EXPECT_FALSE(s.ok());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_473, IOErrorWithTwoMessages_473) {
  Status s = Status::IOError("read error", "file.db");
  EXPECT_TRUE(s.IsIOError());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("read error"));
  EXPECT_NE(std::string::npos, str.find("file.db"));
}

TEST(StatusTest_473, IOErrorToStringContainsMessage_473) {
  Status s = Status::IOError("disk full");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("IO error"));
  EXPECT_NE(std::string::npos, str.find("disk full"));
}

// ==================== Copy Constructor Tests ====================

TEST(StatusTest_473, CopyConstructorOK_473) {
  Status original = Status::OK();
  Status copy(original);
  EXPECT_TRUE(copy.ok());
  EXPECT_TRUE(original.ok());
}

TEST(StatusTest_473, CopyConstructorNotFound_473) {
  Status original = Status::NotFound("missing key");
  Status copy(original);
  EXPECT_TRUE(copy.IsNotFound());
  EXPECT_TRUE(original.IsNotFound());
  EXPECT_EQ(original.ToString(), copy.ToString());
}

TEST(StatusTest_473, CopyConstructorCorruption_473) {
  Status original = Status::Corruption("bad block");
  Status copy(original);
  EXPECT_TRUE(copy.IsCorruption());
  EXPECT_TRUE(original.IsCorruption());
  EXPECT_EQ(original.ToString(), copy.ToString());
}

TEST(StatusTest_473, CopyConstructorIOError_473) {
  Status original = Status::IOError("write failed");
  Status copy(original);
  EXPECT_TRUE(copy.IsIOError());
  EXPECT_TRUE(original.IsIOError());
  EXPECT_EQ(original.ToString(), copy.ToString());
}

// ==================== Copy Assignment Tests ====================

TEST(StatusTest_473, CopyAssignmentOK_473) {
  Status original = Status::OK();
  Status assigned = Status::NotFound("x");
  assigned = original;
  EXPECT_TRUE(assigned.ok());
  EXPECT_TRUE(original.ok());
}

TEST(StatusTest_473, CopyAssignmentError_473) {
  Status original = Status::Corruption("damaged");
  Status assigned = Status::OK();
  assigned = original;
  EXPECT_TRUE(assigned.IsCorruption());
  EXPECT_EQ(original.ToString(), assigned.ToString());
}

TEST(StatusTest_473, SelfAssignment_473) {
  Status s = Status::NotFound("test");
  s = s;
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_NE(std::string::npos, s.ToString().find("test"));
}

// ==================== Move Constructor Tests ====================

TEST(StatusTest_473, MoveConstructorOK_473) {
  Status original = Status::OK();
  Status moved(std::move(original));
  EXPECT_TRUE(moved.ok());
}

TEST(StatusTest_473, MoveConstructorError_473) {
  Status original = Status::IOError("io problem");
  std::string original_str = original.ToString();
  Status moved(std::move(original));
  EXPECT_TRUE(moved.IsIOError());
  EXPECT_EQ(original_str, moved.ToString());
}

// ==================== Move Assignment Tests ====================

TEST(StatusTest_473, MoveAssignmentOK_473) {
  Status s1 = Status::OK();
  Status s2 = Status::NotFound("x");
  s2 = std::move(s1);
  EXPECT_TRUE(s2.ok());
}

TEST(StatusTest_473, MoveAssignmentError_473) {
  Status s1 = Status::InvalidArgument("bad");
  std::string s1_str = s1.ToString();
  Status s2 = Status::OK();
  s2 = std::move(s1);
  EXPECT_TRUE(s2.IsInvalidArgument());
  EXPECT_EQ(s1_str, s2.ToString());
}

// ==================== Empty Message Tests ====================

TEST(StatusTest_473, NotFoundEmptyMessage_473) {
  Status s = Status::NotFound("");
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_473, CorruptionEmptyMessage_473) {
  Status s = Status::Corruption("");
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_473, IOErrorEmptyMessage_473) {
  Status s = Status::IOError("");
  EXPECT_TRUE(s.IsIOError());
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_473, NotSupportedEmptyMessage_473) {
  Status s = Status::NotSupported("");
  EXPECT_TRUE(s.IsNotSupportedError());
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_473, InvalidArgumentEmptyMessage_473) {
  Status s = Status::InvalidArgument("");
  EXPECT_TRUE(s.IsInvalidArgument());
  EXPECT_FALSE(s.ok());
}

// ==================== Boundary: Long Messages ====================

TEST(StatusTest_473, LongMessageNotFound_473) {
  std::string long_msg(10000, 'a');
  Status s = Status::NotFound(long_msg);
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_NE(std::string::npos, s.ToString().find(long_msg));
}

TEST(StatusTest_473, LongMessageBothArgs_473) {
  std::string msg1(5000, 'x');
  std::string msg2(5000, 'y');
  Status s = Status::Corruption(msg1, msg2);
  EXPECT_TRUE(s.IsCorruption());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find(msg1));
  EXPECT_NE(std::string::npos, str.find(msg2));
}

// ==================== Multiple Copies Independence ====================

TEST(StatusTest_473, CopiedStatusIndependentOfOriginal_473) {
  Status original = Status::NotFound("original");
  Status copy = original;
  original = Status::OK();
  EXPECT_TRUE(original.ok());
  EXPECT_TRUE(copy.IsNotFound());
  EXPECT_NE(std::string::npos, copy.ToString().find("original"));
}

TEST(StatusTest_473, ChainedCopy_473) {
  Status s1 = Status::IOError("first");
  Status s2 = s1;
  Status s3 = s2;
  EXPECT_TRUE(s3.IsIOError());
  EXPECT_EQ(s1.ToString(), s3.ToString());
}

// ==================== Reassignment Tests ====================

TEST(StatusTest_473, ReassignDifferentErrorTypes_473) {
  Status s = Status::NotFound("a");
  EXPECT_TRUE(s.IsNotFound());
  
  s = Status::Corruption("b");
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_FALSE(s.IsNotFound());
  
  s = Status::IOError("c");
  EXPECT_TRUE(s.IsIOError());
  EXPECT_FALSE(s.IsCorruption());
  
  s = Status::OK();
  EXPECT_TRUE(s.ok());
  EXPECT_FALSE(s.IsIOError());
}

}  // namespace leveldb
