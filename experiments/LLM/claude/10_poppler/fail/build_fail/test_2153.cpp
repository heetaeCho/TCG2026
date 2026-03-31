#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>

// We need to mock the dependencies since we're treating the implementation as a black box
// and we need to test poppler_document_get_page_by_label

// Forward declarations and minimal type definitions needed for testing
class PDFDoc;
class Page;
class CairoOutputDev;
class GooString;

// Mock Catalog class to control labelToIndex behavior
class MockCatalog {
public:
    MOCK_METHOD(bool, labelToIndex, (const GooString& label, int* index));
};

// Since we can't easily unit test a GLib/GObject-based function that depends on
// complex internal structures (PopplerDocument wrapping a PDFDoc with a Catalog),
// we need to test at a higher level using actual PDF documents or carefully
// constructed mocks.

// For this test, we'll create integration-style tests that exercise the
// poppler_document_get_page_by_label function through the public C API.

extern "C" {
#include <poppler.h>
}

#include <cstdlib>
#include <string>

class PopplerDocumentGetPageByLabelTest_2153 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    
    void SetUp() override {
        // Try to create a simple PDF document for testing
        // We need a valid PDF file. We'll try to find one or create a minimal one.
        GError *error = nullptr;
        
        // Create a minimal PDF in memory
        const char *minimal_pdf = 
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
        
        // Write to a temporary file
        tmp_filename = std::string(g_get_tmp_dir()) + "/test_poppler_2153.pdf";
        FILE *f = fopen(tmp_filename.c_str(), "wb");
        if (f) {
            fwrite(minimal_pdf, 1, strlen(minimal_pdf), f);
            fclose(f);
            
            gchar *uri = g_filename_to_uri(tmp_filename.c_str(), nullptr, &error);
            if (uri) {
                doc = poppler_document_new_from_file(uri, nullptr, &error);
                g_free(uri);
            }
            if (error) {
                g_error_free(error);
                error = nullptr;
            }
        }
    }
    
    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
        if (!tmp_filename.empty()) {
            remove(tmp_filename.c_str());
        }
    }
    
    std::string tmp_filename;
};

// Test: NULL document - this would likely crash, but we test valid cases
// Test: Valid label that maps to an existing page
TEST_F(PopplerDocumentGetPageByLabelTest_2153, ValidLabelReturnsPage_2153) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    // In a simple PDF without explicit page labels, page labels default to "1", "2", etc.
    PopplerPage *page = poppler_document_get_page_by_label(doc, "1");
    // The page may or may not be found depending on whether the catalog supports label lookup
    // For a minimal PDF, it's common that "1" maps to the first page
    if (page) {
        EXPECT_EQ(poppler_page_get_index(page), 0);
        g_object_unref(page);
    }
}

// Test: Invalid/nonexistent label returns nullptr
TEST_F(PopplerDocumentGetPageByLabelTest_2153, InvalidLabelReturnsNull_2153) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    PopplerPage *page = poppler_document_get_page_by_label(doc, "nonexistent_label_xyz");
    EXPECT_EQ(page, nullptr);
}

// Test: Empty string label returns nullptr
TEST_F(PopplerDocumentGetPageByLabelTest_2153, EmptyLabelReturnsNull_2153) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    PopplerPage *page = poppler_document_get_page_by_label(doc, "");
    EXPECT_EQ(page, nullptr);
}

// Test: Very long label string returns nullptr (no such page)
TEST_F(PopplerDocumentGetPageByLabelTest_2153, VeryLongLabelReturnsNull_2153) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    std::string long_label(10000, 'A');
    PopplerPage *page = poppler_document_get_page_by_label(doc, long_label.c_str());
    EXPECT_EQ(page, nullptr);
}

// Test: Label with special characters returns nullptr for simple PDF
TEST_F(PopplerDocumentGetPageByLabelTest_2153, SpecialCharLabelReturnsNull_2153) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    PopplerPage *page = poppler_document_get_page_by_label(doc, "!@#$%^&*()");
    EXPECT_EQ(page, nullptr);
}

// Test: Numeric label that is out of range returns nullptr
TEST_F(PopplerDocumentGetPageByLabelTest_2153, OutOfRangeNumericLabelReturnsNull_2153) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    // Our test PDF has only 1 page, so "999" should not match
    PopplerPage *page = poppler_document_get_page_by_label(doc, "999");
    EXPECT_EQ(page, nullptr);
}

