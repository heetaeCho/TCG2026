#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Stream.h"

class PageTest_717 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadTestDoc(const char* filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test that getMetadata returns a value (nullptr or valid Stream*) without crashing
// This tests the delegation from Page::getMetadata() to PageAttrs::getMetadata()
TEST_F(PageTest_717, GetMetadataReturnsWithoutCrash_717) {
    // We need a valid PDF document to test Page
    // Create a simple PDF in memory
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
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n196\n%%EOF\n";

    auto stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        // getMetadata may return nullptr if no metadata stream is present
        Stream *metadata = page->getMetadata();
        // For a simple PDF without metadata, we expect nullptr
        EXPECT_EQ(metadata, nullptr);
    }
}

// Test basic page properties on a minimal PDF
TEST_F(PageTest_717, BasicPageProperties_717) {
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
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n196\n%%EOF\n";

    auto stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_TRUE(page->isOk());
        EXPECT_EQ(page->getNum(), 1);

        const PDFRectangle *mediaBox = page->getMediaBox();
        ASSERT_NE(mediaBox, nullptr);
        EXPECT_DOUBLE_EQ(mediaBox->x1, 0.0);
        EXPECT_DOUBLE_EQ(mediaBox->y1, 0.0);
        EXPECT_DOUBLE_EQ(mediaBox->x2, 612.0);
        EXPECT_DOUBLE_EQ(mediaBox->y2, 792.0);

        EXPECT_DOUBLE_EQ(page->getMediaWidth(), 612.0);
        EXPECT_DOUBLE_EQ(page->getMediaHeight(), 792.0);
    }
}

// Test that getCropBox falls back to mediaBox when no crop box is specified
TEST_F(PageTest_717, CropBoxFallsBackToMediaBox_717) {
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
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n196\n%%EOF\n";

    auto stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);

        const PDFRectangle *cropBox = page->getCropBox();
        ASSERT_NE(cropBox, nullptr);
        // Without explicit crop box, crop dimensions should match media dimensions
        EXPECT_DOUBLE_EQ(page->getCropWidth(), page->getMediaWidth());
        EXPECT_DOUBLE_EQ(page->getCropHeight(), page->getMediaHeight());

        // isCropped should be false when no explicit crop box
        EXPECT_FALSE(page->isCropped());
    }
}

// Test that getRotate returns default 0 when no rotation is specified
TEST_F(PageTest_717, DefaultRotateIsZero_717) {
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
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n196\n%%EOF\n";

    auto stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_EQ(page->getRotate(), 0);
    }
}

// Test bleed, trim, art boxes default to media/crop box when not specified
TEST_F(PageTest_717, DefaultBleedTrimArtBoxes_717) {
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
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n196\n%%EOF\n";

    auto stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);

        const PDFRectangle *bleedBox = page->getBleedBox();
        ASSERT_NE(bleedBox, nullptr);

        const PDFRectangle *trimBox = page->getTrimBox();
        ASSERT_NE(trimBox, nullptr);

        const PDFRectangle *artBox = page->getArtBox();
        ASSERT_NE(artBox, nullptr);

        const PDFRectangle *cropBox = page->getCropBox();
        ASSERT_NE(cropBox, nullptr);

        // Default bleed/trim/art should equal crop box
        EXPECT_DOUBLE_EQ(bleedBox->x1, cropBox->x1);
        EXPECT_DOUBLE_EQ(bleedBox->y1, cropBox->y1);
        EXPECT_DOUBLE_EQ(bleedBox->x2, cropBox->x2);
        EXPECT_DOUBLE_EQ(bleedBox->y2, cropBox->y2);

        EXPECT_DOUBLE_EQ(trimBox->x1, cropBox->x1);
        EXPECT_DOUBLE_EQ(trimBox->y1, cropBox->y1);
        EXPECT_DOUBLE_EQ(trimBox->x2, cropBox->x2);
        EXPECT_DOUBLE_EQ(trimBox->y2, cropBox->y2);

        EXPECT_DOUBLE_EQ(artBox->x1, cropBox->x1);
        EXPECT_DOUBLE_EQ(artBox->y1, cropBox->y1);
        EXPECT_DOUBLE_EQ(artBox->x2, cropBox->x2);
        EXPECT_DOUBLE_EQ(artBox->y2, cropBox->y2);
    }
}

// Test getLastModified returns nullptr when not set
TEST_F(PageTest_717, GetLastModifiedNullWhenNotSet_717) {
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
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n196\n%%EOF\n";

    auto stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        const GooString *lastMod = page->getLastModified();
        EXPECT_EQ(lastMod, nullptr);
    }
}

