#include <glib.h>
#include <gtest/gtest.h>

// Include the necessary poppler headers
extern "C" {
#include "poppler-form-field.h"
}

// We need access to the struct definition for setting up test data
// Based on the known dependencies, PopplerCertificateInfo has these fields
struct _PopplerCertificateInfo
{
    char *id;
    char *subject_common_name;
    char *subject_organization;
    char *subject_email;
    char *issuer_common_name;
    char *issuer_organization;
    char *issuer_email;
    GDateTime *issued;
    GDateTime *expires;
};

// Forward declare the functions we're testing
extern "C" {
PopplerCertificateInfo *poppler_certificate_info_copy(const PopplerCertificateInfo *certificate_info);
void poppler_certificate_info_free(PopplerCertificateInfo *certificate_info);
}

class PopplerCertificateInfoCopyTest_2405 : public ::testing::Test {
protected:
    void SetUp() override
    {
        info = (PopplerCertificateInfo *)g_malloc0(sizeof(PopplerCertificateInfo));
    }

    void TearDown() override
    {
        if (info) {
            g_free(info->id);
            g_free(info->subject_common_name);
            g_free(info->subject_organization);
            g_free(info->subject_email);
            g_free(info->issuer_common_name);
            g_free(info->issuer_organization);
            g_free(info->issuer_email);
            if (info->issued)
                g_date_time_unref(info->issued);
            if (info->expires)
                g_date_time_unref(info->expires);
            g_free(info);
        }
    }

    void FillInfo()
    {
        info->id = g_strdup("test-id-123");
        info->subject_common_name = g_strdup("John Doe");
        info->subject_organization = g_strdup("Test Org");
        info->subject_email = g_strdup("john@example.com");
        info->issuer_common_name = g_strdup("CA Authority");
        info->issuer_organization = g_strdup("CA Org");
        info->issuer_email = g_strdup("ca@example.com");
        info->issued = g_date_time_new_utc(2023, 1, 15, 10, 30, 0);
        info->expires = g_date_time_new_utc(2025, 12, 31, 23, 59, 59);
    }

    void FreeCopy(PopplerCertificateInfo *copy)
    {
        if (copy) {
            g_free(copy->id);
            g_free(copy->subject_common_name);
            g_free(copy->subject_organization);
            g_free(copy->subject_email);
            g_free(copy->issuer_common_name);
            g_free(copy->issuer_organization);
            g_free(copy->issuer_email);
            if (copy->issued)
                g_date_time_unref(copy->issued);
            if (copy->expires)
                g_date_time_unref(copy->expires);
            g_free(copy);
        }
    }

    PopplerCertificateInfo *info = nullptr;
};

TEST_F(PopplerCertificateInfoCopyTest_2405, CopyReturnsNonNull_2405)
{
    FillInfo();
    PopplerCertificateInfo *copy = poppler_certificate_info_copy(info);
    ASSERT_NE(copy, nullptr);
    FreeCopy(copy);
}

TEST_F(PopplerCertificateInfoCopyTest_2405, CopyReturnsDifferentPointer_2405)
{
    FillInfo();
    PopplerCertificateInfo *copy = poppler_certificate_info_copy(info);
    ASSERT_NE(copy, info);
    FreeCopy(copy);
}

TEST_F(PopplerCertificateInfoCopyTest_2405, CopyIdField_2405)
{
    FillInfo();
    PopplerCertificateInfo *copy = poppler_certificate_info_copy(info);
    ASSERT_NE(copy, nullptr);
    EXPECT_STREQ(copy->id, "test-id-123");
    EXPECT_NE(copy->id, info->id); // Should be a separate allocation
    FreeCopy(copy);
}

TEST_F(PopplerCertificateInfoCopyTest_2405, CopySubjectCommonName_2405)
{
    FillInfo();
    PopplerCertificateInfo *copy = poppler_certificate_info_copy(info);
    ASSERT_NE(copy, nullptr);
    EXPECT_STREQ(copy->subject_common_name, "John Doe");
    EXPECT_NE(copy->subject_common_name, info->subject_common_name);
    FreeCopy(copy);
}

TEST_F(PopplerCertificateInfoCopyTest_2405, CopySubjectOrganization_2405)
{
    FillInfo();
    PopplerCertificateInfo *copy = poppler_certificate_info_copy(info);
    ASSERT_NE(copy, nullptr);
    EXPECT_STREQ(copy->subject_organization, "Test Org");
    EXPECT_NE(copy->subject_organization, info->subject_organization);
    FreeCopy(copy);
}

