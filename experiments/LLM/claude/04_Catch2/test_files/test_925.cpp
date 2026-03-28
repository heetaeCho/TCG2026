#include <gtest/gtest.h>
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"
#include <vector>
#include <string>

// Helper: A simple generator that yields values from a vector
template <typename T>
class FixedValuesGenerator final : public Catch::Generators::IGenerator<T> {
    std::vector<T> m_values;
    size_t m_index = 0;

public:
    FixedValuesGenerator(std::vector<T> values) : m_values(std::move(values)) {
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

template <typename T>
Catch::Generators::GeneratorWrapper<T> fromValues(std::vector<T> values) {
    return Catch::Generators::GeneratorWrapper<T>(
        Catch::Detail::make_unique<FixedValuesGenerator<T>>(std::move(values))
    );
}

class FilterGeneratorTest_925 : public ::testing::Test {
protected:
};

TEST_F(FilterGeneratorTest_925, FilterReturnsMatchingFirstElement_925) {
    // Given a generator [1, 2, 3, 4, 5] and a predicate that accepts odd numbers
    auto gen = Catch::Generators::filter(
        [](int val) { return val % 2 != 0; },
        fromValues<int>({1, 2, 3, 4, 5})
    );

    // The first value returned should be 1 (first odd number)
    EXPECT_EQ(gen.get(), 1);
}

TEST_F(FilterGeneratorTest_925, FilterSkipsNonMatchingFirstElements_925) {
    // Given a generator [2, 4, 5, 6, 7] and a predicate that accepts odd numbers
    // The first matching element is 5
    auto gen = Catch::Generators::filter(
        [](int val) { return val % 2 != 0; },
        fromValues<int>({2, 4, 5, 6, 7})
    );

    EXPECT_EQ(gen.get(), 5);
}

TEST_F(FilterGeneratorTest_925, FilterIteratesThroughAllMatchingValues_925) {
    auto gen = Catch::Generators::filter(
        [](int val) { return val % 2 == 0; },
        fromValues<int>({1, 2, 3, 4, 5, 6})
    );

    // First matching value should be 2
    EXPECT_EQ(gen.get(), 2);

    // Next matching value should be 4
    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 4);

    // Next matching value should be 6
    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 6);

    // No more values
    EXPECT_FALSE(gen.next());
}

TEST_F(FilterGeneratorTest_925, FilterWithAllMatchingValues_925) {
    auto gen = Catch::Generators::filter(
        [](int val) { return true; },
        fromValues<int>({10, 20, 30})
    );

    EXPECT_EQ(gen.get(), 10);
    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);
    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 30);
    EXPECT_FALSE(gen.next());
}

TEST_F(FilterGeneratorTest_925, FilterWithSingleMatchingValue_925) {
    auto gen = Catch::Generators::filter(
        [](int val) { return val == 3; },
        fromValues<int>({1, 2, 3, 4, 5})
    );

    EXPECT_EQ(gen.get(), 3);
    EXPECT_FALSE(gen.next());
}

TEST_F(FilterGeneratorTest_925, FilterWithNoMatchingValuesThrows_925) {
    // When no values match the predicate, the generator should throw
    EXPECT_THROW(
        Catch::Generators::filter(
            [](int val) { return false; },
            fromValues<int>({1, 2, 3})
        ),
        Catch::GeneratorException
    );
}

TEST_F(FilterGeneratorTest_925, FilterWithStringValues_925) {
    auto gen = Catch::Generators::filter(
        [](const std::string& s) { return s.length() > 3; },
        fromValues<std::string>({"hi", "hello", "no", "world", "ok"})
    );

    EXPECT_EQ(gen.get(), "hello");
    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "world");
    EXPECT_FALSE(gen.next());
}

TEST_F(FilterGeneratorTest_925, FilterWithLastElementMatching_925) {
    auto gen = Catch::Generators::filter(
        [](int val) { return val == 5; },
        fromValues<int>({1, 2, 3, 4, 5})
    );

    EXPECT_EQ(gen.get(), 5);
    EXPECT_FALSE(gen.next());
}

TEST_F(FilterGeneratorTest_925, FilterWithConsecutiveMatchingValues_925) {
    auto gen = Catch::Generators::filter(
        [](int val) { return val > 0; },
        fromValues<int>({-1, -2, 1, 2, 3, -3})
    );

    EXPECT_EQ(gen.get(), 1);
    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);
    EXPECT_FALSE(gen.next());
}

TEST_F(FilterGeneratorTest_925, FilterWithComplexPredicate_925) {
    auto gen = Catch::Generators::filter(
        [](int val) { return val > 10 && val < 20 && val % 2 == 0; },
        fromValues<int>({5, 11, 12, 15, 18, 25})
    );

    EXPECT_EQ(gen.get(), 12);
    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 18);
    EXPECT_FALSE(gen.next());
}

TEST_F(FilterGeneratorTest_925, FilterGetIsIdempotent_925) {
    auto gen = Catch::Generators::filter(
        [](int val) { return val % 2 == 0; },
        fromValues<int>({1, 2, 3})
    );

    // Calling get() multiple times should return the same value
    EXPECT_EQ(gen.get(), 2);
    EXPECT_EQ(gen.get(), 2);
    EXPECT_EQ(gen.get(), 2);
}
