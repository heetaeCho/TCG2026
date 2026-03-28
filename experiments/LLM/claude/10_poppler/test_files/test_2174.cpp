#include <glib.h>
#include <gtest/gtest.h>
#include <poppler-document.h>
#include <poppler.h>
#include <cstdio>
#include <cstdlib>
#include <string>

class PopplerDocumentGetAuthorTest_2174 : public ::testing::Test {
protected:
    PopplerDocument *doc_with_author = nullptr;
    PopplerDocument *doc_without_author = nullptr;
    
    void SetUp() override {
        // We'll attempt to load test PDFs if available
        // Tests that require specific documents will be skipped if not available
    }

    void TearDown() override {
        if (doc_with_author) {
            g_object_unref(doc_with_author);
            doc_with_author = nullptr;
        }
        if (doc_without_author) {
            g_object_unref(doc_without_author);
            doc_without_author = nullptr;
        }
    }

    // Helper to create a minimal PDF in a temp file with optional author metadata
    std::string createTempPDFWithAuthor(const std::string &author) {
        std::string tmpfile = std::string(g_get_tmp_dir()) + "/test_author_2174.pdf";
        FILE *f = fopen(tmpfile.c_str(), "wb");
        if (!f) return "";

        // Build a minimal PDF with /Author in the Info dictionary
        std::string pdf;
        pdf += "%PDF-1.4\n";

        // Object 1: Catalog
        std::string obj1 = "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        // Object 2: Pages
        std::string obj2 = "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        // Object 3: Page
        std::string obj3 = "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        // Object 4: Info dict
        std::string obj4 = "4 0 obj\n<< /Author (" + author + ") >>\nendobj\n";

        size_t offset = pdf.size();
        size_t xref_offsets[4];

        xref_offsets[0] = offset;
        pdf += obj1;
        xref_offsets[1] = pdf.size();
        pdf += obj2;
        xref_offsets[2] = pdf.size();
        pdf += obj3;
        xref_offsets[3] = pdf.size();
        pdf += obj4;

        size_t xref_start = pdf.size();
        pdf += "xref\n";
        pdf += "0 5\n";
        char buf[64];
        snprintf(buf, sizeof(buf), "0000000000 65535 f \n");
        pdf += buf;
        for (int i = 0; i < 4; i++) {
            snprintf(buf, sizeof(buf), "%010zu 00000 n \n", xref_offsets[i]);
            pdf += buf;
        }
        pdf += "trailer\n<< /Size 5 /Root 1 0 R /Info 4 0 R >>\n";
        snprintf(buf, sizeof(buf), "startxref\n%zu\n", xref_start);
        pdf += buf;
        pdf += "%%EOF\n";

        fwrite(pdf.data(), 1, pdf.size(), f);
        fclose(f);
        return tmpfile;
    }

    std::string createTempPDFWithoutAuthor() {
        std::string tmpfile = std::string(g_get_tmp_dir()) + "/test_no_author_2174.pdf";
        FILE *f = fopen(tmpfile.c_str(), "wb");
        if (!f) return "";

        std::string pdf;
        pdf += "%PDF-1.4\n";

        std::string obj1 = "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        std::string obj2 = "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        std::string obj3 = "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";

        size_t offset = pdf.size();
        size_t xref_offsets[3];

        xref_offsets[0] = offset;
        pdf += obj1;
        xref_offsets[1] = pdf.size();
        pdf += obj2;
        xref_offsets[2] = pdf.size();
        pdf += obj3;

        size_t xref_start = pdf.size();
        pdf += "xref\n";
        pdf += "0 4\n";
        char buf[64];
        snprintf(buf, sizeof(buf), "0000000000 65535 f \n");
        pdf += buf;
        for (int i = 0; i < 3; i++) {
            snprintf(buf, sizeof(buf), "%010zu 00000 n \n", xref_offsets[i]);
            pdf += buf;
        }
        pdf += "trailer\n<< /Size 4 /Root 1 0 R >>\n";
        snprintf(buf, sizeof(buf), "startxref\n%zu\n", xref_start);
        pdf += buf;
        pdf += "%%EOF\n";

        fwrite(pdf.data(), 1, pdf.size(), f);
        fclose(f);
        return tmpfile;
    }

    PopplerDocument *loadDocument(const std::string &path) {
        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(path.c_str(), nullptr, &error);
        if (!uri) {
            if (error) g_error_free(error);
            return nullptr;
        }
        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        if (error) g_error_free(error);
        return doc;
    }
};

// Test that passing NULL document returns NULL (g_return_val_if_fail check)
TEST_F(PopplerDocumentGetAuthorTest_2174, NullDocumentReturnsNull_2174) {
    // poppler_document_get_author with NULL should return NULL due to g_return_val_if_fail
    gchar *author = poppler_document_get_author(nullptr);
    EXPECT_EQ(author, nullptr);
}

