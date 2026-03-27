// TEST_ID: 232
#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"

namespace {

using YAML::detail::node;
using YAML::detail::node_ref;
using YAML::detail::shared_memory_holder;

class NodeRefGetTest_232 : public ::testing::Test {
 protected:
  shared_memory_holder mem_;  // default-constructed (nullptr) is acceptable for these interface-level tests
};

TEST_F(NodeRefGetTest_232, GetOnFreshNodeReturnsNullptr_232) {
  node parent;
  node key;
  key.set_scalar("missing");

  const node_ref* ref = parent.ref();
  ASSERT_NE(ref, nullptr);

  node* out = ref->get(key, mem_);
  EXPECT_EQ(out, nullptr);
}

TEST_F(NodeRefGetTest_232, GetReturnsInsertedValueForNodeKey_232) {
  node parent;

  node key;
  key.set_scalar("k");

  node value;
  value.set_scalar("v");

  parent.insert(key, value, mem_);

  const node_ref* ref = parent.ref();
  ASSERT_NE(ref, nullptr);

  node* out = ref->get(key, mem_);
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(out->scalar(), "v");
}

TEST_F(NodeRefGetTest_232, GetWithDifferentKeyReturnsNullptr_232) {
  node parent;

  node key1;
  key1.set_scalar("k1");
  node value1;
  value1.set_scalar("v1");

  parent.insert(key1, value1, mem_);

  node key2;
  key2.set_scalar("k2");

  const node_ref* ref = parent.ref();
  ASSERT_NE(ref, nullptr);

  node* out = ref->get(key2, mem_);
  EXPECT_EQ(out, nullptr);
}

TEST_F(NodeRefGetTest_232, GetWithKeyObjectHavingSameScalarFindsValue_232) {
  node parent;

  node key_inserted;
  key_inserted.set_scalar("same");

  node value;
  value.set_scalar("payload");

  parent.insert(key_inserted, value, mem_);

  // Use a different node instance that represents the same logical key.
  node key_lookup;
  key_lookup.set_scalar("same");

  const node_ref* ref = parent.ref();
  ASSERT_NE(ref, nullptr);

  node* out = ref->get(key_lookup, mem_);
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(out->scalar(), "payload");
}

TEST_F(NodeRefGetTest_232, GetAfterRemoveReturnsNullptr_232) {
  node parent;

  node key;
  key.set_scalar("k");
  node value;
  value.set_scalar("v");

  parent.insert(key, value, mem_);

  // Sanity: present before remove.
  ASSERT_NE(parent.get(key, mem_), nullptr);

  EXPECT_TRUE(parent.remove(key, mem_));

  const node_ref* ref = parent.ref();
  ASSERT_NE(ref, nullptr);

  node* out = ref->get(key, mem_);
  EXPECT_EQ(out, nullptr);
}

}  // namespace