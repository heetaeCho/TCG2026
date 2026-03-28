// tests/stringmaker_unsigned_long_convert_273_tests.cpp
#include <gtest/gtest.h>
#include <limits>
#include <vector>

// Include Catch2 headers as available in your project include paths
#include "catch2/catch_tostring.hpp"

namespace {

using UL  = unsigned long;
using ULL = unsigned long long;

// Test fixture kept minimal for clarity/consistency.
class StringMakerUnsignedLongTest_273 : public ::testing::Test {};

// --- Normal operation --------------------------------------------------------

TEST_F(StringMakerUnsignedLongTest_273, ConvertsZero_MatchesULL_273) {
    UL value = 0UL;
    const std::string as_ul  = Catch::StringMaker<UL>::convert(value);
    const std::string as_ull = Catch::StringMaker<ULL>::convert(static_cast<ULL>(value));
    EXPECT_EQ(as_ul, as_ull);
}

TEST_F(StringMakerUnsignedLongTest_273, ConvertsSmallNumber_MatchesULL_273) {
    UL value = static_cast<UL>(42);
    const std::string as_ul  = Catch::StringMaker<UL>::convert(value);
    const std::string as_ull = Catch::StringMaker<ULL>::convert(static_cast<ULL>(value));
    EXPECT_EQ(as_ul, as_ull);
}

// --- Boundary conditions -----------------------------------------------------

TEST_F(StringMakerUnsignedLongTest_273, ConvertsMaxUnsignedLong_MatchesULL_273) {
    const UL value = std::numeric_limits<UL>::max();
    const std::string as_ul  = Catch::StringMaker<UL>::convert(value);
    const std::string as_ull = Catch::StringMaker<ULL>::convert(static_cast<ULL>(value));
    EXPECT_EQ(as_ul, as_ull);
}

TEST_F(StringMakerUnsignedLongTest_273, ConvertsMaxMinusOne_MatchesULL_273) {
    const UL max_ul = std::numeric_limits<UL>::max();
    const UL value = max_ul - static_cast<UL>(1);
    const std::string as_ul  = Catch::StringMaker<UL>::convert(value);
    const std::string as_ull = Catch::StringMaker<ULL>::convert(static_cast<ULL>(value));
    EXPECT_EQ(as_ul, as_ull);
}

// --- Additional representative values ---------------------------------------

TEST_F(StringMakerUnsignedLongTest_273, ConvertsSeveralRepresentativeValues_MatchULL_273) {
    const UL max_ul = std::numeric_limits<UL>::max();
    // Choose a spread of values without assuming formatting details.
    std::vector<UL> samples = {
        static_cast<UL>(1),
        static_cast<UL>(10),
        static_cast<UL>(123456u),
        static_cast<UL>(max_ul / 2u),
        static_cast<UL>(max_ul / 3u),
        static_cast<UL>(max_ul / 10u * 7u) // another mid-range value
    };

    for (UL v : samples) {
        const std::string as_ul  = Catch::StringMaker<UL>::convert(v);
        const std::string as_ull = Catch::StringMaker<ULL>::convert(static_cast<ULL>(v));
        EXPECT_EQ(as_ul, as_ull) << "Mismatch for value: " << v;
    }
}

} // namespace
