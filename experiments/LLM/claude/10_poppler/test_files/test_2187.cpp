#include <glib.h>
#include <glib-object.h>
#include <poppler-document.h>
#include <poppler.h>
#include <gtest/gtest.h>

class PopplerDocumentSetCreationDateTimeTest_2187 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;

    void SetUp() override {
        // Create a minimal PDF in memory to get a PopplerDocument
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

        gsize length = strlen(pdf_content);
        GBytes *bytes = g_bytes_new(pdf_content, length);
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        g_bytes_unref(bytes);

        GError *error = nullptr;
        document = poppler_document_new_from_stream(stream, length, nullptr, nullptr, &error);
        
        if (!document) {
            // Fallback: try poppler_document_new_from_data
            if (error) {
                g_error_free(error);
                error = nullptr;
            }
            // Try creating from data
            char *data = g_strdup(pdf_content);
            document = poppler_document_new_from_data(data, length, nullptr, &error);
            if (!document && error) {
                g_printerr("Failed to create document: %s\n", error->message);
                g_error_free(error);
            }
        }

        g_object_unref(stream);
    }

    void TearDown() override {
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
    }
};

TEST_F(PopplerDocumentSetCreationDateTimeTest_2187, SetValidCreationDateTime_2187) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    GDateTime *dt = g_date_time_new_utc(2023, 6, 15, 10, 30, 0);
    ASSERT_NE(dt, nullptr);

    poppler_document_set_creation_date_time(document, dt);

    GDateTime *retrieved = poppler_document_get_creation_date_time(document);
    ASSERT_NE(retrieved, nullptr);

    EXPECT_EQ(g_date_time_get_year(retrieved), 2023);
    EXPECT_EQ(g_date_time_get_month(retrieved), 6);
    EXPECT_EQ(g_date_time_get_day_of_month(retrieved), 15);
    EXPECT_EQ(g_date_time_get_hour(retrieved), 10);
    EXPECT_EQ(g_date_time_get_minute(retrieved), 30);

    g_date_time_unref(retrieved);
    g_date_time_unref(dt);
}

TEST_F(PopplerDocumentSetCreationDateTimeTest_2187, SetNullCreationDateTime_2187) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    // First set a valid date
    GDateTime *dt = g_date_time_new_utc(2023, 1, 1, 0, 0, 0);
    ASSERT_NE(dt, nullptr);
    poppler_document_set_creation_date_time(document, dt);
    g_date_time_unref(dt);

    // Now set to NULL to clear it
    poppler_document_set_creation_date_time(document, nullptr);

    GDateTime *retrieved = poppler_document_get_creation_date_time(document);
    EXPECT_EQ(retrieved, nullptr);
}

TEST_F(PopplerDocumentSetCreationDateTimeTest_2187, SetCreationDateTimeWithTimezone_2187) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    GTimeZone *tz = g_time_zone_new_identifier("+05:30");
    if (!tz) {
        tz = g_time_zone_new_utc();
    }
    GDateTime *dt = g_date_time_new(tz, 2020, 12, 25, 18, 45, 30);
    ASSERT_NE(dt, nullptr);

    poppler_document_set_creation_date_time(document, dt);

    GDateTime *retrieved = poppler_document_get_creation_date_time(document);
    ASSERT_NE(retrieved, nullptr);

    EXPECT_EQ(g_date_time_get_year(retrieved), 2020);
    EXPECT_EQ(g_date_time_get_month(retrieved), 12);
    EXPECT_EQ(g_date_time_get_day_of_month(retrieved), 25);

    g_date_time_unref(retrieved);
    g_date_time_unref(dt);
    g_time_zone_unref(tz);
}

TEST_F(PopplerDocumentSetCreationDateTimeTest_2187, OverwriteExistingCreationDateTime_2187) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    // Set first date
    GDateTime *dt1 = g_date_time_new_utc(2010, 3, 14, 9, 26, 53);
    ASSERT_NE(dt1, nullptr);
    poppler_document_set_creation_date_time(document, dt1);
    g_date_time_unref(dt1);

    // Overwrite with second date
    GDateTime *dt2 = g_date_time_new_utc(2024, 7, 4, 12, 0, 0);
    ASSERT_NE(dt2, nullptr);
    poppler_document_set_creation_date_time(document, dt2);
    g_date_time_unref(dt2);

    GDateTime *retrieved = poppler_document_get_creation_date_time(document);
    ASSERT_NE(retrieved, nullptr);

    EXPECT_EQ(g_date_time_get_year(retrieved), 2024);
    EXPECT_EQ(g_date_time_get_month(retrieved), 7);
    EXPECT_EQ(g_date_time_get_day_of_month(retrieved), 4);
    EXPECT_EQ(g_date_time_get_hour(retrieved), 12);
    EXPECT_EQ(g_date_time_get_minute(retrieved), 0);

    g_date_time_unref(retrieved);
}

