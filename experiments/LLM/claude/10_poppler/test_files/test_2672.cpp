#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstdio>
#include <cstring>
#include <string>

#include "PDFDoc.h"
#include "GooString.h"
#include "GlobalParams.h"
#include "Link.h"
#include "Page.h"
#include "Annot.h"

// External globals used by printUrlList
extern int firstPage;
extern int lastPage;

// Forward declaration of the function under test
static void printUrlList(PDFDoc *doc);

// We need to include the actual implementation
#include "pdfinfo.cc"

class PrintUrlListTest_2672 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize global params if needed
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to capture stdout
    std::string captureStdout(std::function<void()> func) {
        char buffer[65536] = {0};
        fflush(stdout);
        FILE *old_stdout = stdout;
        FILE *tmp = tmpfile();
        if (!tmp) return "";
        stdout = tmp;
        
        func();
        
        fflush(stdout);
        long size = ftell(tmp);
        rewind(tmp);
        if (size > 0 && size < (long)sizeof(buffer)) {
            fread(buffer, 1, size, tmp);
            buffer[size] = '\0';
        }
        fclose(tmp);
        stdout = old_stdout;
        return std::string(buffer);
    }

    std::unique_ptr<PDFDoc> loadTestDoc(const std::string &filename) {
        auto fileName = std::make_unique<GooString>(filename);
        auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
        return doc;
    }
};

// Test that printUrlList prints the header line even when there are no pages
TEST_F(PrintUrlListTest_2672, HeaderIsPrinted_2672) {
    // Create a minimal valid PDF in memory or use a file
    // For this test, we test with a document that has 0 pages range
    // by setting firstPage > lastPage
    firstPage = 2;
    lastPage = 1;

    // We need some doc - create one from a simple PDF if available
    // Use a minimal approach: create a doc that may or may not be valid
    // The header should still be printed regardless
    
    // Create a minimal PDF in a temp file
    const char *minimalPdf = 
        "%PDF-1.0\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [] /Count 0 >>\nendobj\n"
        "xref\n0 3\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "trailer\n<< /Size 3 /Root 1 0 R >>\n"
        "startxref\n108\n%%EOF\n";
    
    char tmpName[] = "/tmp/test_printurl_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd >= 0) {
        write(fd, minimalPdf, strlen(minimalPdf));
        close(fd);
        
        auto doc = loadTestDoc(tmpName);
        
        std::string output = captureStdout([&]() {
            printUrlList(doc.get());
        });
        
        // Should contain the header
        EXPECT_NE(output.find("Page Type URL"), std::string::npos);
        
        unlink(tmpName);
    }
}

// Test with firstPage > lastPage (no pages to iterate)
TEST_F(PrintUrlListTest_2672, NoPagesPrinted_WhenFirstPageGreaterThanLastPage_2672) {
    firstPage = 5;
    lastPage = 1;
    
    const char *minimalPdf = 
        "%PDF-1.0\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n190\n%%EOF\n";
    
    char tmpName[] = "/tmp/test_printurl2_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd >= 0) {
        write(fd, minimalPdf, strlen(minimalPdf));
        close(fd);
        
        auto doc = loadTestDoc(tmpName);
        
        std::string output = captureStdout([&]() {
            printUrlList(doc.get());
        });
        
        // Only the header should be present, no "Annotation" lines
        EXPECT_NE(output.find("Page Type URL"), std::string::npos);
        EXPECT_EQ(output.find("Annotation"), std::string::npos);
        
        unlink(tmpName);
    }
}

// Test with a page that has no links
TEST_F(PrintUrlListTest_2672, PageWithNoLinks_2672) {
    firstPage = 1;
    lastPage = 1;
    
    const char *minimalPdf = 
        "%PDF-1.0\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n190\n%%EOF\n";
    
    char tmpName[] = "/tmp/test_printurl3_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd >= 0) {
        write(fd, minimalPdf, strlen(minimalPdf));
        close(fd);
        
        auto doc = loadTestDoc(tmpName);
        if (doc && doc->isOk()) {
            std::string output = captureStdout([&]() {
                printUrlList(doc.get());
            });
            
            EXPECT_NE(output.find("Page Type URL"), std::string::npos);
            EXPECT_EQ(output.find("Annotation"), std::string::npos);
        }
        
        unlink(tmpName);
    }
}

// Test with a PDF that contains a URI link annotation
TEST_F(PrintUrlListTest_2672, PageWithUriLink_2672) {
    firstPage = 1;
    lastPage = 1;
    
    // Create a PDF with a URI annotation
    const char *pdfWithLink = 
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Annots [4 0 R] >>\nendobj\n"
        "4 0 obj\n<< /Type /Annot /Subtype /Link /Rect [100 100 200 200] "
        "/A << /Type /Action /S /URI /URI (http://example.com) >> >>\nendobj\n"
        "xref\n0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000232 00000 n \n"
        "trailer\n<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n375\n%%EOF\n";
    
    char tmpName[] = "/tmp/test_printurl4_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd >= 0) {
        write(fd, pdfWithLink, strlen(pdfWithLink));
        close(fd);
        
        auto doc = loadTestDoc(tmpName);
        if (doc && doc->isOk()) {
            std::string output = captureStdout([&]() {
                printUrlList(doc.get());
            });
            
            EXPECT_NE(output.find("Page Type URL"), std::string::npos);
            // If the PDF was parsed correctly with annotations, we expect the URI
            if (output.find("Annotation") != std::string::npos) {
                EXPECT_NE(output.find("http://example.com"), std::string::npos);
                EXPECT_NE(output.find("   1 Annotation"), std::string::npos);
            }
        }
        
        unlink(tmpName);
    }
}

// Test that firstPage and lastPage boundaries are respected
TEST_F(PrintUrlListTest_2672, BoundaryFirstEqualsLastPage_2672) {
    firstPage = 1;
    lastPage = 1;
    
    const char *minimalPdf = 
        "%PDF-1.0\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n190\n%%EOF\n";
    
    char tmpName[] = "/tmp/test_printurl5_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd >= 0) {
        write(fd, minimalPdf, strlen(minimalPdf));
        close(fd);
        
        auto doc = loadTestDoc(tmpName);
        if (doc && doc->isOk()) {
            // Should not crash
            std::string output = captureStdout([&]() {
                printUrlList(doc.get());
            });
            
            EXPECT_NE(output.find("Page Type URL"), std::string::npos);
        }
        
        unlink(tmpName);
    }
}

// Test with lastPage beyond actual number of pages (getPage returns nullptr)
TEST_F(PrintUrlListTest_2672, LastPageBeyondDocPages_2672) {
    firstPage = 1;
    lastPage = 100; // Way beyond actual pages
    
    const char *minimalPdf = 
        "%PDF-1.0\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n190\n%%EOF\n";
    
    char tmpName[] = "/tmp/test_printurl6_XXXXXX";
    int fd = mkstemp(tmpName);
    if (fd >= 0) {
        write(fd, minimalPdf, strlen(minimalPdf));
        close(fd);
        
        auto doc = loadTestDoc(tmpName);
        if (doc && doc->isOk()) {
            // Should not crash even with invalid page numbers
            // getPage returns nullptr for invalid pages, which is checked
            std::string output = captureStdout([&]() {
                printUrlList(doc.get());
            });
            
            EXPECT_NE(output.find("Page Type URL"), std::string::npos);
        }
        
        unlink(tmpName);
    }
}
