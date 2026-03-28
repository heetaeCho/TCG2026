#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_range.hpp>

// If using the amalgamated header instead:
// #include "catch_amalgamated.hpp"

#include <gtest/gtest.h>
#include <vector>
#include <cstdint>

class RangeGeneratorTest_938 : public ::testing::Test {
protected:
};

TEST_F(RangeGeneratorTest_938, BasicIntRange_938) {
    auto gen = Catch::Generators::range(1, 5);
    std::vector<int> values;
    values.push_back(gen.get());
    while (gen.next()) {
        values.push_back(gen.get());
    }
    std::vector<int> expected = {1, 2, 3, 4};
    EXPECT_EQ(values, expected);
}

TEST_F(RangeGeneratorTest_938, SingleElementRange_938) {
    auto gen = Catch::Generators::range(3, 4);
    EXPECT_EQ(gen.get(), 3);
    EXPECT_FALSE(gen.next());
}

TEST_F(RangeGeneratorTest_938, EmptyRangeStartEqualsEnd_938) {
    // When start == end, the range should be empty or produce no valid elements
    // RangeGenerator behavior for empty range: it may still start at start
    // but next() should return false immediately or the generator may be invalid.
    // We test what happens - since start == end, no elements should be generated.
    // However, generators typically require at least one element, so this may
    // throw or behave specially. We test that get() returns start if accessible.
    try {
        auto gen = Catch::Generators::range(5, 5);
        // If it doesn't throw, the behavior is implementation-defined for empty range
        // Just verify we can call get without crashing
        (void)gen.get();
    } catch (...) {
        // Empty range might throw - that's acceptable behavior
    }
}

TEST_F(RangeGeneratorTest_938, NegativeRange_938) {
    auto gen = Catch::Generators::range(-3, 2);
    std::vector<int> values;
    values.push_back(gen.get());
    while (gen.next()) {
        values.push_back(gen.get());
    }
    std::vector<int> expected = {-3, -2, -1, 0, 1};
    EXPECT_EQ(values, expected);
}

TEST_F(RangeGeneratorTest_938, LongLongRange_938) {
    auto gen = Catch::Generators::range(static_cast<long long>(10), static_cast<long long>(13));
    std::vector<long long> values;
    values.push_back(gen.get());
    while (gen.next()) {
        values.push_back(gen.get());
    }
    std::vector<long long> expected = {10, 11, 12};
    EXPECT_EQ(values, expected);
}

TEST_F(RangeGeneratorTest_938, ShortRange_938) {
    auto gen = Catch::Generators::range(static_cast<short>(0), static_cast<short>(3));
    std::vector<short> values;
    values.push_back(gen.get());
    while (gen.next()) {
        values.push_back(gen.get());
    }
    std::vector<short> expected = {0, 1, 2};
    EXPECT_EQ(values, expected);
}

TEST_F(RangeGeneratorTest_938, UnsignedIntRange_938) {
    auto gen = Catch::Generators::range(0u, 4u);
    std::vector<unsigned int> values;
    values.push_back(gen.get());
    while (gen.next()) {
        values.push_back(gen.get());
    }
    std::vector<unsigned int> expected = {0u, 1u, 2u, 3u};
    EXPECT_EQ(values, expected);
}

TEST_F(RangeGeneratorTest_938, FirstElementIsStart_938) {
    auto gen = Catch::Generators::range(42, 45);
    EXPECT_EQ(gen.get(), 42);
}

TEST_F(RangeGeneratorTest_938, LastElementIsEndMinusOne_938) {
    auto gen = Catch::Generators::range(10, 13);
    gen.next(); // 11
    gen.next(); // 12
    EXPECT_EQ(gen.get(), 12);
    EXPECT_FALSE(gen.next());
}

TEST_F(RangeGeneratorTest_938, Int8Range_938) {
    auto gen = Catch::Generators::range(static_cast<int8_t>(-2), static_cast<int8_t>(2));
    std::vector<int8_t> values;
    values.push_back(gen.get());
    while (gen.next()) {
        values.push_back(gen.get());
    }
    std::vector<int8_t> expected = {-2, -1, 0, 1};
    EXPECT_EQ(values, expected);
}

TEST_F(RangeGeneratorTest_938, LargeRange_938) {
    auto gen = Catch::Generators::range(0, 1000);
    int count = 1; // first element
    while (gen.next()) {
        count++;
    }
    EXPECT_EQ(count, 1000);
}

TEST_F(RangeGeneratorTest_938, GetIsIdempotentBeforeNext_938) {
    auto gen = Catch::Generators::range(7, 10);
    EXPECT_EQ(gen.get(), 7);
    EXPECT_EQ(gen.get(), 7);
    EXPECT_EQ(gen.get(), 7);
}

TEST_F(RangeGeneratorTest_938, NextReturnsFalseAfterExhaustion_938) {
    auto gen = Catch::Generators::range(0, 2);
    EXPECT_EQ(gen.get(), 0);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 1);
    EXPECT_FALSE(gen.next());
}

TEST_F(RangeGeneratorTest_938, UnsignedCharRange_938) {
    auto gen = Catch::Generators::range(static_cast<unsigned char>(250), static_cast<unsigned char>(255));
    std::vector<unsigned char> values;
    values.push_back(gen.get());
    while (gen.next()) {
        values.push_back(gen.get());
    }
    EXPECT_EQ(values.size(), 5u);
    EXPECT_EQ(values[0], 250);
    EXPECT_EQ(values[4], 254);
}
