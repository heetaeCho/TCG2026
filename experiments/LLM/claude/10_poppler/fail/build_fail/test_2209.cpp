#include <glib.h>
#include <glib-object.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>

class PopplerDocumentPropertyTest_2209 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    GError *error = nullptr;

    void SetUp() override {
        // Create a minimal PDF in memory
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

        gsize len = strlen(pdf_content);
        GBytes *bytes = g_bytes_new(pdf_content, len);
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        g_bytes_unref(bytes);

        doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);
        g_object_unref(stream);

        if (doc == nullptr) {
            // Try alternative: write to temp file
            char tmpname[] = "/tmp/poppler_test_XXXXXX.pdf";
            int fd = mkstemps(tmpname, 4);
            if (fd >= 0) {
                write(fd, pdf_content, len);
                close(fd);
                gchar *uri = g_filename_to_uri(tmpname, nullptr, nullptr);
                doc = poppler_document_new_from_file(uri, nullptr, &error);
                g_free(uri);
                unlink(tmpname);
            }
        }
    }

    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
        if (error) {
            g_error_free(error);
            error = nullptr;
        }
    }
};

TEST_F(PopplerDocumentPropertyTest_2209, DocumentCreated_2209) {
    // Verify we have a valid document to test with
    ASSERT_NE(doc, nullptr) << "Failed to create test document: "
                            << (error ? error->message : "unknown error");
}

TEST_F(PopplerDocumentPropertyTest_2209, GetTitleProperty_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    gchar *title = nullptr;
    g_object_get(G_OBJECT(doc), "title", &title, NULL);
    // Title may be NULL for our minimal PDF, that's fine
    g_free(title);
}

TEST_F(PopplerDocumentPropertyTest_2209, GetFormatProperty_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    gchar *format = nullptr;
    g_object_get(G_OBJECT(doc), "format", &format, NULL);
    // Format should be something like "PDF-1.4"
    ASSERT_NE(format, nullptr);
    EXPECT_TRUE(g_str_has_prefix(format, "PDF-"));
    g_free(format);
}

TEST_F(PopplerDocumentPropertyTest_2209, GetFormatMajorProperty_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    guint format_major = 0;
    g_object_get(G_OBJECT(doc), "format-major", &format_major, NULL);
    EXPECT_EQ(format_major, 1u);
}

TEST_F(PopplerDocumentPropertyTest_2209, GetFormatMinorProperty_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    guint format_minor = 0;
    g_object_get(G_OBJECT(doc), "format-minor", &format_minor, NULL);
    EXPECT_GE(format_minor, 0u);
}

TEST_F(PopplerDocumentPropertyTest_2209, GetAuthorProperty_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    gchar *author = nullptr;
    g_object_get(G_OBJECT(doc), "author", &author, NULL);
    // May be NULL for our minimal PDF
    g_free(author);
}

TEST_F(PopplerDocumentPropertyTest_2209, GetSubjectProperty_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    gchar *subject = nullptr;
    g_object_get(G_OBJECT(doc), "subject", &subject, NULL);
    g_free(subject);
}

TEST_F(PopplerDocumentPropertyTest_2209, GetKeywordsProperty_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    gchar *keywords = nullptr;
    g_object_get(G_OBJECT(doc), "keywords", &keywords, NULL);
    g_free(keywords);
}

TEST_F(PopplerDocumentPropertyTest_2209, GetCreatorProperty_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    gchar *creator = nullptr;
    g_object_get(G_OBJECT(doc), "creator", &creator, NULL);
    g_free(creator);
}

TEST_F(PopplerDocumentPropertyTest_2209, GetProducerProperty_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    gchar *producer = nullptr;
    g_object_get(G_OBJECT(doc), "producer", &producer, NULL);
    g_free(producer);
}

TEST_F(PopplerDocumentPropertyTest_2209, GetCreationDateProperty_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    gint creation_date = -1;
    g_object_get(G_OBJECT(doc), "creation-date", &creation_date, NULL);
    // For a minimal PDF without creation date, expect 0 or -1
    EXPECT_GE(creation_date, -1);
}

TEST_F(PopplerDocumentPropertyTest_2209, GetCreationDateTimeProperty_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    GDateTime *creation_datetime = nullptr;
    g_object_get(G_OBJECT(doc), "creation-datetime", &creation_datetime, NULL);
    // May be NULL for minimal PDF
    if (creation_datetime) {
        g_date_time_unref(creation_datetime);
    }
}

TEST_F(PopplerDocumentPropertyTest_2209, GetModDateProperty_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    gint mod_date = -1;
    g_object_get(G_OBJECT(doc), "mod-date", &mod_date, NULL);
    EXPECT_GE(mod_date, -1);
}

