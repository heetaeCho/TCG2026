// StructElement_Attribute_getValue_test_1683.cpp

#include <gtest/gtest.h>

#include "StructElement.h"
#include "Object.h"
#include "GooString.h"

namespace {

class AttributeTest_1683 : public ::testing::Test {
protected:
  static Attribute MakeAttrWithInt(const char *name, int v) {
    Object obj;
    obj.initInt(v);
    return Attribute(GooString(name), &obj);
  }

  static Attribute MakeAttrWithBool(const char *name, bool v) {
    Object obj;
    obj.initBool(v);
    return Attribute(GooString(name), &obj);
  }

  static Attribute MakeAttrWithNull(const char *name) {
    Object obj;
    obj.initNull();
    return Attribute(GooString(name), &obj);
  }
};

TEST_F(AttributeTest_1683, GetValueReturnsNonNullPointer_1683) {
  Attribute attr = MakeAttrWithInt("A", 42);

  const Object *val = attr.getValue();
  ASSERT_NE(val, nullptr);
}

TEST_F(AttributeTest_1683, GetValuePointerIsStableAcrossCalls_1683) {
  Attribute attr = MakeAttrWithInt("Stable", 7);

  const Object *v1 = attr.getValue();
  const Object *v2 = attr.getValue();
  ASSERT_NE(v1, nullptr);
  ASSERT_NE(v2, nullptr);
  EXPECT_EQ(v1, v2);
}

TEST_F(AttributeTest_1683, GetValueWorksThroughConstAttribute_1683) {
  Attribute tmp = MakeAttrWithInt("Const", 123);
  const Attribute &attr = tmp;

  const Object *val = attr.getValue();
  ASSERT_NE(val, nullptr);

  // Observable behavior through Object's public interface.
  EXPECT_TRUE(val->isInt());
  EXPECT_EQ(val->getInt(), 123);
}

TEST_F(AttributeTest_1683, GetValueReflectsIntegerValueAtConstruction_1683) {
  Attribute attr = MakeAttrWithInt("IntVal", -1);

  const Object *val = attr.getValue();
  ASSERT_NE(val, nullptr);
  EXPECT_TRUE(val->isInt());
  EXPECT_EQ(val->getInt(), -1);
}

TEST_F(AttributeTest_1683, GetValueHandlesNullObjectValue_1683) {
  Attribute attr = MakeAttrWithNull("NullVal");

  const Object *val = attr.getValue();
  ASSERT_NE(val, nullptr);
  EXPECT_TRUE(val->isNull());
}

TEST_F(AttributeTest_1683, GetValueHandlesBooleanValues_1683) {
  Attribute attrTrue = MakeAttrWithBool("BTrue", true);
  Attribute attrFalse = MakeAttrWithBool("BFalse", false);

  const Object *vTrue = attrTrue.getValue();
  const Object *vFalse = attrFalse.getValue();
  ASSERT_NE(vTrue, nullptr);
  ASSERT_NE(vFalse, nullptr);

  EXPECT_TRUE(vTrue->isBool());
  EXPECT_TRUE(vFalse->isBool());
  EXPECT_TRUE(vTrue->getBool());
  EXPECT_FALSE(vFalse->getBool());
}

} // namespace