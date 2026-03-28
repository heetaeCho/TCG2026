#include <gtest/gtest.h>
#include "./TestProjects/Catch2/src/catch2/benchmark/catch_outlier_classification.hpp"

class OutlierClassificationTest_68 : public ::testing::Test {
protected:
    Catch::Benchmark::OutlierClassification oc;
};

// Test default initialization - all fields should be zero
TEST_F(OutlierClassificationTest_68, DefaultInitialization_68) {
    EXPECT_EQ(oc.samples_seen, 0);
    EXPECT_EQ(oc.low_severe, 0);
    EXPECT_EQ(oc.low_mild, 0);
    EXPECT_EQ(oc.high_mild, 0);
    EXPECT_EQ(oc.high_severe, 0);
}

// Test total() with all default (zero) values
TEST_F(OutlierClassificationTest_68, TotalWithDefaultValues_68) {
    EXPECT_EQ(oc.total(), 0);
}

// Test total() sums all four outlier categories
TEST_F(OutlierClassificationTest_68, TotalSumsAllOutlierCategories_68) {
    oc.low_severe = 1;
    oc.low_mild = 2;
    oc.high_mild = 3;
    oc.high_severe = 4;
    EXPECT_EQ(oc.total(), 10);
}

// Test total() does not include samples_seen
TEST_F(OutlierClassificationTest_68, TotalDoesNotIncludeSamplesSeen_68) {
    oc.samples_seen = 100;
    oc.low_severe = 1;
    oc.low_mild = 2;
    oc.high_mild = 3;
    oc.high_severe = 4;
    EXPECT_EQ(oc.total(), 10);
}

// Test total() with only low_severe set
TEST_F(OutlierClassificationTest_68, TotalWithOnlyLowSevere_68) {
    oc.low_severe = 5;
    EXPECT_EQ(oc.total(), 5);
}

// Test total() with only low_mild set
TEST_F(OutlierClassificationTest_68, TotalWithOnlyLowMild_68) {
    oc.low_mild = 7;
    EXPECT_EQ(oc.total(), 7);
}

// Test total() with only high_mild set
TEST_F(OutlierClassificationTest_68, TotalWithOnlyHighMild_68) {
    oc.high_mild = 3;
    EXPECT_EQ(oc.total(), 3);
}

// Test total() with only high_severe set
TEST_F(OutlierClassificationTest_68, TotalWithOnlyHighSevere_68) {
    oc.high_severe = 9;
    EXPECT_EQ(oc.total(), 9);
}

// Test total() with large values
TEST_F(OutlierClassificationTest_68, TotalWithLargeValues_68) {
    oc.low_severe = 10000;
    oc.low_mild = 20000;
    oc.high_mild = 30000;
    oc.high_severe = 40000;
    EXPECT_EQ(oc.total(), 100000);
}

// Test total() is constexpr compatible
TEST_F(OutlierClassificationTest_68, TotalIsConstexpr_68) {
    constexpr Catch::Benchmark::OutlierClassification constOc{50, 1, 2, 3, 4};
    constexpr int t = constOc.total();
    EXPECT_EQ(t, 10);
}

// Test that total() works correctly when fields are modified after construction
TEST_F(OutlierClassificationTest_68, TotalAfterModification_68) {
    oc.low_severe = 1;
    oc.low_mild = 1;
    oc.high_mild = 1;
    oc.high_severe = 1;
    EXPECT_EQ(oc.total(), 4);

    oc.low_severe = 10;
    EXPECT_EQ(oc.total(), 13);
}

// Test total() with zero values explicitly set
TEST_F(OutlierClassificationTest_68, TotalWithExplicitZeros_68) {
    oc.low_severe = 0;
    oc.low_mild = 0;
    oc.high_mild = 0;
    oc.high_severe = 0;
    EXPECT_EQ(oc.total(), 0);
}

// Test that samples_seen can be set independently and does not affect total
TEST_F(OutlierClassificationTest_68, SamplesSeenIndependentOfTotal_68) {
    oc.samples_seen = 500;
    EXPECT_EQ(oc.total(), 0);
    EXPECT_EQ(oc.samples_seen, 500);
}

// Test aggregate initialization
TEST_F(OutlierClassificationTest_68, AggregateInitialization_68) {
    Catch::Benchmark::OutlierClassification oc2{100, 5, 10, 15, 20};
    EXPECT_EQ(oc2.samples_seen, 100);
    EXPECT_EQ(oc2.low_severe, 5);
    EXPECT_EQ(oc2.low_mild, 10);
    EXPECT_EQ(oc2.high_mild, 15);
    EXPECT_EQ(oc2.high_severe, 20);
    EXPECT_EQ(oc2.total(), 50);
}

// Test total with a single field having value of 1
TEST_F(OutlierClassificationTest_68, TotalBoundarySingleOne_68) {
    oc.low_severe = 1;
    EXPECT_EQ(oc.total(), 1);
}

// Test that total() on a const object works
TEST_F(OutlierClassificationTest_68, TotalOnConstObject_68) {
    oc.low_severe = 2;
    oc.low_mild = 3;
    oc.high_mild = 4;
    oc.high_severe = 5;
    const Catch::Benchmark::OutlierClassification& constRef = oc;
    EXPECT_EQ(constRef.total(), 14);
}
