#include "gtest/gtest.h"
#include "leveldb/status.h"

namespace leveldb {

// ==================== OK Status Tests ====================

TEST(StatusTest_14, OKStatusIsOk_14) {
  Status s = Status::OK();
  EXPECT_TRUE(s.ok());
}

TEST(StatusTest_14, OKStatusIsNotNotFound_14) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsNotFound());
}

TEST(StatusTest_14, OKStatusIsNotCorruption_14) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsCorruption());
}

TEST(StatusTest_14, OKStatusIsNotIOError_14) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsIOError());
}

TEST(StatusTest_14, OKStatusIsNotNotSupported_14) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsNotSupportedError());
}

TEST(StatusTest_14, OKStatusIsNotInvalidArgument_14) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_14, OKStatusToString_14) {
  Status s = Status::OK();
  EXPECT_EQ("OK", s.ToString());
}

// ==================== NotFound Status Tests ====================

TEST(StatusTest_14, NotFoundIsNotOk_14) {
  Status s = Status::NotFound("key missing");
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_14, NotFoundIsNotFound_14) {
  Status s = Status::NotFound("key missing");
  EXPECT_TRUE(s.IsNotFound());
}

TEST(StatusTest_14, NotFoundIsNotCorruption_14) {
  Status s = Status::NotFound("key missing");
  EXPECT_FALSE(s.IsCorruption());
}

TEST(StatusTest_14, NotFoundIsNotIOError_14) {
  Status s = Status::NotFound("key missing");
  EXPECT_FALSE(s.IsIOError());
}

TEST(StatusTest_14, NotFoundIsNotNotSupported_14) {
  Status s = Status::NotFound("key missing");
  EXPECT_FALSE(s.IsNotSupportedError());
}

TEST(StatusTest_14, NotFoundIsNotInvalidArgument_14) {
  Status s = Status::NotFound("key missing");
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_14, NotFoundToStringContainsMessage_14) {
  Status s = Status::NotFound("key missing");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Not found"));
  EXPECT_NE(std::string::npos, str.find("key missing"));
}

TEST(StatusTest_14, NotFoundWithTwoMessages_14) {
  Status s = Status::NotFound("key missing", "details here");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("key missing"));
  EXPECT_NE(std::string::npos, str.find("details here"));
}

// ==================== Corruption Status Tests ====================

TEST(StatusTest_14, CorruptionIsNotOk_14) {
  Status s = Status::Corruption("bad data");
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_14, CorruptionIsCorruption_14) {
  Status s = Status::Corruption("bad data");
  EXPECT_TRUE(s.IsCorruption());
}

TEST(StatusTest_14, CorruptionIsNotNotFound_14) {
  Status s = Status::Corruption("bad data");
  EXPECT_FALSE(s.IsNotFound());
}

TEST(StatusTest_14, CorruptionIsNotIOError_14) {
  Status s = Status::Corruption("bad data");
  EXPECT_FALSE(s.IsIOError());
}

TEST(StatusTest_14, CorruptionToStringContainsMessage_14) {
  Status s = Status::Corruption("bad data");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Corruption"));
  EXPECT_NE(std::string::npos, str.find("bad data"));
}

TEST(StatusTest_14, CorruptionWithTwoMessages_14) {
  Status s = Status::Corruption("bad data", "extra info");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("bad data"));
  EXPECT_NE(std::string::npos, str.find("extra info"));
}

// ==================== NotSupported Status Tests ====================

TEST(StatusTest_14, NotSupportedIsNotOk_14) {
  Status s = Status::NotSupported("feature X");
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_14, NotSupportedIsNotSupported_14) {
  Status s = Status::NotSupported("feature X");
  EXPECT_TRUE(s.IsNotSupportedError());
}

TEST(StatusTest_14, NotSupportedIsNotOtherErrors_14) {
  Status s = Status::NotSupported("feature X");
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_14, NotSupportedToStringContainsMessage_14) {
  Status s = Status::NotSupported("feature X");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Not implemented"));
  EXPECT_NE(std::string::npos, str.find("feature X"));
}

// ==================== InvalidArgument Status Tests ====================

TEST(StatusTest_14, InvalidArgumentIsNotOk_14) {
  Status s = Status::InvalidArgument("bad arg");
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_14, InvalidArgumentIsInvalidArgument_14) {
  Status s = Status::InvalidArgument("bad arg");
  EXPECT_TRUE(s.IsInvalidArgument());
}

TEST(StatusTest_14, InvalidArgumentIsNotOtherErrors_14) {
  Status s = Status::InvalidArgument("bad arg");
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
}

TEST(StatusTest_14, InvalidArgumentToStringContainsMessage_14) {
  Status s = Status::InvalidArgument("bad arg");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Invalid argument"));
  EXPECT_NE(std::string::npos, str.find("bad arg"));
}

TEST(StatusTest_14, InvalidArgumentWithTwoMessages_14) {
  Status s = Status::InvalidArgument("bad arg", "more details");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("bad arg"));
  EXPECT_NE(std::string::npos, str.find("more details"));
}

// ==================== IOError Status Tests ====================

TEST(StatusTest_14, IOErrorIsNotOk_14) {
  Status s = Status::IOError("disk failure");
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_14, IOErrorIsIOError_14) {
  Status s = Status::IOError("disk failure");
  EXPECT_TRUE(s.IsIOError());
}

TEST(StatusTest_14, IOErrorIsNotOtherErrors_14) {
  Status s = Status::IOError("disk failure");
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_14, IOErrorToStringContainsMessage_14) {
  Status s = Status::IOError("disk failure");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("IO error"));
  EXPECT_NE(std::string::npos, str.find("disk failure"));
}

