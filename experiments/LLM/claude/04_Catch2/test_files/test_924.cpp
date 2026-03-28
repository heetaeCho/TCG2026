#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <functional>
#include <memory>

// Minimal infrastructure to test FilterGenerator behavior
namespace TestInfra {

template <typename T>
class IGenerator {
public:
    virtual ~IGenerator() = default;
    virtual T const& get() const = 0;
    virtual bool next() = 0;
};

template <typename T>
class GeneratorWrapper {
    std::unique_ptr<IGenerator<T>> m_impl;
public:
    GeneratorWrapper(std::unique_ptr<IGenerator<T>> impl) : m_impl(std::move(impl)) {}
    T const& get() const { return m_impl->get(); }
    bool next() { return m_impl->next(); }
};

template <typename T, typename Predicate>
class FilterGenerator : public IGenerator<T> {
    GeneratorWrapper<T> m_generator;
    Predicate m_predicate;
public:
    template <typename P = Predicate>
    FilterGenerator(P&& pred, GeneratorWrapper<T>&& generator)
        : m_generator(std::move(generator)), m_predicate(std::forward<P>(pred))
    {
        // The constructor should position on the first element matching the predicate
        if (!m_predicate(m_generator.get())) {
            // Need to advance to the first matching element
            // This mirrors Catch2 behavior where constructor ensures first get() is valid
            bool found = false;
            while (m_generator.next()) {
                if (m_predicate(m_generator.get())) {
                    found = true;
                    break;
                }
            }
            // If not found, the generator is exhausted
        }
    }

    T const& get() const override {
        return m_generator.get();
    }

    bool next() override {
        bool success = m_generator.next();
        if (!success) {
            return false;
        }
        while (!m_predicate(m_generator.get()) && (success = m_generator.next()) == true);
        return success;
    }
};

// A simple generator that produces values from a vector
template <typename T>
class VectorGenerator : public IGenerator<T> {
    std::vector<T> m_values;
    size_t m_index;
public:
    VectorGenerator(std::vector<T> values) : m_values(std::move(values)), m_index(0) {}

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
    return GeneratorWrapper<T>(std::make_unique<VectorGenerator<T>>(std::move(values)));
}

} // namespace TestInfra

using namespace TestInfra;

class FilterGeneratorTest_924 : public ::testing::Test {
protected:
};

// Test: next() returns true when there are matching elements after current position
TEST_F(FilterGeneratorTest_924, NextReturnsTrueWhenMatchingElementExists_924) {
    auto gen = makeVectorGenerator<int>({2, 3, 4, 5, 6});
    auto predicate = [](int val) { return val % 2 == 0; };
    FilterGenerator<int, decltype(predicate)> filter(predicate, std::move(gen));

    // First matching element should be 2
    EXPECT_EQ(filter.get(), 2);

    // next() should find 4
    EXPECT_TRUE(filter.next());
    EXPECT_EQ(filter.get(), 4);

    // next() should find 6
    EXPECT_TRUE(filter.next());
    EXPECT_EQ(filter.get(), 6);
}

// Test: next() returns false when no more matching elements exist
TEST_F(FilterGeneratorTest_924, NextReturnsFalseWhenNoMoreMatchingElements_924) {
    auto gen = makeVectorGenerator<int>({2, 3, 5, 7});
    auto predicate = [](int val) { return val % 2 == 0; };
    FilterGenerator<int, decltype(predicate)> filter(predicate, std::move(gen));

    EXPECT_EQ(filter.get(), 2);

    // No more even numbers after 2
    EXPECT_FALSE(filter.next());
}

// Test: next() returns false immediately when underlying generator is exhausted
TEST_F(FilterGeneratorTest_924, NextReturnsFalseWhenGeneratorExhausted_924) {
    auto gen = makeVectorGenerator<int>({2});
    auto predicate = [](int val) { return val % 2 == 0; };
    FilterGenerator<int, decltype(predicate)> filter(predicate, std::move(gen));

    EXPECT_EQ(filter.get(), 2);
    EXPECT_FALSE(filter.next());
}

