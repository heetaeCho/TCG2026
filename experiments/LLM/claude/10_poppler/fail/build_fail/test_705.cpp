#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class PageTest_705 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadDoc(const char* filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test that isCropped returns a boolean value for a valid page
TEST_F(PageTest_705, IsCroppedReturnsBool_705) {
    // We need a valid PDF to test. We'll use a simple approach:
    // Create a minimal PDF in memory or load one.
    // Since we can't easily create a Page without a PDFDoc, we test through PDFDoc.
    
    // Create a minimal PDF document in memory
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n183\n%%EOF\n";

    size_t len = strlen(pdfContent);
    auto stream = new MemStream(const_cast<char*>(pdfContent), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page* page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        // Without a CropBox, isCropped should return false
        bool cropped = page->isCropped();
        EXPECT_FALSE(cropped);
    }
}

// Test isCropped returns true when CropBox is present and differs from MediaBox
TEST_F(PageTest_705, IsCroppedReturnsTrueWithCropBox_705) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/CropBox[10 10 600 780]>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n210\n%%EOF\n";

    size_t len = strlen(pdfContent);
    auto stream = new MemStream(const_cast<char*>(pdfContent), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page* page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        bool cropped = page->isCropped();
        EXPECT_TRUE(cropped);
    }
}

// Test that getMediaBox returns a valid rectangle
TEST_F(PageTest_705, GetMediaBoxReturnsValidRect_705) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n183\n%%EOF\n";

    size_t len = strlen(pdfContent);
    auto stream = new MemStream(const_cast<char*>(pdfContent), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page* page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        const PDFRectangle* mediaBox = page->getMediaBox();
        ASSERT_NE(mediaBox, nullptr);
        EXPECT_DOUBLE_EQ(mediaBox->x1, 0.0);
        EXPECT_DOUBLE_EQ(mediaBox->y1, 0.0);
        EXPECT_DOUBLE_EQ(mediaBox->x2, 612.0);
        EXPECT_DOUBLE_EQ(mediaBox->y2, 792.0);
    }
}

// Test getMediaWidth and getMediaHeight
TEST_F(PageTest_705, GetMediaWidthAndHeight_705) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n183\n%%EOF\n";

    size_t len = strlen(pdfContent);
    auto stream = new MemStream(const_cast<char*>(pdfContent), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page* page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_DOUBLE_EQ(page->getMediaWidth(), 612.0);
        EXPECT_DOUBLE_EQ(page->getMediaHeight(), 792.0);
    }
}

// Test getCropBox when no CropBox is defined (should default to MediaBox)
TEST_F(PageTest_705, GetCropBoxDefaultsToMediaBox_705) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n183\n%%EOF\n";

    size_t len = strlen(pdfContent);
    auto stream = new MemStream(const_cast<char*>(pdfContent), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page* page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        const PDFRectangle* cropBox = page->getCropBox();
        const PDFRectangle* mediaBox = page->getMediaBox();
        ASSERT_NE(cropBox, nullptr);
        ASSERT_NE(mediaBox, nullptr);
        EXPECT_DOUBLE_EQ(cropBox->x1, mediaBox->x1);
        EXPECT_DOUBLE_EQ(cropBox->y1, mediaBox->y1);
        EXPECT_DOUBLE_EQ(cropBox->x2, mediaBox->x2);
        EXPECT_DOUBLE_EQ(cropBox->y2, mediaBox->y2);
    }
}

// Test getCropWidth and getCropHeight with CropBox
TEST_F(PageTest_705, GetCropWidthAndHeightWithCropBox_705) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/CropBox[10 10 600 780]>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n210\n%%EOF\n";

    size_t len = strlen(pdfContent);
    auto stream = new MemStream(const_cast<char*>(pdfContent), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page* page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_DOUBLE_EQ(page->getCropWidth(), 590.0);
        EXPECT_DOUBLE_EQ(page->getCropHeight(), 770.0);
    }
}

// Test getRotate with default rotation (0)
TEST_F(PageTest_705, GetRotateDefault_705) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n183\n%%EOF\n";

    size_t len = strlen(pdfContent);
    auto stream = new MemStream(const_cast<char*>(pdfContent), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page* page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_EQ(page->getRotate(), 0);
    }
}

// Test getRotate with explicit rotation
TEST_F(PageTest_705, GetRotateWithRotation_705) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/Rotate 90>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n195\n%%EOF\n";

    size_t len = strlen(pdfContent);
    auto stream = new MemStream(const_cast<char*>(pdfContent), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page* page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_EQ(page->getRotate(), 90);
    }
}

// Test getNum returns the correct page number
TEST_F(PageTest_705, GetNumReturnsPageNumber_705) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n183\n%%EOF\n";

    size_t len = strlen(pdfContent);
    auto stream = new MemStream(const_cast<char*>(pdfContent), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page* page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_EQ(page->getNum(), 1);
    }
}

