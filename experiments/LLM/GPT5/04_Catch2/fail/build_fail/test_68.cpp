// File: tests/outlier_classification_total_test.cpp

#include <gtest/gtest.h>
#include "catch2/benchmark/catch_outlier_classification.hpp"

using Catch::Benchmark::OutlierClassification;

// Verifies default-constructed object reports zero total.
TEST(OutlierClassificationTest_68, DefaultTotalIsZero_68) {
    OutlierClassification oc;
    EXPECT_EQ(oc.total(), 0);
}

// Verifies each individual field contributes exactly its value to the total.
TEST(OutlierClassificationTest_68, IndividualFieldContribution_68) {
    OutlierClassification oc;

    oc.low_severe = 5;
    EXPECT_EQ(oc.total(), 5);

    oc = OutlierClassification{};
    oc.low_mild = 7;
    EXPECT_EQ(oc.total(), 7);

    oc = OutlierClassification{};
    oc.high_mild = 9;
    EXPECT_EQ(oc.total(), 9);

    oc = OutlierClassification{};
    oc.high_severe = 11;
    EXPECT_EQ(oc.total(), 11);
}

// Verifies total equals the sum of all publicly observable counters.
TEST(OutlierClassificationTest_68, SumOfAllFields_68) {
    OutlierClassification oc;
    oc.low_severe = 1;
    oc.low_mild = 2;
    oc.high_mild = 3;
    oc.high_severe = 4;

    EXPECT_EQ(oc.total(), 1 + 2 + 3 + 4);
}

// Verifies behavior with negative integers (observable via public fields).
// This does not assume validity of negatives—only that total reflects the sum.
TEST(OutlierClassificationTest_68, HandlesNegativeValues_68) {
    OutlierClassification oc;
    oc.low_severe = -2;
    oc.low_mild = 5;
    oc.high_mild = -1;
    oc.high_severe = 0;

    EXPECT_EQ(oc.total(), (-2) + 5 + (-1) + 0);
}

// Verifies large (but safe) values sum correctly without overflow, staying in-range of int.
TEST(OutlierClassificationTest_68, LargeValuesWithinIntRange_68) {
    OutlierClassification oc;

    // Choose values that keep the sum within INT limits portably.
    // For example, quarters of INT_MAX (implementation-defined but typical 32-bit).
    const int q = INT_MAX / 8; // Extra margin
    oc.low_severe = q;
    oc.low_mild = q;
    oc.high_mild = q;
    oc.high_severe = q;

    const int expected = q + q + q + q;
    EXPECT_EQ(oc.total(), expected);
}

// Verifies total() is callable on const instances (const-correctness).
TEST(OutlierClassificationTest_68, ConstCorrectness_68) {
    OutlierClassification oc;
    oc.low_severe = 3;
    oc.low_mild = 4;
    oc.high_mild = 0;
    oc.high_severe = 2;

    const OutlierClassification& cref = oc;
    EXPECT_EQ(cref.total(), 3 + 4 + 0 + 2);
}