// Test: Filter with all elements matching
TEST_F(FilterGeneratorTest_924, AllElementsMatch_924) {
    auto gen = makeVectorGenerator<int>({2, 4, 6, 8});
    auto predicate = [](int val) { return val % 2 == 0; };
    FilterGenerator<int, decltype(predicate)> filter(predicate, std::move(gen));

    EXPECT_EQ(filter.get(), 2);
    EXPECT_TRUE(filter.next());
    EXPECT_EQ(filter.get(), 4);
    EXPECT_TRUE(filter.next());
    EXPECT_EQ(filter.get(), 6);
    EXPECT_TRUE(filter.next());
    EXPECT_EQ(filter.get(), 8);
    EXPECT_FALSE(filter.next());
}

// Test: Filter skips multiple non-matching elements in a row
TEST_F(FilterGeneratorTest_924, SkipsMultipleNonMatchingElements_924) {
    auto gen = makeVectorGenerator<int>({2, 1, 3, 5, 7, 4});
    auto predicate = [](int val) { return val % 2 == 0; };
    FilterGenerator<int, decltype(predicate)> filter(predicate, std::move(gen));

    EXPECT_EQ(filter.get(), 2);
    EXPECT_TRUE(filter.next());
    EXPECT_EQ(filter.get(), 4);
    EXPECT_FALSE(filter.next());
}

// Test: Filter with no matching elements (first element doesn't match, constructor advances)
TEST_F(FilterGeneratorTest_924, NoMatchingElementsInGenerator_924) {
    auto gen = makeVectorGenerator<int>({1, 3, 5, 7});
    auto predicate = [](int val) { return val % 2 == 0; };
    FilterGenerator<int, decltype(predicate)> filter(predicate, std::move(gen));

    // After constructor, generator is exhausted with no match found
    // next() should return false
    EXPECT_FALSE(filter.next());
}

// Test: Filter with string values
TEST_F(FilterGeneratorTest_924, WorksWithStringValues_924) {
    auto gen = makeVectorGenerator<std::string>({"apple", "banana", "avocado", "cherry", "apricot"});
    auto predicate = [](std::string const& val) { return val[0] == 'a'; };
    FilterGenerator<std::string, decltype(predicate)> filter(predicate, std::move(gen));

    EXPECT_EQ(filter.get(), "apple");
    EXPECT_TRUE(filter.next());
    EXPECT_EQ(filter.get(), "avocado");
    EXPECT_TRUE(filter.next());
    EXPECT_EQ(filter.get(), "apricot");
    EXPECT_FALSE(filter.next());
}

// Test: Filter where first element doesn't match but later ones do
TEST_F(FilterGeneratorTest_924, FirstElementDoesNotMatch_924) {
    auto gen = makeVectorGenerator<int>({1, 3, 4, 5, 6});
    auto predicate = [](int val) { return val % 2 == 0; };
    FilterGenerator<int, decltype(predicate)> filter(predicate, std::move(gen));

    // Constructor should skip 1, 3 and land on 4
    EXPECT_EQ(filter.get(), 4);
    EXPECT_TRUE(filter.next());
    EXPECT_EQ(filter.get(), 6);
    EXPECT_FALSE(filter.next());
}

// Test: Calling next() after it already returned false should still return false
TEST_F(FilterGeneratorTest_924, NextAfterExhaustionReturnsFalse_924) {
    auto gen = makeVectorGenerator<int>({2, 4});
    auto predicate = [](int val) { return val % 2 == 0; };
    FilterGenerator<int, decltype(predicate)> filter(predicate, std::move(gen));

    EXPECT_EQ(filter.get(), 2);
    EXPECT_TRUE(filter.next());
    EXPECT_EQ(filter.get(), 4);
    EXPECT_FALSE(filter.next());
    EXPECT_FALSE(filter.next()); // calling again
}

