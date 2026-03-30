// File: get_level_test_341.cc

#include "gtest/gtest.h"

// Public interfaces used/observed by the tests
#include "leveldb/slice.h"
#include "db/dbformat.h"

// Include the implementation TU to access the internal static function.
// This is necessary because GetLevel has internal linkage.
#include "db/version_edit.cc"

using leveldb::Slice;

class GetLevelTest_341 : public ::testing::Test {
protected:
  // Helper to build a Slice from raw bytes
  static Slice Bytes(const std::string& bytes) { return Slice(bytes); }
};

// --- Normal operation ---

// TEST_ID 341
TEST_F(GetLevelTest_341, ReturnsTrueAndSetsLevelForZero_341) {
  // varint32(0) = 0x00
  Slice input = Bytes(std::string("\x00", 1));
  int level = -1;

  bool ok = leveldb::GetLevel(&input, &level);

  EXPECT_TRUE(ok);
  EXPECT_EQ(level, 0);
  // Observable effect: input is advanced by 1 byte
  EXPECT_EQ(input.size(), 0u);
}

// TEST_ID 341
TEST_F(GetLevelTest_341, ReturnsTrueAndSetsLevelForMaxAllowed_341) {
  // kNumLevels = 7, max allowed is 6 -> single-byte varint 0x06
  Slice input = Bytes(std::string("\x06", 1));
  int level = -1;

  bool ok = leveldb::GetLevel(&input, &level);

  EXPECT_TRUE(ok);
  EXPECT_EQ(level, 6);
  EXPECT_EQ(input.size(), 0u);
}

// TEST_ID 341
TEST_F(GetLevelTest_341, ConsumesOnlyVarintBytesLeavesRemainder_341) {
  // value = 1 (0x01), followed by an extra sentinel 'X'
  std::string buf = std::string("\x01", 1) + "X";
  Slice input = Bytes(buf);
  int level = -1;

  bool ok = leveldb::GetLevel(&input, &level);

  EXPECT_TRUE(ok);
  EXPECT_EQ(level, 1);
  // Should consume exactly the varint (1 byte), leaving the trailing 'X'
  ASSERT_EQ(input.size(), 1u);
  EXPECT_EQ(input.data()[0], 'X');
}

// --- Boundary / error conditions ---

// TEST_ID 341
TEST_F(GetLevelTest_341, ReturnsFalseWhenValueEqualsKNumLevels_341) {
  // value = 7 (== kNumLevels) -> should be rejected
  Slice input = Bytes(std::string("\x07", 1));
  int level = -1;

  bool ok = leveldb::GetLevel(&input, &level);

  EXPECT_FALSE(ok);
  // On failure via "v >= kNumLevels" path, the varint was successfully parsed,
  // so the input should have been consumed by GetVarint32.
  EXPECT_EQ(input.size(), 0u);
  // Function doesn't assign *level on this path; it should remain unchanged.
  EXPECT_EQ(level, -1);
}

// TEST_ID 341
TEST_F(GetLevelTest_341, ReturnsFalseWhenValueGreaterThanKNumLevelsMultiByte_341) {
  // value = 300 -> varint32 is 0xAC 0x02
  std::string buf;
  buf.push_back(static_cast<char>(0xAC)); // 172, continuation
  buf.push_back(static_cast<char>(0x02)); // final
  Slice input = Bytes(buf);
  int level = 123;  // sentinel

  bool ok = leveldb::GetLevel(&input, &level);

  EXPECT_FALSE(ok);
  // GetVarint32 succeeds and consumes 2 bytes even though level is invalid
  EXPECT_EQ(input.size(), 0u);
  EXPECT_EQ(level, 123);
}

// TEST_ID 341
TEST_F(GetLevelTest_341, ReturnsFalseOnEmptyInput_341) {
  // No bytes -> GetVarint32 should fail
  Slice input = Bytes(std::string());
  int level = 42;

  bool ok = leveldb::GetLevel(&input, &level);

  EXPECT_FALSE(ok);
  // When GetVarint32 fails, input should remain unchanged (observable)
  EXPECT_EQ(input.size(), 0u);
  // No write to *level on failure
  EXPECT_EQ(level, 42);
}

// TEST_ID 341
TEST_F(GetLevelTest_341, ReturnsFalseOnIncompleteVarintContinuationOnly_341) {
  // Incomplete varint: 0x80 indicates continuation but no following byte
  Slice input = Bytes(std::string("\x80", 1));
  int level = 9;

  bool ok = leveldb::GetLevel(&input, &level);

  EXPECT_FALSE(ok);
  // On parse failure, input should not be consumed
  EXPECT_EQ(input.size(), 1u);
  EXPECT_EQ(level, 9);
}
