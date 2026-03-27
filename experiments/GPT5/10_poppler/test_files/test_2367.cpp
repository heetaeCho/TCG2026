// poppler_signing_data_get_signature_rectangle_test.cc
#include <gtest/gtest.h>

#include "poppler-form-field.h" // Adjust include path if needed

// The function under test is a C API symbol. We only test observable behavior via the interface.

namespace {

TEST(PopplerSigningDataGetSignatureRectangleTest_2367,
     NullSigningDataReturnsNull_2367) {
  // Boundary / error case: g_return_val_if_fail should return nullptr.
  const PopplerRectangle* rect =
      poppler_signing_data_get_signature_rectangle(nullptr);
  EXPECT_EQ(rect, nullptr);
}

TEST(PopplerSigningDataGetSignatureRectangleTest_2367,
     ReturnsNonNullPointerForValidSigningData_2367) {
  // Normal operation: should return a non-null pointer when signing_data is valid.
  // We avoid relying on internal layout; we just need a valid object instance.
  PopplerSigningData signing_data{};
  const PopplerRectangle* rect =
      poppler_signing_data_get_signature_rectangle(&signing_data);
  EXPECT_NE(rect, nullptr);
}

TEST(PopplerSigningDataGetSignatureRectangleTest_2367,
     ReturnsStablePointerAcrossMultipleCalls_2367) {
  // Observable behavior: repeated calls with the same object should return
  // the same address (it returns a pointer to a member).
  PopplerSigningData signing_data{};
  const PopplerRectangle* rect1 =
      poppler_signing_data_get_signature_rectangle(&signing_data);
  const PopplerRectangle* rect2 =
      poppler_signing_data_get_signature_rectangle(&signing_data);

  ASSERT_NE(rect1, nullptr);
  ASSERT_NE(rect2, nullptr);
  EXPECT_EQ(rect1, rect2);
}

TEST(PopplerSigningDataGetSignatureRectangleTest_2367,
     ReturnedPointerMatchesUnderlyingMemberAddress_2367) {
  // Boundary/consistency: since PopplerSigningData is an exposed struct type in
  // the GLib API, it is valid to compare to the public member address.
  // This does not access private state; it's part of the public struct layout.
  PopplerSigningData signing_data{};
  const PopplerRectangle* rect =
      poppler_signing_data_get_signature_rectangle(&signing_data);

  ASSERT_NE(rect, nullptr);
  EXPECT_EQ(rect, &signing_data.signature_rect);
}

}  // namespace