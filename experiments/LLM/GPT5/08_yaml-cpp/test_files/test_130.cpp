// File: ./TestProjects/yaml-cpp/test/exp_docindicator_test.cpp

#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "exp.h"

namespace {

using YAML::RegEx;

class DocIndicatorTest_130 : public ::testing::Test {
 protected:
  static const RegEx& DocIndicator() { return YAML::Exp::DocIndicator(); }
  static const RegEx& DocStart() { return YAML::Exp::DocStart(); }
  static const RegEx& DocEnd() { return YAML::Exp::DocEnd(); }
};

TEST_F(DocIndicatorTest_130, ReturnsSameInstanceAcrossCalls_130) {
  const RegEx* a = &DocIndicator();
  const RegEx* b = &DocIndicator();
  EXPECT_EQ(a, b);
}

TEST_F(DocIndicatorTest_130, EquivalentToOrOfDocStartAndDocEndOnCommonInputs_130) {
  const RegEx& di = DocIndicator();
  const RegEx& ds = DocStart();
  const RegEx& de = DocEnd();

  const std::vector<std::string> cases = {
      "", " ", "\t", "\n",
      "-", "--", "---", "----",
      ".", "..", "...", "....",
      "a", "abc", " ---", "...\n", "---\n", "... ",
      "----\n", "...\r\n", "---\r\n",
  };

  for (const auto& s : cases) {
    SCOPED_TRACE(::testing::Message() << "input='" << s << "'");
    const bool expected = ds.Matches(s) || de.Matches(s);
    EXPECT_EQ(di.Matches(s), expected);
  }
}

TEST_F(DocIndicatorTest_130, EquivalentToOrWithEmbeddedNullBytes_130) {
  const RegEx& di = DocIndicator();
  const RegEx& ds = DocStart();
  const RegEx& de = DocEnd();

  // Ensure behavior stays consistent even with embedded NULs.
  const std::string with_nul_1 = std::string("...\0", 4);
  const std::string with_nul_2 = std::string("---\0---", 7);
  const std::vector<std::string> cases = {with_nul_1, with_nul_2};

  for (const auto& s : cases) {
    SCOPED_TRACE(::testing::Message() << "size=" << s.size());
    const bool expected = ds.Matches(s) || de.Matches(s);
    EXPECT_EQ(di.Matches(s), expected);
  }
}

TEST_F(DocIndicatorTest_130, DoesNotMatchWhenNeitherDocStartNorDocEndMatches_130) {
  const RegEx& di = DocIndicator();
  const RegEx& ds = DocStart();
  const RegEx& de = DocEnd();

  const std::vector<std::string> cases = {
      "not-a-doc-indicator",
      "----x",
      ".. ..",
      "....a",
      " ---x",
      "...\tmore",
  };

  for (const auto& s : cases) {
    SCOPED_TRACE(::testing::Message() << "input='" << s << "'");
    ASSERT_FALSE(ds.Matches(s) || de.Matches(s));
    EXPECT_FALSE(di.Matches(s));
  }
}

}  // namespace
