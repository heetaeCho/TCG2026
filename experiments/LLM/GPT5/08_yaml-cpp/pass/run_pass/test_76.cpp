// TEST_ID: 76
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "stream.h"  // YAML::Stream

namespace {

class StreamTest_76 : public ::testing::Test {};

TEST_F(StreamTest_76, InitialLineIsZero_76) {
  std::istringstream input("");
  YAML::Stream stream(input);

  EXPECT_EQ(stream.line(), 0);
}

TEST_F(StreamTest_76, LineDoesNotChangeWithoutNewlines_76) {
  std::istringstream input("abcdef");
  YAML::Stream stream(input);

  EXPECT_EQ(stream.line(), 0);

  // Consume a few chars; line should remain unchanged.
  (void)stream.get();
  EXPECT_EQ(stream.line(), 0);
  (void)stream.get();
  EXPECT_EQ(stream.line(), 0);
  (void)stream.get();
  EXPECT_EQ(stream.line(), 0);
}

TEST_F(StreamTest_76, LineIncrementsAfterConsumingLfNewline_76) {
  std::istringstream input("a\nb");
  YAML::Stream stream(input);

  EXPECT_EQ(stream.line(), 0);

  EXPECT_EQ(stream.get(), 'a');
  EXPECT_EQ(stream.line(), 0);

  EXPECT_EQ(stream.get(), '\n');
  EXPECT_EQ(stream.line(), 1);

  EXPECT_EQ(stream.get(), 'b');
  EXPECT_EQ(stream.line(), 1);
}

TEST_F(StreamTest_76, EatAcrossLfNewlineUpdatesLine_76) {
  std::istringstream input("ab\ncd");
  YAML::Stream stream(input);

  EXPECT_EQ(stream.line(), 0);

  stream.eat(2);  // "ab"
  EXPECT_EQ(stream.line(), 0);

  stream.eat(1);  // "\n"
  EXPECT_EQ(stream.line(), 1);

  stream.eat(2);  // "cd"
  EXPECT_EQ(stream.line(), 1);
}

TEST_F(StreamTest_76, GetNThatIncludesLfNewlineUpdatesLine_76) {
  std::istringstream input("a\nb");
  YAML::Stream stream(input);

  EXPECT_EQ(stream.line(), 0);

  const std::string got = stream.get(2);  // should consume 'a' and '\n'
  EXPECT_EQ(got.size(), 2u);
  EXPECT_EQ(got[0], 'a');
  EXPECT_EQ(got[1], '\n');

  EXPECT_EQ(stream.line(), 1);
}

TEST_F(StreamTest_76, WindowsCrlfCountsAsSingleLineBreakAfterConsumingBoth_76) {
  std::istringstream input(std::string("a\r\nb"));
  YAML::Stream stream(input);

  EXPECT_EQ(stream.line(), 0);

  const std::string got = stream.get(3);  // 'a', '\r', '\n'
  ASSERT_EQ(got.size(), 3u);
  EXPECT_EQ(got[0], 'a');
  EXPECT_EQ(got[1], '\r');
  EXPECT_EQ(got[2], '\n');

  // Observable requirement: after consuming a CRLF sequence, line should advance by one.
  EXPECT_EQ(stream.line(), 1);

  EXPECT_EQ(stream.get(), 'b');
  EXPECT_EQ(stream.line(), 1);
}

TEST_F(StreamTest_76, ResetColumnDoesNotChangeLine_76) {
  std::istringstream input("x\ny");
  YAML::Stream stream(input);

  EXPECT_EQ(stream.line(), 0);
  (void)stream.get();       // 'x'
  EXPECT_EQ(stream.line(), 0);
  (void)stream.get();       // '\n'
  EXPECT_EQ(stream.line(), 1);

  stream.ResetColumn();
  EXPECT_EQ(stream.line(), 1);

  (void)stream.get();       // 'y'
  EXPECT_EQ(stream.line(), 1);
}

TEST_F(StreamTest_76, LineDoesNotChangeAfterEofAndExtraReads_76) {
  std::istringstream input("a\n");
  YAML::Stream stream(input);

  EXPECT_EQ(stream.line(), 0);

  (void)stream.get();  // 'a'
  EXPECT_EQ(stream.line(), 0);
  (void)stream.get();  // '\n'
  EXPECT_EQ(stream.line(), 1);

  // Consume past available content (observable via interface: repeated gets shouldn't change line).
  (void)stream.get();
  const int line_after_first_past_end = stream.line();
  (void)stream.get();
  EXPECT_EQ(stream.line(), line_after_first_past_end);
}

}  // namespace
