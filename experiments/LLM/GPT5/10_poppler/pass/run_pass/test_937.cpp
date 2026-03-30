// SPDX-License-Identifier: GPL-2.0-or-later
// File: formpagewidgets_getwidget_test.cpp
//
// Unit tests for FormPageWidgets::getWidget(int)
// Focus: observable behavior through the public interface only.

#include <gtest/gtest.h>

#include <type_traits>
#include <memory>
#include <vector>

#include "Form.h"

// NOTE:
// These tests treat FormPageWidgets as a black box and only validate behavior
// that is observable via the public API. No private state is accessed.

namespace {

class FormPageWidgetsTest_937 : public ::testing::Test {
protected:
  // Helper that checks "repeatability" of getWidget(i) for all valid indices.
  static void ExpectGetWidgetIsStableForAllIndices(const FormPageWidgets& fpw) {
    const int n = fpw.getNumWidgets();
    ASSERT_GE(n, 0);

    for (int i = 0; i < n; ++i) {
      FormWidget* a = fpw.getWidget(i);
      FormWidget* b = fpw.getWidget(i);
      EXPECT_EQ(a, b) << "getWidget(" << i << ") should be stable across repeated calls";
    }
  }
};

} // namespace

TEST_F(FormPageWidgetsTest_937, TypeTraits_CopyIsDeleted_937) {
  static_assert(!std::is_copy_constructible_v<FormPageWidgets>,
                "FormPageWidgets copy constructor must be deleted");
  static_assert(!std::is_copy_assignable_v<FormPageWidgets>,
                "FormPageWidgets copy assignment must be deleted");
}

TEST_F(FormPageWidgetsTest_937, ConstructAndGetNumWidgetsIsNonNegative_937) {
  // Construction dependencies are treated as opaque; nullptr is used intentionally.
  // If the production constructor requires non-null collaborators, this test will
  // reveal that via a crash/failure in the real codebase environment.
  FormPageWidgets fpw(/*annots=*/nullptr, /*page=*/0u, /*form=*/nullptr);

  const int n = fpw.getNumWidgets();
  EXPECT_GE(n, 0);
}

TEST_F(FormPageWidgetsTest_937, GetWidgetIsStableForAllValidIndices_937) {
  FormPageWidgets fpw(/*annots=*/nullptr, /*page=*/0u, /*form=*/nullptr);

  // Only call getWidget(i) for indices that are valid per getNumWidgets().
  ExpectGetWidgetIsStableForAllIndices(fpw);
}

TEST_F(FormPageWidgetsTest_937, AddWidgetsWithEmptyVectorDoesNotBreakGetWidgetStability_937) {
  FormPageWidgets fpw(/*annots=*/nullptr, /*page=*/0u, /*form=*/nullptr);

  // Snapshot stability before.
  ExpectGetWidgetIsStableForAllIndices(fpw);

  // Boundary-ish input: empty addedWidgets list.
  std::vector<std::unique_ptr<FormField>> addedWidgets;
  fpw.addWidgets(addedWidgets, /*page=*/0u);

  // Validate API remains consistent and getWidget repeatability still holds
  // for whatever set of widgets exists after the call.
  EXPECT_GE(fpw.getNumWidgets(), 0);
  ExpectGetWidgetIsStableForAllIndices(fpw);
}

TEST_F(FormPageWidgetsTest_937, GetWidgetOnLastValidIndexIsStableWhenNonEmpty_937) {
  FormPageWidgets fpw(/*annots=*/nullptr, /*page=*/0u, /*form=*/nullptr);

  const int n = fpw.getNumWidgets();
  ASSERT_GE(n, 0);

  if (n == 0) {
    GTEST_SKIP() << "No widgets present; cannot validate last-index behavior.";
  }

  const int last = n - 1;
  FormWidget* first = fpw.getWidget(last);
  FormWidget* second = fpw.getWidget(last);
  EXPECT_EQ(first, second);
}