#include "gtest/gtest.h"
#include "leveldb/status.h"

namespace leveldb {

// Test default constructor creates OK status
TEST(StatusTest_21, DefaultConstructorIsOk_21) {
  Status status;
  EXPECT_TRUE(status.ok());
}

// Test static OK() factory method
TEST(StatusTest_21, StaticOkMethod_21) {
  Status status = Status::OK();
  EXPECT_TRUE(status.ok());
}

// Test NotFound status
TEST(StatusTest_21, NotFoundIsNotOk_21) {
  Status status = Status::NotFound("key not found");
  EXPECT_FALSE(status.ok());
  EXPECT_TRUE(status.IsNotFound());
  EXPECT_FALSE(status.IsCorruption());
  EXPECT_FALSE(status.IsIOError());
  EXPECT_FALSE(status.IsNotSupportedError());
  EXPECT_FALSE(status.IsInvalidArgument());
}

// Test Corruption status
TEST(StatusTest_21, CorruptionIsNotOk_21) {
  Status status = Status::Corruption("data corrupted");
  EXPECT_FALSE(status.ok());
  EXPECT_TRUE(status.IsCorruption());
  EXPECT_FALSE(status.IsNotFound());
  EXPECT_FALSE(status.IsIOError());
  EXPECT_FALSE(status.IsNotSupportedError());
  EXPECT_FALSE(status.IsInvalidArgument());
}

// Test NotSupported status
TEST(StatusTest_21, NotSupportedIsNotOk_21) {
  Status status = Status::NotSupported("operation not supported");
  EXPECT_FALSE(status.ok());
  EXPECT_TRUE(status.IsNotSupportedError());
  EXPECT_FALSE(status.IsNotFound());
  EXPECT_FALSE(status.IsCorruption());
  EXPECT_FALSE(status.IsIOError());
  EXPECT_FALSE(status.IsInvalidArgument());
}

// Test InvalidArgument status
TEST(StatusTest_21, InvalidArgumentIsNotOk_21) {
  Status status = Status::InvalidArgument("bad argument");
  EXPECT_FALSE(status.ok());
  EXPECT_TRUE(status.IsInvalidArgument());
  EXPECT_FALSE(status.IsNotFound());
  EXPECT_FALSE(status.IsCorruption());
  EXPECT_FALSE(status.IsIOError());
  EXPECT_FALSE(status.IsNotSupportedError());
}

// Test IOError status
TEST(StatusTest_21, IOErrorIsNotOk_21) {
  Status status = Status::IOError("io failure");
  EXPECT_FALSE(status.ok());
  EXPECT_TRUE(status.IsIOError());
  EXPECT_FALSE(status.IsNotFound());
  EXPECT_FALSE(status.IsCorruption());
  EXPECT_FALSE(status.IsNotSupportedError());
  EXPECT_FALSE(status.IsInvalidArgument());
}

// Test NotFound with two message arguments
TEST(StatusTest_21, NotFoundWithTwoMessages_21) {
  Status status = Status::NotFound("key", "details");
  EXPECT_FALSE(status.ok());
  EXPECT_TRUE(status.IsNotFound());
  std::string str = status.ToString();
  EXPECT_NE(str.find("key"), std::string::npos);
  EXPECT_NE(str.find("details"), std::string::npos);
}

// Test Corruption with two message arguments
TEST(StatusTest_21, CorruptionWithTwoMessages_21) {
  Status status = Status::Corruption("block", "checksum mismatch");
  EXPECT_FALSE(status.ok());
  EXPECT_TRUE(status.IsCorruption());
  std::string str = status.ToString();
  EXPECT_NE(str.find("block"), std::string::npos);
  EXPECT_NE(str.find("checksum mismatch"), std::string::npos);
}

// Test IOError with two message arguments
TEST(StatusTest_21, IOErrorWithTwoMessages_21) {
  Status status = Status::IOError("file", "permission denied");
  EXPECT_FALSE(status.ok());
  EXPECT_TRUE(status.IsIOError());
  std::string str = status.ToString();
  EXPECT_NE(str.find("file"), std::string::npos);
  EXPECT_NE(str.find("permission denied"), std::string::npos);
}

// Test ToString for OK status
TEST(StatusTest_21, ToStringOk_21) {
  Status status = Status::OK();
  std::string str = status.ToString();
  EXPECT_EQ(str, "OK");
}

// Test ToString for NotFound contains relevant info
TEST(StatusTest_21, ToStringNotFound_21) {
  Status status = Status::NotFound("missing key");
  std::string str = status.ToString();
  EXPECT_NE(str.find("Not found"), std::string::npos);
  EXPECT_NE(str.find("missing key"), std::string::npos);
}

// Test ToString for Corruption contains relevant info
TEST(StatusTest_21, ToStringCorruption_21) {
  Status status = Status::Corruption("bad data");
  std::string str = status.ToString();
  EXPECT_NE(str.find("Corruption"), std::string::npos);
  EXPECT_NE(str.find("bad data"), std::string::npos);
}

// Test ToString for IOError
TEST(StatusTest_21, ToStringIOError_21) {
  Status status = Status::IOError("read failure");
  std::string str = status.ToString();
  EXPECT_NE(str.find("IO error"), std::string::npos);
  EXPECT_NE(str.find("read failure"), std::string::npos);
}

// Test ToString for NotSupported
TEST(StatusTest_21, ToStringNotSupported_21) {
  Status status = Status::NotSupported("unsupported op");
  std::string str = status.ToString();
  EXPECT_NE(str.find("Not implemented"), std::string::npos);
  EXPECT_NE(str.find("unsupported op"), std::string::npos);
}

// Test ToString for InvalidArgument
TEST(StatusTest_21, ToStringInvalidArgument_21) {
  Status status = Status::InvalidArgument("bad arg");
  std::string str = status.ToString();
  EXPECT_NE(str.find("Invalid argument"), std::string::npos);
  EXPECT_NE(str.find("bad arg"), std::string::npos);
}

// Test copy constructor
TEST(StatusTest_21, CopyConstructor_21) {
  Status original = Status::NotFound("test message");
  Status copy(original);
  EXPECT_FALSE(copy.ok());
  EXPECT_TRUE(copy.IsNotFound());
  EXPECT_TRUE(original.IsNotFound());
  EXPECT_EQ(original.ToString(), copy.ToString());
}

// Test copy constructor with OK status
TEST(StatusTest_21, CopyConstructorOk_21) {
  Status original = Status::OK();
  Status copy(original);
  EXPECT_TRUE(copy.ok());
  EXPECT_TRUE(original.ok());
}

// Test copy assignment operator
TEST(StatusTest_21, CopyAssignment_21) {
  Status original = Status::Corruption("corrupted");
  Status assigned;
  EXPECT_TRUE(assigned.ok());
  assigned = original;
  EXPECT_FALSE(assigned.ok());
  EXPECT_TRUE(assigned.IsCorruption());
  EXPECT_TRUE(original.IsCorruption());
}

// Test self-assignment
TEST(StatusTest_21, SelfAssignment_21) {
  Status status = Status::IOError("io error");
  status = status;
  EXPECT_TRUE(status.IsIOError());
}

// Test move constructor
TEST(StatusTest_21, MoveConstructor_21) {
  Status original = Status::InvalidArgument("invalid");
  Status moved(std::move(original));
  EXPECT_FALSE(moved.ok());
  EXPECT_TRUE(moved.IsInvalidArgument());
}

// Test move assignment operator
TEST(StatusTest_21, MoveAssignment_21) {
  Status original = Status::NotSupported("not supported");
  Status assigned;
  assigned = std::move(original);
  EXPECT_FALSE(assigned.ok());
  EXPECT_TRUE(assigned.IsNotSupportedError());
}

// Test copy assignment from OK to error
TEST(StatusTest_21, CopyAssignOkOverError_21) {
  Status error = Status::IOError("error");
  Status ok = Status::OK();
  error = ok;
  EXPECT_TRUE(error.ok());
}

// Test move assignment from OK to error
TEST(StatusTest_21, MoveAssignOkOverError_21) {
  Status error = Status::Corruption("error");
  error = Status::OK();
  EXPECT_TRUE(error.ok());
}

// Test with empty message
TEST(StatusTest_21, NotFoundEmptyMessage_21) {
  Status status = Status::NotFound("");
  EXPECT_FALSE(status.ok());
  EXPECT_TRUE(status.IsNotFound());
}

// Test with empty second message
TEST(StatusTest_21, CorruptionEmptySecondMessage_21) {
  Status status = Status::Corruption("main msg", "");
  EXPECT_FALSE(status.ok());
  EXPECT_TRUE(status.IsCorruption());
  std::string str = status.ToString();
  EXPECT_NE(str.find("main msg"), std::string::npos);
}

// Test multiple statuses are independent
TEST(StatusTest_21, MultipleStatusesIndependent_21) {
  Status s1 = Status::NotFound("a");
  Status s2 = Status::Corruption("b");
  Status s3 = Status::IOError("c");
  Status s4 = Status::NotSupported("d");
  Status s5 = Status::InvalidArgument("e");

  EXPECT_TRUE(s1.IsNotFound());
  EXPECT_TRUE(s2.IsCorruption());
  EXPECT_TRUE(s3.IsIOError());
  EXPECT_TRUE(s4.IsNotSupportedError());
  EXPECT_TRUE(s5.IsInvalidArgument());
}

// Test overwriting status with different error type
TEST(StatusTest_21, OverwriteWithDifferentError_21) {
  Status status = Status::NotFound("not found");
  EXPECT_TRUE(status.IsNotFound());
  status = Status::Corruption("corrupted");
  EXPECT_TRUE(status.IsCorruption());
  EXPECT_FALSE(status.IsNotFound());
}

}  // namespace leveldb
