#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glib.h>
#include <poppler.h>
#include <poppler-document.h>
#include <poppler-page.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>

// Helper to create a simple PDF in memory with given text content
static PopplerDocument *create_pdf_with_text(const char *text_content) {
    // Create a minimal PDF with the given text
    std::string pdf;
    pdf += "%PDF-1.4\n";
    pdf += "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
    pdf += "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
    pdf += "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] ";
    pdf += "/Contents 4 0 R /Resources << /Font << /F1 5 0 R >> >> >>\nendobj\n";
    
    std::string stream = "BT /F1 12 Tf 100 700 Td (";
    stream += text_content;
    stream += ") Tj ET";
    
    char buf[256];
    snprintf(buf, sizeof(buf), "4 0 obj\n<< /Length %d >>\nstream\n", (int)stream.size());
    pdf += buf;
    pdf += stream;
    pdf += "\nendstream\nendobj\n";
    
    pdf += "5 0 obj\n<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\nendobj\n";
    
    std::string xref_pos_str;
    int xref_offset = (int)pdf.size();
    pdf += "xref\n0 6\n";
    pdf += "0000000000 65535 f \n";
    // We need proper offsets, but for poppler loading from memory, let's use a simpler approach
    // Instead, let's write to a temp file and load from there
    
    // Actually, let's just use poppler_document_new_from_data or a temp file approach
    // For reliability, use a temp file with Cairo-generated PDF
    return nullptr; // placeholder
}

class PopplerPageFindTest_2446 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;
    
    void SetUp() override {
        // We'll create documents per test as needed
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
    
    // Helper: create a PDF document from a raw PDF byte string
    PopplerDocument *load_pdf_from_bytes(const char *data, gsize len) {
        GError *error = nullptr;
        GBytes *bytes = g_bytes_new(data, len);
        PopplerDocument *d = poppler_document_new_from_bytes(bytes, nullptr, &error);
        g_bytes_unref(bytes);
        if (error) {
            g_error_free(error);
        }
        return d;
    }
    
    // Create a minimal valid PDF with text content using raw PDF construction
    bool create_simple_pdf_doc(const std::string &text) {
        // Build a minimal valid PDF
        std::string stream_content = "BT /F1 12 Tf 100 700 Td (" + text + ") Tj ET";
        
        // Build objects with correct offsets
        std::string pdf;
        std::vector<int> offsets;
        
        pdf += "%PDF-1.4\n";
        
        // obj 1: catalog
        offsets.push_back((int)pdf.size());
        pdf += "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        
        // obj 2: pages
        offsets.push_back((int)pdf.size());
        pdf += "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        
        // obj 3: page
        offsets.push_back((int)pdf.size());
        pdf += "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
               "/Contents 4 0 R /Resources << /Font << /F1 5 0 R >> >> >>\nendobj\n";
        
        // obj 4: content stream
        offsets.push_back((int)pdf.size());
        char lenbuf[64];
        snprintf(lenbuf, sizeof(lenbuf), "%d", (int)stream_content.size());
        pdf += "4 0 obj\n<< /Length ";
        pdf += lenbuf;
        pdf += " >>\nstream\n";
        pdf += stream_content;
        pdf += "\nendstream\nendobj\n";
        
        // obj 5: font
        offsets.push_back((int)pdf.size());
        pdf += "5 0 obj\n<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\nendobj\n";
        
        int xref_offset = (int)pdf.size();
        pdf += "xref\n";
        pdf += "0 6\n";
        char xbuf[64];
        snprintf(xbuf, sizeof(xbuf), "%010d 65535 f \n", 0);
        pdf += xbuf;
        for (int i = 0; i < 5; i++) {
            snprintf(xbuf, sizeof(xbuf), "%010d 00000 n \n", offsets[i]);
            pdf += xbuf;
        }
        
        pdf += "trailer\n<< /Size 6 /Root 1 0 R >>\n";
        pdf += "startxref\n";
        snprintf(xbuf, sizeof(xbuf), "%d", xref_offset);
        pdf += xbuf;
        pdf += "\n%%EOF\n";
        
        doc = load_pdf_from_bytes(pdf.c_str(), pdf.size());
        if (!doc) return false;
        
        page = poppler_document_get_page(doc, 0);
        return (page != nullptr);
    }
};

// Test: Null page should return NULL (g_return_val_if_fail)
TEST_F(PopplerPageFindTest_2446, NullPageReturnsNull_2446) {
    // Passing NULL as page should trigger g_return_val_if_fail and return NULL
    // Note: This may produce a GLib critical warning
    GList *result = poppler_page_find_text_with_options(nullptr, "test", POPPLER_FIND_DEFAULT);
    EXPECT_EQ(result, nullptr);
}

