// TEST_ID: 511
// File: indentation_test.cpp

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <string>

#include "yaml-cpp/ostream_wrapper.h"
#include "src/indentation.h"

namespace {

TEST(IndentationOperatorTest_511, ZeroIndentWritesNothing_511) {
  YAML::ostream_wrapper out;
  out << YAML::Indentation(0);

  EXPECT_STREQ(out.str(), "");
}

TEST(IndentationOperatorTest_511, SmallIndentWritesExactSpaces_511) {
  YAML::ostream_wrapper out;
  out << YAML::Indentation(3);

  EXPECT_STREQ(out.str(), "   ");
}

TEST(IndentationOperatorTest_511, ChainingAppendsAfterIndent_511) {
  YAML::ostream_wrapper out;
  out << YAML::Indentation(2) << 'X';

  EXPECT_STREQ(out.str(), "  X");
}

TEST(IndentationOperatorTest_511, MultipleIndentsAccumulate_511) {
  YAML::ostream_wrapper out;
  out << YAML::Indentation(1) << YAML::Indentation(2);

  EXPECT_STREQ(out.str(), "   ");
}

TEST(IndentationOperatorTest_511, LargeIndentWritesCorrectCountAndOnlySpaces_511) {
  constexpr std::size_t kN = 1024;

  YAML::ostream_wrapper out;
  out << YAML::Indentation(kN);

  const char* s = out.str();
  ASSERT_NE(s, nullptr);

  const std::size_t len = std::strlen(s);
  EXPECT_EQ(len, kN);
  EXPECT_TRUE(std::all_of(s, s + len, [](char ch) { return ch == ' '; }));
}

TEST(IndentationOperatorTest_511, DoesNotChangeCommentFlag_511) {
  YAML::ostream_wrapper out;
  EXPECT_FALSE(out.comment());

  out << YAML::Indentation(4);

  EXPECT_FALSE(out.comment());
}

}  // namespace