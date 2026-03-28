// File: stringmaker_long_convert_tests_270.cpp
#include <gtest/gtest.h>
#include <limits>
#include "catch2/catch_tostring.hpp"  // Interface under test

// The tests verify observable behavior only:
// - For any given numeric value V representable as long,
//   StringMaker<long>::convert(V) should match
//   StringMaker<long long>::convert(static_cast<long long>(V)).
// This focuses on cross-overload consistency, without assuming
// any particular formatting logic or accessing internals.

using Catch::StringMaker;

namespace {

TEST(StringMakerLongTest_270, ConvertsZero_MatchesLongLong_270) {
    long v = 0L;
    const std::string as_long      = StringMaker<long>::convert(v);
    const std::string as_long_long = StringMaker<long long>::convert(static_cast<long long>(v));
    EXPECT_EQ(as_long, as_long_long);
}

TEST(StringMakerLongTest_270, ConvertsPositive_MatchesLongLong_270) {
    long v = 42L;
    const std::string as_long      = StringMaker<long>::convert(v);
    const std::string as_long_long = StringMaker<long long>::convert(static_cast<long long>(v));
    EXPECT_EQ(as_long, as_long_long);
}

TEST(StringMakerLongTest_270, ConvertsNegative_MatchesLongLong_270) {
    long v = -12345L;
    const std::string as_long      = StringMaker<long>::convert(v);
    const std::string as_long_long = StringMaker<long long>::convert(static_cast<long long>(v));
    EXPECT_EQ(as_long, as_long_long);
}

TEST(StringMakerLongTest_270, ConvertsLongMax_MatchesLongLong_270) {
    const long v = std::numeric_limits<long>::max();
    const std::string as_long      = StringMaker<long>::convert(v);
    const std::string as_long_long = StringMaker<long long>::convert(static_cast<long long>(v));
    EXPECT_EQ(as_long, as_long_long);
}

TEST(StringMakerLongTest_270, ConvertsLongMin_MatchesLongLong_270) {
    const long v = std::numeric_limits<long>::min();
    const std::string as_long      = StringMaker<long>::convert(v);
    const std::string as_long_long = StringMaker<long long>::convert(static_cast<long long>(v));
    EXPECT_EQ(as_long, as_long_long);
}

// A small smoke test across various boundary-ish values to cover more cases
TEST(StringMakerLongTest_270, VarietyOfValues_MatchLongLong_270) {
    const long samples[] = {
        0L, 1L, -1L, 7L, -7L, 99L, -99L,
        std::numeric_limits<long>::max(),
        std::numeric_limits<long>::max() - 1,
        std::numeric_limits<long>::min(),
        std::numeric_limits<long>::min() + 1
    };

    for (long v : samples) {
        const std::string as_long      = StringMaker<long>::convert(v);
        const std::string as_long_long = StringMaker<long long>::convert(static_cast<long long>(v));
        EXPECT_EQ(as_long, as_long_long) << "Mismatch for value: " << v;
    }
}

} // namespace
