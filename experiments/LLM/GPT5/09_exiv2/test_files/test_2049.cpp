// File: test_md5final_2049.cpp
//
// Unit tests for MD5Final (./TestProjects/exiv2/xmpsdk/src/MD5.cpp)
// Constraints respected:
//  - Treat MD5Final as a black box.
//  - Test only observable behavior via public interface and external interactions.
//  - External collaborators (byteSwap / MD5Transform) are provided as test doubles here.

#include <gtest/gtest.h>

#include <array>
#include <cstdint>
#include <cstring>
#include <vector>

// ---- Minimal type/struct definitions (from provided snippet) ----
using UWORD32 = std::uint32_t;
using md5byte = std::uint8_t;

struct MD5_CTX {
  UWORD32 buf[4];
  UWORD32 bytes[2];
  UWORD32 in[16];
};

// ---- External collaborators used by MD5Final (test doubles) ----
namespace {

struct ByteSwapCall {
  const UWORD32* ptr;
  unsigned words;
};

struct TransformCall {
  const UWORD32* buf_ptr;
  const UWORD32* in_ptr;
  std::array<UWORD32, 16> in_snapshot;
};

static std::vector<ByteSwapCall> g_byteSwapCalls;
static std::vector<TransformCall> g_transformCalls;

// Make MD5Transform write deterministic, test-observable output into buf.
// (This is an external collaborator, not internal logic of MD5Final.)
static void WriteDeterministicBuf(UWORD32* buf, std::size_t call_index) {
  // Any stable pattern is fine.
  buf[0] = static_cast<UWORD32>(0x11111111u + static_cast<UWORD32>(call_index));
  buf[1] = static_cast<UWORD32>(0x22222222u + static_cast<UWORD32>(call_index));
  buf[2] = static_cast<UWORD32>(0x33333333u + static_cast<UWORD32>(call_index));
  buf[3] = static_cast<UWORD32>(0x44444444u + static_cast<UWORD32>(call_index));
}

}  // namespace

extern "C" {

// Signature inferred from usage in MD5Final: byteSwap(ctx->in, 16), etc.
void byteSwap(UWORD32* buf, unsigned words) {
  g_byteSwapCalls.push_back(ByteSwapCall{buf, words});
  // No-op is sufficient for these tests; we validate calls and downstream effects.
}

// Signature inferred from usage in MD5Final: MD5Transform(ctx->buf, ctx->in)
void MD5Transform(UWORD32 buf[4], const UWORD32 in[16]) {
  TransformCall call{};
  call.buf_ptr = buf;
  call.in_ptr = in;
  std::memcpy(call.in_snapshot.data(), in, 16 * sizeof(UWORD32));
  g_transformCalls.push_back(call);

  WriteDeterministicBuf(buf, g_transformCalls.size() - 1);
}

}  // extern "C"

// ---- Function under test declaration ----
extern "C" void MD5Final(md5byte digest[16], struct MD5_CTX* ctx);

// ---- Test fixture ----
class MD5FinalTest_2049 : public ::testing::Test {
 protected:
  void SetUp() override {
    g_byteSwapCalls.clear();
    g_transformCalls.clear();
  }

  static void FillSentinels(MD5_CTX& ctx) {
    for (auto& w : ctx.buf) w = 0xAAAAAAAAu;
    for (auto& w : ctx.bytes) w = 0xBBBBBBBBu;
    for (auto& w : ctx.in) w = 0xCCCCCCCCu;
  }

  static bool AllZero(const MD5_CTX& ctx) {
    for (auto w : ctx.buf)
      if (w != 0) return false;
    for (auto w : ctx.bytes)
      if (w != 0) return false;
    for (auto w : ctx.in)
      if (w != 0) return false;
    return true;
  }

  static std::array<UWORD32, 2> ExpectedLengthWords(UWORD32 bytes0, UWORD32 bytes1) {
    // From MD5Final:
    // ctx->in[14] = ctx->bytes[0] << 3;
    // ctx->in[15] = ctx->bytes[1] << 3 | ctx->bytes[0] >> 29;
    return {static_cast<UWORD32>(bytes0 << 3),
            static_cast<UWORD32>((bytes1 << 3) | (bytes0 >> 29))};
  }
};

// --- Tests ---

