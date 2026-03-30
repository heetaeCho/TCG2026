// LinkRendition_test_309.cpp
#include <gtest/gtest.h>

#include "Link.h"

class LinkRenditionTest_309 : public ::testing::Test {};

// The TEST_ID is 309
TEST_F(LinkRenditionTest_309, GetKindReturnsActionRendition_309) {
  Object obj;
  LinkRendition action(&obj);

  EXPECT_EQ(action.getKind(), actionRendition);

  const LinkRendition &constRef = action;
  EXPECT_EQ(constRef.getKind(), actionRendition);
}

// The TEST_ID is 309
TEST_F(LinkRenditionTest_309, GetKindStableAcrossMultipleCalls_309) {
  Object obj;
  LinkRendition action(&obj);

  const auto first = action.getKind();
  const auto second = action.getKind();
  const auto third = action.getKind();

  EXPECT_EQ(first, actionRendition);
  EXPECT_EQ(second, actionRendition);
  EXPECT_EQ(third, actionRendition);
}

// The TEST_ID is 309
TEST_F(LinkRenditionTest_309, GetKindThroughBasePointer_309) {
  Object obj;
  LinkRendition rendition(&obj);

  LinkAction *base = &rendition;
  ASSERT_NE(base, nullptr);
  EXPECT_EQ(base->getKind(), actionRendition);

  const LinkAction *cbase = &rendition;
  ASSERT_NE(cbase, nullptr);
  EXPECT_EQ(cbase->getKind(), actionRendition);
}

// The TEST_ID is 309
TEST_F(LinkRenditionTest_309, ActionRenditionEnumValueIsAsDeclared_309) {
  // Boundary-style check using the provided public enum declaration.
  // If the enum assignments change, this test will catch it.
  EXPECT_EQ(static_cast<int>(actionRendition), 6);
}