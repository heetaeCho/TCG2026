// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for:
//   poppler_certificate_info_get_subject_common_name()
//
// Constraints honored:
// - Treat implementation as black box (no internal logic inference beyond observable contract)
// - Only use public interface/signature + observable behavior
// - No private state access
//
// File under test (as provided):
//   ./TestProjects/poppler/glib/poppler-form-field.cc

#include <gtest/gtest.h>

#include <glib.h>

// Forward declarations matching the production interface.
typedef struct _PopplerCertificateInfo PopplerCertificateInfo;

extern "C" {
const char *poppler_certificate_info_get_subject_common_name(const PopplerCertificateInfo *certificate_info);
}

// Minimal struct layout provided in the prompt (used only to build observable inputs).
// This is not re-implementing logic; it's a test fixture input model.
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

class PopplerCertificateInfoGetSubjectCommonNameTest_2396 : public ::testing::Test {};

TEST_F(PopplerCertificateInfoGetSubjectCommonNameTest_2396,
       NullCertificateInfoReturnsNull_2396) {
  // Boundary / error case: nullptr input should return nullptr (observable via return value).
  const char* ret = poppler_certificate_info_get_subject_common_name(nullptr);
  EXPECT_EQ(ret, nullptr);
}

TEST_F(PopplerCertificateInfoGetSubjectCommonNameTest_2396,
       ReturnsPointerToSubjectCommonNameWhenPresent_2396) {
  // Normal operation: return should match the stored subject_common_name pointer.
  _PopplerCertificateInfo info{};
  info.subject_common_name = const_cast<char*>("Alice Example CN");

  const char* ret = poppler_certificate_info_get_subject_common_name(
      reinterpret_cast<const PopplerCertificateInfo*>(&info));

  EXPECT_EQ(ret, info.subject_common_name);
  EXPECT_STREQ(ret, "Alice Example CN");
}

TEST_F(PopplerCertificateInfoGetSubjectCommonNameTest_2396,
       ReturnsNullWhenSubjectCommonNameIsNull_2396) {
  // Boundary: subject_common_name field is nullptr; should return nullptr.
  _PopplerCertificateInfo info{};
  info.subject_common_name = nullptr;

  const char* ret = poppler_certificate_info_get_subject_common_name(
      reinterpret_cast<const PopplerCertificateInfo*>(&info));

  EXPECT_EQ(ret, nullptr);
}

TEST_F(PopplerCertificateInfoGetSubjectCommonNameTest_2396,
       ReturnsEmptyStringWhenSubjectCommonNameIsEmpty_2396) {
  // Boundary: empty string should be returned as-is (non-null pointer, empty content).
  _PopplerCertificateInfo info{};
  info.subject_common_name = const_cast<char*>("");

  const char* ret = poppler_certificate_info_get_subject_common_name(
      reinterpret_cast<const PopplerCertificateInfo*>(&info));

  ASSERT_NE(ret, nullptr);
  EXPECT_EQ(ret, info.subject_common_name);
  EXPECT_STREQ(ret, "");
}

TEST_F(PopplerCertificateInfoGetSubjectCommonNameTest_2396,
       ReturnedPointerReflectsUpdatedFieldAcrossCalls_2396) {
  // Observable behavior across calls: function returns current field pointer.
  _PopplerCertificateInfo info{};
  info.subject_common_name = const_cast<char*>("CN1");

  const char* ret1 = poppler_certificate_info_get_subject_common_name(
      reinterpret_cast<const PopplerCertificateInfo*>(&info));
  ASSERT_NE(ret1, nullptr);
  EXPECT_STREQ(ret1, "CN1");

  info.subject_common_name = const_cast<char*>("CN2");

  const char* ret2 = poppler_certificate_info_get_subject_common_name(
      reinterpret_cast<const PopplerCertificateInfo*>(&info));
  ASSERT_NE(ret2, nullptr);
  EXPECT_STREQ(ret2, "CN2");

  // Ensure the returned pointers correspond to the current field value.
  EXPECT_EQ(ret2, info.subject_common_name);
}

TEST_F(PopplerCertificateInfoGetSubjectCommonNameTest_2396,
       DoesNotDependOnOtherFields_2396) {
  // Normal/boundary: other fields populated should not affect returned CN pointer.
  _PopplerCertificateInfo info{};
  info.id = const_cast<char*>("id-123");
  info.subject_common_name = const_cast<char*>("Primary CN");
  info.subject_organization = const_cast<char*>("Org");
  info.subject_email = const_cast<char*>("a@example.com");
  info.issuer_common_name = const_cast<char*>("Issuer CN");
  info.issuer_organization = const_cast<char*>("Issuer Org");
  info.issuer_email = const_cast<char*>("issuer@example.com");
  info.issued = nullptr;
  info.expires = nullptr;

  const char* ret = poppler_certificate_info_get_subject_common_name(
      reinterpret_cast<const PopplerCertificateInfo*>(&info));

  EXPECT_EQ(ret, info.subject_common_name);
  EXPECT_STREQ(ret, "Primary CN");
}