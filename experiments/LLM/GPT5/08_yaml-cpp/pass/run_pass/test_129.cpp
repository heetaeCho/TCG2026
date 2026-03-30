// File: ./TestProjects/yaml-cpp/test/exp_docend_test_129.cpp

#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/exp.h"        // YAML::Exp::DocEnd()
#include "TestProjects/yaml-cpp/src/regex_yaml.h" // YAML::RegEx

namespace {

class DocEndTest_129 : public ::testing::Test {};

TEST_F(DocEndTest_129, ReturnsSameInstanceEachCall_129) {
  const YAML::RegEx* first = &YAML::Exp::DocEnd();
  const YAML::RegEx* second = &YAML::Exp::DocEnd();
  EXPECT_EQ(first, second);
}

TEST_F(DocEndTest_129, MatchesExactEllipsis_129) {
  EXPECT_TRUE(YAML::Exp::DocEnd().Matches(std::string("...")));
}

TEST_F(DocEndTest_129, MatchesEllipsisWithTrailingSpace_129) {
  EXPECT_TRUE(YAML::Exp::DocEnd().Matches(std::string("... ")));
}

TEST_F(DocEndTest_129, MatchesEllipsisWithTrailingNewline_129) {
  EXPECT_TRUE(YAML::Exp::DocEnd().Matches(std::string("...\n")));
}

TEST_F(DocEndTest_129, DoesNotMatchEmptyOrShorterStrings_129) {
  EXPECT_FALSE(YAML::Exp::DocEnd().Matches(std::string("")));
  EXPECT_FALSE(YAML::Exp::DocEnd().Matches(std::string(".")));
  EXPECT_FALSE(YAML::Exp::DocEnd().Matches(std::string("..")));
}

TEST_F(DocEndTest_129, DoesNotMatchDifferentMarker_129) {
  EXPECT_FALSE(YAML::Exp::DocEnd().Matches(std::string("---")));
  EXPECT_FALSE(YAML::Exp::DocEnd().Matches(std::string("....")));
}

TEST_F(DocEndTest_129, DoesNotMatchEllipsisFollowedByNonBlankNonBreak_129) {
  EXPECT_FALSE(YAML::Exp::DocEnd().Matches(std::string("...a")));
  EXPECT_FALSE(YAML::Exp::DocEnd().Matches(std::string("...0")));
  EXPECT_FALSE(YAML::Exp::DocEnd().Matches(std::string("..._")));
}

TEST_F(DocEndTest_129, DoesNotMatchWhenExtraDataAfterEmbeddedNull_129) {
  std::string s;
  s.push_back('.');
  s.push_back('.');
  s.push_back('.');
  s.push_back('\0');  // extra non-blank, non-break byte after "..."
  s.push_back('x');
  EXPECT_FALSE(YAML::Exp::DocEnd().Matches(s));
}

}  // namespace
