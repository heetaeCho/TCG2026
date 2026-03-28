#include <glib.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstring>
#include <cstdio>

// We need access to the glib poppler-annot functions
extern "C" {
#include "poppler-annot.h"
}

class PopplerAnnotMarkupSetPopupIsOpenTest_2080 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        // Try to load a test PDF that has markup annotations with popups
        // We'll create a minimal PDF in memory or load from a known path
        GError *error = nullptr;
        
        // Attempt to create a simple document with annotations
        // We need a real PDF document for testing
        const char *test_pdf_path = getenv("TEST_PDF_PATH");
        if (test_pdf_path) {
            gchar *uri = g_filename_to_uri(test_pdf_path, nullptr, &error);
            if (uri) {
                doc = poppler_document_new_from_file(uri, nullptr, &error);
                g_free(uri);
            }
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
    }

    PopplerAnnotMarkup* findMarkupAnnot() {
        if (!page) return nullptr;
        
        GList *annots = poppler_page_get_annot_mapping(page);
        PopplerAnnotMarkup *markup = nullptr;
        
        for (GList *l = annots; l != nullptr; l = l->next) {
            PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
            PopplerAnnot *annot = mapping->annot;
            if (POPPLER_IS_ANNOT_MARKUP(annot)) {
                markup = POPPLER_ANNOT_MARKUP(annot);
                g_object_ref(markup);
                break;
            }
        }
        
        poppler_page_free_annot_mapping(annots);
        return markup;
    }
};

// Test that passing NULL does not crash (g_return_if_fail should handle it)
TEST_F(PopplerAnnotMarkupSetPopupIsOpenTest_2080, NullAnnotDoesNotCrash_2080) {
    // g_return_if_fail should prevent crash on NULL
    // This test verifies the guard clause works
    if (g_test_undefined()) {
        // Suppress GLib critical warnings for this test
        g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_MARKUP*");
        poppler_annot_markup_set_popup_is_open(nullptr, TRUE);
        g_test_assert_expected_messages();
    }
}

// Test setting popup open state to TRUE on a markup annotation
TEST_F(PopplerAnnotMarkupSetPopupIsOpenTest_2080, SetPopupIsOpenTrue_2080) {
    PopplerAnnotMarkup *markup = findMarkupAnnot();
    if (!markup) {
        GTEST_SKIP() << "No markup annotation found in test PDF";
    }
    
    poppler_annot_markup_set_popup_is_open(markup, TRUE);
    gboolean is_open = poppler_annot_markup_get_popup_is_open(markup);
    EXPECT_TRUE(is_open);
    
    g_object_unref(markup);
}

// Test setting popup open state to FALSE on a markup annotation
TEST_F(PopplerAnnotMarkupSetPopupIsOpenTest_2080, SetPopupIsOpenFalse_2080) {
    PopplerAnnotMarkup *markup = findMarkupAnnot();
    if (!markup) {
        GTEST_SKIP() << "No markup annotation found in test PDF";
    }
    
    poppler_annot_markup_set_popup_is_open(markup, FALSE);
    gboolean is_open = poppler_annot_markup_get_popup_is_open(markup);
    EXPECT_FALSE(is_open);
    
    g_object_unref(markup);
}

// Test toggling popup open state
TEST_F(PopplerAnnotMarkupSetPopupIsOpenTest_2080, TogglePopupIsOpen_2080) {
    PopplerAnnotMarkup *markup = findMarkupAnnot();
    if (!markup) {
        GTEST_SKIP() << "No markup annotation found in test PDF";
    }
    
    poppler_annot_markup_set_popup_is_open(markup, TRUE);
    EXPECT_TRUE(poppler_annot_markup_get_popup_is_open(markup));
    
    poppler_annot_markup_set_popup_is_open(markup, FALSE);
    EXPECT_FALSE(poppler_annot_markup_get_popup_is_open(markup));
    
    poppler_annot_markup_set_popup_is_open(markup, TRUE);
    EXPECT_TRUE(poppler_annot_markup_get_popup_is_open(markup));
    
    g_object_unref(markup);
}

// Test setting the same value twice (idempotent behavior)
TEST_F(PopplerAnnotMarkupSetPopupIsOpenTest_2080, SetSameValueTwice_2080) {
    PopplerAnnotMarkup *markup = findMarkupAnnot();
    if (!markup) {
        GTEST_SKIP() << "No markup annotation found in test PDF";
    }
    
    poppler_annot_markup_set_popup_is_open(markup, TRUE);
    EXPECT_TRUE(poppler_annot_markup_get_popup_is_open(markup));
    
    // Setting the same value again should not change anything
    poppler_annot_markup_set_popup_is_open(markup, TRUE);
    EXPECT_TRUE(poppler_annot_markup_get_popup_is_open(markup));
    
    g_object_unref(markup);
}

// Test with invalid (non-markup) annotation type - should trigger g_return_if_fail
TEST_F(PopplerAnnotMarkupSetPopupIsOpenTest_2080, InvalidAnnotType_2080) {
    if (!page) {
        GTEST_SKIP() << "No test PDF available";
    }
    
    // Create a non-markup annotation (e.g., a link annotation wouldn't be markup)
    // We test by creating a generic widget or other non-markup annot
    // Since we can't easily create one, we skip if no suitable annot is found
    GList *annots = poppler_page_get_annot_mapping(page);
    PopplerAnnot *non_markup = nullptr;
    
    for (GList *l = annots; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
        PopplerAnnot *annot = mapping->annot;
        if (!POPPLER_IS_ANNOT_MARKUP(annot)) {
            non_markup = annot;
            g_object_ref(non_markup);
            break;
        }
    }
    
    poppler_page_free_annot_mapping(annots);
    
    if (!non_markup) {
        GTEST_SKIP() << "No non-markup annotation found for negative testing";
    }
    
    // This should trigger g_return_if_fail and do nothing
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_MARKUP*");
    poppler_annot_markup_set_popup_is_open((PopplerAnnotMarkup *)non_markup, TRUE);
    g_test_assert_expected_messages();
    
    g_object_unref(non_markup);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
