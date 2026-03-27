#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox::detail;



// Mock policy for testing

struct MockPolicy {

    using preferred_integer_types_policy = void;

};



TEST_F(is_preferred_integer_types_policyTest_425, DefaultOperatorReturnsFalse_425) {

    is_preferred_integer_types_policy policy;

    EXPECT_FALSE(policy.operator()(...));

}



TEST_F(is_preferred_integer_types_policyTest_425, TemplateOperatorWithMockPolicyReturnsTrue_425) {

    is_preferred_integer_types_policy policy;

    MockPolicy mockPolicy;

    EXPECT_TRUE(policy.template operator()<MockPolicy>(dummy<MockPolicy>()));

}
