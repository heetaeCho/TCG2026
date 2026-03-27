// TEST_ID: 177
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "stream.h"

namespace {

class StreamEatTest_177 : public ::testing::Test {
 protected:
  static YAML::Stream MakeStream(const std::string& s, std::stringstream& backing) {
    backing.str(s);
    backing.clear();
    return YAML::Stream(backing);
  }
};

TEST_F(StreamEatTest_177, EatZeroDoesNotAdvance_177) {
  std::stringstream ss;
  YAML::Stream stream = MakeStream("abcdef", ss);

  const char before = stream.peek();
  const int pos_before = stream.pos();
  const int line_before = stream.line();
  const int col_before = stream.column();

  stream.eat(0);

  EXPECT_EQ(stream.peek(), before);
  EXPECT_EQ(stream.pos(), pos_before);
  EXPECT_EQ(stream.line(), line_before);
  EXPECT_EQ(stream.column(), col_before);
}

TEST_F(StreamEatTest_177, EatPositiveAdvancesAndNextCharIsExpected_177) {
  std::stringstream ss;
  YAML::Stream stream = MakeStream("abcdef", ss);

  stream.eat(2);

  EXPECT_EQ(stream.peek(), 'c');
  EXPECT_EQ(stream.get(), 'c');  // Also verifies the next consumed character.
  EXPECT_EQ(stream.peek(), 'd');
}

TEST_F(StreamEatTest_177, EatNegativeIsNoOp_177) {
  std::stringstream ss;
  YAML::Stream stream = MakeStream("abcdef", ss);

  const char before = stream.peek();
  const int pos_before = stream.pos();
  const int line_before = stream.line();
  const int col_before = stream.column();

  stream.eat(-3);

  EXPECT_EQ(stream.peek(), before);
  EXPECT_EQ(stream.pos(), pos_before);
  EXPECT_EQ(stream.line(), line_before);
  EXPECT_EQ(stream.column(), col_before);
}

TEST_F(StreamEatTest_177, EatBeyondEndMakesStreamNotGoodOrAtEof_177) {
  std::stringstream ss;
  YAML::Stream stream = MakeStream("ab", ss);

  stream.eat(5);

  // Observable end-of-stream outcomes through the public interface:
  // either the stream becomes falsy, or peek() reports EOF.
  const bool is_good = static_cast<bool>(stream);
  const char p = stream.peek();
  EXPECT_TRUE(!is_good || p == YAML::Stream::eof());
}

TEST_F(StreamEatTest_177, EatMatchesRepeatedGetForPositionAndNextChar_177) {
  const std::string input = "a\nbcdef";
  constexpr int kEat = 3;

  std::stringstream ss1;
  std::stringstream ss2;

  YAML::Stream stream_eat = MakeStream(input, ss1);
  YAML::Stream stream_get = MakeStream(input, ss2);

  stream_eat.eat(kEat);
  for (int i = 0; i < kEat; ++i) {
    (void)stream_get.get();
  }

  EXPECT_EQ(stream_eat.peek(), stream_get.peek());
  EXPECT_EQ(stream_eat.pos(), stream_get.pos());
  EXPECT_EQ(stream_eat.line(), stream_get.line());
  EXPECT_EQ(stream_eat.column(), stream_get.column());
}

}  // namespace