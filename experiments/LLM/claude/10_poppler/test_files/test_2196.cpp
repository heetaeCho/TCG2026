#include <glib.h>
#include <glib-object.h>
#include <poppler-document.h>
#include <poppler.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <fstream>
#include <gtest/gtest.h>

class PopplerDocumentGetPageModeTest_2196 : public ::testing::Test {
protected:
    void SetUp() override {
        document_ = nullptr;
    }

    void TearDown() override {
        if (document_) {
            g_object_unref(document_);
            document_ = nullptr;
        }
    }

    PopplerDocument *loadDocumentFromFile(const std::string &path) {
        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(path.c_str(), nullptr, &error);
        if (!uri) {
            if (error) {
                g_error_free(error);
            }
            return nullptr;
        }
        PopplerDocument *doc = poppler_document_new_from_uri(uri, nullptr, &error);
        g_free(uri);
        if (error) {
            g_error_free(error);
        }
        return doc;
    }

    // Create a minimal PDF in memory with a specific PageMode
    PopplerDocument *createMinimalPDFWithPageMode(const char *pageModeStr) {
        // Build a minimal PDF with the given PageMode in the catalog
        std::string pdf;
        pdf += "%PDF-1.4\n";

        // Object 1: Catalog
        std::string catalogObj = "1 0 obj\n<< /Type /Catalog /Pages 2 0 R";
        if (pageModeStr && strlen(pageModeStr) > 0) {
            catalogObj += " /PageMode /";
            catalogObj += pageModeStr;
        }
        catalogObj += " >>\nendobj\n";

        // Object 2: Pages
        std::string pagesObj = "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";

        // Object 3: Page
        std::string pageObj = "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";

        size_t offset1 = pdf.size();
        pdf += catalogObj;
        size_t offset2 = pdf.size();
        pdf += pagesObj;
        size_t offset3 = pdf.size();
        pdf += pageObj;

        size_t xrefOffset = pdf.size();
        pdf += "xref\n";
        pdf += "0 4\n";
        pdf += "0000000000 65535 f \n";

        char buf[64];
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", offset1);
        pdf += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", offset2);
        pdf += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", offset3);
        pdf += buf;

        pdf += "trailer\n<< /Size 4 /Root 1 0 R >>\n";
        pdf += "startxref\n";
        snprintf(buf, sizeof(buf), "%zu\n", xrefOffset);
        pdf += buf;
        pdf += "%%EOF\n";

        GError *error = nullptr;
        GBytes *bytes = g_bytes_new(pdf.data(), pdf.size());
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

        PopplerDocument *doc = poppler_document_new_from_stream(stream, (goffset)pdf.size(), nullptr, nullptr, &error);

        g_object_unref(stream);
        g_bytes_unref(bytes);

        if (error) {
            g_error_free(error);
        }
        return doc;
    }

    PopplerDocument *document_;
};

TEST_F(PopplerDocumentGetPageModeTest_2196, NullDocumentReturnsUnset_2196) {
    // Passing NULL should return POPPLER_PAGE_MODE_UNSET (via g_return_val_if_fail)
    PopplerPageMode mode = poppler_document_get_page_mode(nullptr);
    EXPECT_EQ(mode, POPPLER_PAGE_MODE_UNSET);
}

TEST_F(PopplerDocumentGetPageModeTest_2196, DefaultPageModeNone_2196) {
    // A minimal PDF without explicit PageMode should return UseNone or Unset
    document_ = createMinimalPDFWithPageMode("");
    if (document_) {
        PopplerPageMode mode = poppler_document_get_page_mode(document_);
        // Without PageMode set, catalog default is typically UseNone
        EXPECT_TRUE(mode == POPPLER_PAGE_MODE_NONE || mode == POPPLER_PAGE_MODE_UNSET);
    } else {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
}

TEST_F(PopplerDocumentGetPageModeTest_2196, PageModeUseNone_2196) {
    document_ = createMinimalPDFWithPageMode("UseNone");
    if (document_) {
        PopplerPageMode mode = poppler_document_get_page_mode(document_);
        EXPECT_EQ(mode, POPPLER_PAGE_MODE_NONE);
    } else {
        GTEST_SKIP() << "Could not create PDF with UseNone PageMode";
    }
}

TEST_F(PopplerDocumentGetPageModeTest_2196, PageModeUseOutlines_2196) {
    document_ = createMinimalPDFWithPageMode("UseOutlines");
    if (document_) {
        PopplerPageMode mode = poppler_document_get_page_mode(document_);
        EXPECT_EQ(mode, POPPLER_PAGE_MODE_USE_OUTLINES);
    } else {
        GTEST_SKIP() << "Could not create PDF with UseOutlines PageMode";
    }
}

TEST_F(PopplerDocumentGetPageModeTest_2196, PageModeUseThumbs_2196) {
    document_ = createMinimalPDFWithPageMode("UseThumbs");
    if (document_) {
        PopplerPageMode mode = poppler_document_get_page_mode(document_);
        EXPECT_EQ(mode, POPPLER_PAGE_MODE_USE_THUMBS);
    } else {
        GTEST_SKIP() << "Could not create PDF with UseThumbs PageMode";
    }
}

TEST_F(PopplerDocumentGetPageModeTest_2196, PageModeFullScreen_2196) {
    document_ = createMinimalPDFWithPageMode("FullScreen");
    if (document_) {
        PopplerPageMode mode = poppler_document_get_page_mode(document_);
        EXPECT_EQ(mode, POPPLER_PAGE_MODE_FULL_SCREEN);
    } else {
        GTEST_SKIP() << "Could not create PDF with FullScreen PageMode";
    }
}

TEST_F(PopplerDocumentGetPageModeTest_2196, PageModeUseOC_2196) {
    document_ = createMinimalPDFWithPageMode("UseOC");
    if (document_) {
        PopplerPageMode mode = poppler_document_get_page_mode(document_);
        EXPECT_EQ(mode, POPPLER_PAGE_MODE_USE_OC);
    } else {
        GTEST_SKIP() << "Could not create PDF with UseOC PageMode";
    }
}

TEST_F(PopplerDocumentGetPageModeTest_2196, PageModeUseAttachments_2196) {
    document_ = createMinimalPDFWithPageMode("UseAttachments");
    if (document_) {
        PopplerPageMode mode = poppler_document_get_page_mode(document_);
        EXPECT_EQ(mode, POPPLER_PAGE_MODE_USE_ATTACHMENTS);
    } else {
        GTEST_SKIP() << "Could not create PDF with UseAttachments PageMode";
    }
}

TEST_F(PopplerDocumentGetPageModeTest_2196, ReturnValueIsValidEnum_2196) {
    // For any valid document, the return value should be within the enum range
    document_ = createMinimalPDFWithPageMode("UseNone");
    if (document_) {
        PopplerPageMode mode = poppler_document_get_page_mode(document_);
        EXPECT_GE(mode, POPPLER_PAGE_MODE_UNSET);
        EXPECT_LE(mode, POPPLER_PAGE_MODE_USE_ATTACHMENTS);
    } else {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
}

TEST_F(PopplerDocumentGetPageModeTest_2196, ConsistentResultOnMultipleCalls_2196) {
    // Calling the function multiple times should yield the same result
    document_ = createMinimalPDFWithPageMode("FullScreen");
    if (document_) {
        PopplerPageMode mode1 = poppler_document_get_page_mode(document_);
        PopplerPageMode mode2 = poppler_document_get_page_mode(document_);
        EXPECT_EQ(mode1, mode2);
    } else {
        GTEST_SKIP() << "Could not create PDF document";
    }
}
