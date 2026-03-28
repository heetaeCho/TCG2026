// File: tests/single_value_generator_next_tests_315.cpp

#include <gtest/gtest.h>
#include "Catch2/src/catch2/generators/catch_generators.hpp"

using Catch::Generators::SingleValueGenerator;

// Verifies that a freshly constructed generator reports no further values.
// Requirement covered: Normal operation of next() based on provided interface.
TEST(SingleValueGeneratorTest_315, NextReturnsFalseInitially_315) {
    SingleValueGenerator gen;
    EXPECT_FALSE(gen.next()) << "next() should return false on a fresh generator";
}

// Verifies that repeated calls to next() continue to report no further values.
// Requirement covered: Boundary/Repeated calls — observable behavior stays consistent.
TEST(SingleValueGeneratorTest_315, NextAlwaysFalseOnRepeatedCalls_315) {
    SingleValueGenerator gen;

    for (int i = 0; i < 5; ++i) {
        EXPECT_FALSE(gen.next()) << "next() should always return false";
    }
}
