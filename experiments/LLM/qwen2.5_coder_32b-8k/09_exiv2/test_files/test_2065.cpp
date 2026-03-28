#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming UTF8Unit and UTF32Unit are defined somewhere in the codebase.

typedef unsigned char UTF8Unit;

typedef unsigned int UTF32Unit;



extern void CodePoint_from_UTF8(const UTF8Unit* utf8In, const size_t utf8Len, UTF32Unit* cpOut, size_t* utf8Read);



class UnicodeConversionsTest : public ::testing::Test {

protected:

    UTF8Unit input[4];

    UTF32Unit output;

    size_t bytesRead;



    void SetUp() override {

        memset(input, 0, sizeof(input));

        output = 0;

        bytesRead = 0;

    }

};



TEST_F(UnicodeConversionsTest_NormalOperation_2065, SingleByteASCIICharacter_2065) {

    input[0] = 'A'; // ASCII value for 'A' is 65

    CodePoint_from_UTF8(input, 1, &output, &bytesRead);

    EXPECT_EQ(output, static_cast<UTF32Unit>('A'));

    EXPECT_EQ(bytesRead, 1u);

}



TEST_F(UnicodeConversionsTest_NormalOperation_2065, MultiByteCharacter_2065) {

    input[0] = 0xC3; // First byte of UTF-8 for 'é'

    input[1] = 0xA9; // Second byte of UTF-8 for 'é'

    CodePoint_from_UTF8(input, 2, &output, &bytesRead);

    EXPECT_EQ(output, static_cast<UTF32Unit>(0xE9)); // Unicode code point for 'é'

    EXPECT_EQ(bytesRead, 2u);

}



TEST_F(UnicodeConversionsTest_BoundaryConditions_2065, EmptyInput_2065) {

    CodePoint_from_UTF8(input, 0, &output, &bytesRead);

    EXPECT_EQ(output, static_cast<UTF32Unit>(0));

    EXPECT_EQ(bytesRead, 0u);

}



TEST_F(UnicodeConversionsTest_BoundaryConditions_2065, SingleByteNullCharacter_2065) {

    input[0] = '\0'; // Null character

    CodePoint_from_UTF8(input, 1, &output, &bytesRead);

    EXPECT_EQ(output, static_cast<UTF32Unit>('\0'));

    EXPECT_EQ(bytesRead, 1u);

}



TEST_F(UnicodeConversionsTest_ExceptionalCases_2065, InvalidUTF8Sequence_2065) {

    input[0] = 0xFF; // Invalid first byte of UTF-8

    CodePoint_from_UTF8(input, 1, &output, &bytesRead);

    EXPECT_EQ(output, static_cast<UTF32Unit>(0xFF)); // Behavior is undefined, but should not crash

    EXPECT_EQ(bytesRead, 1u); // Should read at least one byte

}
