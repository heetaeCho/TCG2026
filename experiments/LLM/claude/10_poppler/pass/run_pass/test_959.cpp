#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>

#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

// Helper to find test PDF files - adjust path as needed
static const char* getTestPdfPath() {
    // Try common test PDF locations in poppler test data
    static const char* paths[] = {
        "./test/unittestcases/WithActualText.pdf",
        "../test/unittestcases/WithActualText.pdf",
        "../../test/unittestcases/WithActualText.pdf",
        nullptr
    };
    for (int i = 0; paths[i]; i++) {
        FILE* f = fopen(paths[i], "r");
        if (f) {
            fclose(f);
            return paths[i];
        }
    }
    return nullptr;
}

class PDFDocTest_959 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadTestDoc(const char* path) {
        if (!path) return nullptr;
        auto fileName = std::make_unique<GooString>(path);
        return std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }
};

// Test: Opening a non-existent file should result in not-ok PDFDoc
TEST_F(PDFDocTest_959, OpenNonExistentFile_959) {
    auto fileName = std::make_unique<GooString>("/nonexistent/path/to/file.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc.isOk());
    EXPECT_NE(doc.getErrorCode(), 0);
}

// Test: ErrorPDFDoc creates a doc with error
TEST_F(PDFDocTest_959, ErrorPDFDocCreation_959) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("error.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    EXPECT_FALSE(errorDoc->isOk());
    EXPECT_EQ(errorDoc->getErrorCode(), 1);
}

// Test: ErrorPDFDoc with different error codes
TEST_F(PDFDocTest_959, ErrorPDFDocDifferentCodes_959) {
    auto errorDoc2 = PDFDoc::ErrorPDFDoc(2, std::make_unique<GooString>("error2.pdf"));
    ASSERT_NE(errorDoc2, nullptr);
    EXPECT_FALSE(errorDoc2->isOk());
    EXPECT_EQ(errorDoc2->getErrorCode(), 2);
}

// Test: Opening a valid PDF file
TEST_F(PDFDocTest_959, OpenValidPDF_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    EXPECT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 0);
}

// Test: getNumPages returns positive for valid doc
TEST_F(PDFDocTest_959, GetNumPages_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    EXPECT_GT(doc->getNumPages(), 0);
}

// Test: getPage with valid page number
TEST_F(PDFDocTest_959, GetPageValid_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    Page* page = doc->getPage(1);
    EXPECT_NE(page, nullptr);
}

// Test: getPage with invalid page number (0 or negative)
TEST_F(PDFDocTest_959, GetPageInvalidZero_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    Page* page = doc->getPage(0);
    EXPECT_EQ(page, nullptr);
}

// Test: getPage with page number beyond range
TEST_F(PDFDocTest_959, GetPageBeyondRange_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    int numPages = doc->getNumPages();
    Page* page = doc->getPage(numPages + 1);
    EXPECT_EQ(page, nullptr);
}

// Test: getCatalog returns non-null for valid doc
TEST_F(PDFDocTest_959, GetCatalog_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getCatalog(), nullptr);
}

// Test: getXRef returns non-null for valid doc
TEST_F(PDFDocTest_959, GetXRef_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getXRef(), nullptr);
}

// Test: getBaseStream returns non-null for valid doc
TEST_F(PDFDocTest_959, GetBaseStream_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getBaseStream(), nullptr);
}

// Test: getFileName returns non-null for file-based doc
TEST_F(PDFDocTest_959, GetFileName_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    const GooString* fileName = doc->getFileName();
    EXPECT_NE(fileName, nullptr);
}

// Test: readMetadata - may return null if no metadata
TEST_F(PDFDocTest_959, ReadMetadata_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    // readMetadata may return nullptr if no metadata stream exists
    auto metadata = doc->readMetadata();
    // Just ensure it doesn't crash; result can be null or non-null
    (void)metadata;
}

// Test: getPDFMajorVersion and getPDFMinorVersion
TEST_F(PDFDocTest_959, GetPDFVersion_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    int major = doc->getPDFMajorVersion();
    int minor = doc->getPDFMinorVersion();
    EXPECT_GE(major, 1);
    EXPECT_LE(major, 2);
    EXPECT_GE(minor, 0);
}

// Test: getPageMediaWidth and getPageMediaHeight for valid page
TEST_F(PDFDocTest_959, GetPageMediaDimensions_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    double width = doc->getPageMediaWidth(1);
    double height = doc->getPageMediaHeight(1);
    EXPECT_GT(width, 0.0);
    EXPECT_GT(height, 0.0);
}

// Test: getPageCropWidth and getPageCropHeight for valid page
TEST_F(PDFDocTest_959, GetPageCropDimensions_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    double cropW = doc->getPageCropWidth(1);
    double cropH = doc->getPageCropHeight(1);
    EXPECT_GT(cropW, 0.0);
    EXPECT_GT(cropH, 0.0);
}

// Test: getPageRotate returns valid rotation value
TEST_F(PDFDocTest_959, GetPageRotate_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    int rotate = doc->getPageRotate(1);
    // Rotation should be 0, 90, 180, or 270
    EXPECT_TRUE(rotate == 0 || rotate == 90 || rotate == 180 || rotate == 270);
}

// Test: isEncrypted for unencrypted file
TEST_F(PDFDocTest_959, IsEncrypted_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    // Most test PDFs are not encrypted
    // Just check it doesn't crash
    bool encrypted = doc->isEncrypted();
    (void)encrypted;
}

