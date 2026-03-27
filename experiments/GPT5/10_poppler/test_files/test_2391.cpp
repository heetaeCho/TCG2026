//===----------------------------------------------------------------------===//
// poppler_signing_data_get_document_owner_password unit tests (TEST_ID=2391)
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>

#include <glib.h>

#include "poppler.h"

// We only need the layout for fields used by the tested API. This mirrors the
// provided "Known or Inferred Dependencies" so we can build a valid instance
// for black-box testing.
struct _PopplerSigningData {
  char* destination_filename;
  char* signature_text;
  char* signature_text_left;
  PopplerRectangle signature_rect;
  int left_font_size;
  PopplerColor border_color;
  int border_width;
  PopplerColor background_color;
  char* field_partial_name;
  char* reason;
  char* location;
  char* image_path;
  char* password;
  char* document_owner_password;
  char* document_user_password;
};

class PopplerSigningDataGetDocumentOwnerPasswordTest_2391 : public ::testing::Test {
protected:
  void SetUp() override {
    signing_data_ = static_cast<PopplerSigningData*>(g_malloc0(sizeof(_PopplerSigningData)));
    ASSERT_NE(signing_data_, nullptr);
  }

  void TearDown() override {
    if (signing_data_) {
      // Only free what we allocate in each test.
      auto* sd = reinterpret_cast<_PopplerSigningData*>(signing_data_);
      g_free(sd->document_owner_password);
      signing_data_ = nullptr;
    }
  }

  PopplerSigningData* signing_data_ = nullptr;
};

TEST_F(PopplerSigningDataGetDocumentOwnerPasswordTest_2391,
       NullSigningDataReturnsNull_2391) {
  // Error/boundary: null input should return null (observable behavior).
  const gchar* result = poppler_signing_data_get_document_owner_password(nullptr);
  EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerSigningDataGetDocumentOwnerPasswordTest_2391,
       DefaultOwnerPasswordIsNullWhenUnset_2391) {
  // Normal: newly zero-initialized struct has null password pointer.
  const gchar* result = poppler_signing_data_get_document_owner_password(signing_data_);
  EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerSigningDataGetDocumentOwnerPasswordTest_2391,
       ReturnsPointerToOwnerPasswordWhenSet_2391) {
  auto* sd = reinterpret_cast<_PopplerSigningData*>(signing_data_);
  sd->document_owner_password = g_strdup("owner-secret");
  ASSERT_NE(sd->document_owner_password, nullptr);

  const gchar* result = poppler_signing_data_get_document_owner_password(signing_data_);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "owner-secret");
}

TEST_F(PopplerSigningDataGetDocumentOwnerPasswordTest_2391,
       ReflectsUpdatedOwnerPasswordAfterChange_2391) {
  auto* sd = reinterpret_cast<_PopplerSigningData*>(signing_data_);
  sd->document_owner_password = g_strdup("first");
  ASSERT_NE(sd->document_owner_password, nullptr);

  const gchar* result1 = poppler_signing_data_get_document_owner_password(signing_data_);
  ASSERT_NE(result1, nullptr);
  EXPECT_STREQ(result1, "first");

  // Update to a different value and ensure getter reflects the change.
  g_free(sd->document_owner_password);
  sd->document_owner_password = g_strdup("second");
  ASSERT_NE(sd->document_owner_password, nullptr);

  const gchar* result2 = poppler_signing_data_get_document_owner_password(signing_data_);
  ASSERT_NE(result2, nullptr);
  EXPECT_STREQ(result2, "second");
}

TEST_F(PopplerSigningDataGetDocumentOwnerPasswordTest_2391,
       ReturnsNonNullForEmptyStringPassword_2391) {
  // Boundary: empty string is a valid C string; getter should return non-null
  // and preserve exact contents.
  auto* sd = reinterpret_cast<_PopplerSigningData*>(signing_data_);
  sd->document_owner_password = g_strdup("");
  ASSERT_NE(sd->document_owner_password, nullptr);

  const gchar* result = poppler_signing_data_get_document_owner_password(signing_data_);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "");
}

TEST_F(PopplerSigningDataGetDocumentOwnerPasswordTest_2391,
       DoesNotReturnUserPasswordWhenOnlyUserPasswordSet_2391) {
  // Boundary/behavioral: ensure the owner getter doesn't accidentally expose
  // a different field (user password). Observable via returned pointer/value.
  auto* sd = reinterpret_cast<_PopplerSigningData*>(signing_data_);

  // Set only document_user_password; leave owner password null.
  sd->document_user_password = g_strdup("user-secret");
  ASSERT_NE(sd->document_user_password, nullptr);

  const gchar* result = poppler_signing_data_get_document_owner_password(signing_data_);
  EXPECT_EQ(result, nullptr);

  g_free(sd->document_user_password);
  sd->document_user_password = nullptr;
}