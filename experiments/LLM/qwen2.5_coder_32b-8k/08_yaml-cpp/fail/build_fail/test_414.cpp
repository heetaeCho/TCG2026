#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace detail {



// Mocking classes and helpers if necessary for external collaborators



// Test Fixture

class CheckPolicyListValidityTest_414 : public ::testing::Test {

protected:

    // Setup and teardown if needed

};



TEST_F(CheckPolicyListValidityTest_414, NormalOperation_414) {

    // Arrange

    auto detectorDefaultPairList = /* create appropriate object */;

    auto firstPolicy = /* create appropriate object */;

    auto remainingPolicies = /* create appropriate objects */;



    // Act & Assert

    EXPECT_TRUE(check_policy_list_validity(detectorDefaultPairList, dummy<FirstPolicy>{}, dummy<RemainingPolicies>{}...));

}



TEST_F(CheckPolicyListValidityTest_414, BoundaryCondition_EmptyRemainingPolicies_414) {

    // Arrange

    auto detectorDefaultPairList = /* create appropriate object */;

    auto firstPolicy = /* create appropriate object */;



    // Act & Assert

    EXPECT_TRUE(check_policy_list_validity(detectorDefaultPairList, dummy<FirstPolicy>{}));

}



// Since the function is templated and relies on constexpr behavior,

// it's challenging to provoke exceptions without internal knowledge.

// However, if there are known invalid states or parameters that can be passed in,

// you could test for those.



TEST_F(CheckPolicyListValidityTest_414, ExceptionalCase_InvalidFirstPolicy_414) {

    // Arrange

    auto detectorDefaultPairList = /* create appropriate object */;

    auto invalidFirstPolicy = /* create an invalid policy object */;



    // Act & Assert

    EXPECT_FALSE(check_policy_list_validity(detectorDefaultPairList, dummy<decltype(invalidFirstPolicy)>{}));

}



TEST_F(CheckPolicyListValidityTest_414, ExternalInteraction_VerifyCalls_414) {

    // Arrange

    // If there are external collaborators, use Google Mock to verify interactions.

    // For this specific function, it seems there are no direct external collaborators.



    auto detectorDefaultPairList = /* create appropriate object */;

    auto firstPolicy = /* create appropriate object */;

    auto remainingPolicies = /* create appropriate objects */;



    // Act & Assert

    EXPECT_TRUE(check_policy_list_validity(detectorDefaultPairList, dummy<FirstPolicy>{}, dummy<RemainingPolicies>{}...));

    // Add mock verification if applicable.

}



}}}}
