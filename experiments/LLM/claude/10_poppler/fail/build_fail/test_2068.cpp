#include <glib.h>
#include <poppler.h>
#include <poppler-document.h>
#include <poppler-page.h>
#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>

class PopplerAnnotSetFlagsTest_2068 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        // Create a minimal PDF in memory with an annotation
        // We'll try to create a document and add an annotation to it
        GError *error = nullptr;

        // Create a simple PDF file with at least one page
        const char *pdf_content =
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Annots[4 0 R]>>endobj\n"
            "4 0 obj<</Type/Annot/Subtype/Text/Rect[100 100 200 200]/Contents(Test)/F 0>>endobj\n"
            "xref\n"
            "0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000206 00000 n \n"
            "trailer<</Size 5/Root 1 0 R>>\n"
            "startxref\n"
            "314\n"
            "%%EOF\n";

        gsize len = strlen(pdf_content);

        // Write to a temp file
        tmpfile_path = g_strdup("/tmp/test_poppler_annot_2068.pdf");
        FILE *f = fopen(tmpfile_path, "wb");
        if (f) {
            fwrite(pdf_content, 1, len, f);
            fclose(f);
        }

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
    }

    void TearDown() override {
        if (page)
            g_object_unref(page);
        if (doc)
            g_object_unref(doc);
        if (tmpfile_path) {
            g_unlink(tmpfile_path);
            g_free(tmpfile_path);
        }
    }

    gchar *tmpfile_path = nullptr;

    PopplerAnnot *getFirstAnnot() {
        if (!page) return nullptr;
        GList *annots = poppler_page_get_annot_mapping(page);
        if (!annots) return nullptr;
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)annots->data;
        PopplerAnnot *annot = mapping->annot;
        if (annot)
            g_object_ref(annot);
        poppler_page_free_annot_mapping(annots);
        return annot;
    }
};

TEST_F(PopplerAnnotSetFlagsTest_2068, SetFlagsNormal_2068) {
    PopplerAnnot *annot = getFirstAnnot();
    if (!annot) {
        GTEST_SKIP() << "Could not create annotation for testing";
    }

    PopplerAnnotFlag new_flags = POPPLER_ANNOT_FLAG_HIDDEN;
    poppler_annot_set_flags(annot, new_flags);
    PopplerAnnotFlag result = poppler_annot_get_flags(annot);
    EXPECT_EQ(result, new_flags);

    g_object_unref(annot);
}

TEST_F(PopplerAnnotSetFlagsTest_2068, SetFlagsSameValueNoChange_2068) {
    PopplerAnnot *annot = getFirstAnnot();
    if (!annot) {
        GTEST_SKIP() << "Could not create annotation for testing";
    }

    PopplerAnnotFlag current_flags = poppler_annot_get_flags(annot);
    // Setting the same flags should return early without error
    poppler_annot_set_flags(annot, current_flags);
    PopplerAnnotFlag result = poppler_annot_get_flags(annot);
    EXPECT_EQ(result, current_flags);

    g_object_unref(annot);
}

TEST_F(PopplerAnnotSetFlagsTest_2068, SetFlagsMultipleFlags_2068) {
    PopplerAnnot *annot = getFirstAnnot();
    if (!annot) {
        GTEST_SKIP() << "Could not create annotation for testing";
    }

    PopplerAnnotFlag combined = (PopplerAnnotFlag)(POPPLER_ANNOT_FLAG_HIDDEN | POPPLER_ANNOT_FLAG_PRINT);
    poppler_annot_set_flags(annot, combined);
    PopplerAnnotFlag result = poppler_annot_get_flags(annot);
    EXPECT_EQ(result, combined);

    g_object_unref(annot);
}

TEST_F(PopplerAnnotSetFlagsTest_2068, SetFlagsZero_2068) {
    PopplerAnnot *annot = getFirstAnnot();
    if (!annot) {
        GTEST_SKIP() << "Could not create annotation for testing";
    }

    poppler_annot_set_flags(annot, (PopplerAnnotFlag)0);
    PopplerAnnotFlag result = poppler_annot_get_flags(annot);
    EXPECT_EQ(result, (PopplerAnnotFlag)0);

    g_object_unref(annot);
}

TEST_F(PopplerAnnotSetFlagsTest_2068, SetFlagsSequentialChanges_2068) {
    PopplerAnnot *annot = getFirstAnnot();
    if (!annot) {
        GTEST_SKIP() << "Could not create annotation for testing";
    }

    poppler_annot_set_flags(annot, POPPLER_ANNOT_FLAG_HIDDEN);
    EXPECT_EQ(poppler_annot_get_flags(annot), POPPLER_ANNOT_FLAG_HIDDEN);

    poppler_annot_set_flags(annot, POPPLER_ANNOT_FLAG_PRINT);
    EXPECT_EQ(poppler_annot_get_flags(annot), POPPLER_ANNOT_FLAG_PRINT);

    poppler_annot_set_flags(annot, POPPLER_ANNOT_FLAG_NO_ZOOM);
    EXPECT_EQ(poppler_annot_get_flags(annot), POPPLER_ANNOT_FLAG_NO_ZOOM);

    g_object_unref(annot);
}

TEST_F(PopplerAnnotSetFlagsTest_2068, SetFlagsNullAnnot_2068) {
    // Passing NULL should not crash (g_return_if_fail handles it)
    poppler_annot_set_flags(nullptr, POPPLER_ANNOT_FLAG_HIDDEN);
    // If we reach here, the function handled NULL gracefully
    SUCCEED();
}

TEST_F(PopplerAnnotSetFlagsTest_2068, SetFlagsInvisible_2068) {
    PopplerAnnot *annot = getFirstAnnot();
    if (!annot) {
        GTEST_SKIP() << "Could not create annotation for testing";
    }

    poppler_annot_set_flags(annot, POPPLER_ANNOT_FLAG_INVISIBLE);
    PopplerAnnotFlag result = poppler_annot_get_flags(annot);
    EXPECT_EQ(result, POPPLER_ANNOT_FLAG_INVISIBLE);

    g_object_unref(annot);
}

TEST_F(PopplerAnnotSetFlagsTest_2068, SetFlagsAllCombined_2068) {
    PopplerAnnot *annot = getFirstAnnot();
    if (!annot) {
        GTEST_SKIP() << "Could not create annotation for testing";
    }

    PopplerAnnotFlag all_flags = (PopplerAnnotFlag)(
        POPPLER_ANNOT_FLAG_INVISIBLE |
        POPPLER_ANNOT_FLAG_HIDDEN |
        POPPLER_ANNOT_FLAG_PRINT |
        POPPLER_ANNOT_FLAG_NO_ZOOM |
        POPPLER_ANNOT_FLAG_NO_ROTATE |
        POPPLER_ANNOT_FLAG_NO_VIEW |
        POPPLER_ANNOT_FLAG_READ_ONLY |
        POPPLER_ANNOT_FLAG_LOCKED |
        POPPLER_ANNOT_FLAG_TOGGLE_NO_VIEW |
        POPPLER_ANNOT_FLAG_LOCKED_CONTENTS
    );

    poppler_annot_set_flags(annot, all_flags);
    PopplerAnnotFlag result = poppler_annot_get_flags(annot);
    EXPECT_EQ(result, all_flags);

    g_object_unref(annot);
}
