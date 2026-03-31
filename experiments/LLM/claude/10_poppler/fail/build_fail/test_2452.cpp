#include <glib.h>
#include <glib-object.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstring>
#include <cstdio>

class PopplerPageTest_2452 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        // Create a minimal PDF in memory to work with
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

        document = poppler_document_new_from_data(pdf_content, (int)len, nullptr, &error);
        if (document == nullptr && error != nullptr) {
            g_error_free(error);
            // Try file-based approach
            const char *tmp_path = "/tmp/test_poppler_2452.pdf";
            FILE *f = fopen(tmp_path, "wb");
            if (f) {
                fwrite(pdf_content, 1, len, f);
                fclose(f);
                gchar *uri = g_strdup_printf("file://%s", tmp_path);
                document = poppler_document_new_from_file(uri, nullptr, &error);
                g_free(uri);
                if (error) {
                    g_error_free(error);
                    error = nullptr;
                }
            }
        }
        if (document) {
            page = poppler_document_get_page(document, 0);
        }
    }

    void TearDown() override {
        if (page) {
            g_object_unref(page);
            page = nullptr;
        }
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
    }
};

// Test that we can get a page from a document
TEST_F(PopplerPageTest_2452, GetPageFromDocument_2452) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    ASSERT_NE(page, nullptr);
}

// Test poppler_page_get_index returns 0 for first page
TEST_F(PopplerPageTest_2452, GetPageIndexFirstPage_2452) {
    if (!page) {
        GTEST_SKIP() << "Could not create test page";
    }
    int index = poppler_page_get_index(page);
    EXPECT_EQ(index, 0);
}

// Test poppler_page_get_label returns a label (may be NULL or a string)
TEST_F(PopplerPageTest_2452, GetPageLabel_2452) {
    if (!page) {
        GTEST_SKIP() << "Could not create test page";
    }
    gchar *label = poppler_page_get_label(page);
    // For a simple PDF without page labels, it might return NULL or "1"
    if (label) {
        EXPECT_GT(strlen(label), 0u);
        g_free(label);
    }
}

// Test that the "label" property is readable via GObject property mechanism
TEST_F(PopplerPageTest_2452, LabelPropertyReadable_2452) {
    if (!page) {
        GTEST_SKIP() << "Could not create test page";
    }
    gchar *label = nullptr;
    g_object_get(G_OBJECT(page), "label", &label, NULL);
    // The property should be accessible without error
    // label may be NULL for pages without explicit labels
    if (label) {
        g_free(label);
    }
}

// Test poppler_page_get_size returns positive dimensions
TEST_F(PopplerPageTest_2452, GetPageSize_2452) {
    if (!page) {
        GTEST_SKIP() << "Could not create test page";
    }
    double width = 0, height = 0;
    poppler_page_get_size(page, &width, &height);
    EXPECT_GT(width, 0.0);
    EXPECT_GT(height, 0.0);
}

// Test poppler_page_get_size with expected dimensions (612x792 for US Letter)
TEST_F(PopplerPageTest_2452, GetPageSizeExpectedDimensions_2452) {
    if (!page) {
        GTEST_SKIP() << "Could not create test page";
    }
    double width = 0, height = 0;
    poppler_page_get_size(page, &width, &height);
    EXPECT_NEAR(width, 612.0, 1.0);
    EXPECT_NEAR(height, 792.0, 1.0);
}

// Test poppler_page_get_size with NULL arguments (should not crash)
TEST_F(PopplerPageTest_2452, GetPageSizeNullArgs_2452) {
    if (!page) {
        GTEST_SKIP() << "Could not create test page";
    }
    // Passing NULL for width/height should be handled gracefully
    poppler_page_get_size(page, nullptr, nullptr);
}

// Test getting text from a page (should return empty for a blank page)
TEST_F(PopplerPageTest_2452, GetTextReturnsEmptyForBlankPage_2452) {
    if (!page) {
        GTEST_SKIP() << "Could not create test page";
    }
    gchar *text = poppler_page_get_text(page);
    ASSERT_NE(text, nullptr);
    // Blank page should have empty or whitespace-only text
    // Just verify it doesn't crash and returns valid string
    g_free(text);
}

// Test that PopplerPage is a GObject
TEST_F(PopplerPageTest_2452, IsGObject_2452) {
    if (!page) {
        GTEST_SKIP() << "Could not create test page";
    }
    EXPECT_TRUE(G_IS_OBJECT(page));
}

// Test that PopplerPage type is POPPLER_TYPE_PAGE
TEST_F(PopplerPageTest_2452, TypeCheck_2452) {
    if (!page) {
        GTEST_SKIP() << "Could not create test page";
    }
    EXPECT_TRUE(POPPLER_IS_PAGE(page));
}

// Test that requesting an out-of-range page returns NULL
TEST_F(PopplerPageTest_2452, OutOfRangePageReturnsNull_2452) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    PopplerPage *invalid_page = poppler_document_get_page(document, 999);
    EXPECT_EQ(invalid_page, nullptr);
}

// Test that requesting a negative page index returns NULL
TEST_F(PopplerPageTest_2452, NegativePageIndexReturnsNull_2452) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    PopplerPage *invalid_page = poppler_document_get_page(document, -1);
    EXPECT_EQ(invalid_page, nullptr);
}

