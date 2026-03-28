// StructElement_Attribute_getName_test_1684.cpp

#include <gtest/gtest.h>

#include "StructElement.h"
#include "Object.h"
#include "goo/GooString.h"

namespace {

class AttributeGetNameTest_1684 : public ::testing::Test {
protected:
  // Helper to provide a safe value object for Attribute construction.
  Object MakeNullObject() {
    Object o;
    o.initNull();
    return o;
  }
};

TEST_F(AttributeGetNameTest_1684, UserPropertyCtorReturnsProvidedName_1684) {
  Object v = MakeNullObject();

  Attribute a(GooString("CustomUserProp"), &v);

  const char *n = a.getName();
  ASSERT_NE(n, nullptr);
  EXPECT_STREQ(n, "CustomUserProp");
}

TEST_F(AttributeGetNameTest_1684, UserPropertyEmptyNameBoundary_1684) {
  Object v = MakeNullObject();

  Attribute a(GooString(""), &v);

  const char *n = a.getName();
  ASSERT_NE(n, nullptr);
  EXPECT_STREQ(n, "");
}

TEST_F(AttributeGetNameTest_1684, NonUserPropertyReturnsTypeName_1684) {
  Object v = MakeNullObject();

  // Pick a concrete non-UserProperty type. "Lang" is a common structure attribute in PDF tagging.
  Attribute a(Attribute::Type::Lang, &v);

  const char *name = a.getName();
  const char *typeName = a.getTypeName();

  ASSERT_NE(name, nullptr);
  ASSERT_NE(typeName, nullptr);
  EXPECT_STREQ(name, typeName);
}

TEST_F(AttributeGetNameTest_1684, NonUserPropertyNameConsistentAcrossCalls_1684) {
  Object v = MakeNullObject();

  Attribute a(Attribute::Type::Lang, &v);

  const char *n1 = a.getName();
  const char *n2 = a.getName();
  const char *tn = a.getTypeName();

  ASSERT_NE(n1, nullptr);
  ASSERT_NE(n2, nullptr);
  ASSERT_NE(tn, nullptr);

  // Observable behavior: repeated calls should produce the same visible name string.
  EXPECT_STREQ(n1, n2);
  EXPECT_STREQ(n1, tn);
}

TEST_F(AttributeGetNameTest_1684, UserPropertyNameConsistentAcrossCalls_1684) {
  Object v = MakeNullObject();

  Attribute a(GooString("RepeatableName"), &v);

  const char *n1 = a.getName();
  const char *n2 = a.getName();

  ASSERT_NE(n1, nullptr);
  ASSERT_NE(n2, nullptr);

  EXPECT_STREQ(n1, "RepeatableName");
  EXPECT_STREQ(n2, "RepeatableName");
  EXPECT_STREQ(n1, n2);
}

} // namespace