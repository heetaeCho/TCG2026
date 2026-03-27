// poppler_signing_data_set_left_font_size_test.cc
//
// Unit tests for:
//   void poppler_signing_data_set_left_font_size(PopplerSigningData *signing_data,
//                                                gdouble left_font_size);
//
// Constraints respected:
// - No re-implementation beyond using the public signature and observable effects.
// - Uses GLib log capturing to verify g_return_if_fail() behavior on nullptr.
// - Covers normal, boundary, and error/exceptional (observable) cases.

#include <gtest/gtest.h>

#include <glib.h>

// Include the implementation's public header(s) as they exist in your tree.
// Adjust include paths if your build uses different include roots.
#include "poppler.h"
#include "poppler-form-field.h"

// If PopplerSigningData is opaque in your build and this test does not compile,
// you should include the internal header that exposes _PopplerSigningData for tests.
// The prompt provided the struct layout; we DO NOT redefine it here to avoid ODR issues,
// and instead assume your test build can see the real definition via headers.

namespace {

// Simple GLib log capture for CRITICAL messages (e.g., g_return_if_fail failures).
class GlibCriticalLogCapture {
public:
  GlibCriticalLogCapture() {
    // Capture default domain (nullptr) critical logs.
    default_handler_id_ =
        g_log_set_handler(nullptr,
                          static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL),
                          &GlibCriticalLogCapture::Handler,
                          this);

    // Also capture common Poppler domain if used.
    poppler_handler_id_ =
        g_log_set_handler("Poppler",
                          static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL),
                          &GlibCriticalLogCapture::Handler,
                          this);
  }

  ~GlibCriticalLogCapture() {
    if (default_handler_id_ != 0) {
      g_log_remove_handler(nullptr, default_handler_id_);
    }
    if (poppler_handler_id_ != 0) {
      g_log_remove_handler("Poppler", poppler_handler_id_);
    }
  }

  int critical_count() const { return critical_count_; }
  const gchar* last_domain() const { return last_domain_.empty() ? nullptr : last_domain_.c_str(); }
  const gchar* last_message() const { return last_message_.empty() ? nullptr : last_message_.c_str(); }

private:
  static void Handler(const gchar* log_domain,
                      GLogLevelFlags log_level,
                      const gchar* message,
                      gpointer user_data) {
    auto* self = static_cast<GlibCriticalLogCapture*>(user_data);
    if ((log_level & G_LOG_LEVEL_CRITICAL) == 0) {
      return;
    }
    self->critical_count_++;
    self->last_domain_ = (log_domain != nullptr) ? log_domain : "";
    self->last_message_ = (message != nullptr) ? message : "";
  }

  guint default_handler_id_ = 0;
  guint poppler_handler_id_ = 0;
  int critical_count_ = 0;
  std::string last_domain_;
  std::string last_message_;
};

class PopplerSigningDataSetLeftFontSizeTest_2372 : public ::testing::Test {
protected:
  void SetUp() override {
    // Allocate a zeroed instance so fields start deterministic for tests.
    // This assumes PopplerSigningData is a plain struct type in this build.
    signing_data_ = static_cast<PopplerSigningData*>(g_malloc0(sizeof(*signing_data_)));
    ASSERT_NE(signing_data_, nullptr);

    // Set a known starting value for the observable field.
    signing_data_->left_font_size = 10;
  }

  void TearDown() override {
    g_free(signing_data_);
    signing_data_ = nullptr;
  }

  PopplerSigningData* signing_data_ = nullptr;
};

TEST_F(PopplerSigningDataSetLeftFontSizeTest_2372, NullSigningData_EmitsCriticalAndDoesNotCrash_2372) {
  GlibCriticalLogCapture capture;

  // Should not crash; should emit a CRITICAL log due to g_return_if_fail.
  poppler_signing_data_set_left_font_size(nullptr, 12.0);

  EXPECT_GE(capture.critical_count(), 1);
}

TEST_F(PopplerSigningDataSetLeftFontSizeTest_2372, ZeroFontSize_DoesNotChangeExistingValue_2372) {
  ASSERT_EQ(signing_data_->left_font_size, 10);

  poppler_signing_data_set_left_font_size(signing_data_, 0.0);

  // Observable behavior: value remains unchanged for non-positive input.
  EXPECT_EQ(signing_data_->left_font_size, 10);
}

TEST_F(PopplerSigningDataSetLeftFontSizeTest_2372, NegativeFontSize_DoesNotChangeExistingValue_2372) {
  ASSERT_EQ(signing_data_->left_font_size, 10);

  poppler_signing_data_set_left_font_size(signing_data_, -1.0);

  // Observable behavior: value remains unchanged for non-positive input.
  EXPECT_EQ(signing_data_->left_font_size, 10);
}

TEST_F(PopplerSigningDataSetLeftFontSizeTest_2372, PositiveFontSize_UpdatesValue_2372) {
  ASSERT_EQ(signing_data_->left_font_size, 10);

  poppler_signing_data_set_left_font_size(signing_data_, 12.0);

  EXPECT_EQ(signing_data_->left_font_size, 12);
}

TEST_F(PopplerSigningDataSetLeftFontSizeTest_2372, BoundarySmallPositiveFontSize_UpdatesValue_2372) {
  // Use a small *but still representable as int once assigned* positive value.
  // Keeping it integral avoids relying on any float->int rounding details.
  signing_data_->left_font_size = 2;

  poppler_signing_data_set_left_font_size(signing_data_, 1.0);

  EXPECT_EQ(signing_data_->left_font_size, 1);
}

TEST_F(PopplerSigningDataSetLeftFontSizeTest_2372, LargerPositiveFontSize_UpdatesValue_2372) {
  // Boundary-ish within typical UI ranges; also safe for int.
  signing_data_->left_font_size = 10;

  poppler_signing_data_set_left_font_size(signing_data_, 1000.0);

  EXPECT_EQ(signing_data_->left_font_size, 1000);
}

}  // namespace