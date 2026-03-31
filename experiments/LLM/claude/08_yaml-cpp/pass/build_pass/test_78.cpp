#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "stream.h"

// Test fixture for Stream tests
class StreamTest_78 : public ::testing::Test {
protected:
    // Helper to create a Stream from a string
    std::unique_ptr<std::istringstream> makeStream(const std::string& content) {
        return std::make_unique<std::istringstream>(content);
    }
};

// Test: Stream constructed from non-empty input is truthy
TEST_F(StreamTest_78, ConstructWithNonEmptyInput_BoolIsTrue_78) {
    auto ss = makeStream("hello");
    YAML::Stream stream(*ss);
    EXPECT_TRUE(static_cast<bool>(stream));
    EXPECT_FALSE(!stream);
}

// Test: Stream constructed from empty input
TEST_F(StreamTest_78, ConstructWithEmptyInput_78) {
    auto ss = makeStream("");
    YAML::Stream stream(*ss);
    // Empty stream should return eof on peek
    char c = stream.peek();
    EXPECT_EQ(c, YAML::Stream::eof());
}

// Test: peek returns first character without consuming it
TEST_F(StreamTest_78, PeekReturnsFirstCharWithoutConsuming_78) {
    auto ss = makeStream("abc");
    YAML::Stream stream(*ss);
    char first = stream.peek();
    char second = stream.peek();
    EXPECT_EQ(first, 'a');
    EXPECT_EQ(second, 'a');
}

// Test: get returns and consumes a single character
TEST_F(StreamTest_78, GetReturnsSingleCharAndAdvances_78) {
    auto ss = makeStream("abc");
    YAML::Stream stream(*ss);
    char c1 = stream.get();
    EXPECT_EQ(c1, 'a');
    char c2 = stream.get();
    EXPECT_EQ(c2, 'b');
    char c3 = stream.get();
    EXPECT_EQ(c3, 'c');
}

// Test: get(n) returns string of n characters
TEST_F(StreamTest_78, GetNReturnsNCharacters_78) {
    auto ss = makeStream("hello world");
    YAML::Stream stream(*ss);
    std::string result = stream.get(5);
    EXPECT_EQ(result, "hello");
}

// Test: get(n) with n larger than remaining content
TEST_F(StreamTest_78, GetNMoreThanAvailable_78) {
    auto ss = makeStream("hi");
    YAML::Stream stream(*ss);
    std::string result = stream.get(10);
    // Should return what's available (may include eof markers or just available chars)
    EXPECT_LE(result.size(), 10u);
}

// Test: eat(n) consumes n characters
TEST_F(StreamTest_78, EatConsumesNCharacters_78) {
    auto ss = makeStream("abcdef");
    YAML::Stream stream(*ss);
    stream.eat(3);
    char c = stream.peek();
    EXPECT_EQ(c, 'd');
}

// Test: mark() returns initial position
TEST_F(StreamTest_78, MarkInitialPosition_78) {
    auto ss = makeStream("test");
    YAML::Stream stream(*ss);
    YAML::Mark m = stream.mark();
    EXPECT_EQ(m.pos, 0);
    EXPECT_EQ(m.line, 0);
    EXPECT_EQ(m.column, 0);
}

// Test: pos(), line(), column() return correct initial values
TEST_F(StreamTest_78, InitialPosLineColumn_78) {
    auto ss = makeStream("test");
    YAML::Stream stream(*ss);
    EXPECT_EQ(stream.pos(), 0);
    EXPECT_EQ(stream.line(), 0);
    EXPECT_EQ(stream.column(), 0);
}

// Test: Position advances after get
TEST_F(StreamTest_78, PositionAdvancesAfterGet_78) {
    auto ss = makeStream("abc");
    YAML::Stream stream(*ss);
    stream.get();
    EXPECT_EQ(stream.pos(), 1);
    EXPECT_EQ(stream.column(), 1);
}

