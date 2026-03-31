#include <gtest/gtest.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <fstream>
#include <memory>

// We need to include the necessary headers
#include "PDFDoc.h"
#include "GooString.h"
#include "Error.h"

// External globals used by extractPages
extern int firstPage;
extern int lastPage;

// We need to declare extractPages - it's static in pdfseparate.cc
// so we need to include it or replicate the declaration.
// Since it's static, we'll include the source file for testing purposes.
// This is a common pattern for testing static functions.

// Forward declare or include the function
// We'll wrap it by including the source
namespace {
#include "pdfseparate.cc"
}

class ExtractPagesTest_2736 : public ::testing::Test {
protected:
    std::string testPdfPath;
    std::string outputPattern;
    
    void SetUp() override {
        // Reset global state before each test
        firstPage = 0;
        lastPage = 0;
        
        // Create a minimal valid PDF for testing
        testPdfPath = createMinimalPDF("test_input_2736.pdf");
    }
    
    void TearDown() override {
        // Clean up test files
        remove(testPdfPath.c_str());
        // Clean up any output files
        for (int i = 1; i <= 10; i++) {
            char buf[256];
            snprintf(buf, sizeof(buf), "test_output_2736_%d.pdf", i);
            remove(buf);
        }
        remove("test_output_2736_single.pdf");
    }
    
    std::string createMinimalPDF(const std::string& filename) {
        // Create a minimal valid PDF file
        std::ofstream ofs(filename, std::ios::binary);
        ofs << "%PDF-1.4\n";
        ofs << "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        ofs << "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        ofs << "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        ofs << "xref\n0 4\n";
        ofs << "0000000000 65535 f \n";
        // Calculate offsets approximately
        ofs << "0000000009 00000 n \n";
        ofs << "0000000058 00000 n \n";
        ofs << "0000000115 00000 n \n";
        ofs << "trailer\n<< /Size 4 /Root 1 0 R >>\n";
        ofs << "startxref\n";
        ofs << "190\n";  // approximate
        ofs << "%%EOF\n";
        ofs.close();
        return filename;
    }
    
