// File: parse_uint_tests_580.cpp
#include <gtest/gtest.h>
#include <string>
#include <limits>

namespace Catch {
    // Forward declaration only; we do NOT re-implement anything.
    template <typename T> class Optional;
    Optional<unsigned int> parseUInt(std::string const& input, int base);
}

class ParseUIntTest_580 : public ::testing::Test {};

// --- Normal operation ---

TEST_F(ParseUIntTest_580, ParsesSimpleDecimal_580) {
    auto r = Catch::parseUInt("123", 10);
    ASSERT_TRUE(r.has_value());
    EXPECT_EQ(r.value(), 123u);
}

TEST_F(ParseUIntTest_580, TrimsWhitespaceAroundNumber_580) {
    auto r = Catch::parseUInt(" \t 42  \n", 10);
    ASSERT_TRUE(r.has_value());
    EXPECT_EQ(r.value(), 42u);
}

TEST_F(ParseUIntTest_580, AcceptsLeadingPlusSign_580) {
    auto r = Catch::parseUInt("+7", 10);
    ASSERT_TRUE(r.has_value());
    EXPECT_EQ(r.value(), 7u);
}

TEST_F(ParseUIntTest_580, AutoDetectBaseWithZero_ParsesOctalLike077_580) {
    auto r = Catch::parseUInt("077", 0); // base 0 -> autodetect (“077” -> octal -> 63)
    ASSERT_TRUE(r.has_value());
    EXPECT_EQ(r.value(), 63u);
}

TEST_F(ParseUIntTest_580, ParsesHexInBase16_WithoutPrefix_580) {
    auto r = Catch::parseUInt("FF", 16);
    ASSERT_TRUE(r.has_value());
    EXPECT_EQ(r.value(), 255u);
}

TEST_F(ParseUIntTest_580, ParsesHexInBase16_With0xPrefix_580) {
    auto r = Catch::parseUInt("0x10", 16);
    ASSERT_TRUE(r.has_value());
    EXPECT_EQ(r.value(), 16u);
}

// --- Boundary cases ---

TEST_F(ParseUIntTest_580, AcceptsExactlyUintMax_580) {
    const auto maxStr = std::to_string(std::numeric_limits<unsigned int>::max());
    auto r = Catch::parseUInt(maxStr, 10);
    ASSERT_TRUE(r.has_value());
    EXPECT_EQ(r.value(), std::numeric_limits<unsigned int>::max());
}

TEST_F(ParseUIntTest_580, RejectsValueGreaterThanUintMax_580) {
    // Build string for UINT_MAX + 1 in a wider type
    const unsigned long long tooBig =
        static_cast<unsigned long long>(std::numeric_limits<unsigned int>::max()) + 1ULL;
    const auto s = std::to_string(tooBig);

    auto r = Catch::parseUInt(s, 10);
    EXPECT_FALSE(r.has_value());
}

// --- Error / exceptional inputs (observable via empty optional) ---

TEST_F(ParseUIntTest_580, EmptyStringReturnsEmpty_580) {
    auto r = Catch::parseUInt("", 10);
    EXPECT_FALSE(r.has_value());
}

TEST_F(ParseUIntTest_580, NegativeNumberIsRejected_580) {
    auto r = Catch::parseUInt("-1", 10);
    EXPECT_FALSE(r.has_value());
}

TEST_F(ParseUIntTest_580, NonNumericInputIsRejected_580) {
    auto r = Catch::parseUInt("abc", 10);
    EXPECT_FALSE(r.has_value());
}

TEST_F(ParseUIntTest_580, TrailingGarbageCausesReject_580) {
    auto r = Catch::parseUInt("123abc", 10);
    EXPECT_FALSE(r.has_value());
}

TEST_F(ParseUIntTest_580, InvalidBaseCausesReject_580) {
    // std::stoull would throw for invalid base; function should return empty
    auto r = Catch::parseUInt("10", 1); // base < 2 is invalid
    EXPECT_FALSE(r.has_value());
}

TEST_F(ParseUIntTest_580, OutOfRangeDecimalCausesReject_580) {
    // A very large decimal (many digits) should be treated as out-of-range -> empty
    auto r = Catch::parseUInt("18446744073709551616", 10); // > 2^64-1
    EXPECT_FALSE(r.has_value());
}
