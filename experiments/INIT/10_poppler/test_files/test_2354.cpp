// File: poppler-signing-data-copy-test.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <cstring>

// Prefer including the public Poppler GLib header(s) if available in your tree.
#include <poppler.h>

extern "C" {
// Function under test (implemented in poppler-form-field.cc)
PopplerSigningData *poppler_signing_data_copy(const PopplerSigningData *signing_data);
}

namespace {

static PopplerSigningData *MakeSigningDataAllFieldsSet() {
  PopplerSigningData *d =
      static_cast<PopplerSigningData *>(g_malloc0(sizeof(PopplerSigningData)));

  d->destination_filename = g_strdup("out.pdf");
  d->signature_text = g_strdup("Signed by Unit Test");
  d->signature_text_left = g_strdup("Left text");

  // Rectangle / colors / numeric fields
  d->signature_rect.x1 = 1.0;
  d->signature_rect.y1 = 2.0;
  d->signature_rect.x2 = 3.0;
  d->signature_rect.y2 = 4.0;

  d->font_color.red = 0x1111;
  d->font_color.green = 0x2222;
  d->font_color.blue = 0x3333;

  d->font_size = 10;
  d->left_font_size = 8;

  d->border_color.red = 0xAAAA;
  d->border_color.green = 0xBBBB;
  d->border_color.blue = 0xCCCC;
  d->border_width = 2;

  d->background_color.red = 0x0001;
  d->background_color.green = 0x0002;
  d->background_color.blue = 0x0003;

  d->field_partial_name = g_strdup("Sig1");
  d->reason = g_strdup("Approval");
  d->location = g_strdup("Seoul");
  d->image_path = g_strdup("/tmp/stamp.png");
  d->password = g_strdup("pw");
  d->document_owner_password = g_strdup("owner_pw");
  d->document_user_password = g_strdup("user_pw");

  // Avoid needing to construct PopplerCertificateInfo in tests:
  // keep certificate_info nullptr so copy stays observable and safe.
  d->certificate_info = nullptr;

  // Page is an int in PopplerSigningData (present in real struct).
  d->page = 3;

  return d;
}

static PopplerSigningData *MakeSigningDataWithNullAndEmptyStrings() {
  PopplerSigningData *d =
      static_cast<PopplerSigningData *>(g_malloc0(sizeof(PopplerSigningData)));

  // Mix of nullptr and empty strings
  d->destination_filename = nullptr;
  d->signature_text = g_strdup("");
  d->signature_text_left = nullptr;

  d->signature_rect.x1 = 0.0;
  d->signature_rect.y1 = 0.0;
  d->signature_rect.x2 = 0.0;
  d->signature_rect.y2 = 0.0;

  d->font_color.red = 0;
  d->font_color.green = 0;
  d->font_color.blue = 0;

  d->font_size = 0;
  d->left_font_size = 0;

  d->border_color.red = 0;
  d->border_color.green = 0;
  d->border_color.blue = 0;
  d->border_width = 0;

  d->background_color.red = 0;
  d->background_color.green = 0;
  d->background_color.blue = 0;

  d->field_partial_name = g_strdup("");
  d->reason = nullptr;
  d->location = g_strdup("");
  d->image_path = nullptr;
  d->password = g_strdup("");
  d->document_owner_password = nullptr;
  d->document_user_password = g_strdup("");

  d->certificate_info = nullptr;
  d->page = 0;

  return d;
}

static PopplerSigningData *MakeSigningDataWithLongString() {
  PopplerSigningData *d =
      static_cast<PopplerSigningData *>(g_malloc0(sizeof(PopplerSigningData)));

  // Long string boundary (not huge to avoid stress, but clearly > typical sizes)
  GString *gs = g_string_sized_new(5000);
  for (int i = 0; i < 4096; ++i) g_string_append_c(gs, 'a');
  d->destination_filename = g_string_free(gs, FALSE);  // transfers ownership (char*)

  d->signature_text = g_strdup("T");
  d->signature_text_left = g_strdup("L");

  d->certificate_info = nullptr;
  d->page = 1;

  return d;
}

static void FreeSigningData(PopplerSigningData *d) {
  if (!d) return;

  // Free the string fields shown in the provided snippet / common struct.
  g_free(d->destination_filename);
  g_free(d->signature_text);
  g_free(d->signature_text_left);

  g_free(d->field_partial_name);
  g_free(d->reason);
  g_free(d->location);
  g_free(d->image_path);
  g_free(d->password);
  g_free(d->document_owner_password);
  g_free(d->document_user_password);

  // We intentionally keep certificate_info == nullptr in these tests.
  g_free(d);
}

static void ExpectSameRect(const PopplerRectangle &a, const PopplerRectangle &b) {
  EXPECT_DOUBLE_EQ(a.x1, b.x1);
  EXPECT_DOUBLE_EQ(a.y1, b.y1);
  EXPECT_DOUBLE_EQ(a.x2, b.x2);
  EXPECT_DOUBLE_EQ(a.y2, b.y2);
}

static void ExpectSameColor(const PopplerColor &a, const PopplerColor &b) {
  EXPECT_EQ(a.red, b.red);
  EXPECT_EQ(a.green, b.green);
  EXPECT_EQ(a.blue, b.blue);
}

static void ExpectStringCopied(const char *orig, const char *cpy) {
  if (orig == nullptr) {
    EXPECT_EQ(cpy, nullptr);
    return;
  }
  ASSERT_NE(cpy, nullptr);
  EXPECT_STREQ(cpy, orig);
  // Deep copy: should not be the same pointer when non-null.
  EXPECT_NE(cpy, orig);
}

}  // namespace

