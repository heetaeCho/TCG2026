#include <gtest/gtest.h>

// Include the header for the class under test
#include "catch2/internal/catch_clara.hpp"

using namespace Catch::Clara::Detail;

// Test fixture for ParserBase
class ParserBaseTest_655 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that cardinality returns the expected default value of 1
TEST_F(ParserBaseTest_655, CardinalityReturnsOne_655) {
    ParserBase parser;
    EXPECT_EQ(parser.cardinality(), 1u);
}

// Test that cardinality returns consistent value on multiple calls
TEST_F(ParserBaseTest_655, CardinalityIsConsistentAcrossMultipleCalls_655) {
    ParserBase parser;
    size_t first = parser.cardinality();
    size_t second = parser.cardinality();
    EXPECT_EQ(first, second);
}

// Test that cardinality returns the same value for different instances
TEST_F(ParserBaseTest_655, CardinalityIsSameForDifferentInstances_655) {
    ParserBase parser1;
    ParserBase parser2;
    EXPECT_EQ(parser1.cardinality(), parser2.cardinality());
}

// Test that cardinality return type is size_t and value is non-zero
TEST_F(ParserBaseTest_655, CardinalityIsNonZero_655) {
    ParserBase parser;
    EXPECT_GT(parser.cardinality(), 0u);
}

// Test that the returned cardinality is exactly 1 (boundary: not 0, not 2)
TEST_F(ParserBaseTest_655, CardinalityIsExactlyOne_655) {
    ParserBase parser;
    EXPECT_NE(parser.cardinality(), 0u);
    EXPECT_NE(parser.cardinality(), 2u);
    EXPECT_EQ(parser.cardinality(), 1u);
}
