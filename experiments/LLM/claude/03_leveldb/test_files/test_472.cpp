#include "gtest/gtest.h"
#include "leveldb/status.h"

namespace leveldb {

// ===================== OK Status Tests =====================

TEST(StatusTest_472, DefaultConstructorIsOk_472) {
  Status s;
  EXPECT_TRUE(s.ok());
}

TEST(StatusTest_472, OKFactoryReturnsOkStatus_472) {
  Status s = Status::OK();
  EXPECT_TRUE(s.ok());
}

TEST(StatusTest_472, OKStatusIsNotError_472) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_472, OKStatusToString_472) {
  Status s = Status::OK();
  EXPECT_EQ("OK", s.ToString());
}

// ===================== NotFound Tests =====================

TEST(StatusTest_472, NotFoundStatus_472) {
  Status s = Status::NotFound("key missing");
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_FALSE(s.ok());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_472, NotFoundStatusToStringContainsMessage_472) {
  Status s = Status::NotFound("key missing");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Not found"));
  EXPECT_NE(std::string::npos, str.find("key missing"));
}

TEST(StatusTest_472, NotFoundStatusWithTwoMessages_472) {
  Status s = Status::NotFound("key missing", "details");
  EXPECT_TRUE(s.IsNotFound());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("key missing"));
  EXPECT_NE(std::string::npos, str.find("details"));
}

// ===================== Corruption Tests =====================

TEST(StatusTest_472, CorruptionStatus_472) {
  Status s = Status::Corruption("bad data");
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_FALSE(s.ok());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_472, CorruptionStatusToString_472) {
  Status s = Status::Corruption("bad data");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Corruption"));
  EXPECT_NE(std::string::npos, str.find("bad data"));
}

TEST(StatusTest_472, CorruptionStatusWithTwoMessages_472) {
  Status s = Status::Corruption("bad data", "in block 5");
  EXPECT_TRUE(s.IsCorruption());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("bad data"));
  EXPECT_NE(std::string::npos, str.find("in block 5"));
}

// ===================== NotSupported Tests =====================

TEST(StatusTest_472, NotSupportedStatus_472) {
  Status s = Status::NotSupported("feature X");
  EXPECT_TRUE(s.IsNotSupportedError());
  EXPECT_FALSE(s.ok());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_472, NotSupportedStatusToString_472) {
  Status s = Status::NotSupported("feature X");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Not implemented"));
  EXPECT_NE(std::string::npos, str.find("feature X"));
}

// ===================== InvalidArgument Tests =====================

TEST(StatusTest_472, InvalidArgumentStatus_472) {
  Status s = Status::InvalidArgument("bad arg");
  EXPECT_TRUE(s.IsInvalidArgument());
  EXPECT_FALSE(s.ok());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
}

TEST(StatusTest_472, InvalidArgumentStatusToString_472) {
  Status s = Status::InvalidArgument("bad arg");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Invalid argument"));
  EXPECT_NE(std::string::npos, str.find("bad arg"));
}

// ===================== IOError Tests =====================

TEST(StatusTest_472, IOErrorStatus_472) {
  Status s = Status::IOError("disk full");
  EXPECT_TRUE(s.IsIOError());
  EXPECT_FALSE(s.ok());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_472, IOErrorStatusToString_472) {
  Status s = Status::IOError("disk full");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("IO error"));
  EXPECT_NE(std::string::npos, str.find("disk full"));
}

TEST(StatusTest_472, IOErrorStatusWithTwoMessages_472) {
  Status s = Status::IOError("disk full", "path /tmp");
  EXPECT_TRUE(s.IsIOError());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("disk full"));
  EXPECT_NE(std::string::npos, str.find("path /tmp"));
}

// ===================== Copy Constructor Tests =====================

TEST(StatusTest_472, CopyConstructorOK_472) {
  Status s1 = Status::OK();
  Status s2(s1);
  EXPECT_TRUE(s1.ok());
  EXPECT_TRUE(s2.ok());
}

TEST(StatusTest_472, CopyConstructorError_472) {
  Status s1 = Status::NotFound("missing");
  Status s2(s1);
  EXPECT_TRUE(s1.IsNotFound());
  EXPECT_TRUE(s2.IsNotFound());
  EXPECT_EQ(s1.ToString(), s2.ToString());
}

// ===================== Move Constructor Tests =====================

TEST(StatusTest_472, MoveConstructorOK_472) {
  Status s1 = Status::OK();
  Status s2(std::move(s1));
  EXPECT_TRUE(s2.ok());
}

TEST(StatusTest_472, MoveConstructorError_472) {
  Status s1 = Status::IOError("fail");
  std::string original_str = s1.ToString();
  Status s2(std::move(s1));
  EXPECT_TRUE(s2.IsIOError());
  EXPECT_EQ(original_str, s2.ToString());
}

