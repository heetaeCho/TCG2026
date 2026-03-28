#include <glib.h>
#include <glib-object.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>

class PopplerAnnotInkTest_2133 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;
    gchar *tmp_path = nullptr;
    gchar *uri = nullptr;

    void SetUp() override {
        // Create a minimal PDF in memory to get a valid document/page context
        const char *pdf_content =
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n190\n%%EOF\n";

        // Write to temp file
        tmp_path = g_strdup("/tmp/test_poppler_annot_ink_2133.pdf");
        FILE *f = fopen(tmp_path, "wb");
        if (f) {
            fwrite(pdf_content, 1, strlen(pdf_content), f);
            fclose(f);
        }

        uri = g_strdup_printf("file://%s", tmp_path);
        GError *error = nullptr;
        doc = poppler_document_new_from_file(uri, nullptr, &error);
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
        if (tmp_path) {
            g_remove(tmp_path);
            g_free(tmp_path);
        }
        if (uri) {
            g_free(uri);
        }
    }

    PopplerAnnotInk *createInkAnnot() {
        if (!page) {
            return nullptr;
        }
        PopplerRectangle rect;
        rect.x1 = 10.0;
        rect.y1 = 10.0;
        rect.x2 = 100.0;
        rect.y2 = 100.0;

        // Create an ink annotation
        // Build a simple ink list with one path
        GArray *coords = g_array_new(FALSE, FALSE, sizeof(PopplerPoint));
        PopplerPoint p1 = {20.0, 20.0};
        PopplerPoint p2 = {80.0, 80.0};
        g_array_append_val(coords, p1);
        g_array_append_val(coords, p2);

        GList *ink_list = nullptr;
        ink_list = g_list_append(ink_list, coords);

        PopplerAnnotInk *annot = (PopplerAnnotInk *)poppler_annot_ink_new(doc, &rect, ink_list);

        g_array_free(coords, TRUE);
        g_list_free(ink_list);

        return annot;
    }
};

TEST_F(PopplerAnnotInkTest_2133, SetDrawBelowTrue_2133) {
    PopplerAnnotInk *annot = createInkAnnot();
    ASSERT_NE(annot, nullptr);

    // Should not crash when setting draw_below to TRUE
    poppler_annot_ink_set_draw_below(annot, TRUE);

    g_object_unref(annot);
}

TEST_F(PopplerAnnotInkTest_2133, SetDrawBelowFalse_2133) {
    PopplerAnnotInk *annot = createInkAnnot();
    ASSERT_NE(annot, nullptr);

    // Should not crash when setting draw_below to FALSE
    poppler_annot_ink_set_draw_below(annot, FALSE);

    g_object_unref(annot);
}

TEST_F(PopplerAnnotInkTest_2133, SetDrawBelowToggle_2133) {
    PopplerAnnotInk *annot = createInkAnnot();
    ASSERT_NE(annot, nullptr);

    // Toggle between TRUE and FALSE multiple times
    poppler_annot_ink_set_draw_below(annot, TRUE);
    poppler_annot_ink_set_draw_below(annot, FALSE);
    poppler_annot_ink_set_draw_below(annot, TRUE);

    g_object_unref(annot);
}

TEST_F(PopplerAnnotInkTest_2133, SetDrawBelowMultipleTimesSameValue_2133) {
    PopplerAnnotInk *annot = createInkAnnot();
    ASSERT_NE(annot, nullptr);

    // Setting the same value multiple times should be idempotent
    poppler_annot_ink_set_draw_below(annot, TRUE);
    poppler_annot_ink_set_draw_below(annot, TRUE);
    poppler_annot_ink_set_draw_below(annot, TRUE);

    g_object_unref(annot);
}

TEST_F(PopplerAnnotInkTest_2133, SetDrawBelowNonBooleanValue_2133) {
    PopplerAnnotInk *annot = createInkAnnot();
    ASSERT_NE(annot, nullptr);

    // In GLib, any non-zero gboolean is considered TRUE
    // Passing a non-standard truthy value should still work
    poppler_annot_ink_set_draw_below(annot, 42);

    g_object_unref(annot);
}
