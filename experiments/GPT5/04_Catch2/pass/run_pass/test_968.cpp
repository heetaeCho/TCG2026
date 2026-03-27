// File: tests/EqualsMatcher_vector_tests_968.cpp

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <memory>
#if __has_include(<memory_resource>)
  #include <memory_resource>
  #define HAS_PMR 1
#else
  #define HAS_PMR 0
#endif

// Include the provided (amalgamated) Catch2 header that defines EqualsMatcher.
// Adjust the include path to match your project layout.
#include "Catch2/extras/catch_amalgamated.hpp"

namespace {

template <typename T,
          typename AllocComp = std::allocator<T>,
          typename AllocMatch = std::allocator<T>>
using VecEqualsMatcher =
    Catch::Matchers::EqualsMatcher<T, AllocComp, AllocMatch>;

struct POD {
    int a{};
    int b{};
    // Observable equality via operator==
    bool operator==(const POD& other) const {
        return a == other.a && b == other.b;
    }
};

class EqualsMatcherTest_968 : public ::testing::Test {
protected:
    template <typename T, typename AC = std::allocator<T>, typename AM = std::allocator<T>>
    VecEqualsMatcher<T, AC, AM> makeMatcher(const std::vector<T, AC>& comp) {
        return VecEqualsMatcher<T, AC, AM>(comp);
    }
};

} // namespace

// Normal operation: empty vectors compare equal
TEST_F(EqualsMatcherTest_968, EmptyVectors_ReturnsTrue_968) {
    std::vector<int> comp{};
    auto matcher = makeMatcher<int>(comp);
    std::vector<int> candidate{};
    EXPECT_TRUE(matcher.match(candidate));
}

// Normal operation: same elements & same order -> true
TEST_F(EqualsMatcherTest_968, SameElementsSameOrder_ReturnsTrue_968) {
    std::vector<int> comp{1, 2, 3, 4};
    auto matcher = makeMatcher<int>(comp);
    std::vector<int> candidate{1, 2, 3, 4};
    EXPECT_TRUE(matcher.match(candidate));
}

// Boundary condition: size differs -> false
TEST_F(EqualsMatcherTest_968, DifferentSize_ReturnsFalse_968) {
    std::vector<int> comp{1, 2, 3};
    auto matcher = makeMatcher<int>(comp);
    std::vector<int> candidate{1, 2, 3, 4};
    EXPECT_FALSE(matcher.match(candidate));
}

// Boundary condition: same size, at least one element differs -> false
TEST_F(EqualsMatcherTest_968, SameSizeDifferentElements_ReturnsFalse_968) {
    std::vector<int> comp{1, 2, 3};
    auto matcher = makeMatcher<int>(comp);
    std::vector<int> candidate{1, 99, 3};
    EXPECT_FALSE(matcher.match(candidate));
}

// Normal operation with user-defined type relying only on operator==
// (verifies observable behavior with non-primitive elements)
TEST_F(EqualsMatcherTest_968, WorksWithCustomType_OperatorEqUsed_968) {
    std::vector<POD> comp{{1,2}, {3,4}};
    auto matcher = makeMatcher<POD>(comp);
    std::vector<POD> same{{1,2}, {3,4}};
    std::vector<POD> diff{{1,2}, {3,999}};

    EXPECT_TRUE(matcher.match(same));
    EXPECT_FALSE(matcher.match(diff));
}

// Interface coverage: describe() should be callable without throwing
// (we make no assumptions about its contents)
TEST_F(EqualsMatcherTest_968, Describe_DoesNotThrow_968) {
    std::vector<int> comp{10, 20};
    auto matcher = makeMatcher<int>(comp);
    EXPECT_NO_THROW({
        auto s = matcher.describe();
        (void)s; // avoid unused warning
    });
}

#if HAS_PMR
// Allocator variability (observable): support matching against a vector with
// a different allocator type than the comparator vector.
TEST_F(EqualsMatcherTest_968, DifferentAllocatorTypes_StillComparesByValue_968) {
    std::pmr::monotonic_buffer_resource pool;
    std::pmr::vector<int> candidate{&pool};
    candidate.assign({7, 8, 9});

    // Comparator uses default std::allocator; candidate uses pmr allocator.
    std::vector<int> comp{7, 8, 9};
    // Instantiate matcher whose comparator allocator differs from the match argument allocator.
    VecEqualsMatcher<int, std::allocator<int>, std::pmr::polymorphic_allocator<int>> matcher(comp);

    EXPECT_TRUE(matcher.match(candidate));
}
#endif
