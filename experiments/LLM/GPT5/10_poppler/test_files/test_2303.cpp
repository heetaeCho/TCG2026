// File: poppler-action-new-test-2303.cc
#include <gtest/gtest.h>

#include <glib.h>

#include "poppler-action.h"
#include "poppler-private.h"

// LinkAction is a C++ class from Poppler core.
#include "Link.h"

namespace {

class DummyUnknownLinkAction : public LinkAction {
 public:
  explicit DummyUnknownLinkAction(LinkActionKind kind) : kind_(kind) {}
  ~DummyUnknownLinkAction() override = default;

  const LinkActionKind getKind() override { return kind_; }

 private:
  LinkActionKind kind_;
};

class PopplerActionNewTest_2303 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Nothing to tear down; PopplerAction objects are freed per-test.
  }
};

TEST_F(PopplerActionNewTest_2303, NullLinkReturnsNoneAndCopiesTitle_2303) {
  const gchar* kTitle = "Hello";
  PopplerAction* action = _poppler_action_new(/*document=*/nullptr, /*link=*/nullptr, kTitle);
  ASSERT_NE(action, nullptr);

  EXPECT_EQ(action->type, POPPLER_ACTION_NONE);

  // Title is observable via the public struct layout exposed by poppler-action.h.
  ASSERT_NE(action->any.title, nullptr);
  EXPECT_STREQ(action->any.title, kTitle);

  poppler_action_free(action);
}

TEST_F(PopplerActionNewTest_2303, NullLinkWithNullTitleKeepsTitleNull_2303) {
  PopplerAction* action = _poppler_action_new(/*document=*/nullptr, /*link=*/nullptr, /*title=*/nullptr);
  ASSERT_NE(action, nullptr);

  EXPECT_EQ(action->type, POPPLER_ACTION_NONE);
  EXPECT_EQ(action->any.title, nullptr);

  poppler_action_free(action);
}

TEST_F(PopplerActionNewTest_2303, UnknownKindSetsUnknownTypeAndCopiesTitle_2303) {
  DummyUnknownLinkAction link(actionUnknown);

  const gchar* kTitle = "Unknown action";
  PopplerAction* action = _poppler_action_new(/*document=*/nullptr, &link, kTitle);
  ASSERT_NE(action, nullptr);

  EXPECT_EQ(action->type, POPPLER_ACTION_UNKNOWN);

  ASSERT_NE(action->any.title, nullptr);
  EXPECT_STREQ(action->any.title, kTitle);

  poppler_action_free(action);
}

TEST_F(PopplerActionNewTest_2303, UnknownKindWithEmptyTitleDuplicatesEmptyString_2303) {
  DummyUnknownLinkAction link(actionUnknown);

  const gchar* kTitle = "";
  PopplerAction* action = _poppler_action_new(/*document=*/nullptr, &link, kTitle);
  ASSERT_NE(action, nullptr);

  EXPECT_EQ(action->type, POPPLER_ACTION_UNKNOWN);

  // Empty string should remain an empty string (not nullptr) when provided.
  ASSERT_NE(action->any.title, nullptr);
  EXPECT_STREQ(action->any.title, "");

  poppler_action_free(action);
}

TEST_F(PopplerActionNewTest_2303, OutOfRangeKindFallsBackToUnknown_2303) {
  // Return a value outside the known LinkActionKind enum range. The switch should
  // hit default and yield POPPLER_ACTION_UNKNOWN (observable behavior).
  DummyUnknownLinkAction link(static_cast<LinkActionKind>(999));

  PopplerAction* action = _poppler_action_new(/*document=*/nullptr, &link, /*title=*/"x");
  ASSERT_NE(action, nullptr);

  EXPECT_EQ(action->type, POPPLER_ACTION_UNKNOWN);

  poppler_action_free(action);
}

TEST_F(PopplerActionNewTest_2303, VeryLongTitleIsCopiedAndPreserved_2303) {
  DummyUnknownLinkAction link(actionUnknown);

  // Boundary-ish input: long string.
  const int kLen = 4096;
  GString* s = g_string_sized_new(kLen);
  for (int i = 0; i < kLen; ++i) {
    g_string_append_c(s, 'A' + (i % 26));
  }

  PopplerAction* action =
      _poppler_action_new(/*document=*/nullptr, &link, /*title=*/s->str);
  ASSERT_NE(action, nullptr);

  EXPECT_EQ(action->type, POPPLER_ACTION_UNKNOWN);

  ASSERT_NE(action->any.title, nullptr);
  EXPECT_STREQ(action->any.title, s->str);

  poppler_action_free(action);
  g_string_free(s, TRUE);
}

}  // namespace