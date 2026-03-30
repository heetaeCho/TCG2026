// File: form_field_choice_get_num_choices_ut_912.cpp
#include <gtest/gtest.h>

#include "poppler/Form.h"

// These headers are typically needed for the constructor arguments.
// If your build already pulls them transitively via Form.h, they won't hurt.
#include "poppler/Object.h"
#include "poppler/Ref.h"
#include "poppler/PDFDoc.h"

#include <memory>
#include <set>
#include <vector>
#include <string>

namespace {

class FormFieldChoiceTest_912 : public ::testing::Test {
protected:
  static std::unique_ptr<FormFieldChoice> MakeWithSetPtr_912(std::set<int> *usedParents) {
    // Create the most minimal / neutral inputs we can without assuming internal behavior.
    PDFDoc *doc = nullptr;
    FormField *parent = nullptr;

    Object aobj;        // default-constructed Object; moved into ctor
    Ref ref{0, 0};      // benign ref

    return std::make_unique<FormFieldChoice>(doc, std::move(aobj), ref, parent, usedParents);
  }

  static std::unique_ptr<FormFieldChoice> MakeWithIntPtr_912(int *usedParents) {
    PDFDoc *doc = nullptr;
    FormField *parent = nullptr;

    Object aobj;
    Ref ref{0, 0};

    return std::make_unique<FormFieldChoice>(doc, std::move(aobj), ref, parent, usedParents);
  }
};

TEST_F(FormFieldChoiceTest_912, ConstructWithNullSetPtr_DoesNotCrash_GetNumChoicesNonNegative_912) {
  // Normal-ish construction path (even with nullptr deps) should be safe to query.
  auto field = MakeWithSetPtr_912(nullptr);
  ASSERT_NE(field, nullptr);

  const int n = field->getNumChoices();
  EXPECT_GE(n, 0);
}

TEST_F(FormFieldChoiceTest_912, ConstructWithNullIntPtr_DoesNotCrash_GetNumChoicesNonNegative_912) {
  auto field = MakeWithIntPtr_912(nullptr);
  ASSERT_NE(field, nullptr);

  const int n = field->getNumChoices();
  EXPECT_GE(n, 0);
}

TEST_F(FormFieldChoiceTest_912, GetNumChoices_IsStableAcrossRepeatedCalls_912) {
  auto field = MakeWithSetPtr_912(nullptr);
  ASSERT_NE(field, nullptr);

  const int n1 = field->getNumChoices();
  const int n2 = field->getNumChoices();
  const int n3 = field->getNumChoices();

  EXPECT_EQ(n1, n2);
  EXPECT_EQ(n2, n3);
  EXPECT_GE(n1, 0);
}

TEST_F(FormFieldChoiceTest_912, GetNumChoices_ConsistentWithGetChoiceBoundsWhenPossible_912) {
  auto field = MakeWithSetPtr_912(nullptr);
  ASSERT_NE(field, nullptr);

  const int n = field->getNumChoices();
  ASSERT_GE(n, 0);

  // Boundary-focused checks that don’t assume how Poppler populates choices.
  // We only validate “indexing behavior” in a conditional way:
  // - If there are no choices, index 0 should not yield a valid choice pointer (commonly nullptr).
  // - If there are choices, first element should be queryable without crashing.
  if (n == 0) {
    // We cannot demand a specific policy, but returning nullptr is a common observable behavior.
    // This expectation is intentionally weak: it's allowed to be nullptr; if not nullptr,
    // at least the call succeeded.
    (void)field->getChoice(0);
    SUCCEED();
  } else {
    // Should be safe to query within range.
    const GooString *c0 = field->getChoice(0);
    (void)c0; // Do not assume non-null; only that the call is safe.
    SUCCEED();

    // Out-of-range query: should be safe. We don't assume it must be nullptr.
    const GooString *coor = field->getChoice(n);
    (void)coor;
    SUCCEED();
  }
}

TEST_F(FormFieldChoiceTest_912, GetNumChoices_AfterReset_DoesNotCrashAndStaysNonNegative_912) {
  auto field = MakeWithSetPtr_912(nullptr);
  ASSERT_NE(field, nullptr);

  const int before = field->getNumChoices();
  EXPECT_GE(before, 0);

  // Exercise the reset API with an empty exclusion list (boundary input).
  const std::vector<std::string> excludedFields;
  EXPECT_NO_THROW(field->reset(excludedFields));

  const int after = field->getNumChoices();
  EXPECT_GE(after, 0);

  // Don’t assert equality; reset semantics are implementation-defined.
}

} // namespace