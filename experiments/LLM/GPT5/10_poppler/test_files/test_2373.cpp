// poppler_signing_data_get_left_font_size_test.cpp
#include <gtest/gtest.h>

#include <glib.h>

// Include the public Poppler GLib header(s) that declare PopplerSigningData.
// Adjust include path if your project uses a different umbrella header.
#include <poppler.h>

// The function under test is implemented in poppler-form-field.cc.
// We only rely on its public signature.
extern "C" {
gdouble poppler_signing_data_get_left_font_size(const PopplerSigningData *signing_data);
}

class PopplerSigningDataGetLeftFontSizeTest_2373 : public ::testing::Test {};

// Normal operation: for a valid signing_data, the function should return a finite double.
// (We do not assume any internal field layout or specific value because the type is opaque
// from the public interface perspective.)
TEST_F(PopplerSigningDataGetLeftFontSizeTest_2373, ReturnsFiniteForNonNull_2373) {
  // Allocate some memory to serve as an opaque PopplerSigningData pointer.
  // We do NOT assume any struct fields; we just need a non-null pointer.
  gpointer mem = g_malloc0(64);
  ASSERT_NE(mem, nullptr);

  const PopplerSigningData *sd = static_cast<const PopplerSigningData *>(mem);

  const gdouble v = poppler_signing_data_get_left_font_size(sd);

  EXPECT_TRUE(std::isfinite(v));

  g_free(mem);
}

// Boundary / error case: nullptr input should return the documented/default value 12.0.
TEST_F(PopplerSigningDataGetLeftFontSizeTest_2373, NullReturnsDefault12_2373) {
  const gdouble v = poppler_signing_data_get_left_font_size(nullptr);
  EXPECT_DOUBLE_EQ(v, 12.0);
}

// Boundary condition: ensure the function is stable across repeated calls for the same pointer.
// (Observable behavior: for the same input pointer, it should return the same value.)
TEST_F(PopplerSigningDataGetLeftFontSizeTest_2373, RepeatedCallsReturnSameValueForSamePointer_2373) {
  gpointer mem = g_malloc0(64);
  ASSERT_NE(mem, nullptr);

  const PopplerSigningData *sd = static_cast<const PopplerSigningData *>(mem);

  const gdouble v1 = poppler_signing_data_get_left_font_size(sd);
  const gdouble v2 = poppler_signing_data_get_left_font_size(sd);
  const gdouble v3 = poppler_signing_data_get_left_font_size(sd);

  EXPECT_DOUBLE_EQ(v1, v2);
  EXPECT_DOUBLE_EQ(v2, v3);

  g_free(mem);
}