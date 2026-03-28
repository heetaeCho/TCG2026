#include <gtest/gtest.h>

#include <cstddef>

#include <cstdint>



using UTF16Unit = uint16_t;

using UTF32Unit = uint32_t;



extern "C" {

    void UTF16Nat_to_UTF32Swp(const UTF16Unit* utf16In, const size_t utf16Len, 

                             UTF32Unit* utf32Out, const size_t utf32Len, 

                             size_t* utf16Read, size_t* utf32Written);

}



TEST(UnicodeConversionsTest_2086, BasicConversion_2086) {

    const UTF16Unit utf16In[] = {0x41, 0x42, 0x43};

    const size_t utf16Len = sizeof(utf16In) / sizeof(UTF16Unit);

    UTF32Unit utf32Out[utf16Len];

    size_t utf16Read, utf32Written;



    UTF16Nat_to_UTF32Swp(utf16In, utf16Len, utf32Out, utf16Len, &utf16Read, &utf32Written);



    EXPECT_EQ(utf16Read, utf16Len);

    EXPECT_EQ(utf32Written, utf16Len);

    for (size_t i = 0; i < utf32Written; ++i) {

        EXPECT_EQ(utf32Out[i], static_cast<UTF32Unit>(utf16In[i]));

    }

}



TEST(UnicodeConversionsTest_2086, SurrogatePairConversion_2086) {

    const UTF16Unit utf16In[] = {0xD840, 0xDC00}; // U+10000

    const size_t utf16Len = sizeof(utf16In) / sizeof(UTF16Unit);

    UTF32Unit utf32Out[1];

    size_t utf16Read, utf32Written;



    UTF16Nat_to_UTF32Swp(utf16In, utf16Len, utf32Out, 1, &utf16Read, &utf32Written);



    EXPECT_EQ(utf16Read, utf16Len);

    EXPECT_EQ(utf32Written, 1);

    EXPECT_EQ(utf32Out[0], 0x10000U);

}



TEST(UnicodeConversionsTest_2086, IncompleteSurrogatePair_2086) {

    const UTF16Unit utf16In[] = {0xD840}; // Incomplete surrogate pair

    const size_t utf16Len = sizeof(utf16In) / sizeof(UTF16Unit);

    UTF32Unit utf32Out[1];

    size_t utf16Read, utf32Written;



    UTF16Nat_to_UTF32Swp(utf16In, utf16Len, utf32Out, 1, &utf16Read, &utf32Written);



    EXPECT_EQ(utf16Read, 0);

    EXPECT_EQ(utf32Written, 0);

}



TEST(UnicodeConversionsTest_2086, MixedInput_2086) {

    const UTF16Unit utf16In[] = {0x41, 0xD840, 0xDC00, 0x42};

    const size_t utf16Len = sizeof(utf16In) / sizeof(UTF16Unit);

    UTF32Unit utf32Out[utf16Len];

    size_t utf16Read, utf32Written;



    UTF16Nat_to_UTF32Swp(utf16In, utf16Len, utf32Out, utf16Len, &utf16Read, &utf32Written);



    EXPECT_EQ(utf16Read, utf16Len);

    EXPECT_EQ(utf32Written, 4);

    EXPECT_EQ(utf32Out[0], 0x41U);

    EXPECT_EQ(utf32Out[1], 0x10000U);

    EXPECT_EQ(utf32Out[2], 0x42U);

}



TEST(UnicodeConversionsTest_2086, OutputBufferTooSmall_2086) {

    const UTF16Unit utf16In[] = {0x41, 0xD840, 0xDC00};

    const size_t utf16Len = sizeof(utf16In) / sizeof(UTF16Unit);

    UTF32Unit utf32Out[2];

    size_t utf16Read, utf32Written;



    UTF16Nat_to_UTF32Swp(utf16In, utf16Len, utf32Out, 2, &utf16Read, &utf32Written);



    EXPECT_EQ(utf16Read, 1);

    EXPECT_EQ(utf32Written, 1);

    EXPECT_EQ(utf32Out[0], 0x41U);

}



TEST(UnicodeConversionsTest_2086, InputBufferTooSmallForSurrogatePair_2086) {

    const UTF16Unit utf16In[] = {0xD840}; // Incomplete surrogate pair

    const size_t utf16Len = sizeof(utf16In) / sizeof(UTF16Unit);

    UTF32Unit utf32Out[1];

    size_t utf16Read, utf32Written;



    UTF16Nat_to_UTF32Swp(utf16In, utf16Len, utf32Out, 1, &utf16Read, &utf32Written);



    EXPECT_EQ(utf16Read, 0);

    EXPECT_EQ(utf32Written, 0);

}



TEST(UnicodeConversionsTest_2086, EmptyInput_2086) {

    const UTF16Unit utf16In[] = {};

    const size_t utf16Len = sizeof(utf16In) / sizeof(UTF16Unit);

    UTF32Unit utf32Out[1];

    size_t utf16Read, utf32Written;



    UTF16Nat_to_UTF32Swp(utf16In, utf16Len, utf32Out, 1, &utf16Read, &utf32Written);



    EXPECT_EQ(utf16Read, 0);

    EXPECT_EQ(utf32Written, 0);

}