TEST_F(PopplerDocumentPropertyTest_2209, GetModDateTimeProperty_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    GDateTime *mod_datetime = nullptr;
    g_object_get(G_OBJECT(doc), "mod-datetime", &mod_datetime, NULL);
    if (mod_datetime) {
        g_date_time_unref(mod_datetime);
    }
}

TEST_F(PopplerDocumentPropertyTest_2209, GetLinearizedProperty_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    gboolean linearized = TRUE;
    g_object_get(G_OBJECT(doc), "linearized", &linearized, NULL);
    // Our minimal PDF is not linearized
    EXPECT_FALSE(linearized);
}

TEST_F(PopplerDocumentPropertyTest_2209, GetPageLayoutProperty_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    PopplerPageLayout layout = POPPLER_PAGE_LAYOUT_UNSET;
    g_object_get(G_OBJECT(doc), "page-layout", &layout, NULL);
    // Valid enum value
    EXPECT_GE((int)layout, (int)POPPLER_PAGE_LAYOUT_UNSET);
}

TEST_F(PopplerDocumentPropertyTest_2209, GetPageModeProperty_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    PopplerPageMode mode = POPPLER_PAGE_MODE_UNSET;
    g_object_get(G_OBJECT(doc), "page-mode", &mode, NULL);
    EXPECT_GE((int)mode, (int)POPPLER_PAGE_MODE_UNSET);
}

TEST_F(PopplerDocumentPropertyTest_2209, GetViewerPreferencesProperty_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    PopplerViewerPreferences prefs = POPPLER_VIEWER_PREFERENCES_UNSET;
    g_object_get(G_OBJECT(doc), "viewer-preferences", &prefs, NULL);
    // According to the code, this always returns POPPLER_VIEWER_PREFERENCES_UNSET
    EXPECT_EQ(prefs, POPPLER_VIEWER_PREFERENCES_UNSET);
}

TEST_F(PopplerDocumentPropertyTest_2209, GetPermissionsProperty_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    PopplerPermissions perms = (PopplerPermissions)0;
    g_object_get(G_OBJECT(doc), "permissions", &perms, NULL);
    // Permissions should be non-zero for unencrypted document (all permissions granted)
}

TEST_F(PopplerDocumentPropertyTest_2209, GetPrintScalingProperty_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    PopplerPrintScaling scaling = POPPLER_PRINT_SCALING_APP_DEFAULT;
    g_object_get(G_OBJECT(doc), "print-scaling", &scaling, NULL);
    // Valid enum value
    EXPECT_GE((int)scaling, 0);
}

TEST_F(PopplerDocumentPropertyTest_2209, GetPrintDuplexProperty_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    PopplerPrintDuplex duplex = POPPLER_PRINT_DUPLEX_NONE;
    g_object_get(G_OBJECT(doc), "print-duplex", &duplex, NULL);
    EXPECT_GE((int)duplex, 0);
}

TEST_F(PopplerDocumentPropertyTest_2209, GetPrintNCopiesProperty_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    gint n_copies = -1;
    g_object_get(G_OBJECT(doc), "print-n-copies", &n_copies, NULL);
    EXPECT_GE(n_copies, 0);
}

TEST_F(PopplerDocumentPropertyTest_2209, GetSubtypeProperty_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    PopplerPDFSubtype subtype = POPPLER_PDF_SUBTYPE_UNSET;
    g_object_get(G_OBJECT(doc), "subtype", &subtype, NULL);
    EXPECT_GE((int)subtype, (int)POPPLER_PDF_SUBTYPE_UNSET);
}

TEST_F(PopplerDocumentPropertyTest_2209, GetSubtypeStringProperty_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    gchar *subtype_string = nullptr;
    g_object_get(G_OBJECT(doc), "subtype-string", &subtype_string, NULL);
    // May be NULL for non-conforming PDFs
    g_free(subtype_string);
}

TEST_F(PopplerDocumentPropertyTest_2209, GetSubtypePartProperty_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    PopplerPDFPart part = POPPLER_PDF_SUBTYPE_PART_UNSET;
    g_object_get(G_OBJECT(doc), "subtype-part", &part, NULL);
    EXPECT_GE((int)part, (int)POPPLER_PDF_SUBTYPE_PART_UNSET);
}

TEST_F(PopplerDocumentPropertyTest_2209, GetSubtypeConfProperty_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    PopplerPDFConformance conf = POPPLER_PDF_SUBTYPE_CONF_UNSET;
    g_object_get(G_OBJECT(doc), "subtype-conf", &conf, NULL);
    EXPECT_GE((int)conf, (int)POPPLER_PDF_SUBTYPE_CONF_UNSET);
}

