// File: ./TestProjects/yaml-cpp/test/exp_end_scalar_test_145.cpp

#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/exp.h"

namespace {

class EndScalarTest_145 : public ::testing::Test {
protected:
  const YAML::RegEx& re() const { return YAML::Exp::EndScalar(); }
};

TEST_F(EndScalarTest_145, ReturnsSameInstanceAcrossCalls_145) {
  const YAML::RegEx* p1 = &YAML::Exp::EndScalar();
  const YAML::RegEx* p2 = &YAML::Exp::EndScalar();
  EXPECT_EQ(p1, p2);
}

TEST_F(EndScalarTest_145, MatchesSingleColonChar_145) {
  EXPECT_TRUE(re().Matches(':'));
}

TEST_F(EndScalarTest_145, DoesNotMatchNonColonChar_145) {
  EXPECT_FALSE(re().Matches('a'));
}

TEST_F(EndScalarTest_145, MatchLengthForColonOnly_145) {
  const int n = re().Match(std::string(":"));
  EXPECT_EQ(n, 1);
}

TEST_F(EndScalarTest_145, MatchLengthForColonFollowedBySpace_145) {
  const int n = re().Match(std::string(": "));
  EXPECT_EQ(n, 2);
}

TEST_F(EndScalarTest_145, MatchStopsBeforeNonBlankFollowingColon_145) {
  // Even if the regex engine supports prefix matches, it should not consume 'a'.
  const int n = re().Match(std::string(":a"));
  EXPECT_EQ(n, 1);
}

TEST_F(EndScalarTest_145, DoesNotMatchWhenColonIsNotFirstCharacter_145) {
  const int n = re().Match(std::string("a:"));
  EXPECT_LE(n, 0);
}

TEST_F(EndScalarTest_145, DoesNotMatchEmptyString_145) {
  const int n = re().Match(std::string(""));
  EXPECT_LE(n, 0);
}

}  // namespace
