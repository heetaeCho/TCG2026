#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>

#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

class PDFDocGetPDFMinorVersionTest_995 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a minimal valid PDF in memory with a given header version
    std::string createMinimalPDF(int majorVersion, int minorVersion, int catalogMajor = -1, int catalogMinor = -1) {
        std::ostringstream pdf;
        pdf << "%PDF-" << majorVersion << "." << minorVersion << "\n";

        // Object 1: Catalog
        std::string catalogDict;
        if (catalogMajor > 0 && catalogMinor >= 0) {
            catalogDict = "/Type /Catalog /Pages 2 0 R /Version /" + 
                          std::to_string(catalogMajor) + "." + std::to_string(catalogMinor);
        } else {
            catalogDict = "/Type /Catalog /Pages 2 0 R";
        }
        
        pdf << "1 0 obj\n<< " << catalogDict << " >>\nendobj\n";

        // Object 2: Pages
        pdf << "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";

        // Object 3: Page
        pdf << "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";

        // XRef table
        std::string body = pdf.str();
        size_t xrefOffset = body.size();

        pdf << "xref\n";
        pdf << "0 4\n";
        pdf << "0000000000 65535 f \n";
        
        // Calculate offsets - find each object start
        std::string fullContent = body;
        size_t obj1Pos = fullContent.find("1 0 obj");
        size_t obj2Pos = fullContent.find("2 0 obj");
        size_t obj3Pos = fullContent.find("3 0 obj");

        char buf[21];
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", obj1Pos);
        pdf << buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", obj2Pos);
        pdf << buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", obj3Pos);
        pdf << buf;

        pdf << "trailer\n<< /Size 4 /Root 1 0 R >>\n";
        pdf << "startxref\n" << xrefOffset << "\n%%EOF\n";

        return pdf.str();
    }

    std::unique_ptr<PDFDoc> createPDFDocFromString(const std::string &pdfContent) {
        // Write to a temp file
        std::string tmpFile = "/tmp/test_pdfdoc_995_" + std::to_string(fileCounter++) + ".pdf";
        tempFiles.push_back(tmpFile);
        
        std::ofstream ofs(tmpFile, std::ios::binary);
        ofs.write(pdfContent.data(), pdfContent.size());
        ofs.close();

        auto fileName = std::make_unique<GooString>(tmpFile.c_str());
        return std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }

    void TearDown() override {
        for (const auto &f : tempFiles) {
            std::remove(f.c_str());
        }
    }

    std::vector<std::string> tempFiles;
    static int fileCounter;
};

int PDFDocGetPDFMinorVersionTest_995::fileCounter = 0;

// Test: Header version only (no catalog version), should return header minor version
TEST_F(PDFDocGetPDFMinorVersionTest_995, HeaderVersionOnly_ReturnsHeaderMinor_995) {
    std::string pdf = createMinimalPDF(1, 4);
    auto doc = createPDFDocFromString(pdf);
    
    if (doc && doc->isOk()) {
        // With no /Version in catalog, catalog major version should be -1
        // headerPdfMajorVersion > catalogMajorVersion, so return headerPdfMinorVersion
        EXPECT_EQ(doc->getPDFMinorVersion(), 4);
    }
}

// Test: Header version 1.7, no catalog version
TEST_F(PDFDocGetPDFMinorVersionTest_995, HeaderVersion17_NoCatalog_995) {
    std::string pdf = createMinimalPDF(1, 7);
    auto doc = createPDFDocFromString(pdf);
    
    if (doc && doc->isOk()) {
        EXPECT_EQ(doc->getPDFMinorVersion(), 7);
    }
}

// Test: Header 1.4, catalog version 1.7 => catalog major == header major, max(4,7) = 7
TEST_F(PDFDocGetPDFMinorVersionTest_995, CatalogMinorHigherThanHeader_ReturnsMax_995) {
    std::string pdf = createMinimalPDF(1, 4, 1, 7);
    auto doc = createPDFDocFromString(pdf);
    
    if (doc && doc->isOk()) {
        // catalogMajor(1) == headerMajor(1), so return max(4, 7) = 7
        EXPECT_EQ(doc->getPDFMinorVersion(), 7);
    }
}

