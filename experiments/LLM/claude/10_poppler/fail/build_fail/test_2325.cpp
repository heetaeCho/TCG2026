#include <glib.h>
#include <gtest/gtest.h>

// Forward declarations and type definitions based on the interface
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

struct _PopplerCertificateInfo {
    char *id;
};

PopplerCertificateInfo *poppler_certificate_info_copy(const PopplerCertificateInfo *info);
void poppler_certificate_info_free(PopplerCertificateInfo *info);

typedef struct _PopplerSignatureInfo PopplerSignatureInfo;

struct _PopplerSignatureInfo {
    PopplerSignatureStatus sig_status;
    PopplerCertificateStatus cert_status;
    char *signer_name;
    GDateTime *local_signing_time;
    PopplerCertificateInfo *certificate_info;
};

PopplerSignatureInfo *poppler_signature_info_copy(const PopplerSignatureInfo *siginfo);
void poppler_signature_info_free(PopplerSignatureInfo *siginfo);

}

class PopplerSignatureInfoCopyTest_2325 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    PopplerSignatureInfo *createTestSignatureInfo(
        PopplerSignatureStatus sig_status,
        PopplerCertificateStatus cert_status,
        const char *signer_name,
        GDateTime *signing_time,
        PopplerCertificateInfo *cert_info)
    {
        PopplerSignatureInfo *info = g_new0(PopplerSignatureInfo, 1);
        info->sig_status = sig_status;
        info->cert_status = cert_status;
        info->signer_name = g_strdup(signer_name);
        info->local_signing_time = signing_time ? g_date_time_ref(signing_time) : nullptr;
        info->certificate_info = cert_info;
        return info;
    }

    void freeTestSignatureInfo(PopplerSignatureInfo *info)
    {
        if (info) {
            g_free(info->signer_name);
            if (info->local_signing_time)
                g_date_time_unref(info->local_signing_time);
            if (info->certificate_info)
                g_free(info->certificate_info);
            g_free(info);
        }
    }
};

TEST_F(PopplerSignatureInfoCopyTest_2325, CopyReturnsNonNull_2325)
{
    GDateTime *dt = g_date_time_new_now_local();
    PopplerCertificateInfo *cert = g_new0(PopplerCertificateInfo, 1);

    PopplerSignatureInfo *original = createTestSignatureInfo(
        POPPLER_SIGNATURE_VALID,
        POPPLER_CERTIFICATE_TRUSTED,
        "Test Signer",
        dt,
        cert);

    PopplerSignatureInfo *copy = poppler_signature_info_copy(original);

    ASSERT_NE(copy, nullptr);
    EXPECT_NE(copy, original);

    // Clean up - we need to be careful here since copy was created by the library
    // We'll free the copy's fields manually since we can't call the library's free
    g_free(copy->signer_name);
    if (copy->local_signing_time)
        g_date_time_unref(copy->local_signing_time);
    if (copy->certificate_info)
        g_free(copy->certificate_info);
    g_free(copy);

    freeTestSignatureInfo(original);
    g_date_time_unref(dt);
}

TEST_F(PopplerSignatureInfoCopyTest_2325, CopyPreservesSigStatus_2325)
{
    GDateTime *dt = g_date_time_new_now_local();
    PopplerCertificateInfo *cert = g_new0(PopplerCertificateInfo, 1);

    PopplerSignatureInfo *original = createTestSignatureInfo(
        POPPLER_SIGNATURE_INVALID,
        POPPLER_CERTIFICATE_TRUSTED,
        "Signer",
        dt,
        cert);

    PopplerSignatureInfo *copy = poppler_signature_info_copy(original);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->sig_status, original->sig_status);
    EXPECT_EQ(copy->sig_status, POPPLER_SIGNATURE_INVALID);

    g_free(copy->signer_name);
    if (copy->local_signing_time)
        g_date_time_unref(copy->local_signing_time);
    if (copy->certificate_info)
        g_free(copy->certificate_info);
    g_free(copy);
    freeTestSignatureInfo(original);
    g_date_time_unref(dt);
}

