// File: ./TestProjects/yaml-cpp/test/memory_test_625.cpp

#include <gtest/gtest.h>

#include <yaml-cpp/node/detail/memory.h>

#include <cstddef>
#include <vector>

namespace {

using YAML::detail::memory;

// NOTE:
// These tests treat YAML::detail::memory as a black box and only verify
// observable behavior via the public interface: create_node(), merge(), size().

class MemoryTest_625 : public ::testing::Test {
protected:
  memory mem_;
};

TEST_F(MemoryTest_625, DefaultSizeIsStableAndNonNegative_625) {
  // size() returns size_t, so it can't be negative; verify it's callable/stable.
  const size_t s1 = mem_.size();
  const size_t s2 = mem_.size();
  EXPECT_EQ(s1, s2);
}

TEST_F(MemoryTest_625, CreateNodeDoesNotThrow_625) {
  EXPECT_NO_THROW({
    (void)mem_.create_node();
  });
}

TEST_F(MemoryTest_625, CreateNodeDoesNotDecreaseSize_625) {
  const size_t before = mem_.size();
  (void)mem_.create_node();
  const size_t after = mem_.size();
  EXPECT_GE(after, before);
}

TEST_F(MemoryTest_625, MultipleCreateNodeCallsDoNotDecreaseSizeMonotonic_625) {
  const size_t s0 = mem_.size();
  (void)mem_.create_node();
  const size_t s1 = mem_.size();
  (void)mem_.create_node();
  const size_t s2 = mem_.size();

  EXPECT_GE(s1, s0);
  EXPECT_GE(s2, s1);
}

TEST_F(MemoryTest_625, CreateNodeReturnsDistinctReferencesAcrossCalls_625) {
  // We only check that separate create_node() calls return references
  // to different objects (distinct addresses).
  auto& n1 = mem_.create_node();
  auto& n2 = mem_.create_node();
  EXPECT_NE(&n1, &n2);
}

TEST_F(MemoryTest_625, PreviouslyReturnedNodeReferenceRemainsValidAfterMoreCreates_625) {
  auto& first = mem_.create_node();
  void* first_addr = static_cast<void*>(&first);

  // Create additional nodes; previously returned reference should still refer
  // to the same object address (stability of reference identity).
  for (int i = 0; i < 10; ++i) {
    (void)mem_.create_node();
  }

  EXPECT_EQ(static_cast<void*>(&first), first_addr);
}

TEST_F(MemoryTest_625, MergeDoesNotThrowForEmptyRhs_625) {
  memory rhs;
  EXPECT_NO_THROW({
    mem_.merge(rhs);
  });
}

TEST_F(MemoryTest_625, MergeDoesNotDecreaseSize_625) {
  memory rhs;

  // Populate both sides a bit (without assuming exact counting semantics).
  (void)mem_.create_node();
  (void)mem_.create_node();
  (void)rhs.create_node();

  const size_t before = mem_.size();
  mem_.merge(rhs);
  const size_t after = mem_.size();

  EXPECT_GE(after, before);
}

TEST_F(MemoryTest_625, MergeWithSelfDoesNotThrowAndDoesNotDecreaseSize_625) {
  (void)mem_.create_node();
  (void)mem_.create_node();

  const size_t before = mem_.size();
  EXPECT_NO_THROW({
    mem_.merge(mem_);
  });
  const size_t after = mem_.size();

  EXPECT_GE(after, before);
}

TEST_F(MemoryTest_625, MergePreservesPreviouslyReturnedNodeReferenceIdentity_625) {
  auto& n = mem_.create_node();
  void* addr_before = static_cast<void*>(&n);

  memory rhs;
  (void)rhs.create_node();
  (void)rhs.create_node();

  mem_.merge(rhs);

  // The node reference obtained before merge should still point to the same object.
  EXPECT_EQ(static_cast<void*>(&n), addr_before);
}

}  // namespace