// File: poppler-certificate-info-get-issuance-time-test_2402.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <string.h>

// ---- Minimal interface declarations (from provided snippet) ----
extern "C" {

struct _PopplerCertificateInfo {
  char* id;
  char* subject_common_name;
  char* subject_organization;
  char* subject_email;
  char* issuer_common_name;
  char* issuer_organization;
  char* issuer_email;

  // The provided "Known or Inferred Dependencies" snippet shows `int* issued`,
  // but the function under test returns `GDateTime*` and the implementation
  // returns `certificate_info->issued`. For testing observable behavior, we
  // model this as `GDateTime*` so we can create real GDateTime instances.
  GDateTime* issued;
  GDateTime* expires;
};

typedef struct _PopplerCertificateInfo PopplerCertificateInfo;

GDateTime* poppler_certificate_info_get_issuance_time(
    const PopplerCertificateInfo* certificate_info);

}  // extern "C"

// ---- Helper to capture GLib critical logs from g_return_val_if_fail ----
class ScopedGLogCatcher {
 public:
  ScopedGLogCatcher(const char* domain, GLogLevelFlags levels)
      : domain_(domain), levels_(levels) {
    handler_id_ = g_log_set_handler(domain_, levels_, &ScopedGLogCatcher::Handler, this);
  }

  ~ScopedGLogCatcher() {
    if (handler_id_ != 0) {
      g_log_remove_handler(domain_, handler_id_);
    }
  }

  const std::string& last_message() const { return last_message_; }
  int count() const { return count_; }

 private:
  static void Handler(const gchar* /*log_domain*/,
                      GLogLevelFlags /*log_level*/,
                      const gchar* message,
                      gpointer user_data) {
    auto* self = static_cast<ScopedGLogCatcher*>(user_data);
    self->count_++;
    self->last_message_ = message ? message : "";
  }

  const char* domain_;
  GLogLevelFlags levels_;
  guint handler_id_{0};
  int count_{0};
  std::string last_message_;
};

class PopplerCertificateInfoGetIssuanceTimeTest_2402 : public ::testing::Test {
 protected:
  void SetUp() override { memset(&info_, 0, sizeof(info_)); }

  void TearDown() override {
    if (info_.issued) {
      g_date_time_unref(info_.issued);
      info_.issued = nullptr;
    }
    if (info_.expires) {
      g_date_time_unref(info_.expires);
      info_.expires = nullptr;
    }
  }

  PopplerCertificateInfo info_{};
};

TEST_F(PopplerCertificateInfoGetIssuanceTimeTest_2402, NullInputReturnsNullptr_2402) {
  // g_return_val_if_fail() is expected to emit a CRITICAL log and return nullptr.
  ScopedGLogCatcher catcher("GLib", static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL));

  GDateTime* result = poppler_certificate_info_get_issuance_time(nullptr);

  EXPECT_EQ(result, nullptr);
  EXPECT_GE(catcher.count(), 1);

  // Message format can vary by GLib version/build; assert on robust substrings.
  if (!catcher.last_message().empty()) {
    EXPECT_NE(catcher.last_message().find("poppler_certificate_info_get_issuance_time"),
              std::string::npos);
  }
}

TEST_F(PopplerCertificateInfoGetIssuanceTimeTest_2402, ReturnsIssuedPointerWhenSet_2402) {
  // Normal operation: returns whatever issuance time is stored.
  info_.issued = g_date_time_new_from_unix_utc(1700000000);  // arbitrary fixed timestamp
  ASSERT_NE(info_.issued, nullptr);

  GDateTime* result = poppler_certificate_info_get_issuance_time(&info_);

  EXPECT_EQ(result, info_.issued);
}

TEST_F(PopplerCertificateInfoGetIssuanceTimeTest_2402, ReturnsNullptrWhenIssuedIsNull_2402) {
  // Boundary: valid object but no issuance time set.
  ASSERT_EQ(info_.issued, nullptr);

  GDateTime* result = poppler_certificate_info_get_issuance_time(&info_);

  EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerCertificateInfoGetIssuanceTimeTest_2402, DoesNotRequireOtherFieldsToBeSet_2402) {
  // Boundary: all other fields left null; only issued is set.
  info_.issued = g_date_time_new_now_utc();
  ASSERT_NE(info_.issued, nullptr);

  GDateTime* result = poppler_certificate_info_get_issuance_time(&info_);

  EXPECT_EQ(result, info_.issued);
}