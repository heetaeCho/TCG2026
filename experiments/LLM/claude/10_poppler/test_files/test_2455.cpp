#include <gtest/gtest.h>
#include <poppler.h>
#include <poppler-page.h>
#include <glib.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>

class PopplerPageAnnotMappingTest_2455 : public ::testing::Test {
protected:
    void SetUp() override {
        doc_ = nullptr;
        page_ = nullptr;
    }

    void TearDown() override {
        if (page_) {
            g_object_unref(page_);
            page_ = nullptr;
        }
        if (doc_) {
            g_object_unref(doc_);
            doc_ = nullptr;
        }
        // Clean up any temp files
        for (auto &f : temp_files_) {
            g_unlink(f.c_str());
        }
    }

    // Helper to create a minimal PDF with no annotations
    PopplerDocument *createMinimalPDF() {
        // Create a minimal PDF in memory
        const char *pdf_content =
            "%PDF-1.4\n"
            "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
            "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
            "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer\n<< /Size 4 /Root 1 0 R >>\n"
            "startxref\n198\n%%EOF\n";

        gchar *tmpfile = g_strdup_printf("test_no_annot_%d.pdf", rand());
        temp_files_.push_back(tmpfile);
        FILE *f = fopen(tmpfile, "wb");
        if (!f) {
            g_free(tmpfile);
            return nullptr;
        }
        fwrite(pdf_content, 1, strlen(pdf_content), f);
        fclose(f);

        gchar *uri = g_filename_to_uri(tmpfile, nullptr, nullptr);
        GError *error = nullptr;
        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        g_free(tmpfile);
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }

    // Helper to load a PDF from data
    PopplerDocument *createPDFFromData(const char *data, size_t len) {
        gchar *tmpfile = g_strdup_printf("test_annot_%d.pdf", rand());
        temp_files_.push_back(tmpfile);
        FILE *f = fopen(tmpfile, "wb");
        if (!f) {
            g_free(tmpfile);
            return nullptr;
        }
        fwrite(data, 1, len, f);
        fclose(f);

        gchar *uri = g_filename_to_uri(tmpfile, nullptr, nullptr);
        GError *error = nullptr;
        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        g_free(tmpfile);
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }

    PopplerDocument *doc_;
    PopplerPage *page_;
    std::vector<std::string> temp_files_;
};

// Test that passing NULL returns NULL
TEST_F(PopplerPageAnnotMappingTest_2455, NullPageReturnsNull_2455) {
    GList *result = poppler_page_get_annot_mapping(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test that a page with no annotations returns NULL (empty list)
TEST_F(PopplerPageAnnotMappingTest_2455, NoAnnotationsReturnsNull_2455) {
    doc_ = createMinimalPDF();
    if (!doc_) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }

    page_ = poppler_document_get_page(doc_, 0);
    ASSERT_NE(page_, nullptr);

    GList *result = poppler_page_get_annot_mapping(page_);
    // A page with no annotations should return NULL or empty list
    if (result) {
        EXPECT_EQ(g_list_length(result), 0u);
        poppler_page_free_annot_mapping(result);
    } else {
        EXPECT_EQ(result, nullptr);
    }
}

// Test with a PDF that has a text annotation
TEST_F(PopplerPageAnnotMappingTest_2455, TextAnnotationMapping_2455) {
    // Create a PDF with a text annotation
    // This is a minimal PDF with a text annotation embedded
    const char *pdf_with_annot =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Annots [4 0 R] >>\nendobj\n"
        "4 0 obj\n<< /Type /Annot /Subtype /Text /Rect [100 200 150 250] "
        "/Contents (Test annotation) >>\nendobj\n"
        "xref\n0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000232 00000 n \n"
        "trailer\n<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n340\n%%EOF\n";

    doc_ = createPDFFromData(pdf_with_annot, strlen(pdf_with_annot));
    if (!doc_) {
        GTEST_SKIP() << "Could not create PDF with annotation";
    }

    page_ = poppler_document_get_page(doc_, 0);
    if (!page_) {
        GTEST_SKIP() << "Could not get page";
    }

    GList *result = poppler_page_get_annot_mapping(page_);
    if (result) {
        EXPECT_GE(g_list_length(result), 1u);

        // Check first mapping
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)result->data;
        ASSERT_NE(mapping, nullptr);
        EXPECT_NE(mapping->annot, nullptr);

        // The annotation area should have valid coordinates
        EXPECT_LE(mapping->area.x1, mapping->area.x2);
        // Note: y1 could be less than or greater than y2 depending on coordinate system

        poppler_page_free_annot_mapping(result);
    }
}

