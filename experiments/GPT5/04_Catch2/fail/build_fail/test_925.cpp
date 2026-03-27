// File: tests/FilterGenerator_filter_tests_925.cpp

#include <gtest/gtest.h>
#include "Catch2/extras/catch_amalgamated.hpp"

#include <vector>
#include <stdexcept>

using namespace Catch::Generators;

class FilterGeneratorTest_925 : public ::testing::Test {};

// [Normal] Filters only even numbers from a small set
TEST_F(FilterGeneratorTest_925, FiltersEvenNumbers_925) {
    auto base = values({1, 2, 3, 4, 5});
    auto gen  = filter([](int x){ return x % 2 == 0; }, CATCH_MOVE(base));

    std::vector<int> out;
    // Access the first acceptable element, then advance until exhaustion.
    out.push_back(gen.get());
    while (gen.next()) {
        out.push_back(gen.get());
    }
    EXPECT_EQ(out, (std::vector<int>{2, 4}));
}

// [Boundary] All values rejected -> observable error when attempting to read
TEST_F(FilterGeneratorTest_925, AllValuesRejected_Throws_925) {
    auto base = values({1, 3, 5});
    auto gen  = filter([](int x){ return x % 2 == 0; }, CATCH_MOVE(base));

    // When no element satisfies the predicate, attempting to read should error.
    EXPECT_THROW(
        (void)gen.get(),
        Catch::Generators::GeneratorException
    );
}

// [Boundary] First several values filtered out -> first readable value is first match
TEST_F(FilterGeneratorTest_925, SkipsUntilFirstMatch_925) {
    auto base = values({1, 1, 1, 4, 6});
    auto gen  = filter([](int x){ return x % 2 == 0; }, CATCH_MOVE(base));

    // The initial readable value should be the first matching element.
    EXPECT_EQ(gen.get(), 4);

    // Then it should proceed normally.
    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 6);
    EXPECT_FALSE(gen.next());
}

// [Normal] All values accepted -> pass-through sequence
TEST_F(FilterGeneratorTest_925, AllValuesAccepted_Passthrough_925) {
    auto base = values({1, 2, 3});
    auto gen  = filter([](int){ return true; }, CATCH_MOVE(base));

    std::vector<int> out;
    out.push_back(gen.get());
    while (gen.next()) {
        out.push_back(gen.get());
    }
    EXPECT_EQ(out, (std::vector<int>{1, 2, 3}));
}

// [Exceptional] Predicate throws -> exception propagates during iteration
TEST_F(FilterGeneratorTest_925, PredicateException_Propagates_925) {
    auto base = values({1, 2, 3});
    auto gen  = filter([](int x){
        if (x == 2) throw std::runtime_error("boom");
        return true;
    }, CATCH_MOVE(base));

    // First value (1) is fine.
    EXPECT_NO_THROW((void)gen.get());

    // Advancing into/over value 2 should surface the predicate's exception.
    EXPECT_THROW(
        [&]{
            // Either next() or the subsequent get() may trigger the throw, depending on
            // when the underlying generator/predicate is evaluated—treat as a black box.
            (void)gen.next();
            (void)gen.get();
        }(),
        std::runtime_error
    );
}
