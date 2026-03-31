#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "stream.h"
#include "streamcharsource.h"

namespace YAML {
namespace {

class StreamCharSourceTest_98 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that operator[] returns the correct character at index 0
TEST_F(StreamCharSourceTest_98, OperatorBracketReturnsFirstChar_98) {
  std::istringstream input("Hello, World!");
  Stream stream(input);
  StreamCharSource source(stream);

  EXPECT_EQ('H', source[0]);
}

// Test that operator[] returns correct characters at various indices
TEST_F(StreamCharSourceTest_98, OperatorBracketReturnsCorrectChars_98) {
  std::istringstream input("abcdefghij");
  Stream stream(input);
  StreamCharSource source(stream);

  EXPECT_EQ('a', source[0]);
  EXPECT_EQ('b', source[1]);
  EXPECT_EQ('c', source[2]);
  EXPECT_EQ('d', source[3]);
  EXPECT_EQ('e', source[4]);
}

// Test operator bool on a valid stream
TEST_F(StreamCharSourceTest_98, OperatorBoolTrueForValidStream_98) {
  std::istringstream input("test");
  Stream stream(input);
  StreamCharSource source(stream);

  EXPECT_TRUE(static_cast<bool>(source));
}

// Test operator bool on an empty stream
TEST_F(StreamCharSourceTest_98, OperatorBoolOnEmptyStream_98) {
  std::istringstream input("");
  Stream stream(input);
  StreamCharSource source(stream);

  // An empty stream may or may not be "true" depending on implementation,
  // but we can at least call it without crashing
  bool result = static_cast<bool>(source);
  (void)result; // Just verify it doesn't crash
}

// Test operator! on a valid stream
TEST_F(StreamCharSourceTest_98, OperatorNotOnValidStream_98) {
  std::istringstream input("test");
  Stream stream(input);
  StreamCharSource source(stream);

  // operator! should be the inverse of operator bool
  EXPECT_EQ(!static_cast<bool>(source), !source);
}

// Test operator+ creates a new source with offset
TEST_F(StreamCharSourceTest_98, OperatorPlusCreatesOffsetSource_98) {
  std::istringstream input("abcdefghij");
  Stream stream(input);
  StreamCharSource source(stream);

  const StreamCharSource offsetSource = source + 3;
  // After offsetting by 3, index 0 should be 'd'
  EXPECT_EQ('d', offsetSource[0]);
  EXPECT_EQ('e', offsetSource[1]);
  EXPECT_EQ('f', offsetSource[2]);
}

// Test that operator+ with 0 offset returns equivalent source
TEST_F(StreamCharSourceTest_98, OperatorPlusZeroOffset_98) {
  std::istringstream input("abcdef");
  Stream stream(input);
  StreamCharSource source(stream);

  const StreamCharSource sameSource = source + 0;
  EXPECT_EQ(source[0], sameSource[0]);
  EXPECT_EQ(source[1], sameSource[1]);
  EXPECT_EQ(source[2], sameSource[2]);
}

// Test chaining operator+ calls
TEST_F(StreamCharSourceTest_98, OperatorPlusChained_98) {
  std::istringstream input("abcdefghij");
  Stream stream(input);
  StreamCharSource source(stream);

  const StreamCharSource offset1 = source + 2;
  const StreamCharSource offset2 = offset1 + 3;
  // offset2 should be at position 5 -> 'f'
  EXPECT_EQ('f', offset2[0]);
}

// Test copy constructor
TEST_F(StreamCharSourceTest_98, CopyConstructor_98) {
  std::istringstream input("abcdef");
  Stream stream(input);
  StreamCharSource source(stream);

  StreamCharSource copy(source);
  EXPECT_EQ(source[0], copy[0]);
  EXPECT_EQ(source[1], copy[1]);
}

// Test with single character input
TEST_F(StreamCharSourceTest_98, SingleCharacterInput_98) {
  std::istringstream input("X");
  Stream stream(input);
  StreamCharSource source(stream);

  EXPECT_EQ('X', source[0]);
}

// Test with whitespace characters
TEST_F(StreamCharSourceTest_98, WhitespaceCharacters_98) {
  std::istringstream input(" \t\n");
  Stream stream(input);
  StreamCharSource source(stream);

  EXPECT_EQ(' ', source[0]);
  EXPECT_EQ('\t', source[1]);
}

// Test with special characters
TEST_F(StreamCharSourceTest_98, SpecialCharacters_98) {
  std::istringstream input("!@#$%^&*()");
  Stream stream(input);
  StreamCharSource source(stream);

  EXPECT_EQ('!', source[0]);
  EXPECT_EQ('@', source[1]);
  EXPECT_EQ('#', source[2]);
  EXPECT_EQ('$', source[3]);
}

// Test operator+ with offset of 1
TEST_F(StreamCharSourceTest_98, OperatorPlusOffsetOne_98) {
  std::istringstream input("abcdef");
  Stream stream(input);
  StreamCharSource source(stream);

  const StreamCharSource offset = source + 1;
  EXPECT_EQ('b', offset[0]);
  EXPECT_EQ('c', offset[1]);
}

// Test that original source is not modified by operator+
TEST_F(StreamCharSourceTest_98, OperatorPlusDoesNotModifyOriginal_98) {
  std::istringstream input("abcdef");
  Stream stream(input);
  StreamCharSource source(stream);

  const StreamCharSource offset = source + 3;
  // Original should still start at 'a'
  EXPECT_EQ('a', source[0]);
  // Offset should start at 'd'
  EXPECT_EQ('d', offset[0]);
}

// Test with a longer string
TEST_F(StreamCharSourceTest_98, LongerString_98) {
  std::string longStr(100, 'z');
  longStr[0] = 'a';
  longStr[50] = 'b';
  longStr[99] = 'c';
  std::istringstream input(longStr);
  Stream stream(input);
  StreamCharSource source(stream);

  EXPECT_EQ('a', source[0]);
  EXPECT_EQ('b', source[50]);
  EXPECT_EQ('c', source[99]);
}

}  // namespace
}  // namespace YAML