TEST(StatusTest_472, MoveConstructorLeavesSourceOk_472) {
  Status s1 = Status::Corruption("bad");
  Status s2(std::move(s1));
  // After move, s1's state_ is nullptr, so it should be ok()
  EXPECT_TRUE(s1.ok());
  EXPECT_TRUE(s2.IsCorruption());
}

// ===================== Copy Assignment Tests =====================

TEST(StatusTest_472, CopyAssignmentOK_472) {
  Status s1 = Status::OK();
  Status s2 = Status::NotFound("x");
  s2 = s1;
  EXPECT_TRUE(s2.ok());
  EXPECT_TRUE(s1.ok());
}

TEST(StatusTest_472, CopyAssignmentError_472) {
  Status s1 = Status::Corruption("corrupt");
  Status s2 = Status::OK();
  s2 = s1;
  EXPECT_TRUE(s2.IsCorruption());
  EXPECT_TRUE(s1.IsCorruption());
  EXPECT_EQ(s1.ToString(), s2.ToString());
}

TEST(StatusTest_472, SelfCopyAssignment_472) {
  Status s = Status::IOError("io fail");
  const Status& ref = s;
  s = ref;
  EXPECT_TRUE(s.IsIOError());
}

// ===================== Move Assignment Tests =====================

TEST(StatusTest_472, MoveAssignmentOK_472) {
  Status s1 = Status::OK();
  Status s2 = Status::NotFound("x");
  s2 = std::move(s1);
  EXPECT_TRUE(s2.ok());
}

TEST(StatusTest_472, MoveAssignmentError_472) {
  Status s1 = Status::InvalidArgument("arg");
  std::string original_str = s1.ToString();
  Status s2 = Status::OK();
  s2 = std::move(s1);
  EXPECT_TRUE(s2.IsInvalidArgument());
  EXPECT_EQ(original_str, s2.ToString());
  // s1 should be ok after move
  EXPECT_TRUE(s1.ok());
}

TEST(StatusTest_472, MoveAssignmentOverwritesExisting_472) {
  Status s1 = Status::NotSupported("not supported");
  Status s2 = Status::IOError("io error");
  s2 = std::move(s1);
  EXPECT_TRUE(s2.IsNotSupportedError());
  EXPECT_TRUE(s1.ok());
}

// ===================== Empty Message Tests =====================

TEST(StatusTest_472, NotFoundWithEmptyMessage_472) {
  Status s = Status::NotFound("");
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_472, CorruptionWithEmptyMessage_472) {
  Status s = Status::Corruption("");
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_472, IOErrorWithEmptyMessage_472) {
  Status s = Status::IOError("");
  EXPECT_TRUE(s.IsIOError());
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_472, NotSupportedWithEmptyMessage_472) {
  Status s = Status::NotSupported("");
  EXPECT_TRUE(s.IsNotSupportedError());
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_472, InvalidArgumentWithEmptyMessage_472) {
  Status s = Status::InvalidArgument("");
  EXPECT_TRUE(s.IsInvalidArgument());
  EXPECT_FALSE(s.ok());
}

// ===================== Default Second Message Tests =====================

TEST(StatusTest_472, NotFoundDefaultSecondMessage_472) {
  Status s1 = Status::NotFound("msg");
  Status s2 = Status::NotFound("msg", Slice());
  // Both should produce the same kind of status
  EXPECT_TRUE(s1.IsNotFound());
  EXPECT_TRUE(s2.IsNotFound());
}

// ===================== Multiple Status Interactions =====================

TEST(StatusTest_472, MultipleStatusObjects_472) {
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

// ===================== Chain Assignment Tests =====================

TEST(StatusTest_472, ChainCopyAssignment_472) {
  Status s1 = Status::NotFound("chain");
  Status s2;
  Status s3;
  s3 = s2 = s1;
  EXPECT_TRUE(s1.IsNotFound());
  EXPECT_TRUE(s2.IsNotFound());
  EXPECT_TRUE(s3.IsNotFound());
}

// ===================== Destructor Safety =====================

TEST(StatusTest_472, DestructorOnOkStatus_472) {
  // Just ensure no crash
  { Status s = Status::OK(); }
}

TEST(StatusTest_472, DestructorOnErrorStatus_472) {
  // Just ensure no crash
  { Status s = Status::NotFound("test"); }
}

TEST(StatusTest_472, DestructorAfterMove_472) {
  // Ensure destructor works after move
  {
    Status s1 = Status::Corruption("data");
    Status s2 = std::move(s1);
    // s1 is now in moved-from state, both should destruct safely
  }
}

}  // namespace leveldb
