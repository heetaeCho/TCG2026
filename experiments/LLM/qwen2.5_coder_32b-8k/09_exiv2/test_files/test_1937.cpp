#include <gtest/gtest.h>

#include "XMPUtils.hpp"



// Define a fixture for tests related to WXMPUtils_ConvertFromInt64_1

class WXMPUtilsTest_1937 : public ::testing::Test {

protected:

    XMP_StringPtr strValue = nullptr;

    XMP_StringLen strSize = 0;

    WXMP_Result wResult;



    void SetUp() override {

        strValue = nullptr;

        strSize = 0;

        memset(&wResult, 0, sizeof(WXMP_Result));

    }



    void TearDown() override {

        if (strValue) {

            delete[] strValue;

        }

    }



    // Helper function to allocate memory for string output

    void AllocateStringMemory(XMP_StringLen size) {

        strValue = new XMP_StringPtr[size];

        memset(strValue, 0, size);

    }

};



// Test normal operation with a positive integer value and default format.

TEST_F(WXMPUtilsTest_1937, PositiveInt64DefaultFormat_1937) {

    AllocateStringMemory(256); // Allocate enough memory for the string representation

    XMP_Int64 binValue = 1234567890123;

    strSize = 256;



    WXMPUtils_ConvertFromInt64_1(binValue, nullptr, &strValue, &strSize, &wResult);



    EXPECT_STREQ(strValue, "1234567890123");

}



// Test normal operation with a negative integer value and default format.

TEST_F(WXMPUtilsTest_1937, NegativeInt64DefaultFormat_1937) {

    AllocateStringMemory(256); // Allocate enough memory for the string representation

    XMP_Int64 binValue = -1234567890123;

    strSize = 256;



    WXMPUtils_ConvertFromInt64_1(binValue, nullptr, &strValue, &strSize, &wResult);



    EXPECT_STREQ(strValue, "-1234567890123");

}



// Test normal operation with a zero value and default format.

TEST_F(WXMPUtilsTest_1937, ZeroInt64DefaultFormat_1937) {

    AllocateStringMemory(256); // Allocate enough memory for the string representation

    XMP_Int64 binValue = 0;

    strSize = 256;



    WXMPUtils_ConvertFromInt64_1(binValue, nullptr, &strValue, &strSize, &wResult);



    EXPECT_STREQ(strValue, "0");

}



// Test normal operation with a large positive value and default format.

TEST_F(WXMPUtilsTest_1937, LargePositiveInt64DefaultFormat_1937) {

    AllocateStringMemory(256); // Allocate enough memory for the string representation

    XMP_Int64 binValue = 9223372036854775807; // Maximum int64 value

    strSize = 256;



    WXMPUtils_ConvertFromInt64_1(binValue, nullptr, &strValue, &strSize, &wResult);



    EXPECT_STREQ(strValue, "9223372036854775807");

}



// Test normal operation with a large negative value and default format.

TEST_F(WXMPUtilsTest_1937, LargeNegativeInt64DefaultFormat_1937) {

    AllocateStringMemory(256); // Allocate enough memory for the string representation

    XMP_Int64 binValue = -9223372036854775807; // Minimum int64 value (except signed)

    strSize = 256;



    WXMPUtils_ConvertFromInt64_1(binValue, nullptr, &strValue, &strSize, &wResult);



    EXPECT_STREQ(strValue, "-9223372036854775807");

}



// Test normal operation with a specified format.

TEST_F(WXMPUtilsTest_1937, Int64WithFormat_1937) {

    AllocateStringMemory(256); // Allocate enough memory for the string representation

    XMP_Int64 binValue = 1234;

    strSize = 256;



    WXMPUtils_ConvertFromInt64_1(binValue, "%08ld", &strValue, &strSize, &wResult);



    EXPECT_STREQ(strValue, "00001234");

}



// Test boundary condition with format string being null.

TEST_F(WXMPUtilsTest_1937, Int64WithNullFormat_1937) {

    AllocateStringMemory(256); // Allocate enough memory for the string representation

    XMP_Int64 binValue = 1234;

    strSize = 256;



    WXMPUtils_ConvertFromInt64_1(binValue, nullptr, &strValue, &strSize, &wResult);



    EXPECT_STREQ(strValue, "1234");

}



// Test boundary condition with output string pointer being null.

TEST_F(WXMPUtilsTest_1937, Int64WithNullStrValue_1937) {

    XMP_Int64 binValue = 1234;

    strSize = 0;



    WXMPUtils_ConvertFromInt64_1(binValue, nullptr, nullptr, &strSize, &wResult);



    EXPECT_EQ(strSize, 0);

}



// Test boundary condition with output string length pointer being null.

TEST_F(WXMPUtilsTest_1937, Int64WithNullStrSize_1937) {

    AllocateStringMemory(256); // Allocate enough memory for the string representation

    XMP_Int64 binValue = 1234;



    WXMPUtils_ConvertFromInt64_1(binValue, nullptr, &strValue, nullptr, &wResult);



    EXPECT_TRUE(strSize > 0);

}



// Test boundary condition with all output pointers being null.

TEST_F(WXMPUtilsTest_1937, Int64WithAllNullPointers_1937) {

    XMP_Int64 binValue = 1234;



    WXMPUtils_ConvertFromInt64_1(binValue, nullptr, nullptr, nullptr, &wResult);



    EXPECT_EQ(strSize, 0);

}
