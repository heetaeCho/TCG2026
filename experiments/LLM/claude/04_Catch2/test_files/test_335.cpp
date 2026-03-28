#include <gtest/gtest.h>
#include <climits>
#include <cstdint>
#include <type_traits>

// Include the header under test
#include "./TestProjects/Catch2/src/catch2/internal/catch_random_integer_helpers.hpp"

// Test fixture
class TransposeToNaturalOrderTest_335 : public ::testing::Test {
protected:
};

// ==================== Tests for signed 8-bit types ====================

TEST_F(TransposeToNaturalOrderTest_335, Int8_ZeroInput_335) {
    // When input is 0, XOR with highest bit (0x80) should give 0x80
    uint8_t input = 0;
    uint8_t result = Catch::Detail::transposeToNaturalOrder<int8_t>(input);
    EXPECT_EQ(result, uint8_t(0x80));
}

TEST_F(TransposeToNaturalOrderTest_335, Int8_HighestBitSet_335) {
    // When input has highest bit set (0x80), XOR with 0x80 should give 0
    uint8_t input = 0x80;
    uint8_t result = Catch::Detail::transposeToNaturalOrder<int8_t>(input);
    EXPECT_EQ(result, uint8_t(0x00));
}

TEST_F(TransposeToNaturalOrderTest_335, Int8_AllOnes_335) {
    // Input 0xFF, XOR with 0x80 gives 0x7F
    uint8_t input = 0xFF;
    uint8_t result = Catch::Detail::transposeToNaturalOrder<int8_t>(input);
    EXPECT_EQ(result, uint8_t(0x7F));
}

TEST_F(TransposeToNaturalOrderTest_335, Int8_AllBitsExceptHighest_335) {
    // Input 0x7F, XOR with 0x80 gives 0xFF
    uint8_t input = 0x7F;
    uint8_t result = Catch::Detail::transposeToNaturalOrder<int8_t>(input);
    EXPECT_EQ(result, uint8_t(0xFF));
}

TEST_F(TransposeToNaturalOrderTest_335, Int8_OneValue_335) {
    uint8_t input = 1;
    uint8_t result = Catch::Detail::transposeToNaturalOrder<int8_t>(input);
    EXPECT_EQ(result, uint8_t(0x81));
}

// ==================== Tests for signed 16-bit types ====================

TEST_F(TransposeToNaturalOrderTest_335, Int16_ZeroInput_335) {
    uint16_t input = 0;
    uint16_t result = Catch::Detail::transposeToNaturalOrder<int16_t>(input);
    EXPECT_EQ(result, uint16_t(0x8000));
}

TEST_F(TransposeToNaturalOrderTest_335, Int16_HighestBitSet_335) {
    uint16_t input = 0x8000;
    uint16_t result = Catch::Detail::transposeToNaturalOrder<int16_t>(input);
    EXPECT_EQ(result, uint16_t(0x0000));
}

TEST_F(TransposeToNaturalOrderTest_335, Int16_AllOnes_335) {
    uint16_t input = 0xFFFF;
    uint16_t result = Catch::Detail::transposeToNaturalOrder<int16_t>(input);
    EXPECT_EQ(result, uint16_t(0x7FFF));
}

TEST_F(TransposeToNaturalOrderTest_335, Int16_AllBitsExceptHighest_335) {
    uint16_t input = 0x7FFF;
    uint16_t result = Catch::Detail::transposeToNaturalOrder<int16_t>(input);
    EXPECT_EQ(result, uint16_t(0xFFFF));
}

// ==================== Tests for signed 32-bit types ====================

TEST_F(TransposeToNaturalOrderTest_335, Int32_ZeroInput_335) {
    uint32_t input = 0;
    uint32_t result = Catch::Detail::transposeToNaturalOrder<int32_t>(input);
    EXPECT_EQ(result, uint32_t(0x80000000u));
}

