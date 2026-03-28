#include <glib.h>
#include <poppler.h>
#include <poppler-document.h>
#include <poppler-page.h>
#include <glib-object.h>
#include <cstdio>
#include <cstring>
#include <gtest/gtest.h>

// Helper to create a minimal PDF in memory with a text annotation
static PopplerDocument *create_test_document_with_text_annot()
{
    // Create a minimal PDF document from a string
    const char *pdf_data =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
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
    gsize len = strlen(pdf_data);
    PopplerDocument *doc = poppler_document_new_from_data((char*)pdf_data, (int)len, nullptr, &error);
    if (error) {
        g_error_free(error);
        return nullptr;
    }
    return doc;
}

class PopplerAnnotTextSetIsOpenTest_2090 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override
    {
        doc = create_test_document_with_text_annot();
        if (doc) {
            page = poppler_document_get_page(doc, 0);
        }
    }

    void TearDown() override
    {
        if (page) {
            g_object_unref(page);
        }
        if (doc) {
            g_object_unref(doc);
        }
    }

    PopplerAnnot *add_text_annot()
    {
        if (!page) return nullptr;
        PopplerRectangle rect;
        rect.x1 = 10;
        rect.y1 = 10;
        rect.x2 = 50;
        rect.y2 = 50;
        PopplerAnnot *annot = poppler_annot_text_new(doc, &rect);
        if (annot) {
            poppler_page_add_annot(page, annot);
        }
        return annot;
    }
};

TEST_F(PopplerAnnotTextSetIsOpenTest_2090, SetIsOpenTrue_2090)
{
    PopplerAnnot *annot = add_text_annot();
    ASSERT_NE(annot, nullptr);

    PopplerAnnotText *text_annot = POPPLER_ANNOT_TEXT(annot);
    ASSERT_NE(text_annot, nullptr);

    poppler_annot_text_set_is_open(text_annot, TRUE);
    gboolean result = poppler_annot_text_get_is_open(text_annot);
    EXPECT_TRUE(result);

    g_object_unref(annot);
}

TEST_F(PopplerAnnotTextSetIsOpenTest_2090, SetIsOpenFalse_2090)
{
    PopplerAnnot *annot = add_text_annot();
    ASSERT_NE(annot, nullptr);

    PopplerAnnotText *text_annot = POPPLER_ANNOT_TEXT(annot);
    ASSERT_NE(text_annot, nullptr);

    // First set to open, then close
    poppler_annot_text_set_is_open(text_annot, TRUE);
    poppler_annot_text_set_is_open(text_annot, FALSE);
    gboolean result = poppler_annot_text_get_is_open(text_annot);
    EXPECT_FALSE(result);

    g_object_unref(annot);
}

TEST_F(PopplerAnnotTextSetIsOpenTest_2090, ToggleIsOpen_2090)
{
    PopplerAnnot *annot = add_text_annot();
    ASSERT_NE(annot, nullptr);

    PopplerAnnotText *text_annot = POPPLER_ANNOT_TEXT(annot);
    ASSERT_NE(text_annot, nullptr);

    poppler_annot_text_set_is_open(text_annot, TRUE);
    EXPECT_TRUE(poppler_annot_text_get_is_open(text_annot));

    poppler_annot_text_set_is_open(text_annot, FALSE);
    EXPECT_FALSE(poppler_annot_text_get_is_open(text_annot));

    poppler_annot_text_set_is_open(text_annot, TRUE);
    EXPECT_TRUE(poppler_annot_text_get_is_open(text_annot));

    g_object_unref(annot);
}

TEST_F(PopplerAnnotTextSetIsOpenTest_2090, SetIsOpenWithNullAnnotDoesNotCrash_2090)
{
    // Passing NULL should be handled by g_return_if_fail and not crash
    poppler_annot_text_set_is_open(nullptr, TRUE);
    poppler_annot_text_set_is_open(nullptr, FALSE);
    // If we get here without crashing, the guard worked
    SUCCEED();
}

TEST_F(PopplerAnnotTextSetIsOpenTest_2090, DefaultIsOpenState_2090)
{
    PopplerAnnot *annot = add_text_annot();
    ASSERT_NE(annot, nullptr);

    PopplerAnnotText *text_annot = POPPLER_ANNOT_TEXT(annot);
    ASSERT_NE(text_annot, nullptr);

    // A newly created text annotation should have a defined is_open state
    gboolean result = poppler_annot_text_get_is_open(text_annot);
    // Default is typically FALSE for a new annotation
    EXPECT_FALSE(result);

    g_object_unref(annot);
}

TEST_F(PopplerAnnotTextSetIsOpenTest_2090, SetIsOpenMultipleTimesSameValue_2090)
{
    PopplerAnnot *annot = add_text_annot();
    ASSERT_NE(annot, nullptr);

    PopplerAnnotText *text_annot = POPPLER_ANNOT_TEXT(annot);
    ASSERT_NE(text_annot, nullptr);

    // Setting the same value multiple times should be idempotent
    poppler_annot_text_set_is_open(text_annot, TRUE);
    poppler_annot_text_set_is_open(text_annot, TRUE);
    poppler_annot_text_set_is_open(text_annot, TRUE);
    EXPECT_TRUE(poppler_annot_text_get_is_open(text_annot));

    poppler_annot_text_set_is_open(text_annot, FALSE);
    poppler_annot_text_set_is_open(text_annot, FALSE);
    poppler_annot_text_set_is_open(text_annot, FALSE);
    EXPECT_FALSE(poppler_annot_text_get_is_open(text_annot));

    g_object_unref(annot);
}

TEST_F(PopplerAnnotTextSetIsOpenTest_2090, SetIsOpenWithNonZeroTrueValue_2090)
{
    PopplerAnnot *annot = add_text_annot();
    ASSERT_NE(annot, nullptr);

    PopplerAnnotText *text_annot = POPPLER_ANNOT_TEXT(annot);
    ASSERT_NE(text_annot, nullptr);

    // In GLib, any non-zero value is TRUE
    poppler_annot_text_set_is_open(text_annot, 42);
    gboolean result = poppler_annot_text_get_is_open(text_annot);
    EXPECT_TRUE(result);

    g_object_unref(annot);
}
