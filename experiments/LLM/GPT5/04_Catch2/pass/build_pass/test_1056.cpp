// File: tests/generators/Generators_ctor_and_iteration_1056.cpp

#include <gtest/gtest.h>
#include "catch2/generators/catch_generators.hpp"

using Catch::Generators::Generators;

class GeneratorsTest_1056 : public ::testing::Test {};

// [Normal operation] Multiple values: order + termination
TEST_F(GeneratorsTest_1056, ConstructWithInts_YieldsInOrder_1056) {
    Generators<int> g(1, 2, 3);

    // First element is available immediately
    EXPECT_EQ(g.get(), 1);

    // Advance to second
    ASSERT_TRUE(g.next());
    EXPECT_EQ(g.get(), 2);

    // Advance to third
    ASSERT_TRUE(g.next());
    EXPECT_EQ(g.get(), 3);

    // End should be reported
    EXPECT_FALSE(g.next());
}

// [Boundary] Single element: immediately ends on next()
TEST_F(GeneratorsTest_1056, SingleElement_TerminatesAfterFirst_1056) {
    Generators<int> g(42);

    EXPECT_EQ(g.get(), 42);
    EXPECT_FALSE(g.next()); // nothing after the single value
}

// [Boundary / Type handling] Accepts convertible types via forwarding/SFINAE
TEST_F(GeneratorsTest_1056, AcceptsConvertibleTypes_AndPreservesOrder_1056) {
    short s = 7;
    long  l = 8;
    double d = 9.0; // convertible to int

    Generators<int> g(s, l, d);

    EXPECT_EQ(g.get(), static_cast<int>(s));

    ASSERT_TRUE(g.next());
    EXPECT_EQ(g.get(), static_cast<int>(l));

    ASSERT_TRUE(g.next());
    EXPECT_EQ(g.get(), static_cast<int>(d));

    EXPECT_FALSE(g.next());
}

// [Normal / API robustness] Mix lvalues and rvalues; observable sequence is stable
TEST_F(GeneratorsTest_1056, HandlesLvaluesAndRvalues_1056) {
    std::string a = "alpha";
    std::string b = "beta";

    Generators<std::string> g(a, std::string("mid"), b);

    EXPECT_EQ(g.get(), "alpha");

    ASSERT_TRUE(g.next());
    EXPECT_EQ(g.get(), "mid");

    ASSERT_TRUE(g.next());
    EXPECT_EQ(g.get(), "beta");

    EXPECT_FALSE(g.next());
}

// [Edge interaction] Re-checking get() without advancing should remain stable
TEST_F(GeneratorsTest_1056, GetIsStableWithoutNext_1056) {
    Generators<int> g(5, 6);

    // Multiple reads of get() before advancing should return the same current value
    EXPECT_EQ(g.get(), 5);
    EXPECT_EQ(g.get(), 5);

    ASSERT_TRUE(g.next());
    EXPECT_EQ(g.get(), 6);

    EXPECT_FALSE(g.next());
}
