#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace detail {



// Mock class for Policy with binary_to_decimal_rounding_policy type

struct MockPolicy {

    using binary_to_decimal_rounding_policy = void;

};



TEST(is_binary_to_decimal_rounding_policyTest_421, DefaultOperatorReturnsFalse_421) {

    is_binary_to_decimal_rounding_policy policy;

    EXPECT_FALSE(policy.operator()());

}



TEST(is_binary_to_decimal_rounding_policyTest_421, TemplateOperatorWithMockPolicyReturnsTrue_421) {

    is_binary_to_decimal_rounding_policy policy;

    EXPECT_TRUE(policy.template operator()<MockPolicy>(dummy<MockPolicy>{}));

}



TEST(is_binary_to_decimal_rounding_policyTest_421, TemplateOperatorWithoutBinaryToDecimalRoundingPolicyThrows_421) {

    struct InvalidPolicy {};



    is_binary_to_decimal_rounding_policy policy;

    EXPECT_FALSE((policy.template operator()<InvalidPolicy>(dummy<InvalidPolicy>{})));

}



}}}}
