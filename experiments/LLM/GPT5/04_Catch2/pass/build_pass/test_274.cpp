// File: tests/stringmaker_ull_convert_274_test.cpp
#include <gtest/gtest.h>
#include <limits>
#include "catch2/catch_tostring.hpp"  // Adjust include path if needed

namespace {

using ::Catch::StringMaker;

// A small helper to shorten the call site
static std::string ToStringULL(unsigned long long v) {
    return StringMaker<unsigned long long>::convert(v);
}

// -------------------------
// Normal & boundary cases
// -------------------------

TEST(StringMakerULLTest_274, Zero_NoHex_274) {
    // value == 0 (<= 255) -> decimal only
    EXPECT_EQ(ToStringULL(0ULL), "0");
}

TEST(StringMakerULLTest_274, AtThreshold_NoHex_274) {
    // value == 255 -> decimal only (boundary)
    EXPECT_EQ(ToStringULL(255ULL), "255");
}

TEST(StringMakerULLTest_274, JustAboveThreshold_AppendsHex_274) {
    // value == 256 -> decimal + hex
    EXPECT_EQ(ToStringULL(256ULL), "256 (0x100)");
}

// -------------------------
// Representative larger values
// -------------------------

TEST(StringMakerULLTest_274, LargerValue_LowercaseHex_274) {
    // Pick a value with alphabetic hex digits to assert lowercase output
    // 2748 decimal == 0xABC
    EXPECT_EQ(ToStringULL(2748ULL), "2748 (0xabc)");
}

TEST(StringMakerULLTest_274, MaxValue_AppendsHex_274) {
    // ULLONG_MAX -> decimal + full lowercase hex
    const unsigned long long v = std::numeric_limits<unsigned long long>::max();
    // 18446744073709551615 == 0xffffffffffffffff
    EXPECT_EQ(ToStringULL(v), "18446744073709551615 (0xffffffffffffffff)");
}

} // namespace
