// File: make_generators_tests_323.cpp
#include <gtest/gtest.h>

#include <catch2/generators/catch_generators.hpp>  // from your codebase
#include <memory>
#include <type_traits>

namespace CG = Catch::Generators;

class MakeGeneratorsTest_323 : public ::testing::Test {};

// [Normal] Single wrapper -> first value available via get(); then exhausted
TEST(MakeGeneratorsTest_323, SingleWrapper_YieldsThenExhausted_323) {
    auto gens = CG::makeGenerators(CG::value(123));

    // Compile-time: returned type is Generators<int>
    using GType = decltype(gens);
    static_assert(std::is_same<GType, CG::Generators<int>>::value,
                  "makeGenerators should return Generators<T>");

    EXPECT_EQ(gens.get(), 123);
    // After single value, there is no next element
    EXPECT_FALSE(gens.next());
}

// [Normal] Multiple wrappers are traversed in order
TEST(MakeGeneratorsTest_323, Aggregates_MultipleWrappersInOrder_323) {
    auto gens = CG::makeGenerators(CG::value(1), CG::values({2, 3}));

    // Initial value from the first generator
    EXPECT_EQ(gens.get(), 1);

    // Move to the next underlying generator
    EXPECT_TRUE(gens.next());
    EXPECT_EQ(gens.get(), 2);

    // Stay within the same underlying generator until it finishes
    EXPECT_TRUE(gens.next());
    EXPECT_EQ(gens.get(), 3);

    // All done
    EXPECT_FALSE(gens.next());
}

// [Boundary] It should accept non-wrapper additional args convertible to T
TEST(MakeGeneratorsTest_323, Forwards_ConvertibleNonWrapperArgs_323) {
    // First arg fixes T=int via GeneratorWrapper<int>; second arg is double
    auto gens = CG::makeGenerators(CG::value(10), 4.7 /* convertible to int */);

    EXPECT_EQ(gens.get(), 10);

    // Advance to the converted value
    EXPECT_TRUE(gens.next());
    // Converted/truncated as per T's construction rules (observable via get)
    EXPECT_EQ(gens.get(), 4);

    EXPECT_FALSE(gens.next());
}

// [Boundary] Works with move-only types (e.g., std::unique_ptr)
TEST(MakeGeneratorsTest_323, Supports_MoveOnlyTypes_323) {
    auto gens = CG::makeGenerators(
        CG::value(std::make_unique<int>(5)),
        std::make_unique<int>(6) // non-wrapper, forwarded into T
    );

    // Observe first pointer/value without moving from it
    const std::unique_ptr<int>& p1 = gens.get();
    ASSERT_TRUE(p1);
    EXPECT_EQ(*p1, 5);

    // Advance to second element
    EXPECT_TRUE(gens.next());
    const std::unique_ptr<int>& p2 = gens.get();
    ASSERT_TRUE(p2);
    EXPECT_EQ(*p2, 6);

    EXPECT_FALSE(gens.next());
}

// [Edge-flow] Calling next() before any get() should advance correctly
TEST(MakeGeneratorsTest_323, NextBeforeGet_SkipsToNextGenerator_323) {
    auto gens = CG::makeGenerators(CG::value(1), CG::value(2));

    // First underlying generator has a single value; next() moves past it
    EXPECT_TRUE(gens.next());   // there is still another generator afterwards
    EXPECT_EQ(gens.get(), 2);   // now observing from the second generator
    EXPECT_FALSE(gens.next());  // fully exhausted
}
