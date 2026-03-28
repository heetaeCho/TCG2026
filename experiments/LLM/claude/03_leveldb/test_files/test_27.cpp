#include "gtest/gtest.h"
#include "leveldb/status.h"

namespace leveldb {

// Test default construction creates an OK status
TEST(StatusTest_27, DefaultConstructorIsOK_27) {
  Status status;
  EXPECT_TRUE(status.ok());
}

// Test Status::OK() creates an OK status
TEST(StatusTest_27, OKFactoryIsOK_27) {
  Status status = Status::OK();
  EXPECT_TRUE(status.ok());
  EXPECT_FALSE(status.IsNotFound());
  EXPECT_FALSE(status.IsCorruption());
  EXPECT_FALSE(status.IsIOError());
  EXPECT_FALSE(status.IsNotSupportedError());
  EXPECT_FALSE(status.IsInvalidArgument());
}

// Test NotFound status
TEST(StatusTest_27, NotFoundStatus_27) {
  Status status = Status::NotFound("key missing");
  EXPECT_FALSE(status.ok());
  EXPECT_TRUE(status.IsNotFound());
  EXPECT_FALSE(status.IsCorruption());
  EXPECT_FALSE(status.IsIOError());
  EXPECT_FALSE(status.IsNotSupportedError());
  EXPECT_FALSE(status.IsInvalidArgument());
}

// Test NotFound with two messages
TEST(StatusTest_27, NotFoundWithTwoMessages_27) {
  Status status = Status::NotFound("key missing", "details");
  EXPECT_TRUE(status.IsNotFound());
  std::string str = status.ToString();
  EXPECT_NE(str.find("key missing"), std::string::npos);
  EXPECT_NE(str.find("details"), std::string::npos);
}

// Test Corruption status
TEST(StatusTest_27, CorruptionStatus_27) {
  Status status = Status::Corruption("bad data");
  EXPECT_FALSE(status.ok());
  EXPECT_TRUE(status.IsCorruption());
  EXPECT_FALSE(status.IsNotFound());
  EXPECT_FALSE(status.IsIOError());
  EXPECT_FALSE(status.IsNotSupportedError());
  EXPECT_FALSE(status.IsInvalidArgument());
}

// Test Corruption with two messages
TEST(StatusTest_27, CorruptionWithTwoMessages_27) {
  Status status = Status::Corruption("bad data", "extra info");
  EXPECT_TRUE(status.IsCorruption());
  std::string str = status.ToString();
  EXPECT_NE(str.find("bad data"), std::string::npos);
  EXPECT_NE(str.find("extra info"), std::string::npos);
}

// Test NotSupported status
TEST(StatusTest_27, NotSupportedStatus_27) {
  Status status = Status::NotSupported("unsupported op");
  EXPECT_FALSE(status.ok());
  EXPECT_TRUE(status.IsNotSupportedError());
  EXPECT_FALSE(status.IsNotFound());
  EXPECT_FALSE(status.IsCorruption());
  EXPECT_FALSE(status.IsIOError());
  EXPECT_FALSE(status.IsInvalidArgument());
}

// Test InvalidArgument status
TEST(StatusTest_27, InvalidArgumentStatus_27) {
  Status status = Status::InvalidArgument("bad arg");
  EXPECT_FALSE(status.ok());
  EXPECT_TRUE(status.IsInvalidArgument());
  EXPECT_FALSE(status.IsNotFound());
  EXPECT_FALSE(status.IsCorruption());
  EXPECT_FALSE(status.IsIOError());
  EXPECT_FALSE(status.IsNotSupportedError());
}

// Test IOError status
TEST(StatusTest_27, IOErrorStatus_27) {
  Status status = Status::IOError("disk failure");
  EXPECT_FALSE(status.ok());
  EXPECT_TRUE(status.IsIOError());
  EXPECT_FALSE(status.IsNotFound());
  EXPECT_FALSE(status.IsCorruption());
  EXPECT_FALSE(status.IsNotSupportedError());
  EXPECT_FALSE(status.IsInvalidArgument());
}

// Test IOError with two messages
TEST(StatusTest_27, IOErrorWithTwoMessages_27) {
  Status status = Status::IOError("disk failure", "sector 42");
  EXPECT_TRUE(status.IsIOError());
  std::string str = status.ToString();
  EXPECT_NE(str.find("disk failure"), std::string::npos);
  EXPECT_NE(str.find("sector 42"), std::string::npos);
}

// Test ToString for OK status
TEST(StatusTest_27, ToStringOK_27) {
  Status status = Status::OK();
  std::string str = status.ToString();
  EXPECT_EQ(str, "OK");
}

// Test ToString for NotFound status contains message
TEST(StatusTest_27, ToStringNotFound_27) {
  Status status = Status::NotFound("missing key");
  std::string str = status.ToString();
  EXPECT_NE(str.find("Not found"), std::string::npos);
  EXPECT_NE(str.find("missing key"), std::string::npos);
}

// Test ToString for Corruption status contains message
TEST(StatusTest_27, ToStringCorruption_27) {
  Status status = Status::Corruption("bad block");
  std::string str = status.ToString();
  EXPECT_NE(str.find("Corruption"), std::string::npos);
  EXPECT_NE(str.find("bad block"), std::string::npos);
}

// Test ToString for NotSupported status
TEST(StatusTest_27, ToStringNotSupported_27) {
  Status status = Status::NotSupported("feature X");
  std::string str = status.ToString();
  EXPECT_NE(str.find("Not implemented"), std::string::npos);
  EXPECT_NE(str.find("feature X"), std::string::npos);
}

// Test ToString for InvalidArgument status
TEST(StatusTest_27, ToStringInvalidArgument_27) {
  Status status = Status::InvalidArgument("bad param");
  std::string str = status.ToString();
  EXPECT_NE(str.find("Invalid argument"), std::string::npos);
  EXPECT_NE(str.find("bad param"), std::string::npos);
}

// Test ToString for IOError status
TEST(StatusTest_27, ToStringIOError_27) {
  Status status = Status::IOError("read error");
  std::string str = status.ToString();
  EXPECT_NE(str.find("IO error"), std::string::npos);
  EXPECT_NE(str.find("read error"), std::string::npos);
}

// Test copy constructor from OK status
TEST(StatusTest_27, CopyConstructorOK_27) {
  Status original = Status::OK();
  Status copy(original);
  EXPECT_TRUE(copy.ok());
  EXPECT_TRUE(original.ok());
}

// Test copy constructor from error status
TEST(StatusTest_27, CopyConstructorError_27) {
  Status original = Status::NotFound("some key");
  Status copy(original);
  EXPECT_TRUE(copy.IsNotFound());
  EXPECT_TRUE(original.IsNotFound());
  EXPECT_EQ(copy.ToString(), original.ToString());
}

// Test copy assignment operator
TEST(StatusTest_27, CopyAssignmentOperator_27) {
  Status s1 = Status::NotFound("key1");
  Status s2 = Status::IOError("disk error");
  s2 = s1;
  EXPECT_TRUE(s2.IsNotFound());
  EXPECT_TRUE(s1.IsNotFound());
  EXPECT_EQ(s1.ToString(), s2.ToString());
}

// Test copy assignment from OK to error
TEST(StatusTest_27, CopyAssignmentFromOKToError_27) {
  Status s1 = Status::OK();
  Status s2 = Status::Corruption("data");
  s2 = s1;
  EXPECT_TRUE(s2.ok());
}

// Test copy assignment from error to OK
TEST(StatusTest_27, CopyAssignmentFromErrorToOK_27) {
  Status s1 = Status::InvalidArgument("bad");
  Status s2 = Status::OK();
  s2 = s1;
  EXPECT_TRUE(s2.IsInvalidArgument());
}

// Test self-assignment
TEST(StatusTest_27, SelfAssignment_27) {
  Status s = Status::NotFound("key");
  s = s;
  EXPECT_TRUE(s.IsNotFound());
  std::string str = s.ToString();
  EXPECT_NE(str.find("key"), std::string::npos);
}

// Test move constructor
TEST(StatusTest_27, MoveConstructor_27) {
  Status original = Status::Corruption("corrupted file");
  Status moved(std::move(original));
  EXPECT_TRUE(moved.IsCorruption());
  std::string str = moved.ToString();
  EXPECT_NE(str.find("corrupted file"), std::string::npos);
}

// Test move assignment operator
TEST(StatusTest_27, MoveAssignmentOperator_27) {
  Status s1 = Status::IOError("io problem");
  Status s2 = Status::OK();
  s2 = std::move(s1);
  EXPECT_TRUE(s2.IsIOError());
  std::string str = s2.ToString();
  EXPECT_NE(str.find("io problem"), std::string::npos);
}

// Test move assignment from OK
TEST(StatusTest_27, MoveAssignmentFromOK_27) {
  Status s1 = Status::OK();
  Status s2 = Status::NotFound("key");
  s2 = std::move(s1);
  EXPECT_TRUE(s2.ok());
}

// Test empty message
TEST(StatusTest_27, EmptyMessage_27) {
  Status status = Status::NotFound("");
  EXPECT_TRUE(status.IsNotFound());
  EXPECT_FALSE(status.ok());
}

// Test NotFound with empty second message
TEST(StatusTest_27, NotFoundEmptySecondMessage_27) {
  Status status = Status::NotFound("primary msg", "");
  EXPECT_TRUE(status.IsNotFound());
  std::string str = status.ToString();
  EXPECT_NE(str.find("primary msg"), std::string::npos);
}

// Test multiple assignments in sequence
TEST(StatusTest_27, MultipleAssignments_27) {
  Status s = Status::OK();
  EXPECT_TRUE(s.ok());

  s = Status::NotFound("a");
  EXPECT_TRUE(s.IsNotFound());

  s = Status::Corruption("b");
  EXPECT_TRUE(s.IsCorruption());

  s = Status::IOError("c");
  EXPECT_TRUE(s.IsIOError());

  s = Status::NotSupported("d");
  EXPECT_TRUE(s.IsNotSupportedError());

  s = Status::InvalidArgument("e");
  EXPECT_TRUE(s.IsInvalidArgument());

  s = Status::OK();
  EXPECT_TRUE(s.ok());
}

// Test that error statuses are mutually exclusive
TEST(StatusTest_27, ErrorStatusesMutuallyExclusive_27) {
  Status statuses[] = {
    Status::NotFound("a"),
    Status::Corruption("b"),
    Status::IOError("c"),
    Status::NotSupported("d"),
    Status::InvalidArgument("e"),
  };

  for (const auto& s : statuses) {
    int count = 0;
    if (s.IsNotFound()) count++;
    if (s.IsCorruption()) count++;
    if (s.IsIOError()) count++;
    if (s.IsNotSupportedError()) count++;
    if (s.IsInvalidArgument()) count++;
    EXPECT_EQ(count, 1);
    EXPECT_FALSE(s.ok());
  }
}

// Test copy preserves independence (deep copy)
TEST(StatusTest_27, CopyPreservesIndependence_27) {
  Status s1 = Status::NotFound("original");
  Status s2 = s1;
  s1 = Status::IOError("changed");
  
  EXPECT_TRUE(s1.IsIOError());
  EXPECT_TRUE(s2.IsNotFound());
  EXPECT_NE(s1.ToString(), s2.ToString());
}

// Test long message
TEST(StatusTest_27, LongMessage_27) {
  std::string long_msg(10000, 'x');
  Status status = Status::NotFound(long_msg);
  EXPECT_TRUE(status.IsNotFound());
  std::string str = status.ToString();
  EXPECT_NE(str.find(long_msg), std::string::npos);
}

// Test copy of default constructed status
TEST(StatusTest_27, CopyDefaultConstructed_27) {
  Status s1;
  Status s2 = s1;
  EXPECT_TRUE(s1.ok());
  EXPECT_TRUE(s2.ok());
}

// Test move of default constructed status
TEST(StatusTest_27, MoveDefaultConstructed_27) {
  Status s1;
  Status s2 = std::move(s1);
  EXPECT_TRUE(s2.ok());
}

}  // namespace leveldb
