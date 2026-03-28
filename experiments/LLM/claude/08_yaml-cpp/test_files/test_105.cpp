#include <gtest/gtest.h>
#include "stringsource.h"

namespace YAML {
namespace {

class StringCharSourceTest_105 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Construction with a valid string
TEST_F(StringCharSourceTest_105, ConstructWithValidString_105) {
    const char* str = "Hello, World!";
    StringCharSource source(str, 13);
    EXPECT_TRUE(static_cast<bool>(source));
}

// Test: Construction with empty string
TEST_F(StringCharSourceTest_105, ConstructWithEmptyString_105) {
    const char* str = "";
    StringCharSource source(str, 0);
    EXPECT_FALSE(static_cast<bool>(source));
}

// Test: operator bool returns true for non-empty source
TEST_F(StringCharSourceTest_105, OperatorBoolTrueForNonEmpty_105) {
    const char* str = "test";
    StringCharSource source(str, 4);
    EXPECT_TRUE(static_cast<bool>(source));
    EXPECT_FALSE(!source);
}

// Test: operator bool returns false for empty source
TEST_F(StringCharSourceTest_105, OperatorBoolFalseForEmpty_105) {
    const char* str = "";
    StringCharSource source(str, 0);
    EXPECT_FALSE(static_cast<bool>(source));
    EXPECT_TRUE(!source);
}

// Test: operator[] accesses correct character at index 0
TEST_F(StringCharSourceTest_105, OperatorBracketAccessFirstChar_105) {
    const char* str = "ABCDE";
    StringCharSource source(str, 5);
    EXPECT_EQ('A', source[0]);
}

// Test: operator[] accesses characters at various indices
TEST_F(StringCharSourceTest_105, OperatorBracketAccessVariousIndices_105) {
    const char* str = "ABCDE";
    StringCharSource source(str, 5);
    EXPECT_EQ('A', source[0]);
    EXPECT_EQ('B', source[1]);
    EXPECT_EQ('C', source[2]);
    EXPECT_EQ('D', source[3]);
    EXPECT_EQ('E', source[4]);
}

// Test: operator+ with positive offset
TEST_F(StringCharSourceTest_105, OperatorPlusPositiveOffset_105) {
    const char* str = "ABCDE";
    StringCharSource source(str, 5);
    StringCharSource advanced = source + 2;
    EXPECT_EQ('C', advanced[0]);
}

// Test: operator+ with zero offset returns same position
TEST_F(StringCharSourceTest_105, OperatorPlusZeroOffset_105) {
    const char* str = "ABCDE";
    StringCharSource source(str, 5);
    StringCharSource same = source + 0;
    EXPECT_EQ('A', same[0]);
}

// Test: operator+ with negative offset that would go below zero clamps to zero
TEST_F(StringCharSourceTest_105, OperatorPlusNegativeOffsetClampsToZero_105) {
    const char* str = "ABCDE";
    StringCharSource source(str, 5);
    // Source is at offset 0, adding -1 should clamp to 0
    StringCharSource clamped = source + (-1);
    EXPECT_EQ('A', clamped[0]);
}

// Test: operator+ with negative offset after advancing
TEST_F(StringCharSourceTest_105, OperatorPlusNegativeOffsetAfterAdvance_105) {
    const char* str = "ABCDE";
    StringCharSource source(str, 5);
    StringCharSource advanced = source + 3;
    EXPECT_EQ('D', advanced[0]);
    StringCharSource backedUp = advanced + (-2);
    EXPECT_EQ('B', backedUp[0]);
}

// Test: operator+ does not modify the original source
TEST_F(StringCharSourceTest_105, OperatorPlusDoesNotModifyOriginal_105) {
    const char* str = "ABCDE";
    StringCharSource source(str, 5);
    StringCharSource advanced = source + 3;
    EXPECT_EQ('A', source[0]);
    EXPECT_EQ('D', advanced[0]);
}

// Test: operator++ (prefix increment)
TEST_F(StringCharSourceTest_105, OperatorPrefixIncrement_105) {
    const char* str = "ABCDE";
    StringCharSource source(str, 5);
    EXPECT_EQ('A', source[0]);
    ++source;
    EXPECT_EQ('B', source[0]);
    ++source;
    EXPECT_EQ('C', source[0]);
}

// Test: operator+= with offset
TEST_F(StringCharSourceTest_105, OperatorPlusEqualsOffset_105) {
    const char* str = "ABCDE";
    StringCharSource source(str, 5);
    source += 3;
    EXPECT_EQ('D', source[0]);
}

// Test: operator+= with zero offset
TEST_F(StringCharSourceTest_105, OperatorPlusEqualsZero_105) {
    const char* str = "ABCDE";
    StringCharSource source(str, 5);
    source += 0;
    EXPECT_EQ('A', source[0]);
}

// Test: Advancing past the end makes source evaluate to false
TEST_F(StringCharSourceTest_105, AdvancePastEndMakesFalse_105) {
    const char* str = "AB";
    StringCharSource source(str, 2);
    EXPECT_TRUE(static_cast<bool>(source));
    source += 2;
    EXPECT_FALSE(static_cast<bool>(source));
}

// Test: operator++ chained multiple times reaches end
TEST_F(StringCharSourceTest_105, IncrementToEnd_105) {
    const char* str = "AB";
    StringCharSource source(str, 2);
    EXPECT_TRUE(static_cast<bool>(source));
    ++source;
    EXPECT_TRUE(static_cast<bool>(source));
    EXPECT_EQ('B', source[0]);
    ++source;
    EXPECT_FALSE(static_cast<bool>(source));
}

// Test: operator+ with large negative offset clamps to zero
TEST_F(StringCharSourceTest_105, OperatorPlusLargeNegativeClamps_105) {
    const char* str = "ABCDE";
    StringCharSource source(str, 5);
    source += 2;
    // Now at offset 2 ('C'), adding -100 should clamp to 0
    StringCharSource clamped = source + (-100);
    EXPECT_EQ('A', clamped[0]);
}

// Test: operator+ with positive offset advancing to end
TEST_F(StringCharSourceTest_105, OperatorPlusAdvanceToEnd_105) {
    const char* str = "ABC";
    StringCharSource source(str, 3);
    StringCharSource atEnd = source + 3;
    EXPECT_FALSE(static_cast<bool>(atEnd));
}

// Test: Single character string
TEST_F(StringCharSourceTest_105, SingleCharacterString_105) {
    const char* str = "X";
    StringCharSource source(str, 1);
    EXPECT_TRUE(static_cast<bool>(source));
    EXPECT_EQ('X', source[0]);
    ++source;
    EXPECT_FALSE(static_cast<bool>(source));
}

// Test: operator! is consistent with operator bool
TEST_F(StringCharSourceTest_105, OperatorNotConsistentWithBool_105) {
    const char* str = "test";
    StringCharSource source(str, 4);
    EXPECT_EQ(!static_cast<bool>(source), !source);
    source += 4;
    EXPECT_EQ(!static_cast<bool>(source), !source);
}

// Test: Chaining operator+= calls
TEST_F(StringCharSourceTest_105, ChainingPlusEquals_105) {
    const char* str = "ABCDEFGH";
    StringCharSource source(str, 8);
    source += 2;
    EXPECT_EQ('C', source[0]);
    source += 3;
    EXPECT_EQ('F', source[0]);
    source += 1;
    EXPECT_EQ('G', source[0]);
}

// Test: operator+ returns a copy, original unchanged after multiple operations
TEST_F(StringCharSourceTest_105, OperatorPlusReturnsCopy_105) {
    const char* str = "ABCDEF";
    StringCharSource source(str, 6);
    StringCharSource s1 = source + 1;
    StringCharSource s2 = source + 2;
    StringCharSource s3 = source + 5;
    EXPECT_EQ('A', source[0]);
    EXPECT_EQ('B', s1[0]);
    EXPECT_EQ('C', s2[0]);
    EXPECT_EQ('F', s3[0]);
}

// Test: operator+= returns reference to self (chaining)
TEST_F(StringCharSourceTest_105, OperatorPlusEqualsReturnsReference_105) {
    const char* str = "ABCDEF";
    StringCharSource source(str, 6);
    StringCharSource& ref = (source += 2);
    EXPECT_EQ(&ref, &source);
    EXPECT_EQ('C', source[0]);
}

// Test: operator++ returns reference to self (chaining)
TEST_F(StringCharSourceTest_105, OperatorPrefixIncrementReturnsReference_105) {
    const char* str = "ABCDEF";
    StringCharSource source(str, 6);
    StringCharSource& ref = ++source;
    EXPECT_EQ(&ref, &source);
    EXPECT_EQ('B', source[0]);
}

}  // namespace
}  // namespace YAML