// Test optional dict accessors return nullptr when not present
TEST_F(PageTest_717, OptionalDictAccessorsReturnNull_717) {
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
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n196\n%%EOF\n";

    auto stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);

        // These should return nullptr when not present in the page dict
        EXPECT_EQ(page->getBoxColorInfo(), nullptr);
        EXPECT_EQ(page->getGroup(), nullptr);
        EXPECT_EQ(page->getMetadata(), nullptr);
        EXPECT_EQ(page->getPieceInfo(), nullptr);
        EXPECT_EQ(page->getSeparationInfo(), nullptr);
    }
}

// Test getDoc returns the parent document
TEST_F(PageTest_717, GetDocReturnsParentDocument_717) {
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
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n196\n%%EOF\n";

    auto stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_EQ(page->getDoc(), doc.get());
    }
}

// Test getRef returns a valid Ref
TEST_F(PageTest_717, GetRefReturnsValidRef_717) {
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
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n196\n%%EOF\n";

    auto stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        Ref ref = page->getRef();
        // The page object number should be 3 (from our PDF)
        EXPECT_EQ(ref.num, 3);
        EXPECT_EQ(ref.gen, 0);
    }
}

// Test getDuration returns default value
TEST_F(PageTest_717, GetDurationDefault_717) {
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
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n196\n%%EOF\n";

    auto stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        // Duration should be -1 or similar default when not set
        double duration = page->getDuration();
        EXPECT_LE(duration, 0.0);
    }
}

// Test hasStandaloneFields for a simple page
TEST_F(PageTest_717, HasStandaloneFieldsFalseByDefault_717) {
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
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n196\n%%EOF\n";

    auto stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        EXPECT_FALSE(page->hasStandaloneFields());
    }
}

// Test getPageObj returns a valid object
TEST_F(PageTest_717, GetPageObjReturnsValidObject_717) {
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
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n196\n%%EOF\n";

    auto stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        const Object &pageObj = page->getPageObj();
        EXPECT_TRUE(pageObj.isDict());
    }
}

// Test getResourceDict and getResourceDictObject
TEST_F(PageTest_717, ResourceDictAccessors_717) {
    static const char pdfData[] =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /Resources << >> >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n196\n%%EOF\n";

    auto stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);

        // getResourceDict should return a valid Dict* when resources are present
        Dict *resDict = page->getResourceDict();
        // Could be nullptr or valid depending on page setup
        // getResourceDictObject should also be accessible
        Object *resDictObj = page->getResourceDictObject();
        ASSERT_NE(resDictObj, nullptr);
    }
}

// Test getContents returns an Object
TEST_F(PageTest_717, GetContentsReturnsObject_717) {
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
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n196\n%%EOF\n";

    auto stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        Object contents = page->getContents();
        // A page without contents should return a null object
        EXPECT_TRUE(contents.isNull());
    }
}

// Test getStructParents default
TEST_F(PageTest_717, GetStructParentsDefault_717) {
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
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n196\n%%EOF\n";

    auto stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        int structParents = page->getStructParents();
        // Should be -1 when not set
        EXPECT_EQ(structParents, -1);
    }
}

// Test getThumb returns null object when no thumbnail
TEST_F(PageTest_717, GetThumbReturnsNullWhenAbsent_717) {
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
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n196\n%%EOF\n";

    auto stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        Object thumb = page->getThumb();
        EXPECT_TRUE(thumb.isNull());
    }
}

// Test getTrans returns null object when no transition
TEST_F(PageTest_717, GetTransReturnsNullWhenAbsent_717) {
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
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n196\n%%EOF\n";

    auto stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        Object trans = page->getTrans();
        EXPECT_TRUE(trans.isNull());
    }
}

// Test getActions returns null object when no actions
TEST_F(PageTest_717, GetActionsReturnsNullWhenAbsent_717) {
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
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n196\n%%EOF\n";

    auto stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        Object actions = page->getActions();
        EXPECT_TRUE(actions.isNull());
    }
}

// Test getAnnotsObject
TEST_F(PageTest_717, GetAnnotsObjectWhenNoAnnots_717) {
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
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n196\n%%EOF\n";

    auto stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);
        Object annotsObj = page->getAnnotsObject();
        // Should be null when no annotations are present
        EXPECT_TRUE(annotsObj.isNull());
    }
}

// Test loadThumb returns false when no thumbnail
TEST_F(PageTest_717, LoadThumbReturnsFalseWhenNoThumb_717) {
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
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n196\n%%EOF\n";

    auto stream = new MemStream(const_cast<char*>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);

        unsigned char *data = nullptr;
        int width = 0, height = 0, rowstride = 0;
        bool result = page->loadThumb(&data, &width, &height, &rowstride);
        EXPECT_FALSE(result);
        EXPECT_EQ(data, nullptr);
    }
}
