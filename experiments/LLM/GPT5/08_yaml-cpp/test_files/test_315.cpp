// TEST_ID: 315
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>

#include "contrib/dragonbox.h"

namespace {

template <typename UInt>
constexpr int FloorLog2(UInt n) noexcept {
  return YAML::jkj::dragonbox::detail::log::floor_log2<UInt>(n);
}

template <typename UInt>
constexpr UInt U(UInt v) noexcept {
  return v;
}

}  // namespace

// Compile-time (constexpr) verification
static_assert(FloorLog2<std::uint32_t>(0u) == -1, "floor_log2(0) must be -1");
static_assert(FloorLog2<std::uint32_t>(1u) == 0, "floor_log2(1) must be 0");
static_assert(FloorLog2<std::uint32_t>(2u) == 1, "floor_log2(2) must be 1");
static_assert(FloorLog2<std::uint32_t>(3u) == 1, "floor_log2(3) must be 1");
static_assert(FloorLog2<std::uint32_t>(4u) == 2, "floor_log2(4) must be 2");

static_assert(noexcept(FloorLog2<std::uint32_t>(0u)), "floor_log2 must be noexcept");

TEST(FloorLog2Test_315, ZeroReturnsMinusOne_315) {
  EXPECT_EQ(FloorLog2<std::uint8_t>(U<std::uint8_t>(0)), -1);
  EXPECT_EQ(FloorLog2<std::uint16_t>(U<std::uint16_t>(0)), -1);
  EXPECT_EQ(FloorLog2<std::uint32_t>(U<std::uint32_t>(0)), -1);
  EXPECT_EQ(FloorLog2<std::uint64_t>(U<std::uint64_t>(0)), -1);
}

TEST(FloorLog2Test_315, OneReturnsZero_315) {
  EXPECT_EQ(FloorLog2<std::uint8_t>(U<std::uint8_t>(1)), 0);
  EXPECT_EQ(FloorLog2<std::uint32_t>(U<std::uint32_t>(1)), 0);
  EXPECT_EQ(FloorLog2<std::uint64_t>(U<std::uint64_t>(1)), 0);
}

TEST(FloorLog2Test_315, PowersOfTwoMatchExponent_315) {
  EXPECT_EQ(FloorLog2<std::uint32_t>(1u), 0);
  EXPECT_EQ(FloorLog2<std::uint32_t>(2u), 1);
  EXPECT_EQ(FloorLog2<std::uint32_t>(4u), 2);
  EXPECT_EQ(FloorLog2<std::uint32_t>(8u), 3);
  EXPECT_EQ(FloorLog2<std::uint32_t>(16u), 4);
  EXPECT_EQ(FloorLog2<std::uint32_t>(1u << 31), 31);

  EXPECT_EQ(FloorLog2<std::uint64_t>(1ull), 0);
  EXPECT_EQ(FloorLog2<std::uint64_t>(1ull << 1), 1);
  EXPECT_EQ(FloorLog2<std::uint64_t>(1ull << 32), 32);
  EXPECT_EQ(FloorLog2<std::uint64_t>(1ull << 63), 63);
}

TEST(FloorLog2Test_315, ValuesBetweenPowersOfTwoFloorCorrectly_315) {
  // Between 2^k and 2^(k+1)-1 should map to k
  EXPECT_EQ(FloorLog2<std::uint32_t>(3u), 1);
  EXPECT_EQ(FloorLog2<std::uint32_t>(5u), 2);
  EXPECT_EQ(FloorLog2<std::uint32_t>(7u), 2);
  EXPECT_EQ(FloorLog2<std::uint32_t>(9u), 3);
  EXPECT_EQ(FloorLog2<std::uint32_t>(15u), 3);
  EXPECT_EQ(FloorLog2<std::uint32_t>(31u), 4);
  EXPECT_EQ(FloorLog2<std::uint32_t>(63u), 5);

  EXPECT_EQ(FloorLog2<std::uint64_t>((1ull << 10) + 1ull), 10);
  EXPECT_EQ(FloorLog2<std::uint64_t>((1ull << 20) - 1ull), 19);
  EXPECT_EQ(FloorLog2<std::uint64_t>((1ull << 20) + 12345ull), 20);
}

TEST(FloorLog2Test_315, MaximumValuesReturnTopBitIndex_315) {
  // For unsigned max, floor_log2 should be (bit_width - 1).
  EXPECT_EQ(FloorLog2<std::uint8_t>(std::numeric_limits<std::uint8_t>::max()), 7);
  EXPECT_EQ(FloorLog2<std::uint16_t>(std::numeric_limits<std::uint16_t>::max()), 15);
  EXPECT_EQ(FloorLog2<std::uint32_t>(std::numeric_limits<std::uint32_t>::max()), 31);
  EXPECT_EQ(FloorLog2<std::uint64_t>(std::numeric_limits<std::uint64_t>::max()), 63);
}

TEST(FloorLog2Test_315, NoexceptIsDeclared_315) {
  // Verify the noexcept contract via type traits as an observable API property.
  EXPECT_TRUE((noexcept(YAML::jkj::dragonbox::detail::log::floor_log2<std::uint32_t>(0u))));
  EXPECT_TRUE((noexcept(YAML::jkj::dragonbox::detail::log::floor_log2<std::uint64_t>(1ull))));
}