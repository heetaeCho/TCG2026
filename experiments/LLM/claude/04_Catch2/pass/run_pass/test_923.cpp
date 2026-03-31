#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>

// Since we're testing with Google Test framework as requested:
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the amalgamated header
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

#include <string>
#include <vector>
#include <stdexcept>

// Helper: create a GeneratorWrapper from a fixed sequence
template <typename T>
class FixedGenerator : public Catch::Generators::IGenerator<T> {
    std::vector<T> m_values;
    size_t m_index = 0;
public:
    FixedGenerator(std::vector<T> values) : m_values(std::move(values)) {
        if (m_values.empty()) {
            throw Catch::GeneratorException("FixedGenerator requires at least one value");
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
Catch::Generators::GeneratorWrapper<T> makeFixed(std::vector<T> values) {
    return Catch::Generators::GeneratorWrapper<T>(
        Catch::Detail::make_unique<FixedGenerator<T>>(std::move(values))
    );
}

class FilterGeneratorTest_923 : public ::testing::Test {
protected:
};

// Test that FilterGenerator returns the first element matching the predicate
TEST_F(FilterGeneratorTest_923, GetReturnsFirstMatchingElement_923) {
    auto gen = Catch::Generators::FilterGenerator<int, std::function<bool(int)>>(
        [](int x) { return x % 2 == 0; },
        makeFixed<int>({2, 4, 6})
    );
    EXPECT_EQ(gen.get(), 2);
}

// Test that FilterGenerator skips non-matching initial elements
TEST_F(FilterGeneratorTest_923, SkipsNonMatchingInitialElements_923) {
    auto gen = Catch::Generators::FilterGenerator<int, std::function<bool(int)>>(
        [](int x) { return x > 3; },
        makeFixed<int>({1, 2, 3, 4, 5})
    );
    EXPECT_EQ(gen.get(), 4);
}

// Test that next() advances to the next matching element
TEST_F(FilterGeneratorTest_923, NextAdvancesToNextMatchingElement_923) {
    auto gen = Catch::Generators::FilterGenerator<int, std::function<bool(int)>>(
        [](int x) { return x % 2 == 0; },
        makeFixed<int>({1, 2, 3, 4, 5, 6})
    );
    EXPECT_EQ(gen.get(), 2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 4);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 6);
}

// Test that next() returns false when no more matching elements exist
TEST_F(FilterGeneratorTest_923, NextReturnsFalseWhenExhausted_923) {
    auto gen = Catch::Generators::FilterGenerator<int, std::function<bool(int)>>(
        [](int x) { return x % 2 == 0; },
        makeFixed<int>({1, 2, 3})
    );
    EXPECT_EQ(gen.get(), 2);
    EXPECT_FALSE(gen.next());
}

// Test that all elements match the predicate
TEST_F(FilterGeneratorTest_923, AllElementsMatch_923) {
    auto gen = Catch::Generators::FilterGenerator<int, std::function<bool(int)>>(
        [](int x) { return x > 0; },
        makeFixed<int>({1, 2, 3})
    );
    EXPECT_EQ(gen.get(), 1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);
    EXPECT_FALSE(gen.next());
}

// Test with string type
TEST_F(FilterGeneratorTest_923, WorksWithStringType_923) {
    auto gen = Catch::Generators::FilterGenerator<std::string, std::function<bool(std::string const&)>>(
        [](std::string const& s) { return s.size() > 3; },
        makeFixed<std::string>({"ab", "abcd", "ef", "ghij"})
    );
    EXPECT_EQ(gen.get(), "abcd");
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "ghij");
    EXPECT_FALSE(gen.next());
}

// Test that constructor throws when no elements match the predicate
TEST_F(FilterGeneratorTest_923, ThrowsWhenNoElementsMatch_923) {
    EXPECT_THROW(
        (Catch::Generators::FilterGenerator<int, std::function<bool(int)>>(
            [](int) { return false; },
            makeFixed<int>({1, 2, 3})
        )),
        Catch::GeneratorException
    );
}

// Test with single matching element
TEST_F(FilterGeneratorTest_923, SingleMatchingElement_923) {
    auto gen = Catch::Generators::FilterGenerator<int, std::function<bool(int)>>(
        [](int x) { return x == 5; },
        makeFixed<int>({1, 2, 3, 4, 5})
    );
    EXPECT_EQ(gen.get(), 5);
    EXPECT_FALSE(gen.next());
}

// Test with single element that matches
TEST_F(FilterGeneratorTest_923, SingleElementGenerator_923) {
    auto gen = Catch::Generators::FilterGenerator<int, std::function<bool(int)>>(
        [](int x) { return x == 42; },
        makeFixed<int>({42})
    );
    EXPECT_EQ(gen.get(), 42);
    EXPECT_FALSE(gen.next());
}

// Test boundary: last element is the only match
TEST_F(FilterGeneratorTest_923, OnlyLastElementMatches_923) {
    auto gen = Catch::Generators::FilterGenerator<int, std::function<bool(int)>>(
        [](int x) { return x == 100; },
        makeFixed<int>({1, 2, 3, 100})
    );
    EXPECT_EQ(gen.get(), 100);
    EXPECT_FALSE(gen.next());
}

// Test multiple consecutive non-matching elements between matches
TEST_F(FilterGeneratorTest_923, MultipleNonMatchingBetweenMatches_923) {
    auto gen = Catch::Generators::FilterGenerator<int, std::function<bool(int)>>(
        [](int x) { return x % 10 == 0; },
        makeFixed<int>({10, 1, 2, 3, 4, 5, 20, 6, 7, 8, 30})
    );
    EXPECT_EQ(gen.get(), 10);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 30);
    EXPECT_FALSE(gen.next());
}

// Test get() returns consistent value without calling next()
TEST_F(FilterGeneratorTest_923, GetIsIdempotent_923) {
    auto gen = Catch::Generators::FilterGenerator<int, std::function<bool(int)>>(
        [](int x) { return x > 0; },
        makeFixed<int>({5, 10})
    );
    EXPECT_EQ(gen.get(), 5);
    EXPECT_EQ(gen.get(), 5);
    EXPECT_EQ(gen.get(), 5);
}
