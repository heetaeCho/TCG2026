// File: regexp_sub_test_153.cc
#include "re2/regexp.h"
#include <gtest/gtest.h>

using re2::Regexp;

class RegexpSubTest_153 : public ::testing::Test {
protected:
  // Use zeroed flags to avoid assuming anything about specific flag values.
  static constexpr Regexp::ParseFlags kFlags =
      static_cast<Regexp::ParseFlags>(0);

  // Helper to create a simple leaf without relying on Rune types.
  static Regexp* Leaf(int id = 0) {
    return Regexp::HaveMatch(id, kFlags);
  }
};

// Normal case (nsub == 2): sub() should point to an array whose elements
// correspond to the provided children, in order.
TEST_F(RegexpSubTest_153, Sub_ReturnsArrayForTwoChildren_153) {
  Regexp* a = RegexpSubTest_153::Leaf(1);
  Regexp* b = RegexpSubTest_153::Leaf(2);
  Regexp* subs[2] = {a, b};

  Regexp* parent = Regexp::Concat(subs, 2, RegexpSubTest_153::kFlags);
  ASSERT_NE(parent, nullptr);

  // Observable behavior: parent reports two children,
  // and sub()[i] references the children we passed.
  EXPECT_EQ(parent->nsub(), 2);

  Regexp** out = parent->sub();
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(out[0], a);
  EXPECT_EQ(out[1], b);

  // Pointer returned by sub() should be stable across calls.
  EXPECT_EQ(out, parent->sub());

  // Clean up refs (treating the API as ref-counted but without
  // asserting ownership semantics).
  a->Decref();
  b->Decref();
  parent->Decref();
}

// Boundary (nsub == 1): sub() should reference a single slot containing
// the provided child.
TEST_F(RegexpSubTest_153, Sub_ReturnsSingleSlotForOneChild_153) {
  Regexp* a = RegexpSubTest_153::Leaf(3);
  Regexp* subs[1] = {a};

  Regexp* parent = Regexp::Concat(subs, 1, RegexpSubTest_153::kFlags);
  ASSERT_NE(parent, nullptr);

  EXPECT_EQ(parent->nsub(), 1);

  Regexp** out = parent->sub();
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(out[0], a);

  // Idempotence of pointer.
  EXPECT_EQ(out, parent->sub());

  a->Decref();
  parent->Decref();
}

// Boundary (nsub == 0): leaf nodes should report zero subs.
// We only assert that sub() returns a non-null pointer and that
// repeated calls return the same pointer (stable address).
// We do NOT dereference the returned pointer when nsub()==0.
TEST_F(RegexpSubTest_153, Sub_OnLeafHasStableNonNullPointer_153) {
  Regexp* leaf = RegexpSubTest_153::Leaf(4);
  ASSERT_NE(leaf, nullptr);

  EXPECT_EQ(leaf->nsub(), 0);

  Regexp** p1 = leaf->sub();
  Regexp** p2 = leaf->sub();
  ASSERT_NE(p1, nullptr);
  EXPECT_EQ(p1, p2);  // stable across calls

  leaf->Decref();
}

// Cross-check with a different multi-child constructor (Alternate)
// to avoid coupling the test to a single factory.
TEST_F(RegexpSubTest_153, Sub_WorksWithAlternateToo_153) {
  Regexp* a = RegexpSubTest_153::Leaf(10);
  Regexp* b = RegexpSubTest_153::Leaf(20);
  Regexp* c = RegexpSubTest_153::Leaf(30);
  Regexp* subs[3] = {a, b, c};

  Regexp* parent = Regexp::Alternate(subs, 3, RegexpSubTest_153::kFlags);
  ASSERT_NE(parent, nullptr);

  EXPECT_EQ(parent->nsub(), 3);

  Regexp** out = parent->sub();
  ASSERT_NE(out, nullptr);
  EXPECT_EQ(out[0], a);
  EXPECT_EQ(out[1], b);
  EXPECT_EQ(out[2], c);

  EXPECT_EQ(out, parent->sub());  // stable

  a->Decref();
  b->Decref();
  c->Decref();
  parent->Decref();
}