// Test isOk returns true for a valid page
TEST_F(PageTest_705, IsOkReturnsTrueForValidPage_705) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n183\n%%EOF\n";

    size_t len = strlen(pdfContent);
    auto stream = new MemStream(const_cast<char*>(pdfContent), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page* page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_TRUE(page->isOk());
    }
}

// Test getBleedBox, getTrimBox, getArtBox return non-null
TEST_F(PageTest_705, GetBleedTrimArtBoxNotNull_705) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n183\n%%EOF\n";

    size_t len = strlen(pdfContent);
    auto stream = new MemStream(const_cast<char*>(pdfContent), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page* page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_NE(page->getBleedBox(), nullptr);
        EXPECT_NE(page->getTrimBox(), nullptr);
        EXPECT_NE(page->getArtBox(), nullptr);
    }
}

// Test getDoc returns the parent document
TEST_F(PageTest_705, GetDocReturnsParentDoc_705) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n183\n%%EOF\n";

    size_t len = strlen(pdfContent);
    auto stream = new MemStream(const_cast<char*>(pdfContent), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page* page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_EQ(page->getDoc(), doc.get());
    }
}

// Test isCropped false when no CropBox
TEST_F(PageTest_705, IsCroppedFalseNoCropBox_705) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n183\n%%EOF\n";

    size_t len = strlen(pdfContent);
    auto stream = new MemStream(const_cast<char*>(pdfContent), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page* page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_FALSE(page->isCropped());
    }
}

// Test getDuration for a page without transition duration
TEST_F(PageTest_705, GetDurationDefault_705) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n183\n%%EOF\n";

    size_t len = strlen(pdfContent);
    auto stream = new MemStream(const_cast<char*>(pdfContent), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page* page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        // Default duration should be -1 when not specified
        double duration = page->getDuration();
        EXPECT_LE(duration, 0.0);
    }
}

// Test getPageObj returns a valid object
TEST_F(PageTest_705, GetPageObjReturnsValid_705) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n183\n%%EOF\n";

    size_t len = strlen(pdfContent);
    auto stream = new MemStream(const_cast<char*>(pdfContent), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page* page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        const Object& pageObj = page->getPageObj();
        EXPECT_TRUE(pageObj.isDict());
    }
}

// Test multiple pages
TEST_F(PageTest_705, MultiplePages_705) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R 4 0 R]/Count 2>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
        "4 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 300 400]/CropBox[10 10 290 390]>>endobj\n"
        "xref\n0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000119 00000 n \n"
        "0000000190 00000 n \n"
        "trailer<</Size 5/Root 1 0 R>>\n"
        "startxref\n290\n%%EOF\n";

    size_t len = strlen(pdfContent);
    auto stream = new MemStream(const_cast<char*>(pdfContent), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() >= 2) {
        Page* page1 = doc->getPage(1);
        Page* page2 = doc->getPage(2);
        ASSERT_NE(page1, nullptr);
        ASSERT_NE(page2, nullptr);

        EXPECT_EQ(page1->getNum(), 1);
        EXPECT_EQ(page2->getNum(), 2);

        EXPECT_FALSE(page1->isCropped());
        EXPECT_TRUE(page2->isCropped());

        EXPECT_DOUBLE_EQ(page1->getMediaWidth(), 612.0);
        EXPECT_DOUBLE_EQ(page2->getMediaWidth(), 300.0);
    }
}

// Test getResourceDict for a page without explicit resources
TEST_F(PageTest_705, GetResourceDictNoExplicitResources_705) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n183\n%%EOF\n";

    size_t len = strlen(pdfContent);
    auto stream = new MemStream(const_cast<char*>(pdfContent), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page* page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        // getResourceDict may return nullptr when no resources are defined
        // This is acceptable behavior
        Dict* resDict = page->getResourceDict();
        // Just verify it doesn't crash; result may be null or valid
        (void)resDict;
    }
}

// Test getStructParents default value
TEST_F(PageTest_705, GetStructParentsDefault_705) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n183\n%%EOF\n";

    size_t len = strlen(pdfContent);
    auto stream = new MemStream(const_cast<char*>(pdfContent), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page* page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        int sp = page->getStructParents();
        // When not specified, structParents is typically -1
        EXPECT_EQ(sp, -1);
    }
}

// Test hasStandaloneFields
TEST_F(PageTest_705, HasStandaloneFieldsDefault_705) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n183\n%%EOF\n";

    size_t len = strlen(pdfContent);
    auto stream = new MemStream(const_cast<char*>(pdfContent), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page* page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_FALSE(page->hasStandaloneFields());
    }
}

// Test getRef returns a valid Ref
TEST_F(PageTest_705, GetRefReturnsValidRef_705) {
    const char* pdfContent = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n183\n%%EOF\n";

    size_t len = strlen(pdfContent);
    auto stream = new MemStream(const_cast<char*>(pdfContent), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page* page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        Ref ref = page->getRef();
        // The page object is object 3 in our PDF
        EXPECT_EQ(ref.num, 3);
        EXPECT_EQ(ref.gen, 0);
    }
}
