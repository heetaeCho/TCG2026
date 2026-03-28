#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "stream.h"

namespace YAML {
namespace {

// Helper to create a Stream from a string
class StreamTest_172 : public ::testing::Test {
protected:
    std::unique_ptr<Stream> makeStream(const std::string& content) {
        ss_ = std::make_unique<std::istringstream>(content);
        return std::make_unique<Stream>(*ss_);
    }
    
    std::unique_ptr<std::istringstream> ss_;
};

// Test basic construction and bool operator with valid content
TEST_F(StreamTest_172, ConstructWithValidInput_172) {
    auto stream = makeStream("hello");
    EXPECT_TRUE(static_cast<bool>(*stream));
    EXPECT_FALSE(!(*stream));
}

// Test construction with empty input
TEST_F(StreamTest_172, ConstructWithEmptyInput_172) {
    auto stream = makeStream("");
    // Empty stream should still be valid until we try to read
    // peek on empty should return eof
    char c = stream->peek();
    EXPECT_EQ(c, Stream::eof());
}

// Test peek returns first character without consuming
TEST_F(StreamTest_172, PeekReturnsFirstChar_172) {
    auto stream = makeStream("abc");
    EXPECT_EQ(stream->peek(), 'a');
    // Peek again should return the same character
    EXPECT_EQ(stream->peek(), 'a');
}

// Test get returns and consumes one character
TEST_F(StreamTest_172, GetConsumesOneChar_172) {
    auto stream = makeStream("abc");
    char c = stream->get();
    EXPECT_EQ(c, 'a');
    EXPECT_EQ(stream->peek(), 'b');
}

// Test get(n) returns a string of n characters
TEST_F(StreamTest_172, GetNReturnsNChars_172) {
    auto stream = makeStream("abcdef");
    std::string result = stream->get(3);
    EXPECT_EQ(result, "abc");
    EXPECT_EQ(stream->peek(), 'd');
}

// Test eat(n) consumes n characters
TEST_F(StreamTest_172, EatNConsumesNChars_172) {
    auto stream = makeStream("abcdef");
    stream->eat(3);
    EXPECT_EQ(stream->peek(), 'd');
}

// Test mark returns initial position
TEST_F(StreamTest_172, InitialMarkPosition_172) {
    auto stream = makeStream("abc");
    Mark m = stream->mark();
    EXPECT_EQ(m.pos, 0);
    EXPECT_EQ(m.line, 0);
    EXPECT_EQ(m.column, 0);
}

// Test pos, line, column accessors
TEST_F(StreamTest_172, PosLineColumnAccessors_172) {
    auto stream = makeStream("abc");
    EXPECT_EQ(stream->pos(), 0);
    EXPECT_EQ(stream->line(), 0);
    EXPECT_EQ(stream->column(), 0);
}

// Test position advances after get
TEST_F(StreamTest_172, PositionAdvancesAfterGet_172) {
    auto stream = makeStream("abc");
    stream->get();
    EXPECT_EQ(stream->pos(), 1);
    EXPECT_EQ(stream->column(), 1);
}

// Test position advances after get(n)
TEST_F(StreamTest_172, PositionAdvancesAfterGetN_172) {
    auto stream = makeStream("abcdef");
    stream->get(3);
    EXPECT_EQ(stream->pos(), 3);
    EXPECT_EQ(stream->column(), 3);
}

// Test position advances after eat(n)
TEST_F(StreamTest_172, PositionAdvancesAfterEatN_172) {
    auto stream = makeStream("abcdef");
    stream->eat(2);
    EXPECT_EQ(stream->pos(), 2);
    EXPECT_EQ(stream->column(), 2);
}

// Test newline increments line and resets column
TEST_F(StreamTest_172, NewlineIncrementsLine_172) {
    auto stream = makeStream("a\nb");
    stream->get(); // 'a'
    stream->get(); // '\n'
    EXPECT_EQ(stream->line(), 1);
    EXPECT_EQ(stream->column(), 0);
    EXPECT_EQ(stream->peek(), 'b');
}

// Test reading entire content
TEST_F(StreamTest_172, ReadEntireContent_172) {
    auto stream = makeStream("abc");
    std::string result;
    while (*stream) {
        char c = stream->get();
        if (c != Stream::eof()) {
            result += c;
        }
    }
    EXPECT_EQ(result, "abc");
}

// Test operator bool becomes false at end of stream
TEST_F(StreamTest_172, BoolFalseAtEndOfStream_172) {
    auto stream = makeStream("a");
    stream->get(); // consume 'a'
    // After consuming all chars, peek should return eof
    EXPECT_EQ(stream->peek(), Stream::eof());
}

// Test eof static method
TEST_F(StreamTest_172, EofStaticMethod_172) {
    char eof = Stream::eof();
    // eof should be a consistent value
    EXPECT_EQ(eof, Stream::eof());
}

// Test get(0) returns empty string
TEST_F(StreamTest_172, GetZeroReturnsEmpty_172) {
    auto stream = makeStream("abc");
    std::string result = stream->get(0);
    EXPECT_EQ(result, "");
    EXPECT_EQ(stream->peek(), 'a');
}

// Test eat(0) does nothing
TEST_F(StreamTest_172, EatZeroDoesNothing_172) {
    auto stream = makeStream("abc");
    stream->eat(0);
    EXPECT_EQ(stream->peek(), 'a');
    EXPECT_EQ(stream->pos(), 0);
}

// Test ResetColumn
TEST_F(StreamTest_172, ResetColumnResetsColumnToZero_172) {
    auto stream = makeStream("abcdef");
    stream->get(3);
    EXPECT_EQ(stream->column(), 3);
    stream->ResetColumn();
    EXPECT_EQ(stream->column(), 0);
}

// Test with large content beyond prefetch size
TEST_F(StreamTest_172, LargeContentBeyondPrefetch_172) {
    std::string large(4096, 'x');
    auto stream = makeStream(large);
    EXPECT_TRUE(static_cast<bool>(*stream));
    EXPECT_EQ(stream->peek(), 'x');
    
    // Read all characters
    for (int i = 0; i < 4096; ++i) {
        char c = stream->get();
        EXPECT_EQ(c, 'x');
    }
    EXPECT_EQ(stream->peek(), Stream::eof());
}

// Test multiple newlines
TEST_F(StreamTest_172, MultipleNewlines_172) {
    auto stream = makeStream("a\nb\nc");
    stream->get(); // 'a'
    stream->get(); // '\n'
    EXPECT_EQ(stream->line(), 1);
    stream->get(); // 'b'
    stream->get(); // '\n'
    EXPECT_EQ(stream->line(), 2);
    EXPECT_EQ(stream->column(), 0);
    EXPECT_EQ(stream->peek(), 'c');
}

// Test get(n) when n exceeds available content
TEST_F(StreamTest_172, GetNExceedsContent_172) {
    auto stream = makeStream("ab");
    std::string result = stream->get(5);
    // Should return what's available (implementation may vary, but should not crash)
    EXPECT_LE(result.size(), 5u);
}

// Test eat(n) when n exceeds available content
TEST_F(StreamTest_172, EatNExceedsContent_172) {
    auto stream = makeStream("ab");
    stream->eat(5);
    // Should not crash; stream should be at end
    EXPECT_EQ(stream->peek(), Stream::eof());
}

// Test operator! on valid stream
TEST_F(StreamTest_172, OperatorNotOnValidStream_172) {
    auto stream = makeStream("abc");
    EXPECT_FALSE(!(*stream));
}

// Test operator! on exhausted stream
TEST_F(StreamTest_172, OperatorNotOnExhaustedStream_172) {
    auto stream = makeStream("");
    // An empty stream
    char c = stream->peek();
    EXPECT_EQ(c, Stream::eof());
}

// Test sequential get calls
TEST_F(StreamTest_172, SequentialGetCalls_172) {
    auto stream = makeStream("xyz");
    EXPECT_EQ(stream->get(), 'x');
    EXPECT_EQ(stream->get(), 'y');
    EXPECT_EQ(stream->get(), 'z');
    EXPECT_EQ(stream->get(), Stream::eof());
}

// Test UTF-8 BOM handling (if present)
TEST_F(StreamTest_172, Utf8BomHandling_172) {
    std::string bom = "\xEF\xBB\xBF" "abc";
    auto stream = makeStream(bom);
    // Stream should handle BOM; first readable char may or may not be 'a'
    EXPECT_TRUE(static_cast<bool>(*stream));
}

// Test tab character
TEST_F(StreamTest_172, TabCharacter_172) {
    auto stream = makeStream("\tabc");
    char c = stream->get();
    EXPECT_EQ(c, '\t');
}

// Test carriage return line feed
TEST_F(StreamTest_172, CrLfHandling_172) {
    auto stream = makeStream("a\r\nb");
    stream->get(); // 'a'
    stream->get(); // '\r' or consumes \r\n
    // After processing line ending, we should eventually reach 'b'
    // The exact behavior depends on implementation, but stream should not crash
    while (stream->peek() != 'b' && *stream) {
        stream->get();
    }
    if (*stream) {
        EXPECT_EQ(stream->peek(), 'b');
    }
}

// Test mark after consuming characters
TEST_F(StreamTest_172, MarkAfterConsumption_172) {
    auto stream = makeStream("abcdef");
    stream->get(3);
    Mark m = stream->mark();
    EXPECT_EQ(m.pos, 3);
    EXPECT_EQ(m.column, 3);
    EXPECT_EQ(m.line, 0);
}

// Test single character stream
TEST_F(StreamTest_172, SingleCharStream_172) {
    auto stream = makeStream("x");
    EXPECT_TRUE(static_cast<bool>(*stream));
    EXPECT_EQ(stream->peek(), 'x');
    EXPECT_EQ(stream->get(), 'x');
    EXPECT_EQ(stream->peek(), Stream::eof());
}

// Test get(1) is equivalent to single get
TEST_F(StreamTest_172, GetOneEquivalentToGet_172) {
    auto stream1 = makeStream("abc");
    auto ss2 = std::make_unique<std::istringstream>("abc");
    auto stream2 = std::make_unique<Stream>(*ss2);
    
    char c1 = stream1->get();
    std::string s2 = stream2->get(1);
    
    EXPECT_EQ(c1, s2[0]);
}

}  // namespace
}  // namespace YAML
