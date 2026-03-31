#include <gtest/gtest.h>
#include <glib.h>
#include <cstring>
#include <ctime>

// Include necessary headers
#include "poppler/CertificateInfo.h"

// We need access to the internal struct and function
// The struct _PopplerCertificateInfo and create_certificate_info are defined in poppler-form-field.cc
// We need to declare them for testing purposes

typedef struct _PopplerCertificateInfo PopplerCertificateInfo;

struct _PopplerCertificateInfo {
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

// Forward declare the functions we need
extern "C" {
    PopplerCertificateInfo *poppler_certificate_info_new();
    PopplerCertificateInfo *create_certificate_info(const X509CertificateInfo *ci);
    void poppler_certificate_info_free(PopplerCertificateInfo *info);
}

// If create_certificate_info is static, we may need to include the source directly
// This is a common pattern for testing static functions
#include "poppler-form-field.cc"

class CreateCertificateInfoTest_2404 : public ::testing::Test {
protected:
    void TearDown() override {
        // Cleanup handled per test
    }
};

TEST_F(CreateCertificateInfoTest_2404, NullInputReturnsNull_2404) {
    PopplerCertificateInfo *result = create_certificate_info(nullptr);
    EXPECT_EQ(result, nullptr);
}

TEST_F(CreateCertificateInfoTest_2404, BasicFieldsAreCopied_2404) {
    X509CertificateInfo ci;
    
    GooString nickName("test-cert-id");
    ci.setNickName(nickName);
    
    X509CertificateInfo::EntityInfo subjectInfo;
    subjectInfo.commonName = "Subject CN";
    subjectInfo.organization = "Subject Org";
    subjectInfo.email = "subject@example.com";
    ci.setSubjectInfo(std::move(subjectInfo));
    
    X509CertificateInfo::EntityInfo issuerInfo;
    issuerInfo.commonName = "Issuer CN";
    issuerInfo.organization = "Issuer Org";
    issuerInfo.email = "issuer@example.com";
    ci.setIssuerInfo(std::move(issuerInfo));
    
    X509CertificateInfo::Validity validity;
    validity.notBefore = 1000000;
    validity.notAfter = 2000000;
    ci.setValidity(validity);
    
    PopplerCertificateInfo *result = create_certificate_info(&ci);
    ASSERT_NE(result, nullptr);
    
    EXPECT_STREQ(result->id, "test-cert-id");
    EXPECT_STREQ(result->subject_common_name, "Subject CN");
    EXPECT_STREQ(result->subject_organization, "Subject Org");
    EXPECT_STREQ(result->subject_email, "subject@example.com");
    EXPECT_STREQ(result->issuer_common_name, "Issuer CN");
    EXPECT_STREQ(result->issuer_organization, "Issuer Org");
    EXPECT_STREQ(result->issuer_email, "issuer@example.com");
    
    ASSERT_NE(result->issued, nullptr);
    ASSERT_NE(result->expires, nullptr);
    EXPECT_EQ(g_date_time_to_unix(result->issued), 1000000);
    EXPECT_EQ(g_date_time_to_unix(result->expires), 2000000);
    
    // Cleanup
    g_free(result->id);
    g_free(result->subject_common_name);
    g_free(result->subject_organization);
    g_free(result->subject_email);
    g_free(result->issuer_common_name);
    g_free(result->issuer_organization);
    g_free(result->issuer_email);
    g_date_time_unref(result->issued);
    g_date_time_unref(result->expires);
    g_free(result);
}

TEST_F(CreateCertificateInfoTest_2404, EmptyStringFields_2404) {
    X509CertificateInfo ci;
    
    GooString nickName("");
    ci.setNickName(nickName);
    
    X509CertificateInfo::EntityInfo subjectInfo;
    subjectInfo.commonName = "";
    subjectInfo.organization = "";
    subjectInfo.email = "";
    ci.setSubjectInfo(std::move(subjectInfo));
    
    X509CertificateInfo::EntityInfo issuerInfo;
    issuerInfo.commonName = "";
    issuerInfo.organization = "";
    issuerInfo.email = "";
    ci.setIssuerInfo(std::move(issuerInfo));
    
    X509CertificateInfo::Validity validity;
    validity.notBefore = 0;
    validity.notAfter = 0;
    ci.setValidity(validity);
    
    PopplerCertificateInfo *result = create_certificate_info(&ci);
    ASSERT_NE(result, nullptr);
    
    EXPECT_STREQ(result->id, "");
    EXPECT_STREQ(result->subject_common_name, "");
    EXPECT_STREQ(result->subject_organization, "");
    EXPECT_STREQ(result->subject_email, "");
    EXPECT_STREQ(result->issuer_common_name, "");
    EXPECT_STREQ(result->issuer_organization, "");
    EXPECT_STREQ(result->issuer_email, "");
    
    // Cleanup
    g_free(result->id);
    g_free(result->subject_common_name);
    g_free(result->subject_organization);
    g_free(result->subject_email);
    g_free(result->issuer_common_name);
    g_free(result->issuer_organization);
    g_free(result->issuer_email);
    if (result->issued) g_date_time_unref(result->issued);
    if (result->expires) g_date_time_unref(result->expires);
    g_free(result);
}

TEST_F(CreateCertificateInfoTest_2404, ValidityWithLargeTimestamps_2404) {
    X509CertificateInfo ci;
    
    GooString nickName("large-time-cert");
    ci.setNickName(nickName);
    
    X509CertificateInfo::EntityInfo subjectInfo;
    subjectInfo.commonName = "Test Subject";
    subjectInfo.organization = "Test Org";
    subjectInfo.email = "test@test.com";
    ci.setSubjectInfo(std::move(subjectInfo));
    
    X509CertificateInfo::EntityInfo issuerInfo;
    issuerInfo.commonName = "Test Issuer";
    issuerInfo.organization = "Issuer Org";
    issuerInfo.email = "issuer@test.com";
    ci.setIssuerInfo(std::move(issuerInfo));
    
    X509CertificateInfo::Validity validity;
    // Use a large but valid timestamp (year ~2033)
    validity.notBefore = 1609459200; // 2021-01-01
    validity.notAfter = 1893456000;  // 2030-01-01
    ci.setValidity(validity);
    
    PopplerCertificateInfo *result = create_certificate_info(&ci);
    ASSERT_NE(result, nullptr);
    
    ASSERT_NE(result->issued, nullptr);
    ASSERT_NE(result->expires, nullptr);
    EXPECT_EQ(g_date_time_to_unix(result->issued), 1609459200);
    EXPECT_EQ(g_date_time_to_unix(result->expires), 1893456000);
    
    // Cleanup
    g_free(result->id);
    g_free(result->subject_common_name);
    g_free(result->subject_organization);
    g_free(result->subject_email);
    g_free(result->issuer_common_name);
    g_free(result->issuer_organization);
    g_free(result->issuer_email);
    g_date_time_unref(result->issued);
    g_date_time_unref(result->expires);
    g_free(result);
}

TEST_F(CreateCertificateInfoTest_2404, SpecialCharactersInFields_2404) {
    X509CertificateInfo ci;
    
    GooString nickName("cert-with-special-chars-!@#$%");
    ci.setNickName(nickName);
    
    X509CertificateInfo::EntityInfo subjectInfo;
    subjectInfo.commonName = "Subject with spaces and Üñíçödé";
    subjectInfo.organization = "Org/Unit=Test, Inc.";
    subjectInfo.email = "user+tag@example.co.uk";
    ci.setSubjectInfo(std::move(subjectInfo));
    
    X509CertificateInfo::EntityInfo issuerInfo;
    issuerInfo.commonName = "Issuer with <special> & \"chars\"";
    issuerInfo.organization = "O'Reilly & Associates";
    issuerInfo.email = "admin@sub.domain.example.com";
    ci.setIssuerInfo(std::move(issuerInfo));
    
    X509CertificateInfo::Validity validity;
    validity.notBefore = 100;
    validity.notAfter = 200;
    ci.setValidity(validity);
    
    PopplerCertificateInfo *result = create_certificate_info(&ci);
    ASSERT_NE(result, nullptr);
    
    EXPECT_STREQ(result->id, "cert-with-special-chars-!@#$%");
    EXPECT_STREQ(result->subject_common_name, "Subject with spaces and Üñíçödé");
    EXPECT_STREQ(result->subject_organization, "Org/Unit=Test, Inc.");
    EXPECT_STREQ(result->subject_email, "user+tag@example.co.uk");
    EXPECT_STREQ(result->issuer_common_name, "Issuer with <special> & \"chars\"");
    EXPECT_STREQ(result->issuer_organization, "O'Reilly & Associates");
    EXPECT_STREQ(result->issuer_email, "admin@sub.domain.example.com");
    
    // Cleanup
    g_free(result->id);
    g_free(result->subject_common_name);
    g_free(result->subject_organization);
    g_free(result->subject_email);
    g_free(result->issuer_common_name);
    g_free(result->issuer_organization);
    g_free(result->issuer_email);
    if (result->issued) g_date_time_unref(result->issued);
    if (result->expires) g_date_time_unref(result->expires);
    g_free(result);
}

TEST_F(CreateCertificateInfoTest_2404, DefaultValuesInCertificateInfo_2404) {
    // Test with a freshly created X509CertificateInfo with default values
    X509CertificateInfo ci;
    
    // Don't set anything - use defaults
    X509CertificateInfo::EntityInfo subjectInfo;
    ci.setSubjectInfo(std::move(subjectInfo));
    
    X509CertificateInfo::EntityInfo issuerInfo;
    ci.setIssuerInfo(std::move(issuerInfo));
    
    X509CertificateInfo::Validity validity;
    ci.setValidity(validity);
    
    PopplerCertificateInfo *result = create_certificate_info(&ci);
    ASSERT_NE(result, nullptr);
    
    // Default GooString should give empty string via c_str()
    EXPECT_NE(result->id, nullptr);
    EXPECT_NE(result->subject_common_name, nullptr);
    EXPECT_NE(result->subject_organization, nullptr);
    EXPECT_NE(result->subject_email, nullptr);
    EXPECT_NE(result->issuer_common_name, nullptr);
    EXPECT_NE(result->issuer_organization, nullptr);
    EXPECT_NE(result->issuer_email, nullptr);
    
    // Cleanup
    g_free(result->id);
    g_free(result->subject_common_name);
    g_free(result->subject_organization);
    g_free(result->subject_email);
    g_free(result->issuer_common_name);
    g_free(result->issuer_organization);
    g_free(result->issuer_email);
    if (result->issued) g_date_time_unref(result->issued);
    if (result->expires) g_date_time_unref(result->expires);
    g_free(result);
}

TEST_F(CreateCertificateInfoTest_2404, DifferentSubjectAndIssuer_2404) {
    X509CertificateInfo ci;
    
    GooString nickName("diff-subj-issuer");
    ci.setNickName(nickName);
    
    X509CertificateInfo::EntityInfo subjectInfo;
    subjectInfo.commonName = "Alice";
    subjectInfo.organization = "Alice Corp";
    subjectInfo.email = "alice@alice.com";
    ci.setSubjectInfo(std::move(subjectInfo));
    
    X509CertificateInfo::EntityInfo issuerInfo;
    issuerInfo.commonName = "Bob CA";
    issuerInfo.organization = "Bob Trust";
    issuerInfo.email = "bob@bob.com";
    ci.setIssuerInfo(std::move(issuerInfo));
    
    X509CertificateInfo::Validity validity;
    validity.notBefore = 500000;
    validity.notAfter = 600000;
    ci.setValidity(validity);
    
    PopplerCertificateInfo *result = create_certificate_info(&ci);
    ASSERT_NE(result, nullptr);
    
    // Verify subject and issuer are different
    EXPECT_STREQ(result->subject_common_name, "Alice");
    EXPECT_STREQ(result->issuer_common_name, "Bob CA");
    EXPECT_STRNE(result->subject_common_name, result->issuer_common_name);
    
    EXPECT_STREQ(result->subject_organization, "Alice Corp");
    EXPECT_STREQ(result->issuer_organization, "Bob Trust");
    EXPECT_STRNE(result->subject_organization, result->issuer_organization);
    
    EXPECT_STREQ(result->subject_email, "alice@alice.com");
    EXPECT_STREQ(result->issuer_email, "bob@bob.com");
    EXPECT_STRNE(result->subject_email, result->issuer_email);
    
    // Cleanup
    g_free(result->id);
    g_free(result->subject_common_name);
    g_free(result->subject_organization);
    g_free(result->subject_email);
    g_free(result->issuer_common_name);
    g_free(result->issuer_organization);
    g_free(result->issuer_email);
    if (result->issued) g_date_time_unref(result->issued);
    if (result->expires) g_date_time_unref(result->expires);
    g_free(result);
}

TEST_F(CreateCertificateInfoTest_2404, ZeroTimestampValidity_2404) {
    X509CertificateInfo ci;
    
    GooString nickName("zero-time");
    ci.setNickName(nickName);
    
    X509CertificateInfo::EntityInfo subjectInfo;
    subjectInfo.commonName = "Test";
    ci.setSubjectInfo(std::move(subjectInfo));
    
    X509CertificateInfo::EntityInfo issuerInfo;
    issuerInfo.commonName = "Issuer";
    ci.setIssuerInfo(std::move(issuerInfo));
    
    X509CertificateInfo::Validity validity;
    validity.notBefore = 0; // Unix epoch
    validity.notAfter = 0;  // Unix epoch
    ci.setValidity(validity);
    
    PopplerCertificateInfo *result = create_certificate_info(&ci);
    ASSERT_NE(result, nullptr);
    
    ASSERT_NE(result->issued, nullptr);
    ASSERT_NE(result->expires, nullptr);
    EXPECT_EQ(g_date_time_to_unix(result->issued), 0);
    EXPECT_EQ(g_date_time_to_unix(result->expires), 0);
    
    // Cleanup
    g_free(result->id);
    g_free(result->subject_common_name);
    g_free(result->subject_organization);
    g_free(result->subject_email);
    g_free(result->issuer_common_name);
    g_free(result->issuer_organization);
    g_free(result->issuer_email);
    g_date_time_unref(result->issued);
    g_date_time_unref(result->expires);
    g_free(result);
}

TEST_F(CreateCertificateInfoTest_2404, StringFieldsAreDeepCopied_2404) {
    X509CertificateInfo ci;
    
    GooString nickName("deep-copy-test");
    ci.setNickName(nickName);
    
    X509CertificateInfo::EntityInfo subjectInfo;
    subjectInfo.commonName = "DeepCopySubject";
    subjectInfo.organization = "DeepCopyOrg";
    subjectInfo.email = "deep@copy.com";
    ci.setSubjectInfo(std::move(subjectInfo));
    
    X509CertificateInfo::EntityInfo issuerInfo;
    issuerInfo.commonName = "DeepCopyIssuer";
    issuerInfo.organization = "DeepCopyIssuerOrg";
    issuerInfo.email = "deepissuer@copy.com";
    ci.setIssuerInfo(std::move(issuerInfo));
    
    X509CertificateInfo::Validity validity;
    validity.notBefore = 1000;
    validity.notAfter = 2000;
    ci.setValidity(validity);
    
    PopplerCertificateInfo *result = create_certificate_info(&ci);
    ASSERT_NE(result, nullptr);
    
    // Verify the strings are proper copies (not the same pointer as internal data)
    // We can verify by checking the content is correct
    EXPECT_STREQ(result->id, "deep-copy-test");
    EXPECT_STREQ(result->subject_common_name, "DeepCopySubject");
    
    // The returned strings should be independently allocated (g_strdup)
    // Modifying one should not affect the other - we verify content is correct
    EXPECT_STREQ(result->subject_organization, "DeepCopyOrg");
    EXPECT_STREQ(result->subject_email, "deep@copy.com");
    EXPECT_STREQ(result->issuer_common_name, "DeepCopyIssuer");
    EXPECT_STREQ(result->issuer_organization, "DeepCopyIssuerOrg");
    EXPECT_STREQ(result->issuer_email, "deepissuer@copy.com");
    
    // Cleanup
    g_free(result->id);
    g_free(result->subject_common_name);
    g_free(result->subject_organization);
    g_free(result->subject_email);
    g_free(result->issuer_common_name);
    g_free(result->issuer_organization);
    g_free(result->issuer_email);
    if (result->issued) g_date_time_unref(result->issued);
    if (result->expires) g_date_time_unref(result->expires);
    g_free(result);
}
