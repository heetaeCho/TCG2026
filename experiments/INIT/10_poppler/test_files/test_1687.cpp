// Attribute_isHidden_test_1687.cc
#include <gtest/gtest.h>

#include "StructElement.h"
#include "GooString.h"
#include "Object.h"

namespace {

class AttributeTest_1687 : public ::testing::Test {
protected:
  static Attribute MakeAttrWithNullValue() {
    // Use the (GooString&&, Object*) ctor to avoid relying on Attribute::Type values.
    return Attribute(GooString("TestAttr"), nullptr);
  }

  static Attribute MakeAttrWithObjectValue(Object *obj) {
    return Attribute(GooString("TestAttr"), obj);
  }
};

TEST_F(AttributeTest_1687, SetHiddenTrueMakesIsHiddenTrue_1687) {
  Object obj; // default/null object should be OK to pass as a value pointer
  Attribute attr = MakeAttrWithObjectValue(&obj);

  attr.setHidden(true);
  EXPECT_TRUE(attr.isHidden());
}

TEST_F(AttributeTest_1687, SetHiddenFalseMakesIsHiddenFalse_1687) {
  Object obj;
  Attribute attr = MakeAttrWithObjectValue(&obj);

  attr.setHidden(false);
  EXPECT_FALSE(attr.isHidden());
}

TEST_F(AttributeTest_1687, ToggleHiddenMultipleTimesReflectsLatestValue_1687) {
  Object obj;
  Attribute attr = MakeAttrWithObjectValue(&obj);

  attr.setHidden(true);
  EXPECT_TRUE(attr.isHidden());

  attr.setHidden(false);
  EXPECT_FALSE(attr.isHidden());

  attr.setHidden(true);
  EXPECT_TRUE(attr.isHidden());
}

TEST_F(AttributeTest_1687, ConstAccessIsHiddenReflectsSetHidden_1687) {
  Object obj;
  Attribute attr = MakeAttrWithObjectValue(&obj);

  attr.setHidden(true);
  const Attribute &cattr = attr;
  EXPECT_TRUE(cattr.isHidden());

  attr.setHidden(false);
  EXPECT_FALSE(cattr.isHidden());
}

TEST_F(AttributeTest_1687, NullValueConstructorStillAllowsHiddenToggling_1687) {
  Attribute attr = MakeAttrWithNullValue();

  attr.setHidden(true);
  EXPECT_TRUE(attr.isHidden());

  attr.setHidden(false);
  EXPECT_FALSE(attr.isHidden());
}

} // namespace