// status_to_string_test_456.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/status.h"
#include "leveldb/slice.h"

using ::testing::HasSubstr;
using ::testing::StartsWith;

namespace {

using leveldb::Slice;
using leveldb::Status;

// ---------- OK ----------

TEST(StatusToStringTest_456, DefaultOkReturnsOK_456) {
  Status s;  // default-constructed OK
  EXPECT_EQ(s.ToString(), "OK");
}

TEST(StatusToStringTest_456, StaticOkReturnsOK_456) {
  Status s = Status::OK();
  EXPECT_EQ(s.ToString(), "OK");
}

// ---------- NotFound ----------

TEST(StatusToStringTest_456, NotFound_WithSingleMessage_HasPrefixAndMessage_456) {
  Status s = Status::NotFound(Slice("missing-key"));
  const std::string str = s.ToString();
  EXPECT_THAT(str, StartsWith("NotFound: "));
  EXPECT_THAT(str, HasSubstr("missing-key"));
}

TEST(StatusToStringTest_456, NotFound_WithTwoMessages_ContainsBothInOrder_456) {
  Status s = Status::NotFound(Slice("table"), Slice("meta block"));
  const std::string str = s.ToString();
  EXPECT_THAT(str, StartsWith("NotFound: "));
  auto p1 = str.find("table");
  auto p2 = str.find("meta block");
  ASSERT_NE(p1, std::string::npos);
  ASSERT_NE(p2, std::string::npos);
  EXPECT_LT(p1, p2);  // observable order without asserting exact formatting
}

TEST(StatusToStringTest_456, NotFound_WithEmptyMessages_JustPrefix_456) {
  Status s = Status::NotFound(Slice(""), Slice(""));
  EXPECT_EQ(s.ToString(), "NotFound: ");
}

// ---------- Corruption ----------

TEST(StatusToStringTest_456, Corruption_HasPrefixAndMessage_456) {
  Status s = Status::Corruption(Slice("checksum mismatch"));
  const std::string str = s.ToString();
  EXPECT_THAT(str, StartsWith("Corruption: "));
  EXPECT_THAT(str, HasSubstr("checksum mismatch"));
}

// ---------- NotSupported ----------

TEST(StatusToStringTest_456, NotSupported_HasPrefixAndMessage_456) {
  Status s = Status::NotSupported(Slice("feature X"));
  const std::string str = s.ToString();
  EXPECT_THAT(str, StartsWith("Not implemented: "));
  EXPECT_THAT(str, HasSubstr("feature X"));
}

// ---------- InvalidArgument ----------

TEST(StatusToStringTest_456, InvalidArgument_HasPrefixAndMessage_456) {
  Status s = Status::InvalidArgument(Slice("bad options"));
  const std::string str = s.ToString();
  EXPECT_THAT(str, StartsWith("Invalid argument: "));
  EXPECT_THAT(str, HasSubstr("bad options"));
}

// ---------- IOError ----------

TEST(StatusToStringTest_456, IOError_HasPrefixAndMessage_456) {
  Status s = Status::IOError(Slice("disk full"));
  const std::string str = s.ToString();
  EXPECT_THAT(str, StartsWith("IO error: "));
  EXPECT_THAT(str, HasSubstr("disk full"));
}

// ---------- Copy / Move do not change observable string ----------

TEST(StatusToStringTest_456, CopyAndMove_PreserveToString_456) {
  Status original = Status::IOError(Slice("network down"));
  const std::string expected = original.ToString();

  // Copy
  Status copied = original;
  EXPECT_EQ(copied.ToString(), expected);

  // Move
  Status moved = std::move(copied);
  EXPECT_EQ(moved.ToString(), expected);
}

// ---------- Large message boundary ----------

TEST(StatusToStringTest_456, LargeMessage_IsIncludedInOutput_456) {
  std::string large(8192, 'X');  // reasonably large user message
  Status s = Status::Corruption(Slice(large));
  const std::string str = s.ToString();
  EXPECT_THAT(str, StartsWith("Corruption: "));
  // We don't assert exact size; just that the large content appears.
  EXPECT_THAT(str, HasSubstr(std::string(256, 'X')));  // sample subset appears
}

}  // namespace
