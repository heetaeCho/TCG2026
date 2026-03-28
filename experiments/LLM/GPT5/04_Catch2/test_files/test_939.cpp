// TEST_ID: 939

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <type_traits>

// Include the provided interface (as given in your tree)
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Generators::IteratorGenerator;

class IteratorGeneratorTest_939 : public ::testing::Test {};

// Verifies that get() returns the first element immediately after construction.
// Also asserts the return type is a const reference via compile-time check.
TEST_F(IteratorGeneratorTest_939, Construction_GetReturnsFirstElement_939) {
    std::vector<int> src{10, 20, 30};
    IteratorGenerator<int> gen(src.begin(), src.end());

    static_assert(std::is_same_v<decltype(gen.get()), int const&>, "get() must return const&");

    EXPECT_EQ(gen.get(), 10);
}

// Verifies normal iteration behavior: next() advances through all elements,
// returning true while advancing is possible and false when exhausted.
// (We never call get() after next() has returned false.)
TEST_F(IteratorGeneratorTest_939, NextAdvancesUntilExhausted_939) {
    std::vector<int> src{1, 2, 3};
    IteratorGenerator<int> gen(src.begin(), src.end());

    EXPECT_EQ(gen.get(), 1);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);

    EXPECT_FALSE(gen.next()); // exhausted
}

// Boundary condition: single-element range.
// After observing the single element, next() should report no further values.
TEST_F(IteratorGeneratorTest_939, SingleElementRange_ExhaustsAfterFirstAdvance_939) {
    std::vector<std::string> src{"only"};
    IteratorGenerator<std::string> gen(src.begin(), src.end());

    EXPECT_EQ(gen.get(), "only");
    EXPECT_FALSE(gen.next()); // no more elements
}

// Observable reference stability: get() returns a const reference to the
// current element; calling get() repeatedly without advancing should yield
// the same referent (address equality).
TEST_F(IteratorGeneratorTest_939, GetReferenceStableUntilAdvanced_939) {
    std::vector<std::string> src{"a", "b"};
    IteratorGenerator<std::string> gen(src.begin(), src.end());

    auto const* first_ptr = &gen.get();
    auto const* first_ptr_again = &gen.get();
    EXPECT_EQ(first_ptr, first_ptr_again) << "get() should refer to the same element until next() is called";

    ASSERT_TRUE(gen.next());
    auto const* second_ptr = &gen.get();
    EXPECT_NE(first_ptr, second_ptr) << "Reference should change after advancing to the next element";
}

// Observable isolation from source: the generator copies values from the input
// range at construction. Subsequent mutations of the source should not affect
// values observed via get()/next().
TEST_F(IteratorGeneratorTest_939, SourceMutationDoesNotAffectSequence_939) {
    std::vector<int> src{5, 6, 7};
    IteratorGenerator<int> gen(src.begin(), src.end());

    // Mutate the source after constructing the generator
    src[0] = 50;
    src.push_back(999);

    // The generator should still yield the original copied sequence {5,6,7}
    EXPECT_EQ(gen.get(), 5);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 6);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 7);
    EXPECT_FALSE(gen.next()); // should not see the later push_back(999)
}

// Exceptional/edge case: constructing with an empty range.
// We do not depend on the exact exception type; we assert it throws an std::exception.
TEST_F(IteratorGeneratorTest_939, EmptyRangeConstructionThrows_939) {
    std::vector<int> empty;
    // Some implementations enforce non-empty input and throw; we verify this observable behavior.
    EXPECT_THROW(
        (IteratorGenerator<int>(empty.begin(), empty.end())),
        std::exception
    );
}