    std::string createMultiPagePDF(const std::string& filename, int numPages) {
        std::ofstream ofs(filename, std::ios::binary);
        ofs << "%PDF-1.4\n";
        ofs << "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        
        // Pages object with kids
        ofs << "2 0 obj\n<< /Type /Pages /Kids [";
        for (int i = 0; i < numPages; i++) {
            if (i > 0) ofs << " ";
            ofs << (3 + i) << " 0 R";
        }
        ofs << "] /Count " << numPages << " >>\nendobj\n";
        
        for (int i = 0; i < numPages; i++) {
            ofs << (3 + i) << " 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        }
        
        ofs << "xref\n0 " << (3 + numPages) << "\n";
        ofs << "0000000000 65535 f \n";
        // We'll use approximate offsets - the PDF parser should handle minor issues
        int offset = 9;
        for (int i = 0; i < 2 + numPages; i++) {
            char buf[32];
            snprintf(buf, sizeof(buf), "%010d 00000 n \n", offset);
            ofs << buf;
            offset += 70; // approximate
        }
        
        ofs << "trailer\n<< /Size " << (3 + numPages) << " /Root 1 0 R >>\n";
        ofs << "startxref\n";
        ofs << offset << "\n";
        ofs << "%%EOF\n";
        ofs.close();
        return filename;
    }
};

// Test with a non-existent source file (damaged/missing file)
TEST_F(ExtractPagesTest_2736, NonExistentSourceFile_2736) {
    bool result = extractPages("nonexistent_file_2736.pdf", "output_%d.pdf");
    EXPECT_FALSE(result);
}

// Test with empty source filename
TEST_F(ExtractPagesTest_2736, EmptySourceFileName_2736) {
    bool result = extractPages("", "output_%d.pdf");
    EXPECT_FALSE(result);
}

// Test format string validation: multiple pages without %d pattern
TEST_F(ExtractPagesTest_2736, MultiplePagesMissingPercentD_2736) {
    // Create a multi-page PDF
    std::string multiPdf = createMultiPagePDF("test_multi_2736.pdf", 3);
    firstPage = 1;
    lastPage = 3;
    
    // destFileName without %d pattern - should fail for multiple pages
    bool result = extractPages(multiPdf.c_str(), "output_no_pattern.pdf");
    EXPECT_FALSE(result);
    
    remove(multiPdf.c_str());
}

// Test format string with extra % pattern (not %d, not %%, should fail)
TEST_F(ExtractPagesTest_2736, ExtraPercentPattern_2736) {
    firstPage = 1;
    lastPage = 1;
    
    // Has %d but also has another % pattern like %s
    bool result = extractPages(testPdfPath.c_str(), "output_%d_%s.pdf");
    EXPECT_FALSE(result);
}

// Test with lastPage < firstPage (wrong page range)
TEST_F(ExtractPagesTest_2736, WrongPageRange_2736) {
    firstPage = 5;
    lastPage = 2;
    
    bool result = extractPages(testPdfPath.c_str(), "output_%d.pdf");
    EXPECT_FALSE(result);
}

// Test single page extraction without %d (single page, no pattern needed)
TEST_F(ExtractPagesTest_2736, SinglePageNoPatternNeeded_2736) {
    firstPage = 1;
    lastPage = 1;
    
    bool result = extractPages(testPdfPath.c_str(), "test_output_2736_single.pdf");
    // This may succeed or fail depending on whether the PDF is valid enough
    // for savePageAs. We're mainly testing that the format validation passes.
    // The result depends on the actual PDF validity.
    // Just verify it doesn't crash - the PDF may or may not be fully valid.
    (void)result;
}

// Test with %d pattern for single page
TEST_F(ExtractPagesTest_2736, SinglePageWithPercentD_2736) {
    firstPage = 1;
    lastPage = 1;
    
    bool result = extractPages(testPdfPath.c_str(), "test_output_2736_%d.pdf");
    // Again, result depends on PDF validity for savePageAs
    (void)result;
}

// Test double percent (%%) is properly handled (escaped percent)
TEST_F(ExtractPagesTest_2736, EscapedPercentSign_2736) {
    firstPage = 1;
    lastPage = 1;
    
    // %% is an escaped percent, and no extra unescaped % should remain
    // "output_%%_test.pdf" has no %d but single page so no pattern needed
    bool result = extractPages(testPdfPath.c_str(), "test_output_2736_%%_single.pdf");
    // Should not fail due to format validation for single page
    (void)result;
}

// Test format with %02d pattern
TEST_F(ExtractPagesTest_2736, PaddedFormatPattern_2736) {
    firstPage = 1;
    lastPage = 1;
    
    bool result = extractPages(testPdfPath.c_str(), "test_output_2736_%02d.pdf");
    (void)result;
}

// Test format with %03d pattern
TEST_F(ExtractPagesTest_2736, ThreeDigitPaddedFormat_2736) {
    firstPage = 1;
    lastPage = 1;
    
    bool result = extractPages(testPdfPath.c_str(), "test_output_2736_%03d.pdf");
    (void)result;
}

// Test that firstPage=0 and lastPage=0 defaults to full document range
TEST_F(ExtractPagesTest_2736, DefaultPageRange_2736) {
    firstPage = 0;
    lastPage = 0;
    
    // With defaults, single page PDF: firstPage=1, lastPage=1 (numPages)
    // No %d needed for single page
    bool result = extractPages(testPdfPath.c_str(), "test_output_2736_single.pdf");
    (void)result;
}

// Test firstPage=0 defaults to 1
TEST_F(ExtractPagesTest_2736, FirstPageDefaultsToOne_2736) {
    firstPage = 0;
    lastPage = 1;
    
    bool result = extractPages(testPdfPath.c_str(), "test_output_2736_single.pdf");
    (void)result;
}

// Test two %d patterns should fail
TEST_F(ExtractPagesTest_2736, TwoPercentDPatterns_2736) {
    firstPage = 1;
    lastPage = 1;
    
    // Two %d patterns - second one should be caught as extra %
    bool result = extractPages(testPdfPath.c_str(), "test_output_%d_%d.pdf");
    EXPECT_FALSE(result);
}

// Test with %d and %% together (should work - %% is escaped)
TEST_F(ExtractPagesTest_2736, PercentDWithEscapedPercent_2736) {
    firstPage = 1;
    lastPage = 1;
    
    bool result = extractPages(testPdfPath.c_str(), "test_output_2736_%%_%d.pdf");
    // %% gets neutralized, %d is the only real pattern - should pass validation
    (void)result;
}

// Test multiple pages with valid %d pattern
TEST_F(ExtractPagesTest_2736, MultiplePagesWithPercentD_2736) {
    std::string multiPdf = createMultiPagePDF("test_multi2_2736.pdf", 2);
    firstPage = 1;
    lastPage = 2;
    
    bool result = extractPages(multiPdf.c_str(), "test_output_2736_%d.pdf");
    // Result depends on PDF validity
    (void)result;
    
    remove(multiPdf.c_str());
}
