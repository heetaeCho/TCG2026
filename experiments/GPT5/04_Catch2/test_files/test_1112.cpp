// IteratorGenerator_tests_1112.cpp
#include <gtest/gtest.h>

// Include the amalgamated Catch2 header that provides IteratorGenerator
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Generators::IteratorGenerator;

namespace {

// A small helper to construct in a noexcept context inside EXPECT_* macros.
template <typename It, typename Sent>
static void construct_noop(It first, Sent last) {
    IteratorGenerator<typename std::iterator_traits<It>::value_type> gen(first, last);
    (void)gen; // silence unused warning
}

} // namespace

// ===== Normal operation =====

TEST(IteratorGeneratorTest_1112, ConstructWithNonEmptyRange_DoesNotThrow_1112) {
    std::vector<int> v{10, 20, 30};
    EXPECT_NO_THROW(construct_noop(v.begin(), v.end()));
}

TEST(IteratorGeneratorTest_1112, Iteration_YieldsElementsInOrder_1112) {
    std::vector<int> v{10, 20, 30};
    IteratorGenerator<int> gen(v.begin(), v.end());

    // Initial element is observable via get()
    EXPECT_EQ(gen.get(), 10);

    // next() advances and indicates more elements
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 30);

    // At the end, next() reports no more elements
    EXPECT_FALSE(gen.next());
}

TEST(IteratorGeneratorTest_1112, SingleElementRange_Boundary_1112) {
    std::vector<int> v{42};
    IteratorGenerator<int> gen(v.begin(), v.end());

    EXPECT_EQ(gen.get(), 42);
    EXPECT_FALSE(gen.next()); // No next element
}

TEST(IteratorGeneratorTest_1112, GetIsIdempotentWithoutNext_1112) {
    std::vector<std::string> v{"alpha", "beta"};
    IteratorGenerator<std::string> gen(v.begin(), v.end());

    // Multiple calls to get() without advancing should observe the same value
    EXPECT_EQ(gen.get(), "alpha");
    EXPECT_EQ(gen.get(), "alpha");
}

TEST(IteratorGeneratorTest_1112, NextBeforeFirstGet_AdvancesToSecond_1112) {
    std::vector<int> v{1, 2, 3};
    IteratorGenerator<int> gen(v.begin(), v.end());

    // Advance before any call to get()
    EXPECT_TRUE(gen.next());
    // Now the observable current element should be the second one
    EXPECT_EQ(gen.get(), 2);
}

// ===== Exceptional / error cases (observable via interface) =====

TEST(IteratorGeneratorTest_1112, ConstructWithEmptyRange_Throws_1112) {
    std::vector<int> empty;
    // We do not rely on the specific exception type or message — only that an exception is thrown.
    EXPECT_ANY_THROW(IteratorGenerator<int>(empty.begin(), empty.end()));
}

// ===== Iterator/Sentinel variety (interface-level) =====

TEST(IteratorGeneratorTest_1112, WorksWithPointerIterators_1112) {
    const char* arr[] = {"a", "bb", "ccc"};
    auto first = &arr[0];
    auto last  = &arr[3];

    IteratorGenerator<const char*> gen(first, last);

    EXPECT_STREQ(gen.get(), std::string("a").c_str());
    EXPECT_TRUE(gen.next());
    EXPECT_STREQ(gen.get(), std::string("bb").c_str());
    EXPECT_TRUE(gen.next());
    EXPECT_STREQ(gen.get(), std::string("ccc").c_str());
    EXPECT_FALSE(gen.next());
}
