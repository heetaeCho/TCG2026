#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "PDFDocFactory.h"

class PageTest_713 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadTestDoc(const char *filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test that getRotate returns a valid rotation value (0, 90, 180, or 270)
TEST_F(PageTest_713, GetRotateReturnsValidValue_713) {
    // We need a real PDF to test. We'll create a minimal in-memory PDF.
    // Since we can't easily create a Page without a PDFDoc, we test through PDFDoc.
    // For unit testing without a file, we create a minimal PDF in memory.
    
    const char *pdfData = 
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
        "startxref\n186\n%%EOF\n";

    // Use a temporary file approach or MemStream
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    // Load from file descriptor - use GooString based constructor
    // We'll write to a temp file instead
    char tmpPath[] = "/tmp/poppler_test_XXXXXX";
    int fd = mkstemp(tmpPath);
    ASSERT_GE(fd, 0);
    write(fd, pdfData, strlen(pdfData));
    close(fd);
    fclose(tmpFile);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));
    
    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        if (page) {
            int rotate = page->getRotate();
            // Rotation should be one of 0, 90, 180, 270
            EXPECT_TRUE(rotate == 0 || rotate == 90 || rotate == 180 || rotate == 270)
                << "Rotation was: " << rotate;
        }
    }

    unlink(tmpPath);
}

// Test getRotate with explicit rotation in page dictionary
TEST_F(PageTest_713, GetRotateWithExplicitRotation_713) {
    const char *pdfData =
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
        "startxref\n196\n%%EOF\n";

    char tmpPath[] = "/tmp/poppler_test_rot_XXXXXX";
    int fd = mkstemp(tmpPath);
    ASSERT_GE(fd, 0);
    write(fd, pdfData, strlen(pdfData));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        if (page) {
            EXPECT_EQ(page->getRotate(), 90);
        }
    }

    unlink(tmpPath);
}

// Test getMediaBox returns non-null and valid dimensions
TEST_F(PageTest_713, GetMediaBoxReturnsValidBox_713) {
    const char *pdfData =
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
        "startxref\n186\n%%EOF\n";

    char tmpPath[] = "/tmp/poppler_test_mb_XXXXXX";
    int fd = mkstemp(tmpPath);
    ASSERT_GE(fd, 0);
    write(fd, pdfData, strlen(pdfData));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        if (page) {
            const PDFRectangle *mediaBox = page->getMediaBox();
            ASSERT_NE(mediaBox, nullptr);
            EXPECT_DOUBLE_EQ(mediaBox->x1, 0.0);
            EXPECT_DOUBLE_EQ(mediaBox->y1, 0.0);
            EXPECT_DOUBLE_EQ(mediaBox->x2, 612.0);
            EXPECT_DOUBLE_EQ(mediaBox->y2, 792.0);
        }
    }

    unlink(tmpPath);
}

// Test getMediaWidth and getMediaHeight
TEST_F(PageTest_713, GetMediaWidthAndHeight_713) {
    const char *pdfData =
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
        "startxref\n186\n%%EOF\n";

    char tmpPath[] = "/tmp/poppler_test_wh_XXXXXX";
    int fd = mkstemp(tmpPath);
    ASSERT_GE(fd, 0);
    write(fd, pdfData, strlen(pdfData));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        if (page) {
            EXPECT_DOUBLE_EQ(page->getMediaWidth(), 612.0);
            EXPECT_DOUBLE_EQ(page->getMediaHeight(), 792.0);
        }
    }

    unlink(tmpPath);
}

// Test getNum returns the correct page number
TEST_F(PageTest_713, GetNumReturnsPageNumber_713) {
    const char *pdfData =
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
        "startxref\n186\n%%EOF\n";

    char tmpPath[] = "/tmp/poppler_test_num_XXXXXX";
    int fd = mkstemp(tmpPath);
    ASSERT_GE(fd, 0);
    write(fd, pdfData, strlen(pdfData));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        if (page) {
            EXPECT_EQ(page->getNum(), 1);
        }
    }

    unlink(tmpPath);
}

