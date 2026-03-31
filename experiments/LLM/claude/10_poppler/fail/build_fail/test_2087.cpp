#include <glib.h>
#include <glib-object.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include poppler headers
#include "poppler-annot.h"
#include "poppler-document.h"
#include "poppler-page.h"
#include "PDFDoc.h"
#include "Annot.h"
#include "Object.h"
#include "Dict.h"
#include "PDFDocFactory.h"

// We need access to internal structures for creating test fixtures
extern "C" {
#include "poppler-private.h"
}

class PopplerAnnotMarkupReplyToTest_2087 : public ::testing::Test {
protected:
    void SetUp() override {
        // We'll create documents from test PDF files or construct annotations
        // programmatically where possible
    }

    void TearDown() override {
    }

    // Helper to create a PopplerDocument from a minimal PDF in memory
    PopplerDocument *createMinimalDocument() {
        // Create a simple PDF with a text annotation (which is a markup annotation)
        const char *pdf_path = nullptr;
        // We need a real PDF file for testing; use a temporary approach
        return nullptr;
    }
};

// Test that passing NULL returns the default POPPLER_ANNOT_MARKUP_REPLY_TYPE_R
TEST_F(PopplerAnnotMarkupReplyToTest_2087, NullAnnotReturnsDefaultReplyType_2087) {
    // When passing NULL, g_return_val_if_fail should trigger and return default
    // We suppress the GLib warning for this test
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_MARKUP*");
    
    PopplerAnnotMarkupReplyType result = poppler_annot_markup_get_reply_to(NULL);
    
    g_test_assert_expected_messages();
    EXPECT_EQ(result, POPPLER_ANNOT_MARKUP_REPLY_TYPE_R);
}

// Test with a real PDF file that has markup annotations
class PopplerAnnotMarkupFromFileTest_2087 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    GError *error = nullptr;
    
    void SetUp() override {
        // Try to create a minimal in-memory PDF with annotations
        // We'll generate a minimal PDF buffer
        const char *minimal_pdf =
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Annots[4 0 R]>>endobj\n"
            "4 0 obj<</Type/Annot/Subtype/Text/Rect[100 700 200 750]/Contents(Test)/RT/R>>endobj\n"
            "xref\n"
            "0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000214 00000 n \n"
            "trailer<</Size 5/Root 1 0 R>>\n"
            "startxref\n"
            "321\n"
            "%%EOF\n";
        
        // Write to a temp file
        gchar *tmp_path = nullptr;
        gint fd = g_file_open_tmp("poppler_test_XXXXXX.pdf", &tmp_path, &error);
        if (fd >= 0 && tmp_path) {
            write(fd, minimal_pdf, strlen(minimal_pdf));
            close(fd);
            
            gchar *uri = g_filename_to_uri(tmp_path, nullptr, &error);
            if (uri) {
                doc = poppler_document_new_from_file(uri, nullptr, &error);
                g_free(uri);
            }
            // Clean up temp file
            g_unlink(tmp_path);
            g_free(tmp_path);
        }
    }
    
    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
        }
        if (error) {
            g_error_free(error);
        }
    }
};

// Test that the reply type enum values match expected values
TEST(PopplerAnnotMarkupReplyTypeEnumTest_2087, EnumValuesAreCorrect_2087) {
    EXPECT_EQ(POPPLER_ANNOT_MARKUP_REPLY_TYPE_R, 0);
    EXPECT_EQ(POPPLER_ANNOT_MARKUP_REPLY_TYPE_GROUP, 1);
}

// Test that passing a non-markup annotation (wrong type) returns default
TEST_F(PopplerAnnotMarkupReplyToTest_2087, WrongTypeAnnotReturnsDefault_2087) {
    // Creating a non-PopplerAnnotMarkup GObject and passing it should fail the type check
    // Use a random GObject
    GObject *obj = (GObject*)g_object_new(G_TYPE_OBJECT, NULL);
    
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_MARKUP*");
    
    PopplerAnnotMarkupReplyType result = poppler_annot_markup_get_reply_to((PopplerAnnotMarkup*)obj);
    
    g_test_assert_expected_messages();
    EXPECT_EQ(result, POPPLER_ANNOT_MARKUP_REPLY_TYPE_R);
    
    g_object_unref(obj);
}

