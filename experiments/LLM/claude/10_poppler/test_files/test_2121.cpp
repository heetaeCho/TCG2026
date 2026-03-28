#include <glib.h>
#include <cairo.h>
#include <gtest/gtest.h>

// Include poppler glib headers
extern "C" {
#include "poppler-annot.h"
#include "poppler-document.h"
#include "poppler-page.h"
}

class PopplerAnnotStampTest_2121 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need a real PopplerDocument and a stamp annotation to test with
        document_ = nullptr;
        page_ = nullptr;
        annot_stamp_ = nullptr;
    }

    void TearDown() override {
        if (annot_stamp_) {
            g_object_unref(annot_stamp_);
        }
        if (page_) {
            g_object_unref(page_);
        }
        if (document_) {
            g_object_unref(document_);
        }
    }

    PopplerDocument *document_;
    PopplerPage *page_;
    PopplerAnnot *annot_stamp_;
};

// Test that passing NULL for poppler_annot returns FALSE
TEST_F(PopplerAnnotStampTest_2121, NullAnnotReturnsfalse_2121)
{
    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 100, 100);
    GError *error = nullptr;

    // Passing NULL as the annotation should trigger g_return_val_if_fail and return FALSE
    // Note: g_return_val_if_fail will emit a critical warning, so we suppress it
    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_STAMP*");
    gboolean result = poppler_annot_stamp_set_custom_image(nullptr, surface, &error);
    g_test_assert_expected_messages();

    EXPECT_FALSE(result);

    cairo_surface_destroy(surface);
}

// Test that passing a non-stamp annot type returns FALSE via the type check
TEST_F(PopplerAnnotStampTest_2121, NonStampAnnotReturnsFalse_2121)
{
    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 100, 100);
    GError *error = nullptr;

    // Create a non-stamp annotation type (e.g., text annotation) if possible
    // Since we can't easily create one without a document, we test with an invalid cast
    // Using a random GObject that is not a PopplerAnnotStamp
    GObject *fake_obj = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));

    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_STAMP*");
    gboolean result = poppler_annot_stamp_set_custom_image(reinterpret_cast<PopplerAnnotStamp *>(fake_obj), surface, &error);
    g_test_assert_expected_messages();

    EXPECT_FALSE(result);

    g_object_unref(fake_obj);
    cairo_surface_destroy(surface);
}

// Test with a valid stamp annotation and a valid image surface
TEST_F(PopplerAnnotStampTest_2121, ValidStampAndValidImage_2121)
{
    // Load a test PDF that contains at least one page
    GError *error = nullptr;

    // Try to find a test PDF file - adjust path as needed
    const char *test_pdf_path = nullptr;

    // Try several common test file locations
    const char *paths[] = {
        "./test.pdf",
        "../test.pdf",
        "./TestProjects/poppler/test.pdf",
        nullptr
    };

    for (int i = 0; paths[i] != nullptr; i++) {
        if (g_file_test(paths[i], G_FILE_TEST_EXISTS)) {
            test_pdf_path = paths[i];
            break;
        }
    }

    if (!test_pdf_path) {
        // If no test PDF available, create a stamp annotation using poppler API
        // We need a document for this. Skip test if not available.
        GTEST_SKIP() << "No test PDF available to create stamp annotation";
        return;
    }

    gchar *uri = g_filename_to_uri(test_pdf_path, nullptr, &error);
    if (!uri) {
        GTEST_SKIP() << "Could not convert path to URI";
        return;
    }

    document_ = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);
    if (!document_) {
        GTEST_SKIP() << "Could not open test PDF";
        return;
    }

    page_ = poppler_document_get_page(document_, 0);
    if (!page_) {
        GTEST_SKIP() << "Could not get page from PDF";
        return;
    }

    // Create a stamp annotation
    PopplerRectangle rect = { 100.0, 100.0, 200.0, 200.0 };
    PopplerAnnot *annot = poppler_annot_stamp_new(document_, &rect);
    if (!annot) {
        GTEST_SKIP() << "Could not create stamp annotation";
        return;
    }

    annot_stamp_ = annot;

    // Create a valid ARGB32 cairo image surface
    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 50, 50);
    ASSERT_EQ(cairo_surface_status(surface), CAIRO_STATUS_SUCCESS);

    // Draw something on the surface to make it non-empty
    cairo_t *cr = cairo_create(surface);
    cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);
    cairo_paint(cr);
    cairo_destroy(cr);

    error = nullptr;
    gboolean result = poppler_annot_stamp_set_custom_image(
        POPPLER_ANNOT_STAMP(annot_stamp_), surface, &error);

    EXPECT_TRUE(result);
    EXPECT_EQ(error, nullptr);

    cairo_surface_destroy(surface);
}

