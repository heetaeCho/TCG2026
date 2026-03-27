// File: ./TestProjects/yaml-cpp/test/node_data_begin_test_648.cpp

#include <gtest/gtest.h>

#include <cstddef>

// yaml-cpp internals (node_data is in YAML::detail)
#include "yaml-cpp/node/detail/node_data.h"
#include "yaml-cpp/node/detail/node.h"
#include "yaml-cpp/node/detail/memory.h"

namespace {

class NodeDataBeginTest_648 : public ::testing::Test {
 protected:
  YAML::detail::shared_memory_holder mem_{};

  static std::size_t CountIters(YAML::detail::const_node_iterator it,
                               YAML::detail::const_node_iterator end) {
    std::size_t n = 0;
    for (; it != end; ++it) {
      ++n;
    }
    return n;
  }
};

TEST_F(NodeDataBeginTest_648, UndefinedNode_BeginEqualsEnd_648) {
  YAML::detail::node_data nd;

  const auto b = nd.begin();
  const auto e = nd.end();

  EXPECT_EQ(b, e);
  EXPECT_EQ(CountIters(b, e), 0u);
}

TEST_F(NodeDataBeginTest_648, DefinedNull_BeginEqualsEnd_648) {
  YAML::detail::node_data nd;

  // Observable behavior: for non-sequence/non-map types, begin() should be "empty".
  nd.mark_defined();
  nd.set_null();

  const auto b = nd.begin();
  const auto e = nd.end();

  EXPECT_EQ(b, e);
  EXPECT_EQ(CountIters(b, e), 0u);
}

TEST_F(NodeDataBeginTest_648, DefinedScalar_BeginEqualsEnd_648) {
  YAML::detail::node_data nd;

  nd.mark_defined();
  nd.set_scalar("hello");

  const auto b = nd.begin();
  const auto e = nd.end();

  EXPECT_EQ(b, e);
  EXPECT_EQ(CountIters(b, e), 0u);
}

TEST_F(NodeDataBeginTest_648, DefinedSequenceEmpty_BeginEqualsEnd_648) {
  YAML::detail::node_data nd;

  nd.mark_defined();
  nd.set_type(YAML::NodeType::Sequence);

  const auto b = nd.begin();
  const auto e = nd.end();

  EXPECT_EQ(b, e);
  EXPECT_EQ(CountIters(b, e), 0u);
}

TEST_F(NodeDataBeginTest_648, DefinedSequenceNonEmpty_BeginNotEqualEndAndCountsElements_648) {
  YAML::detail::node_data nd;

  nd.mark_defined();
  nd.set_type(YAML::NodeType::Sequence);

  YAML::detail::node n1(mem_);
  YAML::detail::node n2(mem_);
  nd.push_back(n1, mem_);
  nd.push_back(n2, mem_);

  const auto b = nd.begin();
  const auto e = nd.end();

  EXPECT_NE(b, e);
  EXPECT_EQ(CountIters(b, e), 2u);
}

TEST_F(NodeDataBeginTest_648, DefinedMapEmpty_BeginEqualsEnd_648) {
  YAML::detail::node_data nd;

  nd.mark_defined();
  nd.set_type(YAML::NodeType::Map);

  const auto b = nd.begin();
  const auto e = nd.end();

  EXPECT_EQ(b, e);
  EXPECT_EQ(CountIters(b, e), 0u);
}

TEST_F(NodeDataBeginTest_648, DefinedMapNonEmpty_BeginNotEqualEndAndCountsPairs_648) {
  YAML::detail::node_data nd;

  nd.mark_defined();
  nd.set_type(YAML::NodeType::Map);

  YAML::detail::node k1(mem_);
  YAML::detail::node v1(mem_);
  YAML::detail::node k2(mem_);
  YAML::detail::node v2(mem_);

  nd.insert(k1, v1, mem_);
  nd.insert(k2, v2, mem_);

  const auto b = nd.begin();
  const auto e = nd.end();

  EXPECT_NE(b, e);
  EXPECT_EQ(CountIters(b, e), 2u);
}

TEST_F(NodeDataBeginTest_648, DefinedButNonContainerType_BeginEqualsEnd_648) {
  YAML::detail::node_data nd;

  nd.mark_defined();
  nd.set_type(YAML::NodeType::Sequence);

  YAML::detail::node n(mem_);
  nd.push_back(n, mem_);

  // Switch to a non-container type; begin() should no longer expose iteration.
  nd.set_scalar("now scalar");

  const auto b = nd.begin();
  const auto e = nd.end();

  EXPECT_EQ(b, e);
  EXPECT_EQ(CountIters(b, e), 0u);
}

}  // namespace