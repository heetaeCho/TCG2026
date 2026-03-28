#include <gtest/gtest.h>

// Include the header under test
#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"

namespace {

// A struct that does NOT have a cache_policy type alias
struct NoCachePolicyStruct {
    int value = 0;
};

// A struct that HAS a cache_policy type alias
struct HasCachePolicyStruct {
    using cache_policy = void;
    int value = 0;
};

// Another struct with cache_policy
struct AnotherCachePolicyStruct {
    using cache_policy = int;
};

// A struct with cache_policy being a complex type
struct ComplexCachePolicyStruct {
    struct MyCachePolicy {};
    using cache_policy = MyCachePolicy;
};

} // anonymous namespace

using namespace YAML::jkj::dragonbox::detail;

// Test: Default variadic operator() returns false for fundamental types
TEST(IsCachePolicyTest_423, DefaultReturnsFalseForInt_423) {
    is_cache_policy checker;
    // Passing an int should go through the variadic fallback
    bool result = checker(0);
    EXPECT_FALSE(result);
}

// Test: Default variadic operator() returns false for double
TEST(IsCachePolicyTest_423, DefaultReturnsFalseForDouble_423) {
    is_cache_policy checker;
    bool result = checker(0.0);
    EXPECT_FALSE(result);
}

// Test: Default variadic operator() returns false for nullptr
TEST(IsCachePolicyTest_423, DefaultReturnsFalseForNullptr_423) {
    is_cache_policy checker;
    bool result = checker(nullptr);
    EXPECT_FALSE(result);
}

// Test: Returns false for a struct without cache_policy
TEST(IsCachePolicyTest_423, ReturnsFalseForStructWithoutCachePolicy_423) {
    is_cache_policy checker;
    NoCachePolicyStruct s;
    bool result = checker(s);
    EXPECT_FALSE(result);
}

// Test: Returns true for a struct with cache_policy type alias (via template overload)
TEST(IsCachePolicyTest_423, ReturnsTrueForStructWithCachePolicy_423) {
    is_cache_policy checker;
    HasCachePolicyStruct s;
    // The template overload with SFINAE should match and return true
    bool result = checker(dummy<HasCachePolicyStruct>{});
    EXPECT_TRUE(result);
}

// Test: Returns true for another struct with cache_policy
TEST(IsCachePolicyTest_423, ReturnsTrueForAnotherCachePolicyStruct_423) {
    is_cache_policy checker;
    bool result = checker(dummy<AnotherCachePolicyStruct>{});
    EXPECT_TRUE(result);
}

// Test: Returns true for a struct with complex cache_policy
TEST(IsCachePolicyTest_423, ReturnsTrueForComplexCachePolicyStruct_423) {
    is_cache_policy checker;
    bool result = checker(dummy<ComplexCachePolicyStruct>{});
    EXPECT_TRUE(result);
}

// Test: constexpr behavior - default case
TEST(IsCachePolicyTest_423, IsConstexprFalse_423) {
    constexpr is_cache_policy checker;
    constexpr bool result = checker(42);
    EXPECT_FALSE(result);
    static_assert(!checker(42), "Should be false at compile time for int");
}

// Test: constexpr behavior - with cache_policy struct
TEST(IsCachePolicyTest_423, IsConstexprTrue_423) {
    constexpr is_cache_policy checker;
    constexpr bool result = checker(dummy<HasCachePolicyStruct>{});
    EXPECT_TRUE(result);
    static_assert(checker(dummy<HasCachePolicyStruct>{}), "Should be true at compile time for cache policy struct");
}

// Test: noexcept guarantee
TEST(IsCachePolicyTest_423, IsNoexcept_423) {
    is_cache_policy checker;
    EXPECT_TRUE(noexcept(checker(0)));
    EXPECT_TRUE(noexcept(checker(dummy<HasCachePolicyStruct>{})));
}

// Test: Multiple calls yield consistent results
TEST(IsCachePolicyTest_423, ConsistentResults_423) {
    is_cache_policy checker;
    for (int i = 0; i < 10; ++i) {
        EXPECT_FALSE(checker(i));
    }
    for (int i = 0; i < 10; ++i) {
        EXPECT_TRUE(checker(dummy<HasCachePolicyStruct>{}));
    }
}

// Test: Passing a pointer to a struct without cache_policy
TEST(IsCachePolicyTest_423, ReturnsFalseForPointerType_423) {
    is_cache_policy checker;
    int* ptr = nullptr;
    bool result = checker(ptr);
    EXPECT_FALSE(result);
}

// Test: Passing a char
TEST(IsCachePolicyTest_423, ReturnsFalseForChar_423) {
    is_cache_policy checker;
    bool result = checker('a');
    EXPECT_FALSE(result);
}

// Test: Passing a bool
TEST(IsCachePolicyTest_423, ReturnsFalseForBool_423) {
    is_cache_policy checker;
    bool result = checker(true);
    EXPECT_FALSE(result);
}
