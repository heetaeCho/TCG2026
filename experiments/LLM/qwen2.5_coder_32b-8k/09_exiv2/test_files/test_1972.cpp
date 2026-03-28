#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    #include "./TestProjects/exiv2/xmpsdk/src/XMPMeta-Parse.cpp"

}



using namespace testing;



// Test fixture for CountControlEscape function

class CountControlEscapeTest_1972 : public ::testing::Test {

protected:

    XMP_Uns8 buffer[20];

};



TEST_F(CountControlEscapeTest_1972, ValidProhibitedNumericEscape_1972) {

    const char* input = "&#x41;";

    memcpy(buffer, input, sizeof(input));

    EXPECT_EQ(CountControlEscape(&buffer[0], &buffer[sizeof(input)-1]), 6);

}



TEST_F(CountControlEscapeTest_1972, InvalidShortEscape_1972) {

    const char* input = "&#x4";

    memcpy(buffer, input, sizeof(input));

    EXPECT_EQ(CountControlEscape(&buffer[0], &buffer[sizeof(input)-1]), -1);

}



TEST_F(CountControlEscapeTest_1972, ValidAllowedEscape_1972) {

    const char* input = "&#x9;";

    memcpy(buffer, input, sizeof(input));

    EXPECT_EQ(CountControlEscape(&buffer[0], &buffer[sizeof(input)-1]), 0);

}



TEST_F(CountControlEscapeTest_1972, InvalidNonHexEscape_1972) {

    const char* input = "&#xG;";

    memcpy(buffer, input, sizeof(input));

    EXPECT_EQ(CountControlEscape(&buffer[0], &buffer[sizeof(input)-1]), 0);

}



TEST_F(CountControlEscapeTest_1972, InvalidMissingSemicolon_1972) {

    const char* input = "&#x41";

    memcpy(buffer, input, sizeof(input));

    EXPECT_EQ(CountControlEscape(&buffer[0], &buffer[sizeof(input)-1]), 0);

}



TEST_F(CountControlEscapeTest_1972, BoundaryConditionMinimumLength_1972) {

    const char* input = "&#x;";

    memcpy(buffer, input, sizeof(input));

    EXPECT_EQ(CountControlEscape(&buffer[0], &buffer[sizeof(input)-1]), 0);

}



TEST_F(CountControlEscapeTest_1972, BoundaryConditionExactLength_1972) {

    const char* input = "&#x0;";

    memcpy(buffer, input, sizeof(input));

    EXPECT_EQ(CountControlEscape(&buffer[0], &buffer[sizeof(input)-1]), 0);

}



TEST_F(CountControlEscapeTest_1972, BoundaryConditionMaxAllowedLength_1972) {

    const char* input = "&#xF4;";

    memcpy(buffer, input, sizeof(input));

    EXPECT_EQ(CountControlEscape(&buffer[0], &buffer[sizeof(input)-1]), 6);

}



TEST_F(CountControlEscapeTest_1972, InvalidPartialEscape_1972) {

    const char* input = "&#x41";

    memcpy(buffer, input, sizeof(input));

    EXPECT_EQ(CountControlEscape(&buffer[0], &buffer[sizeof(input)-2]), -1);

}



TEST_F(CountControlEscapeTest_1972, InvalidNonNumericEscape_1972) {

    const char* input = "&amp;";

    memcpy(buffer, input, sizeof(input));

    EXPECT_EQ(CountControlEscape(&buffer[0], &buffer[sizeof(input)-1]), 0);

}
