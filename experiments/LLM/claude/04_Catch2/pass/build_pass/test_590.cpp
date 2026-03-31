#include <gtest/gtest.h>
#include <string>

// We need to include the Catch2 header that declares toLower
// Based on the file path, we include the relevant header
namespace Catch {
    std::string toLower(std::string const& s);
}

// Normal operation tests

TEST(CatchToLowerTest_590, EmptyString_590) {
    std::string input = "";
    std::string result = Catch::toLower(input);
    EXPECT_EQ(result, "");
}

TEST(CatchToLowerTest_590, AllLowercase_590) {
    std::string input = "hello";
    std::string result = Catch::toLower(input);
    EXPECT_EQ(result, "hello");
}

TEST(CatchToLowerTest_590, AllUppercase_590) {
    std::string input = "HELLO";
    std::string result = Catch::toLower(input);
    EXPECT_EQ(result, "hello");
}

TEST(CatchToLowerTest_590, MixedCase_590) {
    std::string input = "HeLLo WoRLd";
    std::string result = Catch::toLower(input);
    EXPECT_EQ(result, "hello world");
}

TEST(CatchToLowerTest_590, SingleUppercaseChar_590) {
    std::string input = "A";
    std::string result = Catch::toLower(input);
    EXPECT_EQ(result, "a");
}

TEST(CatchToLowerTest_590, SingleLowercaseChar_590) {
    std::string input = "a";
    std::string result = Catch::toLower(input);
    EXPECT_EQ(result, "a");
}

TEST(CatchToLowerTest_590, StringWithNumbers_590) {
    std::string input = "Hello123World";
    std::string result = Catch::toLower(input);
    EXPECT_EQ(result, "hello123world");
}

TEST(CatchToLowerTest_590, StringWithSpecialChars_590) {
    std::string input = "Hello!@#$%World";
    std::string result = Catch::toLower(input);
    EXPECT_EQ(result, "hello!@#$%world");
}

TEST(CatchToLowerTest_590, StringWithSpaces_590) {
    std::string input = "   HELLO   ";
    std::string result = Catch::toLower(input);
    EXPECT_EQ(result, "   hello   ");
}

TEST(CatchToLowerTest_590, AllUppercaseAlphabet_590) {
    std::string input = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string result = Catch::toLower(input);
    EXPECT_EQ(result, "abcdefghijklmnopqrstuvwxyz");
}

TEST(CatchToLowerTest_590, AlreadyLowercaseAlphabet_590) {
    std::string input = "abcdefghijklmnopqrstuvwxyz";
    std::string result = Catch::toLower(input);
    EXPECT_EQ(result, "abcdefghijklmnopqrstuvwxyz");
}

TEST(CatchToLowerTest_590, DigitsOnly_590) {
    std::string input = "1234567890";
    std::string result = Catch::toLower(input);
    EXPECT_EQ(result, "1234567890");
}

TEST(CatchToLowerTest_590, OriginalStringUnmodified_590) {
    std::string input = "HELLO";
    std::string result = Catch::toLower(input);
    EXPECT_EQ(input, "HELLO");
    EXPECT_EQ(result, "hello");
}

TEST(CatchToLowerTest_590, StringWithNewlines_590) {
    std::string input = "HELLO\nWORLD\n";
    std::string result = Catch::toLower(input);
    EXPECT_EQ(result, "hello\nworld\n");
}

TEST(CatchToLowerTest_590, StringWithTabs_590) {
    std::string input = "HELLO\tWORLD";
    std::string result = Catch::toLower(input);
    EXPECT_EQ(result, "hello\tworld");
}

TEST(CatchToLowerTest_590, LongString_590) {
    std::string input(1000, 'A');
    std::string expected(1000, 'a');
    std::string result = Catch::toLower(input);
    EXPECT_EQ(result, expected);
}

TEST(CatchToLowerTest_590, BoundaryCharsAroundUppercase_590) {
    // Characters just before 'A' (@) and just after 'Z' ([) should not change
    std::string input = "@AZ[";
    std::string result = Catch::toLower(input);
    EXPECT_EQ(result, "@az[");
}

TEST(CatchToLowerTest_590, BoundaryCharsAroundLowercase_590) {
    // Characters just before 'a' (`) and just after 'z' ({) should not change
    std::string input = "`az{";
    std::string result = Catch::toLower(input);
    EXPECT_EQ(result, "`az{");
}

TEST(CatchToLowerTest_590, NullCharacterInString_590) {
    std::string input("HE\0LO", 5);
    std::string result = Catch::toLower(input);
    EXPECT_EQ(result.size(), 5u);
    EXPECT_EQ(result[0], 'h');
    EXPECT_EQ(result[1], 'e');
    EXPECT_EQ(result[2], '\0');
    EXPECT_EQ(result[3], 'l');
    EXPECT_EQ(result[4], 'o');
}
