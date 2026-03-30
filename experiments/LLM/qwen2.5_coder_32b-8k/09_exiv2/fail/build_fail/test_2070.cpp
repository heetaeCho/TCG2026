#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming UTF8Unit and UTF16Unit are defined types

using UTF8Unit = unsigned char;

using UTF16Unit = uint16_t;



extern "C" {

    void UTF8_to_UTF16Nat(const UTF8Unit* utf8In, const size_t utf8Len, UTF16Unit* utf16Out, const size_t utf16Len, size_t* utf8Read, size_t* utf16Written);

}



class UnicodeConversionsTest : public ::testing::Test {

protected:

    static constexpr size_t kBufferSize = 256;

    UTF8Unit utf8In[kBufferSize];

    UTF16Unit utf16Out[kBufferSize];

    size_t utf8Read;

    size_t utf16Written;



    void SetUp() override {

        memset(utf8In, 0, sizeof(utf8In));

        memset(utf16Out, 0, sizeof(utf16Out));

        utf8Read = 0;

        utf16Written = 0;

    }

};



TEST_F(UnicodeConversionsTest_2070, SimpleASCIIConversion_2070) {

    // Arrange

    const char* input = "Hello";

    memcpy(utf8In, input, strlen(input));



    // Act

    UTF8_to_UTF16Nat(utf8In, strlen(input), utf16Out, kBufferSize, &utf8Read, &utf16Written);



    // Assert

    EXPECT_EQ(utf8Read, strlen(input));

    EXPECT_EQ(utf16Written, strlen(input));

    for (size_t i = 0; i < strlen(input); ++i) {

        EXPECT_EQ(utf16Out[i], static_cast<UTF16Unit>(input[i]));

    }

}



TEST_F(UnicodeConversionsTest_2070, EmptyInput_2070) {

    // Arrange

    const char* input = "";

    memcpy(utf8In, input, strlen(input));



    // Act

    UTF8_to_UTF16Nat(utf8In, strlen(input), utf16Out, kBufferSize, &utf8Read, &utf16Written);



    // Assert

    EXPECT_EQ(utf8Read, 0);

    EXPECT_EQ(utf16Written, 0);

}



TEST_F(UnicodeConversionsTest_2070, SingleByteUTF8_2070) {

    // Arrange

    const char* input = "A";

    memcpy(utf8In, input, strlen(input));



    // Act

    UTF8_to_UTF16Nat(utf8In, strlen(input), utf16Out, kBufferSize, &utf8Read, &utf16Written);



    // Assert

    EXPECT_EQ(utf8Read, 1);

    EXPECT_EQ(utf16Written, 1);

    EXPECT_EQ(utf16Out[0], static_cast<UTF16Unit>('A'));

}



TEST_F(UnicodeConversionsTest_2070, MultiByteUTF8_2070) {

    // Arrange

    const char* input = "😊"; // U+1F60A (4 bytes in UTF-8)

    memcpy(utf8In, input, strlen(input));



    // Act

    UTF8_to_UTF16Nat(utf8In, strlen(input), utf16Out, kBufferSize, &utf8Read, &utf16Written);



    // Assert

    EXPECT_EQ(utf8Read, 4);

    EXPECT_EQ(utf16Written, 2); // Surrogate pair in UTF-16

    EXPECT_EQ(utf16Out[0], 0xD83D);

    EXPECT_EQ(utf16Out[1], 0xDE0A);

}



TEST_F(UnicodeConversionsTest_2070, IncompleteUTF8Character_2070) {

    // Arrange

    const char* input = "\xF0\x9F"; // Truncated U+1F60A (4 bytes in UTF-8)

    memcpy(utf8In, input, strlen(input));



    // Act

    UTF8_to_UTF16Nat(utf8In, strlen(input), utf16Out, kBufferSize, &utf8Read, &utf16Written);



    // Assert

    EXPECT_EQ(utf8Read, 0); // Incomplete character should not be read

    EXPECT_EQ(utf16Written, 0);

}



TEST_F(UnicodeConversionsTest_2070, OutputBufferTooSmallForSurrogatePair_2070) {

    // Arrange

    const char* input = "😊"; // U+1F60A (4 bytes in UTF-8)

    memcpy(utf8In, input, strlen(input));



    // Act

    UTF8_to_UTF16Nat(utf8In, strlen(input), utf16Out, 1, &utf8Read, &utf16Written);



    // Assert

    EXPECT_EQ(utf8Read, 0); // Not enough space for surrogate pair

    EXPECT_EQ(utf16Written, 0);

}



TEST_F(UnicodeConversionsTest_2070, MixedASCIIAndUTF8_2070) {

    // Arrange

    const char* input = "A😊B"; // A (ASCII), U+1F60A (4 bytes in UTF-8), B (ASCII)

    memcpy(utf8In, input, strlen(input));



    // Act

    UTF8_to_UTF16Nat(utf8In, strlen(input), utf16Out, kBufferSize, &utf8Read, &utf16Written);



    // Assert

    EXPECT_EQ(utf8Read, strlen(input));

    EXPECT_EQ(utf16Written, 4); // A (2 bytes) + U+1F60A (4 bytes -> 2 UTF-16 units) + B (2 bytes)

    EXPECT_EQ(utf16Out[0], static_cast<UTF16Unit>('A'));

    EXPECT_EQ(utf16Out[1], 0xD83D);

    EXPECT_EQ(utf16Out[2], 0xDE0A);

    EXPECT_EQ(utf16Out[3], static_cast<UTF16Unit>('B'));

}
