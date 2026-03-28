#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary headers
#include "poppler-annot.h"
#include "poppler-private.h"
#include "poppler-page.h"
#include "PDFRectangle.h"

// Since we're testing a GLib/GObject-based API, we need to work with the
// poppler GLib types. We'll create helper utilities to set up test fixtures.

class PopplerAnnotRectangleTest_2073 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize GLib type system if needed
    }

    void TearDown() override {
    }
};

// Helper to create a PopplerAnnot with a given annotation rectangle
// Note: Since we treat the implementation as a black box, we need to use
// the public API to create annotations. We'll use poppler's document loading
// to create real annotation objects for testing.

// Since creating real PopplerAnnot objects requires a PDF document with
// annotations, and we need to test the rectangle function, we'll create
// a minimal PDF in memory for testing purposes.

#include <poppler.h>
#include <glib.h>
#include <cstring>
#include <cstdio>

// Helper function to create a minimal PDF with an annotation
static GBytes *create_pdf_with_annot(double x1, double y1, double x2, double y2) {
    // Create a minimal PDF with a square annotation at the given coordinates
    char pdf[4096];
    int len = snprintf(pdf, sizeof(pdf),
        "%%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Annots [4 0 R] >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Type /Annot /Subtype /Square /Rect [%g %g %g %g] "
        "/C [1 0 0] >>\n"
        "endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000226 00000 n \n"
        "trailer\n"
        "<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n"
        "350\n"
        "%%%%EOF\n",
        x1, y1, x2, y2);
    return g_bytes_new(pdf, len);
}

static PopplerDocument *load_pdf_from_bytes(GBytes *bytes) {
    GError *error = nullptr;
    gsize size;
    const guchar *data = (const guchar *)g_bytes_get_data(bytes, &size);
    
    // Write to a temp file since poppler_document_new_from_data might not be available
    char tmpfile[] = "/tmp/poppler_test_XXXXXX";
    int fd = mkstemp(tmpfile);
    if (fd < 0) return nullptr;
    write(fd, data, size);
    close(fd);
    
    gchar *uri = g_filename_to_uri(tmpfile, nullptr, nullptr);
    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);
    unlink(tmpfile);
    
    if (error) {
        g_error_free(error);
        return nullptr;
    }
    return doc;
}

// Test: Normal operation - get rectangle of an annotation
TEST_F(PopplerAnnotRectangleTest_2073, NormalRectangle_2073) {
    GBytes *bytes = create_pdf_with_annot(100.0, 200.0, 300.0, 400.0);
    PopplerDocument *doc = load_pdf_from_bytes(bytes);
    if (!doc) {
        g_bytes_unref(bytes);
        GTEST_SKIP() << "Could not load test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);
    
    GList *annot_mappings = poppler_page_get_annot_mapping(page);
    if (annot_mappings) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)annot_mappings->data;
        PopplerAnnot *annot = mapping->annot;
        
        PopplerRectangle rect;
        poppler_annot_get_rectangle(annot, &rect);
        
        // The annotation rect should be retrievable (exact values depend on crop box)
        // For a page with MediaBox [0 0 612 792] and no CropBox, crop_box should be zero
        EXPECT_DOUBLE_EQ(rect.x1, 100.0);
        EXPECT_DOUBLE_EQ(rect.y1, 200.0);
        EXPECT_DOUBLE_EQ(rect.x2, 300.0);
        EXPECT_DOUBLE_EQ(rect.y2, 400.0);
        
        poppler_page_free_annot_mapping(annot_mappings);
    }
    
    g_object_unref(page);
    g_object_unref(doc);
    g_bytes_unref(bytes);
}

// Test: Zero rectangle coordinates
TEST_F(PopplerAnnotRectangleTest_2073, ZeroRectangle_2073) {
    GBytes *bytes = create_pdf_with_annot(0.0, 0.0, 0.0, 0.0);
    PopplerDocument *doc = load_pdf_from_bytes(bytes);
    if (!doc) {
        g_bytes_unref(bytes);
        GTEST_SKIP() << "Could not load test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);
    
    GList *annot_mappings = poppler_page_get_annot_mapping(page);
    if (annot_mappings) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)annot_mappings->data;
        PopplerAnnot *annot = mapping->annot;
        
        PopplerRectangle rect;
        poppler_annot_get_rectangle(annot, &rect);
        
        EXPECT_DOUBLE_EQ(rect.x1, 0.0);
        EXPECT_DOUBLE_EQ(rect.y1, 0.0);
        EXPECT_DOUBLE_EQ(rect.x2, 0.0);
        EXPECT_DOUBLE_EQ(rect.y2, 0.0);
        
        poppler_page_free_annot_mapping(annot_mappings);
    }
    
    g_object_unref(page);
    g_object_unref(doc);
    g_bytes_unref(bytes);
}

