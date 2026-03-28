#include <glib.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstring>
#include <cstdio>
#include <fstream>

class PopplerDocumentGetPdfVersionStringTest_2170 : public ::testing::Test {
protected:
    void SetUp() override {
        document_ = nullptr;
    }

    void TearDown() override {
        if (document_) {
            g_object_unref(document_);
            document_ = nullptr;
        }
    }

    // Helper to create a minimal PDF in memory and load it
    PopplerDocument* createMinimalPDF(const char* version = "1.4") {
        // Create a minimal valid PDF
        std::string pdf;
        pdf += "%PDF-";
        pdf += version;
        pdf += "\n";
        pdf += "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n";
        pdf += "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n";
        pdf += "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n";
        pdf += "xref\n0 4\n";
        pdf += "0000000000 65535 f \n";
        
        // Calculate offsets
        char buf[64];
        size_t obj1_offset = 5 + strlen(version) + 1; // %PDF-version\n
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", obj1_offset);
        pdf += buf;
        
        size_t obj2_offset = obj1_offset + strlen("1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n");
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", obj2_offset);
        pdf += buf;
        
        size_t obj3_offset = obj2_offset + strlen("2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n");
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", obj3_offset);
        pdf += buf;
        
        size_t xref_offset = obj3_offset + strlen("3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n");
        
        pdf += "trailer<</Size 4/Root 1 0 R>>\n";
        pdf += "startxref\n";
        snprintf(buf, sizeof(buf), "%zu\n", xref_offset);
        pdf += buf;
        pdf += "%%EOF\n";

        GError *error = nullptr;
        GBytes *bytes = g_bytes_new(pdf.c_str(), pdf.size());
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        
        PopplerDocument *doc = poppler_document_new_from_stream(
            stream, static_cast<gssize>(pdf.size()), nullptr, nullptr, &error);
        
        g_object_unref(stream);
        g_bytes_unref(bytes);
        
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        
        return doc;
    }

    PopplerDocument *document_;
};

TEST_F(PopplerDocumentGetPdfVersionStringTest_2170, ReturnsNullForNullDocument_2170) {
    // Passing NULL should return NULL (g_return_val_if_fail check)
    // Note: This may produce a g_critical warning
    gchar *result = poppler_document_get_pdf_version_string(nullptr);
    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerDocumentGetPdfVersionStringTest_2170, ReturnsVersionStringForValidDocument_2170) {
    document_ = createMinimalPDF("1.4");
    if (!document_) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    
    gchar *version_str = poppler_document_get_pdf_version_string(document_);
    ASSERT_NE(version_str, nullptr);
    
    // Should start with "PDF-"
    EXPECT_TRUE(g_str_has_prefix(version_str, "PDF-"));
    
    g_free(version_str);
}

TEST_F(PopplerDocumentGetPdfVersionStringTest_2170, VersionStringStartsWithPDFPrefix_2170) {
    document_ = createMinimalPDF("1.7");
    if (!document_) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    
    gchar *version_str = poppler_document_get_pdf_version_string(document_);
    ASSERT_NE(version_str, nullptr);
    EXPECT_EQ(strncmp(version_str, "PDF-", 4), 0);
    
    g_free(version_str);
}

TEST_F(PopplerDocumentGetPdfVersionStringTest_2170, VersionStringContainsNumericPart_2170) {
    document_ = createMinimalPDF("1.4");
    if (!document_) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    
    gchar *version_str = poppler_document_get_pdf_version_string(document_);
    ASSERT_NE(version_str, nullptr);
    
    // The part after "PDF-" should be a parseable number
    const char *num_part = version_str + 4;
    double val = g_ascii_strtod(num_part, nullptr);
    EXPECT_GT(val, 0.0);
    
    g_free(version_str);
}

TEST_F(PopplerDocumentGetPdfVersionStringTest_2170, ReturnedStringIsFreeable_2170) {
    document_ = createMinimalPDF("1.5");
    if (!document_) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    
    gchar *version_str = poppler_document_get_pdf_version_string(document_);
    ASSERT_NE(version_str, nullptr);
    
    // Verify string length is reasonable (should not exceed allocated 16 chars)
    size_t len = strlen(version_str);
    EXPECT_GT(len, 4u);   // At least "PDF-" + something
    EXPECT_LE(len, 15u);  // Should fit in allocated buffer
    
    g_free(version_str);
}

TEST_F(PopplerDocumentGetPdfVersionStringTest_2170, PDF14VersionFormat_2170) {
    document_ = createMinimalPDF("1.4");
    if (!document_) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    
    gchar *version_str = poppler_document_get_pdf_version_string(document_);
    ASSERT_NE(version_str, nullptr);
    
    // For PDF 1.4: major=1, minor=4, result = 1 + 4/10.0 = 1.4
    // With "%.2g" format, 1.4 -> "1.4"
    EXPECT_STREQ(version_str, "PDF-1.4");
    
    g_free(version_str);
}

TEST_F(PopplerDocumentGetPdfVersionStringTest_2170, PDF20VersionFormat_2170) {
    document_ = createMinimalPDF("2.0");
    if (!document_) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    
    gchar *version_str = poppler_document_get_pdf_version_string(document_);
    ASSERT_NE(version_str, nullptr);
    
    // For PDF 2.0: major=2, minor=0, result = 2 + 0/10.0 = 2.0
    // With "%.2g" format, 2.0 -> "2"
    EXPECT_STREQ(version_str, "PDF-2");
    
    g_free(version_str);
}

TEST_F(PopplerDocumentGetPdfVersionStringTest_2170, PDF17VersionFormat_2170) {
    document_ = createMinimalPDF("1.7");
    if (!document_) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    
    gchar *version_str = poppler_document_get_pdf_version_string(document_);
    ASSERT_NE(version_str, nullptr);
    
    // For PDF 1.7: major=1, minor=7, result = 1 + 7/10.0 = 1.7
    // With "%.2g" format, 1.7 -> "1.7"
    EXPECT_STREQ(version_str, "PDF-1.7");
    
    g_free(version_str);
}

TEST_F(PopplerDocumentGetPdfVersionStringTest_2170, MultipleCallsReturnIndependentStrings_2170) {
    document_ = createMinimalPDF("1.4");
    if (!document_) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    
    gchar *version_str1 = poppler_document_get_pdf_version_string(document_);
    gchar *version_str2 = poppler_document_get_pdf_version_string(document_);
    
    ASSERT_NE(version_str1, nullptr);
    ASSERT_NE(version_str2, nullptr);
    
    // Both should have the same content
    EXPECT_STREQ(version_str1, version_str2);
    
    // But should be different allocations
    EXPECT_NE(version_str1, version_str2);
    
    g_free(version_str1);
    g_free(version_str2);
}
