// LinkJavaScript_getKind_ut_323.cpp
#include <gtest/gtest.h>

#include "Link.h"
#include "Object.h"

namespace {

class LinkJavaScriptTest_323 : public ::testing::Test {};

TEST_F(LinkJavaScriptTest_323, GetKindReturnsActionJavaScript_323)
{
  Object jsObj; // default-constructed Object (typically Null)
  LinkJavaScript action(&jsObj);

  EXPECT_EQ(actionJavaScript, action.getKind());
}

TEST_F(LinkJavaScriptTest_323, GetKindViaBasePointerReturnsActionJavaScript_323)
{
  Object jsObj;
  LinkJavaScript action(&jsObj);

  const LinkAction *base = &action;
  ASSERT_NE(base, nullptr);

  EXPECT_EQ(actionJavaScript, base->getKind());
}

TEST_F(LinkJavaScriptTest_323, GetKindIsStableAcrossMultipleCalls_323)
{
  Object jsObj;
  LinkJavaScript action(&jsObj);

  const auto k1 = action.getKind();
  const auto k2 = action.getKind();
  const auto k3 = action.getKind();

  EXPECT_EQ(actionJavaScript, k1);
  EXPECT_EQ(k1, k2);
  EXPECT_EQ(k2, k3);
}

} // namespace