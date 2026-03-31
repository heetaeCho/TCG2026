#include <gtest/gtest.h>
#include <tuple>
#include <string>
#include <vector>

#include "catch2/generators/catch_generators.hpp"

// Test that table() with a single tuple of ints works correctly
TEST(CatchGeneratorsTableTest_322, SingleIntTuple_322) {
    auto gen = Catch::Generators::table<int, int>({
        std::make_tuple(1, 2)
    });

    auto const& val = gen.get();
    EXPECT_EQ(std::get<0>(val), 1);
    EXPECT_EQ(std::get<1>(val), 2);
    EXPECT_FALSE(gen.next());
}

// Test that table() with multiple tuples iterates through all values
TEST(CatchGeneratorsTableTest_322, MultipleIntTuples_322) {
    auto gen = Catch::Generators::table<int, int>({
        std::make_tuple(1, 2),
        std::make_tuple(3, 4),
        std::make_tuple(5, 6)
    });

    // First value
    EXPECT_EQ(std::get<0>(gen.get()), 1);
    EXPECT_EQ(std::get<1>(gen.get()), 2);

    // Second value
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(std::get<0>(gen.get()), 3);
    EXPECT_EQ(std::get<1>(gen.get()), 4);

    // Third value
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(std::get<0>(gen.get()), 5);
    EXPECT_EQ(std::get<1>(gen.get()), 6);

    // No more values
    EXPECT_FALSE(gen.next());
}

// Test table() with mixed types (int, string)
TEST(CatchGeneratorsTableTest_322, MixedTypes_322) {
    auto gen = Catch::Generators::table<int, std::string>({
        std::make_tuple(1, std::string("hello")),
        std::make_tuple(2, std::string("world"))
    });

    EXPECT_EQ(std::get<0>(gen.get()), 1);
    EXPECT_EQ(std::get<1>(gen.get()), "hello");

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(std::get<0>(gen.get()), 2);
    EXPECT_EQ(std::get<1>(gen.get()), "world");

    EXPECT_FALSE(gen.next());
}

// Test table() with three element tuples
TEST(CatchGeneratorsTableTest_322, ThreeElementTuples_322) {
    auto gen = Catch::Generators::table<int, double, bool>({
        std::make_tuple(1, 2.5, true),
        std::make_tuple(3, 4.5, false)
    });

    EXPECT_EQ(std::get<0>(gen.get()), 1);
    EXPECT_DOUBLE_EQ(std::get<1>(gen.get()), 2.5);
    EXPECT_EQ(std::get<2>(gen.get()), true);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(std::get<0>(gen.get()), 3);
    EXPECT_DOUBLE_EQ(std::get<1>(gen.get()), 4.5);
    EXPECT_EQ(std::get<2>(gen.get()), false);

    EXPECT_FALSE(gen.next());
}

// Test table() with a single element in tuple
TEST(CatchGeneratorsTableTest_322, SingleElementTuple_322) {
    auto gen = Catch::Generators::table<int>({
        std::make_tuple(42),
        std::make_tuple(100)
    });

    EXPECT_EQ(std::get<0>(gen.get()), 42);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(std::get<0>(gen.get()), 100);

    EXPECT_FALSE(gen.next());
}

// Test table() with boundary values (int limits)
TEST(CatchGeneratorsTableTest_322, BoundaryValues_322) {
    auto gen = Catch::Generators::table<int, int>({
        std::make_tuple(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()),
        std::make_tuple(0, 0)
    });

    EXPECT_EQ(std::get<0>(gen.get()), std::numeric_limits<int>::min());
    EXPECT_EQ(std::get<1>(gen.get()), std::numeric_limits<int>::max());

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(std::get<0>(gen.get()), 0);
    EXPECT_EQ(std::get<1>(gen.get()), 0);

    EXPECT_FALSE(gen.next());
}

// Test table() with empty strings
TEST(CatchGeneratorsTableTest_322, EmptyStrings_322) {
    auto gen = Catch::Generators::table<std::string, std::string>({
        std::make_tuple(std::string(""), std::string("")),
        std::make_tuple(std::string("a"), std::string(""))
    });

    EXPECT_EQ(std::get<0>(gen.get()), "");
    EXPECT_EQ(std::get<1>(gen.get()), "");

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(std::get<0>(gen.get()), "a");
    EXPECT_EQ(std::get<1>(gen.get()), "");

    EXPECT_FALSE(gen.next());
}

// Test that the returned GeneratorWrapper has the correct type
TEST(CatchGeneratorsTableTest_322, CorrectReturnType_322) {
    auto gen = Catch::Generators::table<int, double>({
        std::make_tuple(1, 1.0)
    });

    using expected_type = Catch::Generators::GeneratorWrapper<std::tuple<int, double>>;
    static_assert(std::is_same<decltype(gen), expected_type>::value,
                  "table() should return GeneratorWrapper of the correct tuple type");
    
    EXPECT_EQ(std::get<0>(gen.get()), 1);
    EXPECT_DOUBLE_EQ(std::get<1>(gen.get()), 1.0);
}

// Test table() with many rows to verify iteration completeness
TEST(CatchGeneratorsTableTest_322, ManyRows_322) {
    auto gen = Catch::Generators::table<int, int>({
        std::make_tuple(0, 0),
        std::make_tuple(1, 1),
        std::make_tuple(2, 4),
        std::make_tuple(3, 9),
        std::make_tuple(4, 16),
        std::make_tuple(5, 25),
        std::make_tuple(6, 36),
        std::make_tuple(7, 49),
        std::make_tuple(8, 64),
        std::make_tuple(9, 81)
    });

    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(std::get<0>(gen.get()), i);
        EXPECT_EQ(std::get<1>(gen.get()), i * i);
        if (i < 9) {
            EXPECT_TRUE(gen.next());
        } else {
            EXPECT_FALSE(gen.next());
        }
    }
}

// Test table() with negative values
TEST(CatchGeneratorsTableTest_322, NegativeValues_322) {
    auto gen = Catch::Generators::table<int, int>({
        std::make_tuple(-1, -2),
        std::make_tuple(-100, -200)
    });

    EXPECT_EQ(std::get<0>(gen.get()), -1);
    EXPECT_EQ(std::get<1>(gen.get()), -2);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(std::get<0>(gen.get()), -100);
    EXPECT_EQ(std::get<1>(gen.get()), -200);

    EXPECT_FALSE(gen.next());
}

// Test table() with floating point values
TEST(CatchGeneratorsTableTest_322, FloatingPointValues_322) {
    auto gen = Catch::Generators::table<double, double>({
        std::make_tuple(0.0, 0.0),
        std::make_tuple(1.1, 2.2),
        std::make_tuple(-3.3, 4.4)
    });

    EXPECT_DOUBLE_EQ(std::get<0>(gen.get()), 0.0);
    EXPECT_DOUBLE_EQ(std::get<1>(gen.get()), 0.0);

    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(std::get<0>(gen.get()), 1.1);
    EXPECT_DOUBLE_EQ(std::get<1>(gen.get()), 2.2);

    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(std::get<0>(gen.get()), -3.3);
    EXPECT_DOUBLE_EQ(std::get<1>(gen.get()), 4.4);

    EXPECT_FALSE(gen.next());
}
