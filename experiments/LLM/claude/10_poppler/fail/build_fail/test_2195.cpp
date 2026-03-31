#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glib-object.h>

// Include necessary headers
extern "C" {
#include "poppler-document.h"
}
#include "poppler-private.h"
#include "Catalog.h"
#include "PDFDoc.h"

// We need to test poppler_document_get_page_layout which depends on:
// 1. A valid PopplerDocument (GObject-based)
// 2. The document's internal PDFDoc and Catalog

// Since we can't easily construct real PopplerDocument objects without
// actual PDF files, we'll use real PDF loading through the poppler glib API.

#include "poppler.h"
#include <cstdio>
#include <cstring>
#include <fstream>

class PopplerDocumentGetPageLayoutTest_2195 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {
        if (doc_) {
            g_object_unref(doc_);
            doc_ = nullptr;
        }
    }

    // Helper to create a minimal PDF in memory with a given page layout
    PopplerDocument *createPdfWithPageLayout(const char *layoutStr) {
        // Create a minimal PDF with the specified PageLayout
        std::string pdf;
        pdf += "%PDF-1.4\n";
        pdf += "1 0 obj\n<< /Type /Catalog /Pages 2 0 R";
        if (layoutStr && strlen(layoutStr) > 0) {
            pdf += " /PageLayout /";
            pdf += layoutStr;
        }
        pdf += " >>\nendobj\n";
        pdf += "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        pdf += "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";

        // Build xref
        std::string xref_section;
        // We need to track offsets - let's just build a simple one
        // Actually, let's write to a temp file and load it
        std::string tmpfile = "/tmp/test_poppler_layout_2195.pdf";
        
        // Rebuild with proper offsets
        std::vector<size_t> offsets;
        std::string body;
        
        body = "%PDF-1.4\n";
        offsets.push_back(body.size());
        
        std::string obj1 = "1 0 obj\n<< /Type /Catalog /Pages 2 0 R";
        if (layoutStr && strlen(layoutStr) > 0) {
            obj1 += " /PageLayout /";
            obj1 += layoutStr;
        }
        obj1 += " >>\nendobj\n";
        body += obj1;
        
        offsets.push_back(body.size());
        body += "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        
        offsets.push_back(body.size());
        body += "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        
        size_t xref_offset = body.size();
        
        char buf[256];
        std::string xref;
        xref += "xref\n";
        xref += "0 4\n";
        snprintf(buf, sizeof(buf), "0000000000 65535 f \n");
        xref += buf;
        for (int i = 0; i < 3; i++) {
            snprintf(buf, sizeof(buf), "%010zu 00000 n \n", offsets[i]);
            xref += buf;
        }
        
        xref += "trailer\n<< /Size 4 /Root 1 0 R >>\n";
        snprintf(buf, sizeof(buf), "startxref\n%zu\n%%%%EOF\n", xref_offset);
        xref += buf;
        
        body += xref;
        
        std::ofstream ofs(tmpfile, std::ios::binary);
        ofs.write(body.data(), body.size());
        ofs.close();
        
        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(tmpfile.c_str(), nullptr, &error);
        if (!uri) {
            if (error) g_error_free(error);
            return nullptr;
        }
        
        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        if (error) {
            g_error_free(error);
        }
        
        return doc;
    }

    PopplerDocument *doc_ = nullptr;
};

// Test: NULL document should return POPPLER_PAGE_LAYOUT_UNSET
TEST_F(PopplerDocumentGetPageLayoutTest_2195, NullDocument_ReturnsUnset_2195) {
    PopplerPageLayout layout = poppler_document_get_page_layout(nullptr);
    EXPECT_EQ(layout, POPPLER_PAGE_LAYOUT_UNSET);
}

// Test: PDF with no PageLayout specified should return POPPLER_PAGE_LAYOUT_UNSET
TEST_F(PopplerDocumentGetPageLayoutTest_2195, NoPageLayout_ReturnsUnset_2195) {
    doc_ = createPdfWithPageLayout("");
    if (!doc_) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    PopplerPageLayout layout = poppler_document_get_page_layout(doc_);
    EXPECT_EQ(layout, POPPLER_PAGE_LAYOUT_UNSET);
}

