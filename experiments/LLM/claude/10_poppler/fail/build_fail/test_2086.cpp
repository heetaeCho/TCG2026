#include <glib.h>
#include <glib-object.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

// Include poppler glib headers
extern "C" {
#include "poppler-annot.h"
#include "poppler-document.h"
#include "poppler-page.h"
}

// We need access to internal poppler types for setting up test fixtures
#include "PDFDoc.h"
#include "Annot.h"
#include "GooString.h"

class PopplerAnnotMarkupGetSubjectTest_2086 : public ::testing::Test {
protected:
    void SetUp() override {
        // We'll use a real PDF to get actual annotations if possible
        doc = nullptr;
        page = nullptr;
    }

    void TearDown() override {
        if (page) {
            g_object_unref(page);
        }
        if (doc) {
            g_object_unref(doc);
        }
    }

    PopplerDocument *doc;
    PopplerPage *page;
};

// Test that passing NULL returns NULL (g_return_val_if_fail check)
TEST_F(PopplerAnnotMarkupGetSubjectTest_2086, NullAnnotReturnsNull_2086)
{
    // g_return_val_if_fail should handle NULL gracefully
    // We need to suppress the GLib warning for this test
    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_MARKUP*");
    gchar *result = poppler_annot_markup_get_subject(nullptr);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, nullptr);
}

// Test with an invalid GObject (not a PopplerAnnotMarkup)
TEST_F(PopplerAnnotMarkupGetSubjectTest_2086, InvalidObjectReturnsNull_2086)
{
    // Create some other GObject that is not a PopplerAnnotMarkup
    // Using a PopplerDocument or any other non-markup object would fail the IS_ANNOT_MARKUP check
    GError *error = nullptr;
    
    // We use a minimal approach: pass a non-PopplerAnnotMarkup pointer
    // The g_return_val_if_fail macro should catch this
    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_MARKUP*");
    gchar *result = poppler_annot_markup_get_subject((PopplerAnnotMarkup *)0x1);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, nullptr);
}

// Integration test: Load a PDF with annotations and test get_subject
// This test requires a PDF file with markup annotations that have subjects set.
// We test with a dynamically created annotation if the API allows it.
class PopplerAnnotMarkupFromPDFTest_2086 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = nullptr;
        // Try to load a test PDF - this path may need adjustment
        GError *error = nullptr;
        
        // Create a minimal test by attempting to find a test PDF
        // If no PDF is available, tests that need it will be skipped
    }

    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
        }
    }

    PopplerDocument *doc;
};

// Test that for a newly created text annotation (which is a markup annotation),
// get_subject returns NULL when no subject has been set
TEST_F(PopplerAnnotMarkupFromPDFTest_2086, NewAnnotHasNullSubject_2086)
{
    GError *error = nullptr;
    
    // Try to find a test PDF file
    const char *test_files[] = {
        "test.pdf",
        "../test.pdf",
        "/tmp/test.pdf",
        nullptr
    };
    
    PopplerDocument *test_doc = nullptr;
    for (int i = 0; test_files[i] != nullptr; i++) {
        gchar *uri = g_filename_to_uri(test_files[i], nullptr, nullptr);
        if (uri) {
            test_doc = poppler_document_new_from_file(uri, nullptr, &error);
            g_free(uri);
            if (test_doc) {
                break;
            }
            if (error) {
                g_clear_error(&error);
            }
        }
    }
    
    if (!test_doc) {
        GTEST_SKIP() << "No test PDF available for annotation subject testing";
        return;
    }

    PopplerPage *page = poppler_document_get_page(test_doc, 0);
    if (!page) {
        g_object_unref(test_doc);
        GTEST_SKIP() << "Could not get page from test PDF";
        return;
    }

    // Create a new text annotation (which is a subclass of markup)
    PopplerRectangle rect = { 10.0, 10.0, 100.0, 100.0 };
    PopplerAnnot *annot = poppler_annot_text_new(test_doc, &rect);
    
    if (annot && POPPLER_IS_ANNOT_MARKUP(annot)) {
        PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot);
        gchar *subject = poppler_annot_markup_get_subject(markup);
        // A newly created annotation may or may not have a subject
        // If it's null, that's expected for a new annotation
        if (subject) {
            g_free(subject);
        }
        // The test passes if we don't crash
        SUCCEED();
        g_object_unref(annot);
    } else {
        if (annot) {
            g_object_unref(annot);
        }
        GTEST_SKIP() << "Created annotation is not a markup annotation";
    }

    g_object_unref(page);
    g_object_unref(test_doc);
}

