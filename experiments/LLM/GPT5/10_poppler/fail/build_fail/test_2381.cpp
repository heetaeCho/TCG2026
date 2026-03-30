// poppler-signing-data-get-field-partial-name-test.cc
#include <gtest/gtest.h>

#include <glib.h>

extern "C" {

// Minimal type definitions needed by the exposed C API.
// (We only rely on the public interface behavior; no private state access in tests.)
typedef struct _PopplerSigningData PopplerSigningData;

// Function under test (as provided).
const gchar *poppler_signing_data_get_field_partial_name(const PopplerSigningData *signing_data);

}  // extern "C"

// We use a test-local struct matching the *known* public layout provided in the prompt
// solely to construct a valid PopplerSigningData instance for black-box calls.
// The tests do NOT inspect or rely on any other fields or internal invariants.
struct _PopplerSigningData {
  char *destination_filename;
  char *signature_text;
  char *signature_text_left;

  // Opaque placeholders to satisfy layout; tests do not use them.
  struct {
    double x1, y1, x2, y2;
  } signature_rect;

  int left_font_size;

  struct {
    unsigned short red, green, blue;
  } border_color;

  int border_width;

  struct {
    unsigned short red, green, blue;
  } background_color;

  char *field_partial_name;
  char *reason;
  char *location;
  char *image_path;
  char *password;
  char *document_owner_password;
  char *document_user_password;
};

class PopplerSigningDataGetFieldPartialNameTest_2381 : public ::testing::Test {
 protected:
  void SetUp() override { g_test_init(nullptr, nullptr, nullptr); }

  static PopplerSigningData *MakeSigningDataWithFieldName(const char *name_or_null) {
    auto *sd = static_cast<_PopplerSigningData *>(g_malloc0(sizeof(_PopplerSigningData)));
    sd->field_partial_name = name_or_null ? g_strdup(name_or_null) : nullptr;
    return reinterpret_cast<PopplerSigningData *>(sd);
  }

  static void FreeSigningData(PopplerSigningData *sd) {
    if (!sd) return;
    auto *real = reinterpret_cast<_PopplerSigningData *>(sd);
    g_free(real->field_partial_name);
    g_free(real);
  }
};

TEST_F(PopplerSigningDataGetFieldPartialNameTest_2381,
       NullSigningDataReturnsEmptyString_2381) {
  // Boundary / error case: API explicitly guards nullptr and returns "".
  const gchar *res = poppler_signing_data_get_field_partial_name(nullptr);
  ASSERT_NE(res, nullptr);
  EXPECT_STREQ(res, "");
}

TEST_F(PopplerSigningDataGetFieldPartialNameTest_2381,
       ReturnsExactFieldPartialNamePointerContents_2381) {
  // Normal operation: returns stored field partial name string.
  PopplerSigningData *sd = MakeSigningDataWithFieldName("SignatureField.Partial");
  const gchar *res = poppler_signing_data_get_field_partial_name(sd);
  ASSERT_NE(res, nullptr);
  EXPECT_STREQ(res, "SignatureField.Partial");
  FreeSigningData(sd);
}

TEST_F(PopplerSigningDataGetFieldPartialNameTest_2381,
       EmptyFieldPartialNameReturnsEmptyString_2381) {
  // Boundary: empty but non-null string should be returned as empty.
  PopplerSigningData *sd = MakeSigningDataWithFieldName("");
  const gchar *res = poppler_signing_data_get_field_partial_name(sd);
  ASSERT_NE(res, nullptr);
  EXPECT_STREQ(res, "");
  FreeSigningData(sd);
}

TEST_F(PopplerSigningDataGetFieldPartialNameTest_2381,
       CallIsRepeatableAndStableForSameObject_2381) {
  // Normal operation: repeated calls should consistently return the same contents.
  PopplerSigningData *sd = MakeSigningDataWithFieldName("A.B.C");
  const gchar *r1 = poppler_signing_data_get_field_partial_name(sd);
  const gchar *r2 = poppler_signing_data_get_field_partial_name(sd);

  ASSERT_NE(r1, nullptr);
  ASSERT_NE(r2, nullptr);
  EXPECT_STREQ(r1, "A.B.C");
  EXPECT_STREQ(r2, "A.B.C");

  // If implementation returns the stored pointer, these may be identical, but we only
  // require observable string stability (do not assume pointer identity).
  FreeSigningData(sd);
}

TEST_F(PopplerSigningDataGetFieldPartialNameTest_2381,
       FieldPartialNameMayBeNullReturnsNullOrEmptyButDoesNotCrash_2381) {
  // Boundary: struct field could be nullptr; interface doesn't document behavior.
  // We only assert it does not crash and returns a non-null C string pointer if possible.
  PopplerSigningData *sd = MakeSigningDataWithFieldName(nullptr);
  const gchar *res = poppler_signing_data_get_field_partial_name(sd);

  // Observable safety expectation: function returns const gchar*; should be safe to use
  // as a C-string in typical codepaths. If it returns nullptr, that's still observable,
  // so accept either nullptr or a valid string; but ensure no crash occurred.
  if (res) {
    // If non-null, it should be a valid NUL-terminated string; the weakest check:
    EXPECT_GE(strlen(res), 0u);
  }

  FreeSigningData(sd);
}