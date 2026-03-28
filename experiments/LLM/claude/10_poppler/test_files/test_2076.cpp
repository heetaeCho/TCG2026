#include <glib.h>
#include <glib-object.h>
#include "poppler.h"
#include "poppler-annot.h"
#include <gtest/gtest.h>
#include <cstring>

// Helper to create a PopplerAnnotMarkup for testing.
// We need a real PDF document with an annotation to get a valid PopplerAnnotMarkup.
class PopplerAnnotMarkupSetLabelTest_2076 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;
    PopplerAnnot *annot = nullptr;
    PopplerAnnotMarkup *markup_annot = nullptr;
    GList *annot_mapping_list = nullptr;

    void SetUp() override {
        // Create a minimal PDF in memory that has a text annotation (markup annotation)
        // so we can test set_label on it.
        // Alternative: create a FreeText annotation on a page.

        // We'll create a simple PDF document from a file or from scratch.
        // Since we need a real annotation, let's create one programmatically.

        GError *error = nullptr;

        // Create a simple one-page PDF in memory
        const char *pdf_data =
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/Annots[4 0 R]>>endobj\n"
            "4 0 obj<</Type/Annot/Subtype/Text/Rect[100 100 200 200]/T(Test)/Contents(Hello)>>endobj\n"
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

        // Write to a temp file
        gchar *tmp_filename = nullptr;
        int fd = g_file_open_tmp("test_poppler_XXXXXX.pdf", &tmp_filename, &error);
        if (fd == -1) {
            GTEST_SKIP() << "Could not create temp file";
            return;
        }

        gsize len = strlen(pdf_data);
        if (write(fd, pdf_data, len) != (ssize_t)len) {
            close(fd);
            g_free(tmp_filename);
            GTEST_SKIP() << "Could not write temp file";
            return;
        }
        close(fd);

        gchar *uri = g_filename_to_uri(tmp_filename, nullptr, &error);
        if (!uri) {
            g_free(tmp_filename);
            GTEST_SKIP() << "Could not create URI";
            return;
        }

        doc = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);

        if (!doc) {
            // The minimal PDF might not parse. Try another approach.
            g_clear_error(&error);
            g_unlink(tmp_filename);
            g_free(tmp_filename);
            GTEST_SKIP() << "Could not create document from minimal PDF";
            return;
        }

        g_unlink(tmp_filename);
        g_free(tmp_filename);

        page = poppler_document_get_page(doc, 0);
        if (!page) {
            GTEST_SKIP() << "Could not get page";
            return;
        }

        annot_mapping_list = poppler_page_get_annot_mapping(page);
        if (!annot_mapping_list) {
            // No annotations found; try adding one
            PopplerRectangle rect = {100, 100, 200, 200};
            annot = POPPLER_ANNOT(poppler_annot_text_new(doc, &rect));
            if (annot && POPPLER_IS_ANNOT_MARKUP(annot)) {
                markup_annot = POPPLER_ANNOT_MARKUP(annot);
            } else {
                GTEST_SKIP() << "Could not create markup annotation";
            }
            return;
        }

        // Find a markup annotation
        for (GList *l = annot_mapping_list; l; l = l->next) {
            PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
            if (POPPLER_IS_ANNOT_MARKUP(mapping->annot)) {
                markup_annot = POPPLER_ANNOT_MARKUP(mapping->annot);
                break;
            }
        }

        if (!markup_annot) {
            GTEST_SKIP() << "No markup annotation found in test PDF";
        }
    }

    void TearDown() override {
        if (annot_mapping_list) {
            poppler_page_free_annot_mapping(annot_mapping_list);
        }
        if (annot && !annot_mapping_list) {
            g_object_unref(annot);
        }
        if (page) {
            g_object_unref(page);
        }
        if (doc) {
            g_object_unref(doc);
        }
    }
};

// Test: Setting a normal ASCII label
TEST_F(PopplerAnnotMarkupSetLabelTest_2076, SetNormalLabel_2076) {
    if (!markup_annot) {
        GTEST_SKIP();
    }

    poppler_annot_markup_set_label(markup_annot, "Test Author");
    gchar *label = poppler_annot_markup_get_label(markup_annot);
    ASSERT_NE(label, nullptr);
    EXPECT_STREQ(label, "Test Author");
    g_free(label);
}

