// TEST_ID: 233
#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_ref.h"

namespace {

using YAML::detail::node;
using YAML::detail::node_ref;
using YAML::detail::shared_memory_holder;

class NodeRefRemoveNodeTest_233 : public ::testing::Test {
protected:
  shared_memory_holder mem_{};
};

TEST_F(NodeRefRemoveNodeTest_233, RemoveFromEmptyReturnsFalse_233) {
  node_ref ref;

  node key;
  key.set_scalar("k");

  EXPECT_FALSE(ref.remove(key, mem_));
}

TEST_F(NodeRefRemoveNodeTest_233, RemoveExistingKeyReturnsTrueAndErases_233) {
  node_ref ref;

  node key;
  key.set_scalar("k");
  node value;
  value.set_scalar("v");

  ref.insert(key, value, mem_);

  // Sanity: key is present before removal (observable via get()).
  ASSERT_NE(ref.get(key, mem_), nullptr);

  EXPECT_TRUE(ref.remove(key, mem_));

  // After removal, key should no longer be present.
  EXPECT_EQ(ref.get(key, mem_), nullptr);
}

TEST_F(NodeRefRemoveNodeTest_233, RemovingSameKeyTwiceSecondTimeReturnsFalse_233) {
  node_ref ref;

  node key;
  key.set_scalar("k");
  node value;
  value.set_scalar("v");

  ref.insert(key, value, mem_);

  ASSERT_TRUE(ref.remove(key, mem_));
  EXPECT_FALSE(ref.remove(key, mem_));
}

TEST_F(NodeRefRemoveNodeTest_233, RemoveWithDefaultConstructedKeyDoesNotThrow_233) {
  node_ref ref;

  node key;  // default-constructed (no scalar set)
  EXPECT_NO_THROW({
    (void)ref.remove(key, mem_);
  });
}

}  // namespace