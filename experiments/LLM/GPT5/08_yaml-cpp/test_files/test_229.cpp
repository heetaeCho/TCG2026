// TEST_ID: 229
#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_ref.h"
#include "yaml-cpp/node/detail/node.h"

namespace {

using YAML::detail::node;
using YAML::detail::node_ref;
using YAML::detail::shared_memory_holder;

class NodeRefInsertTest_229 : public ::testing::Test {
protected:
  shared_memory_holder mem_;  // default-constructed (may be null depending on typedef)
};

TEST_F(NodeRefInsertTest_229, InsertSingleKeyValue_AllowsLookupBySameKeyNode_229) {
  node_ref ref;

  node key;
  key.set_scalar("k");

  node value;
  value.set_scalar("v");

  EXPECT_NO_THROW(ref.insert(key, value, mem_));

  node* got = ref.get(key, mem_);
  ASSERT_NE(got, nullptr);
  EXPECT_EQ(got->scalar(), "v");

  // Insert should not mutate the input nodes' observable state.
  EXPECT_EQ(key.scalar(), "k");
  EXPECT_EQ(value.scalar(), "v");

  // Basic observable container behavior: size should be non-zero after an insert.
  EXPECT_GE(ref.size(), 1u);
}

TEST_F(NodeRefInsertTest_229, InsertMultiplePairs_AllKeysAreRetrievable_229) {
  node_ref ref;

  node k1; k1.set_scalar("a");
  node v1; v1.set_scalar("1");

  node k2; k2.set_scalar("b");
  node v2; v2.set_scalar("2");

  node k3; k3.set_scalar("c");
  node v3; v3.set_scalar("3");

  EXPECT_NO_THROW(ref.insert(k1, v1, mem_));
  EXPECT_NO_THROW(ref.insert(k2, v2, mem_));
  EXPECT_NO_THROW(ref.insert(k3, v3, mem_));

  node* g1 = ref.get(k1, mem_);
  node* g2 = ref.get(k2, mem_);
  node* g3 = ref.get(k3, mem_);

  ASSERT_NE(g1, nullptr);
  ASSERT_NE(g2, nullptr);
  ASSERT_NE(g3, nullptr);

  EXPECT_EQ(g1->scalar(), "1");
  EXPECT_EQ(g2->scalar(), "2");
  EXPECT_EQ(g3->scalar(), "3");

  EXPECT_GE(ref.size(), 3u);
}

TEST_F(NodeRefInsertTest_229, InsertWithDefaultConstructedMemoryHolder_DoesNotThrow_229) {
  node_ref ref;

  node key;
  key.set_scalar("key");

  node value;
  value.set_scalar("value");

  // Boundary-ish case: shared_memory_holder may be null when default-constructed.
  EXPECT_NO_THROW(ref.insert(key, value, shared_memory_holder{}));

  node* got = ref.get(key, shared_memory_holder{});
  ASSERT_NE(got, nullptr);
  EXPECT_EQ(got->scalar(), "value");
}

TEST_F(NodeRefInsertTest_229, InsertValueNodeWithChildren_RetrievedNodeHasObservableContent_229) {
  node_ref ref;

  node key;
  key.set_scalar("parent");

  node value;
  node child;
  child.set_scalar("child0");

  // Build some observable structure in the value node.
  EXPECT_NO_THROW(value.push_back(child, mem_));

  EXPECT_NO_THROW(ref.insert(key, value, mem_));

  node* got = ref.get(key, mem_);
  ASSERT_NE(got, nullptr);

  // Observable behavior: retrieved node should expose the inserted structure via public API.
  EXPECT_GE(got->size(), 1u);

  // Also ensure the original value remains usable/unchanged in an observable way.
  EXPECT_GE(value.size(), 1u);
}

}  // namespace