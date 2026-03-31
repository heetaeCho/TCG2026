#include <glib.h>
#include <glib-object.h>
#include <gtest/gtest.h>
#include <poppler-document.h>
#include <poppler.h>
#include <cstdio>
#include <cstring>
#include <fstream>

class PopplerPSFileTest_2255 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;
    const char *test_pdf_path = nullptr;
    char *temp_pdf_path = nullptr;

    void SetUp() override {
        // Create a minimal valid PDF file for testing
        temp_pdf_path = g_strdup("/tmp/test_poppler_2255.pdf");
        
        // Write a minimal PDF
        std::ofstream pdf(temp_pdf_path, std::ios::binary);
        const char *pdf_content = 
            "%PDF-1.0\n"
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
        pdf.write(pdf_content, strlen(pdf_content));
        pdf.close();

        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(temp_pdf_path, nullptr, &error);
        if (uri) {
            document = poppler_document_new_from_file(uri, nullptr, &error);
            g_free(uri);
        }
        if (error) {
            g_error_free(error);
        }
    }

    void TearDown() override {
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
        if (temp_pdf_path) {
            g_remove(temp_pdf_path);
            g_free(temp_pdf_path);
            temp_pdf_path = nullptr;
        }
    }
};

// Test creating a PopplerPSFile and immediately unreferencing it
TEST_F(PopplerPSFileTest_2255, CreateAndDestroy_2255) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    const char *ps_filename = "/tmp/test_output_2255.ps";
    PopplerPSFile *ps_file = poppler_ps_file_new(document, ps_filename, 0, 1);
    ASSERT_NE(ps_file, nullptr);
    
    g_object_unref(ps_file);
    
    // Cleanup
    g_remove(ps_filename);
}

// Test that poppler_ps_file_new returns a valid GObject
TEST_F(PopplerPSFileTest_2255, IsValidGObject_2255) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    const char *ps_filename = "/tmp/test_output_gobject_2255.ps";
    PopplerPSFile *ps_file = poppler_ps_file_new(document, ps_filename, 0, 1);
    ASSERT_NE(ps_file, nullptr);
    EXPECT_TRUE(G_IS_OBJECT(ps_file));
    EXPECT_TRUE(POPPLER_IS_PS_FILE(ps_file));
    
    g_object_unref(ps_file);
    g_remove(ps_filename);
}

// Test setting paper size on PSFile
TEST_F(PopplerPSFileTest_2255, SetPaperSize_2255) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    const char *ps_filename = "/tmp/test_output_paper_2255.ps";
    PopplerPSFile *ps_file = poppler_ps_file_new(document, ps_filename, 0, 1);
    ASSERT_NE(ps_file, nullptr);
    
    // Should not crash when setting paper size
    poppler_ps_file_set_paper_size(ps_file, 595.0, 842.0); // A4 size
    
    g_object_unref(ps_file);
    g_remove(ps_filename);
}

// Test setting duplex mode on PSFile
TEST_F(PopplerPSFileTest_2255, SetDuplex_2255) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    const char *ps_filename = "/tmp/test_output_duplex_2255.ps";
    PopplerPSFile *ps_file = poppler_ps_file_new(document, ps_filename, 0, 1);
    ASSERT_NE(ps_file, nullptr);
    
    // Should not crash when setting duplex
    poppler_ps_file_set_duplex(ps_file, TRUE);
    
    g_object_unref(ps_file);
    g_remove(ps_filename);
}

// Test setting duplex to FALSE
TEST_F(PopplerPSFileTest_2255, SetDuplexFalse_2255) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    const char *ps_filename = "/tmp/test_output_duplex_false_2255.ps";
    PopplerPSFile *ps_file = poppler_ps_file_new(document, ps_filename, 0, 1);
    ASSERT_NE(ps_file, nullptr);
    
    poppler_ps_file_set_duplex(ps_file, FALSE);
    
    g_object_unref(ps_file);
    g_remove(ps_filename);
}

// Test creating PSFile with page range boundaries
TEST_F(PopplerPSFileTest_2255, PageRangeBoundary_2255) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    const char *ps_filename = "/tmp/test_output_pagerange_2255.ps";
    // Create with first_page = last_page = 0 (single page)
    PopplerPSFile *ps_file = poppler_ps_file_new(document, ps_filename, 0, 0);
    ASSERT_NE(ps_file, nullptr);
    
    g_object_unref(ps_file);
    g_remove(ps_filename);
}

