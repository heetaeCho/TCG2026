#include <glib.h>
#include <glib-object.h>
#include <poppler.h>
#include <ctime>
#include <cstring>
#include <gtest/gtest.h>

class PopplerDocumentGetModificationDateTest_2188 : public ::testing::Test {
protected:
    void SetUp() override {
        // We'll create documents from PDF data or files as needed per test
    }

    void TearDown() override {
    }

    // Helper to create a minimal PDF in memory with a given ModDate
    PopplerDocument *createPdfWithModDate(const char *modDate) {
        // Build a minimal PDF with the given ModDate in the Info dictionary
        GString pdf;
        pdf = "";
        
        std::string pdfContent;
        pdfContent += "%PDF-1.4\n";
        pdfContent += "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        pdfContent += "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        pdfContent += "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        
        if (modDate) {
            pdfContent += "4 0 obj\n<< /ModDate (";
            pdfContent += modDate;
            pdfContent += ") >>\nendobj\n";
        } else {
            pdfContent += "4 0 obj\n<< >>\nendobj\n";
        }
        
        pdfContent += "xref\n0 5\n";
        // We need proper xref - let's use a simpler approach with poppler_document_new_from_data
        
        // Actually, building a valid PDF by hand is complex. Let's use a different approach.
        // We'll write to a temp file.
        
        char tmpname[] = "/tmp/poppler_test_XXXXXX";
        int fd = mkstemp(tmpname);
        if (fd < 0) return nullptr;
        
        std::string obj1 = "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        std::string obj2 = "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        std::string obj3 = "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        std::string obj4;
        if (modDate) {
            obj4 = std::string("4 0 obj\n<< /ModDate (") + modDate + ") >>\nendobj\n";
        } else {
            obj4 = "4 0 obj\n<< >>\nendobj\n";
        }
        
        std::string header = "%PDF-1.4\n";
        
        size_t offset = 0;
        write(fd, header.c_str(), header.size());
        offset += header.size();
        
        size_t off1 = offset;
        write(fd, obj1.c_str(), obj1.size());
        offset += obj1.size();
        
        size_t off2 = offset;
        write(fd, obj2.c_str(), obj2.size());
        offset += obj2.size();
        
        size_t off3 = offset;
        write(fd, obj3.c_str(), obj3.size());
        offset += obj3.size();
        
        size_t off4 = offset;
        write(fd, obj4.c_str(), obj4.size());
        offset += obj4.size();
        
        size_t xrefOff = offset;
        char xref[1024];
        snprintf(xref, sizeof(xref),
            "xref\n"
            "0 5\n"
            "0000000000 65535 f \n"
            "%010zu 00000 n \n"
            "%010zu 00000 n \n"
            "%010zu 00000 n \n"
            "%010zu 00000 n \n"
            "trailer\n<< /Size 5 /Root 1 0 R /Info 4 0 R >>\n"
            "startxref\n%zu\n%%%%EOF\n",
            off1, off2, off3, off4, xrefOff);
        write(fd, xref, strlen(xref));
        close(fd);
        
        gchar *uri = g_filename_to_uri(tmpname, nullptr, nullptr);
        GError *error = nullptr;
        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        unlink(tmpname);
        
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }
};

TEST_F(PopplerDocumentGetModificationDateTest_2188, NullDocumentReturnsNegativeOne_2188) {
    // Passing NULL should trigger g_return_val_if_fail and return (time_t)-1
    // Note: This will produce a GLib warning, but should not crash
    time_t result = poppler_document_get_modification_date(nullptr);
    EXPECT_EQ(result, (time_t)-1);
}

TEST_F(PopplerDocumentGetModificationDateTest_2188, DocumentWithValidModDateReturnsValidTime_2188) {
    // D:20230615120000Z is a valid PDF date: June 15, 2023, 12:00:00 UTC
    PopplerDocument *doc = createPdfWithModDate("D:20230615120000Z");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    time_t result = poppler_document_get_modification_date(doc);
    // The date should be a valid positive time_t (after epoch)
    EXPECT_NE(result, (time_t)-1);
    EXPECT_GT(result, (time_t)0);
    
    // Verify it's approximately correct (June 15, 2023 12:00:00 UTC)
    struct tm *tm_result = gmtime(&result);
    EXPECT_EQ(tm_result->tm_year + 1900, 2023);
    EXPECT_EQ(tm_result->tm_mon + 1, 6);
    EXPECT_EQ(tm_result->tm_mday, 15);
    EXPECT_EQ(tm_result->tm_hour, 12);
    EXPECT_EQ(tm_result->tm_min, 0);
    EXPECT_EQ(tm_result->tm_sec, 0);
    
    g_object_unref(doc);
}

