#include <gtest/gtest.h>
#include <glib-object.h>

// Include poppler glib headers
#include "poppler.h"
#include "poppler-private.h"

class PopplerPSFileTest_2254 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;
    PopplerPSFile *ps_file = nullptr;

    void SetUp() override {
        // Create a minimal PDF in memory for testing
        // We need a valid PopplerDocument to create a PSFile
        GError *error = nullptr;
        
        // Try to create a document from a minimal PDF buffer
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
        
        gsize len = strlen(minimal_pdf);
        GBytes *bytes = g_bytes_new(minimal_pdf, len);
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        
        document = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);
        
        if (document == nullptr && error != nullptr) {
            g_error_free(error);
            error = nullptr;
        }
        
        g_object_unref(stream);
        g_bytes_unref(bytes);
    }

    void TearDown() override {
        if (ps_file != nullptr) {
            g_object_unref(ps_file);
            ps_file = nullptr;
        }
        if (document != nullptr) {
            g_object_unref(document);
            document = nullptr;
        }
    }
};

// Test that PopplerPSFile initialization sets default values correctly
TEST_F(PopplerPSFileTest_2254, InitSetsDefaultValues_2254) {
    if (document == nullptr) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    int n_pages = poppler_document_get_n_pages(document);
    const char *test_filename = "/tmp/test_poppler_ps_init_2254.ps";
    
    ps_file = poppler_ps_file_new(document, test_filename, 0, n_pages);
    ASSERT_NE(ps_file, nullptr);
    
    // Access the internal structure to verify init values
    _PopplerPSFile *internal = (_PopplerPSFile *)ps_file;
    
    // Verify that the init function set the expected default values
    // out should be nullptr after init (before any rendering)
    EXPECT_EQ(internal->out, nullptr);
    
    // paper_width and paper_height should be -1 (default)
    EXPECT_DOUBLE_EQ(internal->paper_width, -1);
    EXPECT_DOUBLE_EQ(internal->paper_height, -1);
    
    // duplex should be FALSE
    EXPECT_EQ(internal->duplex, FALSE);
}

// Test setting paper size on PSFile
TEST_F(PopplerPSFileTest_2254, SetPaperSize_2254) {
    if (document == nullptr) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    int n_pages = poppler_document_get_n_pages(document);
    const char *test_filename = "/tmp/test_poppler_ps_papersize_2254.ps";
    
    ps_file = poppler_ps_file_new(document, test_filename, 0, n_pages);
    ASSERT_NE(ps_file, nullptr);
    
    poppler_ps_file_set_paper_size(ps_file, 595.0, 842.0);
    
    _PopplerPSFile *internal = (_PopplerPSFile *)ps_file;
    EXPECT_DOUBLE_EQ(internal->paper_width, 595.0);
    EXPECT_DOUBLE_EQ(internal->paper_height, 842.0);
}

// Test setting duplex on PSFile
TEST_F(PopplerPSFileTest_2254, SetDuplex_2254) {
    if (document == nullptr) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    int n_pages = poppler_document_get_n_pages(document);
    const char *test_filename = "/tmp/test_poppler_ps_duplex_2254.ps";
    
    ps_file = poppler_ps_file_new(document, test_filename, 0, n_pages);
    ASSERT_NE(ps_file, nullptr);
    
    poppler_ps_file_set_duplex(ps_file, TRUE);
    
    _PopplerPSFile *internal = (_PopplerPSFile *)ps_file;
    EXPECT_EQ(internal->duplex, TRUE);
}

// Test setting duplex to FALSE
TEST_F(PopplerPSFileTest_2254, SetDuplexFalse_2254) {
    if (document == nullptr) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    int n_pages = poppler_document_get_n_pages(document);
    const char *test_filename = "/tmp/test_poppler_ps_duplex_false_2254.ps";
    
    ps_file = poppler_ps_file_new(document, test_filename, 0, n_pages);
    ASSERT_NE(ps_file, nullptr);
    
    // First set to TRUE, then back to FALSE
    poppler_ps_file_set_duplex(ps_file, TRUE);
    poppler_ps_file_set_duplex(ps_file, FALSE);
    
    _PopplerPSFile *internal = (_PopplerPSFile *)ps_file;
    EXPECT_EQ(internal->duplex, FALSE);
}

