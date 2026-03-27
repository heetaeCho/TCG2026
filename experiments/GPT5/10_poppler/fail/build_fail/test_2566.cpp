// poppler_structure_element_get_end_indent_test_2566.cc
#include <gtest/gtest.h>

#include <cmath>

extern "C" {
#include <glib.h>

// Public Poppler GLib API (for the function under test + type declarations)
#include <poppler.h>

// Private header is used only to create a minimal PopplerStructureElement instance
// without relying on any internal behavior (we keep elem == nullptr).
#include "poppler-private.h"
}

class PopplerStructureElementGetEndIndentTest_2566 : public ::testing::Test {
protected:
  void SetUp() override = default;
  void TearDown() override = default;
};

TEST_F(PopplerStructureElementGetEndIndentTest_2566, NullElementReturnsNaN_2566) {
  // Boundary / error case: nullptr input.
  // Observable behavior from interface: returns NAN when precondition fails.
  const gdouble v = poppler_structure_element_get_end_indent(nullptr);
  EXPECT_TRUE(std::isnan(static_cast<double>(v)));
}

TEST_F(PopplerStructureElementGetEndIndentTest_2566,
       ElementWithNullInnerElemReturnsNaN_2566) {
  // Boundary / error case: a PopplerStructureElement instance that is not a block
  // (elem is null -> should fail the "is_block" precondition).
  PopplerStructureElement se{};
  se.elem = nullptr;

  const gdouble v = poppler_structure_element_get_end_indent(&se);
  EXPECT_TRUE(std::isnan(static_cast<double>(v)));
}

TEST_F(PopplerStructureElementGetEndIndentTest_2566,
       ReturnValueIsNaNAndDoesNotModifyInput_2566) {
  // Additional boundary: repeated calls should be safe and consistently return NAN
  // for a non-block element (as observable through the return value).
  PopplerStructureElement se{};
  se.elem = nullptr;

  const gdouble v1 = poppler_structure_element_get_end_indent(&se);
  const gdouble v2 = poppler_structure_element_get_end_indent(&se);

  EXPECT_TRUE(std::isnan(static_cast<double>(v1)));
  EXPECT_TRUE(std::isnan(static_cast<double>(v2)));

  // Keep the only field we can legally observe (since we included the struct definition)
  // unchanged for this minimal non-block case.
  EXPECT_EQ(se.elem, nullptr);
}