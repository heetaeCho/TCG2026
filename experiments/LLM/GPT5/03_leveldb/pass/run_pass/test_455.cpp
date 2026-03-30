// File: crc32c_extend_test.cc
#include <gtest/gtest.h>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

namespace leveldb {
namespace crc32c {
// Forward declaration based on the provided interface.
uint32_t Extend(uint32_t crc, const char* data, size_t n);
}  // namespace crc32c
}  // namespace leveldb

using leveldb::crc32c::Extend;

// A small helper to compute CRC in one shot vs. in pieces and compare.
// (Behavioral property: Extend(crc(a), b) == crc(a+b) with crc(0,·) as base)
static uint32_t CrcOf(const std::string& s) {
  return Extend(/*crc=*/0, s.data(), s.size());
}

class CRC32CExtendTest_455 : public ::testing::Test {};

// --- Normal operation ---

TEST_F(CRC32CExtendTest_455, MatchesKnownVector123456789_455) {
  // Standard CRC32C test vector for "123456789"
  const std::string s = "123456789";
  // Expected CRC32C("123456789") = 0xE3069283
  EXPECT_EQ(0xE3069283u, CrcOf(s));
}

TEST_F(CRC32CExtendTest_455, ConcatenationProperty_SimpleSplit_455) {
  const std::string a = "hello ";
  const std::string b = "world";
  const std::string ab = a + b;

  const uint32_t crc_a = CrcOf(a);
  const uint32_t crc_ab = CrcOf(ab);
  const uint32_t crc_a_b = Extend(crc_a, b.data(), b.size());

  EXPECT_EQ(crc_ab, crc_a_b);
}

TEST_F(CRC32CExtendTest_455, MultipleChunksEquivalentToOneShot_455) {
  const std::string data = "The quick brown fox jumps over the lazy dog.";
  // Split into irregular chunks to exercise various code paths.
  const std::string c1 = data.substr(0, 1);
  const std::string c2 = data.substr(1, 3);
  const std::string c3 = data.substr(4, 7);
  const std::string c4 = data.substr(11, 5);
  const std::string c5 = data.substr(16);  // rest

  uint32_t crc = 0;
  crc = Extend(crc, c1.data(), c1.size());
  crc = Extend(crc, c2.data(), c2.size());
  crc = Extend(crc, c3.data(), c3.size());
  crc = Extend(crc, c4.data(), c4.size());
  crc = Extend(crc, c5.data(), c5.size());

  EXPECT_EQ(CrcOf(data), crc);
}

// --- Boundary conditions ---

TEST_F(CRC32CExtendTest_455, EmptyInputKeepsCRCUnchanged_455) {
  const uint32_t start = 0xDEADBEEFu;  // arbitrary seed
  EXPECT_EQ(start, Extend(start, /*data=*/"", /*n=*/0));
}

TEST_F(CRC32CExtendTest_455, EmptyThenDataEqualsDataOnly_455) {
  const std::string s = "abc";
  uint32_t crc = 0;
  crc = Extend(crc, "", 0);                // empty
  crc = Extend(crc, s.data(), s.size());   // data
  EXPECT_EQ(CrcOf(s), crc);
}

TEST_F(CRC32CExtendTest_455, SmallSizes_1_2_3_4_7_16_31_32_455) {
  const std::string base =
      "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  const std::vector<size_t> sizes = {1, 2, 3, 4, 7, 16, 31, 32};

  for (size_t n : sizes) {
    const std::string s = base.substr(0, n);
    // Compare one-shot vs. two-step split at an odd offset.
    const size_t split = (n > 1) ? 1 : 0;
    const uint32_t crc1 = CrcOf(s);
    uint32_t crc2 = Extend(0, s.data(), split);
    crc2 = Extend(crc2, s.data() + split, n - split);
    EXPECT_EQ(crc1, crc2) << "mismatch for size " << n;
  }
}

TEST_F(CRC32CExtendTest_455, UnalignedStartPointer_455) {
  // Create a buffer with a deliberate 1-byte offset to check unaligned pointer handling.
  const std::string payload = "unaligned-payload-for-crc32c";
  const std::string padded = std::string("\x00", 1) + payload;  // leading pad
  const char* p = padded.data();
  const char* unaligned_ptr = p + 1;  // points exactly to payload start

  const uint32_t crc_aligned = CrcOf(payload);
  const uint32_t crc_unaligned = Extend(0, unaligned_ptr, payload.size());
  EXPECT_EQ(crc_aligned, crc_unaligned);
}

// --- Exceptional / error-like observable cases (where applicable) ---

TEST_F(CRC32CExtendTest_455, DifferentInputsYieldDifferentCRCs_455) {
  const std::string s1 = "same-prefixX";
  const std::string s2 = "same-prefixY";
  const uint32_t c1 = CrcOf(s1);
  const uint32_t c2 = CrcOf(s2);
  // Not a strict guarantee for all strings, but with these distinct inputs the CRCs should differ.
  EXPECT_NE(c1, c2);
}

// --- Larger data & stress-ish behavior ---

TEST_F(CRC32CExtendTest_455, LargeBufferChunkingConsistency_455) {
  // 1 MiB of 'a'
  const size_t N = 1 << 20;
  std::string big(N, 'a');

  // One-shot
  const uint32_t whole = CrcOf(big);

  // Chunked: 64 KiB pieces
  uint32_t chunked = 0;
  const size_t kChunk = 64 << 10;
  for (size_t off = 0; off < N; off += kChunk) {
    const size_t n = std::min(kChunk, N - off);
    chunked = Extend(chunked, big.data() + off, n);
  }

  EXPECT_EQ(whole, chunked);
}

TEST_F(CRC32CExtendTest_455, ExtendFromNonZeroSeedMatchesConcatenation_455) {
  const std::string a = "seed-portion";
  const std::string b = "follow-up-portion";
  const uint32_t seed = CrcOf(a);

  // Extend from seed with b should match CRC of (a+b).
  const uint32_t extended = Extend(seed, b.data(), b.size());
  const uint32_t together = CrcOf(a + b);
  EXPECT_EQ(together, extended);
}
