#include <gtest/gtest.h>

// Include necessary type definitions
typedef unsigned int XMP_Uns32;

// Include the code under test
// We need to replicate the inline function from the header since it's an inline in a .incl_cpp file
#define BanAllEntityUsage 0
static inline bool IsStartChar_ASCII(XMP_Uns32 cp) {
    if ((('a' <= cp) && (cp <= 'z')) || (('A' <= cp) && (cp <= 'Z')) || (cp == '_')) return true;
    return false;
}

// Test fixture
class IsStartCharASCIITest_1875 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ===== Normal operation tests =====

TEST_F(IsStartCharASCIITest_1875, LowercaseA_ReturnsTrue_1875) {
    EXPECT_TRUE(IsStartChar_ASCII('a'));
}

TEST_F(IsStartCharASCIITest_1875, LowercaseZ_ReturnsTrue_1875) {
    EXPECT_TRUE(IsStartChar_ASCII('z'));
}

TEST_F(IsStartCharASCIITest_1875, LowercaseM_ReturnsTrue_1875) {
    EXPECT_TRUE(IsStartChar_ASCII('m'));
}

TEST_F(IsStartCharASCIITest_1875, UppercaseA_ReturnsTrue_1875) {
    EXPECT_TRUE(IsStartChar_ASCII('A'));
}

TEST_F(IsStartCharASCIITest_1875, UppercaseZ_ReturnsTrue_1875) {
    EXPECT_TRUE(IsStartChar_ASCII('Z'));
}

TEST_F(IsStartCharASCIITest_1875, UppercaseM_ReturnsTrue_1875) {
    EXPECT_TRUE(IsStartChar_ASCII('M'));
}

TEST_F(IsStartCharASCIITest_1875, Underscore_ReturnsTrue_1875) {
    EXPECT_TRUE(IsStartChar_ASCII('_'));
}

// ===== All lowercase letters =====

TEST_F(IsStartCharASCIITest_1875, AllLowercaseLetters_ReturnTrue_1875) {
    for (XMP_Uns32 cp = 'a'; cp <= 'z'; ++cp) {
        EXPECT_TRUE(IsStartChar_ASCII(cp)) << "Failed for character: " << (char)cp;
    }
}

// ===== All uppercase letters =====

TEST_F(IsStartCharASCIITest_1875, AllUppercaseLetters_ReturnTrue_1875) {
    for (XMP_Uns32 cp = 'A'; cp <= 'Z'; ++cp) {
        EXPECT_TRUE(IsStartChar_ASCII(cp)) << "Failed for character: " << (char)cp;
    }
}

// ===== Boundary conditions =====

TEST_F(IsStartCharASCIITest_1875, CharBeforeLowercaseA_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII('a' - 1));
}

TEST_F(IsStartCharASCIITest_1875, CharAfterLowercaseZ_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII('z' + 1));
}

TEST_F(IsStartCharASCIITest_1875, CharBeforeUppercaseA_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII('A' - 1));
}

TEST_F(IsStartCharASCIITest_1875, CharAfterUppercaseZ_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII('Z' + 1));
}

TEST_F(IsStartCharASCIITest_1875, CharBeforeUnderscore_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII('_' - 1));
}

TEST_F(IsStartCharASCIITest_1875, CharAfterUnderscore_ReturnsFalse_1875) {
    // '`' is the character after '_'
    EXPECT_FALSE(IsStartChar_ASCII('_' + 1));
}

// ===== Digits should return false =====

TEST_F(IsStartCharASCIITest_1875, Digit0_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII('0'));
}

TEST_F(IsStartCharASCIITest_1875, Digit9_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII('9'));
}

TEST_F(IsStartCharASCIITest_1875, AllDigits_ReturnFalse_1875) {
    for (XMP_Uns32 cp = '0'; cp <= '9'; ++cp) {
        EXPECT_FALSE(IsStartChar_ASCII(cp)) << "Failed for digit: " << (char)cp;
    }
}

