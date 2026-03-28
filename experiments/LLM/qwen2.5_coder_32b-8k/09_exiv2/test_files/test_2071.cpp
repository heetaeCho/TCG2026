#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming UTF8Unit and UTF32Unit are defined somewhere in the codebase.

typedef unsigned char UTF8Unit;

typedef unsigned int UTF32Unit;



extern "C" {

    static void UTF8_to_UTF32Nat(const UTF8Unit * utf8In, const size_t utf8Len, UTF32Unit * utf32Out, const size_t utf32Len, size_t * utf8Read, size_t * utf32Written);

}



class UnicodeConversionsTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary variables or objects here.

    }



    void TearDown() override {

        // Clean up any resources used in the tests.

    }

};



TEST_F(UnicodeConversionsTest_2071, SimpleASCIIConversion_2071) {

    UTF8Unit utf8In[] = {'H', 'e', 'l', 'l', 'o'};

    size_t utf8Len = sizeof(utf8In);

    UTF32Unit utf32Out[5];

    size_t utf32Len = 5;

    size_t utf8Read, utf32Written;



    UTF8_to_UTF32Nat(utf8In, utf8Len, utf32Out, utf32Len, &utf8Read, &utf32Written);



    EXPECT_EQ(utf8Read, utf8Len);

    EXPECT_EQ(utf32Written, 5);

    for (size_t i = 0; i < utf32Written; ++i) {

        EXPECT_EQ(utf32Out[i], static_cast<UTF32Unit>(utf8In[i]));

    }

}



TEST_F(UnicodeConversionsTest_2071, SimpleUTF8Conversion_2071) {

    UTF8Unit utf8In[] = {0xE9, 0x9B, 0xBB}; // "電" in UTF-8

    size_t utf8Len = sizeof(utf8In);

    UTF32Unit utf32Out[1];

    size_t utf32Len = 1;

    size_t utf8Read, utf32Written;



    UTF8_to_UTF32Nat(utf8In, utf8Len, utf32Out, utf32Len, &utf8Read, &utf32Written);



    EXPECT_EQ(utf8Read, utf8Len);

    EXPECT_EQ(utf32Written, 1);

    EXPECT_EQ(utf32Out[0], static_cast<UTF32Unit>(0x96FB)); // "電" in UTF-32

}



TEST_F(UnicodeConversionsTest_2071, MixedASCIIAndUTF8Conversion_2071) {

    UTF8Unit utf8In[] = {'H', 'e', 0xE9, 0x9B, 0xBB}; // "He電"

    size_t utf8Len = sizeof(utf8In);

    UTF32Unit utf32Out[3];

    size_t utf32Len = 3;

    size_t utf8Read, utf32Written;



    UTF8_to_UTF32Nat(utf8In, utf8Len, utf32Out, utf32Len, &utf8Read, &utf32Written);



    EXPECT_EQ(utf8Read, utf8Len);

    EXPECT_EQ(utf32Written, 3);

    EXPECT_EQ(utf32Out[0], static_cast<UTF32Unit>('H'));

    EXPECT_EQ(utf32Out[1], static_cast<UTF32Unit>('e'));

    EXPECT_EQ(utf32Out[2], static_cast<UTF32Unit>(0x96FB)); // "電" in UTF-32

}



TEST_F(UnicodeConversionsTest_2071, IncompleteUTF8Sequence_2071) {

    UTF8Unit utf8In[] = {0xE9}; // Incomplete "電" in UTF-8

    size_t utf8Len = sizeof(utf8In);

    UTF32Unit utf32Out[1];

    size_t utf32Len = 1;

    size_t utf8Read, utf32Written;



    UTF8_to_UTF32Nat(utf8In, utf8Len, utf32Out, utf32Len, &utf8Read, &utf32Written);



    EXPECT_EQ(utf8Read, 0);

    EXPECT_EQ(utf32Written, 0);

}



TEST_F(UnicodeConversionsTest_2071, EmptyInput_2071) {

    UTF8Unit utf8In[] = {};

    size_t utf8Len = sizeof(utf8In);

    UTF32Unit utf32Out[1];

    size_t utf32Len = 1;

    size_t utf8Read, utf32Written;



    UTF8_to_UTF32Nat(utf8In, utf8Len, utf32Out, utf32Len, &utf8Read, &utf32Written);



    EXPECT_EQ(utf8Read, 0);

    EXPECT_EQ(utf32Written, 0);

}



TEST_F(UnicodeConversionsTest_2071, OutputBufferTooSmall_2071) {

    UTF8Unit utf8In[] = {'H', 'e', 0xE9, 0x9B, 0xBB}; // "He電"

    size_t utf8Len = sizeof(utf8In);

    UTF32Unit utf32Out[2];

    size_t utf32Len = 2;

    size_t utf8Read, utf32Written;



    UTF8_to_UTF32Nat(utf8In, utf8Len, utf32Out, utf32Len, &utf8Read, &utf32Written);



    EXPECT_EQ(utf8Read, 2); // Only 'H' and 'e' can be converted

    EXPECT_EQ(utf32Written, 2);

    EXPECT_EQ(utf32Out[0], static_cast<UTF32Unit>('H'));

    EXPECT_EQ(utf32Out[1], static_cast<UTF32Unit>('e'));

}



TEST_F(UnicodeConversionsTest_2071, SingleByteUTF8AtBoundary_2071) {

    UTF8Unit utf8In[] = {'A', 'B', 0xE9}; // "AB電"

    size_t utf8Len = sizeof(utf8In);

    UTF32Unit utf32Out[2];

    size_t utf32Len = 2;

    size_t utf8Read, utf32Written;



    UTF8_to_UTF32Nat(utf8In, utf8Len, utf32Out, utf32Len, &utf8Read, &utf32Written);



    EXPECT_EQ(utf8Read, 4); // 'A', 'B', and the incomplete "電"

    EXPECT_EQ(utf32Written, 2);

    EXPECT_EQ(utf32Out[0], static_cast<UTF32Unit>('A'));

    EXPECT_EQ(utf32Out[1], static_cast<UTF32Unit>('B'));

}
