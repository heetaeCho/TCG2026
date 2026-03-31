#include <gtest/gtest.h>
#include "stringsource.h"

namespace YAML {

// Since the full implementation isn't available in the header shown,
// we need to work with the known interface from the dependency info.
// We'll test based on the observable interface.

class StringCharSourceTest_104 : public ::testing::Test {
protected:
    // Helper to create StringCharSource instances
};

// Test: Construction with valid string and basic boolean conversion
TEST_F(StringCharSourceTest_104, ConstructWithValidString_BoolIsTrue_104) {
    const char* str = "hello";
    StringCharSource source(str, 5);
    EXPECT_TRUE(static_cast<bool>(source));
}

// Test: Construction with empty size yields false
TEST_F(StringCharSourceTest_104, ConstructWithZeroSize_BoolIsFalse_104) {
    const char* str = "hello";
    StringCharSource source(str, 0);
    EXPECT_FALSE(static_cast<bool>(source));
}

// Test: operator! on valid source returns false
TEST_F(StringCharSourceTest_104, OperatorNot_ValidSource_ReturnsFalse_104) {
    const char* str = "hello";
    StringCharSource source(str, 5);
    EXPECT_FALSE(!source);
}

// Test: operator! on empty source returns true
TEST_F(StringCharSourceTest_104, OperatorNot_EmptySource_ReturnsTrue_104) {
    const char* str = "hello";
    StringCharSource source(str, 0);
    EXPECT_TRUE(!source);
}

// Test: operator[] accesses correct character at index 0
TEST_F(StringCharSourceTest_104, SubscriptOperator_Index0_ReturnsFirstChar_104) {
    const char* str = "abcde";
    StringCharSource source(str, 5);
    EXPECT_EQ('a', source[0]);
}

// Test: operator[] accesses correct character at various indices
TEST_F(StringCharSourceTest_104, SubscriptOperator_VariousIndices_ReturnsCorrectChars_104) {
    const char* str = "abcde";
    StringCharSource source(str, 5);
    EXPECT_EQ('a', source[0]);
    EXPECT_EQ('b', source[1]);
    EXPECT_EQ('c', source[2]);
    EXPECT_EQ('d', source[3]);
    EXPECT_EQ('e', source[4]);
}

// Test: operator++ advances the source by one
TEST_F(StringCharSourceTest_104, PreIncrement_AdvancesByOne_104) {
    const char* str = "abcde";
    StringCharSource source(str, 5);
    EXPECT_EQ('a', source[0]);
    ++source;
    EXPECT_EQ('b', source[0]);
}

// Test: operator++ multiple times
TEST_F(StringCharSourceTest_104, PreIncrement_MultipleTimes_AdvancesCorrectly_104) {
    const char* str = "abcde";
    StringCharSource source(str, 5);
    ++source;
    ++source;
    ++source;
    EXPECT_EQ('d', source[0]);
}

// Test: operator+= advances by given offset
TEST_F(StringCharSourceTest_104, PlusEquals_AdvancesByOffset_104) {
    const char* str = "abcde";
    StringCharSource source(str, 5);
    source += 3;
    EXPECT_EQ('d', source[0]);
}

// Test: operator+ returns new source advanced by i
TEST_F(StringCharSourceTest_104, OperatorPlus_ReturnsAdvancedCopy_104) {
    const char* str = "abcde";
    StringCharSource source(str, 5);
    const StringCharSource advanced = source + 2;
    // Original should be unchanged
    EXPECT_EQ('a', source[0]);
    // Advanced copy should be at offset 2
    EXPECT_EQ('c', advanced[0]);
}

// Test: Incrementing to end makes source evaluate to false
TEST_F(StringCharSourceTest_104, IncrementToEnd_BecomesFalse_104) {
    const char* str = "ab";
    StringCharSource source(str, 2);
    EXPECT_TRUE(static_cast<bool>(source));
    ++source;
    EXPECT_TRUE(static_cast<bool>(source));
    ++source;
    EXPECT_FALSE(static_cast<bool>(source));
}

// Test: operator+= to end makes source evaluate to false
TEST_F(StringCharSourceTest_104, PlusEqualsToEnd_BecomesFalse_104) {
    const char* str = "abcde";
    StringCharSource source(str, 5);
    source += 5;
    EXPECT_FALSE(static_cast<bool>(source));
    EXPECT_TRUE(!source);
}

// Test: Single character string
TEST_F(StringCharSourceTest_104, SingleCharString_WorksCorrectly_104) {
    const char* str = "x";
    StringCharSource source(str, 1);
    EXPECT_TRUE(static_cast<bool>(source));
    EXPECT_EQ('x', source[0]);
    ++source;
    EXPECT_FALSE(static_cast<bool>(source));
}

// Test: operator+ with 0 offset returns equivalent source
TEST_F(StringCharSourceTest_104, OperatorPlus_ZeroOffset_ReturnsSamePosition_104) {
    const char* str = "hello";
    StringCharSource source(str, 5);
    const StringCharSource same = source + 0;
    EXPECT_EQ('h', same[0]);
}

// Test: operator+= with 0 offset doesn't change position
TEST_F(StringCharSourceTest_104, PlusEquals_ZeroOffset_NoChange_104) {
    const char* str = "hello";
    StringCharSource source(str, 5);
    source += 0;
    EXPECT_EQ('h', source[0]);
    EXPECT_TRUE(static_cast<bool>(source));
}

// Test: operator++ returns reference to self
TEST_F(StringCharSourceTest_104, PreIncrement_ReturnsSelf_104) {
    const char* str = "abc";
    StringCharSource source(str, 3);
    StringCharSource& ref = ++source;
    EXPECT_EQ('b', ref[0]);
    EXPECT_EQ('b', source[0]);
}

// Test: operator+= returns reference to self
TEST_F(StringCharSourceTest_104, PlusEquals_ReturnsSelf_104) {
    const char* str = "abcde";
    StringCharSource source(str, 5);
    StringCharSource& ref = (source += 2);
    EXPECT_EQ('c', ref[0]);
    EXPECT_EQ('c', source[0]);
}

// Test: Combining ++ and += operations
TEST_F(StringCharSourceTest_104, CombinedIncrementAndPlusEquals_104) {
    const char* str = "abcdefgh";
    StringCharSource source(str, 8);
    ++source;         // now at 'b'
    source += 2;      // now at 'd'
    ++source;         // now at 'e'
    EXPECT_EQ('e', source[0]);
    EXPECT_EQ('f', source[1]);
}

// Test: operator[] with offset after advancing
TEST_F(StringCharSourceTest_104, SubscriptAfterAdvance_CorrectOffset_104) {
    const char* str = "abcdefgh";
    StringCharSource source(str, 8);
    source += 3;
    EXPECT_EQ('d', source[0]);
    EXPECT_EQ('e', source[1]);
    EXPECT_EQ('f', source[2]);
}

}  // namespace YAML
