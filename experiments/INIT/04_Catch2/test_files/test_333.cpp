// File: test_extended_mult_333.cpp
#include <gtest/gtest.h>
#include <cstdint>
#include <limits>

// Include the header under test
#include "catch2/internal/catch_random_integer_helpers.hpp"

using Catch::Detail::extendedMult;

// If ExtendedMultResult is in namespace Catch::Detail, bring it in;
// otherwise adjust the using-declaration to match your codebase.
using Catch::Detail::ExtendedMultResult;

//
// Test fixture (kept minimal; no internal state assumptions)
//
class ExtendedMultTest_333 : public ::testing::Test {};

// ---------- uint8_t cases ----------

TEST_F(ExtendedMultTest_333, ZeroTimesAnything_YieldsZeroHighAndZeroLow_u8_333) {
    const uint8_t x = 0u;
    const uint8_t y = 157u; // arbitrary non-zero
    ExtendedMultResult<uint8_t> r1 = extendedMult<uint8_t>(x, y);
    ExtendedMultResult<uint8_t> r2 = extendedMult<uint8_t>(y, x);

    EXPECT_EQ(r1.high, 0u);
    EXPECT_EQ(r1.low,  0u);
    EXPECT_EQ(r2.high, 0u);
    EXPECT_EQ(r2.low,  0u);
}

TEST_F(ExtendedMultTest_333, TimesOne_ReturnsLowEqualsInput_HighZero_u8_333) {
    const uint8_t a = 42u;
    ExtendedMultResult<uint8_t> r = extendedMult<uint8_t>(a, 1u);
    EXPECT_EQ(r.high, 0u);
    EXPECT_EQ(r.low,  a);
}

TEST_F(ExtendedMultTest_333, MaxTimesMax_u8_333) {
    // 0xFF * 0xFF = 0xFE01 -> high=0xFE, low=0x01 for 8-bit limbs
    const uint8_t m = std::numeric_limits<uint8_t>::max(); // 255
    ExtendedMultResult<uint8_t> r = extendedMult<uint8_t>(m, m);
    EXPECT_EQ(r.high, static_cast<uint8_t>(0xFE));
    EXPECT_EQ(r.low,  static_cast<uint8_t>(0x01));
}

TEST_F(ExtendedMultTest_333, ArbitraryMultiply_CorrectHighAndLow_u8_333) {
    // 200 * 150 = 30000 = 0x7530 -> high=0x75, low=0x30 for 8-bit limbs
    const uint8_t a = 200u;
    const uint8_t b = 150u;
    ExtendedMultResult<uint8_t> r = extendedMult<uint8_t>(a, b);
    EXPECT_EQ(r.high, static_cast<uint8_t>(0x75));
    EXPECT_EQ(r.low,  static_cast<uint8_t>(0x30));
}

TEST_F(ExtendedMultTest_333, Commutativity_SameHighAndLow_u8_333) {
    const uint8_t a = 123u, b = 45u;
    ExtendedMultResult<uint8_t> r1 = extendedMult<uint8_t>(a, b);
    ExtendedMultResult<uint8_t> r2 = extendedMult<uint8_t>(b, a);
    EXPECT_EQ(r1.high, r2.high);
    EXPECT_EQ(r1.low,  r2.low);
}

// ---------- uint32_t cases ----------

TEST_F(ExtendedMultTest_333, ZeroTimesAnything_YieldsZeroHighAndZeroLow_u32_333) {
    const uint32_t x = 0u;
    const uint32_t y = 0xDEADBEEFu;
    ExtendedMultResult<uint32_t> r1 = extendedMult<uint32_t>(x, y);
    ExtendedMultResult<uint32_t> r2 = extendedMult<uint32_t>(y, x);

    EXPECT_EQ(r1.high, 0u);
    EXPECT_EQ(r1.low,  0u);
    EXPECT_EQ(r2.high, 0u);
    EXPECT_EQ(r2.low,  0u);
}

TEST_F(ExtendedMultTest_333, TimesOne_ReturnsLowEqualsInput_HighZero_u32_333) {
    const uint32_t a = 0xCAFEBABEu;
    ExtendedMultResult<uint32_t> r = extendedMult<uint32_t>(a, 1u);
    EXPECT_EQ(r.high, 0u);
    EXPECT_EQ(r.low,  a);
}

TEST_F(ExtendedMultTest_333, MaxTimesMax_u32_333) {
    // (2^32 - 1)^2 = 0xFFFFFFFE00000001 -> high=0xFFFFFFFE, low=0x00000001
    const uint32_t m = std::numeric_limits<uint32_t>::max();
    ExtendedMultResult<uint32_t> r = extendedMult<uint32_t>(m, m);
    EXPECT_EQ(r.high, 0xFFFFFFFEu);
    EXPECT_EQ(r.low,  0x00000001u);
}

TEST_F(ExtendedMultTest_333, ArbitraryMultiply_CorrectHighAndLow_u32_333) {
    // 0x12345678 * 0x9ABCDEF0 = 0x0B00EA4E_242D2080
    const uint32_t a = 0x12345678u;
    const uint32_t b = 0x9ABCDEF0u;
    ExtendedMultResult<uint32_t> r = extendedMult<uint32_t>(a, b);
    EXPECT_EQ(r.high, 0x0B00EA4Eu);
    EXPECT_EQ(r.low,  0x242D2080u);
}

TEST_F(ExtendedMultTest_333, Commutativity_SameHighAndLow_u32_333) {
    const uint32_t a = 0x0BADF00Du;
    const uint32_t b = 0x00C0FFEEu;
    ExtendedMultResult<uint32_t> r1 = extendedMult<uint32_t>(a, b);
    ExtendedMultResult<uint32_t> r2 = extendedMult<uint32_t>(b, a);
    EXPECT_EQ(r1.high, r2.high);
    EXPECT_EQ(r1.low,  r2.low);
}

// ---------- Template constraints (documentation-only) ----------
// Note: static_asserts in the implementation intentionally prevent instantiation
// for signed types or 64-bit unsigned types. These are compile-time constraints
// and cannot be meaningfully exercised at runtime; attempting to instantiate
// extendedMult<int32_t>(...) or extendedMult<uint64_t>(...) should fail to compile.
// The tests above focus on observable behavior for supported unsigned types
// smaller than 64 bits, as required.
