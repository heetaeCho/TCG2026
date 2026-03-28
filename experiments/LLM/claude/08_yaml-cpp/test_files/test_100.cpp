#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include "stream.h"
#include "streamcharsource.h"

namespace YAML {
namespace {

class StreamCharSourceTest_100 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that StreamCharSource converts to true when the stream has data available
TEST_F(StreamCharSourceTest_100, BoolOperatorReturnsTrueWhenDataAvailable_100) {
  std::stringstream ss("Hello, World!");
  Stream stream(ss);
  StreamCharSource source(stream);
  
  EXPECT_TRUE(static_cast<bool>(source));
}

// Test that StreamCharSource converts to false when the stream is empty
TEST_F(StreamCharSourceTest_100, BoolOperatorReturnsFalseWhenStreamEmpty_100) {
  std::stringstream ss("");
  Stream stream(ss);
  StreamCharSource source(stream);
  
  // With empty stream, reading ahead to offset 0 should fail
  // The behavior depends on implementation, but an empty stream likely returns false
  // Actually, ReadAheadTo(0) on an empty stream - there's nothing to read
  EXPECT_FALSE(static_cast<bool>(source));
}

// Test the negation operator
TEST_F(StreamCharSourceTest_100, NegationOperatorWhenDataAvailable_100) {
  std::stringstream ss("Test data");
  Stream stream(ss);
  StreamCharSource source(stream);
  
  EXPECT_FALSE(!source);
}

// Test the negation operator on empty stream
TEST_F(StreamCharSourceTest_100, NegationOperatorWhenStreamEmpty_100) {
  std::stringstream ss("");
  Stream stream(ss);
  StreamCharSource source(stream);
  
  EXPECT_TRUE(!source);
}

// Test operator[] to access characters at offset
TEST_F(StreamCharSourceTest_100, SubscriptOperatorReadsCharacter_100) {
  std::stringstream ss("ABCDEF");
  Stream stream(ss);
  StreamCharSource source(stream);
  
  EXPECT_EQ('A', source[0]);
  EXPECT_EQ('B', source[1]);
  EXPECT_EQ('C', source[2]);
}

// Test operator+ creates a new source with increased offset
TEST_F(StreamCharSourceTest_100, PlusOperatorCreatesOffsetSource_100) {
  std::stringstream ss("ABCDEF");
  Stream stream(ss);
  StreamCharSource source(stream);
  
  StreamCharSource offsetSource = source + 2;
  // The offset source should still be valid
  EXPECT_TRUE(static_cast<bool>(offsetSource));
  // And accessing [0] on the offset source should give character at original offset + 2
  EXPECT_EQ('C', offsetSource[0]);
}

// Test operator+ with offset 0
TEST_F(StreamCharSourceTest_100, PlusOperatorWithZeroOffset_100) {
  std::stringstream ss("ABCDEF");
  Stream stream(ss);
  StreamCharSource source(stream);
  
  StreamCharSource sameSource = source + 0;
  EXPECT_TRUE(static_cast<bool>(sameSource));
  EXPECT_EQ('A', sameSource[0]);
}

// Test chaining operator+
TEST_F(StreamCharSourceTest_100, PlusOperatorChaining_100) {
  std::stringstream ss("ABCDEFGH");
  Stream stream(ss);
  StreamCharSource source(stream);
  
  StreamCharSource offset1 = source + 1;
  StreamCharSource offset3 = offset1 + 2;
  
  EXPECT_EQ('D', offset3[0]);
}

// Test copy constructor
TEST_F(StreamCharSourceTest_100, CopyConstructorWorks_100) {
  std::stringstream ss("Hello");
  Stream stream(ss);
  StreamCharSource source(stream);
  
  StreamCharSource copy(source);
  EXPECT_TRUE(static_cast<bool>(copy));
  EXPECT_EQ('H', copy[0]);
}

// Test that operator+ beyond stream length returns false for bool
TEST_F(StreamCharSourceTest_100, PlusOperatorBeyondStreamLength_100) {
  std::stringstream ss("AB");
  Stream stream(ss);
  StreamCharSource source(stream);
  
  StreamCharSource farAhead = source + 10;
  EXPECT_FALSE(static_cast<bool>(farAhead));
}

// Test with single character stream
TEST_F(StreamCharSourceTest_100, SingleCharacterStream_100) {
  std::stringstream ss("X");
  Stream stream(ss);
  StreamCharSource source(stream);
  
  EXPECT_TRUE(static_cast<bool>(source));
  EXPECT_EQ('X', source[0]);
  
  StreamCharSource next = source + 1;
  EXPECT_FALSE(static_cast<bool>(next));
}

// Test operator[] with various indices
TEST_F(StreamCharSourceTest_100, SubscriptOperatorVariousIndices_100) {
  std::stringstream ss("0123456789");
  Stream stream(ss);
  StreamCharSource source(stream);
  
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ('0' + i, source[static_cast<std::size_t>(i)]);
  }
}

// Test with whitespace content
TEST_F(StreamCharSourceTest_100, StreamWithWhitespace_100) {
  std::stringstream ss("  \t\n");
  Stream stream(ss);
  StreamCharSource source(stream);
  
  EXPECT_TRUE(static_cast<bool>(source));
  EXPECT_EQ(' ', source[0]);
  EXPECT_EQ(' ', source[1]);
  EXPECT_EQ('\t', source[2]);
}

// Test move constructor
TEST_F(StreamCharSourceTest_100, MoveConstructorWorks_100) {
  std::stringstream ss("MovableData");
  Stream stream(ss);
  StreamCharSource source(stream);
  
  StreamCharSource moved(std::move(source));
  EXPECT_TRUE(static_cast<bool>(moved));
  EXPECT_EQ('M', moved[0]);
}

// Test with larger data
TEST_F(StreamCharSourceTest_100, LargerStream_100) {
  std::string largeContent(4096, 'Z');
  std::stringstream ss(largeContent);
  Stream stream(ss);
  StreamCharSource source(stream);
  
  EXPECT_TRUE(static_cast<bool>(source));
  EXPECT_EQ('Z', source[0]);
  EXPECT_EQ('Z', source[100]);
}

// Test operator+ with offset on already offset source checks bool
TEST_F(StreamCharSourceTest_100, OffsetSourceBoolAtBoundary_100) {
  std::stringstream ss("ABC");
  Stream stream(ss);
  StreamCharSource source(stream);
  
  StreamCharSource atLast = source + 2;
  EXPECT_TRUE(static_cast<bool>(atLast));
  EXPECT_EQ('C', atLast[0]);
  
  StreamCharSource pastEnd = source + 3;
  EXPECT_FALSE(static_cast<bool>(pastEnd));
}

}  // namespace
}  // namespace YAML
