#include <gtest/gtest.h>

#include <glib.h>

extern "C" {

// Forward decls from the production code.
typedef struct _PopplerCertificateInfo PopplerCertificateInfo;

const char* poppler_certificate_info_get_id(const PopplerCertificateInfo* certificate_info);

}  // extern "C"

// In this compilation unit, we only need the public layout to allocate/fill fields.
// This is provided as "Known or Inferred Dependencies (Optional)" in the prompt.
struct _PopplerCertificateInfo {
  char* id;
  char* subject_common_name;
  char* subject_organization;
  char* subject_email;
  char* issuer_common_name;
  char* issuer_organization;
  char* issuer_email;
  int* issued;
  int* expires;
};

class PopplerCertificateInfoGetIdTest_2395 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Zero-init to avoid accidental garbage pointers.
    info_ = static_cast<PopplerCertificateInfo*>(g_malloc0(sizeof(_PopplerCertificateInfo)));
  }

  void TearDown() override {
    if (info_) {
      // Only free what we allocate in tests.
      auto* impl = reinterpret_cast<_PopplerCertificateInfo*>(info_);
      g_free(impl->id);
      g_free(info_);
      info_ = nullptr;
    }
  }

  PopplerCertificateInfo* info_ = nullptr;
};

TEST_F(PopplerCertificateInfoGetIdTest_2395, ReturnsNullWhenCertificateInfoIsNull_2395) {
  EXPECT_EQ(poppler_certificate_info_get_id(nullptr), nullptr);
}

TEST_F(PopplerCertificateInfoGetIdTest_2395, ReturnsIdPointerWhenIdIsSet_2395) {
  auto* impl = reinterpret_cast<_PopplerCertificateInfo*>(info_);
  impl->id = g_strdup("cert-id-123");

  const char* id = poppler_certificate_info_get_id(info_);
  ASSERT_NE(id, nullptr);
  EXPECT_STREQ(id, "cert-id-123");
}

TEST_F(PopplerCertificateInfoGetIdTest_2395, ReturnsNullWhenIdFieldIsNull_2395) {
  auto* impl = reinterpret_cast<_PopplerCertificateInfo*>(info_);
  impl->id = nullptr;

  EXPECT_EQ(poppler_certificate_info_get_id(info_), nullptr);
}

TEST_F(PopplerCertificateInfoGetIdTest_2395, ReturnsUpdatedIdAfterIdChanges_2395) {
  auto* impl = reinterpret_cast<_PopplerCertificateInfo*>(info_);

  impl->id = g_strdup("first");
  const char* id1 = poppler_certificate_info_get_id(info_);
  ASSERT_NE(id1, nullptr);
  EXPECT_STREQ(id1, "first");

  g_free(impl->id);
  impl->id = g_strdup("second");
  const char* id2 = poppler_certificate_info_get_id(info_);
  ASSERT_NE(id2, nullptr);
  EXPECT_STREQ(id2, "second");
}

TEST_F(PopplerCertificateInfoGetIdTest_2395, ReturnsSamePointerAsStoredId_2395) {
  auto* impl = reinterpret_cast<_PopplerCertificateInfo*>(info_);
  impl->id = g_strdup("ptr-check");

  const char* returned = poppler_certificate_info_get_id(info_);
  ASSERT_NE(returned, nullptr);
  EXPECT_EQ(returned, impl->id);  // observable: returns the stored pointer
  EXPECT_STREQ(returned, "ptr-check");
}