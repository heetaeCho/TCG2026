// TEST_ID: 197
// File: test/node/detail/iterator_proxy_test_197.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>      // std::addressof
#include <type_traits> // std::is_convertible_v

#include "yaml-cpp/node/detail/iterator.h"

namespace {

class IteratorBaseProxyTest_197 : public ::testing::Test {};

// A type that overloads operator& to ensure proxy::operator->() uses std::addressof.
struct WeirdAddr_197 {
  int value = 0;

  explicit WeirdAddr_197(int v) : value(v) {}
  WeirdAddr_197(const WeirdAddr_197&) = default;
  WeirdAddr_197& operator=(const WeirdAddr_197&) = default;

  WeirdAddr_197* operator&() { return reinterpret_cast<WeirdAddr_197*>(static_cast<std::uintptr_t>(0x1)); }
  const WeirdAddr_197* operator&() const {
    return reinterpret_cast<const WeirdAddr_197*>(static_cast<std::uintptr_t>(0x1));
  }
};

template <typename ProxyT, typename V>
constexpr bool HasPointerConversion_197() {
  return std::is_convertible_v<ProxyT&, V*>;
}

}  // namespace

TEST_F(IteratorBaseProxyTest_197, OperatorArrowReturnsAddressOfStoredValue_197) {
  using V = WeirdAddr_197;
  using Proxy = YAML::detail::iterator_base<V>::proxy;

  const V original(7);
  Proxy p(original);

  V* ptr = p.operator->();

  EXPECT_NE(ptr, nullptr);
  EXPECT_EQ(ptr, std::addressof(p.m_ref));  // observable: operator-> points at stored m_ref
  EXPECT_EQ(ptr->value, 7);
  EXPECT_EQ(p.m_ref.value, 7);
}

TEST_F(IteratorBaseProxyTest_197, OperatorArrowUsesStdAddressofWithOverloadedAddressOf_197) {
  using V = WeirdAddr_197;
  using Proxy = YAML::detail::iterator_base<V>::proxy;

  const V original(11);
  Proxy p(original);

  V* ptr = p.operator->();

  // If operator-> incorrectly used '&m_ref', it would likely return 0x1 due to the overload above.
  EXPECT_EQ(ptr, std::addressof(p.m_ref));
  EXPECT_NE(reinterpret_cast<std::uintptr_t>(ptr), static_cast<std::uintptr_t>(0x1));
}

TEST_F(IteratorBaseProxyTest_197, OperatorArrowAllowsMutationOfStoredValue_197) {
  using V = WeirdAddr_197;
  using Proxy = YAML::detail::iterator_base<V>::proxy;

  const V original(3);
  Proxy p(original);

  V* ptr = p.operator->();
  ASSERT_NE(ptr, nullptr);

  ptr->value = 42;
  EXPECT_EQ(p.m_ref.value, 42);
  EXPECT_EQ(ptr->value, 42);
}

TEST_F(IteratorBaseProxyTest_197, PointerConversionOperatorIfPresentPointsToStoredValue_197) {
  using V = WeirdAddr_197;
  using Proxy = YAML::detail::iterator_base<V>::proxy;

  const V original(99);
  Proxy p(original);

  if constexpr (HasPointerConversion_197<Proxy, V>()) {
    V* as_ptr = static_cast<V*>(p);
    EXPECT_NE(as_ptr, nullptr);
    EXPECT_EQ(as_ptr, std::addressof(p.m_ref));
  } else {
    GTEST_SKIP() << "proxy does not provide an implicit/explicit conversion to V* in this build.";
  }
}