#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>

#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

namespace {

class PDFDocTest_967 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a minimal valid PDF in a temp file and return the filename
    std::string createMinimalPDF() {
        std::string filename = "test_minimal_967.pdf";
        std::ofstream out(filename, std::ios::binary);
        out << "%PDF-1.4\n";
        out << "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        out << "2 0 obj\n<< /Type /Pages /Kids [] /Count 0 >>\nendobj\n";
        out << "xref\n0 3\n";
        out << "0000000000 65535 f \n";
        out << "0000000009 00000 n \n";
        out << "0000000058 00000 n \n";
        out << "trailer\n<< /Size 3 /Root 1 0 R >>\n";
        out << "startxref\n108\n%%EOF\n";
        out.close();
        tempFiles_.push_back(filename);
        return filename;
    }

    // Helper to create a minimal PDF with one page
    std::string createOnePage PDF() {
        std::string filename = "test_onepage_967.pdf";
        std::ofstream out(filename, std::ios::binary);
        // A minimal PDF with 1 page
        std::string content;
        content += "%PDF-1.4\n";
        content += "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        content += "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        content += "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";

        // Calculate offsets
        // This is a simplified approach; offsets may not be perfectly accurate
        // but poppler is somewhat forgiving for test purposes
        size_t obj1_offset = 9;
        size_t obj2_offset = 58;
        size_t obj3_offset = 115;
        size_t xref_offset = content.size();

        // Write xref
        content += "xref\n0 4\n";
        char buf[64];
        snprintf(buf, sizeof(buf), "%010zu 65535 f \n", (size_t)0);
        content += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", obj1_offset);
        content += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", obj2_offset);
        content += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", obj3_offset);
        content += buf;
        content += "trailer\n<< /Size 4 /Root 1 0 R >>\n";
        content += "startxref\n";
        snprintf(buf, sizeof(buf), "%zu", xref_offset);
        content += buf;
        content += "\n%%EOF\n";

        out << content;
        out.close();
        tempFiles_.push_back(filename);
        return filename;
    }

    std::unique_ptr<PDFDoc> loadPDF(const std::string& filename) {
        auto gooFilename = std::make_unique<GooString>(filename);
        return std::make_unique<PDFDoc>(std::move(gooFilename), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    }

    void TearDown() override {
        for (const auto& f : tempFiles_) {
            std::remove(f.c_str());
        }
    }

    std::vector<std::string> tempFiles_;
};

// Test loading a non-existent file
TEST_F(PDFDocTest_967, LoadNonExistentFile_967) {
    auto gooFilename = std::make_unique<GooString>("nonexistent_file_967.pdf");
    PDFDoc doc(std::move(gooFilename), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    EXPECT_FALSE(doc.isOk());
    EXPECT_NE(doc.getErrorCode(), 0);
}

// Test loading a valid minimal PDF
TEST_F(PDFDocTest_967, LoadValidMinimalPDF_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    EXPECT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 0);
}

// Test getNumPages on a zero-page PDF
TEST_F(PDFDocTest_967, GetNumPagesZero_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getNumPages(), 0);
}

// Test PDF version
TEST_F(PDFDocTest_967, GetPDFVersion_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMajorVersion(), 1);
    EXPECT_EQ(doc->getPDFMinorVersion(), 4);
}

// Test okToCopy on an unencrypted PDF (should return true)
TEST_F(PDFDocTest_967, OkToCopyUnencrypted_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToCopy());
}

// Test okToCopy with ignoreOwnerPW=true on unencrypted PDF
TEST_F(PDFDocTest_967, OkToCopyIgnoreOwnerPWUnencrypted_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToCopy(true));
}

// Test okToCopy with ignoreOwnerPW=false on unencrypted PDF
TEST_F(PDFDocTest_967, OkToCopyNoIgnoreOwnerPWUnencrypted_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToCopy(false));
}

// Test okToPrint on unencrypted PDF
TEST_F(PDFDocTest_967, OkToPrintUnencrypted_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrint());
}

// Test okToPrintHighRes on unencrypted PDF
TEST_F(PDFDocTest_967, OkToPrintHighResUnencrypted_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrintHighRes());
}

// Test okToChange on unencrypted PDF
TEST_F(PDFDocTest_967, OkToChangeUnencrypted_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToChange());
}

// Test okToAddNotes on unencrypted PDF
TEST_F(PDFDocTest_967, OkToAddNotesUnencrypted_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAddNotes());
}

// Test okToFillForm on unencrypted PDF
TEST_F(PDFDocTest_967, OkToFillFormUnencrypted_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToFillForm());
}

// Test okToAccessibility on unencrypted PDF
TEST_F(PDFDocTest_967, OkToAccessibilityUnencrypted_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAccessibility());
}

// Test okToAssemble on unencrypted PDF
TEST_F(PDFDocTest_967, OkToAssembleUnencrypted_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAssemble());
}

