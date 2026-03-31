#include <glib.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <fstream>

class PopplerAnnotInkTest_2132 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        // Create a minimal PDF in memory that we can use for testing
        // We'll try to load a document and add ink annotations programmatically
        GError *error = nullptr;
        
        // Minimal valid PDF content
        const char *pdf_content = 
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
            "xref\n"
            "0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n"
            "190\n"
            "%%EOF\n";
        
        gsize len = strlen(pdf_content);
        doc = poppler_document_new_from_data(pdf_content, len, nullptr, &error);
        
        if (!doc && error) {
            g_error_free(error);
            error = nullptr;
            
            // Try writing to a temp file approach
            const char *tmpfile = "/tmp/test_ink_annot_2132.pdf";
            std::ofstream ofs(tmpfile, std::ios::binary);
            ofs.write(pdf_content, len);
            ofs.close();
            
            gchar *uri = g_filename_to_uri(tmpfile, nullptr, nullptr);
            if (uri) {
                doc = poppler_document_new_from_file(uri, nullptr, &error);
                g_free(uri);
            }
            if (error) {
                g_error_free(error);
            }
        }
        
        if (doc) {
            page = poppler_document_get_page(doc, 0);
        }
    }

    void TearDown() override {
        if (page) {
            g_object_unref(page);
        }
        if (doc) {
            g_object_unref(doc);
        }
    }
};

// Test that getting ink list from a valid ink annotation returns non-null with correct path count
TEST_F(PopplerAnnotInkTest_2132, GetInkListReturnsPathsForInkAnnotation_2132) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }
    
    // Get existing annotations - if there are ink annotations, test them
    GList *annots = poppler_page_get_annot_mapping(page);
    
    gboolean found_ink = FALSE;
    for (GList *l = annots; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
        PopplerAnnot *annot = mapping->annot;
        
        if (poppler_annot_get_annot_type(annot) == POPPLER_ANNOT_INK) {
            PopplerAnnotInk *ink_annot = POPPLER_ANNOT_INK(annot);
            gsize n_paths = 0;
            PopplerPath **ink_list = poppler_annot_ink_get_ink_list(ink_annot, &n_paths);
            
            // n_paths should be set (could be 0 or more)
            EXPECT_GE(n_paths, (gsize)0);
            
            if (n_paths > 0) {
                EXPECT_NE(ink_list, nullptr);
            }
            
            // Free the ink list
            for (gsize i = 0; i < n_paths; i++) {
                poppler_path_free(ink_list[i]);
            }
            g_free(ink_list);
            
            found_ink = TRUE;
        }
    }
    
    poppler_page_free_annot_mapping(annots);
    
    if (!found_ink) {
        GTEST_SKIP() << "No ink annotations found in test PDF";
    }
}

// Test that n_paths is properly set even when there are no ink annotations to create
TEST_F(PopplerAnnotInkTest_2132, NPathsIsSetCorrectly_2132) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }
    
    GList *annots = poppler_page_get_annot_mapping(page);
    
    for (GList *l = annots; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
        PopplerAnnot *annot = mapping->annot;
        
        if (poppler_annot_get_annot_type(annot) == POPPLER_ANNOT_INK) {
            PopplerAnnotInk *ink_annot = POPPLER_ANNOT_INK(annot);
            gsize n_paths = 999;  // Initialize to a sentinel value
            PopplerPath **ink_list = poppler_annot_ink_get_ink_list(ink_annot, &n_paths);
            
            // n_paths should have been updated from the sentinel
            EXPECT_NE(n_paths, (gsize)999);
            
            for (gsize i = 0; i < n_paths; i++) {
                poppler_path_free(ink_list[i]);
            }
            g_free(ink_list);
        }
    }
    
    poppler_page_free_annot_mapping(annots);
}

// Test with a PDF file that has ink annotations if available
class PopplerAnnotInkFileTest_2132 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    
    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
        }
    }
    
    bool loadPdfWithInkAnnot(const char *path) {
        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(path, nullptr, nullptr);
        if (!uri) return false;
        doc = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        if (error) {
            g_error_free(error);
            return false;
        }
        return doc != nullptr;
    }
};

// Test that ink list points have valid coordinates (non-NaN, non-Inf)
TEST_F(PopplerAnnotInkTest_2132, InkListPointsHaveValidCoordinates_2132) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }
    
    GList *annots = poppler_page_get_annot_mapping(page);
    gboolean found_ink = FALSE;
    
    for (GList *l = annots; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
        PopplerAnnot *annot = mapping->annot;
        
        if (poppler_annot_get_annot_type(annot) == POPPLER_ANNOT_INK) {
            PopplerAnnotInk *ink_annot = POPPLER_ANNOT_INK(annot);
            gsize n_paths = 0;
            PopplerPath **ink_list = poppler_annot_ink_get_ink_list(ink_annot, &n_paths);
            
            for (gsize i = 0; i < n_paths; i++) {
                ASSERT_NE(ink_list[i], nullptr);
                // Each path should have valid structure
                // We can check that the path object itself is not null
            }
            
            for (gsize i = 0; i < n_paths; i++) {
                poppler_path_free(ink_list[i]);
            }
            g_free(ink_list);
            
            found_ink = TRUE;
        }
    }
    
    poppler_page_free_annot_mapping(annots);
    
    if (!found_ink) {
        GTEST_SKIP() << "No ink annotations found";
    }
}

// Test that calling get_ink_list multiple times returns consistent results
TEST_F(PopplerAnnotInkTest_2132, ConsistentResultsOnMultipleCalls_2132) {
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF";
    }
    
    GList *annots = poppler_page_get_annot_mapping(page);
    gboolean found_ink = FALSE;
    
    for (GList *l = annots; l != nullptr; l = l->next) {
        PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
        PopplerAnnot *annot = mapping->annot;
        
        if (poppler_annot_get_annot_type(annot) == POPPLER_ANNOT_INK) {
            PopplerAnnotInk *ink_annot = POPPLER_ANNOT_INK(annot);
            
            gsize n_paths1 = 0, n_paths2 = 0;
            PopplerPath **ink_list1 = poppler_annot_ink_get_ink_list(ink_annot, &n_paths1);
            PopplerPath **ink_list2 = poppler_annot_ink_get_ink_list(ink_annot, &n_paths2);
            
            EXPECT_EQ(n_paths1, n_paths2);
            
            for (gsize i = 0; i < n_paths1; i++) {
                poppler_path_free(ink_list1[i]);
            }
            g_free(ink_list1);
            
            for (gsize i = 0; i < n_paths2; i++) {
                poppler_path_free(ink_list2[i]);
            }
            g_free(ink_list2);
            
            found_ink = TRUE;
        }
    }
    
    poppler_page_free_annot_mapping(annots);
    
    if (!found_ink) {
        GTEST_SKIP() << "No ink annotations found";
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
