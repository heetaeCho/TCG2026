// File: bytemapbuilder_build_test.cc
#include <gtest/gtest.h>
#include <cstdint>
#include <vector>

// Assume headers are available like this (adjust include paths as needed)
#include "re2/prog.cc"        // or the appropriate header that declares re2::ByteMapBuilder

using re2::ByteMapBuilder;

class ByteMapBuilderBuildTest_410 : public ::testing::Test {
protected:
  static constexpr uint8_t kLeftCanary  = 0xA5;
  static constexpr uint8_t kRightCanary = 0x5A;

  // Utility that calls Build into a caller-provided 256-byte view situated
  // between two 1-byte canaries. Returns the produced bytemap_range.
  static int RunBuild(ByteMapBuilder& b, uint8_t* middle256) {
    int range_out = -123456;  // sentinel to ensure the function writes it
    b.Build(middle256, &range_out);
    return range_out;
  }

  // Allocates a buffer with 1-byte canary on both sides and returns a tuple of:
  // (whole storage, pointer to middle[0], pointer to left canary, pointer to right canary)
  static std::tuple<std::vector<uint8_t>, uint8_t*, uint8_t*, uint8_t*>
  MakeGuardedBuffer(uint8_t initial_fill) {
    std::vector<uint8_t> storage(256 + 2, initial_fill);
    storage.front() = kLeftCanary;
    storage.back()  = kRightCanary;
    uint8_t* mid    = storage.data() + 1; // 256-byte region starts here
    return {std::move(storage), mid, storage.data(), storage.data() + 257};
  }
};

// --- Tests ---

// Verifies Build writes within the 256-byte output region and does not clobber guard bytes.
TEST_F(ByteMapBuilderBuildTest_410, WritesExactlyWithin256Bytes_410) {
  ByteMapBuilder b;

  // Optional: exercise public setup API without assuming any internal logic.
  // These ranges are arbitrary and only serve to define some observable configuration.
  b.Mark(10, 20);
  b.Mark(100, 150);
  b.Merge();

  auto [buf, mid, left_canary, right_canary] = MakeGuardedBuffer(/*initial_fill=*/0xEE);

  // Keep copies of canaries to compare after Build
  uint8_t left_before  = *left_canary;
  uint8_t right_before = *right_canary;

  int out_range = RunBuild(b, mid);

  // Guard bytes must remain intact.
  EXPECT_EQ(left_before,  *left_canary);
  EXPECT_EQ(right_before, *right_canary);

  // bytemap_range must be written (not the sentinel).
  EXPECT_NE(out_range, -123456);

  // Sanity: all 256 bytes are addressable; read them to ensure no UB/crash.
  // (We don't assert specific values since logic is a black box.)
  volatile uint8_t sum = 0;
  for (int i = 0; i < 256; ++i) sum ^= mid[i];
  (void)sum;
}

// Verifies Build is deterministic with respect to the same public configuration,
// and is independent of the prior contents of the output buffer.
TEST_F(ByteMapBuilderBuildTest_410, DeterministicAndOverwritesOutput_410) {
  ByteMapBuilder b;

  // Define some observable configuration via the public API.
  b.Mark(0, 0);
  b.Mark(255, 255);
  b.Mark(42, 200);
  b.Merge();

  // First run with buffer prefilled with 0x00
  auto [buf0, mid0, l0, r0] = MakeGuardedBuffer(/*initial_fill=*/0x00);
  int range0 = RunBuild(b, mid0);

  // Second run with buffer prefilled with 0xFF (should not affect results)
  auto [buf1, mid1, l1, r1] = MakeGuardedBuffer(/*initial_fill=*/0xFF);
  int range1 = RunBuild(b, mid1);

  // Outputs must match byte-for-byte for identical configuration.
  for (int i = 0; i < 256; ++i) {
    EXPECT_EQ(mid0[i], mid1[i]) << "Mismatch at index " << i;
  }
  EXPECT_EQ(range0, range1);
}

// Verifies boundary handling: index 0 and 255 are set, and Build handles
// ranges at boundaries via the public API without out-of-bounds writes.
TEST_F(ByteMapBuilderBuildTest_410, HandlesBoundaryRangesSafely_410) {
  ByteMapBuilder b;

  // Mark boundaries explicitly; we do not assume any color semantics.
  b.Mark(0, 10);
  b.Mark(245, 255);
  b.Merge();

  auto [buf, mid, left_canary, right_canary] = MakeGuardedBuffer(/*initial_fill=*/0xCC);

  // Snapshot canaries
  uint8_t left_before  = *left_canary;
  uint8_t right_before = *right_canary;

  int out_range = RunBuild(b, mid);
  EXPECT_NE(out_range, -123456);

  // Accessing edges should be safe and set to some value.
  // We cannot assume exact values; only that they are written.
  volatile uint8_t v0   = mid[0];
  volatile uint8_t v255 = mid[255];
  (void)v0; (void)v255;

  // No canary corruption
  EXPECT_EQ(left_before,  *left_canary);
  EXPECT_EQ(right_before, *right_canary);
}

// Verifies that calling Build multiple times on the same instance (without further mutations)
// yields identical results. This checks for stable, repeatable output given fixed public state.
TEST_F(ByteMapBuilderBuildTest_410, IdempotentAcrossRepeatedBuilds_410) {
  ByteMapBuilder b;

  // Establish some public-facing configuration.
  b.Mark(5, 5);
  b.Mark(100, 120);
  b.Mark(200, 230);
  b.Merge();

  auto [bufA, midA, lA, rA] = MakeGuardedBuffer(/*initial_fill=*/0x11);
  auto [bufB, midB, lB, rB] = MakeGuardedBuffer(/*initial_fill=*/0x22);

  int rangeA = RunBuild(b, midA);
  int rangeB = RunBuild(b, midB);

  // Results should be identical across runs.
  for (int i = 0; i < 256; ++i) {
    EXPECT_EQ(midA[i], midB[i]) << "Mismatch at index " << i;
  }
  EXPECT_EQ(rangeA, rangeB);
}

