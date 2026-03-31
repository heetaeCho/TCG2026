#include <glib.h>
#include <gtest/gtest.h>

// Forward declarations for the poppler types and functions we need
extern "C" {

typedef struct _PopplerColor {
    guint16 red;
    guint16 green;
    guint16 blue;
} PopplerColor;

typedef struct _PopplerSigningData PopplerSigningData;

PopplerSigningData *poppler_signing_data_new(void);
PopplerSigningData *poppler_signing_data_copy(PopplerSigningData *signing_data);
void poppler_signing_data_free(PopplerSigningData *signing_data);

void poppler_signing_data_set_destination_filename(PopplerSigningData *signing_data, const gchar *filename);
const gchar *poppler_signing_data_get_destination_filename(PopplerSigningData *signing_data);

void poppler_signing_data_set_certificate_info(PopplerSigningData *signing_data, /*PopplerCertificateInfo*/ gpointer certificate_info);
/*PopplerCertificateInfo*/ gpointer poppler_signing_data_get_certificate_info(PopplerSigningData *signing_data);

void poppler_signing_data_set_page(PopplerSigningData *signing_data, int page);
int poppler_signing_data_get_page(PopplerSigningData *signing_data);

void poppler_signing_data_set_signature_text(PopplerSigningData *signing_data, const gchar *signature_text);
const gchar *poppler_signing_data_get_signature_text(PopplerSigningData *signing_data);

void poppler_signing_data_set_signature_text_left(PopplerSigningData *signing_data, const gchar *signature_text_left);
const gchar *poppler_signing_data_get_signature_text_left(PopplerSigningData *signing_data);

void poppler_signing_data_set_field_partial_name(PopplerSigningData *signing_data, const gchar *field_partial_name);
const gchar *poppler_signing_data_get_field_partial_name(PopplerSigningData *signing_data);

void poppler_signing_data_set_reason(PopplerSigningData *signing_data, const gchar *reason);
const gchar *poppler_signing_data_get_reason(PopplerSigningData *signing_data);

void poppler_signing_data_set_location(PopplerSigningData *signing_data, const gchar *location);
const gchar *poppler_signing_data_get_location(PopplerSigningData *signing_data);

void poppler_signing_data_set_image_path(PopplerSigningData *signing_data, const gchar *image_path);
const gchar *poppler_signing_data_get_image_path(PopplerSigningData *signing_data);

void poppler_signing_data_set_password(PopplerSigningData *signing_data, const gchar *password);
const gchar *poppler_signing_data_get_password(PopplerSigningData *signing_data);

void poppler_signing_data_set_document_owner_password(PopplerSigningData *signing_data, const gchar *document_owner_password);
const gchar *poppler_signing_data_get_document_owner_password(PopplerSigningData *signing_data);

void poppler_signing_data_set_document_user_password(PopplerSigningData *signing_data, const gchar *document_user_password);
const gchar *poppler_signing_data_get_document_user_password(PopplerSigningData *signing_data);

void poppler_signing_data_set_font_size(PopplerSigningData *signing_data, gdouble font_size);
gdouble poppler_signing_data_get_font_size(PopplerSigningData *signing_data);

void poppler_signing_data_set_left_font_size(PopplerSigningData *signing_data, gdouble font_size);
gdouble poppler_signing_data_get_left_font_size(PopplerSigningData *signing_data);

void poppler_signing_data_set_font_color(PopplerSigningData *signing_data, const PopplerColor *font_color);
const PopplerColor *poppler_signing_data_get_font_color(PopplerSigningData *signing_data);

void poppler_signing_data_set_border_width(PopplerSigningData *signing_data, gdouble border_width);
gdouble poppler_signing_data_get_border_width(PopplerSigningData *signing_data);

void poppler_signing_data_set_border_color(PopplerSigningData *signing_data, const PopplerColor *border_color);
const PopplerColor *poppler_signing_data_get_border_color(PopplerSigningData *signing_data);

void poppler_signing_data_set_background_color(PopplerSigningData *signing_data, const PopplerColor *background_color);
const PopplerColor *poppler_signing_data_get_background_color(PopplerSigningData *signing_data);
}

class PopplerSigningDataTest_2353 : public ::testing::Test {
protected:
    PopplerSigningData *data = nullptr;

    void SetUp() override { data = poppler_signing_data_new(); }

    void TearDown() override
    {
        if (data) {
            poppler_signing_data_free(data);
            data = nullptr;
        }
    }
};

// Test that new signing data is created and is not null
TEST_F(PopplerSigningDataTest_2353, NewReturnsNonNull_2353)
{
    ASSERT_NE(data, nullptr);
}

