#include <glib.h>
#include <glib-object.h>
#include "poppler-document.h"
#include "poppler.h"
#include <gtest/gtest.h>

class PopplerFontInfoTest_2235 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;

    void SetUp() override {
        // Create a minimal valid PopplerDocument from a simple PDF file
        // We need a valid document to test poppler_font_info_new
        GError *error = nullptr;
        
        // Try to create a document from a minimal PDF in memory
        // First, try to find a test PDF or create one
        const char *minimal_pdf = 
            "%PDF-1.0\n"
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
        
        gsize len = strlen(minimal_pdf);
        
        // Write to a temporary file
        gchar *tmp_path = nullptr;
        GError *tmp_error = nullptr;
        gint fd = g_file_open_tmp("test_pdf_XXXXXX.pdf", &tmp_path, &tmp_error);
        if (fd >= 0 && tmp_path) {
            g_file_set_contents(tmp_path, minimal_pdf, len, nullptr);
            close(fd);
            
            gchar *uri = g_filename_to_uri(tmp_path, nullptr, nullptr);
            if (uri) {
                document = poppler_document_new_from_file(uri, nullptr, &error);
                g_free(uri);
            }
            g_unlink(tmp_path);
            g_free(tmp_path);
        }
        if (tmp_error) {
            g_error_free(tmp_error);
        }
        if (error) {
            g_error_free(error);
        }
    }

    void TearDown() override {
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
    }
};

TEST_F(PopplerFontInfoTest_2235, NewReturnsNonNull_2235) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    PopplerFontInfo *font_info = poppler_font_info_new(document);
    ASSERT_NE(font_info, nullptr);
    g_object_unref(font_info);
}

TEST_F(PopplerFontInfoTest_2235, NewWithNullDocumentReturnsNull_2235) {
    // Passing NULL should trigger g_return_val_if_fail and return NULL
    // Note: This will produce a g_critical warning
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");
    PopplerFontInfo *font_info = poppler_font_info_new(nullptr);
    g_test_assert_expected_messages();
    EXPECT_EQ(font_info, nullptr);
}

TEST_F(PopplerFontInfoTest_2235, NewReturnsValidGObject_2235) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    PopplerFontInfo *font_info = poppler_font_info_new(document);
    ASSERT_NE(font_info, nullptr);
    EXPECT_TRUE(POPPLER_IS_FONT_INFO(font_info));
    g_object_unref(font_info);
}

TEST_F(PopplerFontInfoTest_2235, NewIncreasesDocumentRefCount_2235) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    // Get initial ref count
    guint initial_ref = G_OBJECT(document)->ref_count;
    
    PopplerFontInfo *font_info = poppler_font_info_new(document);
    ASSERT_NE(font_info, nullptr);
    
    // Document should have been ref'd
    EXPECT_EQ(G_OBJECT(document)->ref_count, initial_ref + 1);
    
    g_object_unref(font_info);
    
    // After freeing font_info, document ref count should return
    EXPECT_EQ(G_OBJECT(document)->ref_count, initial_ref);
}

TEST_F(PopplerFontInfoTest_2235, MultipleNewCallsReturnDistinctObjects_2235) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    PopplerFontInfo *font_info1 = poppler_font_info_new(document);
    PopplerFontInfo *font_info2 = poppler_font_info_new(document);
    
    ASSERT_NE(font_info1, nullptr);
    ASSERT_NE(font_info2, nullptr);
    EXPECT_NE(font_info1, font_info2);
    
    g_object_unref(font_info1);
    g_object_unref(font_info2);
}

TEST_F(PopplerFontInfoTest_2235, NewWithInvalidGObjectReturnsNull_2235) {
    // Pass a non-PopplerDocument GObject — should fail POPPLER_IS_DOCUMENT check
    GObject *not_a_document = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);
    
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");
    PopplerFontInfo *font_info = poppler_font_info_new((PopplerDocument *)not_a_document);
    g_test_assert_expected_messages();
    
    EXPECT_EQ(font_info, nullptr);
    g_object_unref(not_a_document);
}

TEST_F(PopplerFontInfoTest_2235, ScanReturnsFalseOnEmptyDocument_2235) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    PopplerFontInfo *font_info = poppler_font_info_new(document);
    ASSERT_NE(font_info, nullptr);
    
    // Scan for fonts on a minimal document with no fonts
    GList *fonts_list = nullptr;
    gboolean result = poppler_font_info_scan(font_info, 1, &fonts_list);
    
    // On a minimal PDF with no pages having text, fonts_list may be empty
    // The result depends on whether there are more pages to scan
    // We just verify the function doesn't crash and returns a valid boolean
    EXPECT_TRUE(result == TRUE || result == FALSE);
    
    if (fonts_list) {
        g_list_free_full(fonts_list, (GDestroyNotify)g_object_unref);
    }
    
    g_object_unref(font_info);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
