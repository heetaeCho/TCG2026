#include "gtest/gtest.h"
#include "leveldb/status.h"

namespace leveldb {

// ==================== Default Construction ====================

TEST(StatusTest_28, DefaultConstructionIsOk_28) {
  Status s;
  EXPECT_TRUE(s.ok());
}

TEST(StatusTest_28, DefaultConstructionNotNotFound_28) {
  Status s;
  EXPECT_FALSE(s.IsNotFound());
}

TEST(StatusTest_28, DefaultConstructionNotCorruption_28) {
  Status s;
  EXPECT_FALSE(s.IsCorruption());
}

TEST(StatusTest_28, DefaultConstructionNotIOError_28) {
  Status s;
  EXPECT_FALSE(s.IsIOError());
}

TEST(StatusTest_28, DefaultConstructionNotNotSupported_28) {
  Status s;
  EXPECT_FALSE(s.IsNotSupportedError());
}

TEST(StatusTest_28, DefaultConstructionNotInvalidArgument_28) {
  Status s;
  EXPECT_FALSE(s.IsInvalidArgument());
}

// ==================== Static Factory: OK ====================

TEST(StatusTest_28, OKStatusIsOk_28) {
  Status s = Status::OK();
  EXPECT_TRUE(s.ok());
}

TEST(StatusTest_28, OKStatusToString_28) {
  Status s = Status::OK();
  EXPECT_EQ("OK", s.ToString());
}

// ==================== Static Factory: NotFound ====================

TEST(StatusTest_28, NotFoundIsNotOk_28) {
  Status s = Status::NotFound("key missing");
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_28, NotFoundIsNotFound_28) {
  Status s = Status::NotFound("key missing");
  EXPECT_TRUE(s.IsNotFound());
}

TEST(StatusTest_28, NotFoundIsNotCorruption_28) {
  Status s = Status::NotFound("key missing");
  EXPECT_FALSE(s.IsCorruption());
}

TEST(StatusTest_28, NotFoundIsNotIOError_28) {
  Status s = Status::NotFound("key missing");
  EXPECT_FALSE(s.IsIOError());
}

TEST(StatusTest_28, NotFoundIsNotNotSupported_28) {
  Status s = Status::NotFound("key missing");
  EXPECT_FALSE(s.IsNotSupportedError());
}

TEST(StatusTest_28, NotFoundIsNotInvalidArgument_28) {
  Status s = Status::NotFound("key missing");
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_28, NotFoundToStringContainsMessage_28) {
  Status s = Status::NotFound("key missing");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Not found"));
  EXPECT_NE(std::string::npos, str.find("key missing"));
}

TEST(StatusTest_28, NotFoundWithTwoMessages_28) {
  Status s = Status::NotFound("key missing", "extra info");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("key missing"));
  EXPECT_NE(std::string::npos, str.find("extra info"));
}

// ==================== Static Factory: Corruption ====================

TEST(StatusTest_28, CorruptionIsNotOk_28) {
  Status s = Status::Corruption("data corrupted");
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_28, CorruptionIsCorruption_28) {
  Status s = Status::Corruption("data corrupted");
  EXPECT_TRUE(s.IsCorruption());
}

TEST(StatusTest_28, CorruptionIsNotNotFound_28) {
  Status s = Status::Corruption("data corrupted");
  EXPECT_FALSE(s.IsNotFound());
}

TEST(StatusTest_28, CorruptionToStringContainsMessage_28) {
  Status s = Status::Corruption("data corrupted");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Corruption"));
  EXPECT_NE(std::string::npos, str.find("data corrupted"));
}

TEST(StatusTest_28, CorruptionWithTwoMessages_28) {
  Status s = Status::Corruption("data corrupted", "block 42");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("data corrupted"));
  EXPECT_NE(std::string::npos, str.find("block 42"));
}

// ==================== Static Factory: NotSupported ====================

TEST(StatusTest_28, NotSupportedIsNotOk_28) {
  Status s = Status::NotSupported("feature X");
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_28, NotSupportedIsNotSupportedError_28) {
  Status s = Status::NotSupported("feature X");
  EXPECT_TRUE(s.IsNotSupportedError());
}

