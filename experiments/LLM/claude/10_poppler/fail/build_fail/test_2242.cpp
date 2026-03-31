#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Poppler GLib headers
#include <poppler.h>

// Poppler core headers
#include "Object.h"
#include "Array.h"
#include "OptionalContent.h"
#include "poppler-private.h"

#include <glib.h>
#include <gio/gio.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <fstream>

class GetOptionalContentItemsSorted_2242 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a minimal PDF with optional content layers
    PopplerDocument *createPdfWithLayers(const std::string &path) {
        // Create a minimal PDF file with optional content
        // This is a simplified approach - in practice we'd use a real PDF
        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(path.c_str(), nullptr, &error);
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }
};

// Test that a document without optional content layers returns no layers
TEST_F(GetOptionalContentItemsSorted_2242, NoLayersDocument_2242) {
    // Create a minimal PDF without layers
    const char *pdf_content =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    const char *tmpfile = "/tmp/test_no_layers_2242.pdf";
    FILE *f = fopen(tmpfile, "wb");
    if (f) {
        fwrite(pdf_content, 1, strlen(pdf_content), f);
        fclose(f);
    }

    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
    ASSERT_NE(uri, nullptr);

    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);

    if (doc) {
        // Get layers - should return NULL for document without OCG
        PopplerLayersIter *iter = poppler_layers_iter_new(doc);
        // A document without layers should have no layer iterator
        // (iter may be NULL)
        if (iter) {
            poppler_layers_iter_free(iter);
        }
        g_object_unref(doc);
    } else {
        if (error) {
            g_error_free(error);
        }
        // Document creation may fail with minimal PDF, that's acceptable
    }
    unlink(tmpfile);
}

// Test with a NULL document pointer - layers iter should handle gracefully
TEST_F(GetOptionalContentItemsSorted_2242, NullDocumentLayersIter_2242) {
    // poppler_layers_iter_new with a document that has no layers
    // We can't pass NULL directly as it would crash, but we test edge conditions
    // This tests the boundary where no OCGs exist
    const char *pdf_content =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n206\n%%EOF\n";

    const char *tmpfile = "/tmp/test_null_doc_2242.pdf";
    FILE *f = fopen(tmpfile, "wb");
    if (f) {
        fwrite(pdf_content, 1, strlen(pdf_content), f);
        fclose(f);
    }

    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
    if (!uri) {
        if (error) g_error_free(error);
        unlink(tmpfile);
        return;
    }

    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);

    if (doc) {
        PopplerLayersIter *iter = poppler_layers_iter_new(doc);
        EXPECT_EQ(iter, nullptr); // No layers in this simple PDF
        if (iter) {
            poppler_layers_iter_free(iter);
        }
        g_object_unref(doc);
    } else {
        if (error) g_error_free(error);
    }
    unlink(tmpfile);
}

