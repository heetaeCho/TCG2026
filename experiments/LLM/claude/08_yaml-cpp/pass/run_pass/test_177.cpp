#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "stream.h"

namespace YAML {
namespace {

class StreamTest_177 : public ::testing::Test {
 protected:
  // Helper to create a Stream from a string
  std::unique_ptr<Stream> makeStream(const std::string& content) {
    auto ss = std::make_unique<std::istringstream>(content);
    streams_.push_back(std::move(ss));
    return std::make_unique<Stream>(*streams_.back());
  }

  std::vector<std::unique_ptr<std::istringstream>> streams_;
};

// Test that a stream created from non-empty input is truthy
TEST_F(StreamTest_177, NonEmptyStreamIsTruthy_177) {
  auto stream = makeStream("hello");
  EXPECT_TRUE(static_cast<bool>(*stream));
  EXPECT_FALSE(!(*stream));
}

// Test that a stream created from empty input is falsy
TEST_F(StreamTest_177, EmptyStreamIsFalsy_177) {
  auto stream = makeStream("");
  EXPECT_FALSE(static_cast<bool>(*stream));
  EXPECT_TRUE(!(*stream));
}

// Test peek returns the first character without consuming it
TEST_F(StreamTest_177, PeekReturnsFirstCharacter_177) {
  auto stream = makeStream("abc");
  char c = stream->peek();
  EXPECT_EQ(c, 'a');
  // Peek again should return same character
  char c2 = stream->peek();
  EXPECT_EQ(c2, 'a');
}

// Test get() returns and consumes one character
TEST_F(StreamTest_177, GetReturnsSingleCharacter_177) {
  auto stream = makeStream("abc");
  char c = stream->get();
  EXPECT_EQ(c, 'a');
  char c2 = stream->get();
  EXPECT_EQ(c2, 'b');
  char c3 = stream->get();
  EXPECT_EQ(c3, 'c');
}

// Test get(int n) returns a string of n characters
TEST_F(StreamTest_177, GetNReturnsNCharacters_177) {
  auto stream = makeStream("abcdef");
  std::string result = stream->get(3);
  EXPECT_EQ(result, "abc");
  std::string result2 = stream->get(3);
  EXPECT_EQ(result2, "def");
}

// Test eat(int n) consumes n characters
TEST_F(StreamTest_177, EatConsumesNCharacters_177) {
  auto stream = makeStream("abcdef");
  stream->eat(3);
  char c = stream->peek();
  EXPECT_EQ(c, 'd');
}

// Test eat(0) does not consume any characters
TEST_F(StreamTest_177, EatZeroConsumesNothing_177) {
  auto stream = makeStream("abc");
  stream->eat(0);
  char c = stream->peek();
  EXPECT_EQ(c, 'a');
}

// Test that consuming all characters makes stream falsy
TEST_F(StreamTest_177, StreamBecomesFalsyAfterFullConsumption_177) {
  auto stream = makeStream("ab");
  stream->get();
  stream->get();
  EXPECT_FALSE(static_cast<bool>(*stream));
}

// Test mark() initial position
TEST_F(StreamTest_177, InitialMarkPosition_177) {
  auto stream = makeStream("abc");
  Mark m = stream->mark();
  EXPECT_EQ(m.pos, 0);
  EXPECT_EQ(m.line, 0);
  EXPECT_EQ(m.column, 0);
}

// Test pos() returns current position
TEST_F(StreamTest_177, PosIncrementsAfterGet_177) {
  auto stream = makeStream("abc");
  EXPECT_EQ(stream->pos(), 0);
  stream->get();
  EXPECT_EQ(stream->pos(), 1);
  stream->get();
  EXPECT_EQ(stream->pos(), 2);
}

// Test line() returns current line number
TEST_F(StreamTest_177, LineIncrementsAfterNewline_177) {
  auto stream = makeStream("a\nb\nc");
  EXPECT_EQ(stream->line(), 0);
  stream->get(); // 'a'
  EXPECT_EQ(stream->line(), 0);
  stream->get(); // '\n'
  EXPECT_EQ(stream->line(), 1);
  stream->get(); // 'b'
  EXPECT_EQ(stream->line(), 1);
  stream->get(); // '\n'
  EXPECT_EQ(stream->line(), 2);
}

// Test column() returns current column number
TEST_F(StreamTest_177, ColumnIncrementsAndResetsOnNewline_177) {
  auto stream = makeStream("ab\ncd");
  EXPECT_EQ(stream->column(), 0);
  stream->get(); // 'a'
  EXPECT_EQ(stream->column(), 1);
  stream->get(); // 'b'
  EXPECT_EQ(stream->column(), 2);
  stream->get(); // '\n'
  EXPECT_EQ(stream->column(), 0);
  stream->get(); // 'c'
  EXPECT_EQ(stream->column(), 1);
}

// Test eof() returns a specific character
TEST_F(StreamTest_177, EofReturnsConsistentValue_177) {
  char eof1 = Stream::eof();
  char eof2 = Stream::eof();
  EXPECT_EQ(eof1, eof2);
}

// Test peek on empty stream returns eof
TEST_F(StreamTest_177, PeekOnEmptyStreamReturnsEof_177) {
  auto stream = makeStream("");
  char c = stream->peek();
  EXPECT_EQ(c, Stream::eof());
}

// Test get on exhausted stream returns eof
TEST_F(StreamTest_177, GetOnExhaustedStreamReturnsEof_177) {
  auto stream = makeStream("a");
  stream->get(); // 'a'
  char c = stream->get();
  EXPECT_EQ(c, Stream::eof());
}

// Test ResetColumn resets column to 0
TEST_F(StreamTest_177, ResetColumnResetsToZero_177) {
  auto stream = makeStream("abcdef");
  stream->get();
  stream->get();
  EXPECT_EQ(stream->column(), 2);
  stream->ResetColumn();
  EXPECT_EQ(stream->column(), 0);
}

// Test eat with value equal to stream length
TEST_F(StreamTest_177, EatEntireStream_177) {
  auto stream = makeStream("abc");
  stream->eat(3);
  EXPECT_FALSE(static_cast<bool>(*stream));
  EXPECT_EQ(stream->peek(), Stream::eof());
}

// Test eat with value larger than stream length
TEST_F(StreamTest_177, EatMoreThanStreamLength_177) {
  auto stream = makeStream("ab");
  stream->eat(5);
  EXPECT_FALSE(static_cast<bool>(*stream));
}

// Test get(n) with n larger than remaining characters
TEST_F(StreamTest_177, GetNMoreThanAvailable_177) {
  auto stream = makeStream("ab");
  std::string result = stream->get(5);
  // Should return what's available (at least "ab")
  EXPECT_GE(result.size(), 2u);
  EXPECT_EQ(result.substr(0, 2), "ab");
}

// Test get(0) returns empty string
TEST_F(StreamTest_177, GetZeroReturnsEmpty_177) {
  auto stream = makeStream("abc");
  std::string result = stream->get(0);
  EXPECT_EQ(result, "");
  // Stream should not be consumed
  EXPECT_EQ(stream->peek(), 'a');
}

// Test mark after several operations
TEST_F(StreamTest_177, MarkReflectsCurrentState_177) {
  auto stream = makeStream("ab\ncd");
  stream->get(); // a
  stream->get(); // b
  stream->get(); // \n
  stream->get(); // c
  Mark m = stream->mark();
  EXPECT_EQ(m.pos, 4);
  EXPECT_EQ(m.line, 1);
  EXPECT_EQ(m.column, 1);
}

// Test with UTF-8 BOM content
TEST_F(StreamTest_177, Utf8BomHandled_177) {
  std::string bom = "\xEF\xBB\xBF";
  std::string content = bom + "hello";
  auto stream = makeStream(content);
  // The stream should be valid
  EXPECT_TRUE(static_cast<bool>(*stream));
  // It should handle BOM and eventually produce 'h'
  // The BOM might be consumed or skipped
}

// Test with single character stream
TEST_F(StreamTest_177, SingleCharacterStream_177) {
  auto stream = makeStream("x");
  EXPECT_TRUE(static_cast<bool>(*stream));
  EXPECT_EQ(stream->peek(), 'x');
  char c = stream->get();
  EXPECT_EQ(c, 'x');
  EXPECT_FALSE(static_cast<bool>(*stream));
}

// Test eat(1) is equivalent to get() in terms of position advancement
TEST_F(StreamTest_177, EatOneAdvancesLikeGet_177) {
  auto stream1 = makeStream("abcdef");
  auto stream2 = makeStream("abcdef");

  stream1->get();
  stream2->eat(1);

  EXPECT_EQ(stream1->pos(), stream2->pos());
  EXPECT_EQ(stream1->peek(), stream2->peek());
}

// Test multiple newlines for line tracking
TEST_F(StreamTest_177, MultipleNewlinesTracking_177) {
  auto stream = makeStream("\n\n\n");
  EXPECT_EQ(stream->line(), 0);
  stream->get(); // first \n
  EXPECT_EQ(stream->line(), 1);
  stream->get(); // second \n
  EXPECT_EQ(stream->line(), 2);
  stream->get(); // third \n
  EXPECT_EQ(stream->line(), 3);
}

// Test that large input doesn't crash (boundary for prefetch buffer)
TEST_F(StreamTest_177, LargeInputHandled_177) {
  std::string large(4096, 'A');
  auto stream = makeStream(large);
  EXPECT_TRUE(static_cast<bool>(*stream));
  stream->eat(4096);
  EXPECT_FALSE(static_cast<bool>(*stream));
}

// Test interleaved peek and get
TEST_F(StreamTest_177, InterleavedPeekAndGet_177) {
  auto stream = makeStream("xyz");
  EXPECT_EQ(stream->peek(), 'x');
  EXPECT_EQ(stream->get(), 'x');
  EXPECT_EQ(stream->peek(), 'y');
  EXPECT_EQ(stream->peek(), 'y');
  EXPECT_EQ(stream->get(), 'y');
  EXPECT_EQ(stream->get(), 'z');
  EXPECT_EQ(stream->peek(), Stream::eof());
}

}  // namespace
}  // namespace YAML
