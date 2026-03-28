#include <gtest/gtest.h>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>
#include <string>
#include <vector>
#include <type_traits>

// We need to work with the Catch2 Generators namespace
using namespace Catch::Generators;

// Helper: A simple generator that yields values from a vector
template <typename T>
class FixedValuesGenerator : public IGenerator<T> {
    std::vector<T> m_values;
    size_t m_idx = 0;
public:
    FixedValuesGenerator(std::vector<T> values) : m_values(std::move(values)) {}

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

// Test fixture
class GeneratorsTest_1056 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Single value constructor - get returns that value
TEST_F(GeneratorsTest_1056, SingleValueGet_1056) {
    Generators<int> gen(1);
    EXPECT_EQ(gen.get(), 1);
}

// Test: Single value constructor - next returns false (only one element)
TEST_F(GeneratorsTest_1056, SingleValueNextReturnsFalse_1056) {
    Generators<int> gen(42);
    EXPECT_EQ(gen.get(), 42);
    EXPECT_FALSE(gen.next());
}

// Test: Multiple values - get returns first value initially
TEST_F(GeneratorsTest_1056, MultipleValuesGetReturnsFirst_1056) {
    Generators<int> gen(10, 20, 30);
    EXPECT_EQ(gen.get(), 10);
}

// Test: Multiple values - next iterates through all values
TEST_F(GeneratorsTest_1056, MultipleValuesIteration_1056) {
    Generators<int> gen(10, 20, 30);
    EXPECT_EQ(gen.get(), 10);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 30);
    EXPECT_FALSE(gen.next());
}

// Test: GeneratorWrapper as argument
TEST_F(GeneratorsTest_1056, GeneratorWrapperArgument_1056) {
    auto wrapper = makeFixedGenerator<int>({100, 200, 300});
    Generators<int> gen(std::move(wrapper));
    EXPECT_EQ(gen.get(), 100);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 200);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 300);
    EXPECT_FALSE(gen.next());
}

// Test: Mix of values and generator wrappers
TEST_F(GeneratorsTest_1056, MixedValuesAndGenerators_1056) {
    auto wrapper = makeFixedGenerator<int>({50, 60});
    Generators<int> gen(10, 20, std::move(wrapper));
    EXPECT_EQ(gen.get(), 10);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 50);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 60);
    EXPECT_FALSE(gen.next());
}

// Test: String type values
TEST_F(GeneratorsTest_1056, StringTypeValues_1056) {
    Generators<std::string> gen(std::string("hello"), std::string("world"));
    EXPECT_EQ(gen.get(), "hello");
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "world");
    EXPECT_FALSE(gen.next());
}

// Test: Double type values
TEST_F(GeneratorsTest_1056, DoubleTypeValues_1056) {
    Generators<double> gen(1.5, 2.5, 3.5);
    EXPECT_DOUBLE_EQ(gen.get(), 1.5);
    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 2.5);
    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 3.5);
    EXPECT_FALSE(gen.next());
}

// Test: Multiple generator wrappers concatenated
TEST_F(GeneratorsTest_1056, MultipleGeneratorWrappersConcatenated_1056) {
    auto wrapper1 = makeFixedGenerator<int>({1, 2});
    auto wrapper2 = makeFixedGenerator<int>({3, 4});
    Generators<int> gen(std::move(wrapper1), std::move(wrapper2));
    EXPECT_EQ(gen.get(), 1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 4);
    EXPECT_FALSE(gen.next());
}

// Test: Value followed by generator wrapper followed by value
TEST_F(GeneratorsTest_1056, ValueGeneratorValue_1056) {
    auto wrapper = makeFixedGenerator<int>({5, 6});
    Generators<int> gen(1, std::move(wrapper), 9);
    EXPECT_EQ(gen.get(), 1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 5);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 6);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 9);
    EXPECT_FALSE(gen.next());
}

// Test: Single generator wrapper with one element
TEST_F(GeneratorsTest_1056, SingleElementGeneratorWrapper_1056) {
    auto wrapper = makeFixedGenerator<int>({42});
    Generators<int> gen(std::move(wrapper));
    EXPECT_EQ(gen.get(), 42);
    EXPECT_FALSE(gen.next());
}

// Test: Negative and zero values
TEST_F(GeneratorsTest_1056, NegativeAndZeroValues_1056) {
    Generators<int> gen(-5, 0, 5);
    EXPECT_EQ(gen.get(), -5);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 0);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 5);
    EXPECT_FALSE(gen.next());
}

// Test: Implicit conversion from compatible type (e.g., int to double)
TEST_F(GeneratorsTest_1056, ImplicitConversionFromCompatibleType_1056) {
    Generators<double> gen(1, 2.5, 3);
    EXPECT_DOUBLE_EQ(gen.get(), 1.0);
    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 2.5);
    EXPECT_TRUE(gen.next());
    EXPECT_DOUBLE_EQ(gen.get(), 3.0);
    EXPECT_FALSE(gen.next());
}

// Test: Large number of values
TEST_F(GeneratorsTest_1056, LargeNumberOfValues_1056) {
    Generators<int> gen(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    for (int i = 1; i <= 10; ++i) {
        EXPECT_EQ(gen.get(), i);
        if (i < 10) {
            EXPECT_TRUE(gen.next());
        } else {
            EXPECT_FALSE(gen.next());
        }
    }
}

// Test: get() is const and returns reference
TEST_F(GeneratorsTest_1056, GetIsConstCorrect_1056) {
    Generators<int> gen(7);
    const auto& val = gen.get();
    EXPECT_EQ(val, 7);
}

// Test: Bool type
TEST_F(GeneratorsTest_1056, BoolTypeValues_1056) {
    Generators<bool> gen(true, false, true);
    EXPECT_EQ(gen.get(), true);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), false);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), true);
    EXPECT_FALSE(gen.next());
}

// Test: Char type
TEST_F(GeneratorsTest_1056, CharTypeValues_1056) {
    Generators<char> gen('a', 'b', 'c');
    EXPECT_EQ(gen.get(), 'a');
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 'b');
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 'c');
    EXPECT_FALSE(gen.next());
}
