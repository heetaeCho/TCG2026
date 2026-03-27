// poppler_signing_data_set_background_color_test.cpp
// Unit tests for poppler_signing_data_set_background_color()
// TEST_ID: 2378

#include <gtest/gtest.h>

#include <glib.h>

#include <climits>
#include <cstring>

// --- Minimal type declarations based on the provided snippets ---
// NOTE: We intentionally do not test any behavior beyond what is observable
// through the provided interface and GLib's g_return_if_fail() logging.

extern "C" {

struct _PopplerColor {
  int red;
  int green;
  int blue;
};
typedef struct _PopplerColor PopplerColor;

// PopplerRectangle is part of Poppler's public GLib API in real codebases.
// It's included here only to match the provided _PopplerSigningData layout.
struct _PopplerRectangle {
  double x1;
  double y1;
  double x2;
  double y2;
};
typedef struct _PopplerRectangle PopplerRectangle;

struct _PopplerSigningData {
public:
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
typedef struct _PopplerSigningData PopplerSigningData;

void poppler_signing_data_set_background_color(PopplerSigningData* signing_data,
                                               const PopplerColor* background_color);

}  // extern "C"

namespace {

class PopplerSigningDataSetBackgroundColorTest_2378 : public ::testing::Test {
protected:
  static PopplerColor MakeColor(int r, int g, int b) {
    PopplerColor c;
    c.red = r;
    c.green = g;
    c.blue = b;
    return c;
  }
};

TEST_F(PopplerSigningDataSetBackgroundColorTest_2378, CopiesColorValues_2378) {
  PopplerSigningData data{};
  // Seed with sentinel values.
  data.background_color = MakeColor(1, 2, 3);

  const PopplerColor new_color = MakeColor(100, 200, 300);

  poppler_signing_data_set_background_color(&data, &new_color);

  EXPECT_EQ(data.background_color.red, 100);
  EXPECT_EQ(data.background_color.green, 200);
  EXPECT_EQ(data.background_color.blue, 300);
}

TEST_F(PopplerSigningDataSetBackgroundColorTest_2378, OverwritesPreviousColor_2378) {
  PopplerSigningData data{};
  data.background_color = MakeColor(-7, -8, -9);

  const PopplerColor first = MakeColor(10, 20, 30);
  const PopplerColor second = MakeColor(40, 50, 60);

  poppler_signing_data_set_background_color(&data, &first);
  EXPECT_EQ(data.background_color.red, 10);
  EXPECT_EQ(data.background_color.green, 20);
  EXPECT_EQ(data.background_color.blue, 30);

  poppler_signing_data_set_background_color(&data, &second);
  EXPECT_EQ(data.background_color.red, 40);
  EXPECT_EQ(data.background_color.green, 50);
  EXPECT_EQ(data.background_color.blue, 60);
}

TEST_F(PopplerSigningDataSetBackgroundColorTest_2378, AcceptsBoundaryIntValues_2378) {
  PopplerSigningData data{};
  data.background_color = MakeColor(0, 0, 0);

  const PopplerColor boundary = MakeColor(INT_MIN, 0, INT_MAX);

  poppler_signing_data_set_background_color(&data, &boundary);

  EXPECT_EQ(data.background_color.red, INT_MIN);
  EXPECT_EQ(data.background_color.green, 0);
  EXPECT_EQ(data.background_color.blue, INT_MAX);
}

TEST_F(PopplerSigningDataSetBackgroundColorTest_2378,
       NullBackgroundColorEmitsCriticalAndDoesNotModify_2378) {
  PopplerSigningData data{};
  data.background_color = MakeColor(11, 22, 33);

  // g_return_if_fail(background_color != nullptr) should log a CRITICAL and return.
  g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL,
                        "*background_color !=*NULL*");

  poppler_signing_data_set_background_color(&data, nullptr);

  g_test_assert_expected_messages();

  // Must remain unchanged if the function returns early.
  EXPECT_EQ(data.background_color.red, 11);
  EXPECT_EQ(data.background_color.green, 22);
  EXPECT_EQ(data.background_color.blue, 33);
}

TEST_F(PopplerSigningDataSetBackgroundColorTest_2378,
       NullSigningDataEmitsCritical_2378) {
  const PopplerColor c = MakeColor(1, 1, 1);

  // g_return_if_fail(signing_data != nullptr) should log a CRITICAL and return.
  g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL,
                        "*signing_data !=*NULL*");

  poppler_signing_data_set_background_color(nullptr, &c);

  g_test_assert_expected_messages();
}

}  // namespace