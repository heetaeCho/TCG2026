#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <memory>

// Helper: A simple IGenerator implementation for testing
template<typename T>
class FixedValueGenerator final : public Catch::Generators::IGenerator<T> {
    std::vector<T> m_values;
    size_t m_index = 0;
public:
    explicit FixedValueGenerator(std::vector<T> values)
        : m_values(std::move(values)) {
        assert(!m_values.empty());
    }

    T const& get() const override {
        return m_values[m_index];
    }

    bool next() override {
        ++m_index;
        return m_index < m_values.size();
    }
};

template<typename T>
Catch::Generators::GeneratorWrapper<T> makeFixedGenerator(std::vector<T> values) {
    return Catch::Generators::GeneratorWrapper<T>(
        Catch::Detail::make_unique<FixedValueGenerator<T>>(std::move(values))
    );
}

class MakeGeneratorsTest_323 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that makeGenerators with a single generator works and returns expected first value
TEST_F(MakeGeneratorsTest_323, SingleGeneratorReturnsFirstValue_323) {
    auto gen = Catch::Generators::makeGenerators(
        makeFixedGenerator<int>({10, 20, 30})
    );

    EXPECT_EQ(gen.get(), 10);
}

// Test that next() advances through values in a single generator
TEST_F(MakeGeneratorsTest_323, SingleGeneratorNextAdvances_323) {
    auto gen = Catch::Generators::makeGenerators(
        makeFixedGenerator<int>({10, 20, 30})
    );

    EXPECT_EQ(gen.get(), 10);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 30);
}

// Test that next() returns false when single generator is exhausted
TEST_F(MakeGeneratorsTest_323, SingleGeneratorExhausted_323) {
    auto gen = Catch::Generators::makeGenerators(
        makeFixedGenerator<int>({10})
    );

    EXPECT_EQ(gen.get(), 10);
    EXPECT_FALSE(gen.next());
}

// Test that makeGenerators with multiple generators chains them
TEST_F(MakeGeneratorsTest_323, MultipleGeneratorsChained_323) {
    auto gen = Catch::Generators::makeGenerators(
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

// Test with three generators chained together
TEST_F(MakeGeneratorsTest_323, ThreeGeneratorsChained_323) {
    auto gen = Catch::Generators::makeGenerators(
        makeFixedGenerator<int>({100}),
        makeFixedGenerator<int>({200}),
        makeFixedGenerator<int>({300})
    );

    EXPECT_EQ(gen.get(), 100);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 200);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 300);
    EXPECT_FALSE(gen.next());
}

// Test with string type
TEST_F(MakeGeneratorsTest_323, StringTypeGenerators_323) {
    auto gen = Catch::Generators::makeGenerators(
        makeFixedGenerator<std::string>({"hello", "world"}),
        makeFixedGenerator<std::string>({"foo"})
    );

    EXPECT_EQ(gen.get(), "hello");
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "world");
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "foo");
    EXPECT_FALSE(gen.next());
}

// Test single element single generator boundary
TEST_F(MakeGeneratorsTest_323, SingleElementSingleGenerator_323) {
    auto gen = Catch::Generators::makeGenerators(
        makeFixedGenerator<double>({3.14})
    );

    EXPECT_DOUBLE_EQ(gen.get(), 3.14);
    EXPECT_FALSE(gen.next());
}

// Test multiple generators each with single element
TEST_F(MakeGeneratorsTest_323, MultipleGeneratorsSingleElement_323) {
    auto gen = Catch::Generators::makeGenerators(
        makeFixedGenerator<int>({1}),
        makeFixedGenerator<int>({2}),
        makeFixedGenerator<int>({3}),
        makeFixedGenerator<int>({4}),
        makeFixedGenerator<int>({5})
    );

    std::vector<int> collected;
    collected.push_back(gen.get());
    while (gen.next()) {
        collected.push_back(gen.get());
    }

    EXPECT_EQ(collected, (std::vector<int>{1, 2, 3, 4, 5}));
}

// Test that get() returns consistent value without calling next()
TEST_F(MakeGeneratorsTest_323, GetIsIdempotent_323) {
    auto gen = Catch::Generators::makeGenerators(
        makeFixedGenerator<int>({42, 99})
    );

    EXPECT_EQ(gen.get(), 42);
    EXPECT_EQ(gen.get(), 42);
    EXPECT_EQ(gen.get(), 42);
}

// Test large number of values
TEST_F(MakeGeneratorsTest_323, LargeNumberOfValues_323) {
    std::vector<int> values;
    for (int i = 0; i < 1000; ++i) {
        values.push_back(i);
    }

    auto gen = Catch::Generators::makeGenerators(
        makeFixedGenerator<int>(values)
    );

    for (int i = 0; i < 1000; ++i) {
        EXPECT_EQ(gen.get(), i);
        if (i < 999) {
            EXPECT_TRUE(gen.next());
        } else {
            EXPECT_FALSE(gen.next());
        }
    }
}

// Test transition between generators in chain
TEST_F(MakeGeneratorsTest_323, TransitionBetweenGenerators_323) {
    auto gen = Catch::Generators::makeGenerators(
        makeFixedGenerator<int>({1, 2, 3}),
        makeFixedGenerator<int>({10, 20, 30})
    );

    // Exhaust first generator
    EXPECT_EQ(gen.get(), 1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);

    // Transition to second generator
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 10);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 30);

    EXPECT_FALSE(gen.next());
}
