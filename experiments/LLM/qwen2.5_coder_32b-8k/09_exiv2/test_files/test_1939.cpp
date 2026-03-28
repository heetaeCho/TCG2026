#include <gtest/gtest.h>

#include "WXMPUtils.hpp"



class WXMPUtils_ConvertFromDate_Test_1939 : public ::testing::Test {

protected:

    XMP_DateTime binValue;

    XMP_StringPtr strValue = nullptr;

    XMP_StringLen strSize = 0;

    WXMP_Result wResult;



    void SetUp() override {

        // Initialize with a default date value

        binValue.year = 2023;

        binValue.month = 10;

        binValue.day = 5;

        binValue.hour = 14;

        binValue.minute = 30;

        binValue.second = 45;

        binValue.tzSign = 1; // Positive

        binValue.tzHour = 2;

        binValue.tzMinute = 0;

        binValue.nanoSecond = 123456789;

    }



    void TearDown() override {

        if (strValue) {

            free(const_cast<char*>(strValue)); // Assuming strValue is dynamically allocated

            strValue = nullptr;

            strSize = 0;

        }

    }

};



TEST_F(WXMPUtils_ConvertFromDate_Test_1939, NormalOperation_1939) {

    WXMPUtils_ConvertFromDate_1(binValue, &strValue, &strSize, &wResult);

    EXPECT_NE(strValue, nullptr);

    EXPECT_GT(strSize, 0);

    // Example: "2023-10-05T14:30:45+02:00"

    EXPECT_STREQ(strValue, "2023-10-05T14:30:45+02:00");

}



TEST_F(WXMPUtils_ConvertFromDate_Test_1939, BoundaryConditions_ZeroTimezone_1939) {

    binValue.tzSign = 0;

    WXMPUtils_ConvertFromDate_1(binValue, &strValue, &strSize, &wResult);

    EXPECT_NE(strValue, nullptr);

    EXPECT_GT(strSize, 0);

    // Example: "2023-10-05T14:30:45Z"

    EXPECT_STREQ(strValue, "2023-10-05T14:30:45Z");

}



TEST_F(WXMPUtils_ConvertFromDate_Test_1939, BoundaryConditions_NegativeTimezone_1939) {

    binValue.tzSign = -1; // Negative

    WXMPUtils_ConvertFromDate_1(binValue, &strValue, &strSize, &wResult);

    EXPECT_NE(strValue, nullptr);

    EXPECT_GT(strSize, 0);

    // Example: "2023-10-05T14:30:45-02:00"

    EXPECT_STREQ(strValue, "2023-10-05T14:30:45-02:00");

}



TEST_F(WXMPUtils_ConvertFromDate_Test_1939, NullStrValuePtr_1939) {

    WXMPUtils_ConvertFromDate_1(binValue, nullptr, &strSize, &wResult);

    EXPECT_EQ(strValue, voidStringPtr); // Assuming voidStringPtr is a global null placeholder

    EXPECT_EQ(strSize, 0);

}



TEST_F(WXMPUtils_ConvertFromDate_Test_1939, NullStrSizePtr_1939) {

    WXMPUtils_ConvertFromDate_1(binValue, &strValue, nullptr, &wResult);

    EXPECT_NE(strValue, nullptr);

    EXPECT_GT(strSize, 0);

}



TEST_F(WXMPUtils_ConvertFromDate_Test_1939, NullWResultPtr_1939) {

    WXMP_Result* nullResult = nullptr;

    WXMPUtils_ConvertFromDate_1(binValue, &strValue, &strSize, nullResult);

    EXPECT_NE(strValue, nullptr);

    EXPECT_GT(strSize, 0);

}



TEST_F(WXMPUtils_ConvertFromDate_Test_1939, LeapYearDate_1939) {

    binValue.year = 2024; // Leap year

    binValue.month = 2;

    binValue.day = 29;

    WXMPUtils_ConvertFromDate_1(binValue, &strValue, &strSize, &wResult);

    EXPECT_NE(strValue, nullptr);

    EXPECT_GT(strSize, 0);

    // Example: "2024-02-29T14:30:45+02:00"

    EXPECT_STREQ(strValue, "2024-02-29T14:30:45+02:00");

}



TEST_F(WXMPUtils_ConvertFromDate_Test_1939, NonLeapYearDate_1939) {

    binValue.year = 2023; // Non-leap year

    binValue.month = 2;

    binValue.day = 28;

    WXMPUtils_ConvertFromDate_1(binValue, &strValue, &strSize, &wResult);

    EXPECT_NE(strValue, nullptr);

    EXPECT_GT(strSize, 0);

    // Example: "2023-02-28T14:30:45+02:00"

    EXPECT_STREQ(strValue, "2023-02-28T14:30:45+02:00");

}
