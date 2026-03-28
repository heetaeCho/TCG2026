// TEST_ID: 284
// File: LinkGoTo_getDest_test.cpp

#include <gtest/gtest.h>

#include "Link.h"
#include "Object.h"
#include "goo/GooString.h"

namespace {

class LinkGoToTest_284 : public ::testing::Test {
protected:
  // Helper: construct LinkGoTo from an Object and return it.
  static std::unique_ptr<LinkGoTo> MakeLinkGoToFromObj(const Object& obj) {
    return std::make_unique<LinkGoTo>(&obj);
  }
};

TEST_F(LinkGoToTest_284, GetDest_NullObject_ReturnsNull_284) {
  Object obj;
  obj.initNull();

  auto action = MakeLinkGoToFromObj(obj);
  ASSERT_NE(action, nullptr);

  // Observable behavior: getDest() is callable and returns a pointer (possibly null).
  // For a null destination object, the destination is expected to be absent.
  EXPECT_EQ(action->getDest(), nullptr);
}

TEST_F(LinkGoToTest_284, GetDest_NamedDestinationString_ReturnsNull_284) {
  Object obj;
  obj.initString(new GooString("NamedDestination"));

  auto action = MakeLinkGoToFromObj(obj);
  ASSERT_NE(action, nullptr);

  // If the destination is expressed as a named destination string, getDest() should be null.
  // (The named destination is retrievable via getNamedDest(), but this test focuses on getDest().)
  EXPECT_EQ(action->getDest(), nullptr);
}

TEST_F(LinkGoToTest_284, GetDest_RepeatedCalls_AreStable_284) {
  Object obj;
  obj.initNull();

  auto action = MakeLinkGoToFromObj(obj);
  ASSERT_NE(action, nullptr);

  const LinkDest* first = action->getDest();
  const LinkDest* second = action->getDest();
  const LinkDest* third = action->getDest();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(LinkGoToTest_284, GetDest_IndependentInstances_DoNotShareDestPointer_284) {
  Object objA;
  objA.initNull();
  Object objB;
  objB.initNull();

  auto a1 = MakeLinkGoToFromObj(objA);
  auto a2 = MakeLinkGoToFromObj(objB);

  ASSERT_NE(a1, nullptr);
  ASSERT_NE(a2, nullptr);

  // For null inputs, both should be null; this also ensures no unexpected shared non-null pointer.
  EXPECT_EQ(a1->getDest(), nullptr);
  EXPECT_EQ(a2->getDest(), nullptr);
}

}  // namespace