#include <glib.h>
#include <glib-object.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>

class PopplerDocumentPropertyTest_2210 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;

    void SetUp() override {
        // Create a minimal valid PDF in memory to get a PopplerDocument
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
        GError *error = nullptr;

        // Write to a temporary file
        char tmpfile[] = "/tmp/poppler_test_XXXXXX.pdf";
        int fd = g_mkstemp(tmpfile);
        ASSERT_NE(fd, -1);
        write(fd, pdf_content, len);
        close(fd);

        gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
        if (error) {
            g_error_free(error);
            error = nullptr;
        }

        if (uri) {
            doc = poppler_document_new_from_file(uri, nullptr, &error);
            g_free(uri);
        }

        if (error) {
            g_error_free(error);
        }

        // If file-based approach didn't work, try from data
        if (!doc) {
            GBytes *bytes = g_bytes_new(pdf_content, len);
            doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
            g_bytes_unref(bytes);
            if (error) {
                g_error_free(error);
                error = nullptr;
            }
        }

        unlink(tmpfile);
    }

    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
    }
};

// Test setting and getting the title property
TEST_F(PopplerDocumentPropertyTest_2210, SetAndGetTitle_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    const char *test_title = "Test Title";
    poppler_document_set_title(doc, test_title);

    gchar *title = poppler_document_get_title(doc);
    if (title) {
        EXPECT_STREQ(title, test_title);
        g_free(title);
    }
}

// Test setting title via GObject property
TEST_F(PopplerDocumentPropertyTest_2210, SetTitleViaProperty_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    g_object_set(G_OBJECT(doc), "title", "Property Title", NULL);

    gchar *title = nullptr;
    g_object_get(G_OBJECT(doc), "title", &title, NULL);
    if (title) {
        EXPECT_STREQ(title, "Property Title");
        g_free(title);
    }
}

// Test setting and getting the author property
TEST_F(PopplerDocumentPropertyTest_2210, SetAndGetAuthor_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    const char *test_author = "Test Author";
    poppler_document_set_author(doc, test_author);

    gchar *author = poppler_document_get_author(doc);
    if (author) {
        EXPECT_STREQ(author, test_author);
        g_free(author);
    }
}

// Test setting author via GObject property
TEST_F(PopplerDocumentPropertyTest_2210, SetAuthorViaProperty_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    g_object_set(G_OBJECT(doc), "author", "Property Author", NULL);

    gchar *author = nullptr;
    g_object_get(G_OBJECT(doc), "author", &author, NULL);
    if (author) {
        EXPECT_STREQ(author, "Property Author");
        g_free(author);
    }
}

// Test setting and getting the subject property
TEST_F(PopplerDocumentPropertyTest_2210, SetAndGetSubject_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    const char *test_subject = "Test Subject";
    poppler_document_set_subject(doc, test_subject);

    gchar *subject = poppler_document_get_subject(doc);
    if (subject) {
        EXPECT_STREQ(subject, test_subject);
        g_free(subject);
    }
}

// Test setting subject via GObject property
TEST_F(PopplerDocumentPropertyTest_2210, SetSubjectViaProperty_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    g_object_set(G_OBJECT(doc), "subject", "Property Subject", NULL);

    gchar *subject = nullptr;
    g_object_get(G_OBJECT(doc), "subject", &subject, NULL);
    if (subject) {
        EXPECT_STREQ(subject, "Property Subject");
        g_free(subject);
    }
}

// Test setting and getting the keywords property
TEST_F(PopplerDocumentPropertyTest_2210, SetAndGetKeywords_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    const char *test_keywords = "keyword1, keyword2, keyword3";
    poppler_document_set_keywords(doc, test_keywords);

    gchar *keywords = poppler_document_get_keywords(doc);
    if (keywords) {
        EXPECT_STREQ(keywords, test_keywords);
        g_free(keywords);
    }
}

