// fanout_test.cc
#include <gtest/gtest.h>
#include <cstdint>
#include <vector>
#include <algorithm>

//
// Minimal shims to satisfy the helper's collaborators strictly through the public surface
//
namespace re2 {

// -------- Minimal SparseArray used only by the helper under test --------
template <typename Value>
class SparseArray {
public:
  struct IndexValue {
    int index;
    Value v;
    Value value() const { return v; }
  };

  using iterator = typename std::vector<IndexValue>::iterator;
  using const_iterator = typename std::vector<IndexValue>::const_iterator;

  explicit SparseArray(int /*max_size*/) {}  // max_size not needed by the helper
  iterator begin() { return data_.begin(); }
  iterator end() { return data_.end(); }

  // Only API the helper needs indirectly via Prog::Fanout
  iterator set(int i, const Value& v) {
    data_.push_back({i, v});
    return std::prev(data_.end());
  }

private:
  std::vector<IndexValue> data_;
};

// -------- External dependency used by the helper: provide a simple version --------
inline int FindMSBSet(uint32_t x) {
  if (x == 0) return -1;
  int pos = -1;
  while (x) { x >>= 1; ++pos; }
  return pos;
}

// -------- Test double for Prog (external collaborator) --------
class Prog {
public:
  // We only need to control size() and Fanout()
  explicit Prog(const std::vector<int>& values) : values_(values) {}

  int size() { return static_cast<int>(values_.size()); }

  // This is the method the helper calls; we simply populate the provided SparseArray.
  void Fanout(SparseArray<int>* fanout) {
    for (int i = 0; i < static_cast<int>(values_.size()); ++i) {
      // The helper skips zero values during counting, but they are still "present".
      fanout->set(i, values_[i]);
    }
  }

private:
  std::vector<int> values_;
};

}  // namespace re2

// Include the .cc that defines the static helper under test.
// This compiles the helper into this TU so the tests can call it.
#include "TestProjects/re2/re2/re2.cc"

using namespace re2;

//
// Tests
//

// Boundary: empty prog -> no entries, histogram nullptr
TEST(FanoutTest_247, EmptyProg_NoHistogram_ReturnsMinusOne_247) {
  Prog prog(/*values=*/{});
  int result = Fanout(&prog, /*histogram=*/nullptr);
  EXPECT_EQ(result, -1);
}

// Boundary: empty prog -> histogram provided should remain empty
TEST(FanoutTest_247, EmptyProg_WithHistogram_AssignsEmptyAndReturnsMinusOne_247) {
  Prog prog(/*values=*/{});
  std::vector<int> hist;
  int result = Fanout(&prog, &hist);
  EXPECT_EQ(result, -1);
  EXPECT_TRUE(hist.empty());
}

// Normal: single power-of-two value (1 -> bucket 0)
TEST(FanoutTest_247, SinglePowerOfTwo_GoesToExactMSBBucket_247) {
  Prog prog({1});
  std::vector<int> hist;
  int result = Fanout(&prog, &hist);
  // msb(1)=0, power-of-two => bucket 0, size=1 => return size-1 = 0
  ASSERT_EQ(result, 0);
  ASSERT_EQ(hist.size(), 1u);
  EXPECT_EQ(hist[0], 1);
}

// Normal: single power-of-two value (8 -> bucket 3)
TEST(FanoutTest_247, SinglePowerOfTwo_EightBucketIsThree_247) {
  Prog prog({8});
  std::vector<int> hist;
  int result = Fanout(&prog, &hist);
  // msb(8)=3, power-of-two => bucket 3, size=4 => return 3
  ASSERT_EQ(result, 3);
  ASSERT_EQ(hist.size(), 4u);
  EXPECT_EQ(hist[0], 0);
  EXPECT_EQ(hist[1], 0);
  EXPECT_EQ(hist[2], 0);
  EXPECT_EQ(hist[3], 1);
}

// Normal: single non-power-of-two (3 -> msb=1, bump to bucket 2)
TEST(FanoutTest_247, SingleNonPowerOfTwo_BumpsToNextBucket_247) {
  Prog prog({3});
  std::vector<int> hist;
  int result = Fanout(&prog, &hist);
  // msb(3)=1, non-power => bucket 2, size=3 => return 2
  ASSERT_EQ(result, 2);
  ASSERT_EQ(hist.size(), 3u);
  EXPECT_EQ(hist[0], 0);
  EXPECT_EQ(hist[1], 0);
  EXPECT_EQ(hist[2], 1);
}

// Normal: multiple mixed values, including zeros that should be ignored
TEST(FanoutTest_247, MixedValues_AccumulatesBucketsAndSkipsZeros_247) {
  // Values: 0 (ignored), 1 (b0), 3 (b2), 4 (b2), 5 (b3), 8 (b3), 15 (b4)
  Prog prog({0, 1, 3, 4, 5, 8, 15});
  std::vector<int> hist;
  int result = Fanout(&prog, &hist);

  // Expected histogram:
  // b0:1, b1:0, b2:2 (3 & 4), b3:2 (5 & 8), b4:1 (15)
  ASSERT_EQ(result, 4);
  ASSERT_EQ(hist.size(), 5u);
  EXPECT_EQ(hist[0], 1);
  EXPECT_EQ(hist[1], 0);
  EXPECT_EQ(hist[2], 2);
  EXPECT_EQ(hist[3], 2);
  EXPECT_EQ(hist[4], 1);
}

// Error-ish: histogram pointer is null, but non-empty data should still compute and return
TEST(FanoutTest_247, NullHistogram_ComputesReturnValueButDoesNotWrite_247) {
  Prog prog({1, 2, 3}); // buckets: 0,1,2 -> size=3 -> return 2
  int result = Fanout(&prog, nullptr);
  EXPECT_EQ(result, 2);
}

