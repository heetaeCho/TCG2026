// TEST_ID: 661
#include <gtest/gtest.h>

#include <cstddef>
#include <memory>
#include <vector>

#include "yaml-cpp/node/detail/impl.h"
#include "yaml-cpp/node/detail/memory.h"

namespace {

class GetSequenceTest_661 : public ::testing::Test {
 protected:
  using Node = YAML::detail::node;
  using Seq = std::vector<Node*>;

  void SetUp() override {
    mem_.reset(new YAML::detail::memory_holder());
  }

  YAML::detail::shared_memory_holder mem_;
  Seq seq_;

  // For tests that need an "undefined" node explicitly not owned by memory_holder.
  std::vector<std::unique_ptr<Node>> owned_nodes_;
  Node* MakeOwnedNode() {
    owned_nodes_.push_back(std::make_unique<Node>());
    return owned_nodes_.back().get();
  }
};

TEST_F(GetSequenceTest_661, KeyZeroOnEmptyCreatesFirstNode_661) {
  ASSERT_TRUE(seq_.empty());

  YAML::detail::node* n = YAML::detail::get(seq_, static_cast<std::size_t>(0), mem_);

  ASSERT_NE(n, nullptr);
  ASSERT_EQ(seq_.size(), 1u);
  EXPECT_EQ(seq_[0], n);
}

TEST_F(GetSequenceTest_661, KeyZeroWhenAlreadyPresentReturnsExistingWithoutGrowing_661) {
  YAML::detail::node* first = YAML::detail::get(seq_, static_cast<std::size_t>(0), mem_);
  ASSERT_NE(first, nullptr);
  ASSERT_EQ(seq_.size(), 1u);

  YAML::detail::node* again = YAML::detail::get(seq_, static_cast<std::size_t>(0), mem_);

  EXPECT_EQ(again, first);
  EXPECT_EQ(seq_.size(), 1u);
}

TEST_F(GetSequenceTest_661, KeyEqualsSizeAppendsAndReturnsNewElement_661) {
  YAML::detail::node* first = YAML::detail::get(seq_, static_cast<std::size_t>(0), mem_);
  ASSERT_NE(first, nullptr);
  ASSERT_EQ(seq_.size(), 1u);

  YAML::detail::node* second = YAML::detail::get(seq_, static_cast<std::size_t>(1), mem_);

  ASSERT_NE(second, nullptr);
  ASSERT_EQ(seq_.size(), 2u);
  EXPECT_EQ(seq_[1], second);
}

TEST_F(GetSequenceTest_661, KeyGreaterThanSizeReturnsNullAndDoesNotGrow_661) {
  YAML::detail::node* first = YAML::detail::get(seq_, static_cast<std::size_t>(0), mem_);
  ASSERT_NE(first, nullptr);
  ASSERT_EQ(seq_.size(), 1u);

  YAML::detail::node* n = YAML::detail::get(seq_, static_cast<std::size_t>(2), mem_);

  EXPECT_EQ(n, nullptr);
  EXPECT_EQ(seq_.size(), 1u);
  EXPECT_EQ(seq_[0], first);
}

TEST_F(GetSequenceTest_661, PreviousElementUndefinedReturnsNullAndDoesNotAppend_661) {
  // Put an explicitly "undefined" node at index 0.
  YAML::detail::node* undefined0 = MakeOwnedNode();
  ASSERT_FALSE(undefined0->is_defined()) << "Test requires a default-constructed detail::node to be undefined.";
  seq_.push_back(undefined0);
  ASSERT_EQ(seq_.size(), 1u);

  // Request key==1 (==size). Because previous (key-1) is undefined, should return nullptr and not grow.
  YAML::detail::node* n = YAML::detail::get(seq_, static_cast<std::size_t>(1), mem_);

  EXPECT_EQ(n, nullptr);
  EXPECT_EQ(seq_.size(), 1u);
  EXPECT_EQ(seq_[0], undefined0);
}

TEST_F(GetSequenceTest_661, KeyZeroDoesNotDependOnPreviousDefinedState_661) {
  // Even if the element at index 0 is undefined, key==0 should not trip the (key>0 && ...) check.
  YAML::detail::node* undefined0 = MakeOwnedNode();
  ASSERT_FALSE(undefined0->is_defined()) << "Test requires a default-constructed detail::node to be undefined.";
  seq_.push_back(undefined0);
  ASSERT_EQ(seq_.size(), 1u);

  YAML::detail::node* n = YAML::detail::get(seq_, static_cast<std::size_t>(0), mem_);

  EXPECT_EQ(n, undefined0);
  EXPECT_EQ(seq_.size(), 1u);
}

}  // namespace