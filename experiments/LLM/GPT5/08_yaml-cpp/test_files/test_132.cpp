// File: ./TestProjects/yaml-cpp/test/exp_key_test_132.cpp

#include <gtest/gtest.h>

#include <string>

#include "exp.h"
#include "regex_yaml.h"

namespace {

class ExpKeyTest_132 : public ::testing::Test {
protected:
  static const YAML::RegEx& Key() { return YAML::Exp::Key(); }
};

TEST_F(ExpKeyTest_132, ReturnsSameInstanceAcrossCalls_132) {
  const YAML::RegEx* first = &Key();
  const YAML::RegEx* second = &Key();
  const YAML::RegEx* third = &Key();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(ExpKeyTest_132, ReferenceRemainsValidAfterRepeatedCalls_132) {
  const YAML::RegEx& ref = Key();

  // Repeated calls should not invalidate the previously obtained reference.
  for (int i = 0; i < 1000; ++i) {
    (void)Key();
  }

  EXPECT_EQ(&ref, &Key());
}

TEST_F(ExpKeyTest_132, CanInvokeMatchesOnCommonInputsWithoutThrow_132) {
  // Black-box safety checks: ensure the returned regex can be used without throwing.
  EXPECT_NO_THROW((void)Key().Matches(std::string("")));
  EXPECT_NO_THROW((void)Key().Matches(std::string("?")));
  EXPECT_NO_THROW((void)Key().Matches(std::string("? ")));
  EXPECT_NO_THROW((void)Key().Matches(std::string("?\n")));
  EXPECT_NO_THROW((void)Key().Matches(std::string("??")));
  EXPECT_NO_THROW((void)Key().Matches(std::string("a")));
  EXPECT_NO_THROW((void)Key().Matches(std::string("a?")));
}

TEST_F(ExpKeyTest_132, CanInvokeMatchOnCommonInputsWithoutThrow_132) {
  // Black-box safety checks for Match() on boundary and typical strings.
  EXPECT_NO_THROW((void)Key().Match(std::string("")));
  EXPECT_NO_THROW((void)Key().Match(std::string("?")));
  EXPECT_NO_THROW((void)Key().Match(std::string("? ")));
  EXPECT_NO_THROW((void)Key().Match(std::string("?\n")));
  EXPECT_NO_THROW((void)Key().Match(std::string("??")));
  EXPECT_NO_THROW((void)Key().Match(std::string("a")));
  EXPECT_NO_THROW((void)Key().Match(std::string("a?")));
}

TEST_F(ExpKeyTest_132, MatchesCharDoesNotThrow_132) {
  // Ensure char-based matching is callable and stable.
  EXPECT_NO_THROW((void)Key().Matches('?'));
  EXPECT_NO_THROW((void)Key().Matches('a'));
  EXPECT_NO_THROW((void)Key().Matches('\n'));
  EXPECT_NO_THROW((void)Key().Matches(' '));
}

}  // namespace
