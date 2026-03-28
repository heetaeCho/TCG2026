#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming UTF32Unit and UTF8Unit are defined somewhere in the codebase.

using UTF32Unit = uint32_t;

using UTF8Unit = uint8_t;



extern "C" {

    void UTF32Nat_to_UTF8(const UTF32Unit* utf32In, const size_t utf32Len, UTF8Unit* utf8Out, const size_t utf8Len, size_t* utf32Read, size_t* utf8Written);

}



class UnicodeConversionsTest_2073 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any common state before each test.

    }



    void TearDown() override {

        // Cleanup any common state after each test.

    }

};



TEST_F(UnicodeConversionsTest_2073, SimpleASCIIConversion_2073) {

    UTF32Unit utf32In[] = { 'H', 'e', 'l', 'l', 'o' };

    size_t utf32Len = sizeof(utf32In) / sizeof(utf32In[0]);

    UTF8Unit utf8Out[16];

    size_t utf8Len = sizeof(utf8Out);

    size_t utf32Read, utf8Written;



    UTF32Nat_to_UTF8(utf32In, utf32Len, utf8Out, utf8Len, &utf32Read, &utf8Written);



    EXPECT_EQ(utf32Read, utf32Len);

    EXPECT_EQ(utf8Written, utf32Len); // 1:1 mapping for ASCII

    EXPECT_EQ(memcmp(utf32In, utf8Out, utf8Written), 0);

}



TEST_F(UnicodeConversionsTest_2073, EmptyInput_2073) {

    UTF32Unit utf32In[] = {};

    size_t utf32Len = sizeof(utf32In) / sizeof(utf32In[0]);

    UTF8Unit utf8Out[16];

    size_t utf8Len = sizeof(utf8Out);

    size_t utf32Read, utf8Written;



    UTF32Nat_to_UTF8(utf32In, utf32Len, utf8Out, utf8Len, &utf32Read, &utf8Written);



    EXPECT_EQ(utf32Read, 0);

    EXPECT_EQ(utf8Written, 0);

}



TEST_F(UnicodeConversionsTest_2073, FullBufferBoundaryASCII_2073) {

    UTF32Unit utf32In[] = { 'H', 'e', 'l', 'l', 'o' };

    size_t utf32Len = sizeof(utf32In) / sizeof(utf32In[0]);

    UTF8Unit utf8Out[5];

    size_t utf8Len = sizeof(utf8Out);

    size_t utf32Read, utf8Written;



    UTF32Nat_to_UTF8(utf32In, utf32Len, utf8Out, utf8Len, &utf32Read, &utf8Written);



    EXPECT_EQ(utf32Read, utf32Len);

    EXPECT_EQ(utf8Written, utf32Len); // 1:1 mapping for ASCII

    EXPECT_EQ(memcmp(utf32In, utf8Out, utf8Written), 0);

}



TEST_F(UnicodeConversionsTest_2073, FullBufferBoundaryNonASCII_2073) {

    UTF32Unit utf32In[] = { 0x1F600 }; // Grinning Face emoji

    size_t utf32Len = sizeof(utf32In) / sizeof(utf32In[0]);

    UTF8Unit utf8Out[4];

    size_t utf8Len = sizeof(utf8Out);

    size_t utf32Read, utf8Written;



    UTF32Nat_to_UTF8(utf32In, utf32Len, utf8Out, utf8Len, &utf32Read, &utf8Written);



    EXPECT_EQ(utf32Read, utf32Len);

    EXPECT_EQ(utf8Written, 4); // Emoji takes 4 bytes in UTF-8

    // Expected UTF-8 encoding for U+1F600 is 0xF0 0x9F 0x98 0x80

    UTF8Unit expected[] = { 0xF0, 0x9F, 0x98, 0x80 };

    EXPECT_EQ(memcmp(expected, utf8Out, utf8Written), 0);

}



TEST_F(UnicodeConversionsTest_2073, InsufficientOutputBuffer_2073) {

    UTF32Unit utf32In[] = { 'H', 'e', 'l', 'l', 'o' };

    size_t utf32Len = sizeof(utf32In) / sizeof(utf32In[0]);

    UTF8Unit utf8Out[4]; // Buffer too small for all characters

    size_t utf8Len = sizeof(utf8Out);

    size_t utf32Read, utf8Written;



    UTF32Nat_to_UTF8(utf32In, utf32Len, utf8Out, utf8Len, &utf32Read, &utf8Written);



    EXPECT_EQ(utf32Read, 4); // Only 4 characters can be written

    EXPECT_EQ(utf8Written, 4);

}



TEST_F(UnicodeConversionsTest_2073, NonASCIIConversion_2073) {

    UTF32Unit utf32In[] = { 'H', 'e', 'l', 'l', 'o', 0x1F600 }; // Grinning Face emoji

    size_t utf32Len = sizeof(utf32In) / sizeof(utf32In[0]);

    UTF8Unit utf8Out[16];

    size_t utf8Len = sizeof(utf8Out);

    size_t utf32Read, utf8Written;



    UTF32Nat_to_UTF8(utf32In, utf32Len, utf8Out, utf8Len, &utf32Read, &utf8Written);



    EXPECT_EQ(utf32Read, utf32Len);

    EXPECT_EQ(utf8Written, 10); // 5 ASCII characters + 4 bytes for the emoji

    UTF8Unit expected[] = { 'H', 'e', 'l', 'l', 'o', 0xF0, 0x9F, 0x98, 0x80 };

    EXPECT_EQ(memcmp(utf32In, utf8Out, 5), 0);

    EXPECT_EQ(memcmp(expected + 5, utf8Out + 5, 4), 0);

}
