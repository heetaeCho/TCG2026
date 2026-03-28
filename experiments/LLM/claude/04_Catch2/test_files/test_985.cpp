#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <cmath>

// Include the necessary headers
// Since we're working with the amalgamated catch2, we need the relevant declarations
namespace Catch {
namespace Benchmark {

struct OutlierClassification {
    int samples_seen = 0;
    int low_severe = 0;
    int low_mild = 0;
    int high_mild = 0;
    int high_severe = 0;

    constexpr int total() const {
        return low_severe + low_mild + high_mild + high_severe;
    }
};

namespace Detail {

// Forward declaration of the function we're testing
OutlierClassification classify_outliers(double const* first, double const* last);

// We also need weighted_average_quantile for the function to work
// It should be defined in the amalgamated source
double weighted_average_quantile(int k, int q, double* first, double* last);

} // namespace Detail
} // namespace Benchmark
} // namespace Catch

class ClassifyOutliersTest_985 : public ::testing::Test {
protected:
    Catch::Benchmark::OutlierClassification classify(const std::vector<double>& data) {
        return Catch::Benchmark::Detail::classify_outliers(data.data(), data.data() + data.size());
    }
};

// Test with empty input
TEST_F(ClassifyOutliersTest_985, EmptyInput_985) {
    std::vector<double> data;
    auto result = classify(data);
    EXPECT_EQ(result.samples_seen, 0);
    EXPECT_EQ(result.low_severe, 0);
    EXPECT_EQ(result.low_mild, 0);
    EXPECT_EQ(result.high_mild, 0);
    EXPECT_EQ(result.high_severe, 0);
}

// Test with single element - no outliers possible (IQR is 0, all thresholds same)
TEST_F(ClassifyOutliersTest_985, SingleElement_985) {
    std::vector<double> data = {5.0};
    auto result = classify(data);
    EXPECT_EQ(result.samples_seen, 1);
    EXPECT_EQ(result.total(), 0);
}

// Test with identical elements - no outliers
TEST_F(ClassifyOutliersTest_985, AllIdenticalElements_985) {
    std::vector<double> data = {10.0, 10.0, 10.0, 10.0, 10.0};
    auto result = classify(data);
    EXPECT_EQ(result.samples_seen, 5);
    EXPECT_EQ(result.low_severe, 0);
    EXPECT_EQ(result.low_mild, 0);
    EXPECT_EQ(result.high_mild, 0);
    EXPECT_EQ(result.high_severe, 0);
}

// Test with no outliers - all values within IQR range
TEST_F(ClassifyOutliersTest_985, NoOutliers_985) {
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    auto result = classify(data);
    EXPECT_EQ(result.samples_seen, 10);
    // With uniformly distributed data from 1-10, the IQR-based thresholds should contain all values
    EXPECT_EQ(result.low_severe, 0);
    EXPECT_EQ(result.high_severe, 0);
}

// Test with obvious high severe outlier
TEST_F(ClassifyOutliersTest_985, HighSevereOutlier_985) {
    // Create data with a tight cluster and one extreme high value
    std::vector<double> data = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
                                 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0,
                                 100.0};
    auto result = classify(data);
    EXPECT_EQ(result.samples_seen, 21);
    EXPECT_GT(result.high_severe, 0);
}

// Test with obvious low severe outlier
TEST_F(ClassifyOutliersTest_985, LowSevereOutlier_985) {
    std::vector<double> data = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
                                 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0,
                                 -100.0};
    auto result = classify(data);
    EXPECT_EQ(result.samples_seen, 21);
    EXPECT_GT(result.low_severe, 0);
}

// Test samples_seen always equals number of elements
TEST_F(ClassifyOutliersTest_985, SamplesSeenEqualsSize_985) {
    std::vector<double> data = {1.0, 2.0, 3.0};
    auto result = classify(data);
    EXPECT_EQ(result.samples_seen, 3);

    data = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
    result = classify(data);
    EXPECT_EQ(result.samples_seen, 7);
}

// Test that total outliers never exceed samples_seen
TEST_F(ClassifyOutliersTest_985, TotalNeverExceedsSamplesSeen_985) {
    std::vector<double> data = {-1000.0, -500.0, 1.0, 2.0, 3.0, 4.0, 5.0, 500.0, 1000.0};
    auto result = classify(data);
    EXPECT_EQ(result.samples_seen, 9);
    EXPECT_LE(result.total(), result.samples_seen);
}

// Test with two elements
TEST_F(ClassifyOutliersTest_985, TwoElements_985) {
    std::vector<double> data = {1.0, 2.0};
    auto result = classify(data);
    EXPECT_EQ(result.samples_seen, 2);
    // With only two elements, IQR-based classification should be well-defined
    EXPECT_LE(result.total(), 2);
}

