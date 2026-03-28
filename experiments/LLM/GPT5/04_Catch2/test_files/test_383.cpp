// BoundManyLambda_isContainer_tests_383.cpp
#include <gtest/gtest.h>

// Include the interface under test
#include "Catch2/src/catch2/internal/catch_clara.hpp"

namespace {

using namespace Catch::Clara::Detail;

// TEST_ID: 383

// Basic behavior: isContainer() should return true.
TEST(BoundManyLambdaTest_383, IsContainer_ReturnsTrue_383) {
    auto lambda = [](auto&&...) {};
    using L = decltype(lambda);
    BoundManyLambda<L> bound(lambda);

    EXPECT_TRUE(bound.isContainer());
}

// Const-correctness: callable on a const object and still returns true.
TEST(BoundManyLambdaTest_383, IsContainer_ConstObject_ReturnsTrue_383) {
    auto lambda = [](auto&&...) {};
    using L = decltype(lambda);
    const BoundManyLambda<L> bound(lambda);

    EXPECT_TRUE(bound.isContainer());
}

// Polymorphic call through the base class should still observe `true`.
// This validates the override behavior without relying on internal state.
TEST(BoundManyLambdaTest_383, IsContainer_ViaBaseReference_ReturnsTrue_383) {
    auto lambda = [](auto&&...) {};
    using L = decltype(lambda);
    BoundManyLambda<L> derived(lambda);

    // Upcast to the base class referenced in the interface snippet.
    BoundLambda<L>& baseRef = derived;
    EXPECT_TRUE(baseRef.isContainer());
}

// Copy semantics should not affect the observable result of isContainer().
TEST(BoundManyLambdaTest_383, IsContainer_AfterCopy_ReturnsTrue_383) {
    auto lambda = [](auto&&...) {};
    using L = decltype(lambda);
    BoundManyLambda<L> original(lambda);
    BoundManyLambda<L> copy = original; // copy-construct

    EXPECT_TRUE(original.isContainer());
    EXPECT_TRUE(copy.isContainer());
}

// Move semantics should not affect the observable result of isContainer().
TEST(BoundManyLambdaTest_383, IsContainer_AfterMove_ReturnsTrue_383) {
    auto lambda = [](auto&&...) {};
    using L = decltype(lambda);
    BoundManyLambda<L> original(lambda);
    BoundManyLambda<L> moved = std::move(original); // move-construct

    // Even after move, the moved-to object should report true.
    EXPECT_TRUE(moved.isContainer());
}

} // namespace