// Test isCropped returns false when no CropBox is specified
TEST_F(PageTest_713, IsCroppedReturnsFalseWhenNoCropBox_713) {
    const char *pdfData =
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
        "startxref\n186\n%%EOF\n";

    char tmpPath[] = "/tmp/poppler_test_crop_XXXXXX";
    int fd = mkstemp(tmpPath);
    ASSERT_GE(fd, 0);
    write(fd, pdfData, strlen(pdfData));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        if (page) {
            EXPECT_FALSE(page->isCropped());
        }
    }

    unlink(tmpPath);
}

// Test isCropped returns true when CropBox is specified
TEST_F(PageTest_713, IsCroppedReturnsTrueWhenCropBoxPresent_713) {
    const char *pdfData =
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
        "startxref\n216\n%%EOF\n";

    char tmpPath[] = "/tmp/poppler_test_cropped_XXXXXX";
    int fd = mkstemp(tmpPath);
    ASSERT_GE(fd, 0);
    write(fd, pdfData, strlen(pdfData));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        if (page) {
            EXPECT_TRUE(page->isCropped());
        }
    }

    unlink(tmpPath);
}

// Test getRotate with no rotation specified defaults to 0
TEST_F(PageTest_713, GetRotateDefaultsToZero_713) {
    const char *pdfData =
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
        "startxref\n186\n%%EOF\n";

    char tmpPath[] = "/tmp/poppler_test_defrot_XXXXXX";
    int fd = mkstemp(tmpPath);
    ASSERT_GE(fd, 0);
    write(fd, pdfData, strlen(pdfData));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        if (page) {
            EXPECT_EQ(page->getRotate(), 0);
        }
    }

    unlink(tmpPath);
}

// Test getRotate with 180 degree rotation
TEST_F(PageTest_713, GetRotate180_713) {
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/Rotate 180>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n197\n%%EOF\n";

    char tmpPath[] = "/tmp/poppler_test_rot180_XXXXXX";
    int fd = mkstemp(tmpPath);
    ASSERT_GE(fd, 0);
    write(fd, pdfData, strlen(pdfData));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        if (page) {
            EXPECT_EQ(page->getRotate(), 180);
        }
    }

    unlink(tmpPath);
}

// Test getRotate with 270 degree rotation
TEST_F(PageTest_713, GetRotate270_713) {
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/Rotate 270>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n197\n%%EOF\n";

    char tmpPath[] = "/tmp/poppler_test_rot270_XXXXXX";
    int fd = mkstemp(tmpPath);
    ASSERT_GE(fd, 0);
    write(fd, pdfData, strlen(pdfData));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        if (page) {
            EXPECT_EQ(page->getRotate(), 270);
        }
    }

    unlink(tmpPath);
}

// Test getCropBox returns valid box when CropBox is set
TEST_F(PageTest_713, GetCropBoxWithExplicitCropBox_713) {
    const char *pdfData =
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
        "startxref\n216\n%%EOF\n";

    char tmpPath[] = "/tmp/poppler_test_cb_XXXXXX";
    int fd = mkstemp(tmpPath);
    ASSERT_GE(fd, 0);
    write(fd, pdfData, strlen(pdfData));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        if (page) {
            const PDFRectangle *cropBox = page->getCropBox();
            ASSERT_NE(cropBox, nullptr);
            EXPECT_DOUBLE_EQ(cropBox->x1, 10.0);
            EXPECT_DOUBLE_EQ(cropBox->y1, 10.0);
            EXPECT_DOUBLE_EQ(cropBox->x2, 600.0);
            EXPECT_DOUBLE_EQ(cropBox->y2, 780.0);
        }
    }

    unlink(tmpPath);
}

// Test getCropWidth and getCropHeight with CropBox
TEST_F(PageTest_713, GetCropWidthAndHeight_713) {
    const char *pdfData =
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
        "startxref\n216\n%%EOF\n";

    char tmpPath[] = "/tmp/poppler_test_cwh_XXXXXX";
    int fd = mkstemp(tmpPath);
    ASSERT_GE(fd, 0);
    write(fd, pdfData, strlen(pdfData));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        if (page) {
            EXPECT_DOUBLE_EQ(page->getCropWidth(), 590.0);
            EXPECT_DOUBLE_EQ(page->getCropHeight(), 770.0);
        }
    }

    unlink(tmpPath);
}

