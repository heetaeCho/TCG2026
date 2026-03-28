#include "gtest/gtest.h"
#include "leveldb/status.h"
#include "leveldb/slice.h"

namespace leveldb {

// Test OK status creation and properties
TEST(StatusTest_19, OKStatusIsOk_19) {
  Status s = Status::OK();
  EXPECT_TRUE(s.ok());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_19, OKStatusToString_19) {
  Status s = Status::OK();
  EXPECT_EQ(s.ToString(), "OK");
}

// Test NotFound status
TEST(StatusTest_19, NotFoundStatus_19) {
  Status s = Status::NotFound("key not found");
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_19, NotFoundStatusToString_19) {
  Status s = Status::NotFound("key not found");
  std::string str = s.ToString();
  EXPECT_NE(str.find("NotFound"), std::string::npos);
  EXPECT_NE(str.find("key not found"), std::string::npos);
}

TEST(StatusTest_19, NotFoundWithTwoMessages_19) {
  Status s = Status::NotFound("key not found", "extra info");
  EXPECT_TRUE(s.IsNotFound());
  std::string str = s.ToString();
  EXPECT_NE(str.find("key not found"), std::string::npos);
  EXPECT_NE(str.find("extra info"), std::string::npos);
}

// Test Corruption status
TEST(StatusTest_19, CorruptionStatus_19) {
  Status s = Status::Corruption("data corrupted");
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_19, CorruptionStatusToString_19) {
  Status s = Status::Corruption("data corrupted");
  std::string str = s.ToString();
  EXPECT_NE(str.find("Corruption"), std::string::npos);
  EXPECT_NE(str.find("data corrupted"), std::string::npos);
}

TEST(StatusTest_19, CorruptionWithTwoMessages_19) {
  Status s = Status::Corruption("data corrupted", "block 42");
  EXPECT_TRUE(s.IsCorruption());
  std::string str = s.ToString();
  EXPECT_NE(str.find("data corrupted"), std::string::npos);
  EXPECT_NE(str.find("block 42"), std::string::npos);
}

// Test NotSupported status
TEST(StatusTest_19, NotSupportedStatus_19) {
  Status s = Status::NotSupported("feature not supported");
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_19, NotSupportedStatusToString_19) {
  Status s = Status::NotSupported("feature not supported");
  std::string str = s.ToString();
  EXPECT_NE(str.find("Not implemented"), std::string::npos);
}

// Test InvalidArgument status
TEST(StatusTest_19, InvalidArgumentStatus_19) {
  Status s = Status::InvalidArgument("bad argument");
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsInvalidArgument());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsIOError());
  EXPECT_FALSE(s.IsNotSupportedError());
}

TEST(StatusTest_19, InvalidArgumentStatusToString_19) {
  Status s = Status::InvalidArgument("bad argument");
  std::string str = s.ToString();
  EXPECT_NE(str.find("Invalid argument"), std::string::npos);
  EXPECT_NE(str.find("bad argument"), std::string::npos);
}

TEST(StatusTest_19, InvalidArgumentWithTwoMessages_19) {
  Status s = Status::InvalidArgument("bad argument", "details");
  EXPECT_TRUE(s.IsInvalidArgument());
  std::string str = s.ToString();
  EXPECT_NE(str.find("bad argument"), std::string::npos);
  EXPECT_NE(str.find("details"), std::string::npos);
}

// Test IOError status
TEST(StatusTest_19, IOErrorStatus_19) {
  Status s = Status::IOError("disk failure");
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsIOError());
  EXPECT_FALSE(s.IsNotFound());
  EXPECT_FALSE(s.IsCorruption());
  EXPECT_FALSE(s.IsNotSupportedError());
  EXPECT_FALSE(s.IsInvalidArgument());
}

TEST(StatusTest_19, IOErrorStatusToString_19) {
  Status s = Status::IOError("disk failure");
  std::string str = s.ToString();
  EXPECT_NE(str.find("IO error"), std::string::npos);
  EXPECT_NE(str.find("disk failure"), std::string::npos);
}

TEST(StatusTest_19, IOErrorWithTwoMessages_19) {
  Status s = Status::IOError("disk failure", "/path/to/file");
  EXPECT_TRUE(s.IsIOError());
  std::string str = s.ToString();
  EXPECT_NE(str.find("disk failure"), std::string::npos);
  EXPECT_NE(str.find("/path/to/file"), std::string::npos);
}

// Test copy constructor
TEST(StatusTest_19, CopyConstructorOK_19) {
  Status original = Status::OK();
  Status copy(original);
  EXPECT_TRUE(copy.ok());
  EXPECT_TRUE(original.ok());
}

TEST(StatusTest_19, CopyConstructorError_19) {
  Status original = Status::NotFound("missing key");
  Status copy(original);
  EXPECT_TRUE(copy.IsNotFound());
  EXPECT_TRUE(original.IsNotFound());
  EXPECT_EQ(copy.ToString(), original.ToString());
}

// Test copy assignment
TEST(StatusTest_19, CopyAssignmentOK_19) {
  Status s = Status::NotFound("test");
  s = Status::OK();
  EXPECT_TRUE(s.ok());
}

TEST(StatusTest_19, CopyAssignmentError_19) {
  Status s = Status::OK();
  Status error = Status::Corruption("bad data");
  s = error;
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_TRUE(error.IsCorruption());
}