TEST(StatusTest_28, NotSupportedIsNotOtherErrors_28) {
  Status s = Status::NotSupported("feature X");
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_28, NotSupportedToStringContainsMessage_28) {
  Status s = Status::NotSupported("feature X");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Not implemented"));
  EXPECT_NE(std::string::npos, str.find("feature X"));
}

// ==================== Static Factory: InvalidArgument ====================

TEST(StatusTest_28, InvalidArgumentIsNotOk_28) {
  Status s = Status::InvalidArgument("bad arg");
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_28, InvalidArgumentIsInvalidArgument_28) {
  Status s = Status::InvalidArgument("bad arg");
  EXPECT_TRUE(s.IsInvalidArgument());
}

TEST(StatusTest_28, InvalidArgumentIsNotOtherErrors_28) {
  Status s = Status::InvalidArgument("bad arg");
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
}

TEST(StatusTest_28, InvalidArgumentToStringContainsMessage_28) {
  Status s = Status::InvalidArgument("bad arg");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("Invalid argument"));
  EXPECT_NE(std::string::npos, str.find("bad arg"));
}

TEST(StatusTest_28, InvalidArgumentWithTwoMessages_28) {
  Status s = Status::InvalidArgument("bad arg", "detail");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("bad arg"));
  EXPECT_NE(std::string::npos, str.find("detail"));
}

// ==================== Static Factory: IOError ====================

TEST(StatusTest_28, IOErrorIsNotOk_28) {
  Status s = Status::IOError("disk failure");
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_28, IOErrorIsIOError_28) {
  Status s = Status::IOError("disk failure");
  EXPECT_TRUE(s.IsIOError());
}

TEST(StatusTest_28, IOErrorIsNotOtherErrors_28) {
  Status s = Status::IOError("disk failure");
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_28, IOErrorToStringContainsMessage_28) {
  Status s = Status::IOError("disk failure");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("IO error"));
  EXPECT_NE(std::string::npos, str.find("disk failure"));
}

TEST(StatusTest_28, IOErrorWithTwoMessages_28) {
  Status s = Status::IOError("disk failure", "errno=5");
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("disk failure"));
  EXPECT_NE(std::string::npos, str.find("errno=5"));
}

// ==================== Copy Constructor ====================

TEST(StatusTest_28, CopyConstructorFromOk_28) {
  Status original = Status::OK();
  Status copy(original);
  EXPECT_TRUE(copy.ok());
  EXPECT_TRUE(original.ok());
}

TEST(StatusTest_28, CopyConstructorFromError_28) {
  Status original = Status::NotFound("missing key");
  Status copy(original);
  EXPECT_TRUE(copy.IsNotFound());
  EXPECT_TRUE(original.IsNotFound());
  EXPECT_NE(std::string::npos, copy.ToString().find("missing key"));
}

TEST(StatusTest_28, CopyConstructorIndependence_28) {
  Status original = Status::Corruption("bad data");
  Status copy(original);
  original = Status::OK();
  EXPECT_TRUE(original.ok());
  EXPECT_TRUE(copy.IsCorruption());
}

// ==================== Copy Assignment ====================

TEST(StatusTest_28, CopyAssignmentFromOkToError_28) {
  Status s = Status::IOError("io problem");
  s = Status::OK();
  EXPECT_TRUE(s.ok());
}

TEST(StatusTest_28, CopyAssignmentFromErrorToOk_28) {
  Status s = Status::OK();
  Status err = Status::NotFound("not here");
  s = err;
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_NE(std::string::npos, s.ToString().find("not here"));
}

TEST(StatusTest_28, CopyAssignmentFromErrorToError_28) {
  Status s = Status::Corruption("bad");
  Status err = Status::IOError("io fail");
  s = err;
  EXPECT_TRUE(s.IsIOError());
  EXPECT_FALSE(s.IsCorruption());
}

TEST(StatusTest_28, SelfCopyAssignment_28) {
  Status s = Status::NotFound("test");
  const Status& ref = s;
  s = ref;
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_NE(std::string::npos, s.ToString().find("test"));
}

// ==================== Move Constructor ====================

