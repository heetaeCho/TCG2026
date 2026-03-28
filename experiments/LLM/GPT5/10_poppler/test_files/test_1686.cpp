// Attribute_setRevision_tests_1686.cpp

#include <gtest/gtest.h>

#include <limits>

#include "StructElement.h"
#include "Object.h"
#include "GooString.h"

class AttributeTest_1686 : public ::testing::Test {
protected:
  // Helper to create an Attribute instance without relying on Attribute::Type.
  static Attribute MakeAttributeWithName() {
    Object value; // default-constructed Object (treated as opaque; only used as required ctor arg)
    GooString name("TestAttr");
    return Attribute(std::move(name), &value);
  }
};

TEST_F(AttributeTest_1686, SetRevisionUpdatesGetRevision_1686) {
  Attribute attr = MakeAttributeWithName();

  const unsigned int rev = 1u;
  EXPECT_NO_THROW(attr.setRevision(rev));
  EXPECT_EQ(attr.getRevision(), rev);
}

TEST_F(AttributeTest_1686, SetRevisionCanBeCalledMultipleTimes_LastWriteWins_1686) {
  Attribute attr = MakeAttributeWithName();

  EXPECT_NO_THROW(attr.setRevision(10u));
  EXPECT_EQ(attr.getRevision(), 10u);

  EXPECT_NO_THROW(attr.setRevision(42u));
  EXPECT_EQ(attr.getRevision(), 42u);
}

TEST_F(AttributeTest_1686, SetRevisionAcceptsZero_Boundary_1686) {
  Attribute attr = MakeAttributeWithName();

  EXPECT_NO_THROW(attr.setRevision(0u));
  EXPECT_EQ(attr.getRevision(), 0u);
}

TEST_F(AttributeTest_1686, SetRevisionAcceptsMaxUnsigned_Boundary_1686) {
  Attribute attr = MakeAttributeWithName();

  const unsigned int max_u = std::numeric_limits<unsigned int>::max();
  EXPECT_NO_THROW(attr.setRevision(max_u));
  EXPECT_EQ(attr.getRevision(), max_u);
}

TEST_F(AttributeTest_1686, SetRevisionDoesNotCorruptFormattedValueObservation_1686) {
  Attribute attr = MakeAttributeWithName();

  // We only observe that calling setRevision doesn't make formatted value retrieval unusable.
  // (No assumptions about default formatted value content.)
  const char *before = nullptr;
  EXPECT_NO_THROW(before = attr.getFormattedValue());

  EXPECT_NO_THROW(attr.setRevision(7u));

  const char *after = nullptr;
  EXPECT_NO_THROW(after = attr.getFormattedValue());

  // The formatted value may or may not change; we only assert the calls are safe and revision updated.
  EXPECT_EQ(attr.getRevision(), 7u);
  (void)before;
  (void)after;
}