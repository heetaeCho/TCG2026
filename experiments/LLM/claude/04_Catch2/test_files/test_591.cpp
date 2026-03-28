#include <gtest/gtest.h>

// Declare the function under test
namespace Catch {
    char toLower(char c);
}

// Normal operation: lowercase letters should remain lowercase
TEST(CatchToLowerTest_591, LowercaseLettersUnchanged_591) {
    for (char c = 'a'; c <= 'z'; ++c) {
        EXPECT_EQ(c, Catch::toLower(c)) << "Failed for char: " << c;
    }
}

// Normal operation: uppercase letters should be converted to lowercase
TEST(CatchToLowerTest_591, UppercaseLettersConverted_591) {
    for (char c = 'A'; c <= 'Z'; ++c) {
        char expected = c - 'A' + 'a';
        EXPECT_EQ(expected, Catch::toLower(c)) << "Failed for char: " << c;
    }
}

// Normal operation: digits should remain unchanged
TEST(CatchToLowerTest_591, DigitsUnchanged_591) {
    for (char c = '0'; c <= '9'; ++c) {
        EXPECT_EQ(c, Catch::toLower(c)) << "Failed for char: " << c;
    }
}

// Normal operation: special/punctuation characters should remain unchanged
TEST(CatchToLowerTest_591, SpecialCharactersUnchanged_591) {
    const char specials[] = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
                             '-', '_', '=', '+', '[', ']', '{', '}', '|', '\\',
                             ';', ':', '\'', '"', ',', '.', '<', '>', '/', '?',
                             '`', '~'};
    for (char c : specials) {
        EXPECT_EQ(c, Catch::toLower(c)) << "Failed for char: " << c;
    }
}

// Boundary condition: space character
TEST(CatchToLowerTest_591, SpaceUnchanged_591) {
    EXPECT_EQ(' ', Catch::toLower(' '));
}

// Boundary condition: null character
TEST(CatchToLowerTest_591, NullCharUnchanged_591) {
    EXPECT_EQ('\0', Catch::toLower('\0'));
}

// Boundary condition: first uppercase letter 'A'
TEST(CatchToLowerTest_591, FirstUppercaseLetter_591) {
    EXPECT_EQ('a', Catch::toLower('A'));
}

// Boundary condition: last uppercase letter 'Z'
TEST(CatchToLowerTest_591, LastUppercaseLetter_591) {
    EXPECT_EQ('z', Catch::toLower('Z'));
}

// Boundary condition: first lowercase letter 'a'
TEST(CatchToLowerTest_591, FirstLowercaseLetter_591) {
    EXPECT_EQ('a', Catch::toLower('a'));
}

// Boundary condition: last lowercase letter 'z'
TEST(CatchToLowerTest_591, LastLowercaseLetter_591) {
    EXPECT_EQ('z', Catch::toLower('z'));
}

// Boundary condition: tab character
TEST(CatchToLowerTest_591, TabCharUnchanged_591) {
    EXPECT_EQ('\t', Catch::toLower('\t'));
}

// Boundary condition: newline character
TEST(CatchToLowerTest_591, NewlineCharUnchanged_591) {
    EXPECT_EQ('\n', Catch::toLower('\n'));
}

// Boundary condition: char with value 127 (DEL)
TEST(CatchToLowerTest_591, DelCharUnchanged_591) {
    EXPECT_EQ(static_cast<char>(127), Catch::toLower(static_cast<char>(127)));
}

// Boundary condition: char with value 1 (SOH)
TEST(CatchToLowerTest_591, SOHCharUnchanged_591) {
    EXPECT_EQ(static_cast<char>(1), Catch::toLower(static_cast<char>(1)));
}

// Specific individual uppercase to lowercase conversions
TEST(CatchToLowerTest_591, SpecificConversions_591) {
    EXPECT_EQ('h', Catch::toLower('H'));
    EXPECT_EQ('e', Catch::toLower('E'));
    EXPECT_EQ('l', Catch::toLower('L'));
    EXPECT_EQ('o', Catch::toLower('O'));
    EXPECT_EQ('w', Catch::toLower('W'));
    EXPECT_EQ('r', Catch::toLower('R'));
    EXPECT_EQ('d', Catch::toLower('D'));
}

// Edge case: characters just outside the uppercase range
TEST(CatchToLowerTest_591, CharsAdjacentToUppercaseRange_591) {
    // '@' is just before 'A' in ASCII
    EXPECT_EQ('@', Catch::toLower('@'));
    // '[' is just after 'Z' in ASCII
    EXPECT_EQ('[', Catch::toLower('['));
}

// Edge case: characters just outside the lowercase range
TEST(CatchToLowerTest_591, CharsAdjacentToLowercaseRange_591) {
    // '`' is just before 'a' in ASCII
    EXPECT_EQ('`', Catch::toLower('`'));
    // '{' is just after 'z' in ASCII
    EXPECT_EQ('{', Catch::toLower('{'));
}
