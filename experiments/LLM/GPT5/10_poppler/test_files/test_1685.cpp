// === Unit tests for StructElement.h (Attribute::getRevision) ===
// File: Attribute_getRevision_1685_test.cc

#include <gtest/gtest.h>

#include "StructElement.h" // Attribute
#include "Object.h"        // Object
#include "goo/GooString.h" // GooString

namespace {

class AttributeTest_1685 : public ::testing::Test {
protected:
  // Helper to build an Attribute using the (GooString&&, Object*) constructor,
  // avoiding assumptions about Attribute::Type enum values.
  static Attribute MakeAttrWithName(Object *obj) {
    return Attribute(GooString("CustomAttrName"), obj);
  }
};

TEST_F(AttributeTest_1685, SetThenGetRevisionReturnsSameValue_1685) {
  Object obj;
  Attribute attr = MakeAttrWithName(&obj);

  const unsigned int rev = 7u;
  attr.setRevision(rev);

  EXPECT_EQ(attr.getRevision(), rev);
}

TEST_F(AttributeTest_1685, GetRevisionWorksOnConstObject_1685) {
  Object obj;
  Attribute attr = MakeAttrWithName(&obj);

  attr.setRevision(42u);

  const Attribute &cattr = attr;
  EXPECT_EQ(cattr.getRevision(), 42u);
}

TEST_F(AttributeTest_1685, RevisionCanBeSetToZeroBoundary_1685) {
  Object obj;
  Attribute attr = MakeAttrWithName(&obj);

  attr.setRevision(0u);
  EXPECT_EQ(attr.getRevision(), 0u);

  // Change away and back to ensure subsequent updates are observable.
  attr.setRevision(1u);
  EXPECT_EQ(attr.getRevision(), 1u);

  attr.setRevision(0u);
  EXPECT_EQ(attr.getRevision(), 0u);
}

TEST_F(AttributeTest_1685, RevisionCanBeSetToMaxUnsignedBoundary_1685) {
  Object obj;
  Attribute attr = MakeAttrWithName(&obj);

  const unsigned int maxu = std::numeric_limits<unsigned int>::max();
  attr.setRevision(maxu);

  EXPECT_EQ(attr.getRevision(), maxu);
}

TEST_F(AttributeTest_1685, MultipleSetRevisionUpdatesAreObservable_1685) {
  Object obj;
  Attribute attr = MakeAttrWithName(&obj);

  attr.setRevision(10u);
  EXPECT_EQ(attr.getRevision(), 10u);

  attr.setRevision(11u);
  EXPECT_EQ(attr.getRevision(), 11u);

  attr.setRevision(999999u);
  EXPECT_EQ(attr.getRevision(), 999999u);
}

} // namespace