// TEST_ID: 285
#include <gtest/gtest.h>

#include "Link.h"
#include "Object.h"
#include "goo/GooString.h"

namespace {

class LinkGoToTest_285 : public ::testing::Test {};

TEST_F(LinkGoToTest_285, GetNamedDest_ReturnsNullForNullObject_285) {
  Object obj;
  obj.initNull();

  LinkGoTo action(&obj);

  // Observable behavior only: should not crash, pointer should be safely retrievable.
  EXPECT_EQ(action.getNamedDest(), nullptr);
}

TEST_F(LinkGoToTest_285, GetNamedDest_ReturnsNonNullForStringObject_285) {
  Object obj;
  obj.initString(new GooString("MyNamedDest"));

  LinkGoTo action(&obj);

  const GooString *named = action.getNamedDest();
  ASSERT_NE(named, nullptr);
  EXPECT_STREQ(named->c_str(), "MyNamedDest");
}

TEST_F(LinkGoToTest_285, GetNamedDest_EmptyStringIsHandled_285) {
  Object obj;
  obj.initString(new GooString(""));

  LinkGoTo action(&obj);

  const GooString *named = action.getNamedDest();
  ASSERT_NE(named, nullptr);
  EXPECT_STREQ(named->c_str(), "");
}

TEST_F(LinkGoToTest_285, GetNamedDest_IsStableAcrossMultipleCalls_285) {
  Object obj;
  obj.initString(new GooString("StableDest"));

  LinkGoTo action(&obj);

  const GooString *first = action.getNamedDest();
  const GooString *second = action.getNamedDest();

  // We only assert observable stability (same pointer and same content).
  ASSERT_NE(first, nullptr);
  ASSERT_NE(second, nullptr);
  EXPECT_EQ(first, second);
  EXPECT_STREQ(first->c_str(), "StableDest");
}

TEST_F(LinkGoToTest_285, GetNamedDest_ReturnsNullForNonStringObject_285) {
  Object obj;
  obj.initInt(123);

  LinkGoTo action(&obj);

  // For an unsupported/irrelevant object type, getNamedDest should be safely usable.
  EXPECT_EQ(action.getNamedDest(), nullptr);
}

} // namespace