// Test: Null text should return NULL
TEST_F(PopplerPageFindTest_2446, NullTextReturnsNull_2446) {
    if (!create_simple_pdf_doc("Hello World")) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    GList *result = poppler_page_find_text_with_options(page, nullptr, POPPLER_FIND_DEFAULT);
    EXPECT_EQ(result, nullptr);
}

// Test: Search for text that exists in the page
TEST_F(PopplerPageFindTest_2446, FindExistingText_2446) {
    if (!create_simple_pdf_doc("Hello World")) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    GList *result = poppler_page_find_text_with_options(page, "Hello", POPPLER_FIND_DEFAULT);
    // "Hello" should be found at least once
    EXPECT_NE(result, nullptr);
    if (result) {
        EXPECT_GE((int)g_list_length(result), 1);
        // Each result should be a valid rectangle
        for (GList *l = result; l; l = l->next) {
            PopplerRectangle *rect = (PopplerRectangle *)l->data;
            EXPECT_NE(rect, nullptr);
            // The rectangle should have non-negative dimensions
            EXPECT_LE(rect->x1, rect->x2);
        }
        g_list_free_full(result, (GDestroyNotify)poppler_rectangle_free);
    }
}

// Test: Search for text that does not exist
TEST_F(PopplerPageFindTest_2446, FindNonExistingText_2446) {
    if (!create_simple_pdf_doc("Hello World")) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    GList *result = poppler_page_find_text_with_options(page, "Nonexistent", POPPLER_FIND_DEFAULT);
    EXPECT_EQ(result, nullptr);
}

// Test: Case-insensitive search (default)
TEST_F(PopplerPageFindTest_2446, CaseInsensitiveDefault_2446) {
    if (!create_simple_pdf_doc("Hello World")) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    GList *result = poppler_page_find_text_with_options(page, "hello", POPPLER_FIND_DEFAULT);
    // Default search is case-insensitive, so "hello" should match "Hello"
    EXPECT_NE(result, nullptr);
    if (result) {
        g_list_free_full(result, (GDestroyNotify)poppler_rectangle_free);
    }
}

// Test: Case-sensitive search should not match different case
TEST_F(PopplerPageFindTest_2446, CaseSensitiveNoMatch_2446) {
    if (!create_simple_pdf_doc("Hello World")) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    GList *result = poppler_page_find_text_with_options(page, "hello", POPPLER_FIND_CASE_SENSITIVE);
    // Case-sensitive: "hello" should NOT match "Hello"
    EXPECT_EQ(result, nullptr);
}

// Test: Case-sensitive search should match exact case
TEST_F(PopplerPageFindTest_2446, CaseSensitiveMatch_2446) {
    if (!create_simple_pdf_doc("Hello World")) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    GList *result = poppler_page_find_text_with_options(page, "Hello", POPPLER_FIND_CASE_SENSITIVE);
    EXPECT_NE(result, nullptr);
    if (result) {
        g_list_free_full(result, (GDestroyNotify)poppler_rectangle_free);
    }
}

// Test: Empty search string
TEST_F(PopplerPageFindTest_2446, EmptySearchString_2446) {
    if (!create_simple_pdf_doc("Hello World")) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    GList *result = poppler_page_find_text_with_options(page, "", POPPLER_FIND_DEFAULT);
    // Empty string search should return no matches
    EXPECT_EQ(result, nullptr);
}

// Test: Search with POPPLER_FIND_WHOLE_WORDS_ONLY
TEST_F(PopplerPageFindTest_2446, WholeWordsOnly_2446) {
    if (!create_simple_pdf_doc("Hello World")) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    // "Hell" is a substring but not a whole word
    GList *result = poppler_page_find_text_with_options(page, "Hell", POPPLER_FIND_WHOLE_WORDS_ONLY);
    // "Hell" should NOT match as a whole word in "Hello World"
    EXPECT_EQ(result, nullptr);
}

// Test: Whole word match
TEST_F(PopplerPageFindTest_2446, WholeWordMatch_2446) {
    if (!create_simple_pdf_doc("Hello World")) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    GList *result = poppler_page_find_text_with_options(page, "World", POPPLER_FIND_WHOLE_WORDS_ONLY);
    EXPECT_NE(result, nullptr);
    if (result) {
        g_list_free_full(result, (GDestroyNotify)poppler_rectangle_free);
    }
}

