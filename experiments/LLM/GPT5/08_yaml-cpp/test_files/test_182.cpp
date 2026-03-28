// TEST_ID: 182
#include <gtest/gtest.h>

#include <memory>   // std::addressof
#include <yaml-cpp/yaml.h>

#include "yaml-cpp/node/detail/node_iterator.h"

namespace {

using V182 = YAML::Node;
using Value182 = YAML::detail::node_iterator_value<V182>;
using Proxy182 = YAML::detail::node_iterator_base<V182>::proxy;

class NodeIteratorProxyTest_182 : public ::testing::Test {
protected:
  static Value182 MakeValueFromMap() {
    // Create a real iterator value from observable public API (YAML::Node iteration).
    const YAML::Node n = YAML::Load("{a: 1}");
    auto it = n.begin();
    return *it;
  }
};

TEST_F(NodeIteratorProxyTest_182, ConversionOperatorReturnsAddressOfMember_182) {
  const Value182 v = MakeValueFromMap();
  Proxy182 p(v);

  Value182* ptr = static_cast<Value182*>(p);

  ASSERT_NE(ptr, nullptr);
  EXPECT_EQ(ptr, std::addressof(p.m_ref));
}

TEST_F(NodeIteratorProxyTest_182, ConversionOperatorIsStableAcrossCalls_182) {
  const Value182 v = MakeValueFromMap();
  Proxy182 p(v);

  Value182* p1 = static_cast<Value182*>(p);
  Value182* p2 = static_cast<Value182*>(p);

  ASSERT_NE(p1, nullptr);
  ASSERT_NE(p2, nullptr);
  EXPECT_EQ(p1, p2);
  EXPECT_EQ(p1, std::addressof(p.m_ref));
}

TEST_F(NodeIteratorProxyTest_182, ArrowOperatorMatchesConversionOperator_182) {
  const Value182 v = MakeValueFromMap();
  Proxy182 p(v);

  Value182* arrow_ptr = p.operator->();
  Value182* conv_ptr = static_cast<Value182*>(p);

  ASSERT_NE(arrow_ptr, nullptr);
  ASSERT_NE(conv_ptr, nullptr);
  EXPECT_EQ(arrow_ptr, conv_ptr);
  EXPECT_EQ(arrow_ptr, std::addressof(p.m_ref));
}

}  // namespace