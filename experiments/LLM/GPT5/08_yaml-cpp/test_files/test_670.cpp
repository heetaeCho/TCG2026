// TEST_ID: 670
//
// Unit tests for YAML::detail::node_data::remove(const Key&, shared_memory_holder)
//
// Constraints respected:
// - Treat implementation as black box (no assumptions about internals)
// - Verify only via public interface: set_type, size, get, remove, force_insert
// - No private state access

#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node_data.h"

namespace {

using YAML::detail::node_data;
using YAML::detail::shared_memory_holder;
using YAML::NodeType;

class NodeDataRemoveTemplateTest_670 : public ::testing::Test {
protected:
  shared_memory_holder mem_{};

  node_data Make(NodeType::value t) {
    node_data d;
    d.set_type(t);
    return d;
  }
};

TEST_F(NodeDataRemoveTemplateTest_670, RemoveFromNullNodeReturnsFalse_670) {
  node_data d;  // default-constructed per header indicates NodeType::Null
  const std::size_t before = d.size();

  EXPECT_FALSE(d.remove(std::string("any-key"), mem_));
  EXPECT_EQ(d.size(), before);
}

TEST_F(NodeDataRemoveTemplateTest_670, RemoveFromEmptySequenceReturnsFalse_670) {
  node_data d = Make(NodeType::Sequence);
  const std::size_t before = d.size();

  EXPECT_FALSE(d.remove(std::size_t{0}, mem_));
  EXPECT_EQ(d.size(), before);
}

TEST_F(NodeDataRemoveTemplateTest_670, RemoveFromEmptyMapReturnsFalse_670) {
  node_data d = Make(NodeType::Map);
  const std::size_t before = d.size();

  EXPECT_FALSE(d.remove(std::string("missing"), mem_));
  EXPECT_EQ(d.size(), before);
}

TEST_F(NodeDataRemoveTemplateTest_670, RemoveExistingKeyFromMapReturnsTrueAndErases_670) {
  node_data d = Make(NodeType::Map);

  // Use only public API to populate:
  d.force_insert<std::string, int>("k1", 11, mem_);
  d.force_insert<std::string, int>("k2", 22, mem_);

  const std::size_t before = d.size();
  ASSERT_GE(before, 2u);

  // Sanity: get should find existing keys before removal.
  EXPECT_NE(d.get(std::string("k1"), mem_), nullptr);
  EXPECT_NE(d.get(std::string("k2"), mem_), nullptr);

  EXPECT_TRUE(d.remove(std::string("k1"), mem_));
  EXPECT_EQ(d.get(std::string("k1"), mem_), nullptr);

  // Other entries should remain.
  EXPECT_NE(d.get(std::string("k2"), mem_), nullptr);

  // Observable size should not increase.
  EXPECT_LE(d.size(), before);
}

TEST_F(NodeDataRemoveTemplateTest_670, RemoveNonExistingKeyFromMapReturnsFalseAndDoesNotIncreaseSize_670) {
  node_data d = Make(NodeType::Map);

  d.force_insert<std::string, int>("present", 1, mem_);
  const std::size_t before = d.size();
  ASSERT_GE(before, 1u);

  EXPECT_FALSE(d.remove(std::string("absent"), mem_));

  // Existing key should still be retrievable.
  EXPECT_NE(d.get(std::string("present"), mem_), nullptr);

  // Size should not increase as a result of remove.
  EXPECT_LE(d.size(), before);
}

TEST_F(NodeDataRemoveTemplateTest_670, RemoveAcceptsDifferentKeyTypeForSameLogicalKey_670) {
  node_data d = Make(NodeType::Map);

  d.force_insert<std::string, int>("alpha", 123, mem_);
  ASSERT_NE(d.get(std::string("alpha"), mem_), nullptr);

  // Remove using a different Key type (const char*), still only checking observable behavior.
  EXPECT_TRUE(d.remove("alpha", mem_));
  EXPECT_EQ(d.get(std::string("alpha"), mem_), nullptr);

  // Removing again should be a no-op / false (key already gone).
  EXPECT_FALSE(d.remove("alpha", mem_));
}

}  // namespace