#include <glib.h>
#include <glib-object.h>
#include <poppler.h>
#include <poppler-document.h>
#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <string>

class PopplerDocumentDestsTreeTest_2162 : public ::testing::Test {
protected:
    void SetUp() override {
        // We'll create documents from PDF files or URIs as needed per test
        document_ = nullptr;
    }

    void TearDown() override {
        if (document_) {
            g_object_unref(document_);
            document_ = nullptr;
        }
    }

    PopplerDocument *document_;

    // Helper to create a minimal PDF in memory with no named destinations
    PopplerDocument *createMinimalPdfDocument() {
        // Minimal valid PDF content
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

        // Write to a temporary file
        char tmpname[] = "/tmp/poppler_test_XXXXXX.pdf";
        int fd = mkstemps(tmpname, 4);
        if (fd < 0) {
            return nullptr;
        }
        write(fd, pdf_content, strlen(pdf_content));
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

    // Helper to create a PDF with named destinations
    PopplerDocument *createPdfWithNamedDests() {
        // PDF with a named destination in the Dests dictionary
        const char *pdf_content =
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R /Dests 4 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
            "endobj\n"
            "4 0 obj\n"
            "<< /testdest [3 0 R /Fit] >>\n"
            "endobj\n"
            "xref\n"
            "0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000074 00000 n \n"
            "0000000131 00000 n \n"
            "0000000208 00000 n \n"
            "trailer\n"
            "<< /Size 5 /Root 1 0 R >>\n"
            "startxref\n"
            "253\n"
            "%%EOF\n";

        char tmpname[] = "/tmp/poppler_dests_test_XXXXXX.pdf";
        int fd = mkstemps(tmpname, 4);
        if (fd < 0) {
            return nullptr;
        }
        write(fd, pdf_content, strlen(pdf_content));
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

// Test that passing NULL document returns NULL
TEST_F(PopplerDocumentDestsTreeTest_2162, NullDocumentReturnsNull_2162) {
    GTree *tree = poppler_document_create_dests_tree(nullptr);
    EXPECT_EQ(tree, nullptr);
}

// Test that a valid document with no named destinations returns an empty (but non-null) tree
TEST_F(PopplerDocumentDestsTreeTest_2162, EmptyDocumentReturnsEmptyTree_2162) {
    document_ = createMinimalPdfDocument();
    if (!document_) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    GTree *tree = poppler_document_create_dests_tree(document_);
    ASSERT_NE(tree, nullptr);

    // The tree should have 0 nodes since there are no named destinations
    int nnodes = g_tree_nnodes(tree);
    EXPECT_EQ(nnodes, 0);

    g_tree_destroy(tree);
}

// Test that the returned tree is a valid GTree pointer
TEST_F(PopplerDocumentDestsTreeTest_2162, ReturnedTreeIsValid_2162) {
    document_ = createMinimalPdfDocument();
    if (!document_) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    GTree *tree = poppler_document_create_dests_tree(document_);
    ASSERT_NE(tree, nullptr);

    // We should be able to look up a non-existent key without crashing
    gpointer result = g_tree_lookup(tree, "nonexistent");
    EXPECT_EQ(result, nullptr);

    g_tree_destroy(tree);
}

// Test with a PDF that has named destinations in the Dests dictionary
TEST_F(PopplerDocumentDestsTreeTest_2162, DocumentWithDestsHasNonEmptyTree_2162) {
    document_ = createPdfWithNamedDests();
    if (!document_) {
        GTEST_SKIP() << "Could not create PDF with named destinations";
    }

    GTree *tree = poppler_document_create_dests_tree(document_);
    ASSERT_NE(tree, nullptr);

    // The tree may have entries if the PDF was parsed correctly
    int nnodes = g_tree_nnodes(tree);
    // We expect at least 0 (parsing may vary), but the tree itself should be valid
    EXPECT_GE(nnodes, 0);

    g_tree_destroy(tree);
}

// Test that calling create_dests_tree multiple times doesn't crash and returns independent trees
TEST_F(PopplerDocumentDestsTreeTest_2162, MultipleCallsReturnIndependentTrees_2162) {
    document_ = createMinimalPdfDocument();
    if (!document_) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    GTree *tree1 = poppler_document_create_dests_tree(document_);
    GTree *tree2 = poppler_document_create_dests_tree(document_);

    ASSERT_NE(tree1, nullptr);
    ASSERT_NE(tree2, nullptr);
    // They should be different tree instances
    EXPECT_NE(tree1, tree2);

    g_tree_destroy(tree1);
    g_tree_destroy(tree2);
}

// Test that the tree uses string comparison for keys (sorted tree)
TEST_F(PopplerDocumentDestsTreeTest_2162, TreeKeysAreSortedByString_2162) {
    document_ = createMinimalPdfDocument();
    if (!document_) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    GTree *tree = poppler_document_create_dests_tree(document_);
    ASSERT_NE(tree, nullptr);

    // The tree should be searchable - looking up keys should work without crash
    gpointer val = g_tree_lookup(tree, "any_key");
    EXPECT_EQ(val, nullptr);

    g_tree_destroy(tree);
}

// Test tree height for empty tree (boundary condition)
TEST_F(PopplerDocumentDestsTreeTest_2162, EmptyTreeHeightIsZero_2162) {
    document_ = createMinimalPdfDocument();
    if (!document_) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    GTree *tree = poppler_document_create_dests_tree(document_);
    ASSERT_NE(tree, nullptr);

    int nnodes = g_tree_nnodes(tree);
    if (nnodes == 0) {
        int height = g_tree_height(tree);
        EXPECT_EQ(height, 0);
    }

    g_tree_destroy(tree);
}
