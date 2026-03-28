#include <glib.h>
#include <gtest/gtest.h>

// Forward declare the struct and function as they would be in the header
extern "C" {

typedef struct _PopplerCertificateInfo {
    char *id;
    char *subject_common_name;
    char *subject_organization;
    char *subject_email;
    char *issuer_common_name;
    char *issuer_organization;
    char *issuer_email;
    GDateTime *issued;
    GDateTime *expires;
} PopplerCertificateInfo;

GDateTime *poppler_certificate_info_get_expiration_time(const PopplerCertificateInfo *certificate_info);
}

class PopplerCertificateInfoTest_2403 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PopplerCertificateInfoTest_2403, ReturnsNullWhenCertificateInfoIsNull_2403)
{
    GDateTime *result = poppler_certificate_info_get_expiration_time(nullptr);
    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerCertificateInfoTest_2403, ReturnsExpiresTimeWhenSet_2403)
{
    PopplerCertificateInfo info = {};
    GDateTime *expected_time = g_date_time_new_utc(2025, 12, 31, 23, 59, 59.0);
    info.expires = expected_time;

    GDateTime *result = poppler_certificate_info_get_expiration_time(&info);
    EXPECT_EQ(result, expected_time);

    g_date_time_unref(expected_time);
}

TEST_F(PopplerCertificateInfoTest_2403, ReturnsNullWhenExpiresIsNull_2403)
{
    PopplerCertificateInfo info = {};
    info.expires = nullptr;

    GDateTime *result = poppler_certificate_info_get_expiration_time(&info);
    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerCertificateInfoTest_2403, ReturnsCorrectExpiresWithOtherFieldsPopulated_2403)
{
    PopplerCertificateInfo info = {};
    info.id = g_strdup("test-id");
    info.subject_common_name = g_strdup("Test Subject");
    info.subject_organization = g_strdup("Test Org");
    info.subject_email = g_strdup("test@example.com");
    info.issuer_common_name = g_strdup("Test Issuer");
    info.issuer_organization = g_strdup("Issuer Org");
    info.issuer_email = g_strdup("issuer@example.com");
    info.issued = g_date_time_new_utc(2020, 1, 1, 0, 0, 0.0);
    info.expires = g_date_time_new_utc(2030, 6, 15, 12, 30, 0.0);

    GDateTime *result = poppler_certificate_info_get_expiration_time(&info);
    EXPECT_EQ(result, info.expires);

    // Verify the datetime content is correct
    EXPECT_EQ(g_date_time_get_year(result), 2030);
    EXPECT_EQ(g_date_time_get_month(result), 6);
    EXPECT_EQ(g_date_time_get_day_of_month(result), 15);
    EXPECT_EQ(g_date_time_get_hour(result), 12);
    EXPECT_EQ(g_date_time_get_minute(result), 30);

    g_free(info.id);
    g_free(info.subject_common_name);
    g_free(info.subject_organization);
    g_free(info.subject_email);
    g_free(info.issuer_common_name);
    g_free(info.issuer_organization);
    g_free(info.issuer_email);
    g_date_time_unref(info.issued);
    g_date_time_unref(info.expires);
}

TEST_F(PopplerCertificateInfoTest_2403, ReturnsExpiresEpochTime_2403)
{
    PopplerCertificateInfo info = {};
    // Unix epoch: 1970-01-01T00:00:00Z
    GDateTime *epoch_time = g_date_time_new_from_unix_utc(0);
    info.expires = epoch_time;

    GDateTime *result = poppler_certificate_info_get_expiration_time(&info);
    EXPECT_EQ(result, epoch_time);
    EXPECT_EQ(g_date_time_get_year(result), 1970);
    EXPECT_EQ(g_date_time_get_month(result), 1);
    EXPECT_EQ(g_date_time_get_day_of_month(result), 1);

    g_date_time_unref(epoch_time);
}

TEST_F(PopplerCertificateInfoTest_2403, ReturnsSamePointerAsExpires_2403)
{
    PopplerCertificateInfo info = {};
    GDateTime *dt = g_date_time_new_utc(2024, 3, 15, 10, 0, 0.0);
    info.expires = dt;

    GDateTime *result1 = poppler_certificate_info_get_expiration_time(&info);
    GDateTime *result2 = poppler_certificate_info_get_expiration_time(&info);

    // Should return the same pointer both times (no copy)
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result1, dt);

    g_date_time_unref(dt);
}