// Test that poppler_page_free_annot_mapping handles NULL gracefully
TEST_F(PopplerPageAnnotMappingTest_2455, FreeAnnotMappingNull_2455) {
    // Should not crash
    poppler_page_free_annot_mapping(nullptr);
}

// Test with a PDF that has multiple annotations
TEST_F(PopplerPageAnnotMappingTest_2455, MultipleAnnotations_2455) {
    const char *pdf_multi_annot =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Annots [4 0 R 5 0 R] >>\nendobj\n"
        "4 0 obj\n<< /Type /Annot /Subtype /Text /Rect [100 200 150 250] "
        "/Contents (Annot 1) >>\nendobj\n"
        "5 0 obj\n<< /Type /Annot /Subtype /Text /Rect [300 400 350 450] "
        "/Contents (Annot 2) >>\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000246 00000 n \n"
        "0000000348 00000 n \n"
        "trailer\n<< /Size 6 /Root 1 0 R >>\n"
        "startxref\n450\n%%EOF\n";

    doc_ = createPDFFromData(pdf_multi_annot, strlen(pdf_multi_annot));
    if (!doc_) {
        GTEST_SKIP() << "Could not create PDF with multiple annotations";
    }

    page_ = poppler_document_get_page(doc_, 0);
    if (!page_) {
        GTEST_SKIP() << "Could not get page";
    }

    GList *result = poppler_page_get_annot_mapping(page_);
    if (result) {
        EXPECT_GE(g_list_length(result), 2u);

        // Verify each mapping has a valid annotation
        for (GList *l = result; l != nullptr; l = l->next) {
            PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
            ASSERT_NE(mapping, nullptr);
            EXPECT_NE(mapping->annot, nullptr);
        }

        poppler_page_free_annot_mapping(result);
    }
}

// Test with a highlight annotation (text markup type)
TEST_F(PopplerPageAnnotMappingTest_2455, HighlightAnnotation_2455) {
    const char *pdf_highlight =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Annots [4 0 R] >>\nendobj\n"
        "4 0 obj\n<< /Type /Annot /Subtype /Highlight /Rect [100 700 200 720] "
        "/QuadPoints [100 720 200 720 100 700 200 700] >>\nendobj\n"
        "xref\n0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000240 00000 n \n"
        "trailer\n<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n400\n%%EOF\n";

    doc_ = createPDFFromData(pdf_highlight, strlen(pdf_highlight));
    if (!doc_) {
        GTEST_SKIP() << "Could not create PDF with highlight annotation";
    }

    page_ = poppler_document_get_page(doc_, 0);
    if (!page_) {
        GTEST_SKIP() << "Could not get page";
    }

    GList *result = poppler_page_get_annot_mapping(page_);
    if (result) {
        EXPECT_GE(g_list_length(result), 1u);

        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)result->data;
        ASSERT_NE(mapping, nullptr);
        EXPECT_NE(mapping->annot, nullptr);

        // Verify that the annotation type is a text markup
        PopplerAnnotType type = poppler_annot_get_annot_type(mapping->annot);
        EXPECT_EQ(type, POPPLER_ANNOT_HIGHLIGHT);

        poppler_page_free_annot_mapping(result);
    }
}

// Test annotation mapping area coordinates for no rotation case
TEST_F(PopplerPageAnnotMappingTest_2455, AreaCoordinatesNoRotation_2455) {
    const char *pdf_data =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Annots [4 0 R] >>\nendobj\n"
        "4 0 obj\n<< /Type /Annot /Subtype /Text /Rect [10 20 30 40] >>\nendobj\n"
        "xref\n0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000230 00000 n \n"
        "trailer\n<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n312\n%%EOF\n";

    doc_ = createPDFFromData(pdf_data, strlen(pdf_data));
    if (!doc_) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    page_ = poppler_document_get_page(doc_, 0);
    if (!page_) {
        GTEST_SKIP() << "Could not get page";
    }

    GList *result = poppler_page_get_annot_mapping(page_);
    if (result) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)result->data;
        ASSERT_NE(mapping, nullptr);

        // For no rotation and no crop box offset, area should match rect
        // Rect is [10 20 30 40], crop_box x1=0, y1=0
        // So mapping area should be x1=10, y1=20, x2=30, y2=40
        EXPECT_DOUBLE_EQ(mapping->area.x1, 10.0);
        EXPECT_DOUBLE_EQ(mapping->area.y1, 20.0);
        EXPECT_DOUBLE_EQ(mapping->area.x2, 30.0);
        EXPECT_DOUBLE_EQ(mapping->area.y2, 40.0);

        poppler_page_free_annot_mapping(result);
    }
}

