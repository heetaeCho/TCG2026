// TEST_ID: 547
// File: yaml-cpp/node/detail/memory_holder_test.cpp

#include <gtest/gtest.h>

#include <yaml-cpp/node/detail/memory.h>

namespace {

using YAML::detail::memory_holder;

class MemoryHolderTest_547 : public ::testing::Test {
protected:
  memory_holder lhs_;
  memory_holder rhs_;
};

TEST_F(MemoryHolderTest_547, CreateNodeDoesNotThrowAndReturnsReference_547) {
  ASSERT_NO_THROW({
    auto& n = lhs_.create_node();
    // Observable, interface-safe check: reference must refer to an object.
    // (Taking the address should be safe if a valid reference was returned.)
    EXPECT_NE(&n, nullptr);
  });
}

TEST_F(MemoryHolderTest_547, CreateNodeCanBeCalledMultipleTimes_547) {
  ASSERT_NO_THROW({
    auto& n1 = lhs_.create_node();
    auto& n2 = lhs_.create_node();
    EXPECT_NE(&n1, nullptr);
    EXPECT_NE(&n2, nullptr);
  });
}

TEST_F(MemoryHolderTest_547, MergeEmptyHoldersDoesNotThrow_547) {
  ASSERT_NO_THROW({
    lhs_.merge(rhs_);
  });

  // After merge, both sides should still be usable through the public interface.
  ASSERT_NO_THROW({
    auto& n_lhs = lhs_.create_node();
    auto& n_rhs = rhs_.create_node();
    EXPECT_NE(&n_lhs, nullptr);
    EXPECT_NE(&n_rhs, nullptr);
  });
}

TEST_F(MemoryHolderTest_547, MergeAfterCreatingNodesDoesNotThrow_547) {
  ASSERT_NO_THROW({
    (void)lhs_.create_node();
    (void)lhs_.create_node();
    (void)rhs_.create_node();
  });

  ASSERT_NO_THROW({
    lhs_.merge(rhs_);
  });

  ASSERT_NO_THROW({
    auto& n_lhs = lhs_.create_node();
    auto& n_rhs = rhs_.create_node();
    EXPECT_NE(&n_lhs, nullptr);
    EXPECT_NE(&n_rhs, nullptr);
  });
}

TEST_F(MemoryHolderTest_547, MergeCanBeCalledMoreThanOnce_547) {
  ASSERT_NO_THROW({
    lhs_.merge(rhs_);
    lhs_.merge(rhs_);
  });

  ASSERT_NO_THROW({
    auto& n_lhs = lhs_.create_node();
    auto& n_rhs = rhs_.create_node();
    EXPECT_NE(&n_lhs, nullptr);
    EXPECT_NE(&n_rhs, nullptr);
  });
}

TEST_F(MemoryHolderTest_547, MergeIsBidirectionalCallable_547) {
  // Boundary-style scenario: merge in the opposite direction as well.
  ASSERT_NO_THROW({
    rhs_.merge(lhs_);
  });

  ASSERT_NO_THROW({
    auto& n_lhs = lhs_.create_node();
    auto& n_rhs = rhs_.create_node();
    EXPECT_NE(&n_lhs, nullptr);
    EXPECT_NE(&n_rhs, nullptr);
  });
}

}  // namespace