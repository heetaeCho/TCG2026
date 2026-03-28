#include <glib-object.h>
#include <gtest/gtest.h>

// Include poppler glib headers
#include "poppler-document.h"

class PopplerPSFileTest_2253 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need a PopplerDocument to create a PSFile
        // We'll try to use a minimal approach
        doc = nullptr;
        ps_file = nullptr;
    }

    void TearDown() override {
        if (ps_file) {
            g_object_unref(ps_file);
            ps_file = nullptr;
        }
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
    }

    PopplerDocument *doc;
    PopplerPSFile *ps_file;

    bool loadTestDocument(const char *path) {
        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(path, nullptr, &error);
        if (!uri) {
            if (error) {
                g_error_free(error);
            }
            return false;
        }
        doc = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        if (!doc) {
            if (error) {
                g_error_free(error);
            }
            return false;
        }
        return true;
    }
};

// Test that PopplerPSFile type is properly registered
TEST_F(PopplerPSFileTest_2253, TypeRegistration_2253)
{
    GType type = poppler_ps_file_get_type();
    EXPECT_NE(type, G_TYPE_INVALID);
}

// Test that PopplerPSFile is a GObject type
TEST_F(PopplerPSFileTest_2253, IsGObjectDerived_2253)
{
    GType type = poppler_ps_file_get_type();
    EXPECT_TRUE(g_type_is_a(type, G_TYPE_OBJECT));
}

// Test creating a PopplerPSFile with a valid document
TEST_F(PopplerPSFileTest_2253, CreatePSFileFromDocument_2253)
{
    // Try to find a test PDF
    const char *test_pdf = "./test.pdf";
    if (!loadTestDocument(test_pdf)) {
        // Try alternate location
        test_pdf = "/tmp/test.pdf";
        if (!loadTestDocument(test_pdf)) {
            GTEST_SKIP() << "No test PDF available";
        }
    }

    int n_pages = poppler_document_get_n_pages(doc);
    ASSERT_GT(n_pages, 0);

    const char *output_file = "/tmp/test_output_2253.ps";
    ps_file = poppler_ps_file_new(doc, output_file, 0, n_pages);
    EXPECT_NE(ps_file, nullptr);

    if (ps_file) {
        EXPECT_TRUE(POPPLER_IS_PS_FILE(ps_file));
    }
}

// Test that PSFile ref/unref works (GObject finalize path)
TEST_F(PopplerPSFileTest_2253, RefUnrefWorks_2253)
{
    const char *test_pdf = "./test.pdf";
    if (!loadTestDocument(test_pdf)) {
        test_pdf = "/tmp/test.pdf";
        if (!loadTestDocument(test_pdf)) {
            GTEST_SKIP() << "No test PDF available";
        }
    }

    int n_pages = poppler_document_get_n_pages(doc);
    ASSERT_GT(n_pages, 0);

    ps_file = poppler_ps_file_new(doc, "/tmp/test_refunref_2253.ps", 0, n_pages);
    ASSERT_NE(ps_file, nullptr);

    // Ref it
    g_object_ref(ps_file);
    // Unref once - should still be alive
    g_object_unref(ps_file);
    EXPECT_TRUE(POPPLER_IS_PS_FILE(ps_file));

    // The TearDown will do the final unref
}

// Test setting paper size on PSFile
TEST_F(PopplerPSFileTest_2253, SetPaperSize_2253)
{
    const char *test_pdf = "./test.pdf";
    if (!loadTestDocument(test_pdf)) {
        test_pdf = "/tmp/test.pdf";
        if (!loadTestDocument(test_pdf)) {
            GTEST_SKIP() << "No test PDF available";
        }
    }

    int n_pages = poppler_document_get_n_pages(doc);
    ASSERT_GT(n_pages, 0);

    ps_file = poppler_ps_file_new(doc, "/tmp/test_papersize_2253.ps", 0, n_pages);
    ASSERT_NE(ps_file, nullptr);

    // Should not crash - setting paper size
    poppler_ps_file_set_paper_size(ps_file, 612.0, 792.0); // Letter size
}

// Test setting duplex on PSFile
TEST_F(PopplerPSFileTest_2253, SetDuplex_2253)
{
    const char *test_pdf = "./test.pdf";
    if (!loadTestDocument(test_pdf)) {
        test_pdf = "/tmp/test.pdf";
        if (!loadTestDocument(test_pdf)) {
            GTEST_SKIP() << "No test PDF available";
        }
    }

    int n_pages = poppler_document_get_n_pages(doc);
    ASSERT_GT(n_pages, 0);

    ps_file = poppler_ps_file_new(doc, "/tmp/test_duplex_2253.ps", 0, n_pages);
    ASSERT_NE(ps_file, nullptr);

    // Should not crash
    poppler_ps_file_set_duplex(ps_file, TRUE);
    poppler_ps_file_set_duplex(ps_file, FALSE);
}

// Test creating PSFile with boundary page ranges
TEST_F(PopplerPSFileTest_2253, BoundaryPageRange_2253)
{
    const char *test_pdf = "./test.pdf";
    if (!loadTestDocument(test_pdf)) {
        test_pdf = "/tmp/test.pdf";
        if (!loadTestDocument(test_pdf)) {
            GTEST_SKIP() << "No test PDF available";
        }
    }

    int n_pages = poppler_document_get_n_pages(doc);
    ASSERT_GT(n_pages, 0);

    // Single page (first page only)
    ps_file = poppler_ps_file_new(doc, "/tmp/test_boundary_2253.ps", 0, 1);
    EXPECT_NE(ps_file, nullptr);
}

// Test the finalize path is exercised properly
TEST_F(PopplerPSFileTest_2253, FinalizeOnDestroy_2253)
{
    const char *test_pdf = "./test.pdf";
    if (!loadTestDocument(test_pdf)) {
        test_pdf = "/tmp/test.pdf";
        if (!loadTestDocument(test_pdf)) {
            GTEST_SKIP() << "No test PDF available";
        }
    }

    int n_pages = poppler_document_get_n_pages(doc);
    ASSERT_GT(n_pages, 0);

    PopplerPSFile *local_ps = poppler_ps_file_new(doc, "/tmp/test_finalize_2253.ps", 0, n_pages);
    ASSERT_NE(local_ps, nullptr);

    // Set a weak pointer to check when it's destroyed
    gpointer weak_ptr = local_ps;
    g_object_add_weak_pointer(G_OBJECT(local_ps), &weak_ptr);

    g_object_unref(local_ps);
    EXPECT_EQ(weak_ptr, nullptr);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
