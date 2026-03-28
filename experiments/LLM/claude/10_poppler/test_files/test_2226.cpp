#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary poppler glib headers
extern "C" {
#include <poppler.h>
}

#include <string>
#include <memory>

class PopplerFontsIterIsEmbeddedTest_2226 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test with a real PDF document that has embedded fonts
TEST_F(PopplerFontsIterIsEmbeddedTest_2226, ReturnsValidBooleanForEmbeddedCheck_2226)
{
    // Create a minimal PDF in memory with a font
    // We test through the public poppler glib API
    GError *error = nullptr;

    // Try to create a simple document from data
    // A minimal PDF with an embedded font
    const char *minimal_pdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<</Font<</F1 4 0 R>>>>>>endobj\n"
        "4 0 obj<</Type/Font/Subtype/Type1/BaseFont/Helvetica>>endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000243 00000 n \n"
        "trailer<</Size 5/Root 1 0 R>>\n"
        "startxref\n"
        "316\n"
        "%%EOF\n";

    gsize len = strlen(minimal_pdf);
    PopplerDocument *doc = poppler_document_new_from_data(minimal_pdf, len, nullptr, &error);

    if (doc == nullptr) {
        // If we can't create the doc from this minimal PDF, skip
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create minimal PDF document for testing";
    }

    PopplerFontInfo *font_info = poppler_font_info_new(doc);
    ASSERT_NE(font_info, nullptr);

    PopplerFontsIter *iter = nullptr;
    gboolean has_more = TRUE;

    // Scan fonts from the document
    while (has_more) {
        has_more = poppler_font_info_scan(font_info, 1, &iter);
        if (iter != nullptr) {
            break;
        }
    }

    if (iter != nullptr) {
        // Test that is_embedded returns a valid gboolean (TRUE or FALSE)
        gboolean is_embedded = poppler_fonts_iter_is_embedded(iter);
        EXPECT_TRUE(is_embedded == TRUE || is_embedded == FALSE);

        // For Helvetica (Type1 base font, not embedded), expect FALSE
        EXPECT_EQ(is_embedded, FALSE);

        poppler_fonts_iter_free(iter);
    }

    g_object_unref(font_info);
    g_object_unref(doc);
}

// Test that NULL iterator is handled (if the API documents this behavior)
// Note: This may crash if the API doesn't handle NULL - marking as death test
TEST_F(PopplerFontsIterIsEmbeddedTest_2226, NullIteratorBehavior_2226)
{
    // Passing NULL to poppler_fonts_iter_is_embedded may cause a crash
    // We document this as expected behavior
    EXPECT_DEATH_IF_SUPPORTED(
        poppler_fonts_iter_is_embedded(nullptr),
        ""
    );
}

// Test with a copy of the iterator
TEST_F(PopplerFontsIterIsEmbeddedTest_2226, CopiedIteratorReturnsSameResult_2226)
{
    GError *error = nullptr;

    const char *minimal_pdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<</Font<</F1 4 0 R>>>>>>endobj\n"
        "4 0 obj<</Type/Font/Subtype/Type1/BaseFont/Helvetica>>endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000243 00000 n \n"
        "trailer<</Size 5/Root 1 0 R>>\n"
        "startxref\n"
        "316\n"
        "%%EOF\n";

    gsize len = strlen(minimal_pdf);
    PopplerDocument *doc = poppler_document_new_from_data(minimal_pdf, len, nullptr, &error);

    if (doc == nullptr) {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create minimal PDF document for testing";
    }

    PopplerFontInfo *font_info = poppler_font_info_new(doc);
    ASSERT_NE(font_info, nullptr);

    PopplerFontsIter *iter = nullptr;
    gboolean has_more = TRUE;

    while (has_more) {
        has_more = poppler_font_info_scan(font_info, 1, &iter);
        if (iter != nullptr) {
            break;
        }
    }

    if (iter != nullptr) {
        PopplerFontsIter *iter_copy = poppler_fonts_iter_copy(iter);
        ASSERT_NE(iter_copy, nullptr);

        gboolean orig_embedded = poppler_fonts_iter_is_embedded(iter);
        gboolean copy_embedded = poppler_fonts_iter_is_embedded(iter_copy);

        EXPECT_EQ(orig_embedded, copy_embedded);

        poppler_fonts_iter_free(iter_copy);
        poppler_fonts_iter_free(iter);
    }

    g_object_unref(font_info);
    g_object_unref(doc);
}

// Test iterating through multiple fonts and checking embedded status
TEST_F(PopplerFontsIterIsEmbeddedTest_2226, AllFontsHaveValidEmbeddedStatus_2226)
{
    GError *error = nullptr;

    // PDF with multiple fonts
    const char *minimal_pdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<</Font<</F1 4 0 R/F2 5 0 R>>>>>>endobj\n"
        "4 0 obj<</Type/Font/Subtype/Type1/BaseFont/Helvetica>>endobj\n"
        "5 0 obj<</Type/Font/Subtype/Type1/BaseFont/Times-Roman>>endobj\n"
        "xref\n"
        "0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000266 00000 n \n"
        "0000000339 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\n"
        "startxref\n"
        "415\n"
        "%%EOF\n";

    gsize len = strlen(minimal_pdf);
    PopplerDocument *doc = poppler_document_new_from_data(minimal_pdf, len, nullptr, &error);

    if (doc == nullptr) {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create minimal PDF document for testing";
    }

    PopplerFontInfo *font_info = poppler_font_info_new(doc);
    ASSERT_NE(font_info, nullptr);

    PopplerFontsIter *iter = nullptr;
    gboolean has_more = TRUE;
    int total_pages = poppler_document_get_n_pages(doc);

    while (has_more) {
        has_more = poppler_font_info_scan(font_info, total_pages, &iter);
        if (iter != nullptr) {
            break;
        }
    }

    if (iter != nullptr) {
        int font_count = 0;
        do {
            gboolean is_embedded = poppler_fonts_iter_is_embedded(iter);
            // Verify it returns a valid boolean
            EXPECT_TRUE(is_embedded == TRUE || is_embedded == FALSE)
                << "Font at index " << font_count << " returned invalid boolean value";
            font_count++;
        } while (poppler_fonts_iter_next(iter));

        EXPECT_GT(font_count, 0);
        poppler_fonts_iter_free(iter);
    }

    g_object_unref(font_info);
    g_object_unref(doc);
}
