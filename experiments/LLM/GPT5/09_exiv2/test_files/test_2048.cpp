// ============================================================================
// Unit tests for MD5Update (./TestProjects/exiv2/xmpsdk/src/MD5.cpp)
// TEST_ID: 2048
// ============================================================================

#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <vector>

// Prefer including the real header from the codebase.
#include "MD5.h"

// Forward declaration for the function under test (implemented in MD5.cpp).
// (Matches the C-style signature shown in the prompt.)
extern void MD5Update(struct MD5_CTX* ctx, md5byte const* buf, unsigned len);

namespace {

class MD5UpdateTest_2048 : public ::testing::Test {
 protected:
  MD5_CTX ctx_{};

  static std::uint8_t* InBytes(MD5_CTX& c) {
    return reinterpret_cast<std::uint8_t*>(c.in);  // 16 * 4 = 64 bytes
  }
  static const std::uint8_t* InBytes(const MD5_CTX& c) {
    return reinterpret_cast<const std::uint8_t*>(c.in);
  }

  void SetUp() override {
    std::memset(&ctx_, 0, sizeof(ctx_));
  }

  static std::vector<std::uint8_t> MakePattern(std::size_t n, std::uint8_t seed) {
    std::vector<std::uint8_t> v(n);
    for (std::size_t i = 0; i < n; ++i) v[i] = static_cast<std::uint8_t>(seed + (i & 0x7F));
    return v;
  }
};

TEST_F(MD5UpdateTest_2048, UpdatesByteCount_NoCarry_2048) {
  ctx_.bytes[0] = 0;
  ctx_.bytes[1] = 0;

  auto input = MakePattern(10, 0x10);
  MD5Update(&ctx_, reinterpret_cast<const md5byte*>(input.data()), static_cast<unsigned>(input.size()));

  EXPECT_EQ(ctx_.bytes[0], 10u);
  EXPECT_EQ(ctx_.bytes[1], 0u);
}

TEST_F(MD5UpdateTest_2048, UpdatesByteCount_WithCarry_2048) {
  // Force a 32-bit wrap in bytes[0] so bytes[1] must increment.
  ctx_.bytes[0] = 0xFFFFFFF0u;
  ctx_.bytes[1] = 7u;

  const unsigned len = 0x30u;  // 48 -> 0xFFFFFFF0 + 0x30 wraps past 2^32
  auto input = MakePattern(len, 0x22);

  MD5Update(&ctx_, reinterpret_cast<const md5byte*>(input.data()), len);

  const std::uint32_t expected_low = static_cast<std::uint32_t>(0xFFFFFFF0u + len);  // wraps
  EXPECT_EQ(ctx_.bytes[0], expected_low);
  EXPECT_EQ(ctx_.bytes[1], 8u);  // incremented by carry
}

TEST_F(MD5UpdateTest_2048, CopiesToIn_WhenAllSpaceAvailableAndLenLessThan64_2048) {
  // bytes[0] old value = 0 -> space available t = 64, and t > len => early return.
  std::memset(InBytes(ctx_), 0xAA, 64);

  auto input = MakePattern(3, 0x40);
  MD5Update(&ctx_, reinterpret_cast<const md5byte*>(input.data()), static_cast<unsigned>(input.size()));

  // With bytes[0] starting at 0, the data should be copied at the beginning of ctx_.in.
  EXPECT_EQ(std::memcmp(InBytes(ctx_), input.data(), input.size()), 0);

  // Surrounding bytes remain as initially set (since only len bytes are copied).
  EXPECT_EQ(InBytes(ctx_)[3], 0xAA);

  EXPECT_EQ(ctx_.bytes[0], 3u);
  EXPECT_EQ(ctx_.bytes[1], 0u);
}

TEST_F(MD5UpdateTest_2048, CopiesToIn_WithNonZeroOffset_WhenLenFitsInRemainingSpace_2048) {
  // Choose bytes[0] so (bytes[0] & 0x3f) == 5 => remaining space t = 64 - 5 = 59.
  // With len=10, t > len => early return; copy begins at offset (64 - t) == 5.
  ctx_.bytes[0] = 5u;
  ctx_.bytes[1] = 0u;

  std::memset(InBytes(ctx_), 0xAA, 64);

  auto input = MakePattern(10, 0x55);
  MD5Update(&ctx_, reinterpret_cast<const md5byte*>(input.data()), static_cast<unsigned>(input.size()));

  const std::size_t offset = 5;
  ASSERT_LE(offset + input.size(), static_cast<std::size_t>(64));

  EXPECT_EQ(std::memcmp(InBytes(ctx_) + offset, input.data(), input.size()), 0);

  // Bytes before and after the copied segment remain unchanged (0xAA).
  EXPECT_EQ(InBytes(ctx_)[0], 0xAA);
  EXPECT_EQ(InBytes(ctx_)[offset - 1], 0xAA);
  EXPECT_EQ(InBytes(ctx_)[offset + input.size()], 0xAA);

  EXPECT_EQ(ctx_.bytes[0], 15u);  // 5 + 10
  EXPECT_EQ(ctx_.bytes[1], 0u);
}

TEST_F(MD5UpdateTest_2048, ExactFillThenRemainder_CopiesRemainderToStartOfIn_2048) {
  // bytes[0] old value = 60 -> (60 & 0x3f) == 60 -> remaining t = 4.
  // Provide len = 10: first 4 bytes fill, then remaining 6 should be copied to start.
  ctx_.bytes[0] = 60u;
  ctx_.bytes[1] = 0u;

  std::memset(InBytes(ctx_), 0xAA, 64);

  auto input = MakePattern(10, 0x70);
  MD5Update(&ctx_, reinterpret_cast<const md5byte*>(input.data()), static_cast<unsigned>(input.size()));

  // After processing, the "remaining bytes" are copied to ctx->in beginning.
  const std::size_t remainder = 6;
  EXPECT_EQ(std::memcmp(InBytes(ctx_), input.data() + 4, remainder), 0);

  EXPECT_EQ(ctx_.bytes[0], 70u);  // 60 + 10
  EXPECT_EQ(ctx_.bytes[1], 0u);
}

TEST_F(MD5UpdateTest_2048, MultipleFullChunksThenRemainder_RemainderCopiedToStartOfIn_2048) {
  // Start aligned.
  ctx_.bytes[0] = 0u;
  ctx_.bytes[1] = 0u;

  const std::size_t total = 64u * 2u + 7u;
  auto input = MakePattern(total, 0x11);

  std::memset(InBytes(ctx_), 0xAA, 64);

  MD5Update(&ctx_, reinterpret_cast<const md5byte*>(input.data()), static_cast<unsigned>(input.size()));

  // Final remainder (7 bytes) should be copied into ctx->in at the beginning.
  const std::size_t rem = 7;
  EXPECT_EQ(std::memcmp(InBytes(ctx_), input.data() + (total - rem), rem), 0);

  EXPECT_EQ(ctx_.bytes[0], static_cast<UWORD32>(total));
  EXPECT_EQ(ctx_.bytes[1], 0u);
}

}  // namespace