// poppler-signing-data-get-document-user-password-test.cc
//
// Unit tests for:
//   const gchar *poppler_signing_data_get_document_user_password(const PopplerSigningData *signing_data)
//
// Constraints:
// - Treat implementation as black box.
// - Only use public/visible interface behavior.
// - No private state access beyond what is explicitly provided in the prompt (struct fields are provided).
//
// TEST_ID: 2393

#include <gtest/gtest.h>

#include <glib.h>
#include <cstring>

// The production code uses these types/names.
typedef struct _PopplerSigningData PopplerSigningData;

struct PopplerRectangle {
  double x1;
  double y1;
  double x2;
  double y2;
};

struct PopplerColor {
  guint16 red;
  guint16 green;
  guint16 blue;
};

struct _PopplerSigningData {
 public:
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

extern "C" {
const gchar* poppler_signing_data_get_document_user_password(
    const PopplerSigningData* signing_data);
}

class PopplerSigningDataGetDocumentUserPasswordTest_2393 : public ::testing::Test {
 protected:
  static PopplerSigningData* NewZeroed() {
    auto* sd = static_cast<PopplerSigningData*>(g_malloc0(sizeof(_PopplerSigningData)));
    return sd;
  }

  static void FreeSigningDataOnly(PopplerSigningData* sd) {
    g_free(sd);
  }
};

TEST_F(PopplerSigningDataGetDocumentUserPasswordTest_2393, NullSigningDataReturnsEmptyString_2393) {
  const gchar* result = poppler_signing_data_get_document_user_password(nullptr);

  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "");
}

TEST_F(PopplerSigningDataGetDocumentUserPasswordTest_2393, ReturnsStoredPasswordPointer_2393) {
  PopplerSigningData* sd = NewZeroed();
  auto* impl = reinterpret_cast<_PopplerSigningData*>(sd);

  // Use a stable string literal to verify pointer identity (observable behavior).
  const char* kPwd = "user-pass";
  impl->document_user_password = const_cast<char*>(kPwd);

  const gchar* result = poppler_signing_data_get_document_user_password(sd);

  EXPECT_EQ(result, kPwd);
  EXPECT_STREQ(result, "user-pass");

  FreeSigningDataOnly(sd);
}

TEST_F(PopplerSigningDataGetDocumentUserPasswordTest_2393, ReturnsEmptyStringWhenFieldIsNull_2393) {
  PopplerSigningData* sd = NewZeroed();
  auto* impl = reinterpret_cast<_PopplerSigningData*>(sd);

  // Ensure the field is null (g_malloc0 already does this, but be explicit).
  impl->document_user_password = nullptr;

  const gchar* result = poppler_signing_data_get_document_user_password(sd);

  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "");

  FreeSigningDataOnly(sd);
}

TEST_F(PopplerSigningDataGetDocumentUserPasswordTest_2393, ReturnsPointerEvenIfPasswordIsEmptyCStr_2393) {
  PopplerSigningData* sd = NewZeroed();
  auto* impl = reinterpret_cast<_PopplerSigningData*>(sd);

  // Empty C-string is different from null; function should return what's stored.
  char empty_pwd[] = "";
  impl->document_user_password = empty_pwd;

  const gchar* result = poppler_signing_data_get_document_user_password(sd);

  EXPECT_EQ(result, empty_pwd);
  EXPECT_STREQ(result, "");

  FreeSigningDataOnly(sd);
}

TEST_F(PopplerSigningDataGetDocumentUserPasswordTest_2393, DoesNotDependOnOtherFields_2393) {
  PopplerSigningData* sd = NewZeroed();
  auto* impl = reinterpret_cast<_PopplerSigningData*>(sd);

  const char* kPwd = "p@ssw0rd!";
  impl->document_user_password = const_cast<char*>(kPwd);

  // Populate other fields with some values to ensure they don't affect result.
  impl->destination_filename = const_cast<char*>("out.pdf");
  impl->signature_text = const_cast<char*>("sig");
  impl->password = const_cast<char*>("other-password");
  impl->document_owner_password = const_cast<char*>("owner-password");
  impl->left_font_size = 12;
  impl->border_width = 2;

  const gchar* result = poppler_signing_data_get_document_user_password(sd);

  EXPECT_EQ(result, kPwd);
  EXPECT_STREQ(result, "p@ssw0rd!");

  FreeSigningDataOnly(sd);
}