// Test isEncrypted on unencrypted PDF
TEST_F(PDFDocTest_967, IsNotEncrypted_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isEncrypted());
}

// Test getXRef returns non-null
TEST_F(PDFDocTest_967, GetXRefNotNull_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getXRef(), nullptr);
}

// Test getCatalog returns non-null
TEST_F(PDFDocTest_967, GetCatalogNotNull_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getCatalog(), nullptr);
}

// Test getFileName returns the filename
TEST_F(PDFDocTest_967, GetFileName_967) {
    std::string filename = createMinimalPDF();
    auto gooFilename = std::make_unique<GooString>(filename);
    std::string expectedName = filename;
    PDFDoc doc(std::move(gooFilename), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    ASSERT_TRUE(doc.isOk());
    const GooString* fn = doc.getFileName();
    ASSERT_NE(fn, nullptr);
    EXPECT_EQ(fn->toStr(), expectedName);
}

// Test ErrorPDFDoc creates an error doc
TEST_F(PDFDocTest_967, ErrorPDFDoc_967) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("error_test.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    EXPECT_FALSE(errorDoc->isOk());
    EXPECT_EQ(errorDoc->getErrorCode(), 1);
}

// Test loading corrupted/invalid content
TEST_F(PDFDocTest_967, LoadCorruptedFile_967) {
    std::string filename = "test_corrupted_967.pdf";
    std::ofstream out(filename, std::ios::binary);
    out << "This is not a valid PDF file at all.";
    out.close();
    tempFiles_.push_back(filename);

    auto doc = loadPDF(filename);
    // The doc may or may not be ok depending on how forgiving poppler is,
    // but we test that it doesn't crash
    // If not ok, error code should be non-zero
    if (!doc->isOk()) {
        EXPECT_NE(doc->getErrorCode(), 0);
    }
}

// Test getBaseStream returns non-null for valid doc
TEST_F(PDFDocTest_967, GetBaseStreamNotNull_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getBaseStream(), nullptr);
}

// Test isLinearized on a non-linearized PDF
TEST_F(PDFDocTest_967, IsNotLinearized_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isLinearized(false));
}

// Test getDocInfo on a PDF without doc info
TEST_F(PDFDocTest_967, GetDocInfoNoInfo_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    Object info = doc->getDocInfo();
    // Should be null or none type since no info dict
    EXPECT_TRUE(info.isNull() || info.isNone() || info.isDict());
}

// Test readMetadata on PDF without metadata
TEST_F(PDFDocTest_967, ReadMetadataNoMetadata_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    auto metadata = doc->readMetadata();
    // No metadata expected, should be nullptr or empty
    // Not crashing is the main check
}

// Test getPage with invalid page number on empty PDF
TEST_F(PDFDocTest_967, GetPageInvalidPageNumber_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getNumPages(), 0);
    // Accessing page 0 or 1 on a 0-page doc
    Page* p = doc->getPage(1);
    EXPECT_EQ(p, nullptr);
}

// Test PDFSubtype on a non-subtyped PDF
TEST_F(PDFDocTest_967, GetPDFSubtype_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    // For a generic PDF, subtype should be none/unknown
    PDFSubtype subtype = doc->getPDFSubtype();
    EXPECT_EQ(subtype, subtypeNull);
}

// Test hasJavascript on a simple PDF without JS
TEST_F(PDFDocTest_967, HasNoJavascript_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->hasJavascript());
}

} // namespace
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <fstream>
#include <cstdio>

#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

namespace {

class PDFDocTest_967 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::string createMinimalPDF() {
        std::string filename = "test_minimal_967.pdf";
        std::ofstream out(filename, std::ios::binary);
        out << "%PDF-1.4\n";
        out << "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        out << "2 0 obj\n<< /Type /Pages /Kids [] /Count 0 >>\nendobj\n";
        out << "xref\n0 3\n";
        out << "0000000000 65535 f \n";
        out << "0000000009 00000 n \n";
        out << "0000000058 00000 n \n";
        out << "trailer\n<< /Size 3 /Root 1 0 R >>\n";
        out << "startxref\n108\n%%EOF\n";
        out.close();
        tempFiles_.push_back(filename);
        return filename;
    }

    std::unique_ptr<PDFDoc> loadPDF(const std::string& filename) {
        auto gooFilename = std::make_unique<GooString>(filename);
        return std::make_unique<PDFDoc>(std::move(gooFilename), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    }

    void TearDown() override {
        for (const auto& f : tempFiles_) {
            std::remove(f.c_str());
        }
    }

    std::vector<std::string> tempFiles_;
};

TEST_F(PDFDocTest_967, LoadNonExistentFile_967) {
    auto gooFilename = std::make_unique<GooString>("nonexistent_file_967.pdf");
    PDFDoc doc(std::move(gooFilename), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    EXPECT_FALSE(doc.isOk());
    EXPECT_NE(doc.getErrorCode(), 0);
}

TEST_F(PDFDocTest_967, LoadValidMinimalPDF_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    EXPECT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 0);
}

TEST_F(PDFDocTest_967, GetNumPagesZero_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getNumPages(), 0);
}

