// TEST_ID: 414
#include <gtest/gtest.h>

#include "TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

namespace d = YAML::jkj::dragonbox::detail;

// Use trivially-defined policy tag types. We don't assume anything about how
// a policy is validated; we only compare check_policy_list_validity() against
// the observable results of check_policy_validity() for the same inputs.
struct PolicyA_414 {};
struct PolicyB_414 {};
struct PolicyC_414 {};
struct PolicyD_414 {};

// In dragonbox, the detector/default-pair list type is typically a template.
// We pick the empty list (no pairs) as a reasonable baseline.
using EmptyDetectorList_414 = d::detector_default_pair_list<>;

}  // namespace

TEST(DragonboxPolicyListValidityTest_414, EmptyPolicyListIsValid_414) {
  // Boundary: no policies.
  constexpr bool ok = d::check_policy_list_validity(EmptyDetectorList_414{});
  EXPECT_TRUE(ok);
}

TEST(DragonboxPolicyListValidityTest_414, SinglePolicyMatchesIndividualValidity_414) {
  // Normal: 1 policy.
  constexpr bool list_ok =
      d::check_policy_list_validity(EmptyDetectorList_414{}, d::dummy<PolicyA_414>{});

  constexpr bool single_ok =
      d::check_policy_validity(d::dummy<PolicyA_414>{}, EmptyDetectorList_414{});

  EXPECT_EQ(list_ok, single_ok);
}

TEST(DragonboxPolicyListValidityTest_414, TwoPoliciesEqualsConjunctionOfIndividualValidity_414) {
  // Normal: 2 policies.
  constexpr bool list_ok = d::check_policy_list_validity(
      EmptyDetectorList_414{}, d::dummy<PolicyA_414>{}, d::dummy<PolicyB_414>{});

  constexpr bool expected =
      d::check_policy_validity(d::dummy<PolicyA_414>{}, EmptyDetectorList_414{}) &&
      d::check_policy_validity(d::dummy<PolicyB_414>{}, EmptyDetectorList_414{});

  EXPECT_EQ(list_ok, expected);
}

TEST(DragonboxPolicyListValidityTest_414, MultiplePoliciesEqualsConjunctionOfIndividualValidity_414) {
  // Boundary: several policies (recursion depth / parameter pack handling).
  constexpr bool list_ok = d::check_policy_list_validity(
      EmptyDetectorList_414{}, d::dummy<PolicyA_414>{}, d::dummy<PolicyB_414>{},
      d::dummy<PolicyC_414>{}, d::dummy<PolicyD_414>{}, d::dummy<PolicyA_414>{},
      d::dummy<PolicyB_414>{}, d::dummy<PolicyC_414>{});

  constexpr bool expected =
      d::check_policy_validity(d::dummy<PolicyA_414>{}, EmptyDetectorList_414{}) &&
      d::check_policy_validity(d::dummy<PolicyB_414>{}, EmptyDetectorList_414{}) &&
      d::check_policy_validity(d::dummy<PolicyC_414>{}, EmptyDetectorList_414{}) &&
      d::check_policy_validity(d::dummy<PolicyD_414>{}, EmptyDetectorList_414{}) &&
      d::check_policy_validity(d::dummy<PolicyA_414>{}, EmptyDetectorList_414{}) &&
      d::check_policy_validity(d::dummy<PolicyB_414>{}, EmptyDetectorList_414{}) &&
      d::check_policy_validity(d::dummy<PolicyC_414>{}, EmptyDetectorList_414{});

  EXPECT_EQ(list_ok, expected);
}

TEST(DragonboxPolicyListValidityTest_414, WorksAtRuntimeAsWellAsConstexpr_414) {
  // Normal: runtime call (still observable behavior: returned bool).
  const bool list_ok = d::check_policy_list_validity(
      EmptyDetectorList_414{}, d::dummy<PolicyA_414>{}, d::dummy<PolicyB_414>{});

  const bool expected =
      d::check_policy_validity(d::dummy<PolicyA_414>{}, EmptyDetectorList_414{}) &&
      d::check_policy_validity(d::dummy<PolicyB_414>{}, EmptyDetectorList_414{});

  EXPECT_EQ(list_ok, expected);
}