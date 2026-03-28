#include <gtest/gtest.h>
#include "stringsource.h"

namespace YAML {
namespace {

class StringCharSourceTest_107 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test construction and basic boolean conversion with valid string
TEST_F(StringCharSourceTest_107, ConstructWithValidString_BoolIsTrue_107) {
  const char* str = "hello";
  StringCharSource source(str, 5);
  EXPECT_TRUE(static_cast<bool>(source));
  EXPECT_FALSE(!source);
}

// Test construction with empty string (size 0)
TEST_F(StringCharSourceTest_107, ConstructWithEmptyString_BoolIsFalse_107) {
  const char* str = "";
  StringCharSource source(str, 0);
  EXPECT_FALSE(static_cast<bool>(source));
  EXPECT_TRUE(!source);
}

// Test operator[] accesses correct characters
TEST_F(StringCharSourceTest_107, SubscriptOperator_ReturnsCorrectChars_107) {
  const char* str = "abcde";
  StringCharSource source(str, 5);
  EXPECT_EQ('a', source[0]);
  EXPECT_EQ('b', source[1]);
  EXPECT_EQ('c', source[2]);
  EXPECT_EQ('d', source[3]);
  EXPECT_EQ('e', source[4]);
}

// Test prefix increment operator advances position
TEST_F(StringCharSourceTest_107, PrefixIncrement_AdvancesPosition_107) {
  const char* str = "abc";
  StringCharSource source(str, 3);
  EXPECT_EQ('a', source[0]);
  ++source;
  EXPECT_EQ('b', source[0]);
  ++source;
  EXPECT_EQ('c', source[0]);
}

// Test operator+= advances position by offset
TEST_F(StringCharSourceTest_107, PlusEqualsOperator_AdvancesPositionByOffset_107) {
  const char* str = "abcdef";
  StringCharSource source(str, 6);
  EXPECT_EQ('a', source[0]);
  source += 3;
  EXPECT_EQ('d', source[0]);
}

// Test operator+= with offset of 0 does nothing
TEST_F(StringCharSourceTest_107, PlusEqualsZero_PositionUnchanged_107) {
  const char* str = "abc";
  StringCharSource source(str, 3);
  EXPECT_EQ('a', source[0]);
  source += 0;
  EXPECT_EQ('a', source[0]);
}

// Test operator+ returns a new source offset by i without modifying original
TEST_F(StringCharSourceTest_107, PlusOperator_ReturnsOffsetCopy_107) {
  const char* str = "abcde";
  StringCharSource source(str, 5);
  StringCharSource offset_source = source + 2;
  // Original should be unchanged
  EXPECT_EQ('a', source[0]);
  // New source should be offset
  EXPECT_EQ('c', offset_source[0]);
}

// Test that incrementing past the end makes bool conversion false
TEST_F(StringCharSourceTest_107, IncrementPastEnd_BoolBecomesFalse_107) {
  const char* str = "a";
  StringCharSource source(str, 1);
  EXPECT_TRUE(static_cast<bool>(source));
  ++source;
  EXPECT_FALSE(static_cast<bool>(source));
}

// Test operator+= past end makes bool conversion false
TEST_F(StringCharSourceTest_107, PlusEqualsPastEnd_BoolBecomesFalse_107) {
  const char* str = "ab";
  StringCharSource source(str, 2);
  EXPECT_TRUE(static_cast<bool>(source));
  source += 2;
  EXPECT_FALSE(static_cast<bool>(source));
}

// Test chaining operator+=
TEST_F(StringCharSourceTest_107, ChainingPlusEquals_107) {
  const char* str = "abcdefgh";
  StringCharSource source(str, 8);
  source += 2;
  source += 3;
  EXPECT_EQ('f', source[0]);
}

// Test chaining prefix increment
TEST_F(StringCharSourceTest_107, ChainingPrefixIncrement_107) {
  const char* str = "abcd";
  StringCharSource source(str, 4);
  ++(++source);
  EXPECT_EQ('c', source[0]);
}

// Test operator[] with non-zero index after advancement
TEST_F(StringCharSourceTest_107, SubscriptWithOffsetAfterAdvance_107) {
  const char* str = "abcdef";
  StringCharSource source(str, 6);
  source += 2;
  EXPECT_EQ('c', source[0]);
  EXPECT_EQ('d', source[1]);
  EXPECT_EQ('e', source[2]);
}

// Test operator+ with 0 offset returns equivalent source
TEST_F(StringCharSourceTest_107, PlusOperatorZero_ReturnsSamePosition_107) {
  const char* str = "abc";
  StringCharSource source(str, 3);
  StringCharSource same = source + 0;
  EXPECT_EQ('a', same[0]);
}

// Test single character string
TEST_F(StringCharSourceTest_107, SingleCharString_107) {
  const char* str = "x";
  StringCharSource source(str, 1);
  EXPECT_TRUE(static_cast<bool>(source));
  EXPECT_EQ('x', source[0]);
  ++source;
  EXPECT_FALSE(static_cast<bool>(source));
}

// Test operator+= returns reference to self
TEST_F(StringCharSourceTest_107, PlusEqualsReturnsSelf_107) {
  const char* str = "abcde";
  StringCharSource source(str, 5);
  StringCharSource& ref = (source += 1);
  EXPECT_EQ(&source, &ref);
  EXPECT_EQ('b', ref[0]);
}

// Test prefix increment returns reference to self
TEST_F(StringCharSourceTest_107, PrefixIncrementReturnsSelf_107) {
  const char* str = "abc";
  StringCharSource source(str, 3);
  StringCharSource& ref = ++source;
  EXPECT_EQ(&source, &ref);
  EXPECT_EQ('b', ref[0]);
}

// Test not operator on valid source
TEST_F(StringCharSourceTest_107, NotOperatorOnValid_ReturnsFalse_107) {
  const char* str = "test";
  StringCharSource source(str, 4);
  EXPECT_FALSE(!source);
}

// Test not operator on exhausted source
TEST_F(StringCharSourceTest_107, NotOperatorOnExhausted_ReturnsTrue_107) {
  const char* str = "t";
  StringCharSource source(str, 1);
  ++source;
  EXPECT_TRUE(!source);
}

// Test large offset via operator+=
TEST_F(StringCharSourceTest_107, LargeOffset_107) {
  const char str[] = "abcdefghijklmnopqrstuvwxyz";
  StringCharSource source(str, 26);
  source += 25;
  EXPECT_EQ('z', source[0]);
  EXPECT_TRUE(static_cast<bool>(source));
  ++source;
  EXPECT_FALSE(static_cast<bool>(source));
}

}  // namespace
}  // namespace YAML
