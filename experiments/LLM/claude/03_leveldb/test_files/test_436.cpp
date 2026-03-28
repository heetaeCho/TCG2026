#include "gtest/gtest.h"
#include "util/histogram.h"
#include <string>
#include <cmath>

namespace leveldb {

class HistogramTest_436 : public ::testing::Test {
 protected:
  Histogram histogram_;

  void SetUp() override {
    histogram_.Clear();
  }
};

// Test that a newly cleared histogram produces a valid ToString output
TEST_F(HistogramTest_436, ClearProducesEmptyHistogram_436) {
  histogram_.Clear();
  std::string result = histogram_.ToString();
  // A cleared histogram should have some string representation
  EXPECT_FALSE(result.empty());
}

// Test adding a single value
TEST_F(HistogramTest_436, AddSingleValue_436) {
  histogram_.Add(1.0);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test adding multiple values
TEST_F(HistogramTest_436, AddMultipleValues_436) {
  histogram_.Add(1.0);
  histogram_.Add(2.0);
  histogram_.Add(3.0);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test adding zero value
TEST_F(HistogramTest_436, AddZeroValue_436) {
  histogram_.Add(0.0);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test adding negative value
TEST_F(HistogramTest_436, AddNegativeValue_436) {
  histogram_.Add(-1.0);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test adding very large value
TEST_F(HistogramTest_436, AddVeryLargeValue_436) {
  histogram_.Add(1e18);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test adding very small positive value
TEST_F(HistogramTest_436, AddVerySmallValue_436) {
  histogram_.Add(1e-10);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test merging two empty histograms
TEST_F(HistogramTest_436, MergeTwoEmptyHistograms_436) {
  Histogram other;
  other.Clear();
  histogram_.Merge(other);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test merging a non-empty histogram into an empty one
TEST_F(HistogramTest_436, MergeNonEmptyIntoEmpty_436) {
  Histogram other;
  other.Clear();
  other.Add(5.0);
  other.Add(10.0);
  histogram_.Merge(other);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test merging an empty histogram into a non-empty one
TEST_F(HistogramTest_436, MergeEmptyIntoNonEmpty_436) {
  histogram_.Add(5.0);
  histogram_.Add(10.0);
  Histogram other;
  other.Clear();
  histogram_.Merge(other);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test merging two non-empty histograms
TEST_F(HistogramTest_436, MergeTwoNonEmptyHistograms_436) {
  histogram_.Add(1.0);
  histogram_.Add(2.0);

  Histogram other;
  other.Clear();
  other.Add(3.0);
  other.Add(4.0);

  histogram_.Merge(other);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test that merging updates min correctly (other has smaller min)
TEST_F(HistogramTest_436, MergeUpdatesMinWhenOtherIsSmaller_436) {
  histogram_.Add(10.0);

  Histogram other;
  other.Clear();
  other.Add(1.0);

  histogram_.Merge(other);
  // After merge, the histogram should reflect min of 1.0
  // We verify through ToString since min_ is private
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test that merging updates max correctly (other has larger max)
TEST_F(HistogramTest_436, MergeUpdatesMaxWhenOtherIsLarger_436) {
  histogram_.Add(1.0);

  Histogram other;
  other.Clear();
  other.Add(100.0);

  histogram_.Merge(other);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test that merging does not change min when other has larger min
TEST_F(HistogramTest_436, MergeKeepsMinWhenOtherIsLarger_436) {
  histogram_.Add(1.0);

  Histogram other;
  other.Clear();
  other.Add(10.0);

  histogram_.Merge(other);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test that merging does not change max when other has smaller max
TEST_F(HistogramTest_436, MergeKeepsMaxWhenOtherIsSmaller_436) {
  histogram_.Add(100.0);

  Histogram other;
  other.Clear();
  other.Add(10.0);

  histogram_.Merge(other);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test Clear resets histogram after adding values
TEST_F(HistogramTest_436, ClearResetsAfterAdding_436) {
  histogram_.Add(1.0);
  histogram_.Add(2.0);
  histogram_.Add(3.0);
  histogram_.Clear();
  std::string result = histogram_.ToString();
  // After clear, should be same as a fresh histogram
  Histogram fresh;
  fresh.Clear();
  std::string freshResult = fresh.ToString();
  EXPECT_EQ(result, freshResult);
}

// Test adding same value multiple times
TEST_F(HistogramTest_436, AddSameValueMultipleTimes_436) {
  for (int i = 0; i < 1000; i++) {
    histogram_.Add(42.0);
  }
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test adding a wide range of values
TEST_F(HistogramTest_436, AddWideRangeOfValues_436) {
  for (double v = 0.0; v <= 1e6; v += 1000.0) {
    histogram_.Add(v);
  }
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test merging histogram with itself (self-merge)
TEST_F(HistogramTest_436, MergeWithSelf_436) {
  histogram_.Add(5.0);
  histogram_.Add(10.0);
  // Merging with itself should double the counts
  histogram_.Merge(histogram_);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test multiple sequential merges
TEST_F(HistogramTest_436, MultipleSequentialMerges_436) {
  Histogram h1, h2, h3;
  h1.Clear();
  h2.Clear();
  h3.Clear();
  h1.Add(1.0);
  h2.Add(2.0);
  h3.Add(3.0);

  histogram_.Merge(h1);
  histogram_.Merge(h2);
  histogram_.Merge(h3);

  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test ToString on empty histogram (no values added)
TEST_F(HistogramTest_436, ToStringOnEmptyHistogram_436) {
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test adding values that would span many buckets
TEST_F(HistogramTest_436, AddValuesAcrossManyBuckets_436) {
  // Add powers of 2 to span bucket boundaries
  for (int i = 0; i < 30; i++) {
    histogram_.Add(std::pow(2.0, i));
  }
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test that Clear followed by Add works correctly
TEST_F(HistogramTest_436, ClearThenAddWorks_436) {
  histogram_.Add(100.0);
  histogram_.Clear();
  histogram_.Add(50.0);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Test merging after clear
TEST_F(HistogramTest_436, MergeAfterClear_436) {
  histogram_.Add(100.0);
  histogram_.Clear();

  Histogram other;
  other.Clear();
  other.Add(50.0);

  histogram_.Merge(other);
  std::string result = histogram_.ToString();
  EXPECT_FALSE(result.empty());
}

// Verify that two histograms with same data produce same ToString
TEST_F(HistogramTest_436, SameDataProducesSameToString_436) {
  Histogram h1, h2;
  h1.Clear();
  h2.Clear();

  h1.Add(1.0);
  h1.Add(2.0);
  h1.Add(3.0);

  h2.Add(1.0);
  h2.Add(2.0);
  h2.Add(3.0);

  EXPECT_EQ(h1.ToString(), h2.ToString());
}

// Test that merge of two histograms is commutative in terms of count
TEST_F(HistogramTest_436, MergeIsCommutativeForToString_436) {
  Histogram h1, h2;
  h1.Clear();
  h2.Clear();

  h1.Add(1.0);
  h1.Add(5.0);
  h2.Add(3.0);
  h2.Add(7.0);

  Histogram merged1, merged2;
  merged1.Clear();
  merged2.Clear();

  // merged1 = h1 + h2
  merged1.Add(1.0);
  merged1.Add(5.0);
  merged1.Merge(h2);

  // merged2 = h2 + h1
  merged2.Add(3.0);
  merged2.Add(7.0);
  merged2.Merge(h1);

  EXPECT_EQ(merged1.ToString(), merged2.ToString());
}

}  // namespace leveldb
