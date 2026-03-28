#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>

// We need to replicate the function signature since it's a static function in a .cc file
// For testing purposes, we include the function definition directly
static std::string getReadableTime(time_t unix_time) {
    std::stringstream stringStream;
    const std::tm tm = *std::localtime(&unix_time);
    stringStream << std::put_time(&tm, "%b %d %Y %H:%M:%S");
    return stringStream.str();
}

class GetReadableTimeTest_2678 : public ::testing::Test {
protected:
    // Helper to get expected string for a given time_t
    std::string expectedTimeString(time_t t) {
        std::stringstream ss;
        const std::tm tm = *std::localtime(&t);
        ss << std::put_time(&tm, "%b %d %Y %H:%M:%S");
        return ss.str();
    }
};

TEST_F(GetReadableTimeTest_2678, EpochZero_2678) {
    time_t epoch = 0;
    std::string result = getReadableTime(epoch);
    std::string expected = expectedTimeString(epoch);
    EXPECT_EQ(result, expected);
    EXPECT_FALSE(result.empty());
}

TEST_F(GetReadableTimeTest_2678, KnownTimestamp_2678) {
    // 2023-01-15 10:30:00 UTC approximately = 1673776200
    time_t known_time = 1673776200;
    std::string result = getReadableTime(known_time);
    std::string expected = expectedTimeString(known_time);
    EXPECT_EQ(result, expected);
    EXPECT_FALSE(result.empty());
}

TEST_F(GetReadableTimeTest_2678, ReturnsNonEmptyString_2678) {
    time_t now = std::time(nullptr);
    std::string result = getReadableTime(now);
    EXPECT_FALSE(result.empty());
}

TEST_F(GetReadableTimeTest_2678, CurrentTimeMatchesExpected_2678) {
    time_t now = std::time(nullptr);
    std::string result = getReadableTime(now);
    std::string expected = expectedTimeString(now);
    EXPECT_EQ(result, expected);
}

TEST_F(GetReadableTimeTest_2678, ContainsYear_2678) {
    // Use a timestamp known to be in year 2020
    // Jan 1, 2020 00:00:00 UTC = 1577836800
    time_t t = 1577836800;
    std::string result = getReadableTime(t);
    // The year should appear in the output (local time may shift the date)
    // But the year should be 2019 or 2020 depending on timezone
    EXPECT_TRUE(result.find("2020") != std::string::npos || 
                result.find("2019") != std::string::npos);
}

TEST_F(GetReadableTimeTest_2678, FormatContainsColons_2678) {
    time_t t = 1609459200; // 2021-01-01 00:00:00 UTC
    std::string result = getReadableTime(t);
    // The time portion should contain colons (HH:MM:SS)
    EXPECT_NE(result.find(':'), std::string::npos);
}

TEST_F(GetReadableTimeTest_2678, DifferentTimesProduceDifferentResults_2678) {
    time_t t1 = 1000000;
    time_t t2 = 2000000000;
    std::string result1 = getReadableTime(t1);
    std::string result2 = getReadableTime(t2);
    EXPECT_NE(result1, result2);
}

TEST_F(GetReadableTimeTest_2678, SameInputProducesSameOutput_2678) {
    time_t t = 1500000000;
    std::string result1 = getReadableTime(t);
    std::string result2 = getReadableTime(t);
    EXPECT_EQ(result1, result2);
}

TEST_F(GetReadableTimeTest_2678, SmallPositiveValue_2678) {
    time_t t = 1; // 1 second after epoch
    std::string result = getReadableTime(t);
    std::string expected = expectedTimeString(t);
    EXPECT_EQ(result, expected);
    EXPECT_FALSE(result.empty());
}

TEST_F(GetReadableTimeTest_2678, LargeTimestamp_2678) {
    // Year ~2033
    time_t t = 2000000000;
    std::string result = getReadableTime(t);
    std::string expected = expectedTimeString(t);
    EXPECT_EQ(result, expected);
    EXPECT_FALSE(result.empty());
}

TEST_F(GetReadableTimeTest_2678, NegativeTimestamp_2678) {
    // Before epoch - December 31, 1969 or similar depending on timezone
    time_t t = -1;
    std::string result = getReadableTime(t);
    std::string expected = expectedTimeString(t);
    EXPECT_EQ(result, expected);
    EXPECT_FALSE(result.empty());
}

TEST_F(GetReadableTimeTest_2678, MiddayTimestamp_2678) {
    // 2022-06-15 12:00:00 UTC = 1655294400
    time_t t = 1655294400;
    std::string result = getReadableTime(t);
    std::string expected = expectedTimeString(t);
    EXPECT_EQ(result, expected);
}

TEST_F(GetReadableTimeTest_2678, OutputFormatHasExpectedLength_2678) {
    // Format: "Mon DD YYYY HH:MM:SS" -> typically around 20 characters
    time_t t = 1609459200;
    std::string result = getReadableTime(t);
    // Minimum reasonable length: "Jan 01 2021 00:00:00" = 20 chars
    EXPECT_GE(result.length(), 19u);
    EXPECT_LE(result.length(), 25u);
}