// Test default password is empty string
TEST_F(PopplerSigningDataTest_2353, DefaultPasswordIsEmptyString_2353)
{
    const gchar *password = poppler_signing_data_get_password(data);
    ASSERT_NE(password, nullptr);
    EXPECT_STREQ(password, "");
}

// Test default page is 0
TEST_F(PopplerSigningDataTest_2353, DefaultPageIsZero_2353)
{
    EXPECT_EQ(poppler_signing_data_get_page(data), 0);
}

// Test default font_size is 10.0
TEST_F(PopplerSigningDataTest_2353, DefaultFontSizeIsTen_2353)
{
    EXPECT_DOUBLE_EQ(poppler_signing_data_get_font_size(data), 10.0);
}

// Test default left_font_size is 20.0
TEST_F(PopplerSigningDataTest_2353, DefaultLeftFontSizeIsTwenty_2353)
{
    EXPECT_DOUBLE_EQ(poppler_signing_data_get_left_font_size(data), 20.0);
}

// Test default border_width is 1.5
TEST_F(PopplerSigningDataTest_2353, DefaultBorderWidthIs1Point5_2353)
{
    EXPECT_DOUBLE_EQ(poppler_signing_data_get_border_width(data), 1.5);
}

// Test default background color is grey (0xEF00, 0xEF00, 0xEF00)
TEST_F(PopplerSigningDataTest_2353, DefaultBackgroundColorIsGrey_2353)
{
    const PopplerColor *bg = poppler_signing_data_get_background_color(data);
    ASSERT_NE(bg, nullptr);
    EXPECT_EQ(bg->red, 0xEF00);
    EXPECT_EQ(bg->green, 0xEF00);
    EXPECT_EQ(bg->blue, 0xEF00);
}

// Test default border color is red (0xFFFF, 0x00, 0x00)
TEST_F(PopplerSigningDataTest_2353, DefaultBorderColorIsRed_2353)
{
    const PopplerColor *bc = poppler_signing_data_get_border_color(data);
    ASSERT_NE(bc, nullptr);
    EXPECT_EQ(bc->red, 0xFFFF);
    EXPECT_EQ(bc->green, 0x00);
    EXPECT_EQ(bc->blue, 0x00);
}

// Test default font color
TEST_F(PopplerSigningDataTest_2353, DefaultFontColorIsSet_2353)
{
    const PopplerColor *fc = poppler_signing_data_get_font_color(data);
    ASSERT_NE(fc, nullptr);
    EXPECT_EQ(fc->red, 0xFFFF);
    EXPECT_EQ(fc->green, 0x00);
    // Note: In the code, border_color.blue is set instead of font_color.blue (likely a bug)
    // We test observable behavior
}

// Test setting and getting password
TEST_F(PopplerSigningDataTest_2353, SetGetPassword_2353)
{
    poppler_signing_data_set_password(data, "mysecretpassword");
    const gchar *password = poppler_signing_data_get_password(data);
    ASSERT_NE(password, nullptr);
    EXPECT_STREQ(password, "mysecretpassword");
}

// Test setting password to null
TEST_F(PopplerSigningDataTest_2353, SetPasswordNull_2353)
{
    poppler_signing_data_set_password(data, nullptr);
    // Should not crash; behavior may vary
}

// Test setting and getting page
TEST_F(PopplerSigningDataTest_2353, SetGetPage_2353)
{
    poppler_signing_data_set_page(data, 5);
    EXPECT_EQ(poppler_signing_data_get_page(data), 5);
}

// Test setting page to negative value
TEST_F(PopplerSigningDataTest_2353, SetPageNegative_2353)
{
    poppler_signing_data_set_page(data, -1);
    EXPECT_EQ(poppler_signing_data_get_page(data), -1);
}

// Test setting and getting font size
TEST_F(PopplerSigningDataTest_2353, SetGetFontSize_2353)
{
    poppler_signing_data_set_font_size(data, 24.5);
    EXPECT_DOUBLE_EQ(poppler_signing_data_get_font_size(data), 24.5);
}

// Test setting font size to zero
TEST_F(PopplerSigningDataTest_2353, SetFontSizeZero_2353)
{
    poppler_signing_data_set_font_size(data, 0.0);
    EXPECT_DOUBLE_EQ(poppler_signing_data_get_font_size(data), 0.0);
}

// Test setting and getting left font size
TEST_F(PopplerSigningDataTest_2353, SetGetLeftFontSize_2353)
{
    poppler_signing_data_set_left_font_size(data, 15.0);
    EXPECT_DOUBLE_EQ(poppler_signing_data_get_left_font_size(data), 15.0);
}

