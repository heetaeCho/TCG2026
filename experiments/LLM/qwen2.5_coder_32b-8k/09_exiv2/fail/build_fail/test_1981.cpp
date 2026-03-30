#include <gtest/gtest.h>

#include "XMP_Const.h"

#include <ctime>



// Assuming the FormatFullDateTime function is part of a class or namespace for testing purposes.

// Since it's a static function and not part of any class in the provided code, we will test it directly.



TEST(FormatFullDateTimeTest_1981, NormalOperation_SecondAndNanoSecondZero_1981) {

    XMP_DateTime tempDate = {2023, 10, 5, 14, 30, 0, 0, 0, 0};

    char buffer[100];

    FormatFullDateTime(tempDate, buffer, sizeof(buffer));

    EXPECT_STREQ(buffer, "2023-10-05T14:30");

}



TEST(FormatFullDateTimeTest_1981, NormalOperation_SecondNonZeroNanoSecondZero_1981) {

    XMP_DateTime tempDate = {2023, 10, 5, 14, 30, 45, 0, 0, 0};

    char buffer[100];

    FormatFullDateTime(tempDate, buffer, sizeof(buffer));

    EXPECT_STREQ(buffer, "2023-10-05T14:30:45");

}



TEST(FormatFullDateTimeTest_1981, NormalOperation_SecondAndNanoSecondNonZero_1981) {

    XMP_DateTime tempDate = {2023, 10, 5, 14, 30, 45, 0, 0, 123456789};

    char buffer[100];

    FormatFullDateTime(tempDate, buffer, sizeof(buffer));

    EXPECT_STREQ(buffer, "2023-10-05T14:30:45.123456789");

}



TEST(FormatFullDateTimeTest_1981, BoundaryCondition_ZeroNanoSecondsTrimming_1981) {

    XMP_DateTime tempDate = {2023, 10, 5, 14, 30, 45, 0, 0, 123456700};

    char buffer[100];

    FormatFullDateTime(tempDate, buffer, sizeof(buffer));

    EXPECT_STREQ(buffer, "2023-10-05T14:30:45.1234567");

}



TEST(FormatFullDateTimeTest_1981, BoundaryCondition_MaxNanoSecondsNoTrimming_1981) {

    XMP_DateTime tempDate = {2023, 10, 5, 14, 30, 45, 0, 0, 999999999};

    char buffer[100];

    FormatFullDateTime(tempDate, buffer, sizeof(buffer));

    EXPECT_STREQ(buffer, "2023-10-05T14:30:45.999999999");

}



TEST(FormatFullDateTimeTest_1981, ErrorCase_BufferTooSmall_1981) {

    XMP_DateTime tempDate = {2023, 10, 5, 14, 30, 45, 0, 0, 123456789};

    char buffer[20]; // Buffer is too small to hold the full date string

    FormatFullDateTime(tempDate, buffer, sizeof(buffer));

    EXPECT_TRUE(strlen(buffer) < 20); // Buffer should not be filled completely due to size limitation

}



TEST(FormatFullDateTimeTest_1981, NormalOperation_NegativeNanoSeconds_1981) {

    XMP_DateTime tempDate = {2023, 10, 5, 14, 30, 45, 0, 0, -1};

    char buffer[100];

    FormatFullDateTime(tempDate, buffer, sizeof(buffer));

    EXPECT_STREQ(buffer, "2023-10-05T14:30:45");

}



TEST(FormatFullDateTimeTest_1981, NormalOperation_NegativeSeconds_1981) {

    XMP_DateTime tempDate = {2023, 10, 5, 14, 30, -1, 0, 0, 123456789};

    char buffer[100];

    FormatFullDateTime(tempDate, buffer, sizeof(buffer));

    EXPECT_STREQ(buffer, "2023-10-05T14:30");

}
