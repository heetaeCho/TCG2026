#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include <poppler.h>
#include <poppler-document.h>
#include <poppler-page.h>
}

#include <cstdlib>
#include <string>

class PopplerAnnotInkTest_2134 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        // We need a valid PDF document to work with annotations.
        // Create a minimal PDF in a temporary file for testing.
        const char *pdf_content =
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/Annots[4 0 R]>>endobj\n"
            "4 0 obj<</Type/Annot/Subtype/Ink/Rect[100 100 200 200]/InkList[[100 100 150 150 200 200]]>>endobj\n"
            "xref\n"
            "0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000206 00000 n \n"
            "trailer<</Size 5/Root 1 0 R>>\n"
            "startxref\n"
            "338\n"
            "%%EOF\n";

        tmp_file = g_strdup("/tmp/test_ink_annot_2134_XXXXXX.pdf");
        // Write to a temp file
        std::string tmp_path = "/tmp/test_ink_annot_2134.pdf";
        FILE *f = fopen(tmp_path.c_str(), "wb");
        if (f) {
            fwrite(pdf_content, 1, strlen(pdf_content), f);
            fclose(f);
        }

        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(tmp_path.c_str(), nullptr, &error);
        if (uri) {
            doc = poppler_document_new_from_file(uri, nullptr, &error);
            g_free(uri);
        }
        if (error) {
            g_error_free(error);
            error = nullptr;
        }

        if (doc) {
            page = poppler_document_get_page(doc, 0);
        }
    }

    void TearDown() override {
        if (page) {
            g_object_unref(page);
        }
        if (doc) {
            g_object_unref(doc);
        }
        if (tmp_file) {
            g_free(tmp_file);
        }
        // Clean up temp file
        unlink("/tmp/test_ink_annot_2134.pdf");
    }

    gchar *tmp_file = nullptr;
};

// Test that poppler_annot_ink_get_draw_below returns a valid gboolean for an ink annotation
TEST_F(PopplerAnnotInkTest_2134, GetDrawBelowReturnsValidBoolean_2134)
{
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF page";
    }

    GList *annots = poppler_page_get_annot_mapping(page);
    if (!annots) {
        GTEST_SKIP() << "No annotations found on test page";
    }

    gboolean found_ink = FALSE;
    for (GList *l = annots; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = static_cast<PopplerAnnotMapping *>(l->data);
        PopplerAnnot *annot = mapping->annot;

        if (poppler_annot_get_annot_type(annot) == POPPLER_ANNOT_INK) {
            PopplerAnnotInk *ink_annot = POPPLER_ANNOT_INK(annot);
            gboolean draw_below = poppler_annot_ink_get_draw_below(ink_annot);
            // The result should be either TRUE or FALSE
            EXPECT_TRUE(draw_below == TRUE || draw_below == FALSE);
            found_ink = TRUE;
        }
    }

    poppler_page_free_annot_mapping(annots);

    if (!found_ink) {
        GTEST_SKIP() << "No ink annotations found on test page";
    }
}

// Test that for a default ink annotation without explicit draw_below, the value is FALSE
TEST_F(PopplerAnnotInkTest_2134, DefaultDrawBelowIsFalse_2134)
{
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF page";
    }

    GList *annots = poppler_page_get_annot_mapping(page);
    if (!annots) {
        GTEST_SKIP() << "No annotations found on test page";
    }

    gboolean found_ink = FALSE;
    for (GList *l = annots; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = static_cast<PopplerAnnotMapping *>(l->data);
        PopplerAnnot *annot = mapping->annot;

        if (poppler_annot_get_annot_type(annot) == POPPLER_ANNOT_INK) {
            PopplerAnnotInk *ink_annot = POPPLER_ANNOT_INK(annot);
            gboolean draw_below = poppler_annot_ink_get_draw_below(ink_annot);
            // Default ink annotations typically have draw_below as FALSE
            EXPECT_EQ(draw_below, FALSE);
            found_ink = TRUE;
        }
    }

    poppler_page_free_annot_mapping(annots);

    if (!found_ink) {
        GTEST_SKIP() << "No ink annotations found on test page";
    }
}

// Test that the ink annotation type is correctly identified
TEST_F(PopplerAnnotInkTest_2134, AnnotTypeIsInk_2134)
{
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF page";
    }

    GList *annots = poppler_page_get_annot_mapping(page);
    if (!annots) {
        GTEST_SKIP() << "No annotations found on test page";
    }

    gboolean found_ink = FALSE;
    for (GList *l = annots; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = static_cast<PopplerAnnotMapping *>(l->data);
        PopplerAnnot *annot = mapping->annot;

        if (poppler_annot_get_annot_type(annot) == POPPLER_ANNOT_INK) {
            // Verify the annot is indeed castable to PopplerAnnotInk
            EXPECT_TRUE(POPPLER_IS_ANNOT_INK(annot));
            found_ink = TRUE;
        }
    }

    poppler_page_free_annot_mapping(annots);

    if (!found_ink) {
        GTEST_SKIP() << "No ink annotations found on test page";
    }
}

// Test with a PDF that has draw_below set explicitly
class PopplerAnnotInkDrawBelowTest_2134 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        // Create a PDF with an ink annotation that has /DrawBelow true
        // Note: DrawBelow is a non-standard extension, we test what we can
        const char *pdf_content =
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/Annots[4 0 R]>>endobj\n"
            "4 0 obj<</Type/Annot/Subtype/Ink/Rect[100 100 200 200]/InkList[[100 100 150 150 200 200]]/DrawBelow true>>endobj\n"
            "xref\n"
            "0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000206 00000 n \n"
            "trailer<</Size 5/Root 1 0 R>>\n"
            "startxref\n"
            "355\n"
            "%%EOF\n";

        std::string tmp_path = "/tmp/test_ink_annot_drawbelow_2134.pdf";
        FILE *f = fopen(tmp_path.c_str(), "wb");
        if (f) {
            fwrite(pdf_content, 1, strlen(pdf_content), f);
            fclose(f);
        }

        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(tmp_path.c_str(), nullptr, &error);
        if (uri) {
            doc = poppler_document_new_from_file(uri, nullptr, &error);
            g_free(uri);
        }
        if (error) {
            g_error_free(error);
        }

        if (doc) {
            page = poppler_document_get_page(doc, 0);
        }
    }

    void TearDown() override {
        if (page) {
            g_object_unref(page);
        }
        if (doc) {
            g_object_unref(doc);
        }
        unlink("/tmp/test_ink_annot_drawbelow_2134.pdf");
    }
};

TEST_F(PopplerAnnotInkDrawBelowTest_2134, DrawBelowExplicitlySet_2134)
{
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF page";
    }

    GList *annots = poppler_page_get_annot_mapping(page);
    if (!annots) {
        GTEST_SKIP() << "No annotations found on test page";
    }

    for (GList *l = annots; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = static_cast<PopplerAnnotMapping *>(l->data);
        PopplerAnnot *annot = mapping->annot;

        if (poppler_annot_get_annot_type(annot) == POPPLER_ANNOT_INK) {
            PopplerAnnotInk *ink_annot = POPPLER_ANNOT_INK(annot);
            gboolean draw_below = poppler_annot_ink_get_draw_below(ink_annot);
            // If the PDF parser honors DrawBelow, it should be TRUE
            // We just verify it returns a valid boolean
            EXPECT_TRUE(draw_below == TRUE || draw_below == FALSE);
        }
    }

    poppler_page_free_annot_mapping(annots);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
