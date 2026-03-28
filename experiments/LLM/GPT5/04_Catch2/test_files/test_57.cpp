// File: generator_untyped_base_test_57.cpp
#include <gtest/gtest.h>
#include "catch2/interfaces/catch_interfaces_generatortracker.hpp"

using Catch::Generators::GeneratorUntypedBase;

// These tests treat the class strictly as a black box and only use its public API.
// No assumptions are made about internal state beyond what's observable via
// currentElementIndex() and default construction semantics.

/*
 * Normal operation: a default-constructed object reports its current element index.
 * Boundary: since the index is size_t, the minimal boundary is 0.
 * Exceptional cases & external interactions are not observable through this interface.
 */

TEST(GeneratorUntypedBaseTest_57, DefaultConstructed_IndexIsZero_57) {
    GeneratorUntypedBase gen;
    // From the provided interface + known defaults, freshly constructed index should be 0.
    EXPECT_EQ(static_cast<std::size_t>(0), gen.currentElementIndex());
}

TEST(GeneratorUntypedBaseTest_57, RepeatedCalls_AreIdempotent_57) {
    GeneratorUntypedBase gen;
    auto first = gen.currentElementIndex();
    auto second = gen.currentElementIndex();
    EXPECT_EQ(first, second);
}

TEST(GeneratorUntypedBaseTest_57, WorksThroughConstReference_57) {
    const GeneratorUntypedBase gen{};
    // Method is const; calling it via a const object should compile and return a value.
    auto idx = gen.currentElementIndex();
    // idx should be a valid size_t; additionally verify expected initial boundary.
    EXPECT_EQ(static_cast<std::size_t>(0), idx);
}

TEST(GeneratorUntypedBaseTest_57, CopyConstruction_PreservesObservableIndex_57) {
    GeneratorUntypedBase original;
    const auto originalIndex = original.currentElementIndex();

    GeneratorUntypedBase copy = original;
    EXPECT_EQ(originalIndex, copy.currentElementIndex());
}

TEST(GeneratorUntypedBaseTest_57, CopyAssignment_PreservesObservableIndex_57) {
    GeneratorUntypedBase a;
    GeneratorUntypedBase b;
    // Establish baselines only through the public accessor.
    const auto aIndex = a.currentElementIndex();

    b = a; // public operator= is defaulted per provided interface
    EXPECT_EQ(aIndex, b.currentElementIndex());
}