TEST_F(PopplerSignatureInfoCopyTest_2325, CopyPreservesCertStatus_2325)
{
    GDateTime *dt = g_date_time_new_now_local();
    PopplerCertificateInfo *cert = g_new0(PopplerCertificateInfo, 1);

    PopplerSignatureInfo *original = createTestSignatureInfo(
        POPPLER_SIGNATURE_VALID,
        POPPLER_CERTIFICATE_EXPIRED,
        "Signer",
        dt,
        cert);

    PopplerSignatureInfo *copy = poppler_signature_info_copy(original);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->cert_status, original->cert_status);
    EXPECT_EQ(copy->cert_status, POPPLER_CERTIFICATE_EXPIRED);

    g_free(copy->signer_name);
    if (copy->local_signing_time)
        g_date_time_unref(copy->local_signing_time);
    if (copy->certificate_info)
        g_free(copy->certificate_info);
    g_free(copy);
    freeTestSignatureInfo(original);
    g_date_time_unref(dt);
}

TEST_F(PopplerSignatureInfoCopyTest_2325, CopyPreservesSignerName_2325)
{
    GDateTime *dt = g_date_time_new_now_local();
    PopplerCertificateInfo *cert = g_new0(PopplerCertificateInfo, 1);

    PopplerSignatureInfo *original = createTestSignatureInfo(
        POPPLER_SIGNATURE_VALID,
        POPPLER_CERTIFICATE_TRUSTED,
        "John Doe",
        dt,
        cert);

    PopplerSignatureInfo *copy = poppler_signature_info_copy(original);

    ASSERT_NE(copy, nullptr);
    ASSERT_NE(copy->signer_name, nullptr);
    EXPECT_STREQ(copy->signer_name, "John Doe");
    // Ensure it's a deep copy (different pointer)
    EXPECT_NE(copy->signer_name, original->signer_name);

    g_free(copy->signer_name);
    if (copy->local_signing_time)
        g_date_time_unref(copy->local_signing_time);
    if (copy->certificate_info)
        g_free(copy->certificate_info);
    g_free(copy);
    freeTestSignatureInfo(original);
    g_date_time_unref(dt);
}

TEST_F(PopplerSignatureInfoCopyTest_2325, CopyPreservesSigningTime_2325)
{
    GDateTime *dt = g_date_time_new_local(2023, 6, 15, 10, 30, 0);
    PopplerCertificateInfo *cert = g_new0(PopplerCertificateInfo, 1);

    PopplerSignatureInfo *original = createTestSignatureInfo(
        POPPLER_SIGNATURE_VALID,
        POPPLER_CERTIFICATE_TRUSTED,
        "Signer",
        dt,
        cert);

    PopplerSignatureInfo *copy = poppler_signature_info_copy(original);

    ASSERT_NE(copy, nullptr);
    ASSERT_NE(copy->local_signing_time, nullptr);

    // Verify the datetime values match
    EXPECT_EQ(g_date_time_get_year(copy->local_signing_time),
              g_date_time_get_year(original->local_signing_time));
    EXPECT_EQ(g_date_time_get_month(copy->local_signing_time),
              g_date_time_get_month(original->local_signing_time));
    EXPECT_EQ(g_date_time_get_day_of_month(copy->local_signing_time),
              g_date_time_get_day_of_month(original->local_signing_time));

    g_free(copy->signer_name);
    if (copy->local_signing_time)
        g_date_time_unref(copy->local_signing_time);
    if (copy->certificate_info)
        g_free(copy->certificate_info);
    g_free(copy);
    freeTestSignatureInfo(original);
    g_date_time_unref(dt);
}

TEST_F(PopplerSignatureInfoCopyTest_2325, CopyIsDifferentObject_2325)
{
    GDateTime *dt = g_date_time_new_now_local();
    PopplerCertificateInfo *cert = g_new0(PopplerCertificateInfo, 1);

    PopplerSignatureInfo *original = createTestSignatureInfo(
        POPPLER_SIGNATURE_VALID,
        POPPLER_CERTIFICATE_TRUSTED,
        "Signer",
        dt,
        cert);

    PopplerSignatureInfo *copy = poppler_signature_info_copy(original);

    ASSERT_NE(copy, nullptr);
    EXPECT_NE(copy, original);

    g_free(copy->signer_name);
    if (copy->local_signing_time)
        g_date_time_unref(copy->local_signing_time);
    if (copy->certificate_info)
        g_free(copy->certificate_info);
    g_free(copy);
    freeTestSignatureInfo(original);
    g_date_time_unref(dt);
}

