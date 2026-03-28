#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "dragonbox.h"



using namespace YAML::jkj::dragonbox::detail;



struct MockPolicy {

    using sign_policy = void;

};



TEST(is_sign_policy_Test_415, DefaultOperatorReturnsFalse_415) {

    is_sign_policy policy_checker;

    EXPECT_FALSE(policy_checker());

}



TEST(is_sign_policy_Test_415, TemplateOperatorWithValidPolicyReturnsTrue_415) {

    is_sign_policy policy_checker;

    EXPECT_TRUE(policy_checker(MockPolicy{}));

}



TEST(is_sign_policy_Test_415, TemplateOperatorWithInvalidPolicyReturnsFalse_415) {

    is_sign_policy policy_checker;

    struct InvalidPolicy {};

    EXPECT_FALSE(policy_checker(InvalidPolicy{}));

}