TEST_F(MD5FinalTest_2049, Final_NormalCount0_CallsCollaboratorsAndSetsLengthWords_2049) {
  MD5_CTX ctx{};
  FillSentinels(ctx);

  // Choose bytes0 with low 6 bits = 0 (count=0), and with bits for >>29 contribution.
  const UWORD32 bytes0 = 0x20000000u;  // low6=0, bytes0>>29 == 1
  const UWORD32 bytes1 = 0x00000002u;  // bytes1<<3 == 0x10
  ctx.bytes[0] = bytes0;
  ctx.bytes[1] = bytes1;

  std::array<md5byte, 16> digest{};
  std::memset(digest.data(), 0xEE, digest.size());

  MD5Final(digest.data(), &ctx);

  // Branch expectation: count=0 => no extra block => MD5Transform called once.
  ASSERT_EQ(g_transformCalls.size(), 1u);
  ASSERT_EQ(g_byteSwapCalls.size(), 2u);

  // byteSwap expected: (ctx->in,14) then (ctx->buf,4)
  EXPECT_EQ(g_byteSwapCalls[0].ptr, static_cast<const UWORD32*>(ctx.in));  // pointer value before zeroing is same address
  EXPECT_EQ(g_byteSwapCalls[0].words, 14u);
  EXPECT_EQ(g_byteSwapCalls[1].ptr, static_cast<const UWORD32*>(ctx.buf));
  EXPECT_EQ(g_byteSwapCalls[1].words, 4u);

  // Last transform should see in[14], in[15] set to length words.
  const auto expected = ExpectedLengthWords(bytes0, bytes1);
  EXPECT_EQ(g_transformCalls.back().in_snapshot[14], expected[0]);
  EXPECT_EQ(g_transformCalls.back().in_snapshot[15], expected[1]);

  // Digest should reflect the deterministic buf written by our MD5Transform stub.
  std::array<UWORD32, 4> out_words{};
  std::memcpy(out_words.data(), digest.data(), 16);
  EXPECT_EQ(out_words[0], 0x11111111u);  // call_index=0
  EXPECT_EQ(out_words[1], 0x22222222u);
  EXPECT_EQ(out_words[2], 0x33333333u);
  EXPECT_EQ(out_words[3], 0x44444444u);

  // ctx should be cleared by MD5Final.
  EXPECT_TRUE(AllZero(ctx));
}

TEST_F(MD5FinalTest_2049, Final_BoundaryCount55_NoExtraBlock_2049) {
  MD5_CTX ctx{};
  FillSentinels(ctx);

  // low6 = 55 triggers boundary where padding "count" becomes 0 (no extra block).
  const UWORD32 bytes0 = 0x20000000u + 55u;
  const UWORD32 bytes1 = 0x00000000u;
  ctx.bytes[0] = bytes0;
  ctx.bytes[1] = bytes1;

  std::array<md5byte, 16> digest{};
  MD5Final(digest.data(), &ctx);

  ASSERT_EQ(g_transformCalls.size(), 1u);
  ASSERT_EQ(g_byteSwapCalls.size(), 2u);

  // Ensure it did not call byteSwap(in,16) (only happens in extra-block path).
  EXPECT_EQ(g_byteSwapCalls[0].words, 14u);
  EXPECT_EQ(g_byteSwapCalls[1].words, 4u);

  const auto expected = ExpectedLengthWords(bytes0, bytes1);
  EXPECT_EQ(g_transformCalls.back().in_snapshot[14], expected[0]);
  EXPECT_EQ(g_transformCalls.back().in_snapshot[15], expected[1]);

  EXPECT_TRUE(AllZero(ctx));
}

TEST_F(MD5FinalTest_2049, Final_BoundaryCount56_TriggersExtraBlockAndTwoTransforms_2049) {
  MD5_CTX ctx{};
  FillSentinels(ctx);

  // low6 = 56 triggers extra-block path (count < 0).
  const UWORD32 bytes0 = 0x20000000u + 56u;
  const UWORD32 bytes1 = 0x00000002u;
  ctx.bytes[0] = bytes0;
  ctx.bytes[1] = bytes1;

  std::array<md5byte, 16> digest{};
  MD5Final(digest.data(), &ctx);

  // Extra block should cause two MD5Transform calls.
  ASSERT_EQ(g_transformCalls.size(), 2u);

  // Extra-block path should call byteSwap(in,16), then byteSwap(in,14), then byteSwap(buf,4).
  ASSERT_EQ(g_byteSwapCalls.size(), 3u);
  EXPECT_EQ(g_byteSwapCalls[0].words, 16u);
  EXPECT_EQ(g_byteSwapCalls[1].words, 14u);
  EXPECT_EQ(g_byteSwapCalls[2].words, 4u);

  // Length words should be set for the final transform (call #2).
  const auto expected = ExpectedLengthWords(bytes0, bytes1);
  EXPECT_EQ(g_transformCalls.back().in_snapshot[14], expected[0]);
  EXPECT_EQ(g_transformCalls.back().in_snapshot[15], expected[1]);

  // Digest should reflect deterministic buf from *second* transform call (call_index=1).
  std::array<UWORD32, 4> out_words{};
  std::memcpy(out_words.data(), digest.data(), 16);
  EXPECT_EQ(out_words[0], 0x11111112u);
  EXPECT_EQ(out_words[1], 0x22222223u);
  EXPECT_EQ(out_words[2], 0x33333334u);
  EXPECT_EQ(out_words[3], 0x44444445u);

  EXPECT_TRUE(AllZero(ctx));
}

TEST_F(MD5FinalTest_2049, Final_WritesDigestEvenWhenInputInHasSentinels_2049) {
  MD5_CTX ctx{};
  FillSentinels(ctx);

  // Any non-crashing input; choose count=0 path for simplicity.
  ctx.bytes[0] = 0u;
  ctx.bytes[1] = 0u;

  std::array<md5byte, 16> digest{};
  std::memset(digest.data(), 0x00, digest.size());

  MD5Final(digest.data(), &ctx);

  // Digest should not remain all-zero due to our MD5Transform stub.
  bool all_zero = true;
  for (auto b : digest) {
    if (b != 0) {
      all_zero = false;
      break;
    }
  }
  EXPECT_FALSE(all_zero);

  EXPECT_TRUE(AllZero(ctx));
}