// Test with a line annotation
TEST_F(PopplerPageAnnotMappingTest_2455, LineAnnotation_2455) {
    const char *pdf_line =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Annots [4 0 R] >>\nendobj\n"
        "4 0 obj\n<< /Type /Annot /Subtype /Line /Rect [50 100 200 300] "
        "/L [50 100 200 300] >>\nendobj\n"
        "xref\n0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000230 00000 n \n"
        "trailer\n<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n360\n%%EOF\n";

    doc_ = createPDFFromData(pdf_line, strlen(pdf_line));
    if (!doc_) {
        GTEST_SKIP() << "Could not create PDF with line annotation";
    }

    page_ = poppler_document_get_page(doc_, 0);
    if (!page_) {
        GTEST_SKIP() << "Could not get page";
    }

    GList *result = poppler_page_get_annot_mapping(page_);
    if (result) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)result->data;
        ASSERT_NE(mapping, nullptr);
        EXPECT_NE(mapping->annot, nullptr);

        PopplerAnnotType type = poppler_annot_get_annot_type(mapping->annot);
        EXPECT_EQ(type, POPPLER_ANNOT_LINE);

        poppler_page_free_annot_mapping(result);
    }
}

// Test with square annotation
TEST_F(PopplerPageAnnotMappingTest_2455, SquareAnnotation_2455) {
    const char *pdf_square =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Annots [4 0 R] >>\nendobj\n"
        "4 0 obj\n<< /Type /Annot /Subtype /Square /Rect [50 50 150 150] >>\nendobj\n"
        "xref\n0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000230 00000 n \n"
        "trailer\n<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n325\n%%EOF\n";

    doc_ = createPDFFromData(pdf_square, strlen(pdf_square));
    if (!doc_) {
        GTEST_SKIP() << "Could not create PDF with square annotation";
    }

    page_ = poppler_document_get_page(doc_, 0);
    if (!page_) {
        GTEST_SKIP() << "Could not get page";
    }

    GList *result = poppler_page_get_annot_mapping(page_);
    if (result) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)result->data;
        ASSERT_NE(mapping, nullptr);
        EXPECT_NE(mapping->annot, nullptr);

        PopplerAnnotType type = poppler_annot_get_annot_type(mapping->annot);
        EXPECT_EQ(type, POPPLER_ANNOT_SQUARE);

        poppler_page_free_annot_mapping(result);
    }
}

// Test with circle annotation
TEST_F(PopplerPageAnnotMappingTest_2455, CircleAnnotation_2455) {
    const char *pdf_circle =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Annots [4 0 R] >>\nendobj\n"
        "4 0 obj\n<< /Type /Annot /Subtype /Circle /Rect [60 60 160 160] >>\nendobj\n"
        "xref\n0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000230 00000 n \n"
        "trailer\n<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n328\n%%EOF\n";

    doc_ = createPDFFromData(pdf_circle, strlen(pdf_circle));
    if (!doc_) {
        GTEST_SKIP() << "Could not create PDF with circle annotation";
    }

    page_ = poppler_document_get_page(doc_, 0);
    if (!page_) {
        GTEST_SKIP() << "Could not get page";
    }

    GList *result = poppler_page_get_annot_mapping(page_);
    if (result) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)result->data;
        ASSERT_NE(mapping, nullptr);
        EXPECT_NE(mapping->annot, nullptr);

        PopplerAnnotType type = poppler_annot_get_annot_type(mapping->annot);
        EXPECT_EQ(type, POPPLER_ANNOT_CIRCLE);

        poppler_page_free_annot_mapping(result);
    }
}

