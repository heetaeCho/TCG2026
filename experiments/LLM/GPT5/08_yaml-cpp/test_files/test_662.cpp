// TEST_ID: 662
#include <gtest/gtest.h>

#include <cstddef>
#include <limits>
#include <vector>

// Include the header under test.
#include "yaml-cpp/node/detail/impl.h"

namespace {

class GetTest_662 : public ::testing::Test {
protected:
  using NodePtr = YAML::detail::node*;

  // Keep the sequence simple: nullptr entries are sufficient for black-box
  // equivalence checks vs get_idx<std::size_t>::get.
  std::vector<NodePtr> seq_{nullptr, nullptr, nullptr};

  YAML::detail::shared_memory_holder mem_{};
};

TEST_F(GetTest_662, NegativeKeyReturnsNullptr_Int_662) {
  const int key = -1;
  EXPECT_EQ(nullptr, YAML::detail::get(seq_, key, mem_));
}

TEST_F(GetTest_662, NegativeKeyReturnsNullptr_MinInt_662) {
  const int key = (std::numeric_limits<int>::min)();
  EXPECT_EQ(nullptr, YAML::detail::get(seq_, key, mem_));
}

TEST_F(GetTest_662, ZeroKeyMatchesGetIdxSizeT_662) {
  const int key = 0;

  auto* expected =
      YAML::detail::get_idx<std::size_t>::get(seq_, static_cast<std::size_t>(key), mem_);
  auto* actual = YAML::detail::get(seq_, key, mem_);

  EXPECT_EQ(expected, actual);
}

TEST_F(GetTest_662, PositiveInRangeKeyMatchesGetIdxSizeT_662) {
  const int key = 1;

  auto* expected =
      YAML::detail::get_idx<std::size_t>::get(seq_, static_cast<std::size_t>(key), mem_);
  auto* actual = YAML::detail::get(seq_, key, mem_);

  EXPECT_EQ(expected, actual);
}

TEST_F(GetTest_662, PositiveOutOfRangeKeyMatchesGetIdxSizeT_662) {
  const int key = 100;  // clearly out of range for seq_ (size 3)

  auto* expected =
      YAML::detail::get_idx<std::size_t>::get(seq_, static_cast<std::size_t>(key), mem_);
  auto* actual = YAML::detail::get(seq_, key, mem_);

  EXPECT_EQ(expected, actual);
}

TEST_F(GetTest_662, LongLongNegativeKeyReturnsNullptr_662) {
  const long long key = -42;
  EXPECT_EQ(nullptr, YAML::detail::get(seq_, key, mem_));
}

TEST_F(GetTest_662, LongLongNonNegativeKeyMatchesGetIdxSizeT_662) {
  const long long key = 2;

  auto* expected =
      YAML::detail::get_idx<std::size_t>::get(seq_, static_cast<std::size_t>(key), mem_);
  auto* actual = YAML::detail::get(seq_, key, mem_);

  EXPECT_EQ(expected, actual);
}

}  // namespace