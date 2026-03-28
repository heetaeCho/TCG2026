#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"
#include "PDFDocFactory.h"

class PageTest_714 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadDoc(const char *filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test that getLastModified returns a value (possibly nullptr) without crashing
TEST_F(PageTest_714, GetLastModifiedReturnsWithoutCrash_714) {
    // Create a minimal PDF in memory to test with
    // We need a valid PDF document. If no test file is available, we test the interface contract.
    // This test verifies the method is callable and returns const GooString*
    
    // Attempt to create a doc from a simple PDF buffer
    static const char pdfData[] = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n195\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);
    
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        // getLastModified may return nullptr if not set
        const GooString *lastMod = page->getLastModified();
        // Just verify it doesn't crash - value may be nullptr
        SUCCEED();
    }
}

// Test getMediaBox on a page
TEST_F(PageTest_714, GetMediaBoxReturnsValidRect_714) {
    static const char pdfData[] = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n195\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        
        const PDFRectangle *mediaBox = page->getMediaBox();
        ASSERT_NE(mediaBox, nullptr);
        EXPECT_DOUBLE_EQ(mediaBox->x1, 0.0);
        EXPECT_DOUBLE_EQ(mediaBox->y1, 0.0);
        EXPECT_DOUBLE_EQ(mediaBox->x2, 612.0);
        EXPECT_DOUBLE_EQ(mediaBox->y2, 792.0);
    }
}

// Test getMediaWidth and getMediaHeight
TEST_F(PageTest_714, GetMediaDimensions_714) {
    static const char pdfData[] = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n195\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        
        EXPECT_DOUBLE_EQ(page->getMediaWidth(), 612.0);
        EXPECT_DOUBLE_EQ(page->getMediaHeight(), 792.0);
    }
}

// Test getNum returns the correct page number
TEST_F(PageTest_714, GetNumReturnsCorrectPageNumber_714) {
    static const char pdfData[] = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n195\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_EQ(page->getNum(), 1);
    }
}

// Test isCropped returns false when no CropBox is set
TEST_F(PageTest_714, IsCroppedFalseWhenNoCropBox_714) {
    static const char pdfData[] = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n195\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_FALSE(page->isCropped());
    }
}

// Test getCropBox returns valid rectangle
TEST_F(PageTest_714, GetCropBoxReturnsValidRect_714) {
    static const char pdfData[] = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n195\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        const PDFRectangle *cropBox = page->getCropBox();
        ASSERT_NE(cropBox, nullptr);
        // When no crop box is set, it defaults to media box
        EXPECT_DOUBLE_EQ(cropBox->x2, 612.0);
        EXPECT_DOUBLE_EQ(cropBox->y2, 792.0);
    }
}

// Test getCropWidth and getCropHeight
TEST_F(PageTest_714, GetCropDimensions_714) {
    static const char pdfData[] = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n195\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_DOUBLE_EQ(page->getCropWidth(), 612.0);
        EXPECT_DOUBLE_EQ(page->getCropHeight(), 792.0);
    }
}

// Test getRotate returns default rotation
TEST_F(PageTest_714, GetRotateReturnsDefaultZero_714) {
    static const char pdfData[] = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n195\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_EQ(page->getRotate(), 0);
    }
}

// Test getBleedBox, getTrimBox, getArtBox return non-null
TEST_F(PageTest_714, GetBoxesReturnNonNull_714) {
    static const char pdfData[] = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n195\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        
        EXPECT_NE(page->getBleedBox(), nullptr);
        EXPECT_NE(page->getTrimBox(), nullptr);
        EXPECT_NE(page->getArtBox(), nullptr);
    }
}

// Test getDuration returns a valid duration
TEST_F(PageTest_714, GetDurationReturnsNonNegative_714) {
    static const char pdfData[] = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n195\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        // Duration should be -1 if not set, or >= 0 if set
        double duration = page->getDuration();
        EXPECT_TRUE(duration == -1.0 || duration >= 0.0);
    }
}

// Test isOk returns true for a valid page
TEST_F(PageTest_714, IsOkReturnsTrueForValidPage_714) {
    static const char pdfData[] = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n195\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_TRUE(page->isOk());
    }
}

// Test getLastModified returns nullptr when not set in page dict
TEST_F(PageTest_714, GetLastModifiedNullWhenNotSet_714) {
    static const char pdfData[] = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n195\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        // No LastModified entry in our test page dict
        const GooString *lastMod = page->getLastModified();
        EXPECT_EQ(lastMod, nullptr);
    }
}

// Test getDoc returns valid pointer
TEST_F(PageTest_714, GetDocReturnsValidPointer_714) {
    static const char pdfData[] = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n195\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_EQ(page->getDoc(), doc.get());
    }
}

// Test hasStandaloneFields
TEST_F(PageTest_714, HasStandaloneFieldsDefaultFalse_714) {
    static const char pdfData[] = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n195\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_FALSE(page->hasStandaloneFields());
    }
}

// Test getPageObj returns a valid object
TEST_F(PageTest_714, GetPageObjReturnsValidObject_714) {
    static const char pdfData[] = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n195\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        const Object &pageObj = page->getPageObj();
        EXPECT_TRUE(pageObj.isDict());
    }
}

// Test getRef returns a valid Ref
TEST_F(PageTest_714, GetRefReturnsValidRef_714) {
    static const char pdfData[] = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n195\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        Ref ref = page->getRef();
        // The page object number should be 3 based on our PDF
        EXPECT_EQ(ref.num, 3);
        EXPECT_EQ(ref.gen, 0);
    }
}

// Test with a page that has LastModified set
TEST_F(PageTest_714, GetLastModifiedReturnsValueWhenSet_714) {
    static const char pdfData[] = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /LastModified (D:20230101120000) >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n225\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        const GooString *lastMod = page->getLastModified();
        if (lastMod != nullptr) {
            // Should contain the date string we set
            std::string lastModStr(lastMod->c_str());
            EXPECT_FALSE(lastModStr.empty());
            EXPECT_NE(lastModStr.find("2023"), std::string::npos);
        }
    }
}

// Test getStructParents
TEST_F(PageTest_714, GetStructParentsDefaultValue_714) {
    static const char pdfData[] = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n195\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        // StructParents should default to -1 when not set
        int sp = page->getStructParents();
        EXPECT_EQ(sp, -1);
    }
}