// Test: Header 1.7, catalog version 1.4 => catalog major == header major, max(7,4) = 7
TEST_F(PDFDocGetPDFMinorVersionTest_995, HeaderMinorHigherThanCatalog_ReturnsMax_995) {
    std::string pdf = createMinimalPDF(1, 7, 1, 4);
    auto doc = createPDFDocFromString(pdf);
    
    if (doc && doc->isOk()) {
        // catalogMajor(1) == headerMajor(1), so return max(7, 4) = 7
        EXPECT_EQ(doc->getPDFMinorVersion(), 7);
    }
}

// Test: Header 1.4, catalog version 2.0 => catalogMajor(2) > headerMajor(1), return catalog minor
TEST_F(PDFDocGetPDFMinorVersionTest_995, CatalogMajorHigher_ReturnsCatalogMinor_995) {
    std::string pdf = createMinimalPDF(1, 4, 2, 0);
    auto doc = createPDFDocFromString(pdf);
    
    if (doc && doc->isOk()) {
        // catalogMajorVersion(2) > headerPdfMajorVersion(1), return catalog minor = 0
        EXPECT_EQ(doc->getPDFMinorVersion(), 0);
    }
}

// Test: Header 1.5, catalog version 1.5 => same versions, max(5,5) = 5
TEST_F(PDFDocGetPDFMinorVersionTest_995, SameVersions_ReturnsSameMinor_995) {
    std::string pdf = createMinimalPDF(1, 5, 1, 5);
    auto doc = createPDFDocFromString(pdf);
    
    if (doc && doc->isOk()) {
        EXPECT_EQ(doc->getPDFMinorVersion(), 5);
    }
}

// Test: Header version 1.0 (minimum minor version)
TEST_F(PDFDocGetPDFMinorVersionTest_995, MinimumMinorVersion_995) {
    std::string pdf = createMinimalPDF(1, 0);
    auto doc = createPDFDocFromString(pdf);
    
    if (doc && doc->isOk()) {
        EXPECT_EQ(doc->getPDFMinorVersion(), 0);
    }
}

// Test: Header version 1.9 (maximum typical minor version)
TEST_F(PDFDocGetPDFMinorVersionTest_995, MaxMinorVersion_995) {
    std::string pdf = createMinimalPDF(1, 9);
    auto doc = createPDFDocFromString(pdf);
    
    if (doc && doc->isOk()) {
        EXPECT_EQ(doc->getPDFMinorVersion(), 9);
    }
}

// Test: getPDFMajorVersion with header only
TEST_F(PDFDocGetPDFMinorVersionTest_995, MajorVersionHeaderOnly_995) {
    std::string pdf = createMinimalPDF(1, 4);
    auto doc = createPDFDocFromString(pdf);
    
    if (doc && doc->isOk()) {
        EXPECT_EQ(doc->getPDFMajorVersion(), 1);
    }
}

// Test: Header 2.0
TEST_F(PDFDocGetPDFMinorVersionTest_995, HeaderVersion20_995) {
    std::string pdf = createMinimalPDF(2, 0);
    auto doc = createPDFDocFromString(pdf);
    
    if (doc && doc->isOk()) {
        EXPECT_EQ(doc->getPDFMajorVersion(), 2);
        EXPECT_EQ(doc->getPDFMinorVersion(), 0);
    }
}

// Test: isOk returns false for non-existent file
TEST_F(PDFDocGetPDFMinorVersionTest_995, NonExistentFile_NotOk_995) {
    auto fileName = std::make_unique<GooString>("/tmp/nonexistent_file_pdfdoc_995.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    
    EXPECT_FALSE(doc->isOk());
}
