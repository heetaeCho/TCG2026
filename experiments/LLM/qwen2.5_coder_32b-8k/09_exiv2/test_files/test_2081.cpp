#include <gtest/gtest.h>

#include "UnicodeConversions.cpp" // Assuming the function is in this file



// Test fixture for UTF8_to_UTF32Swp tests

class UTF8ToUTF32SwpTest_2081 : public ::testing::Test {

protected:

    static constexpr size_t kMaxUtf8Len = 100;

    static constexpr size_t kMaxUtf32Len = 50;



    UTF8Unit utf8In[kMaxUtf8Len] = {0};

    UTF32Unit utf32Out[kMaxUtf32Len] = {0};

    size_t utf8Read = 0;

    size_t utf32Written = 0;



    void ResetBuffers() {

        std::fill(utf8In, utf8In + kMaxUtf8Len, 0);

        std::fill(utf32Out, utf32Out + kMaxUtf32Len, 0);

        utf8Read = 0;

        utf32Written = 0;

    }

};



// Test normal operation with ASCII characters

TEST_F(UTF8ToUTF32SwpTest_2081, AsciiConversion_2081) {

    ResetBuffers();

    const char* input = "Hello";

    size_t len = strlen(input);

    memcpy(utf8In, input, len);



    UTF8_to_UTF32Swp(utf8In, len, utf32Out, kMaxUtf32Len, &utf8Read, &utf32Written);



    EXPECT_EQ(utf8Read, len);

    EXPECT_EQ(utf32Written, len);

    for (size_t i = 0; i < len; ++i) {

        EXPECT_EQ(utf32Out[i], static_cast<UTF32Unit>(input[i]) << 24);

    }

}



// Test normal operation with UTF-8 multi-byte characters

TEST_F(UTF8ToUTF32SwpTest_2081, MultiByteConversion_2081) {

    ResetBuffers();

    const char* input = "\xC3\xA9llo"; // éllo in UTF-8

    size_t len = strlen(input);

    memcpy(utf8In, input, len);



    UTF8_to_UTF32Swp(utf8In, len, utf32Out, kMaxUtf32Len, &utf8Read, &utf32Written);



    EXPECT_EQ(utf8Read, len);

    EXPECT_EQ(utf32Written, 4); // "éllo" -> 4 UTF-32 code points

    EXPECT_EQ(utf32Out[0], 0x00E90000); // 'é'

    for (size_t i = 1; i < 4; ++i) {

        EXPECT_EQ(utf32Out[i], static_cast<UTF32Unit>(input[i + 1]) << 24);

    }

}



// Test boundary condition with zero-length input

TEST_F(UTF8ToUTF32SwpTest_2081, ZeroLengthInput_2081) {

    ResetBuffers();



    UTF8_to_UTF32Swp(utf8In, 0, utf32Out, kMaxUtf32Len, &utf8Read, &utf32Written);



    EXPECT_EQ(utf8Read, 0);

    EXPECT_EQ(utf32Written, 0);

}



// Test boundary condition with zero-length output buffer

TEST_F(UTF8ToUTF32SwpTest_2081, ZeroLengthOutputBuffer_2081) {

    ResetBuffers();

    const char* input = "Hello";

    size_t len = strlen(input);

    memcpy(utf8In, input, len);



    UTF8_to_UTF32Swp(utf8In, len, utf32Out, 0, &utf8Read, &utf32Written);



    EXPECT_EQ(utf8Read, 0);

    EXPECT_EQ(utf32Written, 0);

}



// Test exceptional case where input ends in the middle of a multi-byte character

TEST_F(UTF8ToUTF32SwpTest_2081, IncompleteMultiByteCharacter_2081) {

    ResetBuffers();

    const char* input = "\xC3"; // Incomplete 'é' in UTF-8

    size_t len = strlen(input);

    memcpy(utf8In, input, len);



    UTF8_to_UTF32Swp(utf8In, len, utf32Out, kMaxUtf32Len, &utf8Read, &utf32Written);



    EXPECT_EQ(utf8Read, 0); // No complete character read

    EXPECT_EQ(utf32Written, 0);

}



// Test boundary condition where input and output buffer sizes are equal

TEST_F(UTF8ToUTF32SwpTest_2081, EqualBufferSizes_2081) {

    ResetBuffers();

    const char* input = "Hello";

    size_t len = strlen(input);

    memcpy(utf8In, input, len);



    UTF8_to_UTF32Swp(utf8In, len, utf32Out, len, &utf8Read, &utf32Written);



    EXPECT_EQ(utf8Read, len);

    EXPECT_EQ(utf32Written, len);

    for (size_t i = 0; i < len; ++i) {

        EXPECT_EQ(utf32Out[i], static_cast<UTF32Unit>(input[i]) << 24);

    }

}
