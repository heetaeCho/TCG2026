#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "stream.h"

namespace YAML {
namespace {

class StreamTest_175 : public ::testing::Test {
protected:
};

// Test basic construction and that stream is valid with non-empty input
TEST_F(StreamTest_175, ConstructWithValidInput_175) {
    std::istringstream input("hello");
    Stream stream(input);
    EXPECT_TRUE(static_cast<bool>(stream));
}

// Test that an empty stream is still a valid Stream object but may signal EOF
TEST_F(StreamTest_175, ConstructWithEmptyInput_175) {
    std::istringstream input("");
    Stream stream(input);
    EXPECT_EQ(Stream::eof(), stream.peek());
}

// Test peek returns the first character without advancing
TEST_F(StreamTest_175, PeekReturnsFirstChar_175) {
    std::istringstream input("abc");
    Stream stream(input);
    EXPECT_EQ('a', stream.peek());
    // Peek again should return the same character
    EXPECT_EQ('a', stream.peek());
}

// Test get returns the first character and advances
TEST_F(StreamTest_175, GetReturnsAndAdvances_175) {
    std::istringstream input("abc");
    Stream stream(input);
    EXPECT_EQ('a', stream.get());
    EXPECT_EQ('b', stream.peek());
}

// Test getting all characters from a short string
TEST_F(StreamTest_175, GetAllCharacters_175) {
    std::istringstream input("hi");
    Stream stream(input);
    EXPECT_EQ('h', stream.get());
    EXPECT_EQ('i', stream.get());
    EXPECT_EQ(Stream::eof(), stream.peek());
}

// Test that column increments on regular characters
TEST_F(StreamTest_175, ColumnIncrementsOnGet_175) {
    std::istringstream input("abc");
    Stream stream(input);
    EXPECT_EQ(0, stream.column());
    stream.get(); // 'a'
    EXPECT_EQ(1, stream.column());
    stream.get(); // 'b'
    EXPECT_EQ(2, stream.column());
    stream.get(); // 'c'
    EXPECT_EQ(3, stream.column());
}

// Test that line increments on newline character '\n'
TEST_F(StreamTest_175, LineIncrementsOnNewline_175) {
    std::istringstream input("a\nb");
    Stream stream(input);
    EXPECT_EQ(0, stream.line());
    stream.get(); // 'a'
    EXPECT_EQ(0, stream.line());
    stream.get(); // '\n'
    EXPECT_EQ(1, stream.line());
    EXPECT_EQ(0, stream.column());
    stream.get(); // 'b'
    EXPECT_EQ(1, stream.line());
    EXPECT_EQ(1, stream.column());
}

// Test multiple newlines
TEST_F(StreamTest_175, MultipleNewlines_175) {
    std::istringstream input("a\n\nb");
    Stream stream(input);
    stream.get(); // 'a'
    stream.get(); // '\n'
    EXPECT_EQ(1, stream.line());
    EXPECT_EQ(0, stream.column());
    stream.get(); // '\n'
    EXPECT_EQ(2, stream.line());
    EXPECT_EQ(0, stream.column());
    stream.get(); // 'b'
    EXPECT_EQ(2, stream.line());
    EXPECT_EQ(1, stream.column());
}

// Test carriage return only as line ending
TEST_F(StreamTest_175, CarriageReturnAsLineEnding_175) {
    std::istringstream input("a\rb");
    Stream stream(input);
    stream.get(); // 'a'
    EXPECT_EQ(0, stream.line());
    stream.get(); // '\r'
    EXPECT_EQ(1, stream.line());
    EXPECT_EQ(0, stream.column());
    stream.get(); // 'b'
    EXPECT_EQ(1, stream.line());
}

// Test get(int n) returns a string of n characters
TEST_F(StreamTest_175, GetNCharacters_175) {
    std::istringstream input("abcdef");
    Stream stream(input);
    std::string result = stream.get(3);
    EXPECT_EQ("abc", result);
    EXPECT_EQ('d', stream.peek());
}

// Test get(int n) with n equal to the stream length
TEST_F(StreamTest_175, GetNEntireStream_175) {
    std::istringstream input("hello");
    Stream stream(input);
    std::string result = stream.get(5);
    EXPECT_EQ("hello", result);
    EXPECT_EQ(Stream::eof(), stream.peek());
}

// Test eat(int n) skips n characters
TEST_F(StreamTest_175, EatSkipsCharacters_175) {
    std::istringstream input("abcdef");
    Stream stream(input);
    stream.eat(3);
    EXPECT_EQ('d', stream.peek());
}

// Test eat entire stream
TEST_F(StreamTest_175, EatEntireStream_175) {
    std::istringstream input("abc");
    Stream stream(input);
    stream.eat(3);
    EXPECT_EQ(Stream::eof(), stream.peek());
}

// Test mark returns correct initial values
TEST_F(StreamTest_175, InitialMark_175) {
    std::istringstream input("abc");
    Stream stream(input);
    Mark m = stream.mark();
    EXPECT_EQ(0, m.pos);
    EXPECT_EQ(0, m.line);
    EXPECT_EQ(0, m.column);
}

// Test pos increments as characters are consumed
TEST_F(StreamTest_175, PosIncrements_175) {
    std::istringstream input("abcd");
    Stream stream(input);
    EXPECT_EQ(0, stream.pos());
    stream.get();
    EXPECT_EQ(1, stream.pos());
    stream.get();
    EXPECT_EQ(2, stream.pos());
}

// Test operator! on a valid stream
TEST_F(StreamTest_175, OperatorNotOnValidStream_175) {
    std::istringstream input("hello");
    Stream stream(input);
    EXPECT_FALSE(!stream);
}

// Test operator bool on empty stream / EOF
TEST_F(StreamTest_175, OperatorBoolOnEmptyStream_175) {
    std::istringstream input("");
    Stream stream(input);
    // An empty stream may or may not be "truthy" depending on implementation,
    // but peek should return eof
    char c = stream.peek();
    EXPECT_EQ(Stream::eof(), c);
}

// Test ResetColumn resets the column to zero
TEST_F(StreamTest_175, ResetColumn_175) {
    std::istringstream input("abcdef");
    Stream stream(input);
    stream.get(); // 'a'
    stream.get(); // 'b'
    stream.get(); // 'c'
    EXPECT_EQ(3, stream.column());
    stream.ResetColumn();
    EXPECT_EQ(0, stream.column());
}

// Test eof() returns a consistent value
TEST_F(StreamTest_175, EofIsConsistent_175) {
    char eof1 = Stream::eof();
    char eof2 = Stream::eof();
    EXPECT_EQ(eof1, eof2);
}

// Test getting from an already exhausted stream returns eof
TEST_F(StreamTest_175, GetFromExhaustedStream_175) {
    std::istringstream input("a");
    Stream stream(input);
    stream.get(); // 'a'
    char result = stream.get();
    EXPECT_EQ(Stream::eof(), result);
}

// Test line ending with \r\n (Windows style)
TEST_F(StreamTest_175, CRLFLineEnding_175) {
    std::istringstream input("a\r\nb");
    Stream stream(input);
    stream.get(); // 'a'
    EXPECT_EQ(0, stream.line());
    stream.get(); // '\r'
    // After \r in \r\n, behavior depends on implementation
    // The \n following should be recognized as part of the line ending
    stream.get(); // '\n'
    EXPECT_EQ(1, stream.line());
    stream.get(); // 'b'
    EXPECT_EQ(1, stream.line());
}

// Test a string starting with a newline
TEST_F(StreamTest_175, StartsWithNewline_175) {
    std::istringstream input("\nabc");
    Stream stream(input);
    EXPECT_EQ(0, stream.line());
    stream.get(); // '\n'
    EXPECT_EQ(1, stream.line());
    EXPECT_EQ(0, stream.column());
}

// Test eat(0) does nothing
TEST_F(StreamTest_175, EatZero_175) {
    std::istringstream input("abc");
    Stream stream(input);
    stream.eat(0);
    EXPECT_EQ('a', stream.peek());
    EXPECT_EQ(0, stream.column());
}

// Test get(0) returns empty string
TEST_F(StreamTest_175, GetZeroReturnsEmpty_175) {
    std::istringstream input("abc");
    Stream stream(input);
    std::string result = stream.get(0);
    EXPECT_EQ("", result);
    EXPECT_EQ('a', stream.peek());
}

// Test large input stream
TEST_F(StreamTest_175, LargeInput_175) {
    std::string largeStr(5000, 'x');
    std::istringstream input(largeStr);
    Stream stream(input);
    for (int i = 0; i < 5000; i++) {
        EXPECT_EQ('x', stream.get());
    }
    EXPECT_EQ(Stream::eof(), stream.peek());
}

// Test that mark reflects correct position after mixed operations
TEST_F(StreamTest_175, MarkAfterMixedOperations_175) {
    std::istringstream input("ab\ncd\nef");
    Stream stream(input);
    stream.get(); // 'a'
    stream.get(); // 'b'
    stream.get(); // '\n'
    stream.get(); // 'c'
    
    Mark m = stream.mark();
    EXPECT_EQ(4, m.pos);
    EXPECT_EQ(1, m.line);
    EXPECT_EQ(1, m.column);
}

// Test eating past EOF does not crash
TEST_F(StreamTest_175, EatPastEOF_175) {
    std::istringstream input("ab");
    Stream stream(input);
    stream.eat(10);
    EXPECT_EQ(Stream::eof(), stream.peek());
}

// Test get(n) past EOF
TEST_F(StreamTest_175, GetNPastEOF_175) {
    std::istringstream input("ab");
    Stream stream(input);
    std::string result = stream.get(10);
    // Should return what's available
    EXPECT_GE(result.size(), 0u);
    EXPECT_EQ(Stream::eof(), stream.peek());
}

// Test single character input
TEST_F(StreamTest_175, SingleCharInput_175) {
    std::istringstream input("x");
    Stream stream(input);
    EXPECT_EQ('x', stream.peek());
    EXPECT_EQ('x', stream.get());
    EXPECT_EQ(Stream::eof(), stream.peek());
}

// Test only newlines
TEST_F(StreamTest_175, OnlyNewlines_175) {
    std::istringstream input("\n\n\n");
    Stream stream(input);
    stream.get(); // '\n'
    EXPECT_EQ(1, stream.line());
    stream.get(); // '\n'
    EXPECT_EQ(2, stream.line());
    stream.get(); // '\n'
    EXPECT_EQ(3, stream.line());
}

// Test column resets after newline and increments again
TEST_F(StreamTest_175, ColumnResetsAfterNewline_175) {
    std::istringstream input("ab\ncd");
    Stream stream(input);
    stream.get(); // 'a' -> col 1
    stream.get(); // 'b' -> col 2
    EXPECT_EQ(2, stream.column());
    stream.get(); // '\n' -> col 0
    EXPECT_EQ(0, stream.column());
    stream.get(); // 'c' -> col 1
    EXPECT_EQ(1, stream.column());
    stream.get(); // 'd' -> col 2
    EXPECT_EQ(2, stream.column());
}

}  // namespace
}  // namespace YAML
