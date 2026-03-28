#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node/detail/impl.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

#include <vector>

namespace {

class YamlDetailGetTest_662 : public ::testing::Test {
 protected:
  void SetUp() override {
    pMemory = YAML::detail::shared_memory_holder(new YAML::detail::memory_holder);
  }

  YAML::detail::shared_memory_holder pMemory;
};

// Test that a negative key returns nullptr
TEST_F(YamlDetailGetTest_662, NegativeKeyReturnsNullptr_662) {
  std::vector<YAML::detail::node*> sequence;
  // Add some nodes to the sequence
  YAML::detail::node& n1 = pMemory->create_node();
  sequence.push_back(&n1);

  YAML::detail::node* result = YAML::detail::get(sequence, -1, pMemory);
  EXPECT_EQ(result, nullptr);
}

// Test that a very negative key returns nullptr
TEST_F(YamlDetailGetTest_662, VeryNegativeKeyReturnsNullptr_662) {
  std::vector<YAML::detail::node*> sequence;
  YAML::detail::node& n1 = pMemory->create_node();
  sequence.push_back(&n1);

  YAML::detail::node* result = YAML::detail::get(sequence, -100, pMemory);
  EXPECT_EQ(result, nullptr);
}

// Test that key 0 on an empty sequence returns nullptr (out of bounds)
TEST_F(YamlDetailGetTest_662, ZeroKeyOnEmptySequenceReturnsNullptr_662) {
  std::vector<YAML::detail::node*> sequence;

  YAML::detail::node* result = YAML::detail::get(sequence, 0, pMemory);
  // Key 0 is >= 0, so it delegates to get_idx. On empty sequence, expect nullptr
  EXPECT_EQ(result, nullptr);
}

// Test that key 0 on a sequence with one element returns that element
TEST_F(YamlDetailGetTest_662, ZeroKeyOnSingleElementSequence_662) {
  std::vector<YAML::detail::node*> sequence;
  YAML::detail::node& n1 = pMemory->create_node();
  sequence.push_back(&n1);

  YAML::detail::node* result = YAML::detail::get(sequence, 0, pMemory);
  EXPECT_EQ(result, &n1);
}

// Test that key 1 on a sequence with two elements returns the second element
TEST_F(YamlDetailGetTest_662, ValidIndexReturnsCorrectNode_662) {
  std::vector<YAML::detail::node*> sequence;
  YAML::detail::node& n1 = pMemory->create_node();
  YAML::detail::node& n2 = pMemory->create_node();
  sequence.push_back(&n1);
  sequence.push_back(&n2);

  YAML::detail::node* result = YAML::detail::get(sequence, 1, pMemory);
  EXPECT_EQ(result, &n2);
}

// Test that an out-of-bounds positive key returns nullptr or allocates
TEST_F(YamlDetailGetTest_662, OutOfBoundsPositiveKey_662) {
  std::vector<YAML::detail::node*> sequence;
  YAML::detail::node& n1 = pMemory->create_node();
  sequence.push_back(&n1);

  // Key 5 is out of bounds for a sequence of size 1
  // The const version of get_idx should return nullptr for out-of-bounds
  const std::vector<YAML::detail::node*>& constSeq = sequence;
  YAML::detail::node* result = YAML::detail::get(constSeq, 5, pMemory);
  EXPECT_EQ(result, nullptr);
}

// Test negative key with empty sequence still returns nullptr
TEST_F(YamlDetailGetTest_662, NegativeKeyOnEmptySequence_662) {
  std::vector<YAML::detail::node*> sequence;

  YAML::detail::node* result = YAML::detail::get(sequence, -1, pMemory);
  EXPECT_EQ(result, nullptr);
}

// Test boundary: key == -1 (just below zero)
TEST_F(YamlDetailGetTest_662, BoundaryMinusOne_662) {
  std::vector<YAML::detail::node*> sequence;
  YAML::detail::node& n1 = pMemory->create_node();
  sequence.push_back(&n1);

  YAML::detail::node* result = YAML::detail::get(sequence, -1, pMemory);
  EXPECT_EQ(result, nullptr);
}

// Test with multiple nodes and accessing last valid index
TEST_F(YamlDetailGetTest_662, AccessLastValidIndex_662) {
  std::vector<YAML::detail::node*> sequence;
  YAML::detail::node& n1 = pMemory->create_node();
  YAML::detail::node& n2 = pMemory->create_node();
  YAML::detail::node& n3 = pMemory->create_node();
  sequence.push_back(&n1);
  sequence.push_back(&n2);
  sequence.push_back(&n3);

  YAML::detail::node* result = YAML::detail::get(sequence, 2, pMemory);
  EXPECT_EQ(result, &n3);
}

// Test with key == 0 (boundary between negative and non-negative)
TEST_F(YamlDetailGetTest_662, BoundaryZeroKeyWithNodes_662) {
  std::vector<YAML::detail::node*> sequence;
  YAML::detail::node& n1 = pMemory->create_node();
  YAML::detail::node& n2 = pMemory->create_node();
  sequence.push_back(&n1);
  sequence.push_back(&n2);

  YAML::detail::node* result = YAML::detail::get(sequence, 0, pMemory);
  EXPECT_EQ(result, &n1);
}

}  // namespace
