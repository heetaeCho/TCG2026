#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <stdexcept>
#include <functional>

// We need to include the Catch2 amalgamated header for the FilterGenerator
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Generators;

// Helper: A simple generator that yields values from a vector
template <typename T>
class VectorGenerator : public IGenerator<T> {
    std::vector<T> m_values;
    size_t m_index = 0;
public:
    explicit VectorGenerator(std::vector<T> values) : m_values(std::move(values)) {
        if (m_values.empty()) {
            throw std::runtime_error("VectorGenerator requires at least one value");
        }
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
GeneratorWrapper<T> makeVectorGenerator(std::vector<T> values) {
    return GeneratorWrapper<T>(
        Catch::Detail::make_unique<VectorGenerator<T>>(std::move(values))
    );
}

// Test fixture
class FilterGeneratorTest_1108 : public ::testing::Test {
protected:
};

// Test: First element matches predicate, should be returned by get()
TEST_F(FilterGeneratorTest_1108, FirstElementMatchesPredicate_1108) {
    auto gen = makeVectorGenerator<int>({2, 4, 6, 8});
    auto predicate = [](int v) { return v % 2 == 0; };

    FilterGenerator<int, decltype(predicate)> filter(predicate, std::move(gen));

    EXPECT_EQ(filter.get(), 2);
}

// Test: First element does NOT match predicate, should advance to first matching element
TEST_F(FilterGeneratorTest_1108, FirstElementDoesNotMatchPredicate_1108) {
    auto gen = makeVectorGenerator<int>({1, 3, 4, 6});
    auto predicate = [](int v) { return v % 2 == 0; };

    FilterGenerator<int, decltype(predicate)> filter(predicate, std::move(gen));

    EXPECT_EQ(filter.get(), 4);
}

// Test: No valid value found - should throw generator exception
TEST_F(FilterGeneratorTest_1108, NoValidValueThrowsException_1108) {
    auto gen = makeVectorGenerator<int>({1, 3, 5, 7});
    auto predicate = [](int v) { return v % 2 == 0; };

    EXPECT_THROW(
        (FilterGenerator<int, decltype(predicate)>(predicate, std::move(gen))),
        Catch::GeneratorException
    );
}

// Test: next() advances to the next matching element
TEST_F(FilterGeneratorTest_1108, NextAdvancesToNextMatchingElement_1108) {
    auto gen = makeVectorGenerator<int>({2, 3, 4, 5, 6});
    auto predicate = [](int v) { return v % 2 == 0; };

    FilterGenerator<int, decltype(predicate)> filter(predicate, std::move(gen));

    EXPECT_EQ(filter.get(), 2);
    EXPECT_TRUE(filter.next());
    EXPECT_EQ(filter.get(), 4);
    EXPECT_TRUE(filter.next());
    EXPECT_EQ(filter.get(), 6);
}

// Test: next() returns false when no more matching elements exist
TEST_F(FilterGeneratorTest_1108, NextReturnsFalseWhenExhausted_1108) {
    auto gen = makeVectorGenerator<int>({2, 3, 5});
    auto predicate = [](int v) { return v % 2 == 0; };

    FilterGenerator<int, decltype(predicate)> filter(predicate, std::move(gen));

    EXPECT_EQ(filter.get(), 2);
    EXPECT_FALSE(filter.next());
}

// Test: Single matching element
TEST_F(FilterGeneratorTest_1108, SingleMatchingElement_1108) {
    auto gen = makeVectorGenerator<int>({1, 3, 5, 10, 7, 9});
    auto predicate = [](int v) { return v >= 10; };

    FilterGenerator<int, decltype(predicate)> filter(predicate, std::move(gen));

    EXPECT_EQ(filter.get(), 10);
    EXPECT_FALSE(filter.next());
}

// Test: All elements match the predicate
TEST_F(FilterGeneratorTest_1108, AllElementsMatch_1108) {
    auto gen = makeVectorGenerator<int>({2, 4, 6});
    auto predicate = [](int v) { return v % 2 == 0; };

    FilterGenerator<int, decltype(predicate)> filter(predicate, std::move(gen));

    EXPECT_EQ(filter.get(), 2);
    EXPECT_TRUE(filter.next());
    EXPECT_EQ(filter.get(), 4);
    EXPECT_TRUE(filter.next());
    EXPECT_EQ(filter.get(), 6);
    EXPECT_FALSE(filter.next());
}

// Test: Predicate filters strings
TEST_F(FilterGeneratorTest_1108, StringPredicate_1108) {
    auto gen = makeVectorGenerator<std::string>({"", "hello", "", "world"});
    auto predicate = [](const std::string& s) { return !s.empty(); };

    FilterGenerator<std::string, decltype(predicate)> filter(predicate, std::move(gen));

    EXPECT_EQ(filter.get(), "hello");
    EXPECT_TRUE(filter.next());
    EXPECT_EQ(filter.get(), "world");
    EXPECT_FALSE(filter.next());
}

// Test: Only the last element matches the predicate
TEST_F(FilterGeneratorTest_1108, OnlyLastElementMatches_1108) {
    auto gen = makeVectorGenerator<int>({1, 3, 5, 8});
    auto predicate = [](int v) { return v % 2 == 0; };

    FilterGenerator<int, decltype(predicate)> filter(predicate, std::move(gen));

    EXPECT_EQ(filter.get(), 8);
    EXPECT_FALSE(filter.next());
}

// Test: get() is consistent (returns same value without calling next)
TEST_F(FilterGeneratorTest_1108, GetIsConsistent_1108) {
    auto gen = makeVectorGenerator<int>({5, 10, 15});
    auto predicate = [](int v) { return v >= 10; };

    FilterGenerator<int, decltype(predicate)> filter(predicate, std::move(gen));

    EXPECT_EQ(filter.get(), 10);
    EXPECT_EQ(filter.get(), 10);
    EXPECT_EQ(filter.get(), 10);
}

// Test: Predicate with matching elements interspersed with non-matching
TEST_F(FilterGeneratorTest_1108, InterspersedMatchingElements_1108) {
    auto gen = makeVectorGenerator<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    auto predicate = [](int v) { return v % 3 == 0; };

    FilterGenerator<int, decltype(predicate)> filter(predicate, std::move(gen));

    EXPECT_EQ(filter.get(), 3);
    EXPECT_TRUE(filter.next());
    EXPECT_EQ(filter.get(), 6);
    EXPECT_TRUE(filter.next());
    EXPECT_EQ(filter.get(), 9);
    EXPECT_FALSE(filter.next());
}

// Test: Single element that matches
TEST_F(FilterGeneratorTest_1108, SingleElementMatches_1108) {
    auto gen = makeVectorGenerator<int>({42});
    auto predicate = [](int v) { return v == 42; };

    FilterGenerator<int, decltype(predicate)> filter(predicate, std::move(gen));

    EXPECT_EQ(filter.get(), 42);
    EXPECT_FALSE(filter.next());
}

// Test: Single element that does NOT match - should throw
TEST_F(FilterGeneratorTest_1108, SingleElementDoesNotMatch_1108) {
    auto gen = makeVectorGenerator<int>({41});
    auto predicate = [](int v) { return v == 42; };

    EXPECT_THROW(
        (FilterGenerator<int, decltype(predicate)>(predicate, std::move(gen))),
        Catch::GeneratorException
    );
}
