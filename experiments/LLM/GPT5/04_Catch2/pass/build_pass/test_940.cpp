// File: tests/IteratorGeneratorTests_940.cpp

#include <gtest/gtest.h>
#include <vector>
#include <string>

// Include the amalgamated Catch2 header that declares IteratorGenerator.
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Generators::IteratorGenerator;

//
// Test fixture kept minimal — no peeking into private state.
//
class IteratorGeneratorTest_940 : public ::testing::Test {
protected:
    template <typename T>
    static IteratorGenerator<T> makeGen(const std::vector<T>& v) {
        return IteratorGenerator<T>(v.begin(), v.end());
    }
};

// --- Normal operation: multiple elements ---
TEST_F(IteratorGeneratorTest_940, IteratesThroughAllElements_940) {
    std::vector<int> data{10, 20, 30};
    auto gen = IteratorGenerator<int>(data.begin(), data.end());

    // Initially, get() should expose the first element via the public interface.
    EXPECT_EQ(gen.get(), 10);

    // Advance 1 -> should succeed and expose next
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);

    // Advance 2 -> should succeed and expose next
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 30);

    // Advance past the last -> should report no more values
    EXPECT_FALSE(gen.next());
}

// --- Boundary condition: single element range ---
TEST_F(IteratorGeneratorTest_940, SingleElementStopsAfterFirstAdvance_940) {
    std::vector<std::string> data{"only"};
    auto gen = IteratorGenerator<std::string>(data.begin(), data.end());

    // First visible value
    EXPECT_EQ(gen.get(), "only");

    // Advancing once should report no further values
    EXPECT_FALSE(gen.next());
}

// --- Boundary/robustness: two elements, verify final state transition ---
TEST_F(IteratorGeneratorTest_940, TwoElementsFinalAdvanceReportsFalse_940) {
    std::vector<int> data{1, 2};
    auto gen = IteratorGenerator<int>(data.begin(), data.end());

    // First value
    EXPECT_EQ(gen.get(), 1);

    // Move to second
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);

    // Move past end -> should return false
    EXPECT_FALSE(gen.next());
}