// ===== Special characters should return false =====

TEST_F(IsStartCharASCIITest_1875, Space_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII(' '));
}

TEST_F(IsStartCharASCIITest_1875, Hyphen_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII('-'));
}

TEST_F(IsStartCharASCIITest_1875, Period_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII('.'));
}

TEST_F(IsStartCharASCIITest_1875, Colon_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII(':'));
}

TEST_F(IsStartCharASCIITest_1875, Semicolon_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII(';'));
}

TEST_F(IsStartCharASCIITest_1875, AtSign_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII('@'));
}

TEST_F(IsStartCharASCIITest_1875, ExclamationMark_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII('!'));
}

TEST_F(IsStartCharASCIITest_1875, Hash_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII('#'));
}

TEST_F(IsStartCharASCIITest_1875, DollarSign_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII('$'));
}

TEST_F(IsStartCharASCIITest_1875, Slash_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII('/'));
}

TEST_F(IsStartCharASCIITest_1875, Backslash_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII('\\'));
}

// ===== Edge values =====

TEST_F(IsStartCharASCIITest_1875, ZeroCodePoint_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII(0));
}

TEST_F(IsStartCharASCIITest_1875, NullChar_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII('\0'));
}

TEST_F(IsStartCharASCIITest_1875, MaxASCII_127_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII(127));
}

TEST_F(IsStartCharASCIITest_1875, Value128_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII(128));
}

TEST_F(IsStartCharASCIITest_1875, Value255_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII(255));
}

TEST_F(IsStartCharASCIITest_1875, LargeCodePoint_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII(0x10000));
}

TEST_F(IsStartCharASCIITest_1875, MaxUns32_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII(0xFFFFFFFF));
}

// ===== Characters between uppercase and lowercase ranges =====

TEST_F(IsStartCharASCIITest_1875, LeftBracket_ReturnsFalse_1875) {
    // '[' is between 'Z' and 'a'
    EXPECT_FALSE(IsStartChar_ASCII('['));
}

TEST_F(IsStartCharASCIITest_1875, RightBracket_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII(']'));
}

TEST_F(IsStartCharASCIITest_1875, Caret_ReturnsFalse_1875) {
    // '^' is just before '_'
    EXPECT_FALSE(IsStartChar_ASCII('^'));
}

TEST_F(IsStartCharASCIITest_1875, Backtick_ReturnsFalse_1875) {
    // '`' is between '_' and 'a'
    EXPECT_FALSE(IsStartChar_ASCII('`'));
}

// ===== Brace and tilde (after 'z') =====

TEST_F(IsStartCharASCIITest_1875, OpenBrace_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII('{'));
}

TEST_F(IsStartCharASCIITest_1875, Tilde_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII('~'));
}

// ===== Tab and newline =====

TEST_F(IsStartCharASCIITest_1875, Tab_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII('\t'));
}

TEST_F(IsStartCharASCIITest_1875, Newline_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII('\n'));
}

TEST_F(IsStartCharASCIITest_1875, CarriageReturn_ReturnsFalse_1875) {
    EXPECT_FALSE(IsStartChar_ASCII('\r'));
}

// ===== Specific lowercase boundary letters =====

TEST_F(IsStartCharASCIITest_1875, LowercaseB_ReturnsTrue_1875) {
    EXPECT_TRUE(IsStartChar_ASCII('b'));
}

TEST_F(IsStartCharASCIITest_1875, LowercaseY_ReturnsTrue_1875) {
    EXPECT_TRUE(IsStartChar_ASCII('y'));
}

TEST_F(IsStartCharASCIITest_1875, UppercaseB_ReturnsTrue_1875) {
    EXPECT_TRUE(IsStartChar_ASCII('B'));
}

TEST_F(IsStartCharASCIITest_1875, UppercaseY_ReturnsTrue_1875) {
    EXPECT_TRUE(IsStartChar_ASCII('Y'));
}
