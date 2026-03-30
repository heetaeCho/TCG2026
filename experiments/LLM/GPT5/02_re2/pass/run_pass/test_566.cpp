// File: onepass_index_to_node_test_566.cc
#include <gtest/gtest.h>
#include <cstdint>
#include <vector>

// Forward declare the minimal symbols we need so we can include the real impl.
namespace re2 {
struct OneState;  // We never access its internals.
}

// Include the implementation so we test the real function (no re-implementation).
// Adjust the include path if your project layout differs.
#include "re2/onepass.cc"

namespace {

using re2::IndexToNode;
using re2::OneState;

class IndexToNodeTest_566 : public ::testing::Test {
protected:
  // Helper: convert returned OneState* back to raw byte pointer for comparison.
  static uint8_t* AsBytePtr(OneState* p) {
    return reinterpret_cast<uint8_t*>(p);
  }
};

// [Normal] nodeindex = 0 → should return base address.
TEST_F(IndexToNodeTest_566, ReturnsBasePointer_566) {
  std::vector<uint8_t> buf(64, 0xAA);
  uint8_t* base = buf.data();
  const int kStateSize = 8;
  const int kIndex = 0;

  OneState* out = IndexToNode(base, kStateSize, kIndex);
  EXPECT_EQ(AsBytePtr(out), base);
}

// [Normal] Middle index with typical aligned state size.
TEST_F(IndexToNodeTest_566, ComputesOffsetForMiddleIndex_566) {
  std::vector<uint8_t> buf(128, 0);
  uint8_t* base = buf.data();
  const int kStateSize = 16;
  const int kIndex = 3; // offset = 48

  OneState* out = IndexToNode(base, kStateSize, kIndex);
  EXPECT_EQ(AsBytePtr(out), base + kStateSize * kIndex);
}

// [Boundary] Last valid index within the allocated buffer.
TEST_F(IndexToNodeTest_566, ComputesOffsetForLastIndex_566) {
  const int kStateSize = 24;
  const int kCount = 5;  // total bytes = 120
  std::vector<uint8_t> buf(kStateSize * kCount, 0);
  uint8_t* base = buf.data();
  const int kIndex = kCount - 1; // 4 → offset = 96

  OneState* out = IndexToNode(base, kStateSize, kIndex);
  EXPECT_EQ(AsBytePtr(out), base + kStateSize * kIndex);
}

// [Boundary] Zero state size → pointer should not advance regardless of index.
TEST_F(IndexToNodeTest_566, ZeroStateSizeDoesNotAdvance_566) {
  std::vector<uint8_t> buf(16, 0);
  uint8_t* base = buf.data();
  const int kStateSize = 0;

  // Try a few indices; result should always be the base.
  for (int idx : {0, 1, 10}) {
    OneState* out = IndexToNode(base, kStateSize, idx);
    EXPECT_EQ(AsBytePtr(out), base) << "idx=" << idx;
  }
}

// [Normal] Non-power-of-two state size and larger index.
TEST_F(IndexToNodeTest_566, WorksWithNonPowerOfTwoStateSize_566) {
  const int kStateSize = 7;
  const int kIndex = 10; // offset = 70
  std::vector<uint8_t> buf(kStateSize * (kIndex + 1), 0);
  uint8_t* base = buf.data();

  OneState* out = IndexToNode(base, kStateSize, kIndex);
  EXPECT_EQ(AsBytePtr(out), base + kStateSize * kIndex);
}

} // namespace
