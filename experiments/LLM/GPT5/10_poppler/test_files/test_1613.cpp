// DecryptAesDecryptBlock_test_1613.cc
//
// Unit tests for aesDecryptBlock() in Decrypt.cc
// NOTE: aesDecryptBlock is a static function (internal linkage). To test it via its
// observable effects, we include Decrypt.cc into this test translation unit.
//
// Constraints honored:
// - Treat implementation as black box (no re-implementation of AES logic).
// - Verify only observable effects through the provided struct fields.

#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>

// Poppler headers
#include "Decrypt.h"

// Include the implementation file to access the static function under test.
#include "Decrypt.cc"

namespace {

class DecryptAesDecryptBlockTest_1613 : public ::testing::Test {
protected:
  static DecryptAESState MakeStateWithCbc(const std::array<unsigned char, 16> &cbc,
                                         const std::array<unsigned int, 44> &w) {
    DecryptAESState s;
    // Initialize public fields deterministically.
    std::memset(s.state, 0, sizeof(s.state));
    std::memset(s.buf, 0, sizeof(s.buf));
    s.paddingReached = false;
    s.bufIdx = -12345;

    for (int i = 0; i < 16; ++i) {
      s.cbc[i] = cbc[i];
    }
    for (int i = 0; i < 44; ++i) {
      s.w[i] = w[i];
    }
    return s;
  }

  static std::array<unsigned char, 16> BytesFromSeq(unsigned char start, unsigned char step) {
    std::array<unsigned char, 16> out{};
    unsigned char v = start;
    for (int i = 0; i < 16; ++i) {
      out[i] = v;
      v = static_cast<unsigned char>(v + step);
    }
    return out;
  }

  static std::array<unsigned char, 16> ToArray16(const unsigned char *p) {
    std::array<unsigned char, 16> out{};
    for (int i = 0; i < 16; ++i) out[i] = p[i];
    return out;
  }
};

TEST_F(DecryptAesDecryptBlockTest_1613, UpdatesCbcToInputAndResetsBufIdxWhenNotLast_1613) {
  const auto inArr = BytesFromSeq(0x10, 0x03);
  const auto cbc0 = BytesFromSeq(0xA0, 0x01);
  std::array<unsigned int, 44> w{};
  w.fill(0u);

  DecryptAESState s = MakeStateWithCbc(cbc0, w);

  aesDecryptBlock(&s, inArr.data(), /*last=*/false);

  // Observable behavior: CBC is updated to input bytes.
  for (int i = 0; i < 16; ++i) {
    EXPECT_EQ(s.cbc[i], inArr[i]) << "i=" << i;
  }

  // Observable behavior: bufIdx reset to 0 for non-last block.
  EXPECT_EQ(s.bufIdx, 0);
}

TEST_F(DecryptAesDecryptBlockTest_1613, XorRelationHoldsForDifferentInitialCbcWhenNotLast_1613) {
  // Property test independent of the AES core:
  // buf[i] = Dec(in)[i] XOR cbc_initial[i]
  // So for same key schedule and same input, (buf1 XOR buf2) == (cbc1 XOR cbc2).
  const auto inArr = BytesFromSeq(0x01, 0x07);
  const auto cbc1 = BytesFromSeq(0x00, 0x11);
  const auto cbc2 = BytesFromSeq(0xFF, 0xF3);

  std::array<unsigned int, 44> w{};
  // Use a deterministic non-zero pattern (still black-box; we don't derive anything).
  for (int i = 0; i < 44; ++i) {
    w[i] = static_cast<unsigned int>(0x01020304u + static_cast<unsigned int>(i));
  }

  DecryptAESState s1 = MakeStateWithCbc(cbc1, w);
  DecryptAESState s2 = MakeStateWithCbc(cbc2, w);

  aesDecryptBlock(&s1, inArr.data(), /*last=*/false);
  aesDecryptBlock(&s2, inArr.data(), /*last=*/false);

  for (int i = 0; i < 16; ++i) {
    const unsigned char lhs = static_cast<unsigned char>(s1.buf[i] ^ s2.buf[i]);
    const unsigned char rhs = static_cast<unsigned char>(cbc1[i] ^ cbc2[i]);
    EXPECT_EQ(lhs, rhs) << "i=" << i;
  }

  // Both should have updated CBC to the input.
  for (int i = 0; i < 16; ++i) {
    EXPECT_EQ(s1.cbc[i], inArr[i]) << "i=" << i;
    EXPECT_EQ(s2.cbc[i], inArr[i]) << "i=" << i;
  }

  EXPECT_EQ(s1.bufIdx, 0);
  EXPECT_EQ(s2.bufIdx, 0);
}

TEST_F(DecryptAesDecryptBlockTest_1613, LastBlockSetsBufIdxWithinValidRange_1613) {
  const auto inArr = BytesFromSeq(0x22, 0x05);
  const auto cbc0 = BytesFromSeq(0x33, 0x07);
  std::array<unsigned int, 44> w{};
  w.fill(0u);

  DecryptAESState s = MakeStateWithCbc(cbc0, w);

  aesDecryptBlock(&s, inArr.data(), /*last=*/true);

  // CBC should still update to input.
  for (int i = 0; i < 16; ++i) {
    EXPECT_EQ(s.cbc[i], inArr[i]) << "i=" << i;
  }

  // Observable contract from the code structure:
  // - bufIdx is set to n, where n is corrected to 16 if out of [1,16].
  // We can't force particular padding without relying on internals, so we only check bounds.
  EXPECT_GE(s.bufIdx, 1);
  EXPECT_LE(s.bufIdx, 16);
}

TEST_F(DecryptAesDecryptBlockTest_1613, HandlesAllZeroInputWithoutCrashingAndUpdatesCbc_1613) {
  std::array<unsigned char, 16> inArr{};
  inArr.fill(0x00);

  const auto cbc0 = BytesFromSeq(0x77, 0x09);
  std::array<unsigned int, 44> w{};
  w.fill(0u);

  DecryptAESState s = MakeStateWithCbc(cbc0, w);

  aesDecryptBlock(&s, inArr.data(), /*last=*/false);

  for (int i = 0; i < 16; ++i) {
    EXPECT_EQ(s.cbc[i], 0x00) << "i=" << i;
  }
  EXPECT_EQ(s.bufIdx, 0);
}

TEST_F(DecryptAesDecryptBlockTest_1613, HandlesAllOnesInputWithoutCrashingAndUpdatesCbc_1613) {
  std::array<unsigned char, 16> inArr{};
  inArr.fill(0xFF);

  const auto cbc0 = BytesFromSeq(0x10, 0x10);
  std::array<unsigned int, 44> w{};
  for (int i = 0; i < 44; ++i) {
    w[i] = 0xFFFFFFFFu;
  }

  DecryptAESState s = MakeStateWithCbc(cbc0, w);

  aesDecryptBlock(&s, inArr.data(), /*last=*/false);

  for (int i = 0; i < 16; ++i) {
    EXPECT_EQ(s.cbc[i], 0xFF) << "i=" << i;
  }
  EXPECT_EQ(s.bufIdx, 0);
}

}  // namespace