// Test: Search for full text content
TEST_F(PopplerPageFindTest_2446, FindFullText_2446) {
    if (!create_simple_pdf_doc("Hello World")) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    GList *result = poppler_page_find_text_with_options(page, "Hello World", POPPLER_FIND_DEFAULT);
    EXPECT_NE(result, nullptr);
    if (result) {
        EXPECT_EQ((int)g_list_length(result), 1);
        g_list_free_full(result, (GDestroyNotify)poppler_rectangle_free);
    }
}

// Test: Rectangle coordinates are within page bounds
TEST_F(PopplerPageFindTest_2446, RectangleWithinPageBounds_2446) {
    if (!create_simple_pdf_doc("Hello World")) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    double width, height;
    poppler_page_get_size(page, &width, &height);
    
    GList *result = poppler_page_find_text_with_options(page, "Hello", POPPLER_FIND_DEFAULT);
    EXPECT_NE(result, nullptr);
    if (result) {
        for (GList *l = result; l; l = l->next) {
            PopplerRectangle *rect = (PopplerRectangle *)l->data;
            EXPECT_GE(rect->x1, 0.0);
            EXPECT_GE(rect->y1, 0.0);
            EXPECT_LE(rect->x2, width);
            EXPECT_LE(rect->y2, height);
        }
        g_list_free_full(result, (GDestroyNotify)poppler_rectangle_free);
    }
}

// Test: Multiple occurrences of the same text
TEST_F(PopplerPageFindTest_2446, MultipleOccurrences_2446) {
    // PDF with repeated text: "test test test"
    if (!create_simple_pdf_doc("test test test")) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    GList *result = poppler_page_find_text_with_options(page, "test", POPPLER_FIND_DEFAULT);
    EXPECT_NE(result, nullptr);
    if (result) {
        // Should find 3 occurrences
        EXPECT_EQ((int)g_list_length(result), 3);
        g_list_free_full(result, (GDestroyNotify)poppler_rectangle_free);
    }
}

// Test: Backward search finds same results
TEST_F(PopplerPageFindTest_2446, BackwardSearch_2446) {
    if (!create_simple_pdf_doc("Hello World")) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    GList *forward = poppler_page_find_text_with_options(page, "Hello", POPPLER_FIND_DEFAULT);
    GList *backward = poppler_page_find_text_with_options(page, "Hello", POPPLER_FIND_BACKWARDS);
    
    // Both should find the text
    if (forward) {
        EXPECT_NE(backward, nullptr);
        EXPECT_EQ(g_list_length(forward), g_list_length(backward));
        g_list_free_full(forward, (GDestroyNotify)poppler_rectangle_free);
    }
    if (backward) {
        g_list_free_full(backward, (GDestroyNotify)poppler_rectangle_free);
    }
}

// Test: Single character search
TEST_F(PopplerPageFindTest_2446, SingleCharSearch_2446) {
    if (!create_simple_pdf_doc("abcabc")) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    GList *result = poppler_page_find_text_with_options(page, "a", POPPLER_FIND_DEFAULT);
    EXPECT_NE(result, nullptr);
    if (result) {
        EXPECT_GE((int)g_list_length(result), 2);
        g_list_free_full(result, (GDestroyNotify)poppler_rectangle_free);
    }
}

// Test: Multiline flag with simple text (should still work for single-line matches)
TEST_F(PopplerPageFindTest_2446, MultilineFlagSingleLine_2446) {
    if (!create_simple_pdf_doc("Hello World")) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    GList *result = poppler_page_find_text_with_options(page, "Hello", POPPLER_FIND_MULTILINE);
    EXPECT_NE(result, nullptr);
    if (result) {
        g_list_free_full(result, (GDestroyNotify)poppler_rectangle_free);
    }
}

// Test: Combined flags
TEST_F(PopplerPageFindTest_2446, CombinedFlags_2446) {
    if (!create_simple_pdf_doc("Hello World")) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    PopplerFindFlags flags = (PopplerFindFlags)(POPPLER_FIND_CASE_SENSITIVE | POPPLER_FIND_WHOLE_WORDS_ONLY);
    GList *result = poppler_page_find_text_with_options(page, "Hello", flags);
    EXPECT_NE(result, nullptr);
    if (result) {
        g_list_free_full(result, (GDestroyNotify)poppler_rectangle_free);
    }
}

// Test: Search text longer than document content
TEST_F(PopplerPageFindTest_2446, SearchLongerThanContent_2446) {
    if (!create_simple_pdf_doc("Hi")) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    GList *result = poppler_page_find_text_with_options(page, "This is a very long search string that does not exist", POPPLER_FIND_DEFAULT);
    EXPECT_EQ(result, nullptr);
}
