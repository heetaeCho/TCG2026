#include <glib.h>
#include <glib-object.h>
#include <poppler-document.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstring>
#include <string>

class PopplerDocumentResetFormTest_2207 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;

    void SetUp() override {
        // Try to create a document from a simple PDF for testing.
        // We'll use a minimal approach - create from data or file if available.
        document = nullptr;
    }

    void TearDown() override {
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
    }

    PopplerDocument *createDocumentFromFile(const char *path) {
        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(path, nullptr, &error);
        if (!uri) {
            if (error) g_error_free(error);
            return nullptr;
        }
        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        if (error) g_error_free(error);
        return doc;
    }
};

// Test that calling reset_form with NULL document does not crash (g_return_if_fail should guard)
TEST_F(PopplerDocumentResetFormTest_2207, NullDocumentDoesNotCrash_2207)
{
    // This should be a no-op due to g_return_if_fail
    // We suppress the GLib critical warning
    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");
    poppler_document_reset_form(nullptr, nullptr, FALSE);
    g_test_assert_expected_messages();
}

// Test that calling reset_form with NULL fields list and exclude_fields=FALSE does not crash
TEST_F(PopplerDocumentResetFormTest_2207, NullFieldsListDoesNotCrash_2207)
{
    // Create a minimal PDF in memory to have a valid document
    // Using a minimal valid PDF
    const char *minimal_pdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
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
    GBytes *bytes = g_bytes_new_static(minimal_pdf, strlen(minimal_pdf));
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    document = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);

    if (document) {
        // Should not crash - no form in this simple PDF, so it's a no-op
        poppler_document_reset_form(document, nullptr, FALSE);
        poppler_document_reset_form(document, nullptr, TRUE);
    }
    // If document creation failed, that's okay - we just verify no crash

    if (error) g_error_free(error);
    g_object_unref(stream);
    g_bytes_unref(bytes);
}

// Test that calling reset_form with a non-empty fields list does not crash
TEST_F(PopplerDocumentResetFormTest_2207, NonEmptyFieldsListDoesNotCrash_2207)
{
    const char *minimal_pdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
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
    GBytes *bytes = g_bytes_new_static(minimal_pdf, strlen(minimal_pdf));
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    document = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);

    if (document) {
        GList *fields = nullptr;
        fields = g_list_append(fields, (gpointer) "field1");
        fields = g_list_append(fields, (gpointer) "field2");
        fields = g_list_append(fields, (gpointer) "field3");

        // Should not crash even if no form exists
        poppler_document_reset_form(document, fields, FALSE);
        poppler_document_reset_form(document, fields, TRUE);

        g_list_free(fields);
    }

    if (error) g_error_free(error);
    g_object_unref(stream);
    g_bytes_unref(bytes);
}

// Test with exclude_fields TRUE
TEST_F(PopplerDocumentResetFormTest_2207, ExcludeFieldsTrue_2207)
{
    const char *minimal_pdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
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
    GBytes *bytes = g_bytes_new_static(minimal_pdf, strlen(minimal_pdf));
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    document = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);

    if (document) {
        GList *fields = nullptr;
        fields = g_list_append(fields, (gpointer) "excludeMe");

        poppler_document_reset_form(document, fields, TRUE);

        g_list_free(fields);
    }

    if (error) g_error_free(error);
    g_object_unref(stream);
    g_bytes_unref(bytes);
}

// Test with exclude_fields FALSE
TEST_F(PopplerDocumentResetFormTest_2207, ExcludeFieldsFalse_2207)
{
    const char *minimal_pdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
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
    GBytes *bytes = g_bytes_new_static(minimal_pdf, strlen(minimal_pdf));
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    document = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);

    if (document) {
        GList *fields = nullptr;
        fields = g_list_append(fields, (gpointer) "includeMe");

        poppler_document_reset_form(document, fields, FALSE);

        g_list_free(fields);
    }

    if (error) g_error_free(error);
    g_object_unref(stream);
    g_bytes_unref(bytes);
}

