// File: tests/FilterGenerator_923.tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Catch2/extras/catch_amalgamated.hpp"

using namespace ::testing;

namespace {

// A simple external collaborator for tests: a predictable integer generator.
// This is NOT simulating FilterGenerator internals; it only provides a source
// of values to be wrapped by Catch::Generators::GeneratorWrapper<int>.
class VectorIntGenerator : public Catch::Generators::IGenerator<int> {
public:
    explicit VectorIntGenerator(std::vector<int> values)
        : m_values(std::move(values)), m_index(0) {
        // Precondition for well-formed use: if empty, get() is undefined.
        // Tests avoid calling get() when no values are available.
        if (!m_values.empty()) {
            m_current = m_values[0];
        }
    }

    int const& get() const override {
        return m_current;
    }

    bool next() override {
        if (m_values.empty()) return false;
        if (m_index + 1 < m_values.size()) {
            ++m_index;
            m_current = m_values[m_index];
            return true;
        }
        return false;
    }

private:
    std::vector<int> m_values;
    std::size_t m_index;
    int m_current{};
};

// Helper to build a GeneratorWrapper<int> around our external collaborator.
static Catch::Generators::GeneratorWrapper<int>
MakeWrapper(std::vector<int> values) {
    using IGen = Catch::Generators::IGenerator<int>;
    return Catch::Generators::GeneratorWrapper<int>(
        std::unique_ptr<IGen>(new VectorIntGenerator(std::move(values))));
}

} // namespace

// Test fixture (kept minimal for clarity)
class FilterGeneratorTest_923 : public ::testing::Test {};

// [Normal operation] get() returns current filtered value and does not advance.
TEST_F(FilterGeneratorTest_923, GetReturnsCurrentValue_NoAdvance_923) {
    auto wrapper = MakeWrapper({1, 2, 3});
    auto always_true = [](const int&) { return true; };

    Catch::Generators::FilterGenerator<int, decltype(always_true)> fg(always_true, std::move(wrapper));

    // Calling get() should yield the current value (1) and not advance state.
    auto const* first_addr = &fg.get();
    EXPECT_EQ(fg.get(), 1);
    auto const* second_addr = &fg.get();
    // Same address implies no advancement from repeated get() calls.
    EXPECT_EQ(first_addr, second_addr);
}

// [Normal operation] Filtering passes through only matching elements.
TEST_F(FilterGeneratorTest_923, FiltersAccordingToPredicate_923) {
    auto wrapper = MakeWrapper({1, 2, 3, 4});
    auto is_even = [](const int& x) { return (x % 2) == 0; };

    Catch::Generators::FilterGenerator<int, decltype(is_even)> fg(is_even, std::move(wrapper));

    // On construction, FilterGenerator should expose the first matching element.
    EXPECT_EQ(fg.get(), 2);

    // next() should move to the next matching element.
    EXPECT_TRUE(fg.next());
    EXPECT_EQ(fg.get(), 4);

    // No more matching elements.
    EXPECT_FALSE(fg.next());
}

// [Boundary] next() reflects underlying movement; get() reflects updated current.
TEST_F(FilterGeneratorTest_923, GetReflectsUnderlyingAfterNext_923) {
    auto wrapper = MakeWrapper({5, 6});
    auto pass = [](const int&) { return true; };

    Catch::Generators::FilterGenerator<int, decltype(pass)> fg(pass, std::move(wrapper));

    EXPECT_EQ(fg.get(), 5);
    EXPECT_TRUE(fg.next());
    EXPECT_EQ(fg.get(), 6);
    EXPECT_FALSE(fg.next()); // No more
}

// [Exceptional/edge] When no element satisfies the predicate, iteration ends.
TEST_F(FilterGeneratorTest_923, NoMatch_AllFilteredOut_923) {
    auto wrapper = MakeWrapper({1, 3, 5});
    auto is_even = [](const int& x) { return (x % 2) == 0; };

    Catch::Generators::FilterGenerator<int, decltype(is_even)> fg(is_even, std::move(wrapper));

    // If nothing matches, there is no valid next step; verify iteration ends.
    // We intentionally avoid calling get() here because behavior would be undefined
    // if there is no current valid element to reference.
    EXPECT_FALSE(fg.next()); // Already exhausted; remains false on further calls too.
    EXPECT_FALSE(fg.next());
}
