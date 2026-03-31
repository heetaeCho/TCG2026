#include <glib.h>
#include <glib-object.h>
#include <poppler.h>
#include <ctime>
#include <cstring>
#include <gtest/gtest.h>

class PopplerDocumentSetCreationDateTest_2185 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;

    void SetUp() override {
        // Create a minimal valid PDF in memory to get a PopplerDocument
        const char *pdf_content =
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

        gsize len = strlen(pdf_content);
        GError *error = nullptr;
        document = poppler_document_new_from_data(pdf_content, (int)len, nullptr, &error);
        
        if (document == nullptr && error != nullptr) {
            // Try alternative approach with GBytes
            g_error_free(error);
            error = nullptr;
            GBytes *bytes = g_bytes_new(pdf_content, len);
            document = poppler_document_new_from_bytes(bytes, nullptr, &error);
            g_bytes_unref(bytes);
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
    }
};

// Test setting a valid creation date
TEST_F(PopplerDocumentSetCreationDateTest_2185, SetValidCreationDate_2185) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    time_t test_time = 1000000000; // Sep 8, 2001
    poppler_document_set_creation_date(document, test_time);
    
    time_t retrieved = poppler_document_get_creation_date(document);
    EXPECT_EQ(retrieved, test_time);
}

// Test setting creation date to -1 (should clear the date)
TEST_F(PopplerDocumentSetCreationDateTest_2185, SetCreationDateToNegativeOne_2185) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    // First set a valid date
    time_t valid_time = 1000000000;
    poppler_document_set_creation_date(document, valid_time);
    
    // Now clear it with -1
    poppler_document_set_creation_date(document, (time_t)-1);
    
    time_t retrieved = poppler_document_get_creation_date(document);
    EXPECT_EQ(retrieved, (time_t)-1);
}

// Test setting creation date to epoch (0)
TEST_F(PopplerDocumentSetCreationDateTest_2185, SetCreationDateToEpoch_2185) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    time_t epoch = 0;
    poppler_document_set_creation_date(document, epoch);
    
    time_t retrieved = poppler_document_get_creation_date(document);
    EXPECT_EQ(retrieved, epoch);
}

// Test setting creation date to current time
TEST_F(PopplerDocumentSetCreationDateTest_2185, SetCreationDateToCurrentTime_2185) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    time_t now = time(nullptr);
    poppler_document_set_creation_date(document, now);
    
    time_t retrieved = poppler_document_get_creation_date(document);
    EXPECT_EQ(retrieved, now);
}

// Test overwriting creation date with a new value
TEST_F(PopplerDocumentSetCreationDateTest_2185, OverwriteCreationDate_2185) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    time_t first_time = 1000000000;
    poppler_document_set_creation_date(document, first_time);
    
    time_t second_time = 1500000000;
    poppler_document_set_creation_date(document, second_time);
    
    time_t retrieved = poppler_document_get_creation_date(document);
    EXPECT_EQ(retrieved, second_time);
}

// Test passing NULL document (should not crash due to g_return_if_fail)
TEST_F(PopplerDocumentSetCreationDateTest_2185, NullDocumentDoesNotCrash_2185) {
    // g_return_if_fail should handle NULL gracefully
    // This should simply return without crashing
    poppler_document_set_creation_date(nullptr, 1000000000);
    // If we reach here, the test passes (no crash)
    SUCCEED();
}

// Test setting a large time value
TEST_F(PopplerDocumentSetCreationDateTest_2185, SetLargeCreationDate_2185) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    // Use a large but valid time_t value (year ~2038 boundary for 32-bit)
    time_t large_time = 2000000000;
    poppler_document_set_creation_date(document, large_time);
    
    time_t retrieved = poppler_document_get_creation_date(document);
    EXPECT_EQ(retrieved, large_time);
}

// Test setting creation date to 1 (minimal positive value)
TEST_F(PopplerDocumentSetCreationDateTest_2185, SetCreationDateToOne_2185) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    time_t one = 1;
    poppler_document_set_creation_date(document, one);
    
    time_t retrieved = poppler_document_get_creation_date(document);
    EXPECT_EQ(retrieved, one);
}

// Test clearing and then resetting creation date
TEST_F(PopplerDocumentSetCreationDateTest_2185, ClearAndResetCreationDate_2185) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    
    time_t valid_time = 1234567890;
    poppler_document_set_creation_date(document, valid_time);
    
    // Clear
    poppler_document_set_creation_date(document, (time_t)-1);
    time_t cleared = poppler_document_get_creation_date(document);
    EXPECT_EQ(cleared, (time_t)-1);
    
    // Reset
    poppler_document_set_creation_date(document, valid_time);
    time_t reset = poppler_document_get_creation_date(document);
    EXPECT_EQ(reset, valid_time);
}
