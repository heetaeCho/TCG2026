// TEST_ID: 261
#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"

namespace {

using YAML::detail::node;

// If shared_memory_holder is a smart pointer type (as in yaml-cpp), default construction
// should yield an "empty" holder that is still valid to pass through the interface.
inline YAML::detail::shared_memory_holder DefaultMemory_261() {
  return YAML::detail::shared_memory_holder{};
}

class NodeGetTest_261 : public ::testing::Test {
 protected:
  YAML::detail::shared_memory_holder mem_ = DefaultMemory_261();
};

TEST_F(NodeGetTest_261, ReturnsNullWhenKeyMissing_261) {
  node map;
  node key;
  key.set_scalar("missing");

  node* out = map.get(key, mem_);
  EXPECT_EQ(out, nullptr);
}

TEST_F(NodeGetTest_261, ReturnsNonNullWhenKeyExists_261) {
  node map;

  node key;
  key.set_scalar("k");

  node value;
  value.set_scalar("v");

  map.insert(key, value, mem_);

  node* out = map.get(key, mem_);
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(out->scalar(), "v");
}

TEST_F(NodeGetTest_261, WorksWhenCalledOnConstNode_261) {
  node map;

  node key;
  key.set_scalar("k");

  node value;
  value.set_scalar("v");

  map.insert(key, value, mem_);

  const node& cmap = map;
  node* out = cmap.get(key, mem_);
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(out->scalar(), "v");
}

TEST_F(NodeGetTest_261, FindsValueUsingEquivalentKeyNode_261) {
  node map;

  node key1;
  key1.set_scalar("same-key");

  node value;
  value.set_scalar("value");

  map.insert(key1, value, mem_);

  node key2;
  key2.set_scalar("same-key");

  node* out = map.get(key2, mem_);
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(out->scalar(), "value");
}

TEST_F(NodeGetTest_261, ReturnedPointerAllowsObservableMutation_261) {
  node map;

  node key;
  key.set_scalar("k");

  node value;
  value.set_scalar("v1");

  map.insert(key, value, mem_);

  node* out1 = map.get(key, mem_);
  ASSERT_NE(out1, nullptr);
  EXPECT_EQ(out1->scalar(), "v1");

  // Mutate through the returned pointer (observable via subsequent get()).
  out1->set_scalar("v2");

  node* out2 = map.get(key, mem_);
  ASSERT_NE(out2, nullptr);
  EXPECT_EQ(out2->scalar(), "v2");
}

TEST_F(NodeGetTest_261, EmptyScalarKeyNotFoundByDefault_261) {
  node map;

  node key;
  key.set_scalar("");  // boundary input

  node* out = map.get(key, mem_);
  EXPECT_EQ(out, nullptr);
}

TEST_F(NodeGetTest_261, EmptyScalarKeyCanBeInsertedAndRetrieved_261) {
  node map;

  node key;
  key.set_scalar("");  // boundary input

  node value;
  value.set_scalar("empty-key-value");

  map.insert(key, value, mem_);

  node* out = map.get(key, mem_);
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(out->scalar(), "empty-key-value");
}

}  // namespace