#include <glib.h>
#include <poppler.h>
#include <poppler-document.h>
#include <poppler-page.h>
#include <gtest/gtest.h>
#include <cstring>
#include <cstdio>
#include <string>

// Helper to create a minimal PDF in memory with a text annotation
static PopplerDocument *create_pdf_with_text_annot()
{
    // Create a minimal PDF document from a string
    // We'll use poppler_document_new_from_data or from_file
    // For simplicity, create a temp file with a basic PDF
    const char *pdf_content =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(pdf_content, strlen(pdf_content));
    // Use GInputStream
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
    // Try creating from bytes
    PopplerDocument *doc = poppler_document_new_from_stream(stream, -1, nullptr, &error);
    if (!doc && error) {
        g_error_free(error);
        error = nullptr;
    }
    g_object_unref(stream);
    g_bytes_unref(bytes);
    return doc;
}

class PopplerAnnotTextSetIconTest_2092 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;
    PopplerAnnot *annot = nullptr;

    void SetUp() override
    {
        doc = create_pdf_with_text_annot();
        if (!doc) {
            GTEST_SKIP() << "Could not create test PDF document";
            return;
        }
        page = poppler_document_get_page(doc, 0);
        if (!page) {
            GTEST_SKIP() << "Could not get page from test PDF";
            return;
        }

        // Create a text annotation on the page
        PopplerRectangle rect = { 10.0, 10.0, 50.0, 50.0 };
        annot = poppler_annot_text_new(doc, &rect);
        if (!annot) {
            GTEST_SKIP() << "Could not create text annotation";
            return;
        }
    }

    void TearDown() override
    {
        if (annot)
            g_object_unref(annot);
        if (page)
            g_object_unref(page);
        if (doc)
            g_object_unref(doc);
    }
};

TEST_F(PopplerAnnotTextSetIconTest_2092, SetIconNormalString_2092)
{
    if (!annot) GTEST_SKIP();

    PopplerAnnotText *text_annot = POPPLER_ANNOT_TEXT(annot);
    poppler_annot_text_set_icon(text_annot, "Note");

    gchar *icon = poppler_annot_text_get_icon(text_annot);
    ASSERT_NE(icon, nullptr);
    EXPECT_STREQ(icon, "Note");
    g_free(icon);
}

TEST_F(PopplerAnnotTextSetIconTest_2092, SetIconComment_2092)
{
    if (!annot) GTEST_SKIP();

    PopplerAnnotText *text_annot = POPPLER_ANNOT_TEXT(annot);
    poppler_annot_text_set_icon(text_annot, "Comment");

    gchar *icon = poppler_annot_text_get_icon(text_annot);
    ASSERT_NE(icon, nullptr);
    EXPECT_STREQ(icon, "Comment");
    g_free(icon);
}

TEST_F(PopplerAnnotTextSetIconTest_2092, SetIconHelp_2092)
{
    if (!annot) GTEST_SKIP();

    PopplerAnnotText *text_annot = POPPLER_ANNOT_TEXT(annot);
    poppler_annot_text_set_icon(text_annot, "Help");

    gchar *icon = poppler_annot_text_get_icon(text_annot);
    ASSERT_NE(icon, nullptr);
    EXPECT_STREQ(icon, "Help");
    g_free(icon);
}

TEST_F(PopplerAnnotTextSetIconTest_2092, SetIconNullSetsEmpty_2092)
{
    if (!annot) GTEST_SKIP();

    PopplerAnnotText *text_annot = POPPLER_ANNOT_TEXT(annot);
    // First set a known icon
    poppler_annot_text_set_icon(text_annot, "Note");
    // Now set NULL - should result in empty string
    poppler_annot_text_set_icon(text_annot, nullptr);

    gchar *icon = poppler_annot_text_get_icon(text_annot);
    // NULL icon should translate to empty string internally
    if (icon) {
        EXPECT_STREQ(icon, "");
        g_free(icon);
    }
    // It's also acceptable if icon is NULL
}

TEST_F(PopplerAnnotTextSetIconTest_2092, SetIconEmptyString_2092)
{
    if (!annot) GTEST_SKIP();

    PopplerAnnotText *text_annot = POPPLER_ANNOT_TEXT(annot);
    poppler_annot_text_set_icon(text_annot, "");

    gchar *icon = poppler_annot_text_get_icon(text_annot);
    if (icon) {
        EXPECT_STREQ(icon, "");
        g_free(icon);
    }
}

TEST_F(PopplerAnnotTextSetIconTest_2092, SetIconOverwritesPrevious_2092)
{
    if (!annot) GTEST_SKIP();

    PopplerAnnotText *text_annot = POPPLER_ANNOT_TEXT(annot);
    poppler_annot_text_set_icon(text_annot, "Note");

    gchar *icon1 = poppler_annot_text_get_icon(text_annot);
    ASSERT_NE(icon1, nullptr);
    EXPECT_STREQ(icon1, "Note");
    g_free(icon1);

    poppler_annot_text_set_icon(text_annot, "Key");

    gchar *icon2 = poppler_annot_text_get_icon(text_annot);
    ASSERT_NE(icon2, nullptr);
    EXPECT_STREQ(icon2, "Key");
    g_free(icon2);
}

TEST_F(PopplerAnnotTextSetIconTest_2092, SetIconArbitraryString_2092)
{
    if (!annot) GTEST_SKIP();

    PopplerAnnotText *text_annot = POPPLER_ANNOT_TEXT(annot);
    poppler_annot_text_set_icon(text_annot, "CustomIconName");

    gchar *icon = poppler_annot_text_get_icon(text_annot);
    ASSERT_NE(icon, nullptr);
    EXPECT_STREQ(icon, "CustomIconName");
    g_free(icon);
}

TEST_F(PopplerAnnotTextSetIconTest_2092, SetIconMultipleTimes_2092)
{
    if (!annot) GTEST_SKIP();

    PopplerAnnotText *text_annot = POPPLER_ANNOT_TEXT(annot);

    const char *icons[] = {"Note", "Comment", "Key", "Help", "NewParagraph", "Paragraph", "Insert"};
    for (const char *ic : icons) {
        poppler_annot_text_set_icon(text_annot, ic);
        gchar *retrieved = poppler_annot_text_get_icon(text_annot);
        ASSERT_NE(retrieved, nullptr);
        EXPECT_STREQ(retrieved, ic);
        g_free(retrieved);
    }
}

TEST_F(PopplerAnnotTextSetIconTest_2092, SetIconWithSpecialCharacters_2092)
{
    if (!annot) GTEST_SKIP();

    PopplerAnnotText *text_annot = POPPLER_ANNOT_TEXT(annot);
    poppler_annot_text_set_icon(text_annot, "Icon-With-Dashes_And_Underscores");

    gchar *icon = poppler_annot_text_get_icon(text_annot);
    ASSERT_NE(icon, nullptr);
    EXPECT_STREQ(icon, "Icon-With-Dashes_And_Underscores");
    g_free(icon);
}

// Test that passing a non-PopplerAnnotText doesn't crash (g_return_if_fail guard)
// This is hard to test safely without causing assertion failures, so we skip direct invalid pointer tests.
// The g_return_if_fail macro will log a warning and return without doing anything.

TEST_F(PopplerAnnotTextSetIconTest_2092, SetIconNullAnnotDoesNotCrash_2092)
{
    // g_return_if_fail should handle NULL gracefully (just returns)
    // We need to suppress the GLib warning
    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_TEXT*");
    poppler_annot_text_set_icon(nullptr, "Note");
    g_test_assert_expected_messages();
}
