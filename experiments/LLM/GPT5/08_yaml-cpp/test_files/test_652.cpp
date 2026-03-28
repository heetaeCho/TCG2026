// TEST_ID: 652
#include <gtest/gtest.h>

#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/memory.h"

namespace YAML {
namespace detail {

class NodeDataGetTest_652 : public ::testing::Test {
 protected:
  shared_memory_holder MakeMemory_652() { return shared_memory_holder(new memory_holder); }

  node MakeScalarNode_652(const std::string& s) {
    node n;
    n.set_scalar(s);
    return n;
  }
};

TEST_F(NodeDataGetTest_652, InsertsNewPairWhenKeyMissingInMap_652) {
  node_data nd;
  nd.set_type(NodeType::Map);

  auto mem = MakeMemory_652();
  node key = MakeScalarNode_652("k1");

  EXPECT_EQ(nd.size(), 0u);

  node& v1 = nd.get(key, mem);

  EXPECT_EQ(nd.size(), 1u);

  // Same key should retrieve the same value node (no duplicate insertion).
  node& v2 = nd.get(key, mem);
  EXPECT_EQ(&v1, &v2);
  EXPECT_EQ(nd.size(), 1u);
}

TEST_F(NodeDataGetTest_652, InsertsDistinctValuesForDifferentKeys_652) {
  node_data nd;
  nd.set_type(NodeType::Map);

  auto mem = MakeMemory_652();
  node key1 = MakeScalarNode_652("k1");
  node key2 = MakeScalarNode_652("k2");

  node& v1 = nd.get(key1, mem);
  node& v2 = nd.get(key2, mem);

  EXPECT_EQ(nd.size(), 2u);
  EXPECT_NE(&v1, &v2);

  // Re-accessing each key should return the same corresponding value node.
  EXPECT_EQ(&v1, &nd.get(key1, mem));
  EXPECT_EQ(&v2, &nd.get(key2, mem));
  EXPECT_EQ(nd.size(), 2u);
}

TEST_F(NodeDataGetTest_652, ConvertsNullToMapAndInsertsOnGet_652) {
  node_data nd;  // default is observable as Null in yaml-cpp
  auto mem = MakeMemory_652();
  node key = MakeScalarNode_652("k");

  // Should not throw; should behave like a map after the call.
  node& value = nd.get(key, mem);

  (void)value;
  EXPECT_EQ(nd.type(), NodeType::Map);
  EXPECT_EQ(nd.size(), 1u);
}

TEST_F(NodeDataGetTest_652, ConvertsUndefinedToMapAndInsertsOnGet_652) {
  node_data nd;
  nd.set_type(NodeType::Undefined);

  auto mem = MakeMemory_652();
  node key = MakeScalarNode_652("k");

  node& value = nd.get(key, mem);

  (void)value;
  EXPECT_EQ(nd.type(), NodeType::Map);
  EXPECT_EQ(nd.size(), 1u);
}

TEST_F(NodeDataGetTest_652, ConvertsSequenceToMapAndInsertsOnGet_652) {
  node_data nd;
  nd.set_type(NodeType::Sequence);

  auto mem = MakeMemory_652();
  node key = MakeScalarNode_652("k");

  node& value = nd.get(key, mem);

  (void)value;
  EXPECT_EQ(nd.type(), NodeType::Map);
  EXPECT_EQ(nd.size(), 1u);
}

TEST_F(NodeDataGetTest_652, ThrowsBadSubscriptWhenScalar_652) {
  node_data nd;
  nd.set_type(NodeType::Scalar);

  auto mem = MakeMemory_652();
  node key = MakeScalarNode_652("k");

  EXPECT_THROW(
      {
        // NOLINTNEXTLINE(bugprone-unused-raii)
        nd.get(key, mem);
      },
      BadSubscript);
}

}  // namespace detail
}  // namespace YAML