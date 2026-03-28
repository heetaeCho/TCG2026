#include <gtest/gtest.h>

#include "UnicodeConversions.cpp"



class UnicodeConversionsTest_2083 : public ::testing::Test {

protected:

    const size_t inputSize = 16;

    const size_t outputSize = 48; // UTF-8 can take up to 4 bytes per character

    UTF32Unit utf32In[16];

    UTF8Unit utf8Out[48];

    size_t utf32Read, utf8Written;



    void SetUp() override {

        memset(utf32In, 0, sizeof(utf32In));

        memset(utf8Out, 0, sizeof(utf8Out));

        utf32Read = 0;

        utf8Written = 0;

    }

};



TEST_F(UnicodeConversionsTest_2083, ConvertASCII_2083) {

    // Simple ASCII characters

    for (size_t i = 0; i < inputSize; ++i) {

        utf32In[i] = static_cast<UTF32Unit>('A' + i);

    }

    UTF32Swp_to_UTF8(utf32In, inputSize, utf8Out, outputSize, &utf32Read, &utf8Written);



    for (size_t i = 0; i < inputSize; ++i) {

        EXPECT_EQ(utf8Out[i], 'A' + i);

    }

    EXPECT_EQ(utf32Read, inputSize);

    EXPECT_EQ(utf8Written, inputSize);

}



TEST_F(UnicodeConversionsTest_2083, ConvertBasicMultilingualPlane_2083) {

    // Basic Multilingual Plane (BMP) characters

    UTF32Unit testChars[] = { 0x041F, 0x65E5, 0x0930 };

    size_t expectedUtf8Lengths[] = { 2, 3, 3 };



    for (size_t i = 0; i < 3; ++i) {

        utf32In[i] = testChars[i];

    }

    UTF32Swp_to_UTF8(utf32In, 3, utf8Out, outputSize, &utf32Read, &utf8Written);



    size_t pos = 0;

    for (size_t i = 0; i < 3; ++i) {

        EXPECT_EQ(utf8Out[pos], static_cast<UTF8Unit>(testChars[i] >> 6 | 0xC0));

        EXPECT_EQ(utf8Out[pos + 1], static_cast<UTF8Unit>(testChars[i] & 0x3F | 0x80));

        pos += expectedUtf8Lengths[i];

    }

    EXPECT_EQ(utf32Read, 3);

    EXPECT_EQ(utf8Written, pos);

}



TEST_F(UnicodeConversionsTest_2083, ConvertSupplementaryPlanes_2083) {

    // Supplementary Plane characters

    UTF32Unit testChars[] = { 0x1F600, 0x10400 };

    size_t expectedUtf8Lengths[] = { 4, 4 };



    for (size_t i = 0; i < 2; ++i) {

        utf32In[i] = testChars[i];

    }

    UTF32Swp_to_UTF8(utf32In, 2, utf8Out, outputSize, &utf32Read, &utf8Written);



    size_t pos = 0;

    for (size_t i = 0; i < 2; ++i) {

        EXPECT_EQ(utf8Out[pos], static_cast<UTF8Unit>(testChars[i] >> 18 | 0xF0));

        EXPECT_EQ(utf8Out[pos + 1], static_cast<UTF8Unit>((testChars[i] >> 12) & 0x3F | 0x80));

        EXPECT_EQ(utf8Out[pos + 2], static_cast<UTF8Unit>((testChars[i] >> 6) & 0x3F | 0x80));

        EXPECT_EQ(utf8Out[pos + 3], static_cast<UTF8Unit>(testChars[i] & 0x3F | 0x80));

        pos += expectedUtf8Lengths[i];

    }

    EXPECT_EQ(utf32Read, 2);

    EXPECT_EQ(utf8Written, pos);

}



TEST_F(UnicodeConversionsTest_2083, InputBufferTooSmall_2083) {

    // Not enough input buffer

    utf32In[0] = 'A';

    UTF32Swp_to_UTF8(utf32In, 0, utf8Out, outputSize, &utf32Read, &utf8Written);



    EXPECT_EQ(utf32Read, 0);

    EXPECT_EQ(utf8Written, 0);

}



TEST_F(UnicodeConversionsTest_2083, OutputBufferTooSmall_2083) {

    // Not enough output buffer

    utf32In[0] = 0x1F600; // This character requires 4 bytes in UTF-8

    UTF32Swp_to_UTF8(utf32In, 1, utf8Out, 3, &utf32Read, &utf8Written);



    EXPECT_EQ(utf32Read, 0);

    EXPECT_EQ(utf8Written, 0);

}



TEST_F(UnicodeConversionsTest_2083, MixedCharacters_2083) {

    // Mixed ASCII, BMP, and supplementary plane characters

    UTF32Unit testChars[] = {'A', 0x65E5, 'B', 0x1F600};

    size_t expectedUtf8Lengths[] = { 1, 3, 1, 4 };



    for (size_t i = 0; i < 4; ++i) {

        utf32In[i] = testChars[i];

    }

    UTF32Swp_to_UTF8(utf32In, 4, utf8Out, outputSize, &utf32Read, &utf8Written);



    size_t pos = 0;

    for (size_t i = 0; i < 4; ++i) {

        if (testChars[i] <= 0x7F) { // ASCII

            EXPECT_EQ(utf8Out[pos], testChars[i]);

            pos += expectedUtf8Lengths[i];

        } else if (testChars[i] <= 0xFFFF) { // BMP

            EXPECT_EQ(utf8Out[pos], static_cast<UTF8Unit>(testChars[i] >> 6 | 0xC0));

            EXPECT_EQ(utf8Out[pos + 1], static_cast<UTF8Unit>(testChars[i] & 0x3F | 0x80));

            pos += expectedUtf8Lengths[i];

        } else { // Supplementary Plane

            EXPECT_EQ(utf8Out[pos], static_cast<UTF8Unit>(testChars[i] >> 18 | 0xF0));

            EXPECT_EQ(utf8Out[pos + 1], static_cast<UTF8Unit>((testChars[i] >> 12) & 0x3F | 0x80));

            EXPECT_EQ(utf8Out[pos + 2], static_cast<UTF8Unit>((testChars[i] >> 6) & 0x3F | 0x80));

            EXPECT_EQ(utf8Out[pos + 3], static_cast<UTF8Unit>(testChars[i] & 0x3F | 0x80));

            pos += expectedUtf8Lengths[i];

        }

    }

    EXPECT_EQ(utf32Read, 4);

    EXPECT_EQ(utf8Written, pos);

}