// Test getDuration returns default value when not set
TEST_F(PageTest_713, GetDurationDefault_713) {
    const char *pdfData =
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
        "startxref\n186\n%%EOF\n";

    char tmpPath[] = "/tmp/poppler_test_dur_XXXXXX";
    int fd = mkstemp(tmpPath);
    ASSERT_GE(fd, 0);
    write(fd, pdfData, strlen(pdfData));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        if (page) {
            // Duration defaults to -1 when not specified
            EXPECT_LE(page->getDuration(), 0.0);
        }
    }

    unlink(tmpPath);
}

// Test getDoc returns the parent document
TEST_F(PageTest_713, GetDocReturnsParentDocument_713) {
    const char *pdfData =
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
        "startxref\n186\n%%EOF\n";

    char tmpPath[] = "/tmp/poppler_test_doc_XXXXXX";
    int fd = mkstemp(tmpPath);
    ASSERT_GE(fd, 0);
    write(fd, pdfData, strlen(pdfData));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        if (page) {
            EXPECT_EQ(page->getDoc(), doc.get());
        }
    }

    unlink(tmpPath);
}

// Test isOk returns true for a valid page
TEST_F(PageTest_713, IsOkReturnsTrueForValidPage_713) {
    const char *pdfData =
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
        "startxref\n186\n%%EOF\n";

    char tmpPath[] = "/tmp/poppler_test_ok_XXXXXX";
    int fd = mkstemp(tmpPath);
    ASSERT_GE(fd, 0);
    write(fd, pdfData, strlen(pdfData));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        if (page) {
            EXPECT_TRUE(page->isOk());
        }
    }

    unlink(tmpPath);
}

// Test getBleedBox returns non-null
TEST_F(PageTest_713, GetBleedBoxReturnsNonNull_713) {
    const char *pdfData =
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
        "startxref\n186\n%%EOF\n";

    char tmpPath[] = "/tmp/poppler_test_bb_XXXXXX";
    int fd = mkstemp(tmpPath);
    ASSERT_GE(fd, 0);
    write(fd, pdfData, strlen(pdfData));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        if (page) {
            ASSERT_NE(page->getBleedBox(), nullptr);
            ASSERT_NE(page->getTrimBox(), nullptr);
            ASSERT_NE(page->getArtBox(), nullptr);
        }
    }

    unlink(tmpPath);
}

// Test hasStandaloneFields returns false for a simple page
TEST_F(PageTest_713, HasStandaloneFieldsReturnsFalse_713) {
    const char *pdfData =
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
        "startxref\n186\n%%EOF\n";

    char tmpPath[] = "/tmp/poppler_test_sf_XXXXXX";
    int fd = mkstemp(tmpPath);
    ASSERT_GE(fd, 0);
    write(fd, pdfData, strlen(pdfData));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        if (page) {
            EXPECT_FALSE(page->hasStandaloneFields());
        }
    }

    unlink(tmpPath);
}

// Test rotation inherited from parent Pages node
TEST_F(PageTest_713, GetRotateInheritedFromParent_713) {
    const char *pdfData =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1/Rotate 270>>endobj\n"
        "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n197\n%%EOF\n";

    char tmpPath[] = "/tmp/poppler_test_inhrot_XXXXXX";
    int fd = mkstemp(tmpPath);
    ASSERT_GE(fd, 0);
    write(fd, pdfData, strlen(pdfData));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        if (page) {
            EXPECT_EQ(page->getRotate(), 270);
        }
    }

    unlink(tmpPath);
}

// Test getPageObj returns a valid dict object
TEST_F(PageTest_713, GetPageObjReturnsDict_713) {
    const char *pdfData =
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
        "startxref\n186\n%%EOF\n";

    char tmpPath[] = "/tmp/poppler_test_po_XXXXXX";
    int fd = mkstemp(tmpPath);
    ASSERT_GE(fd, 0);
    write(fd, pdfData, strlen(pdfData));
    close(fd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpPath));

    if (doc->isOk() && doc->getNumPages() > 0) {
        Page *page = doc->getPage(1);
        if (page) {
            const Object &pageObj = page->getPageObj();
            EXPECT_TRUE(pageObj.isDict());
        }
    }

    unlink(tmpPath);
}