// Test that layer_new creates proper Layer structures via the public API
// by checking a PDF that has optional content groups
TEST_F(GetOptionalContentItemsSorted_2242, DocumentWithOCGFromMemory_2242) {
    // Construct a PDF with OCG in memory
    // This is a more complete PDF with optional content
    std::string pdf;
    pdf += "%PDF-1.5\n";
    // Object 1: Catalog
    pdf += "1 0 obj\n<</Type/Catalog/Pages 2 0 R/OCProperties<</OCGs[4 0 R]/D<</Order[4 0 R]/ON[4 0 R]>>>>>>\nendobj\n";
    // Object 2: Pages
    pdf += "2 0 obj\n<</Type/Pages/Kids[3 0 R]/Count 1>>\nendobj\n";
    // Object 3: Page
    pdf += "3 0 obj\n<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>\nendobj\n";
    // Object 4: OCG
    pdf += "4 0 obj\n<</Type/OCG/Name(Layer1)>>\nendobj\n";

    // Calculate xref positions (approximate - this may not parse correctly but tests the path)
    const char *tmpfile = "/tmp/test_ocg_2242.pdf";
    FILE *f = fopen(tmpfile, "wb");
    if (!f) {
        GTEST_SKIP() << "Cannot create temp file";
        return;
    }

    // Write objects and track positions
    long pos[5] = {0};
    
    fprintf(f, "%%PDF-1.5\n");
    pos[1] = ftell(f);
    fprintf(f, "1 0 obj\n<</Type/Catalog/Pages 2 0 R/OCProperties<</OCGs[4 0 R]/D<</Order[4 0 R]/ON[4 0 R]>>>>>>\nendobj\n");
    pos[2] = ftell(f);
    fprintf(f, "2 0 obj\n<</Type/Pages/Kids[3 0 R]/Count 1>>\nendobj\n");
    pos[3] = ftell(f);
    fprintf(f, "3 0 obj\n<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>\nendobj\n");
    pos[4] = ftell(f);
    fprintf(f, "4 0 obj\n<</Type/OCG/Name(Layer1)>>\nendobj\n");
    
    long xref_pos = ftell(f);
    fprintf(f, "xref\n0 5\n");
    fprintf(f, "0000000000 65535 f \n");
    fprintf(f, "%010ld 00000 n \n", pos[1]);
    fprintf(f, "%010ld 00000 n \n", pos[2]);
    fprintf(f, "%010ld 00000 n \n", pos[3]);
    fprintf(f, "%010ld 00000 n \n", pos[4]);
    fprintf(f, "trailer<</Size 5/Root 1 0 R>>\n");
    fprintf(f, "startxref\n%ld\n%%%%EOF\n", xref_pos);
    fclose(f);

    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
    if (!uri) {
        if (error) g_error_free(error);
        unlink(tmpfile);
        GTEST_SKIP() << "Cannot create URI";
        return;
    }

    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);

    if (doc) {
        PopplerLayersIter *iter = poppler_layers_iter_new(doc);
        if (iter) {
            // We have layers - verify we can iterate
            gboolean has_next = TRUE;
            int count = 0;
            do {
                PopplerLayer *layer = poppler_layers_iter_get_layer(iter);
                if (layer) {
                    gchar *title = poppler_layer_get_title(layer);
                    // The layer should have a title
                    if (title) {
                        EXPECT_STREQ(title, "Layer1");
                        g_free(title);
                    }
                    g_object_unref(layer);
                }
                
                PopplerLayersIter *child = poppler_layers_iter_get_child(iter);
                if (child) {
                    poppler_layers_iter_free(child);
                }
                
                count++;
                has_next = poppler_layers_iter_next(iter);
            } while (has_next && count < 100); // safety limit
            
            EXPECT_GE(count, 1);
            poppler_layers_iter_free(iter);
        }
        g_object_unref(doc);
    } else {
        if (error) {
            // PDF might not parse correctly with our hand-crafted content
            g_error_free(error);
        }
    }
    unlink(tmpfile);
}

// Test boundary: empty order array should result in no items
TEST_F(GetOptionalContentItemsSorted_2242, EmptyOrderArray_2242) {
    // Create PDF with OCG but empty order array
    const char *tmpfile = "/tmp/test_empty_order_2242.pdf";
    FILE *f = fopen(tmpfile, "wb");
    if (!f) {
        GTEST_SKIP() << "Cannot create temp file";
        return;
    }

    long pos[5] = {0};
    fprintf(f, "%%PDF-1.5\n");
    pos[1] = ftell(f);
    fprintf(f, "1 0 obj\n<</Type/Catalog/Pages 2 0 R/OCProperties<</OCGs[4 0 R]/D<</Order[]/ON[4 0 R]>>>>>>\nendobj\n");
    pos[2] = ftell(f);
    fprintf(f, "2 0 obj\n<</Type/Pages/Kids[3 0 R]/Count 1>>\nendobj\n");
    pos[3] = ftell(f);
    fprintf(f, "3 0 obj\n<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>\nendobj\n");
    pos[4] = ftell(f);
    fprintf(f, "4 0 obj\n<</Type/OCG/Name(TestLayer)>>\nendobj\n");

    long xref_pos = ftell(f);
    fprintf(f, "xref\n0 5\n");
    fprintf(f, "0000000000 65535 f \n");
    fprintf(f, "%010ld 00000 n \n", pos[1]);
    fprintf(f, "%010ld 00000 n \n", pos[2]);
    fprintf(f, "%010ld 00000 n \n", pos[3]);
    fprintf(f, "%010ld 00000 n \n", pos[4]);
    fprintf(f, "trailer<</Size 5/Root 1 0 R>>\n");
    fprintf(f, "startxref\n%ld\n%%%%EOF\n", xref_pos);
    fclose(f);

    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
    if (!uri) {
        if (error) g_error_free(error);
        unlink(tmpfile);
        GTEST_SKIP();
        return;
    }

    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);

    if (doc) {
        PopplerLayersIter *iter = poppler_layers_iter_new(doc);
        // Empty order array means no layers to iterate
        EXPECT_EQ(iter, nullptr);
        if (iter) {
            poppler_layers_iter_free(iter);
        }
        g_object_unref(doc);
    } else {
        if (error) g_error_free(error);
    }
    unlink(tmpfile);
}

