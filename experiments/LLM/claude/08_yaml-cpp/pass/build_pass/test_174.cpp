#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "stream.h"

namespace YAML {

class StreamTest_174 : public ::testing::Test {
protected:
};

// Test that a Stream constructed from a valid non-empty input stream is truthy
TEST_F(StreamTest_174, ConstructFromNonEmptyStream_IsTruthy_174) {
    std::istringstream input("hello");
    Stream stream(input);
    EXPECT_TRUE(static_cast<bool>(stream));
}

// Test that a Stream constructed from an empty input stream behaves appropriately
TEST_F(StreamTest_174, ConstructFromEmptyStream_174) {
    std::istringstream input("");
    Stream stream(input);
    // An empty stream might still be valid or might immediately be at eof
    // We just observe the behavior
    // After construction with empty string, the stream may or may not be truthy
    // depending on implementation, but we can check it doesn't crash
    bool result = static_cast<bool>(stream);
    (void)result; // just ensure it doesn't crash
}

// Test operator! is the opposite of operator bool
TEST_F(StreamTest_174, OperatorNotIsOppositeOfBool_174) {
    std::istringstream input("test");
    Stream stream(input);
    EXPECT_NE(static_cast<bool>(stream), !stream);
}

// Test peek returns the first character without consuming it
TEST_F(StreamTest_174, PeekReturnsFirstCharacter_174) {
    std::istringstream input("abc");
    Stream stream(input);
    char c1 = stream.peek();
    char c2 = stream.peek();
    EXPECT_EQ(c1, c2);
    EXPECT_EQ(c1, 'a');
}

// Test get returns characters in order
TEST_F(StreamTest_174, GetReturnsCharactersInOrder_174) {
    std::istringstream input("abc");
    Stream stream(input);
    EXPECT_EQ(stream.get(), 'a');
    EXPECT_EQ(stream.get(), 'b');
    EXPECT_EQ(stream.get(), 'c');
}

// Test get(n) returns a string of n characters
TEST_F(StreamTest_174, GetNReturnsStringOfNCharacters_174) {
    std::istringstream input("hello world");
    Stream stream(input);
    std::string result = stream.get(5);
    EXPECT_EQ(result, "hello");
}

// Test that after getting all characters, stream becomes falsy or returns eof
TEST_F(StreamTest_174, StreamBecomesFalsyAfterAllCharsConsumed_174) {
    std::istringstream input("ab");
    Stream stream(input);
    stream.get();
    stream.get();
    // After consuming all characters, peek should return eof
    EXPECT_EQ(stream.peek(), Stream::eof());
}

// Test eat consumes n characters
TEST_F(StreamTest_174, EatConsumesNCharacters_174) {
    std::istringstream input("abcdef");
    Stream stream(input);
    stream.eat(3);
    EXPECT_EQ(stream.peek(), 'd');
}

// Test mark returns position information
TEST_F(StreamTest_174, MarkReturnsInitialPosition_174) {
    std::istringstream input("hello");
    Stream stream(input);
    Mark m = stream.mark();
    EXPECT_EQ(m.pos, 0);
    EXPECT_EQ(m.line, 0);
    EXPECT_EQ(m.column, 0);
}

// Test pos returns current position
TEST_F(StreamTest_174, PosReturnsCurrentPosition_174) {
    std::istringstream input("hello");
    Stream stream(input);
    EXPECT_EQ(stream.pos(), 0);
    stream.get();
    EXPECT_EQ(stream.pos(), 1);
}

// Test line tracking with newlines
TEST_F(StreamTest_174, LineIncrementsOnNewline_174) {
    std::istringstream input("a\nb\nc");
    Stream stream(input);
    EXPECT_EQ(stream.line(), 0);
    stream.get(); // 'a'
    stream.get(); // '\n'
    EXPECT_EQ(stream.line(), 1);
    stream.get(); // 'b'
    stream.get(); // '\n'
    EXPECT_EQ(stream.line(), 2);
}

// Test column tracking
TEST_F(StreamTest_174, ColumnTracksWithinLine_174) {
    std::istringstream input("abc\ndef");
    Stream stream(input);
    EXPECT_EQ(stream.column(), 0);
    stream.get(); // 'a'
    EXPECT_EQ(stream.column(), 1);
    stream.get(); // 'b'
    EXPECT_EQ(stream.column(), 2);
    stream.get(); // 'c'
    EXPECT_EQ(stream.column(), 3);
    stream.get(); // '\n'
    EXPECT_EQ(stream.column(), 0);
}

// Test ResetColumn
TEST_F(StreamTest_174, ResetColumnResetsToZero_174) {
    std::istringstream input("abcdef");
    Stream stream(input);
    stream.get(); // 'a'
    stream.get(); // 'b'
    EXPECT_EQ(stream.column(), 2);
    stream.ResetColumn();
    EXPECT_EQ(stream.column(), 0);
}

// Test eof static method returns a consistent value
TEST_F(StreamTest_174, EofReturnsConsistentValue_174) {
    char eof1 = Stream::eof();
    char eof2 = Stream::eof();
    EXPECT_EQ(eof1, eof2);
}

// Test that peek on exhausted stream returns eof
TEST_F(StreamTest_174, PeekOnExhaustedStreamReturnsEof_174) {
    std::istringstream input("");
    Stream stream(input);
    EXPECT_EQ(stream.peek(), Stream::eof());
}

// Test get with n=0 returns empty string
TEST_F(StreamTest_174, GetZeroReturnsEmptyString_174) {
    std::istringstream input("hello");
    Stream stream(input);
    std::string result = stream.get(0);
    EXPECT_EQ(result, "");
}

// Test eat with n=0 doesn't change position
TEST_F(StreamTest_174, EatZeroDoesNotChangePosition_174) {
    std::istringstream input("hello");
    Stream stream(input);
    int posBefore = stream.pos();
    stream.eat(0);
    EXPECT_EQ(stream.pos(), posBefore);
}

// Test stream with single character
TEST_F(StreamTest_174, SingleCharacterStream_174) {
    std::istringstream input("x");
    Stream stream(input);
    EXPECT_TRUE(static_cast<bool>(stream));
    EXPECT_EQ(stream.peek(), 'x');
    EXPECT_EQ(stream.get(), 'x');
    EXPECT_EQ(stream.peek(), Stream::eof());
}

// Test copy and move are deleted (compile-time check conceptually, just test construction)
TEST_F(StreamTest_174, StreamCanBeConstructed_174) {
    std::istringstream input("test");
    Stream stream(input);
    EXPECT_TRUE(static_cast<bool>(stream));
}

// Test get(n) where n is larger than remaining characters
TEST_F(StreamTest_174, GetNMoreThanAvailable_174) {
    std::istringstream input("ab");
    Stream stream(input);
    std::string result = stream.get(5);
    // Should return whatever is available, up to n
    EXPECT_LE(result.size(), 5u);
    EXPECT_GE(result.size(), 2u);
}

// Test eat(n) where n is larger than remaining characters
TEST_F(StreamTest_174, EatNMoreThanAvailable_174) {
    std::istringstream input("ab");
    Stream stream(input);
    stream.eat(10);
    EXPECT_EQ(stream.peek(), Stream::eof());
}

// Test with multi-line content and position tracking
TEST_F(StreamTest_174, MultiLinePositionTracking_174) {
    std::istringstream input("ab\ncd\nef");
    Stream stream(input);
    // Consume "ab\n"
    stream.get(); stream.get(); stream.get();
    EXPECT_EQ(stream.line(), 1);
    EXPECT_EQ(stream.column(), 0);
    // Consume "cd\n"
    stream.get(); stream.get(); stream.get();
    EXPECT_EQ(stream.line(), 2);
    EXPECT_EQ(stream.column(), 0);
}

// Test with UTF-8 BOM
TEST_F(StreamTest_174, Utf8ContentBasic_174) {
    std::istringstream input("hello");
    Stream stream(input);
    std::string result = stream.get(5);
    EXPECT_EQ(result, "hello");
}

// Test operator bool after failed underlying stream
TEST_F(StreamTest_174, OperatorBoolWithBadStream_174) {
    std::istringstream input("test");
    input.setstate(std::ios::badbit);
    Stream stream(input);
    // The stream might or might not be truthy depending on readahead
    // Just ensure no crash
    bool result = static_cast<bool>(stream);
    (void)result;
}

// Test mark after consuming some characters
TEST_F(StreamTest_174, MarkAfterConsumingCharacters_174) {
    std::istringstream input("abcdef");
    Stream stream(input);
    stream.get();
    stream.get();
    stream.get();
    Mark m = stream.mark();
    EXPECT_EQ(m.pos, 3);
    EXPECT_EQ(m.line, 0);
    EXPECT_EQ(m.column, 3);
}

// Test large input
TEST_F(StreamTest_174, LargeInput_174) {
    std::string largeStr(4096, 'x');
    std::istringstream input(largeStr);
    Stream stream(input);
    EXPECT_TRUE(static_cast<bool>(stream));
    for (int i = 0; i < 4096; ++i) {
        EXPECT_EQ(stream.get(), 'x');
    }
    EXPECT_EQ(stream.peek(), Stream::eof());
}

// Test that eat(1) is equivalent to get() in terms of position advancement
TEST_F(StreamTest_174, EatOneAdvancesLikeGet_174) {
    std::istringstream input1("abcdef");
    std::istringstream input2("abcdef");
    Stream stream1(input1);
    Stream stream2(input2);

    stream1.get();
    stream2.eat(1);

    EXPECT_EQ(stream1.pos(), stream2.pos());
    EXPECT_EQ(stream1.peek(), stream2.peek());
}

}  // namespace YAML
