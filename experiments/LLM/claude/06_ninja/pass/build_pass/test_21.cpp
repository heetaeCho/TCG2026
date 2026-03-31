#include "gtest/gtest.h"
#include "eval_env.h"

// Test fixture for Rule class
class RuleTest_21 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that constructor sets the name correctly
TEST_F(RuleTest_21, ConstructorSetsName_21) {
    Rule rule("my_rule");
    EXPECT_EQ("my_rule", rule.name());
}

// Test name() with empty string
TEST_F(RuleTest_21, ConstructorWithEmptyName_21) {
    Rule rule("");
    EXPECT_EQ("", rule.name());
}

// Test name() with a long string
TEST_F(RuleTest_21, ConstructorWithLongName_21) {
    std::string long_name(1000, 'a');
    Rule rule(long_name);
    EXPECT_EQ(long_name, rule.name());
}

// Test name() with special characters
TEST_F(RuleTest_21, ConstructorWithSpecialCharacters_21) {
    Rule rule("rule-with_special.chars");
    EXPECT_EQ("rule-with_special.chars", rule.name());
}

// Test Phony rule creation
TEST_F(RuleTest_21, PhonyRuleCreation_21) {
    std::unique_ptr<Rule> phony = Rule::Phony();
    ASSERT_NE(nullptr, phony.get());
    EXPECT_TRUE(phony->IsPhony());
}

// Test that a regular rule is not phony
TEST_F(RuleTest_21, RegularRuleIsNotPhony_21) {
    Rule rule("regular_rule");
    EXPECT_FALSE(rule.IsPhony());
}

// Test Phony rule has a name
TEST_F(RuleTest_21, PhonyRuleHasName_21) {
    std::unique_ptr<Rule> phony = Rule::Phony();
    // Phony rule should have some name (typically "phony")
    EXPECT_FALSE(phony->name().empty());
}

// Test AddBinding and GetBinding
TEST_F(RuleTest_21, AddAndGetBinding_21) {
    Rule rule("test_rule");
    EvalString val;
    rule.AddBinding("command", val);
    const EvalString* result = rule.GetBinding("command");
    EXPECT_NE(nullptr, result);
}

// Test GetBinding for non-existent key
TEST_F(RuleTest_21, GetBindingNonExistent_21) {
    Rule rule("test_rule");
    const EvalString* result = rule.GetBinding("nonexistent");
    EXPECT_EQ(nullptr, result);
}

// Test AddBinding overwrites existing binding
TEST_F(RuleTest_21, AddBindingOverwrite_21) {
    Rule rule("test_rule");
    EvalString val1;
    EvalString val2;
    rule.AddBinding("key", val1);
    rule.AddBinding("key", val2);
    const EvalString* result = rule.GetBinding("key");
    EXPECT_NE(nullptr, result);
}

// Test multiple bindings
TEST_F(RuleTest_21, MultipleBindings_21) {
    Rule rule("test_rule");
    EvalString val1, val2, val3;
    rule.AddBinding("command", val1);
    rule.AddBinding("description", val2);
    rule.AddBinding("depfile", val3);

    EXPECT_NE(nullptr, rule.GetBinding("command"));
    EXPECT_NE(nullptr, rule.GetBinding("description"));
    EXPECT_NE(nullptr, rule.GetBinding("depfile"));
    EXPECT_EQ(nullptr, rule.GetBinding("other"));
}

// Test IsReservedBinding with known reserved bindings
TEST_F(RuleTest_21, IsReservedBindingCommand_21) {
    EXPECT_TRUE(Rule::IsReservedBinding("command"));
}

TEST_F(RuleTest_21, IsReservedBindingDepfile_21) {
    EXPECT_TRUE(Rule::IsReservedBinding("depfile"));
}

TEST_F(RuleTest_21, IsReservedBindingDeps_21) {
    EXPECT_TRUE(Rule::IsReservedBinding("deps"));
}

TEST_F(RuleTest_21, IsReservedBindingDescription_21) {
    EXPECT_TRUE(Rule::IsReservedBinding("description"));
}

TEST_F(RuleTest_21, IsReservedBindingGenerator_21) {
    EXPECT_TRUE(Rule::IsReservedBinding("generator"));
}

TEST_F(RuleTest_21, IsReservedBindingRestat_21) {
    EXPECT_TRUE(Rule::IsReservedBinding("restat"));
}

TEST_F(RuleTest_21, IsReservedBindingRspfile_21) {
    EXPECT_TRUE(Rule::IsReservedBinding("rspfile"));
}

TEST_F(RuleTest_21, IsReservedBindingRspfileContent_21) {
    EXPECT_TRUE(Rule::IsReservedBinding("rspfile_content"));
}

// Test IsReservedBinding with non-reserved binding
TEST_F(RuleTest_21, IsNotReservedBinding_21) {
    EXPECT_FALSE(Rule::IsReservedBinding("custom_var"));
}

TEST_F(RuleTest_21, IsNotReservedBindingEmpty_21) {
    EXPECT_FALSE(Rule::IsReservedBinding(""));
}

TEST_F(RuleTest_21, IsNotReservedBindingRandom_21) {
    EXPECT_FALSE(Rule::IsReservedBinding("foobar"));
}

// Test name() returns a reference (consistency check)
TEST_F(RuleTest_21, NameReturnsConsistentReference_21) {
    Rule rule("consistent_name");
    const std::string& name1 = rule.name();
    const std::string& name2 = rule.name();
    EXPECT_EQ(&name1, &name2);
}

// Test with whitespace in name
TEST_F(RuleTest_21, NameWithWhitespace_21) {
    Rule rule("rule with spaces");
    EXPECT_EQ("rule with spaces", rule.name());
}

// Test GetBinding on empty key
TEST_F(RuleTest_21, GetBindingEmptyKey_21) {
    Rule rule("test_rule");
    const EvalString* result = rule.GetBinding("");
    EXPECT_EQ(nullptr, result);
}

// Test AddBinding with empty key
TEST_F(RuleTest_21, AddBindingEmptyKey_21) {
    Rule rule("test_rule");
    EvalString val;
    rule.AddBinding("", val);
    const EvalString* result = rule.GetBinding("");
    EXPECT_NE(nullptr, result);
}
