// File: db/dbformat_debugstring_test.cc

#include "db/dbformat.h"
#include "leveldb/slice.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <limits>
#include <string>

using ::testing::StartsWith;

namespace leveldb {

class InternalKeyTest_187 : public ::testing::Test {};

TEST_F(InternalKeyTest_187, DebugString_ReturnsParsedStringOnValidKey_187) {
  // Arrange: build a valid ParsedInternalKey and set InternalKey from it
  ParsedInternalKey pik(Slice("user"), static_cast<SequenceNumber>(42), kTypeValue);
  InternalKey ik;
  ik.SetFrom(pik);

  // Act
  const std::string internal_debug = ik.DebugString();
  const std::string parsed_debug = pik.DebugString();

  // Assert: InternalKey::DebugString should mirror ParsedInternalKey::DebugString for valid keys
  EXPECT_EQ(internal_debug, parsed_debug);
}

TEST_F(InternalKeyTest_187, DebugString_ConstructorEquivalentToSetFrom_187) {
  // Arrange: create via constructor and via SetFrom with same components
  ParsedInternalKey pik(Slice("abc"), static_cast<SequenceNumber>(1), kTypeDeletion);

  InternalKey from_ctor(Slice("abc"), static_cast<SequenceNumber>(1), kTypeDeletion);

  InternalKey from_setfrom;
  from_setfrom.SetFrom(pik);

  // Act
  const std::string ctor_debug = from_ctor.DebugString();
  const std::string setfrom_debug = from_setfrom.DebugString();

  // Assert: Both creation paths should yield the same DebugString
  EXPECT_EQ(ctor_debug, setfrom_debug);
}

TEST_F(InternalKeyTest_187, DebugString_ReportsBadForInvalidEncoding_187) {
  // Arrange: create an InternalKey from an arbitrary, invalid byte sequence
  InternalKey ik;
  const std::string garbage = "not-an-internal-key";
  // If DecodeFrom returns false, that’s observable error behavior via the interface.
  bool ok = ik.DecodeFrom(Slice(garbage));
  EXPECT_FALSE(ok);

  // Act
  const std::string s = ik.DebugString();

  // Assert: Invalid keys should be reported as "(bad)…"
  EXPECT_THAT(s, StartsWith("(bad)"));
}

TEST_F(InternalKeyTest_187, DebugString_RoundTripsSpecialUserKey_187) {
  // Arrange: user key containing special characters including embedded NUL
  std::string special_key = std::string("a\0b\n\t\x7F", 5);  // 5 bytes: a, NUL, b, newline, tab (0x7F optional)
  ParsedInternalKey pik(Slice(special_key), static_cast<SequenceNumber>(7), kTypeValue);
  InternalKey ik;
  ik.SetFrom(pik);

  // Act
  const std::string internal_debug = ik.DebugString();
  const std::string parsed_debug = pik.DebugString();

  // Assert: For a valid key, InternalKey::DebugString equals ParsedInternalKey::DebugString
  EXPECT_EQ(internal_debug, parsed_debug);
}

TEST_F(InternalKeyTest_187, DebugString_HandlesLargeSequenceNumber_187) {
  // Arrange: Use a large SequenceNumber to exercise boundary-like conditions via the public API.
  const SequenceNumber big = std::numeric_limits<SequenceNumber>::max();
  ParsedInternalKey pik(Slice("max-seq"), big, kTypeValue);
  InternalKey ik;
  ik.SetFrom(pik);

  // Act
  const std::string internal_debug = ik.DebugString();
  const std::string parsed_debug = pik.DebugString();

  // Assert
  EXPECT_EQ(internal_debug, parsed_debug);
}

}  // namespace leveldb