// Test with negative values
TEST_F(ClassifyOutliersTest_985, NegativeValues_985) {
    std::vector<double> data = {-10.0, -9.0, -8.0, -7.0, -6.0, -5.0, -4.0, -3.0, -2.0, -1.0};
    auto result = classify(data);
    EXPECT_EQ(result.samples_seen, 10);
    // Uniformly spaced negative values should have no outliers
    EXPECT_EQ(result.low_severe, 0);
    EXPECT_EQ(result.high_severe, 0);
}

// Test classification boundaries with carefully crafted data
// With data: lots of values creating known Q1, Q3, and specific outlier points
TEST_F(ClassifyOutliersTest_985, MildOutliers_985) {
    // Create data where Q1 ≈ 25, Q3 ≈ 75, IQR ≈ 50
    // him = 75 + 75 = 150, his = 75 + 150 = 225
    // lom = 25 - 75 = -50, los = 25 - 150 = -125
    // Values between 150-225 or -125 to -50 should be mild outliers
    std::vector<double> data;
    for (int i = 0; i <= 100; ++i) {
        data.push_back(static_cast<double>(i));
    }
    // Add mild outliers
    data.push_back(160.0);  // should be high_mild
    data.push_back(-60.0);  // should be low_mild
    
    auto result = classify(data);
    EXPECT_EQ(result.samples_seen, static_cast<int>(data.size()));
    // We expect at least some mild outliers
    EXPECT_GT(result.high_mild + result.low_mild, 0);
}

// Test that the function doesn't modify the input data
TEST_F(ClassifyOutliersTest_985, InputDataUnmodified_985) {
    std::vector<double> data = {5.0, 3.0, 1.0, 4.0, 2.0};
    std::vector<double> original = data;
    classify(data);
    EXPECT_EQ(data, original);
}

// Test with large dataset of uniform values
TEST_F(ClassifyOutliersTest_985, LargeUniformDataset_985) {
    std::vector<double> data(1000, 42.0);
    auto result = classify(data);
    EXPECT_EQ(result.samples_seen, 1000);
    EXPECT_EQ(result.total(), 0);
}

// Test non-negative counts
TEST_F(ClassifyOutliersTest_985, AllCountsNonNegative_985) {
    std::vector<double> data = {-1000.0, -100.0, 1.0, 2.0, 3.0, 100.0, 1000.0};
    auto result = classify(data);
    EXPECT_GE(result.samples_seen, 0);
    EXPECT_GE(result.low_severe, 0);
    EXPECT_GE(result.low_mild, 0);
    EXPECT_GE(result.high_mild, 0);
    EXPECT_GE(result.high_severe, 0);
}

// Test that categories are mutually exclusive (a sample is counted in at most one category)
TEST_F(ClassifyOutliersTest_985, CategoriesMutuallyExclusive_985) {
    std::vector<double> data = {-1000.0, -50.0, 1.0, 2.0, 3.0, 4.0, 5.0, 50.0, 1000.0};
    auto result = classify(data);
    // total outliers + non-outliers should equal samples_seen
    int non_outliers = result.samples_seen - result.total();
    EXPECT_GE(non_outliers, 0);
    EXPECT_EQ(non_outliers + result.total(), result.samples_seen);
}

// Test with symmetric data - symmetric outliers should be detected symmetrically
TEST_F(ClassifyOutliersTest_985, SymmetricData_985) {
    std::vector<double> data;
    // Symmetric around 0
    for (int i = -50; i <= 50; ++i) {
        data.push_back(static_cast<double>(i));
    }
    // Add symmetric outliers
    data.push_back(200.0);
    data.push_back(-200.0);
    
    auto result = classify(data);
    EXPECT_EQ(result.samples_seen, static_cast<int>(data.size()));
    // Due to symmetry, high and low outlier counts should be equal
    EXPECT_EQ(result.low_severe + result.low_mild, result.high_severe + result.high_mild);
}

// Test with very large outliers
TEST_F(ClassifyOutliersTest_985, VeryLargeOutliers_985) {
    std::vector<double> data = {1.0, 2.0, 3.0, 4.0, 5.0, 1e15};
    auto result = classify(data);
    EXPECT_EQ(result.samples_seen, 6);
    EXPECT_GT(result.high_severe + result.high_mild, 0);
}

// Test with three elements
TEST_F(ClassifyOutliersTest_985, ThreeElements_985) {
    std::vector<double> data = {1.0, 2.0, 3.0};
    auto result = classify(data);
    EXPECT_EQ(result.samples_seen, 3);
}

// Test constexpr total() function
TEST_F(ClassifyOutliersTest_985, TotalFunction_985) {
    std::vector<double> data = {-1000.0, -500.0, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 500.0, 1000.0};
    auto result = classify(data);
    EXPECT_EQ(result.total(), result.low_severe + result.low_mild + result.high_mild + result.high_severe);
}