// Test: Negative coordinate values in rectangle
TEST_F(PopplerAnnotRectangleTest_2073, NegativeCoordinates_2073) {
    GBytes *bytes = create_pdf_with_annot(-50.0, -100.0, 50.0, 100.0);
    PopplerDocument *doc = load_pdf_from_bytes(bytes);
    if (!doc) {
        g_bytes_unref(bytes);
        GTEST_SKIP() << "Could not load test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);
    
    GList *annot_mappings = poppler_page_get_annot_mapping(page);
    if (annot_mappings) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)annot_mappings->data;
        PopplerAnnot *annot = mapping->annot;
        
        PopplerRectangle rect;
        poppler_annot_get_rectangle(annot, &rect);
        
        // With no crop box offset, values should match the annotation rect
        EXPECT_DOUBLE_EQ(rect.x1, -50.0);
        EXPECT_DOUBLE_EQ(rect.y1, -100.0);
        EXPECT_DOUBLE_EQ(rect.x2, 50.0);
        EXPECT_DOUBLE_EQ(rect.y2, 100.0);
        
        poppler_page_free_annot_mapping(annot_mappings);
    }
    
    g_object_unref(page);
    g_object_unref(doc);
    g_bytes_unref(bytes);
}

// Test: Large coordinate values
TEST_F(PopplerAnnotRectangleTest_2073, LargeCoordinates_2073) {
    GBytes *bytes = create_pdf_with_annot(10000.0, 20000.0, 30000.0, 40000.0);
    PopplerDocument *doc = load_pdf_from_bytes(bytes);
    if (!doc) {
        g_bytes_unref(bytes);
        GTEST_SKIP() << "Could not load test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);
    
    GList *annot_mappings = poppler_page_get_annot_mapping(page);
    if (annot_mappings) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)annot_mappings->data;
        PopplerAnnot *annot = mapping->annot;
        
        PopplerRectangle rect;
        poppler_annot_get_rectangle(annot, &rect);
        
        EXPECT_DOUBLE_EQ(rect.x1, 10000.0);
        EXPECT_DOUBLE_EQ(rect.y1, 20000.0);
        EXPECT_DOUBLE_EQ(rect.x2, 30000.0);
        EXPECT_DOUBLE_EQ(rect.y2, 40000.0);
        
        poppler_page_free_annot_mapping(annot_mappings);
    }
    
    g_object_unref(page);
    g_object_unref(doc);
    g_bytes_unref(bytes);
}

// Test: Null poppler_rect should not crash (g_return_if_fail guard)
TEST_F(PopplerAnnotRectangleTest_2073, NullRectParameter_2073) {
    GBytes *bytes = create_pdf_with_annot(100.0, 200.0, 300.0, 400.0);
    PopplerDocument *doc = load_pdf_from_bytes(bytes);
    if (!doc) {
        g_bytes_unref(bytes);
        GTEST_SKIP() << "Could not load test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);
    
    GList *annot_mappings = poppler_page_get_annot_mapping(page);
    if (annot_mappings) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)annot_mappings->data;
        PopplerAnnot *annot = mapping->annot;
        
        // This should not crash due to g_return_if_fail
        poppler_annot_get_rectangle(annot, nullptr);
        
        poppler_page_free_annot_mapping(annot_mappings);
    }
    
    g_object_unref(page);
    g_object_unref(doc);
    g_bytes_unref(bytes);
}

// Test: Null annot parameter should not crash (g_return_if_fail guard)
TEST_F(PopplerAnnotRectangleTest_2073, NullAnnotParameter_2073) {
    PopplerRectangle rect;
    // This should not crash due to g_return_if_fail(POPPLER_IS_ANNOT)
    poppler_annot_get_rectangle(nullptr, &rect);
    // If we reach here, the guard worked
    SUCCEED();
}

// Test: Fractional coordinate values
TEST_F(PopplerAnnotRectangleTest_2073, FractionalCoordinates_2073) {
    GBytes *bytes = create_pdf_with_annot(10.5, 20.75, 30.25, 40.125);
    PopplerDocument *doc = load_pdf_from_bytes(bytes);
    if (!doc) {
        g_bytes_unref(bytes);
        GTEST_SKIP() << "Could not load test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);
    
    GList *annot_mappings = poppler_page_get_annot_mapping(page);
    if (annot_mappings) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)annot_mappings->data;
        PopplerAnnot *annot = mapping->annot;
        
        PopplerRectangle rect;
        poppler_annot_get_rectangle(annot, &rect);
        
        EXPECT_NEAR(rect.x1, 10.5, 0.01);
        EXPECT_NEAR(rect.y1, 20.75, 0.01);
        EXPECT_NEAR(rect.x2, 30.25, 0.01);
        EXPECT_NEAR(rect.y2, 40.125, 0.01);
        
        poppler_page_free_annot_mapping(annot_mappings);
    }
    
    g_object_unref(page);
    g_object_unref(doc);
    g_bytes_unref(bytes);
}

