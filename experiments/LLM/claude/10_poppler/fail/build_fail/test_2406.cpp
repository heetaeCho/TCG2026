#include <glib.h>
#include <gtest/gtest.h>

// Based on the provided interface, we need the PopplerCertificateInfo structure
// and the poppler_certificate_info_free function.

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

void poppler_certificate_info_free(PopplerCertificateInfo *certificate_info);

} // extern "C"

class PopplerCertificateInfoFreeTest_2406 : public ::testing::Test {
protected:
    PopplerCertificateInfo *createFullCertificateInfo() {
        PopplerCertificateInfo *info = g_new0(PopplerCertificateInfo, 1);
        info->id = g_strdup("test-id-123");
        info->subject_common_name = g_strdup("Test Subject CN");
        info->subject_organization = g_strdup("Test Subject Org");
        info->subject_email = g_strdup("subject@test.com");
        info->issuer_common_name = g_strdup("Test Issuer CN");
        info->issuer_organization = g_strdup("Test Issuer Org");
        info->issuer_email = g_strdup("issuer@test.com");
        info->issued = g_date_time_new_now_utc();
        info->expires = g_date_time_new_now_utc();
        return info;
    }

    PopplerCertificateInfo *createEmptyCertificateInfo() {
        PopplerCertificateInfo *info = g_new0(PopplerCertificateInfo, 1);
        // All fields are NULL due to g_new0
        return info;
    }
};

// Test that passing nullptr does not crash
TEST_F(PopplerCertificateInfoFreeTest_2406, FreeNullPointerDoesNotCrash_2406) {
    EXPECT_NO_FATAL_FAILURE(poppler_certificate_info_free(nullptr));
}

// Test freeing a fully populated certificate info struct
TEST_F(PopplerCertificateInfoFreeTest_2406, FreeFullyPopulatedInfo_2406) {
    PopplerCertificateInfo *info = createFullCertificateInfo();
    EXPECT_NO_FATAL_FAILURE(poppler_certificate_info_free(info));
}

// Test freeing a certificate info struct where all fields are NULL
TEST_F(PopplerCertificateInfoFreeTest_2406, FreeAllNullFields_2406) {
    PopplerCertificateInfo *info = createEmptyCertificateInfo();
    EXPECT_NO_FATAL_FAILURE(poppler_certificate_info_free(info));
}

// Test freeing a certificate info struct with only some fields set
TEST_F(PopplerCertificateInfoFreeTest_2406, FreePartiallyPopulatedInfo_2406) {
    PopplerCertificateInfo *info = g_new0(PopplerCertificateInfo, 1);
    info->id = g_strdup("partial-id");
    info->subject_common_name = g_strdup("Partial CN");
    // Leave other fields as NULL
    EXPECT_NO_FATAL_FAILURE(poppler_certificate_info_free(info));
}

// Test freeing with only string fields set, no datetime fields
TEST_F(PopplerCertificateInfoFreeTest_2406, FreeOnlyStringFieldsSet_2406) {
    PopplerCertificateInfo *info = g_new0(PopplerCertificateInfo, 1);
    info->id = g_strdup("id-only-strings");
    info->subject_common_name = g_strdup("Subject CN");
    info->subject_organization = g_strdup("Subject Org");
    info->subject_email = g_strdup("subject@example.com");
    info->issuer_common_name = g_strdup("Issuer CN");
    info->issuer_organization = g_strdup("Issuer Org");
    info->issuer_email = g_strdup("issuer@example.com");
    info->issued = nullptr;
    info->expires = nullptr;
    EXPECT_NO_FATAL_FAILURE(poppler_certificate_info_free(info));
}

// Test freeing with only datetime fields set, no string fields
TEST_F(PopplerCertificateInfoFreeTest_2406, FreeOnlyDateTimeFieldsSet_2406) {
    PopplerCertificateInfo *info = g_new0(PopplerCertificateInfo, 1);
    info->issued = g_date_time_new_now_utc();
    info->expires = g_date_time_new_now_utc();
    EXPECT_NO_FATAL_FAILURE(poppler_certificate_info_free(info));
}

// Test freeing with only the id field set
TEST_F(PopplerCertificateInfoFreeTest_2406, FreeOnlyIdSet_2406) {
    PopplerCertificateInfo *info = g_new0(PopplerCertificateInfo, 1);
    info->id = g_strdup("only-id");
    EXPECT_NO_FATAL_FAILURE(poppler_certificate_info_free(info));
}

// Test freeing with only issuer fields set
TEST_F(PopplerCertificateInfoFreeTest_2406, FreeOnlyIssuerFieldsSet_2406) {
    PopplerCertificateInfo *info = g_new0(PopplerCertificateInfo, 1);
    info->issuer_common_name = g_strdup("Issuer CN Only");
    info->issuer_organization = g_strdup("Issuer Org Only");
    info->issuer_email = g_strdup("issuer-only@test.com");
    EXPECT_NO_FATAL_FAILURE(poppler_certificate_info_free(info));
}

// Test freeing with empty strings (valid but empty)
TEST_F(PopplerCertificateInfoFreeTest_2406, FreeEmptyStrings_2406) {
    PopplerCertificateInfo *info = g_new0(PopplerCertificateInfo, 1);
    info->id = g_strdup("");
    info->subject_common_name = g_strdup("");
    info->subject_organization = g_strdup("");
    info->subject_email = g_strdup("");
    info->issuer_common_name = g_strdup("");
    info->issuer_organization = g_strdup("");
    info->issuer_email = g_strdup("");
    EXPECT_NO_FATAL_FAILURE(poppler_certificate_info_free(info));
}

// Test freeing with only expires datetime set
TEST_F(PopplerCertificateInfoFreeTest_2406, FreeOnlyExpiresSet_2406) {
    PopplerCertificateInfo *info = g_new0(PopplerCertificateInfo, 1);
    info->expires = g_date_time_new_now_utc();
    EXPECT_NO_FATAL_FAILURE(poppler_certificate_info_free(info));
}

// Test freeing with only issued datetime set
TEST_F(PopplerCertificateInfoFreeTest_2406, FreeOnlyIssuedSet_2406) {
    PopplerCertificateInfo *info = g_new0(PopplerCertificateInfo, 1);
    info->issued = g_date_time_new_now_utc();
    EXPECT_NO_FATAL_FAILURE(poppler_certificate_info_free(info));
}
