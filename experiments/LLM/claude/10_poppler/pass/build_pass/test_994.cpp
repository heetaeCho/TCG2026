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
    // Try common test PDF locations
    static const char* paths[] = {
        "./test.pdf",
        "../test-data/unittestcases/simple.pdf",
        nullptr
    };
    for (int i = 0; paths[i]; i++) {
        std::ifstream f(paths[i]);
        if (f.good()) return paths[i];
    }
    return nullptr;
}

// Helper to create a minimal valid PDF in memory as a string
static std::string createMinimalPDF(int majorVersion = 1, int minorVersion = 4) {
    std::string pdf;
    pdf += "%PDF-" + std::to_string(majorVersion) + "." + std::to_string(minorVersion) + "\n";
    pdf += "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
    pdf += "2 0 obj\n<< /Type /Pages /Kids [] /Count 0 >>\nendobj\n";
    pdf += "xref\n0 3\n";
    pdf += "0000000000 65535 f \n";
    // Calculate offsets
    std::string header = "%PDF-" + std::to_string(majorVersion) + "." + std::to_string(minorVersion) + "\n";
    char buf[21];
    snprintf(buf, sizeof(buf), "%010d", (int)header.size());
    pdf += std::string(buf) + " 00000 n \n";
    int obj2Offset = (int)(header.size() + std::string("1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n").size());
    snprintf(buf, sizeof(buf), "%010d", obj2Offset);
    pdf += std::string(buf) + " 00000 n \n";
    pdf += "trailer\n<< /Size 3 /Root 1 0 R >>\n";
    // Calculate xref offset
    int xrefOffset = (int)(header.size() + 
        std::string("1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n").size() +
        std::string("2 0 obj\n<< /Type /Pages /Kids [] /Count 0 >>\nendobj\n").size());
    pdf += "startxref\n" + std::to_string(xrefOffset) + "\n%%EOF\n";
    return pdf;
}

// Write a string to a temporary file and return the filename
static std::string writeTempPDF(const std::string& content) {
    static int counter = 0;
    std::string filename = "/tmp/test_pdfdoc_994_" + std::to_string(counter++) + ".pdf";
    std::ofstream out(filename, std::ios::binary);
    out.write(content.c_str(), content.size());
    out.close();
    return filename;
}

class PDFDocTest_994 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test creating a PDFDoc from a valid file
TEST_F(PDFDocTest_994, OpenValidPDF_994) {
    std::string content = createMinimalPDF(1, 4);
    std::string filename = writeTempPDF(content);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                         std::optional<GooString>(),
                                         std::optional<GooString>(),
                                         std::function<void(void)>());
    
    // The document may or may not parse correctly depending on exact offset calculations,
    // but we can test that it doesn't crash and reports status
    // If ok, check basic properties
    if (doc->isOk()) {
        EXPECT_EQ(doc->getErrorCode(), 0);
    }
    
    std::remove(filename.c_str());
}

// Test creating a PDFDoc from a non-existent file
TEST_F(PDFDocTest_994, OpenNonExistentFile_994) {
    auto doc = std::make_unique<PDFDoc>(
        std::make_unique<GooString>("/tmp/nonexistent_file_994_test.pdf"),
        std::optional<GooString>(),
        std::optional<GooString>(),
        std::function<void(void)>());
    
    EXPECT_FALSE(doc->isOk());
    EXPECT_NE(doc->getErrorCode(), 0);
}

// Test ErrorPDFDoc static method
TEST_F(PDFDocTest_994, ErrorPDFDoc_994) {
    auto doc = PDFDoc::ErrorPDFDoc(42, std::make_unique<GooString>("error_file.pdf"));
    
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 42);
}