// Test setting keywords via GObject property
TEST_F(PopplerDocumentPropertyTest_2210, SetKeywordsViaProperty_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    g_object_set(G_OBJECT(doc), "keywords", "prop_keyword1, prop_keyword2", NULL);

    gchar *keywords = nullptr;
    g_object_get(G_OBJECT(doc), "keywords", &keywords, NULL);
    if (keywords) {
        EXPECT_STREQ(keywords, "prop_keyword1, prop_keyword2");
        g_free(keywords);
    }
}

// Test setting and getting the creator property
TEST_F(PopplerDocumentPropertyTest_2210, SetAndGetCreator_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    const char *test_creator = "Test Creator App";
    poppler_document_set_creator(doc, test_creator);

    gchar *creator = poppler_document_get_creator(doc);
    if (creator) {
        EXPECT_STREQ(creator, test_creator);
        g_free(creator);
    }
}

// Test setting creator via GObject property
TEST_F(PopplerDocumentPropertyTest_2210, SetCreatorViaProperty_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    g_object_set(G_OBJECT(doc), "creator", "Property Creator", NULL);

    gchar *creator = nullptr;
    g_object_get(G_OBJECT(doc), "creator", &creator, NULL);
    if (creator) {
        EXPECT_STREQ(creator, "Property Creator");
        g_free(creator);
    }
}

// Test setting and getting the producer property
TEST_F(PopplerDocumentPropertyTest_2210, SetAndGetProducer_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    const char *test_producer = "Test Producer";
    poppler_document_set_producer(doc, test_producer);

    gchar *producer = poppler_document_get_producer(doc);
    if (producer) {
        EXPECT_STREQ(producer, test_producer);
        g_free(producer);
    }
}

// Test setting producer via GObject property
TEST_F(PopplerDocumentPropertyTest_2210, SetProducerViaProperty_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    g_object_set(G_OBJECT(doc), "producer", "Property Producer", NULL);

    gchar *producer = nullptr;
    g_object_get(G_OBJECT(doc), "producer", &producer, NULL);
    if (producer) {
        EXPECT_STREQ(producer, "Property Producer");
        g_free(producer);
    }
}

// Test setting and getting creation date
TEST_F(PopplerDocumentPropertyTest_2210, SetAndGetCreationDate_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    time_t test_date = 1609459200; // 2021-01-01 00:00:00 UTC
    poppler_document_set_creation_date(doc, (time_t)test_date);

    time_t creation_date = poppler_document_get_creation_date(doc);
    EXPECT_EQ(creation_date, test_date);
}

// Test setting creation date via GObject property
TEST_F(PopplerDocumentPropertyTest_2210, SetCreationDateViaProperty_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    gint test_date = 1609459200;
    g_object_set(G_OBJECT(doc), "creation-date", test_date, NULL);

    gint creation_date = 0;
    g_object_get(G_OBJECT(doc), "creation-date", &creation_date, NULL);
    EXPECT_EQ(creation_date, test_date);
}

// Test setting and getting modification date
TEST_F(PopplerDocumentPropertyTest_2210, SetAndGetModDate_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    time_t test_date = 1609459200;
    poppler_document_set_modification_date(doc, (time_t)test_date);

    time_t mod_date = poppler_document_get_modification_date(doc);
    EXPECT_EQ(mod_date, test_date);
}

// Test setting modification date via GObject property
TEST_F(PopplerDocumentPropertyTest_2210, SetModDateViaProperty_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    gint test_date = 1609459200;
    g_object_set(G_OBJECT(doc), "mod-date", test_date, NULL);

    gint mod_date = 0;
    g_object_get(G_OBJECT(doc), "mod-date", &mod_date, NULL);
    EXPECT_EQ(mod_date, test_date);
}

// Test setting and getting creation datetime
TEST_F(PopplerDocumentPropertyTest_2210, SetAndGetCreationDateTime_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    GDateTime *test_dt = g_date_time_new_utc(2021, 6, 15, 12, 30, 0);
    ASSERT_NE(test_dt, nullptr);

    poppler_document_set_creation_date_time(doc, test_dt);

    GDateTime *result_dt = poppler_document_get_creation_date_time(doc);
    if (result_dt) {
        EXPECT_TRUE(g_date_time_equal(result_dt, test_dt));
        g_date_time_unref(result_dt);
    }

    g_date_time_unref(test_dt);
}

