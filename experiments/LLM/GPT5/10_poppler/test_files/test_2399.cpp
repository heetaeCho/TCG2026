// File: poppler-certificate-info-get-issuer-common-name-test.cpp
#include <gtest/gtest.h>

#include <glib.h>
#include <cstring>

// The production struct is shown in the prompt; we only mirror fields needed to
// construct inputs for the public C API function under test.
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

using PopplerCertificateInfo = _PopplerCertificateInfo;

extern "C" {
const char *poppler_certificate_info_get_issuer_common_name(
    const PopplerCertificateInfo *certificate_info);
}

class PopplerCertificateInfoGetIssuerCommonNameTest_2399 : public ::testing::Test {
protected:
  static PopplerCertificateInfo MakeEmpty() {
    PopplerCertificateInfo info{};
    info.id = nullptr;
    info.subject_common_name = nullptr;
    info.subject_organization = nullptr;
    info.subject_email = nullptr;
    info.issuer_common_name = nullptr;
    info.issuer_organization = nullptr;
    info.issuer_email = nullptr;
    info.issued = nullptr;
    info.expires = nullptr;
    return info;
  }

  static char *Dup(const char *s) {
    // Use glib allocator to match typical Poppler GLib conventions.
    return s ? g_strdup(s) : nullptr;
  }
};

TEST_F(PopplerCertificateInfoGetIssuerCommonNameTest_2399,
       NullCertificateInfoReturnsNull_2399) {
  // Boundary / error case: nullptr input should return nullptr per g_return_val_if_fail.
  const char *result = poppler_certificate_info_get_issuer_common_name(nullptr);
  EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerCertificateInfoGetIssuerCommonNameTest_2399,
       IssuerCommonNameNullReturnsNull_2399) {
  // Boundary case: valid object with null issuer_common_name should return nullptr.
  PopplerCertificateInfo info = MakeEmpty();

  const char *result = poppler_certificate_info_get_issuer_common_name(&info);
  EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerCertificateInfoGetIssuerCommonNameTest_2399,
       ReturnsExactPointerStoredInStruct_2399) {
  // Normal operation: should return the stored pointer (no copying observable via interface).
  PopplerCertificateInfo info = MakeEmpty();
  info.issuer_common_name = Dup("Example Issuer CN");

  const char *result = poppler_certificate_info_get_issuer_common_name(&info);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result, info.issuer_common_name);
  EXPECT_STREQ(result, "Example Issuer CN");

  g_free(info.issuer_common_name);
}

TEST_F(PopplerCertificateInfoGetIssuerCommonNameTest_2399,
       EmptyStringIssuerCommonNameReturnedAsEmptyString_2399) {
  // Boundary case: empty string should be returned as-is.
  PopplerCertificateInfo info = MakeEmpty();
  info.issuer_common_name = Dup("");

  const char *result = poppler_certificate_info_get_issuer_common_name(&info);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result, info.issuer_common_name);
  EXPECT_STREQ(result, "");

  g_free(info.issuer_common_name);
}

TEST_F(PopplerCertificateInfoGetIssuerCommonNameTest_2399,
       DoesNotDependOnOtherFields_2399) {
  // Normal operation: unrelated fields should not affect the returned issuer CN.
  PopplerCertificateInfo info = MakeEmpty();
  info.id = Dup("id-123");
  info.subject_common_name = Dup("Subject CN");
  info.subject_organization = Dup("Subject Org");
  info.subject_email = Dup("subject@example.com");
  info.issuer_common_name = Dup("Issuer CN");
  info.issuer_organization = Dup("Issuer Org");
  info.issuer_email = Dup("issuer@example.com");

  const char *result = poppler_certificate_info_get_issuer_common_name(&info);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result, info.issuer_common_name);
  EXPECT_STREQ(result, "Issuer CN");

  g_free(info.id);
  g_free(info.subject_common_name);
  g_free(info.subject_organization);
  g_free(info.subject_email);
  g_free(info.issuer_common_name);
  g_free(info.issuer_organization);
  g_free(info.issuer_email);
}