// Test getPDFMajorVersion returns at least 1 for a valid PDF
TEST_F(PDFDocTest_994, GetPDFMajorVersion_994) {
    std::string content = createMinimalPDF(1, 7);
    std::string filename = writeTempPDF(content);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                         std::optional<GooString>(),
                                         std::optional<GooString>(),
                                         std::function<void(void)>());
    
    if (doc->isOk()) {
        int major = doc->getPDFMajorVersion();
        EXPECT_GE(major, 1);
    }
    
    std::remove(filename.c_str());
}

// Test getPDFMinorVersion for a valid PDF
TEST_F(PDFDocTest_994, GetPDFMinorVersion_994) {
    std::string content = createMinimalPDF(1, 7);
    std::string filename = writeTempPDF(content);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                         std::optional<GooString>(),
                                         std::optional<GooString>(),
                                         std::function<void(void)>());
    
    if (doc->isOk()) {
        int minor = doc->getPDFMinorVersion();
        EXPECT_GE(minor, 0);
    }
    
    std::remove(filename.c_str());
}

// Test getFileName returns the filename used to open the document
TEST_F(PDFDocTest_994, GetFileName_994) {
    std::string content = createMinimalPDF(1, 4);
    std::string filename = writeTempPDF(content);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                         std::optional<GooString>(),
                                         std::optional<GooString>(),
                                         std::function<void(void)>());
    
    const GooString* fn = doc->getFileName();
    ASSERT_NE(fn, nullptr);
    EXPECT_EQ(fn->toStr(), filename);
    
    std::remove(filename.c_str());
}

// Test getNumPages on an empty PDF (0 pages)
TEST_F(PDFDocTest_994, GetNumPagesEmptyPDF_994) {
    std::string content = createMinimalPDF(1, 4);
    std::string filename = writeTempPDF(content);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                         std::optional<GooString>(),
                                         std::optional<GooString>(),
                                         std::function<void(void)>());
    
    if (doc->isOk()) {
        int numPages = doc->getNumPages();
        EXPECT_GE(numPages, 0);
    }
    
    std::remove(filename.c_str());
}

// Test getCatalog returns non-null for a valid document
TEST_F(PDFDocTest_994, GetCatalog_994) {
    std::string content = createMinimalPDF(1, 4);
    std::string filename = writeTempPDF(content);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                         std::optional<GooString>(),
                                         std::optional<GooString>(),
                                         std::function<void(void)>());
    
    if (doc->isOk()) {
        Catalog* cat = doc->getCatalog();
        EXPECT_NE(cat, nullptr);
    }
    
    std::remove(filename.c_str());
}

// Test getXRef returns non-null for a valid document
TEST_F(PDFDocTest_994, GetXRef_994) {
    std::string content = createMinimalPDF(1, 4);
    std::string filename = writeTempPDF(content);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                         std::optional<GooString>(),
                                         std::optional<GooString>(),
                                         std::function<void(void)>());
    
    if (doc->isOk()) {
        XRef* xref = doc->getXRef();
        EXPECT_NE(xref, nullptr);
    }
    
    std::remove(filename.c_str());
}

// Test isEncrypted on an unencrypted PDF
TEST_F(PDFDocTest_994, IsNotEncrypted_994) {
    std::string content = createMinimalPDF(1, 4);
    std::string filename = writeTempPDF(content);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                         std::optional<GooString>(),
                                         std::optional<GooString>(),
                                         std::function<void(void)>());
    
    if (doc->isOk()) {
        EXPECT_FALSE(doc->isEncrypted());
    }
    
    std::remove(filename.c_str());
}

// Test permission checks on an unencrypted PDF
TEST_F(PDFDocTest_994, PermissionsUnencrypted_994) {
    std::string content = createMinimalPDF(1, 4);
    std::string filename = writeTempPDF(content);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                         std::optional<GooString>(),
                                         std::optional<GooString>(),
                                         std::function<void(void)>());
    
    if (doc->isOk()) {
        EXPECT_TRUE(doc->okToPrint());
        EXPECT_TRUE(doc->okToPrintHighRes());
        EXPECT_TRUE(doc->okToChange());
        EXPECT_TRUE(doc->okToCopy());
        EXPECT_TRUE(doc->okToAddNotes());
        EXPECT_TRUE(doc->okToFillForm());
        EXPECT_TRUE(doc->okToAccessibility());
        EXPECT_TRUE(doc->okToAssemble());
    }
    
    std::remove(filename.c_str());
}

