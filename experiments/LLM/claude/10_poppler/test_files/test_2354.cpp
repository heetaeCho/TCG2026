#include <glib.h>
#include <gtest/gtest.h>
#include <cstring>

// Include the poppler glib headers
#include "poppler-form-field.h"

class PopplerSigningDataCopyTest_2354 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(PopplerSigningDataCopyTest_2354, CopyNullReturnsNull_2354)
{
    PopplerSigningData *result = poppler_signing_data_copy(nullptr);
    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopyNewlyCreatedSigningData_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);
    EXPECT_NE(copy, original);

    poppler_signing_data_free(copy);
    poppler_signing_data_free(original);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopyPreservesDestinationFilename_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    poppler_signing_data_set_destination_filename(original, "/tmp/test_output.pdf");

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);

    const char *orig_filename = poppler_signing_data_get_destination_filename(original);
    const char *copy_filename = poppler_signing_data_get_destination_filename(copy);

    ASSERT_NE(orig_filename, nullptr);
    ASSERT_NE(copy_filename, nullptr);
    EXPECT_STREQ(orig_filename, copy_filename);
    // Ensure it's a deep copy (different pointers)
    EXPECT_NE(orig_filename, copy_filename);

    poppler_signing_data_free(copy);
    poppler_signing_data_free(original);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopyPreservesSignatureText_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    poppler_signing_data_set_signature_text(original, "Signed by Test User");

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);

    const char *orig_text = poppler_signing_data_get_signature_text(original);
    const char *copy_text = poppler_signing_data_get_signature_text(copy);

    ASSERT_NE(orig_text, nullptr);
    ASSERT_NE(copy_text, nullptr);
    EXPECT_STREQ(orig_text, copy_text);
    EXPECT_NE(orig_text, copy_text);

    poppler_signing_data_free(copy);
    poppler_signing_data_free(original);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopyPreservesSignatureTextLeft_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    poppler_signing_data_set_signature_text_left(original, "Left text content");

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);

    const char *orig_text_left = poppler_signing_data_get_signature_text_left(original);
    const char *copy_text_left = poppler_signing_data_get_signature_text_left(copy);

    ASSERT_NE(orig_text_left, nullptr);
    ASSERT_NE(copy_text_left, nullptr);
    EXPECT_STREQ(orig_text_left, copy_text_left);

    poppler_signing_data_free(copy);
    poppler_signing_data_free(original);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopyPreservesPage_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    poppler_signing_data_set_page(original, 5);

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);

    EXPECT_EQ(poppler_signing_data_get_page(original), poppler_signing_data_get_page(copy));
    EXPECT_EQ(poppler_signing_data_get_page(copy), 5);

    poppler_signing_data_free(copy);
    poppler_signing_data_free(original);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopyPreservesSignatureRectangle_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    PopplerRectangle rect;
    rect.x1 = 10.0;
    rect.y1 = 20.0;
    rect.x2 = 200.0;
    rect.y2 = 100.0;
    poppler_signing_data_set_signature_rectangle(original, &rect);

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);

    const PopplerRectangle *orig_rect = poppler_signing_data_get_signature_rectangle(original);
    const PopplerRectangle *copy_rect = poppler_signing_data_get_signature_rectangle(copy);

    ASSERT_NE(orig_rect, nullptr);
    ASSERT_NE(copy_rect, nullptr);
    EXPECT_DOUBLE_EQ(orig_rect->x1, copy_rect->x1);
    EXPECT_DOUBLE_EQ(orig_rect->y1, copy_rect->y1);
    EXPECT_DOUBLE_EQ(orig_rect->x2, copy_rect->x2);
    EXPECT_DOUBLE_EQ(orig_rect->y2, copy_rect->y2);

    poppler_signing_data_free(copy);
    poppler_signing_data_free(original);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopyPreservesFontSize_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    poppler_signing_data_set_font_size(original, 14.5);

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);

    EXPECT_DOUBLE_EQ(poppler_signing_data_get_font_size(original), poppler_signing_data_get_font_size(copy));

    poppler_signing_data_free(copy);
    poppler_signing_data_free(original);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopyPreservesLeftFontSize_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    poppler_signing_data_set_left_font_size(original, 10.0);

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);

    EXPECT_DOUBLE_EQ(poppler_signing_data_get_left_font_size(original), poppler_signing_data_get_left_font_size(copy));

    poppler_signing_data_free(copy);
    poppler_signing_data_free(original);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopyPreservesFontColor_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    PopplerColor color;
    color.red = 255;
    color.green = 128;
    color.blue = 64;
    poppler_signing_data_set_font_color(original, &color);

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);

    const PopplerColor *orig_color = poppler_signing_data_get_font_color(original);
    const PopplerColor *copy_color = poppler_signing_data_get_font_color(copy);

    ASSERT_NE(orig_color, nullptr);
    ASSERT_NE(copy_color, nullptr);
    EXPECT_EQ(orig_color->red, copy_color->red);
    EXPECT_EQ(orig_color->green, copy_color->green);
    EXPECT_EQ(orig_color->blue, copy_color->blue);

    poppler_signing_data_free(copy);
    poppler_signing_data_free(original);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopyPreservesBorderColor_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    PopplerColor border_color;
    border_color.red = 0;
    border_color.green = 0;
    border_color.blue = 0;
    poppler_signing_data_set_border_color(original, &border_color);

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);

    const PopplerColor *orig_bc = poppler_signing_data_get_border_color(original);
    const PopplerColor *copy_bc = poppler_signing_data_get_border_color(copy);

    ASSERT_NE(orig_bc, nullptr);
    ASSERT_NE(copy_bc, nullptr);
    EXPECT_EQ(orig_bc->red, copy_bc->red);
    EXPECT_EQ(orig_bc->green, copy_bc->green);
    EXPECT_EQ(orig_bc->blue, copy_bc->blue);

    poppler_signing_data_free(copy);
    poppler_signing_data_free(original);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopyPreservesBorderWidth_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    poppler_signing_data_set_border_width(original, 3.0);

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);

    EXPECT_DOUBLE_EQ(poppler_signing_data_get_border_width(original), poppler_signing_data_get_border_width(copy));

    poppler_signing_data_free(copy);
    poppler_signing_data_free(original);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopyPreservesBackgroundColor_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    PopplerColor bg_color;
    bg_color.red = 65535;
    bg_color.green = 65535;
    bg_color.blue = 65535;
    poppler_signing_data_set_background_color(original, &bg_color);

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);

    const PopplerColor *orig_bg = poppler_signing_data_get_background_color(original);
    const PopplerColor *copy_bg = poppler_signing_data_get_background_color(copy);

    ASSERT_NE(orig_bg, nullptr);
    ASSERT_NE(copy_bg, nullptr);
    EXPECT_EQ(orig_bg->red, copy_bg->red);
    EXPECT_EQ(orig_bg->green, copy_bg->green);
    EXPECT_EQ(orig_bg->blue, copy_bg->blue);

    poppler_signing_data_free(copy);
    poppler_signing_data_free(original);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopyPreservesFieldPartialName_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    poppler_signing_data_set_field_partial_name(original, "SignatureField1");

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);

    const char *orig_name = poppler_signing_data_get_field_partial_name(original);
    const char *copy_name = poppler_signing_data_get_field_partial_name(copy);

    ASSERT_NE(orig_name, nullptr);
    ASSERT_NE(copy_name, nullptr);
    EXPECT_STREQ(orig_name, copy_name);
    EXPECT_NE(orig_name, copy_name);

    poppler_signing_data_free(copy);
    poppler_signing_data_free(original);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopyPreservesReason_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    poppler_signing_data_set_reason(original, "I approve this document");

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);

    const char *orig_reason = poppler_signing_data_get_reason(original);
    const char *copy_reason = poppler_signing_data_get_reason(copy);

    ASSERT_NE(orig_reason, nullptr);
    ASSERT_NE(copy_reason, nullptr);
    EXPECT_STREQ(orig_reason, copy_reason);

    poppler_signing_data_free(copy);
    poppler_signing_data_free(original);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopyPreservesLocation_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    poppler_signing_data_set_location(original, "New York, USA");

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);

    const char *orig_location = poppler_signing_data_get_location(original);
    const char *copy_location = poppler_signing_data_get_location(copy);

    ASSERT_NE(orig_location, nullptr);
    ASSERT_NE(copy_location, nullptr);
    EXPECT_STREQ(orig_location, copy_location);

    poppler_signing_data_free(copy);
    poppler_signing_data_free(original);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopyPreservesImagePath_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    poppler_signing_data_set_image_path(original, "/tmp/signature.png");

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);

    const char *orig_path = poppler_signing_data_get_image_path(original);
    const char *copy_path = poppler_signing_data_get_image_path(copy);

    ASSERT_NE(orig_path, nullptr);
    ASSERT_NE(copy_path, nullptr);
    EXPECT_STREQ(orig_path, copy_path);

    poppler_signing_data_free(copy);
    poppler_signing_data_free(original);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopyPreservesPassword_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    poppler_signing_data_set_password(original, "secretpassword123");

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);

    const char *orig_pass = poppler_signing_data_get_password(original);
    const char *copy_pass = poppler_signing_data_get_password(copy);

    ASSERT_NE(orig_pass, nullptr);
    ASSERT_NE(copy_pass, nullptr);
    EXPECT_STREQ(orig_pass, copy_pass);
    EXPECT_NE(orig_pass, copy_pass);

    poppler_signing_data_free(copy);
    poppler_signing_data_free(original);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopyPreservesDocumentOwnerPassword_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    poppler_signing_data_set_document_owner_password(original, "ownerpass");

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);

    const char *orig_owner = poppler_signing_data_get_document_owner_password(original);
    const char *copy_owner = poppler_signing_data_get_document_owner_password(copy);

    ASSERT_NE(orig_owner, nullptr);
    ASSERT_NE(copy_owner, nullptr);
    EXPECT_STREQ(orig_owner, copy_owner);

    poppler_signing_data_free(copy);
    poppler_signing_data_free(original);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopyPreservesDocumentUserPassword_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    poppler_signing_data_set_document_user_password(original, "userpass");

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);

    const char *orig_user = poppler_signing_data_get_document_user_password(original);
    const char *copy_user = poppler_signing_data_get_document_user_password(copy);

    ASSERT_NE(orig_user, nullptr);
    ASSERT_NE(copy_user, nullptr);
    EXPECT_STREQ(orig_user, copy_user);

    poppler_signing_data_free(copy);
    poppler_signing_data_free(original);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopyIsIndependentFromOriginal_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    poppler_signing_data_set_destination_filename(original, "/tmp/original.pdf");
    poppler_signing_data_set_signature_text(original, "Original Text");
    poppler_signing_data_set_page(original, 3);

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);

    // Modify original after copy
    poppler_signing_data_set_destination_filename(original, "/tmp/modified.pdf");
    poppler_signing_data_set_signature_text(original, "Modified Text");
    poppler_signing_data_set_page(original, 7);

    // Copy should still have original values
    EXPECT_STREQ(poppler_signing_data_get_destination_filename(copy), "/tmp/original.pdf");
    EXPECT_STREQ(poppler_signing_data_get_signature_text(copy), "Original Text");
    EXPECT_EQ(poppler_signing_data_get_page(copy), 3);

    poppler_signing_data_free(copy);
    poppler_signing_data_free(original);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopyWithAllFieldsSet_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    poppler_signing_data_set_destination_filename(original, "/tmp/full_test.pdf");
    poppler_signing_data_set_signature_text(original, "Full Signature");
    poppler_signing_data_set_signature_text_left(original, "Left Text");
    poppler_signing_data_set_page(original, 2);

    PopplerRectangle rect = { 50.0, 50.0, 250.0, 150.0 };
    poppler_signing_data_set_signature_rectangle(original, &rect);

    PopplerColor font_color = { 100, 200, 300 };
    poppler_signing_data_set_font_color(original, &font_color);
    poppler_signing_data_set_font_size(original, 12.0);
    poppler_signing_data_set_left_font_size(original, 8.0);

    PopplerColor border_color = { 0, 0, 0 };
    poppler_signing_data_set_border_color(original, &border_color);
    poppler_signing_data_set_border_width(original, 2.0);

    PopplerColor bg_color = { 65535, 65535, 65535 };
    poppler_signing_data_set_background_color(original, &bg_color);

    poppler_signing_data_set_field_partial_name(original, "sig_field");
    poppler_signing_data_set_reason(original, "Approval");
    poppler_signing_data_set_location(original, "London");
    poppler_signing_data_set_image_path(original, "/tmp/sig.png");
    poppler_signing_data_set_password(original, "pass123");
    poppler_signing_data_set_document_owner_password(original, "owner123");
    poppler_signing_data_set_document_user_password(original, "user123");

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);

    // Verify all fields
    EXPECT_STREQ(poppler_signing_data_get_destination_filename(copy), "/tmp/full_test.pdf");
    EXPECT_STREQ(poppler_signing_data_get_signature_text(copy), "Full Signature");
    EXPECT_STREQ(poppler_signing_data_get_signature_text_left(copy), "Left Text");
    EXPECT_EQ(poppler_signing_data_get_page(copy), 2);

    const PopplerRectangle *copy_rect = poppler_signing_data_get_signature_rectangle(copy);
    ASSERT_NE(copy_rect, nullptr);
    EXPECT_DOUBLE_EQ(copy_rect->x1, 50.0);
    EXPECT_DOUBLE_EQ(copy_rect->y1, 50.0);
    EXPECT_DOUBLE_EQ(copy_rect->x2, 250.0);
    EXPECT_DOUBLE_EQ(copy_rect->y2, 150.0);

    const PopplerColor *copy_fc = poppler_signing_data_get_font_color(copy);
    ASSERT_NE(copy_fc, nullptr);
    EXPECT_EQ(copy_fc->red, 100);
    EXPECT_EQ(copy_fc->green, 200);
    EXPECT_EQ(copy_fc->blue, 300);

    EXPECT_DOUBLE_EQ(poppler_signing_data_get_font_size(copy), 12.0);
    EXPECT_DOUBLE_EQ(poppler_signing_data_get_left_font_size(copy), 8.0);

    const PopplerColor *copy_bc = poppler_signing_data_get_border_color(copy);
    ASSERT_NE(copy_bc, nullptr);
    EXPECT_EQ(copy_bc->red, 0);
    EXPECT_EQ(copy_bc->green, 0);
    EXPECT_EQ(copy_bc->blue, 0);

    EXPECT_DOUBLE_EQ(poppler_signing_data_get_border_width(copy), 2.0);

    const PopplerColor *copy_bg = poppler_signing_data_get_background_color(copy);
    ASSERT_NE(copy_bg, nullptr);
    EXPECT_EQ(copy_bg->red, 65535);
    EXPECT_EQ(copy_bg->green, 65535);
    EXPECT_EQ(copy_bg->blue, 65535);

    EXPECT_STREQ(poppler_signing_data_get_field_partial_name(copy), "sig_field");
    EXPECT_STREQ(poppler_signing_data_get_reason(copy), "Approval");
    EXPECT_STREQ(poppler_signing_data_get_location(copy), "London");
    EXPECT_STREQ(poppler_signing_data_get_image_path(copy), "/tmp/sig.png");
    EXPECT_STREQ(poppler_signing_data_get_password(copy), "pass123");
    EXPECT_STREQ(poppler_signing_data_get_document_owner_password(copy), "owner123");
    EXPECT_STREQ(poppler_signing_data_get_document_user_password(copy), "user123");

    poppler_signing_data_free(copy);
    poppler_signing_data_free(original);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopyWithEmptyStrings_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    poppler_signing_data_set_destination_filename(original, "");
    poppler_signing_data_set_signature_text(original, "");
    poppler_signing_data_set_reason(original, "");

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);

    const char *copy_filename = poppler_signing_data_get_destination_filename(copy);
    const char *copy_text = poppler_signing_data_get_signature_text(copy);
    const char *copy_reason = poppler_signing_data_get_reason(copy);

    if (copy_filename != nullptr) {
        EXPECT_STREQ(copy_filename, "");
    }
    if (copy_text != nullptr) {
        EXPECT_STREQ(copy_text, "");
    }
    if (copy_reason != nullptr) {
        EXPECT_STREQ(copy_reason, "");
    }

    poppler_signing_data_free(copy);
    poppler_signing_data_free(original);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopyWithZeroPage_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    poppler_signing_data_set_page(original, 0);

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);

    EXPECT_EQ(poppler_signing_data_get_page(copy), 0);

    poppler_signing_data_free(copy);
    poppler_signing_data_free(original);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopyWithZeroBorderWidth_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    poppler_signing_data_set_border_width(original, 0.0);

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);

    EXPECT_DOUBLE_EQ(poppler_signing_data_get_border_width(copy), 0.0);

    poppler_signing_data_free(copy);
    poppler_signing_data_free(original);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopyWithZeroFontSize_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    poppler_signing_data_set_font_size(original, 0.0);

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);

    EXPECT_DOUBLE_EQ(poppler_signing_data_get_font_size(copy), 0.0);

    poppler_signing_data_free(copy);
    poppler_signing_data_free(original);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopyPreservesLargePageNumber_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    poppler_signing_data_set_page(original, 99999);

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);

    EXPECT_EQ(poppler_signing_data_get_page(copy), 99999);

    poppler_signing_data_free(copy);
    poppler_signing_data_free(original);
}