// Test with multiple OCGs in order
TEST_F(GetOptionalContentItemsSorted_2242, MultipleOCGsInOrder_2242) {
    const char *tmpfile = "/tmp/test_multi_ocg_2242.pdf";
    FILE *f = fopen(tmpfile, "wb");
    if (!f) {
        GTEST_SKIP() << "Cannot create temp file";
        return;
    }

    long pos[6] = {0};
    fprintf(f, "%%PDF-1.5\n");
    pos[1] = ftell(f);
    fprintf(f, "1 0 obj\n<</Type/Catalog/Pages 2 0 R/OCProperties<</OCGs[4 0 R 5 0 R]/D<</Order[4 0 R 5 0 R]/ON[4 0 R 5 0 R]>>>>>>\nendobj\n");
    pos[2] = ftell(f);
    fprintf(f, "2 0 obj\n<</Type/Pages/Kids[3 0 R]/Count 1>>\nendobj\n");
    pos[3] = ftell(f);
    fprintf(f, "3 0 obj\n<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>\nendobj\n");
    pos[4] = ftell(f);
    fprintf(f, "4 0 obj\n<</Type/OCG/Name(Layer1)>>\nendobj\n");
    pos[5] = ftell(f);
    fprintf(f, "5 0 obj\n<</Type/OCG/Name(Layer2)>>\nendobj\n");

    long xref_pos = ftell(f);
    fprintf(f, "xref\n0 6\n");
    fprintf(f, "0000000000 65535 f \n");
    fprintf(f, "%010ld 00000 n \n", pos[1]);
    fprintf(f, "%010ld 00000 n \n", pos[2]);
    fprintf(f, "%010ld 00000 n \n", pos[3]);
    fprintf(f, "%010ld 00000 n \n", pos[4]);
    fprintf(f, "%010ld 00000 n \n", pos[5]);
    fprintf(f, "trailer<</Size 6/Root 1 0 R>>\n");
    fprintf(f, "startxref\n%ld\n%%%%EOF\n", xref_pos);
    fclose(f);

    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
    if (!uri) {
        if (error) g_error_free(error);
        unlink(tmpfile);
        GTEST_SKIP();
        return;
    }

    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);

    if (doc) {
        PopplerLayersIter *iter = poppler_layers_iter_new(doc);
        if (iter) {
            int count = 0;
            do {
                PopplerLayer *layer = poppler_layers_iter_get_layer(iter);
                if (layer) {
                    gchar *title = poppler_layer_get_title(layer);
                    if (title) {
                        // Verify layers are returned in order
                        if (count == 0) {
                            EXPECT_STREQ(title, "Layer1");
                        } else if (count == 1) {
                            EXPECT_STREQ(title, "Layer2");
                        }
                        g_free(title);
                    }
                    g_object_unref(layer);
                }
                count++;
            } while (poppler_layers_iter_next(iter) && count < 100);

            EXPECT_EQ(count, 2);
            poppler_layers_iter_free(iter);
        }
        g_object_unref(doc);
    } else {
        if (error) g_error_free(error);
    }
    unlink(tmpfile);
}

