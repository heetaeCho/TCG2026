// File: ./TestProjects/yaml-cpp/test/dragonbox_is_cache_policy_test_423.cpp

#include <gtest/gtest.h>

#include "contrib/dragonbox.h"

namespace {

using YAML::jkj::dragonbox::detail::is_cache_policy;
using YAML::jkj::dragonbox::detail::dummy;

// A policy type that does NOT declare Policy::cache_policy.
struct PolicyWithoutCachePolicy_423 {};

// A policy type that declares Policy::cache_policy (the typical marker for a cache policy).
struct PolicyWithCachePolicy_423 {
  using cache_policy = void;
};

}  // namespace

TEST(IsCachePolicyTest_423, EllipsisOverloadReturnsFalseForArbitraryArguments_423) {
  constexpr is_cache_policy pred{};

  EXPECT_FALSE(pred(0));
  EXPECT_FALSE(pred(123u));
  EXPECT_FALSE(pred(3.14));
  EXPECT_FALSE(pred("anything"));
}

TEST(IsCachePolicyTest_423, ReturnsFalseForPolicyWithoutCachePolicy_423) {
  constexpr is_cache_policy pred{};

  // If Policy::cache_policy doesn't exist, the template overload is not viable and
  // the ellipsis overload should be selected, which is defined to return false.
  EXPECT_FALSE(pred(dummy<PolicyWithoutCachePolicy_423>{}));
}

TEST(IsCachePolicyTest_423, ReturnsTrueForPolicyWithCachePolicyMarker_423) {
  constexpr is_cache_policy pred{};

  // Observable behavior expected from the interface intent: a Policy that has a
  // nested `cache_policy` marker should be identified as a cache policy.
  EXPECT_TRUE(pred(dummy<PolicyWithCachePolicy_423>{}));
}

TEST(IsCachePolicyTest_423, CallableInConstantEvaluationContext_423) {
  constexpr is_cache_policy pred{};

  // Constant-evaluation checks (the operators are declared constexpr).
  static_assert(pred(0) == false, "ellipsis overload should be constexpr and return false");

  // For the marker-based overload:
  static_assert(pred(dummy<PolicyWithoutCachePolicy_423>{}) == false,
                "Policy without cache_policy should not be detected");

  static_assert(pred(dummy<PolicyWithCachePolicy_423>{}) == true,
                "Policy with cache_policy marker should be detected");
}

TEST(IsCachePolicyTest_423, OperatorsAreNoexcept_423) {
  constexpr is_cache_policy pred{};

  static_assert(noexcept(pred(0)), "operator()(...) should be noexcept");
  static_assert(noexcept(pred(dummy<PolicyWithoutCachePolicy_423>{})),
                "operator()(dummy<Policy>) should be noexcept (ellipsis path)");
  static_assert(noexcept(pred(dummy<PolicyWithCachePolicy_423>{})),
                "operator()(dummy<Policy>) should be noexcept (marker path)");
}