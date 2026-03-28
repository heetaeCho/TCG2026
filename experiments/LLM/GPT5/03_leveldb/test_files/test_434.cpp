// File: util/histogram_clear_test.cc

#include "util/histogram.h"
#include <gtest/gtest.h>

namespace leveldb {

class HistogramClearTest_434 : public ::testing::Test {
protected:
  Histogram h_;

  // Helper: capture the canonical "empty" representation without relying on format.
  std::string EmptyRepr() const {
    Histogram fresh;
    return fresh.ToString();
  }
};

// [Normal] After adding values, Clear() should restore the initial (empty) state.
TEST_F(HistogramClearTest_434, ClearRestoresInitialState_434) {
  const std::string initial = EmptyRepr();

  // Sanity: fresh histogram matches its own empty representation.
  EXPECT_EQ(h_.ToString(), initial);

  // Mutate via public API only.
  h_.Add(1.0);
  h_.Add(5.0);
  h_.Add(10.0);

  // Observable state should differ after adds.
  EXPECT_NE(h_.ToString(), initial);

  // Clear and verify we’re back to the initial observable state.
  h_.Clear();
  EXPECT_EQ(h_.ToString(), initial);
}

// [Boundary] Clearing an already empty histogram keeps it unchanged.
TEST_F(HistogramClearTest_434, ClearOnEmptyIsNoop_434) {
  const std::string initial = h_.ToString();

  h_.Clear();
  EXPECT_EQ(h_.ToString(), initial);
}

// [Boundary/Idempotence] Calling Clear() multiple times yields the same observable state.
TEST_F(HistogramClearTest_434, ClearIsIdempotent_434) {
  // Make it non-empty first.
  h_.Add(3.14);
  h_.Add(2.71);
  ASSERT_NE(h_.ToString(), EmptyRepr());

  h_.Clear();
  const std::string after_first = h_.ToString();

  h_.Clear();
  const std::string after_second = h_.ToString();

  EXPECT_EQ(after_second, after_first);
  EXPECT_EQ(after_first, EmptyRepr());
}

// [Interaction] After Merge changes the histogram, Clear() still restores the empty state.
TEST_F(HistogramClearTest_434, ClearAfterMerge_434) {
  Histogram other;
  other.Add(100.0);
  other.Add(200.0);

  // Merge alters observable state.
  h_.Merge(other);
  EXPECT_NE(h_.ToString(), EmptyRepr());

  // Clear must reset to empty observable state.
  h_.Clear();
  EXPECT_EQ(h_.ToString(), EmptyRepr());
}

}  // namespace leveldb
