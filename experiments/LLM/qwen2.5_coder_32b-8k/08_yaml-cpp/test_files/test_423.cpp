#include <gtest/gtest.h>

#include <gmock/gmock.h>



namespace YAML { namespace jkj { namespace dragonbox { namespace detail {



struct dummy {};



TEST_F(is_cache_policyTest_423, OperatorCallReturnsFalseForNonPolicyType_423) {

    is_cache_policy policy_checker;

    EXPECT_FALSE(policy_checker.operator()());

}



TEST_F(is_cache_policyTest_423, OperatorCallReturnsTrueForValidCachePolicy_423) {

    struct MockPolicy {

        using cache_policy = int; // Dummy type to simulate a valid cache policy

    };

    

    is_cache_policy policy_checker;

    EXPECT_TRUE(policy_checker.operator()(dummy<MockPolicy>()));

}



TEST_F(is_cache_policyTest_423, OperatorCallReturnsFalseForInvalidCachePolicy_423) {

    struct InvalidPolicy {

        // Missing cache_policy type to simulate an invalid cache policy

    };

    

    is_cache_policy policy_checker;

    EXPECT_FALSE(policy_checker.operator()(dummy<InvalidPolicy>()));

}



}}}}




