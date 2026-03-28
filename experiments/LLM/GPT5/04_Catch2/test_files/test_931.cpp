// File: tests/Generators_Map_Test_931.cpp
//
// These tests exercise the public observable behavior of Catch::Generators::map.
// We do NOT access private state or re-implement any internal logic.
// We validate results via GeneratorWrapper<T>::get() and ::next() only.

#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <utility>

#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Generators::map;
using Catch::Generators::value;
using Catch::Generators::values;

class GeneratorsMapTest_931 : public ::testing::Test {};

// [Normal operation] Mapping a simple arithmetic transformation over a finite sequence.
TEST_F(GeneratorsMapTest_931, MapsSimpleSequence_931) {
    auto base = values({1, 2, 3});
    auto doubled = map([](int x) { return x * 2; }, std::move(base));

    EXPECT_EQ(doubled.get(), 2);
    EXPECT_TRUE(doubled.next());

    EXPECT_EQ(doubled.get(), 4);
    EXPECT_TRUE(doubled.next());

    EXPECT_EQ(doubled.get(), 6);
    EXPECT_FALSE(doubled.next()); // End of sequence should report false
}

// [Boundary] Single-element sequence remains single after mapping; end reached immediately after first element.
TEST_F(GeneratorsMapTest_931, SingleElementBoundary_931) {
    auto base = value(42);
    auto plus_one = map([](int x) { return x + 1; }, std::move(base));

    EXPECT_EQ(plus_one.get(), 43);
    EXPECT_FALSE(plus_one.next()); // No second element
}

// [Exceptional case] If the mapping function throws for some element, the exception is observable.
TEST_F(GeneratorsMapTest_931, ExceptionPropagation_931) {
    auto base = values({0, 1});
    auto throwing = map(
        [](int x) -> int {
            if (x == 1) throw std::runtime_error("boom");
            return x;
        },
        std::move(base)
    );

    // First element is fine
    EXPECT_EQ(throwing.get(), 0);
    ASSERT_TRUE(throwing.next());

    // On the element that triggers the exception, the observable access throws
    EXPECT_THROW((void)throwing.get(), std::runtime_error);
}

// [Type transformation] Mapping can change the element type (int -> std::string).
TEST_F(GeneratorsMapTest_931, TypeTransformIntToString_931) {
    auto base = value(5);
    auto to_stringified = map(
        [](int x) { return std::string(static_cast<size_t>(x), 'a'); },
        std::move(base)
    );

    const std::string& s = to_stringified.get();
    EXPECT_EQ(s, "aaaaa");
    EXPECT_FALSE(to_stringified.next());
}

// [Composition] Mapping can be chained; results reflect sequential transformations.
TEST_F(GeneratorsMapTest_931, ChainedMapping_931) {
    auto base = values({1, 2});
    auto inc = map([](int x) { return x + 1; }, std::move(base));
    auto to_str = map([](int x) { return std::to_string(x); }, std::move(inc));

    EXPECT_EQ(to_str.get(), std::string("2"));
    EXPECT_TRUE(to_str.next());

    EXPECT_EQ(to_str.get(), std::string("3"));
    EXPECT_FALSE(to_str.next());
}
