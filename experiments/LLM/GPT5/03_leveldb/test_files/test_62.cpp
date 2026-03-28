// File: version_edit_setlognumber_test.cc

#include "db/version_edit.h"

#include <gtest/gtest.h>
#include <limits>
#include <string>

namespace leveldb {

class VersionEditTest_62 : public ::testing::Test {};

// [Normal] Setting a typical log number should be reflected in DebugString.
TEST_F(VersionEditTest_62, DebugStringReflectsSetLogNumber_62) {
  VersionEdit edit;
  edit.SetLogNumber(12345);

  const std::string dbg = edit.DebugString();
  // Observable behavior: DebugString mentions the field and the value.
  EXPECT_NE(dbg.find("log_number"), std::string::npos);
  EXPECT_NE(dbg.find("12345"), std::string::npos);
}

// [Boundary] When not set, DebugString should not mention log_number.
TEST_F(VersionEditTest_62, DebugStringDoesNotContainLogNumberWhenUnset_62) {
  VersionEdit edit;

  const std::string dbg = edit.DebugString();
  EXPECT_EQ(dbg.find("log_number"), std::string::npos);
}

// [Boundary] Setting log number to 0 should be observable in DebugString.
TEST_F(VersionEditTest_62, SetLogNumber_BoundaryZero_62) {
  VersionEdit edit;
  edit.SetLogNumber(0);

  const std::string dbg = edit.DebugString();
  EXPECT_NE(dbg.find("log_number"), std::string::npos);
  EXPECT_NE(dbg.find("0"), std::string::npos);
}

// [Boundary] Setting to max uint64_t should be observable in DebugString.
TEST_F(VersionEditTest_62, SetLogNumber_BoundaryMaxUint64_62) {
  VersionEdit edit;
  const uint64_t kMax = std::numeric_limits<uint64_t>::max();
  edit.SetLogNumber(kMax);

  const std::string expected = std::to_string(kMax);
  const std::string dbg = edit.DebugString();
  EXPECT_NE(dbg.find("log_number"), std::string::npos);
  EXPECT_NE(dbg.find(expected), std::string::npos);
}

// [Normal] Calling SetLogNumber multiple times should reflect the latest value.
TEST_F(VersionEditTest_62, SetLogNumber_OverwriteUpdatesValue_62) {
  VersionEdit edit;
  edit.SetLogNumber(1001);
  edit.SetLogNumber(2002);  // latest should win (observable via DebugString)

  const std::string dbg = edit.DebugString();
  EXPECT_NE(dbg.find("2002"), std::string::npos);
  // Ensure earlier value is not reported any more in the human-readable output.
  EXPECT_EQ(dbg.find("1001"), std::string::npos);
}

// [Normal] Encode/Decode round-trip should preserve the set log number (black-box).
TEST_F(VersionEditTest_62, EncodeDecodeRoundTrip_PreservesLogNumber_62) {
  VersionEdit src;
  const uint64_t value = 777;
  src.SetLogNumber(value);

  std::string encoded;
  src.EncodeTo(&encoded);

  VersionEdit dst;
  Status s = dst.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok());

  const std::string dbg = dst.DebugString();
  EXPECT_NE(dbg.find("log_number"), std::string::npos);
  EXPECT_NE(dbg.find(std::to_string(value)), std::string::npos);
}

}  // namespace leveldb
