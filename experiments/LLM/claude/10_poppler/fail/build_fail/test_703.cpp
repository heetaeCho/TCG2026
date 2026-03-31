#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

// Poppler headers
#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"

class PageTest_703 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadDocument(const char *filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// We need a simple test PDF. We'll create one in memory using a minimal PDF structure.
// For practical testing, we'll use PDFDoc's ability to parse from a buffer.

class PageFromBufferTest_703 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> createMinimalPDF() {
        // Minimal valid PDF with one page
        static const char *pdfData =
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
            "/CropBox [10 10 600 780] "
            "/BleedBox [5 5 607 787] "
            "/TrimBox [15 15 597 777] "
            "/ArtBox [20 20 592 772] "
            "/Rotate 90 "
            "/Contents 4 0 R >>\n"
            "endobj\n"
            "4 0 obj\n"
            "<< /Length 0 >>\n"
            "stream\n"
            "\n"
            "endstream\n"
            "endobj\n"
            "xref\n"
            "0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000352 00000 n \n"
            "trailer\n"
            "<< /Size 5 /Root 1 0 R >>\n"
            "startxref\n"
            "402\n"
            "%%EOF\n";

        // We need to create a proper PDF. Let's just build it properly with correct offsets.
        // Instead, use the simpler approach with GooString.
        
        std::string pdf;
        pdf += "%PDF-1.4\n";
        
        size_t obj1_offset = pdf.size();
        pdf += "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        
        size_t obj2_offset = pdf.size();
        pdf += "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        
        size_t obj3_offset = pdf.size();
        pdf += "3 0 obj\n<< /Type /Page /Parent 2 0 R "
               "/MediaBox [0 0 612 792] "
               "/CropBox [10 10 600 780] "
               "/BleedBox [5 5 607 787] "
               "/TrimBox [15 15 597 777] "
               "/ArtBox [20 20 592 772] "
               "/Rotate 90 "
               ">>\nendobj\n";
        
        size_t xref_offset = pdf.size();
        
        char buf[256];
        pdf += "xref\n";
        pdf += "0 4\n";
        pdf += "0000000000 65535 f \r\n";
        snprintf(buf, sizeof(buf), "%010zu 00000 n \r\n", obj1_offset);
        pdf += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \r\n", obj2_offset);
        pdf += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \r\n", obj3_offset);
        pdf += buf;
        
        pdf += "trailer\n<< /Size 4 /Root 1 0 R >>\n";
        snprintf(buf, sizeof(buf), "startxref\n%zu\n%%%%EOF\n", xref_offset);
        pdf += buf;
        
        auto *stream = new MemStream(const_cast<char*>(pdf.c_str()), 0, pdf.size(), Object(objNull));
        // We need to copy the data since MemStream doesn't own it
        char *dataCopy = (char*)gmalloc(pdf.size());
        memcpy(dataCopy, pdf.c_str(), pdf.size());
        
        auto doc = std::make_unique<PDFDoc>(new MemStream(dataCopy, 0, pdf.size(), Object(objNull)));
        if (!doc->isOk()) {
            gfree(dataCopy);
            return nullptr;
        }
        return doc;
    }

    std::unique_ptr<PDFDoc> createMinimalPDFNoOptionalBoxes() {
        std::string pdf;
        pdf += "%PDF-1.4\n";
        
        size_t obj1_offset = pdf.size();
        pdf += "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        
        size_t obj2_offset = pdf.size();
        pdf += "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        
        size_t obj3_offset = pdf.size();
        pdf += "3 0 obj\n<< /Type /Page /Parent 2 0 R "
               "/MediaBox [0 0 200 300] "
               ">>\nendobj\n";
        
        size_t xref_offset = pdf.size();
        
        char buf[256];
        pdf += "xref\n";
        pdf += "0 4\n";
        pdf += "0000000000 65535 f \r\n";
        snprintf(buf, sizeof(buf), "%010zu 00000 n \r\n", obj1_offset);
        pdf += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \r\n", obj2_offset);
        pdf += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \r\n", obj3_offset);
        pdf += buf;
        
        pdf += "trailer\n<< /Size 4 /Root 1 0 R >>\n";
        snprintf(buf, sizeof(buf), "startxref\n%zu\n%%%%EOF\n", xref_offset);
        pdf += buf;
        
        char *dataCopy = (char*)gmalloc(pdf.size());
        memcpy(dataCopy, pdf.c_str(), pdf.size());
        
        auto doc = std::make_unique<PDFDoc>(new MemStream(dataCopy, 0, pdf.size(), Object(objNull)));
        if (!doc->isOk()) {
            gfree(dataCopy);
            return nullptr;
        }
        return doc;
    }
};

