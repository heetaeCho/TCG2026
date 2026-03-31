#include <gtest/gtest.h>
#include <type_traits>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// Helper struct that has a cache_policy type alias
struct PolicyWithCachePolicy {
    using cache_policy = int;
};

// Helper struct that does NOT have a cache_policy type alias
struct PolicyWithoutCachePolicy {
    using some_other_policy = int;
};

// Another valid policy with a different cache_policy type
struct AnotherPolicyWithCachePolicy {
    using cache_policy = double;
};

// Empty struct with no type aliases at all
struct EmptyPolicy {};

// Policy where cache_policy is a struct
struct PolicyWithStructCachePolicy {
    struct cache_policy {};
};

// Policy where cache_policy is void
struct PolicyWithVoidCachePolicy {
    using cache_policy = void;
};

using namespace YAML::jkj::dragonbox::detail;

// Test fixture
class IsCachePolicyTest_424 : public ::testing::Test {
protected:
    is_cache_policy checker;
};

// Test that a policy with cache_policy type alias returns true
TEST_F(IsCachePolicyTest_424, ReturnsTrueForPolicyWithCachePolicy_424) {
    constexpr bool result = is_cache_policy{}(dummy<PolicyWithCachePolicy>{});
    EXPECT_TRUE(result);
}

// Test that another policy with cache_policy type alias returns true
TEST_F(IsCachePolicyTest_424, ReturnsTrueForAnotherPolicyWithCachePolicy_424) {
    constexpr bool result = is_cache_policy{}(dummy<AnotherPolicyWithCachePolicy>{});
    EXPECT_TRUE(result);
}

// Test that a policy with struct cache_policy returns true
TEST_F(IsCachePolicyTest_424, ReturnsTrueForPolicyWithStructCachePolicy_424) {
    constexpr bool result = is_cache_policy{}(dummy<PolicyWithStructCachePolicy>{});
    EXPECT_TRUE(result);
}

// Test that a policy with void cache_policy returns true
TEST_F(IsCachePolicyTest_424, ReturnsTrueForPolicyWithVoidCachePolicy_424) {
    constexpr bool result = is_cache_policy{}(dummy<PolicyWithVoidCachePolicy>{});
    EXPECT_TRUE(result);
}

// Test that the result is constexpr / noexcept
TEST_F(IsCachePolicyTest_424, OperatorIsNoexcept_424) {
    EXPECT_TRUE(noexcept(is_cache_policy{}(dummy<PolicyWithCachePolicy>{})));
}

// Test that the operator is constexpr evaluable
TEST_F(IsCachePolicyTest_424, OperatorIsConstexpr_424) {
    constexpr is_cache_policy c{};
    constexpr bool val = c(dummy<PolicyWithCachePolicy>{});
    EXPECT_TRUE(val);
}

// Test SFINAE: policies without cache_policy should NOT be callable
// We verify this by checking that the call expression is not valid via SFINAE
template <typename T, typename = void>
struct is_callable_with : std::false_type {};

template <typename T>
struct is_callable_with<T, 
    std::void_t<decltype(std::declval<is_cache_policy>()(std::declval<dummy<T>>()))>> 
    : std::true_type {};

TEST_F(IsCachePolicyTest_424, NotCallableForPolicyWithoutCachePolicy_424) {
    // PolicyWithoutCachePolicy does not have cache_policy, so SFINAE should exclude it
    EXPECT_FALSE((is_callable_with<PolicyWithoutCachePolicy>::value));
}

TEST_F(IsCachePolicyTest_424, NotCallableForEmptyPolicy_424) {
    // EmptyPolicy does not have cache_policy
    EXPECT_FALSE((is_callable_with<EmptyPolicy>::value));
}

TEST_F(IsCachePolicyTest_424, CallableForPolicyWithCachePolicy_424) {
    EXPECT_TRUE((is_callable_with<PolicyWithCachePolicy>::value));
}

TEST_F(IsCachePolicyTest_424, CallableForPolicyWithStructCachePolicy_424) {
    EXPECT_TRUE((is_callable_with<PolicyWithStructCachePolicy>::value));
}

} // namespace
