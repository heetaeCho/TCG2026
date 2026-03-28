// Dict_getXRef_tests_118.cpp
// Unit tests for Dict::getXRef() based strictly on the public interface.

#include <gtest/gtest.h>

#include "Dict.h"  // from ./TestProjects/poppler/poppler/Dict.h

namespace {

class DictGetXRefTest_118 : public ::testing::Test {};

TEST_F(DictGetXRefTest_118, ReturnsPointerPassedToConstructor_118) {
  // We do not rely on XRef construction details; getXRef() is pointer-based.
  XRef* xref = reinterpret_cast<XRef*>(static_cast<uintptr_t>(0x1234));

  Dict d(xref);
  EXPECT_EQ(d.getXRef(), xref);
}

TEST_F(DictGetXRefTest_118, ReturnsNullWhenConstructedWithNull_118) {
  Dict d(nullptr);
  EXPECT_EQ(d.getXRef(), nullptr);
}

TEST_F(DictGetXRefTest_118, SetXRefUpdatesValueObservedByGetXRef_118) {
  XRef* xref1 = reinterpret_cast<XRef*>(static_cast<uintptr_t>(0x1111));
  XRef* xref2 = reinterpret_cast<XRef*>(static_cast<uintptr_t>(0x2222));

  Dict d(xref1);
  ASSERT_EQ(d.getXRef(), xref1);

  d.setXRef(xref2);
  EXPECT_EQ(d.getXRef(), xref2);
}

TEST_F(DictGetXRefTest_118, SetXRefAcceptsNullAndGetXRefReflectsIt_118) {
  XRef* xref = reinterpret_cast<XRef*>(static_cast<uintptr_t>(0x9999));

  Dict d(xref);
  ASSERT_EQ(d.getXRef(), xref);

  d.setXRef(nullptr);
  EXPECT_EQ(d.getXRef(), nullptr);
}

}  // namespace