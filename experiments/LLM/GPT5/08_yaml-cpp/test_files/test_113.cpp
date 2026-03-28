// File: ./TestProjects/yaml-cpp/test/regeximpl_match_stream_test_113.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "regeximpl.h"          // provides RegEx::Match(const Stream&) inline wrapper
#include "regex_yaml.h"         // RegEx constructors + Match(Source) declaration
#include "stream.h"             // YAML::Stream
#include "streamcharsource.h"   // YAML::StreamCharSource

namespace {

struct StreamWithBacking_113 {
  std::stringstream ss;
  YAML::Stream stream;

  explicit StreamWithBacking_113(const std::string& text) : ss(text), stream(ss) {}
};

class RegExMatchStreamWrapperTest_113 : public ::testing::Test {};

TEST_F(RegExMatchStreamWrapperTest_113, MatchStreamEqualsMatchStreamCharSource_SingleChar_113) {
  const YAML::RegEx ex('a');
  StreamWithBacking_113 input("abc");

  const YAML::StreamCharSource source(input.stream);

  int via_stream = 0;
  int via_source = 0;

  EXPECT_NO_THROW(via_stream = ex.Match(input.stream));
  EXPECT_NO_THROW(via_source = ex.Match(source));

  EXPECT_EQ(via_stream, via_source);
}

TEST_F(RegExMatchStreamWrapperTest_113, MatchStreamEqualsMatchStreamCharSource_NoMatchCase_113) {
  const YAML::RegEx ex('a');
  StreamWithBacking_113 input("zzz");

  const YAML::StreamCharSource source(input.stream);

  int via_stream = 0;
  int via_source = 0;

  EXPECT_NO_THROW(via_stream = ex.Match(input.stream));
  EXPECT_NO_THROW(via_source = ex.Match(source));

  EXPECT_EQ(via_stream, via_source);
}

TEST_F(RegExMatchStreamWrapperTest_113, MatchStreamEqualsMatchStreamCharSource_EmptyStream_113) {
  const YAML::RegEx ex('a');
  StreamWithBacking_113 input("");

  const YAML::StreamCharSource source(input.stream);

  int via_stream = 0;
  int via_source = 0;

  EXPECT_NO_THROW(via_stream = ex.Match(input.stream));
  EXPECT_NO_THROW(via_source = ex.Match(source));

  EXPECT_EQ(via_stream, via_source);
}

TEST_F(RegExMatchStreamWrapperTest_113, MatchStreamEqualsMatchStreamCharSource_RangeRegex_113) {
  const YAML::RegEx ex('a', 'z');  // range constructor
  StreamWithBacking_113 input("mno");

  const YAML::StreamCharSource source(input.stream);

  int via_stream = 0;
  int via_source = 0;

  EXPECT_NO_THROW(via_stream = ex.Match(input.stream));
  EXPECT_NO_THROW(via_source = ex.Match(source));

  EXPECT_EQ(via_stream, via_source);
}

TEST_F(RegExMatchStreamWrapperTest_113, MatchStreamIsDeterministicAcrossRepeatedCalls_113) {
  const YAML::RegEx ex('a');
  StreamWithBacking_113 input("abc");

  const YAML::StreamCharSource source(input.stream);

  int s1 = 0, s2 = 0, c1 = 0, c2 = 0;

  EXPECT_NO_THROW(s1 = ex.Match(input.stream));
  EXPECT_NO_THROW(s2 = ex.Match(input.stream));
  EXPECT_NO_THROW(c1 = ex.Match(source));
  EXPECT_NO_THROW(c2 = ex.Match(source));

  EXPECT_EQ(s1, s2);
  EXPECT_EQ(c1, c2);
  EXPECT_EQ(s1, c1);
}

}  // namespace