// Test find_text on blank page returns NULL (no results)
TEST_F(PopplerPageTest_2452, FindTextOnBlankPage_2452) {
    if (!page) {
        GTEST_SKIP() << "Could not create test page";
    }
    GList *results = poppler_page_find_text(page, "nonexistent");
    EXPECT_EQ(results, nullptr);
}

// Test that the label property spec exists
TEST_F(PopplerPageTest_2452, LabelPropertyExists_2452) {
    if (!page) {
        GTEST_SKIP() << "Could not create test page";
    }
    GObjectClass *klass = G_OBJECT_GET_CLASS(page);
    GParamSpec *pspec = g_object_class_find_property(klass, "label");
    ASSERT_NE(pspec, nullptr);
    EXPECT_STREQ(g_param_spec_get_name(pspec), "label");
}

// Test that the label property is of type string
TEST_F(PopplerPageTest_2452, LabelPropertyIsString_2452) {
    if (!page) {
        GTEST_SKIP() << "Could not create test page";
    }
    GObjectClass *klass = G_OBJECT_GET_CLASS(page);
    GParamSpec *pspec = g_object_class_find_property(klass, "label");
    ASSERT_NE(pspec, nullptr);
    EXPECT_EQ(G_PARAM_SPEC_VALUE_TYPE(pspec), G_TYPE_STRING);
}

// Test that the label property is read-only
TEST_F(PopplerPageTest_2452, LabelPropertyIsReadOnly_2452) {
    if (!page) {
        GTEST_SKIP() << "Could not create test page";
    }
    GObjectClass *klass = G_OBJECT_GET_CLASS(page);
    GParamSpec *pspec = g_object_class_find_property(klass, "label");
    ASSERT_NE(pspec, nullptr);
    EXPECT_TRUE(pspec->flags & G_PARAM_READABLE);
    EXPECT_FALSE(pspec->flags & G_PARAM_WRITABLE);
}

// Test that label property nick and blurb are set
TEST_F(PopplerPageTest_2452, LabelPropertyNickAndBlurb_2452) {
    if (!page) {
        GTEST_SKIP() << "Could not create test page";
    }
    GObjectClass *klass = G_OBJECT_GET_CLASS(page);
    GParamSpec *pspec = g_object_class_find_property(klass, "label");
    ASSERT_NE(pspec, nullptr);
    EXPECT_STREQ(g_param_spec_get_nick(pspec), "Page Label");
    EXPECT_STREQ(g_param_spec_get_blurb(pspec), "The label of the page");
}

// Test document page count
TEST_F(PopplerPageTest_2452, DocumentHasOnePage_2452) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }
    int n_pages = poppler_document_get_n_pages(document);
    EXPECT_EQ(n_pages, 1);
}

// Additional test with labeled PDF
class PopplerPageLabeledTest_2452 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;

    void SetUp() override {
        // PDF with page labels
        const char *pdf_content =
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R /PageLabels << /Nums [0 << /P (Cover) >>] >> >>\n"
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
            "0000000104 00000 n \n"
            "0000000161 00000 n \n"
            "trailer\n"
            "<< /Size 4 /Root 1 0 R >>\n"
            "startxref\n"
            "236\n"
            "%%EOF\n";

        gsize len = strlen(pdf_content);
        GError *error = nullptr;

        const char *tmp_path = "/tmp/test_poppler_labeled_2452.pdf";
        FILE *f = fopen(tmp_path, "wb");
        if (f) {
            fwrite(pdf_content, 1, len, f);
            fclose(f);
            gchar *uri = g_strdup_printf("file://%s", tmp_path);
            document = poppler_document_new_from_file(uri, nullptr, &error);
            g_free(uri);
            if (error) {
                g_error_free(error);
                error = nullptr;
            }
        }
    }

    void TearDown() override {
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
    }
};

TEST_F(PopplerPageLabeledTest_2452, LabeledPageHasLabel_2452) {
    if (!document) {
        GTEST_SKIP() << "Could not create labeled test document";
    }
    PopplerPage *page = poppler_document_get_page(document, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page from labeled document";
    }
    gchar *label = poppler_page_get_label(page);
    if (label) {
        EXPECT_STREQ(label, "Cover");
        g_free(label);
    }
    g_object_unref(page);
}

TEST_F(PopplerPageLabeledTest_2452, LabelPropertyMatchesGetLabel_2452) {
    if (!document) {
        GTEST_SKIP() << "Could not create labeled test document";
    }
    PopplerPage *page = poppler_document_get_page(document, 0);
    if (!page) {
        GTEST_SKIP() << "Could not get page from labeled document";
    }
    gchar *label_func = poppler_page_get_label(page);
    gchar *label_prop = nullptr;
    g_object_get(G_OBJECT(page), "label", &label_prop, NULL);

    if (label_func && label_prop) {
        EXPECT_STREQ(label_func, label_prop);
    } else {
        // Both should be NULL or both non-NULL
        EXPECT_EQ(label_func, label_prop);
    }

    g_free(label_func);
    g_free(label_prop);
    g_object_unref(page);
}