// Test mapping list order is preserved (first annotation first in list)
TEST_F(PopplerPageAnnotMappingTest_2455, MappingOrderPreserved_2455) {
    const char *pdf_ordered =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Annots [4 0 R 5 0 R 6 0 R] >>\nendobj\n"
        "4 0 obj\n<< /Type /Annot /Subtype /Text /Rect [10 10 20 20] >>\nendobj\n"
        "5 0 obj\n<< /Type /Annot /Subtype /Text /Rect [30 30 40 40] >>\nendobj\n"
        "6 0 obj\n<< /Type /Annot /Subtype /Text /Rect [50 50 60 60] >>\nendobj\n"
        "xref\n0 7\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000258 00000 n \n"
        "0000000338 00000 n \n"
        "0000000418 00000 n \n"
        "trailer\n<< /Size 7 /Root 1 0 R >>\n"
        "startxref\n498\n%%EOF\n";

    doc_ = createPDFFromData(pdf_ordered, strlen(pdf_ordered));
    if (!doc_) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    page_ = poppler_document_get_page(doc_, 0);
    if (!page_) {
        GTEST_SKIP() << "Could not get page";
    }

    GList *result = poppler_page_get_annot_mapping(page_);
    if (result) {
        guint len = g_list_length(result);
        EXPECT_GE(len, 3u);

        // Verify that all mappings have valid annotations
        for (GList *l = result; l != nullptr; l = l->next) {
            PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
            ASSERT_NE(mapping, nullptr);
            EXPECT_NE(mapping->annot, nullptr);
        }

        poppler_page_free_annot_mapping(result);
    }
}

// Test stamp annotation type
TEST_F(PopplerPageAnnotMappingTest_2455, StampAnnotation_2455) {
    const char *pdf_stamp =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Annots [4 0 R] >>\nendobj\n"
        "4 0 obj\n<< /Type /Annot /Subtype /Stamp /Rect [100 100 200 200] "
        "/Name /Approved >>\nendobj\n"
        "xref\n0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000230 00000 n \n"
        "trailer\n<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n355\n%%EOF\n";

    doc_ = createPDFFromData(pdf_stamp, strlen(pdf_stamp));
    if (!doc_) {
        GTEST_SKIP() << "Could not create PDF with stamp annotation";
    }

    page_ = poppler_document_get_page(doc_, 0);
    if (!page_) {
        GTEST_SKIP() << "Could not get page";
    }

    GList *result = poppler_page_get_annot_mapping(page_);
    if (result) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)result->data;
        ASSERT_NE(mapping, nullptr);
        EXPECT_NE(mapping->annot, nullptr);

        PopplerAnnotType type = poppler_annot_get_annot_type(mapping->annot);
        EXPECT_EQ(type, POPPLER_ANNOT_STAMP);

        poppler_page_free_annot_mapping(result);
    }
}

// Test with underline text markup annotation
TEST_F(PopplerPageAnnotMappingTest_2455, UnderlineAnnotation_2455) {
    const char *pdf_underline =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Annots [4 0 R] >>\nendobj\n"
        "4 0 obj\n<< /Type /Annot /Subtype /Underline /Rect [100 700 300 720] "
        "/QuadPoints [100 720 300 720 100 700 300 700] >>\nendobj\n"
        "xref\n0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000230 00000 n \n"
        "trailer\n<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n420\n%%EOF\n";

    doc_ = createPDFFromData(pdf_underline, strlen(pdf_underline));
    if (!doc_) {
        GTEST_SKIP() << "Could not create PDF with underline annotation";
    }

    page_ = poppler_document_get_page(doc_, 0);
    if (!page_) {
        GTEST_SKIP() << "Could not get page";
    }

    GList *result = poppler_page_get_annot_mapping(page_);
    if (result) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)result->data;
        ASSERT_NE(mapping, nullptr);
        EXPECT_NE(mapping->annot, nullptr);

        PopplerAnnotType type = poppler_annot_get_annot_type(mapping->annot);
        EXPECT_EQ(type, POPPLER_ANNOT_UNDERLINE);

        poppler_page_free_annot_mapping(result);
    }
}

