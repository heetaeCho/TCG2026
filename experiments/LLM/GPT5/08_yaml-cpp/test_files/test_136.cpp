// File: ./TestProjects/yaml-cpp/test/exp_value_in_json_flow_test.cpp

#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/exp.h"
#include "TestProjects/yaml-cpp/src/regex_yaml.h"

namespace {

TEST(ValueInJSONFlowTest_136, ReturnsSameInstanceAcrossCalls_136) {
  const YAML::RegEx* first = nullptr;
  const YAML::RegEx* second = nullptr;

  EXPECT_NO_THROW(first = &YAML::Exp::ValueInJSONFlow());
  EXPECT_NO_THROW(second = &YAML::Exp::ValueInJSONFlow());

  ASSERT_NE(first, nullptr);
  ASSERT_NE(second, nullptr);
  EXPECT_EQ(first, second);
}

TEST(ValueInJSONFlowTest_136, MatchesColonCharacter_136) {
  const YAML::RegEx& ex = YAML::Exp::ValueInJSONFlow();

  bool matches = false;
  EXPECT_NO_THROW(matches = ex.Matches(':'));
  EXPECT_TRUE(matches);
}

TEST(ValueInJSONFlowTest_136, DoesNotMatchDifferentCharacters_136) {
  const YAML::RegEx& ex = YAML::Exp::ValueInJSONFlow();

  // A small representative set (letters, digits, whitespace, punctuation).
  const char not_colon[] = {'a', 'Z', '0', '9', ' ', '\n', '\t', '-', '_', '{',
                            '}', '[', ']', ',', ';', '.', '/'};

  for (char ch : not_colon) {
    bool matches = true;  // set opposite to ensure call actually updates it
    EXPECT_NO_THROW(matches = ex.Matches(ch)) << "ch=" << static_cast<int>(ch);
    EXPECT_FALSE(matches) << "Expected ':'-regex not to match ch=" << static_cast<int>(ch);
  }
}

TEST(ValueInJSONFlowTest_136, StringMatchColonOnly_136) {
  const YAML::RegEx& ex = YAML::Exp::ValueInJSONFlow();

  bool matches = false;

  // A string that is exactly ":" should match.
  EXPECT_NO_THROW(matches = ex.Matches(std::string(":")));
  EXPECT_TRUE(matches);

  // A string that doesn't contain ':' should not match (observable behavior expectation).
  EXPECT_NO_THROW(matches = ex.Matches(std::string("abc")));
  EXPECT_FALSE(matches);

  // Boundary: empty string should not match.
  EXPECT_NO_THROW(matches = ex.Matches(std::string("")));
  EXPECT_FALSE(matches);
}

}  // namespace
