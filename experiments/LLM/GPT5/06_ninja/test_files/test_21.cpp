// File: rule_test_21.cc

#include "eval_env.h"

#include <gtest/gtest.h>
#include <memory>
#include <string>

class RuleTest_21 : public ::testing::Test {};

// Constructor & name()

TEST_F(RuleTest_21, ConstructorStoresName_21) {
  Rule rule("link");
  EXPECT_EQ(rule.name(), std::string("link"));
}

TEST_F(RuleTest_21, NonPhonyRuleIsNotPhony_21) {
  Rule rule("compile");
  EXPECT_FALSE(rule.IsPhony());
}

// GetBinding / AddBinding behavior

TEST_F(RuleTest_21, GetBindingReturnsNullForUnknownKey_21) {
  Rule rule("rule_with_no_bindings");

  const EvalString* binding = rule.GetBinding("does_not_exist");
  EXPECT_EQ(binding, nullptr);
}

TEST_F(RuleTest_21, AddBindingThenGetBindingReturnsNonNull_21) {
  Rule rule("simple");
  EvalString value;

  rule.AddBinding("command", value);
  const EvalString* binding = rule.GetBinding("command");

  ASSERT_NE(binding, nullptr);
}

TEST_F(RuleTest_21, AddMultipleBindingsAndRetrieveEach_21) {
  Rule rule("multi");
  EvalString val1;
  EvalString val2;

  rule.AddBinding("command", val1);
  rule.AddBinding("description", val2);

  const EvalString* cmd = rule.GetBinding("command");
  const EvalString* desc = rule.GetBinding("description");

  ASSERT_NE(cmd, nullptr);
  ASSERT_NE(desc, nullptr);
  EXPECT_NE(cmd, desc);  // They should be distinct bindings for different keys.
}

// Phony rule factory

TEST_F(RuleTest_21, PhonyFactoryCreatesNonNullRule_21) {
  std::unique_ptr<Rule> phony = Rule::Phony();
  EXPECT_TRUE(phony != nullptr);
}

TEST_F(RuleTest_21, PhonyRuleIsMarkedPhony_21) {
  std::unique_ptr<Rule> phony = Rule::Phony();
  ASSERT_TRUE(phony != nullptr);
  EXPECT_TRUE(phony->IsPhony());
}

// IsReservedBinding behavior

TEST_F(RuleTest_21, ReservedBindingNamesRecognized_21) {
  // These are typical reserved variables in Ninja rules.
  EXPECT_TRUE(Rule::IsReservedBinding("command"));
  EXPECT_TRUE(Rule::IsReservedBinding("description"));
}

TEST_F(RuleTest_21, NonReservedBindingNamesNotRecognized_21) {
  EXPECT_FALSE(Rule::IsReservedBinding("custom_var"));
  EXPECT_FALSE(Rule::IsReservedBinding("another_custom_var"));
}