TEST_F(PopplerSigningDataCopyTest_2354, CopyWithLongStringValues_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    // Create a long string
    std::string long_str(1000, 'A');
    poppler_signing_data_set_destination_filename(original, long_str.c_str());

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);

    const char *copy_filename = poppler_signing_data_get_destination_filename(copy);
    ASSERT_NE(copy_filename, nullptr);
    EXPECT_STREQ(copy_filename, long_str.c_str());

    poppler_signing_data_free(copy);
    poppler_signing_data_free(original);
}

TEST_F(PopplerSigningDataCopyTest_2354, FreeCopyDoesNotAffectOriginal_2354)
{
    PopplerSigningData *original = poppler_signing_data_new();
    ASSERT_NE(original, nullptr);

    poppler_signing_data_set_destination_filename(original, "/tmp/test.pdf");
    poppler_signing_data_set_signature_text(original, "Test Signature");

    PopplerSigningData *copy = poppler_signing_data_copy(original);
    ASSERT_NE(copy, nullptr);

    // Free the copy
    poppler_signing_data_free(copy);

    // Original should still be accessible and valid
    EXPECT_STREQ(poppler_signing_data_get_destination_filename(original), "/tmp/test.pdf");
    EXPECT_STREQ(poppler_signing_data_get_signature_text(original), "Test Signature");

    poppler_signing_data_free(original);
}
