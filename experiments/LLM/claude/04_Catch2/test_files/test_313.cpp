#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "catch2/generators/catch_generators.hpp"
#include "catch2/generators/catch_generator_exception.hpp"

// We need to create a mock/fake IGenerator to test GeneratorWrapper
// since GeneratorWrapper delegates to an IGenerator via m_generator

namespace Catch {
namespace Generators {

// A simple concrete generator for testing purposes
template <typename T>
class FixedValueGenerator : public IGenerator<T> {
    T m_value;
    int m_remaining;
    
public:
    FixedValueGenerator(T value, int count)
        : m_value(std::move(value)), m_remaining(count) {}
    
    T const& get() const override {
        return m_value;
    }
    
    bool next() override {
        if (m_remaining > 0) {
            --m_remaining;
            return true;
        }
        return false;
    }
};

// A generator that produces a sequence of values
template <typename T>
class SequenceGenerator : public IGenerator<T> {
    std::vector<T> m_values;
    size_t m_currentIndex;
    
public:
    SequenceGenerator(std::vector<T> values)
        : m_values(std::move(values)), m_currentIndex(0) {}
    
    T const& get() const override {
        return m_values[m_currentIndex];
    }
    
    bool next() override {
        if (m_currentIndex + 1 < m_values.size()) {
            ++m_currentIndex;
            return true;
        }
        return false;
    }
};

// A generator that is immediately exhausted (no values to advance to)
template <typename T>
class ExhaustedGenerator : public IGenerator<T> {
    T m_value;
public:
    ExhaustedGenerator(T value) : m_value(std::move(value)) {}
    
    T const& get() const override {
        return m_value;
    }
    
    bool next() override {
        return false;
    }
};

} // namespace Generators
} // namespace Catch

using namespace Catch::Generators;

// Test fixture
class GeneratorWrapperTest_313 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that get() returns the initial value of the generator
TEST_F(GeneratorWrapperTest_313, GetReturnsInitialValue_313) {
    auto gen = new FixedValueGenerator<int>(42, 3);
    GeneratorWrapper<int> wrapper(gen);
    
    EXPECT_EQ(wrapper.get(), 42);
}

// Test that next() returns true when generator has more values
TEST_F(GeneratorWrapperTest_313, NextReturnsTrueWhenMoreValues_313) {
    auto gen = new FixedValueGenerator<int>(10, 2);
    GeneratorWrapper<int> wrapper(gen);
    
    EXPECT_TRUE(wrapper.next());
}

// Test that next() returns false when generator is exhausted
TEST_F(GeneratorWrapperTest_313, NextReturnsFalseWhenExhausted_313) {
    auto gen = new ExhaustedGenerator<int>(99);
    GeneratorWrapper<int> wrapper(gen);
    
    EXPECT_FALSE(wrapper.next());
}

// Test that get() returns correct value after advancing with next()
TEST_F(GeneratorWrapperTest_313, GetReturnsCorrectValueAfterNext_313) {
    auto gen = new SequenceGenerator<int>({1, 2, 3});
    GeneratorWrapper<int> wrapper(gen);
    
    EXPECT_EQ(wrapper.get(), 1);
    
    EXPECT_TRUE(wrapper.next());
    EXPECT_EQ(wrapper.get(), 2);
    
    EXPECT_TRUE(wrapper.next());
    EXPECT_EQ(wrapper.get(), 3);
    
    EXPECT_FALSE(wrapper.next());
}

// Test with string type
TEST_F(GeneratorWrapperTest_313, WorksWithStringType_313) {
    auto gen = new SequenceGenerator<std::string>({"hello", "world"});
    GeneratorWrapper<std::string> wrapper(gen);
    
    EXPECT_EQ(wrapper.get(), "hello");
    
    EXPECT_TRUE(wrapper.next());
    EXPECT_EQ(wrapper.get(), "world");
    
    EXPECT_FALSE(wrapper.next());
}

// Test single element generator
TEST_F(GeneratorWrapperTest_313, SingleElementGenerator_313) {
    auto gen = new SequenceGenerator<int>({42});
    GeneratorWrapper<int> wrapper(gen);
    
    EXPECT_EQ(wrapper.get(), 42);
    EXPECT_FALSE(wrapper.next());
}

