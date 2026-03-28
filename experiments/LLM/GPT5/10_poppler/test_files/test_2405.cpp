// poppler_certificate_info_copy_test_2405.cc
#include <gtest/gtest.h>

#include <glib.h>

// Poppler GLib headers are typically available via this include in the test environment.
#include <poppler.h>

namespace {

class GlibCriticalLogCatcher {
public:
    GlibCriticalLogCatcher()
    {
        old_handler_ = g_log_set_handler(
            /*log_domain=*/"GLib",
            static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL),
            &GlibCriticalLogCatcher::Handler,
            this);
        old_handler_glib_ = g_log_set_handler(
            /*log_domain=*/"GLib-GObject",
            static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL),
            &GlibCriticalLogCatcher::Handler,
            this);
    }

    ~GlibCriticalLogCatcher()
    {
        if (old_handler_ != 0) {
            g_log_remove_handler("GLib", old_handler_);
        }
        if (old_handler_glib_ != 0) {
            g_log_remove_handler("GLib-GObject", old_handler_glib_);
        }
    }

    int critical_count() const { return critical_count_; }

private:
    static void Handler(const gchar* /*log_domain*/,
                        GLogLevelFlags /*log_level*/,
                        const gchar* /*message*/,
                        gpointer user_data)
    {
        auto* self = static_cast<GlibCriticalLogCatcher*>(user_data);
        self->critical_count_++;
    }

    guint old_handler_ = 0;
    guint old_handler_glib_ = 0;
    int critical_count_ = 0;
};

static void FreeCertificateInfo(PopplerCertificateInfo* info)
{
    if (!info) {
        return;
    }

    // These fields are part of the public struct in Poppler GLib.
    g_free(info->id);
    g_free(info->subject_common_name);
    g_free(info->subject_organization);
    g_free(info->subject_email);
    g_free(info->issuer_common_name);
    g_free(info->issuer_organization);
    g_free(info->issuer_email);

    if (info->issued) {
        g_date_time_unref(info->issued);
    }
    if (info->expires) {
        g_date_time_unref(info->expires);
    }

    g_free(info);
}

static PopplerCertificateInfo* MakeCertificateInfo(const char* id,
                                                  const char* scn,
                                                  const char* sorg,
                                                  const char* semail,
                                                  const char* icn,
                                                  const char* iorg,
                                                  const char* iemail,
                                                  GDateTime* issued,
                                                  GDateTime* expires)
{
    auto* info = static_cast<PopplerCertificateInfo*>(g_malloc0(sizeof(PopplerCertificateInfo)));
    info->id = g_strdup(id);
    info->subject_common_name = g_strdup(scn);
    info->subject_organization = g_strdup(sorg);
    info->subject_email = g_strdup(semail);
    info->issuer_common_name = g_strdup(icn);
    info->issuer_organization = g_strdup(iorg);
    info->issuer_email = g_strdup(iemail);

    // Caller passes owned references; store them directly.
    info->issued = issued;
    info->expires = expires;
    return info;
}

class PopplerCertificateInfoCopyTest_2405 : public ::testing::Test {
protected:
    void TearDown() override
    {
        FreeCertificateInfo(src_);
        src_ = nullptr;

        FreeCertificateInfo(dup_);
        dup_ = nullptr;
    }

    PopplerCertificateInfo* src_ = nullptr;
    PopplerCertificateInfo* dup_ = nullptr;
};

} // namespace

TEST_F(PopplerCertificateInfoCopyTest_2405, NullInputReturnsNullAndEmitsCritical_2405)
{
    GlibCriticalLogCatcher catcher;

    PopplerCertificateInfo* out = poppler_certificate_info_copy(nullptr);
    EXPECT_EQ(out, nullptr);

    // A g_return_val_if_fail() typically logs a CRITICAL.
    EXPECT_GE(catcher.critical_count(), 1);
}

