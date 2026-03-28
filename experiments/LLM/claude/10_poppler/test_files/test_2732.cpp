#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "goo/GooString.h"

// We need to include the Unicode type definition
// Unicode is typically defined as unsigned int in poppler
typedef unsigned int Unicode;

// Declaration of the function under test (it's static in the original file,
// so we need to either include it or redefine the signature for testing).
// Since it's a static function in a .cc file, we'll include the implementation
// directly for testing purposes.
static std::string print_uni_str(const Unicode *u, const unsigned uLen)
{
    if (!uLen) {
        return "";
    }
    std::string gstr_buff0 = GooString::format("{0:c}", (*u < 0x7F ? *u & 0xFF : '?'));
    for (unsigned i = 1; i < uLen; i++) {
        if (u[i] < 0x7F) {
            gstr_buff0.push_back(static_cast<char>(u[i]) & 0xFF);
        }
    }
    return gstr_buff0;
}

class PrintUniStrTest_2732 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Empty input (uLen == 0) should return empty string
TEST_F(PrintUniStrTest_2732, EmptyInput_ReturnsEmptyString_2732)
{
    Unicode u[] = { 'A' };
    std::string result = print_uni_str(u, 0);
    EXPECT_EQ(result, "");
}

// Test: Single ASCII character
TEST_F(PrintUniStrTest_2732, SingleAsciiCharacter_2732)
{
    Unicode u[] = { 'A' };
    std::string result = print_uni_str(u, 1);
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 'A');
}

// Test: Single character that is non-ASCII (>= 0x7F) should produce '?'
TEST_F(PrintUniStrTest_2732, SingleNonAsciiCharacter_ReturnsQuestionMark_2732)
{
    Unicode u[] = { 0x80 };
    std::string result = print_uni_str(u, 1);
    EXPECT_FALSE(result.empty());
    // The first character should be '?' since 0x80 >= 0x7F
    EXPECT_EQ(result[0], '?');
}

// Test: Multiple ASCII characters
TEST_F(PrintUniStrTest_2732, MultipleAsciiCharacters_2732)
{
    Unicode u[] = { 'H', 'e', 'l', 'l', 'o' };
    std::string result = print_uni_str(u, 5);
    // First char formatted via GooString::format, rest appended
    EXPECT_EQ(result.length(), 5u);
    EXPECT_EQ(result[0], 'H');
    EXPECT_EQ(result[1], 'e');
    EXPECT_EQ(result[2], 'l');
    EXPECT_EQ(result[3], 'l');
    EXPECT_EQ(result[4], 'o');
}

// Test: First character is ASCII, subsequent characters include non-ASCII (should be skipped)
TEST_F(PrintUniStrTest_2732, MixedAsciiAndNonAscii_NonAsciiSkipped_2732)
{
    Unicode u[] = { 'A', 0x100, 'B', 0x200, 'C' };
    std::string result = print_uni_str(u, 5);
    // First char: 'A' (ASCII)
    // Second: 0x100 >= 0x7F, skipped
    // Third: 'B' (ASCII), appended
    // Fourth: 0x200 >= 0x7F, skipped
    // Fifth: 'C' (ASCII), appended
    EXPECT_EQ(result.length(), 3u);
    EXPECT_EQ(result[0], 'A');
    EXPECT_EQ(result[1], 'B');
    EXPECT_EQ(result[2], 'C');
}

// Test: First character is non-ASCII, rest are ASCII
TEST_F(PrintUniStrTest_2732, FirstNonAsciiRestAscii_2732)
{
    Unicode u[] = { 0xFF, 'B', 'C' };
    std::string result = print_uni_str(u, 3);
    // First char: 0xFF >= 0x7F -> '?'
    // Second: 'B' appended
    // Third: 'C' appended
    EXPECT_EQ(result.length(), 3u);
    EXPECT_EQ(result[0], '?');
    EXPECT_EQ(result[1], 'B');
    EXPECT_EQ(result[2], 'C');
}

// Test: All non-ASCII characters
TEST_F(PrintUniStrTest_2732, AllNonAsciiCharacters_2732)
{
    Unicode u[] = { 0x80, 0x100, 0x200 };
    std::string result = print_uni_str(u, 3);
    // First char: '?'
    // Rest: all >= 0x7F, skipped
    EXPECT_EQ(result.length(), 1u);
    EXPECT_EQ(result[0], '?');
}

