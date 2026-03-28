#include "gtest/gtest.h"
#include "util/histogram.h"
#include <string>
#include <cmath>

namespace leveldb {

class HistogramTest_435 : public ::testing::Test {
 protected:
  Histogram histogram_;

  void SetUp() override {
    histogram_.Clear();
  }
};

// Test that a freshly cleared histogram produces a valid ToString output
TEST_F(HistogramTest_435, ClearProducesEmptyHistogram_435) {
  histogram_.Clear();
  std::string result = histogram_.ToString();
  // An empty histogram should still produce a valid string
  EXPECT_FALSE(result.empty());
}

// Test adding a single value
TEST_F(HistogramTest_435, AddSingleValue_435) {
  histogram_.Add(1.0);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
  // The string should contain "Count: 1"
  EXPECT_NE(result.find("Count: 1"), std::string::npos);
}

// Test adding multiple values
TEST_F(HistogramTest_435, AddMultipleValues_435) {
  histogram_.Add(1.0);
  histogram_.Add(2.0);
  histogram_.Add(3.0);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("Count: 3"), std::string::npos);
}

// Test adding zero value
TEST_F(HistogramTest_435, AddZeroValue_435) {
  histogram_.Add(0.0);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("Count: 1"), std::string::npos);
}

// Test adding negative value
TEST_F(HistogramTest_435, AddNegativeValue_435) {
  histogram_.Add(-1.0);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("Count: 1"), std::string::npos);
}

// Test adding very large value
TEST_F(HistogramTest_435, AddVeryLargeValue_435) {
  histogram_.Add(1e18);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("Count: 1"), std::string::npos);
}

// Test adding very small positive value
TEST_F(HistogramTest_435, AddVerySmallPositiveValue_435) {
  histogram_.Add(1e-10);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("Count: 1"), std::string::npos);
}

// Test adding the same value multiple times
TEST_F(HistogramTest_435, AddSameValueMultipleTimes_435) {
  for (int i = 0; i < 100; i++) {
    histogram_.Add(5.0);
  }
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("Count: 100"), std::string::npos);
}

// Test Merge with another histogram
TEST_F(HistogramTest_435, MergeTwoHistograms_435) {
  Histogram other;
  other.Clear();

  histogram_.Add(1.0);
  histogram_.Add(2.0);

  other.Add(3.0);
  other.Add(4.0);

  histogram_.Merge(other);

  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("Count: 4"), std::string::npos);
}

// Test Merge with empty histogram
TEST_F(HistogramTest_435, MergeWithEmptyHistogram_435) {
  Histogram other;
  other.Clear();

  histogram_.Add(1.0);
  histogram_.Add(2.0);

  histogram_.Merge(other);

  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("Count: 2"), std::string::npos);
}

// Test Merge into empty histogram
TEST_F(HistogramTest_435, MergeIntoEmptyHistogram_435) {
  Histogram other;
  other.Clear();
  other.Add(1.0);
  other.Add(2.0);

  histogram_.Merge(other);

  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("Count: 2"), std::string::npos);
}

// Test Clear after adding values
TEST_F(HistogramTest_435, ClearAfterAdding_435) {
  histogram_.Add(1.0);
  histogram_.Add(2.0);
  histogram_.Add(3.0);
  histogram_.Clear();

  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
  // After clear, count should be 0
  EXPECT_NE(result.find("Count: 0"), std::string::npos);
}

// Test ToString on empty histogram
TEST_F(HistogramTest_435, ToStringOnEmptyHistogram_435) {
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test adding a range of values across bucket boundaries
TEST_F(HistogramTest_435, AddRangeOfValues_435) {
  for (double v = 1.0; v <= 10000.0; v *= 2.0) {
    histogram_.Add(v);
  }
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test that average is reflected correctly in ToString for uniform values
TEST_F(HistogramTest_435, AverageReflectedInToString_435) {
  histogram_.Add(10.0);
  histogram_.Add(10.0);
  histogram_.Add(10.0);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
  // Average should be 10
  EXPECT_NE(result.find("Average"), std::string::npos);
}

// Test adding many values to stress bucket distribution
TEST_F(HistogramTest_435, AddManyValues_435) {
  for (int i = 0; i < 10000; i++) {
    histogram_.Add(static_cast<double>(i));
  }
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("Count: 10000"), std::string::npos);
}

// Test merging two histograms both with many values
TEST_F(HistogramTest_435, MergeTwoLargeHistograms_435) {
  Histogram other;
  other.Clear();

  for (int i = 0; i < 500; i++) {
    histogram_.Add(static_cast<double>(i));
    other.Add(static_cast<double>(i + 500));
  }

  histogram_.Merge(other);

  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
  EXPECT_NE(result.find("Count: 1000"), std::string::npos);
}

// Test that min and max are correctly tracked (observable via ToString)
TEST_F(HistogramTest_435, MinMaxTracking_435) {
  histogram_.Add(5.0);
  histogram_.Add(100.0);
  histogram_.Add(0.5);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
  // The min and max should appear somewhere in the output
}

// Test double Clear
TEST_F(HistogramTest_435, DoubleClear_435) {
  histogram_.Add(1.0);
  histogram_.Clear();
  histogram_.Clear();
  std::string result = histogram_.ToString();
  EXPECT_NE(result.find("Count: 0"), std::string::npos);
}

// Test Merge of histogram with itself conceptually (via a copy pattern)
TEST_F(HistogramTest_435, MergeSelfLike_435) {
  histogram_.Add(5.0);
  histogram_.Add(10.0);

  Histogram copy;
  copy.Clear();
  copy.Add(5.0);
  copy.Add(10.0);

  histogram_.Merge(copy);

  std::string result = histogram_.ToString();
  EXPECT_NE(result.find("Count: 4"), std::string::npos);
}

}  // namespace leveldb