// Test: Rectangle with equal x1,x2 and y1,y2 (degenerate/point rectangle)
TEST_F(PopplerAnnotRectangleTest_2073, DegeneratePointRectangle_2073) {
    GBytes *bytes = create_pdf_with_annot(150.0, 250.0, 150.0, 250.0);
    PopplerDocument *doc = load_pdf_from_bytes(bytes);
    if (!doc) {
        g_bytes_unref(bytes);
        GTEST_SKIP() << "Could not load test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);
    
    GList *annot_mappings = poppler_page_get_annot_mapping(page);
    if (annot_mappings) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)annot_mappings->data;
        PopplerAnnot *annot = mapping->annot;
        
        PopplerRectangle rect;
        poppler_annot_get_rectangle(annot, &rect);
        
        EXPECT_DOUBLE_EQ(rect.x1, 150.0);
        EXPECT_DOUBLE_EQ(rect.y1, 250.0);
        EXPECT_DOUBLE_EQ(rect.x2, 150.0);
        EXPECT_DOUBLE_EQ(rect.y2, 250.0);
        
        poppler_page_free_annot_mapping(annot_mappings);
    }
    
    g_object_unref(page);
    g_object_unref(doc);
    g_bytes_unref(bytes);
}

// Test with CropBox to verify crop box subtraction
TEST_F(PopplerAnnotRectangleTest_2073, WithCropBox_2073) {
    // Create a PDF with a CropBox that offsets the coordinates
    const char *pdf_str =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/CropBox [50 50 562 742] "
        "/Annots [4 0 R] >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Type /Annot /Subtype /Square /Rect [100 200 300 400] "
        "/C [1 0 0] >>\n"
        "endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000270 00000 n \n"
        "trailer\n"
        "<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n"
        "400\n"
        "%%EOF\n";
    
    char tmpfile[] = "/tmp/poppler_crop_test_XXXXXX";
    int fd = mkstemp(tmpfile);
    if (fd < 0) {
        GTEST_SKIP() << "Could not create temp file";
    }
    write(fd, pdf_str, strlen(pdf_str));
    close(fd);
    
    gchar *uri = g_filename_to_uri(tmpfile, nullptr, nullptr);
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);
    unlink(tmpfile);
    
    if (!doc) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not load test PDF with crop box";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);
    
    GList *annot_mappings = poppler_page_get_annot_mapping(page);
    if (annot_mappings) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)annot_mappings->data;
        PopplerAnnot *annot = mapping->annot;
        
        PopplerRectangle rect;
        poppler_annot_get_rectangle(annot, &rect);
        
        // With CropBox [50 50 ...], the x values should be offset by 50
        // and y values by 50
        // rect.x1 = 100 - 50 = 50
        // rect.y1 = 200 - 50 = 150
        // rect.x2 = 300 - 50 = 250
        // rect.y2 = 400 - 50 = 350
        EXPECT_NEAR(rect.x1, 50.0, 1.0);
        EXPECT_NEAR(rect.y1, 150.0, 1.0);
        EXPECT_NEAR(rect.x2, 250.0, 1.0);
        EXPECT_NEAR(rect.y2, 350.0, 1.0);
        
        poppler_page_free_annot_mapping(annot_mappings);
    }
    
    g_object_unref(page);
    g_object_unref(doc);
}

// Test: calling get_rectangle multiple times returns consistent results
TEST_F(PopplerAnnotRectangleTest_2073, ConsistentResults_2073) {
    GBytes *bytes = create_pdf_with_annot(72.0, 144.0, 288.0, 576.0);
    PopplerDocument *doc = load_pdf_from_bytes(bytes);
    if (!doc) {
        g_bytes_unref(bytes);
        GTEST_SKIP() << "Could not load test PDF";
    }
    
    PopplerPage *page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);
    
    GList *annot_mappings = poppler_page_get_annot_mapping(page);
    if (annot_mappings) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)annot_mappings->data;
        PopplerAnnot *annot = mapping->annot;
        
        PopplerRectangle rect1, rect2;
        poppler_annot_get_rectangle(annot, &rect1);
        poppler_annot_get_rectangle(annot, &rect2);
        
        EXPECT_DOUBLE_EQ(rect1.x1, rect2.x1);
        EXPECT_DOUBLE_EQ(rect1.y1, rect2.y1);
        EXPECT_DOUBLE_EQ(rect1.x2, rect2.x2);
        EXPECT_DOUBLE_EQ(rect1.y2, rect2.y2);
        
        poppler_page_free_annot_mapping(annot_mappings);
    }
    
    g_object_unref(page);
    g_object_unref(doc);
    g_bytes_unref(bytes);
}