// Test setting various paper sizes
TEST_F(PopplerPSFileTest_2255, SetLetterPaperSize_2255) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    const char *ps_filename = "/tmp/test_output_letter_2255.ps";
    PopplerPSFile *ps_file = poppler_ps_file_new(document, ps_filename, 0, 1);
    ASSERT_NE(ps_file, nullptr);
    
    // US Letter size
    poppler_ps_file_set_paper_size(ps_file, 612.0, 792.0);
    
    g_object_unref(ps_file);
    g_remove(ps_filename);
}

// Test setting zero paper size (boundary condition)
TEST_F(PopplerPSFileTest_2255, SetZeroPaperSize_2255) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    const char *ps_filename = "/tmp/test_output_zero_2255.ps";
    PopplerPSFile *ps_file = poppler_ps_file_new(document, ps_filename, 0, 1);
    ASSERT_NE(ps_file, nullptr);
    
    // Should not crash with zero dimensions
    poppler_ps_file_set_paper_size(ps_file, 0.0, 0.0);
    
    g_object_unref(ps_file);
    g_remove(ps_filename);
}

// Test that finalize properly cleans up (verified by no memory leaks/crashes)
TEST_F(PopplerPSFileTest_2255, FinalizeCleanup_2255) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    const char *ps_filename = "/tmp/test_output_finalize_2255.ps";
    PopplerPSFile *ps_file = poppler_ps_file_new(document, ps_filename, 0, 1);
    ASSERT_NE(ps_file, nullptr);
    
    // Set various properties before destruction
    poppler_ps_file_set_paper_size(ps_file, 595.0, 842.0);
    poppler_ps_file_set_duplex(ps_file, TRUE);
    
    // This triggers finalize
    g_object_unref(ps_file);
    
    // If we reach here without crash, finalize worked correctly
    g_remove(ps_filename);
}

// Test creating multiple PSFile objects from same document
TEST_F(PopplerPSFileTest_2255, MultipleFromSameDocument_2255) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    const char *ps_filename1 = "/tmp/test_output_multi1_2255.ps";
    const char *ps_filename2 = "/tmp/test_output_multi2_2255.ps";
    
    PopplerPSFile *ps_file1 = poppler_ps_file_new(document, ps_filename1, 0, 1);
    PopplerPSFile *ps_file2 = poppler_ps_file_new(document, ps_filename2, 0, 1);
    
    ASSERT_NE(ps_file1, nullptr);
    ASSERT_NE(ps_file2, nullptr);
    
    g_object_unref(ps_file1);
    g_object_unref(ps_file2);
    
    g_remove(ps_filename1);
    g_remove(ps_filename2);
}

// Test setting very large paper size (boundary condition)
TEST_F(PopplerPSFileTest_2255, SetLargePaperSize_2255) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    const char *ps_filename = "/tmp/test_output_large_2255.ps";
    PopplerPSFile *ps_file = poppler_ps_file_new(document, ps_filename, 0, 1);
    ASSERT_NE(ps_file, nullptr);
    
    // Very large paper size
    poppler_ps_file_set_paper_size(ps_file, 100000.0, 100000.0);
    
    g_object_unref(ps_file);
    g_remove(ps_filename);
}

// Test reference counting
TEST_F(PopplerPSFileTest_2255, ReferenceCount_2255) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    const char *ps_filename = "/tmp/test_output_refcount_2255.ps";
    PopplerPSFile *ps_file = poppler_ps_file_new(document, ps_filename, 0, 1);
    ASSERT_NE(ps_file, nullptr);
    
    // Add a reference
    g_object_ref(ps_file);
    
    // First unref should not finalize
    g_object_unref(ps_file);
    
    // Should still be valid
    EXPECT_TRUE(POPPLER_IS_PS_FILE(ps_file));
    
    // Second unref should finalize
    g_object_unref(ps_file);
    
    g_remove(ps_filename);
}

// Test negative paper dimensions (boundary)
TEST_F(PopplerPSFileTest_2255, SetNegativePaperSize_2255) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    const char *ps_filename = "/tmp/test_output_neg_2255.ps";
    PopplerPSFile *ps_file = poppler_ps_file_new(document, ps_filename, 0, 1);
    ASSERT_NE(ps_file, nullptr);
    
    // Negative dimensions - should not crash
    poppler_ps_file_set_paper_size(ps_file, -1.0, -1.0);
    
    g_object_unref(ps_file);
    g_remove(ps_filename);
}
