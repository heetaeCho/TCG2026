#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "stream.h"

namespace YAML {
namespace {

// Test basic construction and bool operator with valid input
TEST(StreamTest_72, ConstructWithValidInput_72) {
    std::istringstream input("hello");
    Stream stream(input);
    EXPECT_TRUE(static_cast<bool>(stream));
    EXPECT_FALSE(!stream);
}

// Test construction with empty input
TEST(StreamTest_72, ConstructWithEmptyInput_72) {
    std::istringstream input("");
    Stream stream(input);
    // Empty stream - behavior depends on implementation
    // but we can at least construct it
}

// Test peek returns first character
TEST(StreamTest_72, PeekReturnsFirstCharacter_72) {
    std::istringstream input("abc");
    Stream stream(input);
    EXPECT_EQ('a', stream.peek());
    // Peek should not advance
    EXPECT_EQ('a', stream.peek());
}

// Test get returns and advances
TEST(StreamTest_72, GetReturnsAndAdvances_72) {
    std::istringstream input("abc");
    Stream stream(input);
    EXPECT_EQ('a', stream.get());
    EXPECT_EQ('b', stream.get());
    EXPECT_EQ('c', stream.get());
}

// Test get(n) returns string of n characters
TEST(StreamTest_72, GetNReturnsStringOfNCharacters_72) {
    std::istringstream input("hello world");
    Stream stream(input);
    std::string result = stream.get(5);
    EXPECT_EQ("hello", result);
}

// Test eat skips characters
TEST(StreamTest_72, EatSkipsCharacters_72) {
    std::istringstream input("abcdef");
    Stream stream(input);
    stream.eat(3);
    EXPECT_EQ('d', stream.peek());
}

// Test mark returns initial position
TEST(StreamTest_72, MarkReturnsInitialPosition_72) {
    std::istringstream input("hello");
    Stream stream(input);
    Mark m = stream.mark();
    EXPECT_EQ(0, m.pos);
    EXPECT_EQ(0, m.line);
    EXPECT_EQ(0, m.column);
}

// Test pos returns current position
TEST(StreamTest_72, PosReturnsCurrentPosition_72) {
    std::istringstream input("hello");
    Stream stream(input);
    EXPECT_EQ(0, stream.pos());
    stream.get();
    EXPECT_EQ(1, stream.pos());
}

// Test line tracking
TEST(StreamTest_72, LineTrackingOnNewline_72) {
    std::istringstream input("ab\ncd");
    Stream stream(input);
    EXPECT_EQ(0, stream.line());
    stream.get(); // 'a'
    stream.get(); // 'b'
    stream.get(); // '\n'
    EXPECT_EQ(1, stream.line());
}

// Test column tracking
TEST(StreamTest_72, ColumnTrackingOnNewline_72) {
    std::istringstream input("ab\ncd");
    Stream stream(input);
    EXPECT_EQ(0, stream.column());
    stream.get(); // 'a'
    EXPECT_EQ(1, stream.column());
    stream.get(); // 'b'
    EXPECT_EQ(2, stream.column());
    stream.get(); // '\n'
    EXPECT_EQ(0, stream.column());
    stream.get(); // 'c'
    EXPECT_EQ(1, stream.column());
}

// Test ResetColumn
TEST(StreamTest_72, ResetColumnResetsColumnToZero_72) {
    std::istringstream input("abcdef");
    Stream stream(input);
    stream.get();
    stream.get();
    EXPECT_EQ(2, stream.column());
    stream.ResetColumn();
    EXPECT_EQ(0, stream.column());
}

// Test eof static method
TEST(StreamTest_72, EofReturnsEofCharacter_72) {
    char eofChar = Stream::eof();
    // eof() should return some sentinel value
    // We just verify it's callable and returns consistently
    EXPECT_EQ(eofChar, Stream::eof());
}

// Test reading past end of stream
TEST(StreamTest_72, ReadPastEndOfStream_72) {
    std::istringstream input("ab");
    Stream stream(input);
    stream.get(); // 'a'
    stream.get(); // 'b'
    // After exhausting input, peek should return eof
    EXPECT_EQ(Stream::eof(), stream.peek());
}

// Test bool operator becomes false at end of stream
TEST(StreamTest_72, BoolOperatorFalseAtEnd_72) {
    std::istringstream input("a");
    Stream stream(input);
    EXPECT_TRUE(static_cast<bool>(stream));
    stream.get(); // 'a'
    // After consuming all input, stream should become false
    EXPECT_FALSE(static_cast<bool>(stream));
    EXPECT_TRUE(!stream);
}

// Test not operator on exhausted stream
TEST(StreamTest_72, NotOperatorOnExhaustedStream_72) {
    std::istringstream input("");
    Stream stream(input);
    // Empty stream should test as not valid
    // The behavior depends on implementation, but we test the operator
    bool notResult = !stream;
    bool boolResult = static_cast<bool>(stream);
    EXPECT_EQ(!boolResult, notResult);
}

// Test get(n) with n larger than remaining
TEST(StreamTest_72, GetNLargerThanRemaining_72) {
    std::istringstream input("hi");
    Stream stream(input);
    std::string result = stream.get(10);
    // Should get at most what's available
    EXPECT_LE(result.size(), 10u);
}

// Test eat(0) does nothing
TEST(StreamTest_72, EatZeroDoesNothing_72) {
    std::istringstream input("abc");
    Stream stream(input);
    stream.eat(0);
    EXPECT_EQ('a', stream.peek());
}

// Test get(0) returns empty string
TEST(StreamTest_72, GetZeroReturnsEmptyString_72) {
    std::istringstream input("abc");
    Stream stream(input);
    std::string result = stream.get(0);
    EXPECT_EQ("", result);
    EXPECT_EQ('a', stream.peek());
}

// Test single character input
TEST(StreamTest_72, SingleCharacterInput_72) {
    std::istringstream input("x");
    Stream stream(input);
    EXPECT_TRUE(static_cast<bool>(stream));
    EXPECT_EQ('x', stream.peek());
    EXPECT_EQ('x', stream.get());
    EXPECT_EQ(Stream::eof(), stream.peek());
}

// Test mark after advancing
TEST(StreamTest_72, MarkAfterAdvancing_72) {
    std::istringstream input("ab\ncd");
    Stream stream(input);
    stream.get(); // 'a'
    stream.get(); // 'b'
    stream.get(); // '\n'
    Mark m = stream.mark();
    EXPECT_EQ(3, m.pos);
    EXPECT_EQ(1, m.line);
    EXPECT_EQ(0, m.column);
}

// Test with UTF-8 BOM
TEST(StreamTest_72, Utf8BomHandling_72) {
    std::string bomContent = "\xEF\xBB\xBF" "hello";
    std::istringstream input(bomContent);
    Stream stream(input);
    // After BOM, first readable character should be 'h'
    // The stream should handle the BOM transparently
    EXPECT_TRUE(static_cast<bool>(stream));
}

// Test large input
TEST(StreamTest_72, LargeInput_72) {
    std::string largeContent(5000, 'a');
    std::istringstream input(largeContent);
    Stream stream(input);
    EXPECT_TRUE(static_cast<bool>(stream));
    EXPECT_EQ('a', stream.peek());
    stream.eat(4999);
    EXPECT_EQ('a', stream.get());
    EXPECT_EQ(Stream::eof(), stream.peek());
}

// Test multiple newlines
TEST(StreamTest_72, MultipleNewlines_72) {
    std::istringstream input("\n\n\n");
    Stream stream(input);
    stream.get(); // first \n
    EXPECT_EQ(1, stream.line());
    stream.get(); // second \n
    EXPECT_EQ(2, stream.line());
    stream.get(); // third \n
    EXPECT_EQ(3, stream.line());
}

// Test copy and move are deleted (compile-time check implicit)
// We verify the stream works without copy/move
TEST(StreamTest_72, StreamIsNotCopyableOrMovable_72) {
    EXPECT_FALSE(std::is_copy_constructible<Stream>::value);
    EXPECT_FALSE(std::is_move_constructible<Stream>::value);
    EXPECT_FALSE(std::is_copy_assignable<Stream>::value);
    EXPECT_FALSE(std::is_move_assignable<Stream>::value);
}

// Test interleaved peek and get
TEST(StreamTest_72, InterleavedPeekAndGet_72) {
    std::istringstream input("xyz");
    Stream stream(input);
    EXPECT_EQ('x', stream.peek());
    EXPECT_EQ('x', stream.get());
    EXPECT_EQ('y', stream.peek());
    EXPECT_EQ('y', stream.peek());
    EXPECT_EQ('y', stream.get());
    EXPECT_EQ('z', stream.peek());
    EXPECT_EQ('z', stream.get());
    EXPECT_EQ(Stream::eof(), stream.peek());
}

// Test eat followed by get(n)
TEST(StreamTest_72, EatThenGetN_72) {
    std::istringstream input("abcdefgh");
    Stream stream(input);
    stream.eat(3);
    std::string result = stream.get(3);
    EXPECT_EQ("def", result);
}

// Test \r\n line ending
TEST(StreamTest_72, CRLFLineEnding_72) {
    std::istringstream input("ab\r\ncd");
    Stream stream(input);
    stream.get(); // 'a'
    stream.get(); // 'b'
    stream.get(); // '\r' or consolidated newline
    // After the line ending, line should have incremented
    // The exact behavior depends on how CRLF is handled
    int lineAfter = stream.line();
    EXPECT_GE(lineAfter, 1);
}

}  // namespace
}  // namespace YAML