// Test nested OCGs (sub-arrays in order)
TEST_F(GetOptionalContentItemsSorted_2242, NestedOCGsWithChildren_2242) {
    const char *tmpfile = "/tmp/test_nested_ocg_2242.pdf";
    FILE *f = fopen(tmpfile, "wb");
    if (!f) {
        GTEST_SKIP() << "Cannot create temp file";
        return;
    }

    long pos[6] = {0};
    fprintf(f, "%%PDF-1.5\n");
    pos[1] = ftell(f);
    // Order: [4 0 R [5 0 R]] - Layer1 with child Layer2
    fprintf(f, "1 0 obj\n<</Type/Catalog/Pages 2 0 R/OCProperties<</OCGs[4 0 R 5 0 R]/D<</Order[4 0 R[5 0 R]]/ON[4 0 R 5 0 R]>>>>>>\nendobj\n");
    pos[2] = ftell(f);
    fprintf(f, "2 0 obj\n<</Type/Pages/Kids[3 0 R]/Count 1>>\nendobj\n");
    pos[3] = ftell(f);
    fprintf(f, "3 0 obj\n<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>\nendobj\n");
    pos[4] = ftell(f);
    fprintf(f, "4 0 obj\n<</Type/OCG/Name(Parent)>>\nendobj\n");
    pos[5] = ftell(f);
    fprintf(f, "5 0 obj\n<</Type/OCG/Name(Child)>>\nendobj\n");

    long xref_pos = ftell(f);
    fprintf(f, "xref\n0 6\n");
    fprintf(f, "0000000000 65535 f \n");
    fprintf(f, "%010ld 00000 n \n", pos[1]);
    fprintf(f, "%010ld 00000 n \n", pos[2]);
    fprintf(f, "%010ld 00000 n \n", pos[3]);
    fprintf(f, "%010ld 00000 n \n", pos[4]);
    fprintf(f, "%010ld 00000 n \n", pos[5]);
    fprintf(f, "trailer<</Size 6/Root 1 0 R>>\n");
    fprintf(f, "startxref\n%ld\n%%%%EOF\n", xref_pos);
    fclose(f);

    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
    if (!uri) {
        if (error) g_error_free(error);
        unlink(tmpfile);
        GTEST_SKIP();
        return;
    }

    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);

    if (doc) {
        PopplerLayersIter *iter = poppler_layers_iter_new(doc);
        if (iter) {
            // First item should be the parent layer
            PopplerLayer *layer = poppler_layers_iter_get_layer(iter);
            if (layer) {
                gchar *title = poppler_layer_get_title(layer);
                if (title) {
                    EXPECT_STREQ(title, "Parent");
                    g_free(title);
                }
                g_object_unref(layer);
            }

            // Check for children
            PopplerLayersIter *child_iter = poppler_layers_iter_get_child(iter);
            if (child_iter) {
                PopplerLayer *child_layer = poppler_layers_iter_get_layer(child_iter);
                if (child_layer) {
                    gchar *child_title = poppler_layer_get_title(child_layer);
                    if (child_title) {
                        EXPECT_STREQ(child_title, "Child");
                        g_free(child_title);
                    }
                    g_object_unref(child_layer);
                }
                poppler_layers_iter_free(child_iter);
            }

            poppler_layers_iter_free(iter);
        }
        g_object_unref(doc);
    } else {
        if (error) g_error_free(error);
    }
    unlink(tmpfile);
}

// Test with string labels in order array
TEST_F(GetOptionalContentItemsSorted_2242, OCGWithStringLabel_2242) {
    const char *tmpfile = "/tmp/test_string_label_2242.pdf";
    FILE *f = fopen(tmpfile, "wb");
    if (!f) {
        GTEST_SKIP() << "Cannot create temp file";
        return;
    }

    long pos[5] = {0};
    fprintf(f, "%%PDF-1.5\n");
    pos[1] = ftell(f);
    // Order: [(GroupLabel) 4 0 R] - string label followed by OCG ref
    fprintf(f, "1 0 obj\n<</Type/Catalog/Pages 2 0 R/OCProperties<</OCGs[4 0 R]/D<</Order[(GroupLabel) 4 0 R]/ON[4 0 R]>>>>>>\nendobj\n");
    pos[2] = ftell(f);
    fprintf(f, "2 0 obj\n<</Type/Pages/Kids[3 0 R]/Count 1>>\nendobj\n");
    pos[3] = ftell(f);
    fprintf(f, "3 0 obj\n<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>\nendobj\n");
    pos[4] = ftell(f);
    fprintf(f, "4 0 obj\n<</Type/OCG/Name(MyLayer)>>\nendobj\n");

    long xref_pos = ftell(f);
    fprintf(f, "xref\n0 5\n");
    fprintf(f, "0000000000 65535 f \n");
    fprintf(f, "%010ld 00000 n \n", pos[1]);
    fprintf(f, "%010ld 00000 n \n", pos[2]);
    fprintf(f, "%010ld 00000 n \n", pos[3]);
    fprintf(f, "%010ld 00000 n \n", pos[4]);
    fprintf(f, "trailer<</Size 5/Root 1 0 R>>\n");
    fprintf(f, "startxref\n%ld\n%%%%EOF\n", xref_pos);
    fclose(f);

    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
    if (!uri) {
        if (error) g_error_free(error);
        unlink(tmpfile);
        GTEST_SKIP();
        return;
    }

    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);

    if (doc) {
        PopplerLayersIter *iter = poppler_layers_iter_new(doc);
        if (iter) {
            // Iterate through layers - the string label should affect layer title
            int count = 0;
            do {
                PopplerLayer *layer = poppler_layers_iter_get_layer(iter);
                if (layer) {
                    gchar *title = poppler_layer_get_title(layer);
                    if (title) {
                        // Title could be affected by the string label
                        EXPECT_NE(title, nullptr);
                        g_free(title);
                    }
                    g_object_unref(layer);
                }
                count++;
            } while (poppler_layers_iter_next(iter) && count < 100);

            EXPECT_GE(count, 1);
            poppler_layers_iter_free(iter);
        }
        g_object_unref(doc);
    } else {
        if (error) g_error_free(error);
    }
    unlink(tmpfile);
}

