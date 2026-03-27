// File: catch_to_string_tests_195.cpp
#include <gtest/gtest.h>
#include <string>
#include <limits>
#include <cstdint>

// Include the header under test
#include "Catch2/src/catch2/internal/catch_to_string.hpp"

using Catch::to_string;

TEST(CatchToString_195, IntZero_195) {
    int v = 0;
    EXPECT_EQ(to_string(v), std::to_string(v));
}

TEST(CatchToString_195, IntPositive_195) {
    int v = 42;
    EXPECT_EQ(to_string(v), std::to_string(v));
}

TEST(CatchToString_195, IntNegative_195) {
    int v = -17;
    EXPECT_EQ(to_string(v), std::to_string(v));
}

TEST(CatchToString_195, LongLongMax_195) {
    long long v = std::numeric_limits<long long>::max();
    EXPECT_EQ(to_string(v), std::to_string(v));
}

TEST(CatchToString_195, LongLongMin_195) {
    long long v = std::numeric_limits<long long>::min();
    EXPECT_EQ(to_string(v), std::to_string(v));
}

TEST(CatchToString_195, UnsignedLongLongMax_195) {
    unsigned long long v = std::numeric_limits<unsigned long long>::max();
    EXPECT_EQ(to_string(v), std::to_string(v));
}