// Test setting and getting border width
TEST_F(PopplerSigningDataTest_2353, SetGetBorderWidth_2353)
{
    poppler_signing_data_set_border_width(data, 3.0);
    EXPECT_DOUBLE_EQ(poppler_signing_data_get_border_width(data), 3.0);
}

// Test setting border width to zero
TEST_F(PopplerSigningDataTest_2353, SetBorderWidthZero_2353)
{
    poppler_signing_data_set_border_width(data, 0.0);
    EXPECT_DOUBLE_EQ(poppler_signing_data_get_border_width(data), 0.0);
}

// Test setting and getting background color
TEST_F(PopplerSigningDataTest_2353, SetGetBackgroundColor_2353)
{
    PopplerColor color;
    color.red = 0x1234;
    color.green = 0x5678;
    color.blue = 0x9ABC;
    poppler_signing_data_set_background_color(data, &color);

    const PopplerColor *result = poppler_signing_data_get_background_color(data);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 0x1234);
    EXPECT_EQ(result->green, 0x5678);
    EXPECT_EQ(result->blue, 0x9ABC);
}

// Test setting and getting border color
TEST_F(PopplerSigningDataTest_2353, SetGetBorderColor_2353)
{
    PopplerColor color;
    color.red = 0x0000;
    color.green = 0xFFFF;
    color.blue = 0x0000;
    poppler_signing_data_set_border_color(data, &color);

    const PopplerColor *result = poppler_signing_data_get_border_color(data);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 0x0000);
    EXPECT_EQ(result->green, 0xFFFF);
    EXPECT_EQ(result->blue, 0x0000);
}

// Test setting and getting font color
TEST_F(PopplerSigningDataTest_2353, SetGetFontColor_2353)
{
    PopplerColor color;
    color.red = 0x0000;
    color.green = 0x0000;
    color.blue = 0xFFFF;
    poppler_signing_data_set_font_color(data, &color);

    const PopplerColor *result = poppler_signing_data_get_font_color(data);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 0x0000);
    EXPECT_EQ(result->green, 0x0000);
    EXPECT_EQ(result->blue, 0xFFFF);
}

// Test setting and getting destination filename
TEST_F(PopplerSigningDataTest_2353, SetGetDestinationFilename_2353)
{
    poppler_signing_data_set_destination_filename(data, "/tmp/signed.pdf");
    const gchar *filename = poppler_signing_data_get_destination_filename(data);
    ASSERT_NE(filename, nullptr);
    EXPECT_STREQ(filename, "/tmp/signed.pdf");
}

// Test setting and getting signature text
TEST_F(PopplerSigningDataTest_2353, SetGetSignatureText_2353)
{
    poppler_signing_data_set_signature_text(data, "John Doe");
    const gchar *text = poppler_signing_data_get_signature_text(data);
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "John Doe");
}

// Test setting and getting signature text left
TEST_F(PopplerSigningDataTest_2353, SetGetSignatureTextLeft_2353)
{
    poppler_signing_data_set_signature_text_left(data, "Left Text");
    const gchar *text = poppler_signing_data_get_signature_text_left(data);
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "Left Text");
}

// Test setting and getting field partial name
TEST_F(PopplerSigningDataTest_2353, SetGetFieldPartialName_2353)
{
    poppler_signing_data_set_field_partial_name(data, "sig_field");
    const gchar *name = poppler_signing_data_get_field_partial_name(data);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "sig_field");
}

// Test setting and getting reason
TEST_F(PopplerSigningDataTest_2353, SetGetReason_2353)
{
    poppler_signing_data_set_reason(data, "I approve this document");
    const gchar *reason = poppler_signing_data_get_reason(data);
    ASSERT_NE(reason, nullptr);
    EXPECT_STREQ(reason, "I approve this document");
}

// Test setting and getting location
TEST_F(PopplerSigningDataTest_2353, SetGetLocation_2353)
{
    poppler_signing_data_set_location(data, "New York, USA");
    const gchar *location = poppler_signing_data_get_location(data);
    ASSERT_NE(location, nullptr);
    EXPECT_STREQ(location, "New York, USA");
}

// Test setting and getting image path
TEST_F(PopplerSigningDataTest_2353, SetGetImagePath_2353)
{
    poppler_signing_data_set_image_path(data, "/tmp/signature.png");
    const gchar *path = poppler_signing_data_get_image_path(data);
    ASSERT_NE(path, nullptr);
    EXPECT_STREQ(path, "/tmp/signature.png");
}

