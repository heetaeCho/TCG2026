// File: ./TestProjects/yaml-cpp/test/stream_get_n_test.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "stream.h"

namespace {

class StreamGetTest_176 : public ::testing::Test {
 protected:
  static std::string ReadBySingleGets(YAML::Stream& s, int n) {
    std::string out;
    if (n <= 0) return out;
    out.reserve(static_cast<std::string::size_type>(n));
    for (int i = 0; i < n; ++i) {
      out.push_back(s.get());
    }
    return out;
  }

  static YAML::Stream MakeStreamFrom(const std::string& input, std::istringstream& backing) {
    backing.clear();
    backing.str(input);
    return YAML::Stream(backing);
  }
};

TEST_F(StreamGetTest_176, GetPositiveMatchesRepeatedSingleGet_176) {
  const std::string input = "abcdef";

  std::istringstream iss1, iss2;
  YAML::Stream s1 = MakeStreamFrom(input, iss1);
  YAML::Stream s2 = MakeStreamFrom(input, iss2);

  const int n = 3;
  const std::string expected = ReadBySingleGets(s1, n);

  std::string actual;
  EXPECT_NO_THROW(actual = s2.get(n));
  EXPECT_EQ(actual, expected);
}

TEST_F(StreamGetTest_176, GetZeroReturnsEmptyAndDoesNotConsume_176) {
  const std::string input = "xyz";

  std::istringstream iss;
  YAML::Stream s = MakeStreamFrom(input, iss);

  const char before = s.peek();

  std::string out;
  EXPECT_NO_THROW(out = s.get(0));
  EXPECT_TRUE(out.empty());

  const char after = s.peek();
  EXPECT_EQ(after, before);
}

TEST_F(StreamGetTest_176, GetNegativeReturnsEmptyAndDoesNotConsume_176) {
  const std::string input = "hello";

  std::istringstream iss;
  YAML::Stream s = MakeStreamFrom(input, iss);

  const char before = s.peek();

  std::string out;
  EXPECT_NO_THROW(out = s.get(-7));
  EXPECT_TRUE(out.empty());

  const char after = s.peek();
  EXPECT_EQ(after, before);
}

TEST_F(StreamGetTest_176, GetOnEmptyStreamMatchesRepeatedSingleGet_176) {
  const std::string input = "";

  std::istringstream iss1, iss2;
  YAML::Stream s1 = MakeStreamFrom(input, iss1);
  YAML::Stream s2 = MakeStreamFrom(input, iss2);

  const int n = 5;
  const std::string expected = ReadBySingleGets(s1, n);

  std::string actual;
  EXPECT_NO_THROW(actual = s2.get(n));
  EXPECT_EQ(actual, expected);
}

TEST_F(StreamGetTest_176, LargeGetCrossesInternalBufferingMatchesRepeatedSingleGet_176) {
  // Use a large input to exercise internal buffering/prefetching without assuming its details.
  std::string input;
  input.reserve(6000);
  for (int i = 0; i < 6000; ++i) {
    input.push_back(static_cast<char>('a' + (i % 26)));
  }

  std::istringstream iss1, iss2;
  YAML::Stream s1 = MakeStreamFrom(input, iss1);
  YAML::Stream s2 = MakeStreamFrom(input, iss2);

  const int n = 2049;  // boundary around typical prefetch sizes, but compared purely via public behavior
  const std::string expected = ReadBySingleGets(s1, n);

  std::string actual;
  EXPECT_NO_THROW(actual = s2.get(n));
  EXPECT_EQ(actual, expected);
  EXPECT_EQ(actual.size(), expected.size());
}

TEST_F(StreamGetTest_176, SequentialCallsEquivalentToSingleGetsSequence_176) {
  const std::string input = "0123456789";

  std::istringstream iss1, iss2;
  YAML::Stream s1 = MakeStreamFrom(input, iss1);
  YAML::Stream s2 = MakeStreamFrom(input, iss2);

  // Build expected by single gets in the same pattern as the tested code path.
  const std::string expected_a = ReadBySingleGets(s1, 4);
  const std::string expected_b = ReadBySingleGets(s1, 3);

  std::string a, b;
  EXPECT_NO_THROW(a = s2.get(4));
  EXPECT_NO_THROW(b = s2.get(3));

  EXPECT_EQ(a, expected_a);
  EXPECT_EQ(b, expected_b);
}

}  // namespace