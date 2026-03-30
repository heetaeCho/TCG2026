#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "eval_env.h"



using namespace testing;



class RuleTest : public ::testing::Test {

protected:

    std::unique_ptr<Rule> rule;

    

    void SetUp() override {

        rule = std::make_unique<Rule>("test_rule");

    }

};



TEST_F(RuleTest_21, ConstructorInitializesNameCorrectly_21) {

    EXPECT_EQ(rule->name(), "test_rule");

}



TEST_F(RuleTest_21, IsPhonyReturnsFalseByDefault_21) {

    EXPECT_FALSE(rule->IsPhony());

}



TEST_F(RuleTest_21, PhonyRuleIsRecognizedAsPhony_21) {

    auto phonyRule = Rule::Phony();

    EXPECT_TRUE(phonyRule->IsPhony());

}



TEST_F(RuleTest_21, AddBindingStoresBindingCorrectly_21) {

    EvalString value("test_value");

    rule->AddBinding("key", value);

    const EvalString* retrievedValue = rule->GetBinding("key");

    ASSERT_NE(retrievedValue, nullptr);

    EXPECT_EQ(*retrievedValue, "test_value");

}



TEST_F(RuleTest_21, GetBindingReturnsNullptrForNonexistentKey_21) {

    const EvalString* retrievedValue = rule->GetBinding("non_existent_key");

    EXPECT_EQ(retrievedValue, nullptr);

}



TEST_F(RuleTest_21, IsReservedBindingRecognizesReservedVariable_21) {

    EXPECT_TRUE(Rule::IsReservedBinding("phony"));

    EXPECT_FALSE(Rule::IsReservedBinding("non_reserved_var"));

}
