#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox::detail;



// Mock class to simulate the Policy with trailing_zero_policy

class MockPolicy {

public:

    using trailing_zero_policy = int;

};



TEST_F(DragonboxDetailTests_417, TrailingZeroPolicyOperatorReturnsFalse_417) {

    is_trailing_zero_policy policy;

    EXPECT_FALSE(policy.operator()(...));

}



TEST_F(DragonboxDetailTests_417, TrailingZeroPolicyOperatorWithDummyReturnsFalse_417) {

    is_trailing_zero_policy policy;

    EXPECT_FALSE(policy.template operator()<MockPolicy>(dummy<MockPolicy>()));

}
