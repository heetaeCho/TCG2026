#include <gtest/gtest.h>
#include "stringsource.h"

namespace YAML {

class StringCharSourceTest_103 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test: Basic indexing operator returns correct character
TEST_F(StringCharSourceTest_103, IndexOperatorReturnsCorrectChar_103) {
  const char* str = "Hello, World!";
  StringCharSource source(str, 13);
  EXPECT_EQ('H', source[0]);
  EXPECT_EQ('e', source[1]);
  EXPECT_EQ('l', source[2]);
  EXPECT_EQ('l', source[3]);
  EXPECT_EQ('o', source[4]);
  EXPECT_EQ(',', source[5]);
  EXPECT_EQ(' ', source[6]);
  EXPECT_EQ('W', source[7]);
}

// Test: Last character accessible via index
TEST_F(StringCharSourceTest_103, IndexOperatorLastChar_103) {
  const char* str = "ABCDE";
  StringCharSource source(str, 5);
  EXPECT_EQ('E', source[4]);
}

// Test: Single character string
TEST_F(StringCharSourceTest_103, SingleCharString_103) {
  const char* str = "X";
  StringCharSource source(str, 1);
  EXPECT_EQ('X', source[0]);
}

// Test: Operator bool returns true for non-empty source
TEST_F(StringCharSourceTest_103, OperatorBoolTrueWhenValid_103) {
  const char* str = "Test";
  StringCharSource source(str, 4);
  EXPECT_TRUE(static_cast<bool>(source));
}

// Test: Operator ! returns false for non-empty source
TEST_F(StringCharSourceTest_103, OperatorNotFalseWhenValid_103) {
  const char* str = "Test";
  StringCharSource source(str, 4);
  EXPECT_FALSE(!source);
}

// Test: Operator bool returns false for empty source
TEST_F(StringCharSourceTest_103, OperatorBoolFalseWhenEmpty_103) {
  const char* str = "";
  StringCharSource source(str, 0);
  EXPECT_FALSE(static_cast<bool>(source));
}

// Test: Operator ! returns true for empty source
TEST_F(StringCharSourceTest_103, OperatorNotTrueWhenEmpty_103) {
  const char* str = "";
  StringCharSource source(str, 0);
  EXPECT_TRUE(!source);
}

// Test: Pre-increment advances offset
TEST_F(StringCharSourceTest_103, PreIncrementAdvancesOffset_103) {
  const char* str = "ABCDEF";
  StringCharSource source(str, 6);
  EXPECT_EQ('A', source[0]);
  ++source;
  EXPECT_EQ('B', source[0]);
  ++source;
  EXPECT_EQ('C', source[0]);
}

// Test: Operator += advances offset by given amount
TEST_F(StringCharSourceTest_103, PlusEqualsAdvancesOffset_103) {
  const char* str = "ABCDEFGH";
  StringCharSource source(str, 8);
  EXPECT_EQ('A', source[0]);
  source += 3;
  EXPECT_EQ('D', source[0]);
  EXPECT_EQ('E', source[1]);
}

// Test: Operator + returns a new source advanced by i positions
TEST_F(StringCharSourceTest_103, PlusOperatorReturnsAdvancedCopy_103) {
  const char* str = "ABCDEFGH";
  StringCharSource source(str, 8);
  StringCharSource advanced = source + 4;
  EXPECT_EQ('E', advanced[0]);
  // Original should remain unchanged
  EXPECT_EQ('A', source[0]);
}

// Test: Incrementing to end makes source evaluate to false
TEST_F(StringCharSourceTest_103, IncrementToEndBecomesFalse_103) {
  const char* str = "AB";
  StringCharSource source(str, 2);
  EXPECT_TRUE(static_cast<bool>(source));
  ++source;
  EXPECT_TRUE(static_cast<bool>(source));
  ++source;
  EXPECT_FALSE(static_cast<bool>(source));
}

// Test: PlusEquals to end makes source evaluate to false
TEST_F(StringCharSourceTest_103, PlusEqualsToEndBecomesFalse_103) {
  const char* str = "ABCD";
  StringCharSource source(str, 4);
  EXPECT_TRUE(static_cast<bool>(source));
  source += 4;
  EXPECT_FALSE(static_cast<bool>(source));
}

// Test: Operator + does not modify original source
TEST_F(StringCharSourceTest_103, PlusOperatorDoesNotModifyOriginal_103) {
  const char* str = "Hello";
  StringCharSource source(str, 5);
  StringCharSource copy = source + 2;
  EXPECT_EQ('H', source[0]);
  EXPECT_EQ('l', copy[0]);
}

// Test: Chained increments
TEST_F(StringCharSourceTest_103, ChainedIncrements_103) {
  const char* str = "12345";
  StringCharSource source(str, 5);
  ++(++source);
  EXPECT_EQ('3', source[0]);
}

// Test: Index after increment accesses correct position
TEST_F(StringCharSourceTest_103, IndexAfterIncrementCorrect_103) {
  const char* str = "abcdef";
  StringCharSource source(str, 6);
  source += 2;
  EXPECT_EQ('c', source[0]);
  EXPECT_EQ('d', source[1]);
  EXPECT_EQ('e', source[2]);
  EXPECT_EQ('f', source[3]);
}

// Test: Operator += with zero does not change position
TEST_F(StringCharSourceTest_103, PlusEqualsZeroNoChange_103) {
  const char* str = "Test";
  StringCharSource source(str, 4);
  source += 0;
  EXPECT_EQ('T', source[0]);
  EXPECT_TRUE(static_cast<bool>(source));
}

// Test: Operator + with zero returns equivalent source
TEST_F(StringCharSourceTest_103, PlusZeroReturnsSamePosition_103) {
  const char* str = "Test";
  StringCharSource source(str, 4);
  StringCharSource same = source + 0;
  EXPECT_EQ('T', same[0]);
}

// Test: Special characters in string
TEST_F(StringCharSourceTest_103, SpecialCharacters_103) {
  const char* str = "\n\t\r\0abc";
  StringCharSource source(str, 7);
  EXPECT_EQ('\n', source[0]);
  EXPECT_EQ('\t', source[1]);
  EXPECT_EQ('\r', source[2]);
  EXPECT_EQ('\0', source[3]);
}

// Test: Null characters in string are handled correctly
TEST_F(StringCharSourceTest_103, NullCharInMiddle_103) {
  const char str[] = {'A', '\0', 'B', 'C'};
  StringCharSource source(str, 4);
  EXPECT_EQ('A', source[0]);
  EXPECT_EQ('\0', source[1]);
  EXPECT_EQ('B', source[2]);
  EXPECT_EQ('C', source[3]);
}

}  // namespace YAML