// Test: Filter with single matching element at the end
TEST_F(FilterGeneratorTest_924, SingleMatchingElementAtEnd_924) {
    auto gen = makeVectorGenerator<int>({1, 3, 5, 7, 8});
    auto predicate = [](int val) { return val % 2 == 0; };
    FilterGenerator<int, decltype(predicate)> filter(predicate, std::move(gen));

    EXPECT_EQ(filter.get(), 8);
    EXPECT_FALSE(filter.next());
}

// Test: Filter with matching element only at the beginning
TEST_F(FilterGeneratorTest_924, SingleMatchingElementAtBeginning_924) {
    auto gen = makeVectorGenerator<int>({2, 1, 3, 5});
    auto predicate = [](int val) { return val % 2 == 0; };
    FilterGenerator<int, decltype(predicate)> filter(predicate, std::move(gen));

    EXPECT_EQ(filter.get(), 2);
    EXPECT_FALSE(filter.next());
}

// Test: get() returns consistent value without calling next()
TEST_F(FilterGeneratorTest_924, GetReturnsConsistentValue_924) {
    auto gen = makeVectorGenerator<int>({2, 4, 6});
    auto predicate = [](int val) { return val % 2 == 0; };
    FilterGenerator<int, decltype(predicate)> filter(predicate, std::move(gen));

    EXPECT_EQ(filter.get(), 2);
    EXPECT_EQ(filter.get(), 2); // calling get() again without next()
    EXPECT_EQ(filter.get(), 2); // still the same
}

// Test: Predicate that accepts all values (identity filter)
TEST_F(FilterGeneratorTest_924, PredicateAcceptsAll_924) {
    auto gen = makeVectorGenerator<int>({1, 2, 3, 4, 5});
    auto predicate = [](int) { return true; };
    FilterGenerator<int, decltype(predicate)> filter(predicate, std::move(gen));

    EXPECT_EQ(filter.get(), 1);
    EXPECT_TRUE(filter.next());
    EXPECT_EQ(filter.get(), 2);
    EXPECT_TRUE(filter.next());
    EXPECT_EQ(filter.get(), 3);
    EXPECT_TRUE(filter.next());
    EXPECT_EQ(filter.get(), 4);
    EXPECT_TRUE(filter.next());
    EXPECT_EQ(filter.get(), 5);
    EXPECT_FALSE(filter.next());
}

// Test: Large sequence with sparse matching elements
TEST_F(FilterGeneratorTest_924, LargeSequenceSparseMatches_924) {
    std::vector<int> values;
    for (int i = 0; i < 1000; ++i) {
        values.push_back(i);
    }
    auto gen = makeVectorGenerator<int>(values);
    auto predicate = [](int val) { return val % 100 == 0; };
    FilterGenerator<int, decltype(predicate)> filter(predicate, std::move(gen));

    EXPECT_EQ(filter.get(), 0);
    for (int expected = 100; expected < 1000; expected += 100) {
        EXPECT_TRUE(filter.next());
        EXPECT_EQ(filter.get(), expected);
    }
    EXPECT_FALSE(filter.next());
}

// Test: Filter with negative numbers
TEST_F(FilterGeneratorTest_924, WorksWithNegativeNumbers_924) {
    auto gen = makeVectorGenerator<int>({-5, -4, -3, -2, -1, 0, 1, 2});
    auto predicate = [](int val) { return val < 0; };
    FilterGenerator<int, decltype(predicate)> filter(predicate, std::move(gen));

    EXPECT_EQ(filter.get(), -5);
    EXPECT_TRUE(filter.next());
    EXPECT_EQ(filter.get(), -4);
    EXPECT_TRUE(filter.next());
    EXPECT_EQ(filter.get(), -3);
    EXPECT_TRUE(filter.next());
    EXPECT_EQ(filter.get(), -2);
    EXPECT_TRUE(filter.next());
    EXPECT_EQ(filter.get(), -1);
    EXPECT_FALSE(filter.next());
}
