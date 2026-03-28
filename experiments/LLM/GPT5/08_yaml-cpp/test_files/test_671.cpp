// TEST_ID: 671
//
// Unit tests for YAML::detail::node_data::force_insert
//
// Notes:
// - These tests treat node_data as a black box and only assert observable behavior
//   through the public interface (type(), size(), get(), remove(), and exceptions).
// - We intentionally avoid depending on any private/internal state or re-implementing logic.

#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/impl.h"  // for inline force_insert definition (if needed by build)

namespace {

using YAML::detail::node_data;
using YAML::detail::shared_memory_holder;

class NodeDataForceInsertTest_671 : public ::testing::Test {
 protected:
  shared_memory_holder mem_;  // Default-constructed holder is used as an opaque token.

  template <typename Key>
  const YAML::detail::node* GetNode(const node_data& nd, const Key& key) {
    // node_data::get is templated and returns a node pointer (or null if not found)
    return nd.get(key, mem_);
  }

  template <typename Key>
  bool RemoveKey(node_data& nd, const Key& key) {
    return nd.remove(key, mem_);
  }
};

TEST_F(NodeDataForceInsertTest_671, ForceInsertFromNullConvertsToMapAndInserts_671) {
  node_data nd;
  nd.set_null();
  EXPECT_EQ(nd.type(), YAML::NodeType::Null);

  EXPECT_NO_THROW(nd.force_insert("k1", "v1", mem_));

  EXPECT_EQ(nd.type(), YAML::NodeType::Map);
  EXPECT_NE(GetNode(nd, "k1"), nullptr);
  EXPECT_TRUE(RemoveKey(nd, "k1"));
  EXPECT_EQ(GetNode(nd, "k1"), nullptr);
}

TEST_F(NodeDataForceInsertTest_671, ForceInsertFromUndefinedConvertsToMapAndInserts_671) {
  node_data nd;
  nd.set_type(YAML::NodeType::Undefined);
  EXPECT_EQ(nd.type(), YAML::NodeType::Undefined);

  EXPECT_NO_THROW(nd.force_insert("k1", "v1", mem_));

  EXPECT_EQ(nd.type(), YAML::NodeType::Map);
  EXPECT_NE(GetNode(nd, "k1"), nullptr);
}

TEST_F(NodeDataForceInsertTest_671, ForceInsertFromSequenceConvertsToMapAndInserts_671) {
  node_data nd;
  nd.set_type(YAML::NodeType::Sequence);
  EXPECT_EQ(nd.type(), YAML::NodeType::Sequence);

  EXPECT_NO_THROW(nd.force_insert("k1", "v1", mem_));

  EXPECT_EQ(nd.type(), YAML::NodeType::Map);
  EXPECT_NE(GetNode(nd, "k1"), nullptr);
}

TEST_F(NodeDataForceInsertTest_671, ForceInsertIntoExistingMapInsertsMultipleDistinctKeys_671) {
  node_data nd;
  nd.set_type(YAML::NodeType::Map);
  EXPECT_EQ(nd.type(), YAML::NodeType::Map);

  EXPECT_NO_THROW(nd.force_insert("k1", "v1", mem_));
  EXPECT_NO_THROW(nd.force_insert("k2", "v2", mem_));

  EXPECT_NE(GetNode(nd, "k1"), nullptr);
  EXPECT_NE(GetNode(nd, "k2"), nullptr);

  // Removing should succeed for inserted keys.
  EXPECT_TRUE(RemoveKey(nd, "k1"));
  EXPECT_TRUE(RemoveKey(nd, "k2"));
  EXPECT_EQ(GetNode(nd, "k1"), nullptr);
  EXPECT_EQ(GetNode(nd, "k2"), nullptr);
}

TEST_F(NodeDataForceInsertTest_671, ForceInsertThrowsBadInsertWhenScalar_671) {
  node_data nd;
  nd.set_scalar("already-a-scalar");
  ASSERT_EQ(nd.type(), YAML::NodeType::Scalar);

  EXPECT_THROW(nd.force_insert("k1", "v1", mem_), YAML::BadInsert);

  // Observable post-condition: still scalar (no mutation asserted beyond observable type).
  EXPECT_EQ(nd.type(), YAML::NodeType::Scalar);
}

TEST_F(NodeDataForceInsertTest_671, ForceInsertAcceptsNonStringKeyType_671) {
  node_data nd;
  nd.set_null();

  // Key is an int; value is a string.
  EXPECT_NO_THROW(nd.force_insert(42, "answer", mem_));

  EXPECT_EQ(nd.type(), YAML::NodeType::Map);
  EXPECT_NE(GetNode(nd, 42), nullptr);
}

TEST_F(NodeDataForceInsertTest_671, ForceInsertAcceptsEmptyStringKeyAndValue_671) {
  node_data nd;
  nd.set_null();

  EXPECT_NO_THROW(nd.force_insert(std::string(""), std::string(""), mem_));

  EXPECT_EQ(nd.type(), YAML::NodeType::Map);
  EXPECT_NE(GetNode(nd, std::string("")), nullptr);
}

TEST_F(NodeDataForceInsertTest_671, ForceInsertThenRemoveReturnsFalseOnSecondRemove_671) {
  node_data nd;
  nd.set_null();

  EXPECT_NO_THROW(nd.force_insert("k1", "v1", mem_));
  EXPECT_TRUE(RemoveKey(nd, "k1"));

  // Boundary / error-ish observable behavior: removing again should fail (key no longer present).
  EXPECT_FALSE(RemoveKey(nd, "k1"));
  EXPECT_EQ(GetNode(nd, "k1"), nullptr);
}

}  // namespace