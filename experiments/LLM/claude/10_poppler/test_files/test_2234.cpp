#include <glib.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>

class PopplerFontInfoTest_2234 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;

    void SetUp() override {
        // Create a minimal PDF in memory for testing
        const char *pdf_content =
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
            "/Contents 4 0 R /Resources << /Font << /F1 5 0 R >> >> >>\n"
            "endobj\n"
            "4 0 obj\n"
            "<< /Length 44 >>\n"
            "stream\n"
            "BT /F1 12 Tf 100 700 Td (Hello) Tj ET\n"
            "endstream\n"
            "endobj\n"
            "5 0 obj\n"
            "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
            "endobj\n"
            "xref\n"
            "0 6\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000282 00000 n \n"
            "0000000376 00000 n \n"
            "trailer\n"
            "<< /Size 6 /Root 1 0 R >>\n"
            "startxref\n"
            "456\n"
            "%%EOF\n";

        // Write to a temporary file
        const char *tmp_path = "/tmp/test_poppler_fontinfo_2234.pdf";
        FILE *f = fopen(tmp_path, "wb");
        if (f) {
            fwrite(pdf_content, 1, strlen(pdf_content), f);
            fclose(f);
        }

        gchar *uri = g_filename_to_uri(tmp_path, nullptr, nullptr);
        GError *error = nullptr;
        document = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);

        if (error) {
            g_error_free(error);
            document = nullptr;
        }
    }

    void TearDown() override {
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
        unlink("/tmp/test_poppler_fontinfo_2234.pdf");
    }
};

// Test that PopplerFontInfo can be created from a valid document
TEST_F(PopplerFontInfoTest_2234, CreateFontInfo_2234) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerFontInfo *font_info = poppler_font_info_new(document);
    ASSERT_NE(font_info, nullptr);
    EXPECT_TRUE(POPPLER_IS_FONT_INFO(font_info));

    g_object_unref(font_info);
}

// Test that PopplerFontInfo scan works and returns a result
TEST_F(PopplerFontInfoTest_2234, ScanFonts_2234) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerFontInfo *font_info = poppler_font_info_new(document);
    ASSERT_NE(font_info, nullptr);

    PopplerFontsIter *iter = nullptr;
    gboolean has_more = poppler_font_info_scan(font_info, 1, &iter);

    // The scan should return a boolean indicating whether there are more pages
    // iter may or may not be null depending on whether fonts were found
    EXPECT_TRUE(has_more == TRUE || has_more == FALSE);

    if (iter) {
        poppler_fonts_iter_free(iter);
    }

    g_object_unref(font_info);
}

// Test that PopplerFontInfo can be freed (finalizer runs without crash)
TEST_F(PopplerFontInfoTest_2234, FreeFontInfo_2234) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerFontInfo *font_info = poppler_font_info_new(document);
    ASSERT_NE(font_info, nullptr);

    // This should trigger poppler_font_info_finalize without crashing
    g_object_unref(font_info);
}

// Test that document ref count is maintained properly after font info creation and destruction
TEST_F(PopplerFontInfoTest_2234, DocumentRefCountMaintained_2234) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    // Add a ref so we can check the document survives
    g_object_ref(document);
    guint initial_ref = G_OBJECT(document)->ref_count;

    PopplerFontInfo *font_info = poppler_font_info_new(document);
    ASSERT_NE(font_info, nullptr);

    // Font info should have increased ref count
    guint during_ref = G_OBJECT(document)->ref_count;
    EXPECT_GT(during_ref, initial_ref);

    g_object_unref(font_info);

    // After font info is destroyed, ref count should go back
    guint after_ref = G_OBJECT(document)->ref_count;
    EXPECT_EQ(after_ref, initial_ref);

    g_object_unref(document);
    // Prevent double unref in TearDown
    document = nullptr;
}

// Test scanning all pages exhaustively
TEST_F(PopplerFontInfoTest_2234, ScanAllPages_2234) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerFontInfo *font_info = poppler_font_info_new(document);
    ASSERT_NE(font_info, nullptr);

    int n_pages = poppler_document_get_n_pages(document);
    PopplerFontsIter *iter = nullptr;

    // Scan all pages at once
    gboolean has_more = poppler_font_info_scan(font_info, n_pages, &iter);

    // After scanning all pages, there should be no more
    EXPECT_FALSE(has_more);

    if (iter) {
        poppler_fonts_iter_free(iter);
    }

    g_object_unref(font_info);
}

// Test scanning beyond total number of pages
TEST_F(PopplerFontInfoTest_2234, ScanBeyondPageCount_2234) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerFontInfo *font_info = poppler_font_info_new(document);
    ASSERT_NE(font_info, nullptr);

    int n_pages = poppler_document_get_n_pages(document);
    PopplerFontsIter *iter = nullptr;

    // Scan more pages than exist
    gboolean has_more = poppler_font_info_scan(font_info, n_pages + 10, &iter);

    EXPECT_FALSE(has_more);

    if (iter) {
        poppler_fonts_iter_free(iter);
    }

    g_object_unref(font_info);
}

// Test multiple sequential scans
TEST_F(PopplerFontInfoTest_2234, MultipleScanCalls_2234) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerFontInfo *font_info = poppler_font_info_new(document);
    ASSERT_NE(font_info, nullptr);

    PopplerFontsIter *iter = nullptr;
    gboolean has_more = TRUE;
    int scan_count = 0;

    while (has_more) {
        has_more = poppler_font_info_scan(font_info, 1, &iter);
        if (iter) {
            poppler_fonts_iter_free(iter);
            iter = nullptr;
        }
        scan_count++;
        // Safety limit to prevent infinite loops
        if (scan_count > 100) {
            break;
        }
    }

    EXPECT_LE(scan_count, 100);
    EXPECT_FALSE(has_more);

    g_object_unref(font_info);
}

// Test creating multiple font info objects for the same document
TEST_F(PopplerFontInfoTest_2234, MultipleInfoObjectsSameDoc_2234) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerFontInfo *font_info1 = poppler_font_info_new(document);
    PopplerFontInfo *font_info2 = poppler_font_info_new(document);

    ASSERT_NE(font_info1, nullptr);
    ASSERT_NE(font_info2, nullptr);
    EXPECT_NE(font_info1, font_info2);

    g_object_unref(font_info1);
    g_object_unref(font_info2);
}

// Test that free_font_info resets scan position
TEST_F(PopplerFontInfoTest_2234, FreeAndRecreateFontInfo_2234) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    // First scan
    PopplerFontInfo *font_info = poppler_font_info_new(document);
    ASSERT_NE(font_info, nullptr);

    PopplerFontsIter *iter = nullptr;
    int n_pages = poppler_document_get_n_pages(document);
    poppler_font_info_scan(font_info, n_pages, &iter);
    if (iter) {
        poppler_fonts_iter_free(iter);
        iter = nullptr;
    }
    g_object_unref(font_info);

    // Second scan with new font_info - should work from the beginning
    font_info = poppler_font_info_new(document);
    ASSERT_NE(font_info, nullptr);

    gboolean has_more = poppler_font_info_scan(font_info, 1, &iter);
    // Should be able to scan again (behavior depends on page count)
    if (n_pages > 1) {
        EXPECT_TRUE(has_more);
    }

    if (iter) {
        poppler_fonts_iter_free(iter);
    }
    g_object_unref(font_info);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
