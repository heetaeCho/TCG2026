#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// We need to include the actual header
#include "catch2/generators/catch_generators.hpp"

// Since we're testing Catch2's GeneratorWrapper, we need to create a mock/concrete
// implementation of IGenerator<T> to use as a collaborator.

namespace {

// A simple concrete generator that produces values from a vector
template <typename T>
class SimpleGenerator : public Catch::Generators::IGenerator<T> {
    std::vector<T> m_values;
    size_t m_index = 0;
public:
    explicit SimpleGenerator(std::vector<T> values)
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

// A generator that produces a single value
template <typename T>
class SingleValueGenerator : public Catch::Generators::IGenerator<T> {
    T m_value;
public:
    explicit SingleValueGenerator(T value) : m_value(std::move(value)) {}

    T const& get() const override {
        return m_value;
    }

    bool next() override {
        return false;
    }
};

// Mock generator for verifying interactions
template <typename T>
class MockGenerator : public Catch::Generators::IGenerator<T> {
public:
    MOCK_METHOD(T const&, get, (), (const, override));
    MOCK_METHOD(bool, next, (), (override));
};

} // anonymous namespace

// Test fixture
class GeneratorWrapperTest_312 : public ::testing::Test {
protected:
    // Helper to create a GeneratorWrapper from a raw pointer
    template <typename T>
    Catch::Generators::GeneratorWrapper<T> makeWrapper(Catch::Generators::IGenerator<T>* gen) {
        return Catch::Generators::GeneratorWrapper<T>(gen);
    }
};

// Test that get() returns the first value of the generator
TEST_F(GeneratorWrapperTest_312, GetReturnsCurrentValue_312) {
    auto wrapper = makeWrapper<int>(new SimpleGenerator<int>({42, 43, 44}));
    EXPECT_EQ(wrapper.get(), 42);
}

// Test that get() returns the correct value after calling next()
TEST_F(GeneratorWrapperTest_312, GetReturnsUpdatedValueAfterNext_312) {
    auto wrapper = makeWrapper<int>(new SimpleGenerator<int>({10, 20, 30}));
    EXPECT_EQ(wrapper.get(), 10);
    EXPECT_TRUE(wrapper.next());
    EXPECT_EQ(wrapper.get(), 20);
    EXPECT_TRUE(wrapper.next());
    EXPECT_EQ(wrapper.get(), 30);
}

// Test that next() returns false when generator is exhausted
TEST_F(GeneratorWrapperTest_312, NextReturnsFalseWhenExhausted_312) {
    auto wrapper = makeWrapper<int>(new SimpleGenerator<int>({1, 2}));
    EXPECT_TRUE(wrapper.next());  // move to second element
    EXPECT_FALSE(wrapper.next()); // no more elements
}

// Test with a single value generator
TEST_F(GeneratorWrapperTest_312, SingleValueGeneratorExhaustsImmediately_312) {
    auto wrapper = makeWrapper<int>(new SingleValueGenerator<int>(99));
    EXPECT_EQ(wrapper.get(), 99);
    EXPECT_FALSE(wrapper.next());
}

// Test with string type
TEST_F(GeneratorWrapperTest_312, WorksWithStringType_312) {
    auto wrapper = makeWrapper<std::string>(
        new SimpleGenerator<std::string>({"hello", "world"}));
    EXPECT_EQ(wrapper.get(), "hello");
    EXPECT_TRUE(wrapper.next());
    EXPECT_EQ(wrapper.get(), "world");
    EXPECT_FALSE(wrapper.next());
}

// Test that get() can be called multiple times without advancing
TEST_F(GeneratorWrapperTest_312, GetIsIdempotent_312) {
    auto wrapper = makeWrapper<int>(new SimpleGenerator<int>({5, 10}));
    EXPECT_EQ(wrapper.get(), 5);
    EXPECT_EQ(wrapper.get(), 5);
    EXPECT_EQ(wrapper.get(), 5);
}

// Test get() returns const reference
TEST_F(GeneratorWrapperTest_312, GetReturnsConstReference_312) {
    auto wrapper = makeWrapper<int>(new SimpleGenerator<int>({42}));
    const int& ref1 = wrapper.get();
    const int& ref2 = wrapper.get();
    EXPECT_EQ(&ref1, &ref2); // Same address, since it's a reference to the same underlying value
}

// Test construction with GeneratorPtr (unique_ptr)
TEST_F(GeneratorWrapperTest_312, ConstructionWithGeneratorPtr_312) {
    Catch::Generators::GeneratorPtr<int> ptr(new SimpleGenerator<int>({7, 8, 9}));
    Catch::Generators::GeneratorWrapper<int> wrapper(std::move(ptr));
    EXPECT_EQ(wrapper.get(), 7);
    EXPECT_TRUE(wrapper.next());
    EXPECT_EQ(wrapper.get(), 8);
}

// Test with mock generator to verify delegation
TEST_F(GeneratorWrapperTest_312, DelegatesGetToUnderlyingGenerator_312) {
    auto* mockGen = new MockGenerator<int>();
    int value = 55;
    EXPECT_CALL(*mockGen, get())
        .WillRepeatedly(::testing::ReturnRef(value));
    
    auto wrapper = makeWrapper<int>(mockGen);
    EXPECT_EQ(wrapper.get(), 55);
}

// Test with mock generator to verify next() delegation
TEST_F(GeneratorWrapperTest_312, DelegatesNextToUnderlyingGenerator_312) {
    auto* mockGen = new MockGenerator<int>();
    int value = 1;
    EXPECT_CALL(*mockGen, get())
        .WillRepeatedly(::testing::ReturnRef(value));
    EXPECT_CALL(*mockGen, next())
        .WillOnce(::testing::Return(true))
        .WillOnce(::testing::Return(false));
    
    auto wrapper = makeWrapper<int>(mockGen);
    EXPECT_TRUE(wrapper.next());
    EXPECT_FALSE(wrapper.next());
}

// Test with double type
TEST_F(GeneratorWrapperTest_312, WorksWithDoubleType_312) {
    auto wrapper = makeWrapper<double>(
        new SimpleGenerator<double>({1.5, 2.5, 3.5}));
    EXPECT_DOUBLE_EQ(wrapper.get(), 1.5);
    EXPECT_TRUE(wrapper.next());
    EXPECT_DOUBLE_EQ(wrapper.get(), 2.5);
    EXPECT_TRUE(wrapper.next());
    EXPECT_DOUBLE_EQ(wrapper.get(), 3.5);
    EXPECT_FALSE(wrapper.next());
}

// Test iterating through all values
TEST_F(GeneratorWrapperTest_312, IterateThroughAllValues_312) {
    std::vector<int> expected = {1, 2, 3, 4, 5};
    auto wrapper = makeWrapper<int>(new SimpleGenerator<int>(expected));
    
    std::vector<int> actual;
    actual.push_back(wrapper.get());
    while (wrapper.next()) {
        actual.push_back(wrapper.get());
    }
    
    EXPECT_EQ(actual, expected);
}

// Test with a large number of values
TEST_F(GeneratorWrapperTest_312, LargeNumberOfValues_312) {
    std::vector<int> values(1000);
    for (int i = 0; i < 1000; ++i) {
        values[i] = i;
    }
    
    auto wrapper = makeWrapper<int>(new SimpleGenerator<int>(values));
    
    EXPECT_EQ(wrapper.get(), 0);
    for (int i = 1; i < 1000; ++i) {
        EXPECT_TRUE(wrapper.next());
        EXPECT_EQ(wrapper.get(), i);
    }
    EXPECT_FALSE(wrapper.next());
}

// Test move construction of GeneratorWrapper
TEST_F(GeneratorWrapperTest_312, MoveConstruction_312) {
    auto wrapper1 = makeWrapper<int>(new SimpleGenerator<int>({100, 200}));
    EXPECT_EQ(wrapper1.get(), 100);
    
    Catch::Generators::GeneratorWrapper<int> wrapper2(std::move(wrapper1));
    EXPECT_EQ(wrapper2.get(), 100);
    EXPECT_TRUE(wrapper2.next());
    EXPECT_EQ(wrapper2.get(), 200);
}
