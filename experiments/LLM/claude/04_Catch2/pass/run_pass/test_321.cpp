#include <catch2/generators/catch_generators.hpp>
#include <catch2/catch_test_macros.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <memory>

// We need to work with the Catch2 generator framework
// Create a simple generator that yields a fixed number of values
namespace Catch {
namespace Generators {

template <typename T>
class FixedGenerator : public IGenerator<T> {
    std::vector<T> m_values;
    size_t m_index = 0;
public:
    FixedGenerator(std::vector<T> values) : m_values(std::move(values)) {
        assert(!m_values.empty());
    }

    T const& get() const override {
        return m_values[m_index];
    }

    bool next() override {
        if (m_index + 1 < m_values.size()) {
            ++m_index;
            return true;
        }
        return false;
    }
};

template <typename T>
GeneratorWrapper<T> makeFixedGenerator(std::vector<T> values) {
    return GeneratorWrapper<T>(
        Catch::Detail::make_unique<FixedGenerator<T>>(std::move(values))
    );
}

} // namespace Generators
} // namespace Catch

using namespace Catch::Generators;

class GeneratorsTest_321 : public ::testing::Test {
protected:
};

// Test: Single generator with single value - next() should return false
TEST_F(GeneratorsTest_321, SingleGeneratorSingleValue_NextReturnsFalse_321) {
    auto gen = Generators<int>(makeFixedGenerator<int>({1}));
    
    // Initial get should return first value
    EXPECT_EQ(gen.get(), 1);
    
    // next() should return false since the single generator is exhausted
    // and there are no more generators
    EXPECT_FALSE(gen.next());
}

// Test: Single generator with multiple values
TEST_F(GeneratorsTest_321, SingleGeneratorMultipleValues_321) {
    auto gen = Generators<int>(makeFixedGenerator<int>({10, 20, 30}));
    
    EXPECT_EQ(gen.get(), 10);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 30);
    
    // Generator exhausted, no more generators
    EXPECT_FALSE(gen.next());
}

// Test: Multiple generators, each with single value
TEST_F(GeneratorsTest_321, MultipleGeneratorsSingleValueEach_321) {
    auto gen = Generators<int>(
        makeFixedGenerator<int>({1}),
        makeFixedGenerator<int>({2})
    );
    
    EXPECT_EQ(gen.get(), 1);
    
    // First generator exhausted, moves to second
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    
    // Second generator exhausted, no more
    EXPECT_FALSE(gen.next());
}

// Test: Multiple generators with multiple values each
TEST_F(GeneratorsTest_321, MultipleGeneratorsMultipleValues_321) {
    auto gen = Generators<int>(
        makeFixedGenerator<int>({1, 2}),
        makeFixedGenerator<int>({3, 4, 5})
    );
    
    EXPECT_EQ(gen.get(), 1);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    
    // First generator exhausted, move to second
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 4);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 5);
    
    EXPECT_FALSE(gen.next());
}

// Test: After exhaustion, repeated next() calls return false
TEST_F(GeneratorsTest_321, ExhaustedGeneratorKeepsReturningFalse_321) {
    auto gen = Generators<int>(makeFixedGenerator<int>({1}));
    
    EXPECT_FALSE(gen.next());
    EXPECT_FALSE(gen.next());
    EXPECT_FALSE(gen.next());
}

// Test: Three generators chained together
TEST_F(GeneratorsTest_321, ThreeGeneratorsChained_321) {
    auto gen = Generators<int>(
        makeFixedGenerator<int>({1}),
        makeFixedGenerator<int>({2}),
        makeFixedGenerator<int>({3})
    );
    
    EXPECT_EQ(gen.get(), 1);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);
    
    EXPECT_FALSE(gen.next());
}

// Test: Construction with plain values (not GeneratorWrappers)
TEST_F(GeneratorsTest_321, ConstructionWithPlainValues_321) {
    auto gen = Generators<int>(1, 2, 3);
    
    EXPECT_EQ(gen.get(), 1);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);
    
    EXPECT_FALSE(gen.next());
}

// Test: Mixed plain values and generator wrappers
TEST_F(GeneratorsTest_321, MixedValuesAndGenerators_321) {
    auto gen = Generators<int>(
        1,
        makeFixedGenerator<int>({2, 3}),
        4
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

// Test: String type generators
TEST_F(GeneratorsTest_321, StringTypeGenerators_321) {
    auto gen = Generators<std::string>(
        makeFixedGenerator<std::string>({"hello", "world"})
    );
    
    EXPECT_EQ(gen.get(), "hello");
    
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "world");
    
    EXPECT_FALSE(gen.next());
}

// Test: Get returns consistent value without calling next
TEST_F(GeneratorsTest_321, GetReturnsConsistentValueWithoutNext_321) {
    auto gen = Generators<int>(makeFixedGenerator<int>({42, 99}));
    
    EXPECT_EQ(gen.get(), 42);
    EXPECT_EQ(gen.get(), 42);
    EXPECT_EQ(gen.get(), 42);
    
    EXPECT_TRUE(gen.next());
    
    EXPECT_EQ(gen.get(), 99);
    EXPECT_EQ(gen.get(), 99);
}

// Test: Large number of generators
TEST_F(GeneratorsTest_321, ManyPlainValues_321) {
    auto gen = Generators<int>(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    
    for (int expected = 1; expected <= 10; ++expected) {
        EXPECT_EQ(gen.get(), expected);
        if (expected < 10) {
            EXPECT_TRUE(gen.next());
        } else {
            EXPECT_FALSE(gen.next());
        }
    }
}
