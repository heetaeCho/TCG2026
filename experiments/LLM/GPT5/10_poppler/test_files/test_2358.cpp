// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for poppler_signing_data_set_certificate_info()
// TEST_ID: 2358
//
// NOTE: These tests treat the implementation as a black box and verify only
// observable behavior via the public data structures / effects.

#include <gtest/gtest.h>

#include <glib.h>

#include <cstring>

// Poppler GLib headers (project-provided)
#include <poppler.h>

// Some Poppler GLib installs expose these in poppler.h; if your build uses a
// different header split, you may need to include poppler-form-field.h instead.
extern "C" {
void poppler_signing_data_set_certificate_info(PopplerSigningData *signing_data,
                                               const PopplerCertificateInfo *certificate_info);

PopplerCertificateInfo *poppler_certificate_info_copy(const PopplerCertificateInfo *certificate_info);
void poppler_certificate_info_free(PopplerCertificateInfo *certificate_info);
}

// ---- Helpers to capture g_return_if_fail() criticals (observable behavior) ----

namespace {

struct GLogCapture {
  guint handler_default = 0;
  guint handler_poppler = 0;
  guint handler_Poppler = 0;

  int critical_count = 0;
  GLogLevelFlags last_level = (GLogLevelFlags)0;
  std::string last_domain;
  std::string last_message;

  static void Handler(const gchar *log_domain,
                      GLogLevelFlags log_level,
                      const gchar *message,
                      gpointer user_data) {
    auto *self = static_cast<GLogCapture *>(user_data);
    if ((log_level & G_LOG_LEVEL_CRITICAL) == 0) {
      return;
    }
    self->critical_count++;
    self->last_level = log_level;
    self->last_domain = log_domain ? log_domain : "";
    self->last_message = message ? message : "";
  }

  void Install() {
    // g_return_if_fail() uses CRITICAL.
    handler_default =
        g_log_set_handler(nullptr, (GLogLevelFlags)(G_LOG_LEVEL_CRITICAL), &GLogCapture::Handler, this);
    handler_poppler =
        g_log_set_handler("poppler", (GLogLevelFlags)(G_LOG_LEVEL_CRITICAL), &GLogCapture::Handler, this);
    handler_Poppler =
        g_log_set_handler("Poppler", (GLogLevelFlags)(G_LOG_LEVEL_CRITICAL), &GLogCapture::Handler, this);
  }

  void Uninstall() {
    if (handler_default) g_log_remove_handler(nullptr, handler_default);
    if (handler_poppler) g_log_remove_handler("poppler", handler_poppler);
    if (handler_Poppler) g_log_remove_handler("Poppler", handler_Poppler);
    handler_default = handler_poppler = handler_Poppler = 0;
  }

  ~GLogCapture() { Uninstall(); }
};

static PopplerCertificateInfo *MakeCertInfo(const char *id,
                                            const char *sub_cn,
                                            const char *sub_org,
                                            const char *sub_email,
                                            const char *iss_cn,
                                            const char *iss_org,
                                            const char *iss_email) {
  // PopplerCertificateInfo is a struct in Poppler GLib (not a GObject).
  auto *ci = (PopplerCertificateInfo *)g_new0(PopplerCertificateInfo, 1);

  // Strings are owned by the struct; use g_strdup.
  ci->id = id ? g_strdup(id) : nullptr;
  ci->subject_common_name = sub_cn ? g_strdup(sub_cn) : nullptr;
  ci->subject_organization = sub_org ? g_strdup(sub_org) : nullptr;
  ci->subject_email = sub_email ? g_strdup(sub_email) : nullptr;
  ci->issuer_common_name = iss_cn ? g_strdup(iss_cn) : nullptr;
  ci->issuer_organization = iss_org ? g_strdup(iss_org) : nullptr;
  ci->issuer_email = iss_email ? g_strdup(iss_email) : nullptr;

  // Leave issued/expires nullptr to avoid assumptions about expected layout/length.
  ci->issued = nullptr;
  ci->expires = nullptr;

  return ci;
}

}  // namespace

// ---- Test fixture ----

class PopplerSigningDataSetCertificateInfoTest_2358 : public ::testing::Test {
protected:
  void SetUp() override {
    signing_data_ = (PopplerSigningData *)g_new0(PopplerSigningData, 1);
    // Ensure the field used by the function starts as nullptr.
    signing_data_->certificate_info = nullptr;
  }

  void TearDown() override {
    if (signing_data_) {
      g_clear_pointer(&signing_data_->certificate_info, poppler_certificate_info_free);
      g_free(signing_data_);
      signing_data_ = nullptr;
    }
  }

  PopplerSigningData *signing_data_ = nullptr;
};

// ---- Tests ----

TEST_F(PopplerSigningDataSetCertificateInfoTest_2358, NullSigningDataEmitsCriticalAndReturns_2358) {
  GLogCapture cap;
  cap.Install();

  auto *ci = MakeCertInfo("id", "sub-cn", "sub-org", "sub@email", "iss-cn", "iss-org", "iss@email");
  ASSERT_NE(ci, nullptr);

  poppler_signing_data_set_certificate_info(nullptr, ci);

  EXPECT_GE(cap.critical_count, 1);

  // Clean up our input cert info (the function returned early, so it won't own it).
  poppler_certificate_info_free(ci);
}