// Test creating PSFile with specific page range
TEST_F(PopplerPSFileTest_2254, CreateWithPageRange_2254) {
    if (document == nullptr) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    const char *test_filename = "/tmp/test_poppler_ps_pagerange_2254.ps";
    
    ps_file = poppler_ps_file_new(document, test_filename, 0, 1);
    ASSERT_NE(ps_file, nullptr);
    
    _PopplerPSFile *internal = (_PopplerPSFile *)ps_file;
    EXPECT_EQ(internal->first_page, 0);
    EXPECT_EQ(internal->last_page, 1);
}

// Test paper size with zero values
TEST_F(PopplerPSFileTest_2254, SetPaperSizeZero_2254) {
    if (document == nullptr) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    int n_pages = poppler_document_get_n_pages(document);
    const char *test_filename = "/tmp/test_poppler_ps_zero_paper_2254.ps";
    
    ps_file = poppler_ps_file_new(document, test_filename, 0, n_pages);
    ASSERT_NE(ps_file, nullptr);
    
    poppler_ps_file_set_paper_size(ps_file, 0.0, 0.0);
    
    _PopplerPSFile *internal = (_PopplerPSFile *)ps_file;
    EXPECT_DOUBLE_EQ(internal->paper_width, 0.0);
    EXPECT_DOUBLE_EQ(internal->paper_height, 0.0);
}

// Test paper size with large values
TEST_F(PopplerPSFileTest_2254, SetPaperSizeLarge_2254) {
    if (document == nullptr) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    int n_pages = poppler_document_get_n_pages(document);
    const char *test_filename = "/tmp/test_poppler_ps_large_paper_2254.ps";
    
    ps_file = poppler_ps_file_new(document, test_filename, 0, n_pages);
    ASSERT_NE(ps_file, nullptr);
    
    poppler_ps_file_set_paper_size(ps_file, 10000.0, 10000.0);
    
    _PopplerPSFile *internal = (_PopplerPSFile *)ps_file;
    EXPECT_DOUBLE_EQ(internal->paper_width, 10000.0);
    EXPECT_DOUBLE_EQ(internal->paper_height, 10000.0);
}

// Test that PSFile stores the filename
TEST_F(PopplerPSFileTest_2254, StoresFilename_2254) {
    if (document == nullptr) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    const char *test_filename = "/tmp/test_poppler_ps_filename_2254.ps";
    
    ps_file = poppler_ps_file_new(document, test_filename, 0, 1);
    ASSERT_NE(ps_file, nullptr);
    
    _PopplerPSFile *internal = (_PopplerPSFile *)ps_file;
    ASSERT_NE(internal->filename, nullptr);
    EXPECT_STREQ(internal->filename, test_filename);
}

// Test that PSFile stores the document reference
TEST_F(PopplerPSFileTest_2254, StoresDocumentReference_2254) {
    if (document == nullptr) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    const char *test_filename = "/tmp/test_poppler_ps_docref_2254.ps";
    
    ps_file = poppler_ps_file_new(document, test_filename, 0, 1);
    ASSERT_NE(ps_file, nullptr);
    
    _PopplerPSFile *internal = (_PopplerPSFile *)ps_file;
    EXPECT_EQ(internal->document, document);
}

// Test multiple paper size changes
TEST_F(PopplerPSFileTest_2254, MultiplePaperSizeChanges_2254) {
    if (document == nullptr) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    int n_pages = poppler_document_get_n_pages(document);
    const char *test_filename = "/tmp/test_poppler_ps_multi_paper_2254.ps";
    
    ps_file = poppler_ps_file_new(document, test_filename, 0, n_pages);
    ASSERT_NE(ps_file, nullptr);
    
    // Set A4
    poppler_ps_file_set_paper_size(ps_file, 595.0, 842.0);
    _PopplerPSFile *internal = (_PopplerPSFile *)ps_file;
    EXPECT_DOUBLE_EQ(internal->paper_width, 595.0);
    EXPECT_DOUBLE_EQ(internal->paper_height, 842.0);
    
    // Change to Letter
    poppler_ps_file_set_paper_size(ps_file, 612.0, 792.0);
    EXPECT_DOUBLE_EQ(internal->paper_width, 612.0);
    EXPECT_DOUBLE_EQ(internal->paper_height, 792.0);
}

// Test PSFile is a GObject
TEST_F(PopplerPSFileTest_2254, IsGObject_2254) {
    if (document == nullptr) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    const char *test_filename = "/tmp/test_poppler_ps_gobject_2254.ps";
    
    ps_file = poppler_ps_file_new(document, test_filename, 0, 1);
    ASSERT_NE(ps_file, nullptr);
    
    EXPECT_TRUE(G_IS_OBJECT(ps_file));
    EXPECT_TRUE(POPPLER_IS_PS_FILE(ps_file));
}
