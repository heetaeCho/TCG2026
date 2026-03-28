#include "gtest/gtest.h"
#include "leveldb/status.h"

namespace leveldb {

// Test fixture for Status class
class StatusTest_26 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// ==================== OK Status Tests ====================

TEST_F(StatusTest_26, OKStatusIsOk_26) {
  Status s = Status::OK();
  EXPECT_TRUE(s.ok());
}

TEST_F(StatusTest_26, OKStatusIsNotNotFound_26) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsNotFound());
}

TEST_F(StatusTest_26, OKStatusIsNotCorruption_26) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsCorruption());
}

TEST_F(StatusTest_26, OKStatusIsNotIOError_26) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsIOError());
}

TEST_F(StatusTest_26, OKStatusIsNotNotSupported_26) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsNotSupportedError());
}

TEST_F(StatusTest_26, OKStatusIsNotInvalidArgument_26) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST_F(StatusTest_26, OKStatusToString_26) {
  Status s = Status::OK();
  EXPECT_EQ("OK", s.ToString());
}

// ==================== NotFound Status Tests ====================

TEST_F(StatusTest_26, NotFoundStatusIsNotOk_26) {
  Status s = Status::NotFound("key not found");
  EXPECT_FALSE(s.ok());
}

TEST_F(StatusTest_26, NotFoundStatusIsNotFound_26) {
  Status s = Status::NotFound("key not found");
  EXPECT_TRUE(s.IsNotFound());
}

TEST_F(StatusTest_26, NotFoundStatusIsNotCorruption_26) {
  Status s = Status::NotFound("key not found");
  EXPECT_FALSE(s.IsCorruption());
}

TEST_F(StatusTest_26, NotFoundStatusIsNotIOError_26) {
  Status s = Status::NotFound("key not found");
  EXPECT_FALSE(s.IsIOError());
}

TEST_F(StatusTest_26, NotFoundStatusIsNotNotSupported_26) {
  Status s = Status::NotFound("key not found");
  EXPECT_FALSE(s.IsNotSupportedError());
}

TEST_F(StatusTest_26, NotFoundStatusIsNotInvalidArgument_26) {
  Status s = Status::NotFound("key not found");
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST_F(StatusTest_26, NotFoundStatusToStringContainsMessage_26) {
  Status s = Status::NotFound("key not found");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("key not found"));
  EXPECT_NE(std::string::npos, str.find("NotFound"));
}

TEST_F(StatusTest_26, NotFoundWithTwoMessages_26) {
  Status s = Status::NotFound("primary msg", "secondary msg");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("primary msg"));
  EXPECT_NE(std::string::npos, str.find("secondary msg"));
}

// ==================== Corruption Status Tests ====================

TEST_F(StatusTest_26, CorruptionStatusIsNotOk_26) {
  Status s = Status::Corruption("data corrupted");
  EXPECT_FALSE(s.ok());
}

TEST_F(StatusTest_26, CorruptionStatusIsCorruption_26) {
  Status s = Status::Corruption("data corrupted");
  EXPECT_TRUE(s.IsCorruption());
}

TEST_F(StatusTest_26, CorruptionStatusIsNotNotFound_26) {
  Status s = Status::Corruption("data corrupted");
  EXPECT_FALSE(s.IsNotFound());
}

TEST_F(StatusTest_26, CorruptionStatusIsNotIOError_26) {
  Status s = Status::Corruption("data corrupted");
  EXPECT_FALSE(s.IsIOError());
}

TEST_F(StatusTest_26, CorruptionStatusToStringContainsMessage_26) {
  Status s = Status::Corruption("data corrupted");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("data corrupted"));
  EXPECT_NE(std::string::npos, str.find("Corruption"));
}

TEST_F(StatusTest_26, CorruptionWithTwoMessages_26) {
  Status s = Status::Corruption("primary", "secondary");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("primary"));
  EXPECT_NE(std::string::npos, str.find("secondary"));
}

// ==================== NotSupported Status Tests ====================

TEST_F(StatusTest_26, NotSupportedStatusIsNotOk_26) {
  Status s = Status::NotSupported("not supported");
  EXPECT_FALSE(s.ok());
}

TEST_F(StatusTest_26, NotSupportedStatusIsNotSupported_26) {
  Status s = Status::NotSupported("not supported");
  EXPECT_TRUE(s.IsNotSupportedError());
}

TEST_F(StatusTest_26, NotSupportedStatusIsNotOtherErrors_26) {
  Status s = Status::NotSupported("not supported");
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST_F(StatusTest_26, NotSupportedStatusToStringContainsMessage_26) {
  Status s = Status::NotSupported("feature X");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("feature X"));
  EXPECT_NE(std::string::npos, str.find("Not implemented"));
}

// ==================== InvalidArgument Status Tests ====================

TEST_F(StatusTest_26, InvalidArgumentStatusIsNotOk_26) {
  Status s = Status::InvalidArgument("bad argument");
  EXPECT_FALSE(s.ok());
}

TEST_F(StatusTest_26, InvalidArgumentStatusIsInvalidArgument_26) {
  Status s = Status::InvalidArgument("bad argument");
  EXPECT_TRUE(s.IsInvalidArgument());
}

TEST_F(StatusTest_26, InvalidArgumentStatusIsNotOtherErrors_26) {
  Status s = Status::InvalidArgument("bad argument");
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
}

TEST_F(StatusTest_26, InvalidArgumentStatusToStringContainsMessage_26) {
  Status s = Status::InvalidArgument("bad argument");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("bad argument"));
  EXPECT_NE(std::string::npos, str.find("Invalid argument"));
}

