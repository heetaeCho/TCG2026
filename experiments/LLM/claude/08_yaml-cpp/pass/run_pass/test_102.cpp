#include <gtest/gtest.h>
#include "stringsource.h"

namespace YAML {

class StringCharSourceTest_102 : public ::testing::Test {
protected:
    // Helper to create StringCharSource instances
};

// Test: A non-empty string source should be truthy
TEST_F(StringCharSourceTest_102, NonEmptySourceIsTruthy_102) {
    const char* str = "hello";
    StringCharSource source(str, 5);
    EXPECT_TRUE(static_cast<bool>(source));
}

// Test: An empty string source (size 0) should be falsy
TEST_F(StringCharSourceTest_102, EmptySourceIsFalsy_102) {
    const char* str = "";
    StringCharSource source(str, 0);
    EXPECT_FALSE(static_cast<bool>(source));
}

// Test: operator! should return true for empty source
TEST_F(StringCharSourceTest_102, OperatorNotOnEmptySource_102) {
    const char* str = "";
    StringCharSource source(str, 0);
    EXPECT_TRUE(!source);
}

// Test: operator! should return false for non-empty source
TEST_F(StringCharSourceTest_102, OperatorNotOnNonEmptySource_102) {
    const char* str = "abc";
    StringCharSource source(str, 3);
    EXPECT_FALSE(!source);
}

// Test: operator[] should return the correct character at index 0
TEST_F(StringCharSourceTest_102, SubscriptOperatorAtZero_102) {
    const char* str = "hello";
    StringCharSource source(str, 5);
    EXPECT_EQ('h', source[0]);
}

// Test: operator[] should return correct characters at various indices
TEST_F(StringCharSourceTest_102, SubscriptOperatorAtVariousIndices_102) {
    const char* str = "abcde";
    StringCharSource source(str, 5);
    EXPECT_EQ('a', source[0]);
    EXPECT_EQ('b', source[1]);
    EXPECT_EQ('c', source[2]);
    EXPECT_EQ('d', source[3]);
    EXPECT_EQ('e', source[4]);
}

// Test: Pre-increment operator should advance the source
TEST_F(StringCharSourceTest_102, PreIncrementAdvancesSource_102) {
    const char* str = "ab";
    StringCharSource source(str, 2);
    EXPECT_EQ('a', source[0]);
    ++source;
    EXPECT_EQ('b', source[0]);
}

// Test: Pre-increment to exhaustion makes source falsy
TEST_F(StringCharSourceTest_102, PreIncrementToExhaustion_102) {
    const char* str = "a";
    StringCharSource source(str, 1);
    EXPECT_TRUE(static_cast<bool>(source));
    ++source;
    EXPECT_FALSE(static_cast<bool>(source));
}

// Test: operator+= should advance offset by given amount
TEST_F(StringCharSourceTest_102, PlusEqualsAdvancesOffset_102) {
    const char* str = "abcdef";
    StringCharSource source(str, 6);
    source += 3;
    EXPECT_EQ('d', source[0]);
}

// Test: operator+= to exact end makes source falsy
TEST_F(StringCharSourceTest_102, PlusEqualsToEnd_102) {
    const char* str = "abc";
    StringCharSource source(str, 3);
    source += 3;
    EXPECT_FALSE(static_cast<bool>(source));
}

// Test: operator+ returns a new source advanced by i positions
TEST_F(StringCharSourceTest_102, PlusOperatorReturnsAdvancedCopy_102) {
    const char* str = "abcdef";
    StringCharSource source(str, 6);
    StringCharSource advanced = source + 2;
    // Original should be unchanged
    EXPECT_EQ('a', source[0]);
    // Advanced copy should point to 'c'
    EXPECT_EQ('c', advanced[0]);
}

// Test: operator+ with 0 should return equivalent source
TEST_F(StringCharSourceTest_102, PlusOperatorWithZero_102) {
    const char* str = "abc";
    StringCharSource source(str, 3);
    StringCharSource same = source + 0;
    EXPECT_EQ('a', same[0]);
    EXPECT_TRUE(static_cast<bool>(same));
}

// Test: Multiple increments followed by subscript
TEST_F(StringCharSourceTest_102, MultipleIncrementsAndSubscript_102) {
    const char* str = "xyz";
    StringCharSource source(str, 3);
    ++source;
    ++source;
    EXPECT_EQ('z', source[0]);
    ++source;
    EXPECT_FALSE(static_cast<bool>(source));
}

// Test: Single character string source
TEST_F(StringCharSourceTest_102, SingleCharacterSource_102) {
    const char* str = "X";
    StringCharSource source(str, 1);
    EXPECT_TRUE(static_cast<bool>(source));
    EXPECT_EQ('X', source[0]);
    ++source;
    EXPECT_FALSE(static_cast<bool>(source));
}

// Test: operator+= with 0 should not change state
TEST_F(StringCharSourceTest_102, PlusEqualsZero_102) {
    const char* str = "abc";
    StringCharSource source(str, 3);
    source += 0;
    EXPECT_TRUE(static_cast<bool>(source));
    EXPECT_EQ('a', source[0]);
}

// Test: Combination of += and ++ operations
TEST_F(StringCharSourceTest_102, CombinedPlusEqualsAndIncrement_102) {
    const char* str = "abcdef";
    StringCharSource source(str, 6);
    source += 2;  // now at 'c'
    EXPECT_EQ('c', source[0]);
    ++source;     // now at 'd'
    EXPECT_EQ('d', source[0]);
    source += 2;  // now at 'f'
    EXPECT_EQ('f', source[0]);
    ++source;     // exhausted
    EXPECT_FALSE(static_cast<bool>(source));
}

// Test: operator+ does not modify the original source
TEST_F(StringCharSourceTest_102, PlusOperatorDoesNotModifyOriginal_102) {
    const char* str = "abcde";
    StringCharSource source(str, 5);
    StringCharSource copy = source + 4;
    // Original unchanged
    EXPECT_EQ('a', source[0]);
    EXPECT_TRUE(static_cast<bool>(source));
    // Copy at last char
    EXPECT_EQ('e', copy[0]);
    EXPECT_TRUE(static_cast<bool>(copy));
}

// Test: Subscript with offset after increment
TEST_F(StringCharSourceTest_102, SubscriptWithOffsetAfterIncrement_102) {
    const char* str = "abcdef";
    StringCharSource source(str, 6);
    ++source; // at 'b'
    EXPECT_EQ('b', source[0]);
    EXPECT_EQ('c', source[1]);
    EXPECT_EQ('d', source[2]);
}

}  // namespace YAML
