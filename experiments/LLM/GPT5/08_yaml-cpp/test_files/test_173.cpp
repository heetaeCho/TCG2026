// TEST_ID: 173
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "stream.h"

namespace {

class StreamPeekTest_173 : public ::testing::Test {
 protected:
  static YAML::Stream MakeStream(const std::string& input) {
    // YAML::Stream takes a non-owning reference to the std::istream.
    // Keep the stream alive in each test (as a local variable) and construct Stream from it.
    std::istringstream iss(input);
    YAML::Stream s(iss);
    // NOTE: Returning by value would try to copy/move (deleted). So this helper is unused.
    // Kept intentionally to document lifetime requirements.
    return s;
  }
};

}  // namespace

TEST_F(StreamPeekTest_173, PeekOnEmptyInputReturnsEof_173) {
  std::istringstream iss("");
  YAML::Stream stream(iss);

  EXPECT_EQ(stream.peek(), YAML::Stream::eof());
  EXPECT_EQ(stream.peek(), YAML::Stream::eof());  // repeated peek stays EOF
}

TEST_F(StreamPeekTest_173, PeekDoesNotConsumeCharacter_173) {
  std::istringstream iss("abc");
  YAML::Stream stream(iss);

  const char p = stream.peek();
  ASSERT_NE(p, YAML::Stream::eof());

  const char g = stream.get();
  EXPECT_EQ(g, p) << "peek() should not consume; get() should return the same first character";
}

TEST_F(StreamPeekTest_173, MultiplePeeksReturnSameValueUntilConsumed_173) {
  std::istringstream iss("abc");
  YAML::Stream stream(iss);

  const char p1 = stream.peek();
  const char p2 = stream.peek();
  EXPECT_EQ(p1, p2);

  (void)stream.get();  // consume one character

  const char p3 = stream.peek();
  // If there was at least 2 chars, the next peek should not equal the first.
  EXPECT_NE(p3, p1);
}

TEST_F(StreamPeekTest_173, PeekTracksPositionAfterGet_173) {
  std::istringstream iss("abc");
  YAML::Stream stream(iss);

  EXPECT_EQ(stream.peek(), 'a');
  EXPECT_EQ(stream.get(), 'a');

  EXPECT_EQ(stream.peek(), 'b');
  EXPECT_EQ(stream.get(), 'b');

  EXPECT_EQ(stream.peek(), 'c');
  EXPECT_EQ(stream.get(), 'c');

  EXPECT_EQ(stream.peek(), YAML::Stream::eof());
}

TEST_F(StreamPeekTest_173, SingleCharacterInputTransitionsToEof_173) {
  std::istringstream iss("x");
  YAML::Stream stream(iss);

  EXPECT_EQ(stream.peek(), 'x');
  EXPECT_EQ(stream.get(), 'x');
  EXPECT_EQ(stream.peek(), YAML::Stream::eof());
}

TEST_F(StreamPeekTest_173, PeekReflectsEatAdvancingTheStream_173) {
  std::istringstream iss("abc");
  YAML::Stream stream(iss);

  EXPECT_EQ(stream.peek(), 'a');

  stream.eat(1);  // advance by one
  EXPECT_EQ(stream.peek(), 'b');

  stream.eat(2);  // advance past remaining chars ("b","c")
  EXPECT_EQ(stream.peek(), YAML::Stream::eof());
}

TEST_F(StreamPeekTest_173, PeekWorksWithGetNAndDoesNotSkipUnexpectedly_173) {
  std::istringstream iss("abcd");
  YAML::Stream stream(iss);

  EXPECT_EQ(stream.peek(), 'a');

  const std::string first2 = stream.get(2);
  EXPECT_EQ(first2.size(), 2u);
  EXPECT_EQ(first2[0], 'a');
  EXPECT_EQ(first2[1], 'b');

  EXPECT_EQ(stream.peek(), 'c');

  const std::string rest = stream.get(10);  // request more than remains
  // We don't assume exact behavior beyond observable consistency:
  // - Whatever is returned, the stream should eventually be at EOF.
  EXPECT_EQ(stream.peek(), YAML::Stream::eof());
}

TEST_F(StreamPeekTest_173, PeekAtEofRemainsEofAfterAdditionalOperations_173) {
  std::istringstream iss("");
  YAML::Stream stream(iss);

  EXPECT_EQ(stream.peek(), YAML::Stream::eof());

  // Exercising other public APIs at EOF should not make peek return non-EOF.
  stream.eat(0);
  EXPECT_EQ(stream.peek(), YAML::Stream::eof());

  const std::string s = stream.get(1);
  (void)s;
  EXPECT_EQ(stream.peek(), YAML::Stream::eof());
}