TEST_F(StatusTest_26, InvalidArgumentWithTwoMessages_26) {
  Status s = Status::InvalidArgument("arg1", "arg2");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("arg1"));
  EXPECT_NE(std::string::npos, str.find("arg2"));
}

// ==================== IOError Status Tests ====================

TEST_F(StatusTest_26, IOErrorStatusIsNotOk_26) {
  Status s = Status::IOError("io error");
  EXPECT_FALSE(s.ok());
}

TEST_F(StatusTest_26, IOErrorStatusIsIOError_26) {
  Status s = Status::IOError("io error");
  EXPECT_TRUE(s.IsIOError());
}

TEST_F(StatusTest_26, IOErrorStatusIsNotOtherErrors_26) {
  Status s = Status::IOError("io error");
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST_F(StatusTest_26, IOErrorStatusToStringContainsMessage_26) {
  Status s = Status::IOError("disk failure");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("disk failure"));
  EXPECT_NE(std::string::npos, str.find("IO error"));
}

TEST_F(StatusTest_26, IOErrorWithTwoMessages_26) {
  Status s = Status::IOError("read error", "file.dat");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("read error"));
  EXPECT_NE(std::string::npos, str.find("file.dat"));
}

// ==================== Copy and Move Tests ====================

TEST_F(StatusTest_26, CopyConstructorFromOK_26) {
  Status original = Status::OK();
  Status copy(original);
  EXPECT_TRUE(copy.ok());
  EXPECT_TRUE(original.ok());
}

TEST_F(StatusTest_26, CopyConstructorFromError_26) {
  Status original = Status::NotFound("test message");
  Status copy(original);
  EXPECT_TRUE(copy.IsNotFound());
  EXPECT_TRUE(original.IsNotFound());
}

TEST_F(StatusTest_26, CopyAssignmentFromOK_26) {
  Status s = Status::NotFound("error");
  s = Status::OK();
  EXPECT_TRUE(s.ok());
}

TEST_F(StatusTest_26, CopyAssignmentFromError_26) {
  Status s = Status::OK();
  Status error = Status::Corruption("corrupted");
  s = error;
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_TRUE(error.IsCorruption());
}

TEST_F(StatusTest_26, MoveConstructor_26) {
  Status original = Status::IOError("io problem");
  Status moved(std::move(original));
  EXPECT_TRUE(moved.IsIOError());
}

TEST_F(StatusTest_26, MoveAssignment_26) {
  Status s = Status::OK();
  s = Status::InvalidArgument("bad arg");
  EXPECT_TRUE(s.IsInvalidArgument());
}

TEST_F(StatusTest_26, SelfAssignment_26) {
  Status s = Status::NotFound("self test");
  s = s;
  EXPECT_TRUE(s.IsNotFound());
}

// ==================== Default Constructor Tests ====================

TEST_F(StatusTest_26, DefaultConstructorIsOk_26) {
  Status s;
  EXPECT_TRUE(s.ok());
}

// ==================== Empty Message Tests ====================

TEST_F(StatusTest_26, NotFoundWithEmptyMessage_26) {
  Status s = Status::NotFound("");
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_FALSE(s.ok());
}

TEST_F(StatusTest_26, CorruptionWithEmptyMessage_26) {
  Status s = Status::Corruption("");
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_FALSE(s.ok());
}

TEST_F(StatusTest_26, IOErrorWithEmptyMessage_26) {
  Status s = Status::IOError("");
  EXPECT_TRUE(s.IsIOError());
  EXPECT_FALSE(s.ok());
}

TEST_F(StatusTest_26, InvalidArgumentWithEmptyMessage_26) {
  Status s = Status::InvalidArgument("");
  EXPECT_TRUE(s.IsInvalidArgument());
  EXPECT_FALSE(s.ok());
}

TEST_F(StatusTest_26, NotSupportedWithEmptyMessage_26) {
  Status s = Status::NotSupported("");
  EXPECT_TRUE(s.IsNotSupportedError());
  EXPECT_FALSE(s.ok());
}

// ==================== Multiple Assignments Tests ====================

TEST_F(StatusTest_26, MultipleAssignments_26) {
  Status s = Status::OK();
  EXPECT_TRUE(s.ok());

  s = Status::NotFound("nf");
  EXPECT_TRUE(s.IsNotFound());

  s = Status::Corruption("cor");
  EXPECT_TRUE(s.IsCorruption());

  s = Status::IOError("io");
  EXPECT_TRUE(s.IsIOError());

  s = Status::InvalidArgument("inv");
  EXPECT_TRUE(s.IsInvalidArgument());

  s = Status::NotSupported("ns");
  EXPECT_TRUE(s.IsNotSupportedError());

  s = Status::OK();
  EXPECT_TRUE(s.ok());
}

// ==================== ToString for OK ====================

TEST_F(StatusTest_26, ToStringForDefaultConstructed_26) {
  Status s;
  EXPECT_EQ("OK", s.ToString());
}

// ==================== Long Message Test ====================

TEST_F(StatusTest_26, LongErrorMessage_26) {
  std::string long_msg(1000, 'x');
  Status s = Status::NotFound(long_msg);
  EXPECT_TRUE(s.IsNotFound());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find(long_msg));
}

// ==================== Copy preserves message ====================

TEST_F(StatusTest_26, CopyPreservesMessage_26) {
  Status original = Status::Corruption("important message");
  Status copy = original;
  EXPECT_EQ(original.ToString(), copy.ToString());
}

}  // namespace leveldb
