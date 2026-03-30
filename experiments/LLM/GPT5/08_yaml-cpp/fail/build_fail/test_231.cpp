// TEST_ID: 231
#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/node/detail/node_ref.h"

namespace {

using YAML::detail::node_ref;
using YAML::detail::shared_memory_holder;
using YAML::NodeType;

class NodeRefRemoveTest_231 : public ::testing::Test {
 protected:
  shared_memory_holder mem_{};

  static node_ref MakeMapRef(shared_memory_holder mem) {
    node_ref r;
    r.mark_defined();
    r.set_type(NodeType::Map);

    // Sanity: ensure we can insert through the public interface.
    r.force_insert("k1", "v1", mem);
    r.force_insert("k2", "v2", mem);
    r.force_insert("k3", "v3", mem);
    return r;
  }
};

TEST_F(NodeRefRemoveTest_231, RemoveExistingKey_ReturnsTrueAndErases_231) {
  node_ref r;
  r.mark_defined();
  r.set_type(NodeType::Map);

  r.force_insert("alpha", "1", mem_);
  ASSERT_EQ(r.size(), 1u);
  ASSERT_NE(r.get("alpha", mem_), nullptr);

  const bool removed = r.remove(std::string("alpha"), mem_);
  EXPECT_TRUE(removed);
  EXPECT_EQ(r.size(), 0u);
  EXPECT_EQ(r.get("alpha", mem_), nullptr);
}

TEST_F(NodeRefRemoveTest_231, RemoveMissingKey_ReturnsFalseAndNoChange_231) {
  node_ref r;
  r.mark_defined();
  r.set_type(NodeType::Map);

  r.force_insert("present", "42", mem_);
  ASSERT_EQ(r.size(), 1u);
  ASSERT_NE(r.get("present", mem_), nullptr);
  ASSERT_EQ(r.get("absent", mem_), nullptr);

  const bool removed = r.remove(std::string("absent"), mem_);
  EXPECT_FALSE(removed);

  // Observable: size and existing key remain unchanged.
  EXPECT_EQ(r.size(), 1u);
  EXPECT_NE(r.get("present", mem_), nullptr);
  EXPECT_EQ(r.get("absent", mem_), nullptr);
}

TEST_F(NodeRefRemoveTest_231, RemoveFromEmptyMap_ReturnsFalse_231) {
  node_ref r;
  r.mark_defined();
  r.set_type(NodeType::Map);

  ASSERT_EQ(r.size(), 0u);
  EXPECT_FALSE(r.remove(std::string("nope"), mem_));
  EXPECT_EQ(r.size(), 0u);
}

TEST_F(NodeRefRemoveTest_231, RemoveAcceptsConstCharKey_231) {
  node_ref r;
  r.mark_defined();
  r.set_type(NodeType::Map);

  r.force_insert("c_key", "c_val", mem_);
  ASSERT_EQ(r.size(), 1u);
  ASSERT_NE(r.get("c_key", mem_), nullptr);

  // Template Key = const char*
  const bool removed = r.remove("c_key", mem_);
  EXPECT_TRUE(removed);
  EXPECT_EQ(r.size(), 0u);
  EXPECT_EQ(r.get("c_key", mem_), nullptr);
}

TEST_F(NodeRefRemoveTest_231, RemoveOneOfMany_DecreasesSizeAndKeepsOthers_231) {
  node_ref r = MakeMapRef(mem_);
  ASSERT_EQ(r.size(), 3u);

  ASSERT_NE(r.get("k1", mem_), nullptr);
  ASSERT_NE(r.get("k2", mem_), nullptr);
  ASSERT_NE(r.get("k3", mem_), nullptr);

  const bool removed = r.remove(std::string("k2"), mem_);
  EXPECT_TRUE(removed);

  EXPECT_EQ(r.size(), 2u);
  EXPECT_NE(r.get("k1", mem_), nullptr);
  EXPECT_EQ(r.get("k2", mem_), nullptr);
  EXPECT_NE(r.get("k3", mem_), nullptr);
}

}  // namespace