class PopplerSigningDataCopyTest_2354 : public ::testing::Test {};

TEST_F(PopplerSigningDataCopyTest_2354, NullInputReturnsNull_2354) {
  EXPECT_EQ(poppler_signing_data_copy(nullptr), nullptr);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopiesAllObservableFieldsDeeply_2354) {
  PopplerSigningData *orig = MakeSigningDataAllFieldsSet();
  ASSERT_NE(orig, nullptr);

  PopplerSigningData *cpy = poppler_signing_data_copy(orig);
  ASSERT_NE(cpy, nullptr);

  // Strings: content equal, pointers distinct (deep copy).
  ExpectStringCopied(orig->destination_filename, cpy->destination_filename);
  ExpectStringCopied(orig->signature_text, cpy->signature_text);
  ExpectStringCopied(orig->signature_text_left, cpy->signature_text_left);
  ExpectStringCopied(orig->field_partial_name, cpy->field_partial_name);
  ExpectStringCopied(orig->reason, cpy->reason);
  ExpectStringCopied(orig->location, cpy->location);
  ExpectStringCopied(orig->image_path, cpy->image_path);
  ExpectStringCopied(orig->password, cpy->password);
  ExpectStringCopied(orig->document_owner_password, cpy->document_owner_password);
  ExpectStringCopied(orig->document_user_password, cpy->document_user_password);

  // Struct / numeric fields.
  ExpectSameRect(orig->signature_rect, cpy->signature_rect);
  ExpectSameColor(orig->font_color, cpy->font_color);
  EXPECT_EQ(orig->font_size, cpy->font_size);
  EXPECT_EQ(orig->left_font_size, cpy->left_font_size);

  ExpectSameColor(orig->border_color, cpy->border_color);
  EXPECT_EQ(orig->border_width, cpy->border_width);

  ExpectSameColor(orig->background_color, cpy->background_color);

  // Other simple fields.
  EXPECT_EQ(orig->page, cpy->page);

  // Certificate info: we kept it null, copy should keep null (observable and safe).
  EXPECT_EQ(orig->certificate_info, nullptr);
  EXPECT_EQ(cpy->certificate_info, nullptr);

  FreeSigningData(cpy);
  FreeSigningData(orig);
}

TEST_F(PopplerSigningDataCopyTest_2354, NullAndEmptyStringsAreHandled_2354) {
  PopplerSigningData *orig = MakeSigningDataWithNullAndEmptyStrings();
  ASSERT_NE(orig, nullptr);

  PopplerSigningData *cpy = poppler_signing_data_copy(orig);
  ASSERT_NE(cpy, nullptr);

  // Null stays null; empty stays empty; deep copy where applicable.
  ExpectStringCopied(orig->destination_filename, cpy->destination_filename);
  ExpectStringCopied(orig->signature_text, cpy->signature_text);
  ExpectStringCopied(orig->signature_text_left, cpy->signature_text_left);

  ExpectStringCopied(orig->field_partial_name, cpy->field_partial_name);
  ExpectStringCopied(orig->reason, cpy->reason);
  ExpectStringCopied(orig->location, cpy->location);
  ExpectStringCopied(orig->image_path, cpy->image_path);
  ExpectStringCopied(orig->password, cpy->password);
  ExpectStringCopied(orig->document_owner_password, cpy->document_owner_password);
  ExpectStringCopied(orig->document_user_password, cpy->document_user_password);

  // Basic fields still copy.
  ExpectSameRect(orig->signature_rect, cpy->signature_rect);
  ExpectSameColor(orig->font_color, cpy->font_color);
  ExpectSameColor(orig->border_color, cpy->border_color);
  ExpectSameColor(orig->background_color, cpy->background_color);
  EXPECT_EQ(orig->font_size, cpy->font_size);
  EXPECT_EQ(orig->left_font_size, cpy->left_font_size);
  EXPECT_EQ(orig->border_width, cpy->border_width);
  EXPECT_EQ(orig->page, cpy->page);

  FreeSigningData(cpy);
  FreeSigningData(orig);
}

TEST_F(PopplerSigningDataCopyTest_2354, ModifyingOriginalDoesNotAffectCopy_2354) {
  PopplerSigningData *orig = MakeSigningDataAllFieldsSet();
  ASSERT_NE(orig, nullptr);

  PopplerSigningData *cpy = poppler_signing_data_copy(orig);
  ASSERT_NE(cpy, nullptr);
  ASSERT_NE(orig->destination_filename, nullptr);
  ASSERT_NE(cpy->destination_filename, nullptr);

  // Mutate the original buffer in-place; copy should remain unchanged.
  const char *copy_before = cpy->destination_filename;
  ASSERT_STREQ(copy_before, "out.pdf");

  orig->destination_filename[0] = 'X';
  EXPECT_STREQ(orig->destination_filename, "Xut.pdf");
  EXPECT_STREQ(cpy->destination_filename, "out.pdf");

  FreeSigningData(cpy);
  FreeSigningData(orig);
}

TEST_F(PopplerSigningDataCopyTest_2354, LongStringCopiesCorrectly_2354) {
  PopplerSigningData *orig = MakeSigningDataWithLongString();
  ASSERT_NE(orig, nullptr);
  ASSERT_NE(orig->destination_filename, nullptr);

  PopplerSigningData *cpy = poppler_signing_data_copy(orig);
  ASSERT_NE(cpy, nullptr);

  ExpectStringCopied(orig->destination_filename, cpy->destination_filename);

  // Basic sanity on length equality (boundary-ish behavior).
  EXPECT_EQ(std::strlen(orig->destination_filename), std::strlen(cpy->destination_filename));

  FreeSigningData(cpy);
  FreeSigningData(orig);
}