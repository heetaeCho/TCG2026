// TEST_ID: 664
//
// File: test/node/detail/remove_idx_test.cpp
//
// Notes:
// - We treat YAML::detail::remove_idx::remove as a black box.
// - Observable behavior from the provided stub interface:
//     * Returns bool
//     * Accepts (std::vector<node*>&, const Key&, std::size_t&)
//     * The provided partial implementation always returns false.
// - We avoid relying on any private/internal state of YAML::node or YAML::Key.
// - We only validate what we can observe through the interface: return value,
//   and that the function can be called across typical/boundary inputs without throwing.
//
// If your real codebase defines YAML::detail::node and YAML::detail::Key,
// include the actual header and remove the local forward declarations below.

#include <gtest/gtest.h>

#include <cstddef>
#include <vector>

// Include the header under test from your codebase.
#include "yaml-cpp/node/detail/impl.h"

namespace YAML {
namespace detail {

// If these types are already defined by the included header in your codebase,
// remove these forward declarations.
struct node;
struct Key;

}  // namespace detail
}  // namespace YAML

namespace {

using YAML::detail::Key;
using YAML::detail::node;

class RemoveIdxTest_664 : public ::testing::Test {};

TEST_F(RemoveIdxTest_664, EmptyVectorReturnsFalse_664) {
  std::vector<node*> nodes;
  std::size_t idx = 0;

  // Key is opaque; we must construct a reference. We only need a const reference for calling.
  // In real code, Key should be default-constructible or constructible as needed.
  // If Key is not default-constructible, replace this with a valid Key creation in your codebase.
  const Key* key_ptr = nullptr;
  // We can't dereference nullptr; so we skip and instead use a dummy object storage.
  // This trick avoids assuming Key has a public constructor while still providing a reference
  // by allocating raw storage and not touching its internals.
  alignas(Key) unsigned char key_storage[sizeof(Key)];
  const Key& key = *reinterpret_cast<const Key*>(key_storage);

  EXPECT_FALSE(YAML::detail::remove_idx::remove(nodes, key, idx));
}

TEST_F(RemoveIdxTest_664, NonEmptyVectorReturnsFalse_664) {
  std::vector<node*> nodes;
  nodes.push_back(nullptr);  // boundary: vector contains a null node* (still a valid pointer value)
  std::size_t idx = 0;

  alignas(Key) unsigned char key_storage[sizeof(Key)];
  const Key& key = *reinterpret_cast<const Key*>(key_storage);

  EXPECT_FALSE(YAML::detail::remove_idx::remove(nodes, key, idx));
}

TEST_F(RemoveIdxTest_664, LargeIndexValueReturnsFalse_664) {
  std::vector<node*> nodes;
  nodes.push_back(nullptr);
  nodes.push_back(nullptr);

  std::size_t idx = static_cast<std::size_t>(-1);  // boundary: max size_t
  alignas(Key) unsigned char key_storage[sizeof(Key)];
  const Key& key = *reinterpret_cast<const Key*>(key_storage);

  EXPECT_FALSE(YAML::detail::remove_idx::remove(nodes, key, idx));
}

TEST_F(RemoveIdxTest_664, IndexIsNotRequiredToBeInitializedReturnsFalse_664) {
  std::vector<node*> nodes;
  nodes.push_back(nullptr);

  // boundary: idx has an arbitrary non-zero value
  std::size_t idx = 12345;

  alignas(Key) unsigned char key_storage[sizeof(Key)];
  const Key& key = *reinterpret_cast<const Key*>(key_storage);

  EXPECT_FALSE(YAML::detail::remove_idx::remove(nodes, key, idx));
}

TEST_F(RemoveIdxTest_664, DoesNotThrowForTypicalInputs_664) {
  std::vector<node*> nodes;
  nodes.push_back(nullptr);
  std::size_t idx = 0;

  alignas(Key) unsigned char key_storage[sizeof(Key)];
  const Key& key = *reinterpret_cast<const Key*>(key_storage);

  EXPECT_NO_THROW({
    (void)YAML::detail::remove_idx::remove(nodes, key, idx);
  });
}

}  // namespace