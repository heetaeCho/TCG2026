// poppler-certificate-info-get-subject-organization-test.cc
//
// Unit tests for:
//   const char *poppler_certificate_info_get_subject_organization(const PopplerCertificateInfo *certificate_info)
//
// Constraints honored:
// - Treat implementation as black box (only assert observable behavior).
// - No private/internal state access beyond the provided public struct fields (dependency snippet).
// - Include normal + boundary + error (null) cases.

#include <gtest/gtest.h>

#include <cstring>

#include <glib.h>

// The production code uses PopplerCertificateInfo as an opaque-ish type in the API.
// For unit testing this single function, we mirror the dependency struct definition
// provided in the prompt (not re-implementing any logic; just enabling construction).
typedef struct _PopplerCertificateInfo PopplerCertificateInfo;

struct _PopplerCertificateInfo {
    char *id;
    char *subject_common_name;
    char *subject_organization;
    char *subject_email;
    char *issuer_common_name;
    char *issuer_organization;
    char *issuer_email;
    int *issued;
    int *expires;
};

extern "C" {
const char *poppler_certificate_info_get_subject_organization(const PopplerCertificateInfo *certificate_info);
}

namespace {

class PopplerCertificateInfoGetSubjectOrganizationTest_2397 : public ::testing::Test {
protected:
    void SetUp() override { std::memset(&info_, 0, sizeof(info_)); }

    PopplerCertificateInfo info_{};
};

TEST_F(PopplerCertificateInfoGetSubjectOrganizationTest_2397, NullCertificateInfoReturnsNull_2397) {
    // Error case: observable via return value for nullptr input.
    EXPECT_EQ(poppler_certificate_info_get_subject_organization(nullptr), nullptr);
}

TEST_F(PopplerCertificateInfoGetSubjectOrganizationTest_2397, ReturnsSubjectOrganizationPointerWhenSet_2397) {
    // Normal operation: when subject_organization is set, returns it.
    info_.subject_organization = const_cast<char *>("Example Org");

    const char *ret = poppler_certificate_info_get_subject_organization(&info_);
    ASSERT_NE(ret, nullptr);
    EXPECT_STREQ(ret, "Example Org");
    // Also ensure pointer identity is preserved (no copying observable needed).
    EXPECT_EQ(ret, info_.subject_organization);
}

TEST_F(PopplerCertificateInfoGetSubjectOrganizationTest_2397, ReturnsNullWhenSubjectOrganizationIsNull_2397) {
    // Boundary: struct is valid but field is null.
    info_.subject_organization = nullptr;

    EXPECT_EQ(poppler_certificate_info_get_subject_organization(&info_), nullptr);
}

TEST_F(PopplerCertificateInfoGetSubjectOrganizationTest_2397,
       ReturnsSubjectOrganizationEvenIfEmptyString_2397) {
    // Boundary: empty string is a valid C-string; should be returned as-is.
    info_.subject_organization = const_cast<char *>("");

    const char *ret = poppler_certificate_info_get_subject_organization(&info_);
    ASSERT_NE(ret, nullptr);
    EXPECT_STREQ(ret, "");
    EXPECT_EQ(ret, info_.subject_organization);
}

TEST_F(PopplerCertificateInfoGetSubjectOrganizationTest_2397,
       DoesNotDependOnOtherFields_2397) {
    // Boundary/robustness: other fields set should not affect the returned value.
    info_.subject_organization = const_cast<char *>("Org A");
    info_.subject_common_name = const_cast<char *>("CN");
    info_.issuer_organization = const_cast<char *>("Issuer Org");
    info_.issuer_common_name = const_cast<char *>("Issuer CN");
    info_.subject_email = const_cast<char *>("a@example.com");

    const char *ret = poppler_certificate_info_get_subject_organization(&info_);
    ASSERT_NE(ret, nullptr);
    EXPECT_STREQ(ret, "Org A");
    EXPECT_EQ(ret, info_.subject_organization);
}

} // namespace