// Test move constructor
TEST(StatusTest_19, MoveConstructor_19) {
  Status original = Status::IOError("io error");
  Status moved(std::move(original));
  EXPECT_TRUE(moved.IsIOError());
}

// Test move assignment
TEST(StatusTest_19, MoveAssignment_19) {
  Status s = Status::OK();
  s = Status::InvalidArgument("invalid");
  EXPECT_TRUE(s.IsInvalidArgument());
}

// Test self-assignment
TEST(StatusTest_19, SelfCopyAssignment_19) {
  Status s = Status::NotFound("test message");
  const Status& ref = s;
  s = ref;
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_NE(s.ToString().find("test message"), std::string::npos);
}

// Test with empty messages
TEST(StatusTest_19, EmptyMessageNotFound_19) {
  Status s = Status::NotFound("");
  EXPECT_TRUE(s.IsNotFound());
  EXPECT_FALSE(s.ok());
}

TEST(StatusTest_19, EmptyMessageCorruption_19) {
  Status s = Status::Corruption("");
  EXPECT_TRUE(s.IsCorruption());
}

// Test with Slice-based messages
TEST(StatusTest_19, SliceBasedMessage_19) {
  std::string msg = "detailed error message";
  Slice slice_msg(msg);
  Status s = Status::InvalidArgument(slice_msg);
  EXPECT_TRUE(s.IsInvalidArgument());
  EXPECT_NE(s.ToString().find("detailed error message"), std::string::npos);
}

TEST(StatusTest_19, SliceBasedTwoMessages_19) {
  Slice msg1("primary error");
  Slice msg2("secondary detail");
  Status s = Status::IOError(msg1, msg2);
  EXPECT_TRUE(s.IsIOError());
  std::string str = s.ToString();
  EXPECT_NE(str.find("primary error"), std::string::npos);
  EXPECT_NE(str.find("secondary detail"), std::string::npos);
}

// Test default constructor
TEST(StatusTest_19, DefaultConstructorIsOK_19) {
  Status s;
  EXPECT_TRUE(s.ok());
}

// Test that different error types are mutually exclusive
TEST(StatusTest_19, ErrorTypesMutuallyExclusive_19) {
  Status notFound = Status::NotFound("test");
  Status corruption = Status::Corruption("test");
  Status notSupported = Status::NotSupported("test");
  Status invalidArg = Status::InvalidArgument("test");
  Status ioError = Status::IOError("test");

  // NotFound
  EXPECT_TRUE(notFound.IsNotFound());
  EXPECT_FALSE(notFound.IsCorruption());
  EXPECT_FALSE(notFound.IsNotSupportedError());
  EXPECT_FALSE(notFound.IsInvalidArgument());
  EXPECT_FALSE(notFound.IsIOError());

  // Corruption
  EXPECT_FALSE(corruption.IsNotFound());
  EXPECT_TRUE(corruption.IsCorruption());
  EXPECT_FALSE(corruption.IsNotSupportedError());
  EXPECT_FALSE(corruption.IsInvalidArgument());
  EXPECT_FALSE(corruption.IsIOError());

  // NotSupported
  EXPECT_FALSE(notSupported.IsNotFound());
  EXPECT_FALSE(notSupported.IsCorruption());
  EXPECT_TRUE(notSupported.IsNotSupportedError());
  EXPECT_FALSE(notSupported.IsInvalidArgument());
  EXPECT_FALSE(notSupported.IsIOError());

  // InvalidArgument
  EXPECT_FALSE(invalidArg.IsNotFound());
  EXPECT_FALSE(invalidArg.IsCorruption());
  EXPECT_FALSE(invalidArg.IsNotSupportedError());
  EXPECT_TRUE(invalidArg.IsInvalidArgument());
  EXPECT_FALSE(invalidArg.IsIOError());

  // IOError
  EXPECT_FALSE(ioError.IsNotFound());
  EXPECT_FALSE(ioError.IsCorruption());
  EXPECT_FALSE(ioError.IsNotSupportedError());
  EXPECT_FALSE(ioError.IsInvalidArgument());
  EXPECT_TRUE(ioError.IsIOError());
}

// Test with long messages
TEST(StatusTest_19, LongMessage_19) {
  std::string longMsg(10000, 'x');
  Status s = Status::Corruption(longMsg);
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_NE(s.ToString().find(longMsg), std::string::npos);
}

// Test copy preserves independence
TEST(StatusTest_19, CopyIndependence_19) {
  Status s1 = Status::NotFound("original");
  Status s2 = s1;
  s1 = Status::OK();
  EXPECT_TRUE(s1.ok());
  EXPECT_TRUE(s2.IsNotFound());
}

// Test assignment chain
TEST(StatusTest_19, AssignmentChain_19) {
  Status s1 = Status::NotFound("a");
  Status s2 = Status::Corruption("b");
  Status s3 = Status::IOError("c");

  s1 = s2 = s3;
  EXPECT_TRUE(s1.IsIOError());
  EXPECT_TRUE(s2.IsIOError());
  EXPECT_TRUE(s3.IsIOError());
}

// Test default second message (empty Slice)
TEST(StatusTest_19, DefaultSecondMessage_19) {
  Status s1 = Status::NotFound("msg");
  Status s2 = Status::NotFound("msg", Slice());
  // Both should produce the same result since default is empty Slice
  EXPECT_TRUE(s1.IsNotFound());
  EXPECT_TRUE(s2.IsNotFound());
}

}  // namespace leveldb
