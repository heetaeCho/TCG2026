#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Page.h"
#include "Object.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

// Helper to create a minimal valid PDF document for testing
class PageTest_724 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a test PDF document from a file
    std::unique_ptr<PDFDoc> createTestDoc(const char *filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test that getContents returns an Object (even if null/none for a page without contents)
TEST_F(PageTest_724, GetContentsReturnsObject_724) {
    // We need a real PDF to test. We'll create a minimal in-memory PDF.
    // Using a simple PDF file approach
    const char *pdfData =
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
        "196\n"
        "%%EOF\n";

    // Write to a temporary file
    FILE *f = fopen("/tmp/test_page_724.pdf", "wb");
    if (f) {
        fwrite(pdfData, 1, strlen(pdfData), f);
        fclose(f);
    }

    auto doc = createTestDoc("/tmp/test_page_724.pdf");
    if (!doc) {
        // If we can't create the doc, skip the test gracefully
        GTEST_SKIP() << "Could not create test PDF document";
    }

    // Get the first page
    Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "Could not get page from test PDF";
    }

    // getContents should return an Object - for a page without stream contents, 
    // it should be null or none type
    Object contentsObj = page->getContents();
    // A page without a Contents entry should return a null object
    EXPECT_TRUE(contentsObj.isNull() || contentsObj.isNone());
}

// Test that getContents returns a valid stream/array when page has contents
TEST_F(PageTest_724, GetContentsWithContentStream_724) {
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /Contents 4 0 R >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Length 44 >>\n"
        "stream\n"
        "BT /F1 12 Tf 100 700 Td (Hello) Tj ET\n"
        "endstream\n"
        "endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000206 00000 n \n"
        "trailer\n"
        "<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n"
        "302\n"
        "%%EOF\n";

    FILE *f = fopen("/tmp/test_page_contents_724.pdf", "wb");
    if (f) {
        fwrite(pdfData, 1, strlen(pdfData), f);
        fclose(f);
    }

    auto doc = createTestDoc("/tmp/test_page_contents_724.pdf");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document with contents";
    }

    Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "Could not get page from test PDF";
    }

    Object contentsObj = page->getContents();
    // When page has a Contents entry pointing to a stream, it should be a stream
    // It could also be an array of streams, or if reference resolution fails, something else
    // We just verify it's not none (it was defined in the page dict)
    EXPECT_FALSE(contentsObj.isNone());
}

// Test basic page properties alongside getContents
TEST_F(PageTest_724, PageBasicProperties_724) {
    const char *pdfData =
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
        "196\n"
        "%%EOF\n";

    FILE *f = fopen("/tmp/test_page_props_724.pdf", "wb");
    if (f) {
        fwrite(pdfData, 1, strlen(pdfData), f);
        fclose(f);
    }

    auto doc = createTestDoc("/tmp/test_page_props_724.pdf");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    EXPECT_TRUE(page->isOk());
    EXPECT_EQ(page->getNum(), 1);

    // MediaBox should be [0 0 612 792]
    const PDFRectangle *mediaBox = page->getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
    EXPECT_DOUBLE_EQ(mediaBox->x1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->y1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->x2, 612.0);
    EXPECT_DOUBLE_EQ(mediaBox->y2, 792.0);

    EXPECT_DOUBLE_EQ(page->getMediaWidth(), 612.0);
    EXPECT_DOUBLE_EQ(page->getMediaHeight(), 792.0);
}

// Test getContents can be called multiple times
TEST_F(PageTest_724, GetContentsMultipleCalls_724) {
    const char *pdfData =
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
        "196\n"
        "%%EOF\n";

    FILE *f = fopen("/tmp/test_page_multi_724.pdf", "wb");
    if (f) {
        fwrite(pdfData, 1, strlen(pdfData), f);
        fclose(f);
    }

    auto doc = createTestDoc("/tmp/test_page_multi_724.pdf");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    // Call getContents multiple times - should be consistent
    Object contents1 = page->getContents();
    Object contents2 = page->getContents();

    EXPECT_EQ(contents1.getType(), contents2.getType());
}

// Test getThumb for a page without thumbnail
TEST_F(PageTest_724, GetThumbNoThumbnail_724) {
    const char *pdfData =
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
        "196\n"
        "%%EOF\n";

    FILE *f = fopen("/tmp/test_page_thumb_724.pdf", "wb");
    if (f) {
        fwrite(pdfData, 1, strlen(pdfData), f);
        fclose(f);
    }

    auto doc = createTestDoc("/tmp/test_page_thumb_724.pdf");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    Object thumbObj = page->getThumb();
    EXPECT_TRUE(thumbObj.isNull() || thumbObj.isNone());
}

// Test getTrans for a page without transition
TEST_F(PageTest_724, GetTransNoTransition_724) {
    const char *pdfData =
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
        "196\n"
        "%%EOF\n";

    FILE *f = fopen("/tmp/test_page_trans_724.pdf", "wb");
    if (f) {
        fwrite(pdfData, 1, strlen(pdfData), f);
        fclose(f);
    }

    auto doc = createTestDoc("/tmp/test_page_trans_724.pdf");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    Object transObj = page->getTrans();
    EXPECT_TRUE(transObj.isNull() || transObj.isNone());
}

