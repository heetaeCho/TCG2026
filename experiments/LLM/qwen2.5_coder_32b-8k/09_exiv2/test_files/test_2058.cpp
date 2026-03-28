#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "UnicodeConversions.hpp"

#include <string>



using namespace testing;



// Test fixture for FromUTF16 function

class UnicodeConversionsTest_2058 : public ::testing::Test {

protected:

    std::string utf8Str;

};



// Normal operation: Convert a simple UTF-16 string to UTF-8

TEST_F(UnicodeConversionsTest_2058, SimpleConversionLE_2058) {

    const UTF16Unit utf16In[] = { 0x48, 0x65, 0x6C, 0x6C, 0x6F }; // "Hello" in UTF-16 LE

    FromUTF16(utf16In, 5, &utf8Str, false);

    EXPECT_EQ(utf8Str, "Hello");

}



TEST_F(UnicodeConversionsTest_2058, SimpleConversionBE_2058) {

    const UTF16Unit utf16In[] = { 0x48, 0x00, 0x65, 0x00, 0x6C, 0x00, 0x6C, 0x00, 0x6F, 0x00 }; // "Hello" in UTF-16 BE

    FromUTF16(utf16In, 5, &utf8Str, true);

    EXPECT_EQ(utf8Str, "Hello");

}



// Boundary condition: Empty input

TEST_F(UnicodeConversionsTest_2058, EmptyInputLE_2058) {

    const UTF16Unit utf16In[] = {};

    FromUTF16(utf16In, 0, &utf8Str, false);

    EXPECT_EQ(utf8Str, "");

}



TEST_F(UnicodeConversionsTest_2058, EmptyInputBE_2058) {

    const UTF16Unit utf16In[] = {};

    FromUTF16(utf16In, 0, &utf8Str, true);

    EXPECT_EQ(utf8Str, "");

}



// Boundary condition: Single character

TEST_F(UnicodeConversionsTest_2058, SingleCharLE_2058) {

    const UTF16Unit utf16In[] = { 0x41 }; // "A" in UTF-16 LE

    FromUTF16(utf16In, 1, &utf8Str, false);

    EXPECT_EQ(utf8Str, "A");

}



TEST_F(UnicodeConversionsTest_2058, SingleCharBE_2058) {

    const UTF16Unit utf16In[] = { 0x41, 0x00 }; // "A" in UTF-16 BE

    FromUTF16(utf16In, 1, &utf8Str, true);

    EXPECT_EQ(utf8Str, "A");

}



// Exceptional case: Incomplete Unicode at end of string

TEST_F(UnicodeConversionsTest_2058, IncompleteUnicodeLE_2058) {

    const UTF16Unit utf16In[] = { 0xD8, 0x34 }; // Incomplete surrogate pair in UTF-16 LE

    EXPECT_THROW({

        FromUTF16(utf16In, 1, &utf8Str, false);

    }, XMP_Error);

}



TEST_F(UnicodeConversionsTest_2058, IncompleteUnicodeBE_2058) {

    const UTF16Unit utf16In[] = { 0x34, 0xD8 }; // Incomplete surrogate pair in UTF-16 BE

    EXPECT_THROW({

        FromUTF16(utf16In, 1, &utf8Str, true);

    }, XMP_Error);

}



// Test case for multi-byte characters

TEST_F(UnicodeConversionsTest_2058, MultiByteCharsLE_2058) {

    const UTF16Unit utf16In[] = { 0x4F60, 0x597D }; // "你好" in UTF-16 LE

    FromUTF16(utf16In, 2, &utf8Str, false);

    EXPECT_EQ(utf8Str, "\xE4\xBD\xA0\xE5%A5\xBD"); // "你好" in UTF-8

}



TEST_F(UnicodeConversionsTest_2058, MultiByteCharsBE_2058) {

    const UTF16Unit utf16In[] = { 0x604F, 0x7D59 }; // "你好" in UTF-16 BE

    FromUTF16(utf16In, 2, &utf8Str, true);

    EXPECT_EQ(utf8Str, "\xE4\xBD\xA0\xE5%A5\xBD"); // "你好" in UTF-8

}
