#include <glib.h>
#include <poppler.h>
#include <glib/poppler-page.h>
#include <glib/poppler-annot.h>
#include <cstdio>
#include <cstring>
#include <gtest/gtest.h>

// Helper to create a minimal valid PDF in memory
static PopplerDocument *create_test_document_with_annot()
{
    // Create a minimal PDF with one page
    const char *pdf_content =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
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

    GError *error = nullptr;
    gsize len = strlen(pdf_content);
    GBytes *bytes = g_bytes_new(pdf_content, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
    
    PopplerDocument *doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);
    
    g_object_unref(stream);
    g_bytes_unref(bytes);
    
    if (!doc && error) {
        g_error_free(error);
    }
    
    return doc;
}

static PopplerDocument *create_test_document_from_file()
{
    // Try to create a simple PDF using GLib's temp file facilities
    const char *pdf_content =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000063 00000 n \n"
        "0000000120 00000 n \n"
        "trailer << /Size 4 /Root 1 0 R >>\n"
        "startxref\n"
        "200\n"
        "%%EOF\n";

    char *tmpfile = nullptr;
    GError *error = nullptr;
    int fd = g_file_open_tmp("test_pdf_XXXXXX.pdf", &tmpfile, &error);
    if (fd < 0) {
        if (error) g_error_free(error);
        return nullptr;
    }

    write(fd, pdf_content, strlen(pdf_content));
    close(fd);

    gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
    if (!uri) {
        g_free(tmpfile);
        if (error) g_error_free(error);
        return nullptr;
    }

    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
    
    g_free(uri);
    unlink(tmpfile);
    g_free(tmpfile);
    
    if (!doc && error) {
        g_error_free(error);
    }
    
    return doc;
}

class PopplerPageRemoveAnnotTest_2462 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override
    {
        doc = create_test_document_from_file();
        if (doc) {
            page = poppler_document_get_page(doc, 0);
        }
    }

    void TearDown() override
    {
        if (page) {
            g_object_unref(page);
            page = nullptr;
        }
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
    }
};

// Test that passing NULL page does not crash (g_return_if_fail handles it)
TEST_F(PopplerPageRemoveAnnotTest_2462, NullPageDoesNotCrash_2462)
{
    if (!doc || !page) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    // Create a text annotation to use
    PopplerRectangle rect = {100.0, 100.0, 200.0, 200.0};
    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot *>(
        poppler_annot_text_new(doc, &rect));
    
    ASSERT_NE(annot, nullptr);
    
    // Should not crash - g_return_if_fail will just return
    poppler_page_remove_annot(nullptr, annot);
    
    g_object_unref(annot);
}

// Test that passing NULL annot does not crash (g_return_if_fail handles it)
TEST_F(PopplerPageRemoveAnnotTest_2462, NullAnnotDoesNotCrash_2462)
{
    if (!doc || !page) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    // Should not crash - g_return_if_fail will just return
    poppler_page_remove_annot(page, nullptr);
}

// Test that passing both NULL does not crash
TEST_F(PopplerPageRemoveAnnotTest_2462, BothNullDoesNotCrash_2462)
{
    // Should not crash - g_return_if_fail will just return on first check
    poppler_page_remove_annot(nullptr, nullptr);
}

// Test adding and then removing an annotation
TEST_F(PopplerPageRemoveAnnotTest_2462, AddAndRemoveAnnot_2462)
{
    if (!doc || !page) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerRectangle rect = {100.0, 100.0, 200.0, 200.0};
    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot *>(
        poppler_annot_text_new(doc, &rect));
    
    ASSERT_NE(annot, nullptr);
    
    // Add the annotation first
    poppler_page_add_annot(page, annot);
    
    // Get the annotation mapping list - should have at least one
    GList *annot_mappings = poppler_page_get_annot_mapping(page);
    guint count_before = g_list_length(annot_mappings);
    poppler_page_free_annot_mapping(annot_mappings);
    
    EXPECT_GE(count_before, 1u);
    
    // Now remove it
    poppler_page_remove_annot(page, annot);
    
    // After removal, count should be one less
    GList *annot_mappings_after = poppler_page_get_annot_mapping(page);
    guint count_after = g_list_length(annot_mappings_after);
    poppler_page_free_annot_mapping(annot_mappings_after);
    
    EXPECT_EQ(count_after, count_before - 1);
    
    g_object_unref(annot);
}

