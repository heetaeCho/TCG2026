// TEST_ID: 198
#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "yaml-cpp/node/detail/iterator.h"

namespace {

template <typename V>
using ProxyT = typename YAML::detail::iterator_base<V>::proxy;

struct OverloadedAddress {
  int value{0};
  explicit OverloadedAddress(int v = 0) : value(v) {}

  // Deliberately "wrong" address operator to ensure std::addressof is used.
  OverloadedAddress* operator&() { return reinterpret_cast<OverloadedAddress*>(0x1234); }
  const OverloadedAddress* operator&() const {
    return reinterpret_cast<const OverloadedAddress*>(0x1234);
  }
};

}  // namespace

class IteratorProxyTest_198 : public ::testing::Test {};

TEST_F(IteratorProxyTest_198, ConversionReturnsPointerToInternalRef_Int_198) {
  ProxyT<int> p(7);

  int* ptr = p;  // proxy::operator V*()

  EXPECT_EQ(ptr, std::addressof(p.m_ref));
  EXPECT_EQ(*ptr, 7);
}

TEST_F(IteratorProxyTest_198, ConversionPointerAllowsMutation_198) {
  ProxyT<int> p(1);

  int* ptr = p;
  *ptr = 42;

  EXPECT_EQ(p.m_ref, 42);
}

TEST_F(IteratorProxyTest_198, ConversionIsStableAcrossMultipleCalls_198) {
  ProxyT<std::string> p(std::string("hello"));

  std::string* p1 = p;
  std::string* p2 = p;

  EXPECT_EQ(p1, p2);
  EXPECT_EQ(p1, std::addressof(p.m_ref));
  EXPECT_EQ(*p1, "hello");
}

TEST_F(IteratorProxyTest_198, UsesStdAddressofWhenOperatorAddressIsOverloaded_198) {
  ProxyT<OverloadedAddress> p(OverloadedAddress{9});

  OverloadedAddress* ptr = p;

  // If proxy::operator V*() uses std::addressof, this will be the real address,
  // not the fake one returned by OverloadedAddress::operator&().
  EXPECT_EQ(ptr, std::addressof(p.m_ref));
  EXPECT_NE(reinterpret_cast<std::uintptr_t>(ptr), static_cast<std::uintptr_t>(0x1234));
  EXPECT_EQ(ptr->value, 9);
}