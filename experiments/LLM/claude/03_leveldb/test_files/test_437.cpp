#include "gtest/gtest.h"
#include "util/histogram.h"

#include <string>
#include <cmath>

namespace leveldb {

class HistogramTest_437 : public ::testing::Test {
 protected:
  Histogram histogram_;

  void SetUp() override {
    histogram_.Clear();
  }
};

// Test that a freshly constructed/cleared histogram has sensible ToString output
TEST_F(HistogramTest_437, EmptyHistogramToString_437) {
  std::string result = histogram_.ToString();
  // Count should be 0
  EXPECT_NE(result.find("Count: 0"), std::string::npos);
  // Should contain header lines
  EXPECT_NE(result.find("------------------------------------------------------"),
             std::string::npos);
}

// Test Clear resets the histogram
TEST_F(HistogramTest_437, ClearResetsHistogram_437) {
  histogram_.Add(1.0);
  histogram_.Add(2.0);
  histogram_.Clear();
  std::string result = histogram_.ToString();
  EXPECT_NE(result.find("Count: 0"), std::string::npos);
}

// Test adding a single value
TEST_F(HistogramTest_437, AddSingleValue_437) {
  histogram_.Add(42.0);
  std::string result = histogram_.ToString();
  EXPECT_NE(result.find("Count: 1"), std::string::npos);
  // Average should be 42
  EXPECT_NE(result.find("Average: 42.0000"), std::string::npos);
  // Min and Max should both be 42
  EXPECT_NE(result.find("Min: 42.0000"), std::string::npos);
  EXPECT_NE(result.find("Max: 42.0000"), std::string::npos);
}

// Test adding multiple identical values
TEST_F(HistogramTest_437, AddMultipleIdenticalValues_437) {
  for (int i = 0; i < 100; i++) {
    histogram_.Add(10.0);
  }
  std::string result = histogram_.ToString();
  EXPECT_NE(result.find("Count: 100"), std::string::npos);
  EXPECT_NE(result.find("Average: 10.0000"), std::string::npos);
  // StdDev should be 0 for identical values
  EXPECT_NE(result.find("StdDev: 0.00"), std::string::npos);
}

// Test adding two different values
TEST_F(HistogramTest_437, AddTwoDifferentValues_437) {
  histogram_.Add(10.0);
  histogram_.Add(20.0);
  std::string result = histogram_.ToString();
  EXPECT_NE(result.find("Count: 2"), std::string::npos);
  EXPECT_NE(result.find("Average: 15.0000"), std::string::npos);
  EXPECT_NE(result.find("Min: 10.0000"), std::string::npos);
  EXPECT_NE(result.find("Max: 20.0000"), std::string::npos);
}

// Test adding zero value
TEST_F(HistogramTest_437, AddZeroValue_437) {
  histogram_.Add(0.0);
  std::string result = histogram_.ToString();
  EXPECT_NE(result.find("Count: 1"), std::string::npos);
  EXPECT_NE(result.find("Average: 0.0000"), std::string::npos);
}

// Test adding negative values
TEST_F(HistogramTest_437, AddNegativeValue_437) {
  histogram_.Add(-5.0);
  std::string result = histogram_.ToString();
  EXPECT_NE(result.find("Count: 1"), std::string::npos);
}

// Test adding a very large value
TEST_F(HistogramTest_437, AddVeryLargeValue_437) {
  histogram_.Add(1e18);
  std::string result = histogram_.ToString();
  EXPECT_NE(result.find("Count: 1"), std::string::npos);
}

// Test adding a very small positive value
TEST_F(HistogramTest_437, AddVerySmallPositiveValue_437) {
  histogram_.Add(0.001);
  std::string result = histogram_.ToString();
  EXPECT_NE(result.find("Count: 1"), std::string::npos);
}

// Test Merge with another histogram
TEST_F(HistogramTest_437, MergeTwoHistograms_437) {
  Histogram other;
  other.Clear();

  histogram_.Add(10.0);
  histogram_.Add(20.0);

  other.Add(30.0);
  other.Add(40.0);

  histogram_.Merge(other);

  std::string result = histogram_.ToString();
  EXPECT_NE(result.find("Count: 4"), std::string::npos);
  // Average should be (10+20+30+40)/4 = 25
  EXPECT_NE(result.find("Average: 25.0000"), std::string::npos);
  EXPECT_NE(result.find("Min: 10.0000"), std::string::npos);
  EXPECT_NE(result.find("Max: 40.0000"), std::string::npos);
}

// Test Merge with empty histogram
TEST_F(HistogramTest_437, MergeEmptyHistogram_437) {
  Histogram other;
  other.Clear();

  histogram_.Add(5.0);
  histogram_.Merge(other);

  std::string result = histogram_.ToString();
  EXPECT_NE(result.find("Count: 1"), std::string::npos);
  EXPECT_NE(result.find("Average: 5.0000"), std::string::npos);
}

// Test Merge into empty histogram
TEST_F(HistogramTest_437, MergeIntoEmptyHistogram_437) {
  Histogram other;
  other.Clear();
  other.Add(7.0);

  histogram_.Merge(other);

  std::string result = histogram_.ToString();
  EXPECT_NE(result.find("Count: 1"), std::string::npos);
  EXPECT_NE(result.find("Average: 7.0000"), std::string::npos);
}

// Test that ToString contains bucket information when values are added
TEST_F(HistogramTest_437, ToStringContainsBucketLines_437) {
  for (int i = 0; i < 50; i++) {
    histogram_.Add(static_cast<double>(i));
  }
  std::string result = histogram_.ToString();
  // Should have bucket lines with '#' marks
  EXPECT_NE(result.find("#"), std::string::npos);
  // Should have percentage signs
  EXPECT_NE(result.find("%"), std::string::npos);
}

// Test with a wide range of values
TEST_F(HistogramTest_437, WideRangeOfValues_437) {
  histogram_.Add(1.0);
  histogram_.Add(100.0);
  histogram_.Add(10000.0);
  histogram_.Add(1000000.0);

  std::string result = histogram_.ToString();
  EXPECT_NE(result.find("Count: 4"), std::string::npos);
  EXPECT_NE(result.find("Min: 1.0000"), std::string::npos);
  EXPECT_NE(result.find("Max: 1000000.0000"), std::string::npos);
}

// Test Median appears in ToString
TEST_F(HistogramTest_437, MedianAppearsInToString_437) {
  histogram_.Add(1.0);
  histogram_.Add(2.0);
  histogram_.Add(3.0);
  std::string result = histogram_.ToString();
  EXPECT_NE(result.find("Median:"), std::string::npos);
}

// Test standard deviation with varying data
TEST_F(HistogramTest_437, StandardDeviationNonZero_437) {
  histogram_.Add(1.0);
  histogram_.Add(100.0);
  std::string result = histogram_.ToString();
  // StdDev should not be 0
  // We can't check exact value, but it should be present
  EXPECT_NE(result.find("StdDev:"), std::string::npos);
  // StdDev should not be 0.00 since values differ significantly
  // The stddev of {1, 100} is ~49.5
  EXPECT_EQ(result.find("StdDev: 0.00"), std::string::npos);
}

// Test that calling Clear after Merge gives empty histogram
TEST_F(HistogramTest_437, ClearAfterMerge_437) {
  Histogram other;
  other.Clear();
  other.Add(10.0);
  other.Add(20.0);

  histogram_.Add(5.0);
  histogram_.Merge(other);
  histogram_.Clear();

  std::string result = histogram_.ToString();
  EXPECT_NE(result.find("Count: 0"), std::string::npos);
}

// Test adding many values
TEST_F(HistogramTest_437, AddManyValues_437) {
  for (int i = 0; i < 10000; i++) {
    histogram_.Add(static_cast<double>(i));
  }
  std::string result = histogram_.ToString();
  EXPECT_NE(result.find("Count: 10000"), std::string::npos);
}

// Test ToString output is non-empty even for empty histogram
TEST_F(HistogramTest_437, ToStringNonEmptyForEmptyHistogram_437) {
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test that ToString contains the separator line
TEST_F(HistogramTest_437, ToStringContainsSeparatorLine_437) {
  histogram_.Add(1.0);
  std::string result = histogram_.ToString();
  EXPECT_NE(result.find("------------------------------------------------------"),
             std::string::npos);
}

// Test cumulative percentage reaches 100% for last bucket entry
TEST_F(HistogramTest_437, CumulativePercentage_437) {
  histogram_.Add(1.0);
  std::string result = histogram_.ToString();
  EXPECT_NE(result.find("100.000%"), std::string::npos);
}

// Test merging histogram with itself via copy
TEST_F(HistogramTest_437, MergeWithCopy_437) {
  histogram_.Add(5.0);
  histogram_.Add(15.0);
  
  Histogram copy;
  copy.Clear();
  copy.Add(5.0);
  copy.Add(15.0);
  
  histogram_.Merge(copy);
  
  std::string result = histogram_.ToString();
  EXPECT_NE(result.find("Count: 4"), std::string::npos);
  EXPECT_NE(result.find("Average: 10.0000"), std::string::npos);
}

}  // namespace leveldb
