#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming UTF16Unit and UTF32Unit are defined somewhere in the header files.

typedef unsigned short UTF16Unit;

typedef unsigned int UTF32Unit;



extern "C" {

    void UTF16Swp_to_UTF32Nat(const UTF16Unit * utf16In, const size_t utf16Len, UTF32Unit * utf32Out, const size_t utf32Len, size_t * utf16Read, size_t * utf32Written);

}



// Helper function to convert little-endian UTF-16 to big-endian (swapped) UTF-16

void ConvertToSwappedUTF16(const std::vector<UTF16Unit>& inputLE, std::vector<UTF16Unit>& outputBE) {

    for (UTF16Unit c : inputLE) {

        outputBE.push_back((c >> 8) | ((c & 0xFF) << 8));

    }

}



TEST(UnicodeConversionsTest_2087, NormalOperation_SimpleASCII_2087) {

    std::vector<UTF16Unit> utf16InLE = {0x48, 0x65, 0x6C, 0x6C, 0x6F}; // "Hello"

    std::vector<UTF16Unit> utf16In;

    ConvertToSwappedUTF16(utf16InLE, utf16In);



    std::vector<UTF32Unit> utf32Out(5);

    size_t utf16Read = 0;

    size_t utf32Written = 0;



    UTF16Swp_to_UTF32Nat(utf16In.data(), utf16In.size(), utf32Out.data(), utf32Out.size(), &utf16Read, &utf32Written);



    EXPECT_EQ(utf16Read, 5);

    EXPECT_EQ(utf32Written, 5);

    for (size_t i = 0; i < 5; ++i) {

        EXPECT_EQ(utf32Out[i], utf16InLE[i]);

    }

}



TEST(UnicodeConversionsTest_2087, NormalOperation_SimpleSurrogates_2087) {

    std::vector<UTF16Unit> utf16InLE = {0xD840, 0xDC00}; // U+10000

    std::vector<UTF16Unit> utf16In;

    ConvertToSwappedUTF16(utf16InLE, utf16In);



    std::vector<UTF32Unit> utf32Out(1);

    size_t utf16Read = 0;

    size_t utf32Written = 0;



    UTF16Swp_to_UTF32Nat(utf16In.data(), utf16In.size(), utf32Out.data(), utf32Out.size(), &utf16Read, &utf32Written);



    EXPECT_EQ(utf16Read, 2);

    EXPECT_EQ(utf32Written, 1);

    EXPECT_EQ(utf32Out[0], 0x10000U);

}



TEST(UnicodeConversionsTest_2087, BoundaryCondition_EmptyInput_2087) {

    std::vector<UTF16Unit> utf16In;

    std::vector<UTF32Unit> utf32Out(1);

    size_t utf16Read = 0;

    size_t utf32Written = 0;



    UTF16Swp_to_UTF32Nat(utf16In.data(), utf16In.size(), utf32Out.data(), utf32Out.size(), &utf16Read, &utf32Written);



    EXPECT_EQ(utf16Read, 0);

    EXPECT_EQ(utf32Written, 0);

}



TEST(UnicodeConversionsTest_2087, BoundaryCondition_SmallOutputBuffer_2087) {

    std::vector<UTF16Unit> utf16InLE = {0x48, 0x65, 0x6C, 0x6C, 0x6F}; // "Hello"

    std::vector<UTF16Unit> utf16In;

    ConvertToSwappedUTF16(utf16InLE, utf16In);



    std::vector<UTF32Unit> utf32Out(3);

    size_t utf16Read = 0;

    size_t utf32Written = 0;



    UTF16Swp_to_UTF32Nat(utf16In.data(), utf16In.size(), utf32Out.data(), utf32Out.size(), &utf16Read, &utf32Written);



    EXPECT_EQ(utf16Read, 3);

    EXPECT_EQ(utf32Written, 3);

    for (size_t i = 0; i < 3; ++i) {

        EXPECT_EQ(utf32Out[i], utf16InLE[i]);

    }

}



TEST(UnicodeConversionsTest_2087, BoundaryCondition_SurrogatePairAtEndOfInput_2087) {

    std::vector<UTF16Unit> utf16InLE = {0x48, 0x65, 0xD840}; // "He" + high surrogate

    std::vector<UTF16Unit> utf16In;

    ConvertToSwappedUTF16(utf16InLE, utf16In);



    std::vector<UTF32Unit> utf32Out(2);

    size_t utf16Read = 0;

    size_t utf32Written = 0;



    UTF16Swp_to_UTF32Nat(utf16In.data(), utf16In.size(), utf32Out.data(), utf32Out.size(), &utf16Read, &utf32Written);



    EXPECT_EQ(utf16Read, 2);

    EXPECT_EQ(utf32Written, 2);

    EXPECT_EQ(utf32Out[0], utf16InLE[0]);

    EXPECT_EQ(utf32Out[1], utf16InLE[1]);

}



TEST(UnicodeConversionsTest_2087, ErrorCondition_MalformedSurrogatePair_2087) {

    std::vector<UTF16Unit> utf16InLE = {0xD840}; // High surrogate without low surrogate

    std::vector<UTF16Unit> utf16In;

    ConvertToSwappedUTF16(utf16InLE, utf16In);



    std::vector<UTF32Unit> utf32Out(1);

    size_t utf16Read = 0;

    size_t utf32Written = 0;



    UTF16Swp_to_UTF32Nat(utf16In.data(), utf16In.size(), utf32Out.data(), utf32Out.size(), &utf16Read, &utf32Written);



    EXPECT_EQ(utf16Read, 0);

    EXPECT_EQ(utf32Written, 0);

}



TEST(UnicodeConversionsTest_2087, ErrorCondition_SurrogatePairWithoutHighSurrogate_2087) {

    std::vector<UTF16Unit> utf16InLE = {0xDC00}; // Low surrogate without high surrogate

    std::vector<UTF16Unit> utf16In;

    ConvertToSwappedUTF16(utf16InLE, utf16In);



    std::vector<UTF32Unit> utf32Out(1);

    size_t utf16Read = 0;

    size_t utf32Written = 0;



    UTF16Swp_to_UTF32Nat(utf16In.data(), utf16In.size(), utf32Out.data(), utf32Out.size(), &utf16Read, &utf32Written);



    EXPECT_EQ(utf16Read, 0);

    EXPECT_EQ(utf32Written, 0);

}