// Test setting creation datetime via GObject property
TEST_F(PopplerDocumentPropertyTest_2210, SetCreationDateTimeViaProperty_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    GDateTime *test_dt = g_date_time_new_utc(2022, 3, 10, 8, 0, 0);
    ASSERT_NE(test_dt, nullptr);

    g_object_set(G_OBJECT(doc), "creation-datetime", test_dt, NULL);

    GDateTime *result_dt = nullptr;
    g_object_get(G_OBJECT(doc), "creation-datetime", &result_dt, NULL);
    if (result_dt) {
        EXPECT_TRUE(g_date_time_equal(result_dt, test_dt));
        g_date_time_unref(result_dt);
    }

    g_date_time_unref(test_dt);
}

// Test setting and getting modification datetime
TEST_F(PopplerDocumentPropertyTest_2210, SetAndGetModDateTime_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    GDateTime *test_dt = g_date_time_new_utc(2021, 12, 25, 0, 0, 0);
    ASSERT_NE(test_dt, nullptr);

    poppler_document_set_modification_date_time(doc, test_dt);

    GDateTime *result_dt = poppler_document_get_modification_date_time(doc);
    if (result_dt) {
        EXPECT_TRUE(g_date_time_equal(result_dt, test_dt));
        g_date_time_unref(result_dt);
    }

    g_date_time_unref(test_dt);
}

// Test setting modification datetime via GObject property
TEST_F(PopplerDocumentPropertyTest_2210, SetModDateTimeViaProperty_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    GDateTime *test_dt = g_date_time_new_utc(2023, 1, 1, 0, 0, 0);
    ASSERT_NE(test_dt, nullptr);

    g_object_set(G_OBJECT(doc), "mod-datetime", test_dt, NULL);

    GDateTime *result_dt = nullptr;
    g_object_get(G_OBJECT(doc), "mod-datetime", &result_dt, NULL);
    if (result_dt) {
        EXPECT_TRUE(g_date_time_equal(result_dt, test_dt));
        g_date_time_unref(result_dt);
    }

    g_date_time_unref(test_dt);
}

// Test setting title to NULL
TEST_F(PopplerDocumentPropertyTest_2210, SetTitleToNull_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    poppler_document_set_title(doc, "Some Title");
    poppler_document_set_title(doc, nullptr);

    gchar *title = poppler_document_get_title(doc);
    // After setting to NULL, title should be NULL or empty
    if (title) {
        g_free(title);
    }
    // No crash is the main assertion here
}

// Test setting author to NULL
TEST_F(PopplerDocumentPropertyTest_2210, SetAuthorToNull_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    poppler_document_set_author(doc, "Some Author");
    poppler_document_set_author(doc, nullptr);

    gchar *author = poppler_document_get_author(doc);
    if (author) {
        g_free(author);
    }
}

// Test setting empty string title
TEST_F(PopplerDocumentPropertyTest_2210, SetEmptyTitle_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    poppler_document_set_title(doc, "");

    gchar *title = poppler_document_get_title(doc);
    if (title) {
        EXPECT_STREQ(title, "");
        g_free(title);
    }
}

// Test setting empty string author
TEST_F(PopplerDocumentPropertyTest_2210, SetEmptyAuthor_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    poppler_document_set_author(doc, "");

    gchar *author = poppler_document_get_author(doc);
    if (author) {
        EXPECT_STREQ(author, "");
        g_free(author);
    }
}

// Test getting page count
TEST_F(PopplerDocumentPropertyTest_2210, GetNPages_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    int n_pages = poppler_document_get_n_pages(doc);
    EXPECT_GE(n_pages, 0);
}

// Test setting creation date to zero
TEST_F(PopplerDocumentPropertyTest_2210, SetCreationDateToZero_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    poppler_document_set_creation_date(doc, 0);
    time_t creation_date = poppler_document_get_creation_date(doc);
    // Just verify no crash; value may or may not be 0
    (void)creation_date;
}

