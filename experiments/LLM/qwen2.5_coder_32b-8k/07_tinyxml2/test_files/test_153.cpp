#include <gtest/gtest.h>

#include <cstdarg>

#include <cstdio>



// Mocking the TIXML_VSCPRINTF function for testing purposes.

extern "C" {

    int TIXML_VSCPRINTF(const char* format, va_list va) { 

        return vsnprintf(0, 0, format, va); 

    }

}



// Test fixture class

class TIXML_VSCPRINTFTest_153 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



// Normal operation test case

TEST_F(TIXML_VSCPRINTFTest_153, ReturnsCorrectLengthForSimpleString_153) {

    const char* format = "Hello, world!";

    va_list args;

    va_start(args, format);

    int result = TIXML_VSCPRINTF(format, args);

    va_end(args);



    EXPECT_EQ(result, 12); // Length of "Hello, world!"

}



// Boundary condition test case

TEST_F(TIXML_VSCPRINTFTest_153, ReturnsZeroForEmptyString_153) {

    const char* format = "";

    va_list args;

    va_start(args, format);

    int result = TIXML_VSCPRINTF(format, args);

    va_end(args);



    EXPECT_EQ(result, 0); // Length of ""

}



// Test case with format specifiers

TEST_F(TIXML_VSCPRINTFTest_153, ReturnsCorrectLengthWithFormatSpecifiers_153) {

    const char* format = "Value: %d, String: %s";

    int value = 42;

    const char* str = "forty-two";



    va_list args;

    va_start(args, format);

    va_arg(args, int); // Skip the first argument

    va_arg(args, const char*); // Skip the second argument

    int result = TIXML_VSCPRINTF(format, args);

    va_end(args);



    EXPECT_EQ(result, 26); // Length of "Value: 42, String: forty-two"

}



// Test case with very large string (boundary condition)

TEST_F(TIXML_VSCPRINTFTest_153, ReturnsCorrectLengthForLargeString_153) {

    const char* format = "%s";

    std::string long_string(1000, 'a'); // Create a string of 1000 'a's



    va_list args;

    va_start(args, format);

    va_arg(args, const char*); // Skip the argument

    int result = TIXML_VSCPRINTF(format, args);

    va_end(args);



    EXPECT_EQ(result, 1000); // Length of the long string

}



// Exceptional case (not directly applicable here as vsnprintf does not throw exceptions)

// However, we can test for invalid format strings

TEST_F(TIXML_VSCPRINTFTest_153, HandlesInvalidFormatStringGracefully_153) {

    const char* format = "%"; // Invalid format string



    va_list args;

    va_start(args, format);

    int result = TIXML_VSCPRINTF(format, args);

    va_end(args);



    EXPECT_EQ(result, -1); // vsnprintf should return -1 for invalid format

}
