// create_certificate_info_test_2404.cc
//
// Unit tests for create_certificate_info() in poppler-form-field.cc
// TEST_ID: 2404
//
// Note:
// - create_certificate_info() is a static function, so we include the .cc directly
//   to compile it into this test translation unit and test it as a black box
//   through its observable outputs (returned PopplerCertificateInfo fields).

#include <gtest/gtest.h>

#include <glib.h>

#include "poppler/CertificateInfo.h"
#include "goo/GooString.h"

// Poppler GLib public headers (for PopplerCertificateInfo + free API if available)
#include <poppler.h>

// Include implementation to access the static function in this TU.
#include "glib/poppler-form-field.cc"

namespace {

class CreateCertificateInfoTest_2404 : public ::testing::Test {
protected:
    static X509CertificateInfo::EntityInfo MakeEntity(const char *cn,
                                                      const char *org,
                                                      const char *email)
    {
        X509CertificateInfo::EntityInfo e;
        // These members are used by create_certificate_info() via .c_str().
        // If upstream changes EntityInfo shape, this test will fail to compile,
        // which is appropriate given we only rely on the provided interface.
        e.commonName = cn ? cn : "";
        e.organization = org ? org : "";
        e.email = email ? email : "";
        return e;
    }

    static X509CertificateInfo MakeCert(const char *nickname,
                                        const X509CertificateInfo::EntityInfo &subject,
                                        const X509CertificateInfo::EntityInfo &issuer,
                                        time_t notBefore,
                                        time_t notAfter)
    {
        X509CertificateInfo ci;

        ci.setNickName(GooString(nickname ? nickname : ""));

        // Move into setters (signature shows EntityInfo&&).
        ci.setSubjectInfo(X509CertificateInfo::EntityInfo(subject));
        ci.setIssuerInfo(X509CertificateInfo::EntityInfo(issuer));

        X509CertificateInfo::Validity v;
        v.notBefore = notBefore;
        v.notAfter = notAfter;
        ci.setValidity(v);

        return ci;
    }

