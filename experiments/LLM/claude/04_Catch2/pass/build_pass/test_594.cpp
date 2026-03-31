#include <gtest/gtest.h>
#include <string>

// Declare the function under test
namespace Catch {
    bool replaceInPlace(std::string& str, std::string const& replaceThis, std::string const& withThis);
}

class ReplaceInPlaceTest_594 : public ::testing::Test {
protected:
};

// Normal operation tests

TEST_F(ReplaceInPlaceTest_594, SingleOccurrenceReplacement_594) {
    std::string str = "Hello World";
    bool result = Catch::replaceInPlace(str, "World", "Earth");
    EXPECT_TRUE(result);
    EXPECT_EQ(str, "Hello Earth");
}

TEST_F(ReplaceInPlaceTest_594, MultipleOccurrencesReplacement_594) {
    std::string str = "aaa";
    bool result = Catch::replaceInPlace(str, "a", "bb");
    EXPECT_TRUE(result);
    EXPECT_EQ(str, "bbbbbb");
}

TEST_F(ReplaceInPlaceTest_594, ReplaceWithShorterString_594) {
    std::string str = "Hello Beautiful World";
    bool result = Catch::replaceInPlace(str, "Beautiful ", "");
    EXPECT_TRUE(result);
    EXPECT_EQ(str, "Hello World");
}

TEST_F(ReplaceInPlaceTest_594, ReplaceWithLongerString_594) {
    std::string str = "ab";
    bool result = Catch::replaceInPlace(str, "ab", "abcdef");
    EXPECT_TRUE(result);
    EXPECT_EQ(str, "abcdef");
}

TEST_F(ReplaceInPlaceTest_594, ReplaceAtBeginning_594) {
    std::string str = "Hello World";
    bool result = Catch::replaceInPlace(str, "Hello", "Goodbye");
    EXPECT_TRUE(result);
    EXPECT_EQ(str, "Goodbye World");
}

TEST_F(ReplaceInPlaceTest_594, ReplaceAtEnd_594) {
    std::string str = "Hello World";
    bool result = Catch::replaceInPlace(str, "World", "Universe");
    EXPECT_TRUE(result);
    EXPECT_EQ(str, "Hello Universe");
}

TEST_F(ReplaceInPlaceTest_594, ReplaceEntireString_594) {
    std::string str = "abc";
    bool result = Catch::replaceInPlace(str, "abc", "xyz");
    EXPECT_TRUE(result);
    EXPECT_EQ(str, "xyz");
}

TEST_F(ReplaceInPlaceTest_594, ReplaceWithEmptyString_594) {
    std::string str = "Hello World";
    bool result = Catch::replaceInPlace(str, "World", "");
    EXPECT_TRUE(result);
    EXPECT_EQ(str, "Hello ");
}

TEST_F(ReplaceInPlaceTest_594, ReplaceMultipleAdjacentOccurrences_594) {
    std::string str = "aaaa";
    bool result = Catch::replaceInPlace(str, "aa", "b");
    EXPECT_TRUE(result);
    EXPECT_EQ(str, "bb");
}

TEST_F(ReplaceInPlaceTest_594, ReplaceWithSameString_594) {
    std::string str = "Hello World";
    bool result = Catch::replaceInPlace(str, "World", "World");
    EXPECT_TRUE(result);
    EXPECT_EQ(str, "Hello World");
}

// Boundary condition tests

TEST_F(ReplaceInPlaceTest_594, NoMatchReturnsFalse_594) {
    std::string str = "Hello World";
    bool result = Catch::replaceInPlace(str, "xyz", "abc");
    EXPECT_FALSE(result);
    EXPECT_EQ(str, "Hello World");
}

TEST_F(ReplaceInPlaceTest_594, EmptyStringNoMatch_594) {
    std::string str = "";
    bool result = Catch::replaceInPlace(str, "abc", "xyz");
    EXPECT_FALSE(result);
    EXPECT_EQ(str, "");
}

TEST_F(ReplaceInPlaceTest_594, ReplaceEntireStringWithEmpty_594) {
    std::string str = "abc";
    bool result = Catch::replaceInPlace(str, "abc", "");
    EXPECT_TRUE(result);
    EXPECT_EQ(str, "");
}