// Test with a single field in the list
TEST_F(PopplerDocumentResetFormTest_2207, SingleFieldInList_2207)
{
    const char *minimal_pdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
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
    GBytes *bytes = g_bytes_new_static(minimal_pdf, strlen(minimal_pdf));
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    document = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);

    if (document) {
        GList *fields = nullptr;
        fields = g_list_append(fields, (gpointer) "singleField");

        poppler_document_reset_form(document, fields, FALSE);

        g_list_free(fields);
    }

    if (error) g_error_free(error);
    g_object_unref(stream);
    g_bytes_unref(bytes);
}

// Test with empty string field names
TEST_F(PopplerDocumentResetFormTest_2207, EmptyStringFieldNames_2207)
{
    const char *minimal_pdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
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
    GBytes *bytes = g_bytes_new_static(minimal_pdf, strlen(minimal_pdf));
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    document = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);

    if (document) {
        GList *fields = nullptr;
        fields = g_list_append(fields, (gpointer) "");

        poppler_document_reset_form(document, fields, FALSE);

        g_list_free(fields);
    }

    if (error) g_error_free(error);
    g_object_unref(stream);
    g_bytes_unref(bytes);
}

// Test calling reset_form multiple times consecutively
TEST_F(PopplerDocumentResetFormTest_2207, MultipleResetCalls_2207)
{
    const char *minimal_pdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
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
    GBytes *bytes = g_bytes_new_static(minimal_pdf, strlen(minimal_pdf));
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    document = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);

    if (document) {
        // Call reset multiple times - should be safe
        poppler_document_reset_form(document, nullptr, FALSE);
        poppler_document_reset_form(document, nullptr, TRUE);
        poppler_document_reset_form(document, nullptr, FALSE);
    }

    if (error) g_error_free(error);
    g_object_unref(stream);
    g_bytes_unref(bytes);
}

// Test with a PDF that has an AcroForm (form fields)
TEST_F(PopplerDocumentResetFormTest_2207, PDFWithAcroForm_2207)
{
    // A minimal PDF with an AcroForm containing a text field
    const char *pdf_with_form =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R/AcroForm<</Fields[4 0 R]>>>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Annots[4 0 R]>>endobj\n"
        "4 0 obj<</Type/Annot/Subtype/Widget/FT/Tx/T(testField)/V(hello)/Rect[100 700 300 720]/P 3 0 R>>endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000080 00000 n \n"
        "0000000131 00000 n \n"
        "0000000228 00000 n \n"
        "trailer<</Size 5/Root 1 0 R>>\n"
        "startxref\n"
        "368\n"
        "%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(pdf_with_form, strlen(pdf_with_form));
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    document = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);

    if (document) {
        // Reset all fields
        poppler_document_reset_form(document, nullptr, FALSE);

        // Reset specific field
        GList *fields = nullptr;
        fields = g_list_append(fields, (gpointer) "testField");
        poppler_document_reset_form(document, fields, FALSE);
        g_list_free(fields);

        // Reset excluding specific field
        fields = nullptr;
        fields = g_list_append(fields, (gpointer) "testField");
        poppler_document_reset_form(document, fields, TRUE);
        g_list_free(fields);
    }

    if (error) g_error_free(error);
    g_object_unref(stream);
    g_bytes_unref(bytes);
}

// Test with many fields in the list
TEST_F(PopplerDocumentResetFormTest_2207, ManyFieldsInList_2207)
{
    const char *minimal_pdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
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
    GBytes *bytes = g_bytes_new_static(minimal_pdf, strlen(minimal_pdf));
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    document = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);

    if (document) {
        GList *fields = nullptr;
        // Add many field names
        for (int i = 0; i < 100; i++) {
            fields = g_list_append(fields, (gpointer) "fieldName");
        }

        poppler_document_reset_form(document, fields, FALSE);
        poppler_document_reset_form(document, fields, TRUE);

        g_list_free(fields);
    }

    if (error) g_error_free(error);
    g_object_unref(stream);
    g_bytes_unref(bytes);
}
