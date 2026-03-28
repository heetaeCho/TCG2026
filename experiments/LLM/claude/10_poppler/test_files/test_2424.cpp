#include <glib-object.h>
#include <poppler.h>
#include "poppler-private.h"
#include <gtest/gtest.h>

// We need access to the internal function
extern "C" {
PopplerPage *_poppler_page_new(PopplerDocument *document, Page *page, int index);
}

class PopplerPageNewTest_2424 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;

    void SetUp() override {
        // Create a minimal PDF in memory to get a valid PopplerDocument
        const char *pdf_content =
            "%PDF-1.0\n"
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

        GError *error = nullptr;
        GBytes *bytes = g_bytes_new_static(pdf_content, strlen(pdf_content));
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        doc = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);
        g_object_unref(stream);
        g_bytes_unref(bytes);

        // If stream-based loading isn't available, try from data
        if (doc == nullptr) {
            if (error) {
                g_error_free(error);
                error = nullptr;
            }
            // Write to a temp file
            char tmpname[] = "/tmp/poppler_test_XXXXXX.pdf";
            int fd = mkstemps(tmpname, 4);
            if (fd >= 0) {
                write(fd, pdf_content, strlen(pdf_content));
                close(fd);
                gchar *uri = g_filename_to_uri(tmpname, nullptr, nullptr);
                doc = poppler_document_new_from_file(uri, nullptr, &error);
                g_free(uri);
                unlink(tmpname);
            }
            if (error) {
                g_error_free(error);
            }
        }
    }

    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
    }
};

TEST_F(PopplerPageNewTest_2424, ReturnsNullForNullDocument_2424) {
    PopplerPage *page = _poppler_page_new(nullptr, nullptr, 0);
    EXPECT_EQ(page, nullptr);
}

TEST_F(PopplerPageNewTest_2424, ReturnsNonNullForValidDocument_2424) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }
    PopplerPage *page = _poppler_page_new(doc, nullptr, 0);
    ASSERT_NE(page, nullptr);
    EXPECT_TRUE(POPPLER_IS_PAGE(page));
    g_object_unref(page);
}

TEST_F(PopplerPageNewTest_2424, PageIndexIsSet_2424) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }
    PopplerPage *page = _poppler_page_new(doc, nullptr, 5);
    ASSERT_NE(page, nullptr);
    // poppler_page_get_index returns the index
    int idx = poppler_page_get_index(page);
    EXPECT_EQ(idx, 5);
    g_object_unref(page);
}

TEST_F(PopplerPageNewTest_2424, PageIndexZero_2424) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }
    PopplerPage *page = _poppler_page_new(doc, nullptr, 0);
    ASSERT_NE(page, nullptr);
    EXPECT_EQ(poppler_page_get_index(page), 0);
    g_object_unref(page);
}

TEST_F(PopplerPageNewTest_2424, PageIndexNegative_2424) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }
    PopplerPage *page = _poppler_page_new(doc, nullptr, -1);
    ASSERT_NE(page, nullptr);
    EXPECT_EQ(poppler_page_get_index(page), -1);
    g_object_unref(page);
}

TEST_F(PopplerPageNewTest_2424, DocumentRefIncremented_2424) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }
    // Get initial ref count
    guint initial_ref = G_OBJECT(doc)->ref_count;
    PopplerPage *page = _poppler_page_new(doc, nullptr, 0);
    ASSERT_NE(page, nullptr);
    // Document ref count should have increased
    EXPECT_EQ(G_OBJECT(doc)->ref_count, initial_ref + 1);
    g_object_unref(page);
    // After unref of page, document ref should return to initial (or page destructor unrefs)
}

TEST_F(PopplerPageNewTest_2424, InvalidGObjectNotDocument_2424) {
    // Pass a non-PopplerDocument GObject - should return NULL due to g_return_val_if_fail
    GObject *not_a_doc = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);
    PopplerPage *page = _poppler_page_new((PopplerDocument *)not_a_doc, nullptr, 0);
    EXPECT_EQ(page, nullptr);
    g_object_unref(not_a_doc);
}

TEST_F(PopplerPageNewTest_2424, LargeIndex_2424) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }
    PopplerPage *page = _poppler_page_new(doc, nullptr, 999999);
    ASSERT_NE(page, nullptr);
    EXPECT_EQ(poppler_page_get_index(page), 999999);
    g_object_unref(page);
}
