// File: ./TestProjects/yaml-cpp/test/memory_test_626.cpp

#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/memory.h"

namespace {

using YAML::detail::memory;

// Helper: create N nodes in a memory instance (observable via size()).
static void CreateN(memory& m, size_t n) {
  for (size_t i = 0; i < n; ++i) {
    (void)m.create_node();
  }
}

class MemoryTest_626 : public ::testing::Test {};

TEST_F(MemoryTest_626, DefaultConstructedHasZeroSize_626) {
  memory m;
  EXPECT_EQ(m.size(), 0u);
}

TEST_F(MemoryTest_626, CreateNodeIncreasesSizeByOnePerCall_626) {
  memory m;

  const size_t s0 = m.size();
  (void)m.create_node();
  const size_t s1 = m.size();
  EXPECT_EQ(s1, s0 + 1);

  (void)m.create_node();
  const size_t s2 = m.size();
  EXPECT_EQ(s2, s1 + 1);

  (void)m.create_node();
  const size_t s3 = m.size();
  EXPECT_EQ(s3, s2 + 1);
}

TEST_F(MemoryTest_626, MergeIntoEmptyAddsAllRhsNodesAndDoesNotChangeRhs_626) {
  memory lhs;
  memory rhs;

  CreateN(rhs, 5);
  ASSERT_EQ(lhs.size(), 0u);
  const size_t rhs_before = rhs.size();

  lhs.merge(rhs);

  EXPECT_EQ(rhs.size(), rhs_before);      // rhs observable state unchanged
  EXPECT_EQ(lhs.size(), rhs_before);      // lhs received rhs nodes
}

TEST_F(MemoryTest_626, MergeIntoNonEmptyIncreasesSizeByRhsSizeAndDoesNotChangeRhs_626) {
  memory lhs;
  memory rhs;

  CreateN(lhs, 3);
  CreateN(rhs, 4);

  const size_t lhs_before = lhs.size();
  const size_t rhs_before = rhs.size();

  lhs.merge(rhs);

  EXPECT_EQ(rhs.size(), rhs_before);                 // rhs unchanged
  EXPECT_EQ(lhs.size(), lhs_before + rhs_before);    // lhs grows by rhs size
}

TEST_F(MemoryTest_626, MergeWithEmptyRhsDoesNotChangeLhs_626) {
  memory lhs;
  memory rhs;

  CreateN(lhs, 7);
  ASSERT_EQ(rhs.size(), 0u);

  const size_t lhs_before = lhs.size();
  lhs.merge(rhs);

  EXPECT_EQ(rhs.size(), 0u);
  EXPECT_EQ(lhs.size(), lhs_before);
}

}  // namespace