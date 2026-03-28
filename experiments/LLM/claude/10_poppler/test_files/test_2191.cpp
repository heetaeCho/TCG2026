#include <glib.h>
#include <glib-object.h>
#include <poppler-document.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstring>

class PopplerDocumentSetModificationDateTimeTest_2191 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;

    void SetUp() override {
        // Create a minimal PDF in memory to get a valid PopplerDocument
        const char *pdf_content =
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

        gsize length = strlen(pdf_content);
        GBytes *bytes = g_bytes_new(pdf_content, length);
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        g_bytes_unref(bytes);

        GError *error = nullptr;
        document = poppler_document_new_from_stream(stream, length, nullptr, nullptr, &error);
        
        if (!document) {
            // Try alternative method
            if (error) {
                g_error_free(error);
                error = nullptr;
            }
            // Create from data
            document = poppler_document_new_from_data((char*)pdf_content, (int)length, nullptr, &error);
        }

        if (error) {
            g_error_free(error);
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

TEST_F(PopplerDocumentSetModificationDateTimeTest_2191, SetValidModificationDateTime_2191) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    GDateTime *dt = g_date_time_new_utc(2023, 6, 15, 10, 30, 0);
    ASSERT_NE(dt, nullptr);

    // Should not crash or fail
    poppler_document_set_modification_date_time(document, dt);

    // Verify we can retrieve it back
    GDateTime *retrieved = poppler_document_get_modification_date_time(document);
    if (retrieved) {
        EXPECT_EQ(g_date_time_get_year(retrieved), 2023);
        EXPECT_EQ(g_date_time_get_month(retrieved), 6);
        EXPECT_EQ(g_date_time_get_day_of_month(retrieved), 15);
        g_date_time_unref(retrieved);
    }

    g_date_time_unref(dt);
}

TEST_F(PopplerDocumentSetModificationDateTimeTest_2191, SetNullDateTime_2191) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    // Setting nullptr should clear the modification date
    poppler_document_set_modification_date_time(document, nullptr);

    GDateTime *retrieved = poppler_document_get_modification_date_time(document);
    // After setting null, retrieved should be null
    EXPECT_EQ(retrieved, nullptr);
    if (retrieved) {
        g_date_time_unref(retrieved);
    }
}

TEST_F(PopplerDocumentSetModificationDateTimeTest_2191, SetNullDocument_2191) {
    // Passing null document should not crash (g_return_if_fail handles it)
    GDateTime *dt = g_date_time_new_utc(2023, 6, 15, 10, 30, 0);
    ASSERT_NE(dt, nullptr);

    // Should return without crashing due to g_return_if_fail
    poppler_document_set_modification_date_time(nullptr, dt);

    g_date_time_unref(dt);
}

TEST_F(PopplerDocumentSetModificationDateTimeTest_2191, SetBothNull_2191) {
    // Both null should not crash due to g_return_if_fail
    poppler_document_set_modification_date_time(nullptr, nullptr);
}

TEST_F(PopplerDocumentSetModificationDateTimeTest_2191, SetEpochDateTime_2191) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    // Unix epoch
    GDateTime *dt = g_date_time_new_utc(1970, 1, 1, 0, 0, 0);
    ASSERT_NE(dt, nullptr);

    poppler_document_set_modification_date_time(document, dt);

    GDateTime *retrieved = poppler_document_get_modification_date_time(document);
    if (retrieved) {
        EXPECT_EQ(g_date_time_get_year(retrieved), 1970);
        EXPECT_EQ(g_date_time_get_month(retrieved), 1);
        EXPECT_EQ(g_date_time_get_day_of_month(retrieved), 1);
        g_date_time_unref(retrieved);
    }

    g_date_time_unref(dt);
}

TEST_F(PopplerDocumentSetModificationDateTimeTest_2191, SetFutureDateTime_2191) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    GDateTime *dt = g_date_time_new_utc(2099, 12, 31, 23, 59, 59);
    ASSERT_NE(dt, nullptr);

    poppler_document_set_modification_date_time(document, dt);

    GDateTime *retrieved = poppler_document_get_modification_date_time(document);
    if (retrieved) {
        EXPECT_EQ(g_date_time_get_year(retrieved), 2099);
        EXPECT_EQ(g_date_time_get_month(retrieved), 12);
        EXPECT_EQ(g_date_time_get_day_of_month(retrieved), 31);
        g_date_time_unref(retrieved);
    }

    g_date_time_unref(dt);
}

TEST_F(PopplerDocumentSetModificationDateTimeTest_2191, OverwriteModificationDateTime_2191) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    GDateTime *dt1 = g_date_time_new_utc(2020, 1, 1, 0, 0, 0);
    ASSERT_NE(dt1, nullptr);
    poppler_document_set_modification_date_time(document, dt1);

    GDateTime *dt2 = g_date_time_new_utc(2025, 7, 20, 12, 0, 0);
    ASSERT_NE(dt2, nullptr);
    poppler_document_set_modification_date_time(document, dt2);

    GDateTime *retrieved = poppler_document_get_modification_date_time(document);
    if (retrieved) {
        EXPECT_EQ(g_date_time_get_year(retrieved), 2025);
        EXPECT_EQ(g_date_time_get_month(retrieved), 7);
        EXPECT_EQ(g_date_time_get_day_of_month(retrieved), 20);
        g_date_time_unref(retrieved);
    }

    g_date_time_unref(dt1);
    g_date_time_unref(dt2);
}

TEST_F(PopplerDocumentSetModificationDateTimeTest_2191, SetThenClearModificationDateTime_2191) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    GDateTime *dt = g_date_time_new_utc(2023, 3, 15, 8, 0, 0);
    ASSERT_NE(dt, nullptr);

    poppler_document_set_modification_date_time(document, dt);

    // Now clear it
    poppler_document_set_modification_date_time(document, nullptr);

    GDateTime *retrieved = poppler_document_get_modification_date_time(document);
    EXPECT_EQ(retrieved, nullptr);
    if (retrieved) {
        g_date_time_unref(retrieved);
    }

    g_date_time_unref(dt);
}

TEST_F(PopplerDocumentSetModificationDateTimeTest_2191, SetDateTimeWithTimezone_2191) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    GTimeZone *tz = g_time_zone_new_offset(3600 * 5); // UTC+5
    GDateTime *dt = g_date_time_new(tz, 2023, 8, 10, 14, 30, 0);
    ASSERT_NE(dt, nullptr);

    poppler_document_set_modification_date_time(document, dt);

    GDateTime *retrieved = poppler_document_get_modification_date_time(document);
    if (retrieved) {
        // The date should be preserved (possibly converted)
        g_date_time_unref(retrieved);
    }

    g_date_time_unref(dt);
    g_time_zone_unref(tz);
}
