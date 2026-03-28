// File: tests/convert_seconds_tests_101.cpp
#include <gtest/gtest.h>
#include <chrono>
#include <string>

// Include the header that declares Catch::convert overloads
// Adjust the include path to match your project layout if needed.
#include "Catch2/src/catch2/catch_tostring.hpp"

using namespace std::chrono;

//
// Test suite: convert(std::chrono::duration<*, std::ratio<1>>) -> "<count> s"
//
TEST(ConvertSecondsTest_101, FormatsPositiveIntegralSeconds_101) {
    // Normal operation: integral count
    duration<long long, std::ratio<1>> d{5}; // 5 seconds
    std::string out = Catch::convert(d);
    EXPECT_EQ(out, "5 s");
}

TEST(ConvertSecondsTest_101, FormatsZeroSeconds_101) {
    // Boundary: zero
    duration<int, std::ratio<1>> d{0};
    std::string out = Catch::convert(d);
    EXPECT_EQ(out, "0 s");
}

TEST(ConvertSecondsTest_101, FormatsNegativeIntegralSeconds_101) {
    // Exceptional-ish but valid: negative duration with signed rep
    duration<int, std::ratio<1>> d{-3};
    std::string out = Catch::convert(d);
    EXPECT_EQ(out, "-3 s");
}

TEST(ConvertSecondsTest_101, FormatsFloatingPointSeconds_101) {
    // Normal operation: floating-point rep should stream as-is
    duration<double, std::ratio<1>> d{1.5};
    std::string out = Catch::convert(d);
    // Expect exact streamed value followed by " s"
    EXPECT_EQ(out, "1.5 s");
}

TEST(ConvertSecondsTest_101, FormatsLargeIntegralSeconds_101) {
    // Boundary: very large positive value
    duration<long long, std::ratio<1>> d{std::numeric_limits<long long>::max()};
    std::string out = Catch::convert(d);
    // Build expected via standard streaming of the count (observable behavior)
    std::ostringstream oss;
    oss << std::numeric_limits<long long>::max() << " s";
    EXPECT_EQ(out, oss.str());
}
