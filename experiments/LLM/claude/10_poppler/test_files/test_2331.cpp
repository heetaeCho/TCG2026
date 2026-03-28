#include <glib.h>
#include <gtest/gtest.h>

// Forward declarations and type definitions based on the provided interface
extern "C" {

typedef enum {
    POPPLER_SIGNATURE_VALID,
    POPPLER_SIGNATURE_INVALID,
    POPPLER_SIGNATURE_DIGEST_MISMATCH,
    POPPLER_SIGNATURE_DECODING_ERROR,
    POPPLER_SIGNATURE_GENERIC_ERROR,
    POPPLER_SIGNATURE_NOT_FOUND,
    POPPLER_SIGNATURE_NOT_VERIFIED
} PopplerSignatureStatus;

typedef enum {
    POPPLER_CERTIFICATE_TRUSTED,
    POPPLER_CERTIFICATE_UNTRUSTED_ISSUER,
    POPPLER_CERTIFICATE_UNKNOWN_ISSUER,
    POPPLER_CERTIFICATE_REVOKED,
    POPPLER_CERTIFICATE_EXPIRED,
    POPPLER_CERTIFICATE_GENERIC_ERROR,
    POPPLER_CERTIFICATE_NOT_VERIFIED
} PopplerCertificateStatus;

typedef struct _PopplerCertificateInfo PopplerCertificateInfo;

typedef struct _PopplerSignatureInfo {
    int sig_status;
    PopplerCertificateStatus cert_status;
    char *signer_name;
    GDateTime *local_signing_time;
    PopplerCertificateInfo *certificate_info;
} PopplerSignatureInfo;

GDateTime *poppler_signature_info_get_local_signing_time(const PopplerSignatureInfo *siginfo);

}

class PopplerSignatureInfoGetLocalSigningTimeTest_2331 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PopplerSignatureInfoGetLocalSigningTimeTest_2331, ReturnsNullWhenSigInfoIsNull_2331)
{
    GDateTime *result = poppler_signature_info_get_local_signing_time(nullptr);
    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerSignatureInfoGetLocalSigningTimeTest_2331, ReturnsValidDateTime_2331)
{
    PopplerSignatureInfo siginfo;
    memset(&siginfo, 0, sizeof(siginfo));

    GDateTime *expected_time = g_date_time_new_now_local();
    siginfo.local_signing_time = expected_time;

    GDateTime *result = poppler_signature_info_get_local_signing_time(&siginfo);
    EXPECT_EQ(result, expected_time);

    g_date_time_unref(expected_time);
}

TEST_F(PopplerSignatureInfoGetLocalSigningTimeTest_2331, ReturnsNullDateTimeWhenFieldIsNull_2331)
{
    PopplerSignatureInfo siginfo;
    memset(&siginfo, 0, sizeof(siginfo));
    siginfo.local_signing_time = nullptr;

    GDateTime *result = poppler_signature_info_get_local_signing_time(&siginfo);
    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerSignatureInfoGetLocalSigningTimeTest_2331, ReturnsSpecificDateTime_2331)
{
    PopplerSignatureInfo siginfo;
    memset(&siginfo, 0, sizeof(siginfo));

    // Create a specific date/time: 2023-06-15 10:30:00 UTC
    GTimeZone *tz = g_time_zone_new_utc();
    GDateTime *specific_time = g_date_time_new(tz, 2023, 6, 15, 10, 30, 0.0);
    siginfo.local_signing_time = specific_time;

    GDateTime *result = poppler_signature_info_get_local_signing_time(&siginfo);
    EXPECT_EQ(result, specific_time);

    // Verify the returned pointer gives us the correct date components
    EXPECT_EQ(g_date_time_get_year(result), 2023);
    EXPECT_EQ(g_date_time_get_month(result), 6);
    EXPECT_EQ(g_date_time_get_day_of_month(result), 15);
    EXPECT_EQ(g_date_time_get_hour(result), 10);
    EXPECT_EQ(g_date_time_get_minute(result), 30);

    g_date_time_unref(specific_time);
    g_time_zone_unref(tz);
}

TEST_F(PopplerSignatureInfoGetLocalSigningTimeTest_2331, ReturnsSamePointerAsSet_2331)
{
    PopplerSignatureInfo siginfo;
    memset(&siginfo, 0, sizeof(siginfo));

    GDateTime *time1 = g_date_time_new_now_local();
    siginfo.local_signing_time = time1;

    GDateTime *result1 = poppler_signature_info_get_local_signing_time(&siginfo);
    GDateTime *result2 = poppler_signature_info_get_local_signing_time(&siginfo);

    // Should return the same pointer both times (no copy)
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result1, time1);

    g_date_time_unref(time1);
}

TEST_F(PopplerSignatureInfoGetLocalSigningTimeTest_2331, WorksWithOtherFieldsPopulated_2331)
{
    PopplerSignatureInfo siginfo;
    memset(&siginfo, 0, sizeof(siginfo));

    siginfo.sig_status = POPPLER_SIGNATURE_VALID;
    siginfo.cert_status = POPPLER_CERTIFICATE_TRUSTED;
    siginfo.signer_name = g_strdup("Test Signer");
    siginfo.certificate_info = nullptr;

    GDateTime *expected_time = g_date_time_new_now_local();
    siginfo.local_signing_time = expected_time;

    GDateTime *result = poppler_signature_info_get_local_signing_time(&siginfo);
    EXPECT_EQ(result, expected_time);

    g_date_time_unref(expected_time);
    g_free(siginfo.signer_name);
}
