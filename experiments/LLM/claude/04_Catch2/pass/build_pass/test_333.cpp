#include <gtest/gtest.h>
#include <cstdint>
#include <climits>
#include "catch2/internal/catch_random_integer_helpers.hpp"

// Test fixture for extendedMult tests
class ExtendedMultTest_333 : public ::testing::Test {
protected:
};

// ==================== uint8_t tests ====================

TEST_F(ExtendedMultTest_333, Uint8_ZeroTimesZero_333) {
    auto result = Catch::Detail::extendedMult<std::uint8_t>(0, 0);
    EXPECT_EQ(result.upper, 0u);
    EXPECT_EQ(result.lower, 0u);
}

TEST_F(ExtendedMultTest_333, Uint8_ZeroTimesOne_333) {
    auto result = Catch::Detail::extendedMult<std::uint8_t>(0, 1);
    EXPECT_EQ(result.upper, 0u);
    EXPECT_EQ(result.lower, 0u);
}

TEST_F(ExtendedMultTest_333, Uint8_OneTimesOne_333) {
    auto result = Catch::Detail::extendedMult<std::uint8_t>(1, 1);
    EXPECT_EQ(result.upper, 0u);
    EXPECT_EQ(result.lower, 1u);
}

TEST_F(ExtendedMultTest_333, Uint8_MaxTimesOne_333) {
    auto result = Catch::Detail::extendedMult<std::uint8_t>(255, 1);
    EXPECT_EQ(result.upper, 0u);
    EXPECT_EQ(result.lower, 255u);
}

TEST_F(ExtendedMultTest_333, Uint8_MaxTimesMax_333) {
    // 255 * 255 = 65025 = 0xFE01
    // upper = 0xFE = 254, lower = 0x01 = 1
    auto result = Catch::Detail::extendedMult<std::uint8_t>(255, 255);
    EXPECT_EQ(result.upper, 254u);
    EXPECT_EQ(result.lower, 1u);
}

TEST_F(ExtendedMultTest_333, Uint8_16Times16_333) {
    // 16 * 16 = 256 = 0x0100
    // upper = 1, lower = 0
    auto result = Catch::Detail::extendedMult<std::uint8_t>(16, 16);
    EXPECT_EQ(result.upper, 1u);
    EXPECT_EQ(result.lower, 0u);
}

TEST_F(ExtendedMultTest_333, Uint8_Commutativity_333) {
    auto result1 = Catch::Detail::extendedMult<std::uint8_t>(13, 200);
    auto result2 = Catch::Detail::extendedMult<std::uint8_t>(200, 13);
    EXPECT_EQ(result1.upper, result2.upper);
    EXPECT_EQ(result1.lower, result2.lower);
}

TEST_F(ExtendedMultTest_333, Uint8_ZeroTimesMax_333) {
    auto result = Catch::Detail::extendedMult<std::uint8_t>(0, 255);
    EXPECT_EQ(result.upper, 0u);
    EXPECT_EQ(result.lower, 0u);
}

TEST_F(ExtendedMultTest_333, Uint8_KnownProduct_333) {
    // 100 * 200 = 20000 = 0x4E20
    // upper = 0x4E = 78, lower = 0x20 = 32
    auto result = Catch::Detail::extendedMult<std::uint8_t>(100, 200);
    EXPECT_EQ(result.upper, 78u);
    EXPECT_EQ(result.lower, 32u);
}

// ==================== uint16_t tests ====================

TEST_F(ExtendedMultTest_333, Uint16_ZeroTimesZero_333) {
    auto result = Catch::Detail::extendedMult<std::uint16_t>(0, 0);
    EXPECT_EQ(result.upper, 0u);
    EXPECT_EQ(result.lower, 0u);
}

TEST_F(ExtendedMultTest_333, Uint16_OneTimesOne_333) {
    auto result = Catch::Detail::extendedMult<std::uint16_t>(1, 1);
    EXPECT_EQ(result.upper, 0u);
    EXPECT_EQ(result.lower, 1u);
}

TEST_F(ExtendedMultTest_333, Uint16_MaxTimesMax_333) {
    // 65535 * 65535 = 4294836225 = 0xFFFE0001
    // upper = 0xFFFE = 65534, lower = 0x0001 = 1
    auto result = Catch::Detail::extendedMult<std::uint16_t>(65535, 65535);
    EXPECT_EQ(result.upper, 65534u);
    EXPECT_EQ(result.lower, 1u);
}

