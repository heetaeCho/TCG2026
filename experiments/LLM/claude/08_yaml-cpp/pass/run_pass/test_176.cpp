#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "stream.h"

namespace YAML {
namespace {

class StreamTest_176 : public ::testing::Test {
 protected:
  // Helper to create a Stream from a string
  std::unique_ptr<Stream> MakeStream(const std::string& input) {
    ss_ = std::make_unique<std::istringstream>(input);
    return std::make_unique<Stream>(*ss_);
  }

  std::unique_ptr<std::istringstream> ss_;
};

// Test that a stream constructed from a non-empty input is truthy
TEST_F(StreamTest_176, NonEmptyStreamIsTruthy_176) {
  auto stream = MakeStream("hello");
  EXPECT_TRUE(static_cast<bool>(*stream));
}

// Test that a stream constructed from an empty input is falsy
TEST_F(StreamTest_176, EmptyStreamIsFalsy_176) {
  auto stream = MakeStream("");
  // After construction with empty input, the stream should indicate no more data
  EXPECT_FALSE(static_cast<bool>(*stream));
}

// Test operator! on non-empty stream
TEST_F(StreamTest_176, OperatorNotOnNonEmptyStream_176) {
  auto stream = MakeStream("abc");
  EXPECT_FALSE(!(*stream));
}

// Test operator! on empty stream
TEST_F(StreamTest_176, OperatorNotOnEmptyStream_176) {
  auto stream = MakeStream("");
  EXPECT_TRUE(!(*stream));
}

// Test peek returns the first character without consuming it
TEST_F(StreamTest_176, PeekReturnsFirstChar_176) {
  auto stream = MakeStream("xyz");
  char c1 = stream->peek();
  char c2 = stream->peek();
  EXPECT_EQ(c1, 'x');
  EXPECT_EQ(c2, 'x');  // peek should not advance
}

// Test get() returns characters in sequence
TEST_F(StreamTest_176, GetReturnsSingleCharsInOrder_176) {
  auto stream = MakeStream("abc");
  EXPECT_EQ(stream->get(), 'a');
  EXPECT_EQ(stream->get(), 'b');
  EXPECT_EQ(stream->get(), 'c');
}

// Test get(n) returns a string of n characters
TEST_F(StreamTest_176, GetNReturnsStringOfNChars_176) {
  auto stream = MakeStream("hello world");
  std::string result = stream->get(5);
  EXPECT_EQ(result, "hello");
}

// Test get(0) returns empty string
TEST_F(StreamTest_176, GetZeroReturnsEmptyString_176) {
  auto stream = MakeStream("hello");
  std::string result = stream->get(0);
  EXPECT_EQ(result, "");
}

// Test get(-1) returns empty string (negative n)
TEST_F(StreamTest_176, GetNegativeReturnsEmptyString_176) {
  auto stream = MakeStream("hello");
  std::string result = stream->get(-1);
  EXPECT_EQ(result, "");
}

// Test get(n) where n equals the entire content length
TEST_F(StreamTest_176, GetNEqualsContentLength_176) {
  auto stream = MakeStream("abcd");
  std::string result = stream->get(4);
  EXPECT_EQ(result, "abcd");
}

// Test get(1) returns a single-character string
TEST_F(StreamTest_176, GetOneReturnsOneCharString_176) {
  auto stream = MakeStream("z");
  std::string result = stream->get(1);
  EXPECT_EQ(result, "z");
}

// Test that get() advances the position tracked by mark
TEST_F(StreamTest_176, GetAdvancesPosition_176) {
  auto stream = MakeStream("abcdef");
  int initialPos = stream->pos();
  stream->get();
  int afterOneGet = stream->pos();
  EXPECT_EQ(afterOneGet, initialPos + 1);
}

// Test that eat(n) consumes n characters
TEST_F(StreamTest_176, EatConsumesNChars_176) {
  auto stream = MakeStream("abcdef");
  stream->eat(3);
  EXPECT_EQ(stream->peek(), 'd');
}

// Test eat(0) does nothing
TEST_F(StreamTest_176, EatZeroDoesNothing_176) {
  auto stream = MakeStream("hello");
  stream->eat(0);
  EXPECT_EQ(stream->peek(), 'h');
}

// Test initial mark values
TEST_F(StreamTest_176, InitialMarkValues_176) {
  auto stream = MakeStream("test");
  EXPECT_EQ(stream->pos(), 0);
  EXPECT_EQ(stream->line(), 0);
  EXPECT_EQ(stream->column(), 0);
}

// Test that line count increases on newline
TEST_F(StreamTest_176, NewlineIncrementsLine_176) {
  auto stream = MakeStream("a\nb");
  stream->get();  // 'a'
  int lineBeforeNewline = stream->line();
  stream->get();  // '\n'
  int lineAfterNewline = stream->line();
  EXPECT_EQ(lineAfterNewline, lineBeforeNewline + 1);
}

// Test that column resets after newline
TEST_F(StreamTest_176, ColumnResetsAfterNewline_176) {
  auto stream = MakeStream("ab\ncd");
  stream->get();  // 'a'
  stream->get();  // 'b'
  stream->get();  // '\n'
  EXPECT_EQ(stream->column(), 0);
  stream->get();  // 'c'
  EXPECT_EQ(stream->column(), 1);
}

// Test eof() static method returns a specific character
TEST_F(StreamTest_176, EofStaticMethod_176) {
  char eofChar = Stream::eof();
  // eof should be a consistent value
  EXPECT_EQ(eofChar, Stream::eof());
}

// Test that reading past end of stream returns eof
TEST_F(StreamTest_176, GetPastEndReturnsEof_176) {
  auto stream = MakeStream("a");
  stream->get();  // 'a'
  char c = stream->get();
  EXPECT_EQ(c, Stream::eof());
}

// Test that peek on exhausted stream returns eof
TEST_F(StreamTest_176, PeekOnExhaustedStreamReturnsEof_176) {
  auto stream = MakeStream("x");
  stream->get();  // 'x'
  EXPECT_EQ(stream->peek(), Stream::eof());
}

// Test stream becomes falsy after all content consumed
TEST_F(StreamTest_176, StreamBecomesFalsyAfterConsuming_176) {
  auto stream = MakeStream("ab");
  stream->get();
  stream->get();
  EXPECT_FALSE(static_cast<bool>(*stream));
}

// Test get(n) when n exceeds available content
TEST_F(StreamTest_176, GetNExceedsContentLength_176) {
  auto stream = MakeStream("hi");
  std::string result = stream->get(10);
  // Should return whatever is available (may include eof chars)
  EXPECT_GE(result.size(), 2u);
  EXPECT_EQ(result[0], 'h');
  EXPECT_EQ(result[1], 'i');
}

// Test ResetColumn
TEST_F(StreamTest_176, ResetColumnResetsToZero_176) {
  auto stream = MakeStream("abcdef");
  stream->get();  // advance column
  stream->get();
  EXPECT_GT(stream->column(), 0);
  stream->ResetColumn();
  EXPECT_EQ(stream->column(), 0);
}

// Test mark() returns Mark struct with correct values
TEST_F(StreamTest_176, MarkReturnsCorrectValues_176) {
  auto stream = MakeStream("test");
  Mark m = stream->mark();
  EXPECT_EQ(m.pos, stream->pos());
  EXPECT_EQ(m.line, stream->line());
  EXPECT_EQ(m.column, stream->column());
}

// Test sequential get(n) calls return correct subsequences
TEST_F(StreamTest_176, SequentialGetNCalls_176) {
  auto stream = MakeStream("abcdefgh");
  std::string first = stream->get(3);
  std::string second = stream->get(3);
  EXPECT_EQ(first, "abc");
  EXPECT_EQ(second, "def");
}

// Test eat followed by get
TEST_F(StreamTest_176, EatThenGet_176) {
  auto stream = MakeStream("abcdef");
  stream->eat(2);
  EXPECT_EQ(stream->get(), 'c');
}

// Test with larger input to exercise prefetch buffer
TEST_F(StreamTest_176, LargerInputPrefetch_176) {
  std::string largeInput(4096, 'A');
  largeInput[4095] = 'Z';
  auto stream = MakeStream(largeInput);
  stream->eat(4095);
  EXPECT_EQ(stream->get(), 'Z');
}

// Test UTF-8 multi-byte character handling (simple BOM-less UTF-8)
TEST_F(StreamTest_176, Utf8MultiByte_176) {
  // UTF-8 encoding of U+00E9 (é) is 0xC3 0xA9
  std::string utf8Input;
  utf8Input += static_cast<char>(0xC3);
  utf8Input += static_cast<char>(0xA9);
  utf8Input += 'a';
  auto stream = MakeStream(utf8Input);
  // The stream should be valid
  EXPECT_TRUE(static_cast<bool>(*stream));
}

// Test with only whitespace
TEST_F(StreamTest_176, WhitespaceOnly_176) {
  auto stream = MakeStream("   ");
  EXPECT_EQ(stream->get(), ' ');
  EXPECT_EQ(stream->get(), ' ');
  EXPECT_EQ(stream->get(), ' ');
  EXPECT_FALSE(static_cast<bool>(*stream));
}

// Test with tab characters
TEST_F(StreamTest_176, TabCharacters_176) {
  auto stream = MakeStream("\t\t");
  char c = stream->get();
  EXPECT_EQ(c, '\t');
}

// Test multiple newlines
TEST_F(StreamTest_176, MultipleNewlines_176) {
  auto stream = MakeStream("\n\n\n");
  stream->get();
  stream->get();
  stream->get();
  EXPECT_EQ(stream->line(), 3);
}

}  // namespace
}  // namespace YAML