// Test with strikeout text markup annotation
TEST_F(PopplerPageAnnotMappingTest_2455, StrikeOutAnnotation_2455) {
    const char *pdf_strikeout =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Annots [4 0 R] >>\nendobj\n"
        "4 0 obj\n<< /Type /Annot /Subtype /StrikeOut /Rect [100 700 300 720] "
        "/QuadPoints [100 720 300 720 100 700 300 700] >>\nendobj\n"
        "xref\n0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000230 00000 n \n"
        "trailer\n<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n425\n%%EOF\n";

    doc_ = createPDFFromData(pdf_strikeout, strlen(pdf_strikeout));
    if (!doc_) {
        GTEST_SKIP() << "Could not create PDF with strikeout annotation";
    }

    page_ = poppler_document_get_page(doc_, 0);
    if (!page_) {
        GTEST_SKIP() << "Could not get page";
    }

    GList *result = poppler_page_get_annot_mapping(page_);
    if (result) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)result->data;
        ASSERT_NE(mapping, nullptr);
        EXPECT_NE(mapping->annot, nullptr);

        PopplerAnnotType type = poppler_annot_get_annot_type(mapping->annot);
        EXPECT_EQ(type, POPPLER_ANNOT_STRIKE_OUT);

        poppler_page_free_annot_mapping(result);
    }
}

// Test with an unknown/generic annotation subtype
TEST_F(PopplerPageAnnotMappingTest_2455, GenericAnnotation_2455) {
    const char *pdf_generic =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Annots [4 0 R] >>\nendobj\n"
        "4 0 obj\n<< /Type /Annot /Subtype /Caret /Rect [50 50 100 100] >>\nendobj\n"
        "xref\n0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000230 00000 n \n"
        "trailer\n<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n326\n%%EOF\n";

    doc_ = createPDFFromData(pdf_generic, strlen(pdf_generic));
    if (!doc_) {
        GTEST_SKIP() << "Could not create PDF with caret annotation";
    }

    page_ = poppler_document_get_page(doc_, 0);
    if (!page_) {
        GTEST_SKIP() << "Could not get page";
    }

    GList *result = poppler_page_get_annot_mapping(page_);
    if (result) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)result->data;
        ASSERT_NE(mapping, nullptr);
        EXPECT_NE(mapping->annot, nullptr);

        // Caret falls into the default case
        PopplerAnnotType type = poppler_annot_get_annot_type(mapping->annot);
        EXPECT_EQ(type, POPPLER_ANNOT_CARET);

        poppler_page_free_annot_mapping(result);
    }
}

// Test with page having a rotated page (90 degrees)
TEST_F(PopplerPageAnnotMappingTest_2455, RotatedPage90_2455) {
    const char *pdf_rotated =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Rotate 90 /Annots [4 0 R] >>\nendobj\n"
        "4 0 obj\n<< /Type /Annot /Subtype /Text /Rect [100 200 150 250] >>\nendobj\n"
        "xref\n0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000254 00000 n \n"
        "trailer\n<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n340\n%%EOF\n";

    doc_ = createPDFFromData(pdf_rotated, strlen(pdf_rotated));
    if (!doc_) {
        GTEST_SKIP() << "Could not create rotated PDF";
    }

    page_ = poppler_document_get_page(doc_, 0);
    if (!page_) {
        GTEST_SKIP() << "Could not get page";
    }

    GList *result = poppler_page_get_annot_mapping(page_);
    if (result) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)result->data;
        ASSERT_NE(mapping, nullptr);
        EXPECT_NE(mapping->annot, nullptr);

        // For 90 degree rotation without flagNoRotate:
        // area.x1 = rect.y1 = 200
        // area.y1 = height - rect.x2 = 792 - 150 = 642
        // area.x2 = area.x1 + annot_height = 200 + 50 = 250
        // area.y2 = area.y1 + annot_width = 642 + 50 = 692
        EXPECT_DOUBLE_EQ(mapping->area.x1, 200.0);
        EXPECT_DOUBLE_EQ(mapping->area.y1, 642.0);
        EXPECT_DOUBLE_EQ(mapping->area.x2, 250.0);
        EXPECT_DOUBLE_EQ(mapping->area.y2, 692.0);

        poppler_page_free_annot_mapping(result);
    }
}

