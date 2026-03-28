// File: ./TestProjects/yaml-cpp/test/dragonbox_check_policy_validity_test_411.cpp

#include <type_traits>

#include <gtest/gtest.h>

#include "contrib/dragonbox.h"

namespace {

struct PolicyA_411 {};
struct PolicyB_411 {};

}  // namespace

TEST(DragonboxPolicyValidityTest_411, ReturnsFalseForEmptyDetectorList_411) {
  using ::YAML::jkj::dragonbox::detail::check_policy_validity;
  using ::YAML::jkj::dragonbox::detail::detector_default_pair_list;
  using ::YAML::jkj::dragonbox::detail::dummy;

  EXPECT_FALSE(check_policy_validity(dummy<PolicyA_411>{}, detector_default_pair_list<>{}));
}

TEST(DragonboxPolicyValidityTest_411, ReturnsFalseForDifferentPolicyType_411) {
  using ::YAML::jkj::dragonbox::detail::check_policy_validity;
  using ::YAML::jkj::dragonbox::detail::detector_default_pair_list;
  using ::YAML::jkj::dragonbox::detail::dummy;

  EXPECT_FALSE(check_policy_validity(dummy<PolicyB_411>{}, detector_default_pair_list<>{}));
}

TEST(DragonboxPolicyValidityTest_411, IsNoexcept_411) {
  using ::YAML::jkj::dragonbox::detail::check_policy_validity;
  using ::YAML::jkj::dragonbox::detail::detector_default_pair_list;
  using ::YAML::jkj::dragonbox::detail::dummy;

  static_assert(noexcept(check_policy_validity(dummy<PolicyA_411>{}, detector_default_pair_list<>{})),
                "check_policy_validity(dummy<Policy>, detector_default_pair_list<>) must be noexcept");
  EXPECT_TRUE((noexcept(check_policy_validity(dummy<PolicyA_411>{}, detector_default_pair_list<>{}))));
}

TEST(DragonboxPolicyValidityTest_411, IsConstexprEvaluable_411) {
  using ::YAML::jkj::dragonbox::detail::check_policy_validity;
  using ::YAML::jkj::dragonbox::detail::detector_default_pair_list;
  using ::YAML::jkj::dragonbox::detail::dummy;

  constexpr bool v =
      check_policy_validity(dummy<PolicyA_411>{}, detector_default_pair_list<>{});
  static_assert(!v, "Expected constexpr evaluation to be false for empty detector_default_pair_list<>");

  EXPECT_FALSE(v);
}