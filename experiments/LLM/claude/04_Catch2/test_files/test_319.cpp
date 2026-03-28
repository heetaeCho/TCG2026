#include <gtest/gtest.h>
#include "catch2/generators/catch_generators.hpp"
#include <string>
#include <vector>

// Test that values() creates a generator with a single element
TEST(GeneratorsValuesTest_319, SingleIntValue_319) {
    auto gen = Catch::Generators::values({42});
    // The first value should be accessible via get()
    EXPECT_EQ(gen.get(), 42);
    // With only one value, next() should return false
    EXPECT_FALSE(gen.next());
}

// Test that values() creates a generator with multiple integer elements
TEST(GeneratorsValuesTest_319, MultipleIntValues_319) {
    auto gen = Catch::Generators::values({1, 2, 3});
    EXPECT_EQ(gen.get(), 1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);
    EXPECT_FALSE(gen.next());
}

// Test that values() works with string types
TEST(GeneratorsValuesTest_319, StringValues_319) {
    auto gen = Catch::Generators::values<std::string>({"hello", "world"});
    EXPECT_EQ(gen.get(), "hello");
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "world");
    EXPECT_FALSE(gen.next());
}

// Test that values() works with double types
TEST(GeneratorsValuesTest_319, DoubleValues_319) {
    auto gen = Catch::Generators::values({1.5, 2.5, 3.5});
    EXPECT_DOUBLE_EQ(gen.get(), 1.5);
    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 2.5);
    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 3.5);
    EXPECT_FALSE(gen.next());
}

// Test that values() works with negative integers
TEST(GeneratorsValuesTest_319, NegativeIntValues_319) {
    auto gen = Catch::Generators::values({-3, -2, -1, 0, 1});
    EXPECT_EQ(gen.get(), -3);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), -2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), -1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 0);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 1);
    EXPECT_FALSE(gen.next());
}

// Test that values() works with boolean types
TEST(GeneratorsValuesTest_319, BoolValues_319) {
    auto gen = Catch::Generators::values({true, false});
    EXPECT_EQ(gen.get(), true);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), false);
    EXPECT_FALSE(gen.next());
}

// Test that values() works with a single string value
TEST(GeneratorsValuesTest_319, SingleStringValue_319) {
    auto gen = Catch::Generators::values<std::string>({"only"});
    EXPECT_EQ(gen.get(), "only");
    EXPECT_FALSE(gen.next());
}

// Test that values() works with duplicate values
TEST(GeneratorsValuesTest_319, DuplicateValues_319) {
    auto gen = Catch::Generators::values({5, 5, 5});
    EXPECT_EQ(gen.get(), 5);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 5);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 5);
    EXPECT_FALSE(gen.next());
}

// Test that values() with char type
TEST(GeneratorsValuesTest_319, CharValues_319) {
    auto gen = Catch::Generators::values({'a', 'b', 'c'});
    EXPECT_EQ(gen.get(), 'a');
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 'b');
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 'c');
    EXPECT_FALSE(gen.next());
}

// Test that after exhaustion, next() continues to return false
TEST(GeneratorsValuesTest_319, ExhaustedGeneratorStaysExhausted_319) {
    auto gen = Catch::Generators::values({10});
    EXPECT_EQ(gen.get(), 10);
    EXPECT_FALSE(gen.next());
    // Calling next() again after exhaustion
    EXPECT_FALSE(gen.next());
}

// Test large number of values
TEST(GeneratorsValuesTest_319, LargeNumberOfValues_319) {
    auto gen = Catch::Generators::values({0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(gen.get(), i);
        if (i < 9) {
            EXPECT_TRUE(gen.next());
        } else {
            EXPECT_FALSE(gen.next());
        }
    }
}

// Test with unsigned integers
TEST(GeneratorsValuesTest_319, UnsignedIntValues_319) {
    auto gen = Catch::Generators::values<unsigned int>({0u, 100u, 200u});
    EXPECT_EQ(gen.get(), 0u);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 100u);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 200u);
    EXPECT_FALSE(gen.next());
}