TEST_F(TransposeToNaturalOrderTest_335, Int32_HighestBitSet_335) {
    uint32_t input = 0x80000000u;
    uint32_t result = Catch::Detail::transposeToNaturalOrder<int32_t>(input);
    EXPECT_EQ(result, uint32_t(0x00000000u));
}

TEST_F(TransposeToNaturalOrderTest_335, Int32_AllOnes_335) {
    uint32_t input = 0xFFFFFFFFu;
    uint32_t result = Catch::Detail::transposeToNaturalOrder<int32_t>(input);
    EXPECT_EQ(result, uint32_t(0x7FFFFFFFu));
}

TEST_F(TransposeToNaturalOrderTest_335, Int32_AllBitsExceptHighest_335) {
    uint32_t input = 0x7FFFFFFFu;
    uint32_t result = Catch::Detail::transposeToNaturalOrder<int32_t>(input);
    EXPECT_EQ(result, uint32_t(0xFFFFFFFFu));
}

TEST_F(TransposeToNaturalOrderTest_335, Int32_ArbitraryValue_335) {
    uint32_t input = 0x12345678u;
    uint32_t result = Catch::Detail::transposeToNaturalOrder<int32_t>(input);
    EXPECT_EQ(result, uint32_t(0x12345678u ^ 0x80000000u));
}

// ==================== Tests for signed 64-bit types ====================

TEST_F(TransposeToNaturalOrderTest_335, Int64_ZeroInput_335) {
    uint64_t input = 0;
    uint64_t result = Catch::Detail::transposeToNaturalOrder<int64_t>(input);
    EXPECT_EQ(result, uint64_t(0x8000000000000000ull));
}

TEST_F(TransposeToNaturalOrderTest_335, Int64_HighestBitSet_335) {
    uint64_t input = 0x8000000000000000ull;
    uint64_t result = Catch::Detail::transposeToNaturalOrder<int64_t>(input);
    EXPECT_EQ(result, uint64_t(0x0000000000000000ull));
}

TEST_F(TransposeToNaturalOrderTest_335, Int64_AllOnes_335) {
    uint64_t input = 0xFFFFFFFFFFFFFFFFull;
    uint64_t result = Catch::Detail::transposeToNaturalOrder<int64_t>(input);
    EXPECT_EQ(result, uint64_t(0x7FFFFFFFFFFFFFFFull));
}

TEST_F(TransposeToNaturalOrderTest_335, Int64_AllBitsExceptHighest_335) {
    uint64_t input = 0x7FFFFFFFFFFFFFFFull;
    uint64_t result = Catch::Detail::transposeToNaturalOrder<int64_t>(input);
    EXPECT_EQ(result, uint64_t(0xFFFFFFFFFFFFFFFFull));
}

TEST_F(TransposeToNaturalOrderTest_335, Int64_ArbitraryValue_335) {
    uint64_t input = 0xDEADBEEFCAFEBABEull;
    uint64_t result = Catch::Detail::transposeToNaturalOrder<int64_t>(input);
    EXPECT_EQ(result, uint64_t(0xDEADBEEFCAFEBABEull ^ 0x8000000000000000ull));
}

// ==================== Involution property tests ====================

TEST_F(TransposeToNaturalOrderTest_335, Int8_DoubleApplicationIsIdentity_335) {
    // Applying the function twice should return the original value (XOR is its own inverse)
    uint8_t input = 0x42;
    uint8_t once = Catch::Detail::transposeToNaturalOrder<int8_t>(input);
    uint8_t twice = Catch::Detail::transposeToNaturalOrder<int8_t>(once);
    EXPECT_EQ(twice, input);
}

TEST_F(TransposeToNaturalOrderTest_335, Int32_DoubleApplicationIsIdentity_335) {
    uint32_t input = 0xABCD1234u;
    uint32_t once = Catch::Detail::transposeToNaturalOrder<int32_t>(input);
    uint32_t twice = Catch::Detail::transposeToNaturalOrder<int32_t>(once);
    EXPECT_EQ(twice, input);
}