TEST_F(PopplerCertificateInfoCopyTest_2405, CopySubjectEmail_2405)
{
    FillInfo();
    PopplerCertificateInfo *copy = poppler_certificate_info_copy(info);
    ASSERT_NE(copy, nullptr);
    EXPECT_STREQ(copy->subject_email, "john@example.com");
    EXPECT_NE(copy->subject_email, info->subject_email);
    FreeCopy(copy);
}

TEST_F(PopplerCertificateInfoCopyTest_2405, CopyIssuerCommonName_2405)
{
    FillInfo();
    PopplerCertificateInfo *copy = poppler_certificate_info_copy(info);
    ASSERT_NE(copy, nullptr);
    EXPECT_STREQ(copy->issuer_common_name, "CA Authority");
    EXPECT_NE(copy->issuer_common_name, info->issuer_common_name);
    FreeCopy(copy);
}

TEST_F(PopplerCertificateInfoCopyTest_2405, CopyIssuerOrganization_2405)
{
    FillInfo();
    PopplerCertificateInfo *copy = poppler_certificate_info_copy(info);
    ASSERT_NE(copy, nullptr);
    EXPECT_STREQ(copy->issuer_organization, "CA Org");
    EXPECT_NE(copy->issuer_organization, info->issuer_organization);
    FreeCopy(copy);
}

TEST_F(PopplerCertificateInfoCopyTest_2405, CopyIssuerEmail_2405)
{
    FillInfo();
    PopplerCertificateInfo *copy = poppler_certificate_info_copy(info);
    ASSERT_NE(copy, nullptr);
    EXPECT_STREQ(copy->issuer_email, "ca@example.com");
    EXPECT_NE(copy->issuer_email, info->issuer_email);
    FreeCopy(copy);
}

TEST_F(PopplerCertificateInfoCopyTest_2405, CopyIssuedDateTime_2405)
{
    FillInfo();
    PopplerCertificateInfo *copy = poppler_certificate_info_copy(info);
    ASSERT_NE(copy, nullptr);
    ASSERT_NE(copy->issued, nullptr);
    EXPECT_TRUE(g_date_time_equal(copy->issued, info->issued));
    FreeCopy(copy);
}

TEST_F(PopplerCertificateInfoCopyTest_2405, CopyExpiresDateTime_2405)
{
    FillInfo();
    PopplerCertificateInfo *copy = poppler_certificate_info_copy(info);
    ASSERT_NE(copy, nullptr);
    ASSERT_NE(copy->expires, nullptr);
    EXPECT_TRUE(g_date_time_equal(copy->expires, info->expires));
    FreeCopy(copy);
}

TEST_F(PopplerCertificateInfoCopyTest_2405, CopyNullReturnsNull_2405)
{
    // g_return_val_if_fail should return nullptr for null input
    PopplerCertificateInfo *copy = poppler_certificate_info_copy(nullptr);
    EXPECT_EQ(copy, nullptr);
}

TEST_F(PopplerCertificateInfoCopyTest_2405, CopyAllFieldsPreserved_2405)
{
    FillInfo();
    PopplerCertificateInfo *copy = poppler_certificate_info_copy(info);
    ASSERT_NE(copy, nullptr);

    EXPECT_STREQ(copy->id, info->id);
    EXPECT_STREQ(copy->subject_common_name, info->subject_common_name);
    EXPECT_STREQ(copy->subject_organization, info->subject_organization);
    EXPECT_STREQ(copy->subject_email, info->subject_email);
    EXPECT_STREQ(copy->issuer_common_name, info->issuer_common_name);
    EXPECT_STREQ(copy->issuer_organization, info->issuer_organization);
    EXPECT_STREQ(copy->issuer_email, info->issuer_email);
    EXPECT_TRUE(g_date_time_equal(copy->issued, info->issued));
    EXPECT_TRUE(g_date_time_equal(copy->expires, info->expires));

    FreeCopy(copy);
}

TEST_F(PopplerCertificateInfoCopyTest_2405, CopyWithEmptyStrings_2405)
{
    info->id = g_strdup("");
    info->subject_common_name = g_strdup("");
    info->subject_organization = g_strdup("");
    info->subject_email = g_strdup("");
    info->issuer_common_name = g_strdup("");
    info->issuer_organization = g_strdup("");
    info->issuer_email = g_strdup("");
    info->issued = g_date_time_new_utc(2000, 1, 1, 0, 0, 0);
    info->expires = g_date_time_new_utc(2000, 1, 1, 0, 0, 0);

    PopplerCertificateInfo *copy = poppler_certificate_info_copy(info);
    ASSERT_NE(copy, nullptr);

    EXPECT_STREQ(copy->id, "");
    EXPECT_STREQ(copy->subject_common_name, "");
    EXPECT_STREQ(copy->subject_organization, "");
    EXPECT_STREQ(copy->subject_email, "");
    EXPECT_STREQ(copy->issuer_common_name, "");
    EXPECT_STREQ(copy->issuer_organization, "");
    EXPECT_STREQ(copy->issuer_email, "");

    FreeCopy(copy);
}

