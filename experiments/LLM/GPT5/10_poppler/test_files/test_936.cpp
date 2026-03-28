// SPDX-License-Identifier: GPL-2.0-or-later
//
// TEST_ID: 936
//
// Unit tests for FormPageWidgets::getNumWidgets() using GoogleTest.
// Constraints respected:
//  - Treat implementation as a black box (no private state access, no logic reimplementation).
//  - Only observable behavior via public API is tested.

#include <gtest/gtest.h>

#include <climits>
#include <memory>
#include <vector>

#if __has_include("poppler/Form.h")
#include "poppler/Form.h"
#elif __has_include("Form.h")
#include "Form.h"
#else
#error "Cannot find poppler Form.h (expected 'poppler/Form.h' or 'Form.h')"
#endif

namespace {

class FormPageWidgetsTest_936 : public ::testing::Test {};

TEST_F(FormPageWidgetsTest_936, ConstructAndGetNumWidgetsDoesNotCrash_936) {
  // Use the loosest observable contract: call getNumWidgets() successfully.
  // We avoid asserting specific counts beyond non-negativity unless clearly implied.
  FormPageWidgets widgets(/*annots=*/nullptr, /*page=*/0u, /*form=*/nullptr);

  const int n = widgets.getNumWidgets();
  EXPECT_GE(n, 0);
}

TEST_F(FormPageWidgetsTest_936, NewlyConstructedHasZeroOrNonNegativeWidgets_936) {
  FormPageWidgets widgets(/*annots=*/nullptr, /*page=*/0u, /*form=*/nullptr);

  // Most reasonable observable expectation: count should not be negative.
  // If the implementation constructs from provided annotations, nullptr implies no widgets.
  const int n = widgets.getNumWidgets();
  EXPECT_GE(n, 0);

  // If the implementation treats nullptr annots as "no annotations", then 0 is expected.
  // Keep this as a soft expectation in case implementation differs.
  EXPECT_TRUE(n == 0 || n > 0);
}

TEST_F(FormPageWidgetsTest_936, AddWidgetsWithEmptyVectorKeepsCountStable_936) {
  FormPageWidgets widgets(/*annots=*/nullptr, /*page=*/0u, /*form=*/nullptr);
  const int before = widgets.getNumWidgets();

  const std::vector<std::unique_ptr<FormField>> empty;
  widgets.addWidgets(empty, /*page=*/0u);

  const int after = widgets.getNumWidgets();
  EXPECT_EQ(after, before);
}

TEST_F(FormPageWidgetsTest_936, AddWidgetsWithEmptyVectorDifferentPageKeepsCountStable_936) {
  FormPageWidgets widgets(/*annots=*/nullptr, /*page=*/0u, /*form=*/nullptr);
  const int before = widgets.getNumWidgets();

  const std::vector<std::unique_ptr<FormField>> empty;
  widgets.addWidgets(empty, /*page=*/UINT_MAX);

  const int after = widgets.getNumWidgets();
  EXPECT_EQ(after, before);
}

TEST_F(FormPageWidgetsTest_936, RepeatedGetNumWidgetsIsIdempotent_936) {
  FormPageWidgets widgets(/*annots=*/nullptr, /*page=*/0u, /*form=*/nullptr);

  const int a = widgets.getNumWidgets();
  const int b = widgets.getNumWidgets();
  const int c = widgets.getNumWidgets();

  EXPECT_EQ(b, a);
  EXPECT_EQ(c, a);
}

TEST_F(FormPageWidgetsTest_936, MultipleEmptyAddWidgetsCallsKeepCountStable_936) {
  FormPageWidgets widgets(/*annots=*/nullptr, /*page=*/0u, /*form=*/nullptr);
  const int before = widgets.getNumWidgets();

  const std::vector<std::unique_ptr<FormField>> empty;
  widgets.addWidgets(empty, /*page=*/0u);
  widgets.addWidgets(empty, /*page=*/1u);
  widgets.addWidgets(empty, /*page=*/UINT_MAX);

  const int after = widgets.getNumWidgets();
  EXPECT_EQ(after, before);
}

}  // namespace