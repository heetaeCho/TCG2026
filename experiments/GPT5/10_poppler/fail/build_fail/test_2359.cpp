// poppler-form-field-test-2359.cc
#include <gtest/gtest.h>

#include <glib.h>

// Poppler GLib public header (for PopplerRectangle/PopplerColor/PopplerCertificateInfo typedefs)
#include <poppler.h>

// Function under test (provided by the Poppler GLib library/object files).
extern "C" {
const PopplerCertificateInfo *
poppler_signing_data_get_certificate_info(const PopplerSigningData *signing_data);
}

// NOTE:
// The public headers typically treat PopplerSigningData as an opaque type. For the purpose of
// constructing inputs and observing behavior through the public API, we define a compatible struct
// layout here based on the provided snippet, plus the 'certificate_info' member that the function
// accesses. We do not inspect any other internal state via any Poppler APIs.
extern "C" {
struct _PopplerSigningData {
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

  // Accessed by poppler_signing_data_get_certificate_info()
  PopplerCertificateInfo *certificate_info;
};
}

// Helper to capture GLib criticals triggered by g_return_val_if_fail.
namespace {
struct GlibLogCapture {
  GlibLogCapture(const gchar *domain, GLogLevelFlags levels)
      : domain_(domain), levels_(levels) {
    handler_id_ = g_log_set_handler(
        domain_, static_cast<GLogLevelFlags>(levels_),
        &GlibLogCapture::Handler, this);
  }

  ~GlibLogCapture() {
    if (handler_id_ != 0) {
      g_log_remove_handler(domain_, handler_id_);
    }
  }

  bool saw_critical = false;

 private:
  static void Handler(const gchar * /*log_domain*/,
                      GLogLevelFlags log_level,
                      const gchar * /*message*/,
                      gpointer user_data) {
    auto *self = static_cast<GlibLogCapture *>(user_data);
    if (log_level & G_LOG_LEVEL_CRITICAL) {
      self->saw_critical = true;
    }
  }

  const gchar *domain_;
  GLogLevelFlags levels_;
  guint handler_id_ = 0;
};
}  // namespace

class PopplerSigningDataTest_2359 : public ::testing::Test {};

TEST_F(PopplerSigningDataTest_2359, NullSigningDataReturnsNullAndEmitsCritical_2359) {
  // g_return_val_if_fail typically logs a GLib critical.
  GlibLogCapture capture("GLib", static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL));

  const PopplerCertificateInfo *info = poppler_signing_data_get_certificate_info(nullptr);

  EXPECT_EQ(info, nullptr);
  EXPECT_TRUE(capture.saw_critical);
}

TEST_F(PopplerSigningDataTest_2359, CertificateInfoNullReturnsNull_2359) {
  _PopplerSigningData signing_data{};
  signing_data.certificate_info = nullptr;

  const PopplerCertificateInfo *info =
      poppler_signing_data_get_certificate_info(reinterpret_cast<PopplerSigningData *>(&signing_data));

  EXPECT_EQ(info, nullptr);
}

TEST_F(PopplerSigningDataTest_2359, ReturnsSameCertificateInfoPointer_2359) {
  _PopplerSigningData signing_data{};

  // We only need a stable address to compare; the function returns the pointer as-is.
  PopplerCertificateInfo dummy_cert_info{};
  signing_data.certificate_info = &dummy_cert_info;

  const PopplerCertificateInfo *info =
      poppler_signing_data_get_certificate_info(reinterpret_cast<PopplerSigningData *>(&signing_data));

  EXPECT_EQ(info, &dummy_cert_info);
}

TEST_F(PopplerSigningDataTest_2359, WorksWithNonNullSigningDataEvenIfOtherFieldsAreNull_2359) {
  _PopplerSigningData signing_data{};
  // Leave all other fields default/null.
  PopplerCertificateInfo dummy_cert_info{};
  signing_data.certificate_info = &dummy_cert_info;

  const PopplerCertificateInfo *info =
      poppler_signing_data_get_certificate_info(reinterpret_cast<PopplerSigningData *>(&signing_data));

  EXPECT_EQ(info, &dummy_cert_info);
}