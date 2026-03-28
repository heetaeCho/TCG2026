#include <gtest/gtest.h>

#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/ptr.h"

namespace {

using YAML::detail::node_data;
using YAML::detail::shared_memory_holder;
using YAML::Node;
using YAML::NodeType;

// Helper: allocate a YAML::detail::node on heap so node& is valid.
static YAML::detail::node& NewDetailNode() {
  return *new YAML::detail::node();
}

// Helper: create a YAML::Node “key” that wraps a given detail::node*.
static Node MakePublicNodeFromDetail(YAML::detail::node* p) {
  // yaml-cpp's Node has a constructor (node*, shared_memory_holder).
  // This is part of yaml-cpp's internal/public boundary and is used by
  // tests elsewhere in this codebase; we rely only on observable behavior.
  return Node(p, shared_memory_holder());
}

// Helper: create a map entry (key node*, value node*) with given scalars.
static std::pair<YAML::detail::node*, YAML::detail::node*> MakeMapPair(
    const std::string& key_scalar, const std::string& value_scalar) {
  auto* k = new YAML::detail::node();
  auto* v = new YAML::detail::node();

  k->set_scalar(key_scalar);
  v->set_scalar(value_scalar);

  return {k, v};
}

class NodeDataGetTest_651 : public ::testing::Test {
 protected:
  node_data data_;
  shared_memory_holder mem_;
};

TEST_F(NodeDataGetTest_651, ReturnsNullWhenNotMap_651) {
  // node_data defaults to some type (often Null/Undefined). Regardless, if not
  // a Map, get() must return nullptr.
  auto& key_detail = NewDetailNode();
  Node key = MakePublicNodeFromDetail(&key_detail);

  EXPECT_EQ(nullptr, data_.get(key_detail, mem_));

  delete &key_detail;
  (void)key;  // suppress unused warnings in case Node isn't used by build flags
}

TEST_F(NodeDataGetTest_651, ReturnsNullForMapWithNoEntries_651) {
  data_.set_type(NodeType::Map);

  auto& key_detail = NewDetailNode();
  Node key = MakePublicNodeFromDetail(&key_detail);

  EXPECT_EQ(nullptr, data_.get(key_detail, mem_));

  delete &key_detail;
  (void)key;
}

TEST_F(NodeDataGetTest_651, ReturnsNullWhenKeyNotFound_651) {
  data_.set_type(NodeType::Map);

  // Add one entry under key "a"
  auto pair1 = MakeMapPair("a", "value-a");
  data_.insert_map(pair1.first, pair1.second);

  // Search for a different key "b"
  auto& key_detail = NewDetailNode();
  key_detail.set_scalar("b");
  Node key = MakePublicNodeFromDetail(&key_detail);

  EXPECT_EQ(nullptr, data_.get(key_detail, mem_));

  delete &key_detail;
  // cleanup map nodes we created
  delete pair1.first;
  delete pair1.second;
  (void)key;
}

TEST_F(NodeDataGetTest_651, ReturnsValueNodePointerWhenKeyMatches_651) {
  data_.set_type(NodeType::Map);

  auto pair1 = MakeMapPair("k1", "v1");
  auto pair2 = MakeMapPair("k2", "v2");
  data_.insert_map(pair1.first, pair1.second);
  data_.insert_map(pair2.first, pair2.second);

  // Build a search key that should match "k2"
  auto& key_detail = NewDetailNode();
  key_detail.set_scalar("k2");
  Node key = MakePublicNodeFromDetail(&key_detail);

  YAML::detail::node* found = data_.get(key_detail, mem_);
  ASSERT_NE(nullptr, found);

  // Observable check: the found node should represent scalar "v2"
  Node found_public = MakePublicNodeFromDetail(found);
  EXPECT_TRUE(found_public.IsScalar());
  EXPECT_EQ("v2", found_public.Scalar());

  delete &key_detail;
  delete pair1.first;
  delete pair1.second;
  delete pair2.first;
  delete pair2.second;
  (void)key;
}

TEST_F(NodeDataGetTest_651, ReturnsFirstMatchingValueIfDuplicateKeysExist_651) {
  data_.set_type(NodeType::Map);

  // Insert duplicate keys "dup" with different values, in order.
  auto first = MakeMapPair("dup", "first");
  auto second = MakeMapPair("dup", "second");
  data_.insert_map(first.first, first.second);
  data_.insert_map(second.first, second.second);

  auto& key_detail = NewDetailNode();
  key_detail.set_scalar("dup");
  Node key = MakePublicNodeFromDetail(&key_detail);

  YAML::detail::node* found = data_.get(key_detail, mem_);
  ASSERT_NE(nullptr, found);

  Node found_public = MakePublicNodeFromDetail(found);
  EXPECT_TRUE(found_public.IsScalar());
  EXPECT_EQ("first", found_public.Scalar());

  delete &key_detail;
  delete first.first;
  delete first.second;
  delete second.first;
  delete second.second;
  (void)key;
}

TEST_F(NodeDataGetTest_651, HandlesNonScalarKeyComparisonAndNotFound_651) {
  data_.set_type(NodeType::Map);

  // Insert scalar key "s"
  auto pair1 = MakeMapPair("s", "vs");
  data_.insert_map(pair1.first, pair1.second);

  // Search with a non-scalar key node (e.g., a sequence)
  auto& key_detail = NewDetailNode();
  key_detail.set_type(NodeType::Sequence);
  Node key = MakePublicNodeFromDetail(&key_detail);

  // We only assert it doesn't crash and returns nullptr (observable).
  EXPECT_EQ(nullptr, data_.get(key_detail, mem_));

  delete &key_detail;
  delete pair1.first;
  delete pair1.second;
  (void)key;
}

}  // namespace