TEST(StatusTest_28, MoveConstructorFromOk_28) {
  Status original = Status::OK();
  Status moved(std::move(original));
  EXPECT_TRUE(moved.ok());
}

TEST(StatusTest_28, MoveConstructorFromError_28) {
  Status original = Status::NotFound("moved key");
  Status moved(std::move(original));
  EXPECT_TRUE(moved.IsNotFound());
  EXPECT_NE(std::string::npos, moved.ToString().find("moved key"));
}

// ==================== Move Assignment ====================

TEST(StatusTest_28, MoveAssignmentFromErrorToOk_28) {
  Status s = Status::OK();
  Status err = Status::Corruption("corrupt");
  s = std::move(err);
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_NE(std::string::npos, s.ToString().find("corrupt"));
}

TEST(StatusTest_28, MoveAssignmentFromOkToError_28) {
  Status s = Status::IOError("io");
  Status ok = Status::OK();
  s = std::move(ok);
  EXPECT_TRUE(s.ok());
}

TEST(StatusTest_28, MoveAssignmentFromErrorToError_28) {
  Status s = Status::NotFound("a");
  Status err = Status::InvalidArgument("b");
  s = std::move(err);
  EXPECT_TRUE(s.IsInvalidArgument());
  EXPECT_NE(std::string::npos, s.ToString().find("b"));
}

// ==================== Empty Message ====================

TEST(StatusTest_28, NotFoundWithEmptyMessage_28) {
  Status s = Status::NotFound("");
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_28, CorruptionWithEmptyMessage_28) {
  Status s = Status::Corruption("");
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_28, IOErrorWithEmptyMessage_28) {
  Status s = Status::IOError("");
  EXPECT_TRUE(s.IsIOError());
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_28, NotSupportedWithEmptyMessage_28) {
  Status s = Status::NotSupported("");
  EXPECT_TRUE(s.IsNotSupportedError());
}

TEST(StatusTest_28, InvalidArgumentWithEmptyMessage_28) {
  Status s = Status::InvalidArgument("");
  EXPECT_TRUE(s.IsInvalidArgument());
}

// ==================== ToString for OK ====================

TEST(StatusTest_28, OKToStringIsExactlyOK_28) {
  Status s = Status::OK();
  EXPECT_EQ("OK", s.ToString());
}

// ==================== Multiple assignments chain ====================

TEST(StatusTest_28, ChainedAssignments_28) {
  Status s1 = Status::NotFound("a");
  Status s2 = Status::IOError("b");
  Status s3 = Status::Corruption("c");

  s1 = s2 = s3;
  EXPECT_TRUE(s1.IsCorruption());
  EXPECT_TRUE(s2.IsCorruption());
  EXPECT_TRUE(s3.IsCorruption());
}

// ==================== Boundary: very long message ====================

TEST(StatusTest_28, LongMessage_28) {
  std::string long_msg(10000, 'x');
  Status s = Status::NotFound(long_msg);
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_NE(std::string::npos, s.ToString().find(long_msg));
}

// ==================== Boundary: second message only ====================

TEST(StatusTest_28, NotFoundWithEmptyFirstAndNonEmptySecond_28) {
  Status s = Status::NotFound("", "secondary");
  EXPECT_TRUE(s.IsNotFound());
  std::string str = s.ToString();
  EXPECT_NE(std::string::npos, str.find("secondary"));
}

// ==================== Destructor doesn't crash ====================

TEST(StatusTest_28, DestructorOnOkStatus_28) {
  { Status s = Status::OK(); }
  SUCCEED();
}

TEST(StatusTest_28, DestructorOnErrorStatus_28) {
  { Status s = Status::NotFound("test destruction"); }
  SUCCEED();
}

// ==================== Multiple copies of same status ====================

TEST(StatusTest_28, MultipleCopiesAreIndependent_28) {
  Status original = Status::InvalidArgument("original msg");
  Status copy1(original);
  Status copy2(original);
  Status copy3 = copy1;

  original = Status::OK();
  EXPECT_TRUE(original.ok());
  EXPECT_TRUE(copy1.IsInvalidArgument());
  EXPECT_TRUE(copy2.IsInvalidArgument());
  EXPECT_TRUE(copy3.IsInvalidArgument());
}

}  // namespace leveldb