// Test with a valid stamp annotation and a zero-size image
TEST_F(PopplerAnnotStampTest_2121, ValidStampZeroSizeImage_2121)
{
    GError *error = nullptr;
    const char *test_pdf_path = nullptr;

    const char *paths[] = {
        "./test.pdf",
        "../test.pdf",
        "./TestProjects/poppler/test.pdf",
        nullptr
    };

    for (int i = 0; paths[i] != nullptr; i++) {
        if (g_file_test(paths[i], G_FILE_TEST_EXISTS)) {
            test_pdf_path = paths[i];
            break;
        }
    }

    if (!test_pdf_path) {
        GTEST_SKIP() << "No test PDF available";
        return;
    }

    gchar *uri = g_filename_to_uri(test_pdf_path, nullptr, &error);
    if (!uri) {
        GTEST_SKIP() << "Could not convert path to URI";
        return;
    }

    document_ = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);
    if (!document_) {
        GTEST_SKIP() << "Could not open test PDF";
        return;
    }

    PopplerRectangle rect = { 100.0, 100.0, 200.0, 200.0 };
    PopplerAnnot *annot = poppler_annot_stamp_new(document_, &rect);
    if (!annot) {
        GTEST_SKIP() << "Could not create stamp annotation";
        return;
    }
    annot_stamp_ = annot;

    // Create a zero-size surface - this may fail or return an error
    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 0, 0);

    error = nullptr;
    gboolean result = poppler_annot_stamp_set_custom_image(
        POPPLER_ANNOT_STAMP(annot_stamp_), surface, &error);

    // Zero-size image may or may not be accepted; we just verify no crash
    // and that if it fails, error is set
    if (!result) {
        EXPECT_NE(error, nullptr);
        if (error) {
            g_error_free(error);
        }
    }

    cairo_surface_destroy(surface);
}

// Test with a valid stamp annotation and non-ARGB32 surface format
TEST_F(PopplerAnnotStampTest_2121, ValidStampNonARGB32Surface_2121)
{
    GError *error = nullptr;
    const char *test_pdf_path = nullptr;

    const char *paths[] = {
        "./test.pdf",
        "../test.pdf",
        "./TestProjects/poppler/test.pdf",
        nullptr
    };

    for (int i = 0; paths[i] != nullptr; i++) {
        if (g_file_test(paths[i], G_FILE_TEST_EXISTS)) {
            test_pdf_path = paths[i];
            break;
        }
    }

    if (!test_pdf_path) {
        GTEST_SKIP() << "No test PDF available";
        return;
    }

    gchar *uri = g_filename_to_uri(test_pdf_path, nullptr, &error);
    if (!uri) {
        GTEST_SKIP() << "Could not convert path to URI";
        return;
    }

    document_ = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);
    if (!document_) {
        GTEST_SKIP() << "Could not open test PDF";
        return;
    }

    PopplerRectangle rect = { 100.0, 100.0, 200.0, 200.0 };
    PopplerAnnot *annot = poppler_annot_stamp_new(document_, &rect);
    if (!annot) {
        GTEST_SKIP() << "Could not create stamp annotation";
        return;
    }
    annot_stamp_ = annot;

    // Create a RGB24 surface (not ARGB32)
    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, 50, 50);
    ASSERT_EQ(cairo_surface_status(surface), CAIRO_STATUS_SUCCESS);

    cairo_t *cr = cairo_create(surface);
    cairo_set_source_rgb(cr, 0.0, 1.0, 0.0);
    cairo_paint(cr);
    cairo_destroy(cr);

    error = nullptr;
    gboolean result = poppler_annot_stamp_set_custom_image(
        POPPLER_ANNOT_STAMP(annot_stamp_), surface, &error);

    // RGB24 format may or may not be accepted
    // We verify no crash and consistent error reporting
    if (!result) {
        // If it fails, error should be set
        EXPECT_NE(error, nullptr);
        if (error) {
            g_error_free(error);
        }
    } else {
        EXPECT_EQ(error, nullptr);
    }

    cairo_surface_destroy(surface);
}

// Test passing NULL error pointer (should still work)
TEST_F(PopplerAnnotStampTest_2121, NullErrorPointer_2121)
{
    GError *error = nullptr;
    const char *test_pdf_path = nullptr;

    const char *paths[] = {
        "./test.pdf",
        "../test.pdf",
        "./TestProjects/poppler/test.pdf",
        nullptr
    };

    for (int i = 0; paths[i] != nullptr; i++) {
        if (g_file_test(paths[i], G_FILE_TEST_EXISTS)) {
            test_pdf_path = paths[i];
            break;
        }
    }

    if (!test_pdf_path) {
        GTEST_SKIP() << "No test PDF available";
        return;
    }

    gchar *uri = g_filename_to_uri(test_pdf_path, nullptr, &error);
    if (!uri) {
        GTEST_SKIP() << "Could not convert path to URI";
        return;
    }

    document_ = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);
    if (!document_) {
        GTEST_SKIP() << "Could not open test PDF";
        return;
    }

    PopplerRectangle rect = { 100.0, 100.0, 200.0, 200.0 };
    PopplerAnnot *annot = poppler_annot_stamp_new(document_, &rect);
    if (!annot) {
        GTEST_SKIP() << "Could not create stamp annotation";
        return;
    }
    annot_stamp_ = annot;

    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 50, 50);
    cairo_t *cr = cairo_create(surface);
    cairo_set_source_rgb(cr, 0.0, 0.0, 1.0);
    cairo_paint(cr);
    cairo_destroy(cr);

    // Pass NULL for error pointer - should not crash
    gboolean result = poppler_annot_stamp_set_custom_image(
        POPPLER_ANNOT_STAMP(annot_stamp_), surface, nullptr);

    EXPECT_TRUE(result);

    cairo_surface_destroy(surface);
}

