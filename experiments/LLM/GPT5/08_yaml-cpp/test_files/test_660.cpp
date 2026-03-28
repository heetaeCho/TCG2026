// File: yaml-cpp/node/detail/impl_get_sequence_test_660.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <vector>

#include "yaml-cpp/node/detail/impl.h"

namespace {

using YAML::detail::get;
using YAML::detail::node;
using YAML::detail::shared_memory_holder;

class GetSequenceTest_660 : public ::testing::Test {
 protected:
  // The function under test ignores the memory-holder parameter, but we still
  // must pass a valid value. This assumes shared_memory_holder is default
  // constructible in the real codebase (as it typically is in yaml-cpp internals).
  shared_memory_holder mem_{};
};

TEST_F(GetSequenceTest_660, EmptySequenceReturnsNullptrForZeroKey_660) {
  std::vector<node*> seq;
  node* out = get(seq, static_cast<std::size_t>(0), mem_);
  EXPECT_EQ(out, nullptr);
}

TEST_F(GetSequenceTest_660, EmptySequenceReturnsNullptrForLargeKey_660) {
  std::vector<node*> seq;
  node* out = get(seq, static_cast<std::size_t>(123456u), mem_);
  EXPECT_EQ(out, nullptr);
}

TEST_F(GetSequenceTest_660, KeyEqualToSizeReturnsNullptr_660) {
  node* p0 = reinterpret_cast<node*>(static_cast<std::uintptr_t>(0x1));
  node* p1 = reinterpret_cast<node*>(static_cast<std::uintptr_t>(0x2));

  std::vector<node*> seq{p0, p1};
  const auto original_size = seq.size();

  // key == size() is out-of-range
  node* out = get(seq, static_cast<std::size_t>(seq.size()), mem_);
  EXPECT_EQ(out, nullptr);

  // Should not modify the sequence.
  EXPECT_EQ(seq.size(), original_size);
  EXPECT_EQ(seq[0], p0);
  EXPECT_EQ(seq[1], p1);
}

TEST_F(GetSequenceTest_660, KeyGreaterThanSizeReturnsNullptr_660) {
  node* p0 = reinterpret_cast<node*>(static_cast<std::uintptr_t>(0x10));
  std::vector<node*> seq{p0};

  node* out = get(seq, static_cast<std::size_t>(2), mem_);
  EXPECT_EQ(out, nullptr);
}

TEST_F(GetSequenceTest_660, ReturnsFirstElementForZeroKey_660) {
  node* p0 = reinterpret_cast<node*>(static_cast<std::uintptr_t>(0x100));
  node* p1 = reinterpret_cast<node*>(static_cast<std::uintptr_t>(0x200));
  std::vector<node*> seq{p0, p1};

  node* out = get(seq, static_cast<std::size_t>(0), mem_);
  EXPECT_EQ(out, p0);
}

TEST_F(GetSequenceTest_660, ReturnsLastElementForLastValidKey_660) {
  node* p0 = reinterpret_cast<node*>(static_cast<std::uintptr_t>(0x111));
  node* p1 = reinterpret_cast<node*>(static_cast<std::uintptr_t>(0x222));
  node* p2 = reinterpret_cast<node*>(static_cast<std::uintptr_t>(0x333));

  std::vector<node*> seq{p0, p1, p2};

  node* out = get(seq, static_cast<std::size_t>(2), mem_);
  EXPECT_EQ(out, p2);
}

TEST_F(GetSequenceTest_660, ReturnsNullptrWhenStoredPointerIsNull_660) {
  node* p0 = reinterpret_cast<node*>(static_cast<std::uintptr_t>(0xABC));
  std::vector<node*> seq{p0, nullptr};

  node* out0 = get(seq, static_cast<std::size_t>(0), mem_);
  node* out1 = get(seq, static_cast<std::size_t>(1), mem_);

  EXPECT_EQ(out0, p0);
  EXPECT_EQ(out1, nullptr);
}

}  // namespace