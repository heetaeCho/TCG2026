// LinkJavaScript_tests_322.cpp
// Unit tests for LinkJavaScript (Poppler)
// TEST_ID: 322

#include <gtest/gtest.h>

#include "Link.h"

// Poppler headers typically provide Object via Link.h includes, but include explicitly if needed.
// If your build complains, uncomment the line below.
// #include "Object.h"

namespace {

// Keep naming consistent and include TEST_ID in fixture name.
class LinkJavaScriptTest_322 : public ::testing::Test {};

} // namespace

TEST_F(LinkJavaScriptTest_322, CreateObjectThenConstruct_IsOkAndScriptRoundTrips_322) {
  const std::string js = "app.alert('hello');";

  Object obj = LinkJavaScript::createObject(nullptr, js);
  LinkJavaScript action(&obj);

  // Observable behavior via public API
  EXPECT_TRUE(action.isOk());
  EXPECT_EQ(action.getKind(), actionJavaScript);
  EXPECT_EQ(action.getScript(), js);
}

TEST_F(LinkJavaScriptTest_322, EmptyScript_CreateObjectThenConstruct_StillCallable_322) {
  const std::string js; // empty

  Object obj = LinkJavaScript::createObject(nullptr, js);
  LinkJavaScript action(&obj);

  // Do not assume "valid" or "invalid" for empty; just verify interface behavior is stable.
  // (If Poppler defines empty JS as invalid, isOk() may be false; if not, it may be true.)
  (void)action.isOk();
  EXPECT_EQ(action.getKind(), actionJavaScript);
  EXPECT_EQ(action.getScript(), js);
}

TEST_F(LinkJavaScriptTest_322, UnicodeScript_RoundTrips_322) {
  const std::string js = u8"console.log('한글 ✓');";

  Object obj = LinkJavaScript::createObject(nullptr, js);
  LinkJavaScript action(&obj);

  EXPECT_EQ(action.getKind(), actionJavaScript);
  EXPECT_EQ(action.getScript(), js);
}

TEST_F(LinkJavaScriptTest_322, LargeScript_RoundTrips_322) {
  std::string js;
  js.reserve(20000);
  for (int i = 0; i < 2000; ++i) {
    js += "var x = 1 + 2; ";
  }

  Object obj = LinkJavaScript::createObject(nullptr, js);
  LinkJavaScript action(&obj);

  EXPECT_EQ(action.getKind(), actionJavaScript);
  EXPECT_EQ(action.getScript(), js);
}

TEST_F(LinkJavaScriptTest_322, ConstructWithNonJavaScriptObject_IsOkIsFalseOrStable_322) {
  // Boundary / error-case: pass an Object that is not the shape expected for JavaScript actions.
  // We avoid asserting a specific internal interpretation; we only require it to be safe and observable.
  Object badObj;
  badObj.initInt(123);

  LinkJavaScript action(&badObj);

  // Common expectation is that this is invalid; if Poppler chooses otherwise, this still exercises
  // the behavior without inferring private logic.
  EXPECT_FALSE(action.isOk());
}

TEST_F(LinkJavaScriptTest_322, ConstructWithNullPointer_IsOkIsFalseOrStable_322) {
  // Exceptional / error-case boundary: nullptr input.
  // If the implementation asserts/crashes on nullptr in your build, change this test to EXPECT_DEATH.
  LinkJavaScript action(nullptr);

  EXPECT_FALSE(action.isOk());
  EXPECT_EQ(action.getKind(), actionJavaScript);
}