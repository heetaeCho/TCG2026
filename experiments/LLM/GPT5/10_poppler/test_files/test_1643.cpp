// Sha512HashBlockTest_1643.cc
#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <cstring>

// NOTE:
// sha512HashBlock is a file-local (static) function in Decrypt.cc.
// To test it as a black box via its signature/observable outputs, we include the
// implementation file so the symbol is available in this translation unit.
#include "Decrypt.cc"

namespace {

constexpr std::array<uint64_t, 8> kSha512IV = {
    0x6a09e667f3bcc908ULL, 0xbb67ae8584caa73bULL, 0x3c6ef372fe94f82bULL,
    0xa54ff53a5f1d36f1ULL, 0x510e527fade682d1ULL, 0x9b05688c2b3e6c1fULL,
    0x1f83d9abfb41bd6bULL, 0x5be0cd19137e2179ULL,
};

// One-block SHA-512 padding for empty message.
constexpr std::array<unsigned char, 128> kBlkEmpty = []() {
  std::array<unsigned char, 128> b{};
  b[0] = 0x80; // 1 bit then zeros; length is 0, stored in last 16 bytes (all zero).
  return b;
}();

// One-block SHA-512 padding for "abc" (0x61 0x62 0x63), bit-length = 24 (0x18).
constexpr std::array<unsigned char, 128> kBlkAbc = []() {
  std::array<unsigned char, 128> b{};
  b[0] = 0x61;
  b[1] = 0x62;
  b[2] = 0x63;
  b[3] = 0x80;
  // Last 16 bytes are 128-bit length; high 64 bits = 0, low 64 bits = 24 (0x18).
  b[127] = 0x18;
  return b;
}();

// Incrementing bytes block: 0x00,0x01,...,0x7f
constexpr std::array<unsigned char, 128> kBlkInc = []() {
  std::array<unsigned char, 128> b{};
  for (size_t i = 0; i < b.size(); ++i) b[i] = static_cast<unsigned char>(i);
  return b;
}();

// Expected results (observable outputs) for sha512HashBlock given the inputs.
// These are known-good reference values (SHA-512 test vectors / precomputed states).
constexpr std::array<uint64_t, 8> kExpectedEmptyDigestState = {
    0xcf83e1357eefb8bdULL, 0xf1542850d66d8007ULL, 0xd620e4050b5715dcULL,
    0x83f4a921d36ce9ceULL, 0x47d0d13c5d85f2b0ULL, 0xff8318d2877eec2fULL,
    0x63b931bd47417a81ULL, 0xa538327af927da3eULL,
};

constexpr std::array<uint64_t, 8> kExpectedAbcDigestState = {
    0xddaf35a193617abaULL, 0xcc417349ae204131ULL, 0x12e6fa4e89a97ea2ULL,
    0x0a9eeee64b55d39aULL, 0x2192992a274fc1a8ULL, 0x36ba3c23a3feebbdULL,
    0x454d4423643ce80eULL, 0x2a9ac94fa54ca49fULL,
};

constexpr std::array<uint64_t, 8> kExpectedAbcWithModifiedIV = {
    0xdad410ae270d7a2dULL, 0x538c5834d4141bdbULL, 0x09b61558a6159928ULL,
    0x2587c60746cb0961ULL, 0xb20ec379ad3a37d0ULL, 0xd3e23db51950cafbULL,
    0x324dd8be5411ffc1ULL, 0x14e6eccf853ff032ULL,
};

constexpr std::array<uint64_t, 8> kExpectedIncBlockState = {
    0x8e03953cd57cd687ULL, 0x9321270afa70c582ULL, 0x7bb5b69be59a8f01ULL,
    0x30147e94f2aedf7bULL, 0xdc01c56c92343ca8ULL, 0xbd837bb7f0208f5aULL,
    0x23e155694516b6f1ULL, 0x47099d491a30b151ULL,
};

class Sha512HashBlockTest_1643 : public ::testing::Test {
 protected:
  static std::array<uint64_t, 8> Run(const std::array<unsigned char, 128> &blk,
                                     const std::array<uint64_t, 8> &initialH) {
    std::array<uint64_t, 8> H = initialH;
    sha512HashBlock(blk.data(), H.data());
    return H;
  }
};

} // namespace

TEST_F(Sha512HashBlockTest_1643, EmptyMessageOneBlockMatchesKnownDigestState_1643) {
  const auto out = Run(kBlkEmpty, kSha512IV);
  EXPECT_EQ(out, kExpectedEmptyDigestState);
}

TEST_F(Sha512HashBlockTest_1643, AbcMessageOneBlockMatchesKnownDigestState_1643) {
  const auto out = Run(kBlkAbc, kSha512IV);
  EXPECT_EQ(out, kExpectedAbcDigestState);
}

TEST_F(Sha512HashBlockTest_1643, DeterministicForSameInputs_1643) {
  const auto out1 = Run(kBlkAbc, kSha512IV);
  const auto out2 = Run(kBlkAbc, kSha512IV);
  EXPECT_EQ(out1, out2);
  EXPECT_EQ(out1, kExpectedAbcDigestState);
}

TEST_F(Sha512HashBlockTest_1643, DifferentBlocksProduceDifferentStatesFromSameIV_1643) {
  const auto outEmpty = Run(kBlkEmpty, kSha512IV);
  const auto outAbc = Run(kBlkAbc, kSha512IV);
  EXPECT_NE(outEmpty, outAbc);
  EXPECT_EQ(outEmpty, kExpectedEmptyDigestState);
  EXPECT_EQ(outAbc, kExpectedAbcDigestState);
}

TEST_F(Sha512HashBlockTest_1643, DifferentInitialStateAffectsOutput_1643) {
  auto modifiedIV = kSha512IV;
  modifiedIV[0] = modifiedIV[0] + 1ULL;

  const auto out = Run(kBlkAbc, modifiedIV);
  EXPECT_EQ(out, kExpectedAbcWithModifiedIV);

  // Also confirm it differs from the standard IV result for the same block.
  const auto outStandard = Run(kBlkAbc, kSha512IV);
  EXPECT_NE(out, outStandard);
}

TEST_F(Sha512HashBlockTest_1643, IncrementingBlockMatchesPrecomputedState_1643) {
  const auto out = Run(kBlkInc, kSha512IV);
  EXPECT_EQ(out, kExpectedIncBlockState);
}

TEST_F(Sha512HashBlockTest_1643, ModifiesStateInPlace_1643) {
  std::array<uint64_t, 8> H = kSha512IV;
  const auto original = H;

  sha512HashBlock(kBlkAbc.data(), H.data());

  EXPECT_NE(H, original);
  EXPECT_EQ(H, kExpectedAbcDigestState);
}