TEST_F(PopplerCertificateInfoCopyTest_2405, CopiesAllFieldsAndAllocatesNewStruct_2405)
{
    GDateTime* issued = g_date_time_new_utc(2020, 1, 2, 3, 4, 5.0);
    GDateTime* expires = g_date_time_new_utc(2030, 12, 31, 23, 59, 59.0);

    src_ = MakeCertificateInfo("id-123",
                              "Alice",
                              "Example Org",
                              "alice@example.com",
                              "Example CA",
                              "CA Org",
                              "ca@example.com",
                              issued,
                              expires);

    dup_ = poppler_certificate_info_copy(src_);
    ASSERT_NE(dup_, nullptr);
    EXPECT_NE(dup_, src_);

    // Content equality
    ASSERT_NE(dup_->id, nullptr);
    EXPECT_STREQ(dup_->id, "id-123");
    ASSERT_NE(dup_->subject_common_name, nullptr);
    EXPECT_STREQ(dup_->subject_common_name, "Alice");
    ASSERT_NE(dup_->subject_organization, nullptr);
    EXPECT_STREQ(dup_->subject_organization, "Example Org");
    ASSERT_NE(dup_->subject_email, nullptr);
    EXPECT_STREQ(dup_->subject_email, "alice@example.com");
    ASSERT_NE(dup_->issuer_common_name, nullptr);
    EXPECT_STREQ(dup_->issuer_common_name, "Example CA");
    ASSERT_NE(dup_->issuer_organization, nullptr);
    EXPECT_STREQ(dup_->issuer_organization, "CA Org");
    ASSERT_NE(dup_->issuer_email, nullptr);
    EXPECT_STREQ(dup_->issuer_email, "ca@example.com");

    // String pointer independence (dup'd strings should not alias the source pointers).
    EXPECT_NE(dup_->id, src_->id);
    EXPECT_NE(dup_->subject_common_name, src_->subject_common_name);
    EXPECT_NE(dup_->subject_organization, src_->subject_organization);
    EXPECT_NE(dup_->subject_email, src_->subject_email);
    EXPECT_NE(dup_->issuer_common_name, src_->issuer_common_name);
    EXPECT_NE(dup_->issuer_organization, src_->issuer_organization);
    EXPECT_NE(dup_->issuer_email, src_->issuer_email);

    // Date/time fields are expected to be preserved (copy retains valid references).
    ASSERT_NE(dup_->issued, nullptr);
    ASSERT_NE(dup_->expires, nullptr);

    // If the implementation uses g_date_time_ref(), pointers will match (and refcount increases).
    // This is observable and safe to assert without reading any private state.
    EXPECT_EQ(dup_->issued, src_->issued);
    EXPECT_EQ(dup_->expires, src_->expires);

    // Sanity: both should format successfully.
    gchar* issued_str = g_date_time_format(dup_->issued, "%Y-%m-%dT%H:%M:%SZ");
    gchar* expires_str = g_date_time_format(dup_->expires, "%Y-%m-%dT%H:%M:%SZ");
    EXPECT_NE(issued_str, nullptr);
    EXPECT_NE(expires_str, nullptr);
    g_free(issued_str);
    g_free(expires_str);
}

TEST_F(PopplerCertificateInfoCopyTest_2405, HandlesEmptyStrings_2405)
{
    GDateTime* issued = g_date_time_new_utc(2021, 6, 1, 0, 0, 0.0);
    GDateTime* expires = g_date_time_new_utc(2022, 6, 1, 0, 0, 0.0);

    src_ = MakeCertificateInfo("",
                              "",
                              "",
                              "",
                              "",
                              "",
                              "",
                              issued,
                              expires);

    dup_ = poppler_certificate_info_copy(src_);
    ASSERT_NE(dup_, nullptr);

    EXPECT_STREQ(dup_->id, "");
    EXPECT_STREQ(dup_->subject_common_name, "");
    EXPECT_STREQ(dup_->subject_organization, "");
    EXPECT_STREQ(dup_->subject_email, "");
    EXPECT_STREQ(dup_->issuer_common_name, "");
    EXPECT_STREQ(dup_->issuer_organization, "");
    EXPECT_STREQ(dup_->issuer_email, "");

    EXPECT_NE(dup_->id, src_->id);
    EXPECT_NE(dup_->subject_common_name, src_->subject_common_name);
    EXPECT_NE(dup_->subject_organization, src_->subject_organization);
    EXPECT_NE(dup_->subject_email, src_->subject_email);
    EXPECT_NE(dup_->issuer_common_name, src_->issuer_common_name);
    EXPECT_NE(dup_->issuer_organization, src_->issuer_organization);
    EXPECT_NE(dup_->issuer_email, src_->issuer_email);
}

TEST_F(PopplerCertificateInfoCopyTest_2405, PreservesNullStringFields_2405)
{
    GDateTime* issued = g_date_time_new_utc(2024, 2, 29, 12, 0, 0.0);
    GDateTime* expires = g_date_time_new_utc(2025, 2, 28, 12, 0, 0.0);

    // Build with some null string fields (valid boundary case for g_strdup(NULL) => NULL).
    src_ = static_cast<PopplerCertificateInfo*>(g_malloc0(sizeof(PopplerCertificateInfo)));
    src_->id = nullptr;
    src_->subject_common_name = g_strdup("CN");
    src_->subject_organization = nullptr;
    src_->subject_email = g_strdup("e@example.com");
    src_->issuer_common_name = nullptr;
    src_->issuer_organization = g_strdup("Issuer Org");
    src_->issuer_email = nullptr;
    src_->issued = issued;
    src_->expires = expires;

    dup_ = poppler_certificate_info_copy(src_);
    ASSERT_NE(dup_, nullptr);

    EXPECT_EQ(dup_->id, nullptr);
    ASSERT_NE(dup_->subject_common_name, nullptr);
    EXPECT_STREQ(dup_->subject_common_name, "CN");
    EXPECT_EQ(dup_->subject_organization, nullptr);
    ASSERT_NE(dup_->subject_email, nullptr);
    EXPECT_STREQ(dup_->subject_email, "e@example.com");
    EXPECT_EQ(dup_->issuer_common_name, nullptr);
    ASSERT_NE(dup_->issuer_organization, nullptr);
    EXPECT_STREQ(dup_->issuer_organization, "Issuer Org");
    EXPECT_EQ(dup_->issuer_email, nullptr);

    // Duplicated non-null strings should not alias.
    EXPECT_NE(dup_->subject_common_name, src_->subject_common_name);
    EXPECT_NE(dup_->subject_email, src_->subject_email);
    EXPECT_NE(dup_->issuer_organization, src_->issuer_organization);

    // Dates preserved and usable.
    ASSERT_NE(dup_->issued, nullptr);
    ASSERT_NE(dup_->expires, nullptr);
    EXPECT_EQ(dup_->issued, src_->issued);
    EXPECT_EQ(dup_->expires, src_->expires);
}