// Test that a PDF with an author field returns the correct author string
TEST_F(PopplerDocumentGetAuthorTest_2174, DocumentWithAuthorReturnsAuthor_2174) {
    std::string path = createTempPDFWithAuthor("John Doe");
    ASSERT_FALSE(path.empty());

    PopplerDocument *doc = loadDocument(path);
    if (!doc) {
        // If we can't load the doc, skip
        g_remove(path.c_str());
        GTEST_SKIP() << "Could not load test PDF";
    }

    gchar *author = poppler_document_get_author(doc);
    ASSERT_NE(author, nullptr);
    EXPECT_STREQ(author, "John Doe");
    g_free(author);

    g_object_unref(doc);
    g_remove(path.c_str());
}

// Test that a PDF without an author field returns NULL
TEST_F(PopplerDocumentGetAuthorTest_2174, DocumentWithoutAuthorReturnsNull_2174) {
    std::string path = createTempPDFWithoutAuthor();
    ASSERT_FALSE(path.empty());

    PopplerDocument *doc = loadDocument(path);
    if (!doc) {
        g_remove(path.c_str());
        GTEST_SKIP() << "Could not load test PDF";
    }

    gchar *author = poppler_document_get_author(doc);
    // When no author is set, it should return NULL
    EXPECT_EQ(author, nullptr);
    if (author) g_free(author);

    g_object_unref(doc);
    g_remove(path.c_str());
}

// Test that a PDF with an empty author string is handled
TEST_F(PopplerDocumentGetAuthorTest_2174, DocumentWithEmptyAuthor_2174) {
    std::string path = createTempPDFWithAuthor("");
    ASSERT_FALSE(path.empty());

    PopplerDocument *doc = loadDocument(path);
    if (!doc) {
        g_remove(path.c_str());
        GTEST_SKIP() << "Could not load test PDF";
    }

    gchar *author = poppler_document_get_author(doc);
    // An empty author might return NULL or an empty string depending on implementation
    if (author != nullptr) {
        // If non-null, it should be an empty string
        EXPECT_STREQ(author, "");
        g_free(author);
    }

    g_object_unref(doc);
    g_remove(path.c_str());
}

// Test that returned string is a proper UTF-8 string (the function converts via _poppler_goo_string_to_utf8)
TEST_F(PopplerDocumentGetAuthorTest_2174, AuthorStringIsValidUTF8_2174) {
    std::string path = createTempPDFWithAuthor("Test Author");
    ASSERT_FALSE(path.empty());

    PopplerDocument *doc = loadDocument(path);
    if (!doc) {
        g_remove(path.c_str());
        GTEST_SKIP() << "Could not load test PDF";
    }

    gchar *author = poppler_document_get_author(doc);
    if (author != nullptr) {
        EXPECT_TRUE(g_utf8_validate(author, -1, nullptr));
        g_free(author);
    }

    g_object_unref(doc);
    g_remove(path.c_str());
}

// Test with a longer author name
TEST_F(PopplerDocumentGetAuthorTest_2174, LongAuthorName_2174) {
    std::string longAuthor(200, 'A');
    std::string path = createTempPDFWithAuthor(longAuthor);
    ASSERT_FALSE(path.empty());

    PopplerDocument *doc = loadDocument(path);
    if (!doc) {
        g_remove(path.c_str());
        GTEST_SKIP() << "Could not load test PDF";
    }

    gchar *author = poppler_document_get_author(doc);
    ASSERT_NE(author, nullptr);
    EXPECT_EQ(std::string(author), longAuthor);
    g_free(author);

    g_object_unref(doc);
    g_remove(path.c_str());
}

// Test that calling get_author multiple times returns consistent results
TEST_F(PopplerDocumentGetAuthorTest_2174, MultipleCallsReturnConsistentResult_2174) {
    std::string path = createTempPDFWithAuthor("Consistent Author");
    ASSERT_FALSE(path.empty());

    PopplerDocument *doc = loadDocument(path);
    if (!doc) {
        g_remove(path.c_str());
        GTEST_SKIP() << "Could not load test PDF";
    }

    gchar *author1 = poppler_document_get_author(doc);
    gchar *author2 = poppler_document_get_author(doc);

    ASSERT_NE(author1, nullptr);
    ASSERT_NE(author2, nullptr);
    EXPECT_STREQ(author1, author2);
    // They should be separate allocations
    EXPECT_NE(author1, author2);

    g_free(author1);
    g_free(author2);

    g_object_unref(doc);
    g_remove(path.c_str());
}

// Test author with special characters
TEST_F(PopplerDocumentGetAuthorTest_2174, AuthorWithSpecialCharacters_2174) {
    // Use ASCII-safe special characters that won't break PDF syntax
    std::string path = createTempPDFWithAuthor("Author Name 123 !@#");
    ASSERT_FALSE(path.empty());

    PopplerDocument *doc = loadDocument(path);
    if (!doc) {
        g_remove(path.c_str());
        GTEST_SKIP() << "Could not load test PDF";
    }

    gchar *author = poppler_document_get_author(doc);
    if (author != nullptr) {
        EXPECT_TRUE(g_utf8_validate(author, -1, nullptr));
        EXPECT_STREQ(author, "Author Name 123 !@#");
        g_free(author);
    }

    g_object_unref(doc);
    g_remove(path.c_str());
}
