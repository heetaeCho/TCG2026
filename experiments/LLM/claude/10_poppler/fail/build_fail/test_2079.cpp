#include <glib.h>
#include <poppler.h>
#include <poppler-document.h>
#include <poppler-page.h>
#include <cstdio>
#include <cstring>
#include <gtest/gtest.h>

class PopplerAnnotMarkupPopupTest_2079 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        // We'll try to create a minimal test scenario
        // Tests that require a real document will be skipped if not available
    }

    void TearDown() override {
        if (page) {
            g_object_unref(page);
            page = nullptr;
        }
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
    }

    bool loadTestDocument(const char *path) {
        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(path, nullptr, &error);
        if (!uri) {
            if (error) g_error_free(error);
            return false;
        }
        doc = poppler_document_new_from_uri(uri, nullptr, &error);
        g_free(uri);
        if (!doc) {
            if (error) g_error_free(error);
            return false;
        }
        if (poppler_document_get_n_pages(doc) > 0) {
            page = poppler_document_get_page(doc, 0);
        }
        return (page != nullptr);
    }
};

// Test that passing NULL returns FALSE (g_return_val_if_fail should handle this)
TEST_F(PopplerAnnotMarkupPopupTest_2079, NullAnnotReturnsFlase_2079) {
    // g_return_val_if_fail with NULL should return FALSE
    // We need to suppress the GLib critical warning for this test
    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*");
    gboolean result = poppler_annot_markup_get_popup_is_open(nullptr);
    g_test_assert_expected_messages();
    EXPECT_FALSE(result);
}

// Test that passing an invalid (non-markup) annotation type returns FALSE
TEST_F(PopplerAnnotMarkupPopupTest_2079, InvalidAnnotTypeReturnsFalse_2079) {
    // Create a non-markup annotation type and cast it
    // This should fail the POPPLER_IS_ANNOT_MARKUP check
    // We use a generic GObject that is not a PopplerAnnotMarkup
    GObject *fake_obj = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);
    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*");
    gboolean result = poppler_annot_markup_get_popup_is_open((PopplerAnnotMarkup *)fake_obj);
    g_test_assert_expected_messages();
    EXPECT_FALSE(result);
    g_object_unref(fake_obj);
}

// Test with a real markup annotation that has no popup - should return FALSE
TEST_F(PopplerAnnotMarkupPopupTest_2079, MarkupAnnotWithNoPopupReturnsFalse_2079) {
    PopplerRectangle rect = {100.0, 100.0, 200.0, 200.0};
    PopplerAnnotMarkup *markup_annot = nullptr;

    // Create a text annotation (which is a markup annotation subtype)
    PopplerAnnot *annot = poppler_annot_text_new(nullptr, &rect);
    if (annot == nullptr) {
        GTEST_SKIP() << "Cannot create PopplerAnnotText without a document";
        return;
    }

    if (POPPLER_IS_ANNOT_MARKUP(annot)) {
        markup_annot = POPPLER_ANNOT_MARKUP(annot);
        gboolean result = poppler_annot_markup_get_popup_is_open(markup_annot);
        // Without explicitly setting a popup, it should return FALSE
        EXPECT_FALSE(result);
    }

    g_object_unref(annot);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