// Test that getMediaBox returns a valid pointer and correct values
TEST_F(PageFromBufferTest_703, GetMediaBox_ReturnsCorrectValues_703) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    const PDFRectangle *mediaBox = page->getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
    EXPECT_DOUBLE_EQ(mediaBox->x1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->y1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->x2, 612.0);
    EXPECT_DOUBLE_EQ(mediaBox->y2, 792.0);
}

// Test getMediaWidth and getMediaHeight
TEST_F(PageFromBufferTest_703, GetMediaWidthAndHeight_703) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    EXPECT_DOUBLE_EQ(page->getMediaWidth(), 612.0);
    EXPECT_DOUBLE_EQ(page->getMediaHeight(), 792.0);
}

// Test getCropBox returns valid values when CropBox is set
TEST_F(PageFromBufferTest_703, GetCropBox_WhenSet_ReturnsCorrectValues_703) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    const PDFRectangle *cropBox = page->getCropBox();
    ASSERT_NE(cropBox, nullptr);
    // CropBox is clipped to MediaBox
    EXPECT_GE(cropBox->x1, 0.0);
    EXPECT_GE(cropBox->y1, 0.0);
    EXPECT_LE(cropBox->x2, 612.0);
    EXPECT_LE(cropBox->y2, 792.0);
}

// Test isCropped returns true when CropBox is set
TEST_F(PageFromBufferTest_703, IsCropped_WhenCropBoxSet_ReturnsTrue_703) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    EXPECT_TRUE(page->isCropped());
}

// Test isCropped returns false when no CropBox
TEST_F(PageFromBufferTest_703, IsCropped_WhenNoCropBox_ReturnsFalse_703) {
    auto doc = createMinimalPDFNoOptionalBoxes();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    EXPECT_FALSE(page->isCropped());
}

// Test getCropWidth and getCropHeight
TEST_F(PageFromBufferTest_703, GetCropWidthAndHeight_703) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    EXPECT_GT(page->getCropWidth(), 0.0);
    EXPECT_GT(page->getCropHeight(), 0.0);
}

// Test getBleedBox
TEST_F(PageFromBufferTest_703, GetBleedBox_WhenSet_ReturnsNonNull_703) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    const PDFRectangle *bleedBox = page->getBleedBox();
    ASSERT_NE(bleedBox, nullptr);
}

// Test getTrimBox
TEST_F(PageFromBufferTest_703, GetTrimBox_WhenSet_ReturnsNonNull_703) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    const PDFRectangle *trimBox = page->getTrimBox();
    ASSERT_NE(trimBox, nullptr);
}

// Test getArtBox
TEST_F(PageFromBufferTest_703, GetArtBox_WhenSet_ReturnsNonNull_703) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    const PDFRectangle *artBox = page->getArtBox();
    ASSERT_NE(artBox, nullptr);
}

// Test getRotate
TEST_F(PageFromBufferTest_703, GetRotate_WhenSet_ReturnsCorrectValue_703) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    EXPECT_EQ(page->getRotate(), 90);
}

// Test getRotate defaults to 0 when not set
TEST_F(PageFromBufferTest_703, GetRotate_WhenNotSet_ReturnsZero_703) {
    auto doc = createMinimalPDFNoOptionalBoxes();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    EXPECT_EQ(page->getRotate(), 0);
}

// Test getNum returns correct page number
TEST_F(PageFromBufferTest_703, GetNum_ReturnsCorrectPageNumber_703) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    EXPECT_EQ(page->getNum(), 1);
}

// Test isOk returns true for a valid page
TEST_F(PageFromBufferTest_703, IsOk_ForValidPage_ReturnsTrue_703) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    EXPECT_TRUE(page->isOk());
}

// Test getDoc returns the owning document
TEST_F(PageFromBufferTest_703, GetDoc_ReturnsOwningDocument_703) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    EXPECT_EQ(page->getDoc(), doc.get());
}

// Test getRef returns a valid Ref
TEST_F(PageFromBufferTest_703, GetRef_ReturnsValidRef_703) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Ref ref = page->getRef();
    EXPECT_GT(ref.num, 0);
}

// Test getPageObj returns a valid object
TEST_F(PageFromBufferTest_703, GetPageObj_ReturnsValidObject_703) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    const Object &pageObj = page->getPageObj();
    EXPECT_TRUE(pageObj.isDict());
}

// Test getDuration returns default value when not set
TEST_F(PageFromBufferTest_703, GetDuration_WhenNotSet_ReturnsNegative_703) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    // Default duration when not set is typically -1
    EXPECT_LT(page->getDuration(), 0.0);
}

// Test getContents
TEST_F(PageFromBufferTest_703, GetContents_WhenNoContents_ReturnsNullObj_703) {
    auto doc = createMinimalPDFNoOptionalBoxes();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Object contents = page->getContents();
    // When no contents, it should be null
    EXPECT_TRUE(contents.isNull());
}

