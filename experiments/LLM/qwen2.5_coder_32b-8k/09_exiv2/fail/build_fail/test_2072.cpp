#include <gtest/gtest.h>

#include <cstring>



extern "C" {

    void UTF16Nat_to_UTF8(const unsigned short* utf16In, const size_t utf16Len, unsigned char* utf8Out, const size_t utf8Len, size_t *utf16Read, size_t *utf8Written);

}



class UnicodeConversionsTest_2072 : public ::testing::Test {

protected:

    static constexpr size_t kMaxUtf16 = 100;

    static constexpr size_t kMaxUtf8 = 300;



    unsigned short utf16Input[kMaxUtf16];

    unsigned char utf8Output[kMaxUtf8];

    size_t utf16Read, utf8Written;



    void setUp() {

        memset(utf16Input, 0, sizeof(utf16Input));

        memset(utf8Output, 0, sizeof(utf8Output));

        utf16Read = 0;

        utf8Written = 0;

    }



    void TearDown() override {

        memset(utf16Input, 0, sizeof(utf16Input));

        memset(utf8Output, 0, sizeof(utf8Output));

        utf16Read = 0;

        utf8Written = 0;

    }

};



TEST_F(UnicodeConversionsTest_2072, SimpleASCIIConversion_2072) {

    const unsigned short input[] = { 'H', 'e', 'l', 'l', 'o', 0 };

    memcpy(utf16Input, input, sizeof(input));



    UTF16Nat_to_UTF8(utf16Input, 5, utf8Output, kMaxUtf8, &utf16Read, &utf8Written);



    EXPECT_EQ(utf16Read, 5);

    EXPECT_EQ(utf8Written, 5);

    EXPECT_STREQ(reinterpret_cast<const char*>(utf8Output), "Hello");

}



TEST_F(UnicodeConversionsTest_2072, SingleByteUTF8Conversion_2072) {

    const unsigned short input[] = { 'A', '\u00E9', '\u20AC', 0 }; // A, é, €

    memcpy(utf16Input, input, sizeof(input));



    UTF16Nat_to_UTF8(utf16Input, 3, utf8Output, kMaxUtf8, &utf16Read, &utf8Written);



    EXPECT_EQ(utf16Read, 3);

    EXPECT_EQ(utf8Written, 6);

    std::string expected = "A\xC3\xA9\xE2\x82\xAC";

    EXPECT_EQ(memcmp(utf8Output, expected.data(), utf8Written), 0);

}



TEST_F(UnicodeConversionsTest_2072, SurrogatePairConversion_2072) {

    const unsigned short input[] = { 0xD834, 0xDD1E, '!', 0 }; // Musical symbol G clef followed by exclamation mark

    memcpy(utf16Input, input, sizeof(input));



    UTF16Nat_to_UTF8(utf16Input, 3, utf8Output, kMaxUtf8, &utf16Read, &utf8Written);



    EXPECT_EQ(utf16Read, 3);

    EXPECT_EQ(utf8Written, 4);

    std::string expected = "\xF0\x9D\x84\x9E!";

    EXPECT_EQ(memcmp(utf8Output, expected.data(), utf8Written), 0);

}



TEST_F(UnicodeConversionsTest_2072, InsufficientOutputBuffer_2072) {

    const unsigned short input[] = { 'A', '\u00E9', '\u20AC', 0 }; // A, é, €

    memcpy(utf16Input, input, sizeof(input));



    UTF16Nat_to_UTF8(utf16Input, 3, utf8Output, 4, &utf16Read, &utf8Written); // Output buffer size of 4



    EXPECT_EQ(utf16Read, 2);

    EXPECT_EQ(utf8Written, 3);

    std::string expected = "A\xC3";

    EXPECT_EQ(memcmp(utf8Output, expected.data(), utf8Written), 0);

}



TEST_F(UnicodeConversionsTest_2072, EmptyInputBuffer_2072) {

    UTF16Nat_to_UTF8(utf16Input, 0, utf8Output, kMaxUtf8, &utf16Read, &utf8Written);



    EXPECT_EQ(utf16Read, 0);

    EXPECT_EQ(utf8Written, 0);

}



TEST_F(UnicodeConversionsTest_2072, EmptyOutputBuffer_2072) {

    const unsigned short input[] = { 'A', 0 };

    memcpy(utf16Input, input, sizeof(input));



    UTF16Nat_to_UTF8(utf16Input, 1, utf8Output, 0, &utf16Read, &utf8Written);



    EXPECT_EQ(utf16Read, 0);

    EXPECT_EQ(utf8Written, 0);

}



TEST_F(UnicodeConversionsTest_2072, MixedSurrogatesAndASCII_2072) {

    const unsigned short input[] = { 'H', '\u00E9', 0xD834, 0xDD1E, '!', 0 }; // H, é, Musical symbol G clef followed by exclamation mark

    memcpy(utf16Input, input, sizeof(input));



    UTF16Nat_to_UTF8(utf16Input, 5, utf8Output, kMaxUtf8, &utf16Read, &utf8Written);



    EXPECT_EQ(utf16Read, 5);

    EXPECT_EQ(utf8Written, 9);

    std::string expected = "H\xC3\xA9\xF0\x9D\x84\x9E!";

    EXPECT_EQ(memcmp(utf8Output, expected.data(), utf8Written), 0);

}
