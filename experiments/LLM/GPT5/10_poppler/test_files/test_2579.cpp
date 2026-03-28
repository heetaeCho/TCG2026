// poppler_structure_element_get_text_decoration_thickness_test_2579.cc

#include <gtest/gtest.h>

#include <cmath>   // std::isnan, NAN
#include <limits>

// Poppler GLib headers
#include <poppler.h>

// We need the struct definition to be able to build a minimal instance.
// (This is provided in the prompt as a known dependency.)
#include "poppler-private.h"

namespace {

class PopplerStructureElementThicknessTest_2579 : public ::testing::Test {
protected:
  static bool IsNaN(double v) { return std::isnan(v); }
};

TEST_F(PopplerStructureElementThicknessTest_2579, NullPointerReturnsNaN_2579) {
  // Observable behavior: precondition fails -> returns NAN (via g_return_val_if_fail).
  const gdouble thickness =
      poppler_structure_element_get_text_decoration_thickness(nullptr);
  EXPECT_TRUE(IsNaN(thickness));
}

TEST_F(PopplerStructureElementThicknessTest_2579, NullElemFieldReturnsNaN_2579) {
  // Construct a minimal PopplerStructureElement with elem == nullptr.
  // This should not satisfy "is_inline", so the function should return NAN.
  PopplerStructureElement element;
  element.elem = nullptr;

  const gdouble thickness =
      poppler_structure_element_get_text_decoration_thickness(&element);
  EXPECT_TRUE(IsNaN(thickness));
}

TEST_F(PopplerStructureElementThicknessTest_2579,
       RepeatedCallsOnInvalidElementStayNaN_2579) {
  PopplerStructureElement element;
  element.elem = nullptr;

  const gdouble t1 =
      poppler_structure_element_get_text_decoration_thickness(&element);
  const gdouble t2 =
      poppler_structure_element_get_text_decoration_thickness(&element);
  const gdouble t3 =
      poppler_structure_element_get_text_decoration_thickness(&element);

  EXPECT_TRUE(IsNaN(t1));
  EXPECT_TRUE(IsNaN(t2));
  EXPECT_TRUE(IsNaN(t3));
}

}  // namespace