// Test removing annotation from a page that initially has no annotations
TEST_F(PopplerPageRemoveAnnotTest_2462, RemoveAnnotFromEmptyPage_2462)
{
    if (!doc || !page) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    // Get initial count
    GList *annot_mappings = poppler_page_get_annot_mapping(page);
    guint initial_count = g_list_length(annot_mappings);
    poppler_page_free_annot_mapping(annot_mappings);
    
    // Create an annotation but don't add it to the page
    PopplerRectangle rect = {50.0, 50.0, 150.0, 150.0};
    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot *>(
        poppler_annot_text_new(doc, &rect));
    
    ASSERT_NE(annot, nullptr);
    
    // Try removing an annotation that was never added - this tests boundary behavior
    // The underlying implementation should handle this gracefully
    poppler_page_remove_annot(page, annot);
    
    // Count should remain the same
    GList *annot_mappings_after = poppler_page_get_annot_mapping(page);
    guint count_after = g_list_length(annot_mappings_after);
    poppler_page_free_annot_mapping(annot_mappings_after);
    
    EXPECT_EQ(count_after, initial_count);
    
    g_object_unref(annot);
}

// Test adding multiple annotations and removing one
TEST_F(PopplerPageRemoveAnnotTest_2462, RemoveOneOfMultipleAnnots_2462)
{
    if (!doc || !page) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerRectangle rect1 = {10.0, 10.0, 50.0, 50.0};
    PopplerRectangle rect2 = {60.0, 60.0, 100.0, 100.0};
    PopplerRectangle rect3 = {110.0, 110.0, 150.0, 150.0};
    
    PopplerAnnot *annot1 = reinterpret_cast<PopplerAnnot *>(
        poppler_annot_text_new(doc, &rect1));
    PopplerAnnot *annot2 = reinterpret_cast<PopplerAnnot *>(
        poppler_annot_text_new(doc, &rect2));
    PopplerAnnot *annot3 = reinterpret_cast<PopplerAnnot *>(
        poppler_annot_text_new(doc, &rect3));
    
    ASSERT_NE(annot1, nullptr);
    ASSERT_NE(annot2, nullptr);
    ASSERT_NE(annot3, nullptr);
    
    poppler_page_add_annot(page, annot1);
    poppler_page_add_annot(page, annot2);
    poppler_page_add_annot(page, annot3);
    
    GList *mappings = poppler_page_get_annot_mapping(page);
    guint count_after_add = g_list_length(mappings);
    poppler_page_free_annot_mapping(mappings);
    
    EXPECT_GE(count_after_add, 3u);
    
    // Remove the middle annotation
    poppler_page_remove_annot(page, annot2);
    
    GList *mappings_after = poppler_page_get_annot_mapping(page);
    guint count_after_remove = g_list_length(mappings_after);
    poppler_page_free_annot_mapping(mappings_after);
    
    EXPECT_EQ(count_after_remove, count_after_add - 1);
    
    g_object_unref(annot1);
    g_object_unref(annot2);
    g_object_unref(annot3);
}

// Test removing the same annotation twice
TEST_F(PopplerPageRemoveAnnotTest_2462, RemoveSameAnnotTwice_2462)
{
    if (!doc || !page) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    PopplerRectangle rect = {100.0, 100.0, 200.0, 200.0};
    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot *>(
        poppler_annot_text_new(doc, &rect));
    
    ASSERT_NE(annot, nullptr);
    
    poppler_page_add_annot(page, annot);
    
    GList *mappings = poppler_page_get_annot_mapping(page);
    guint count_before = g_list_length(mappings);
    poppler_page_free_annot_mapping(mappings);
    
    // Remove once
    poppler_page_remove_annot(page, annot);
    
    GList *mappings_after1 = poppler_page_get_annot_mapping(page);
    guint count_after1 = g_list_length(mappings_after1);
    poppler_page_free_annot_mapping(mappings_after1);
    
    EXPECT_EQ(count_after1, count_before - 1);
    
    // Remove again - should handle gracefully (annotation already removed)
    poppler_page_remove_annot(page, annot);
    
    GList *mappings_after2 = poppler_page_get_annot_mapping(page);
    guint count_after2 = g_list_length(mappings_after2);
    poppler_page_free_annot_mapping(mappings_after2);
    
    // Count should not decrease further
    EXPECT_EQ(count_after2, count_after1);
    
    g_object_unref(annot);
}

// Test passing invalid GObject types (not PopplerPage or PopplerAnnot)
TEST_F(PopplerPageRemoveAnnotTest_2462, InvalidGObjectTypeDoesNotCrash_2462)
{
    if (!doc || !page) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    // Pass a GObject that is not a PopplerAnnot - g_return_if_fail should catch this
    // Using the document as the annot parameter (wrong type)
    poppler_page_remove_annot(page, reinterpret_cast<PopplerAnnot *>(doc));
    
    // If we get here, the g_return_if_fail caught the invalid type
    SUCCEED();
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
