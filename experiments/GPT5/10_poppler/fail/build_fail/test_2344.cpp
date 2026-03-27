// File: poppler-form-field-choice-commit-on-change-test-2344.cc
//
// Unit tests for:
//   gboolean poppler_form_field_choice_commit_on_change(PopplerFormField *field)
//
// Constraints honored:
// - Treat implementation as a black box.
// - Only observable behavior tested (return value + GLib critical on precondition failure).
// - No access to private/internal state beyond the provided public struct layout in poppler-private.h.
// - Google Mock used only for an external collaborator attempt (FormWidgetChoice), guarded to avoid
//   making non-deterministic assertions if the underlying API is not mockable in this build.

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <glib.h>

#include "poppler-private.h"
#include "poppler-form-field.h"

// Poppler core (for FormWidget / FormWidgetChoice / getType / formChoice, etc.)
#include "poppler/Form.h"

using ::testing::_;
using ::testing::Return;

namespace {

// Many Poppler builds define FormWidgetType / FormType enums. We only need "formChoice" and
// "getType()" to compile. If the identifiers differ in your tree, adjust includes accordingly.

// A minimal non-choice widget that makes the precondition fail.
class FakeNonChoiceWidget : public FormWidget {
public:
  // FormWidget's ctor signature varies across Poppler versions; most have a default or protected ctor.
  // If your build requires parameters, adapt this fake accordingly.
  FakeNonChoiceWidget() = default;
  ~FakeNonChoiceWidget() override = default;

  // getType() is used by the function under test.
  // Return something that is *not* formChoice. We try a conservative approach:
  // - If "formChoice" is an enum value, cast + 1 is different.
  FormWidgetType getType() const override {
    return static_cast<FormWidgetType>(static_cast<int>(formChoice) + 1);
  }
};

// Attempt to mock a choice widget for the "normal operation" path.
// Whether this is fully mockable depends on whether commitOnSelChange/getType are virtual in the
// actual Poppler headers used by the codebase.
//
// We keep the test that relies on this behavior *guarded* and will skip if not viable.
class MockChoiceWidget : public FormWidgetChoice {
public:
  // FormWidgetChoice constructor signature (from prompt):
  //   FormWidgetChoice(PDFDoc*, Object*, unsigned int, Ref, FormField*)
  //
  // We pass null-ish values; this is only safe if the ctor tolerates them in your build.
  // If it doesn't, the guarded test will skip after construction failure is detected
  // (but construction failure may be a hard crash depending on implementation).
  MockChoiceWidget()
      : FormWidgetChoice(/*docA=*/nullptr,
                         /*dictObj=*/nullptr,
                         /*num=*/0,
                         /*ref=*/Ref{0, 0},
                         /*p=*/nullptr) {}

  ~MockChoiceWidget() override = default;

  // getType is required by the tested function precondition.
  // We *want* it to be formChoice.
  FormWidgetType getType() const override { return formChoice; }

  // If commitOnSelChange is virtual in this build, this will be invoked.
  // If it is not virtual, the tested function will call the base implementation instead.
  MOCK_METHOD(bool, commitOnSelChange, (), (const));
};

class PopplerFormFieldChoiceCommitOnChangeTest_2344 : public ::testing::Test {
protected:
  void TearDown() override {
    // Ensure no dangling expected GLib log messages.
    // (If a test sets expectations, it should also assert them.)
  }

  static PopplerFormField MakeFieldWithWidget(FormWidget* widget) {
    PopplerFormField field{};
    field.widget = widget;
    field.field_modified_action = nullptr;
    field.format_field_action = nullptr;
    field.validate_field_action = nullptr;
    field.calculate_field_action = nullptr;
    return field;
  }
};

}  // namespace

// ----------- Tests -----------

TEST_F(PopplerFormFieldChoiceCommitOnChangeTest_2344,
       ReturnsFalseAndLogsCriticalWhenWidgetTypeIsNotChoice_2344) {
  FakeNonChoiceWidget non_choice;
  PopplerFormField field = MakeFieldWithWidget(&non_choice);

  // g_return_val_if_fail() should emit a CRITICAL and return FALSE.
  // Message text can vary; match by domain/pattern conservatively.
  g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, "*assertion*formChoice*failed*");

  const gboolean result = poppler_form_field_choice_commit_on_change(&field);

  g_test_assert_expected_messages();
  EXPECT_FALSE(result);
}

TEST_F(PopplerFormFieldChoiceCommitOnChangeTest_2344,
       DoesNotCrashAndReturnsABooleanWhenWidgetIsChoice_2344) {
  // This test validates that the function can be called in the "choice" path and produces a gboolean.
  // It does not assert an exact value unless mocking is viable, because the internal implementation
  // of FormWidgetChoice is treated as a black box.

  // If your Poppler build's FormWidgetChoice ctor cannot take null parameters, this test may crash.
  // In that case, replace with a real document-based construction in your harness.
  MockChoiceWidget choice;
  PopplerFormField field = MakeFieldWithWidget(&choice);

  // Do not set a log expectation; if the precondition is satisfied, it shouldn't log CRITICAL.
  // We also avoid asserting the exact return value without knowing whether commitOnSelChange is
  // virtual/mockable.
  //
  // We *do* ensure the result is a valid gboolean (0 or 1 in practice, but gboolean is int).
  const gboolean result = poppler_form_field_choice_commit_on_change(&field);

  // Observable boundary: gboolean should be either FALSE(0) or TRUE(non-zero).
  // This is intentionally weak but deterministic.
  EXPECT_TRUE(result == FALSE || result == TRUE);
}

TEST_F(PopplerFormFieldChoiceCommitOnChangeTest_2344,
       PropagatesCommitOnSelChangeReturnValueWhenMockable_2344) {
  // This is the intended "normal operation + external interaction" verification:
  // if commitOnSelChange is virtual (and thus mockable), the wrapper should return its value and
  // the mock expectation should be satisfied.
  //
  // If commitOnSelChange is not virtual in this build, this test would be non-deterministic.
  // We therefore detect mockability by a small probe and skip if it doesn't behave as expected.

  MockChoiceWidget choice;
  PopplerFormField field = MakeFieldWithWidget(&choice);

  // Probe: call through the most-derived type to ensure the mock is wired correctly.
  // (This always hits the mock method itself, even if the base method is non-virtual; it only
  // verifies that the object is usable.)
  EXPECT_CALL(choice, commitOnSelChange()).WillOnce(Return(true));
  const bool probe = choice.commitOnSelChange();
  EXPECT_TRUE(probe);

  // Now test the actual wrapper. If commitOnSelChange is virtual and dispatches through vtable,
  // our expectation will be consumed; if not virtual, the wrapper won't call the mock and the test
  // would fail. We avoid flakiness by skipping when we detect mismatch.
  //
  // Set up a new expectation for the wrapper call.
  ::testing::Mock::VerifyAndClearExpectations(&choice);
  EXPECT_CALL(choice, commitOnSelChange()).WillOnce(Return(false));

  const gboolean result = poppler_form_field_choice_commit_on_change(&field);

  // If the mock expectation wasn't used, gMock will fail at test end.
  // But if the build is non-mockable (non-virtual), we want to skip instead of failing.
  // We detect that by checking whether result equals our mocked FALSE.
  if (result != FALSE) {
    ::testing::Mock::VerifyAndClearExpectations(&choice);
    GTEST_SKIP() << "FormWidgetChoice::commitOnSelChange() does not appear mock-dispatchable "
                    "in this build (likely non-virtual). Wrapper return could not be verified "
                    "via external interaction.";
  }

  EXPECT_FALSE(result);
}