// Test: Setting a UTF-8 label with non-ASCII characters
TEST_F(PopplerAnnotMarkupSetLabelTest_2076, SetUTF8Label_2076) {
    if (!markup_annot) {
        GTEST_SKIP();
    }

    const gchar *utf8_label = "Ünïcödé Àuthör";
    poppler_annot_markup_set_label(markup_annot, utf8_label);
    gchar *label = poppler_annot_markup_get_label(markup_annot);
    ASSERT_NE(label, nullptr);
    EXPECT_STREQ(label, utf8_label);
    g_free(label);
}

// Test: Setting an empty string label
TEST_F(PopplerAnnotMarkupSetLabelTest_2076, SetEmptyLabel_2076) {
    if (!markup_annot) {
        GTEST_SKIP();
    }

    poppler_annot_markup_set_label(markup_annot, "");
    gchar *label = poppler_annot_markup_get_label(markup_annot);
    // Empty string should result in either nullptr or empty string
    if (label) {
        EXPECT_STREQ(label, "");
        g_free(label);
    }
}

// Test: Setting a NULL label
TEST_F(PopplerAnnotMarkupSetLabelTest_2076, SetNullLabel_2076) {
    if (!markup_annot) {
        GTEST_SKIP();
    }

    // First set a non-null label
    poppler_annot_markup_set_label(markup_annot, "Initial");
    // Now set to NULL
    poppler_annot_markup_set_label(markup_annot, nullptr);
    // Should not crash; the label should be cleared or empty
    gchar *label = poppler_annot_markup_get_label(markup_annot);
    // After setting NULL, label could be nullptr or empty
    if (label) {
        EXPECT_STREQ(label, "");
        g_free(label);
    }
}

// Test: Setting label twice (overwrite)
TEST_F(PopplerAnnotMarkupSetLabelTest_2076, SetLabelTwice_2076) {
    if (!markup_annot) {
        GTEST_SKIP();
    }

    poppler_annot_markup_set_label(markup_annot, "First Label");
    gchar *label1 = poppler_annot_markup_get_label(markup_annot);
    ASSERT_NE(label1, nullptr);
    EXPECT_STREQ(label1, "First Label");
    g_free(label1);

    poppler_annot_markup_set_label(markup_annot, "Second Label");
    gchar *label2 = poppler_annot_markup_get_label(markup_annot);
    ASSERT_NE(label2, nullptr);
    EXPECT_STREQ(label2, "Second Label");
    g_free(label2);
}

// Test: Setting a very long label
TEST_F(PopplerAnnotMarkupSetLabelTest_2076, SetLongLabel_2076) {
    if (!markup_annot) {
        GTEST_SKIP();
    }

    // Create a long string
    std::string long_label(10000, 'A');
    poppler_annot_markup_set_label(markup_annot, long_label.c_str());
    gchar *label = poppler_annot_markup_get_label(markup_annot);
    ASSERT_NE(label, nullptr);
    EXPECT_EQ(std::string(label), long_label);
    g_free(label);
}

// Test: Passing NULL as the annotation should not crash (g_return_if_fail guards it)
TEST_F(PopplerAnnotMarkupSetLabelTest_2076, NullAnnotDoesNotCrash_2076) {
    // This should trigger g_return_if_fail and simply return without crashing
    poppler_annot_markup_set_label(nullptr, "Some label");
    // If we reach here, we didn't crash — that's the test
    SUCCEED();
}

// Test: Label with special characters
TEST_F(PopplerAnnotMarkupSetLabelTest_2076, SetLabelWithSpecialChars_2076) {
    if (!markup_annot) {
        GTEST_SKIP();
    }

    const gchar *special_label = "Line1\nLine2\tTab \"Quotes\" <Angle>";
    poppler_annot_markup_set_label(markup_annot, special_label);
    gchar *label = poppler_annot_markup_get_label(markup_annot);
    ASSERT_NE(label, nullptr);
    EXPECT_STREQ(label, special_label);
    g_free(label);
}

// Test: Label with CJK characters
TEST_F(PopplerAnnotMarkupSetLabelTest_2076, SetLabelWithCJK_2076) {
    if (!markup_annot) {
        GTEST_SKIP();
    }

    const gchar *cjk_label = "日本語テスト";
    poppler_annot_markup_set_label(markup_annot, cjk_label);
    gchar *label = poppler_annot_markup_get_label(markup_annot);
    ASSERT_NE(label, nullptr);
    EXPECT_STREQ(label, cjk_label);
    g_free(label);
}
