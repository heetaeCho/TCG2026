// File: ./TestProjects/yaml-cpp/test/memory_test_627.cpp

#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/memory.h"

namespace {

using YAML::detail::memory;

class MemoryTest_627 : public ::testing::Test {};

TEST_F(MemoryTest_627, DefaultConstructedHasZeroSize_627) {
  memory m;
  EXPECT_EQ(m.size(), 0u);
}

TEST_F(MemoryTest_627, ConstDefaultConstructedHasZeroSize_627) {
  const memory m;
  EXPECT_EQ(m.size(), 0u);
}

TEST_F(MemoryTest_627, CreateNodeIncreasesSize_627) {
  memory m;
  const size_t before = m.size();

  (void)m.create_node();

  const size_t after = m.size();
  EXPECT_GT(after, before);
}

TEST_F(MemoryTest_627, MultipleCreateNodeIncreasesSizeByCount_627) {
  memory m;
  const size_t before = m.size();

  constexpr size_t kCount = 10;
  for (size_t i = 0; i < kCount; ++i) {
    (void)m.create_node();
  }

  EXPECT_EQ(m.size(), before + kCount);
}

TEST_F(MemoryTest_627, MergeFromEmptyDoesNotChangeSize_627) {
  memory lhs;
  for (int i = 0; i < 3; ++i) {
    (void)lhs.create_node();
  }

  const memory rhs_empty;

  const size_t before = lhs.size();
  lhs.merge(rhs_empty);
  EXPECT_EQ(lhs.size(), before);
}

TEST_F(MemoryTest_627, MergeIntoEmptyResultsInNonZeroWhenRhsNonEmpty_627) {
  memory rhs;
  for (int i = 0; i < 4; ++i) {
    (void)rhs.create_node();
  }

  memory lhs_empty;
  EXPECT_EQ(lhs_empty.size(), 0u);
  ASSERT_GT(rhs.size(), 0u);

  lhs_empty.merge(rhs);

  EXPECT_GT(lhs_empty.size(), 0u);
  EXPECT_GE(lhs_empty.size(), rhs.size());
}

TEST_F(MemoryTest_627, MergeNonEmptyIncreasesOrKeepsSizeAndAtLeastRhsSize_627) {
  memory lhs;
  for (int i = 0; i < 2; ++i) {
    (void)lhs.create_node();
  }

  memory rhs;
  for (int i = 0; i < 5; ++i) {
    (void)rhs.create_node();
  }

  const size_t lhs_before = lhs.size();
  const size_t rhs_before = rhs.size();

  lhs.merge(rhs);

  EXPECT_GE(lhs.size(), lhs_before);
  EXPECT_GE(lhs.size(), rhs_before);
  EXPECT_GT(lhs.size(), lhs_before);
}

TEST_F(MemoryTest_627, SelfMergeIsSafeAndDoesNotDecreaseSize_627) {
  memory m;
  for (int i = 0; i < 6; ++i) {
    (void)m.create_node();
  }

  const size_t before = m.size();
  m.merge(m);
  EXPECT_GE(m.size(), before);
}

}  // namespace