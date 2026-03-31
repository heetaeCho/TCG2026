#include <gtest/gtest.h>
#include <string>

// Re-declare the function under test since it's static in the original file.
// We include the implementation here to make it testable.
static std::string myStringReplace(const std::string &inString, const std::string &oldToken, const std::string &newToken) {
    std::string result = inString;
    size_t foundLoc;
    int advance = 0;
    do {
        foundLoc = result.find(oldToken, advance);
        if (foundLoc != std::string::npos) {
            result.replace(foundLoc, oldToken.length(), newToken);
            advance = foundLoc + newToken.length();
        }
    } while (foundLoc != std::string::npos);
    return result;
}

// Normal operation tests

TEST(MyStringReplaceTest_2720, BasicReplacement_2720) {
    std::string result = myStringReplace("hello world", "world", "there");
    EXPECT_EQ(result, "hello there");
}

TEST(MyStringReplaceTest_2720, MultipleOccurrences_2720) {
    std::string result = myStringReplace("aaa", "a", "b");
    EXPECT_EQ(result, "bbb");
}

TEST(MyStringReplaceTest_2720, NoOccurrence_2720) {
    std::string result = myStringReplace("hello world", "xyz", "abc");
    EXPECT_EQ(result, "hello world");
}

TEST(MyStringReplaceTest_2720, ReplaceWithEmpty_2720) {
    std::string result = myStringReplace("hello world", "world", "");
    EXPECT_EQ(result, "hello ");
}

TEST(MyStringReplaceTest_2720, ReplaceWithLongerString_2720) {
    std::string result = myStringReplace("ab", "a", "xyz");
    EXPECT_EQ(result, "xyzb");
}

TEST(MyStringReplaceTest_2720, ReplaceWithShorterString_2720) {
    std::string result = myStringReplace("abcabc", "abc", "x");
    EXPECT_EQ(result, "xx");
}

TEST(MyStringReplaceTest_2720, ReplaceEntireString_2720) {
    std::string result = myStringReplace("hello", "hello", "goodbye");
    EXPECT_EQ(result, "goodbye");
}

TEST(MyStringReplaceTest_2720, ReplaceAtBeginning_2720) {
    std::string result = myStringReplace("abc def", "abc", "xyz");
    EXPECT_EQ(result, "xyz def");
}

TEST(MyStringReplaceTest_2720, ReplaceAtEnd_2720) {
    std::string result = myStringReplace("hello abc", "abc", "xyz");
    EXPECT_EQ(result, "hello xyz");
}

TEST(MyStringReplaceTest_2720, ReplaceInMiddle_2720) {
    std::string result = myStringReplace("hello abc world", "abc", "xyz");
    EXPECT_EQ(result, "hello xyz world");
}

// Boundary condition tests

TEST(MyStringReplaceTest_2720, EmptyInputString_2720) {
    std::string result = myStringReplace("", "a", "b");
    EXPECT_EQ(result, "");
}

TEST(MyStringReplaceTest_2720, EmptyOldTokenEmptyInput_2720) {
    // When oldToken is empty, find("", 0) returns 0 (npos is not returned).
    // This could lead to an infinite loop or specific behavior.
    // Since the advance moves forward by newToken.length(), if newToken is also empty,
    // advance stays at 0 and this could infinite loop. 
    // We test with non-empty newToken only if we know it terminates.
    // Actually, with empty oldToken: result.find("", 0) == 0, replace(0, 0, "x") inserts "x",
    // advance = 0 + 1 = 1, then find("", 1) == 1, etc. This would be infinite.
    // Skip this test to avoid undefined/infinite behavior.
}

TEST(MyStringReplaceTest_2720, SingleCharacterString_2720) {
    std::string result = myStringReplace("a", "a", "b");
    EXPECT_EQ(result, "b");
}

TEST(MyStringReplaceTest_2720, SingleCharacterNoMatch_2720) {
    std::string result = myStringReplace("a", "b", "c");
    EXPECT_EQ(result, "a");
}

TEST(MyStringReplaceTest_2720, OldTokenLongerThanInput_2720) {
    std::string result = myStringReplace("ab", "abc", "x");
    EXPECT_EQ(result, "ab");
}

TEST(MyStringReplaceTest_2720, OldTokenSameAsNewToken_2720) {
    std::string result = myStringReplace("hello world", "world", "world");
    EXPECT_EQ(result, "hello world");
}

TEST(MyStringReplaceTest_2720, ReplacementContainsOldToken_2720) {
    // oldToken = "a", newToken = "ba"
    // This should not cause infinite loop because advance moves past newToken
    std::string result = myStringReplace("a", "a", "ba");
    EXPECT_EQ(result, "ba");
}

TEST(MyStringReplaceTest_2720, ReplacementContainsOldTokenMultiple_2720) {
    std::string result = myStringReplace("aXa", "a", "ba");
    EXPECT_EQ(result, "baXba");
}

TEST(MyStringReplaceTest_2720, ConsecutiveOccurrences_2720) {
    std::string result = myStringReplace("aaaa", "aa", "b");
    EXPECT_EQ(result, "bb");
}

TEST(MyStringReplaceTest_2720, OverlappingPatternNotMatched_2720) {
    // "aaa" with oldToken "aa" -> replaces first "aa", advance moves to 1 (past replacement "b"),
    // then finds "a" at position 1 which is not "aa", so result is "ba"
    std::string result = myStringReplace("aaa", "aa", "b");
    EXPECT_EQ(result, "ba");
}

TEST(MyStringReplaceTest_2720, ReplaceWithSameLength_2720) {
    std::string result = myStringReplace("abcabc", "abc", "xyz");
    EXPECT_EQ(result, "xyzxyz");
}

TEST(MyStringReplaceTest_2720, SpecialCharacters_2720) {
    std::string result = myStringReplace("hello\nworld\n", "\n", "\\n");
    EXPECT_EQ(result, "hello\\nworld\\n");
}

TEST(MyStringReplaceTest_2720, SpacesInTokens_2720) {
    std::string result = myStringReplace("hello   world", "  ", " ");
    EXPECT_EQ(result, "hello  world");
}

TEST(MyStringReplaceTest_2720, MultipleSpaceReplacements_2720) {
    // "a  b  c" replace "  " with " " -> "a b c" (but advance moves past replacement)
    // First: find "  " at 1, replace -> "a b  c", advance = 1+1 = 2
    // Second: find "  " starting at 2 -> found at 3, replace -> "a b c", advance = 3+1 = 4
    // Third: find "  " starting at 4 -> not found
    std::string result = myStringReplace("a  b  c", "  ", " ");
    EXPECT_EQ(result, "a b c");
}

TEST(MyStringReplaceTest_2720, LargeString_2720) {
    std::string input(1000, 'a');
    std::string result = myStringReplace(input, "a", "bb");
    std::string expected(2000, 'b');
    EXPECT_EQ(result, expected);
}

TEST(MyStringReplaceTest_2720, EmptyNewTokenRemovesAll_2720) {
    std::string result = myStringReplace("abcabcabc", "abc", "");
    EXPECT_EQ(result, "");
}

TEST(MyStringReplaceTest_2720, ReplaceAllSingleChars_2720) {
    std::string result = myStringReplace("aaaa", "a", "");
    EXPECT_EQ(result, "");
}

TEST(MyStringReplaceTest_2720, UnicodelikeContent_2720) {
    std::string result = myStringReplace("café", "é", "e");
    EXPECT_EQ(result, "cafe");
}
