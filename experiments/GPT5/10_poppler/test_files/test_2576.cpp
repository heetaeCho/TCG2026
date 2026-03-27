// File: poppler-structure-element-baseline-shift-test_2576.cc
//
// Unit tests for:
//   gdouble poppler_structure_element_get_baseline_shift(PopplerStructureElement *poppler_structure_element)
//
// Constraints honored:
// - Treat implementation as a black box
// - No private state inspection (only using public API + safe construction for boundary/error inputs)
// - Focus on observable behavior (return value: NaN on failed precondition)

#include <gtest/gtest.h>

#include <cmath>

// GLib / Poppler GLib
#include <glib.h>

// The public Poppler GLib header should declare PopplerStructureElement and the function under test.
#include <poppler.h>

// The project provides this private header in-tree (as shown in the prompt) which exposes the
// incomplete struct layout. We only use it to safely construct boundary inputs (elem == nullptr),
// not to inspect or depend on internal logic.
#include "poppler-private.h"

namespace {

class PopplerStructureElementBaselineShiftTest_2576 : public ::testing::Test {
protected:
  static void ExpectIsNaN(gdouble v) { EXPECT_TRUE(std::isnan(static_cast<double>(v))); }
};

} // namespace

TEST_F(PopplerStructureElementBaselineShiftTest_2576, NullElementReturnsNaN_2576)
{
  // Observable behavior: g_return_val_if_fail(...) returns NAN on failed precondition.
  gdouble v = poppler_structure_element_get_baseline_shift(nullptr);
  ExpectIsNaN(v);
}

TEST_F(PopplerStructureElementBaselineShiftTest_2576, ElementWithNullInnerStructElementReturnsNaN_2576)
{
  // Construct a boundary PopplerStructureElement where the wrapped StructElement* is null.
  // The function under test checks an "is_inline" precondition; for an invalid/non-inline element,
  // it must return NAN (observable behavior).
  _PopplerStructureElement fake {};
  fake.elem = nullptr;

  gdouble v = poppler_structure_element_get_baseline_shift(reinterpret_cast<PopplerStructureElement *>(&fake));
  ExpectIsNaN(v);
}

TEST_F(PopplerStructureElementBaselineShiftTest_2576, MultipleCallsWithInvalidElementRemainStable_2576)
{
  // Boundary: repeated calls should be safe and consistently return NAN for invalid inputs.
  _PopplerStructureElement fake {};
  fake.elem = nullptr;
  auto *pe = reinterpret_cast<PopplerStructureElement *>(&fake);

  gdouble v1 = poppler_structure_element_get_baseline_shift(pe);
  gdouble v2 = poppler_structure_element_get_baseline_shift(pe);

  ExpectIsNaN(v1);
  ExpectIsNaN(v2);
}