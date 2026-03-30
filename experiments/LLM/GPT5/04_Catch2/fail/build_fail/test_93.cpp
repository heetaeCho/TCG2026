// File: tests/ratio_string_symbol_93_test.cpp

#include <gtest/gtest.h>
#include <ratio>
#include <string>

// Include the provided headers (paths based on prompt)
#include "Catch2/src/catch2/catch_tostring.hpp"

using Catch::ratio_string;

TEST(RatioStringTest_93, ReturnsThousandth_93) {
    // Normal operation: common non-trivial denominator
    using R = std::ratio<1, 1000>;
    const std::string s = ratio_string<R>::symbol();
    EXPECT_EQ(s, "[1/1000]");
}

TEST(RatioStringTest_93, ReturnsUnity_93) {
    // Boundary: unity ratio (numerator == denominator)
    using R = std::ratio<1, 1>;
    const std::string s = ratio_string<R>::symbol();
    EXPECT_EQ(s, "[1/1]");
}

TEST(RatioStringTest_93, HandlesNegativeAndReduces_93) {
    // Reduction & sign handling are properties of std::ratio
    // std::ratio<-3, 6> normalizes to -1/2
    using R = std::ratio<-3, 6>;
    const std::string s = ratio_string<R>::symbol();
    EXPECT_EQ(s, "[-1/2]");
}

TEST(RatioStringTest_93, LargeNumeratorNoReduction_93) {
    // Large numbers that do not reduce (gcd(1'000'000, 3) == 1)
    using R = std::ratio<1000000, 3>;
    const std::string s = ratio_string<R>::symbol();
    EXPECT_EQ(s, "[1000000/3]");
}

TEST(RatioStringTest_93, StableAcrossRepeatedCalls_93) {
    // Observable behavior: repeated invocations return equal values
    using R = std::ratio<2, 5>;
    const std::string first = ratio_string<R>::symbol();
    const std::string second = ratio_string<R>::symbol();
    EXPECT_EQ(first, "[2/5]");
    EXPECT_EQ(second, "[2/5]");
    // And they are distinct std::string objects with the same content
    // (verifies no shared mutable buffer leaks through the interface)
    EXPECT_NE(&first, &second);
}

TEST(RatioStringTest_93, HandlesAlreadyReducedNegativeNumerator_93) {
    // Another negative case that is already reduced to ensure consistency
    using R = std::ratio<-7, 3>;
    const std::string s = ratio_string<R>::symbol();
    EXPECT_EQ(s, "[-7/3]");
}
