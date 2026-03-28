// File: tests/chrono_convert_tests_100.cpp

#include <gtest/gtest.h>
#include <chrono>
#include <string>

// Include the headers from the provided interface
#include "catch2/catch_tostring.hpp"  // for Catch::convert and ratio_string

namespace {

// Helper to build the expected string using only public interface elements.
template <typename Ratio, typename CountT>
std::string ExpectedDurationString(CountT count) {
    return std::to_string(count) + " " + Catch::ratio_string<Ratio>::symbol() + "s";
}

// Overload for floating counts to match default stream formatting used by Catch::convert
template <typename Ratio>
std::string ExpectedDurationString(double count) {
    // Use an ostringstream to mirror default formatting of operator<< for double
    std::ostringstream oss;
    oss << count;
    return oss.str() + " " + Catch::ratio_string<Ratio>::symbol() + "s";
}

} // namespace

// ----------------------- Normal operation -----------------------

TEST(ChronoConvertTest_100, ConvertsIntegralSeconds_100) {
    using Dur = std::chrono::duration<int, std::ratio<1>>;
    Dur d{42};

    const std::string actual = Catch::convert(d);
    const std::string expected = ExpectedDurationString<std::ratio<1>>(d.count());

    EXPECT_EQ(actual, expected);
}

TEST(ChronoConvertTest_100, ConvertsFractionalMilliseconds_100) {
    using Dur = std::chrono::duration<double, std::milli>;
    Dur d{1.5}; // 1.5 ms

    const std::string actual = Catch::convert(d);
    const std::string expected = ExpectedDurationString<std::milli>(d.count());

    EXPECT_EQ(actual, expected);
}

// ----------------------- Boundary conditions -----------------------

TEST(ChronoConvertTest_100, ConvertsZeroDuration_100) {
    using Dur = std::chrono::duration<int, std::ratio<60>>; // minutes-like ratio
    Dur d{0};

    const std::string actual = Catch::convert(d);
    const std::string expected = ExpectedDurationString<std::ratio<60>>(d.count());

    EXPECT_EQ(actual, expected);
}

TEST(ChronoConvertTest_100, ConvertsNegativeCount_100) {
    using Dur = std::chrono::duration<long long, std::ratio<60>>; // minutes-like ratio
    Dur d{-7};

    const std::string actual = Catch::convert(d);
    const std::string expected = ExpectedDurationString<std::ratio<60>>(d.count());

    EXPECT_EQ(actual, expected);
}

// ----------------------- Exceptional / edge-like cases (as observable) -----------------------

TEST(ChronoConvertTest_100, ConvertsVeryLargeHours_100) {
    using Dur = std::chrono::duration<unsigned long long, std::ratio<3600>>; // hours-like ratio
    // Use a large value to ensure formatting handles big integers
    Dur d{123456789ULL};

    const std::string actual = Catch::convert(d);
    const std::string expected =
        ExpectedDurationString<std::ratio<3600>>(static_cast<unsigned long long>(d.count()));

    EXPECT_EQ(actual, expected);
}

// ----------------------- Generic ratio (non-specialized) -----------------------

TEST(ChronoConvertTest_100, ConvertsCustomRatioSeven_100) {
    using seven = std::ratio<7, 1>;
    using Dur = std::chrono::duration<int, seven>;
    Dur d{3};

    const std::string actual = Catch::convert(d);
    const std::string expected = ExpectedDurationString<seven>(d.count());

    EXPECT_EQ(actual, expected);
}