// Test: Permission check methods don't crash
TEST_F(PDFDocTest_959, PermissionChecks_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    // For unencrypted docs, these should generally return true
    EXPECT_TRUE(doc->okToPrint());
    EXPECT_TRUE(doc->okToPrintHighRes());
    EXPECT_TRUE(doc->okToChange());
    EXPECT_TRUE(doc->okToCopy());
    EXPECT_TRUE(doc->okToAddNotes());
    EXPECT_TRUE(doc->okToFillForm());
    EXPECT_TRUE(doc->okToAccessibility());
    EXPECT_TRUE(doc->okToAssemble());
}

// Test: getDocInfo returns an Object (may be null dict for simple PDFs)
TEST_F(PDFDocTest_959, GetDocInfo_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    Object info = doc->getDocInfo();
    // Just check it doesn't crash
    (void)info;
}

// Test: getOutline doesn't crash
TEST_F(PDFDocTest_959, GetOutline_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    Outline* outline = doc->getOutline();
    // May be null if no outline
    (void)outline;
}

// Test: isLinearized
TEST_F(PDFDocTest_959, IsLinearized_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    bool linearized = doc->isLinearized(false);
    // Just verify it returns without crashing
    (void)linearized;
}

// Test: hasJavascript
TEST_F(PDFDocTest_959, HasJavascript_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    bool hasJs = doc->hasJavascript();
    (void)hasJs;
}

// Test: getID
TEST_F(PDFDocTest_959, GetID_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    GooString permanentId;
    GooString updateId;
    bool hasId = doc->getID(&permanentId, &updateId);
    (void)hasId;
}

// Test: getOptContentConfig
TEST_F(PDFDocTest_959, GetOptContentConfig_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    const OCGs* ocgs = doc->getOptContentConfig();
    // May be null
    (void)ocgs;
}

// Test: getLinks for valid page
TEST_F(PDFDocTest_959, GetLinks_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    auto links = doc->getLinks(1);
    // links may be empty but should not crash
    (void)links;
}

// Test: getSignatureFields
TEST_F(PDFDocTest_959, GetSignatureFields_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    auto sigFields = doc->getSignatureFields();
    // Typically empty for simple PDFs
    (void)sigFields;
}

// Test: getPDFSubtype
TEST_F(PDFDocTest_959, GetPDFSubtype_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    PDFSubtype subtype = doc->getPDFSubtype();
    (void)subtype;
}

// Test: setDocInfoTitle and getDocInfoTitle roundtrip
TEST_F(PDFDocTest_959, DocInfoTitleRoundtrip_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    auto title = std::make_unique<GooString>("Test Title 959");
    doc->setDocInfoTitle(std::move(title));
    auto retrieved = doc->getDocInfoTitle();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "Test Title 959");
}

// Test: setDocInfoAuthor and getDocInfoAuthor roundtrip
TEST_F(PDFDocTest_959, DocInfoAuthorRoundtrip_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    auto author = std::make_unique<GooString>("Test Author");
    doc->setDocInfoAuthor(std::move(author));
    auto retrieved = doc->getDocInfoAuthor();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "Test Author");
}

// Test: removeDocInfo clears info
TEST_F(PDFDocTest_959, RemoveDocInfo_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoTitle(std::make_unique<GooString>("To Be Removed"));
    doc->removeDocInfo();
    // After removal, getDocInfo should return null object
    Object info = doc->getDocInfo();
    EXPECT_TRUE(info.isNull());
}

// Test: ErrorPDFDoc with null filename
TEST_F(PDFDocTest_959, ErrorPDFDocNullFilename_959) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(3, nullptr);
    ASSERT_NE(errorDoc, nullptr);
    EXPECT_FALSE(errorDoc->isOk());
    EXPECT_EQ(errorDoc->getErrorCode(), 3);
}

// Test: getStructTreeRoot
TEST_F(PDFDocTest_959, GetStructTreeRoot_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    const StructTreeRoot* root = doc->getStructTreeRoot();
    // May be null for PDFs without structure tree
    (void)root;
}

// Test: findDest with non-existent destination
TEST_F(PDFDocTest_959, FindDestNonExistent_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());
    GooString destName("NonExistentDestination12345");
    auto dest = doc->findDest(&destName);
    EXPECT_EQ(dest, nullptr);
}

// Test: setDocInfoStringEntry and getDocInfoStringEntry
TEST_F(PDFDocTest_959, DocInfoStringEntry_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoStringEntry("Subject", std::make_unique<GooString>("Test Subject"));
    auto val = doc->getDocInfoStringEntry("Subject");
    ASSERT_NE(val, nullptr);
    EXPECT_STREQ(val->c_str(), "Test Subject");
}

// Test: setDocInfoSubject roundtrip
TEST_F(PDFDocTest_959, DocInfoSubjectRoundtrip_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoSubject(std::make_unique<GooString>("My Subject"));
    auto retrieved = doc->getDocInfoSubject();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "My Subject");
}

// Test: setDocInfoKeywords roundtrip
TEST_F(PDFDocTest_959, DocInfoKeywordsRoundtrip_959) {
    const char* path = getTestPdfPath();
    if (!path) {
        GTEST_SKIP() << "No test PDF found";
    }
    auto doc = loadTestDoc(path);
    ASSERT_NE(doc, nullptr);
    ASSERT_TRUE(doc->isOk());

    doc->setDocInfoKeywords(std::make_unique<GooString>("key1 key2"));
    auto retrieved = doc->getDocInfoKeywords();
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved->c_str(), "key1 key2");
}
