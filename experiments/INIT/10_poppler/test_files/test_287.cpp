// LinkGoToR_getKind_tests_287.cpp
#include <gtest/gtest.h>

#include "poppler/Link.h"
#include "poppler/Object.h"

namespace {

class LinkGoToRTest_287 : public ::testing::Test {
protected:
  // Default-constructed Objects are a reasonable "boundary" input: empty/none.
  Object fileSpecObj_;
  Object destObj_;
};

TEST_F(LinkGoToRTest_287, GetKindReturnsActionGoToR_287) {
  LinkGoToR action(&fileSpecObj_, &destObj_);
  EXPECT_EQ(action.getKind(), actionGoToR);
}

TEST_F(LinkGoToRTest_287, GetKindReturnsActionGoToRViaBasePointer_287) {
  LinkGoToR action(&fileSpecObj_, &destObj_);
  LinkAction* base = &action;

  ASSERT_NE(base, nullptr);
  EXPECT_EQ(base->getKind(), actionGoToR);
}

TEST_F(LinkGoToRTest_287, GetKindIsStableAcrossMultipleCalls_287) {
  LinkGoToR action(&fileSpecObj_, &destObj_);

  const auto k1 = action.getKind();
  const auto k2 = action.getKind();
  const auto k3 = action.getKind();

  EXPECT_EQ(k1, actionGoToR);
  EXPECT_EQ(k2, actionGoToR);
  EXPECT_EQ(k3, actionGoToR);
}

TEST_F(LinkGoToRTest_287, CallingIsOkDoesNotChangeKind_287) {
  LinkGoToR action(&fileSpecObj_, &destObj_);

  // We don't assume what isOk() returns for these boundary inputs; just that it's callable.
  (void)action.isOk();

  EXPECT_EQ(action.getKind(), actionGoToR);
}

}  // namespace