// Test with a non-image cairo surface (e.g., PDF surface)
TEST_F(PopplerAnnotStampTest_2121, NonImageSurface_2121)
{
    GError *error = nullptr;
    const char *test_pdf_path = nullptr;

    const char *paths[] = {
        "./test.pdf",
        "../test.pdf",
        "./TestProjects/poppler/test.pdf",
        nullptr
    };

    for (int i = 0; paths[i] != nullptr; i++) {
        if (g_file_test(paths[i], G_FILE_TEST_EXISTS)) {
            test_pdf_path = paths[i];
            break;
        }
    }

    if (!test_pdf_path) {
        GTEST_SKIP() << "No test PDF available";
        return;
    }

    gchar *uri = g_filename_to_uri(test_pdf_path, nullptr, &error);
    if (!uri) {
        GTEST_SKIP() << "Could not convert path to URI";
        return;
    }

    document_ = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);
    if (!document_) {
        GTEST_SKIP() << "Could not open test PDF";
        return;
    }

    PopplerRectangle rect = { 100.0, 100.0, 200.0, 200.0 };
    PopplerAnnot *annot = poppler_annot_stamp_new(document_, &rect);
    if (!annot) {
        GTEST_SKIP() << "Could not create stamp annotation";
        return;
    }
    annot_stamp_ = annot;

    // Create a non-image surface (recording surface)
    cairo_surface_t *surface = cairo_recording_surface_create(CAIRO_CONTENT_COLOR_ALPHA, nullptr);

    error = nullptr;
    gboolean result = poppler_annot_stamp_set_custom_image(
        POPPLER_ANNOT_STAMP(annot_stamp_), surface, &error);

    // Non-image surfaces should likely fail
    if (!result) {
        EXPECT_NE(error, nullptr);
        if (error) {
            g_error_free(error);
        }
    }

    cairo_surface_destroy(surface);
}

// Test setting custom image twice (overwrite)
TEST_F(PopplerAnnotStampTest_2121, SetCustomImageTwice_2121)
{
    GError *error = nullptr;
    const char *test_pdf_path = nullptr;

    const char *paths[] = {
        "./test.pdf",
        "../test.pdf",
        "./TestProjects/poppler/test.pdf",
        nullptr
    };

    for (int i = 0; paths[i] != nullptr; i++) {
        if (g_file_test(paths[i], G_FILE_TEST_EXISTS)) {
            test_pdf_path = paths[i];
            break;
        }
    }

    if (!test_pdf_path) {
        GTEST_SKIP() << "No test PDF available";
        return;
    }

    gchar *uri = g_filename_to_uri(test_pdf_path, nullptr, &error);
    if (!uri) {
        GTEST_SKIP() << "Could not convert path to URI";
        return;
    }

    document_ = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);
    if (!document_) {
        GTEST_SKIP() << "Could not open test PDF";
        return;
    }

    PopplerRectangle rect = { 100.0, 100.0, 200.0, 200.0 };
    PopplerAnnot *annot = poppler_annot_stamp_new(document_, &rect);
    if (!annot) {
        GTEST_SKIP() << "Could not create stamp annotation";
        return;
    }
    annot_stamp_ = annot;

    // First image
    cairo_surface_t *surface1 = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 50, 50);
    cairo_t *cr1 = cairo_create(surface1);
    cairo_set_source_rgb(cr1, 1.0, 0.0, 0.0);
    cairo_paint(cr1);
    cairo_destroy(cr1);

    error = nullptr;
    gboolean result1 = poppler_annot_stamp_set_custom_image(
        POPPLER_ANNOT_STAMP(annot_stamp_), surface1, &error);
    EXPECT_TRUE(result1);
    EXPECT_EQ(error, nullptr);

    // Second image (overwrite)
    cairo_surface_t *surface2 = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 100, 100);
    cairo_t *cr2 = cairo_create(surface2);
    cairo_set_source_rgb(cr2, 0.0, 1.0, 0.0);
    cairo_paint(cr2);
    cairo_destroy(cr2);

    error = nullptr;
    gboolean result2 = poppler_annot_stamp_set_custom_image(
        POPPLER_ANNOT_STAMP(annot_stamp_), surface2, &error);
    EXPECT_TRUE(result2);
    EXPECT_EQ(error, nullptr);

    cairo_surface_destroy(surface1);
    cairo_surface_destroy(surface2);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
