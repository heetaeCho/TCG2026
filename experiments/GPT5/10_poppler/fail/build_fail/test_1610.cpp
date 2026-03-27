// Decrypt_invMixColumns_test_1610.cc
#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <cstring>

// NOTE:
// invMixColumns is a static inline function in Decrypt.cc (not exposed via headers).
// To test it as a black-box without re-implementing internals, we include the .cc
// so the function is available in this translation unit.
//
// If your build can't find this include, adjust the relative path accordingly.
#include "Decrypt.cc"

namespace {

using State16 = std::array<unsigned char, 16>;

static State16 MakeState(const std::initializer_list<uint8_t> bytes) {
  State16 s{};
  size_t i = 0;
  for (auto b : bytes) {
    if (i >= s.size()) break;
    s[i++] = static_cast<unsigned char>(b);
  }
  return s;
}

TEST(InvMixColumnsTest_1610, ZeroStateRemainsZero_1610) {
  State16 state{};
  const State16 original = state;

  invMixColumns(state.data());

  EXPECT_EQ(state, original);
}

TEST(InvMixColumnsTest_1610, KnownVectorFromFIPS197_MixColumnsInverse_1610) {
  // FIPS-197 (AES) MixColumns example (commonly cited):
  // Before MixColumns (state matrix):
  //   d4 e0 b8 1e
  //   bf b4 41 27
  //   5d 52 11 98
  //   30 ae f1 e5
  // After MixColumns:
  //   04 e0 48 28
  //   66 cb f8 06
  //   81 19 d3 26
  //   e5 9a 7a 4c
  //
  // This implementation stores the AES state column-major:
  // indices [c, 4+c, 8+c, 12+c] form column c.
  //
  // So "After MixColumns" in column-major order:
  // col0: 04 66 81 e5
  // col1: e0 cb 19 9a
  // col2: 48 f8 d3 7a
  // col3: 28 06 26 4c
  const State16 afterMix = MakeState({
      0x04, 0xE0, 0x48, 0x28,
      0x66, 0xCB, 0xF8, 0x06,
      0x81, 0x19, 0xD3, 0x26,
      0xE5, 0x9A, 0x7A, 0x4C,
  });

  // Expected "Before MixColumns" in column-major order:
  // col0: d4 bf 5d 30
  // col1: e0 b4 52 ae
  // col2: b8 41 11 f1
  // col3: 1e 27 98 e5
  const State16 beforeMixExpected = MakeState({
      0xD4, 0xE0, 0xB8, 0x1E,
      0xBF, 0xB4, 0x41, 0x27,
      0x5D, 0x52, 0x11, 0x98,
      0x30, 0xAE, 0xF1, 0xE5,
  });

  State16 state = afterMix;
  invMixColumns(state.data());

  EXPECT_EQ(state, beforeMixExpected);
}

TEST(InvMixColumnsTest_1610, SingleColumnKnownVector_OthersZero_1610) {
  // Use the well-known single-column pair:
  // MixColumns(d4 bf 5d 30) = 04 66 81 e5
  // Therefore InvMixColumns(04 66 81 e5) = d4 bf 5d 30
  //
  // Put (04 66 81 e5) in column 0; other columns are zero.
  State16 state{};
  state[0]  = 0x04;
  state[4]  = 0x66;
  state[8]  = 0x81;
  state[12] = 0xE5;

  invMixColumns(state.data());

  EXPECT_EQ(state[0],  static_cast<unsigned char>(0xD4));
  EXPECT_EQ(state[4],  static_cast<unsigned char>(0xBF));
  EXPECT_EQ(state[8],  static_cast<unsigned char>(0x5D));
  EXPECT_EQ(state[12], static_cast<unsigned char>(0x30));

  // Other columns should remain the inverse transform of zeros (which is still zeros).
  for (int c = 1; c < 4; ++c) {
    EXPECT_EQ(state[c],      static_cast<unsigned char>(0x00));
    EXPECT_EQ(state[4 + c],  static_cast<unsigned char>(0x00));
    EXPECT_EQ(state[8 + c],  static_cast<unsigned char>(0x00));
    EXPECT_EQ(state[12 + c], static_cast<unsigned char>(0x00));
  }
}

TEST(InvMixColumnsTest_1610, DoesNotWriteOutside16Bytes_1610) {
  // Boundary-style test: ensure the function doesn't write out of bounds.
  alignas(16) unsigned char buffer[16 + 2];
  buffer[0] = 0xA5;               // left guard
  buffer[17] = 0x5A;              // right guard

  // Fill state bytes with a non-trivial pattern.
  for (int i = 0; i < 16; ++i) buffer[1 + i] = static_cast<unsigned char>(i * 7);

  invMixColumns(&buffer[1]);

  EXPECT_EQ(buffer[0], static_cast<unsigned char>(0xA5));
  EXPECT_EQ(buffer[17], static_cast<unsigned char>(0x5A));
}

}  // namespace