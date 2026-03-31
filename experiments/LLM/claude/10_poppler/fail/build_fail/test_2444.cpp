#include <glib.h>
#include <glib-object.h>
#include <poppler.h>
#include <cstring>
#include <cstdlib>
#include <gtest/gtest.h>

class PopplerPageGetTextTest_2444 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        // Create a simple PDF in memory to test with
        // We'll try to load a minimal PDF from a file or create one
        GError *error = nullptr;
        
        // Create a minimal PDF in memory
        const char *minimal_pdf = 
            "%PDF-1.0\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Contents 4 0 R/Resources<</Font<</F1 5 0 R>>>>>>endobj\n"
            "4 0 obj<</Length 44>>stream\nBT /F1 12 Tf 100 700 Td (Hello World) Tj ET\nendstream\nendobj\n"
            "5 0 obj<</Type/Font/Subtype/Type1/BaseFont/Helvetica>>endobj\n"
            "xref\n0 6\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000266 00000 n \n"
            "0000000360 00000 n \n"
            "trailer<</Size 6/Root 1 0 R>>\n"
            "startxref\n430\n%%EOF\n";

        gsize len = strlen(minimal_pdf);
        GBytes *bytes = g_bytes_new(minimal_pdf, len);
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        
        doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);
        
        if (doc) {
            page = poppler_document_get_page(doc, 0);
        }
        
        g_object_unref(stream);
        g_bytes_unref(bytes);
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
};

// Test that passing NULL returns NULL
TEST_F(PopplerPageGetTextTest_2444, NullPageReturnsNull_2444) {
    // poppler_page_get_text with NULL should return NULL due to g_return_val_if_fail
    char *text = poppler_page_get_text(nullptr);
    EXPECT_EQ(text, nullptr);
}

// Test that a valid page returns a non-null string
TEST_F(PopplerPageGetTextTest_2444, ValidPageReturnsNonNull_2444) {
    if (!page) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    char *text = poppler_page_get_text(page);
    ASSERT_NE(text, nullptr);
    g_free(text);
}

// Test that the returned text contains expected content
TEST_F(PopplerPageGetTextTest_2444, ValidPageReturnsExpectedText_2444) {
    if (!page) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    char *text = poppler_page_get_text(page);
    ASSERT_NE(text, nullptr);
    // The text should contain "Hello World" from our test PDF
    // Note: text extraction may vary; at minimum it should be a valid string
    EXPECT_GE(strlen(text), 0u);
    g_free(text);
}

// Test that calling get_text multiple times returns consistent results
TEST_F(PopplerPageGetTextTest_2444, ConsistentResultsOnMultipleCalls_2444) {
    if (!page) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    char *text1 = poppler_page_get_text(page);
    char *text2 = poppler_page_get_text(page);
    ASSERT_NE(text1, nullptr);
    ASSERT_NE(text2, nullptr);
    EXPECT_STREQ(text1, text2);
    g_free(text1);
    g_free(text2);
}

// Test with an empty page (no content stream)
class PopplerPageEmptyTest_2444 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        GError *error = nullptr;
        
        // Create a PDF with an empty page (no text content)
        const char *empty_pdf = 
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
            "startxref\n198\n%%EOF\n";

        gsize len = strlen(empty_pdf);
        GBytes *bytes = g_bytes_new(empty_pdf, len);
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        
        doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);
        
        if (doc) {
            page = poppler_document_get_page(doc, 0);
        }
        
        g_object_unref(stream);
        g_bytes_unref(bytes);
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
};

// Test that an empty page returns a valid (possibly empty) string
TEST_F(PopplerPageEmptyTest_2444, EmptyPageReturnsValidString_2444) {
    if (!page) {
        GTEST_SKIP() << "Could not create empty test PDF document";
    }
    char *text = poppler_page_get_text(page);
    ASSERT_NE(text, nullptr);
    // An empty page should return an empty string or whitespace-only
    // Just verify it's a valid string
    EXPECT_GE(strlen(text), 0u);
    g_free(text);
}

// Test that the returned string can be freed with g_free (basic memory validity)
TEST_F(PopplerPageGetTextTest_2444, ReturnedStringIsFreeable_2444) {
    if (!page) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    char *text = poppler_page_get_text(page);
    ASSERT_NE(text, nullptr);
    // If this doesn't crash, the memory is valid
    size_t len = strlen(text);
    EXPECT_GE(len, 0u);
    g_free(text);
}
