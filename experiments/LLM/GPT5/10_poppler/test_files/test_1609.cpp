// Decrypt_mixColumns_test_1609.cc
#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <cstring>

// NOTE: mixColumns is declared static inline in Decrypt.cc (translation-unit local).
// To test it via its real implementation (black-box), we include the .cc here.
#include "Decrypt.cc"

namespace {

using State16 = std::array<unsigned char, 16>;

static void ExpectStateEq(const unsigned char *actual, const State16 &expected) {
  ASSERT_NE(actual, nullptr);
  for (size_t i = 0; i < expected.size(); ++i) {
    EXPECT_EQ(actual[i], expected[i]) << "Mismatch at index " << i;
  }
}

TEST(MixColumnsTest_1609, Fips197KnownVector_StateTransformsAsExpected_1609) {
  // FIPS-197 (AES) Section 5.1.3 MixColumns example:
  // Input state (column-major as used by AES state):
  // d4 e0 b8 1e
  // bf b4 41 27
  // 5d 52 11 98
  // 30 ae f1 e5
  // Output:
  // 04 e0 48 28
  // 66 cb f8 06
  // 81 19 d3 26
  // e5 9a 7a 4c
  //
  // Decrypt.cc mixColumns operates on 16-byte state with indices:
  // column c = { state[c], state[4+c], state[8+c], state[12+c] }.

  State16 state = {
      0xd4, 0xe0, 0xb8, 0x1e, //
      0xbf, 0xb4, 0x41, 0x27, //
      0x5d, 0x52, 0x11, 0x98, //
      0x30, 0xae, 0xf1, 0xe5  //
  };

  const State16 expected = {
      0x04, 0xe0, 0x48, 0x28, //
      0x66, 0xcb, 0xf8, 0x06, //
      0x81, 0x19, 0xd3, 0x26, //
      0xe5, 0x9a, 0x7a, 0x4c  //
  };

  mixColumns(state.data());
  ExpectStateEq(state.data(), expected);
}

TEST(MixColumnsTest_1609, AllZeros_RemainsAllZeros_1609) {
  State16 state{};
  const State16 expected{}; // all zeros

  mixColumns(state.data());
  ExpectStateEq(state.data(), expected);
}

TEST(MixColumnsTest_1609, InPlaceOperation_UsesAndUpdatesSameBuffer_1609) {
  // This test checks observable "in-place" behavior:
  // - the function can be called on the same buffer (no separate output parameter)
  // - it deterministically transforms the state.
  State16 state1 = {
      0xd4, 0xe0, 0xb8, 0x1e, //
      0xbf, 0xb4, 0x41, 0x27, //
      0x5d, 0x52, 0x11, 0x98, //
      0x30, 0xae, 0xf1, 0xe5  //
  };
  State16 state2 = state1;

  mixColumns(state1.data());
  mixColumns(state2.data());

  // Same input -> same output.
  EXPECT_EQ(state1, state2);

  // And for this non-trivial input, output differs from input (sanity).
  EXPECT_NE(state1, State16({
                         0xd4, 0xe0, 0xb8, 0x1e, //
                         0xbf, 0xb4, 0x41, 0x27, //
                         0x5d, 0x52, 0x11, 0x98, //
                         0x30, 0xae, 0xf1, 0xe5  //
                     }));
}

TEST(MixColumnsTest_1609, DoesNotWriteOutside16Bytes_GuardBytesUnchanged_1609) {
  // Boundary/robustness: ensure only the 16-byte state region is modified.
  // We use guard bytes around the state and verify guards remain unchanged.
  constexpr size_t kGuardSize = 8;
  constexpr unsigned char kGuardPatternA = 0xA5;
  constexpr unsigned char kGuardPatternB = 0x5A;

  std::array<unsigned char, kGuardSize + 16 + kGuardSize> buf{};
  std::memset(buf.data(), kGuardPatternA, kGuardSize);
  std::memset(buf.data() + kGuardSize + 16, kGuardPatternB, kGuardSize);

  unsigned char *state = buf.data() + kGuardSize;

  // Fill the state with the known FIPS-197 input vector.
  const unsigned char input[16] = {
      0xd4, 0xe0, 0xb8, 0x1e, //
      0xbf, 0xb4, 0x41, 0x27, //
      0x5d, 0x52, 0x11, 0x98, //
      0x30, 0xae, 0xf1, 0xe5  //
  };
  std::memcpy(state, input, 16);

  mixColumns(state);

  // Guards unchanged.
  for (size_t i = 0; i < kGuardSize; ++i) {
    EXPECT_EQ(buf[i], kGuardPatternA) << "Left guard modified at " << i;
  }
  for (size_t i = 0; i < kGuardSize; ++i) {
    EXPECT_EQ(buf[kGuardSize + 16 + i], kGuardPatternB) << "Right guard modified at " << i;
  }
}

} // namespace