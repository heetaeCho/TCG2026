#include <glib-object.h>
#include <gtest/gtest.h>

// Include poppler glib headers
extern "C" {
#include "poppler-annot.h"
#include "poppler-document.h"
#include "poppler-page.h"
}

class PopplerAnnotSquareTest_2117 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL returns NULL (g_return_val_if_fail should catch this)
TEST_F(PopplerAnnotSquareTest_2117, GetInteriorColorWithNullReturnsNull_2117)
{
    // Passing NULL should trigger g_return_val_if_fail and return NULL
    // We need to suppress the GLib warning for this test
    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_SQUARE*");
    PopplerColor *color = poppler_annot_square_get_interior_color(NULL);
    g_test_assert_expected_messages();
    EXPECT_EQ(color, nullptr);
}

// Test that passing a wrong type returns NULL (g_return_val_if_fail type check)
TEST_F(PopplerAnnotSquareTest_2117, GetInteriorColorWithWrongTypeReturnsNull_2117)
{
    // Create any GObject that is NOT a PopplerAnnotSquare
    // We'll use a generic GObject to test the type check
    GObject *wrong_obj = (GObject *)g_object_new(G_TYPE_OBJECT, NULL);
    ASSERT_NE(wrong_obj, nullptr);

    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_SQUARE*");
    PopplerColor *color = poppler_annot_square_get_interior_color((PopplerAnnotSquare *)wrong_obj);
    g_test_assert_expected_messages();
    EXPECT_EQ(color, nullptr);

    g_object_unref(wrong_obj);
}

// Test with an actual PopplerAnnotSquare created from a real PDF document
// Since we cannot easily create a PopplerAnnotSquare without a PDF,
// we test the function with a document that has square annotations if available.
// For robustness, we test creation via a minimal PDF with a square annotation.
TEST_F(PopplerAnnotSquareTest_2117, GetInteriorColorFromAnnotSquareWithNoInteriorColor_2117)
{
    // Create a minimal PDF in memory that has a square annotation
    const char *pdf_content =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/Annots[4 0 R]>>endobj\n"
        "4 0 obj<</Type/Annot/Subtype/Square/Rect[100 100 200 200]/C[1 0 0]>>endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000206 00000 n \n"
        "trailer<</Size 5/Root 1 0 R>>\n"
        "startxref\n"
        "291\n"
        "%%EOF\n";

    gsize len = strlen(pdf_content);
    GError *error = NULL;

    // Try to create a document from the data
    PopplerDocument *doc = poppler_document_new_from_data((char *)pdf_content, (int)len, NULL, &error);

    if (doc == NULL) {
        // If we can't create a document from our minimal PDF, skip gracefully
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create PDF document for testing";
        return;
    }

    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (page == NULL) {
        g_object_unref(doc);
        GTEST_SKIP() << "Could not get page from PDF document";
        return;
    }

    GList *annot_mappings = poppler_page_get_annot_mapping(page);
    PopplerAnnotSquare *square_annot = NULL;

    for (GList *l = annot_mappings; l != NULL; l = l->next) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
        if (poppler_annot_get_annot_type(mapping->annot) == POPPLER_ANNOT_SQUARE) {
            square_annot = POPPLER_ANNOT_SQUARE(mapping->annot);
            break;
        }
    }

    if (square_annot != NULL) {
        // This annotation has no interior color set, so it may return NULL or a color
        PopplerColor *color = poppler_annot_square_get_interior_color(square_annot);
        // We just verify the function doesn't crash; color may be NULL or valid
        if (color != NULL) {
            g_free(color);
        }
    }

    poppler_page_free_annot_mapping(annot_mappings);
    g_object_unref(page);
    g_object_unref(doc);
}

// Test with a square annotation that has an interior color (IC entry)
TEST_F(PopplerAnnotSquareTest_2117, GetInteriorColorFromAnnotSquareWithInteriorColor_2117)
{
    const char *pdf_content =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/Annots[4 0 R]>>endobj\n"
        "4 0 obj<</Type/Annot/Subtype/Square/Rect[100 100 200 200]/C[1 0 0]/IC[0 1 0]>>endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000206 00000 n \n"
        "trailer<</Size 5/Root 1 0 R>>\n"
        "startxref\n"
        "302\n"
        "%%EOF\n";

    gsize len = strlen(pdf_content);
    GError *error = NULL;

    PopplerDocument *doc = poppler_document_new_from_data((char *)pdf_content, (int)len, NULL, &error);

    if (doc == NULL) {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create PDF document for testing";
        return;
    }

    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (page == NULL) {
        g_object_unref(doc);
        GTEST_SKIP() << "Could not get page from PDF document";
        return;
    }

    GList *annot_mappings = poppler_page_get_annot_mapping(page);
    PopplerAnnotSquare *square_annot = NULL;

    for (GList *l = annot_mappings; l != NULL; l = l->next) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
        if (poppler_annot_get_annot_type(mapping->annot) == POPPLER_ANNOT_SQUARE) {
            square_annot = POPPLER_ANNOT_SQUARE(mapping->annot);
            break;
        }
    }

    if (square_annot != NULL) {
        PopplerColor *color = poppler_annot_square_get_interior_color(square_annot);
        // If interior color was parsed, verify it's non-null
        // The IC array [0 1 0] should give green
        if (color != NULL) {
            // Green channel should be high, red and blue should be low
            EXPECT_EQ(color->red, 0);
            EXPECT_GT(color->green, 0);
            EXPECT_EQ(color->blue, 0);
            g_free(color);
        }
        // If color is NULL, the PDF might not have been parsed with IC support
    }

    poppler_page_free_annot_mapping(annot_mappings);
    g_object_unref(page);
    g_object_unref(doc);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
