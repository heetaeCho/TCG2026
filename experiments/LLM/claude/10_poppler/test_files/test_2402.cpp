#include <glib.h>
#include <gtest/gtest.h>

// Forward declare the struct and function as they would be exposed via the header
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

GDateTime *poppler_certificate_info_get_issuance_time(const PopplerCertificateInfo *certificate_info);
}

class PopplerCertificateInfoGetIssuanceTimeTest_2402 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing nullptr returns nullptr
TEST_F(PopplerCertificateInfoGetIssuanceTimeTest_2402, ReturnsNullWhenCertificateInfoIsNull_2402)
{
    GDateTime *result = poppler_certificate_info_get_issuance_time(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test that a valid certificate info with a non-null issued field returns the correct GDateTime
TEST_F(PopplerCertificateInfoGetIssuanceTimeTest_2402, ReturnsIssuedTimeWhenValid_2402)
{
    PopplerCertificateInfo info = {};
    memset(&info, 0, sizeof(info));

    GDateTime *expected_time = g_date_time_new_utc(2024, 1, 15, 10, 30, 0);
    info.issued = expected_time;

    GDateTime *result = poppler_certificate_info_get_issuance_time(&info);
    EXPECT_EQ(result, expected_time);

    // Verify the returned datetime has the expected values
    EXPECT_EQ(g_date_time_get_year(result), 2024);
    EXPECT_EQ(g_date_time_get_month(result), 1);
    EXPECT_EQ(g_date_time_get_day_of_month(result), 15);
    EXPECT_EQ(g_date_time_get_hour(result), 10);
    EXPECT_EQ(g_date_time_get_minute(result), 30);

    g_date_time_unref(expected_time);
}

// Test that a valid certificate info with a null issued field returns nullptr
TEST_F(PopplerCertificateInfoGetIssuanceTimeTest_2402, ReturnsNullWhenIssuedFieldIsNull_2402)
{
    PopplerCertificateInfo info = {};
    memset(&info, 0, sizeof(info));
    info.issued = nullptr;

    GDateTime *result = poppler_certificate_info_get_issuance_time(&info);
    EXPECT_EQ(result, nullptr);
}

// Test with a different valid date to ensure the correct field is being returned
TEST_F(PopplerCertificateInfoGetIssuanceTimeTest_2402, ReturnsDifferentIssuedTime_2402)
{
    PopplerCertificateInfo info = {};
    memset(&info, 0, sizeof(info));

    GDateTime *issued_time = g_date_time_new_utc(2000, 6, 30, 23, 59, 59);
    GDateTime *expires_time = g_date_time_new_utc(2030, 12, 31, 0, 0, 0);
    info.issued = issued_time;
    info.expires = expires_time;

    GDateTime *result = poppler_certificate_info_get_issuance_time(&info);

    // Ensure we get the issued time, not the expires time
    EXPECT_EQ(result, issued_time);
    EXPECT_NE(result, expires_time);
    EXPECT_EQ(g_date_time_get_year(result), 2000);
    EXPECT_EQ(g_date_time_get_month(result), 6);

    g_date_time_unref(issued_time);
    g_date_time_unref(expires_time);
}

// Test that the function returns the exact pointer stored in the struct (not a copy)
TEST_F(PopplerCertificateInfoGetIssuanceTimeTest_2402, ReturnsSamePointerAsStoredInStruct_2402)
{
    PopplerCertificateInfo info = {};
    memset(&info, 0, sizeof(info));

    GDateTime *issued_time = g_date_time_new_utc(2023, 3, 14, 12, 0, 0);
    info.issued = issued_time;

    GDateTime *result1 = poppler_certificate_info_get_issuance_time(&info);
    GDateTime *result2 = poppler_certificate_info_get_issuance_time(&info);

    // Both calls should return the same pointer
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result1, issued_time);

    g_date_time_unref(issued_time);
}

// Test with all other fields populated to ensure no interference
TEST_F(PopplerCertificateInfoGetIssuanceTimeTest_2402, WorksWithFullyPopulatedStruct_2402)
{
    PopplerCertificateInfo info = {};
    info.id = g_strdup("test-id");
    info.subject_common_name = g_strdup("Test CN");
    info.subject_organization = g_strdup("Test Org");
    info.subject_email = g_strdup("test@test.com");
    info.issuer_common_name = g_strdup("Issuer CN");
    info.issuer_organization = g_strdup("Issuer Org");
    info.issuer_email = g_strdup("issuer@test.com");
    info.issued = g_date_time_new_utc(2022, 11, 1, 8, 0, 0);
    info.expires = g_date_time_new_utc(2025, 11, 1, 8, 0, 0);

    GDateTime *result = poppler_certificate_info_get_issuance_time(&info);
    EXPECT_EQ(result, info.issued);
    EXPECT_EQ(g_date_time_get_year(result), 2022);
    EXPECT_EQ(g_date_time_get_month(result), 11);

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
