#include <glib.h>
#include <poppler.h>
#include <cairo.h>
#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <fstream>

class PopplerPageGetThumbnailTest_2438 : public ::testing::Test {
protected:
    void SetUp() override {
        doc_ = nullptr;
        page_ = nullptr;
    }

    void TearDown() override {
        if (page_) {
            g_object_unref(page_);
            page_ = nullptr;
        }
        if (doc_) {
            g_object_unref(doc_);
            doc_ = nullptr;
        }
        // Clean up any temp files
        for (auto &f : temp_files_) {
            g_unlink(f.c_str());
        }
    }

    PopplerDocument *loadDocumentFromFile(const char *path) {
        gchar *uri = g_filename_to_uri(path, nullptr, nullptr);
        if (!uri) return nullptr;
        GError *error = nullptr;
        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }

    // Create a minimal valid PDF without thumbnails
    std::string createMinimalPDF() {
        std::string filename = "/tmp/test_no_thumb_2438.pdf";
        temp_files_.push_back(filename);

        const char *pdf_content =
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
            "endobj\n"
            "xref\n"
            "0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer\n"
            "<< /Size 4 /Root 1 0 R >>\n"
            "startxref\n"
            "190\n"
            "%%EOF\n";

        std::ofstream ofs(filename, std::ios::binary);
        ofs.write(pdf_content, strlen(pdf_content));
        ofs.close();
        return filename;
    }

    PopplerDocument *doc_;
    PopplerPage *page_;
    std::vector<std::string> temp_files_;
};

// Test that passing NULL returns NULL (g_return_val_if_fail check)
TEST_F(PopplerPageGetThumbnailTest_2438, NullPageReturnsNull_2438) {
    // Suppress GLib critical warnings for this test
    g_test_expect_message("poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_PAGE*");
    
    cairo_surface_t *surface = poppler_page_get_thumbnail(nullptr);
    EXPECT_EQ(surface, nullptr);
    
    // Allow the test to proceed even if the message wasn't exactly as expected
    g_test_assert_expected_messages();
}

// Test that a page without a thumbnail returns NULL
TEST_F(PopplerPageGetThumbnailTest_2438, PageWithoutThumbnailReturnsNull_2438) {
    std::string pdf_path = createMinimalPDF();
    doc_ = loadDocumentFromFile(pdf_path.c_str());
    
    if (!doc_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    int n_pages = poppler_document_get_n_pages(doc_);
    ASSERT_GT(n_pages, 0);
    
    page_ = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page_, nullptr);
    
    cairo_surface_t *surface = poppler_page_get_thumbnail(page_);
    EXPECT_EQ(surface, nullptr);
    
    if (surface) {
        cairo_surface_destroy(surface);
    }
}

// Test thumbnail size retrieval for page without thumbnail
TEST_F(PopplerPageGetThumbnailTest_2438, GetThumbnailSizeNoThumb_2438) {
    std::string pdf_path = createMinimalPDF();
    doc_ = loadDocumentFromFile(pdf_path.c_str());
    
    if (!doc_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    page_ = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page_, nullptr);
    
    int width = -1, height = -1;
    gboolean has_thumb = poppler_page_get_thumbnail_size(page_, &width, &height);
    
    // Page without thumbnail should return FALSE
    EXPECT_FALSE(has_thumb);
}

// Test that passing an invalid GObject (not a PopplerPage) returns NULL
TEST_F(PopplerPageGetThumbnailTest_2438, InvalidObjectReturnsNull_2438) {
    // Create a non-PopplerPage GObject
    // Using a GObject that is definitely not a PopplerPage
    g_test_expect_message("poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_PAGE*");
    
    // Cast a random GObject - this should fail the POPPLER_IS_PAGE check
    GObject *obj = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);
    cairo_surface_t *surface = poppler_page_get_thumbnail((PopplerPage *)obj);
    EXPECT_EQ(surface, nullptr);
    
    g_object_unref(obj);
    g_test_assert_expected_messages();
}

// Test with a valid page that the returned surface (if any) is valid cairo surface
TEST_F(PopplerPageGetThumbnailTest_2438, ReturnedSurfaceIsValidIfNotNull_2438) {
    std::string pdf_path = createMinimalPDF();
    doc_ = loadDocumentFromFile(pdf_path.c_str());
    
    if (!doc_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    page_ = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page_, nullptr);
    
    cairo_surface_t *surface = poppler_page_get_thumbnail(page_);
    
    if (surface != nullptr) {
        // If a surface is returned, verify it's a valid cairo surface
        cairo_status_t status = cairo_surface_status(surface);
        EXPECT_EQ(status, CAIRO_STATUS_SUCCESS);
        
        // Check that it has positive dimensions
        int width = cairo_image_surface_get_width(surface);
        int height = cairo_image_surface_get_height(surface);
        EXPECT_GT(width, 0);
        EXPECT_GT(height, 0);
        
        cairo_surface_destroy(surface);
    } else {
        // No thumbnail is also acceptable for a minimal PDF
        SUCCEED();
    }
}

// Test calling get_thumbnail multiple times on same page is consistent
TEST_F(PopplerPageGetThumbnailTest_2438, MultipleCalls_ConsistentResult_2438) {
    std::string pdf_path = createMinimalPDF();
    doc_ = loadDocumentFromFile(pdf_path.c_str());
    
    if (!doc_) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    page_ = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page_, nullptr);
    
    cairo_surface_t *surface1 = poppler_page_get_thumbnail(page_);
    cairo_surface_t *surface2 = poppler_page_get_thumbnail(page_);
    
    // Both calls should return the same result (both NULL or both non-NULL)
    if (surface1 == nullptr) {
        EXPECT_EQ(surface2, nullptr);
    } else {
        EXPECT_NE(surface2, nullptr);
        
        // If both are non-null, they should have the same dimensions
        int w1 = cairo_image_surface_get_width(surface1);
        int h1 = cairo_image_surface_get_height(surface1);
        int w2 = cairo_image_surface_get_width(surface2);
        int h2 = cairo_image_surface_get_height(surface2);
        EXPECT_EQ(w1, w2);
        EXPECT_EQ(h1, h2);
    }
    
    if (surface1) cairo_surface_destroy(surface1);
    if (surface2) cairo_surface_destroy(surface2);
}
