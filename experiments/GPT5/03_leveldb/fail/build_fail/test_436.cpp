// File: util/histogram_merge_test_436.cc

#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "util/histogram.h"

namespace {

using leveldb::Histogram;

static Histogram BuildHist(const std::vector<double>& vals) {
  Histogram h;
  for (double v : vals) h.Add(v);
  return h;
}

// Helper: merge(A, B) and compare ToString with histogram built from A∪B (multiset).
static void ExpectMergeMatchesCombined(const std::vector<double>& a,
                                       const std::vector<double>& b) {
  Histogram A = BuildHist(a);
  Histogram B = BuildHist(b);

  Histogram merged = A;   // copy
  merged.Merge(B);

  Histogram combined;
  for (double v : a) combined.Add(v);
  for (double v : b) combined.Add(v);

  EXPECT_EQ(merged.ToString(), combined.ToString());
}

class HistogramMergeTest_436 : public ::testing::Test {};

TEST_F(HistogramMergeTest_436, MergeEmptyWithEmpty_436) {
  ExpectMergeMatchesCombined({}, {});
}

TEST_F(HistogramMergeTest_436, MergeNonEmptyWithEmpty_436) {
  ExpectMergeMatchesCombined({1.0, 2.5, 3.0}, {});
}

TEST_F(HistogramMergeTest_436, MergeEmptyWithNonEmpty_436) {
  ExpectMergeMatchesCombined({}, {-5.0, 0.0, 7.25});
}

TEST_F(HistogramMergeTest_436, MergeGeneralEqualityToCombined_436) {
  // Normal operation: mixed distribution
  std::vector<double> a = {1, 2, 2, 3, 10.5};
  std::vector<double> b = {0, 2, 4.5, 4.5, 100};
  ExpectMergeMatchesCombined(a, b);
}

TEST_F(HistogramMergeTest_436, MergeOrderIndependence_436) {
  // Boundary/normal: order should not affect observable result
  std::vector<double> a = {3, 3, 3, 7};
  std::vector<double> b = {-2, 0, 5, 9};

  Histogram A = BuildHist(a);
  Histogram B = BuildHist(b);

  Histogram AB = A;
  AB.Merge(B);

  Histogram BA = B;
  BA.Merge(A);

  EXPECT_EQ(AB.ToString(), BA.ToString());
}

TEST_F(HistogramMergeTest_436, MergeAssociativity_436) {
  // (A + B) + C == A + (B + C) in observable behavior
  std::vector<double> a = {1, 8};
  std::vector<double> b = {2, 2, 3};
  std::vector<double> c = {-10, 0, 0.5};

  Histogram A = BuildHist(a);
  Histogram B = BuildHist(b);
  Histogram C = BuildHist(c);

  Histogram left = A;
  left.Merge(B);
  left.Merge(C);

  Histogram right = A;
  Histogram tmp = B;
  tmp.Merge(C);
  right.Merge(tmp);

  EXPECT_EQ(left.ToString(), right.ToString());
}

TEST_F(HistogramMergeTest_436, MergeSelfEquivalentToDuplicatedAdds_436) {
  // Edge case: merging a histogram into itself should be equivalent to
  // adding the same values again (observable via ToString()).
  std::vector<double> vals = {-3.14, -3.14, 0.0, 1.5, 2.75, 1000.0};

  Histogram h = BuildHist(vals);
  Histogram self = h;      // snapshot before self-merge
  h.Merge(h);              // self-merge

  Histogram duplicated;
  for (double v : vals) duplicated.Add(v);
  for (double v : vals) duplicated.Add(v);

  EXPECT_EQ(h.ToString(), duplicated.ToString());

  // Also ensure self-merge does not equal the single-shot snapshot
  // (observable change occurred).
  EXPECT_NE(h.ToString(), self.ToString());
}

TEST_F(HistogramMergeTest_436, MergeHandlesNegativeZeroLarge_436) {
  // Boundary values, including negative, zeros, very large/small magnitudes
  std::vector<double> a = {-1e12, -1e3, -1.0, -0.0};
  std::vector<double> b = {0.0, 1.0, 1e3, 1e12};

  ExpectMergeMatchesCombined(a, b);
}

}  // namespace
