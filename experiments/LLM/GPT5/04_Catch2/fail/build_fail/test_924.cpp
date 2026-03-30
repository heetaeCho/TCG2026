// File: tests/FilterGenerator_next_tests_924.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Catch2/extras/catch_amalgamated.hpp"

using ::testing::_;
using ::testing::InSequence;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::Invoke;

namespace {

using namespace Catch::Generators;

// ---- Helpers: minimal collaborators for black-box testing ----

// A tiny concrete generator over a vector<int>, via IGenerator<int>.
// This is a *collaborator* used only for observable behavior of FilterGenerator.
class VectorIntGenerator : public IGenerator<int> {
public:
    explicit VectorIntGenerator(std::vector<int> values)
        : m_values(std::move(values)), m_idx(static_cast<size_t>(-1)), m_current(0) {}

    const int& get() const override { return m_current; }

    bool next() override {
        if (m_idx + 1 >= m_values.size()) return false;
        ++m_idx;
        m_current = m_values[m_idx];
        return true;
    }

private:
    std::vector<int> m_values;
    size_t m_idx;
    int m_current;
};

// A Google Mock for IGenerator<int> to verify interaction counts/order.
class MockIntGenerator : public IGenerator<int> {
public:
    MOCK_METHOD(const int&, get, (), (const, override));
    MOCK_METHOD(bool, next, (), (override));

    // Storage to back the reference returned by get().
    int storage = 0;
};

struct FilterGeneratorTest_924 : ::testing::Test {
    // Utility to create a GeneratorWrapper<int> from a unique_ptr<IGenerator<int>>.
    static GeneratorWrapper<int> wrap(std::unique_ptr<IGenerator<int>> gen) {
        return GeneratorWrapper<int>(std::move(gen));
    }
};

} // namespace

// --- Tests ---

// Normal operation: should yield only values satisfying the predicate and in order.
TEST_F(FilterGeneratorTest_924, FiltersMatchingValuesInOrder_924) {
    auto base = std::make_unique<VectorIntGenerator>(std::vector<int>{1, 2, 3, 4, 5});
    auto wrapper = wrap(std::move(base));

    auto is_even = [](int v) { return (v % 2) == 0; };
    FilterGenerator<int, decltype(is_even)> uut(is_even, std::move(wrapper));

    // 1) First matching (2)
    ASSERT_TRUE(uut.next());
    EXPECT_EQ(uut.get(), 2);

    // 2) Next matching (4)
    ASSERT_TRUE(uut.next());
    EXPECT_EQ(uut.get(), 4);

    // 3) No more matches -> exhausts
    EXPECT_FALSE(uut.next());
}

// Boundary: when the first element already matches, next() should succeed immediately.
TEST_F(FilterGeneratorTest_924, FirstElementMatches_924) {
    auto base = std::make_unique<VectorIntGenerator>(std::vector<int>{2, 3});
    auto wrapper = wrap(std::move(base));

    auto is_even = [](int v) { return (v % 2) == 0; };
    FilterGenerator<int, decltype(is_even)> uut(is_even, std::move(wrapper));

    ASSERT_TRUE(uut.next());
    EXPECT_EQ(uut.get(), 2);
}

// Boundary: no element matches the predicate -> next() returns false immediately.
TEST_F(FilterGeneratorTest_924, NoMatchingElements_924) {
    auto base = std::make_unique<VectorIntGenerator>(std::vector<int>{1, 3, 5});
    auto wrapper = wrap(std::move(base));

    auto is_even = [](int v) { return (v % 2) == 0; };
    FilterGenerator<int, decltype(is_even)> uut(is_even, std::move(wrapper));

    EXPECT_FALSE(uut.next()); // nothing matches
}

// Boundary/Idempotence: after exhaustion, further next() calls keep returning false.
TEST_F(FilterGeneratorTest_924, NextRemainsFalseAfterExhaustion_924) {
    auto base = std::make_unique<VectorIntGenerator>(std::vector<int>{1});
    auto wrapper = wrap(std::move(base));

    auto is_even = [](int v) { return (v % 2) == 0; };
    FilterGenerator<int, decltype(is_even)> uut(is_even, std::move(wrapper));

    // No matches in underlying generator
    EXPECT_FALSE(uut.next());
    EXPECT_FALSE(uut.next()); // stays false
    EXPECT_FALSE(uut.next()); // stays false
}

// External interaction verification: ensure FilterGenerator keeps calling the
// underlying generator's next() until the predicate passes.
TEST_F(FilterGeneratorTest_924, SkipsUntilPredicateSatisfied_924) {
    NiceMock<MockIntGenerator>* mockPtr = new NiceMock<MockIntGenerator>();
    std::unique_ptr<IGenerator<int>> base(mockPtr);

    // Underlying sequence: 1 (odd), 3 (odd), 5 (odd), 6 (even), then exhausted
    std::vector<int> seq{1, 3, 5, 6};
    auto it = seq.begin();

    // Program the mock behavior:
    // - next(): advance until we run out; return true while in range; false otherwise.
    // - get(): return reference to current storage.
    ON_CALL(*mockPtr, next())
        .WillByDefault(Invoke([mockPtr, &it, &seq]() -> bool {
            if (it == seq.end()) return false;
            mockPtr->storage = *it;
            ++it;
            return true;
        }));

    ON_CALL(*mockPtr, get())
        .WillByDefault(Invoke([mockPtr]() -> const int& {
            return mockPtr->storage;
        }));

    // We expect next() to be called repeatedly until an even value appears (6).
    // The FilterGenerator contract (observable via behavior) requires it to
    // skip non-matching values before succeeding.
    {
        InSequence s;
        EXPECT_CALL(*mockPtr, next()).Times(1); // loads 1
        EXPECT_CALL(*mockPtr, get()).Times(1);  // checks 1 -> false, loop continues
        EXPECT_CALL(*mockPtr, next()).Times(1); // loads 3
        EXPECT_CALL(*mockPtr, get()).Times(1);  // checks 3 -> false
        EXPECT_CALL(*mockPtr, next()).Times(1); // loads 5
        EXPECT_CALL(*mockPtr, get()).Times(1);  // checks 5 -> false
        EXPECT_CALL(*mockPtr, next()).Times(1); // loads 6
        EXPECT_CALL(*mockPtr, get()).Times(1);  // checks 6 -> true, loop ends
    }

    auto wrapper = FilterGeneratorTest_924::wrap(std::move(base));
    auto is_even = [](int v) { return (v % 2) == 0; };
    FilterGenerator<int, decltype(is_even)> uut(is_even, std::move(wrapper));

    ASSERT_TRUE(uut.next());      // should succeed when 6 is reached
    EXPECT_EQ(uut.get(), 6);      // observable value is the first that satisfies predicate

    // Subsequent call should exhaust (seq is finished)
    EXPECT_FALSE(uut.next());
}
