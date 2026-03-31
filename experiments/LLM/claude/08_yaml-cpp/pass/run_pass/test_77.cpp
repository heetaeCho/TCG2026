#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "stream.h"

namespace YAML {
namespace {

// ==================== Construction and Basic State Tests ====================

TEST(StreamTest_77, ConstructFromEmptyStream_77) {
    std::istringstream input("");
    Stream stream(input);
    EXPECT_FALSE(stream);
}

TEST(StreamTest_77, ConstructFromNonEmptyStream_77) {
    std::istringstream input("hello");
    Stream stream(input);
    EXPECT_TRUE(stream);
}

TEST(StreamTest_77, BoolOperatorOnEmptyStream_77) {
    std::istringstream input("");
    Stream stream(input);
    EXPECT_TRUE(!stream);
}

TEST(StreamTest_77, BoolOperatorOnNonEmptyStream_77) {
    std::istringstream input("abc");
    Stream stream(input);
    EXPECT_FALSE(!stream);
}

// ==================== Peek Tests ====================

TEST(StreamTest_77, PeekReturnsFirstChar_77) {
    std::istringstream input("xyz");
    Stream stream(input);
    EXPECT_EQ('x', stream.peek());
}

TEST(StreamTest_77, PeekDoesNotAdvance_77) {
    std::istringstream input("abc");
    Stream stream(input);
    EXPECT_EQ('a', stream.peek());
    EXPECT_EQ('a', stream.peek());
}

TEST(StreamTest_77, PeekOnEmptyStreamReturnsEof_77) {
    std::istringstream input("");
    Stream stream(input);
    EXPECT_EQ(Stream::eof(), stream.peek());
}

// ==================== Get (single char) Tests ====================

TEST(StreamTest_77, GetReturnsSingleChar_77) {
    std::istringstream input("abc");
    Stream stream(input);
    char c = stream.get();
    EXPECT_EQ('a', c);
}

TEST(StreamTest_77, GetAdvancesPosition_77) {
    std::istringstream input("abc");
    Stream stream(input);
    stream.get();
    EXPECT_EQ('b', stream.peek());
}

TEST(StreamTest_77, GetSequentialChars_77) {
    std::istringstream input("hello");
    Stream stream(input);
    EXPECT_EQ('h', stream.get());
    EXPECT_EQ('e', stream.get());
    EXPECT_EQ('l', stream.get());
    EXPECT_EQ('l', stream.get());
    EXPECT_EQ('o', stream.get());
}

TEST(StreamTest_77, GetOnEmptyStreamReturnsEof_77) {
    std::istringstream input("");
    Stream stream(input);
    EXPECT_EQ(Stream::eof(), stream.get());
}

TEST(StreamTest_77, GetPastEndReturnsEof_77) {
    std::istringstream input("a");
    Stream stream(input);
    stream.get();
    EXPECT_EQ(Stream::eof(), stream.get());
}

// ==================== Get (n chars) Tests ====================

TEST(StreamTest_77, GetNReturnsString_77) {
    std::istringstream input("hello world");
    Stream stream(input);
    std::string result = stream.get(5);
    EXPECT_EQ("hello", result);
}

TEST(StreamTest_77, GetNAdvancesPosition_77) {
    std::istringstream input("abcdef");
    Stream stream(input);
    stream.get(3);
    EXPECT_EQ('d', stream.peek());
}

TEST(StreamTest_77, GetNZeroReturnsEmpty_77) {
    std::istringstream input("abc");
    Stream stream(input);
    std::string result = stream.get(0);
    EXPECT_EQ("", result);
    EXPECT_EQ('a', stream.peek());
}

TEST(StreamTest_77, GetNExceedingLength_77) {
    std::istringstream input("ab");
    Stream stream(input);
    std::string result = stream.get(10);
    // Should return what's available
    EXPECT_EQ(2u, result.size());
    EXPECT_EQ("ab", result);
}

// ==================== Eat Tests ====================

TEST(StreamTest_77, EatAdvancesPosition_77) {
    std::istringstream input("abcdef");
    Stream stream(input);
    stream.eat(3);
    EXPECT_EQ('d', stream.peek());
}

TEST(StreamTest_77, EatZeroDoesNotAdvance_77) {
    std::istringstream input("abc");
    Stream stream(input);
    stream.eat(0);
    EXPECT_EQ('a', stream.peek());
}

TEST(StreamTest_77, EatEntireStream_77) {
    std::istringstream input("abc");
    Stream stream(input);
    stream.eat(3);
    EXPECT_EQ(Stream::eof(), stream.peek());
    EXPECT_FALSE(stream);
}

// ==================== Mark / Position Tests ====================

TEST(StreamTest_77, InitialMarkIsZero_77) {
    std::istringstream input("abc");
    Stream stream(input);
    Mark m = stream.mark();
    EXPECT_EQ(0, m.pos);
    EXPECT_EQ(0, m.line);
    EXPECT_EQ(0, m.column);
}

TEST(StreamTest_77, PosIncrementsOnGet_77) {
    std::istringstream input("abcde");
    Stream stream(input);
    stream.get();
    stream.get();
    EXPECT_EQ(2, stream.pos());
}

TEST(StreamTest_77, ColumnIncrementsOnGet_77) {
    std::istringstream input("abcde");
    Stream stream(input);
    EXPECT_EQ(0, stream.column());
    stream.get();
    EXPECT_EQ(1, stream.column());
    stream.get();
    EXPECT_EQ(2, stream.column());
}

TEST(StreamTest_77, LineIncrementsOnNewline_77) {
    std::istringstream input("ab\ncd");
    Stream stream(input);
    EXPECT_EQ(0, stream.line());
    stream.get(); // 'a'
    stream.get(); // 'b'
    stream.get(); // '\n'
    EXPECT_EQ(1, stream.line());
    EXPECT_EQ(0, stream.column());
}

TEST(StreamTest_77, ColumnResetsOnNewline_77) {
    std::istringstream input("ab\ncd");
    Stream stream(input);
    stream.get(); // 'a'
    stream.get(); // 'b'
    EXPECT_EQ(2, stream.column());
    stream.get(); // '\n'
    EXPECT_EQ(0, stream.column());
    stream.get(); // 'c'
    EXPECT_EQ(1, stream.column());
}

TEST(StreamTest_77, ResetColumnResetsToZero_77) {
    std::istringstream input("abcde");
    Stream stream(input);
    stream.get();
    stream.get();
    EXPECT_EQ(2, stream.column());
    stream.ResetColumn();
    EXPECT_EQ(0, stream.column());
}

TEST(StreamTest_77, MarkReturnsCorrectValues_77) {
    std::istringstream input("ab\ncd");
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

// ==================== EOF static method ====================

TEST(StreamTest_77, EofIsConsistent_77) {
    char eof1 = Stream::eof();
    char eof2 = Stream::eof();
    EXPECT_EQ(eof1, eof2);
}

// ==================== Copy/Move Deleted ====================

TEST(StreamTest_77, StreamIsNotCopyable_77) {
    EXPECT_FALSE(std::is_copy_constructible<Stream>::value);
    EXPECT_FALSE(std::is_copy_assignable<Stream>::value);
}

TEST(StreamTest_77, StreamIsNotMovable_77) {
    EXPECT_FALSE(std::is_move_constructible<Stream>::value);
    EXPECT_FALSE(std::is_move_assignable<Stream>::value);
}

// ==================== Multiple Newlines ====================

TEST(StreamTest_77, MultipleNewlines_77) {
    std::istringstream input("a\n\nb");
    Stream stream(input);
    stream.get(); // 'a'
    stream.get(); // '\n'
    EXPECT_EQ(1, stream.line());
    stream.get(); // '\n'
    EXPECT_EQ(2, stream.line());
    EXPECT_EQ(0, stream.column());
    stream.get(); // 'b'
    EXPECT_EQ(2, stream.line());
    EXPECT_EQ(1, stream.column());
}

// ==================== Tab Character ====================

TEST(StreamTest_77, TabCharacterAdvancesColumn_77) {
    std::istringstream input("\t");
    Stream stream(input);
    char c = stream.get();
    EXPECT_EQ('\t', c);
    // Column should have advanced in some way
    EXPECT_GT(stream.column(), 0);
}

// ==================== Large Input ====================

TEST(StreamTest_77, LargeInputStreaming_77) {
    std::string largeInput(4096, 'x');
    std::istringstream input(largeInput);
    Stream stream(input);
    
    for (int i = 0; i < 4096; ++i) {
        EXPECT_TRUE(static_cast<bool>(stream));
        char c = stream.get();
        EXPECT_EQ('x', c);
    }
    EXPECT_FALSE(stream);
}

// ==================== GetN and Eat Combined ====================

TEST(StreamTest_77, GetNAndEatCombined_77) {
    std::istringstream input("abcdefghij");
    Stream stream(input);
    stream.eat(3);      // skip "abc"
    std::string s = stream.get(4); // get "defg"
    EXPECT_EQ("defg", s);
    EXPECT_EQ('h', stream.peek());
}

// ==================== Single Character Stream ====================

TEST(StreamTest_77, SingleCharacterStream_77) {
    std::istringstream input("Z");
    Stream stream(input);
    EXPECT_TRUE(stream);
    EXPECT_EQ('Z', stream.peek());
    EXPECT_EQ('Z', stream.get());
    EXPECT_FALSE(stream);
    EXPECT_EQ(Stream::eof(), stream.peek());
}

// ==================== Carriage Return Handling ====================

TEST(StreamTest_77, CarriageReturnNewline_77) {
    std::istringstream input("a\r\nb");
    Stream stream(input);
    stream.get(); // 'a'
    stream.get(); // '\r' or normalized
    // After CR+LF, we should be on the next line eventually
    stream.get(); // '\n' or next char
    // Line should have advanced
    EXPECT_GE(stream.line(), 1);
}

// ==================== Initial Position ====================

TEST(StreamTest_77, InitialPosition_77) {
    std::istringstream input("test");
    Stream stream(input);
    EXPECT_EQ(0, stream.pos());
    EXPECT_EQ(0, stream.line());
    EXPECT_EQ(0, stream.column());
}

// ==================== Eat past end ====================

TEST(StreamTest_77, EatPastEnd_77) {
    std::istringstream input("ab");
    Stream stream(input);
    stream.eat(10);
    EXPECT_FALSE(stream);
    EXPECT_EQ(Stream::eof(), stream.peek());
}

}  // namespace
}  // namespace YAML
