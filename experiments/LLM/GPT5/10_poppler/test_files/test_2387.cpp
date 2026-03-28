// poppler-signing-data-get-image-path-test-2387.cc
#include <gtest/gtest.h>

#include "poppler-form-field.h" // Provides PopplerSigningData and poppler_signing_data_get_image_path

// The production struct layout is provided in the prompt; we use it only to build
// a concrete PopplerSigningData instance for black-box testing of the public API.
// We do NOT test or rely on any other fields' semantics.
struct _PopplerSigningData {
  char* destination_filename;
  char* signature_text;
  char* signature_text_left;
  PopplerRectangle signature_rect;
  int left_font_size;
  PopplerColor border_color;
  int border_width;
  PopplerColor background_color;
  char* field_partial_name;
  char* reason;
  char* location;
  char* image_path;
  char* password;
  char* document_owner_password;
  char* document_user_password;
};

class PopplerSigningDataGetImagePathTest_2387 : public ::testing::Test {};

TEST_F(PopplerSigningDataGetImagePathTest_2387, NullSigningDataReturnsNull_2387) {
  // Observable behavior: g_return_val_if_fail(signing_data != nullptr, nullptr)
  EXPECT_EQ(poppler_signing_data_get_image_path(nullptr), nullptr);
}

TEST_F(PopplerSigningDataGetImagePathTest_2387, ReturnsSamePointerWhenImagePathSet_2387) {
  _PopplerSigningData data{};
  const char kPath[] = "/tmp/sig.png";
  data.image_path = const_cast<char*>(kPath);

  const PopplerSigningData* signing_data = reinterpret_cast<const PopplerSigningData*>(&data);

  const gchar* result = poppler_signing_data_get_image_path(signing_data);
  EXPECT_EQ(result, kPath); // pointer equality is the observable contract here
}

TEST_F(PopplerSigningDataGetImagePathTest_2387, ReturnsNullWhenImagePathIsNull_2387) {
  _PopplerSigningData data{};
  data.image_path = nullptr;

  const PopplerSigningData* signing_data = reinterpret_cast<const PopplerSigningData*>(&data);

  EXPECT_EQ(poppler_signing_data_get_image_path(signing_data), nullptr);
}

TEST_F(PopplerSigningDataGetImagePathTest_2387, EmptyStringImagePathIsReturnedAsIs_2387) {
  _PopplerSigningData data{};
  // Boundary condition: empty C string (non-null pointer)
  const char kEmpty[] = "";
  data.image_path = const_cast<char*>(kEmpty);

  const PopplerSigningData* signing_data = reinterpret_cast<const PopplerSigningData*>(&data);

  const gchar* result = poppler_signing_data_get_image_path(signing_data);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "");
}

TEST_F(PopplerSigningDataGetImagePathTest_2387, VeryLongStringPointerIsReturnedAsIs_2387) {
  _PopplerSigningData data{};

  // Boundary condition: long string; we only assert it is returned unchanged.
  static char long_path[4096];
  for (size_t i = 0; i + 1 < sizeof(long_path); ++i) long_path[i] = 'a';
  long_path[sizeof(long_path) - 1] = '\0';

  data.image_path = long_path;

  const PopplerSigningData* signing_data = reinterpret_cast<const PopplerSigningData*>(&data);

  const gchar* result = poppler_signing_data_get_image_path(signing_data);
  EXPECT_EQ(result, long_path);
  EXPECT_EQ(result[0], 'a');
  EXPECT_EQ(result[sizeof(long_path) - 2], 'a');
  EXPECT_EQ(result[sizeof(long_path) - 1], '\0');
}