// Test that get() consistently returns the same value without calling next()
TEST_F(GeneratorWrapperTest_313, GetIsIdempotent_313) {
    auto gen = new FixedValueGenerator<int>(7, 1);
    GeneratorWrapper<int> wrapper(gen);
    
    EXPECT_EQ(wrapper.get(), 7);
    EXPECT_EQ(wrapper.get(), 7);
    EXPECT_EQ(wrapper.get(), 7);
}

// Test next() called multiple times after exhaustion
TEST_F(GeneratorWrapperTest_313, NextAfterExhaustionReturnsFalse_313) {
    auto gen = new SequenceGenerator<int>({1, 2});
    GeneratorWrapper<int> wrapper(gen);
    
    EXPECT_TRUE(wrapper.next());
    EXPECT_FALSE(wrapper.next());
    // Calling next again after exhaustion should still return false
    EXPECT_FALSE(wrapper.next());
}

// Test with double type
TEST_F(GeneratorWrapperTest_313, WorksWithDoubleType_313) {
    auto gen = new SequenceGenerator<double>({1.5, 2.5, 3.5});
    GeneratorWrapper<double> wrapper(gen);
    
    EXPECT_DOUBLE_EQ(wrapper.get(), 1.5);
    
    EXPECT_TRUE(wrapper.next());
    EXPECT_DOUBLE_EQ(wrapper.get(), 2.5);
    
    EXPECT_TRUE(wrapper.next());
    EXPECT_DOUBLE_EQ(wrapper.get(), 3.5);
    
    EXPECT_FALSE(wrapper.next());
}

// Test GeneratorWrapper constructed with GeneratorPtr (unique_ptr)
TEST_F(GeneratorWrapperTest_313, ConstructWithGeneratorPtr_313) {
    auto genPtr = Catch::Detail::unique_ptr<IGenerator<int>>(new SequenceGenerator<int>({10, 20}));
    GeneratorWrapper<int> wrapper(std::move(genPtr));
    
    EXPECT_EQ(wrapper.get(), 10);
    EXPECT_TRUE(wrapper.next());
    EXPECT_EQ(wrapper.get(), 20);
    EXPECT_FALSE(wrapper.next());
}

// Test that the wrapper properly iterates through many values
TEST_F(GeneratorWrapperTest_313, ManyValuesIteration_313) {
    std::vector<int> values;
    for (int i = 0; i < 100; ++i) {
        values.push_back(i);
    }
    
    auto gen = new SequenceGenerator<int>(values);
    GeneratorWrapper<int> wrapper(gen);
    
    EXPECT_EQ(wrapper.get(), 0);
    for (int i = 1; i < 100; ++i) {
        EXPECT_TRUE(wrapper.next());
        EXPECT_EQ(wrapper.get(), i);
    }
    EXPECT_FALSE(wrapper.next());
}

// Test with negative numbers
TEST_F(GeneratorWrapperTest_313, WorksWithNegativeNumbers_313) {
    auto gen = new SequenceGenerator<int>({-5, -3, -1, 0, 1});
    GeneratorWrapper<int> wrapper(gen);
    
    EXPECT_EQ(wrapper.get(), -5);
    EXPECT_TRUE(wrapper.next());
    EXPECT_EQ(wrapper.get(), -3);
    EXPECT_TRUE(wrapper.next());
    EXPECT_EQ(wrapper.get(), -1);
    EXPECT_TRUE(wrapper.next());
    EXPECT_EQ(wrapper.get(), 0);
    EXPECT_TRUE(wrapper.next());
    EXPECT_EQ(wrapper.get(), 1);
    EXPECT_FALSE(wrapper.next());
}

// Test get returns const reference
TEST_F(GeneratorWrapperTest_313, GetReturnsConstReference_313) {
    auto gen = new SequenceGenerator<std::string>({"test"});
    GeneratorWrapper<std::string> wrapper(gen);
    
    const std::string& ref1 = wrapper.get();
    const std::string& ref2 = wrapper.get();
    
    // Both references should point to the same object
    EXPECT_EQ(&ref1, &ref2);
    EXPECT_EQ(ref1, "test");
}
