// File: parser_base_cardinality_test_655.cpp

#include <gtest/gtest.h>
#include "catch2/internal/catch_clara.hpp"  // Uses the provided interface

using Catch::Clara::Detail::ParserBase;

// Verifies basic, observable behavior: cardinality() returns 1.
TEST(ParserBaseTest_655, CardinalityIsOne_655) {
    ParserBase p;
    EXPECT_EQ(static_cast<size_t>(1), p.cardinality());
}

// Verifies cardinality() is stable across repeated calls (no internal state assumptions).
TEST(ParserBaseTest_655, CardinalityConsistentAcrossCalls_655) {
    ParserBase p;
    size_t first = p.cardinality();
    size_t second = p.cardinality();
    EXPECT_EQ(first, second);
    EXPECT_EQ(static_cast<size_t>(1), first);
}

// Verifies const-correctness: callable on a const instance.
TEST(ParserBaseTest_655, CardinalityOnConstInstance_655) {
    const ParserBase p;
    EXPECT_EQ(static_cast<size_t>(1), p.cardinality());
}

// Verifies behavior across multiple independent instances (no shared state assumed).
TEST(ParserBaseTest_655, CardinalityMultipleInstances_655) {
    ParserBase a;
    ParserBase b;
    EXPECT_EQ(a.cardinality(), b.cardinality());
    EXPECT_EQ(static_cast<size_t>(1), a.cardinality());
    EXPECT_EQ(static_cast<size_t>(1), b.cardinality());
}
