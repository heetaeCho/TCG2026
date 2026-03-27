// TEST_ID: 659
#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "yaml-cpp/node/detail/impl.h"

// The provided partial code references YAML::detail::node, Key, and shared_memory_holder.
// In many yaml-cpp builds those are available via the included header, but to keep the
// test focused on observable behavior, we only assert that get(...) returns nullptr.
//
// If your build complains about missing Key/shared_memory_holder types, make sure your
// include path points at the project’s yaml-cpp headers (not a different installed version).

namespace {

class GetIdxTest_659 : public ::testing::Test {};

}  // namespace

TEST_F(GetIdxTest_659, ReturnsNullptrForEmptySequence_659) {
  std::vector<YAML::detail::node*> seq;

  // Construct default values for key and memory holder.
  // These should be default-constructible in the real codebase.
  YAML::Key key{};
  YAML::detail::shared_memory_holder mem{};

  YAML::detail::node* out = YAML::detail::get_idx::get(seq, key, mem);
  EXPECT_EQ(out, nullptr);
}

TEST_F(GetIdxTest_659, ReturnsNullptrForNonEmptySequence_659) {
  // Sequence contains arbitrary pointers; get(...) should still return nullptr
  // per the provided implementation (observable behavior).
  YAML::detail::node* fake1 = reinterpret_cast<YAML::detail::node*>(0x1);
  YAML::detail::node* fake2 = reinterpret_cast<YAML::detail::node*>(0x2);

  std::vector<YAML::detail::node*> seq{fake1, fake2};

  YAML::Key key{};
  YAML::detail::shared_memory_holder mem{};

  YAML::detail::node* out = YAML::detail::get_idx::get(seq, key, mem);
  EXPECT_EQ(out, nullptr);
}

TEST_F(GetIdxTest_659, ReturnsNullptrWithDifferentKeys_659) {
  std::vector<YAML::detail::node*> seq;

  YAML::detail::shared_memory_holder mem{};

  // Try a couple of distinct keys (as far as the type allows).
  // We avoid assuming any internal semantics—only that the return is observable.
  YAML::Key key1{};
  YAML::Key key2{};

  YAML::detail::node* out1 = YAML::detail::get_idx::get(seq, key1, mem);
  YAML::detail::node* out2 = YAML::detail::get_idx::get(seq, key2, mem);

  EXPECT_EQ(out1, nullptr);
  EXPECT_EQ(out2, nullptr);
}

TEST_F(GetIdxTest_659, ReturnsNullptrWithDifferentMemoryHolders_659) {
  std::vector<YAML::detail::node*> seq;
  YAML::Key key{};

  YAML::detail::shared_memory_holder mem1{};
  YAML::detail::shared_memory_holder mem2{};

  YAML::detail::node* out1 = YAML::detail::get_idx::get(seq, key, mem1);
  YAML::detail::node* out2 = YAML::detail::get_idx::get(seq, key, mem2);

  EXPECT_EQ(out1, nullptr);
  EXPECT_EQ(out2, nullptr);
}