// File: parsed_internal_key_debugstring_test_186.cc

#include <gtest/gtest.h>
#include <cstdint>
#include <string>

#include "db/dbformat.h"   // ParsedInternalKey, SequenceNumber, ValueType
#include "leveldb/slice.h" // Slice

namespace leveldb {

class ParsedInternalKeyTest_186 : public ::testing::Test {};

TEST(ParsedInternalKeyTest_186, BasicFormatting_186) {
  // Normal operation: simple ASCII key, typical sequence, typical type
  ParsedInternalKey pik(Slice("abc"), static_cast<SequenceNumber>(42),
                        static_cast<ValueType>(1));

  const std::string s = pik.DebugString();

  // Expected format: '<user_key>' @ <sequence> : <int(type)>
  EXPECT_EQ(s, "'abc' @ 42 : 1");
}

TEST(ParsedInternalKeyTest_186, EmptyKeyAndZeroes_186) {
  // Boundary: empty key, zero sequence, zero type
  ParsedInternalKey pik(Slice(""), static_cast<SequenceNumber>(0),
                        static_cast<ValueType>(0));

  const std::string s = pik.DebugString();

  EXPECT_EQ(s, "'' @ 0 : 0");
}

TEST(ParsedInternalKeyTest_186, KeyWithSpaces_186) {
  // Boundary-ish (formatting): spaces should pass through as-is in output
  ParsedInternalKey pik(Slice("a b c"), static_cast<SequenceNumber>(7),
                        static_cast<ValueType>(123));

  const std::string s = pik.DebugString();

  EXPECT_EQ(s, "'a b c' @ 7 : 123");
}

TEST(ParsedInternalKeyTest_186, MaxSequenceNumber_186) {
  // Boundary: maximum 64-bit sequence number
  const SequenceNumber max_seq = std::numeric_limits<SequenceNumber>::max();
  ParsedInternalKey pik(Slice("k"), max_seq, static_cast<ValueType>(2));

  const std::string s = pik.DebugString();

  // We assert the exact decimal value appears in the expected format.
  EXPECT_EQ(s, "'k' @ 18446744073709551615 : 2");
}

} // namespace leveldb