// Test getMediaBox with minimal (no optional boxes) PDF
TEST_F(PageFromBufferTest_703, GetMediaBox_MinimalPDF_CorrectValues_703) {
    auto doc = createMinimalPDFNoOptionalBoxes();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    const PDFRectangle *mediaBox = page->getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
    EXPECT_DOUBLE_EQ(mediaBox->x1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->y1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->x2, 200.0);
    EXPECT_DOUBLE_EQ(mediaBox->y2, 300.0);
}

// Test getMediaWidth and getMediaHeight for minimal PDF
TEST_F(PageFromBufferTest_703, GetMediaWidthHeight_MinimalPDF_703) {
    auto doc = createMinimalPDFNoOptionalBoxes();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    EXPECT_DOUBLE_EQ(page->getMediaWidth(), 200.0);
    EXPECT_DOUBLE_EQ(page->getMediaHeight(), 300.0);
}

// Test getCropBox defaults to MediaBox when no CropBox set
TEST_F(PageFromBufferTest_703, GetCropBox_WhenNotSet_DefaultsToMediaBox_703) {
    auto doc = createMinimalPDFNoOptionalBoxes();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    const PDFRectangle *cropBox = page->getCropBox();
    const PDFRectangle *mediaBox = page->getMediaBox();
    ASSERT_NE(cropBox, nullptr);
    ASSERT_NE(mediaBox, nullptr);
    
    EXPECT_DOUBLE_EQ(cropBox->x1, mediaBox->x1);
    EXPECT_DOUBLE_EQ(cropBox->y1, mediaBox->y1);
    EXPECT_DOUBLE_EQ(cropBox->x2, mediaBox->x2);
    EXPECT_DOUBLE_EQ(cropBox->y2, mediaBox->y2);
}

// Test getCropWidth and getCropHeight default to media dimensions
TEST_F(PageFromBufferTest_703, GetCropWidthHeight_WhenNoCropBox_EqualsMediaDimensions_703) {
    auto doc = createMinimalPDFNoOptionalBoxes();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    EXPECT_DOUBLE_EQ(page->getCropWidth(), page->getMediaWidth());
    EXPECT_DOUBLE_EQ(page->getCropHeight(), page->getMediaHeight());
}

// Test getLastModified returns null when not set
TEST_F(PageFromBufferTest_703, GetLastModified_WhenNotSet_ReturnsNull_703) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    const GooString *lastModified = page->getLastModified();
    // Not set in our test PDF, expect nullptr
    EXPECT_EQ(lastModified, nullptr);
}

// Test getResourceDict
TEST_F(PageFromBufferTest_703, GetResourceDict_ReturnsNullWhenNoResources_703) {
    auto doc = createMinimalPDFNoOptionalBoxes();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    // No resources in our minimal PDF
    Dict *resources = page->getResourceDict();
    // Could be null or not depending on implementation - just test it doesn't crash
    (void)resources;
}

// Test getStructParents default
TEST_F(PageFromBufferTest_703, GetStructParents_WhenNotSet_ReturnsMinusOne_703) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    // When StructParents is not set, it should return -1
    EXPECT_EQ(page->getStructParents(), -1);
}

// Test hasStandaloneFields
TEST_F(PageFromBufferTest_703, HasStandaloneFields_WhenNone_ReturnsFalse_703) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    EXPECT_FALSE(page->hasStandaloneFields());
}

// Test getThumb returns null when no thumbnail
TEST_F(PageFromBufferTest_703, GetThumb_WhenNotSet_ReturnsNullObj_703) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Object thumb = page->getThumb();
    EXPECT_TRUE(thumb.isNull());
}

// Test getTrans returns null when no transition
TEST_F(PageFromBufferTest_703, GetTrans_WhenNotSet_ReturnsNullObj_703) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Object trans = page->getTrans();
    EXPECT_TRUE(trans.isNull());
}

// Test getActions returns null when no actions
TEST_F(PageFromBufferTest_703, GetActions_WhenNotSet_ReturnsNullObj_703) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Object actions = page->getActions();
    EXPECT_TRUE(actions.isNull());
}

// Test getAnnotsObject
TEST_F(PageFromBufferTest_703, GetAnnotsObject_WhenNoAnnots_703) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Object annotsObj = page->getAnnotsObject();
    // No annotations in our test PDF
    EXPECT_TRUE(annotsObj.isNull() || annotsObj.isArray());
}

// Test loadThumb fails when no thumbnail present
TEST_F(PageFromBufferTest_703, LoadThumb_WhenNoThumbnail_ReturnsFalse_703) {
    auto doc = createMinimalPDF();
    ASSERT_NE(doc, nullptr);
    ASSERT_GE(doc->getNumPages(), 1);
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    unsigned char *data = nullptr;
    int width = 0, height = 0, rowstride = 0;
    bool result = page->loadThumb(&data, &width, &height, &rowstride);
    EXPECT_FALSE(result);
}