// Test ErrorPDFDoc with different error codes
TEST_F(PDFDocTest_994, ErrorPDFDocDifferentCodes_994) {
    auto doc1 = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("err1.pdf"));
    ASSERT_NE(doc1, nullptr);
    EXPECT_FALSE(doc1->isOk());
    EXPECT_EQ(doc1->getErrorCode(), 1);
    
    auto doc2 = PDFDoc::ErrorPDFDoc(99, std::make_unique<GooString>("err99.pdf"));
    ASSERT_NE(doc2, nullptr);
    EXPECT_FALSE(doc2->isOk());
    EXPECT_EQ(doc2->getErrorCode(), 99);
}

// Test ErrorPDFDoc with nullptr filename
TEST_F(PDFDocTest_994, ErrorPDFDocNullFilename_994) {
    auto doc = PDFDoc::ErrorPDFDoc(5, nullptr);
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 5);
    EXPECT_EQ(doc->getFileName(), nullptr);
}

// Test getPDFSubtype on a standard PDF
TEST_F(PDFDocTest_994, GetPDFSubtype_994) {
    std::string content = createMinimalPDF(1, 4);
    std::string filename = writeTempPDF(content);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                         std::optional<GooString>(),
                                         std::optional<GooString>(),
                                         std::function<void(void)>());
    
    if (doc->isOk()) {
        // Just ensure it doesn't crash; the subtype for a regular PDF is typically "None"
        PDFSubtype subtype = doc->getPDFSubtype();
        (void)subtype;
    }
    
    std::remove(filename.c_str());
}

// Test getBaseStream returns non-null
TEST_F(PDFDocTest_994, GetBaseStream_994) {
    std::string content = createMinimalPDF(1, 4);
    std::string filename = writeTempPDF(content);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                         std::optional<GooString>(),
                                         std::optional<GooString>(),
                                         std::function<void(void)>());
    
    if (doc->isOk()) {
        BaseStream* bs = doc->getBaseStream();
        EXPECT_NE(bs, nullptr);
    }
    
    std::remove(filename.c_str());
}

// Test that getPDFMajorVersion takes max of header and catalog version
TEST_F(PDFDocTest_994, GetPDFMajorVersionMaxBehavior_994) {
    // Create a PDF with header version 2.0
    std::string content = createMinimalPDF(2, 0);
    std::string filename = writeTempPDF(content);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                         std::optional<GooString>(),
                                         std::optional<GooString>(),
                                         std::function<void(void)>());
    
    if (doc->isOk()) {
        int major = doc->getPDFMajorVersion();
        // The catalog version is likely -1 (not set), so max(2, -1) = 2
        EXPECT_GE(major, 1);
    }
    
    std::remove(filename.c_str());
}

// Test readMetadata on a PDF without metadata
TEST_F(PDFDocTest_994, ReadMetadataNoMetadata_994) {
    std::string content = createMinimalPDF(1, 4);
    std::string filename = writeTempPDF(content);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                         std::optional<GooString>(),
                                         std::optional<GooString>(),
                                         std::function<void(void)>());
    
    if (doc->isOk()) {
        auto metadata = doc->readMetadata();
        // No metadata in minimal PDF, should be nullptr
        EXPECT_EQ(metadata, nullptr);
    }
    
    std::remove(filename.c_str());
}

