#include <gtest/gtest.h>
#include <string>

// Declaration of the function under test
namespace Catch {
    bool contains(std::string const& s, std::string const& infix);
}

// Normal operation tests

TEST(CatchContainsTest_588, InfixFoundInMiddle_588) {
    EXPECT_TRUE(Catch::contains("hello world", "lo wo"));
}

TEST(CatchContainsTest_588, InfixFoundAtBeginning_588) {
    EXPECT_TRUE(Catch::contains("hello world", "hello"));
}

TEST(CatchContainsTest_588, InfixFoundAtEnd_588) {
    EXPECT_TRUE(Catch::contains("hello world", "world"));
}

TEST(CatchContainsTest_588, InfixNotFound_588) {
    EXPECT_FALSE(Catch::contains("hello world", "xyz"));
}

TEST(CatchContainsTest_588, ExactMatch_588) {
    EXPECT_TRUE(Catch::contains("hello", "hello"));
}

TEST(CatchContainsTest_588, SingleCharacterFound_588) {
    EXPECT_TRUE(Catch::contains("hello", "e"));
}

TEST(CatchContainsTest_588, SingleCharacterNotFound_588) {
    EXPECT_FALSE(Catch::contains("hello", "z"));
}

// Boundary condition tests

TEST(CatchContainsTest_588, EmptyInfixAlwaysFound_588) {
    EXPECT_TRUE(Catch::contains("hello", ""));
}

TEST(CatchContainsTest_588, EmptyStringEmptyInfix_588) {
    EXPECT_TRUE(Catch::contains("", ""));
}

TEST(CatchContainsTest_588, EmptyStringNonEmptyInfix_588) {
    EXPECT_FALSE(Catch::contains("", "a"));
}

TEST(CatchContainsTest_588, InfixLongerThanString_588) {
    EXPECT_FALSE(Catch::contains("hi", "hello world"));
}

TEST(CatchContainsTest_588, StringAndInfixSameSingleChar_588) {
    EXPECT_TRUE(Catch::contains("a", "a"));
}

TEST(CatchContainsTest_588, StringSingleCharInfixDifferent_588) {
    EXPECT_FALSE(Catch::contains("a", "b"));
}

// Case sensitivity tests

TEST(CatchContainsTest_588, CaseSensitiveNotFound_588) {
    EXPECT_FALSE(Catch::contains("Hello World", "hello"));
}

TEST(CatchContainsTest_588, CaseSensitiveFound_588) {
    EXPECT_TRUE(Catch::contains("Hello World", "Hello"));
}

// Special character tests

TEST(CatchContainsTest_588, ContainsSpaces_588) {
    EXPECT_TRUE(Catch::contains("hello world", " "));
}

TEST(CatchContainsTest_588, ContainsNewline_588) {
    EXPECT_TRUE(Catch::contains("hello\nworld", "\n"));
}

TEST(CatchContainsTest_588, ContainsTab_588) {
    EXPECT_TRUE(Catch::contains("hello\tworld", "\t"));
}

TEST(CatchContainsTest_588, ContainsNullCharInMiddle_588) {
    std::string s("hel\0lo", 6);
    std::string infix("\0", 1);
    EXPECT_TRUE(Catch::contains(s, infix));
}

// Repeated pattern tests

TEST(CatchContainsTest_588, RepeatedPatternFound_588) {
    EXPECT_TRUE(Catch::contains("aaaa", "aa"));
}

TEST(CatchContainsTest_588, PartialMatchNotSufficient_588) {
    EXPECT_FALSE(Catch::contains("abc", "abd"));
}

TEST(CatchContainsTest_588, OverlappingInfixFound_588) {
    EXPECT_TRUE(Catch::contains("abcabc", "cab"));
}
