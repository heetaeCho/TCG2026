// File: ./TestProjects/yaml-cpp/test/dragonbox_is_cache_policy_test_424.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "contrib/dragonbox.h"

namespace {

namespace detail = YAML::jkj::dragonbox::detail;

// Helper: checks whether Functor{}(detail::dummy<Policy>{}) is a valid expression.
template <class Functor, class Policy>
constexpr bool IsInvocableWithDummyV =
    std::is_invocable_v<Functor, detail::dummy<Policy>>;

struct PolicyWithCachePolicyInt {
  using cache_policy = int;
};

struct PolicyWithCachePolicyVoid {
  using cache_policy = void;
};

struct PolicyWithoutCachePolicy {};

}  // namespace

TEST(IsCachePolicyTest_424, PolicyWithCachePolicy_ReturnsTrue_424) {
  detail::is_cache_policy pred{};

  // Basic observable behavior: for a Policy that provides Policy::cache_policy,
  // operator()(dummy<Policy>) should be callable and return true.
  EXPECT_TRUE((pred(detail::dummy<PolicyWithCachePolicyInt>{})));
}

TEST(IsCachePolicyTest_424, PolicyWithCachePolicyDifferentType_ReturnsTrue_424) {
  detail::is_cache_policy pred{};

  // Boundary-ish: cache_policy exists even if it's an unusual type (void).
  EXPECT_TRUE((pred(detail::dummy<PolicyWithCachePolicyVoid>{})));
}

TEST(IsCachePolicyTest_424, PolicyWithoutCachePolicy_NotInvocableOrFalse_424) {
  detail::is_cache_policy pred{};

  // We do NOT assume how the "no cache_policy" case is implemented:
  // - It might be SFINAE-disabled (not invocable), OR
  // - It might be invocable and return false via another overload/specialization.
  //
  // We only assert behavior that is observable from the interface.
  if constexpr (IsInvocableWithDummyV<detail::is_cache_policy, PolicyWithoutCachePolicy>) {
    EXPECT_FALSE((pred(detail::dummy<PolicyWithoutCachePolicy>{})));
  } else {
    SUCCEED();  // Not invocable is an acceptable/observable "error" behavior.
  }
}

TEST(IsCachePolicyTest_424, PolicyWithCachePolicy_IsNoexcept_424) {
  detail::is_cache_policy pred{};

  // The interface marks the operator() noexcept for the cache-policy-enabled path.
  static_assert(noexcept(pred(detail::dummy<PolicyWithCachePolicyInt>{})),
                "Expected is_cache_policy::operator() to be noexcept for Policy with cache_policy.");
  EXPECT_TRUE(noexcept(pred(detail::dummy<PolicyWithCachePolicyInt>{})));
}

TEST(IsCachePolicyTest_424, PolicyWithCachePolicy_IsConstexprCallable_424) {
  // The interface marks the operator() constexpr; verify it can be used in a constant expression.
  constexpr detail::is_cache_policy pred{};
  constexpr bool value = pred(detail::dummy<PolicyWithCachePolicyInt>{});
  static_assert(value, "Expected constexpr evaluation to yield true for Policy with cache_policy.");
  EXPECT_TRUE(value);
}