TEST_F(ReplaceInPlaceTest_594, ReplaceSingleCharWithSingleChar_594) {
    std::string str = "a";
    bool result = Catch::replaceInPlace(str, "a", "b");
    EXPECT_TRUE(result);
    EXPECT_EQ(str, "b");
}

TEST_F(ReplaceInPlaceTest_594, ReplacePatternLongerThanString_594) {
    std::string str = "ab";
    bool result = Catch::replaceInPlace(str, "abcd", "xyz");
    EXPECT_FALSE(result);
    EXPECT_EQ(str, "ab");
}

TEST_F(ReplaceInPlaceTest_594, MultipleNonOverlappingOccurrences_594) {
    std::string str = "xAxBxAx";
    bool result = Catch::replaceInPlace(str, "x", "yy");
    EXPECT_TRUE(result);
    EXPECT_EQ(str, "yyAyyByyAyy");
}

TEST_F(ReplaceInPlaceTest_594, ReplaceAllOccurrencesRemoved_594) {
    std::string str = "abababab";
    bool result = Catch::replaceInPlace(str, "ab", "");
    EXPECT_TRUE(result);
    EXPECT_EQ(str, "");
}

TEST_F(ReplaceInPlaceTest_594, ReplaceMiddleOfString_594) {
    std::string str = "abcdef";
    bool result = Catch::replaceInPlace(str, "cd", "XX");
    EXPECT_TRUE(result);
    EXPECT_EQ(str, "abXXef");
}

TEST_F(ReplaceInPlaceTest_594, ReplaceMultiCharPatternMultipleTimes_594) {
    std::string str = "the cat sat on the mat";
    bool result = Catch::replaceInPlace(str, "the", "a");
    EXPECT_TRUE(result);
    EXPECT_EQ(str, "a cat sat on a mat");
}

TEST_F(ReplaceInPlaceTest_594, ReplaceSingleCharacterMultipleTimes_594) {
    std::string str = "banana";
    bool result = Catch::replaceInPlace(str, "a", "o");
    EXPECT_TRUE(result);
    EXPECT_EQ(str, "bonono");
}

TEST_F(ReplaceInPlaceTest_594, ReplaceWithSubstringOfReplaceThis_594) {
    // Ensures no infinite loop: replacing "aa" with "a"
    std::string str = "aaaa";
    bool result = Catch::replaceInPlace(str, "aa", "a");
    EXPECT_TRUE(result);
    EXPECT_EQ(str, "aa");
}

TEST_F(ReplaceInPlaceTest_594, StringContainsOnlyPattern_594) {
    std::string str = "xxx";
    bool result = Catch::replaceInPlace(str, "xxx", "y");
    EXPECT_TRUE(result);
    EXPECT_EQ(str, "y");
}

TEST_F(ReplaceInPlaceTest_594, PatternAtVeryEnd_594) {
    std::string str = "testend";
    bool result = Catch::replaceInPlace(str, "end", "START");
    EXPECT_TRUE(result);
    EXPECT_EQ(str, "testSTART");
}

TEST_F(ReplaceInPlaceTest_594, PatternAtVeryBeginning_594) {
    std::string str = "startmiddle";
    bool result = Catch::replaceInPlace(str, "start", "BEGIN");
    EXPECT_TRUE(result);
    EXPECT_EQ(str, "BEGINmiddle");
}

TEST_F(ReplaceInPlaceTest_594, NoMatchPreservesOriginalString_594) {
    std::string str = "unchanged string";
    std::string original = str;
    bool result = Catch::replaceInPlace(str, "missing", "replacement");
    EXPECT_FALSE(result);
    EXPECT_EQ(str, original);
}

TEST_F(ReplaceInPlaceTest_594, ReplaceSpecialCharacters_594) {
    std::string str = "line1\nline2\nline3";
    bool result = Catch::replaceInPlace(str, "\n", " ");
    EXPECT_TRUE(result);
    EXPECT_EQ(str, "line1 line2 line3");
}