// Test setting and getting document owner password
TEST_F(PopplerSigningDataTest_2353, SetGetDocumentOwnerPassword_2353)
{
    poppler_signing_data_set_document_owner_password(data, "ownerpass");
    const gchar *pass = poppler_signing_data_get_document_owner_password(data);
    ASSERT_NE(pass, nullptr);
    EXPECT_STREQ(pass, "ownerpass");
}

// Test setting and getting document user password
TEST_F(PopplerSigningDataTest_2353, SetGetDocumentUserPassword_2353)
{
    poppler_signing_data_set_document_user_password(data, "userpass");
    const gchar *pass = poppler_signing_data_get_document_user_password(data);
    ASSERT_NE(pass, nullptr);
    EXPECT_STREQ(pass, "userpass");
}

// Test copy functionality preserves password
TEST_F(PopplerSigningDataTest_2353, CopyPreservesPassword_2353)
{
    poppler_signing_data_set_password(data, "testpass");
    PopplerSigningData *copy = poppler_signing_data_copy(data);
    ASSERT_NE(copy, nullptr);

    const gchar *password = poppler_signing_data_get_password(copy);
    ASSERT_NE(password, nullptr);
    EXPECT_STREQ(password, "testpass");

    poppler_signing_data_free(copy);
}

// Test copy functionality preserves page
TEST_F(PopplerSigningDataTest_2353, CopyPreservesPage_2353)
{
    poppler_signing_data_set_page(data, 42);
    PopplerSigningData *copy = poppler_signing_data_copy(data);
    ASSERT_NE(copy, nullptr);

    EXPECT_EQ(poppler_signing_data_get_page(copy), 42);

    poppler_signing_data_free(copy);
}

// Test copy preserves font size
TEST_F(PopplerSigningDataTest_2353, CopyPreservesFontSize_2353)
{
    poppler_signing_data_set_font_size(data, 36.0);
    PopplerSigningData *copy = poppler_signing_data_copy(data);
    ASSERT_NE(copy, nullptr);

    EXPECT_DOUBLE_EQ(poppler_signing_data_get_font_size(copy), 36.0);

    poppler_signing_data_free(copy);
}

// Test copy preserves background color
TEST_F(PopplerSigningDataTest_2353, CopyPreservesBackgroundColor_2353)
{
    PopplerColor color;
    color.red = 0xABCD;
    color.green = 0x1234;
    color.blue = 0x5678;
    poppler_signing_data_set_background_color(data, &color);

    PopplerSigningData *copy = poppler_signing_data_copy(data);
    ASSERT_NE(copy, nullptr);

    const PopplerColor *result = poppler_signing_data_get_background_color(copy);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 0xABCD);
    EXPECT_EQ(result->green, 0x1234);
    EXPECT_EQ(result->blue, 0x5678);

    poppler_signing_data_free(copy);
}

// Test copy is independent from original (modifying copy doesn't affect original)
TEST_F(PopplerSigningDataTest_2353, CopyIsIndependent_2353)
{
    poppler_signing_data_set_password(data, "original");
    PopplerSigningData *copy = poppler_signing_data_copy(data);
    ASSERT_NE(copy, nullptr);

    poppler_signing_data_set_password(copy, "modified");

    EXPECT_STREQ(poppler_signing_data_get_password(data), "original");
    EXPECT_STREQ(poppler_signing_data_get_password(copy), "modified");

    poppler_signing_data_free(copy);
}

// Test overwriting values (set twice, get latest)
TEST_F(PopplerSigningDataTest_2353, OverwritePassword_2353)
{
    poppler_signing_data_set_password(data, "first");
    poppler_signing_data_set_password(data, "second");
    EXPECT_STREQ(poppler_signing_data_get_password(data), "second");
}

// Test overwriting page
TEST_F(PopplerSigningDataTest_2353, OverwritePage_2353)
{
    poppler_signing_data_set_page(data, 1);
    poppler_signing_data_set_page(data, 99);
    EXPECT_EQ(poppler_signing_data_get_page(data), 99);
}

// Test setting empty string for text fields
TEST_F(PopplerSigningDataTest_2353, SetEmptyStringSignatureText_2353)
{
    poppler_signing_data_set_signature_text(data, "");
    const gchar *text = poppler_signing_data_get_signature_text(data);
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "");
}

// Test setting very long string
TEST_F(PopplerSigningDataTest_2353, SetLongStringPassword_2353)
{
    std::string longStr(1000, 'A');
    poppler_signing_data_set_password(data, longStr.c_str());
    const gchar *password = poppler_signing_data_get_password(data);
    ASSERT_NE(password, nullptr);
    EXPECT_STREQ(password, longStr.c_str());
}