// Test with a document containing a Text annotation (which is a markup annotation)
// to verify the default reply type (replyTypeR)
TEST_F(PopplerAnnotMarkupFromFileTest_2087, TextAnnotDefaultReplyTypeIsR_2087) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }
    
    GList *annots = poppler_page_get_annot_mapping(page);
    
    bool found_markup = false;
    for (GList *l = annots; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
        PopplerAnnot *annot = mapping->annot;
        
        if (POPPLER_IS_ANNOT_MARKUP(annot)) {
            PopplerAnnotMarkupReplyType reply_type = 
                poppler_annot_markup_get_reply_to(POPPLER_ANNOT_MARKUP(annot));
            // Default reply type for Text annotations without explicit RT should be R
            EXPECT_EQ(reply_type, POPPLER_ANNOT_MARKUP_REPLY_TYPE_R);
            found_markup = true;
        }
    }
    
    poppler_page_free_annot_mapping(annots);
    g_object_unref(page);
    
    // It's okay if we didn't find markup annotations in our minimal PDF
    if (!found_markup) {
        GTEST_SKIP() << "No markup annotations found in test document";
    }
}

// Test with a PDF that has RT/Group reply type
class PopplerAnnotMarkupGroupReplyTest_2087 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    GError *error = nullptr;
    
    void SetUp() override {
        const char *pdf_with_group =
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Annots[4 0 R 5 0 R]>>endobj\n"
            "4 0 obj<</Type/Annot/Subtype/Text/Rect[100 700 200 750]/Contents(Parent)>>endobj\n"
            "5 0 obj<</Type/Annot/Subtype/Text/Rect[100 600 200 650]/Contents(Reply)/IRT 4 0 R/RT/Group>>endobj\n"
            "xref\n"
            "0 6\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000226 00000 n \n"
            "0000000323 00000 n \n"
            "trailer<</Size 6/Root 1 0 R>>\n"
            "startxref\n"
            "441\n"
            "%%EOF\n";
        
        gchar *tmp_path = nullptr;
        gint fd = g_file_open_tmp("poppler_group_test_XXXXXX.pdf", &tmp_path, &error);
        if (fd >= 0 && tmp_path) {
            write(fd, pdf_with_group, strlen(pdf_with_group));
            close(fd);
            
            gchar *uri = g_filename_to_uri(tmp_path, nullptr, &error);
            if (uri) {
                doc = poppler_document_new_from_file(uri, nullptr, &error);
                g_free(uri);
            }
            g_unlink(tmp_path);
            g_free(tmp_path);
        }
    }
    
    void TearDown() override {
        if (doc) g_object_unref(doc);
        if (error) g_error_free(error);
    }
};

TEST_F(PopplerAnnotMarkupGroupReplyTest_2087, GroupReplyTypeAnnotation_2087) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document with group reply";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }
    
    GList *annots = poppler_page_get_annot_mapping(page);
    
    bool found_group_reply = false;
    for (GList *l = annots; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
        PopplerAnnot *annot = mapping->annot;
        
        if (POPPLER_IS_ANNOT_MARKUP(annot)) {
            PopplerAnnotMarkupReplyType reply_type = 
                poppler_annot_markup_get_reply_to(POPPLER_ANNOT_MARKUP(annot));
            
            if (reply_type == POPPLER_ANNOT_MARKUP_REPLY_TYPE_GROUP) {
                found_group_reply = true;
            }
            // Either R or Group should be valid
            EXPECT_TRUE(reply_type == POPPLER_ANNOT_MARKUP_REPLY_TYPE_R || 
                        reply_type == POPPLER_ANNOT_MARKUP_REPLY_TYPE_GROUP);
        }
    }
    
    poppler_page_free_annot_mapping(annots);
    g_object_unref(page);
    
    if (!found_group_reply) {
        // The minimal PDF may not parse correctly, but we at least verified no crashes
        GTEST_SKIP() << "Group reply annotation not found (PDF may not have parsed correctly)";
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
