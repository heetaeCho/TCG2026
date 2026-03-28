#include <glib-object.h>
#include <glib.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

// Include poppler glib headers
#include "poppler.h"
#include "poppler-private.h"

#include <cstdio>
#include <cstring>
#include <string>

class PopplerPageRenderToPsTest_2451 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;
    PopplerPage *page = nullptr;
    std::string test_pdf_path;
    std::string output_ps_path;

    void SetUp() override
    {
        // Create a minimal PDF in memory or find a test PDF
        // We'll create a simple one-page PDF file for testing
        const char *pdf_content = "%PDF-1.0\n"
                                  "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                                  "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                                  "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
                                  "xref\n"
                                  "0 4\n"
                                  "0000000000 65535 f \n"
                                  "0000000009 00000 n \n"
                                  "0000000058 00000 n \n"
                                  "0000000115 00000 n \n"
                                  "trailer<</Size 4/Root 1 0 R>>\n"
                                  "startxref\n"
                                  "206\n"
                                  "%%EOF\n";

        // Write test PDF to a temporary file
        test_pdf_path = "/tmp/test_poppler_2451.pdf";
        output_ps_path = "/tmp/test_poppler_output_2451.ps";

        FILE *f = fopen(test_pdf_path.c_str(), "wb");
        if (f) {
            fwrite(pdf_content, 1, strlen(pdf_content), f);
            fclose(f);
        }

        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(test_pdf_path.c_str(), nullptr, &error);
        if (uri) {
            document = poppler_document_new_from_file(uri, nullptr, &error);
            g_free(uri);
        }
        if (error) {
            g_error_free(error);
            error = nullptr;
        }

        if (document) {
            page = poppler_document_get_page(document, 0);
        }
    }

    void TearDown() override
    {
        if (page) {
            g_object_unref(page);
            page = nullptr;
        }
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
        // Clean up temp files
        remove(test_pdf_path.c_str());
        remove(output_ps_path.c_str());
    }
};

// Test that passing a NULL page triggers the g_return_if_fail guard and does not crash
TEST_F(PopplerPageRenderToPsTest_2451, NullPageDoesNotCrash_2451)
{
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    PopplerPSFile *ps_file = poppler_ps_file_new(document, output_ps_path.c_str(), 0, 1);
    ASSERT_NE(ps_file, nullptr);

    poppler_ps_file_set_paper_size(ps_file, 612.0, 792.0);

    // Should safely return without crash due to g_return_if_fail
    // We suppress the GLib warning for this test
    g_test_expect_message("Poppler-glib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_PAGE*");
    poppler_page_render_to_ps(nullptr, ps_file);
    g_test_assert_expected_messages();

    g_object_unref(ps_file);
}

// Test that passing a NULL ps_file triggers the g_return_if_fail guard and does not crash
TEST_F(PopplerPageRenderToPsTest_2451, NullPSFileDoesNotCrash_2451)
{
    if (!page) {
        GTEST_SKIP() << "Could not create test page";
    }

    g_test_expect_message("Poppler-glib", G_LOG_LEVEL_CRITICAL, "*ps_file*");
    poppler_page_render_to_ps(page, nullptr);
    g_test_assert_expected_messages();
}

// Test normal rendering to PS file
TEST_F(PopplerPageRenderToPsTest_2451, NormalRenderToPS_2451)
{
    if (!document || !page) {
        GTEST_SKIP() << "Could not create test document/page";
    }

    PopplerPSFile *ps_file = poppler_ps_file_new(document, output_ps_path.c_str(), 0, 1);
    ASSERT_NE(ps_file, nullptr);

    poppler_ps_file_set_paper_size(ps_file, 612.0, 792.0);

    // This should not crash and should produce output
    poppler_page_render_to_ps(page, ps_file);

    g_object_unref(ps_file);

    // After unref, the PS file should have been written
    FILE *f = fopen(output_ps_path.c_str(), "r");
    if (f) {
        fseek(f, 0, SEEK_END);
        long size = ftell(f);
        fclose(f);
        // The file should have some content
        EXPECT_GT(size, 0);
    }
}

// Test rendering the same page twice to the same PS file (second call reuses PSOutputDev)
TEST_F(PopplerPageRenderToPsTest_2451, RenderSamePageTwice_2451)
{
    if (!document || !page) {
        GTEST_SKIP() << "Could not create test document/page";
    }

    PopplerPSFile *ps_file = poppler_ps_file_new(document, output_ps_path.c_str(), 0, 1);
    ASSERT_NE(ps_file, nullptr);

    poppler_ps_file_set_paper_size(ps_file, 612.0, 792.0);

    // First render - initializes PSOutputDev
    poppler_page_render_to_ps(page, ps_file);
    // Second render - reuses existing PSOutputDev
    poppler_page_render_to_ps(page, ps_file);

    g_object_unref(ps_file);
}

// Test rendering with duplex enabled
TEST_F(PopplerPageRenderToPsTest_2451, RenderWithDuplex_2451)
{
    if (!document || !page) {
        GTEST_SKIP() << "Could not create test document/page";
    }

    PopplerPSFile *ps_file = poppler_ps_file_new(document, output_ps_path.c_str(), 0, 1);
    ASSERT_NE(ps_file, nullptr);

    poppler_ps_file_set_paper_size(ps_file, 612.0, 792.0);
    poppler_ps_file_set_duplex(ps_file, TRUE);

    poppler_page_render_to_ps(page, ps_file);

    g_object_unref(ps_file);
}

// Test rendering with custom paper size
TEST_F(PopplerPageRenderToPsTest_2451, RenderWithCustomPaperSize_2451)
{
    if (!document || !page) {
        GTEST_SKIP() << "Could not create test document/page";
    }

    PopplerPSFile *ps_file = poppler_ps_file_new(document, output_ps_path.c_str(), 0, 1);
    ASSERT_NE(ps_file, nullptr);

    // Use A4 paper size
    poppler_ps_file_set_paper_size(ps_file, 595.0, 842.0);

    poppler_page_render_to_ps(page, ps_file);

    g_object_unref(ps_file);

    FILE *f = fopen(output_ps_path.c_str(), "r");
    if (f) {
        fseek(f, 0, SEEK_END);
        long size = ftell(f);
        fclose(f);
        EXPECT_GT(size, 0);
    }
}

// Test that both NULL page and NULL ps_file are handled
TEST_F(PopplerPageRenderToPsTest_2451, BothNullDoesNotCrash_2451)
{
    g_test_expect_message("Poppler-glib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_PAGE*");
    poppler_page_render_to_ps(nullptr, nullptr);
    g_test_assert_expected_messages();
}

// Test rendering with page range of exactly one page (boundary)
TEST_F(PopplerPageRenderToPsTest_2451, SinglePageRange_2451)
{
    if (!document || !page) {
        GTEST_SKIP() << "Could not create test document/page";
    }

    // first_page == last_page == 0 (single page range)
    PopplerPSFile *ps_file = poppler_ps_file_new(document, output_ps_path.c_str(), 0, 0);
    ASSERT_NE(ps_file, nullptr);

    poppler_ps_file_set_paper_size(ps_file, 612.0, 792.0);

    poppler_page_render_to_ps(page, ps_file);

    g_object_unref(ps_file);
}
