// File: dfa_constants_byteptr_test_440.cc
#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>
#include <string>

// Forward-declare State so the special-pointer macros compile without
// relying on internal definitions. We don't inspect or define it.
struct State;

// Include the provided partial implementation to access the interface under test.
// NOTE: This is included as a source file only to reach the static inline BytePtr
// and the macro constants. We do NOT re-implement anything here.
#include "re2/dfa.cc"

using ::testing::Test;

class DfaInterfaceTest_440 : public Test {};

// ---- BytePtr tests ----

TEST_F(DfaInterfaceTest_440, BytePtr_ReturnsSameAddress_440) {
  // Arrange
  uint32_t value = 0x11223344u;

  // Act
  const uint8_t* p = re2::BytePtr(&value);

  // Assert: address equality to the canonical reinterpret_cast
  ASSERT_EQ(p, reinterpret_cast<const uint8_t*>(&value));

  // Additionally validate first byte matches the underlying memory.
  // (No assumption about endianness beyond byte-for-byte equivalence.)
  EXPECT_EQ(*p, *reinterpret_cast<const uint8_t*>(&value));
}

TEST_F(DfaInterfaceTest_440, BytePtr_NullptrInputYieldsNullptr_440) {
  const void* ptr = nullptr;
  const uint8_t* p = re2::BytePtr(ptr);
  EXPECT_EQ(p, nullptr);
}

TEST_F(DfaInterfaceTest_440, BytePtr_WorksWithCharBuffer_440) {
  char buf[4] = {'A', 'B', 'C', '\0'};
  const uint8_t* p = re2::BytePtr(buf);

  ASSERT_NE(p, nullptr);
  EXPECT_EQ(p[0], static_cast<uint8_t>('A'));
  EXPECT_EQ(p[1], static_cast<uint8_t>('B'));
  EXPECT_EQ(p[2], static_cast<uint8_t>('C'));
  EXPECT_EQ(p[3], static_cast<uint8_t>('\0'));
}

TEST_F(DfaInterfaceTest_440, BytePtr_ReflectsUnderlyingMutation_440) {
  // Arrange: use a small POD so we can mutate bytes and observe via BytePtr.
  uint32_t v = 0;
  const uint8_t* p = re2::BytePtr(&v);
  ASSERT_NE(p, nullptr);

  // Act: mutate via a non-const byte view; we don't write through p.
  uint8_t* mutable_bytes = reinterpret_cast<uint8_t*>(&v);
  mutable_bytes[0] = 0xAA;
  mutable_bytes[1] = 0xBB;

  // Assert: BytePtr view observes updated memory
  EXPECT_EQ(p[0], 0xAA);
  EXPECT_EQ(p[1], 0xBB);
}

TEST_F(DfaInterfaceTest_440, BytePtr_WithStdStringData_440) {
  // Boundary-ish case: empty string still has a valid c_str() pointer
  std::string s;
  const uint8_t* p_empty = re2::BytePtr(s.c_str());
  ASSERT_NE(p_empty, nullptr);
  EXPECT_EQ(*p_empty, static_cast<uint8_t>('\0'));

  // Non-empty string
  s = "re2";
  const uint8_t* p = re2::BytePtr(s.data());
  ASSERT_NE(p, nullptr);
  EXPECT_EQ(p[0], static_cast<uint8_t>('r'));
  EXPECT_EQ(p[1], static_cast<uint8_t>('e'));
  EXPECT_EQ(p[2], static_cast<uint8_t>('2'));
}

// ---- Special constants/macros tests ----

TEST_F(DfaInterfaceTest_440, SpecialStates_AreNonNullAndDistinct_440) {
  // DeadState and FullMatchState are special sentinel pointers.
  // Validate they are non-null and not equal to each other.
  State* dead = DeadState;
  State* full = FullMatchState;

  ASSERT_NE(dead, nullptr);
  ASSERT_NE(full, nullptr);
  EXPECT_NE(dead, full);
}

TEST_F(DfaInterfaceTest_440, SpecialStates_HaveExpectedSentinelValues_440) {
  // Validate exact sentinel values as specified by the interface.
  EXPECT_EQ(DeadState, reinterpret_cast<State*>(1));
  EXPECT_EQ(FullMatchState, reinterpret_cast<State*>(2));
}

TEST_F(DfaInterfaceTest_440, MatchSeparators_HaveExpectedIntegerValues_440) {
  // Validate numeric sentinels for matching boundaries.
  EXPECT_EQ(Mark, -1);
  EXPECT_EQ(MatchSep, -2);
}
