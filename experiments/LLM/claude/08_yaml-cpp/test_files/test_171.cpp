#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "stream.h"

namespace YAML {
namespace {

// ============================================================
// Test Fixture
// ============================================================
class StreamTest_171 : public ::testing::Test {
 protected:
  // Helper to create a Stream from a string
  std::unique_ptr<std::istringstream> MakeISS(const std::string& s) {
    return std::make_unique<std::istringstream>(s);
  }
};

// ============================================================
// Basic Construction and Boolean Operator
// ============================================================

TEST_F(StreamTest_171, EmptyStreamIsFalsy_171) {
  auto iss = MakeISS("");
  Stream stream(*iss);
  // An empty stream should eventually return eof / be falsy
  // peek on empty should give eof
  EXPECT_EQ(Stream::eof(), stream.peek());
}

TEST_F(StreamTest_171, NonEmptyStreamIsTruthy_171) {
  auto iss = MakeISS("hello");
  Stream stream(*iss);
  EXPECT_TRUE(static_cast<bool>(stream));
}

TEST_F(StreamTest_171, BoolOperatorOnEmptyStream_171) {
  auto iss = MakeISS("");
  Stream stream(*iss);
  // After peeking eof, stream may be falsy
  stream.peek();
  EXPECT_FALSE(static_cast<bool>(stream));
}

TEST_F(StreamTest_171, NotOperatorOnEmptyStream_171) {
  auto iss = MakeISS("");
  Stream stream(*iss);
  stream.peek();
  EXPECT_TRUE(!stream);
}

TEST_F(StreamTest_171, NotOperatorOnNonEmptyStream_171) {
  auto iss = MakeISS("a");
  Stream stream(*iss);
  EXPECT_FALSE(!stream);
}

// ============================================================
// Peek
// ============================================================

TEST_F(StreamTest_171, PeekReturnFirstChar_171) {
  auto iss = MakeISS("abc");
  Stream stream(*iss);
  EXPECT_EQ('a', stream.peek());
}

TEST_F(StreamTest_171, PeekDoesNotConsume_171) {
  auto iss = MakeISS("abc");
  Stream stream(*iss);
  EXPECT_EQ('a', stream.peek());
  EXPECT_EQ('a', stream.peek());
}

TEST_F(StreamTest_171, PeekOnEmptyReturnsEof_171) {
  auto iss = MakeISS("");
  Stream stream(*iss);
  EXPECT_EQ(Stream::eof(), stream.peek());
}

// ============================================================
// Get (single character)
// ============================================================

TEST_F(StreamTest_171, GetReturnFirstChar_171) {
  auto iss = MakeISS("abc");
  Stream stream(*iss);
  EXPECT_EQ('a', stream.get());
}

TEST_F(StreamTest_171, GetConsumesCharacter_171) {
  auto iss = MakeISS("abc");
  Stream stream(*iss);
  stream.get();
  EXPECT_EQ('b', stream.peek());
}

TEST_F(StreamTest_171, GetAllCharacters_171) {
  auto iss = MakeISS("xyz");
  Stream stream(*iss);
  EXPECT_EQ('x', stream.get());
  EXPECT_EQ('y', stream.get());
  EXPECT_EQ('z', stream.get());
  EXPECT_EQ(Stream::eof(), stream.peek());
}

TEST_F(StreamTest_171, GetOnEmptyReturnsEof_171) {
  auto iss = MakeISS("");
  Stream stream(*iss);
  EXPECT_EQ(Stream::eof(), stream.get());
}

// ============================================================
// Get (n characters)
// ============================================================

TEST_F(StreamTest_171, GetNReturnsSubstring_171) {
  auto iss = MakeISS("abcdef");
  Stream stream(*iss);
  std::string result = stream.get(3);
  EXPECT_EQ("abc", result);
}

TEST_F(StreamTest_171, GetNConsumesNCharacters_171) {
  auto iss = MakeISS("abcdef");
  Stream stream(*iss);
  stream.get(3);
  EXPECT_EQ('d', stream.peek());
}

TEST_F(StreamTest_171, GetNZero_171) {
  auto iss = MakeISS("abc");
  Stream stream(*iss);
  std::string result = stream.get(0);
  EXPECT_EQ("", result);
  EXPECT_EQ('a', stream.peek());
}

TEST_F(StreamTest_171, GetNEntireStream_171) {
  auto iss = MakeISS("hello");
  Stream stream(*iss);
  std::string result = stream.get(5);
  EXPECT_EQ("hello", result);
  EXPECT_EQ(Stream::eof(), stream.peek());
}

TEST_F(StreamTest_171, GetNMoreThanAvailable_171) {
  auto iss = MakeISS("hi");
  Stream stream(*iss);
  std::string result = stream.get(10);
  // Should return what's available (possibly with eof chars)
  EXPECT_FALSE(result.empty());
}

// ============================================================
// Eat
// ============================================================

TEST_F(StreamTest_171, EatConsumesCharacters_171) {
  auto iss = MakeISS("abcdef");
  Stream stream(*iss);
  stream.eat(3);
  EXPECT_EQ('d', stream.peek());
}

TEST_F(StreamTest_171, EatZero_171) {
  auto iss = MakeISS("abc");
  Stream stream(*iss);
  stream.eat(0);
  EXPECT_EQ('a', stream.peek());
}

TEST_F(StreamTest_171, EatEntireStream_171) {
  auto iss = MakeISS("abc");
  Stream stream(*iss);
  stream.eat(3);
  EXPECT_EQ(Stream::eof(), stream.peek());
}

// ============================================================
// Mark / Position Tracking
// ============================================================

TEST_F(StreamTest_171, InitialPositionIsZero_171) {
  auto iss = MakeISS("abc");
  Stream stream(*iss);
  EXPECT_EQ(0, stream.pos());
}

TEST_F(StreamTest_171, InitialLineIsZero_171) {
  auto iss = MakeISS("abc");
  Stream stream(*iss);
  EXPECT_EQ(0, stream.line());
}

TEST_F(StreamTest_171, InitialColumnIsZero_171) {
  auto iss = MakeISS("abc");
  Stream stream(*iss);
  EXPECT_EQ(0, stream.column());
}

TEST_F(StreamTest_171, PositionAdvancesOnGet_171) {
  auto iss = MakeISS("abc");
  Stream stream(*iss);
  stream.get();
  EXPECT_EQ(1, stream.pos());
}

TEST_F(StreamTest_171, ColumnAdvancesOnGet_171) {
  auto iss = MakeISS("abc");
  Stream stream(*iss);
  stream.get();
  EXPECT_EQ(1, stream.column());
}

TEST_F(StreamTest_171, LineAdvancesOnNewline_171) {
  auto iss = MakeISS("a\nb");
  Stream stream(*iss);
  stream.get();  // 'a'
  stream.get();  // '\n'
  EXPECT_EQ(1, stream.line());
}

TEST_F(StreamTest_171, ColumnResetsOnNewline_171) {
  auto iss = MakeISS("a\nb");
  Stream stream(*iss);
  stream.get();  // 'a'
  stream.get();  // '\n'
  EXPECT_EQ(0, stream.column());
}

TEST_F(StreamTest_171, MarkReflectsPosition_171) {
  auto iss = MakeISS("abc");
  Stream stream(*iss);
  stream.get();
  stream.get();
  Mark m = stream.mark();
  EXPECT_EQ(2, m.pos);
  EXPECT_EQ(0, m.line);
  EXPECT_EQ(2, m.column);
}

TEST_F(StreamTest_171, ResetColumnResetsToZero_171) {
  auto iss = MakeISS("abcdef");
  Stream stream(*iss);
  stream.get();
  stream.get();
  stream.get();
  EXPECT_EQ(3, stream.column());
  stream.ResetColumn();
  EXPECT_EQ(0, stream.column());
}

// ============================================================
// EOF static method
// ============================================================

TEST_F(StreamTest_171, EofIsConsistent_171) {
  char eof1 = Stream::eof();
  char eof2 = Stream::eof();
  EXPECT_EQ(eof1, eof2);
}

// ============================================================
// Multi-line tracking
// ============================================================

TEST_F(StreamTest_171, MultipleNewlines_171) {
  auto iss = MakeISS("a\nb\nc");
  Stream stream(*iss);
  stream.get();  // 'a'
  stream.get();  // '\n'
  stream.get();  // 'b'
  stream.get();  // '\n'
  EXPECT_EQ(2, stream.line());
  EXPECT_EQ(0, stream.column());
  EXPECT_EQ('c', stream.peek());
}

TEST_F(StreamTest_171, CarriageReturnLineFeed_171) {
  auto iss = MakeISS("a\r\nb");
  Stream stream(*iss);
  stream.get();  // 'a'
  stream.get();  // '\r' or processed as newline
  // After consuming the line ending, we should be on line 1
  // The exact behavior depends on implementation, but line should advance
  char c = stream.get();  // could be '\n' or 'b' depending on CRLF handling
  // Just verify we can read 'b' eventually
  if (c != 'b') {
    c = stream.get();
  }
  EXPECT_EQ('b', c);
}

// ============================================================
// UTF-8 handling
// ============================================================

TEST_F(StreamTest_171, SimpleAsciiStream_171) {
  auto iss = MakeISS("Hello, World!");
  Stream stream(*iss);
  std::string result = stream.get(13);
  EXPECT_EQ("Hello, World!", result);
}

TEST_F(StreamTest_171, Utf8TwoByteCharacter_171) {
  // é is U+00E9, encoded as 0xC3 0xA9 in UTF-8
  std::string input = "\xC3\xA9";
  auto iss = MakeISS(input);
  Stream stream(*iss);
  // Should be able to read something without crashing
  char c = stream.get();
  EXPECT_NE(Stream::eof(), c);
}

TEST_F(StreamTest_171, Utf8ThreeByteCharacter_171) {
  // € is U+20AC, encoded as 0xE2 0x82 0xAC in UTF-8
  std::string input = "\xE2\x82\xAC";
  auto iss = MakeISS(input);
  Stream stream(*iss);
  EXPECT_TRUE(static_cast<bool>(stream));
  // Read through the character
  while (static_cast<bool>(stream)) {
    stream.get();
  }
}

TEST_F(StreamTest_171, Utf8FourByteCharacter_171) {
  // 𝄞 is U+1D11E, encoded as 0xF0 0x9D 0x84 0x9E in UTF-8
  std::string input = "\xF0\x9D\x84\x9E";
  auto iss = MakeISS(input);
  Stream stream(*iss);
  EXPECT_TRUE(static_cast<bool>(stream));
}

// ============================================================
// Large input
// ============================================================

TEST_F(StreamTest_171, LargeInput_171) {
  std::string large(4096, 'x');
  auto iss = MakeISS(large);
  Stream stream(*iss);
  for (int i = 0; i < 4096; ++i) {
    EXPECT_EQ('x', stream.get());
  }
  EXPECT_EQ(Stream::eof(), stream.peek());
}

// ============================================================
// Interleaved peek and get
// ============================================================

TEST_F(StreamTest_171, InterleavedPeekAndGet_171) {
  auto iss = MakeISS("abcd");
  Stream stream(*iss);
  EXPECT_EQ('a', stream.peek());
  EXPECT_EQ('a', stream.get());
  EXPECT_EQ('b', stream.peek());
  EXPECT_EQ('b', stream.peek());
  EXPECT_EQ('b', stream.get());
  EXPECT_EQ('c', stream.get());
  EXPECT_EQ('d', stream.peek());
  EXPECT_EQ('d', stream.get());
  EXPECT_EQ(Stream::eof(), stream.peek());
}

// ============================================================
// Eat followed by get
// ============================================================

TEST_F(StreamTest_171, EatThenGet_171) {
  auto iss = MakeISS("abcdef");
  Stream stream(*iss);
  stream.eat(2);
  EXPECT_EQ('c', stream.get());
}

TEST_F(StreamTest_171, EatThenGetN_171) {
  auto iss = MakeISS("abcdef");
  Stream stream(*iss);
  stream.eat(2);
  std::string result = stream.get(3);
  EXPECT_EQ("cde", result);
}

// ============================================================
// Position tracking with eat
// ============================================================

TEST_F(StreamTest_171, PositionAfterEat_171) {
  auto iss = MakeISS("abcdef");
  Stream stream(*iss);
  stream.eat(4);
  EXPECT_EQ(4, stream.pos());
  EXPECT_EQ(4, stream.column());
}

// ============================================================
// Single character stream
// ============================================================

TEST_F(StreamTest_171, SingleCharStream_171) {
  auto iss = MakeISS("X");
  Stream stream(*iss);
  EXPECT_TRUE(static_cast<bool>(stream));
  EXPECT_EQ('X', stream.peek());
  EXPECT_EQ('X', stream.get());
  EXPECT_EQ(Stream::eof(), stream.peek());
  EXPECT_FALSE(static_cast<bool>(stream));
}

// ============================================================
// Newline only stream
// ============================================================

TEST_F(StreamTest_171, NewlineOnlyStream_171) {
  auto iss = MakeISS("\n");
  Stream stream(*iss);
  EXPECT_EQ('\n', stream.get());
  EXPECT_EQ(1, stream.line());
  EXPECT_EQ(0, stream.column());
}

// ============================================================
// Tab character
// ============================================================

TEST_F(StreamTest_171, TabCharacter_171) {
  auto iss = MakeISS("\tabc");
  Stream stream(*iss);
  char c = stream.get();
  EXPECT_EQ('\t', c);
  EXPECT_EQ('a', stream.peek());
}

// ============================================================
// GetN with value 1
// ============================================================

TEST_F(StreamTest_171, GetNOne_171) {
  auto iss = MakeISS("abc");
  Stream stream(*iss);
  std::string result = stream.get(1);
  EXPECT_EQ("a", result);
  EXPECT_EQ('b', stream.peek());
}

}  // namespace
}  // namespace YAML