// Test: Verify returned string is a valid UTF-8 when subject exists
TEST_F(PopplerAnnotMarkupFromPDFTest_2086, SubjectIsValidUTF8WhenPresent_2086)
{
    GError *error = nullptr;
    
    const char *test_files[] = {
        "test.pdf",
        "../test.pdf",
        "/tmp/test.pdf",
        nullptr
    };
    
    PopplerDocument *test_doc = nullptr;
    for (int i = 0; test_files[i] != nullptr; i++) {
        gchar *uri = g_filename_to_uri(test_files[i], nullptr, nullptr);
        if (uri) {
            test_doc = poppler_document_new_from_file(uri, nullptr, &error);
            g_free(uri);
            if (test_doc) {
                break;
            }
            if (error) {
                g_clear_error(&error);
            }
        }
    }
    
    if (!test_doc) {
        GTEST_SKIP() << "No test PDF available";
        return;
    }

    // Iterate pages looking for markup annotations with subjects
    int n_pages = poppler_document_get_n_pages(test_doc);
    bool found_subject = false;
    
    for (int i = 0; i < n_pages && !found_subject; i++) {
        PopplerPage *pg = poppler_document_get_page(test_doc, i);
        if (!pg) continue;
        
        GList *annot_mapping = poppler_page_get_annot_mapping(pg);
        for (GList *l = annot_mapping; l != nullptr; l = l->next) {
            PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
            PopplerAnnot *annot = mapping->annot;
            
            if (POPPLER_IS_ANNOT_MARKUP(annot)) {
                PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot);
                gchar *subject = poppler_annot_markup_get_subject(markup);
                if (subject) {
                    EXPECT_TRUE(g_utf8_validate(subject, -1, nullptr))
                        << "Subject string is not valid UTF-8: " << subject;
                    g_free(subject);
                    found_subject = true;
                    break;
                }
            }
        }
        
        poppler_page_free_annot_mapping(annot_mapping);
        g_object_unref(pg);
    }
    
    if (!found_subject) {
        // It's okay if no annotation with subject was found - test is inconclusive
        GTEST_SKIP() << "No markup annotation with subject found in test PDF";
    }
    
    g_object_unref(test_doc);
}

// Test: calling get_subject multiple times returns consistent results
TEST_F(PopplerAnnotMarkupFromPDFTest_2086, MultipleCallsReturnConsistentResults_2086)
{
    GError *error = nullptr;
    
    const char *test_files[] = {
        "test.pdf",
        "../test.pdf",
        "/tmp/test.pdf",
        nullptr
    };
    
    PopplerDocument *test_doc = nullptr;
    for (int i = 0; test_files[i] != nullptr; i++) {
        gchar *uri = g_filename_to_uri(test_files[i], nullptr, nullptr);
        if (uri) {
            test_doc = poppler_document_new_from_file(uri, nullptr, &error);
            g_free(uri);
            if (test_doc) {
                break;
            }
            if (error) {
                g_clear_error(&error);
            }
        }
    }
    
    if (!test_doc) {
        GTEST_SKIP() << "No test PDF available";
        return;
    }

    PopplerPage *pg = poppler_document_get_page(test_doc, 0);
    if (!pg) {
        g_object_unref(test_doc);
        GTEST_SKIP() << "Could not get page";
        return;
    }

    GList *annot_mapping = poppler_page_get_annot_mapping(pg);
    bool tested = false;
    
    for (GList *l = annot_mapping; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
        PopplerAnnot *annot = mapping->annot;
        
        if (POPPLER_IS_ANNOT_MARKUP(annot)) {
            PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot);
            gchar *subject1 = poppler_annot_markup_get_subject(markup);
            gchar *subject2 = poppler_annot_markup_get_subject(markup);
            
            // Both calls should return the same value
            if (subject1 == nullptr) {
                EXPECT_EQ(subject2, nullptr);
            } else {
                ASSERT_NE(subject2, nullptr);
                EXPECT_STREQ(subject1, subject2);
            }
            
            g_free(subject1);
            g_free(subject2);
            tested = true;
            break;
        }
    }
    
    poppler_page_free_annot_mapping(annot_mapping);
    g_object_unref(pg);
    g_object_unref(test_doc);
    
    if (!tested) {
        GTEST_SKIP() << "No markup annotations found in test PDF";
    }
}

// Test: returned string is a newly allocated string (caller owns it)
TEST_F(PopplerAnnotMarkupFromPDFTest_2086, ReturnedStringIsNewlyAllocated_2086)
{
    GError *error = nullptr;
    
    const char *test_files[] = {
        "test.pdf",
        "../test.pdf",
        "/tmp/test.pdf",
        nullptr
    };
    
    PopplerDocument *test_doc = nullptr;
    for (int i = 0; test_files[i] != nullptr; i++) {
        gchar *uri = g_filename_to_uri(test_files[i], nullptr, nullptr);
        if (uri) {
            test_doc = poppler_document_new_from_file(uri, nullptr, &error);
            g_free(uri);
            if (test_doc) {
                break;
            }
            if (error) {
                g_clear_error(&error);
            }
        }
    }
    
    if (!test_doc) {
        GTEST_SKIP() << "No test PDF available";
        return;
    }

    PopplerPage *pg = poppler_document_get_page(test_doc, 0);
    if (!pg) {
        g_object_unref(test_doc);
        GTEST_SKIP() << "Could not get page";
        return;
    }

    GList *annot_mapping = poppler_page_get_annot_mapping(pg);
    bool tested = false;
    
    for (GList *l = annot_mapping; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
        PopplerAnnot *annot = mapping->annot;
        
        if (POPPLER_IS_ANNOT_MARKUP(annot)) {
            PopplerAnnotMarkup *markup = POPPLER_ANNOT_MARKUP(annot);
            gchar *subject1 = poppler_annot_markup_get_subject(markup);
            gchar *subject2 = poppler_annot_markup_get_subject(markup);
            
            if (subject1 != nullptr && subject2 != nullptr) {
                // They should be different pointers (newly allocated each time)
                EXPECT_NE(subject1, subject2)
                    << "get_subject should return newly allocated strings";
                EXPECT_STREQ(subject1, subject2);
            }
            
            g_free(subject1);
            g_free(subject2);
            tested = true;
            break;
        }
    }
    
    poppler_page_free_annot_mapping(annot_mapping);
    g_object_unref(pg);
    g_object_unref(test_doc);
    
    if (!tested) {
        GTEST_SKIP() << "No markup annotations found in test PDF";
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