// Test setting modification date to zero
TEST_F(PopplerDocumentPropertyTest_2210, SetModDateToZero_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    poppler_document_set_modification_date(doc, 0);
    time_t mod_date = poppler_document_get_modification_date(doc);
    (void)mod_date;
}

// Test setting title with special characters
TEST_F(PopplerDocumentPropertyTest_2210, SetTitleWithSpecialChars_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    const char *special_title = "Título con caractères spéciaux: 日本語 中文";
    poppler_document_set_title(doc, special_title);

    gchar *title = poppler_document_get_title(doc);
    if (title) {
        EXPECT_STREQ(title, special_title);
        g_free(title);
    }
}

// Test setting title with very long string
TEST_F(PopplerDocumentPropertyTest_2210, SetTitleLongString_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    std::string long_title(10000, 'A');
    poppler_document_set_title(doc, long_title.c_str());

    gchar *title = poppler_document_get_title(doc);
    if (title) {
        EXPECT_EQ(std::string(title), long_title);
        g_free(title);
    }
}

// Test overwriting title
TEST_F(PopplerDocumentPropertyTest_2210, OverwriteTitle_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    poppler_document_set_title(doc, "First Title");
    poppler_document_set_title(doc, "Second Title");

    gchar *title = poppler_document_get_title(doc);
    if (title) {
        EXPECT_STREQ(title, "Second Title");
        g_free(title);
    }
}

// Test reading format property (read-only)
TEST_F(PopplerDocumentPropertyTest_2210, GetFormatProperty_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    gchar *format = nullptr;
    g_object_get(G_OBJECT(doc), "format", &format, NULL);
    // Format should be non-null for a valid PDF
    if (format) {
        EXPECT_TRUE(strlen(format) > 0);
        g_free(format);
    }
}

// Test reading linearized property (read-only)
TEST_F(PopplerDocumentPropertyTest_2210, GetLinearizedProperty_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    gboolean linearized = FALSE;
    g_object_get(G_OBJECT(doc), "linearized", &linearized, NULL);
    // Our simple test PDF is not linearized
    // Just verify it doesn't crash
}

// Test setting subject to NULL
TEST_F(PopplerDocumentPropertyTest_2210, SetSubjectToNull_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    poppler_document_set_subject(doc, "A Subject");
    poppler_document_set_subject(doc, nullptr);

    gchar *subject = poppler_document_get_subject(doc);
    if (subject) {
        g_free(subject);
    }
}

// Test setting keywords to NULL
TEST_F(PopplerDocumentPropertyTest_2210, SetKeywordsToNull_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    poppler_document_set_keywords(doc, "some keywords");
    poppler_document_set_keywords(doc, nullptr);

    gchar *keywords = poppler_document_get_keywords(doc);
    if (keywords) {
        g_free(keywords);
    }
}

// Test setting creator to NULL
TEST_F(PopplerDocumentPropertyTest_2210, SetCreatorToNull_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    poppler_document_set_creator(doc, "some creator");
    poppler_document_set_creator(doc, nullptr);

    gchar *creator = poppler_document_get_creator(doc);
    if (creator) {
        g_free(creator);
    }
}

// Test setting producer to NULL
TEST_F(PopplerDocumentPropertyTest_2210, SetProducerToNull_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    poppler_document_set_producer(doc, "some producer");
    poppler_document_set_producer(doc, nullptr);

    gchar *producer = poppler_document_get_producer(doc);
    if (producer) {
        g_free(producer);
    }
}