TEST_F(ExtendedMultTest_333, Uint16_MaxTimesOne_333) {
    auto result = Catch::Detail::extendedMult<std::uint16_t>(65535, 1);
    EXPECT_EQ(result.upper, 0u);
    EXPECT_EQ(result.lower, 65535u);
}

TEST_F(ExtendedMultTest_333, Uint16_256Times256_333) {
    // 256 * 256 = 65536 = 0x10000
    // upper = 1, lower = 0
    auto result = Catch::Detail::extendedMult<std::uint16_t>(256, 256);
    EXPECT_EQ(result.upper, 1u);
    EXPECT_EQ(result.lower, 0u);
}

TEST_F(ExtendedMultTest_333, Uint16_Commutativity_333) {
    auto result1 = Catch::Detail::extendedMult<std::uint16_t>(1234, 5678);
    auto result2 = Catch::Detail::extendedMult<std::uint16_t>(5678, 1234);
    EXPECT_EQ(result1.upper, result2.upper);
    EXPECT_EQ(result1.lower, result2.lower);
}

TEST_F(ExtendedMultTest_333, Uint16_KnownProduct_333) {
    // 1000 * 50000 = 50000000 = 0x02FAF080
    // upper = 0x02FA = 762, lower = 0xF080 = 61568
    auto result = Catch::Detail::extendedMult<std::uint16_t>(1000, 50000);
    EXPECT_EQ(result.upper, 762u);
    EXPECT_EQ(result.lower, 61568u);
}

TEST_F(ExtendedMultTest_333, Uint16_ZeroTimesMax_333) {
    auto result = Catch::Detail::extendedMult<std::uint16_t>(0, 65535);
    EXPECT_EQ(result.upper, 0u);
    EXPECT_EQ(result.lower, 0u);
}

// ==================== uint32_t tests ====================

TEST_F(ExtendedMultTest_333, Uint32_ZeroTimesZero_333) {
    auto result = Catch::Detail::extendedMult<std::uint32_t>(0u, 0u);
    EXPECT_EQ(result.upper, 0u);
    EXPECT_EQ(result.lower, 0u);
}

TEST_F(ExtendedMultTest_333, Uint32_OneTimesOne_333) {
    auto result = Catch::Detail::extendedMult<std::uint32_t>(1u, 1u);
    EXPECT_EQ(result.upper, 0u);
    EXPECT_EQ(result.lower, 1u);
}

TEST_F(ExtendedMultTest_333, Uint32_MaxTimesOne_333) {
    auto result = Catch::Detail::extendedMult<std::uint32_t>(0xFFFFFFFFu, 1u);
    EXPECT_EQ(result.upper, 0u);
    EXPECT_EQ(result.lower, 0xFFFFFFFFu);
}

TEST_F(ExtendedMultTest_333, Uint32_MaxTimesMax_333) {
    // 0xFFFFFFFF * 0xFFFFFFFF = 0xFFFFFFFE00000001
    // upper = 0xFFFFFFFE, lower = 0x00000001
    auto result = Catch::Detail::extendedMult<std::uint32_t>(0xFFFFFFFFu, 0xFFFFFFFFu);
    EXPECT_EQ(result.upper, 0xFFFFFFFEu);
    EXPECT_EQ(result.lower, 0x00000001u);
}

TEST_F(ExtendedMultTest_333, Uint32_MaxTimesTwo_333) {
    // 0xFFFFFFFF * 2 = 0x1FFFFFFFE
    // upper = 1, lower = 0xFFFFFFFE
    auto result = Catch::Detail::extendedMult<std::uint32_t>(0xFFFFFFFFu, 2u);
    EXPECT_EQ(result.upper, 1u);
    EXPECT_EQ(result.lower, 0xFFFFFFFEu);
}

TEST_F(ExtendedMultTest_333, Uint32_PowerOfTwo_333) {
    // 0x10000 * 0x10000 = 0x100000000
    // upper = 1, lower = 0
    auto result = Catch::Detail::extendedMult<std::uint32_t>(0x10000u, 0x10000u);
    EXPECT_EQ(result.upper, 1u);
    EXPECT_EQ(result.lower, 0u);
}

