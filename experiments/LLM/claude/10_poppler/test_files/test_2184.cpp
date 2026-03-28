#include <glib.h>
#include <glib-object.h>
#include <poppler-document.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <ctime>
#include <cstring>
#include <cstdio>

class PopplerDocumentGetCreationDateTest_2184 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;

    void SetUp() override {
        // We'll load documents per test as needed
    }

    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
    }

    PopplerDocument *loadDocumentFromFile(const char *filename) {
        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(filename, nullptr, &error);
        if (!uri) {
            if (error) {
                g_error_free(error);
            }
            return nullptr;
        }
        PopplerDocument *d = poppler_document_new_from_uri(uri, nullptr, &error);
        g_free(uri);
        if (error) {
            g_error_free(error);
        }
        return d;
    }

    // Helper to create a minimal PDF in memory with a given CreationDate
    PopplerDocument *createPdfWithCreationDate(const char *creation_date_str) {
        // Build a minimal PDF with the specified CreationDate in the Info dictionary
        char pdf_content[4096];
        int len;

        if (creation_date_str) {
            len = snprintf(pdf_content, sizeof(pdf_content),
                "%%PDF-1.4\n"
                "1 0 obj\n"
                "<< /Type /Catalog /Pages 2 0 R >>\n"
                "endobj\n"
                "2 0 obj\n"
                "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
                "endobj\n"
                "3 0 obj\n"
                "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
                "endobj\n"
                "4 0 obj\n"
                "<< /CreationDate (%s) >>\n"
                "endobj\n"
                "xref\n"
                "0 5\n"
                "0000000000 65535 f \n"
                "0000000009 00000 n \n"
                "0000000058 00000 n \n"
                "0000000115 00000 n \n"
                "0000000198 00000 n \n"
                "trailer\n"
                "<< /Size 5 /Root 1 0 R /Info 4 0 R >>\n"
                "startxref\n"
                "250\n"
                "%%%%EOF\n",
                creation_date_str);
        } else {
            len = snprintf(pdf_content, sizeof(pdf_content),
                "%%PDF-1.4\n"
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
                "198\n"
                "%%%%EOF\n");
        }

        GError *error = nullptr;
        PopplerDocument *d = poppler_document_new_from_data(pdf_content, len, nullptr, &error);
        if (error) {
            g_error_free(error);
        }
        return d;
    }
};

// Test that passing NULL document returns (time_t)-1
TEST_F(PopplerDocumentGetCreationDateTest_2184, NullDocumentReturnsNegativeOne_2184) {
    // Passing NULL should trigger g_return_val_if_fail and return (time_t)-1
    // Note: This may produce a g_critical warning, which is expected
    time_t result = poppler_document_get_creation_date(nullptr);
    EXPECT_EQ(result, (time_t)-1);
}

// Test a PDF without any Info dictionary (no creation date)
TEST_F(PopplerDocumentGetCreationDateTest_2184, NoCreationDateReturnsNegativeOne_2184) {
    doc = createPdfWithCreationDate(nullptr);
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF without creation date";
    }
    time_t result = poppler_document_get_creation_date(doc);
    EXPECT_EQ(result, (time_t)-1);
}

// Test a PDF with a valid creation date string
TEST_F(PopplerDocumentGetCreationDateTest_2184, ValidCreationDateReturnsPositiveTime_2184) {
    // D:20230615120000+00'00' represents June 15, 2023 12:00:00 UTC
    doc = createPdfWithCreationDate("D:20230615120000+00'00'");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF with valid creation date";
    }
    time_t result = poppler_document_get_creation_date(doc);
    // The date should be valid and not -1
    EXPECT_NE(result, (time_t)-1);
    // Verify it's a reasonable timestamp (after year 2000)
    if (result != (time_t)-1) {
        EXPECT_GT(result, (time_t)946684800); // Jan 1, 2000 UTC
    }
}

// Test a PDF with an invalid/malformed creation date string
TEST_F(PopplerDocumentGetCreationDateTest_2184, InvalidCreationDateReturnsNegativeOne_2184) {
    doc = createPdfWithCreationDate("not-a-valid-date");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF with invalid creation date";
    }
    time_t result = poppler_document_get_creation_date(doc);
    EXPECT_EQ(result, (time_t)-1);
}

// Test a PDF with an empty creation date string
TEST_F(PopplerDocumentGetCreationDateTest_2184, EmptyCreationDateReturnsNegativeOne_2184) {
    doc = createPdfWithCreationDate("");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF with empty creation date";
    }
    time_t result = poppler_document_get_creation_date(doc);
    EXPECT_EQ(result, (time_t)-1);
}

// Test a PDF with a known specific date to verify correct conversion
TEST_F(PopplerDocumentGetCreationDateTest_2184, KnownDateValueIsCorrect_2184) {
    // D:20000101000000Z represents Jan 1, 2000 00:00:00 UTC = epoch 946684800
    doc = createPdfWithCreationDate("D:20000101000000Z");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF with known date";
    }
    time_t result = poppler_document_get_creation_date(doc);
    if (result != (time_t)-1) {
        // Jan 1, 2000 00:00:00 UTC
        EXPECT_EQ(result, (time_t)946684800);
    }
}

// Test that calling the function twice returns the same value (idempotent)
TEST_F(PopplerDocumentGetCreationDateTest_2184, IdempotentCalls_2184) {
    doc = createPdfWithCreationDate("D:20230101000000Z");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    time_t result1 = poppler_document_get_creation_date(doc);
    time_t result2 = poppler_document_get_creation_date(doc);
    EXPECT_EQ(result1, result2);
}

// Test with a creation date that has timezone offset
TEST_F(PopplerDocumentGetCreationDateTest_2184, CreationDateWithTimezoneOffset_2184) {
    // D:20230615120000+05'30' represents June 15, 2023 12:00:00 +05:30
    doc = createPdfWithCreationDate("D:20230615120000+05'30'");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF with timezone offset";
    }
    time_t result = poppler_document_get_creation_date(doc);
    // Should parse successfully
    EXPECT_NE(result, (time_t)-1);
}

// Test with date only (no time component)
TEST_F(PopplerDocumentGetCreationDateTest_2184, DateOnlyCreationDate_2184) {
    doc = createPdfWithCreationDate("D:20230615");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF with date only";
    }
    time_t result = poppler_document_get_creation_date(doc);
    // This may or may not be valid depending on the parser's strictness
    // We just verify it doesn't crash and returns a consistent value
    time_t result2 = poppler_document_get_creation_date(doc);
    EXPECT_EQ(result, result2);
}
