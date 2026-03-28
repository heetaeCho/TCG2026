#include <glib.h>
#include <poppler.h>
#include <poppler-document.h>
#include <poppler-page.h>
#include <gtest/gtest.h>
#include <cstring>
#include <cstdio>

// We need a helper to create a PDF with a line annotation for testing
// Since we can't easily create PopplerAnnotLine objects without a document,
// we'll create a minimal PDF in memory.

class PopplerAnnotLineSetVerticesTest_2112 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;
    PopplerAnnot *annot = nullptr;

    void SetUp() override {
        // Create a minimal PDF file in a temp location
        const char *pdf_content =
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/Annots[4 0 R]>>endobj\n"
            "4 0 obj<</Type/Annot/Subtype/Line/Rect[100 100 300 300]/L[100 100 300 300]>>endobj\n"
            "xref\n0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000206 00000 n \n"
            "trailer<</Size 5/Root 1 0 R>>\n"
            "startxref\n313\n%%EOF\n";

        tmpfile_path = g_strdup("/tmp/test_annot_line_2112.pdf");
        FILE *f = fopen(tmpfile_path, "wb");
        if (f) {
            fwrite(pdf_content, 1, strlen(pdf_content), f);
            fclose(f);
        }

        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(tmpfile_path, nullptr, &error);
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

        // Try to get annotation from the page
        if (page) {
            GList *annot_mappings = poppler_page_get_annot_mapping(page);
            if (annot_mappings) {
                PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)annot_mappings->data;
                if (mapping && mapping->annot) {
                    annot = (PopplerAnnot *)g_object_ref(mapping->annot);
                }
                poppler_page_free_annot_mapping(annot_mappings);
            }
        }
    }

    void TearDown() override {
        if (annot)
            g_object_unref(annot);
        if (page)
            g_object_unref(page);
        if (doc)
            g_object_unref(doc);
        if (tmpfile_path) {
            unlink(tmpfile_path);
            g_free(tmpfile_path);
        }
    }

    gchar *tmpfile_path = nullptr;
};

TEST_F(PopplerAnnotLineSetVerticesTest_2112, NullAnnotDoesNotCrash_2112) {
    PopplerPoint start = {10.0, 20.0};
    PopplerPoint end = {30.0, 40.0};
    // Should not crash - g_return_if_fail handles null
    poppler_annot_line_set_vertices(nullptr, &start, &end);
}

TEST_F(PopplerAnnotLineSetVerticesTest_2112, NullStartDoesNotCrash_2112) {
    if (!annot || !POPPLER_IS_ANNOT_LINE(annot))
        GTEST_SKIP() << "No line annotation available";

    PopplerPoint end = {30.0, 40.0};
    poppler_annot_line_set_vertices(POPPLER_ANNOT_LINE(annot), nullptr, &end);
}

TEST_F(PopplerAnnotLineSetVerticesTest_2112, NullEndDoesNotCrash_2112) {
    if (!annot || !POPPLER_IS_ANNOT_LINE(annot))
        GTEST_SKIP() << "No line annotation available";

    PopplerPoint start = {10.0, 20.0};
    poppler_annot_line_set_vertices(POPPLER_ANNOT_LINE(annot), &start, nullptr);
}

TEST_F(PopplerAnnotLineSetVerticesTest_2112, SetVerticesNormalValues_2112) {
    if (!annot || !POPPLER_IS_ANNOT_LINE(annot))
        GTEST_SKIP() << "No line annotation available";

    PopplerPoint start = {150.0, 200.0};
    PopplerPoint end = {350.0, 400.0};

    PopplerAnnotLine *line_annot = POPPLER_ANNOT_LINE(annot);
    poppler_annot_line_set_vertices(line_annot, &start, &end);

    // No crash means success; the function is void
    SUCCEED();
}

TEST_F(PopplerAnnotLineSetVerticesTest_2112, SetVerticesZeroValues_2112) {
    if (!annot || !POPPLER_IS_ANNOT_LINE(annot))
        GTEST_SKIP() << "No line annotation available";

    PopplerPoint start = {0.0, 0.0};
    PopplerPoint end = {0.0, 0.0};

    PopplerAnnotLine *line_annot = POPPLER_ANNOT_LINE(annot);
    poppler_annot_line_set_vertices(line_annot, &start, &end);
    SUCCEED();
}

TEST_F(PopplerAnnotLineSetVerticesTest_2112, SetVerticesNegativeValues_2112) {
    if (!annot || !POPPLER_IS_ANNOT_LINE(annot))
        GTEST_SKIP() << "No line annotation available";

    PopplerPoint start = {-100.0, -200.0};
    PopplerPoint end = {-50.0, -25.0};

    PopplerAnnotLine *line_annot = POPPLER_ANNOT_LINE(annot);
    poppler_annot_line_set_vertices(line_annot, &start, &end);
    SUCCEED();
}

TEST_F(PopplerAnnotLineSetVerticesTest_2112, SetVerticesLargeValues_2112) {
    if (!annot || !POPPLER_IS_ANNOT_LINE(annot))
        GTEST_SKIP() << "No line annotation available";

    PopplerPoint start = {1e10, 1e10};
    PopplerPoint end = {-1e10, -1e10};

    PopplerAnnotLine *line_annot = POPPLER_ANNOT_LINE(annot);
    poppler_annot_line_set_vertices(line_annot, &start, &end);
    SUCCEED();
}

TEST_F(PopplerAnnotLineSetVerticesTest_2112, SetVerticesSamePoint_2112) {
    if (!annot || !POPPLER_IS_ANNOT_LINE(annot))
        GTEST_SKIP() << "No line annotation available";

    PopplerPoint start = {42.5, 42.5};
    PopplerPoint end = {42.5, 42.5};

    PopplerAnnotLine *line_annot = POPPLER_ANNOT_LINE(annot);
    poppler_annot_line_set_vertices(line_annot, &start, &end);
    SUCCEED();
}

TEST_F(PopplerAnnotLineSetVerticesTest_2112, BothNullPointsDoNotCrash_2112) {
    if (!annot || !POPPLER_IS_ANNOT_LINE(annot))
        GTEST_SKIP() << "No line annotation available";

    PopplerAnnotLine *line_annot = POPPLER_ANNOT_LINE(annot);
    poppler_annot_line_set_vertices(line_annot, nullptr, nullptr);
}

TEST_F(PopplerAnnotLineSetVerticesTest_2112, AllNullParamsDoNotCrash_2112) {
    poppler_annot_line_set_vertices(nullptr, nullptr, nullptr);
}

TEST_F(PopplerAnnotLineSetVerticesTest_2112, SetVerticesMultipleTimes_2112) {
    if (!annot || !POPPLER_IS_ANNOT_LINE(annot))
        GTEST_SKIP() << "No line annotation available";

    PopplerAnnotLine *line_annot = POPPLER_ANNOT_LINE(annot);

    PopplerPoint start1 = {10.0, 20.0};
    PopplerPoint end1 = {30.0, 40.0};
    poppler_annot_line_set_vertices(line_annot, &start1, &end1);

    PopplerPoint start2 = {50.0, 60.0};
    PopplerPoint end2 = {70.0, 80.0};
    poppler_annot_line_set_vertices(line_annot, &start2, &end2);

    PopplerPoint start3 = {100.0, 200.0};
    PopplerPoint end3 = {300.0, 400.0};
    poppler_annot_line_set_vertices(line_annot, &start3, &end3);

    SUCCEED();
}