TEST(StatusTest_14, IOErrorWithTwoMessages_14) {
  Status s = Status::IOError("disk failure", "sector 42");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("disk failure"));
  EXPECT_NE(std::string::npos, str.find("sector 42"));
}

// ==================== Copy Constructor Tests ====================

TEST(StatusTest_14, CopyConstructorOK_14) {
  Status original = Status::OK();
  Status copy(original);
  EXPECT_TRUE(copy.ok());
  EXPECT_TRUE(original.ok());
}

TEST(StatusTest_14, CopyConstructorNotFound_14) {
  Status original = Status::NotFound("test msg");
  Status copy(original);
  EXPECT_TRUE(copy.IsNotFound());
  EXPECT_TRUE(original.IsNotFound());
  EXPECT_EQ(original.ToString(), copy.ToString());
}

TEST(StatusTest_14, CopyConstructorCorruption_14) {
  Status original = Status::Corruption("corrupt data");
  Status copy(original);
  EXPECT_TRUE(copy.IsCorruption());
  EXPECT_EQ(original.ToString(), copy.ToString());
}

TEST(StatusTest_14, CopyConstructorIOError_14) {
  Status original = Status::IOError("io problem");
  Status copy(original);
  EXPECT_TRUE(copy.IsIOError());
  EXPECT_EQ(original.ToString(), copy.ToString());
}

// ==================== Move Constructor Tests ====================

TEST(StatusTest_14, MoveConstructorOK_14) {
  Status original = Status::OK();
  Status moved(std::move(original));
  EXPECT_TRUE(moved.ok());
}

TEST(StatusTest_14, MoveConstructorNotFound_14) {
  Status original = Status::NotFound("move test");
  std::string originalStr = original.ToString();
  Status moved(std::move(original));
  EXPECT_TRUE(moved.IsNotFound());
  EXPECT_EQ(originalStr, moved.ToString());
}

// ==================== Copy Assignment Tests ====================

TEST(StatusTest_14, CopyAssignmentOK_14) {
  Status s1 = Status::NotFound("something");
  Status s2 = Status::OK();
  s1 = s2;
  EXPECT_TRUE(s1.ok());
  EXPECT_TRUE(s2.ok());
}

TEST(StatusTest_14, CopyAssignmentError_14) {
  Status s1 = Status::OK();
  Status s2 = Status::Corruption("corrupt");
  s1 = s2;
  EXPECT_TRUE(s1.IsCorruption());
  EXPECT_TRUE(s2.IsCorruption());
  EXPECT_EQ(s1.ToString(), s2.ToString());
}

TEST(StatusTest_14, SelfAssignment_14) {
  Status s = Status::NotFound("self test");
  std::string before = s.ToString();
  s = s;
  EXPECT_EQ(before, s.ToString());
  EXPECT_TRUE(s.IsNotFound());
}

// ==================== Move Assignment Tests ====================

TEST(StatusTest_14, MoveAssignmentOK_14) {
  Status s1 = Status::Corruption("error");
  Status s2 = Status::OK();
  s1 = std::move(s2);
  EXPECT_TRUE(s1.ok());
}

TEST(StatusTest_14, MoveAssignmentError_14) {
  Status s1 = Status::OK();
  Status s2 = Status::IOError("io err");
  std::string s2Str = s2.ToString();
  s1 = std::move(s2);
  EXPECT_TRUE(s1.IsIOError());
  EXPECT_EQ(s2Str, s1.ToString());
}

// ==================== Default Constructor Tests ====================

TEST(StatusTest_14, DefaultConstructorIsOk_14) {
  Status s;
  EXPECT_TRUE(s.ok());
}

TEST(StatusTest_14, DefaultConstructorToString_14) {
  Status s;
  EXPECT_EQ("OK", s.ToString());
}

// ==================== Empty Message Tests ====================

TEST(StatusTest_14, NotFoundWithEmptyMessage_14) {
  Status s = Status::NotFound("");
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_14, CorruptionWithEmptyMessage_14) {
  Status s = Status::Corruption("");
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_14, IOErrorWithEmptyMessage_14) {
  Status s = Status::IOError("");
  EXPECT_TRUE(s.IsIOError());
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_14, NotSupportedWithEmptyMessage_14) {
  Status s = Status::NotSupported("");
  EXPECT_TRUE(s.IsNotSupportedError());
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_14, InvalidArgumentWithEmptyMessage_14) {
  Status s = Status::InvalidArgument("");
  EXPECT_TRUE(s.IsInvalidArgument());
  EXPECT_FALSE(s.ok());
}

// ==================== Multiple Reassignment Tests ====================

TEST(StatusTest_14, MultipleReassignment_14) {
  Status s = Status::OK();
  EXPECT_TRUE(s.ok());

  s = Status::NotFound("first");
  EXPECT_TRUE(s.IsNotFound());

  s = Status::Corruption("second");
  EXPECT_TRUE(s.IsCorruption());

  s = Status::IOError("third");
  EXPECT_TRUE(s.IsIOError());

  s = Status::OK();
  EXPECT_TRUE(s.ok());
}

// ==================== Long Message Tests ====================

TEST(StatusTest_14, LongMessageNotFound_14) {
  std::string longMsg(10000, 'x');
  Status s = Status::NotFound(longMsg);
  EXPECT_TRUE(s.IsNotFound());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find(longMsg));
}

TEST(StatusTest_14, LongMessageIOError_14) {
  std::string longMsg(10000, 'y');
  Status s = Status::IOError(longMsg);
  EXPECT_TRUE(s.IsIOError());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find(longMsg));
}

}  // namespace leveldb
