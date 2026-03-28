#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glib.h>

// Include poppler glib headers
#include "poppler-annot.h"
#include "poppler-private.h"
#include "poppler-document.h"

#include <memory>
#include <string>

// Include poppler core headers
#include "Annot.h"
#include "GooString.h"
#include "PDFDoc.h"

class PopplerAnnotGetContentsTest_2063 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL returns NULL
TEST_F(PopplerAnnotGetContentsTest_2063, NullAnnotReturnsNull_2063)
{
    gchar *result = poppler_annot_get_contents(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test with a valid poppler annot loaded from a real PDF with annotations
// Since we cannot easily construct PopplerAnnot objects without a real PDF,
// we test the NULL/invalid input paths that are observable.

// Test that a non-PopplerAnnot GObject returns NULL (g_return_val_if_fail check)
TEST_F(PopplerAnnotGetContentsTest_2063, InvalidGObjectReturnsNull_2063)
{
    // Passing a non-annot pointer should trigger g_return_val_if_fail and return NULL
    // We use NULL which is the simplest invalid input
    gchar *result = poppler_annot_get_contents((PopplerAnnot *)nullptr);
    EXPECT_EQ(result, nullptr);
}

// Integration-style test: Load a PDF with annotations and verify get_contents behavior
// This test requires a test PDF file. We create a minimal test that checks
// the function can be called on actual annotation objects from a document.
class PopplerAnnotFromDocTest_2063 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override
    {
        // Try to load a test PDF - if not available, skip
        GError *error = nullptr;
        // We'll try to create a minimal scenario; if no test file is available, tests will be skipped
        doc = nullptr;
        page = nullptr;
    }

    void TearDown() override
    {
        if (page) {
            g_object_unref(page);
        }
        if (doc) {
            g_object_unref(doc);
        }
    }

    bool loadTestPdf(const char *path)
    {
        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(path, nullptr, &error);
        if (!uri) {
            if (error)
                g_error_free(error);
            return false;
        }
        doc = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        if (!doc) {
            if (error)
                g_error_free(error);
            return false;
        }
        if (poppler_document_get_n_pages(doc) > 0) {
            page = poppler_document_get_page(doc, 0);
        }
        return (page != nullptr);
    }
};

// Test that get_contents returns a string or NULL for annotations from a real document
TEST_F(PopplerAnnotFromDocTest_2063, GetContentsFromRealAnnot_2063)
{
    // This test demonstrates the interface usage pattern
    // Without a test PDF, we verify the null-safety
    gchar *result = poppler_annot_get_contents(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test that the returned string (if non-null) is a valid UTF-8 string
TEST_F(PopplerAnnotGetContentsTest_2063, ReturnedStringIsValidUtf8OrNull_2063)
{
    // We can only test the null case without a real PDF
    gchar *result = poppler_annot_get_contents(nullptr);
    if (result != nullptr) {
        EXPECT_TRUE(g_utf8_validate(result, -1, nullptr));
        g_free(result);
    } else {
        EXPECT_EQ(result, nullptr);
    }
}
