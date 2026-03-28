// File: tests/AnyTrueFactoryTests_193.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <vector>

// Public interface under test
#include <catch2/matchers/catch_matchers_quantifiers.hpp>

namespace {

using Catch::Matchers::AnyTrue;

TEST(AnyTrueFactoryTest_193, FactoryConstructsWithoutThrow_193) {
    EXPECT_NO_THROW({
        auto m = AnyTrue();
        (void)m; // suppress unused warning
    });
}

TEST(AnyTrueFactoryTest_193, ReturnedTypeIsMoveConstructibleAndAssignable_193) {
    using M = decltype(AnyTrue());
    // Compile-time guarantees about the returned type as used by standard containers
    static_assert(std::is_move_constructible<M>::value,
                  "AnyTrue() must return a move-constructible type");
    static_assert(std::is_move_assignable<M>::value,
                  "AnyTrue() must return a move-assignable type");
    SUCCEED(); // if we compiled, the assertions above held
}

TEST(AnyTrueFactoryTest_193, MultipleCallsYieldIndependentObjects_193) {
    auto a = AnyTrue();
    auto b = AnyTrue();

    // Different objects occupy different storage
    EXPECT_NE(std::addressof(a), std::addressof(b));
}

TEST(AnyTrueFactoryTest_193, UsableInStandardContainerContexts_193) {
    using M = decltype(AnyTrue());
    std::vector<M> v;
    // Pushing back constructed temporaries should be valid
    EXPECT_NO_THROW({
        v.push_back(AnyTrue());
        v.emplace_back(AnyTrue());
    });
    EXPECT_EQ(v.size(), 2u);
}

} // namespace