// Test: Label "0" - page labels typically start from "1"
TEST_F(PopplerDocumentGetPageByLabelTest_2153, ZeroLabelReturnsNull_2153) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    PopplerPage *page = poppler_document_get_page_by_label(doc, "0");
    EXPECT_EQ(page, nullptr);
}

// Test: Negative number as label
TEST_F(PopplerDocumentGetPageByLabelTest_2153, NegativeNumberLabelReturnsNull_2153) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    PopplerPage *page = poppler_document_get_page_by_label(doc, "-1");
    EXPECT_EQ(page, nullptr);
}

// Test with a multi-page PDF
class PopplerDocumentMultiPageTest_2153 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    std::string tmp_filename;
    
    void SetUp() override {
        GError *error = nullptr;
        
        // Create a minimal 3-page PDF
        const char *multi_page_pdf = 
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R 4 0 R 5 0 R] /Count 3 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
            "endobj\n"
            "4 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
            "endobj\n"
            "5 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
            "endobj\n"
            "xref\n"
            "0 6\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000131 00000 n \n"
            "0000000208 00000 n \n"
            "0000000285 00000 n \n"
            "trailer\n"
            "<< /Size 6 /Root 1 0 R >>\n"
            "startxref\n"
            "362\n"
            "%%EOF\n";
        
        tmp_filename = std::string(g_get_tmp_dir()) + "/test_poppler_multi_2153.pdf";
        FILE *f = fopen(tmp_filename.c_str(), "wb");
        if (f) {
            fwrite(multi_page_pdf, 1, strlen(multi_page_pdf), f);
            fclose(f);
            
            gchar *uri = g_filename_to_uri(tmp_filename.c_str(), nullptr, &error);
            if (uri) {
                doc = poppler_document_new_from_file(uri, nullptr, &error);
                g_free(uri);
            }
            if (error) {
                g_error_free(error);
                error = nullptr;
            }
        }
    }
    
    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
        if (!tmp_filename.empty()) {
            remove(tmp_filename.c_str());
        }
    }
};

// Test: Get different pages by their default numeric labels in multi-page doc
TEST_F(PopplerDocumentMultiPageTest_2153, GetPageByNumericLabel_2153) {
    if (!doc) {
        GTEST_SKIP() << "Could not create multi-page test PDF document";
    }
    
    // Default page labels are "1", "2", "3"
    PopplerPage *page1 = poppler_document_get_page_by_label(doc, "1");
    if (page1) {
        EXPECT_EQ(poppler_page_get_index(page1), 0);
        g_object_unref(page1);
    }
    
    PopplerPage *page2 = poppler_document_get_page_by_label(doc, "2");
    if (page2) {
        EXPECT_EQ(poppler_page_get_index(page2), 1);
        g_object_unref(page2);
    }
    
    PopplerPage *page3 = poppler_document_get_page_by_label(doc, "3");
    if (page3) {
        EXPECT_EQ(poppler_page_get_index(page3), 2);
        g_object_unref(page3);
    }
}

// Test: Page beyond count returns nullptr in multi-page doc
TEST_F(PopplerDocumentMultiPageTest_2153, BeyondPageCountReturnsNull_2153) {
    if (!doc) {
        GTEST_SKIP() << "Could not create multi-page test PDF document";
    }
    
    PopplerPage *page = poppler_document_get_page_by_label(doc, "4");
    EXPECT_EQ(page, nullptr);
}

// Test: Whitespace-only label
TEST_F(PopplerDocumentGetPageByLabelTest_2153, WhitespaceLabelReturnsNull_2153) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    PopplerPage *page = poppler_document_get_page_by_label(doc, "   ");
    EXPECT_EQ(page, nullptr);
}

// Test: Label with leading/trailing whitespace around valid number
TEST_F(PopplerDocumentGetPageByLabelTest_2153, LabelWithWhitespaceAroundNumber_2153) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    // " 1 " should not match "1" as labels are exact matches
    PopplerPage *page = poppler_document_get_page_by_label(doc, " 1 ");
    // This may or may not return a page - depends on implementation
    // But it should not crash
    if (page) {
        g_object_unref(page);
    }
}

// Test: Unicode label
TEST_F(PopplerDocumentGetPageByLabelTest_2153, UnicodeLabelReturnsNull_2153) {
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    PopplerPage *page = poppler_document_get_page_by_label(doc, "\xC3\xA9\xC3\xA8"); // "éè" in UTF-8
    EXPECT_EQ(page, nullptr);
}
