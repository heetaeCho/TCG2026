// poppler-certificate-info-get-issuer-organization-test.cc
#include <gtest/gtest.h>

#include <glib.h>

extern "C" {

// Forward declarations matching the production interface.
typedef struct _PopplerCertificateInfo PopplerCertificateInfo;

const char *poppler_certificate_info_get_issuer_organization(const PopplerCertificateInfo *certificate_info);

// This struct definition is provided in the prompt as a known dependency.
// We use it only to construct observable inputs for the public API.
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

}  // extern "C"

namespace {

class PopplerCertificateInfoGetIssuerOrganizationTest_2400 : public ::testing::Test {
protected:
  void SetUp() override {
    // Ensure GLib log domains won't crash tests; we assert behavior via return values.
  }
};

TEST_F(PopplerCertificateInfoGetIssuerOrganizationTest_2400,
       ReturnsNullWhenCertificateInfoIsNull_2400) {
  const char *result = poppler_certificate_info_get_issuer_organization(nullptr);
  EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerCertificateInfoGetIssuerOrganizationTest_2400,
       ReturnsIssuerOrganizationPointerWhenSet_2400) {
  PopplerCertificateInfo info{};
  const char kOrg[] = "Example Issuer Org";
  // Store a stable pointer; API returns const char*.
  info.issuer_organization = const_cast<char *>(kOrg);

  const char *result = poppler_certificate_info_get_issuer_organization(&info);
  EXPECT_EQ(result, kOrg);
  // Also verify content matches expected string (observable behavior).
  EXPECT_STREQ(result, "Example Issuer Org");
}

TEST_F(PopplerCertificateInfoGetIssuerOrganizationTest_2400,
       ReturnsNullWhenIssuerOrganizationFieldIsNull_2400) {
  PopplerCertificateInfo info{};
  info.issuer_organization = nullptr;

  const char *result = poppler_certificate_info_get_issuer_organization(&info);
  EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerCertificateInfoGetIssuerOrganizationTest_2400,
       ReturnsEmptyStringWhenIssuerOrganizationIsEmpty_2400) {
  PopplerCertificateInfo info{};
  const char kEmpty[] = "";
  info.issuer_organization = const_cast<char *>(kEmpty);

  const char *result = poppler_certificate_info_get_issuer_organization(&info);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "");
}

TEST_F(PopplerCertificateInfoGetIssuerOrganizationTest_2400,
       ReturnsPointerToNonNullTerminatedOrBinaryDataAsIs_2400) {
  // Boundary-ish: issuer_organization points to data with embedded NUL.
  // We only validate pointer identity and that returned buffer begins as expected.
  PopplerCertificateInfo info{};
  static char buf[] = {'A', 'B', '\0', 'C', '\0'};
  info.issuer_organization = buf;

  const char *result = poppler_certificate_info_get_issuer_organization(&info);
  ASSERT_EQ(result, buf);
  EXPECT_EQ(result[0], 'A');
  EXPECT_EQ(result[1], 'B');
  EXPECT_EQ(result[2], '\0');
}

}  // namespace