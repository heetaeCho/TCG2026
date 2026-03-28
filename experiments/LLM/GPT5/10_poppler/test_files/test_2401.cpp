#include <gtest/gtest.h>

#include <glib.h>

extern "C" {
#include "poppler.h"
}

// The production struct is shown in the prompt as an optional dependency.
// We only use it to construct observable inputs for the C API under test.
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

class PopplerCertificateInfoGetIssuerEmailTest_2401 : public ::testing::Test {
protected:
  void TearDown() override { g_free(email_); }

  char *email_ = nullptr;
};

TEST_F(PopplerCertificateInfoGetIssuerEmailTest_2401, ReturnsIssuerEmailPointer_2401) {
  _PopplerCertificateInfo info{};
  email_ = g_strdup("issuer@example.com");
  info.issuer_email = email_;

  const char *ret = poppler_certificate_info_get_issuer_email(
      reinterpret_cast<const PopplerCertificateInfo *>(&info));

  ASSERT_NE(ret, nullptr);
  EXPECT_STREQ(ret, "issuer@example.com");
  // Observable behavior: returns the stored pointer (no copying implied by API).
  EXPECT_EQ(ret, info.issuer_email);
}

TEST_F(PopplerCertificateInfoGetIssuerEmailTest_2401, ReturnsNullWhenIssuerEmailIsNull_2401) {
  _PopplerCertificateInfo info{};
  info.issuer_email = nullptr;

  const char *ret = poppler_certificate_info_get_issuer_email(
      reinterpret_cast<const PopplerCertificateInfo *>(&info));

  EXPECT_EQ(ret, nullptr);
}

TEST_F(PopplerCertificateInfoGetIssuerEmailTest_2401, AcceptsEmptyStringIssuerEmail_2401) {
  _PopplerCertificateInfo info{};
  email_ = g_strdup("");
  info.issuer_email = email_;

  const char *ret = poppler_certificate_info_get_issuer_email(
      reinterpret_cast<const PopplerCertificateInfo *>(&info));

  ASSERT_NE(ret, nullptr);
  EXPECT_STREQ(ret, "");
  EXPECT_EQ(ret, info.issuer_email);
}

TEST_F(PopplerCertificateInfoGetIssuerEmailTest_2401, GReturnValIfFailNullptrInputReturnsNull_2401) {
  // Exceptional/error case (observable): g_return_val_if_fail should return nullptr.
  const char *ret = poppler_certificate_info_get_issuer_email(nullptr);
  EXPECT_EQ(ret, nullptr);
}

TEST_F(PopplerCertificateInfoGetIssuerEmailTest_2401, DoesNotDependOnOtherFields_2401) {
  _PopplerCertificateInfo info{};
  // Populate unrelated fields with non-null pointers to ensure the function
  // still returns issuer_email.
  info.id = const_cast<char *>("id");
  info.subject_common_name = const_cast<char *>("sub_cn");
  info.subject_organization = const_cast<char *>("sub_org");
  info.subject_email = const_cast<char *>("sub@example.com");
  info.issuer_common_name = const_cast<char *>("iss_cn");
  info.issuer_organization = const_cast<char *>("iss_org");
  info.issued = reinterpret_cast<int *>(0x1);
  info.expires = reinterpret_cast<int *>(0x2);

  email_ = g_strdup("only-this-matters@example.com");
  info.issuer_email = email_;

  const char *ret = poppler_certificate_info_get_issuer_email(
      reinterpret_cast<const PopplerCertificateInfo *>(&info));

  ASSERT_NE(ret, nullptr);
  EXPECT_STREQ(ret, "only-this-matters@example.com");
  EXPECT_EQ(ret, info.issuer_email);
}