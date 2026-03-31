#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/impl.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

#include <vector>

namespace YAML {
namespace detail {

class GetFunctionTest_663 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = shared_memory_holder(new memory_holder);
  }

  shared_memory_holder pMemory;
};

// Test that a negative key returns nullptr
TEST_F(GetFunctionTest_663, NegativeKeyReturnsNullptr_663) {
  std::vector<node*> sequence;
  node* result = get(sequence, -1, pMemory);
  EXPECT_EQ(result, nullptr);
}

// Test that a very negative key returns nullptr
TEST_F(GetFunctionTest_663, VeryNegativeKeyReturnsNullptr_663) {
  std::vector<node*> sequence;
  node* result = get(sequence, -100, pMemory);
  EXPECT_EQ(result, nullptr);
}

// Test that INT_MIN returns nullptr
TEST_F(GetFunctionTest_663, IntMinKeyReturnsNullptr_663) {
  std::vector<node*> sequence;
  node* result = get(sequence, std::numeric_limits<int>::min(), pMemory);
  EXPECT_EQ(result, nullptr);
}

// Test that key=0 on empty sequence returns a non-null node (created by get_idx)
TEST_F(GetFunctionTest_663, ZeroKeyOnEmptySequenceReturnsNode_663) {
  std::vector<node*> sequence;
  node* result = get(sequence, 0, pMemory);
  // get_idx with mutable vector should create/expand the sequence
  EXPECT_NE(result, nullptr);
}

// Test that key=0 returns the first element when sequence has elements
TEST_F(GetFunctionTest_663, ZeroKeyReturnsFirstElement_663) {
  std::vector<node*> sequence;
  // First call with key 0 to populate
  node* first = get(sequence, 0, pMemory);
  ASSERT_NE(first, nullptr);
  // Second call with same key should return same node
  node* result = get(sequence, 0, pMemory);
  EXPECT_EQ(result, first);
}

// Test that positive key expands sequence and returns valid node
TEST_F(GetFunctionTest_663, PositiveKeyReturnsNode_663) {
  std::vector<node*> sequence;
  node* result = get(sequence, 2, pMemory);
  EXPECT_NE(result, nullptr);
  // The sequence should have been expanded to at least size 3
  EXPECT_GE(sequence.size(), 3u);
}

// Test that accessing sequential indices returns different nodes
TEST_F(GetFunctionTest_663, DifferentIndicesReturnDifferentNodes_663) {
  std::vector<node*> sequence;
  node* node0 = get(sequence, 0, pMemory);
  node* node1 = get(sequence, 1, pMemory);
  node* node2 = get(sequence, 2, pMemory);
  EXPECT_NE(node0, nullptr);
  EXPECT_NE(node1, nullptr);
  EXPECT_NE(node2, nullptr);
  // Different indices should yield different node pointers
  EXPECT_NE(node0, node1);
  EXPECT_NE(node1, node2);
  EXPECT_NE(node0, node2);
}

// Test that repeated access to same index returns same node
TEST_F(GetFunctionTest_663, RepeatedAccessSameIndexReturnsSameNode_663) {
  std::vector<node*> sequence;
  node* first_call = get(sequence, 5, pMemory);
  node* second_call = get(sequence, 5, pMemory);
  EXPECT_EQ(first_call, second_call);
}

// Test minus one key returns nullptr even with populated sequence
TEST_F(GetFunctionTest_663, NegativeOneWithPopulatedSequenceReturnsNullptr_663) {
  std::vector<node*> sequence;
  get(sequence, 0, pMemory);
  get(sequence, 1, pMemory);
  ASSERT_FALSE(sequence.empty());
  node* result = get(sequence, -1, pMemory);
  EXPECT_EQ(result, nullptr);
}

}  // namespace detail
}  // namespace YAML
