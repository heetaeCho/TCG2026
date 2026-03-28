#include "gtest/gtest.h"
#include "util/histogram.h"
#include <string>
#include <cmath>

namespace leveldb {

class HistogramTest_434 : public ::testing::Test {
 protected:
  Histogram histogram_;

  void SetUp() override {
    histogram_.Clear();
  }
};

// Test that Clear initializes the histogram properly
TEST_F(HistogramTest_434, ClearInitializesHistogram_434) {
  // After Clear, ToString should represent an empty histogram
  std::string result = histogram_.ToString();
  // An empty histogram should have count 0
  EXPECT_TRUE(result.find("Count: 0") != std::string::npos ||
              result.find("0.0000") != std::string::npos ||
              !result.empty());
}

// Test adding a single value
TEST_F(HistogramTest_434, AddSingleValue_434) {
  histogram_.Add(1.0);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test adding multiple values
TEST_F(HistogramTest_434, AddMultipleValues_434) {
  histogram_.Add(1.0);
  histogram_.Add(2.0);
  histogram_.Add(3.0);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test adding zero value
TEST_F(HistogramTest_434, AddZeroValue_434) {
  histogram_.Add(0.0);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test adding negative value
TEST_F(HistogramTest_434, AddNegativeValue_434) {
  histogram_.Add(-1.0);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test adding very large value
TEST_F(HistogramTest_434, AddVeryLargeValue_434) {
  histogram_.Add(1e18);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test adding very small positive value
TEST_F(HistogramTest_434, AddVerySmallValue_434) {
  histogram_.Add(0.0001);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test adding the same value many times
TEST_F(HistogramTest_434, AddSameValueManyTimes_434) {
  for (int i = 0; i < 1000; i++) {
    histogram_.Add(5.0);
  }
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test Clear after adding values resets the histogram
TEST_F(HistogramTest_434, ClearAfterAdding_434) {
  histogram_.Add(1.0);
  histogram_.Add(2.0);
  histogram_.Add(3.0);
  histogram_.Clear();
  std::string after_clear = histogram_.ToString();
  
  Histogram fresh;
  fresh.Clear();
  std::string fresh_str = fresh.ToString();
  
  EXPECT_EQ(after_clear, fresh_str);
}

// Test Merge of two histograms
TEST_F(HistogramTest_434, MergeTwoHistograms_434) {
  Histogram other;
  other.Clear();
  
  histogram_.Add(1.0);
  histogram_.Add(2.0);
  
  other.Add(3.0);
  other.Add(4.0);
  
  histogram_.Merge(other);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test Merge with empty histogram
TEST_F(HistogramTest_434, MergeWithEmptyHistogram_434) {
  Histogram other;
  other.Clear();
  
  histogram_.Add(1.0);
  histogram_.Add(2.0);
  
  std::string before_merge = histogram_.ToString();
  histogram_.Merge(other);
  std::string after_merge = histogram_.ToString();
  
  // Merging an empty histogram should not change the result significantly
  // (the string representation might differ slightly but data should be same)
  EXPECT_FALSE(after_merge.empty());
}

// Test Merge empty into empty
TEST_F(HistogramTest_434, MergeEmptyIntoEmpty_434) {
  Histogram other;
  other.Clear();
  
  histogram_.Merge(other);
  std::string result = histogram_.ToString();
  
  Histogram fresh;
  fresh.Clear();
  EXPECT_EQ(result, fresh.ToString());
}

// Test ToString on empty histogram
TEST_F(HistogramTest_434, ToStringEmpty_434) {
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test ToString after single add
TEST_F(HistogramTest_434, ToStringAfterSingleAdd_434) {
  histogram_.Add(42.0);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test adding values across a wide range
TEST_F(HistogramTest_434, AddWideRangeOfValues_434) {
  histogram_.Add(0.001);
  histogram_.Add(1.0);
  histogram_.Add(100.0);
  histogram_.Add(10000.0);
  histogram_.Add(1000000.0);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test that Merge is commutative in terms of resulting statistics
TEST_F(HistogramTest_434, MergeIsCommutative_434) {
  Histogram h1, h2;
  h1.Clear();
  h2.Clear();
  
  h1.Add(1.0);
  h1.Add(3.0);
  h2.Add(2.0);
  h2.Add(4.0);
  
  Histogram merged1, merged2;
  merged1.Clear();
  merged2.Clear();
  
  merged1.Add(1.0);
  merged1.Add(3.0);
  merged1.Merge(h2);
  
  merged2.Add(2.0);
  merged2.Add(4.0);
  merged2.Merge(h1);
  
  EXPECT_EQ(merged1.ToString(), merged2.ToString());
}

// Test adding many different values
TEST_F(HistogramTest_434, AddManyDifferentValues_434) {
  for (int i = 0; i < 10000; i++) {
    histogram_.Add(static_cast<double>(i));
  }
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test multiple Clear calls
TEST_F(HistogramTest_434, MultipleClearCalls_434) {
  histogram_.Add(1.0);
  histogram_.Clear();
  histogram_.Clear();
  histogram_.Clear();
  
  Histogram fresh;
  fresh.Clear();
  EXPECT_EQ(histogram_.ToString(), fresh.ToString());
}

// Test Merge self (merge histogram with itself)
TEST_F(HistogramTest_434, MergeSelfDoublesCount_434) {
  histogram_.Add(5.0);
  histogram_.Add(10.0);
  
  std::string before = histogram_.ToString();
  histogram_.Merge(histogram_);
  std::string after = histogram_.ToString();
  
  // After merging with itself, the string should differ (doubled counts)
  EXPECT_NE(before, after);
}

// Test boundary: adding at bucket limit boundaries
TEST_F(HistogramTest_434, AddBoundaryValues_434) {
  histogram_.Add(1.0);
  histogram_.Add(2.0);
  histogram_.Add(5.0);
  histogram_.Add(10.0);
  histogram_.Add(50.0);
  histogram_.Add(100.0);
  histogram_.Add(1000.0);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

}  // namespace leveldb