TEST_F(TransposeToNaturalOrderTest_335, Int64_DoubleApplicationIsIdentity_335) {
    uint64_t input = 0x123456789ABCDEF0ull;
    uint64_t once = Catch::Detail::transposeToNaturalOrder<int64_t>(input);
    uint64_t twice = Catch::Detail::transposeToNaturalOrder<int64_t>(once);
    EXPECT_EQ(twice, input);
}

// ==================== Order preservation tests ====================

TEST_F(TransposeToNaturalOrderTest_335, Int32_PreservesRelativeOrderForPositiveSignedRange_335) {
    // For values that would represent positive signed integers (highest bit set in unsigned = positive in natural order),
    // the function should maintain ordering
    uint32_t a = 0x80000000u; // corresponds to signed 0
    uint32_t b = 0x80000001u; // corresponds to signed 1
    uint32_t result_a = Catch::Detail::transposeToNaturalOrder<int32_t>(a);
    uint32_t result_b = Catch::Detail::transposeToNaturalOrder<int32_t>(b);
    // After transpose, the order should map: 0x80000000 -> 0, 0x80000001 -> 1
    EXPECT_LT(result_a, result_b);
}

TEST_F(TransposeToNaturalOrderTest_335, Int32_NegativeToPositiveOrdering_335) {
    // In two's complement, 0x00000000 (unsigned) represents signed -2^31 via the transpose
    // and 0xFFFFFFFF represents signed max. After transpose, the result for 0x00000000 should be
    // less than for 0xFFFFFFFF.
    // 0x00000000 -> 0x80000000
    // 0xFFFFFFFF -> 0x7FFFFFFF
    // Actually 0x80000000 > 0x7FFFFFFF, so let's verify the actual mapping.
    uint32_t neg_extreme = 0x00000000u; // maps to 0x80000000 in natural order
    uint32_t pos_extreme = 0xFFFFFFFFu; // maps to 0x7FFFFFFF in natural order
    uint32_t result_neg = Catch::Detail::transposeToNaturalOrder<int32_t>(neg_extreme);
    uint32_t result_pos = Catch::Detail::transposeToNaturalOrder<int32_t>(pos_extreme);
    EXPECT_EQ(result_neg, uint32_t(0x80000000u));
    EXPECT_EQ(result_pos, uint32_t(0x7FFFFFFFu));
}

// ==================== Constexpr test ====================

TEST_F(TransposeToNaturalOrderTest_335, Int32_IsConstexpr_335) {
    constexpr uint32_t result = Catch::Detail::transposeToNaturalOrder<int32_t>(uint32_t(0));
    EXPECT_EQ(result, uint32_t(0x80000000u));
}

TEST_F(TransposeToNaturalOrderTest_335, Int64_IsConstexpr_335) {
    constexpr uint64_t result = Catch::Detail::transposeToNaturalOrder<int64_t>(uint64_t(0));
    EXPECT_EQ(result, uint64_t(0x8000000000000000ull));
}

// ==================== Boundary: single bit patterns ====================

TEST_F(TransposeToNaturalOrderTest_335, Int8_SingleBitPatterns_335) {
    // Test each single bit for 8-bit
    for (int bit = 0; bit < 8; ++bit) {
        uint8_t input = uint8_t(1) << bit;
        uint8_t expected = input ^ uint8_t(0x80);
        uint8_t result = Catch::Detail::transposeToNaturalOrder<int8_t>(input);
        EXPECT_EQ(result, expected) << "Failed for bit " << bit;
    }
}

TEST_F(TransposeToNaturalOrderTest_335, Int32_SingleBitPatterns_335) {
    for (int bit = 0; bit < 32; ++bit) {
        uint32_t input = uint32_t(1) << bit;
        uint32_t expected = input ^ uint32_t(0x80000000u);
        uint32_t result = Catch::Detail::transposeToNaturalOrder<int32_t>(input);
        EXPECT_EQ(result, expected) << "Failed for bit " << bit;
    }
}
