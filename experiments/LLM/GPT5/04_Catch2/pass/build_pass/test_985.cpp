// File: tests/classify_outliers_tests_985.cpp

#include <gtest/gtest.h>

// Only include the public struct declaration; do not depend on internals.
#include "catch2/benchmark/catch_outlier_classification.hpp"

// Forward declare the function under test in its namespace (no implementation).
namespace Catch { namespace Benchmark { namespace Detail {
    OutlierClassification classify_outliers(double const* first, double const* last);
}}}

using Catch::Benchmark::OutlierClassification;
using Catch::Benchmark::Detail::classify_outliers;

// Helper to invoke classify_outliers on a container
template <typename Contiguous>
static OutlierClassification Classify(const Contiguous& c) {
    return classify_outliers(c.data(), c.data() + c.size());
}

// ------------------------------------------------------------------
// TEST_ID: 985
// ------------------------------------------------------------------

// All values identical -> quartiles equal, IQR = 0 -> thresholds collapse to that value.
// Because comparisons are strict (< and >), equal values should NOT be counted as outliers.
TEST(ClassifyOutliersTest_985, AllEqual_NoOutliers_985) {
    std::vector<double> v(20, 42.0);
    auto o = Classify(v);

    EXPECT_EQ(o.samples_seen, static_cast<int>(v.size()));
    EXPECT_EQ(o.low_severe, 0);
    EXPECT_EQ(o.low_mild,   0);
    EXPECT_EQ(o.high_mild,  0);
    EXPECT_EQ(o.high_severe,0);
}

// Single element is a degenerate case of "all equal" and should also yield no outliers.
TEST(ClassifyOutliersTest_985, SingleElement_NoOutliers_985) {
    std::vector<double> v{3.14};
    auto o = Classify(v);

    EXPECT_EQ(o.samples_seen, 1);
    EXPECT_EQ(o.low_severe, 0);
    EXPECT_EQ(o.low_mild,   0);
    EXPECT_EQ(o.high_mild,  0);
    EXPECT_EQ(o.high_severe,0);
}

// Many zeros ensure q1 == q3 == 0 (IQR = 0), so any value strictly below 0 is low_severe
// and any value strictly above 0 is high_severe (due to strict comparisons).
TEST(ClassifyOutliersTest_985, IQRZero_ExtremesBecomeSevere_985) {
    std::vector<double> v(30, 0.0);
    v.push_back(-100.0);
    v.push_back(+100.0);

    auto o = Classify(v);

    EXPECT_EQ(o.samples_seen, static_cast<int>(v.size()));
    EXPECT_EQ(o.low_mild,   0);
    EXPECT_EQ(o.high_mild,  0);
    EXPECT_EQ(o.low_severe, 1);
    EXPECT_EQ(o.high_severe,1);
}

// Construct a robust bimodal set with a large plateau at 0 and 1 so that q1 ≈ 0, q3 ≈ 1,
// giving IQR ≈ 1. Then thresholds are approximately:
//   lom = -1.5, los = -3, him = 2.5, his = 4
// Add points that should land in each "mild" and "severe" region on both tails.
// This relies only on observable classification results.
TEST(ClassifyOutliersTest_985, MildAndSevereBothSides_985) {
    std::vector<double> base;
    base.insert(base.end(), 200, 0.0);  // large plateau at 0
    base.insert(base.end(), 200, 1.0);  // large plateau at 1

    // Add values designed to fall into each bucket given IQR around 1
    base.push_back(-2.0); // between -3 and -1.5  -> low_mild
    base.push_back(-4.0); // < -3                 -> low_severe
    base.push_back( 3.0); // between 2.5 and 4    -> high_mild
    base.push_back( 5.0); // > 4                  -> high_severe

    auto o = Classify(base);

    EXPECT_EQ(o.samples_seen, static_cast<int>(base.size()));

    // Expect exactly one in each of the four outlier bins
    EXPECT_EQ(o.low_mild,    1);
    EXPECT_EQ(o.low_severe,  1);
    EXPECT_EQ(o.high_mild,   1);
    EXPECT_EQ(o.high_severe, 1);
}
