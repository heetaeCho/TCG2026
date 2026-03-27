#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming UTF16Unit and UTF32Unit are defined somewhere in the codebase.

typedef uint16_t UTF16Unit;

typedef uint32_t UTF32Unit;



extern "C" {

    void UTF16Swp_to_UTF32Swp(const UTF16Unit* utf16In, const size_t utf16Len, UTF32Unit* utf32Out, const size_t utf32Len, size_t* utf16Read, size_t* utf32Written);

}



TEST(UTF16Swp_to_UTF32SwpTest_2084, NormalOperation_SingleCodePoint_2084) {

    UTF16Unit utf16In[] = {0x0041}; // 'A'

    size_t utf16Len = 1;

    UTF32Unit utf32Out[1];

    size_t utf32Len = 1;

    size_t utf16Read, utf32Written;



    UTF16Swp_to_UTF32Swp(utf16In, utf16Len, utf32Out, utf32Len, &utf16Read, &utf32Written);



    EXPECT_EQ(utf16Read, 1);

    EXPECT_EQ(utf32Written, 1);

    EXPECT_EQ(utf32Out[0], 0x00000041);

}



TEST(UTF16Swp_to_UTF32SwpTest_2084, NormalOperation_TwoCodePoints_2084) {

    UTF16Unit utf16In[] = {0x0041, 0x0042}; // 'A', 'B'

    size_t utf16Len = 2;

    UTF32Unit utf32Out[2];

    size_t utf32Len = 2;

    size_t utf16Read, utf32Written;



    UTF16Swp_to_UTF32Swp(utf16In, utf16Len, utf32Out, utf32Len, &utf16Read, &utf32Written);



    EXPECT_EQ(utf16Read, 2);

    EXPECT_EQ(utf32Written, 2);

    EXPECT_EQ(utf32Out[0], 0x00000041);

    EXPECT_EQ(utf32Out[1], 0x00000042);

}



TEST(UTF16Swp_to_UTF32SwpTest_2084, BoundaryCondition_EmptyInput_2084) {

    UTF16Unit utf16In[] = {};

    size_t utf16Len = 0;

    UTF32Unit utf32Out[1];

    size_t utf32Len = 1;

    size_t utf16Read, utf32Written;



    UTF16Swp_to_UTF32Swp(utf16In, utf16Len, utf32Out, utf32Len, &utf16Read, &utf32Written);



    EXPECT_EQ(utf16Read, 0);

    EXPECT_EQ(utf32Written, 0);

}



TEST(UTF16Swp_to_UTF32SwpTest_2084, BoundaryCondition_EmptyOutput_2084) {

    UTF16Unit utf16In[] = {0x0041}; // 'A'

    size_t utf16Len = 1;

    UTF32Unit utf32Out[1];

    size_t utf32Len = 0;

    size_t utf16Read, utf32Written;



    UTF16Swp_to_UTF32Swp(utf16In, utf16Len, utf32Out, utf32Len, &utf16Read, &utf32Written);



    EXPECT_EQ(utf16Read, 0);

    EXPECT_EQ(utf32Written, 0);

}



TEST(UTF16Swp_to_UTF32SwpTest_2084, BoundaryCondition_Utf16SurrogatePair_2084) {

    UTF16Unit utf16In[] = {0xD835, 0xDC00}; // Mathematical bold capital A

    size_t utf16Len = 2;

    UTF32Unit utf32Out[1];

    size_t utf32Len = 1;

    size_t utf16Read, utf32Written;



    UTF16Swp_to_UTF32Swp(utf16In, utf16Len, utf32Out, utf32Len, &utf16Read, &utf32Written);



    EXPECT_EQ(utf16Read, 2);

    EXPECT_EQ(utf32Written, 1);

    EXPECT_EQ(utf32Out[0], 0x1D400);

}



TEST(UTF16Swp_to_UTF32SwpTest_2084, ErrorCase_IncompleteSurrogatePair_2084) {

    UTF16Unit utf16In[] = {0xD835}; // Incomplete surrogate pair

    size_t utf16Len = 1;

    UTF32Unit utf32Out[1];

    size_t utf32Len = 1;

    size_t utf16Read, utf32Written;



    UTF16Swp_to_UTF32Swp(utf16In, utf16Len, utf32Out, utf32Len, &utf16Read, &utf32Written);



    EXPECT_EQ(utf16Read, 0);

    EXPECT_EQ(utf32Written, 0);

}



TEST(UTF16Swp_to_UTF32SwpTest_2084, ErrorCase_InvalidSurrogatePair_2084) {

    UTF16Unit utf16In[] = {0xD835, 0x0041}; // Invalid surrogate pair

    size_t utf16Len = 2;

    UTF32Unit utf32Out[1];

    size_t utf32Len = 1;

    size_t utf16Read, utf32Written;



    UTF16Swp_to_UTF32Swp(utf16In, utf16Len, utf32Out, utf32Len, &utf16Read, &utf32Written);



    EXPECT_EQ(utf16Read, 0);

    EXPECT_EQ(utf32Written, 0);

}