TEST_F(PopplerSignatureInfoCopyTest_2325, CopyNullReturnsNull_2325)
{
    // g_return_val_if_fail should return NULL when passed nullptr
    // Note: This may produce a g_critical warning but should not crash
    PopplerSignatureInfo *result = poppler_signature_info_copy(nullptr);
    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerSignatureInfoCopyTest_2325, CopyWithEmptySignerName_2325)
{
    GDateTime *dt = g_date_time_new_now_local();
    PopplerCertificateInfo *cert = g_new0(PopplerCertificateInfo, 1);

    PopplerSignatureInfo *original = createTestSignatureInfo(
        POPPLER_SIGNATURE_VALID,
        POPPLER_CERTIFICATE_TRUSTED,
        "",
        dt,
        cert);

    PopplerSignatureInfo *copy = poppler_signature_info_copy(original);

    ASSERT_NE(copy, nullptr);
    ASSERT_NE(copy->signer_name, nullptr);
    EXPECT_STREQ(copy->signer_name, "");

    g_free(copy->signer_name);
    if (copy->local_signing_time)
        g_date_time_unref(copy->local_signing_time);
    if (copy->certificate_info)
        g_free(copy->certificate_info);
    g_free(copy);
    freeTestSignatureInfo(original);
    g_date_time_unref(dt);
}

TEST_F(PopplerSignatureInfoCopyTest_2325, CopyWithDifferentSigStatusValues_2325)
{
    PopplerSignatureStatus statuses[] = {
        POPPLER_SIGNATURE_VALID,
        POPPLER_SIGNATURE_INVALID,
        POPPLER_SIGNATURE_DIGEST_MISMATCH,
        POPPLER_SIGNATURE_DECODING_ERROR,
        POPPLER_SIGNATURE_GENERIC_ERROR,
        POPPLER_SIGNATURE_NOT_FOUND,
        POPPLER_SIGNATURE_NOT_VERIFIED
    };

    for (auto status : statuses) {
        GDateTime *dt = g_date_time_new_now_local();
        PopplerCertificateInfo *cert = g_new0(PopplerCertificateInfo, 1);

        PopplerSignatureInfo *original = createTestSignatureInfo(
            status,
            POPPLER_CERTIFICATE_TRUSTED,
            "Signer",
            dt,
            cert);

        PopplerSignatureInfo *copy = poppler_signature_info_copy(original);

        ASSERT_NE(copy, nullptr);
        EXPECT_EQ(copy->sig_status, status);

        g_free(copy->signer_name);
        if (copy->local_signing_time)
            g_date_time_unref(copy->local_signing_time);
        if (copy->certificate_info)
            g_free(copy->certificate_info);
        g_free(copy);
        freeTestSignatureInfo(original);
        g_date_time_unref(dt);
    }
}

TEST_F(PopplerSignatureInfoCopyTest_2325, CopyWithDifferentCertStatusValues_2325)
{
    PopplerCertificateStatus statuses[] = {
        POPPLER_CERTIFICATE_TRUSTED,
        POPPLER_CERTIFICATE_UNTRUSTED_ISSUER,
        POPPLER_CERTIFICATE_UNKNOWN_ISSUER,
        POPPLER_CERTIFICATE_REVOKED,
        POPPLER_CERTIFICATE_EXPIRED,
        POPPLER_CERTIFICATE_GENERIC_ERROR,
        POPPLER_CERTIFICATE_NOT_VERIFIED
    };

    for (auto status : statuses) {
        GDateTime *dt = g_date_time_new_now_local();
        PopplerCertificateInfo *cert = g_new0(PopplerCertificateInfo, 1);

        PopplerSignatureInfo *original = createTestSignatureInfo(
            POPPLER_SIGNATURE_VALID,
            status,
            "Signer",
            dt,
            cert);

        PopplerSignatureInfo *copy = poppler_signature_info_copy(original);

        ASSERT_NE(copy, nullptr);
        EXPECT_EQ(copy->cert_status, status);

        g_free(copy->signer_name);
        if (copy->local_signing_time)
            g_date_time_unref(copy->local_signing_time);
        if (copy->certificate_info)
            g_free(copy->certificate_info);
        g_free(copy);
        freeTestSignatureInfo(original);
        g_date_time_unref(dt);
    }
}

