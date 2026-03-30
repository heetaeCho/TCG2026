// File: tests/ApproxVectorMatcher_980_Test.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <vector>

// Include the amalgamated Catch2 header that exposes the Approx(...) factory
#include "Catch2/extras/catch_amalgamated.hpp"

// Minimal custom allocator to verify allocator propagation through the template
template <typename T>
struct MyAlloc : std::allocator<T> {
    using value_type = T;
    MyAlloc() noexcept = default;
    template <class U>
    MyAlloc(const MyAlloc<U>&) noexcept {}
};

// Shorthand to the namespace where Approx is defined
namespace CM = Catch::Matchers;

//
// Normal operation: basic double vector -> returns the expected ApproxMatcher type
//
TEST(ApproxVectorMatcher_980, ReturnsApproxMatcher_WithDoubleVector_980) {
    std::vector<double> comp{1.0, 2.0, 3.0};

    auto m = CM::Approx(comp);

    using Expected = CM::ApproxMatcher<double, std::allocator<double>, std::allocator<double>>;
    static_assert(std::is_same<decltype(m), Expected>::value,
                  "Approx(comp) must return ApproxMatcher<double, std::allocator<double>, std::allocator<double>>");
    (void)m; // silence unused warning
}

//
// Normal operation: float vector -> expected ApproxMatcher type
//
TEST(ApproxVectorMatcher_980, ReturnsApproxMatcher_WithFloatVector_980) {
    std::vector<float> comp{0.1f, 0.2f};

    auto m = CM::Approx(comp);

    using Expected = CM::ApproxMatcher<float, std::allocator<float>, std::allocator<float>>;
    static_assert(std::is_same<decltype(m), Expected>::value,
                  "Approx(comp) must return ApproxMatcher<float, std::allocator<float>, std::allocator<float>>");
    (void)m;
}

//
// Boundary condition: empty comparator vector should still construct without throwing
//
TEST(ApproxVectorMatcher_980, Constructs_WithEmptyComparatorVector_980) {
    std::vector<int> empty;

    EXPECT_NO_THROW({
        auto m = CM::Approx(empty);
        using Expected = CM::ApproxMatcher<int, std::allocator<int>, std::allocator<int>>;
        static_assert(std::is_same<decltype(m), Expected>::value, "Type should still match for empty comparator");
        (void)m;
    });
}

//
// Boundary condition: large comparator vector should still construct and return correct type
//
TEST(ApproxVectorMatcher_980, Constructs_WithLargeComparatorVector_980) {
    std::vector<int> comp(1000, 42);

    auto m = CM::Approx(comp);

    using Expected = CM::ApproxMatcher<int, std::allocator<int>, std::allocator<int>>;
    static_assert(std::is_same<decltype(m), Expected>::value, "Type must match for large comparator");
    (void)m;
}

//
// Allocator propagation: custom allocator in comparator should propagate to the ApproxMatcher template args
//
TEST(ApproxVectorMatcher_980, PropagatesCustomAllocator_980) {
    using A = MyAlloc<float>;
    std::vector<float, A> comp{1.0f, 2.0f};

    auto m = CM::Approx(comp);

    using Expected = CM::ApproxMatcher<float, A, A>;
    static_assert(std::is_same<decltype(m), Expected>::value,
                  "Allocator type used by the comparator vector must appear in ApproxMatcher<T, AllocComp, AllocMatch>");
    (void)m;
}

//
// Type traits / external interactions with standard C++: returned matcher should be copy/move constructible
//
TEST(ApproxVectorMatcher_980, MatcherIsCopyAndMoveConstructible_980) {
    std::vector<double> comp{4.0, 5.0};

    auto m = CM::Approx(comp);
    using M = decltype(m);

    static_assert(std::is_copy_constructible<M>::value, "Matcher should be copy-constructible");
    static_assert(std::is_move_constructible<M>::value, "Matcher should be move-constructible");

    // Runtime check that copy/move are viable (observable via successful compilation and no throws)
    M copy(m);           // copy
    M moved(std::move(m)); // move
    (void)copy;
    (void)moved;
}

//
// Sanity: works with integral comparator vector as well
//
TEST(ApproxVectorMatcher_980, ReturnsApproxMatcher_WithIntVector_980) {
    std::vector<int> comp{1, 2, 3};

    auto m = CM::Approx(comp);

    using Expected = CM::ApproxMatcher<int, std::allocator<int>, std::allocator<int>>;
    static_assert(std::is_same<decltype(m), Expected>::value,
                  "Approx(comp) must return ApproxMatcher<int, std::allocator<int>, std::allocator<int>>");
    (void)m;
}
