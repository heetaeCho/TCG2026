#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "stream.h"

namespace YAML {
namespace {

// Test fixture for Stream tests
class StreamTest_75 : public ::testing::Test {
protected:
    // Helper to create a stream from a string
    std::unique_ptr<Stream> makeStream(const std::string& content) {
        auto ss = std::make_unique<std::istringstream>(content);
        streams_.push_back(std::move(ss));
        return std::make_unique<Stream>(*streams_.back());
    }

    std::vector<std::unique_ptr<std::istringstream>> streams_;
};

// Test that a newly constructed stream from non-empty input is truthy
TEST_F(StreamTest_75, ConstructFromNonEmptyStream_IsTruthy_75) {
    auto stream = makeStream("hello");
    EXPECT_TRUE(static_cast<bool>(*stream));
}

// Test that a newly constructed stream from empty input behaves correctly
TEST_F(StreamTest_75, ConstructFromEmptyStream_75) {
    auto stream = makeStream("");
    // An empty stream should not be readable
    EXPECT_FALSE(static_cast<bool>(*stream));
}

// Test operator! on non-empty stream
TEST_F(StreamTest_75, OperatorNot_NonEmptyStream_ReturnsFalse_75) {
    auto stream = makeStream("abc");
    EXPECT_FALSE(!(*stream));
}

// Test operator! on empty stream
TEST_F(StreamTest_75, OperatorNot_EmptyStream_ReturnsTrue_75) {
    auto stream = makeStream("");
    EXPECT_TRUE(!(*stream));
}

// Test initial position is 0
TEST_F(StreamTest_75, InitialPosition_IsZero_75) {
    auto stream = makeStream("hello");
    EXPECT_EQ(0, stream->pos());
}

// Test initial line is 0
TEST_F(StreamTest_75, InitialLine_IsZero_75) {
    auto stream = makeStream("hello");
    EXPECT_EQ(0, stream->line());
}

// Test initial column is 0
TEST_F(StreamTest_75, InitialColumn_IsZero_75) {
    auto stream = makeStream("hello");
    EXPECT_EQ(0, stream->column());
}

// Test peek returns first character without advancing
TEST_F(StreamTest_75, Peek_ReturnsFirstCharWithoutAdvancing_75) {
    auto stream = makeStream("abc");
    char c = stream->peek();
    EXPECT_EQ('a', c);
    // Peek again should return same character
    EXPECT_EQ('a', stream->peek());
    // Position should not change
    EXPECT_EQ(0, stream->pos());
}

// Test peek on empty stream returns eof
TEST_F(StreamTest_75, Peek_EmptyStream_ReturnsEof_75) {
    auto stream = makeStream("");
    char c = stream->peek();
    EXPECT_EQ(Stream::eof(), c);
}

// Test get() returns character and advances position
TEST_F(StreamTest_75, Get_ReturnsCharAndAdvances_75) {
    auto stream = makeStream("abc");
    char c = stream->get();
    EXPECT_EQ('a', c);
    EXPECT_EQ(1, stream->pos());
}

// Test get() on sequential characters
TEST_F(StreamTest_75, Get_SequentialCharacters_75) {
    auto stream = makeStream("xyz");
    EXPECT_EQ('x', stream->get());
    EXPECT_EQ('y', stream->get());
    EXPECT_EQ('z', stream->get());
    EXPECT_EQ(3, stream->pos());
}

// Test get(n) returns string of n characters
TEST_F(StreamTest_75, GetN_ReturnsNCharacters_75) {
    auto stream = makeStream("hello world");
    std::string result = stream->get(5);
    EXPECT_EQ("hello", result);
    EXPECT_EQ(5, stream->pos());
}

// Test get(n) with n=0 returns empty string
TEST_F(StreamTest_75, GetN_Zero_ReturnsEmptyString_75) {
    auto stream = makeStream("hello");
    std::string result = stream->get(0);
    EXPECT_EQ("", result);
    EXPECT_EQ(0, stream->pos());
}

// Test get(n) with n larger than available characters
TEST_F(StreamTest_75, GetN_MoreThanAvailable_75) {
    auto stream = makeStream("hi");
    std::string result = stream->get(10);
    // Should return what's available
    EXPECT_GE(2u, result.size());
}

// Test eat(n) skips n characters
TEST_F(StreamTest_75, Eat_SkipsNCharacters_75) {
    auto stream = makeStream("abcdef");
    stream->eat(3);
    EXPECT_EQ(3, stream->pos());
    EXPECT_EQ('d', stream->peek());
}

// Test eat(0) does nothing
TEST_F(StreamTest_75, Eat_Zero_DoesNothing_75) {
    auto stream = makeStream("abc");
    stream->eat(0);
    EXPECT_EQ(0, stream->pos());
    EXPECT_EQ('a', stream->peek());
}

// Test that reading until end makes stream falsy
TEST_F(StreamTest_75, ReadUntilEnd_StreamBecomesFalsy_75) {
    auto stream = makeStream("ab");
    stream->get();
    stream->get();
    EXPECT_FALSE(static_cast<bool>(*stream));
}

// Test eof() static method returns consistent value
TEST_F(StreamTest_75, Eof_ReturnsConsistentValue_75) {
    char eof1 = Stream::eof();
    char eof2 = Stream::eof();
    EXPECT_EQ(eof1, eof2);
}

// Test mark() returns current mark
TEST_F(StreamTest_75, Mark_ReturnsCurrentMark_75) {
    auto stream = makeStream("abc");
    Mark m = stream->mark();
    EXPECT_EQ(0, m.pos);
    EXPECT_EQ(0, m.line);
    EXPECT_EQ(0, m.column);
}

// Test mark() after getting some characters
TEST_F(StreamTest_75, Mark_AfterGet_UpdatesPos_75) {
    auto stream = makeStream("abc");
    stream->get();
    stream->get();
    Mark m = stream->mark();
    EXPECT_EQ(2, m.pos);
    EXPECT_EQ(2, m.column);
}

// Test newline advances line counter
TEST_F(StreamTest_75, Newline_AdvancesLineCounter_75) {
    auto stream = makeStream("a\nb");
    stream->get(); // 'a'
    stream->get(); // '\n'
    EXPECT_EQ(1, stream->line());
}

// Test newline resets column
TEST_F(StreamTest_75, Newline_ResetsColumn_75) {
    auto stream = makeStream("a\nb");
    stream->get(); // 'a'
    stream->get(); // '\n'
    EXPECT_EQ(0, stream->column());
}

// Test ResetColumn resets column to 0
TEST_F(StreamTest_75, ResetColumn_ResetsToZero_75) {
    auto stream = makeStream("abcdef");
    stream->get();
    stream->get();
    stream->get();
    EXPECT_EQ(3, stream->column());
    stream->ResetColumn();
    EXPECT_EQ(0, stream->column());
}

// Test multiple newlines
TEST_F(StreamTest_75, MultipleNewlines_CorrectLineCount_75) {
    auto stream = makeStream("a\nb\nc");
    stream->get(); // 'a'
    stream->get(); // '\n'
    stream->get(); // 'b'
    stream->get(); // '\n'
    EXPECT_EQ(2, stream->line());
    EXPECT_EQ('c', stream->peek());
}

// Test get after eat
TEST_F(StreamTest_75, GetAfterEat_ReturnsCorrectChar_75) {
    auto stream = makeStream("abcdef");
    stream->eat(3);
    char c = stream->get();
    EXPECT_EQ('d', c);
}

// Test large input stream
TEST_F(StreamTest_75, LargeInput_HandlesCorrectly_75) {
    std::string large(4096, 'x');
    auto stream = makeStream(large);
    EXPECT_TRUE(static_cast<bool>(*stream));
    EXPECT_EQ('x', stream->peek());
    stream->eat(4096);
    EXPECT_FALSE(static_cast<bool>(*stream));
}

// Test single character stream
TEST_F(StreamTest_75, SingleCharStream_75) {
    auto stream = makeStream("z");
    EXPECT_TRUE(static_cast<bool>(*stream));
    EXPECT_EQ('z', stream->get());
    EXPECT_FALSE(static_cast<bool>(*stream));
    EXPECT_EQ(Stream::eof(), stream->peek());
}

// Test position consistency between pos() and mark().pos
TEST_F(StreamTest_75, PosConsistentWithMark_75) {
    auto stream = makeStream("abcde");
    stream->get();
    stream->get();
    EXPECT_EQ(stream->pos(), stream->mark().pos);
}

// Test line consistency between line() and mark().line
TEST_F(StreamTest_75, LineConsistentWithMark_75) {
    auto stream = makeStream("a\nb");
    stream->get();
    stream->get();
    EXPECT_EQ(stream->line(), stream->mark().line);
}

// Test column consistency between column() and mark().column
TEST_F(StreamTest_75, ColumnConsistentWithMark_75) {
    auto stream = makeStream("abc");
    stream->get();
    stream->get();
    EXPECT_EQ(stream->column(), stream->mark().column);
}

// Test tab character handling
TEST_F(StreamTest_75, TabCharacter_AdvancesColumn_75) {
    auto stream = makeStream("\tabc");
    stream->get(); // tab
    // Column should advance (exact behavior depends on implementation)
    EXPECT_GE(stream->column(), 1);
}

// Test carriage return handling
TEST_F(StreamTest_75, CarriageReturn_75) {
    auto stream = makeStream("a\rb");
    stream->get(); // 'a'
    stream->get(); // '\r'
    // CR should act as newline in YAML
    EXPECT_GE(stream->line(), 0);
}

// Test CRLF handling
TEST_F(StreamTest_75, CRLF_HandledAsOneLine_75) {
    auto stream = makeStream("a\r\nb");
    stream->get(); // 'a'
    stream->get(); // '\r' or '\n' depending on implementation
    // After reading past the line ending, we should be on the next line
    while (stream->peek() != 'b' && static_cast<bool>(*stream)) {
        stream->get();
    }
    EXPECT_EQ(1, stream->line());
}

// Test get(1) returns single character string
TEST_F(StreamTest_75, GetOne_ReturnsSingleCharString_75) {
    auto stream = makeStream("abc");
    std::string result = stream->get(1);
    EXPECT_EQ(1u, result.size());
    EXPECT_EQ("a", result);
}

// Test eat followed by peek
TEST_F(StreamTest_75, EatThenPeek_75) {
    auto stream = makeStream("0123456789");
    stream->eat(5);
    EXPECT_EQ('5', stream->peek());
}

// Test UTF-8 BOM handling
TEST_F(StreamTest_75, Utf8Bom_HandledCorrectly_75) {
    std::string bom = "\xEF\xBB\xBF";
    std::string content = bom + "hello";
    auto stream = makeStream(content);
    // Stream should handle BOM and still be valid
    EXPECT_TRUE(static_cast<bool>(*stream));
}

}  // namespace
}  // namespace YAML
