// File: tests/benchmark_function_operator_call_895.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include "Catch2/extras/catch_amalgamated.hpp"

namespace {
using BF = Catch::Benchmark::Detail::BenchmarkFunction;
using Chronometer = Catch::Benchmark::Chronometer;

// Simple callable types for constructing BenchmarkFunction
struct FunObject {
    void operator()(Chronometer) const {}
};

struct NonCallable {}; // Should NOT be usable to construct BF

} // namespace

// Ensures the type can be default-constructed per interface (no behavior assumed)
TEST(BenchmarkFunctionTraits_895, DefaultConstructible_895) {
    EXPECT_TRUE(std::is_default_constructible_v<BF>);
}

// Move/copy properties should match the interface (move only; copy deleted)
TEST(BenchmarkFunctionTraits_895, MoveAndCopySemantics_895) {
    EXPECT_TRUE(std::is_move_constructible_v<BF>);
    EXPECT_TRUE(std::is_move_assignable_v<BF>);
    EXPECT_FALSE(std::is_copy_constructible_v<BF>);
    EXPECT_FALSE(std::is_copy_assignable_v<BF>);
}

// Move operations declared noexcept in interface should be noexcept
TEST(BenchmarkFunctionTraits_895, NoexceptMoveSemantics_895) {
    EXPECT_TRUE(noexcept(BF(std::declval<BF&&>())));
    EXPECT_TRUE(noexcept(std::declval<BF&>() = std::declval<BF&&>()));
}

// The templated constructor should accept a callable (e.g., lambda or fun object)
TEST(BenchmarkFunctionConstruction_895, AcceptsCallable_895) {
    using Lambda = void(*)(Chronometer); // function pointer taking Chronometer
    auto lam = +[](Chronometer) {};

    EXPECT_TRUE((std::is_constructible_v<BF, FunObject>));
    EXPECT_TRUE((std::is_constructible_v<BF, decltype(lam)>));
    EXPECT_TRUE((std::is_constructible_v<BF, Lambda>));
}

// SFINAE guard: the templated constructor must not accept BenchmarkFunction itself
TEST(BenchmarkFunctionConstruction_895, RejectsSelfType_895) {
    // If SFINAE works (via is_related guard), constructing from BF should be ill-formed.
    EXPECT_FALSE((std::is_constructible_v<BF, BF>));
    EXPECT_FALSE((std::is_constructible_v<BF, const BF&>));
    EXPECT_FALSE((std::is_constructible_v<BF, BF&&>));
}

// Call operator: verify it's well-formed (type-level), returns void, and can be
// invoked with a Chronometer (we do NOT instantiate Chronometer at runtime).
TEST(BenchmarkFunctionCallable_895, OperatorSignatureWithChronometer_895) {
    // Check invocability on the type (no runtime construction of Chronometer).
    EXPECT_TRUE((std::is_invocable_v<const BF&, Chronometer>));

    // Ensure the return type is void, matching `void operator()(Chronometer) const`
    EXPECT_TRUE((std::is_same_v<
        void,
        std::invoke_result_t<const BF&, Chronometer>
    >));
}

// Non-callable types should NOT satisfy the Fun constructor (interface-level constraint)
TEST(BenchmarkFunctionConstruction_895, RejectsNonCallable_895) {
    EXPECT_FALSE((std::is_constructible_v<BF, NonCallable>));
}
