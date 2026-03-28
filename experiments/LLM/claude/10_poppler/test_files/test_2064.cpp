#include <glib.h>
#include <poppler.h>
#include <poppler-document.h>
#include <poppler-page.h>
#include <cstring>
#include <cstdio>
#include <gtest/gtest.h>

class PopplerAnnotSetContentsTest_2064 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;
    GList *annots = nullptr;

    void SetUp() override {
        // Create a minimal PDF in memory with an annotation
        // We'll use a simple PDF with a text annotation
        const char *pdf_content =
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/Annots[4 0 R]>>endobj\n"
            "4 0 obj<</Type/Annot/Subtype/Text/Rect[100 100 200 200]/Contents(Initial)>>endobj\n"
            "xref\n"
            "0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000206 00000 n \n"
            "trailer<</Size 5/Root 1 0 R>>\n"
            "startxref\n"
            "302\n"
            "%%EOF\n";

        gsize len = strlen(pdf_content);

        GError *error = nullptr;
        GBytes *bytes = g_bytes_new(pdf_content, len);
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);
        g_object_unref(stream);
        g_bytes_unref(bytes);

        if (!doc) {
            // Try alternative: write to temp file
            if (error) {
                g_error_free(error);
                error = nullptr;
            }
            char tmpname[] = "/tmp/poppler_test_XXXXXX.pdf";
            int fd = mkstemps(tmpname, 4);
            if (fd >= 0) {
                write(fd, pdf_content, len);
                close(fd);
                doc = poppler_document_new_from_file(
                    g_strdup_printf("file://%s", tmpname), nullptr, &error);
                unlink(tmpname);
            }
        }

        if (doc) {
            page = poppler_document_get_page(doc, 0);
            if (page) {
                annots = poppler_page_get_annot_mapping(page);
            }
        }
    }

    void TearDown() override {
        if (annots) {
            poppler_page_free_annot_mapping(annots);
        }
        if (page) {
            g_object_unref(page);
        }
        if (doc) {
            g_object_unref(doc);
        }
    }

    PopplerAnnot *getFirstAnnot() {
        if (annots && annots->data) {
            PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)annots->data;
            return mapping->annot;
        }
        return nullptr;
    }
};

TEST_F(PopplerAnnotSetContentsTest_2064, SetSimpleASCIIContents_2064) {
    PopplerAnnot *annot = getFirstAnnot();
    if (!annot) {
        GTEST_SKIP() << "Could not create test annotation";
    }

    poppler_annot_set_contents(annot, "Hello World");
    gchar *result = poppler_annot_get_contents(annot);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Hello World");
    g_free(result);
}

TEST_F(PopplerAnnotSetContentsTest_2064, SetEmptyStringContents_2064) {
    PopplerAnnot *annot = getFirstAnnot();
    if (!annot) {
        GTEST_SKIP() << "Could not create test annotation";
    }

    poppler_annot_set_contents(annot, "");
    gchar *result = poppler_annot_get_contents(annot);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
    g_free(result);
}

TEST_F(PopplerAnnotSetContentsTest_2064, SetNullContents_2064) {
    PopplerAnnot *annot = getFirstAnnot();
    if (!annot) {
        GTEST_SKIP() << "Could not create test annotation";
    }

    // First set something non-null
    poppler_annot_set_contents(annot, "Something");
    // Then set null
    poppler_annot_set_contents(annot, nullptr);
    gchar *result = poppler_annot_get_contents(annot);
    // After setting null, contents should be empty or null
    if (result) {
        EXPECT_STREQ(result, "");
        g_free(result);
    }
}

TEST_F(PopplerAnnotSetContentsTest_2064, SetUTF8Contents_2064) {
    PopplerAnnot *annot = getFirstAnnot();
    if (!annot) {
        GTEST_SKIP() << "Could not create test annotation";
    }

    // Set UTF-8 content with non-ASCII characters
    const gchar *utf8_str = "Héllo Wörld";
    poppler_annot_set_contents(annot, utf8_str);
    gchar *result = poppler_annot_get_contents(annot);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, utf8_str);
    g_free(result);
}

TEST_F(PopplerAnnotSetContentsTest_2064, SetContentsMultipleTimes_2064) {
    PopplerAnnot *annot = getFirstAnnot();
    if (!annot) {
        GTEST_SKIP() << "Could not create test annotation";
    }

    poppler_annot_set_contents(annot, "First");
    gchar *result1 = poppler_annot_get_contents(annot);
    ASSERT_NE(result1, nullptr);
    EXPECT_STREQ(result1, "First");
    g_free(result1);

    poppler_annot_set_contents(annot, "Second");
    gchar *result2 = poppler_annot_get_contents(annot);
    ASSERT_NE(result2, nullptr);
    EXPECT_STREQ(result2, "Second");
    g_free(result2);
}

TEST_F(PopplerAnnotSetContentsTest_2064, SetContentsWithUnicodeSymbols_2064) {
    PopplerAnnot *annot = getFirstAnnot();
    if (!annot) {
        GTEST_SKIP() << "Could not create test annotation";
    }

    // CJK characters and emoji
    const gchar *unicode_str = "日本語テスト";
    poppler_annot_set_contents(annot, unicode_str);
    gchar *result = poppler_annot_get_contents(annot);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, unicode_str);
    g_free(result);
}

TEST_F(PopplerAnnotSetContentsTest_2064, SetContentsLongString_2064) {
    PopplerAnnot *annot = getFirstAnnot();
    if (!annot) {
        GTEST_SKIP() << "Could not create test annotation";
    }

    // Create a long string
    std::string long_str(10000, 'A');
    poppler_annot_set_contents(annot, long_str.c_str());
    gchar *result = poppler_annot_get_contents(annot);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(std::string(result), long_str);
    g_free(result);
}

TEST_F(PopplerAnnotSetContentsTest_2064, SetContentsWithNewlines_2064) {
    PopplerAnnot *annot = getFirstAnnot();
    if (!annot) {
        GTEST_SKIP() << "Could not create test annotation";
    }

    const gchar *newline_str = "Line1\nLine2\nLine3";
    poppler_annot_set_contents(annot, newline_str);
    gchar *result = poppler_annot_get_contents(annot);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, newline_str);
    g_free(result);
}

TEST_F(PopplerAnnotSetContentsTest_2064, NullAnnotDoesNotCrash_2064) {
    // g_return_if_fail should handle null gracefully (just returns)
    // This should not crash
    poppler_annot_set_contents(nullptr, "test");
}

TEST_F(PopplerAnnotSetContentsTest_2064, SetContentsSingleChar_2064) {
    PopplerAnnot *annot = getFirstAnnot();
    if (!annot) {
        GTEST_SKIP() << "Could not create test annotation";
    }

    poppler_annot_set_contents(annot, "X");
    gchar *result = poppler_annot_get_contents(annot);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "X");
    g_free(result);
}
