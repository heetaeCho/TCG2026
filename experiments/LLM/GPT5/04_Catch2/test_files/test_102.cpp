// File: test_convert_minutes_102.cpp

#include <gtest/gtest.h>
#include <chrono>

// Include the header under test
#include "Catch2/src/catch2/catch_tostring.hpp"

using namespace std::chrono;

// Fixture kept simple for naming consistency & future extension
class ConvertMinutesTest_102 : public ::testing::Test {};

// Normal operation: small positive minutes
TEST_F(ConvertMinutesTest_102, FormatsWholeMinutes_102) {
    EXPECT_EQ(Catch::convert(minutes{5}), "5 m");
    EXPECT_EQ(Catch::convert(minutes{1}), "1 m");
    EXPECT_EQ(Catch::convert(minutes{123}), "123 m");
}

// Boundary: zero minutes
TEST_F(ConvertMinutesTest_102, FormatsZeroMinutes_102) {
    EXPECT_EQ(Catch::convert(minutes{0}), "0 m");
}

// Boundary: negative minutes (if supported by the interface type)
TEST_F(ConvertMinutesTest_102, FormatsNegativeMinutes_102) {
    EXPECT_EQ(Catch::convert(minutes{-12}), "-12 m");
}

// Large value: ensure formatting scales to big integral counts
TEST_F(ConvertMinutesTest_102, FormatsLargeMinutes_102) {
    // Keep within long long to avoid UB while still being large
    const long long big = 1000000000LL; // 1e9 minutes
    EXPECT_EQ(Catch::convert(minutes{big}), "1000000000 m");
}

// Type coverage: other integral reps that are compatible with ratio<60>
TEST_F(ConvertMinutesTest_102, AcceptsDifferentIntegralRepTypes_102) {
    // duration<int, ratio<60>> is still "minutes"-like; verify consistent formatting
    std::chrono::duration<int, std::ratio<60>> mins_int{42};
    EXPECT_EQ(Catch::convert(mins_int), "42 m");

    std::chrono::duration<short, std::ratio<60>> mins_short{7};
    EXPECT_EQ(Catch::convert(mins_short), "7 m");
}