TEST_F(PopplerDocumentSetCreationDateTimeTest_2187, SetEpochDateTime_2187) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    // Unix epoch
    GDateTime *dt = g_date_time_new_utc(1970, 1, 1, 0, 0, 0);
    ASSERT_NE(dt, nullptr);

    poppler_document_set_creation_date_time(document, dt);

    GDateTime *retrieved = poppler_document_get_creation_date_time(document);
    ASSERT_NE(retrieved, nullptr);

    EXPECT_EQ(g_date_time_get_year(retrieved), 1970);
    EXPECT_EQ(g_date_time_get_month(retrieved), 1);
    EXPECT_EQ(g_date_time_get_day_of_month(retrieved), 1);

    g_date_time_unref(retrieved);
    g_date_time_unref(dt);
}

TEST_F(PopplerDocumentSetCreationDateTimeTest_2187, SetNullDocumentDoesNotCrash_2187) {
    // Passing NULL document should be handled gracefully by g_return_if_fail
    // This should not crash; the function should simply return
    GDateTime *dt = g_date_time_new_utc(2023, 1, 1, 0, 0, 0);
    ASSERT_NE(dt, nullptr);

    // Expect this to just return without crashing due to g_return_if_fail
    poppler_document_set_creation_date_time(nullptr, dt);

    g_date_time_unref(dt);
}

TEST_F(PopplerDocumentSetCreationDateTimeTest_2187, SetFutureDateCreationDateTime_2187) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    GDateTime *dt = g_date_time_new_utc(2099, 12, 31, 23, 59, 59);
    ASSERT_NE(dt, nullptr);

    poppler_document_set_creation_date_time(document, dt);

    GDateTime *retrieved = poppler_document_get_creation_date_time(document);
    ASSERT_NE(retrieved, nullptr);

    EXPECT_EQ(g_date_time_get_year(retrieved), 2099);
    EXPECT_EQ(g_date_time_get_month(retrieved), 12);
    EXPECT_EQ(g_date_time_get_day_of_month(retrieved), 31);
    EXPECT_EQ(g_date_time_get_hour(retrieved), 23);
    EXPECT_EQ(g_date_time_get_minute(retrieved), 59);

    g_date_time_unref(retrieved);
    g_date_time_unref(dt);
}

TEST_F(PopplerDocumentSetCreationDateTimeTest_2187, SetAndClearAndSetAgain_2187) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    // Set a date
    GDateTime *dt1 = g_date_time_new_utc(2015, 5, 20, 8, 0, 0);
    ASSERT_NE(dt1, nullptr);
    poppler_document_set_creation_date_time(document, dt1);
    g_date_time_unref(dt1);

    // Clear it
    poppler_document_set_creation_date_time(document, nullptr);
    GDateTime *retrieved = poppler_document_get_creation_date_time(document);
    EXPECT_EQ(retrieved, nullptr);

    // Set again
    GDateTime *dt2 = g_date_time_new_utc(2018, 11, 11, 11, 11, 11);
    ASSERT_NE(dt2, nullptr);
    poppler_document_set_creation_date_time(document, dt2);
    g_date_time_unref(dt2);

    retrieved = poppler_document_get_creation_date_time(document);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_EQ(g_date_time_get_year(retrieved), 2018);
    EXPECT_EQ(g_date_time_get_month(retrieved), 11);
    EXPECT_EQ(g_date_time_get_day_of_month(retrieved), 11);

    g_date_time_unref(retrieved);
}

TEST_F(PopplerDocumentSetCreationDateTimeTest_2187, SetNegativeTimezoneOffset_2187) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    GTimeZone *tz = g_time_zone_new_identifier("-08:00");
    if (!tz) {
        tz = g_time_zone_new_utc();
    }
    GDateTime *dt = g_date_time_new(tz, 2022, 2, 28, 16, 30, 0);
    ASSERT_NE(dt, nullptr);

    poppler_document_set_creation_date_time(document, dt);

    GDateTime *retrieved = poppler_document_get_creation_date_time(document);
    ASSERT_NE(retrieved, nullptr);

    EXPECT_EQ(g_date_time_get_year(retrieved), 2022);
    EXPECT_EQ(g_date_time_get_month(retrieved), 2);
    EXPECT_EQ(g_date_time_get_day_of_month(retrieved), 28);

    g_date_time_unref(retrieved);
    g_date_time_unref(dt);
    g_time_zone_unref(tz);
}