TEST_F(PopplerSignatureInfoCopyTest_2325, CopyWithLongSignerName_2325)
{
    GDateTime *dt = g_date_time_new_now_local();
    PopplerCertificateInfo *cert = g_new0(PopplerCertificateInfo, 1);

    // Create a long signer name
    std::string longName(1000, 'A');

    PopplerSignatureInfo *original = createTestSignatureInfo(
        POPPLER_SIGNATURE_VALID,
        POPPLER_CERTIFICATE_TRUSTED,
        longName.c_str(),
        dt,
        cert);

    PopplerSignatureInfo *copy = poppler_signature_info_copy(original);

    ASSERT_NE(copy, nullptr);
    ASSERT_NE(copy->signer_name, nullptr);
    EXPECT_STREQ(copy->signer_name, longName.c_str());
    EXPECT_EQ(strlen(copy->signer_name), 1000u);

    g_free(copy->signer_name);
    if (copy->local_signing_time)
        g_date_time_unref(copy->local_signing_time);
    if (copy->certificate_info)
        g_free(copy->certificate_info);
    g_free(copy);
    freeTestSignatureInfo(original);
    g_date_time_unref(dt);
}

TEST_F(PopplerSignatureInfoCopyTest_2325, CopyAllFieldsPreserved_2325)
{
    GDateTime *dt = g_date_time_new_local(2024, 1, 15, 14, 30, 45);
    PopplerCertificateInfo *cert = g_new0(PopplerCertificateInfo, 1);

    PopplerSignatureInfo *original = createTestSignatureInfo(
        POPPLER_SIGNATURE_DIGEST_MISMATCH,
        POPPLER_CERTIFICATE_REVOKED,
        "Jane Smith",
        dt,
        cert);

    PopplerSignatureInfo *copy = poppler_signature_info_copy(original);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->sig_status, POPPLER_SIGNATURE_DIGEST_MISMATCH);
    EXPECT_EQ(copy->cert_status, POPPLER_CERTIFICATE_REVOKED);
    EXPECT_STREQ(copy->signer_name, "Jane Smith");
    ASSERT_NE(copy->local_signing_time, nullptr);
    EXPECT_EQ(g_date_time_get_year(copy->local_signing_time), 2024);
    EXPECT_EQ(g_date_time_get_month(copy->local_signing_time), 1);
    EXPECT_EQ(g_date_time_get_day_of_month(copy->local_signing_time), 15);
    EXPECT_EQ(g_date_time_get_hour(copy->local_signing_time), 14);
    EXPECT_EQ(g_date_time_get_minute(copy->local_signing_time), 30);
    EXPECT_NE(copy->certificate_info, nullptr);

    g_free(copy->signer_name);
    if (copy->local_signing_time)
        g_date_time_unref(copy->local_signing_time);
    if (copy->certificate_info)
        g_free(copy->certificate_info);
    g_free(copy);
    freeTestSignatureInfo(original);
    g_date_time_unref(dt);
}

TEST_F(PopplerSignatureInfoCopyTest_2325, MultipleCopiesAreIndependent_2325)
{
    GDateTime *dt = g_date_time_new_now_local();
    PopplerCertificateInfo *cert = g_new0(PopplerCertificateInfo, 1);

    PopplerSignatureInfo *original = createTestSignatureInfo(
        POPPLER_SIGNATURE_VALID,
        POPPLER_CERTIFICATE_TRUSTED,
        "Signer",
        dt,
        cert);

    PopplerSignatureInfo *copy1 = poppler_signature_info_copy(original);
    PopplerSignatureInfo *copy2 = poppler_signature_info_copy(original);

    ASSERT_NE(copy1, nullptr);
    ASSERT_NE(copy2, nullptr);
    EXPECT_NE(copy1, copy2);
    EXPECT_NE(copy1, original);
    EXPECT_NE(copy2, original);

    EXPECT_STREQ(copy1->signer_name, copy2->signer_name);
    EXPECT_NE(copy1->signer_name, copy2->signer_name);

    // Cleanup
    auto cleanCopy = [](PopplerSignatureInfo *c) {
        g_free(c->signer_name);
        if (c->local_signing_time)
            g_date_time_unref(c->local_signing_time);
        if (c->certificate_info)
            g_free(c->certificate_info);
        g_free(c);
    };

    cleanCopy(copy1);
    cleanCopy(copy2);
    freeTestSignatureInfo(original);
    g_date_time_unref(dt);
}
