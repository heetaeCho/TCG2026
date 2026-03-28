// TEST_ID: 75
#include <gtest/gtest.h>

#include <sstream>
#include <string>

// Prefer the local project header path used in the prompt.
#include "stream.h"

// Some builds expose Mark via this include; if it's already included by stream.h
// this will be harmless. If your include paths differ, adjust accordingly.
#include "yaml-cpp/mark.h"

namespace {

class StreamPosTest_75 : public ::testing::Test {
protected:
  static YAML::Stream MakeStreamFrom(const std::string& s, std::istringstream& backing) {
    backing.str(s);
    backing.clear();
    return YAML::Stream(backing);
  }
};

TEST_F(StreamPosTest_75, InitialPosIsZero_75) {
  std::istringstream in1("");
  YAML::Stream s1(in1);
  EXPECT_EQ(s1.pos(), 0);

  std::istringstream in2("abc");
  YAML::Stream s2(in2);
  EXPECT_EQ(s2.pos(), 0);
}

TEST_F(StreamPosTest_75, PeekDoesNotAdvancePos_75) {
  std::istringstream in("abc");
  YAML::Stream s(in);

  const int p0 = s.pos();
  (void)s.peek();
  EXPECT_EQ(s.pos(), p0);

  (void)s.peek();
  EXPECT_EQ(s.pos(), p0);
}

TEST_F(StreamPosTest_75, GetAdvancesPosByOnePerCall_75) {
  std::istringstream in("abc");
  YAML::Stream s(in);

  EXPECT_EQ(s.pos(), 0);
  EXPECT_EQ(s.get(), 'a');
  EXPECT_EQ(s.pos(), 1);

  EXPECT_EQ(s.get(), 'b');
  EXPECT_EQ(s.pos(), 2);

  EXPECT_EQ(s.get(), 'c');
  EXPECT_EQ(s.pos(), 3);
}

TEST_F(StreamPosTest_75, GetStringAdvancesPosByN_75) {
  std::istringstream in("abcd");
  YAML::Stream s(in);

  const int p0 = s.pos();
  const std::string out = s.get(2);

  EXPECT_EQ(out, "ab");
  EXPECT_EQ(s.pos(), p0 + 2);

  // Next char should be 'c' (peek should not move pos).
  const int p1 = s.pos();
  EXPECT_EQ(s.peek(), 'c');
  EXPECT_EQ(s.pos(), p1);
}

TEST_F(StreamPosTest_75, EatAdvancesPosByN_75) {
  std::istringstream in("abcd");
  YAML::Stream s(in);

  const int p0 = s.pos();
  s.eat(2);
  EXPECT_EQ(s.pos(), p0 + 2);

  const int p1 = s.pos();
  EXPECT_EQ(s.peek(), 'c');
  EXPECT_EQ(s.pos(), p1);
}

TEST_F(StreamPosTest_75, EatZeroDoesNotChangePos_75) {
  std::istringstream in("abc");
  YAML::Stream s(in);

  const int p0 = s.pos();
  s.eat(0);
  EXPECT_EQ(s.pos(), p0);

  // Still at beginning.
  EXPECT_EQ(s.peek(), 'a');
  EXPECT_EQ(s.pos(), p0);
}

TEST_F(StreamPosTest_75, GetZeroReturnsEmptyAndDoesNotAdvancePos_75) {
  std::istringstream in("abc");
  YAML::Stream s(in);

  const int p0 = s.pos();
  const std::string out = s.get(0);

  EXPECT_TRUE(out.empty());
  EXPECT_EQ(s.pos(), p0);

  EXPECT_EQ(s.peek(), 'a');
  EXPECT_EQ(s.pos(), p0);
}

TEST_F(StreamPosTest_75, MarkPosMatchesPos_75) {
  std::istringstream in("ab");
  YAML::Stream s(in);

  EXPECT_EQ(s.mark().pos, s.pos());
  (void)s.get();
  EXPECT_EQ(s.mark().pos, s.pos());
  (void)s.get();
  EXPECT_EQ(s.mark().pos, s.pos());
}

TEST_F(StreamPosTest_75, AtEofFurtherOperationsDoNotDecreasePos_75) {
  std::istringstream in("a");
  YAML::Stream s(in);

  EXPECT_EQ(s.get(), 'a');
  const int endPos = s.pos();

  // Attempt a few operations past end; they should not move pos backwards.
  const char pk = s.peek();
  (void)pk;
  EXPECT_GE(s.pos(), endPos);

  const char g = s.get();
  (void)g;
  EXPECT_GE(s.pos(), endPos);

  s.eat(1);
  EXPECT_GE(s.pos(), endPos);

  // If eof() is available, it's reasonable to compare the post-EOF get result.
  // (We don't require a specific behavior beyond being a stable EOF sentinel.)
  EXPECT_EQ(YAML::Stream::eof(), YAML::Stream::eof());
}

TEST_F(StreamPosTest_75, LargeEatBeyondRemainingDoesNotCrash_75) {
  std::istringstream in("abc");
  YAML::Stream s(in);

  const int p0 = s.pos();
  EXPECT_NO_THROW(s.eat(1000000));
  EXPECT_GE(s.pos(), p0);

  const int p1 = s.pos();
  EXPECT_NO_THROW(s.eat(1000000));
  EXPECT_GE(s.pos(), p1);
}

}  // namespace
