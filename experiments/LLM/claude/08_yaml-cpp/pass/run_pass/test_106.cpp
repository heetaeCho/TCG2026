#include <gtest/gtest.h>
#include "stringsource.h"

namespace YAML {

class StringCharSourceTest_106 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction and basic boolean conversion with non-empty string
TEST_F(StringCharSourceTest_106, ConstructWithNonEmptyString_BoolTrue_106) {
    const char* str = "hello";
    StringCharSource source(str, 5);
    EXPECT_TRUE(static_cast<bool>(source));
}

// Test construction with empty string (size 0)
TEST_F(StringCharSourceTest_106, ConstructWithEmptyString_BoolFalse_106) {
    const char* str = "";
    StringCharSource source(str, 0);
    EXPECT_FALSE(static_cast<bool>(source));
}

// Test operator! with non-empty string
TEST_F(StringCharSourceTest_106, OperatorNot_NonEmpty_ReturnsFalse_106) {
    const char* str = "hello";
    StringCharSource source(str, 5);
    EXPECT_FALSE(!source);
}

// Test operator! with empty string
TEST_F(StringCharSourceTest_106, OperatorNot_Empty_ReturnsTrue_106) {
    const char* str = "";
    StringCharSource source(str, 0);
    EXPECT_TRUE(!source);
}

// Test operator[] accessing first character
TEST_F(StringCharSourceTest_106, SubscriptOperator_FirstChar_106) {
    const char* str = "abcde";
    StringCharSource source(str, 5);
    EXPECT_EQ('a', source[0]);
}

// Test operator[] accessing subsequent characters
TEST_F(StringCharSourceTest_106, SubscriptOperator_OffsetChars_106) {
    const char* str = "abcde";
    StringCharSource source(str, 5);
    EXPECT_EQ('b', source[1]);
    EXPECT_EQ('c', source[2]);
    EXPECT_EQ('d', source[3]);
    EXPECT_EQ('e', source[4]);
}

// Test prefix increment operator
TEST_F(StringCharSourceTest_106, PrefixIncrement_AdvancesPosition_106) {
    const char* str = "abcde";
    StringCharSource source(str, 5);
    EXPECT_EQ('a', source[0]);
    ++source;
    EXPECT_EQ('b', source[0]);
    ++source;
    EXPECT_EQ('c', source[0]);
}

// Test prefix increment returns reference to self
TEST_F(StringCharSourceTest_106, PrefixIncrement_ReturnsSelf_106) {
    const char* str = "abcde";
    StringCharSource source(str, 5);
    StringCharSource& ref = ++source;
    EXPECT_EQ(&source, &ref);
}

// Test operator+= advances by given offset
TEST_F(StringCharSourceTest_106, PlusEqualsOperator_AdvancesByOffset_106) {
    const char* str = "abcdefgh";
    StringCharSource source(str, 8);
    source += 3;
    EXPECT_EQ('d', source[0]);
}

// Test operator+= returns reference to self
TEST_F(StringCharSourceTest_106, PlusEqualsOperator_ReturnsSelf_106) {
    const char* str = "abcde";
    StringCharSource source(str, 5);
    StringCharSource& ref = (source += 2);
    EXPECT_EQ(&source, &ref);
}

// Test operator+ creates new source at offset
TEST_F(StringCharSourceTest_106, PlusOperator_CreatesNewAtOffset_106) {
    const char* str = "abcde";
    StringCharSource source(str, 5);
    const StringCharSource newSource = source + 2;
    EXPECT_EQ('c', newSource[0]);
    // Original should be unchanged
    EXPECT_EQ('a', source[0]);
}

// Test incrementing to end makes bool false
TEST_F(StringCharSourceTest_106, IncrementToEnd_BoolBecomesFalse_106) {
    const char* str = "ab";
    StringCharSource source(str, 2);
    EXPECT_TRUE(static_cast<bool>(source));
    ++source;
    EXPECT_TRUE(static_cast<bool>(source));
    ++source;
    EXPECT_FALSE(static_cast<bool>(source));
}

// Test operator+= to end makes bool false
TEST_F(StringCharSourceTest_106, PlusEqualsToEnd_BoolBecomesFalse_106) {
    const char* str = "abcde";
    StringCharSource source(str, 5);
    source += 5;
    EXPECT_FALSE(static_cast<bool>(source));
}

// Test single character string
TEST_F(StringCharSourceTest_106, SingleCharString_106) {
    const char* str = "x";
    StringCharSource source(str, 1);
    EXPECT_TRUE(static_cast<bool>(source));
    EXPECT_EQ('x', source[0]);
    ++source;
    EXPECT_FALSE(static_cast<bool>(source));
}

// Test operator+= with zero offset does nothing
TEST_F(StringCharSourceTest_106, PlusEqualsZero_NoChange_106) {
    const char* str = "hello";
    StringCharSource source(str, 5);
    source += 0;
    EXPECT_EQ('h', source[0]);
    EXPECT_TRUE(static_cast<bool>(source));
}

// Test operator+ with zero offset
TEST_F(StringCharSourceTest_106, PlusZero_SamePosition_106) {
    const char* str = "hello";
    StringCharSource source(str, 5);
    const StringCharSource newSource = source + 0;
    EXPECT_EQ('h', newSource[0]);
}

// Test chained increments
TEST_F(StringCharSourceTest_106, ChainedIncrements_106) {
    const char* str = "abcdef";
    StringCharSource source(str, 6);
    ++(++source);
    EXPECT_EQ('c', source[0]);
}

// Test operator[] with offset after increment
TEST_F(StringCharSourceTest_106, SubscriptAfterIncrement_106) {
    const char* str = "abcde";
    StringCharSource source(str, 5);
    ++source;
    EXPECT_EQ('b', source[0]);
    EXPECT_EQ('c', source[1]);
    EXPECT_EQ('d', source[2]);
}

// Test combination of increment and plus equals
TEST_F(StringCharSourceTest_106, CombinedIncrementAndPlusEquals_106) {
    const char* str = "abcdefghij";
    StringCharSource source(str, 10);
    ++source;       // offset 1 -> 'b'
    source += 3;    // offset 4 -> 'e'
    EXPECT_EQ('e', source[0]);
    ++source;       // offset 5 -> 'f'
    EXPECT_EQ('f', source[0]);
}

// Test operator+ does not modify original
TEST_F(StringCharSourceTest_106, PlusOperatorDoesNotModifyOriginal_106) {
    const char* str = "abcde";
    StringCharSource source(str, 5);
    const StringCharSource newSource = source + 4;
    EXPECT_EQ('a', source[0]);
    EXPECT_EQ('e', newSource[0]);
}

// Test bool conversion at boundary (one before end)
TEST_F(StringCharSourceTest_106, BoolAtOneBeforeEnd_106) {
    const char* str = "abc";
    StringCharSource source(str, 3);
    source += 2;
    EXPECT_TRUE(static_cast<bool>(source));
    EXPECT_EQ('c', source[0]);
}

}  // namespace YAML