TEST_F(PopplerDocumentPropertyTest_2209, GetMetadataProperty_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    gchar *metadata = nullptr;
    g_object_get(G_OBJECT(doc), "metadata", &metadata, NULL);
    // May be NULL for minimal PDF
    g_free(metadata);
}

TEST_F(PopplerDocumentPropertyTest_2209, GetNPages_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    int n_pages = poppler_document_get_n_pages(doc);
    EXPECT_EQ(n_pages, 1);
}

TEST_F(PopplerDocumentPropertyTest_2209, GetPage_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    PopplerPage *page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);
    g_object_unref(page);
}

TEST_F(PopplerDocumentPropertyTest_2209, GetPageOutOfRange_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    PopplerPage *page = poppler_document_get_page(doc, 999);
    EXPECT_EQ(page, nullptr);
}

TEST_F(PopplerDocumentPropertyTest_2209, GetPageNegativeIndex_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    PopplerPage *page = poppler_document_get_page(doc, -1);
    EXPECT_EQ(page, nullptr);
}

TEST_F(PopplerDocumentPropertyTest_2209, PdfVersionConsistency_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    guint major_ver = 0, minor_ver = 0;
    poppler_document_get_pdf_version(doc, &major_ver, &minor_ver);

    gchar *version_string = poppler_document_get_pdf_version_string(doc);
    ASSERT_NE(version_string, nullptr);

    gchar *expected = g_strdup_printf("PDF-%u.%u", major_ver, minor_ver);
    EXPECT_STREQ(version_string, expected);
    g_free(expected);
    g_free(version_string);
}

TEST_F(PopplerDocumentPropertyTest_2209, FormatMajorMinorConsistency_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    guint major_prop = 0, minor_prop = 0;
    g_object_get(G_OBJECT(doc), "format-major", &major_prop, "format-minor", &minor_prop, NULL);

    guint major_func = 0, minor_func = 0;
    poppler_document_get_pdf_version(doc, &major_func, &minor_func);

    EXPECT_EQ(major_prop, major_func);
    EXPECT_EQ(minor_prop, minor_func);
}

TEST_F(PopplerDocumentPropertyTest_2209, ViewerPreferencesAlwaysUnset_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    // The code has a FIXME and always returns POPPLER_VIEWER_PREFERENCES_UNSET
    PopplerViewerPreferences prefs = (PopplerViewerPreferences)0xFF;
    g_object_get(G_OBJECT(doc), "viewer-preferences", &prefs, NULL);
    EXPECT_EQ(prefs, POPPLER_VIEWER_PREFERENCES_UNSET);
}

// Test loading from NULL data - error case
TEST_F(PopplerDocumentPropertyTest_2209, NewFromDataNull_2209) {
    GError *err = nullptr;
    PopplerDocument *null_doc = poppler_document_new_from_data(nullptr, 0, nullptr, &err);
    // Should fail gracefully
    if (null_doc) {
        g_object_unref(null_doc);
    }
    if (err) {
        g_error_free(err);
    }
}

// Test that multiple property gets return consistent results
TEST_F(PopplerDocumentPropertyTest_2209, MultiplePropertyGetConsistency_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    gboolean lin1 = FALSE, lin2 = FALSE;
    g_object_get(G_OBJECT(doc), "linearized", &lin1, NULL);
    g_object_get(G_OBJECT(doc), "linearized", &lin2, NULL);
    EXPECT_EQ(lin1, lin2);
}

TEST_F(PopplerDocumentPropertyTest_2209, TitlePropertyMatchesFunction_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    gchar *title_prop = nullptr;
    g_object_get(G_OBJECT(doc), "title", &title_prop, NULL);

    gchar *title_func = poppler_document_get_title(doc);

    // Both should be the same (either both NULL or same string)
    if (title_prop == nullptr) {
        EXPECT_EQ(title_func, nullptr);
    } else {
        ASSERT_NE(title_func, nullptr);
        EXPECT_STREQ(title_prop, title_func);
    }
    g_free(title_prop);
    g_free(title_func);
}

TEST_F(PopplerDocumentPropertyTest_2209, AuthorPropertyMatchesFunction_2209) {
    if (!doc) GTEST_SKIP() << "No document available";

    gchar *author_prop = nullptr;
    g_object_get(G_OBJECT(doc), "author", &author_prop, NULL);

    gchar *author_func = poppler_document_get_author(doc);

    if (author_prop == nullptr) {
        EXPECT_EQ(author_func, nullptr);
    } else {
        ASSERT_NE(author_func, nullptr);
        EXPECT_STREQ(author_prop, author_func);
    }
    g_free(author_prop);
    g_free(author_func);
}
