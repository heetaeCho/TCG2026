// Decrypt_sha256HashBlock_test_1634.cc
#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <cstring>

// NOTE:
// sha256HashBlock() is declared `static` in Decrypt.cc (internal linkage).
// For black-box testing via its observable outputs, we include the implementation
// file so the test translation unit can call it.
//
// This pattern assumes Decrypt.cc is NOT also compiled/linked separately into the
// same test binary (otherwise you may get duplicate symbol/link issues).
#include "Decrypt.cc"

namespace {

class Sha256HashBlockTest_1634 : public ::testing::Test {
protected:
  static std::array<unsigned int, 8> Sha256IV() {
    // SHA-256 initial hash values (FIPS 180-4).
    return {0x6a09e667U, 0xbb67ae85U, 0x3c6ef372U, 0xa54ff53aU,
            0x510e527fU, 0x9b05688cU, 0x1f83d9abU, 0x5be0cd19U};
  }
};

TEST_F(Sha256HashBlockTest_1634, HashesEmptyMessagePaddedSingleBlock_1634) {
  // Build the single padded 512-bit block for message "" (0 bytes):
  // 0x80, then zeros, then 64-bit length (0).
  std::array<unsigned char, 64> blk{};
  blk[0] = 0x80;
  // last 8 bytes already zero for length=0

  auto blk_copy = blk;

  auto H = Sha256IV();
  sha256HashBlock(blk.data(), H.data());

  // SHA-256("") =
  // e3b0c442 98fc1c14 9afbf4c8 996fb924 27ae41e4 649b934c a495991b 7852b855
  const std::array<unsigned int, 8> expected = {
      0xe3b0c442U, 0x98fc1c14U, 0x9afbf4c8U, 0x996fb924U,
      0x27ae41e4U, 0x649b934cU, 0xa495991bU, 0x7852b855U};

  EXPECT_EQ(H, expected);

  // Input block should not be modified.
  EXPECT_EQ(0, std::memcmp(blk.data(), blk_copy.data(), blk.size()));
}

TEST_F(Sha256HashBlockTest_1634, HashesAbcMessagePaddedSingleBlock_1634) {
  // Build the single padded 512-bit block for message "abc" (3 bytes):
  // 61 62 63 80 00..00 [len=24 bits]
  std::array<unsigned char, 64> blk{};
  blk[0] = 0x61;
  blk[1] = 0x62;
  blk[2] = 0x63;
  blk[3] = 0x80;
  // 64-bit big-endian length in bits (24 = 0x18)
  blk[63] = 0x18;

  auto blk_copy = blk;

  auto H = Sha256IV();
  sha256HashBlock(blk.data(), H.data());

  // SHA-256("abc") =
  // ba7816bf 8f01cfea 414140de 5dae2223 b00361a3 96177a9c b410ff61 f20015ad
  const std::array<unsigned int, 8> expected = {
      0xba7816bfU, 0x8f01cfeaU, 0x414140deU, 0x5dae2223U,
      0xb00361a3U, 0x96177a9cU, 0xb410ff61U, 0xf20015adU};

  EXPECT_EQ(H, expected);

  // Input block should not be modified.
  EXPECT_EQ(0, std::memcmp(blk.data(), blk_copy.data(), blk.size()));
}

TEST_F(Sha256HashBlockTest_1634, DeterministicForSameInputAndInitialState_1634) {
  // Use "abc" padded block again.
  std::array<unsigned char, 64> blk{};
  blk[0] = 0x61;
  blk[1] = 0x62;
  blk[2] = 0x63;
  blk[3] = 0x80;
  blk[63] = 0x18;

  auto H1 = Sha256IV();
  auto H2 = Sha256IV();

  sha256HashBlock(blk.data(), H1.data());
  sha256HashBlock(blk.data(), H2.data());

  EXPECT_EQ(H1, H2);
}

TEST_F(Sha256HashBlockTest_1634, DifferentInitialStateProducesDifferentOutput_1634) {
  // Boundary-style check: observable dependence on the provided initial state.
  std::array<unsigned char, 64> blk{};
  blk[0] = 0x80;  // empty-message padded block

  auto H_ref = Sha256IV();
  auto H_alt = Sha256IV();
  // Flip one bit in the initial state.
  H_alt[0] ^= 0x00000001U;

  sha256HashBlock(blk.data(), H_ref.data());
  sha256HashBlock(blk.data(), H_alt.data());

  EXPECT_NE(H_ref, H_alt);
}

} // namespace