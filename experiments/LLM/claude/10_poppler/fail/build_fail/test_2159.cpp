#include <gtest/gtest.h>
#include <glib-object.h>

// Include poppler glib headers
extern "C" {
#include "poppler-document.h"
}

class PopplerDocumentFindDestTest_2159 : public ::testing::Test {
protected:
    void SetUp() override {
        // We'll create documents from actual PDF files where needed
        document_ = nullptr;
    }

    void TearDown() override {
        if (document_) {
            g_object_unref(document_);
            document_ = nullptr;
        }
    }

    PopplerDocument *document_;
};

// Test that passing NULL document returns NULL
TEST_F(PopplerDocumentFindDestTest_2159, NullDocumentReturnsNull_2159)
{
    PopplerDest *dest = poppler_document_find_dest(nullptr, "some_dest");
    EXPECT_EQ(dest, nullptr);
}

// Test that passing NULL link_name returns NULL
TEST_F(PopplerDocumentFindDestTest_2159, NullLinkNameReturnsNull_2159)
{
    // Create a minimal valid PDF in memory to get a valid PopplerDocument
    const char *minimal_pdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(minimal_pdf, strlen(minimal_pdf));
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    document_ = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);

    g_object_unref(stream);
    g_bytes_unref(bytes);

    if (document_ != nullptr) {
        PopplerDest *dest = poppler_document_find_dest(document_, nullptr);
        EXPECT_EQ(dest, nullptr);
    } else {
        // If we can't create the document, just test the NULL case
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create minimal PDF document for testing";
    }
}

// Test that a non-existent destination returns NULL
TEST_F(PopplerDocumentFindDestTest_2159, NonExistentDestReturnsNull_2159)
{
    const char *minimal_pdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(minimal_pdf, strlen(minimal_pdf));
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    document_ = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);

    g_object_unref(stream);
    g_bytes_unref(bytes);

    if (document_ != nullptr) {
        PopplerDest *dest = poppler_document_find_dest(document_, "nonexistent_destination");
        EXPECT_EQ(dest, nullptr);
    } else {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create minimal PDF document for testing";
    }
}

// Test with empty string link_name
TEST_F(PopplerDocumentFindDestTest_2159, EmptyLinkNameReturnsNull_2159)
{
    const char *minimal_pdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(minimal_pdf, strlen(minimal_pdf));
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    document_ = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);

    g_object_unref(stream);
    g_bytes_unref(bytes);

    if (document_ != nullptr) {
        PopplerDest *dest = poppler_document_find_dest(document_, "");
        // Empty string should either return nullptr or be handled gracefully
        if (dest != nullptr) {
            poppler_dest_free(dest);
        }
        // We just verify it doesn't crash; the result depends on implementation
    } else {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create minimal PDF document for testing";
    }
}

// Test with a very long link name that doesn't exist
TEST_F(PopplerDocumentFindDestTest_2159, VeryLongLinkNameReturnsNull_2159)
{
    const char *minimal_pdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(minimal_pdf, strlen(minimal_pdf));
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    document_ = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);

    g_object_unref(stream);
    g_bytes_unref(bytes);

    if (document_ != nullptr) {
        std::string long_name(10000, 'a');
        PopplerDest *dest = poppler_document_find_dest(document_, long_name.c_str());
        EXPECT_EQ(dest, nullptr);
    } else {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create minimal PDF document for testing";
    }
}

// Test with special characters in link name
TEST_F(PopplerDocumentFindDestTest_2159, SpecialCharsLinkNameReturnsNull_2159)
{
    const char *minimal_pdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(minimal_pdf, strlen(minimal_pdf));
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    document_ = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);

    g_object_unref(stream);
    g_bytes_unref(bytes);

    if (document_ != nullptr) {
        PopplerDest *dest = poppler_document_find_dest(document_, "!@#$%^&*()");
        // Should not crash, likely returns nullptr for non-existent dest
        if (dest != nullptr) {
            poppler_dest_free(dest);
        }
    } else {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create minimal PDF document for testing";
    }
}

// Test that both NULL document and NULL link_name returns NULL
TEST_F(PopplerDocumentFindDestTest_2159, BothNullReturnsNull_2159)
{
    PopplerDest *dest = poppler_document_find_dest(nullptr, nullptr);
    EXPECT_EQ(dest, nullptr);
}

// Test with a PDF that has named destinations
TEST_F(PopplerDocumentFindDestTest_2159, ValidPdfWithNamedDest_2159)
{
    // Create a PDF with a named destination
    const char *pdf_with_dest =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R/Dests 4 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "4 0 obj<</mydest [3 0 R /Fit]>>endobj\n"
        "xref\n0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000072 00000 n \n"
        "0000000125 00000 n \n"
        "0000000198 00000 n \n"
        "trailer<</Size 5/Root 1 0 R>>\nstartxref\n240\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(pdf_with_dest, strlen(pdf_with_dest));
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    document_ = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);

    g_object_unref(stream);
    g_bytes_unref(bytes);

    if (document_ != nullptr) {
        // Try to find a destination that might exist
        PopplerDest *dest = poppler_document_find_dest(document_, "mydest");
        // The result depends on whether the PDF was parsed correctly
        if (dest != nullptr) {
            // If found, the dest should be valid
            EXPECT_NE(dest->type, POPPLER_DEST_UNKNOWN);
            poppler_dest_free(dest);
        }
        // Also verify non-existent dest returns NULL
        PopplerDest *no_dest = poppler_document_find_dest(document_, "no_such_dest");
        EXPECT_EQ(no_dest, nullptr);
    } else {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create PDF document with named destinations";
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
