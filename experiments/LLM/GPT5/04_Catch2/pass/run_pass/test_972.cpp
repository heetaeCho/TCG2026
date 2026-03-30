// File: tests/ApproxMatcher_epsilon_test_972.cpp
#include <gtest/gtest.h>
#include <vector>

// Include the provided Catch2 amalgamated header where ApproxMatcher is declared
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Matchers::ApproxMatcher;

class ApproxMatcherEpsilonTest_972 : public ::testing::Test {};

// [972] Chainability: epsilon returns *this (reference to the same object)
TEST_F(ApproxMatcherEpsilonTest_972, EpsilonIsChainable_ReturnsSelf_972) {
    std::vector<double> comp{1.0, 2.0};
    ApproxMatcher<double, std::allocator<double>, std::allocator<double>> m(comp);

    // Call epsilon and ensure it returns the same object reference.
    auto* addr_before = &m;
    auto* addr_after  = &m.epsilon(1e-3);
    EXPECT_EQ(addr_before, addr_after);
}

// [972] Accepts various numeric types constructible to double (int, float, double, long double)
// We only verify the calls compile and return *this; we do not rely on internal behavior.
TEST_F(ApproxMatcherEpsilonTest_972, EpsilonAcceptsDifferentNumericTypes_972) {
    std::vector<double> comp{0.0};
    ApproxMatcher<double, std::allocator<double>, std::allocator<double>> m(comp);

    EXPECT_EQ(&m, &m.epsilon(1));              // int
    EXPECT_EQ(&m, &m.epsilon(1.0f));           // float
    EXPECT_EQ(&m, &m.epsilon(1.0));            // double
    long double ld = 1.0L;
    EXPECT_EQ(&m, &m.epsilon(ld));             // long double
}

// [972] Behavior: Tight epsilon should fail a close-but-outside-epsilon match,
// relaxing epsilon should make the same vectors match.
// This verifies epsilon actually affects observable matching behavior.
TEST_F(ApproxMatcherEpsilonTest_972, TightThenLooseEpsilonChangesMatchOutcome_972) {
    std::vector<double> comp{1.0, 2.0};
    std::vector<double> probe_close{1.001, 2.0}; // ~1e-3 difference on first element

    ApproxMatcher<double, std::allocator<double>, std::allocator<double>> m(comp);

    // With a very tight epsilon we expect mismatch
    m.epsilon(1e-6);
    EXPECT_FALSE(m.match(probe_close));

    // With a looser epsilon (1e-2) we expect it to match
    m.epsilon(1e-2);
    EXPECT_TRUE(m.match(probe_close));
}

// [972] Boundary: Empty vectors — reasonable expectation is that equal (both empty) matches,
// and epsilon calls remain chainable.
TEST_F(ApproxMatcherEpsilonTest_972, EmptyVectorsMatchRegardlessOfEpsilon_972) {
    std::vector<double> empty_comp;
    std::vector<double> empty_probe;

    ApproxMatcher<double, std::allocator<double>, std::allocator<double>> m(empty_comp);

    m.epsilon(1e-9);
    EXPECT_TRUE(m.match(empty_probe));

    m.epsilon(1e-2);
    EXPECT_TRUE(m.match(empty_probe));
}

// [972] Error/edge: Size mismatch should not be “fixed” by changing epsilon.
// We verify that even a very large epsilon does not cause size-mismatched vectors to match.
TEST_F(ApproxMatcherEpsilonTest_972, SizeMismatchDoesNotMatchEvenWithHugeEpsilon_972) {
    std::vector<double> comp{1.0, 2.0};
    std::vector<double> different_size{1.0, 2.0, 3.0};

    ApproxMatcher<double, std::allocator<double>, std::allocator<double>> m(comp);

    m.epsilon(1.0);     // moderate epsilon
    EXPECT_FALSE(m.match(different_size));

    m.epsilon(1e6);     // huge epsilon
    EXPECT_FALSE(m.match(different_size));
}
