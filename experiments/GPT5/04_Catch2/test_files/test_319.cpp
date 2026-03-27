// File: values_generator_tests_319.cpp
#include <gtest/gtest.h>
#include <catch2/generators/catch_generators.hpp>
#include <string>

using Catch::Generators::values;
using Catch::Generators::GeneratorWrapper;

class ValuesGeneratorTest_319 : public ::testing::Test {};

// [Normal] Yields all provided ints in order, then reports exhaustion.
TEST_F(ValuesGeneratorTest_319, IntsYieldInOrderAndThenExhaust_319) {
    GeneratorWrapper<int> gen = values<int>({1, 2, 3});

    EXPECT_EQ(gen.get(), 1);          // first value observable immediately
    EXPECT_TRUE(gen.next());          // can advance
    EXPECT_EQ(gen.get(), 2);          // second value
    EXPECT_TRUE(gen.next());          // advance again
    EXPECT_EQ(gen.get(), 3);          // third value
    EXPECT_FALSE(gen.next());         // no more values
    // After exhaustion, observable behavior should remain stable (still last value)
    EXPECT_EQ(gen.get(), 3);
}

// [Normal] Works with non-primitive types (e.g., std::string).
TEST_F(ValuesGeneratorTest_319, StringsYieldInOrder_319) {
    auto gen = values<std::string>({"alpha", "beta"});

    EXPECT_EQ(gen.get(), "alpha");
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "beta");
    EXPECT_FALSE(gen.next());
    EXPECT_EQ(gen.get(), "beta");
}

// [Boundary] Single-element list: available, then immediately exhausted.
TEST_F(ValuesGeneratorTest_319, SingleElementBoundary_319) {
    auto gen = values<int>({42});

    EXPECT_EQ(gen.get(), 42);
    EXPECT_FALSE(gen.next());     // already at the only value
    EXPECT_EQ(gen.get(), 42);     // remains observable
}

// [Exceptional] Empty initializer list should be an error that is observable
// via exception when constructing/obtaining the generator.
TEST_F(ValuesGeneratorTest_319, EmptyInitializerListThrows_319) {
    // The concrete exception type lives in Catch2, but we only assert that
    // an exception derived from std::exception is thrown (observable failure).
    EXPECT_THROW(
        (void)values<int>({}),
        std::exception
    );
}

// [Interaction] The generator should not modify (mutate) the values it exposes.
// We verify by observing unchanged values across repeated get() calls without next().
TEST_F(ValuesGeneratorTest_319, RepeatedGetDoesNotChangeValue_319) {
    auto gen = values<std::string>({"same", "next"});

    const std::string& first_ref = gen.get();
    EXPECT_EQ(first_ref, "same");
    // Repeated get() calls should keep returning the same observable value
    EXPECT_EQ(gen.get(), "same");
    EXPECT_EQ(gen.get(), "same");

    // After advancing once, the observable value changes accordingly
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "next");
}