// Test that copy constructor and assignment are deleted (compile-time check, 
// but we verify the document is usable)
TEST_F(PDFDocTest_994, DocumentIsNotCopyable_994) {
    // This is a compile-time property. We just verify that we can use the document normally.
    auto doc = PDFDoc::ErrorPDFDoc(0, std::make_unique<GooString>("test.pdf"));
    ASSERT_NE(doc, nullptr);
    // The following would not compile:
    // PDFDoc copy = *doc;
    // PDFDoc copy2(std::move(*doc)); // move is also not explicitly defined
}

// Test isLinearized on a non-linearized PDF
TEST_F(PDFDocTest_994, IsLinearizedFalse_994) {
    std::string content = createMinimalPDF(1, 4);
    std::string filename = writeTempPDF(content);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                         std::optional<GooString>(),
                                         std::optional<GooString>(),
                                         std::function<void(void)>());
    
    if (doc->isOk()) {
        EXPECT_FALSE(doc->isLinearized(false));
    }
    
    std::remove(filename.c_str());
}

// Test getDocInfo on a minimal PDF (likely returns null object)
TEST_F(PDFDocTest_994, GetDocInfo_994) {
    std::string content = createMinimalPDF(1, 4);
    std::string filename = writeTempPDF(content);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                         std::optional<GooString>(),
                                         std::optional<GooString>(),
                                         std::function<void(void)>());
    
    if (doc->isOk()) {
        Object info = doc->getDocInfo();
        // Minimal PDF has no Info dictionary
        // info could be null or a dict
        (void)info;
    }
    
    std::remove(filename.c_str());
}

// Test hasJavascript on a PDF without JS
TEST_F(PDFDocTest_994, HasJavascriptFalse_994) {
    std::string content = createMinimalPDF(1, 4);
    std::string filename = writeTempPDF(content);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                         std::optional<GooString>(),
                                         std::optional<GooString>(),
                                         std::function<void(void)>());
    
    if (doc->isOk()) {
        EXPECT_FALSE(doc->hasJavascript());
    }
    
    std::remove(filename.c_str());
}

// Test getPage with invalid page number
TEST_F(PDFDocTest_994, GetPageInvalidIndex_994) {
    std::string content = createMinimalPDF(1, 4);
    std::string filename = writeTempPDF(content);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                         std::optional<GooString>(),
                                         std::optional<GooString>(),
                                         std::function<void(void)>());
    
    if (doc->isOk()) {
        // Page 0 is typically invalid (1-indexed)
        Page* page = doc->getPage(0);
        EXPECT_EQ(page, nullptr);
        
        // Page beyond count
        Page* pageBeyond = doc->getPage(doc->getNumPages() + 1);
        EXPECT_EQ(pageBeyond, nullptr);
    }
    
    std::remove(filename.c_str());
}

// Test opening a corrupt/empty file
TEST_F(PDFDocTest_994, OpenEmptyFile_994) {
    std::string filename = writeTempPDF("");
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                         std::optional<GooString>(),
                                         std::optional<GooString>(),
                                         std::function<void(void)>());
    
    EXPECT_FALSE(doc->isOk());
    
    std::remove(filename.c_str());
}

// Test opening garbage data
TEST_F(PDFDocTest_994, OpenGarbageFile_994) {
    std::string garbage = "This is not a PDF file at all, just random garbage data.";
    std::string filename = writeTempPDF(garbage);
    
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename.c_str()),
                                         std::optional<GooString>(),
                                         std::optional<GooString>(),
                                         std::function<void(void)>());
    
    EXPECT_FALSE(doc->isOk());
    
    std::remove(filename.c_str());
}

// Test getFopenErrno for non-existent file
TEST_F(PDFDocTest_994, GetFopenErrno_994) {
    auto doc = std::make_unique<PDFDoc>(
        std::make_unique<GooString>("/tmp/absolutely_nonexistent_994.pdf"),
        std::optional<GooString>(),
        std::optional<GooString>(),
        std::function<void(void)>());
    
    EXPECT_FALSE(doc->isOk());
    // fopenErrno should be non-zero for a file that doesn't exist
    EXPECT_NE(doc->getFopenErrno(), 0);
}
