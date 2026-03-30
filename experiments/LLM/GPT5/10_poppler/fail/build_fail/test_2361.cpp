// File: poppler-signing-data-get-page-test-2361.cc

#include <gtest/gtest.h>

#include <climits>
#include <cstring>

#include <glib.h>

// Try to include real Poppler GLib headers if available.
#if __has_include(<poppler.h>)
#include <poppler.h>
#endif
#if __has_include(<poppler-form-field.h>)
#include <poppler-form-field.h>
#endif

// If the build environment doesn't provide PopplerSigningData in headers,
// fall back to a minimal compatible declaration for compiling the tests.
// NOTE: This is only to satisfy compilation; the implementation under test is
// treated as a black box, and tests assert only observable behavior.
#ifndef POPPLER_SIGNING_DATA_FALLBACK_2361
#define POPPLER_SIGNING_DATA_FALLBACK_2361

// Detect whether PopplerSigningData is already declared.
#if !defined(POPPLER_TYPE_SIGNING_DATA) && !defined(__POPPLER_SIGNING_DATA_H__) && !defined(_POPPLER_SIGNING_DATA_DEFINED)
extern "C" {

// Minimal structs if Poppler types are not present.
#ifndef POPPLER_RECTANGLE_DEFINED_2361
#define POPPLER_RECTANGLE_DEFINED_2361
typedef struct _PopplerRectangle {
  double x1;
  double y1;
  double x2;
  double y2;
} PopplerRectangle;
#endif

#ifndef POPPLER_COLOR_DEFINED_2361
#define POPPLER_COLOR_DEFINED_2361
typedef struct _PopplerColor {
  guint16 red;
  guint16 green;
  guint16 blue;
} PopplerColor;
#endif

typedef struct _PopplerSigningData PopplerSigningData;

// Matches the dependency snippet (plus `page`, which the function reads).
struct _PopplerSigningData {
public:
  char *destination_filename;
  char *signature_text;
  char *signature_text_left;
  PopplerRectangle signature_rect;
  int left_font_size;
  PopplerColor border_color;
  int border_width;
  PopplerColor background_color;
  char *field_partial_name;
  char *reason;
  char *location;
  char *image_path;
  char *password;
  char *document_owner_password;
  char *document_user_password;

  // The implementation under test returns signing_data->page.
  int page;
};

// Function under test (provided by the library/translation unit).
int poppler_signing_data_get_page(const PopplerSigningData *signing_data);

} // extern "C"
#endif
#endif  // POPPLER_SIGNING_DATA_FALLBACK_2361

namespace {

class ScopedGlibCriticalTrap_2361 {
public:
  ScopedGlibCriticalTrap_2361()
      : hit_(false) {
    handler_id_ = g_log_set_handler(
        "GLib",
        static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL),
        &ScopedGlibCriticalTrap_2361::HandlerThunk,
        this);
  }

  ~ScopedGlibCriticalTrap_2361() {
    if (handler_id_ != 0) {
      g_log_remove_handler("GLib", handler_id_);
    }
  }

  bool hit() const { return hit_; }

private:
  static void HandlerThunk(const gchar * /*log_domain*/,
                           GLogLevelFlags /*log_level*/,
                           const gchar * /*message*/,
                           gpointer user_data) {
    auto *self = static_cast<ScopedGlibCriticalTrap_2361 *>(user_data);
    self->hit_ = true;
  }

  guint handler_id_{0};
  bool hit_;
};

class PopplerSigningDataGetPageTest_2361 : public ::testing::Test {
protected:
  void SetUp() override {
    signing_data_ = g_new0(PopplerSigningData, 1);
  }

  void TearDown() override {
    g_free(signing_data_);
    signing_data_ = nullptr;
  }

  PopplerSigningData *signing_data_{nullptr};
};

}  // namespace

TEST_F(PopplerSigningDataGetPageTest_2361, NullReturnsZeroAndEmitsCritical_2361) {
  ScopedGlibCriticalTrap_2361 trap;

  const int page = poppler_signing_data_get_page(nullptr);

  EXPECT_EQ(page, 0);
  // g_return_val_if_fail typically emits a GLib critical.
  EXPECT_TRUE(trap.hit());
}

TEST_F(PopplerSigningDataGetPageTest_2361, ReturnsStoredPageForTypicalValue_2361) {
  signing_data_->page = 3;

  EXPECT_EQ(poppler_signing_data_get_page(signing_data_), 3);
}

TEST_F(PopplerSigningDataGetPageTest_2361, BoundaryAllowsZeroPage_2361) {
  signing_data_->page = 0;

  EXPECT_EQ(poppler_signing_data_get_page(signing_data_), 0);
}

TEST_F(PopplerSigningDataGetPageTest_2361, BoundaryAllowsNegativePage_2361) {
  signing_data_->page = -1;

  EXPECT_EQ(poppler_signing_data_get_page(signing_data_), -1);
}

TEST_F(PopplerSigningDataGetPageTest_2361, BoundaryAllowsMaxIntPage_2361) {
  signing_data_->page = INT_MAX;

  EXPECT_EQ(poppler_signing_data_get_page(signing_data_), INT_MAX);
}

TEST_F(PopplerSigningDataGetPageTest_2361, BoundaryAllowsMinIntPage_2361) {
  signing_data_->page = INT_MIN;

  EXPECT_EQ(poppler_signing_data_get_page(signing_data_), INT_MIN);
}