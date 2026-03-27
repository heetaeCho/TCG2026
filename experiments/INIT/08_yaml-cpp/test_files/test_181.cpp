// TEST_ID: 181
// File: test/node/detail/node_iterator_proxy_test.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <memory>   // std::addressof

#include "yaml-cpp/node/detail/node_iterator.h"

namespace {

template <typename ProxyT, typename ValueT>
constexpr bool kHasPointerConversion =
    std::is_convertible_v<ProxyT, ValueT*> || std::is_convertible_v<ProxyT&, ValueT*>;

}  // namespace

TEST(NodeIteratorProxyTest_181, OperatorArrowReturnsAddressOfStoredRef_181) {
  using V = YAML::Node;
  using Base = YAML::detail::node_iterator_base<V>;
  using Proxy = typename Base::proxy;
  using Value = YAML::detail::node_iterator_value<V>;

  Value value{};         // relies only on public/default construction if available
  Proxy proxy(value);    // uses the provided public ctor

  Value* p = proxy.operator->();
  EXPECT_NE(p, nullptr);
  EXPECT_EQ(p, std::addressof(proxy.m_ref));
}

TEST(NodeIteratorProxyTest_181, OperatorArrowIsStableAcrossMultipleCalls_181) {
  using V = YAML::Node;
  using Base = YAML::detail::node_iterator_base<V>;
  using Proxy = typename Base::proxy;
  using Value = YAML::detail::node_iterator_value<V>;

  Value value{};
  Proxy proxy(value);

  Value* p1 = proxy.operator->();
  Value* p2 = proxy.operator->();
  EXPECT_EQ(p1, p2);
  EXPECT_EQ(p1, std::addressof(proxy.m_ref));
}

TEST(NodeIteratorProxyTest_181, ConversionOperatorMatchesOperatorArrowWhenPresent_181) {
  using V = YAML::Node;
  using Base = YAML::detail::node_iterator_base<V>;
  using Proxy = typename Base::proxy;
  using Value = YAML::detail::node_iterator_value<V>;

  Value value{};
  Proxy proxy(value);

  // The interface shows an optional `operator node_iterator_value<V>*();`
  // This test only asserts behavior if that conversion is actually available.
  if constexpr (kHasPointerConversion<Proxy, Value>) {
    Value* p_arrow = proxy.operator->();
    Value* p_conv = static_cast<Value*>(proxy);
    EXPECT_EQ(p_conv, p_arrow);
    EXPECT_EQ(p_conv, std::addressof(proxy.m_ref));
  } else {
    GTEST_SKIP() << "proxy is not convertible to node_iterator_value<V>* in this build.";
  }
}