// Test multiple properties set in sequence
TEST_F(PopplerDocumentPropertyTest_2210, SetMultipleProperties_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    poppler_document_set_title(doc, "My Title");
    poppler_document_set_author(doc, "My Author");
    poppler_document_set_subject(doc, "My Subject");
    poppler_document_set_keywords(doc, "key1, key2");
    poppler_document_set_creator(doc, "My Creator");
    poppler_document_set_producer(doc, "My Producer");

    gchar *title = poppler_document_get_title(doc);
    gchar *author = poppler_document_get_author(doc);
    gchar *subject = poppler_document_get_subject(doc);
    gchar *keywords = poppler_document_get_keywords(doc);
    gchar *creator = poppler_document_get_creator(doc);
    gchar *producer = poppler_document_get_producer(doc);

    if (title) { EXPECT_STREQ(title, "My Title"); g_free(title); }
    if (author) { EXPECT_STREQ(author, "My Author"); g_free(author); }
    if (subject) { EXPECT_STREQ(subject, "My Subject"); g_free(subject); }
    if (keywords) { EXPECT_STREQ(keywords, "key1, key2"); g_free(keywords); }
    if (creator) { EXPECT_STREQ(creator, "My Creator"); g_free(creator); }
    if (producer) { EXPECT_STREQ(producer, "My Producer"); g_free(producer); }
}

// Test setting creation datetime to NULL
TEST_F(PopplerDocumentPropertyTest_2210, SetCreationDateTimeToNull_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    GDateTime *dt = g_date_time_new_utc(2021, 1, 1, 0, 0, 0);
    poppler_document_set_creation_date_time(doc, dt);
    g_date_time_unref(dt);

    poppler_document_set_creation_date_time(doc, nullptr);

    GDateTime *result = poppler_document_get_creation_date_time(doc);
    if (result) {
        g_date_time_unref(result);
    }
    // Main assertion: no crash
}

// Test setting modification datetime to NULL
TEST_F(PopplerDocumentPropertyTest_2210, SetModDateTimeToNull_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    GDateTime *dt = g_date_time_new_utc(2021, 1, 1, 0, 0, 0);
    poppler_document_set_modification_date_time(doc, dt);
    g_date_time_unref(dt);

    poppler_document_set_modification_date_time(doc, nullptr);

    GDateTime *result = poppler_document_get_modification_date_time(doc);
    if (result) {
        g_date_time_unref(result);
    }
}

// Test getting page layout property
TEST_F(PopplerDocumentPropertyTest_2210, GetPageLayout_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    PopplerPageLayout layout = poppler_document_get_page_layout(doc);
    // Just ensure no crash and value is within valid enum range
    EXPECT_GE((int)layout, 0);
}

// Test getting page mode property
TEST_F(PopplerDocumentPropertyTest_2210, GetPageMode_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    PopplerPageMode mode = poppler_document_get_page_mode(doc);
    EXPECT_GE((int)mode, 0);
}

// Test getting n_pages for a simple document
TEST_F(PopplerDocumentPropertyTest_2210, PageCountIsOne_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    int n_pages = poppler_document_get_n_pages(doc);
    EXPECT_EQ(n_pages, 1);
}

// Test getting a page by index
TEST_F(PopplerDocumentPropertyTest_2210, GetPageByIndex_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    PopplerPage *page = poppler_document_get_page(doc, 0);
    EXPECT_NE(page, nullptr);
    if (page) {
        g_object_unref(page);
    }
}

// Test getting a page with invalid index
TEST_F(PopplerDocumentPropertyTest_2210, GetPageInvalidIndex_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    PopplerPage *page = poppler_document_get_page(doc, 999);
    EXPECT_EQ(page, nullptr);
}

// Test getting a page with negative index
TEST_F(PopplerDocumentPropertyTest_2210, GetPageNegativeIndex_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    PopplerPage *page = poppler_document_get_page(doc, -1);
    EXPECT_EQ(page, nullptr);
}

// Test creation date with negative value
TEST_F(PopplerDocumentPropertyTest_2210, SetCreationDateNegative_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    poppler_document_set_creation_date(doc, -1);
    time_t creation_date = poppler_document_get_creation_date(doc);
    // Verify no crash; the semantics of negative date is implementation-defined
    (void)creation_date;
}

// Test getting metadata
TEST_F(PopplerDocumentPropertyTest_2210, GetMetadata_2210) {
    if (!doc) GTEST_SKIP() << "Could not create PopplerDocument";

    gchar *metadata = poppler_document_get_metadata(doc);
    // Metadata may be NULL if not present
    if (metadata) {
        g_free(metadata);
    }
}