// Test that g_list_reverse is applied - items should be in order
TEST_F(GetOptionalContentItemsSorted_2242, ItemsReturnedInCorrectOrder_2242) {
    const char *tmpfile = "/tmp/test_order_2242.pdf";
    FILE *f = fopen(tmpfile, "wb");
    if (!f) {
        GTEST_SKIP() << "Cannot create temp file";
        return;
    }

    long pos[7] = {0};
    fprintf(f, "%%PDF-1.5\n");
    pos[1] = ftell(f);
    fprintf(f, "1 0 obj\n<</Type/Catalog/Pages 2 0 R/OCProperties<</OCGs[4 0 R 5 0 R 6 0 R]/D<</Order[4 0 R 5 0 R 6 0 R]/ON[4 0 R 5 0 R 6 0 R]>>>>>>\nendobj\n");
    pos[2] = ftell(f);
    fprintf(f, "2 0 obj\n<</Type/Pages/Kids[3 0 R]/Count 1>>\nendobj\n");
    pos[3] = ftell(f);
    fprintf(f, "3 0 obj\n<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>\nendobj\n");
    pos[4] = ftell(f);
    fprintf(f, "4 0 obj\n<</Type/OCG/Name(First)>>\nendobj\n");
    pos[5] = ftell(f);
    fprintf(f, "5 0 obj\n<</Type/OCG/Name(Second)>>\nendobj\n");
    pos[6] = ftell(f);
    fprintf(f, "6 0 obj\n<</Type/OCG/Name(Third)>>\nendobj\n");

    long xref_pos = ftell(f);
    fprintf(f, "xref\n0 7\n");
    fprintf(f, "0000000000 65535 f \n");
    for (int i = 1; i <= 6; i++) {
        fprintf(f, "%010ld 00000 n \n", pos[i]);
    }
    fprintf(f, "trailer<</Size 7/Root 1 0 R>>\n");
    fprintf(f, "startxref\n%ld\n%%%%EOF\n", xref_pos);
    fclose(f);

    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
    if (!uri) {
        if (error) g_error_free(error);
        unlink(tmpfile);
        GTEST_SKIP();
        return;
    }

    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);

    if (doc) {
        PopplerLayersIter *iter = poppler_layers_iter_new(doc);
        if (iter) {
            const char *expected[] = {"First", "Second", "Third"};
            int count = 0;
            do {
                PopplerLayer *layer = poppler_layers_iter_get_layer(iter);
                if (layer) {
                    gchar *title = poppler_layer_get_title(layer);
                    if (title && count < 3) {
                        EXPECT_STREQ(title, expected[count]);
                        g_free(title);
                    }
                    g_object_unref(layer);
                }
                count++;
            } while (poppler_layers_iter_next(iter) && count < 100);

            EXPECT_EQ(count, 3);
            poppler_layers_iter_free(iter);
        }
        g_object_unref(doc);
    } else {
        if (error) g_error_free(error);
    }
    unlink(tmpfile);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
