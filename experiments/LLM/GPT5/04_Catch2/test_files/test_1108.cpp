// File: tests/FilterGenerator_tests_1108.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Use the real Catch2 amalgamated header so we exercise the real implementation.
#include <catch_amalgamated.hpp>

using ::testing::HasSubstr;

namespace {

using namespace Catch::Generators;

// A simple external collaborator used by the tests: a concrete generator that
// yields a fixed sequence of values. This is *not* simulating any internal
// behavior of FilterGenerator; it's just a source of values.
// It conforms to the public IGenerator<T> interface.
template <typename T>
class VectorGenerator final : public IGenerator<T> {
public:
    explicit VectorGenerator(std::vector<T> values)
        : data_(std::move(values)), idx_(0) {}

    T const& get() const override {
        // Precondition in Catch2: get() is only called when current is valid.
        // Our tests only call get() when at least one element exists.
        return data_.at(idx_);
    }

    bool next() override {
        if (idx_ + 1 < data_.size()) {
            ++idx_;
            return true;
        }
        return false;
    }

private:
    std::vector<T> data_;
    std::size_t idx_;
};

// Helper to wrap our collaborator into Catch2's GeneratorWrapper<T>
template <typename T>
GeneratorWrapper<T> wrapVec(std::vector<T> vals) {
    return GeneratorWrapper<T>(
        Catch::Detail::make_unique<VectorGenerator<T>>(std::move(vals)));
}

} // namespace

// ------------------------- Tests -------------------------

// Fixture kept minimal for consistency with your naming convention.
class FilterGeneratorTest_1108 : public ::testing::Test {};

// Normal operation: constructor finds the first value that satisfies predicate,
// even if the very first underlying value does not. Then next() advances to the
// next satisfying value and eventually exhausts.
TEST_F(FilterGeneratorTest_1108, ConstructorSkipsUntilFirstMatch_1108) {
    auto wrapped = wrapVec<int>({1, 2, 3, 4}); // underlying values
    auto is_even = [](int v) { return v % 2 == 0; };

    FilterGenerator<int, decltype(is_even)> sut(is_even, std::move(wrapped));

    // After construction, the current value must be the first matching one (2).
    EXPECT_EQ(sut.get(), 2);

    // next() should move to the next matching value (4) and then exhaust.
    EXPECT_TRUE(sut.next());
    EXPECT_EQ(sut.get(), 4);

    EXPECT_FALSE(sut.next()); // no more even numbers
}

// Normal operation: predicate allows all — behavior mirrors the underlying generator.
TEST_F(FilterGeneratorTest_1108, PredicateAlwaysTrueMirrorsUnderlying_1108) {
    auto wrapped = wrapVec<int>({5, 6});
    auto always_true = [](int) { return true; };

    FilterGenerator<int, decltype(always_true)> sut(always_true, std::move(wrapped));

    EXPECT_EQ(sut.get(), 5);
    EXPECT_TRUE(sut.next());
    EXPECT_EQ(sut.get(), 6);
    EXPECT_FALSE(sut.next());
}

// Exceptional case: no values satisfy the predicate.
// Observable behavior: construction throws a generator exception with the documented message.
TEST_F(FilterGeneratorTest_1108, ThrowsWhenNoValidValueExists_1108) {
    auto wrapped = wrapVec<int>({7, 9, 11});
    auto always_false = [](int) { return false; };

    try {
        FilterGenerator<int, decltype(always_false)> sut(always_false, std::move(wrapped));
        // If we got here, no exception was thrown — fail the test.
        FAIL() << "Expected a generator exception when no valid value exists";
    } catch (const Catch::Generators::GeneratorException& ex) {
        // Message is part of the observable contract from the partial code.
        EXPECT_THAT(std::string{ex.what()},
                    HasSubstr("No valid value found in filtered generator"));
    } catch (...) {
        FAIL() << "Expected Catch::Generators::GeneratorException";
    }
}

// Boundary-ish behavior: first underlying value already matches — constructor should
// accept it as the initial current value without requiring additional next() to start.
TEST_F(FilterGeneratorTest_1108, FirstValueMatchesIsUsedAsInitial_1108) {
    auto wrapped = wrapVec<int>({10, 12, 14});
    auto ge_ten = [](int v) { return v >= 10; };

    FilterGenerator<int, decltype(ge_ten)> sut(ge_ten, std::move(wrapped));

    // The first element already matches; it should be the current value.
    EXPECT_EQ(sut.get(), 10);

    // Step through to ensure subsequent matching values are surfaced, then exhausted.
    EXPECT_TRUE(sut.next());
    EXPECT_EQ(sut.get(), 12);
    EXPECT_TRUE(sut.next());
    EXPECT_EQ(sut.get(), 14);
    EXPECT_FALSE(sut.next());
}