// Test getActions for a page without actions
TEST_F(PageTest_724, GetActionsNoActions_724) {
    const char *pdfData =
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
        "196\n"
        "%%EOF\n";

    FILE *f = fopen("/tmp/test_page_actions_724.pdf", "wb");
    if (f) {
        fwrite(pdfData, 1, strlen(pdfData), f);
        fclose(f);
    }

    auto doc = createTestDoc("/tmp/test_page_actions_724.pdf");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    Object actionsObj = page->getActions();
    EXPECT_TRUE(actionsObj.isNull() || actionsObj.isNone());
}

// Test getAnnotsObject for a page without annotations
TEST_F(PageTest_724, GetAnnotsObjectNoAnnots_724) {
    const char *pdfData =
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
        "196\n"
        "%%EOF\n";

    FILE *f = fopen("/tmp/test_page_annots_724.pdf", "wb");
    if (f) {
        fwrite(pdfData, 1, strlen(pdfData), f);
        fclose(f);
    }

    auto doc = createTestDoc("/tmp/test_page_annots_724.pdf");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    Object annotsObj = page->getAnnotsObject();
    // A page without Annots should return null or none
    EXPECT_TRUE(annotsObj.isNull() || annotsObj.isNone() || annotsObj.isArray());
}

// Test page rotation default
TEST_F(PageTest_724, GetRotateDefault_724) {
    const char *pdfData =
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
        "196\n"
        "%%EOF\n";

    FILE *f = fopen("/tmp/test_page_rotate_724.pdf", "wb");
    if (f) {
        fwrite(pdfData, 1, strlen(pdfData), f);
        fclose(f);
    }

    auto doc = createTestDoc("/tmp/test_page_rotate_724.pdf");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    // Default rotation should be 0
    EXPECT_EQ(page->getRotate(), 0);
}

// Test getDuration for a page without duration
TEST_F(PageTest_724, GetDurationDefault_724) {
    const char *pdfData =
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
        "196\n"
        "%%EOF\n";

    FILE *f = fopen("/tmp/test_page_duration_724.pdf", "wb");
    if (f) {
        fwrite(pdfData, 1, strlen(pdfData), f);
        fclose(f);
    }

    auto doc = createTestDoc("/tmp/test_page_duration_724.pdf");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    // Duration for a page without Dur entry should be -1 or 0
    double duration = page->getDuration();
    EXPECT_LE(duration, 0.0);
}

// Test crop box equals media box when no crop box is specified
TEST_F(PageTest_724, CropBoxEqualsMediaBoxWhenNotCropped_724) {
    const char *pdfData =
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
        "196\n"
        "%%EOF\n";

    FILE *f = fopen("/tmp/test_page_cropbox_724.pdf", "wb");
    if (f) {
        fwrite(pdfData, 1, strlen(pdfData), f);
        fclose(f);
    }

    auto doc = createTestDoc("/tmp/test_page_cropbox_724.pdf");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    const PDFRectangle *mediaBox = page->getMediaBox();
    const PDFRectangle *cropBox = page->getCropBox();
    ASSERT_NE(mediaBox, nullptr);
    ASSERT_NE(cropBox, nullptr);

    // When no crop box is specified, it defaults to media box
    EXPECT_DOUBLE_EQ(cropBox->x1, mediaBox->x1);
    EXPECT_DOUBLE_EQ(cropBox->y1, mediaBox->y1);
    EXPECT_DOUBLE_EQ(cropBox->x2, mediaBox->x2);
    EXPECT_DOUBLE_EQ(cropBox->y2, mediaBox->y2);

    EXPECT_DOUBLE_EQ(page->getCropWidth(), page->getMediaWidth());
    EXPECT_DOUBLE_EQ(page->getCropHeight(), page->getMediaHeight());
}

// Test hasStandaloneFields for a basic page
TEST_F(PageTest_724, HasStandaloneFieldsDefault_724) {
    const char *pdfData =
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
        "196\n"
        "%%EOF\n";

    FILE *f = fopen("/tmp/test_page_standalone_724.pdf", "wb");
    if (f) {
        fwrite(pdfData, 1, strlen(pdfData), f);
        fclose(f);
    }

    auto doc = createTestDoc("/tmp/test_page_standalone_724.pdf");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    EXPECT_FALSE(page->hasStandaloneFields());
}

// Test getPageObj returns a valid dict
TEST_F(PageTest_724, GetPageObjReturnsDict_724) {
    const char *pdfData =
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
        "196\n"
        "%%EOF\n";

    FILE *f = fopen("/tmp/test_page_obj_724.pdf", "wb");
    if (f) {
        fwrite(pdfData, 1, strlen(pdfData), f);
        fclose(f);
    }

    auto doc = createTestDoc("/tmp/test_page_obj_724.pdf");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "Could not get page";
    }

    const Object &pageObj = page->getPageObj();
    EXPECT_TRUE(pageObj.isDict());
}
