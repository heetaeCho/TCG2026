// File: convert_hours_to_string_103_tests.cpp

#include <gtest/gtest.h>
#include <chrono>
#include <limits>
#include <string>

// Include header under test (adjust include path to your repo layout)
#include "catch2/catch_tostring.hpp"

using namespace std::chrono;

class CatchToStringConvertHoursTest_103 : public ::testing::Test {};

TEST_F(CatchToStringConvertHoursTest_103, ConvertsZeroHours_103) {
    auto d = hours{0};
    std::string s = Catch::convert(d);
    EXPECT_EQ(s, "0 h");
}

TEST_F(CatchToStringConvertHoursTest_103, ConvertsPositiveHours_103) {
    auto d = hours{24};
    std::string s = Catch::convert(d);
    EXPECT_EQ(s, "24 h");
}

TEST_F(CatchToStringConvertHoursTest_103, ConvertsNegativeHours_103) {
    auto d = hours{-3};
    std::string s = Catch::convert(d);
    EXPECT_EQ(s, "-3 h");
}

TEST_F(CatchToStringConvertHoursTest_103, PreservesFloatingPointHours_103) {
    // Use explicit duration with ratio<3600> and floating representation
    std::chrono::duration<double, std::ratio<3600>> d{1.5};
    std::string s = Catch::convert(d);
    EXPECT_EQ(s, "1.5 h");
}

TEST_F(CatchToStringConvertHoursTest_103, HandlesVeryLargeHourCounts_103) {
    using LLHours = std::chrono::duration<long long, std::ratio<3600>>;
    const auto big = std::numeric_limits<long long>::max();
    std::string s = Catch::convert(LLHours{big});

    // Expected string is "<max> h"
    std::string expected = std::to_string(big) + " h";
    EXPECT_EQ(s, expected);
}

TEST_F(CatchToStringConvertHoursTest_103, FormatIsNumberSpaceH_103) {
    auto d = hours{7};
    std::string s = Catch::convert(d);

    ASSERT_FALSE(s.empty());
    // Ends with 'h' and has exactly one space before 'h'
    EXPECT_EQ(s.back(), 'h');
    ASSERT_GE(s.size(), 3u);                    // at least "0 h"
    EXPECT_EQ(s[s.size() - 2], ' ');
    // The part before the space should be the raw count
    EXPECT_EQ(s.substr(0, s.size() - 2), "7");
}
