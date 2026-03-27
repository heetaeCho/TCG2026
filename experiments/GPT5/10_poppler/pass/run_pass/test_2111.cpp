// File: poppler-annot-screen-get-action-test_2111.cc
#include <gtest/gtest.h>

// Minimal forward declarations / test doubles to compile the unit under test.
// We only model what is required by the public interface shown in the prompt.
struct _PopplerAction {};
typedef _PopplerAction PopplerAction;

// The prompt shows an (optional) dependency declaring an empty struct, but the
// provided function dereferences `poppler_annot->action`, so the real type must
// contain an `action` member. For unit testing the interface, we provide the
// minimal layout needed to interact with the function.
struct _PopplerAnnotScreen {
  PopplerAction* action;
};
typedef _PopplerAnnotScreen PopplerAnnotScreen;

// Unit under test (as provided).
extern "C" PopplerAction* poppler_annot_screen_get_action(PopplerAnnotScreen* poppler_annot) {
  return poppler_annot->action;
}

class PopplerAnnotScreenGetActionTest_2111 : public ::testing::Test {};

TEST_F(PopplerAnnotScreenGetActionTest_2111, ReturnsSameActionPointer_2111) {
  PopplerAction dummy_action{};
  PopplerAnnotScreen annot{};
  annot.action = &dummy_action;

  PopplerAction* out = poppler_annot_screen_get_action(&annot);

  EXPECT_EQ(out, &dummy_action);
}

TEST_F(PopplerAnnotScreenGetActionTest_2111, ReturnsNullWhenActionIsNull_2111) {
  PopplerAnnotScreen annot{};
  annot.action = nullptr;

  PopplerAction* out = poppler_annot_screen_get_action(&annot);

  EXPECT_EQ(out, nullptr);
}

#if GTEST_HAS_DEATH_TEST
TEST_F(PopplerAnnotScreenGetActionTest_2111, DeathOnNullAnnotPointer_2111) {
  // The implementation dereferences the pointer with no null-check.
  // This is an observable error case (process termination) via the interface.
  ASSERT_DEATH(
      {
        (void)poppler_annot_screen_get_action(nullptr);
      },
      "");
}
#endif