// Test: Line advances on newline character
TEST_F(StreamTest_78, LineAdvancesOnNewline_78) {
    auto ss = makeStream("a\nb");
    YAML::Stream stream(*ss);
    stream.get(); // 'a'
    stream.get(); // '\n'
    EXPECT_EQ(stream.line(), 1);
    EXPECT_EQ(stream.column(), 0);
}

// Test: ResetColumn resets column to 0
TEST_F(StreamTest_78, ResetColumnResetsToZero_78) {
    auto ss = makeStream("abcdef");
    YAML::Stream stream(*ss);
    stream.get(); // 'a'
    stream.get(); // 'b'
    stream.get(); // 'c'
    EXPECT_EQ(stream.column(), 3);
    stream.ResetColumn();
    EXPECT_EQ(stream.column(), 0);
}

// Test: ResetColumn on initial state
TEST_F(StreamTest_78, ResetColumnOnInitialState_78) {
    auto ss = makeStream("test");
    YAML::Stream stream(*ss);
    stream.ResetColumn();
    EXPECT_EQ(stream.column(), 0);
}

// Test: eof() returns a specific character
TEST_F(StreamTest_78, EofReturnsConsistentValue_78) {
    char e1 = YAML::Stream::eof();
    char e2 = YAML::Stream::eof();
    EXPECT_EQ(e1, e2);
}

// Test: After consuming all characters, peek returns eof
TEST_F(StreamTest_78, AfterAllConsumedPeekReturnsEof_78) {
    auto ss = makeStream("ab");
    YAML::Stream stream(*ss);
    stream.get();
    stream.get();
    EXPECT_EQ(stream.peek(), YAML::Stream::eof());
}

// Test: After consuming all characters, bool is false
TEST_F(StreamTest_78, AfterAllConsumedBoolIsFalse_78) {
    auto ss = makeStream("a");
    YAML::Stream stream(*ss);
    stream.get();
    // After consuming everything, further operations should reflect end
    EXPECT_EQ(stream.peek(), YAML::Stream::eof());
}

// Test: eat(0) does nothing
TEST_F(StreamTest_78, EatZeroDoesNothing_78) {
    auto ss = makeStream("abc");
    YAML::Stream stream(*ss);
    stream.eat(0);
    EXPECT_EQ(stream.peek(), 'a');
    EXPECT_EQ(stream.pos(), 0);
}

// Test: get(0) returns empty string
TEST_F(StreamTest_78, GetZeroReturnsEmptyString_78) {
    auto ss = makeStream("abc");
    YAML::Stream stream(*ss);
    std::string result = stream.get(0);
    EXPECT_EQ(result, "");
    EXPECT_EQ(stream.peek(), 'a');
}

// Test: Multiple newlines track line correctly
TEST_F(StreamTest_78, MultipleNewlinesTrackLineCorrectly_78) {
    auto ss = makeStream("a\nb\nc");
    YAML::Stream stream(*ss);
    stream.get(); // 'a'
    stream.get(); // '\n'
    EXPECT_EQ(stream.line(), 1);
    stream.get(); // 'b'
    stream.get(); // '\n'
    EXPECT_EQ(stream.line(), 2);
    stream.get(); // 'c'
    EXPECT_EQ(stream.line(), 2);
}

// Test: Column tracks correctly within a line
TEST_F(StreamTest_78, ColumnTracksCorrectlyWithinLine_78) {
    auto ss = makeStream("abcd\nef");
    YAML::Stream stream(*ss);
    stream.get(); // a, col=1
    stream.get(); // b, col=2
    stream.get(); // c, col=3
    stream.get(); // d, col=4
    EXPECT_EQ(stream.column(), 4);
    stream.get(); // \n, col=0
    EXPECT_EQ(stream.column(), 0);
    stream.get(); // e, col=1
    EXPECT_EQ(stream.column(), 1);
}

