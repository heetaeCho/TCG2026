#include <glib.h>
#include <glib-object.h>
#include <poppler.h>
#include <ctime>
#include <cstring>
#include <gtest/gtest.h>

class PopplerDocumentSetModificationDateTest_2189 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;

    void SetUp() override {
        // Create a simple PDF in memory to get a valid PopplerDocument
        // We'll try to create a document from a minimal PDF file
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
        GBytes *bytes = g_bytes_new(pdf_content, len);
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        GError *error = nullptr;

        doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);

        if (doc == nullptr && error != nullptr) {
            g_error_free(error);
            error = nullptr;
        }

        // If stream-based creation failed, try creating from data
        if (doc == nullptr) {
            char *data = g_strdup(pdf_content);
            doc = poppler_document_new_from_data(data, len, nullptr, &error);
            if (doc == nullptr && error != nullptr) {
                g_error_free(error);
                error = nullptr;
            }
            if (doc == nullptr) {
                g_free(data);
            }
        }

        g_object_unref(stream);
        g_bytes_unref(bytes);
    }

    void TearDown() override {
        if (doc != nullptr) {
            g_object_unref(doc);
            doc = nullptr;
        }
    }
};

TEST_F(PopplerDocumentSetModificationDateTest_2189, SetValidModificationDate_2189) {
    if (doc == nullptr) {
        GTEST_SKIP() << "Could not create test document";
    }

    time_t now = time(nullptr);
    poppler_document_set_modification_date(doc, now);

    // Verify the date was set by reading it back
    time_t retrieved = poppler_document_get_modification_date(doc);
    // The retrieved date should match what we set (possibly with some rounding)
    EXPECT_EQ(retrieved, now);
}

TEST_F(PopplerDocumentSetModificationDateTest_2189, SetModificationDateToNegativeOne_2189) {
    if (doc == nullptr) {
        GTEST_SKIP() << "Could not create test document";
    }

    // Setting to (time_t)-1 should clear the modification date (set to nullptr)
    poppler_document_set_modification_date(doc, (time_t)-1);

    time_t retrieved = poppler_document_get_modification_date(doc);
    // When cleared, we expect -1 or 0 to be returned
    EXPECT_TRUE(retrieved == (time_t)-1 || retrieved == (time_t)0);
}

TEST_F(PopplerDocumentSetModificationDateTest_2189, SetModificationDateToZero_2189) {
    if (doc == nullptr) {
        GTEST_SKIP() << "Could not create test document";
    }

    // Epoch time (0) is a valid date
    poppler_document_set_modification_date(doc, (time_t)0);

    time_t retrieved = poppler_document_get_modification_date(doc);
    EXPECT_EQ(retrieved, (time_t)0);
}

TEST_F(PopplerDocumentSetModificationDateTest_2189, SetModificationDateToSpecificTime_2189) {
    if (doc == nullptr) {
        GTEST_SKIP() << "Could not create test document";
    }

    // Set a specific known date: 2023-01-15 12:00:00 UTC (approximate)
    time_t specific_time = 1673784000;
    poppler_document_set_modification_date(doc, specific_time);

    time_t retrieved = poppler_document_get_modification_date(doc);
    EXPECT_EQ(retrieved, specific_time);
}

TEST_F(PopplerDocumentSetModificationDateTest_2189, SetModificationDateOverwritesPrevious_2189) {
    if (doc == nullptr) {
        GTEST_SKIP() << "Could not create test document";
    }

    time_t first_time = 1000000;
    time_t second_time = 2000000;

    poppler_document_set_modification_date(doc, first_time);
    time_t retrieved1 = poppler_document_get_modification_date(doc);
    EXPECT_EQ(retrieved1, first_time);

    poppler_document_set_modification_date(doc, second_time);
    time_t retrieved2 = poppler_document_get_modification_date(doc);
    EXPECT_EQ(retrieved2, second_time);
}

TEST_F(PopplerDocumentSetModificationDateTest_2189, NullDocumentDoesNotCrash_2189) {
    // Passing NULL should be handled gracefully by g_return_if_fail
    poppler_document_set_modification_date(nullptr, time(nullptr));
    // If we reach here, no crash occurred
    SUCCEED();
}

TEST_F(PopplerDocumentSetModificationDateTest_2189, SetAndClearModificationDate_2189) {
    if (doc == nullptr) {
        GTEST_SKIP() << "Could not create test document";
    }

    // First set a valid date
    time_t now = time(nullptr);
    poppler_document_set_modification_date(doc, now);
    time_t retrieved = poppler_document_get_modification_date(doc);
    EXPECT_EQ(retrieved, now);

    // Now clear it
    poppler_document_set_modification_date(doc, (time_t)-1);
    time_t cleared = poppler_document_get_modification_date(doc);
    EXPECT_TRUE(cleared == (time_t)-1 || cleared == (time_t)0);
}

TEST_F(PopplerDocumentSetModificationDateTest_2189, SetLargeModificationDate_2189) {
    if (doc == nullptr) {
        GTEST_SKIP() << "Could not create test document";
    }

    // A large but valid date (year 2038 range on 32-bit, but should work on 64-bit)
    time_t large_time = 2000000000;
    poppler_document_set_modification_date(doc, large_time);

    time_t retrieved = poppler_document_get_modification_date(doc);
    EXPECT_EQ(retrieved, large_time);
}

TEST_F(PopplerDocumentSetModificationDateTest_2189, SetSmallPositiveModificationDate_2189) {
    if (doc == nullptr) {
        GTEST_SKIP() << "Could not create test document";
    }

    // Very small positive time (1 second after epoch)
    time_t small_time = 1;
    poppler_document_set_modification_date(doc, small_time);

    time_t retrieved = poppler_document_get_modification_date(doc);
    EXPECT_EQ(retrieved, small_time);
}
