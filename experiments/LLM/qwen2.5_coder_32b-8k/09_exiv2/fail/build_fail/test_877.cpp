#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "value.cpp" // Assuming the partial implementation is in this file



namespace Exiv2 {



class TimeValueTest_877 : public ::testing::Test {

protected:

    TimeValue time_value;



    void SetUp() override {

        // Initialize time_value with default or known values if necessary

        time_value.time_.hour = 10;

        time_value.time_.minute = 30;

        time_value.time_.second = 45;

        time_value.time_.tzHour = -2;

        time_value.time_.tzMinute = 15;

    }

};



TEST_F(TimeValueTest_877, CopyFormatsTimeCorrectly_877) {

    byte buffer[12] = {0}; // Buffer to hold the formatted string

    size_t bytes_written = time_value.copy(buffer, ByteOrder::bigEndian);

    EXPECT_EQ(bytes_written, 11U);

    EXPECT_STREQ(reinterpret_cast<char*>(buffer), "103045-0215");

}



TEST_F(TimeValueTest_877, CopyFormatsPositiveTimezone_877) {

    time_value.time_.tzHour = 3;

    time_value.time_.tzMinute = 45;

    byte buffer[12] = {0}; // Buffer to hold the formatted string

    size_t bytes_written = time_value.copy(buffer, ByteOrder::bigEndian);

    EXPECT_EQ(bytes_written, 11U);

    EXPECT_STREQ(reinterpret_cast<char*>(buffer), "103045+0345");

}



TEST_F(TimeValueTest_877, CopyFormatsZeroTimezone_877) {

    time_value.time_.tzHour = 0;

    time_value.time_.tzMinute = 0;

    byte buffer[12] = {0}; // Buffer to hold the formatted string

    size_t bytes_written = time_value.copy(buffer, ByteOrder::bigEndian);

    EXPECT_EQ(bytes_written, 11U);

    EXPECT_STREQ(reinterpret_cast<char*>(buffer), "103045+0000");

}



TEST_F(TimeValueTest_877, CopyHandlesMaxTimeValues_877) {

    time_value.time_.hour = 23;

    time_value.time_.minute = 59;

    time_value.time_.second = 59;

    byte buffer[12] = {0}; // Buffer to hold the formatted string

    size_t bytes_written = time_value.copy(buffer, ByteOrder::bigEndian);

    EXPECT_EQ(bytes_written, 11U);

    EXPECT_STREQ(reinterpret_cast<char*>(buffer), "235959-0215");

}



TEST_F(TimeValueTest_877, CopyThrowsOnInsufficientBuffer_877) {

    byte buffer[10] = {0}; // Buffer too small to hold the formatted string

    EXPECT_THROW(time_value.copy(buffer, ByteOrder::bigEndian), Exiv2Error);

}



}  // namespace Exiv2
