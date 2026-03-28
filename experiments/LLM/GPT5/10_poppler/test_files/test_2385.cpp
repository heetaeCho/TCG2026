// poppler-signing-data-get-location-test.cc
#include <gtest/gtest.h>

#include <glib.h>

#include "poppler-form-field.h" // Provides PopplerSigningData and poppler_signing_data_get_location()

namespace {

class PopplerSigningDataGetLocationTest_2385 : public ::testing::Test {};

TEST_F(PopplerSigningDataGetLocationTest_2385, NullSigningDataReturnsNull_2385) {
  // Boundary / error case: g_return_val_if_fail should return nullptr when signing_data is null.
  const gchar* location = poppler_signing_data_get_location(nullptr);
  EXPECT_EQ(location, nullptr);
}

TEST_F(PopplerSigningDataGetLocationTest_2385, ValidSigningDataReturnsPointer_2385) {
  // Normal operation: returns the stored location pointer.
  PopplerSigningData data{};
  data.location = const_cast<char*>("Seoul");

  const gchar* location = poppler_signing_data_get_location(&data);
  EXPECT_NE(location, nullptr);
  EXPECT_STREQ(location, "Seoul");
}

TEST_F(PopplerSigningDataGetLocationTest_2385, LocationCanBeNullAndIsReturnedAsNull_2385) {
  // Boundary condition: location field itself may be null; function should return it as-is.
  PopplerSigningData data{};
  data.location = nullptr;

  const gchar* location = poppler_signing_data_get_location(&data);
  EXPECT_EQ(location, nullptr);
}

TEST_F(PopplerSigningDataGetLocationTest_2385, ReturnsExactPointerNotACopy_2385) {
  // Observable behavior: returns the exact pointer stored in the struct (no copying observable).
  PopplerSigningData data{};
  gchar buf[] = "Busan";
  data.location = buf;

  const gchar* location = poppler_signing_data_get_location(&data);
  EXPECT_EQ(location, buf);
  EXPECT_STREQ(location, "Busan");
}

}  // namespace