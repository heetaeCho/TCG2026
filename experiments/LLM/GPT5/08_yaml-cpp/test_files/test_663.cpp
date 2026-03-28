// TEST_ID: 663
#include <gtest/gtest.h>

#include <climits>
#include <vector>

#include "yaml-cpp/node/detail/impl.h"

namespace {

class GetSequenceTest_663 : public ::testing::Test {
protected:
  // Use a sequence of nullptrs to avoid relying on node construction details.
  std::vector<YAML::detail::node*> seq_{nullptr, nullptr, nullptr};
  YAML::detail::shared_memory_holder mem_{};
};

TEST_F(GetSequenceTest_663, NegativeKeyReturnsNullptr_663) {
  const int key = -1;
  YAML::detail::node* out = YAML::detail::get(seq_, key, mem_);
  EXPECT_EQ(out, nullptr);
}

TEST_F(GetSequenceTest_663, VeryNegativeKeyReturnsNullptr_663) {
  const int key = INT_MIN;
  YAML::detail::node* out = YAML::detail::get(seq_, key, mem_);
  EXPECT_EQ(out, nullptr);
}

TEST_F(GetSequenceTest_663, ZeroKeyMatchesGetIdxResult_663) {
  const int key = 0;

  YAML::detail::node* out = YAML::detail::get(seq_, key, mem_);
  YAML::detail::node* expected =
      YAML::detail::get_idx<std::size_t>::get(seq_, static_cast<std::size_t>(key), mem_);

  EXPECT_EQ(out, expected);
}

TEST_F(GetSequenceTest_663, PositiveKeyMatchesGetIdxResult_663) {
  const int key = 1;

  YAML::detail::node* out = YAML::detail::get(seq_, key, mem_);
  YAML::detail::node* expected =
      YAML::detail::get_idx<std::size_t>::get(seq_, static_cast<std::size_t>(key), mem_);

  EXPECT_EQ(out, expected);
}

TEST_F(GetSequenceTest_663, LargeNonNegativeKeyMatchesGetIdxResult_663) {
  const int key = 123456;

  YAML::detail::node* out = YAML::detail::get(seq_, key, mem_);
  YAML::detail::node* expected =
      YAML::detail::get_idx<std::size_t>::get(seq_, static_cast<std::size_t>(key), mem_);

  EXPECT_EQ(out, expected);
}

TEST_F(GetSequenceTest_663, EmptySequenceNegativeKeyReturnsNullptr_663) {
  std::vector<YAML::detail::node*> empty;
  const int key = -5;

  YAML::detail::node* out = YAML::detail::get(empty, key, mem_);
  EXPECT_EQ(out, nullptr);
}

TEST_F(GetSequenceTest_663, EmptySequenceNonNegativeKeyMatchesGetIdxResult_663) {
  std::vector<YAML::detail::node*> empty;
  const int key = 0;

  YAML::detail::node* out = YAML::detail::get(empty, key, mem_);
  YAML::detail::node* expected =
      YAML::detail::get_idx<std::size_t>::get(empty, static_cast<std::size_t>(key), mem_);

  EXPECT_EQ(out, expected);
}

}  // namespace