// Test: PDF with SinglePage layout
TEST_F(PopplerDocumentGetPageLayoutTest_2195, SinglePageLayout_ReturnsSinglePage_2195) {
    doc_ = createPdfWithPageLayout("SinglePage");
    if (!doc_) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    PopplerPageLayout layout = poppler_document_get_page_layout(doc_);
    EXPECT_EQ(layout, POPPLER_PAGE_LAYOUT_SINGLE_PAGE);
}

// Test: PDF with OneColumn layout
TEST_F(PopplerDocumentGetPageLayoutTest_2195, OneColumnLayout_ReturnsOneColumn_2195) {
    doc_ = createPdfWithPageLayout("OneColumn");
    if (!doc_) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    PopplerPageLayout layout = poppler_document_get_page_layout(doc_);
    EXPECT_EQ(layout, POPPLER_PAGE_LAYOUT_ONE_COLUMN);
}

// Test: PDF with TwoColumnLeft layout
TEST_F(PopplerDocumentGetPageLayoutTest_2195, TwoColumnLeftLayout_ReturnsTwoColumnLeft_2195) {
    doc_ = createPdfWithPageLayout("TwoColumnLeft");
    if (!doc_) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    PopplerPageLayout layout = poppler_document_get_page_layout(doc_);
    EXPECT_EQ(layout, POPPLER_PAGE_LAYOUT_TWO_COLUMN_LEFT);
}

// Test: PDF with TwoColumnRight layout
TEST_F(PopplerDocumentGetPageLayoutTest_2195, TwoColumnRightLayout_ReturnsTwoColumnRight_2195) {
    doc_ = createPdfWithPageLayout("TwoColumnRight");
    if (!doc_) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    PopplerPageLayout layout = poppler_document_get_page_layout(doc_);
    EXPECT_EQ(layout, POPPLER_PAGE_LAYOUT_TWO_COLUMN_RIGHT);
}

// Test: PDF with TwoPageLeft layout
TEST_F(PopplerDocumentGetPageLayoutTest_2195, TwoPageLeftLayout_ReturnsTwoPageLeft_2195) {
    doc_ = createPdfWithPageLayout("TwoPageLeft");
    if (!doc_) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    PopplerPageLayout layout = poppler_document_get_page_layout(doc_);
    EXPECT_EQ(layout, POPPLER_PAGE_LAYOUT_TWO_PAGE_LEFT);
}

// Test: PDF with TwoPageRight layout
TEST_F(PopplerDocumentGetPageLayoutTest_2195, TwoPageRightLayout_ReturnsTwoPageRight_2195) {
    doc_ = createPdfWithPageLayout("TwoPageRight");
    if (!doc_) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    PopplerPageLayout layout = poppler_document_get_page_layout(doc_);
    EXPECT_EQ(layout, POPPLER_PAGE_LAYOUT_TWO_PAGE_RIGHT);
}

// Test: Calling the function multiple times on the same document returns consistent results
TEST_F(PopplerDocumentGetPageLayoutTest_2195, ConsistentResults_OnMultipleCalls_2195) {
    doc_ = createPdfWithPageLayout("SinglePage");
    if (!doc_) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    PopplerPageLayout layout1 = poppler_document_get_page_layout(doc_);
    PopplerPageLayout layout2 = poppler_document_get_page_layout(doc_);
    EXPECT_EQ(layout1, layout2);
}

// Test: Return value is within the valid enum range
TEST_F(PopplerDocumentGetPageLayoutTest_2195, ReturnValueInValidRange_2195) {
    doc_ = createPdfWithPageLayout("OneColumn");
    if (!doc_) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    PopplerPageLayout layout = poppler_document_get_page_layout(doc_);
    EXPECT_GE(layout, POPPLER_PAGE_LAYOUT_UNSET);
    EXPECT_LE(layout, POPPLER_PAGE_LAYOUT_TWO_PAGE_RIGHT);
}

// Test: PDF with no layout returns value in valid range
TEST_F(PopplerDocumentGetPageLayoutTest_2195, NoLayout_ReturnValueInValidRange_2195) {
    doc_ = createPdfWithPageLayout("");
    if (!doc_) {
        GTEST_SKIP() << "Could not create test PDF";
    }
    PopplerPageLayout layout = poppler_document_get_page_layout(doc_);
    EXPECT_GE(layout, POPPLER_PAGE_LAYOUT_UNSET);
    EXPECT_LE(layout, POPPLER_PAGE_LAYOUT_TWO_PAGE_RIGHT);
}
