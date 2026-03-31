#include "catch2/generators/catch_generators.hpp"
#include "catch2/generators/catch_generator_exception.hpp"
#include "catch2/internal/catch_source_line_info.hpp"

#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace Catch::Generators;

// Helper: A simple generator that produces a fixed sequence of values
template <typename T>
class FixedValuesGenerator : public IGenerator<T> {
    std::vector<T> m_values;
    size_t m_idx = 0;
public:
    explicit FixedValuesGenerator(std::vector<T> values)
        : m_values(std::move(values)) {}

    T const& get() const override {
        return m_values[m_idx];
    }

    bool next() override {
        ++m_idx;
        return m_idx < m_values.size();
    }
};

template <typename T>
GeneratorWrapper<T> makeFixedGenerator(std::vector<T> values) {
    return GeneratorWrapper<T>(
        Catch::Detail::make_unique<FixedValuesGenerator<T>>(std::move(values))
    );
}

class GeneratorsTest_320 : public ::testing::Test {
protected:
};

// Test that a single plain value can be stored and retrieved
TEST_F(GeneratorsTest_320, SingleValue_Get_320) {
    auto gen = Generators<int>(42);
    EXPECT_EQ(gen.get(), 42);
}

// Test that next() returns false for a single value (no more elements)
TEST_F(GeneratorsTest_320, SingleValue_NextReturnsFalse_320) {
    auto gen = Generators<int>(42);
    EXPECT_FALSE(gen.next());
}

// Test multiple plain values
TEST_F(GeneratorsTest_320, MultipleValues_Iteration_320) {
    auto gen = Generators<int>(1, 2, 3);
    EXPECT_EQ(gen.get(), 1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);
    EXPECT_FALSE(gen.next());
}

// Test with a GeneratorWrapper as argument
TEST_F(GeneratorsTest_320, SingleGeneratorWrapper_320) {
    auto gen = Generators<int>(makeFixedGenerator<int>({10, 20, 30}));
    EXPECT_EQ(gen.get(), 10);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 30);
    EXPECT_FALSE(gen.next());
}

// Test mixing values and generators
TEST_F(GeneratorsTest_320, MixedValuesAndGenerators_320) {
    auto gen = Generators<int>(1, makeFixedGenerator<int>({2, 3}), 4);
    EXPECT_EQ(gen.get(), 1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 4);
    EXPECT_FALSE(gen.next());
}

// Test with string type
TEST_F(GeneratorsTest_320, StringValues_320) {
    auto gen = Generators<std::string>(std::string("hello"), std::string("world"));
    EXPECT_EQ(gen.get(), "hello");
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "world");
    EXPECT_FALSE(gen.next());
}

// Test multiple generators chained together
TEST_F(GeneratorsTest_320, MultipleGeneratorWrappers_320) {
    auto gen = Generators<int>(
        makeFixedGenerator<int>({1, 2}),
        makeFixedGenerator<int>({3, 4})
    );
    EXPECT_EQ(gen.get(), 1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 4);
    EXPECT_FALSE(gen.next());
}

// Test that get() returns consistent value without calling next()
TEST_F(GeneratorsTest_320, GetIsIdempotent_320) {
    auto gen = Generators<int>(42, 99);
    EXPECT_EQ(gen.get(), 42);
    EXPECT_EQ(gen.get(), 42);
    EXPECT_EQ(gen.get(), 42);
}

// Test with implicitly convertible types (e.g., int to double)
TEST_F(GeneratorsTest_320, ImplicitConversion_320) {
    auto gen = Generators<double>(1, 2.5, 3);
    EXPECT_DOUBLE_EQ(gen.get(), 1.0);
    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 2.5);
    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 3.0);
    EXPECT_FALSE(gen.next());
}

// Test single generator wrapper with one element
TEST_F(GeneratorsTest_320, SingleElementGenerator_320) {
    auto gen = Generators<int>(makeFixedGenerator<int>({99}));
    EXPECT_EQ(gen.get(), 99);
    EXPECT_FALSE(gen.next());
}

// Test value followed by generator
TEST_F(GeneratorsTest_320, ValueThenGenerator_320) {
    auto gen = Generators<int>(0, makeFixedGenerator<int>({1}));
    EXPECT_EQ(gen.get(), 0);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 1);
    EXPECT_FALSE(gen.next());
}

// Test generator followed by value
TEST_F(GeneratorsTest_320, GeneratorThenValue_320) {
    auto gen = Generators<int>(makeFixedGenerator<int>({1}), 0);
    EXPECT_EQ(gen.get(), 1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 0);
    EXPECT_FALSE(gen.next());
}

// Test many values to check boundary handling
TEST_F(GeneratorsTest_320, ManyValues_320) {
    auto gen = Generators<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    for (int i = 1; i <= 10; ++i) {
        EXPECT_EQ(gen.get(), i);
        if (i < 10) {
            EXPECT_TRUE(gen.next());
        } else {
            EXPECT_FALSE(gen.next());
        }
    }
}
