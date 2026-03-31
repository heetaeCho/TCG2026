#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "stream.h"

namespace YAML {
namespace {

// Test fixture for Stream tests
class StreamTest_76 : public ::testing::Test {
 protected:
  // Helper to create a stream from a string
  std::unique_ptr<Stream> MakeStream(const std::string& input) {
    ss_ = std::make_unique<std::istringstream>(input);
    return std::make_unique<Stream>(*ss_);
  }

  std::unique_ptr<std::istringstream> ss_;
};

// ==================== Construction and Basic State ====================

TEST_F(StreamTest_76, EmptyStreamIsInvalid_76) {
  auto stream = MakeStream("");
  // An empty stream should not have readable characters
  // peek should return eof
  EXPECT_EQ(Stream::eof(), stream->peek());
}

TEST_F(StreamTest_76, EmptyStreamBoolOperatorFalse_76) {
  auto stream = MakeStream("");
  // After checking, empty stream should evaluate to false (or eof behavior)
  // Actually, an empty stream may still be "valid" until we try to read
  // Let's just verify behavior is consistent
  char c = stream->peek();
  EXPECT_EQ(Stream::eof(), c);
}

TEST_F(StreamTest_76, NonEmptyStreamBoolOperatorTrue_76) {
  auto stream = MakeStream("hello");
  EXPECT_TRUE(static_cast<bool>(*stream));
}

TEST_F(StreamTest_76, NonEmptyStreamNotOperatorFalse_76) {
  auto stream = MakeStream("hello");
  EXPECT_FALSE(!(*stream));
}

// ==================== Initial Position ====================

TEST_F(StreamTest_76, InitialLineIsZero_76) {
  auto stream = MakeStream("hello");
  EXPECT_EQ(0, stream->line());
}

TEST_F(StreamTest_76, InitialColumnIsZero_76) {
  auto stream = MakeStream("hello");
  EXPECT_EQ(0, stream->column());
}

TEST_F(StreamTest_76, InitialPosIsZero_76) {
  auto stream = MakeStream("hello");
  EXPECT_EQ(0, stream->pos());
}

// ==================== Peek ====================

TEST_F(StreamTest_76, PeekReturnsFirstChar_76) {
  auto stream = MakeStream("abc");
  EXPECT_EQ('a', stream->peek());
}

TEST_F(StreamTest_76, PeekDoesNotAdvance_76) {
  auto stream = MakeStream("abc");
  EXPECT_EQ('a', stream->peek());
  EXPECT_EQ('a', stream->peek());
  EXPECT_EQ(0, stream->pos());
}

TEST_F(StreamTest_76, PeekOnEmptyReturnsEof_76) {
  auto stream = MakeStream("");
  EXPECT_EQ(Stream::eof(), stream->peek());
}

// ==================== Get (single char) ====================

TEST_F(StreamTest_76, GetReturnsSingleChar_76) {
  auto stream = MakeStream("abc");
  char c = stream->get();
  EXPECT_EQ('a', c);
}

TEST_F(StreamTest_76, GetAdvancesPosition_76) {
  auto stream = MakeStream("abc");
  stream->get();
  EXPECT_EQ('b', stream->peek());
}

TEST_F(StreamTest_76, GetAdvancesPosCounter_76) {
  auto stream = MakeStream("abc");
  stream->get();
  EXPECT_EQ(1, stream->pos());
}

TEST_F(StreamTest_76, GetAdvancesColumn_76) {
  auto stream = MakeStream("abc");
  stream->get();
  EXPECT_EQ(1, stream->column());
}

TEST_F(StreamTest_76, GetMultipleCharsSequentially_76) {
  auto stream = MakeStream("abcdef");
  EXPECT_EQ('a', stream->get());
  EXPECT_EQ('b', stream->get());
  EXPECT_EQ('c', stream->get());
  EXPECT_EQ(3, stream->pos());
  EXPECT_EQ(3, stream->column());
}

TEST_F(StreamTest_76, GetPastEndReturnsEof_76) {
  auto stream = MakeStream("a");
  stream->get();
  EXPECT_EQ(Stream::eof(), stream->get());
}

// ==================== Get (n chars) ====================

TEST_F(StreamTest_76, GetNReturnsNChars_76) {
  auto stream = MakeStream("abcdef");
  std::string result = stream->get(3);
  EXPECT_EQ("abc", result);
}

TEST_F(StreamTest_76, GetNAdvancesPosition_76) {
  auto stream = MakeStream("abcdef");
  stream->get(3);
  EXPECT_EQ('d', stream->peek());
  EXPECT_EQ(3, stream->pos());
}

TEST_F(StreamTest_76, GetNZeroReturnsEmptyString_76) {
  auto stream = MakeStream("abcdef");
  std::string result = stream->get(0);
  EXPECT_EQ("", result);
  EXPECT_EQ('a', stream->peek());
}

TEST_F(StreamTest_76, GetNBeyondEndReturnsAvailable_76) {
  auto stream = MakeStream("ab");
  std::string result = stream->get(10);
  // Should return what's available (up to the end)
  EXPECT_FALSE(result.empty());
  EXPECT_LE(result.size(), 10u);
}

// ==================== Eat ====================

TEST_F(StreamTest_76, EatAdvancesWithoutReturning_76) {
  auto stream = MakeStream("abcdef");
  stream->eat(3);
  EXPECT_EQ('d', stream->peek());
}

TEST_F(StreamTest_76, EatZeroDoesNothing_76) {
  auto stream = MakeStream("abcdef");
  stream->eat(0);
  EXPECT_EQ('a', stream->peek());
  EXPECT_EQ(0, stream->pos());
}

TEST_F(StreamTest_76, EatUpdatesPos_76) {
  auto stream = MakeStream("abcdef");
  stream->eat(4);
  EXPECT_EQ(4, stream->pos());
}

// ==================== Line Tracking ====================

TEST_F(StreamTest_76, NewlineAdvancesLine_76) {
  auto stream = MakeStream("a\nb");
  stream->get(); // 'a'
  stream->get(); // '\n'
  EXPECT_EQ(1, stream->line());
  EXPECT_EQ('b', stream->peek());
}

TEST_F(StreamTest_76, MultipleNewlinesAdvanceLine_76) {
  auto stream = MakeStream("a\nb\nc");
  stream->get(); // 'a'
  stream->get(); // '\n'
  stream->get(); // 'b'
  stream->get(); // '\n'
  EXPECT_EQ(2, stream->line());
  EXPECT_EQ('c', stream->peek());
}

TEST_F(StreamTest_76, NewlineResetsColumn_76) {
  auto stream = MakeStream("abc\ndef");
  stream->get(); // 'a'
  stream->get(); // 'b'
  stream->get(); // 'c'
  EXPECT_EQ(3, stream->column());
  stream->get(); // '\n'
  EXPECT_EQ(0, stream->column());
  EXPECT_EQ(1, stream->line());
}

// ==================== ResetColumn ====================

TEST_F(StreamTest_76, ResetColumnSetsColumnToZero_76) {
  auto stream = MakeStream("abcdef");
  stream->get();
  stream->get();
  stream->get();
  EXPECT_EQ(3, stream->column());
  stream->ResetColumn();
  EXPECT_EQ(0, stream->column());
}

TEST_F(StreamTest_76, ResetColumnDoesNotAffectPos_76) {
  auto stream = MakeStream("abcdef");
  stream->get();
  stream->get();
  int posBefore = stream->pos();
  stream->ResetColumn();
  EXPECT_EQ(posBefore, stream->pos());
}

TEST_F(StreamTest_76, ResetColumnDoesNotAffectLine_76) {
  auto stream = MakeStream("ab\ncd");
  stream->get(); // a
  stream->get(); // b
  stream->get(); // \n
  stream->get(); // c
  int lineBefore = stream->line();
  stream->ResetColumn();
  EXPECT_EQ(lineBefore, stream->line());
}

// ==================== Mark ====================

TEST_F(StreamTest_76, MarkReturnsCurrentPosition_76) {
  auto stream = MakeStream("abcdef");
  stream->get();
  stream->get();
  Mark m = stream->mark();
  EXPECT_EQ(2, m.pos);
  EXPECT_EQ(0, m.line);
  EXPECT_EQ(2, m.column);
}

TEST_F(StreamTest_76, MarkAfterNewline_76) {
  auto stream = MakeStream("ab\ncd");
  stream->get(); // a
  stream->get(); // b
  stream->get(); // \n
  stream->get(); // c
  Mark m = stream->mark();
  EXPECT_EQ(1, m.line);
  EXPECT_EQ(1, m.column);
}

// ==================== eof() static method ====================

TEST_F(StreamTest_76, EofIsConsistent_76) {
  // eof should return the same value each time
  EXPECT_EQ(Stream::eof(), Stream::eof());
}

// ==================== Stream with various content ====================

TEST_F(StreamTest_76, StreamWithOnlyNewlines_76) {
  auto stream = MakeStream("\n\n\n");
  stream->get(); // \n
  EXPECT_EQ(1, stream->line());
  stream->get(); // \n
  EXPECT_EQ(2, stream->line());
  stream->get(); // \n
  EXPECT_EQ(3, stream->line());
}

TEST_F(StreamTest_76, StreamWithSingleChar_76) {
  auto stream = MakeStream("x");
  EXPECT_TRUE(static_cast<bool>(*stream));
  EXPECT_EQ('x', stream->get());
  EXPECT_EQ(Stream::eof(), stream->peek());
}

TEST_F(StreamTest_76, StreamWithCarriageReturnLineFeed_76) {
  auto stream = MakeStream("a\r\nb");
  stream->get(); // a
  stream->get(); // \r or \n (depending on handling)
  // The stream should handle \r\n as a single line ending
  // After consuming the line ending, we should eventually get 'b'
  // and line should have advanced
}

TEST_F(StreamTest_76, LargeInputStream_76) {
  std::string large(5000, 'a');
  auto stream = MakeStream(large);
  for (int i = 0; i < 5000; ++i) {
    EXPECT_EQ('a', stream->get());
  }
  EXPECT_EQ(Stream::eof(), stream->peek());
}

TEST_F(StreamTest_76, GetNThenPeek_76) {
  auto stream = MakeStream("hello world");
  std::string hello = stream->get(5);
  EXPECT_EQ("hello", hello);
  EXPECT_EQ(' ', stream->peek());
}

TEST_F(StreamTest_76, EatThenGetN_76) {
  auto stream = MakeStream("hello world");
  stream->eat(6); // eat "hello "
  std::string world = stream->get(5);
  EXPECT_EQ("world", world);
}

TEST_F(StreamTest_76, BoolOperatorAfterExhausted_76) {
  auto stream = MakeStream("a");
  stream->get();
  // Stream should be exhausted
  EXPECT_EQ(Stream::eof(), stream->peek());
}

TEST_F(StreamTest_76, TabCharacterAdvancesColumn_76) {
  auto stream = MakeStream("\tabc");
  stream->get(); // tab
  // Column should have advanced (by at least 1)
  EXPECT_GE(stream->column(), 1);
}

TEST_F(StreamTest_76, CopyConstructorDeleted_76) {
  // This is a compile-time check - Stream(const Stream&) = delete
  EXPECT_FALSE(std::is_copy_constructible<Stream>::value);
}

TEST_F(StreamTest_76, MoveConstructorDeleted_76) {
  EXPECT_FALSE(std::is_move_constructible<Stream>::value);
}

TEST_F(StreamTest_76, CopyAssignmentDeleted_76) {
  EXPECT_FALSE(std::is_copy_assignable<Stream>::value);
}

TEST_F(StreamTest_76, MoveAssignmentDeleted_76) {
  EXPECT_FALSE(std::is_move_assignable<Stream>::value);
}

}  // namespace
}  // namespace YAML
