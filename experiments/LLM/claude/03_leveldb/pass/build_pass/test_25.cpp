#include "gtest/gtest.h"
#include "leveldb/status.h"

namespace leveldb {

// Test fixture for Status tests
class StatusTest_25 : public ::testing::Test {
 protected:
  Status ok_status_;
};

// ==================== OK Status Tests ====================

TEST_F(StatusTest_25, OKStatusIsOk_25) {
  Status s = Status::OK();
  EXPECT_TRUE(s.ok());
}

TEST_F(StatusTest_25, OKStatusIsNotNotFound_25) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsNotFound());
}

TEST_F(StatusTest_25, OKStatusIsNotCorruption_25) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsCorruption());
}

TEST_F(StatusTest_25, OKStatusIsNotIOError_25) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsIOError());
}

TEST_F(StatusTest_25, OKStatusIsNotNotSupportedError_25) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsNotSupportedError());
}

TEST_F(StatusTest_25, OKStatusIsNotInvalidArgument_25) {
  Status s = Status::OK();
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST_F(StatusTest_25, DefaultConstructorIsOk_25) {
  Status s;
  EXPECT_TRUE(s.ok());
}

TEST_F(StatusTest_25, OKStatusToString_25) {
  Status s = Status::OK();
  EXPECT_EQ("OK", s.ToString());
}

// ==================== NotFound Status Tests ====================

TEST_F(StatusTest_25, NotFoundIsNotOk_25) {
  Status s = Status::NotFound("key missing");
  EXPECT_FALSE(s.ok());
}

TEST_F(StatusTest_25, NotFoundIsNotFound_25) {
  Status s = Status::NotFound("key missing");
  EXPECT_TRUE(s.IsNotFound());
}

TEST_F(StatusTest_25, NotFoundIsNotCorruption_25) {
  Status s = Status::NotFound("key missing");
  EXPECT_FALSE(s.IsCorruption());
}

TEST_F(StatusTest_25, NotFoundIsNotIOError_25) {
  Status s = Status::NotFound("key missing");
  EXPECT_FALSE(s.IsIOError());
}

TEST_F(StatusTest_25, NotFoundIsNotNotSupported_25) {
  Status s = Status::NotFound("key missing");
  EXPECT_FALSE(s.IsNotSupportedError());
}

TEST_F(StatusTest_25, NotFoundIsNotInvalidArgument_25) {
  Status s = Status::NotFound("key missing");
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST_F(StatusTest_25, NotFoundToStringContainsMessage_25) {
  Status s = Status::NotFound("key missing");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Not found"));
  EXPECT_NE(std::string::npos, str.find("key missing"));
}

TEST_F(StatusTest_25, NotFoundWithTwoMessages_25) {
  Status s = Status::NotFound("key missing", "details");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Not found"));
  EXPECT_NE(std::string::npos, str.find("key missing"));
  EXPECT_NE(std::string::npos, str.find("details"));
}

// ==================== Corruption Status Tests ====================

TEST_F(StatusTest_25, CorruptionIsNotOk_25) {
  Status s = Status::Corruption("bad data");
  EXPECT_FALSE(s.ok());
}

TEST_F(StatusTest_25, CorruptionIsCorruption_25) {
  Status s = Status::Corruption("bad data");
  EXPECT_TRUE(s.IsCorruption());
}

TEST_F(StatusTest_25, CorruptionIsNotNotFound_25) {
  Status s = Status::Corruption("bad data");
  EXPECT_FALSE(s.IsNotFound());
}

TEST_F(StatusTest_25, CorruptionIsNotIOError_25) {
  Status s = Status::Corruption("bad data");
  EXPECT_FALSE(s.IsIOError());
}

TEST_F(StatusTest_25, CorruptionIsNotNotSupported_25) {
  Status s = Status::Corruption("bad data");
  EXPECT_FALSE(s.IsNotSupportedError());
}

TEST_F(StatusTest_25, CorruptionIsNotInvalidArgument_25) {
  Status s = Status::Corruption("bad data");
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST_F(StatusTest_25, CorruptionToStringContainsMessage_25) {
  Status s = Status::Corruption("bad data");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Corruption"));
  EXPECT_NE(std::string::npos, str.find("bad data"));
}

TEST_F(StatusTest_25, CorruptionWithTwoMessages_25) {
  Status s = Status::Corruption("bad data", "extra info");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Corruption"));
  EXPECT_NE(std::string::npos, str.find("bad data"));
  EXPECT_NE(std::string::npos, str.find("extra info"));
}

// ==================== NotSupported Status Tests ====================

TEST_F(StatusTest_25, NotSupportedIsNotOk_25) {
  Status s = Status::NotSupported("feature X");
  EXPECT_FALSE(s.ok());
}

TEST_F(StatusTest_25, NotSupportedIsNotSupportedError_25) {
  Status s = Status::NotSupported("feature X");
  EXPECT_TRUE(s.IsNotSupportedError());
}

TEST_F(StatusTest_25, NotSupportedIsNotNotFound_25) {
  Status s = Status::NotSupported("feature X");
  EXPECT_FALSE(s.IsNotFound());
}

TEST_F(StatusTest_25, NotSupportedIsNotCorruption_25) {
  Status s = Status::NotSupported("feature X");
  EXPECT_FALSE(s.IsCorruption());
}

TEST_F(StatusTest_25, NotSupportedIsNotIOError_25) {
  Status s = Status::NotSupported("feature X");
  EXPECT_FALSE(s.IsIOError());
}

TEST_F(StatusTest_25, NotSupportedIsNotInvalidArgument_25) {
  Status s = Status::NotSupported("feature X");
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST_F(StatusTest_25, NotSupportedToStringContainsMessage_25) {
  Status s = Status::NotSupported("feature X");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Not implemented"));
  EXPECT_NE(std::string::npos, str.find("feature X"));
}

TEST_F(StatusTest_25, NotSupportedWithTwoMessages_25) {
  Status s = Status::NotSupported("feature X", "use Y instead");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("feature X"));
  EXPECT_NE(std::string::npos, str.find("use Y instead"));
}

// ==================== InvalidArgument Status Tests ====================

TEST_F(StatusTest_25, InvalidArgumentIsNotOk_25) {
  Status s = Status::InvalidArgument("bad arg");
  EXPECT_FALSE(s.ok());
}

TEST_F(StatusTest_25, InvalidArgumentIsInvalidArgument_25) {
  Status s = Status::InvalidArgument("bad arg");
  EXPECT_TRUE(s.IsInvalidArgument());
}

TEST_F(StatusTest_25, InvalidArgumentIsNotNotFound_25) {
  Status s = Status::InvalidArgument("bad arg");
  EXPECT_FALSE(s.IsNotFound());
}

TEST_F(StatusTest_25, InvalidArgumentIsNotCorruption_25) {
  Status s = Status::InvalidArgument("bad arg");
  EXPECT_FALSE(s.IsCorruption());
}

TEST_F(StatusTest_25, InvalidArgumentIsNotIOError_25) {
  Status s = Status::InvalidArgument("bad arg");
  EXPECT_FALSE(s.IsIOError());
}

TEST_F(StatusTest_25, InvalidArgumentIsNotNotSupported_25) {
  Status s = Status::InvalidArgument("bad arg");
  EXPECT_FALSE(s.IsNotSupportedError());
}

TEST_F(StatusTest_25, InvalidArgumentToStringContainsMessage_25) {
  Status s = Status::InvalidArgument("bad arg");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Invalid argument"));
  EXPECT_NE(std::string::npos, str.find("bad arg"));
}

TEST_F(StatusTest_25, InvalidArgumentWithTwoMessages_25) {
  Status s = Status::InvalidArgument("bad arg", "details");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("bad arg"));
  EXPECT_NE(std::string::npos, str.find("details"));
}

// ==================== IOError Status Tests ====================

TEST_F(StatusTest_25, IOErrorIsNotOk_25) {
  Status s = Status::IOError("disk failure");
  EXPECT_FALSE(s.ok());
}

TEST_F(StatusTest_25, IOErrorIsIOError_25) {
  Status s = Status::IOError("disk failure");
  EXPECT_TRUE(s.IsIOError());
}

TEST_F(StatusTest_25, IOErrorIsNotNotFound_25) {
  Status s = Status::IOError("disk failure");
  EXPECT_FALSE(s.IsNotFound());
}

TEST_F(StatusTest_25, IOErrorIsNotCorruption_25) {
  Status s = Status::IOError("disk failure");
  EXPECT_FALSE(s.IsCorruption());
}

TEST_F(StatusTest_25, IOErrorIsNotNotSupported_25) {
  Status s = Status::IOError("disk failure");
  EXPECT_FALSE(s.IsNotSupportedError());
}

TEST_F(StatusTest_25, IOErrorIsNotInvalidArgument_25) {
  Status s = Status::IOError("disk failure");
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST_F(StatusTest_25, IOErrorToStringContainsMessage_25) {
  Status s = Status::IOError("disk failure");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("IO error"));
  EXPECT_NE(std::string::npos, str.find("disk failure"));
}

TEST_F(StatusTest_25, IOErrorWithTwoMessages_25) {
  Status s = Status::IOError("disk failure", "sector 42");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("disk failure"));
  EXPECT_NE(std::string::npos, str.find("sector 42"));
}

// ==================== Copy and Move Tests ====================

TEST_F(StatusTest_25, CopyConstructorFromOk_25) {
  Status original = Status::OK();
  Status copy(original);
  EXPECT_TRUE(copy.ok());
  EXPECT_TRUE(original.ok());
}

TEST_F(StatusTest_25, CopyConstructorFromError_25) {
  Status original = Status::NotFound("missing");
  Status copy(original);
  EXPECT_TRUE(copy.IsNotFound());
  EXPECT_TRUE(original.IsNotFound());
}

TEST_F(StatusTest_25, CopyAssignmentFromOk_25) {
  Status s = Status::NotFound("something");
  s = Status::OK();
  EXPECT_TRUE(s.ok());
}

TEST_F(StatusTest_25, CopyAssignmentFromError_25) {
  Status s = Status::OK();
  Status error = Status::Corruption("data");
  s = error;
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_TRUE(error.IsCorruption());
}

TEST_F(StatusTest_25, MoveConstructor_25) {
  Status original = Status::IOError("disk");
  Status moved(std::move(original));
  EXPECT_TRUE(moved.IsIOError());
}

TEST_F(StatusTest_25, MoveAssignment_25) {
  Status s = Status::OK();
  s = Status::InvalidArgument("bad");
  EXPECT_TRUE(s.IsInvalidArgument());
}

TEST_F(StatusTest_25, SelfAssignment_25) {
  Status s = Status::NotFound("test");
  s = s;
  EXPECT_TRUE(s.IsNotFound());
}

// ==================== Boundary / Edge Cases ====================

TEST_F(StatusTest_25, EmptyMessageNotFound_25) {
  Status s = Status::NotFound("");
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_FALSE(s.ok());
}

TEST_F(StatusTest_25, EmptyMessageCorruption_25) {
  Status s = Status::Corruption("");
  EXPECT_TRUE(s.IsCorruption());
}

TEST_F(StatusTest_25, EmptyMessageIOError_25) {
  Status s = Status::IOError("");
  EXPECT_TRUE(s.IsIOError());
}

TEST_F(StatusTest_25, EmptyMessageNotSupported_25) {
  Status s = Status::NotSupported("");
  EXPECT_TRUE(s.IsNotSupportedError());
}

TEST_F(StatusTest_25, EmptyMessageInvalidArgument_25) {
  Status s = Status::InvalidArgument("");
  EXPECT_TRUE(s.IsInvalidArgument());
}

TEST_F(StatusTest_25, LongMessageNotFound_25) {
  std::string long_msg(10000, 'x');
  Status s = Status::NotFound(long_msg);
  EXPECT_TRUE(s.IsNotFound());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find(long_msg));
}

