// TEST_ID: 96
// File: test_Object_getString_96.cpp

#include <gtest/gtest.h>

#include "poppler/Object.h"
#include "poppler/goo/GooString.h"

namespace {

class ObjectGetStringTest_96 : public ::testing::Test {};

static std::string toStdString_96(const GooString *s) {
  if (!s) return {};
  // GooString in Poppler provides getCString().
  return std::string(s->getCString() ? s->getCString() : "");
}

} // namespace

TEST_F(ObjectGetStringTest_96, ReturnsNonNullForStdStringConstructor_96) {
  Object obj(std::string("hello"));
  const GooString *s = obj.getString();
  ASSERT_NE(s, nullptr);
  EXPECT_EQ(toStdString_96(s), "hello");
}

TEST_F(ObjectGetStringTest_96, HandlesEmptyString_96) {
  Object obj(std::string(""));
  const GooString *s = obj.getString();
  ASSERT_NE(s, nullptr);
  EXPECT_EQ(toStdString_96(s), "");
}

TEST_F(ObjectGetStringTest_96, ReturnsNonNullForUniquePtrGooStringConstructor_96) {
  auto gs = std::make_unique<GooString>("world");
  Object obj(std::move(gs));
  const GooString *s = obj.getString();
  ASSERT_NE(s, nullptr);
  EXPECT_EQ(toStdString_96(s), "world");
}

TEST_F(ObjectGetStringTest_96, StablePointerAcrossRepeatedCalls_96) {
  Object obj(std::string("repeat"));
  const GooString *s1 = obj.getString();
  const GooString *s2 = obj.getString();
  ASSERT_NE(s1, nullptr);
  ASSERT_NE(s2, nullptr);
  EXPECT_EQ(s1, s2);                 // same underlying string object
  EXPECT_EQ(toStdString_96(s1), "repeat");
  EXPECT_EQ(toStdString_96(s2), "repeat");
}

TEST_F(ObjectGetStringTest_96, DeathOnNonStringBoolObject_96) {
  Object obj(true);

  // OBJECT_TYPE_CHECK(objString) is expected to reject non-string types.
  // Use death tests to validate observable failure when supported/enabled.
  ASSERT_DEATH_IF_SUPPORTED({ (void)obj.getString(); }, "");
}

TEST_F(ObjectGetStringTest_96, DeathOnNonStringIntObject_96) {
  Object obj(123);
  ASSERT_DEATH_IF_SUPPORTED({ (void)obj.getString(); }, "");
}

TEST_F(ObjectGetStringTest_96, DeathOnNullObject_96) {
  Object obj = Object::null();
  ASSERT_DEATH_IF_SUPPORTED({ (void)obj.getString(); }, "");
}