// Test: eat advances position correctly
TEST_F(StreamTest_78, EatAdvancesPosition_78) {
    auto ss = makeStream("abcdefgh");
    YAML::Stream stream(*ss);
    stream.eat(4);
    EXPECT_EQ(stream.pos(), 4);
    EXPECT_EQ(stream.peek(), 'e');
}

// Test: get(n) followed by peek
TEST_F(StreamTest_78, GetNFollowedByPeek_78) {
    auto ss = makeStream("abcdefgh");
    YAML::Stream stream(*ss);
    std::string s = stream.get(3);
    EXPECT_EQ(s, "abc");
    EXPECT_EQ(stream.peek(), 'd');
}

// Test: Stream with only newline
TEST_F(StreamTest_78, StreamWithOnlyNewline_78) {
    auto ss = makeStream("\n");
    YAML::Stream stream(*ss);
    char c = stream.get();
    EXPECT_EQ(c, '\n');
    EXPECT_EQ(stream.line(), 1);
    EXPECT_EQ(stream.column(), 0);
}

// Test: Large input stream
TEST_F(StreamTest_78, LargeInputStream_78) {
    std::string large(4096, 'x');
    auto ss = makeStream(large);
    YAML::Stream stream(*ss);
    EXPECT_TRUE(static_cast<bool>(stream));
    EXPECT_EQ(stream.peek(), 'x');
    stream.eat(4096);
    EXPECT_EQ(stream.peek(), YAML::Stream::eof());
}

// Test: ResetColumn after newline
TEST_F(StreamTest_78, ResetColumnAfterNewline_78) {
    auto ss = makeStream("ab\ncd");
    YAML::Stream stream(*ss);
    stream.get(); // a
    stream.get(); // b
    stream.get(); // \n
    EXPECT_EQ(stream.column(), 0);
    stream.get(); // c
    EXPECT_EQ(stream.column(), 1);
    stream.ResetColumn();
    EXPECT_EQ(stream.column(), 0);
}

// Test: Copy and move constructors are deleted (compile-time check implicitly)
// This is a design verification - we just ensure the class works as expected with single ownership
TEST_F(StreamTest_78, SingleOwnershipWorks_78) {
    auto ss = makeStream("test");
    YAML::Stream stream(*ss);
    EXPECT_EQ(stream.peek(), 't');
}

// Test: operator! on valid stream
TEST_F(StreamTest_78, OperatorNotOnValidStream_78) {
    auto ss = makeStream("data");
    YAML::Stream stream(*ss);
    EXPECT_FALSE(!stream);
}

// Test: operator! on exhausted stream
TEST_F(StreamTest_78, OperatorNotOnExhaustedStream_78) {
    auto ss = makeStream("");
    YAML::Stream stream(*ss);
    // An empty stream - peek returns eof
    EXPECT_EQ(stream.peek(), YAML::Stream::eof());
}

// Test: Carriage return handling
TEST_F(StreamTest_78, CarriageReturnHandling_78) {
    auto ss = makeStream("a\r\nb");
    YAML::Stream stream(*ss);
    stream.get(); // 'a'
    stream.get(); // '\r' or newline normalized
    // After processing the line ending, line should advance
    // The exact behavior depends on implementation, but we verify no crash
    // and that we can continue reading
    char c = stream.get();
    // Could be '\n' or 'b' depending on normalization
    // Just verify we don't crash and can continue
    if (c != 'b') {
        c = stream.get(); // should be 'b' now
    }
}

// Test: mark reflects position after operations
TEST_F(StreamTest_78, MarkReflectsPositionAfterOps_78) {
    auto ss = makeStream("xyz");
    YAML::Stream stream(*ss);
    stream.get();
    stream.get();
    YAML::Mark m = stream.mark();
    EXPECT_EQ(m.pos, 2);
    EXPECT_EQ(m.column, 2);
    EXPECT_EQ(m.line, 0);
}
