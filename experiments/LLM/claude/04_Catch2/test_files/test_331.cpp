#include <gtest/gtest.h>
#include <cstdint>
#include "./TestProjects/Catch2/src/catch2/internal/catch_random_integer_helpers.hpp"

namespace {

using Catch::Detail::extendedMultPortable;
using Catch::Detail::ExtendedMultResult;

// Helper to verify multiplication result against expected upper and lower parts
void VerifyMult(std::uint64_t lhs, std::uint64_t rhs,
                std::uint64_t expected_upper, std::uint64_t expected_lower) {
    auto result = extendedMultPortable(lhs, rhs);
    EXPECT_EQ(result.upper, expected_upper) 
        << "lhs=" << lhs << " rhs=" << rhs;
    EXPECT_EQ(result.lower, expected_lower) 
        << "lhs=" << lhs << " rhs=" << rhs;
}

class ExtendedMultPortableTest_331 : public ::testing::Test {};

// Test: 0 * 0 = 0
TEST_F(ExtendedMultPortableTest_331, ZeroTimesZero_331) {
    VerifyMult(0, 0, 0, 0);
}

// Test: 0 * any = 0
TEST_F(ExtendedMultPortableTest_331, ZeroTimesNonZero_331) {
    VerifyMult(0, 12345, 0, 0);
    VerifyMult(12345, 0, 0, 0);
}

// Test: 1 * 1 = 1
TEST_F(ExtendedMultPortableTest_331, OneTimesOne_331) {
    VerifyMult(1, 1, 0, 1);
}

// Test: 1 * x = x (identity)
TEST_F(ExtendedMultPortableTest_331, IdentityMultiplication_331) {
    VerifyMult(1, 0xDEADBEEFCAFEBABEULL, 0, 0xDEADBEEFCAFEBABEULL);
    VerifyMult(0xDEADBEEFCAFEBABEULL, 1, 0, 0xDEADBEEFCAFEBABEULL);
}

// Test: Small numbers that fit in lower 64 bits
TEST_F(ExtendedMultPortableTest_331, SmallNumbers_331) {
    VerifyMult(100, 200, 0, 20000);
    VerifyMult(0xFFFF, 0xFFFF, 0, 0xFFFE0001ULL);
}

// Test: Numbers that just fit in 32 bits
TEST_F(ExtendedMultPortableTest_331, Max32BitNumbers_331) {
    // 0xFFFFFFFF * 0xFFFFFFFF = 0xFFFFFFFE00000001
    VerifyMult(0xFFFFFFFFULL, 0xFFFFFFFFULL, 0, 0xFFFFFFFE00000001ULL);
}

// Test: Maximum uint64 values
TEST_F(ExtendedMultPortableTest_331, MaxUint64TimesMaxUint64_331) {
    // 0xFFFFFFFFFFFFFFFF * 0xFFFFFFFFFFFFFFFF = 0xFFFFFFFFFFFFFFFE:0000000000000001
    auto result = extendedMultPortable(UINT64_MAX, UINT64_MAX);
    EXPECT_EQ(result.upper, 0xFFFFFFFFFFFFFFFEULL);
    EXPECT_EQ(result.lower, 0x0000000000000001ULL);
}

// Test: MaxUint64 * 1
TEST_F(ExtendedMultPortableTest_331, MaxUint64TimesOne_331) {
    VerifyMult(UINT64_MAX, 1, 0, UINT64_MAX);
    VerifyMult(1, UINT64_MAX, 0, UINT64_MAX);
}

// Test: MaxUint64 * 2
TEST_F(ExtendedMultPortableTest_331, MaxUint64TimesTwo_331) {
    // 0xFFFFFFFFFFFFFFFF * 2 = 0x1:FFFFFFFFFFFFFFFE
    VerifyMult(UINT64_MAX, 2, 1, UINT64_MAX - 1);
    VerifyMult(2, UINT64_MAX, 1, UINT64_MAX - 1);
}

// Test: Powers of 2
TEST_F(ExtendedMultPortableTest_331, PowersOfTwo_331) {
    // 2^32 * 2^32 = 2^64, which overflows into upper
    VerifyMult(1ULL << 32, 1ULL << 32, 1, 0);
    
    // 2^63 * 2 = 2^64
    VerifyMult(1ULL << 63, 2, 1, 0);
    
    // 2^48 * 2^48 = 2^96
    VerifyMult(1ULL << 48, 1ULL << 48, 1ULL << 32, 0);
}

// Test: Commutativity
TEST_F(ExtendedMultPortableTest_331, Commutativity_331) {
    std::uint64_t a = 0x123456789ABCDEF0ULL;
    std::uint64_t b = 0xFEDCBA9876543210ULL;
    auto r1 = extendedMultPortable(a, b);
    auto r2 = extendedMultPortable(b, a);
    EXPECT_EQ(r1.upper, r2.upper);
    EXPECT_EQ(r1.lower, r2.lower);
}

// Test: Known multiplication with carry
TEST_F(ExtendedMultPortableTest_331, KnownMultiplicationWithCarry_331) {
    // 0x1'0000'0000 * 0x1'0000'0000 = 0x1:0000000000000000
    VerifyMult(0x100000000ULL, 0x100000000ULL, 1, 0);
}

// Test: Large numbers producing specific known results
TEST_F(ExtendedMultPortableTest_331, LargeNumbersKnownResult_331) {
    // 0x8000000000000000 * 2 = 0x1:0000000000000000
    VerifyMult(0x8000000000000000ULL, 2, 1, 0);
    
    // 0x8000000000000000 * 0x8000000000000000 = 0x4000000000000000:0000000000000000
    VerifyMult(0x8000000000000000ULL, 0x8000000000000000ULL, 
               0x4000000000000000ULL, 0);
}

// Test: Values with only high 32 bits set
TEST_F(ExtendedMultPortableTest_331, HighBitsOnly_331) {
    // 0xFFFFFFFF00000000 * 0xFFFFFFFF00000000
    std::uint64_t a = 0xFFFFFFFF00000000ULL;
    auto result = extendedMultPortable(a, a);
    // (0xFFFFFFFF * 2^32)^2 = 0xFFFFFFFF^2 * 2^64
    // 0xFFFFFFFF^2 = 0xFFFFFFFE00000001
    EXPECT_EQ(result.upper, 0xFFFFFFFE00000001ULL);
    EXPECT_EQ(result.lower, 0);
}

// Test: Values with only low 32 bits set
TEST_F(ExtendedMultPortableTest_331, LowBitsOnly_331) {
    std::uint64_t a = 0x00000000FFFFFFFFULL;
    auto result = extendedMultPortable(a, a);
    EXPECT_EQ(result.upper, 0);
    EXPECT_EQ(result.lower, 0xFFFFFFFE00000001ULL);
}

// Test: Mixed high and low bits
TEST_F(ExtendedMultPortableTest_331, MixedHighLowBits_331) {
    // 0x0000000100000001 * 0x0000000100000001 = 0x100000002:00000001
    std::uint64_t a = 0x0000000100000001ULL;
    auto result = extendedMultPortable(a, a);
    // (2^32 + 1)^2 = 2^64 + 2^33 + 1 = 1:0000000200000001
    EXPECT_EQ(result.upper, 1);
    EXPECT_EQ(result.lower, 0x0000000200000001ULL);
}

// Test: Specific regression-style values
TEST_F(ExtendedMultPortableTest_331, SpecificValues_331) {
    // 3 * 5 = 15
    VerifyMult(3, 5, 0, 15);
    
    // 0xABCDEF * 0x123456 - small enough to fit in 64 bits
    std::uint64_t a = 0xABCDEF;
    std::uint64_t b = 0x123456;
    VerifyMult(a, b, 0, a * b);
}

// Test: Boundary around 32-bit overflow
TEST_F(ExtendedMultPortableTest_331, Boundary32BitOverflow_331) {
    // (2^32 - 1) * (2^32 + 1) = 2^64 - 1
    VerifyMult(0xFFFFFFFFULL, 0x100000001ULL, 0, 0xFFFFFFFFFFFFFFFFULL);
}

// Test: Single bit patterns
TEST_F(ExtendedMultPortableTest_331, SingleBitPatterns_331) {
    // 2^63 * 2^63 should produce upper = 2^62, lower = 0
    VerifyMult(1ULL << 63, 1ULL << 63, 1ULL << 62, 0);
}

// Test: MaxUint64 * 0
TEST_F(ExtendedMultPortableTest_331, MaxUint64TimesZero_331) {
    VerifyMult(UINT64_MAX, 0, 0, 0);
    VerifyMult(0, UINT64_MAX, 0, 0);
}

// Test: Result structure fields are correct
TEST_F(ExtendedMultPortableTest_331, ResultStructure_331) {
    auto result = extendedMultPortable(10, 20);
    EXPECT_EQ(result.upper, 0ULL);
    EXPECT_EQ(result.lower, 200ULL);
}

// Test: Constexpr evaluation
TEST_F(ExtendedMultPortableTest_331, ConstexprEvaluation_331) {
    constexpr auto result = extendedMultPortable(UINT64_MAX, UINT64_MAX);
    static_assert(result.upper == 0xFFFFFFFFFFFFFFFEULL, "upper mismatch");
    static_assert(result.lower == 0x0000000000000001ULL, "lower mismatch");
    EXPECT_EQ(result.upper, 0xFFFFFFFFFFFFFFFEULL);
    EXPECT_EQ(result.lower, 0x0000000000000001ULL);
}

} // namespace