TEST_F(PopplerDocumentGetModificationDateTest_2188, DocumentWithNoModDateReturnsNegativeOne_2188) {
    // Create a PDF with no ModDate field
    PopplerDocument *doc = createPdfWithModDate(nullptr);
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    time_t result = poppler_document_get_modification_date(doc);
    EXPECT_EQ(result, (time_t)-1);
    
    g_object_unref(doc);
}

TEST_F(PopplerDocumentGetModificationDateTest_2188, DocumentWithInvalidModDateReturnsNegativeOne_2188) {
    // Create a PDF with an invalid date string
    PopplerDocument *doc = createPdfWithModDate("not-a-date");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    time_t result = poppler_document_get_modification_date(doc);
    EXPECT_EQ(result, (time_t)-1);
    
    g_object_unref(doc);
}

TEST_F(PopplerDocumentGetModificationDateTest_2188, DocumentWithModDateEpochReturnsZero_2188) {
    // D:19700101000000Z should be epoch time 0
    PopplerDocument *doc = createPdfWithModDate("D:19700101000000Z");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    time_t result = poppler_document_get_modification_date(doc);
    // Should be 0 (epoch) or at least not -1
    if (result != (time_t)-1) {
        EXPECT_EQ(result, (time_t)0);
    }
    
    g_object_unref(doc);
}

TEST_F(PopplerDocumentGetModificationDateTest_2188, DocumentWithModDateWithTimezone_2188) {
    // D:20200101120000+05'30' - with timezone offset
    PopplerDocument *doc = createPdfWithModDate("D:20200101120000+05'30'");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    time_t result = poppler_document_get_modification_date(doc);
    // Should be a valid time, not -1
    EXPECT_NE(result, (time_t)-1);
    EXPECT_GT(result, (time_t)0);
    
    // 2020-01-01 12:00:00 +05:30 => 2020-01-01 06:30:00 UTC
    struct tm *tm_result = gmtime(&result);
    EXPECT_EQ(tm_result->tm_year + 1900, 2020);
    EXPECT_EQ(tm_result->tm_mon + 1, 1);
    EXPECT_EQ(tm_result->tm_mday, 1);
    EXPECT_EQ(tm_result->tm_hour, 6);
    EXPECT_EQ(tm_result->tm_min, 30);
    
    g_object_unref(doc);
}

TEST_F(PopplerDocumentGetModificationDateTest_2188, DocumentWithEmptyModDate_2188) {
    // Empty string as ModDate
    PopplerDocument *doc = createPdfWithModDate("");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    time_t result = poppler_document_get_modification_date(doc);
    EXPECT_EQ(result, (time_t)-1);
    
    g_object_unref(doc);
}

TEST_F(PopplerDocumentGetModificationDateTest_2188, DocumentWithPartialDate_2188) {
    // D:2023 - only year, partial date
    PopplerDocument *doc = createPdfWithModDate("D:2023");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    time_t result = poppler_document_get_modification_date(doc);
    // Depending on implementation, this might be valid or invalid
    // We just ensure it doesn't crash and returns a reasonable value
    // Either a valid time or -1
    if (result != (time_t)-1) {
        EXPECT_GT(result, (time_t)0);
    }
    
    g_object_unref(doc);
}

TEST_F(PopplerDocumentGetModificationDateTest_2188, DocumentWithNegativeTimezone_2188) {
    // D:20210701080000-07'00' - with negative timezone offset
    PopplerDocument *doc = createPdfWithModDate("D:20210701080000-07'00'");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    
    time_t result = poppler_document_get_modification_date(doc);
    EXPECT_NE(result, (time_t)-1);
    EXPECT_GT(result, (time_t)0);
    
    // 2021-07-01 08:00:00 -07:00 => 2021-07-01 15:00:00 UTC
    struct tm *tm_result = gmtime(&result);
    EXPECT_EQ(tm_result->tm_year + 1900, 2021);
    EXPECT_EQ(tm_result->tm_mon + 1, 7);
    EXPECT_EQ(tm_result->tm_mday, 1);
    EXPECT_EQ(tm_result->tm_hour, 15);
    EXPECT_EQ(tm_result->tm_min, 0);
    
    g_object_unref(doc);
}