    static void AssertDateTimeUnixEq(GDateTime *dt, time_t expected)
    {
        ASSERT_NE(dt, nullptr);
        // g_date_time_to_unix returns gint64 seconds since epoch (UTC).
        const gint64 got = g_date_time_to_unix(dt);
        ASSERT_EQ(got, static_cast<gint64>(expected));
    }
};

TEST_F(CreateCertificateInfoTest_2404, CopiesAllFieldsAndCreatesDateTimes_2404)
{
    const auto subject = MakeEntity("Subject CN", "Subject Org", "subject@example.com");
    const auto issuer = MakeEntity("Issuer CN", "Issuer Org", "issuer@example.com");

    const time_t notBefore = static_cast<time_t>(1700000000);
    const time_t notAfter = static_cast<time_t>(1700003600);

    X509CertificateInfo ci = MakeCert("My Nick", subject, issuer, notBefore, notAfter);

    PopplerCertificateInfo *info = create_certificate_info(&ci);
    ASSERT_NE(info, nullptr);

    ASSERT_NE(info->id, nullptr);
    EXPECT_STREQ(info->id, "My Nick");

    ASSERT_NE(info->subject_common_name, nullptr);
    EXPECT_STREQ(info->subject_common_name, "Subject CN");
    ASSERT_NE(info->subject_organization, nullptr);
    EXPECT_STREQ(info->subject_organization, "Subject Org");
    ASSERT_NE(info->subject_email, nullptr);
    EXPECT_STREQ(info->subject_email, "subject@example.com");

    ASSERT_NE(info->issuer_common_name, nullptr);
    EXPECT_STREQ(info->issuer_common_name, "Issuer CN");
    ASSERT_NE(info->issuer_organization, nullptr);
    EXPECT_STREQ(info->issuer_organization, "Issuer Org");
    ASSERT_NE(info->issuer_email, nullptr);
    EXPECT_STREQ(info->issuer_email, "issuer@example.com");

    // issued/expires are created from unix UTC times.
    AssertDateTimeUnixEq(reinterpret_cast<GDateTime *>(info->issued), notBefore);
    AssertDateTimeUnixEq(reinterpret_cast<GDateTime *>(info->expires), notAfter);

    // Clean up
    // poppler-glib typically provides a free function for this boxed type.
    // If it's not available in a given build, fall back to manual cleanup.
#ifdef POPPLER_TYPE_CERTIFICATE_INFO
    poppler_certificate_info_free(info);
#else
    g_free(info->id);
    g_free(info->subject_common_name);
    g_free(info->subject_organization);
    g_free(info->subject_email);
    g_free(info->issuer_common_name);
    g_free(info->issuer_organization);
    g_free(info->issuer_email);
    if (info->issued) {
        g_date_time_unref(reinterpret_cast<GDateTime *>(info->issued));
    }
    if (info->expires) {
        g_date_time_unref(reinterpret_cast<GDateTime *>(info->expires));
    }
    g_free(info);
#endif
}

TEST_F(CreateCertificateInfoTest_2404, EmptyStringsAreDuplicatedAndNotNull_2404)
{
    const auto subject = MakeEntity("", "", "");
    const auto issuer = MakeEntity("", "", "");

    X509CertificateInfo ci = MakeCert("", subject, issuer, 1, 2);

    PopplerCertificateInfo *info = create_certificate_info(&ci);
    ASSERT_NE(info, nullptr);

    // g_strdup("") should return a non-null allocated empty string.
    ASSERT_NE(info->id, nullptr);
    EXPECT_STREQ(info->id, "");

    ASSERT_NE(info->subject_common_name, nullptr);
    EXPECT_STREQ(info->subject_common_name, "");
    ASSERT_NE(info->subject_organization, nullptr);
    EXPECT_STREQ(info->subject_organization, "");
    ASSERT_NE(info->subject_email, nullptr);
    EXPECT_STREQ(info->subject_email, "");

    ASSERT_NE(info->issuer_common_name, nullptr);
    EXPECT_STREQ(info->issuer_common_name, "");
    ASSERT_NE(info->issuer_organization, nullptr);
    EXPECT_STREQ(info->issuer_organization, "");
    ASSERT_NE(info->issuer_email, nullptr);
    EXPECT_STREQ(info->issuer_email, "");

    AssertDateTimeUnixEq(reinterpret_cast<GDateTime *>(info->issued), 1);
    AssertDateTimeUnixEq(reinterpret_cast<GDateTime *>(info->expires), 2);

#ifdef POPPLER_TYPE_CERTIFICATE_INFO
    poppler_certificate_info_free(info);
#else
    g_free(info->id);
    g_free(info->subject_common_name);
    g_free(info->subject_organization);
    g_free(info->subject_email);
    g_free(info->issuer_common_name);
    g_free(info->issuer_organization);
    g_free(info->issuer_email);
    if (info->issued) {
        g_date_time_unref(reinterpret_cast<GDateTime *>(info->issued));
    }
    if (info->expires) {
        g_date_time_unref(reinterpret_cast<GDateTime *>(info->expires));
    }
    g_free(info);
#endif
}

TEST_F(CreateCertificateInfoTest_2404, ValidityUnixEpochBoundaryIsHandled_2404)
{
    const auto subject = MakeEntity("CN", "Org", "a@b");
    const auto issuer = MakeEntity("ICN", "IOrg", "i@b");

    // Boundary at Unix epoch.
    X509CertificateInfo ci = MakeCert("n", subject, issuer, 0, 0);

    PopplerCertificateInfo *info = create_certificate_info(&ci);
    ASSERT_NE(info, nullptr);

    AssertDateTimeUnixEq(reinterpret_cast<GDateTime *>(info->issued), 0);
    AssertDateTimeUnixEq(reinterpret_cast<GDateTime *>(info->expires), 0);

#ifdef POPPLER_TYPE_CERTIFICATE_INFO
    poppler_certificate_info_free(info);
#else
    g_free(info->id);
    g_free(info->subject_common_name);
    g_free(info->subject_organization);
    g_free(info->subject_email);
    g_free(info->issuer_common_name);
    g_free(info->issuer_organization);
    g_free(info->issuer_email);
    if (info->issued) {
        g_date_time_unref(reinterpret_cast<GDateTime *>(info->issued));
    }
    if (info->expires) {
        g_date_time_unref(reinterpret_cast<GDateTime *>(info->expires));
    }
    g_free(info);
#endif
}

TEST_F(CreateCertificateInfoTest_2404, NullInputReturnsNullAndEmitsCritical_2404)
{
    // g_return_val_if_fail logs a CRITICAL and returns the provided value (nullptr).
    g_test_expect_message(nullptr,
                          G_LOG_LEVEL_CRITICAL,
                          "*create_certificate_info*assertion*ci*!=*nullptr*failed*");

    PopplerCertificateInfo *info = create_certificate_info(nullptr);
    EXPECT_EQ(info, nullptr);

    g_test_assert_expected_messages();
}

} // namespace