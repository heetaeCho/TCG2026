#include <gtest/gtest.h>

#include "UnicodeConversions.cpp"  // Assuming the function is in this file for testing purposes



// Test fixture for UTF8_to_UTF16Swp tests

class UTF8ToUTF16SwpTest : public ::testing::Test {

protected:

    const size_t kMaxUtf8Len = 256;

    const size_t kMaxUtf16Len = 256;

    UTF8Unit utf8Input[kMaxUtf8Len];

    UTF16Unit utf16Output[kMaxUtf16Len];

    size_t utf8Read, utf16Written;



    void SetUp() override {

        memset(utf8Input, 0, sizeof(utf8Input));

        memset(utf16Output, 0, sizeof(utf16Output));

        utf8Read = 0;

        utf16Written = 0;

    }

};



// Test for normal operation with ASCII characters

TEST_F(UTF8ToUTF16SwpTest, NormalOperationASCII_2080) {

    const char* testString = "Hello";

    memcpy(utf8Input, testString, strlen(testString));

    UTF8_to_UTF16Swp(utf8Input, strlen(testString), utf16Output, kMaxUtf16Len, &utf8Read, &utf16Written);

    EXPECT_EQ(utf8Read, strlen(testString));

    for (size_t i = 0; i < utf16Written; ++i) {

        EXPECT_EQ(utf16Output[i], static_cast<UTF16Unit>(testString[i]) << 8);

    }

}



// Test for normal operation with UTF-8 multibyte characters

TEST_F(UTF8ToUTF16SwpTest, NormalOperationMultibyte_2080) {

    const char* testString = "😊"; // U+1F60A GRINNING FACE WITH SMILING EYES

    memcpy(utf8Input, testString, strlen(testString));

    UTF8_to_UTF16Swp(utf8Input, strlen(testString), utf16Output, kMaxUtf16Len, &utf8Read, &utf16Written);

    EXPECT_EQ(utf8Read, strlen(testString));

    EXPECT_EQ(utf16Written, 2); // surrogate pair

}



// Test for boundary condition with empty input

TEST_F(UTF8ToUTF16SwpTest, BoundaryEmptyInput_2080) {

    UTF8_to_UTF16Swp(utf8Input, 0, utf16Output, kMaxUtf16Len, &utf8Read, &utf16Written);

    EXPECT_EQ(utf8Read, 0);

    EXPECT_EQ(utf16Written, 0);

}



// Test for boundary condition with empty output buffer

TEST_F(UTF8ToUTF16SwpTest, BoundaryEmptyOutput_2080) {

    const char* testString = "A";

    memcpy(utf8Input, testString, strlen(testString));

    UTF8_to_UTF16Swp(utf8Input, strlen(testString), utf16Output, 0, &utf8Read, &utf16Written);

    EXPECT_EQ(utf8Read, 0);

    EXPECT_EQ(utf16Written, 0);

}



// Test for error case with incomplete UTF-8 sequence at the end of input

TEST_F(UTF8ToUTF16SwpTest, ErrorIncompleteSequence_2080) {

    const char* testString = "\xC3"; // Incomplete UTF-8 sequence for 'Ã'

    memcpy(utf8Input, testString, strlen(testString));

    UTF8_to_UTF16Swp(utf8Input, strlen(testString), utf16Output, kMaxUtf16Len, &utf8Read, &utf16Written);

    EXPECT_EQ(utf8Read, 0); // No valid characters read

    EXPECT_EQ(utf16Written, 0);

}



// Test for error case with not enough room in output buffer for surrogate pair

TEST_F(UTF8ToUTF16SwpTest, ErrorNotEnoughRoomForSurrogate_2080) {

    const char* testString = "😊"; // U+1F60A GRINNING FACE WITH SMILING EYES

    memcpy(utf8Input, testString, strlen(testString));

    UTF8_to_UTF16Swp(utf8Input, strlen(testString), utf16Output, 1, &utf8Read, &utf16Written);

    EXPECT_EQ(utf8Read, 0); // No valid characters read due to insufficient space

    EXPECT_EQ(utf16Written, 0);

}
