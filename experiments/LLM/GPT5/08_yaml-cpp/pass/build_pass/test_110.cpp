// File: ./TestProjects/yaml-cpp/test/regeximpl_matches_stream_test_110.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "regex_yaml.h"
#include "stream.h"

namespace {

struct StreamHolder_110 {
  explicit StreamHolder_110(const std::string& s) : iss(s), stream(iss) {}
  std::istringstream iss;
  YAML::Stream stream;
};

}  // namespace

class RegExImplTest_110 : public ::testing::Test {};

TEST_F(RegExImplTest_110, MatchesIsEquivalentToMatchNonNegative_110) {
  const YAML::RegEx re('a');

  StreamHolder_110 h1("abc");
  StreamHolder_110 h2("abc");

  const int m = re.Match(h1.stream);
  const bool matches = re.Matches(h2.stream);

  EXPECT_EQ(matches, m >= 0);
}

TEST_F(RegExImplTest_110, MatchesReturnsTrueWhenSingleCharMatchesAtBeginning_110) {
  const YAML::RegEx re('a');
  StreamHolder_110 h("abc");

  EXPECT_TRUE(re.Matches(h.stream));
}

TEST_F(RegExImplTest_110, MatchesReturnsFalseWhenSingleCharDoesNotMatch_110) {
  const YAML::RegEx re('b');
  StreamHolder_110 h("abc");

  EXPECT_FALSE(re.Matches(h.stream));
}

TEST_F(RegExImplTest_110, MatchesDoesNotAdvanceStreamPosition_110) {
  const YAML::RegEx re('a');
  StreamHolder_110 h("abc");

  const int pos_before = h.stream.pos();
  const char peek_before = h.stream.peek();

  const bool result = re.Matches(h.stream);
  (void)result;

  EXPECT_EQ(h.stream.pos(), pos_before);
  EXPECT_EQ(h.stream.peek(), peek_before);
}

TEST_F(RegExImplTest_110, MatchesHandlesEmptyStreamWithoutThrow_110) {
  const YAML::RegEx re('a');
  StreamHolder_110 h("");

  EXPECT_NO_THROW({
    const bool b = re.Matches(h.stream);
    (void)b;
  });
}

TEST_F(RegExImplTest_110, MatchesOnEmptyStreamIsEquivalentToMatchNonNegative_110) {
  const YAML::RegEx re('a');

  StreamHolder_110 h1("");
  StreamHolder_110 h2("");

  const int m = re.Match(h1.stream);
  const bool matches = re.Matches(h2.stream);

  EXPECT_EQ(matches, m >= 0);
}

TEST_F(RegExImplTest_110, MatchesRangeRegexBehavesConsistentlyWithMatch_110) {
  const YAML::RegEx re('a', 'z');

  StreamHolder_110 h1("m");
  StreamHolder_110 h2("m");

  EXPECT_EQ(re.Matches(h2.stream), re.Match(h1.stream) >= 0);
}

TEST_F(RegExImplTest_110, MatchesMismatchRangeRegexBehavesConsistentlyWithMatch_110) {
  const YAML::RegEx re('a', 'z');

  StreamHolder_110 h1("9");
  StreamHolder_110 h2("9");

  EXPECT_EQ(re.Matches(h2.stream), re.Match(h1.stream) >= 0);
}