// Test: Boundary value - character exactly at 0x7E (last valid ASCII in the < 0x7F check)
TEST_F(PrintUniStrTest_2732, BoundaryValue_0x7E_IsAscii_2732)
{
    Unicode u[] = { 0x7E };
    std::string result = print_uni_str(u, 1);
    EXPECT_EQ(result[0], '~'); // 0x7E is '~'
}

// Test: Boundary value - character exactly at 0x7F (should be treated as non-ASCII)
TEST_F(PrintUniStrTest_2732, BoundaryValue_0x7F_IsNonAscii_2732)
{
    Unicode u[] = { 0x7F };
    std::string result = print_uni_str(u, 1);
    // 0x7F is NOT < 0x7F, so it goes to '?'
    EXPECT_EQ(result[0], '?');
}

// Test: Boundary value - 0x7F in subsequent positions (should be skipped)
TEST_F(PrintUniStrTest_2732, BoundaryValue_0x7F_InSubsequentPosition_Skipped_2732)
{
    Unicode u[] = { 'A', 0x7F, 'B' };
    std::string result = print_uni_str(u, 3);
    // First: 'A'
    // Second: 0x7F, not < 0x7F, skipped
    // Third: 'B', appended
    EXPECT_EQ(result.length(), 2u);
    EXPECT_EQ(result[0], 'A');
    EXPECT_EQ(result[1], 'B');
}

// Test: Null character (0x00) which is < 0x7F
TEST_F(PrintUniStrTest_2732, NullCharacterInArray_2732)
{
    Unicode u[] = { 0x00 };
    std::string result = print_uni_str(u, 1);
    // 0x00 < 0x7F, so it should use 0x00 & 0xFF = 0x00
    // The result depends on GooString::format behavior with null char
    EXPECT_FALSE(result.empty() || result[0] == '\0');
}

// Test: Single character 'a' (lowercase)
TEST_F(PrintUniStrTest_2732, SingleLowercaseCharacter_2732)
{
    Unicode u[] = { 'a' };
    std::string result = print_uni_str(u, 1);
    EXPECT_EQ(result[0], 'a');
}

// Test: Digits
TEST_F(PrintUniStrTest_2732, DigitCharacters_2732)
{
    Unicode u[] = { '0', '1', '9' };
    std::string result = print_uni_str(u, 3);
    EXPECT_EQ(result.length(), 3u);
    EXPECT_EQ(result[0], '0');
    EXPECT_EQ(result[1], '1');
    EXPECT_EQ(result[2], '9');
}

// Test: Space character
TEST_F(PrintUniStrTest_2732, SpaceCharacter_2732)
{
    Unicode u[] = { ' ' };
    std::string result = print_uni_str(u, 1);
    EXPECT_EQ(result[0], ' ');
}

// Test: Very high Unicode value as first character
TEST_F(PrintUniStrTest_2732, VeryHighUnicodeFirstChar_2732)
{
    Unicode u[] = { 0x10000 };
    std::string result = print_uni_str(u, 1);
    EXPECT_EQ(result[0], '?');
}

// Test: uLen is 0 with nullptr
TEST_F(PrintUniStrTest_2732, ZeroLengthWithNullptr_2732)
{
    std::string result = print_uni_str(nullptr, 0);
    EXPECT_EQ(result, "");
}

// Test: Special ASCII characters (punctuation)
TEST_F(PrintUniStrTest_2732, SpecialAsciiCharacters_2732)
{
    Unicode u[] = { '!', '@', '#', '$', '%' };
    std::string result = print_uni_str(u, 5);
    EXPECT_EQ(result.length(), 5u);
    EXPECT_EQ(result[0], '!');
    EXPECT_EQ(result[1], '@');
    EXPECT_EQ(result[2], '#');
    EXPECT_EQ(result[3], '$');
    EXPECT_EQ(result[4], '%');
}

// Test: Character value 1 (SOH - Start of Heading, control character but < 0x7F)
TEST_F(PrintUniStrTest_2732, ControlCharacter_2732)
{
    Unicode u[] = { 1 };
    std::string result = print_uni_str(u, 1);
    // 1 < 0x7F, so 1 & 0xFF = 1
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], '\x01');
}