TEST_F(PopplerSigningDataSetCertificateInfoTest_2358, NullCertificateInfoEmitsCriticalAndReturns_2358) {
  GLogCapture cap;
  cap.Install();

  poppler_signing_data_set_certificate_info(signing_data_, nullptr);

  EXPECT_GE(cap.critical_count, 1);
  EXPECT_EQ(signing_data_->certificate_info, nullptr);
}

TEST_F(PopplerSigningDataSetCertificateInfoTest_2358, SetsCopyNotSamePointerAndCopiesStrings_2358) {
  auto *ci = MakeCertInfo("cert-1", "Alice", "OrgA", "alice@example.com", "CA", "CAOrg", "ca@example.com");
  ASSERT_NE(ci, nullptr);

  poppler_signing_data_set_certificate_info(signing_data_, ci);

  ASSERT_NE(signing_data_->certificate_info, nullptr);
  EXPECT_NE(signing_data_->certificate_info, ci);

  // Verify observable state in the copied struct (no assumptions beyond field presence).
  EXPECT_STREQ(signing_data_->certificate_info->id, "cert-1");
  EXPECT_STREQ(signing_data_->certificate_info->subject_common_name, "Alice");
  EXPECT_STREQ(signing_data_->certificate_info->subject_organization, "OrgA");
  EXPECT_STREQ(signing_data_->certificate_info->subject_email, "alice@example.com");
  EXPECT_STREQ(signing_data_->certificate_info->issuer_common_name, "CA");
  EXPECT_STREQ(signing_data_->certificate_info->issuer_organization, "CAOrg");
  EXPECT_STREQ(signing_data_->certificate_info->issuer_email, "ca@example.com");

  // Free original to ensure signing_data holds its own copy (should remain valid).
  poppler_certificate_info_free(ci);

  ASSERT_NE(signing_data_->certificate_info, nullptr);
  EXPECT_STREQ(signing_data_->certificate_info->id, "cert-1");
  EXPECT_STREQ(signing_data_->certificate_info->subject_common_name, "Alice");
}

TEST_F(PopplerSigningDataSetCertificateInfoTest_2358, PassingStoredPointerIsNoOpAndKeepsPointer_2358) {
  auto *ci = MakeCertInfo("cert-keep", "Bob", nullptr, nullptr, nullptr, nullptr, nullptr);
  ASSERT_NE(ci, nullptr);

  poppler_signing_data_set_certificate_info(signing_data_, ci);
  poppler_certificate_info_free(ci);

  ASSERT_NE(signing_data_->certificate_info, nullptr);
  PopplerCertificateInfo *stored = signing_data_->certificate_info;

  // This should hit the "if (signing_data->certificate_info == certificate_info) return;" branch.
  poppler_signing_data_set_certificate_info(signing_data_, stored);

  EXPECT_EQ(signing_data_->certificate_info, stored);
  EXPECT_STREQ(signing_data_->certificate_info->id, "cert-keep");
  EXPECT_STREQ(signing_data_->certificate_info->subject_common_name, "Bob");
}

TEST_F(PopplerSigningDataSetCertificateInfoTest_2358, ReplacesExistingCertificateInfoWithNewCopy_2358) {
  auto *ci1 = MakeCertInfo("cert-1", "Alice", "OrgA", nullptr, nullptr, nullptr, nullptr);
  auto *ci2 = MakeCertInfo("cert-2", "Charlie", "OrgB", "charlie@example.com", "CA2", nullptr, nullptr);
  ASSERT_NE(ci1, nullptr);
  ASSERT_NE(ci2, nullptr);

  poppler_signing_data_set_certificate_info(signing_data_, ci1);
  ASSERT_NE(signing_data_->certificate_info, nullptr);
  PopplerCertificateInfo *stored1 = signing_data_->certificate_info;

  poppler_signing_data_set_certificate_info(signing_data_, ci2);

  ASSERT_NE(signing_data_->certificate_info, nullptr);
  PopplerCertificateInfo *stored2 = signing_data_->certificate_info;

  // Observable outcome: pointer changed and content matches ci2, but is not the same pointer.
  EXPECT_NE(stored2, stored1);
  EXPECT_NE(stored2, ci2);

  EXPECT_STREQ(stored2->id, "cert-2");
  EXPECT_STREQ(stored2->subject_common_name, "Charlie");
  EXPECT_STREQ(stored2->subject_organization, "OrgB");
  EXPECT_STREQ(stored2->subject_email, "charlie@example.com");
  EXPECT_STREQ(stored2->issuer_common_name, "CA2");

  poppler_certificate_info_free(ci1);
  poppler_certificate_info_free(ci2);
}

TEST_F(PopplerSigningDataSetCertificateInfoTest_2358, HandlesNullStringFieldsWithoutCrashing_2358) {
  auto *ci = MakeCertInfo(nullptr, nullptr, "OrgOnly", nullptr, nullptr, nullptr, nullptr);
  ASSERT_NE(ci, nullptr);

  poppler_signing_data_set_certificate_info(signing_data_, ci);

  ASSERT_NE(signing_data_->certificate_info, nullptr);

  EXPECT_EQ(signing_data_->certificate_info->id, nullptr);
  EXPECT_EQ(signing_data_->certificate_info->subject_common_name, nullptr);
  ASSERT_NE(signing_data_->certificate_info->subject_organization, nullptr);
  EXPECT_STREQ(signing_data_->certificate_info->subject_organization, "OrgOnly");

  poppler_certificate_info_free(ci);
}