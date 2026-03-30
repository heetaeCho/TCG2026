// TEST_ID: 647
//
// Unit tests for YAML::detail::node_data::size() (black-box)
// Focus: observable behavior via public interface only.

#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

namespace {

using YAML::detail::node;
using YAML::detail::node_data;
using YAML::detail::shared_memory_holder;

shared_memory_holder MakeMemory_647() {
  return std::make_shared<YAML::detail::memory_holder>();
}

node MakeNode_647(const shared_memory_holder& mem) {
  return node(mem);
}

class NodeDataSizeTest_647 : public ::testing::Test {
 protected:
  shared_memory_holder mem_ = MakeMemory_647();
};

}  // namespace

TEST_F(NodeDataSizeTest_647, DefaultConstructedNotDefinedReturnsZero_647) {
  node_data d;

  EXPECT_NO_THROW({
    const std::size_t s = d.size();
    EXPECT_EQ(s, 0u);
  });
}

TEST_F(NodeDataSizeTest_647, MarkDefinedButNullTypeReturnsZero_647) {
  node_data d;

  d.mark_defined();
  d.set_type(YAML::NodeType::Null);

  EXPECT_NO_THROW({
    const std::size_t s = d.size();
    EXPECT_EQ(s, 0u);
  });
}

TEST_F(NodeDataSizeTest_647, MarkDefinedButScalarTypeReturnsZero_647) {
  node_data d;

  d.mark_defined();
  d.set_type(YAML::NodeType::Scalar);
  d.set_scalar("hello");

  EXPECT_NO_THROW({
    const std::size_t s = d.size();
    EXPECT_EQ(s, 0u);
  });
}

TEST_F(NodeDataSizeTest_647, SequenceTypeEmptyReturnsZero_647) {
  node_data d;

  d.mark_defined();
  d.set_type(YAML::NodeType::Sequence);

  EXPECT_NO_THROW({
    const std::size_t s = d.size();
    EXPECT_EQ(s, 0u);
  });
}

TEST_F(NodeDataSizeTest_647, SequenceTypePushBackIncreasesSize_647) {
  node_data d;

  d.mark_defined();
  d.set_type(YAML::NodeType::Sequence);

  node n1 = MakeNode_647(mem_);
  node n2 = MakeNode_647(mem_);

  EXPECT_NO_THROW({
    d.push_back(n1, mem_);
    EXPECT_EQ(d.size(), 1u);

    d.push_back(n2, mem_);
    EXPECT_EQ(d.size(), 2u);
  });

  // Re-check multiple times (should be stable / not statefully degrade).
  EXPECT_NO_THROW({
    EXPECT_EQ(d.size(), 2u);
    EXPECT_EQ(d.size(), 2u);
  });
}

TEST_F(NodeDataSizeTest_647, MapTypeEmptyReturnsZero_647) {
  node_data d;

  d.mark_defined();
  d.set_type(YAML::NodeType::Map);

  EXPECT_NO_THROW({
    const std::size_t s = d.size();
    EXPECT_EQ(s, 0u);
  });
}

TEST_F(NodeDataSizeTest_647, MapTypeInsertIncreasesSizeAndRemoveDecreases_647) {
  node_data d;

  d.mark_defined();
  d.set_type(YAML::NodeType::Map);

  node key1 = MakeNode_647(mem_);
  node val1 = MakeNode_647(mem_);
  key1.mark_defined();
  key1.set_type(YAML::NodeType::Scalar);
  key1.set_scalar("k1");
  val1.mark_defined();
  val1.set_type(YAML::NodeType::Scalar);
  val1.set_scalar("v1");

  node key2 = MakeNode_647(mem_);
  node val2 = MakeNode_647(mem_);
  key2.mark_defined();
  key2.set_type(YAML::NodeType::Scalar);
  key2.set_scalar("k2");
  val2.mark_defined();
  val2.set_type(YAML::NodeType::Scalar);
  val2.set_scalar("v2");

  EXPECT_NO_THROW({
    d.insert(key1, val1, mem_);
    EXPECT_EQ(d.size(), 1u);

    d.insert(key2, val2, mem_);
    EXPECT_EQ(d.size(), 2u);
  });

  // Removing existing key should be observable via size change if removal succeeds.
  bool removed1 = false;
  EXPECT_NO_THROW({ removed1 = d.remove(key1, mem_); });
  if (removed1) {
    EXPECT_EQ(d.size(), 1u);
  }

  // Removing the same key again should not increase size; if it reports success,
  // size should not increase either.
  bool removed_again = false;
  EXPECT_NO_THROW({ removed_again = d.remove(key1, mem_); });
  (void)removed_again;

  EXPECT_NO_THROW({ EXPECT_LE(d.size(), 1u); });
}

TEST_F(NodeDataSizeTest_647, NotDefinedAlwaysReturnsZeroEvenIfTypeSet_647) {
  node_data d;

  // Intentionally do NOT call mark_defined().
  d.set_type(YAML::NodeType::Sequence);

  node n = MakeNode_647(mem_);

  EXPECT_NO_THROW({
    d.push_back(n, mem_);
    EXPECT_EQ(d.size(), 0u);
  });

  d.set_type(YAML::NodeType::Map);

  node k = MakeNode_647(mem_);
  node v = MakeNode_647(mem_);
  k.mark_defined();
  k.set_type(YAML::NodeType::Scalar);
  k.set_scalar("k");
  v.mark_defined();
  v.set_type(YAML::NodeType::Scalar);
  v.set_scalar("v");

  EXPECT_NO_THROW({
    d.insert(k, v, mem_);
    EXPECT_EQ(d.size(), 0u);
  });
}