TEST_F(PDFDocTest_967, GetPDFVersion_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getPDFMajorVersion(), 1);
    EXPECT_EQ(doc->getPDFMinorVersion(), 4);
}

TEST_F(PDFDocTest_967, OkToCopyUnencrypted_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToCopy());
}

TEST_F(PDFDocTest_967, OkToCopyIgnoreOwnerPWTrue_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToCopy(true));
}

TEST_F(PDFDocTest_967, OkToCopyIgnoreOwnerPWFalse_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToCopy(false));
}

TEST_F(PDFDocTest_967, OkToPrintUnencrypted_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrint());
}

TEST_F(PDFDocTest_967, OkToPrintHighResUnencrypted_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrintHighRes());
}

TEST_F(PDFDocTest_967, OkToChangeUnencrypted_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToChange());
}

TEST_F(PDFDocTest_967, OkToAddNotesUnencrypted_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAddNotes());
}

TEST_F(PDFDocTest_967, OkToFillFormUnencrypted_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToFillForm());
}

TEST_F(PDFDocTest_967, OkToAccessibilityUnencrypted_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAccessibility());
}

TEST_F(PDFDocTest_967, OkToAssembleUnencrypted_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToAssemble());
}

TEST_F(PDFDocTest_967, IsNotEncrypted_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isEncrypted());
}

TEST_F(PDFDocTest_967, GetXRefNotNull_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getXRef(), nullptr);
}

TEST_F(PDFDocTest_967, GetCatalogNotNull_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getCatalog(), nullptr);
}

TEST_F(PDFDocTest_967, GetFileName_967) {
    std::string filename = createMinimalPDF();
    auto gooFilename = std::make_unique<GooString>(filename);
    PDFDoc doc(std::move(gooFilename), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    ASSERT_TRUE(doc.isOk());
    const GooString* fn = doc.getFileName();
    ASSERT_NE(fn, nullptr);
    EXPECT_EQ(fn->toStr(), filename);
}

TEST_F(PDFDocTest_967, ErrorPDFDoc_967) {
    auto errorDoc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("error_test.pdf"));
    ASSERT_NE(errorDoc, nullptr);
    EXPECT_FALSE(errorDoc->isOk());
    EXPECT_EQ(errorDoc->getErrorCode(), 1);
}

TEST_F(PDFDocTest_967, LoadCorruptedFile_967) {
    std::string filename = "test_corrupted_967.pdf";
    std::ofstream out(filename, std::ios::binary);
    out << "This is not a valid PDF file at all.";
    out.close();
    tempFiles_.push_back(filename);

    auto doc = loadPDF(filename);
    if (!doc->isOk()) {
        EXPECT_NE(doc->getErrorCode(), 0);
    }
}

TEST_F(PDFDocTest_967, GetBaseStreamNotNull_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_NE(doc->getBaseStream(), nullptr);
}

TEST_F(PDFDocTest_967, IsNotLinearized_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isLinearized(false));
}

TEST_F(PDFDocTest_967, GetDocInfoNoInfo_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    Object info = doc->getDocInfo();
    EXPECT_TRUE(info.isNull() || info.isNone() || info.isDict());
}

TEST_F(PDFDocTest_967, ReadMetadataNoMetadata_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    auto metadata = doc->readMetadata();
    // No metadata expected
}

TEST_F(PDFDocTest_967, GetPageInvalidPageNumber_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_EQ(doc->getNumPages(), 0);
    Page* p = doc->getPage(1);
    EXPECT_EQ(p, nullptr);
}

TEST_F(PDFDocTest_967, HasNoJavascript_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->hasJavascript());
}

TEST_F(PDFDocTest_967, XRefOkToCopyDelegatesToXRef_967) {
    std::string filename = createMinimalPDF();
    auto doc = loadPDF(filename);
    ASSERT_TRUE(doc->isOk());
    XRef* xref = doc->getXRef();
    ASSERT_NE(xref, nullptr);
    // Both should give same result for unencrypted doc
    EXPECT_EQ(doc->okToCopy(false), xref->okToCopy(false));
    EXPECT_EQ(doc->okToCopy(true), xref->okToCopy(true));
}

TEST_F(PDFDocTest_967, EmptyFileError_967) {
    std::string filename = "test_empty_967.pdf";
    std::ofstream out(filename, std::ios::binary);
    out.close();
    tempFiles_.push_back(filename);

    auto doc = loadPDF(filename);
    EXPECT_FALSE(doc->isOk());
}

} // namespace