TEST_F(StatusTest_25, NotFoundWithEmptySecondMessage_25) {
  Status s = Status::NotFound("primary", "");
  EXPECT_TRUE(s.IsNotFound());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("primary"));
}

TEST_F(StatusTest_25, CopyPreservesMessage_25) {
  Status original = Status::NotFound("specific key", "in table");
  Status copy(original);
  std::string orig_str = original.ToString();
  std::string copy_str = copy.ToString();
  EXPECT_EQ(orig_str, copy_str);
}

TEST_F(StatusTest_25, AssignmentPreservesMessage_25) {
  Status s1 = Status::IOError("file.db", "permission denied");
  Status s2;
  s2 = s1;
  EXPECT_EQ(s1.ToString(), s2.ToString());
}

TEST_F(StatusTest_25, MoveAssignmentOverwritesPrevious_25) {
  Status s = Status::Corruption("old error");
  s = Status::IOError("new error");
  EXPECT_TRUE(s.IsIOError());
  EXPECT_FALSE(s.IsCorruption());
}

TEST_F(StatusTest_25, MultipleStatusesIndependent_25) {
  Status s1 = Status::NotFound("a");
  Status s2 = Status::Corruption("b");
  Status s3 = Status::IOError("c");
  Status s4 = Status::NotSupported("d");
  Status s5 = Status::InvalidArgument("e");
  Status s6 = Status::OK();

  EXPECT_TRUE(s1.IsNotFound());
  EXPECT_TRUE(s2.IsCorruption());
  EXPECT_TRUE(s3.IsIOError());
  EXPECT_TRUE(s4.IsNotSupportedError());
  EXPECT_TRUE(s5.IsInvalidArgument());
  EXPECT_TRUE(s6.ok());
}

}  // namespace leveldb