TEST_F(ExtendedMultTest_333, Uint32_Commutativity_333) {
    auto result1 = Catch::Detail::extendedMult<std::uint32_t>(123456u, 789012u);
    auto result2 = Catch::Detail::extendedMult<std::uint32_t>(789012u, 123456u);
    EXPECT_EQ(result1.upper, result2.upper);
    EXPECT_EQ(result1.lower, result2.lower);
}

TEST_F(ExtendedMultTest_333, Uint32_ZeroTimesMax_333) {
    auto result = Catch::Detail::extendedMult<std::uint32_t>(0u, 0xFFFFFFFFu);
    EXPECT_EQ(result.upper, 0u);
    EXPECT_EQ(result.lower, 0u);
}

TEST_F(ExtendedMultTest_333, Uint32_KnownProduct_333) {
    // 1000000000 * 3 = 3000000000 = 0xB2D05E00
    // This fits in 32 bits, so upper = 0
    auto result = Catch::Detail::extendedMult<std::uint32_t>(1000000000u, 3u);
    EXPECT_EQ(result.upper, 0u);
    EXPECT_EQ(result.lower, 3000000000u);
}

TEST_F(ExtendedMultTest_333, Uint32_LargeProduct_333) {
    // 1000000000 * 5 = 5000000000 = 0x12A05F200
    // upper = 1, lower = 0x2A05F200 = 705032704
    auto result = Catch::Detail::extendedMult<std::uint32_t>(1000000000u, 5u);
    EXPECT_EQ(result.upper, 1u);
    EXPECT_EQ(result.lower, 705032704u);
}

// ==================== Constexpr test ====================

TEST_F(ExtendedMultTest_333, ConstexprEvaluation_333) {
    constexpr auto result = Catch::Detail::extendedMult<std::uint8_t>(10, 20);
    static_assert(result.upper == 0, "upper should be 0");
    static_assert(result.lower == 200, "lower should be 200");
    EXPECT_EQ(result.upper, 0u);
    EXPECT_EQ(result.lower, 200u);
}

TEST_F(ExtendedMultTest_333, ConstexprEvaluation_Overflow_333) {
    constexpr auto result = Catch::Detail::extendedMult<std::uint8_t>(255, 255);
    static_assert(result.upper == 254, "upper should be 254");
    static_assert(result.lower == 1, "lower should be 1");
    EXPECT_EQ(result.upper, 254u);
    EXPECT_EQ(result.lower, 1u);
}

// ==================== Result reconstruction tests ====================

TEST_F(ExtendedMultTest_333, Uint8_ReconstructFullProduct_333) {
    std::uint8_t a = 123, b = 234;
    auto result = Catch::Detail::extendedMult(a, b);
    std::uint16_t full = (std::uint16_t(result.upper) << 8) | result.lower;
    EXPECT_EQ(full, std::uint16_t(a) * std::uint16_t(b));
}

TEST_F(ExtendedMultTest_333, Uint16_ReconstructFullProduct_333) {
    std::uint16_t a = 12345, b = 54321;
    auto result = Catch::Detail::extendedMult(a, b);
    std::uint32_t full = (std::uint32_t(result.upper) << 16) | result.lower;
    EXPECT_EQ(full, std::uint32_t(a) * std::uint32_t(b));
}

TEST_F(ExtendedMultTest_333, Uint32_ReconstructFullProduct_333) {
    std::uint32_t a = 123456789u, b = 987654321u;
    auto result = Catch::Detail::extendedMult(a, b);
    std::uint64_t full = (std::uint64_t(result.upper) << 32) | result.lower;
    EXPECT_EQ(full, std::uint64_t(a) * std::uint64_t(b));
}

// ==================== Identity element tests ====================

TEST_F(ExtendedMultTest_333, Uint8_MultiplyByOneIsIdentity_333) {
    for (unsigned i = 0; i < 256; ++i) {
        auto val = static_cast<std::uint8_t>(i);
        auto result = Catch::Detail::extendedMult(val, std::uint8_t(1));
        EXPECT_EQ(result.upper, 0u);
        EXPECT_EQ(result.lower, val);
    }
}

TEST_F(ExtendedMultTest_333, Uint8_MultiplyByZeroIsZero_333) {
    for (unsigned i = 0; i < 256; ++i) {
        auto val = static_cast<std::uint8_t>(i);
        auto result = Catch::Detail::extendedMult(val, std::uint8_t(0));
        EXPECT_EQ(result.upper, 0u);
        EXPECT_EQ(result.lower, 0u);
    }
}