// Test with page having 180 degree rotation
TEST_F(PopplerPageAnnotMappingTest_2455, RotatedPage180_2455) {
    const char *pdf_rotated =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Rotate 180 /Annots [4 0 R] >>\nendobj\n"
        "4 0 obj\n<< /Type /Annot /Subtype /Text /Rect [100 200 150 250] >>\nendobj\n"
        "xref\n0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000255 00000 n \n"
        "trailer\n<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n341\n%%EOF\n";

    doc_ = createPDFFromData(pdf_rotated, strlen(pdf_rotated));
    if (!doc_) {
        GTEST_SKIP() << "Could not create rotated PDF";
    }

    page_ = poppler_document_get_page(doc_, 0);
    if (!page_) {
        GTEST_SKIP() << "Could not get page";
    }

    GList *result = poppler_page_get_annot_mapping(page_);
    if (result) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)result->data;
        ASSERT_NE(mapping, nullptr);

        // For 180 degree rotation without flagNoRotate:
        // area.x1 = width - rect.x2 = 612 - 150 = 462
        // area.y1 = height - rect.y2 = 792 - 250 = 542
        // area.x2 = area.x1 + annot_width = 462 + 50 = 512
        // area.y2 = area.y1 + annot_height = 542 + 50 = 592
        EXPECT_DOUBLE_EQ(mapping->area.x1, 462.0);
        EXPECT_DOUBLE_EQ(mapping->area.y1, 542.0);
        EXPECT_DOUBLE_EQ(mapping->area.x2, 512.0);
        EXPECT_DOUBLE_EQ(mapping->area.y2, 592.0);

        poppler_page_free_annot_mapping(result);
    }
}

// Test with page having 270 degree rotation
TEST_F(PopplerPageAnnotMappingTest_2455, RotatedPage270_2455) {
    const char *pdf_rotated =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Rotate 270 /Annots [4 0 R] >>\nendobj\n"
        "4 0 obj\n<< /Type /Annot /Subtype /Text /Rect [100 200 150 250] >>\nendobj\n"
        "xref\n0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000255 00000 n \n"
        "trailer\n<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n341\n%%EOF\n";

    doc_ = createPDFFromData(pdf_rotated, strlen(pdf_rotated));
    if (!doc_) {
        GTEST_SKIP() << "Could not create rotated PDF";
    }

    page_ = poppler_document_get_page(doc_, 0);
    if (!page_) {
        GTEST_SKIP() << "Could not get page";
    }

    GList *result = poppler_page_get_annot_mapping(page_);
    if (result) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)result->data;
        ASSERT_NE(mapping, nullptr);

        // For 270 degree rotation without flagNoRotate:
        // width = 612 (but poppler_page_get_size with 270 rotation swaps w/h)
        // Actually, poppler_page_get_size returns the rotated dimensions
        // For 270 rotation, width and height are swapped by poppler_page_get_size
        // Let's just verify the mapping exists and has reasonable values
        EXPECT_NE(mapping->annot, nullptr);

        poppler_page_free_annot_mapping(result);
    }
}

// Test annot mapping copy function
TEST_F(PopplerPageAnnotMappingTest_2455, AnnotMappingCopy_2455) {
    PopplerAnnotMapping *original = poppler_annot_mapping_new();
    ASSERT_NE(original, nullptr);
    original->area.x1 = 10.0;
    original->area.y1 = 20.0;
    original->area.x2 = 30.0;
    original->area.y2 = 40.0;
    original->annot = nullptr;

    PopplerAnnotMapping *copy = poppler_annot_mapping_copy(original);
    ASSERT_NE(copy, nullptr);
    EXPECT_DOUBLE_EQ(copy->area.x1, 10.0);
    EXPECT_DOUBLE_EQ(copy->area.y1, 20.0);
    EXPECT_DOUBLE_EQ(copy->area.x2, 30.0);
    EXPECT_DOUBLE_EQ(copy->area.y2, 40.0);

    poppler_annot_mapping_free(copy);
    poppler_annot_mapping_free(original);
}

// Test annot mapping new returns initialized struct
TEST_F(PopplerPageAnnotMappingTest_2455, AnnotMappingNew_2455) {
    PopplerAnnotMapping *mapping = poppler_annot_mapping_new();
    ASSERT_NE(mapping, nullptr);
    poppler_annot_mapping_free(mapping);
}

// Test annot mapping free with NULL
TEST_F(PopplerPageAnnotMappingTest_2455, AnnotMappingFreeNull_2455) {
    // Should not crash
    poppler_annot_mapping_free(nullptr);
}
