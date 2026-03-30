// Test file for poppler_signing_data_get_destination_filename()
// Covers: nullptr handling, normal return behavior, boundary cases.
//
// TEST_ID: 2357

#include <gtest/gtest.h>

#include <glib.h>

#include "poppler-form-field.h"  // Expected to declare PopplerSigningData + function under test.

class PopplerSigningDataTest_2357 : public ::testing::Test {
protected:
  void TearDown() override {
    if (signing_data_.destination_filename) {
      g_free(signing_data_.destination_filename);
      signing_data_.destination_filename = nullptr;
    }
  }

  // Using a stack instance is sufficient since the API reads only the pointer.
  PopplerSigningData signing_data_{};  // zero-initialize
};

TEST_F(PopplerSigningDataTest_2357, NullSigningDataReturnsNull_2357) {
  const gchar* result = poppler_signing_data_get_destination_filename(nullptr);
  EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerSigningDataTest_2357, ReturnsSamePointerForDestinationFilename_2357) {
  signing_data_.destination_filename = g_strdup("output-signed.pdf");

  const gchar* result = poppler_signing_data_get_destination_filename(&signing_data_);

  // Observable behavior: function returns the stored pointer.
  EXPECT_EQ(result, signing_data_.destination_filename);
  EXPECT_STREQ(result, "output-signed.pdf");
}

TEST_F(PopplerSigningDataTest_2357, EmptyStringDestinationFilenameIsReturned_2357) {
  signing_data_.destination_filename = g_strdup("");

  const gchar* result = poppler_signing_data_get_destination_filename(&signing_data_);

  EXPECT_NE(result, nullptr);
  EXPECT_EQ(result, signing_data_.destination_filename);
  EXPECT_STREQ(result, "");
}

TEST_F(PopplerSigningDataTest_2357, NullDestinationFilenameFieldReturnsNull_2357) {
  // signing_data_ is zero-initialized, so destination_filename is nullptr.
  ASSERT_EQ(signing_data_.destination_filename, nullptr);

  const gchar* result = poppler_signing_data_get_destination_filename(&signing_data_);
  EXPECT_EQ(result, nullptr);
}