TEST_F(PopplerCertificateInfoCopyTest_2405, CopyWithUnicodeStrings_2405)
{
    info->id = g_strdup("ïd-ünïcödé");
    info->subject_common_name = g_strdup("名前テスト");
    info->subject_organization = g_strdup("组织机构");
    info->subject_email = g_strdup("tëst@éxample.com");
    info->issuer_common_name = g_strdup("Íssuér ÇÀ");
    info->issuer_organization = g_strdup("Örgänïzätïön");
    info->issuer_email = g_strdup("íssuér@éxample.com");
    info->issued = g_date_time_new_utc(2024, 6, 15, 12, 0, 0);
    info->expires = g_date_time_new_utc(2026, 6, 15, 12, 0, 0);

    PopplerCertificateInfo *copy = poppler_certificate_info_copy(info);
    ASSERT_NE(copy, nullptr);

    EXPECT_STREQ(copy->id, "ïd-ünïcödé");
    EXPECT_STREQ(copy->subject_common_name, "名前テスト");
    EXPECT_STREQ(copy->subject_organization, "组织机构");
    EXPECT_STREQ(copy->subject_email, "tëst@éxample.com");
    EXPECT_STREQ(copy->issuer_common_name, "Íssuér ÇÀ");
    EXPECT_STREQ(copy->issuer_organization, "Örgänïzätïön");
    EXPECT_STREQ(copy->issuer_email, "íssuér@éxample.com");

    FreeCopy(copy);
}

TEST_F(PopplerCertificateInfoCopyTest_2405, CopyIsIndependent_2405)
{
    FillInfo();
    PopplerCertificateInfo *copy = poppler_certificate_info_copy(info);
    ASSERT_NE(copy, nullptr);

    // Modify original after copy
    g_free(info->id);
    info->id = g_strdup("modified-id");

    // Copy should still have original value
    EXPECT_STREQ(copy->id, "test-id-123");

    FreeCopy(copy);
}

TEST_F(PopplerCertificateInfoCopyTest_2405, CopyDateTimeValues_2405)
{
    FillInfo();
    PopplerCertificateInfo *copy = poppler_certificate_info_copy(info);
    ASSERT_NE(copy, nullptr);

    // Verify the issued date components
    EXPECT_EQ(g_date_time_get_year(copy->issued), 2023);
    EXPECT_EQ(g_date_time_get_month(copy->issued), 1);
    EXPECT_EQ(g_date_time_get_day_of_month(copy->issued), 15);

    // Verify the expires date components
    EXPECT_EQ(g_date_time_get_year(copy->expires), 2025);
    EXPECT_EQ(g_date_time_get_month(copy->expires), 12);
    EXPECT_EQ(g_date_time_get_day_of_month(copy->expires), 31);

    FreeCopy(copy);
}

TEST_F(PopplerCertificateInfoCopyTest_2405, CopyWithLongStrings_2405)
{
    // Test with very long strings
    std::string longStr(4096, 'A');
    info->id = g_strdup(longStr.c_str());
    info->subject_common_name = g_strdup(longStr.c_str());
    info->subject_organization = g_strdup(longStr.c_str());
    info->subject_email = g_strdup(longStr.c_str());
    info->issuer_common_name = g_strdup(longStr.c_str());
    info->issuer_organization = g_strdup(longStr.c_str());
    info->issuer_email = g_strdup(longStr.c_str());
    info->issued = g_date_time_new_utc(2024, 1, 1, 0, 0, 0);
    info->expires = g_date_time_new_utc(2025, 1, 1, 0, 0, 0);

    PopplerCertificateInfo *copy = poppler_certificate_info_copy(info);
    ASSERT_NE(copy, nullptr);

    EXPECT_STREQ(copy->id, longStr.c_str());
    EXPECT_STREQ(copy->subject_common_name, longStr.c_str());
    EXPECT_STREQ(copy->subject_organization, longStr.c_str());
    EXPECT_STREQ(copy->subject_email, longStr.c_str());
    EXPECT_STREQ(copy->issuer_common_name, longStr.c_str());
    EXPECT_STREQ(copy->issuer_organization, longStr.c_str());
    EXPECT_STREQ(copy->issuer_email, longStr.c_str());

    FreeCopy(copy);
}