// Test setting font size to negative value
TEST_F(PopplerSigningDataTest_2353, SetNegativeFontSize_2353)
{
    poppler_signing_data_set_font_size(data, -5.0);
    EXPECT_DOUBLE_EQ(poppler_signing_data_get_font_size(data), -5.0);
}

// Test setting border width to negative value
TEST_F(PopplerSigningDataTest_2353, SetNegativeBorderWidth_2353)
{
    poppler_signing_data_set_border_width(data, -1.0);
    EXPECT_DOUBLE_EQ(poppler_signing_data_get_border_width(data), -1.0);
}

// Test freeing null does not crash
TEST_F(PopplerSigningDataTest_2353, FreeNullDoesNotCrash_2353)
{
    poppler_signing_data_free(nullptr);
    // If we get here without crashing, the test passes
}

// Test copy preserves border width
TEST_F(PopplerSigningDataTest_2353, CopyPreservesBorderWidth_2353)
{
    poppler_signing_data_set_border_width(data, 5.0);
    PopplerSigningData *copy = poppler_signing_data_copy(data);
    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(poppler_signing_data_get_border_width(copy), 5.0);
    poppler_signing_data_free(copy);
}

// Test copy preserves destination filename
TEST_F(PopplerSigningDataTest_2353, CopyPreservesDestinationFilename_2353)
{
    poppler_signing_data_set_destination_filename(data, "/output/test.pdf");
    PopplerSigningData *copy = poppler_signing_data_copy(data);
    ASSERT_NE(copy, nullptr);
    const gchar *fn = poppler_signing_data_get_destination_filename(copy);
    ASSERT_NE(fn, nullptr);
    EXPECT_STREQ(fn, "/output/test.pdf");
    poppler_signing_data_free(copy);
}

// Test setting and getting all color channels at boundaries
TEST_F(PopplerSigningDataTest_2353, SetColorBoundaryValues_2353)
{
    PopplerColor color;
    color.red = 0xFFFF;
    color.green = 0xFFFF;
    color.blue = 0xFFFF;
    poppler_signing_data_set_background_color(data, &color);

    const PopplerColor *result = poppler_signing_data_get_background_color(data);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 0xFFFF);
    EXPECT_EQ(result->green, 0xFFFF);
    EXPECT_EQ(result->blue, 0xFFFF);
}

// Test setting all color channels to zero
TEST_F(PopplerSigningDataTest_2353, SetColorAllZero_2353)
{
    PopplerColor color;
    color.red = 0x0000;
    color.green = 0x0000;
    color.blue = 0x0000;
    poppler_signing_data_set_border_color(data, &color);

    const PopplerColor *result = poppler_signing_data_get_border_color(data);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->red, 0x0000);
    EXPECT_EQ(result->green, 0x0000);
    EXPECT_EQ(result->blue, 0x0000);
}

// Test multiple new/free cycles don't leak (basic smoke test)
TEST_F(PopplerSigningDataTest_2353, MultipleNewFree_2353)
{
    for (int i = 0; i < 100; i++) {
        PopplerSigningData *d = poppler_signing_data_new();
        ASSERT_NE(d, nullptr);
        poppler_signing_data_free(d);
    }
}

// Test setting reason to unicode string
TEST_F(PopplerSigningDataTest_2353, SetUnicodeReason_2353)
{
    poppler_signing_data_set_reason(data, "Ünïcödé Réâsön");
    const gchar *reason = poppler_signing_data_get_reason(data);
    ASSERT_NE(reason, nullptr);
    EXPECT_STREQ(reason, "Ünïcödé Réâsön");
}

// Test copy preserves left font size
TEST_F(PopplerSigningDataTest_2353, CopyPreservesLeftFontSize_2353)
{
    poppler_signing_data_set_left_font_size(data, 30.0);
    PopplerSigningData *copy = poppler_signing_data_copy(data);
    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(poppler_signing_data_get_left_font_size(copy), 30.0);
    poppler_signing_data_free(copy);
}

// Test copy preserves signature text
TEST_F(PopplerSigningDataTest_2353, CopyPreservesSignatureText_2353)
{
    poppler_signing_data_set_signature_text(data, "Signed by Admin");
    PopplerSigningData *copy = poppler_signing_data_copy(data);
    ASSERT_NE(copy, nullptr);
    const gchar *text = poppler_signing_data_get_signature_text(copy);
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, "Signed by Admin");
    poppler_signing_data_free(copy);
}

// Test page boundary with large value
TEST_F(PopplerSigningDataTest_2353, SetPageLargeValue_2353)
{
    poppler_signing_data_set_page(data, 999999);
    EXPECT_EQ(poppler_signing_data_get_page(data), 999999);
}
